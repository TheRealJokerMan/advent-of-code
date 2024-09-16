//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#pragma once

#include "lib/str.hxx"

#include <cmath>
#include <string>
#include <vector>

namespace com::day06
{
    /// Count the number of solutions.
    /// \param time The duration of the race.
    /// \param distance The distance travelled in the race.
    /// \return The number of ways the race record could have been beaten.
    static inline auto countSolutions(int64_t time, int64_t distance) -> int64_t
    {
        double const max{ (-time - std::sqrt(time * time - 4 * (-1) * (-distance))) / (2 * (-1)) };
        double const min{ (-time + std::sqrt(time * time - 4 * (-1) * (-distance))) / (2 * (-1)) };

        return static_cast<int64_t>(std::floor(std::nexttoward(max, min)) - std::ceil(std::nexttoward(min, max)) + 1);
    }
} // namespace com::day06
