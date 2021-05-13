// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#include "../include/elite.hpp"
#include "../include/ast.hpp"

void EliteAST::init_keywords() noexcept  {
    this->ast_set  = "set"  ;
    this->ast_as   = "as"   ;
    this->ast_for  = "for"  ;
    this->ast_print= "print";
    this->ast_use  = "use"  ;

    this->ast_left_parenthese = "(";
    this->ast_right_parenthese= ")";

    this->ast_square_left_bracket = "[";
    this->ast_square_right_bracket= "]";

    this->ast_for_functions = std::vector<std::string> {
        "signal"
    };

    this->ast_for_functions_arguments = std::vector<std::string> {
        "start"
    };

    this->ast_for_use = std::vector<std::string> {
        "signal",
        "exec"
    };

    this->ast_for_use_argument = std::vector<std::string> {
        "exit"
    };

    this->add_token(this->ast_set  , EliteKeywords::Set  );
    this->add_token(this->ast_as   , EliteKeywords::As   );
    this->add_token(this->ast_for  , EliteKeywords::For  );
    this->add_token(this->ast_print, EliteKeywords::Print);
    this->add_token(this->ast_use  , EliteKeywords::Use  );

    this->add_token(this->ast_left_parenthese , EliteKeywords::LeftParenthese );
    this->add_token(this->ast_right_parenthese, EliteKeywords::RightParenthese);

    this->add_token(this->ast_square_left_bracket , EliteKeywords::LeftSqBracket );
    this->add_token(this->ast_square_right_bracket, EliteKeywords::RightSqBracket);

    this->add_use_function("signal", EliteASTUseFunctions::Signal);
    this->add_use_function("exec"  , EliteASTUseFunctions::Exec  );

    this->add_use_argument("exit", EliteASTUseArguments::Exit   );
}

void EliteAST::add_token(std::string token, EliteKeywords token_type) noexcept {
    this->syntax_list.insert(std::make_pair(token, token_type));
}

void EliteAST::add_use_function(std::string function, EliteASTUseFunctions token_type) noexcept {
    this->ast_use_functions.insert(std::make_pair(function, token_type));
}

void EliteAST::add_use_argument(std::string argument, EliteASTUseArguments token_type) noexcept {
    this->ast_use_list.insert(std::make_pair(argument, token_type));
}

EliteKeywords EliteAST::match_types(std::string& token) noexcept {
    auto token_type = this->syntax_list.find(token);

    if(token_type != this->syntax_list.end()) {
        return token_type->second;
    }

    return EliteKeywords::Undefined;
}

EliteASTUseFunctions EliteAST::match_use_functions(std::string function) noexcept {
    auto function_type = this->ast_use_functions.find(function);

    if(function_type != this->ast_use_functions.end()) {
        return function_type->second;
    }

    return EliteASTUseFunctions::Undefined;
}

EliteASTUseArguments EliteAST::match_use_arguments(std::string argument) noexcept {
    auto argument_type = this->ast_use_list.find(argument);

    if(argument_type != this->ast_use_list.end()) {
        return argument_type->second;
    }

    return EliteASTUseArguments::Undefined;
}