#pragma once

#include <iostream>

template <typename T>
struct binary {
    const T & data;
    binary(const T & data) : data(data) {}
};

template <typename T>
std::istream & operator>> (std::istream & is, const binary <T> & m) {
    is.read(const_cast <char*> (reinterpret_cast <const char *> (&m.data)), sizeof(T));
    return is;
}

template <typename T>
std::ostream & operator<< (std::ostream & os, const binary <T> & m) {
    os.write(reinterpret_cast <const char *> (&m.data), sizeof(T));
    return os;
}