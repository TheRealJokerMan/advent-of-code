//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib01.hxx"
#include "lib02.hxx"

#include <catch2/catch_all.hpp>

namespace com
{
    static auto const s_data = std::string("Time:      7  15   30\n"
                                           "Distance:  9  40  200");

    TEST_CASE("Day06")
    {
        SECTION("Part 1")
        {
            auto const actual{ com::day06::part01(common::toList(s_data)) };
            REQUIRE(288 == actual);
        }

        SECTION("Part 2")
        {
            auto const actual{ com::day06::part02(common::toList(s_data)) };
            REQUIRE(71503 == actual);
        }
    }

} // namespace com
