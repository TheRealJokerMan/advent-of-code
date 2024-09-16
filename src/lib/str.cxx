//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib/str.hxx"

#include <algorithm>
#include <ranges>
#include <regex>

namespace com::common
{
    auto toList(std::string const& input, char const token) -> std::vector<std::string>
    {
        auto const functor{ [](auto&& range) { return std::string(range.begin(), range.end()); } };

        std::vector<std::string> result;
        std::ranges::transform(input | std::views::split(token), std::back_inserter(result), functor);

        return result;
    }

    template <typename T>
    static auto toVector(std::string const& input) -> std::vector<T>
    {
        std::smatch    match;
        std::regex     re("(\\d+)");
        std::vector<T> result;
        auto           start(input.cbegin());

        while (std::regex_search(start, input.cend(), match, re))
        {
            auto const token{ match.str(1) };

            result.emplace_back(std::stoul(token));
            start = match.suffix().first;
        }

        return result;
    }

    auto toVectorInt(std::string const& input) -> std::vector<int64_t>
    {
        return toVector<int64_t>(input);
    }

    auto toVectorUInt(std::string const& input) -> std::vector<uint64_t>
    {
        return toVector<uint64_t>(input);
    }
} // namespace com::common
