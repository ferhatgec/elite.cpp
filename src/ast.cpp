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

    this->add_token(this->ast_set  , EliteKeywords::Set  );
    this->add_token(this->ast_as   , EliteKeywords::As   );
    this->add_token(this->ast_for  , EliteKeywords::For  );
    this->add_token(this->ast_print, EliteKeywords::Print);

    this->add_token(this->ast_left_parenthese , EliteKeywords::LeftParenthese );
    this->add_token(this->ast_right_parenthese, EliteKeywords::RightParenthese);

    this->add_token(this->ast_square_left_bracket , EliteKeywords::LeftSqBracket );
    this->add_token(this->ast_square_right_bracket, EliteKeywords::RightSqBracket);
}

void EliteAST::add_token(std::string token, EliteKeywords token_type) noexcept {
    this->syntax_list.insert(std::make_pair(token, token_type));
}

EliteKeywords EliteAST::match_types(std::string& token) noexcept {
    auto token_type = this->syntax_list.find(token);

    if(token_type != this->syntax_list.end()) {
        return token_type->second;
    }

    return EliteKeywords::Undefined;
}

std::string EliteAST::extract_arg(std::string argument) noexcept {
    if(argument.front() == '"' && argument.back() == '"' && argument.length() >= 2) {
        argument.erase(argument.end() - 1);
        argument.erase(argument.begin()          );

        return argument;
    } return "";
}