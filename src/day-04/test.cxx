//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib.hxx"
#include "lib/str.hxx"

#include <catch2/catch_all.hpp>

namespace com
{
    static auto const s_data = std::string("Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n"
                                           "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n"
                                           "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1\n"
                                           "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n"
                                           "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n"
                                           "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11");

    TEST_CASE("Day04")
    {
        SECTION("Part 1")
        {
            auto const actual{ com::day04::part01(common::toList(s_data)) };
            REQUIRE(13 == actual);
        }

        SECTION("Part 2")
        {
            auto const actual{ com::day04::part02(common::toList(s_data)) };
            REQUIRE(30 == actual);
        }
    }

} // namespace com
