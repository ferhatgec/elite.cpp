// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef ELITE_CPP_TOKENIZER_HPP
#define ELITE_CPP_TOKENIZER_HPP

#include "elite.hpp"
#include "helpers.hpp"

namespace tokenizer {
    static std::vector<std::string> TOKEN_LIST = {
            "(",
            ")",
            "[",
            "]"
    };

    static inline bool is_data   (std::string token) noexcept {
        if(token.length() < 2) { return false; }

        return (left_trim(token).front() == '"' ||
                right_trim(token).back() == '"') ? true : false;
    }

    static inline bool is_fully_data(std::string token) noexcept {
        if(token.length() < 2) { return false; }

        return (left_trim(token).front() == '"' &&
            right_trim(token).back() == '"') ? true : false;
    }

    static inline bool is_comment(std::string token) noexcept {
        if(token.length() < 2) { return false; }

        return (left_trim(token).front() == '\\'
                || right_trim(token).back() == '\\') ? true : false;
    }

    static inline std::string replace_with(std::string token,
                                           char character) noexcept {
        token = __replace(token,
                          to_str(character)," " + to_str(character) + " ");

        return token;
    }

    static inline std::string get_data(std::vector<std::string> tokens,
                                       std::size_t n) noexcept {
        std::string temporary;

        temporary.append(tokens[n]);

        if(is_fully_data(temporary)) {
            return temporary;
        }

        for(n += 1; n < tokens.size(); n++) {
            if(tokens[n].empty()) { continue; }

            if(!is_data(tokens[n])) {
                temporary.append(" " + tokens[n]);

                continue;
            }

            temporary.append(" " + tokens[n]);

            break;
        }

        return temporary;
    }

    static inline std::string replace_for_tokenize(std::string token) noexcept {
        for(auto& character : TOKEN_LIST) {
            token = replace_with(token, character[0]);
        }

        return token;
    }

    static inline std::vector<std::string> tokenize_first(EliteRead& raw_data) noexcept {
        auto temporary_tokens  = split_ws(raw_data.raw_data);
        std::vector<std::string> tokenized_data;

        std::string variable_data;

        bool found_data = false;

        for(std::size_t i = 0; i < temporary_tokens.size(); i++) {
            if(is_data(temporary_tokens[i])) {
                tokenized_data
                    .push_back(get_data(temporary_tokens, i));

                continue;
            }

            auto tokenize = replace_for_tokenize(temporary_tokens[i]);
            auto x        = split_ws(tokenize);

            for(auto& operators : x) {
                variable_data.append    (operators);

                tokenized_data.push_back(operators);
            }
        }

        return tokenized_data;
    }
}

#endif // ELITE_CPP_TOKENIZER_HPP