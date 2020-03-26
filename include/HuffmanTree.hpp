#pragma once

#include <set>
#include <vector>
#include <cstdint>

#include "HuffmanException.hpp"

static const int BYTE = 8;
static const int EMPTY = -1;

class HuffmanTree {
private:
    struct TreeNode;

private:
    int32_t root;
    std::vector <TreeNode> data;

public:
    HuffmanTree(const std::vector <int32_t> & cnt);
    ~HuffmanTree();

    void get_codewords(std::vector < std::vector <bool> > & result);
    void restore(const std::vector <bool> & encoded, std::vector <uint8_t> & decoded);

    friend class HuffmanTreeTest;

private:
    void dfs_get(const int32_t v, std::vector <bool> & cur, std::vector < std::vector <bool> > & result);
    int32_t dfs_restore(const int32_t v, const std::vector <bool> & encoded, std::size_t & idx);
};


struct HuffmanTree::TreeNode {
    bool is_leaf;
    int32_t left, right;

    TreeNode() : is_leaf(true), left(EMPTY), right(EMPTY) {}
    TreeNode(int32_t left, int32_t right) : is_leaf(false), left(left), right(right) {}

    bool operator== (const TreeNode & other) {
        return (left == other.left)
            && (right == other.right)
            && (is_leaf == other.is_leaf);
    }
};