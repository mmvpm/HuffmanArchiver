#include "HuffmanTree.hpp"

typedef std::pair <int32_t, int32_t> pii;

HuffmanTree::HuffmanTree(const std::vector <int32_t> & cnt) {
    std::set <pii> builder;
    for (int32_t i = 0; i < static_cast <int32_t> (cnt.size()); ++i) {
        if (cnt[i] > 0) {
            builder.insert({cnt[i], i});
        }
    }
    int32_t last_unused = cnt.size();
    data.assign(cnt.size() * 2, TreeNode());

    if (builder.size() == 1) {
        builder.insert({0, 0});
    }

    while (builder.size() > 1) {
        pii a =  *(builder.begin());
        builder.erase(builder.begin());

        pii b =  *(builder.begin());
        builder.erase(builder.begin());

        data[last_unused] = TreeNode(a.second, b.second);
        builder.insert({a.first + b.first, last_unused});
        ++last_unused;
    }

    root = (builder.empty() ? EMPTY : builder.begin()->second);
}

HuffmanTree::~HuffmanTree() {
    data.clear();
}

void HuffmanTree::get_codewords(std::vector < std::vector <bool> > & result) {
    if (root == EMPTY) {
        return;
    }
    std::vector <bool> cur;
    dfs_get(root, cur, result);
}

void HuffmanTree::restore(const std::vector <bool> & encoded, std::vector <uint8_t> & decoded) {
    if (root == EMPTY || encoded.empty()) {
        return;
    }
    std::size_t idx = 0;
    while (idx < encoded.size()) {
        decoded.push_back(static_cast <uint8_t> (dfs_restore(root, encoded, idx)));
    }
}

void HuffmanTree::dfs_get(const int32_t v, std::vector <bool> & cur, std::vector < std::vector <bool> > & result) {
    if (data[v].is_leaf) {
        result[v] = cur;
        return;
    }

    cur.push_back(0);
    dfs_get(data[v].left, cur, result);
    cur.pop_back();

    cur.push_back(1);
    dfs_get(data[v].right, cur, result);
    cur.pop_back();
}

int32_t HuffmanTree::dfs_restore(const int32_t v, const std::vector <bool> & encoded, std::size_t & idx) {
    if (data[v].is_leaf) {
        return v;
    }
    if (!(idx < encoded.size())) {
        throw HuffmanException("Invalid format.");
    }

    if (encoded[idx] == 0) {
        return dfs_restore(data[v].left, encoded, ++idx);
    }
    else {
        return dfs_restore(data[v].right, encoded, ++idx);
    }
}