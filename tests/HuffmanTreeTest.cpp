#include "HuffmanTreeTest.hpp"

static const int32_t SIZE = 1 << BYTE;

void HuffmanTreeTest::testTreeRoot_EMPTY() {
    std::vector <int32_t> cnt(SIZE);
    HuffmanTree tree(cnt);
    DO_CHECK(tree.root == EMPTY);
}

void HuffmanTreeTest::testTreeRoot_ONE_CHAR() {
    std::vector <int32_t> cnt(SIZE);
    cnt['a'] = 1;
    HuffmanTree tree(cnt);
    DO_CHECK(tree.root == SIZE);
}

void HuffmanTreeTest::testTreeRoot_TWO_CHARS() {
    std::vector <int32_t> cnt(SIZE);
    cnt['a'] = 1;
    cnt['b'] = 2;
    HuffmanTree tree(cnt);
    DO_CHECK(tree.root == (SIZE));
}

void HuffmanTreeTest::testTreeRoot_FULL() {
    std::vector <int32_t> cnt(SIZE, 1);
    HuffmanTree tree(cnt);
    DO_CHECK(tree.root == 2 * SIZE - 2);
}

void HuffmanTreeTest::testBuildTree_EMPTY() {
    std::vector <int32_t> cnt(SIZE);
    HuffmanTree tree(cnt);
    bool res = true;
    std::vector <HuffmanTree::TreeNode> empty_data(SIZE + 1);
    for (std::size_t i = 0; i < empty_data.size(); ++i) {
        res &= (empty_data[i] == tree.data[i]);
    }
    DO_CHECK(res);
}

void HuffmanTreeTest::testBuildTree_ONE_CHAR() {
    std::vector <int32_t> cnt(SIZE);
    cnt[0] = 1;
    HuffmanTree tree(cnt);
    bool res = true;
    std::vector <HuffmanTree::TreeNode> my_data(SIZE + 1);
    for (std::size_t i = 0; i < my_data.size(); ++i) {
        if (i != SIZE) {
            res &= (my_data[i] == tree.data[i]);
        }
        else {
            res &= (HuffmanTree::TreeNode(0, 0) == tree.data[i]);
        }
    }
    DO_CHECK(res);
}

void HuffmanTreeTest::testBuildTree_TWO_CHARS() {
    std::vector <int32_t> cnt(SIZE);
    cnt[0] = 1;
    cnt[SIZE - 1] = 1;
    HuffmanTree tree(cnt);
    DO_CHECK(tree.data[SIZE] == HuffmanTree::TreeNode(0, SIZE - 1));
}

void HuffmanTreeTest::testBuildTree_FULL() {
    std::vector <int32_t> cnt(SIZE, 1);
    HuffmanTree tree(cnt);
    bool res = true;
    for (int32_t i = 0; i < SIZE; ++i) {
        res &= (HuffmanTree::TreeNode() == tree.data[i]);
    }
    for (int32_t i = SIZE; i < SIZE * 2 - 1; ++i) {
        int32_t idx = 2 * SIZE - 1 - i;
        int32_t left = 2 * SIZE - 1 - 2 * idx;
        int32_t right = 2 * SIZE - 1 - 2 * idx - 1;
        res &= (HuffmanTree::TreeNode(left, right) == tree.data[i])
               || (HuffmanTree::TreeNode(right, left) == tree.data[i]);
    }
    DO_CHECK(res);
}

void HuffmanTreeTest::testGetCodewords_EMPTY() {
    std::vector <int32_t> cnt(SIZE);
    HuffmanTree tree(cnt);
    std::vector < std::vector <bool> > res(SIZE);
    tree.get_codewords(res);
    DO_CHECK(res == std::vector < std::vector <bool> > (SIZE));
}

void HuffmanTreeTest::testGetCodewords_ONE_CHAR() {
    std::vector <int32_t> cnt(SIZE);
    cnt.back() = 1;
    HuffmanTree tree(cnt);
    std::vector < std::vector <bool> > res(SIZE);
    tree.get_codewords(res);
    std::vector < std::vector <bool> > ideal(SIZE);
    ideal[0] = std::vector <bool> (1, 0);
    ideal.back() = std::vector <bool> (1, 1);
    DO_CHECK(res == ideal);
}

