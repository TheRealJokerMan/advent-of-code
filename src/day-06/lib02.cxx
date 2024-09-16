//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib02.hxx"

#include <ranges>
#include <regex>

namespace com::day06
{
    struct Table
    {
        uint64_t time;
        uint64_t distance;
    };

    static void deserialize(std::regex const& re, std::string const& input, uint64_t* result)
    {
        std::smatch match;

        if (std::regex_search(input, match, re))
        {
            auto const contents{ input.substr(match.length(), input.length() - match.length() + 1) };

            *result = 0;
            for (auto const c : contents)
            {
                if (!std::isdigit(c))
                    continue;

                *result *= 10;
                *result += c - '0';
            }
        }
    }

    static void deserialize(std::vector<std::string> const& data, Table* table)
    {
        for (auto const& line : data)
        {
            deserialize(std::regex("Time\\s*:"), line, &table->time);
            deserialize(std::regex("Distance\\s*:"), line, &table->distance);
        }
    }

    auto part02(std::vector<std::string> const& data) -> int64_t
    {
        Table table;
        deserialize(data, &table);

        return countSolutions(table.time, table.distance);
    }
} // namespace com::day06
