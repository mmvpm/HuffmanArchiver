#include "HuffmanArchiver.hpp"

void HuffmanArchiver::encode(const std::string & file_in, const std::string & file_out) {
    std::vector <uint8_t> source;
    input_source(file_in, source);

    std::vector <int32_t> cnt(1 << BYTE);
    counting(source, cnt);

    HuffmanTree tree(cnt);

    std::vector < std::vector <bool> > codewords(1 << BYTE);
    tree.get_codewords(codewords);

    std::vector <bool> encoded;
    for (uint8_t ch : source) {
        for (auto e : codewords[ch]) {
            encoded.push_back(e);
        }
    }

    output_encoded(file_out, encoded, cnt);
}

void HuffmanArchiver::decode(const std::string & file_in, const std::string & file_out) {
    std::vector <bool> encoded;
    std::vector <int32_t> cnt(1 << BYTE);
    input_encoded(file_in, encoded, cnt);

    HuffmanTree tree(cnt);

    std::vector <uint8_t> decoded;
    tree.restore(encoded, decoded);

    output_decoded(file_out, decoded);
}


void HuffmanArchiver::input_source(const std::string & file_in, std::vector <uint8_t> & source) {
    std::ifstream in(file_in, std::ios_base::binary);
    if (!in.is_open()) {
        in.close();
        throw HuffmanException("Unable to open file.");
    }

    uint8_t ch;
    while (in >> binary <uint8_t> (ch)) {
        source.push_back(ch);
    }
    source_size = source.size();

    in.close();
}

void HuffmanArchiver::input_encoded(const std::string & file_in, std::vector <bool> & encoded, std::vector <int32_t> & cnt) {
    std::ifstream in(file_in, std::ios_base::binary);
    if (!in.is_open()) {
        in.close();
        throw HuffmanException("Unable to open file.");
    }

    uint16_t cnt_not_zero;
    uint8_t unused;
    in >> binary <uint16_t> (cnt_not_zero);
    in >> binary <uint8_t> (unused);
    extra_data_size += sizeof(uint16_t) + sizeof(uint8_t);

    if (in.std::ios::fail() || in.std::ios::bad()) {
        throw HuffmanException("Invalid format.");
    }

    uint8_t ch;
    int32_t cnt_ch;
    for (int32_t i = 0; i < static_cast <int32_t> (cnt_not_zero); ++i) {
        in >> binary <uint8_t> (ch);
        in >> binary <int32_t> (cnt_ch);
        if (in.std::ios::fail() || in.std::ios::bad()) {
            throw HuffmanException("Invalid format.");
        }

        cnt[ch] = cnt_ch;
    }
    extra_data_size += static_cast <int32_t> (cnt_not_zero) * (sizeof(uint8_t) + sizeof(int32_t));

    while (in >> binary <uint8_t> (ch)) {
        for (int32_t i = BYTE - 1; i >= 0; --i) {
            encoded.push_back((ch >> i) & 1);
        }
    }
    if (unused > encoded.size()) {
        throw HuffmanException("Invalid format.");
    }

    source_size = encoded.size() / BYTE * sizeof(uint8_t);

    for (int32_t i = 0; i < static_cast <int32_t> (unused); ++i) {
        encoded.pop_back();
    }

    in.close();
}

void HuffmanArchiver::output_encoded(const std::string & file_out, std::vector <bool> & encoded, std::vector <int32_t> & cnt) {
    uint16_t cnt_not_zero = 0;
    for (std::size_t i = 0; i < cnt.size(); ++i) {
        if (cnt[i] != 0) {
            ++cnt_not_zero;
        }
    }

    uint8_t unused = (BYTE - encoded.size() % BYTE) % BYTE;
    for (int32_t i = 0; i < static_cast <int32_t> (unused); ++i) {
        encoded.push_back(0);
    }

    std::ofstream out(file_out, std::ios_base::binary);

    out << binary <uint16_t> (cnt_not_zero);
    out << binary <uint8_t> (unused);
    extra_data_size += sizeof(uint16_t) + sizeof(uint8_t);

    for (std::size_t i = 0; i < cnt.size(); ++i) {
        if (cnt[i] != 0) {
            out << binary <uint8_t> (static_cast <uint8_t> (i));
            out << binary <int32_t> (cnt[i]);
        }
    }
    extra_data_size += static_cast <int32_t> (cnt_not_zero) * (sizeof(uint8_t) + sizeof(int32_t));

    for (std::size_t i = 0; i < encoded.size(); i += BYTE) {
        uint8_t bin_char = 0;
        for (int32_t j = BYTE - 1; j >= 0; --j) {
            bin_char += (1 << j) * encoded[i + BYTE - 1 - j];
        }
        out << binary <uint8_t> (bin_char);
    }
    result_size = encoded.size() / BYTE * sizeof(uint8_t);
    encoded.resize(encoded.size() - unused);

    out.close();
}

void HuffmanArchiver::output_decoded(const std::string & file_out, const std::vector <uint8_t> & decoded) {
    std::ofstream out(file_out, std::ios_base::binary);

    for (std::size_t i = 0; i < decoded.size(); ++i) {
        out << binary <uint8_t> (decoded[i]);
    }
    result_size = decoded.size() * sizeof(uint8_t);

    out.close();
}


void HuffmanArchiver::counting(const std::vector <uint8_t> & source, std::vector <int32_t> & cnt) noexcept {
    for (auto ch : source) {
        ++cnt[ch];
    }
}

std::size_t HuffmanArchiver::get_source_size() const noexcept {
    return source_size;
}

std::size_t HuffmanArchiver::get_result_size() const noexcept {
    return result_size;
}

std::size_t HuffmanArchiver::get_extra_data_size() const noexcept {
    return extra_data_size;
}