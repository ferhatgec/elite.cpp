// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#include <fstream>

#include "../include/elite.hpp"
#include "../include/helpers.hpp"
#include "../include/tokenizer.hpp"

bool EliteRead::check_is_elite(const std::string& file) noexcept {
    return to_lowercase(file) == GENERIC_FILENAME ? true : false;
}

void EliteRead::read_raw_file(const std::string& file) noexcept {
    if(!check_is_elite(file)) {
        std::cout << "to_lowercase(" << file << ") ignored\n";
    }

    std::ifstream stream(file);

    for(std::string temporary_data; std::getline(stream, temporary_data);) {
        if(tokenizer::is_comment(temporary_data)) { continue; }

        this->raw_data.append(" " + temporary_data + "\n");
    }
}