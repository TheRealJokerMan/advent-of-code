//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#pragma once

#include "lib/str.hxx"

#include <filesystem>
#include <string_view>

namespace com::common
{
    /// Load the contents of a file into a list of strings delimited by a token.
    /// \param directory The directory containing the file.
    /// \param fileName The name of the file.
    /// \param token The token to split the string by.
    /// \return The contents of the file as a delimited list if successful; an empty list otherwise.
    auto loadAsList(std::filesystem::path const& directory, std::string_view const fileName, char const token = '\n') -> std::vector<std::string>;

} // namespace com::common
