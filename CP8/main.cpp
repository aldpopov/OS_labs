#include "../include/tools.h"

#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <unordered_set>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <config.yaml> <max_parallel_jobs>" << std::endl;
        return 1;
    }

    const std::string configFile = argv[1];
    int maxParallelJobs;
    try {
        maxParallelJobs = std::stoi(argv[2]);
    } catch (std::invalid_argument&) {
        std::cerr << "Error: Incorrect args types" << std::endl;
        return 1;
    }

    if (argc == 4) {
        mustBreak = argv[3];
    }

    std::ifstream file(configFile);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << configFile << std::endl;
        return 1;
    }

    YAML::Node config = YAML::Load(file);
    file.close();

    std::unordered_set<int> ids;
    for (const auto& job : config["jobs"]) {
        int id;
        try {
            id = job["id"].as<int>();

            if (ids.find(id) != ids.end()) {
                std::cerr << "Error: DAG contains duplicated ids" << std::endl;
                return 1;
            }

            ids.insert(id);
            std::string name = job["name"].as<std::string>();
            jobs[id] = {name, job["dependencies"].as<std::vector<int>>(), job["barrier"].as<std::string>(), job["time"].as<int>()};
        } catch (YAML::Exception&) {
            std::cerr << "Error: Parsing YAML failed" << std::endl;
            return 1;
        }
        graph[id] = job["dependencies"].as<std::vector<int>>();

        if (job["barrier"]) {
            const std::string barrier_name = job["barrier"].as<std::string>();
            if (barriers.find(barrier_name) == barriers.end()) {
                pthread_barrier_t barrier;
                pthread_barrier_init(&barrier, nullptr, job["barrier_count"].as<int>());
                barriers.emplace(barrier_name, barrier);
            }
        }
    }

    if (!ValidateDAG(graph)) {
        return 1;
    }

    for (const auto& [job, deps] : graph) {
        inDegree[job] = deps.size();
        if (deps.empty()) {
            readyJobs.push(job);
        }
    }

    std::vector<pthread_t> workers;

    for (int i = 0; i < maxParallelJobs; ++i) {
        pthread_t thread;
        pthread_create(&thread, nullptr, ThreadProcess, nullptr);
        workers.emplace_back(thread);
    }

    pthread_cond_broadcast(&queueCV);

    for (auto& worker : workers) {
        pthread_join(worker, nullptr);
    }

    for (auto& [_, barrier] : barriers) {
        pthread_barrier_destroy(&barrier);
    }

    std::cout << (errorFlag ? "Execution failed" : "Execution completed successfully") << std::endl;

    return 0;
}