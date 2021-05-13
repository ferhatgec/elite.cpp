// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#include <iostream>
#include <fstream>

#include "../include/elite.hpp"
#include "../include/lexer.hpp"

int main(int argc, char** argv) noexcept {
    if(argc < 2) {
        std::cout << "Fegeya Elite - small, powerful build system\n"; std::exit(1);
    }

    EliteRead init_reader;

    init_reader.read_raw_file(std::string(argv[1]));

    lexer::init_lexer(init_reader, argv, argc);
}