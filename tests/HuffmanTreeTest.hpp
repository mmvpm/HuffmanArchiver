#pragma once

#include "AutoTest.hpp"
#include "HuffmanTree.hpp"

class HuffmanTreeTest : public AutoTest {
private:
    static void testTreeRoot_EMPTY();
    static void testTreeRoot_ONE_CHAR();
    static void testTreeRoot_TWO_CHARS();
    static void testTreeRoot_FULL();

    static void testBuildTree_EMPTY();
    static void testBuildTree_ONE_CHAR();
    static void testBuildTree_TWO_CHARS();
    static void testBuildTree_FULL();

    static void testGetCodewords_EMPTY();
    static void testGetCodewords_ONE_CHAR();
    static void testGetCodewords_TWO_CHARS();
    static void testGetCodewords_FULL();

    static void testRestore_EMPTY();
    static void testRestore_ONE_CHAR();
    static void testRestore_TWO_CHARS();
    static void testRestore_FULL();

public:
    static void runAllTests();
};