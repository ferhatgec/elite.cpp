// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef ELITE_CPP_AST_HPP
#define ELITE_CPP_AST_HPP

#include <unordered_map>

#include "elite.hpp"

enum class EliteKeywords {
    Set,
    As,
    For,
    Print,
    Println,
    Use,
    If,

    LeftParenthese,
    RightParenthese,

    LeftSqBracket,
    RightSqBracket,

    Undefined
};

enum class EliteASTIfFunctions {
    Eq,
    UnEq,

    Undefined
};

enum class EliteASTForFunctions {
    Signal,
    Specific,
    Argument,
    Exists,

    Undefined
};

enum class EliteASTForSpecificTargets {
    Windows,
    macOS,
    iOS,
    Linux,
    Android,
    FreeBSD,
    DragonFly,
    OpenBSD,
    NetBSD,

    Undefined
};

enum class EliteASTUseFunctions {
    Signal,
    Exec,

    Undefined
};

enum class EliteASTUseArguments {
    Exit,

    Undefined
};

class EliteAST{
public:
    std::string ast_set    ;
    std::string ast_as     ;
    std::string ast_for    ;
    std::string ast_print  ;
    std::string ast_println;
    std::string ast_use    ;
    std::string ast_if     ;

    std::string ast_left_parenthese;
    std::string ast_right_parenthese;

    std::string ast_square_left_bracket ;
    std::string ast_square_right_bracket;

    std::vector<std::string> ast_for_use                ;

    std::vector<std::string> ast_for_functions_arguments;
    std::vector<std::string> ast_for_use_argument       ;

    std::unordered_map<std::string, EliteKeywords             > syntax_list             ;

    std::unordered_map<std::string, EliteASTForFunctions      > ast_for_functions       ;
    std::unordered_map<std::string, EliteASTForSpecificTargets> ast_for_specific_targets;
    std::unordered_map<std::string, EliteASTIfFunctions       > ast_if_functions        ;
    std::unordered_map<std::string, EliteASTUseFunctions      > ast_use_functions       ;
    std::unordered_map<std::string, EliteASTUseArguments      > ast_use_list            ;
public:
    EliteAST() = default;
    ~EliteAST()= default;

    void          init_keywords   ()                                noexcept;
    void          add_token       (std::string token,
                                EliteKeywords token_type)           noexcept;
    void          add_for_function(std::string function,
                                   EliteASTForFunctions token_type) noexcept;
    void
           add_for_specific_target(std::string function,
                             EliteASTForSpecificTargets token_type) noexcept;
    void          add_if_function (std::string statement,
                                   EliteASTIfFunctions  token_type) noexcept;
    void          add_use_function(std::string function,
                                   EliteASTUseFunctions token_type) noexcept;
    void          add_use_argument(std::string argument,
                                   EliteASTUseArguments token_type) noexcept;

    EliteKeywords match_types               (std::string& token  )  noexcept;
    EliteASTForFunctions match_for_functions(std::string function)  noexcept;
    EliteASTForSpecificTargets
                  match_for_specific_targets(std::string target  )  noexcept;
    EliteASTIfFunctions  match_if_functions (std::string statement) noexcept;
    EliteASTUseFunctions match_use_functions(std::string function)  noexcept;
    EliteASTUseArguments match_use_arguments(std::string argument)  noexcept;
};

class EliteDataInfos {
public:
    EliteKeywords __type;

    std::string   __name;
    std::string   __data;
};

class EliteDataTree {
public:
    std::vector<EliteDataInfos> variable_list;
};

namespace ast_helpers {
    static inline std::string extract_arg(std::string argument) noexcept {
        if(argument.front() == '"' && argument.back() == '"' && argument.length() >= 2) {
            argument.erase(argument.end() - 1);
            argument.erase(argument.begin()          );

            return argument;
        } return "";
    }
}

#endif // ELITE_CPP_AST_HPP
