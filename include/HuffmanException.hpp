#pragma once

#include <string>
#include <stdexcept>

class HuffmanException : public std::logic_error {
public:
    HuffmanException(const std::string & s) : std::logic_error(s) {}
};