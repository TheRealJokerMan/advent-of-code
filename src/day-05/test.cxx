//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib/str.hxx"
#include "lib01.hxx"
#include "lib02.hxx"

#include <catch2/catch_all.hpp>

namespace com
{
    static auto const s_data = std::string("seeds: 79 14 55 13\n"
                                           "\n"
                                           "seed-to-soil map:\n"
                                           "50 98 2\n"
                                           "52 50 48\n"
                                           "\n"
                                           "soil-to-fertilizer map:\n"
                                           "0 15 37\n"
                                           "37 52 2\n"
                                           "39 0 15\n"
                                           "\n"
                                           "fertilizer-to-water map:\n"
                                           "49 53 8\n"
                                           "0 11 42\n"
                                           "42 0 7\n"
                                           "57 7 4\n"
                                           "\n"
                                           "water-to-light map:\n"
                                           "88 18 7\n"
                                           "18 25 70\n"
                                           "\n"
                                           "light-to-temperature map:\n"
                                           "45 77 23\n"
                                           "81 45 19\n"
                                           "68 64 13\n"
                                           "\n"
                                           "temperature-to-humidity map:\n"
                                           "0 69 1\n"
                                           "1 0 69\n"
                                           "\n"
                                           "humidity-to-location map:\n"
                                           "60 56 37\n"
                                           "56 93 4\n");

    TEST_CASE("Day05")
    {
        SECTION("Part 1")
        {
            auto const actual{ com::day05::part01(common::toList(s_data)) };
            REQUIRE(35 == actual);
        }

        SECTION("Part 2")
        {
            auto const actual{ com::day05::part02(common::toList(s_data)) };
            REQUIRE(46 == actual);
        }
    }

} // namespace com
