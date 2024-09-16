//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib/fios.hxx"

#include <algorithm>
#include <fstream>
#include <ranges>
#include <streambuf>

namespace com::common
{
    static auto getSize(std::ifstream& t)
    {
        std::streampos size;
        t.seekg(0, std::ios::end);
        size = t.tellg();
        t.seekg(0, std::ios::beg);

        return size;
    }

    auto loadAsList(std::filesystem::path const& directory, std::string_view const fileName, char const token) -> std::vector<std::string>
    {
        auto const    path((std::filesystem::weakly_canonical(directory) / fileName).make_preferred());
        std::ifstream stream(path);
        std::string   input;

        // Perform up-front allocation.
        input.reserve(getSize(stream));
        input.assign(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());

        // Convert into list.
        return toList(input, token);
    }
} // namespace com::common
