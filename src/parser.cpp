// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#include "../include/ast.hpp"
#include "../include/elite.hpp"
#include "../include/parser.hpp"
#include "../include/helpers.hpp"

void EliteParser::parse_tokens(std::vector <std::string> tokens) noexcept {
    auto __matched_type = EliteKeywords::Undefined;

    bool is_variable         = false,
         is_data             = false,

         is_for              = false,
         is_for_argument     = false,

         is_print            = false,

         is_use              = false,
         is_use_argument     = false,

         is_data_initializer = false;

    std::string variable_name, variable_data;

    for(auto& token : tokens) {
        if(token.empty()) { continue; }

        auto __token   = right_trim(left_trim(token));


        __matched_type = this->init_ast.match_types(__token);

        switch(__matched_type) {
            case EliteKeywords::Set  : {
                is_variable = true;

                continue;
            }

            case EliteKeywords::As   : {
                if(is_variable) {
                    is_data_initializer = true;

                    continue;
                }

                // Syntax error {set}

                continue;
            }

            case EliteKeywords::For  : {
                is_for = true;

                continue;
            }

            case EliteKeywords::Print: {
                is_print = true;

                continue;
            }

            case EliteKeywords::Use  : {
                is_use = true;

                continue;
            }

            case EliteKeywords::LeftParenthese :
            case EliteKeywords::RightParenthese:
            case EliteKeywords::LeftSqBracket  :
            case EliteKeywords::RightSqBracket : {}

            default: {
                if(is_use) {
                    if(is_use_argument) {
                        auto __token__ = this->init_ast.extract_arg(__token);

                        for(auto& argument : this->init_ast.ast_for_use_argument) {
                            if(argument == __token__) {
                                this->ast_parse_use(__token__);
                            }
                        }

                        continue;
                    }

                    for(auto& function : this->init_ast.ast_for_use) {
                        if(function == __token) {
                            is_use_argument = true;

                            continue;
                        }
                    }
                }

                if(is_print) {
                    std::cout <<
                        this->init_ast.extract_arg(__token);

                    is_print = false;

                    continue;
                }

                if(is_for) {
                    if(is_for_argument) {
                        auto __token__ = this->init_ast.extract_arg(__token);

                        for(auto& argument : this->init_ast.ast_for_functions_arguments) {
                            if(argument == __token__) {
                                // TODO: Signal parser
                                break;
                            }
                        }

                        is_for = is_for_argument = false;

                        continue;
                    }

                    for(auto& function : this->init_ast.ast_for_functions) {
                        if(function == __token) {
                            is_for_argument = true;
                            break;
                        }
                    }

                    continue;
                }

                if(is_variable) {
                    if(is_data_initializer) {
                        is_variable = is_data_initializer = false;

                        this->token_set(variable_name, __token);

                        variable_name.clear();

                        continue;
                    }

                    variable_name = __token;

                    continue;
                }
            }
        }
    }
}

void EliteParser::ast_parse_use(std::string argument) noexcept {
    switch(this->init_ast.match_use_arguments(argument)) {
        case EliteASTUseArguments::Exit: {
            std::exit(1);
        }

        default: {
            // Syntax error (undefined argument)
        }
    }
}

void EliteParser::token_set(std::string variable, std::string data) noexcept {
    this->data_tree.variable_list.push_back(
            EliteDataInfos {
                EliteKeywords::Set,
                variable,
                data
            });
}