// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef ELITE_CPP_READ_HPP
#define ELITE_CPP_READ_HPP

#include <vector>
#include <string>
#include "elite.hpp"

#define GENERIC_FILENAME "elitefile"

class EliteRead {
public:
    std::string raw_data;

    std::vector<std::string> unparsed;
public:
    EliteRead() = default;
    ~EliteRead()= default;

    bool check_is_elite(const std::string& file) noexcept;
    void read_raw_file (const std::string& file) noexcept;
};

#endif // ELITE_CPP_READ_HPP
