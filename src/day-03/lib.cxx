//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib.hxx"

#include <algorithm>
#include <map>
#include <ranges>

namespace com::day03
{
    using Index = std::pair<int64_t, int64_t>;

    static auto isSymbol(char const ch)
    {
        return not std::isdigit(ch) and ch != '.';
    }

    static auto getNextNumber(std::string_view const line, int64_t const columnIndex)
    {
        auto position{ columnIndex };

        while (position < std::ssize(line) and not std::isdigit(line[position]))
            ++position;

        auto length{ std::make_pair(position, position) };
        if (position < std::ssize(line))
        {
            while (position < std::ssize(line) and std::isdigit(line[position]))
                ++position;

            length.second = position - 1;
        }

        return length;
    }

    static auto scan(std::string_view const line, int64_t const left, int64_t const right)
    {
        return std::ranges::any_of(line.substr(std::max(0ll, left), right - left + 1), isSymbol);
    }

    auto part01(std::vector<std::string> const& data) -> int64_t
    {
        int64_t result{ 0 };

        for (auto rowIndex = 0u; rowIndex < data.size(); ++rowIndex)
        {
            auto const& entry{ data[rowIndex] };
            size_t      pos{ 0 };

            while (pos < entry.length())
            {
                const auto index{ getNextNumber(entry, pos) };
                pos = index.second + 1;

                if (index.second < std::ssize(entry))
                {
                    auto const left{ index.first - 1 };
                    auto const right{ index.second + 1 };
                    auto const line{ data[rowIndex] };
                    auto       isValid{ (left >= 0 and isSymbol(line[left])) or (right < std::ssize(line) and isSymbol(line[right])) };

                    if (not isValid and rowIndex > 0)
                        isValid = scan(data[rowIndex - 1], left, right);

                    if (not isValid and rowIndex + 1 < data.size())
                        isValid = scan(data[rowIndex + 1], left, right);

                    if (isValid)
                        result += std::atoi(entry.data() + index.first);
                }
            }
        }

        return result;
    }

    auto part02(std::vector<std::string> const& data) -> int64_t
    {
        std::map<std::pair<int64_t, int64_t>, std::vector<int64_t>> values;

        for (auto rowIndex = 0u; rowIndex < data.size(); ++rowIndex)
        {
            auto const& entry{ data[rowIndex] };
            size_t      position{ 0 };

            while (position < entry.length())
            {
                auto const index{ getNextNumber(entry, position) };
                position = index.second + 1;

                if (index.second < std::ssize(entry))
                {
                    auto const left = std::max(0, static_cast<int32_t>(index.first - 1));
                    auto const right = static_cast<int32_t>(std::min(index.second + 1, static_cast<int64_t>(entry.size()) - 1));
                    auto const from = std::max(0, static_cast<int32_t>(rowIndex - 1));
                    auto const to = static_cast<int32_t>(std::min((int64_t) rowIndex + 1, static_cast<int64_t>(data.size()) - 1));

                    for (auto line = from; line <= to; ++line)
                    {
                        for (auto i = left; i <= right; ++i)
                        {
                            if (not data[line].empty())
                            {
                                if (data[line][i] == '*')
                                    values[{ line, i }].emplace_back(atoi(data[rowIndex].data() + index.first));
                            }
                        }
                    }
                }
            }
        }

        int64_t result{ 0 };
        for (auto const& [_, nums] : values)
        {
            if (nums.size() == 2)
                result += nums[0] * nums[1];
        }

        return result;
    }
} // namespace com::day03
