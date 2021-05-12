// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef ELITE_CPP_LEXER_HPP
#define ELITE_CPP_LEXER_HPP

#include "ast.hpp"
#include "parser.hpp"
#include "elite.hpp"
#include "tokenizer.hpp"

namespace lexer {
    static inline void init_lexer(EliteRead& init) noexcept {
        auto        tokens      = tokenizer::tokenize_first(init);
        EliteParser init_parser;


        init_parser.parse_tokens(tokens);
    }
}

#endif // ELITE_CPP_LEXER_HPP
