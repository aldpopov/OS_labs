#include <gtest/gtest.h>
#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
#include <cstring>
#include <pthread.h>

#include "tools.h"

// Тест для функции IsCyclicUtil
TEST(isCyclicUtil, test)
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

    auto good = IsCyclicUtil(id, goodGraph, visited1, recStack1);
    auto bad = IsCyclicUtil(id, badGraph, visited2, recStack2);

    ASSERT_FALSE(good);
    ASSERT_TRUE(bad);
}

// Тест для функции IsCyclic
TEST(isCyclic, test)
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

    auto good = IsCyclic(goodGraph);
    auto bad = IsCyclic(badGraph);

    ASSERT_FALSE(good);
    ASSERT_TRUE(bad);
}

// Тест для функции ValidateDAG
TEST(validateDAG, test)
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

    auto good = ValidateDAG(goodGraph);
    auto bad1 = ValidateDAG(badGraph1);
    auto bad2 = ValidateDAG(badGraph2);

    auto output = testing::internal::GetCapturedStderr();

    ASSERT_TRUE(good);
    ASSERT_FALSE(bad1);
    ASSERT_FALSE(bad2);
    ASSERT_EQ(output, expectedResult);
}

// Тест для функции ExecuteJob с барьером
TEST(executeJob, test)
{
    auto expectedResult = "Starting job: some\nJob completed: some\n";

    auto name = "some";
    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, nullptr, 1); // Инициализация барьера

    std::atomic<bool> errorFlag = false;
    const int execTime = 2;

    testing::internal::CaptureStdout();

    ExecuteJob(name, &barrier, errorFlag, execTime);

    auto output = testing::internal::GetCapturedStdout();

    ASSERT_EQ(output, expectedResult);

    pthread_barrier_destroy(&barrier); // Уничтожение барьера
}

// Тест для функции ThreadProcess с барьером
TEST(threadProcess, test)
{
    auto expectedResult = "Starting job: a\nJob completed: a\nStarting job: b\nJob completed: b\n"
                          "Starting job: c\nJob completed: c\nStarting job: d\nJob completed: d\n";

    readyJobs.push(1);
    readyJobs.push(2);

    // Correct job dependencies and barriers
    jobs = {
        {1, Job{"a", {}, "barrier1", 1}},
        {2, Job{"b", {}, "barrier2", 2}},
        {3, Job{"c", {1, 2}, "barrier2", 3}}, // Corrected dependencies
        {4, Job{"d", {3}, "barrier1", 4}},    // Added dependency on job 3
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

    // Initialize barriers with correct counts
    pthread_barrier_t barrier1;
    pthread_barrier_init(&barrier1, nullptr, 1);

    pthread_barrier_t barrier2;
    pthread_barrier_init(&barrier2, nullptr, 1);

    barriers = {
        {"barrier1", barrier1},
        {"barrier2", barrier2},
    };

    testing::internal::CaptureStdout();

    // Start ThreadProcess in a separate thread
    pthread_t thread;
    pthread_create(&thread, nullptr, ThreadProcess, nullptr);

    // Wait for the thread to finish
    pthread_join(thread, nullptr);

    auto output = testing::internal::GetCapturedStdout();

    // Clean up barriers
    pthread_barrier_destroy(&barrier1);
    pthread_barrier_destroy(&barrier2);

    ASSERT_EQ(output, expectedResult);
}