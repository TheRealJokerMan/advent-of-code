//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace com::common
{
    /// Split a string into a list of strings delimited by a token.
    /// \param input The string to split.
    /// \param token The token to split the string by.
    /// \return A delimited list if successful; an empty list otherwise.
    auto toList(std::string const& input, char const token = '\n') -> std::vector<std::string>;

    /// Split a string into a list of numbers.
    /// \param input The string to split.
    /// \return A list of numbers.
    auto toVectorInt(std::string const& input) -> std::vector<int64_t>;

    /// Split a string into a list of numbers.
    /// \param input The string to split.
    /// \return A list of numbers.
    auto toVectorUInt(std::string const& input) -> std::vector<uint64_t>;

} // namespace com::common
