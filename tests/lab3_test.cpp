#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <stdexcept>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include "../LW3/src/parent.c"
#include "../LW3/src/utils.c"

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

std::string getOutputFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    std::string result((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    return result;
}

TEST(FileTest, Standard_Sum) {
    TempFile tempFile("12 22 32 42 52");
    const char* outputFileName = "output.txt";
    FILE* outputFile = fopen(outputFileName, "w+");
    if (outputFile == nullptr) {
        FAIL() << "Failed to create temp output file";
    }
    int originalStdout = dup(STDOUT_FILENO);
    dup2(fileno(outputFile), STDOUT_FILENO);
    MainFunction(const_cast<char*>(tempFile.getFileName().c_str()));
    fflush(stdout);
    dup2(originalStdout, STDOUT_FILENO);
    close(originalStdout);
    fclose(outputFile);
    std::string outputStr = getOutputFromFile(outputFileName);
    EXPECT_EQ(outputStr, "160.00\n");
    std::remove(outputFileName);
}

TEST(FileTest, Negative_Sum) {
    TempFile tempFile("1.2 -2.2");
    const char* outputFileName = "output.txt";
    FILE* outputFile = fopen(outputFileName, "w+");
    if (outputFile == nullptr) {
        FAIL() << "Failed to create temp output file";
    }
    int originalStdout = dup(STDOUT_FILENO);
    dup2(fileno(outputFile), STDOUT_FILENO);
    MainFunction(const_cast<char*>(tempFile.getFileName().c_str()));
    fflush(stdout);
    dup2(originalStdout, STDOUT_FILENO);
    close(originalStdout);
    fclose(outputFile);
    std::string outputStr = getOutputFromFile(outputFileName);
    EXPECT_EQ(outputStr, "-1.00\n");
    std::remove(outputFileName);
}
