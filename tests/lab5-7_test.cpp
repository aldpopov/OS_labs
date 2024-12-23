#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>
#include "../LW5-7/include/manage_node.h"
#include "../LW5-7/include/calc_node.h"
#include "../LW5-7/include/tree.h"
#include "../LW5-7/include/upcoming_operations.h"
#include "../LW5-7/include/comp_utils.h"
#include "../LW5-7/src/comp_utils.c"
//#include "../LW5-7/src/manage_node.c"
//#include "../LW5-7/src/tree.c"
//#include "../LW5-7/src/upcoming_operations.c"
//#include "../LW5-7/src/message.c"

extern "C" {
    void mock_main();
    extern int create_result;
    extern int ping_result;
    extern int exec_result;
}

// Тест для проверки создания узла
TEST(ManageNodeTest, CreateCalculateNode) {
    mock_main();
    EXPECT_NE(create_result, -1); // Убеждаемся, что создание узла прошло успешно
}

// Тест для проверки доступности узла
TEST(ManageNodeTest, PingNode) {
    mock_main();
    EXPECT_EQ(ping_result, 1); // Убеждаемся, что узел доступен
}

// Тест для проверки выполнения команды exec
TEST(ManageNodeTest, ExecCommand) {
    mock_main();
    EXPECT_EQ(exec_result, 0); // Убеждаемся, что команда exec выполнена успешно
}

// Тест для проверки доступности всех узлов
TEST(ManageNodeTest, PingAll) {
    mock_main();
    // Здесь можно добавить проверку вывода ping_all, если это требуется
}

// Тест для проверки функции find_substring
TEST(CompUtilsTest, FindSubstring) {
    const char* text1 = "abracadabra";
    const char* pattern1 = "abra";
    char* result1 = find_substring(text1, pattern1);
    EXPECT_STREQ(result1, "0;7"); // Проверяем, что подстрока найдена в правильных позициях

    const char* text2 = "mississippi";
    const char* pattern2 = "ss";
    char* result2 = find_substring(text2, pattern2);
    EXPECT_STREQ(result2, "2;5"); // Проверяем, что подстрока найдена в правильных позициях

    const char* text3 = "hello";
    const char* pattern3 = "world";
    char* result3 = find_substring(text3, pattern3);
    EXPECT_STREQ(result3, "-1"); // Проверяем, что подстрока не найдена

    const char* text4 = "";
    const char* pattern4 = "test";
    char* result4 = find_substring(text4, pattern4);
    EXPECT_STREQ(result4, "-1"); // Проверяем, что подстрока не найдена в пустом тексте

    const char* text5 = "test";
    const char* pattern5 = "";
    char* result5 = find_substring(text5, pattern5);
    EXPECT_STREQ(result5, "-1"); // Проверяем, что подстрока не найдена, если паттерн пустой
}