void HuffmanTreeTest::testGetCodewords_TWO_CHARS() {
    std::vector <int32_t> cnt(SIZE);
    cnt['c'] = 1;
    cnt['d'] = 2;
    HuffmanTree tree(cnt);
    std::vector < std::vector <bool> > res(SIZE);
    tree.get_codewords(res);
    std::vector < std::vector <bool> > ideal(SIZE);
    ideal['c'] = std::vector <bool> (1, 0);
    ideal['d'] = std::vector <bool> (1, 1);
    DO_CHECK(res == ideal);
}

void HuffmanTreeTest::testGetCodewords_FULL() {
    std::vector <int32_t> cnt(SIZE, 1);
    HuffmanTree tree(cnt);
    std::vector < std::vector <bool> > res(SIZE);
    tree.get_codewords(res);
    bool value_check = true;
    for (std::size_t i = 0; i < res.size(); ++i) {
        std::vector <bool> bin(BYTE);
        std::size_t x = i, j = bin.size();
        while (x) {
            bin[--j] = x % 2;
            x /= 2;
        }
        value_check &= (res[i] == bin);
    }
    DO_CHECK(value_check);
}

void HuffmanTreeTest::testRestore_EMPTY() {
    std::vector <int32_t> cnt(SIZE);
    HuffmanTree tree(cnt);
    std::vector <bool> encoded;
    std::vector <uint8_t> decoded;
    tree.restore(encoded, decoded);
    DO_CHECK(decoded == std::vector <uint8_t> ());
}

void HuffmanTreeTest::testRestore_ONE_CHAR() {
    std::vector <int32_t> cnt(SIZE);
    cnt['F'] = 1;
    HuffmanTree tree(cnt);
    std::vector <bool> encoded {1};
    std::vector <uint8_t> decoded;
    tree.restore(encoded, decoded);
    DO_CHECK(decoded == std::vector <uint8_t> {'F'});
}

void HuffmanTreeTest::testRestore_TWO_CHARS() {
    std::vector <int32_t> cnt(SIZE);
    cnt['F'] = 2;
    cnt['f'] = 1;
    HuffmanTree tree(cnt);
    std::vector <bool> encoded {0, 1};
    std::vector <uint8_t> decoded;
    tree.restore(encoded, decoded);
    DO_CHECK(decoded == (std::vector <uint8_t> {'f', 'F'}));
}

void HuffmanTreeTest::testRestore_FULL() {
    std::vector <int32_t> cnt(SIZE, 1);
    HuffmanTree tree(cnt);
    std::vector <bool> encoded;
    for (int32_t i = 0; i < (SIZE); ++i) {
        for (int32_t j = BYTE - 1; j >= 0; --j) {
            encoded.push_back(i & (1 << j));
        }
    }
    std::vector <uint8_t> decoded;
    tree.restore(encoded, decoded);
    std::vector <uint8_t> ideal(SIZE);
    for (std::size_t i = 0; i < ideal.size(); ++i) {
        ideal[i] = i;
    }
    DO_CHECK(decoded == ideal);
}

void HuffmanTreeTest::runAllTests() {
    testTreeRoot_EMPTY();
    testTreeRoot_ONE_CHAR();
    testTreeRoot_TWO_CHARS();
    testTreeRoot_FULL();

    testBuildTree_EMPTY();
    testBuildTree_ONE_CHAR();
    testBuildTree_TWO_CHARS();
    testBuildTree_FULL();

    testGetCodewords_EMPTY();
    testGetCodewords_ONE_CHAR();
    testGetCodewords_TWO_CHARS();
    testGetCodewords_FULL();

    testRestore_EMPTY();
    testRestore_ONE_CHAR();
    testRestore_TWO_CHARS();
    testRestore_FULL();
}