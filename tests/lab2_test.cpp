#include "gtest/gtest.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include "../LW2/src/lab_2_utils.c"


TEST(GameSimulationTest, SingleThreadCorrectness) {
    int k = 5;
    int player1_score = 10;
    int player2_score = 15;
    int experiments = 1000;
    int max_threads = 1;
    int current_round = 0;

    run_simulation(k, current_round, player1_score, player2_score, experiments, max_threads);
    SUCCEED();

}

TEST(GameSimulationTest, SingleThreadVsMultiThread) {
    int k = 5;
    int player1_score = 10;
    int player2_score = 15;
    int experiments = 1000;
    int current_round = 0;

    int max_threads_1 = 1;
    int max_threads_2 = 4;

    GameData data1, data2;
    data1.k = data2.k = k;
    data1.player1_score = data2.player1_score = player1_score;
    data1.player2_score = data2.player2_score = player2_score;
    data1.experiments = data2.experiments = experiments;
    data1.thread_count = max_threads_1;
    data2.thread_count = max_threads_2;
    data1.player1_wins = data2.player1_wins = 0;
    data1.player2_wins = data2.player2_wins = 0;
    data1.draws = data2.draws = 0;
    pthread_mutex_init(&data1.mutex, NULL);
    pthread_mutex_init(&data2.mutex, NULL);

    pthread_t threads1[max_threads_1], threads2[max_threads_2];
    srand(time(NULL));

    for (int i = 0; i < max_threads_1; ++i) pthread_create(&threads1[i], NULL, simulate_games, &data1);
    for (int i = 0; i < max_threads_2; ++i) pthread_create(&threads2[i], NULL, simulate_games, &data2);

    for (int i = 0; i < max_threads_1; ++i) pthread_join(threads1[i], NULL);
    for (int i = 0; i < max_threads_2; ++i) pthread_join(threads2[i], NULL);


    double ratio1 = (double)data1.player1_wins / (data1.player1_wins + data1.player2_wins + data1.draws);
    double ratio2 = (double)data2.player1_wins / (data2.player1_wins + data2.player2_wins + data2.draws);
    EXPECT_NEAR(ratio1, ratio2, 0.1);


    pthread_mutex_destroy(&data1.mutex);
    pthread_mutex_destroy(&data2.mutex);
}


TEST(GameSimulationTest, MultiThreadFaster) {
    int k = 5;
    int player1_score = 10;
    int player2_score = 15;
    int experiments = 1000000;
    int current_round = 0;
    int max_threads_1 = 1;
    int max_threads_2 = 15;

    auto start_time_1 = std::chrono::high_resolution_clock::now();
    run_simulation(k, current_round, player1_score, player2_score, experiments, max_threads_1);
    auto end_time_1 = std::chrono::high_resolution_clock::now();
    auto duration_1 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_1 - start_time_1);

    auto start_time_2 = std::chrono::high_resolution_clock::now();
    run_simulation(k, current_round, player1_score, player2_score, experiments, max_threads_2);
    auto end_time_2 = std::chrono::high_resolution_clock::now();
    auto duration_2 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_2 - start_time_2);

    EXPECT_GT(duration_2.count(), duration_1.count());
}