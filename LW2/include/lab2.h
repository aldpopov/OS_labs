#pragma once
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


typedef struct {
   int k;
   int player1_score;
   int player2_score;
   int experiments;
   int thread_count;
   int player1_wins;
   int player2_wins;
   int draws;
   pthread_mutex_t mutex;
} GameData;

int roll_dice();
void* simulate_games(void* arg);
void run_simulation(int k, int current_round, int player1_score, int player2_score, int experiments, int max_threads);