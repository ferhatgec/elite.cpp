#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"

// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#include <filesystem>

#include "../include/ast.hpp"
#include "../include/elite.hpp"
#include "../include/parser.hpp"
#include "../include/helpers.hpp"
#include "../include/tokenizer.hpp"

void EliteParser::parse_tokens(std::vector <std::string> tokens) noexcept {
    auto __matched_type          = EliteKeywords::Undefined       ;
    auto __last_matched_function = EliteASTForFunctions::Undefined;

    bool is_variable         = false,
         is_defined          = false,

         is_for              = false,
         is_for_argument     = false,

         is_print            = false,
         is_newline          = false,

         is_use              = false,
         is_use_argument     = false,

         is_data_initializer = false,

         is_function         = false,
         is_main_os          = true;

    u32 count_end_of_function= 0;

    std::string variable_name, variable_data;

    for(auto& token : tokens) {
        if(token.empty()) { continue; }

        auto __token   = right_trim(left_trim(token));

        if(is_defined) {
            __token    = this->token_get(__token);

            is_defined = false;
        }
        else if(tokenizer::is_variable(__token)) { is_defined = true; continue; }

        __matched_type = this->init_ast.match_types(__token);

        switch(__matched_type) {
            case EliteKeywords::Set    : {
                is_variable = true;

                continue;
            }

            case EliteKeywords::As     : {
                if(is_variable) {
                    is_data_initializer = true;

                    continue;
                }

                // Syntax error {set}

                continue;
            }

            case EliteKeywords::For    : {
                is_for = true;

                continue;
            }

            case EliteKeywords::Print  : {
                is_print = true;

                continue;
            }

            case EliteKeywords::Println: {
                is_print = is_newline = true;

                continue;
            }

            case EliteKeywords::Use    : {
                is_use = true;

                continue;
            }

            case EliteKeywords::LeftParenthese :
            case EliteKeywords::RightParenthese: {}


            case EliteKeywords::LeftSqBracket  : {
                if(is_main_os) {
                    ++count_end_of_function;
                }

                continue;
            }

            case EliteKeywords::RightSqBracket : {
                if(is_main_os) {
                    --count_end_of_function;
                } else { is_main_os = true; }

                if(count_end_of_function == 0) {
                    is_main_os = is_function = false;
                }

                continue;
            }

            default: {
                if(!is_main_os) {
                    is_print        =
                    is_newline      =
                    is_use          =
                    is_use_argument = false;

                    continue;
                }

                if(tokenizer::is_data(__token)) {
                    std::string __data, __format      ;
                    bool        __is_formatter = false;

                    for(auto& character : __token) {
                        if(__is_formatter) {
                            if(character == '}') {
                                __is_formatter = false;
                                __data.append(this->token_get(__format));

                                __format.clear();

                                continue;
                            }

                            __format.push_back(character);

                            continue;
                        }

                        if(character == '{') {
                            __is_formatter = true;

                            continue;
                        }

                        __data.push_back(character);
                    }

                    __token = __data;
                }

                if(is_use) {
                    if(is_use_argument) {
                        auto __token__ = ast_helpers::extract_arg(__token);

                        for(auto& argument : this->init_ast.ast_for_use_argument) {
                            if(argument == __token__) {
                                this->ast_parse_use(__token__);
                            }
                        }


                        if(__token__.empty()) { continue; }

                        this->ast_parse_use_function(variable_data,
                                                     __token__);

                        is_use = is_use_argument = false;

                        continue;
                    }

                    for(auto& function : this->init_ast.ast_for_use) {
                        if(function == __token) {
                            is_use_argument = true;
                            variable_data   = function;

                            continue;
                        }
                    }
                }

                if(is_print) {
                    std::cout <<
                        ast_helpers::extract_arg(__token);

                    if(is_newline) { std::cout << '\n'; }

                    is_print = is_newline = false;

                    continue;
                }

                if(is_for) {
                    if(is_for_argument) {
                        auto __token__ = ast_helpers::extract_arg(__token);

                        if(__token__.empty()) { __token__ = __token; }

                        switch(__last_matched_function) {
                            case EliteASTForFunctions::Specific:
                            case EliteASTForFunctions::Argument:
                            case EliteASTForFunctions::Exists  : {
                                is_main_os = this->ast_parse_for_functions(variable_name,
                                                                           __token__);
                            }

                            default: {
                                this->ast_parse_for_functions(variable_name,
                                                              __token__);
                            }
                        }


                        is_for = is_for_argument = false;

                        variable_name.clear();

                        continue;
                    }

                    if(this->init_ast.match_for_functions(__token) != EliteASTForFunctions::Undefined) {
                        is_for_argument         = true;
                        __last_matched_function = this->init_ast.match_for_functions(__token);

                        variable_name           = __token;
                    }

                    continue;
                }

                if(is_variable) {
                    if(is_data_initializer) {
                        is_variable = is_data_initializer = false;

                        this->token_set(variable_name,
                                        ast_helpers::extract_arg(__token));

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

bool EliteParser::ast_parse_for_functions(std::string function, std::string argument) noexcept {
    switch(this->init_ast.match_for_functions(function)) {
        case EliteASTForFunctions::Signal  : {
            // TODO: Signal parser

            return false;
        }

        case EliteASTForFunctions::Specific: {
            return this->ast_parse_for_specific_target(argument);
        }

        case EliteASTForFunctions::Argument: {
            return this->is_same_arg(argument);
        }

        case EliteASTForFunctions::Exists  : {
            return this->is_exists(argument);
        }

        default: {
            // Syntax error (undefined function)
            return false;
        }
    }
}

bool EliteParser::ast_parse_for_specific_target(std::string target) noexcept {
    switch(this->init_ast.match_for_specific_targets(target)) {
        // case EliteASTForSpecificTargets::Windows: {
        //
        // }
        //
        // case EliteASTForSpecificTargets::macOS: {
        //
        // }<
        //
        // case EliteASTForSpecificTargets::iOS: {
        //
        // }
        //
        // case EliteASTForSpecificTargets::Linux: {
        //
        // }
        //
        // case EliteASTForSpecificTargets::Android: {
        //
        // }
        //
        // case EliteASTForSpecificTargets::FreeBSD: {
        //
        // }
        //
        // case EliteASTForSpecificTargets::DragonFly: {
        //
        // }
        //
        // case EliteASTForSpecificTargets::Bitrig: {
        //
        // }
        //
        // case EliteASTForSpecificTargets ::OpenBSD: {
        //
        // }
        //
        // case EliteASTForSpecificTargets::NetBSD: {
        //
        // }
        case EliteASTForSpecificTargets::Undefined: {
            return false;
        }

        default: {
            return this->is_same(target);
        }
    }
}

void EliteParser::ast_parse_use_function(std::string function, std::string argument) noexcept {
    switch(this->init_ast.match_use_functions(function)) {
        case EliteASTUseFunctions::Signal: {
            this->ast_parse_use(argument);
        }

        case EliteASTUseFunctions::Exec  : {
            if(std::system(argument.c_str())) {
                // Execution error
            }
        }

        default: {
            // Syntax error (Undefined function)
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
    for(std::size_t i = 0; i < this->data_tree.variable_list.size(); i++) {
        if(this->data_tree.variable_list[i].__name == variable) {
            this->data_tree.variable_list[i].__data = data;

            return;
        }
    }

    this->data_tree.variable_list.push_back(
            EliteDataInfos {
                EliteKeywords::Set,
                variable,
                data
            });
}

std::string EliteParser::token_get(std::string variable) noexcept {
    for(auto& variable_list : this->data_tree.variable_list) {
        if(variable == variable_list.__name) {
            if(variable_list.__type != EliteKeywords::Undefined) {
                return variable_list.__data;
            }
        }
    }

    return "";
}

bool EliteParser::is_exists(std::string& path) noexcept {
    return (std::filesystem::exists(path)) ? true : false;
}

bool EliteParser::is_same_arg(std::string& argument) noexcept {
    return (this->__argv[this->__argc - 1] == argument) ? true : false;
}

bool EliteParser::is_same(std::string& target) noexcept {
    return (this->to_os_keyword() == target) ? true : false;
}

std::string EliteParser::to_os_keyword() noexcept {
    #if defined(_WIN16)        \
        || defined(_WIN32)     \
        || defined(_WIN64)     \
        || defined(__WIN32__)  \
        || defined(__TOS_WIN__)\
        || defined(__WINDOWS__)
        return "windows";
    #elif defined(macintosh)   \
        || defined(Macintosh)
        || (defined(__APPLE__) && defined(__MACH__))
        return "macos";
    #elif defined(__linux__)    \
        || defined(linux)       \
        || defined(__linux)     \
        || defined(__gnu_linux__)
        return "linux";
    #elif defined(__ANDROID__)
        return "android";
    #elif (defined(__FreeBSD_kernel__)
        && defined(__GLIBC__))         \
        || defined(__FreeBSD__)        \
        || defined(__FreeBSD_kernel__)
        return "freebsd";
    #elif defined(__DragonFly__)
        return "dragonfly";
    #elif defined(__OpenBSD__)
        return "openbsd";
    #elif defined(__NetBSD__)
        return "netbsd";
    #endif
}