// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef ELITE_CPP_HELPERS_HPP
#define ELITE_CPP_HELPERS_HPP

#include <cctype>
#include <algorithm>
#include <sstream>

#include "elite.hpp"

namespace {
    static inline std::string to_lowercase(std::string data) noexcept {
        std::transform(data.begin(), data.end(), data.begin(),
                       [](unsigned char ch) { return std::tolower(ch); });

        return data;
    }

    static inline std::string left_trim(std::string data) noexcept {
        data.erase(data.begin(),
                   std::find_if(data.begin(), data.end(),
                                [](unsigned char ch){ return !std::isspace(ch); }));

        return data;
    }

    static inline std::string right_trim(std::string data) noexcept {
        data.erase(std::find_if(data.rbegin(), data.rend(),
                                [](unsigned char ch){ return !std::isspace(ch); })
                                .base(), data.end());

        return data;
    }

    static inline std::vector<std::string>
            split_ws(std::string data) noexcept {
        std::vector<std::string> temporary;
        std::istringstream       stream(data);

        for(std::string __temporary; stream >> __temporary;
            temporary.push_back(__temporary));

        return temporary;
    }

    static inline std::string to_str(char arg) noexcept {
        std::string __str(1, arg); return __str;
    }

    static inline std::string __replace(std::string __str,
                                         const std::string& from,
                                         const std::string& to) noexcept {
        if(!from.empty()) {
            for(std::size_t pos = 0;
                (pos = __str.find(from, pos)) != std::string::npos;
                pos += to.size()) {
                __str.replace(pos, from.size(), to);
            }
        }

        return __str;
    }
}

#endif // ELITE_CPP_HELPERS_HPP
