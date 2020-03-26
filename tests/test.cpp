#include <iostream>

#include "HuffmanTreeTest.hpp"
#include "HuffmanArchiverTest.hpp"

int main() {
    try {
        HuffmanTreeTest::runAllTests();
        HuffmanArchiverTest::runAllTests();
        AutoTest::showFinalResult();
    }
    catch (HuffmanException & h) {
        std::cout << h.what() << std::endl;
    }
    catch (std::bad_alloc & b) {
        std::cout << "Unable to allocate memory." << std::endl;
    }
    catch (...) {
        std::cout << "Something went wrong..." << std::endl;
    }

    return 0;
}