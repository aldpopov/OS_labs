#include <gtest/gtest.h>
#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
#include <cstring>
#include <pthread.h>

#include "cp8_utils.h"

TEST(is_cyclic_util, test)
{
    auto id = 3;
    std::unordered_map<int, bool> visited1, recStack1;
    std::unordered_map<int, std::vector<int>> goodGraph = {
        {1, {}},
        {2, {1}},
        {3, {1, 2}}
    };

    std::unordered_map<int, bool> visited2, recStack2;
    std::unordered_map<int, std::vector<int>> badGraph = {
        {1, {2}},
        {2, {1}},
        {3, {1, 2}}
    };

    auto good = is_cyclic_util(id, goodGraph, visited1, recStack1);
    auto bad = is_cyclic_util(id, badGraph, visited2, recStack2);

    ASSERT_FALSE(good);
    ASSERT_TRUE(bad);
}

TEST(is_cyclic, test)
{
    std::unordered_map<int, std::vector<int>> goodGraph = {
        {1, {}},
        {2, {1}},
        {3, {1, 2}}
    };

    std::unordered_map<int, std::vector<int>> badGraph = {
        {1, {2}},
        {2, {1}},
        {3, {1, 2}}
    };

    auto good = is_cyclic(goodGraph);
    auto bad = is_cyclic(badGraph);

    ASSERT_FALSE(good);
    ASSERT_TRUE(bad);
}

TEST(check_graph, test)
{
    auto expectedResult = "Error: DAG contains cycles\nError: DAG is not a single connected component\n";

    std::unordered_map<int, std::vector<int>> goodGraph = {
        {1, {}},
        {2, {1}},
        {3, {1, 2}}
    };

    std::unordered_map<int, std::vector<int>> badGraph1 = {
        {1, {2}},
        {2, {1}},
        {3, {1, 2}}
    };

    std::unordered_map<int, std::vector<int>> badGraph2 = {
        {1, {}},
        {2, {1}},
        {3, {}},
        {4, {3}}
    };

    testing::internal::CaptureStderr();

    auto good = check_graph(goodGraph);
    auto bad1 = check_graph(badGraph1);
    auto bad2 = check_graph(badGraph2);

    auto output = testing::internal::GetCapturedStderr();

    ASSERT_TRUE(good);
    ASSERT_FALSE(bad1);
    ASSERT_FALSE(bad2);
    ASSERT_EQ(output, expectedResult);
}

TEST(exec, test)
{
    auto expectedResult = "some (1) starts, it's id = 1;\nsome (1) finished;\n";

    auto name = "some";
    int jobId = 1;
    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, nullptr, 1);

    std::atomic<bool> errorFlag = false;
    const int execTime = 2;

    testing::internal::CaptureStdout();

    exec(name, jobId, &barrier, errorFlag, execTime);

    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, expectedResult);

    pthread_barrier_destroy(&barrier);
}

TEST(thread_process, test)
{
    auto expectedResult = "a (1) starts, it's id = 1;\na (1) finished;\nb (2) starts, it's id = 2;\nb (2) finished;\n"
                          "c (3) starts, it's id = 3;\nc (3) finished;\nd (4) starts, it's id = 4;\nd (4) finished;\n";

    readyJobs.push(1);
    readyJobs.push(2);

    jobs = {
        {1, Job{"a", {}, "barrier1", 1}},
        {2, Job{"b", {}, "barrier2", 2}},
        {3, Job{"c", {1, 2}, "barrier2", 3}},
        {4, Job{"d", {3}, "barrier1", 4}},
    };

    graph = {
        {1, {}},
        {2, {}},
        {3, {1, 2}},
        {4, {3}}
    };

    inDegree = {
        {1, 0},
        {2, 0},
        {3, 2},
        {4, 1}
    };

    pthread_barrier_t barrier1;
    pthread_barrier_init(&barrier1, nullptr, 1);

    pthread_barrier_t barrier2;
    pthread_barrier_init(&barrier2, nullptr, 1);

    barriers = {
        {"barrier1", barrier1},
        {"barrier2", barrier2},
    };

    testing::internal::CaptureStdout();

    pthread_t thread;
    pthread_create(&thread, nullptr, thread_process, nullptr);

    pthread_join(thread, nullptr);

    auto output = testing::internal::GetCapturedStdout();

    pthread_barrier_destroy(&barrier1);
    pthread_barrier_destroy(&barrier2);

    ASSERT_EQ(output, expectedResult);
}