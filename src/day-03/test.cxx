//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib.hxx"
#include "lib/str.hxx"

#include <catch2/catch_all.hpp>

namespace com
{
    static auto const s_data = std::string("467..114..\n"
                                           "...*......\n"
                                           "..35..633.\n"
                                           "......#...\n"
                                           "617*......\n"
                                           ".....+.58.\n"
                                           "..592.....\n"
                                           "......755.\n"
                                           "...$.*....\n"
                                           ".664.598..");

    TEST_CASE("Day03")
    {
        SECTION("Part 1")
        {
            auto const actual{ com::day03::part01(common::toList(s_data)) };
            REQUIRE(4361 == actual);
        }

        SECTION("Part 2")
        {
            auto const actual{ com::day03::part02(common::toList(s_data)) };
            REQUIRE(467835 == actual);
        }
    }

} // namespace com
