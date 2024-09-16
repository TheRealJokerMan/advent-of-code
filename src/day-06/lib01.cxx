//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib01.hxx"

#include <ranges>
#include <regex>

namespace com::day06
{
    struct Table
    {
        std::vector<uint64_t> times;
        std::vector<uint64_t> distances;
    };

    static void deserialize(std::regex const& re, std::string const& input, std::vector<uint64_t>* result)
    {
        std::smatch match;

        if (std::regex_search(input, match, re))
        {
            auto const contents{ input.substr(match.length(), input.length() - match.length() + 1) };

            result->assign_range(common::toVectorUInt(contents));
        }
    }

    static void deserialize(std::vector<std::string> const& data, Table* table)
    {
        for (auto const& line : data)
        {
            deserialize(std::regex("Time\\s*:"), line, &table->times);
            deserialize(std::regex("Distance\\s*:"), line, &table->distances);
        }
    }

    auto part01(std::vector<std::string> const& data) -> int64_t
    {
        Table table;
        deserialize(data, &table);

        int64_t result{ 1 };
        auto    records{ std::views::zip(table.times, table.distances) };
        std::ranges::for_each(records,
                              [&](auto&& v)
                              {
                                  auto&& [t, d] = v;
                                  result *= countSolutions(t, d);
                              });

        return result;
    }
} // namespace com::day06
