//
// Copyright(c) 2023 Jamie Kenyon. All Rights Reserved.
// SPDX-License-Identifier: MIT.
//

#include "lib.hxx"
#include "lib/str.hxx"

#include <ranges>
#include <regex>

namespace com::day04
{
    /// Represents a card in the data set.
    struct Card
    {
        /// The ID of the card.
        std::string id;

        /// The card numbers.
        std::vector<uint64_t> cardNumbers;

        /// The winning numbers.
        std::vector<uint64_t> winningNumbers;
    };

    static auto deserialize(std::vector<std::string> const& data)
    {
        std::vector<Card> cards;

        for (auto const& line : data)
        {
            std::regex  re("Card\\s*(\\d+):");
            std::smatch match;

            if (std::regex_search(line, match, re))
            {
                auto&      card{ cards.emplace_back(match.str(1)) };
                auto const contents{ line.substr(match.length(), line.length() - match.length() + 1) };
                auto const sequences{ common::toList(contents, '|') };

                card.cardNumbers = common::toVectorUInt(sequences[0]);
                card.winningNumbers = common::toVectorUInt(sequences[1]);
            }
        }

        return cards;
    }

    auto part01(std::vector<std::string> const& data) -> int64_t
    {
        int64_t result{ 0 };
        auto    cards{ deserialize(data) };

        for (auto const& card : cards)
        {
            int64_t points{ 0 };
            for (auto const number : card.cardNumbers)
            {
                if (std::ranges::find(card.winningNumbers, number) != card.winningNumbers.end())
                {
                    if (points == 0)
                        points = 1;
                    else
                        points *= 2;
                }
            }

            result += points;
        }

        return result;
    }

    auto part02(std::vector<std::string> const& data) -> int64_t
    {
        int64_t              result{ 0 };
        auto                 cards{ deserialize(data) };
        std::vector<int64_t> copies(cards.size(), 1);

        for (auto cardIndex = 0u; cardIndex < cards.size(); ++cardIndex)
        {
            auto const& card{ cards[cardIndex] };
            uint64_t    matches{};

            for (auto const number : card.cardNumbers)
            {
                if (std::ranges::find(card.winningNumbers, number) != card.winningNumbers.end())
                    ++matches;
            }

            for (auto matchIndex = 1; matchIndex <= matches; ++matchIndex)
                copies[cardIndex + matchIndex] += copies[cardIndex];

            result += copies[cardIndex];
        }

        return result;
    }
} // namespace com::day04
