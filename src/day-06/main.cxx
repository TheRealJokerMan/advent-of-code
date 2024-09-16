//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib/fios.hxx"
#include "lib01.hxx"
#include "lib02.hxx"

#include <iostream>

auto main(int32_t /*argc*/, char* /*argv*/[]) -> int32_t
{
    auto const data{ com::common::loadAsList(DATA_DIR, "data.txt") };

    std::cout << "Part 01 result " << com::day06::part01(data) << std::endl;
    std::cout << "Part 02 result " << com::day06::part02(data) << std::endl;

    return 0;
}
