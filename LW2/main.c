#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include "lab2.h"

int main() {
   int k, current_round, player1_score, player2_score, experiments, max_threads;

   printf("Enter K, ROUND, P1SCORE, P2SCORE, EXPERIMENTS, MAXTHREADS (separated by spaces):\n");
   int scanf_result = scanf("%d %d %d %d %d %d", &k, &current_round, &player1_score, &player2_score, &experiments, &max_threads);
   if (scanf_result != 6) {
      fprintf(stderr, "Invalid input format. Please enter six integers separated by spaces.\n");
      return 1; 
   }

   if (k <= 0 || current_round < 0 || experiments < 0 || max_threads <= 0 || player1_score < 0 || player2_score < 0) {
      fprintf(stderr, "Invalid input values. Please enter positive integers for K, ROUND, EXPERIMENTS, MAXTHREADS and non-negative for scores.\n");
      return 1;
   }
   if (k > INT_MAX / 2 || current_round > INT_MAX / 2 || experiments > INT_MAX / 2 || max_threads > INT_MAX / 2 || player1_score > INT_MAX / 2 || player2_score > INT_MAX / 2) {
      fprintf(stderr, "Input values are too large, potential for integer overflow.\n");
      return 1;
   }

   run_simulation(k, current_round, player1_score, player2_score, experiments, max_threads);
   return 0;
}
