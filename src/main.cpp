#include <iostream>
#include <cstring>

#include "HuffmanArchiver.hpp"

static const int ARGC_CORRECT = 6;

int main(int argc, char ** argv) {
    HuffmanArchiver archiver;

    try {
        if (argc != ARGC_CORRECT) {
            throw HuffmanException("Invalid arguments.");
        }

        int action_idx = 0;
        int file_in_idx = 0;
        int file_out_idx = 0;
        for (int i = 1; i < argc; ++i) {
            if (action_idx == 0 && (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "-u") == 0)) {
                action_idx = i;
            }
            else if (file_in_idx == 0 && strcmp(argv[i], "-f") == 0) {
                file_in_idx = i + 1;
                ++i;
            }
            else if (file_out_idx == 0 && strcmp(argv[i], "-o") == 0) {
                file_out_idx = i + 1;
                ++i;
            }
        }

        if (action_idx == 0) {
            throw HuffmanException("Invalid arguments (action).");
        }
        if (!(0 < file_in_idx && file_in_idx < argc)) {
            throw HuffmanException("Invalid arguments (file_in).");
        }
        if (!(0 < file_out_idx && file_out_idx < argc)) {
            throw HuffmanException("Invalid arguments (file_out).");
        }

        if (strcmp(argv[action_idx], "-c") == 0) {
            archiver.encode(argv[file_in_idx], argv[file_out_idx]);
        }
        else {
            archiver.decode(argv[file_in_idx], argv[file_out_idx]);
        }

        std::cout << archiver.get_source_size() << std::endl;
        std::cout << archiver.get_result_size() << std::endl;
        std::cout << archiver.get_extra_data_size() << std::endl;
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