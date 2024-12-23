#include "include/manage_node.h"
#include "include/tree.h"
#include "include/upcoming_operations.h"
#include <stdio.h>

// Глобальные переменные для хранения результатов тестов
int create_result = 0;
int ping_result = 0;
int exec_result = 0;

// Функция для тестирования создания узла
void test_create_calc_node() {
    create_result = create_calc_node(1, -1);
    printf("create_calc_node result: %d\n", create_result);
}

// Функция для тестирования проверки доступности узла
void test_ping_node() {
    ping_result = ping_node(1);
    printf("ping_node result: %d\n", ping_result);
}

// Функция для тестирования выполнения команды exec
void test_exec() {
    exec_result = exec(1, "abracadabra", "abra");
    printf("exec result: %d\n", exec_result);
}

// Функция для тестирования проверки доступности всех узлов
void test_ping_all() {
    ping_all();
}

// Основная функция для запуска тестов
void mock_main() {
    test_create_calc_node();
    test_ping_node();
    test_exec();
    test_ping_all();
}