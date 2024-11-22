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
            throw std::runtime_error("Failed to create temp file");
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

TEST(FileTest, Standard_Sum) {
    TempFile tempFile("12 22 32 42 52");
    FILE* outputFile = tmpfile();
    if (outputFile == nullptr) {
        FAIL() << "Failed to create temp file";
    }
    MainTestFunction(tempFile.getFileName().c_str(), outputFile);
    std::string outputStr = getOutputFromFile(outputFile);
    fclose(outputFile);
    EXPECT_EQ(outputStr, "Sum: 160.00\n");
}

TEST(FileTest, Standard_Negative_Sum) {
    TempFile tempFile("-1.1 -1.1 -2.2 -1.1");
    FILE* outputFile = tmpfile();
    if (outputFile == nullptr) {
        FAIL() << "Failed to create temp file";
    }
    MainTestFunction(tempFile.getFileName().c_str(), outputFile);
    std::string outputStr = getOutputFromFile(outputFile);
    fclose(outputFile);
    EXPECT_EQ(outputStr, "Sum: -5.50\n");
}

TEST(FileTest, Standard_Mesh_Sum) {
    TempFile tempFile("-1.1 1.25 2.4 -1.05");
    FILE* outputFile = tmpfile();
    if (outputFile == nullptr) {
        FAIL() << "Failed to create temp file";
    }
    MainTestFunction(tempFile.getFileName().c_str(), outputFile);
    std::string outputStr = getOutputFromFile(outputFile);
    fclose(outputFile);
    EXPECT_EQ(outputStr, "Sum: 1.50\n");
}

TEST(FileTest, Zeroes_Sum) {
    TempFile tempFile("0 0 0 0");
    FILE* outputFile = tmpfile();
    if (outputFile == nullptr) {
        FAIL() << "Failed to create temp file";
    }
    MainTestFunction(tempFile.getFileName().c_str(), outputFile);
    std::string outputStr = getOutputFromFile(outputFile);
    fclose(outputFile);
    EXPECT_EQ(outputStr, "Sum: 0.00\n");
}
