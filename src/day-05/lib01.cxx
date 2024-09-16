//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib01.hxx"

#include <regex>

namespace com::day05
{
    struct Table
    {
        std::vector<uint64_t> seeds;
        std::vector<Map>      maps;
    };

    static void deserialize(std::vector<std::string> const& data, Table* table)
    {
        std::smatch match;
        std::regex  reMap("([\\w|-]+)\\s+map:");
        std::regex  reSeeds("seeds\\s*:");
        Map*        currentMap{};

        for (auto const& line : data)
        {
            if (line.empty())
                continue;

            if (std::regex_search(line, match, reSeeds)) // Match the table header.
            {
                auto const contents{ line.substr(match.length(), line.length() - match.length() + 1) };
                table->seeds = common::toVectorUInt(contents);
            }
            else if (std::regex_search(line, match, reMap)) // Match a map header.
            {
                currentMap = &table->maps.emplace_back(match.str(1));
            }
            else if (currentMap)
            {
                auto const v{ common::toVectorUInt(line) };

                if (v.size() == 3)
                    currentMap->addRange(v[1], v[0], v[2]);
            }
        }
    }

    auto part01(std::vector<std::string> const& data) -> int64_t
    {
        Table table;
        deserialize(data, &table);

        for (auto const& level : table.maps)
        {
            for (auto& seed : table.seeds)
            {
                for (auto map : level.ranges)
                {
                    if (seed >= map.source and seed < map.source + map.range)
                    {
                        seed = map.destination + (seed - map.source);
                        break;
                    }
                }
            }
        }

        return *std::ranges::min_element(table.seeds);
    }
} // namespace com::day05
