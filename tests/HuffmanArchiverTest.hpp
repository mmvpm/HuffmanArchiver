#pragma once

#include <cstdio>

#include "AutoTest.hpp"
#include "HuffmanArchiver.hpp"

class HuffmanArchiverTest : public AutoTest {
private:
    static void testIOSource_SMALL_SIZE_TEXT();
    static void testIOSource_BIG_SIZE_TEXT();
    static void testIOSource_SMALL_SIZE_BIN();
    static void testIOSource_BIG_SIZE_BIN();

    static void testIOEncoded_SMALL_SIZE_TEXT();
    static void testIOEncoded_BIG_SIZE_TEXT();
    static void testIOEncoded_SMALL_SIZE_BIN();
    static void testIOEncoded_BIG_SIZE_BIN();

    static void testIOSource_EMPTY_TEXT();
    static void testIOSource_EMPTY_BIN();
    static void testIOEncoded_EMPTY_TEXT();
    static void testIOEncoded_EMPTY_BIN();

    static void testCounting_EMPTY();
    static void testCounting_ONE_CHAR();
    static void testCounting_EVEN();
    static void testCounting_FULL();

    static void testEncodeDecode_EMPTY_TEXT();
    static void testEncodeDecode_EMPTY_BIN();
    static void testEncodeDecode_SMALL_SIZE();
    static void testEncodeDecode_BIG_SIZE();

    static void testIOSource_NO_FILE();
    static void testIOEncoded_NO_FILE();
    static void testIOEncoded_EOF();
    static void testEncodeDecode_INVALID_FILE();

public:
    static void runAllTests();
};