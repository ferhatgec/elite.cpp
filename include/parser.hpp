// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef ELITE_CPP_PARSER_HPP
#define ELITE_CPP_PARSER_HPP

#include "ast.hpp"
#include "elite.hpp"

class EliteParser {
public:
    EliteAST      init_ast ;
    EliteDataTree data_tree;
public:
    EliteParser() {
        this->init_ast.init_keywords();
    }

    ~EliteParser()= default;

    void parse_tokens(std::vector<std::string> tokens       ) noexcept;
    void token_set   (std::string variable, std::string data) noexcept;
};

#endif // ELITE_CPP_PARSER_HPP
