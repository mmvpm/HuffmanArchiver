#pragma once

#include <cstdlib>
#include <iostream>

#define DO_CHECK(X) check(X, __FILE__, __func__, __LINE__)

class AutoTest {
protected:
    static int failedNum;
    static int totalNum;

protected:
    static void check(bool expr, const char *func, const char *filename, size_t lineNum);

public:
    static void showFinalResult();
};