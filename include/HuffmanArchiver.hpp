#pragma once

#include <fstream>

#include "binary.hpp"
#include "HuffmanTree.hpp"

class HuffmanArchiver {
private:
    std::size_t source_size = 0;
    std::size_t result_size = 0;
    std::size_t extra_data_size = 0;

public:
    void encode(const std::string & file_in, const std::string & file_out);
    void decode(const std::string & file_in, const std::string & file_out);

    std::size_t get_source_size() const noexcept;
    std::size_t get_result_size() const noexcept;
    std::size_t get_extra_data_size() const noexcept;

private:
    void input_source(const std::string & file_in, std::vector <uint8_t> & source);
    void output_encoded(const std::string & file_out, std::vector <bool> & encoded, std::vector <int32_t> & cnt);

    void input_encoded(const std::string & file_in, std::vector <bool> & encoded, std::vector <int32_t> & cnt);
    void output_decoded(const std::string & file_out, const std::vector <uint8_t> & decoded);

    void counting(const std::vector <uint8_t> & source, std::vector <int32_t> & cnt) noexcept;

    friend class HuffmanArchiverTest;
};