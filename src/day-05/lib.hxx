//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#pragma once

#include "lib/str.hxx"

namespace com::day05
{
    struct Range
    {
        uint64_t source{};
        uint64_t destination{};
        uint64_t range{};
    };

    struct Map
    {
        std::string        name;
        std::vector<Range> ranges;

        void addRange(uint64_t sourceStart, uint64_t destinationStart, uint64_t range)
        {
            ranges.emplace_back(sourceStart, destinationStart, range);
        }
    };
} // namespace com::day05
