#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <string>
#include <sstream>
#include <random>
#include "lab1.h"
#include "../LW1/src/lab_1_utils.c"

extern "C" {
    #include <lab1.h>
}

class TempFile {
public:
    TempFile(const std::string& content) {
        std::srand(static_cast<unsigned>(std::time(0)));
        fileName = "test_file_" + std::to_string(std::rand()) + ".txt";
        std::ofstream outFile(fileName);
        if (!outFile) {
            throw std::runtime_error("Не удалось создать временный файл");
        }
        outFile << content;
        outFile.close();
    }

    ~TempFile() {
        std::remove(fileName.c_str());
    }

    std::string getFileName() const {
        return fileName;
    }

private:
    std::string fileName;
};

std::string getOutputFromFile(FILE* file) {
    rewind(file);
    char buffer[1024];
    std::string result;
    while (fgets(buffer, sizeof(buffer), file) != nullptr) {
        result += buffer;
    }
    return result;
}

TEST(FileTest, StandartPositiveSum) {
    TempFile tempFile("1.2 2.2 3.2 4.2 5.2");
    FILE* outputFile = tmpfile();
    if (outputFile == nullptr) {
        FAIL() << "Не удалось создать временный файл";
    }
    MainTestFunction(tempFile.getFileName().c_str(), outputFile);
    std::string outputStr = getOutputFromFile(outputFile);
    fclose(outputFile);
    EXPECT_EQ(outputStr, "Сумма: 16\n");
}

TEST(FileTest, StandartNegativeSum) {
    TempFile tempFile("-1.1 -1.1 -2.2 -1.1");
    FILE* outputFile = tmpfile();
    if (outputFile == nullptr) {
        FAIL() << "Не удалось создать временный файл";
    }
    MainTestFunction(tempFile.getFileName().c_str(), outputFile);
    std::string outputStr = getOutputFromFile(outputFile);
    fclose(outputFile);
    EXPECT_EQ(outputStr, "Сумма: -5.5\n");
}

TEST(FileTest, StandartMeshSum) {
    TempFile tempFile("-1.1 1.25 2.4 -1.05");
    FILE* outputFile = tmpfile();
    if (outputFile == nullptr) {
        FAIL() << "Не удалось создать временный файл";
    }
    MainTestFunction(tempFile.getFileName().c_str(), outputFile);
    std::string outputStr = getOutputFromFile(outputFile);
    fclose(outputFile);
    EXPECT_EQ(outputStr, "Сумма: 1.5\n");
}

TEST(FileTest, OnlyZeroSum) {
    TempFile tempFile("0 0 0 0");
    FILE* outputFile = tmpfile();
    if (outputFile == nullptr) {
        FAIL() << "Не удалось создать временный файл";
    }
    MainTestFunction(tempFile.getFileName().c_str(), outputFile);
    std::string outputStr = getOutputFromFile(outputFile);
    fclose(outputFile);
    EXPECT_EQ(outputStr, "Сумма: 0\n");
}
