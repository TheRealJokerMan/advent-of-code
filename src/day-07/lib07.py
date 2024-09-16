#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import functools
import re


@functools.total_ordering
class Hand(object):
    '''A deserialized representation of the input data.'''

    values = 'j123456789TJQKA'

    def __init__(self, cards: str, bid: int):
        self.bid = int(bid)
        self.cards = cards
        self.rank = list(map(Hand.values.index, cards))
        self.type = self.__compute_type(c for c in cards if c != 'j') + min(4, cards.count('j'))

    def __lt__(self, other):
        return (self.type, self.rank, self.bid) < (other.type, other.rank, other.bid)

    def __compute_type(self, cards):
        cards = ''.join(sorted(cards, key=Hand.values.index))

        expression_types = [
            (r'(.)\1{4}', 5),
            (r'(.)\1{3}', 4),
            (r'(.)\1\1(.)\2|(.)\3(.)\4\4', 3.5),
            (r'(.)\1\1', 3),
            (r'(.)\1.?(.)\2', 2.5),
            (r'(.)\1', 2),
        ]

        for exp, hand_type in expression_types:
            if re.search(exp, cards):
                return hand_type
        return 1


class Engine(object):
    '''Generates the solution for day 07.'''

    def __init__(self, data: list[str]):
        self.data = data

    def part01(self) -> int:
        '''
        Solution for part 01.

        :returns: A valid integer.
        '''

        hands = sorted(self.__get_hands())
        ranked = [(i + 1, hand.bid) for i, hand in enumerate(hands)]
        return sum(rank * bid for rank, bid in ranked)

    def part02(self) -> int:
        '''
        Solution for part 02.

        :returns: A valid integer.
        '''

        self.data = [data.replace('J', 'j') for data in self.data]
        hands = sorted(self.__get_hands())
        ranked = [(i + 1, hand.bid) for i, hand in enumerate(hands)]
        return sum(rank * bid for rank, bid in ranked)

    def __get_hands(self) -> list[Hand]:
        return [(Hand(parts[0], parts[1])) for line in self.data if (parts := line.split())[1]]
