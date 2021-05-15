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

    char**        __argv   ;
    u32           __argc   ;
public:
    EliteParser(char** __argv__, u32 __argc__) : __argv(__argv__), __argc(__argc__) {
        this->init_ast.init_keywords();
    }

    ~EliteParser()= default;

    void parse_tokens            (std::vector<std::string> tokens       ) noexcept;

    bool ast_parse_for_functions (std::string function,
                                  std::string argument                  ) noexcept;
    bool
    ast_parse_for_specific_target(std::string target                    ) noexcept;

    bool ast_parse_if_function   (std::string function,
                                  std::string argument_1,
                                  std::string argument_2                ) noexcept;

    void ast_parse_use_function  (std::string function,
                                  std::string argument                  ) noexcept;

    void ast_parse_use           (std::string argument                  ) noexcept;

    void token_set               (std::string variable, std::string data) noexcept;
    std::string token_get        (std::string variable                  ) noexcept;

    bool is_exists               (std::string& path                     ) noexcept;
    bool is_same_arg             (std::string& argument                 ) noexcept;
    bool is_same                 (std::string& target                   ) noexcept;
    bool is_same_argument        (std::string& argument_1,
                                  std::string& argument_2               ) noexcept;
    std::string to_os_keyword    (                                      ) noexcept;
};

#endif // ELITE_CPP_PARSER_HPP
