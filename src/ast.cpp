// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#include "../include/elite.hpp"
#include "../include/ast.hpp"

void EliteAST::init_keywords() noexcept  {
    this->ast_set    = "set"                 ;
    this->ast_as     = "as"                  ;
    this->ast_for    = "for"                 ;
    this->ast_print  = "print"               ;
    this->ast_println= this->ast_print + "ln";
    this->ast_use    = "use"                 ;
    this->ast_if     = "if"                  ;

    this->ast_left_parenthese = "(";
    this->ast_right_parenthese= ")";

    this->ast_square_left_bracket = "[";
    this->ast_square_right_bracket= "]";

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

    this->add_token(this->ast_set         , EliteKeywords::Set    );
    this->add_token(this->ast_as          , EliteKeywords::As     );
    this->add_token(this->ast_for         , EliteKeywords::For    );
    this->add_token(this->ast_print       , EliteKeywords::Print  );
    this->add_token(this->ast_println     , EliteKeywords::Println);
    this->add_token(this->ast_use         , EliteKeywords::Use    );
    this->add_token(this->ast_if          , EliteKeywords::If     );

    this->add_token(this->ast_left_parenthese , EliteKeywords::LeftParenthese );
    this->add_token(this->ast_right_parenthese, EliteKeywords::RightParenthese);

    this->add_token(this->ast_square_left_bracket , EliteKeywords::LeftSqBracket );
    this->add_token(this->ast_square_right_bracket, EliteKeywords::RightSqBracket);

    this->add_for_function("signal"  , EliteASTForFunctions::Signal  );
    this->add_for_function("specific", EliteASTForFunctions::Specific);
    this->add_for_function("argument", EliteASTForFunctions::Argument);
    this->add_for_function("exists"  , EliteASTForFunctions::Exists  );

    this->add_for_specific_target("windows"  , EliteASTForSpecificTargets::Windows  );
    this->add_for_specific_target("macos"    , EliteASTForSpecificTargets::macOS    );
    this->add_for_specific_target("ios"      , EliteASTForSpecificTargets::iOS      );
    this->add_for_specific_target("linux"    , EliteASTForSpecificTargets::Linux    );
    this->add_for_specific_target("android"  , EliteASTForSpecificTargets::Android  );
    this->add_for_specific_target("freebsd"  , EliteASTForSpecificTargets::FreeBSD  );
    this->add_for_specific_target("dragonfly", EliteASTForSpecificTargets::DragonFly);
    this->add_for_specific_target("openbsd"  , EliteASTForSpecificTargets::OpenBSD  );
    this->add_for_specific_target("netbsd"   , EliteASTForSpecificTargets::NetBSD   );

    this->add_if_function ("eq"   , EliteASTIfFunctions::Eq     );

    this->add_use_function("signal", EliteASTUseFunctions::Signal);
    this->add_use_function("exec"  , EliteASTUseFunctions::Exec  );

    this->add_use_argument("exit", EliteASTUseArguments::Exit   );
}

void EliteAST::add_token(std::string token, EliteKeywords token_type) noexcept {
    this->syntax_list.insert(std::make_pair(token, token_type));
}

void EliteAST::add_for_function(std::string function, EliteASTForFunctions token_type) noexcept {
    this->ast_for_functions.insert(std::make_pair(function, token_type));
}

void EliteAST::add_for_specific_target(std::string function, EliteASTForSpecificTargets token_type) noexcept {
    this->ast_for_specific_targets.insert(std::make_pair(function, token_type));
}

void EliteAST::add_if_function(std::string statement, EliteASTIfFunctions token_type) noexcept {
    this->ast_if_functions.insert(std::make_pair(statement, token_type));
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
    } return EliteKeywords::Undefined;
}

EliteASTForFunctions EliteAST::match_for_functions(std::string function) noexcept {
    auto function_type = this->ast_for_functions.find(function);

    if(function_type != this->ast_for_functions.end()) {
        return function_type->second;
    } return EliteASTForFunctions::Undefined;
}

EliteASTForSpecificTargets EliteAST::match_for_specific_targets(std::string target) noexcept {
    auto target_type = this->ast_for_specific_targets.find(target);

    if(target_type != this->ast_for_specific_targets.end()) {
        return target_type->second;
    } return EliteASTForSpecificTargets::Undefined;
}

EliteASTIfFunctions EliteAST::match_if_functions(std::string statement) noexcept {
    auto statement_type = this->ast_if_functions.find(statement);

    if(statement_type != this->ast_if_functions.end()) {
        return statement_type->second;
    } return EliteASTIfFunctions::Undefined;
}

EliteASTUseFunctions EliteAST::match_use_functions(std::string function) noexcept {
    auto function_type = this->ast_use_functions.find(function);

    if(function_type != this->ast_use_functions.end()) {
        return function_type->second;
    } return EliteASTUseFunctions::Undefined;
}

EliteASTUseArguments EliteAST::match_use_arguments(std::string argument) noexcept {
    auto argument_type = this->ast_use_list.find(argument);

    if(argument_type != this->ast_use_list.end()) {
        return argument_type->second;
    } return EliteASTUseArguments::Undefined;
}