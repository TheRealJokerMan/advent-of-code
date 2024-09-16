//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib02.hxx"
#include "lib/str.hxx"

#include <regex>

namespace com::day05
{
    struct Table
    {
        std::vector<std::pair<uint64_t, uint64_t>> seedRanges;
        std::vector<Map>                           maps;
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
                auto const seeds{ common::toVectorUInt(contents) };

                if ((seeds.size() % 2) != 0)
                    throw std::range_error("Seeds are not supplied as a multiple of two.");

                for (auto seedIt = seeds.begin(); seedIt != seeds.end(); ++seedIt)
                {
                    auto nextSeedIt{ std::next(seedIt) };

                    table->seedRanges.emplace_back(std::make_pair(*seedIt, *nextSeedIt));

                    ++seedIt; // skip an element as these are pairs.
                }
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

    // TODO: Refactor this. I've written geometric algorithms smarter than this.
    auto part02(std::vector<std::string> const& data) -> int64_t
    {
        Table table;
        deserialize(data, &table);

        auto& ranges{ table.seedRanges };

        for (auto const& level : table.maps)
        {
            for (auto i = 0u; i < table.seedRanges.size(); ++i)
            {
                for (auto const& map : level.ranges)
                {
                    auto const start{ ranges[i].first };
                    auto const end{ ranges[i].first + ranges[i].second };

                    if (start >= map.source and end <= map.source + map.range)
                    {
                        ranges[i].first = map.destination + (start - map.source);
                        break;
                    }
                    else if (map.source >= start and map.source + map.range <= end)
                    {
                        table.seedRanges.push_back(std::make_pair(start, map.source - start));
                        table.seedRanges.push_back(std::make_pair(map.source + map.range, end - (map.source + map.range)));

                        ranges[i].first = map.destination;
                        ranges[i].second = map.range;
                        break;
                    }
                    else if (start >= map.source and start < map.source + map.range)
                    {
                        auto const length{ map.source + map.range - start };

                        table.seedRanges.push_back({ start + length, ranges[i].second - length });

                        ranges[i].first = start + map.destination - map.source;
                        ranges[i].second = length;
                        break;
                    }
                    else if (end > map.source and end < map.source + map.range)
                    {
                        auto const length{ map.source - start };

                        table.seedRanges.push_back({ start, length });

                        ranges[i].first = map.destination;
                        ranges[i].second = ranges[i].second - length;
                        break;
                    }
                }
            }
        }

        return std::ranges::min_element(table.seedRanges, [](auto const& a, auto const& b) { return a.first < b.first; })->first;
    }
} // namespace com::day05
