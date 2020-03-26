#include "AutoTest.hpp"

void AutoTest::check(bool expr, const char *func, const char  *filename, size_t lineNum) {
    if (!expr) {
        std::cout << "Failed " << func << std::endl;
        std::cout << "In file " << filename << std::endl;
        std::cout << "On line " << lineNum << std::endl;
        failedNum++;
    }
    totalNum++;
}

void AutoTest::showFinalResult() {
    std::cout << "Failed tests: " << failedNum << std::endl;
    std::cout << "Total tests: " << totalNum << std::endl;
}

int AutoTest::failedNum = 0;
int AutoTest::totalNum = 0;