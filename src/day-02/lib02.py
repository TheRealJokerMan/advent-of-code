#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import functools
import re


class Game(object):
    '''A deserialized representation of the input data.'''

    def __init__(self, id: int):
        self.id = int(id)
        self.rounds: list[dict[str, int]] = []

    def add_round(self, round: dict[str, int]) -> None:
        '''
        Add a round to a game.

        :param round: A dictionary of key/value pairs.
        :returns: A valid integer.
        '''

        self.rounds.append(round)


class Engine(object):
    '''Generates the solution for day 02.'''

    def __init__(self, data: list[str]):
        self.games = []

        self.__parse_data(data)

    def part_01(self, limits: dict[str, int]) -> int:
        '''
        Solution for part 01.

        :returns: A valid integer.
        '''

        result = 0

        for game in self.games:
            if self.__is_game_possible(game, limits):
                result += game.id

        return result

    def part_02(self) -> int:
        '''
        Solution for part 02.

        :returns: A valid integer.
        '''

        return sum([self.__power(game) for game in self.games])

    def __is_game_possible(self, game: Game, limits: dict[str, int]) -> bool:
        for round in game.rounds:
            for color in round.keys():
                if round[color] > limits[color]:
                    return False

        return True

    def __parse_data(self, data: list[str]) -> None:
        for entry in data:
            if len(entry) == 0:
                break

            game_entry, round_entry = entry.split(':')

            if (m := re.match(r'Game\s+(\d+)', game_entry)):
                game = Game(m.group(1))

                for round_data in round_entry.split(';'):
                    m = re.findall(r'(\d+)\s*(\w+)', round_data)
                    round = {}
                    for match in m:
                        round[match[1]] = int(match[0])
                    game.add_round(round)

                self.games.append(game)

    def __power(self, game: Game):
        limits: dict[str, int] = {}

        for round in game.rounds:
            for color in round.keys():
                if color not in limits or round[color] > limits[color]:
                    limits[color] = round[color]

        return functools.reduce(lambda a, b: a * b, limits.values())
