#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import copy
import itertools


class Engine(object):
    '''Generates the solution for day 10.'''

    def __init__(self, data: list[str]):
        self.data = list(map(str.strip, data))

    def part01(self) -> int:
        '''
        Solution for part 01.

        :returns: A valid integer.
        '''

        universe = Engine.expand_universe(self.data)

        galaxies = set()
        for y, row in enumerate(universe):
            for x, item in enumerate(row):
                if item == "#":
                    galaxies.add((x, y))

        return sum(Engine.manhattan_distance(a, b) for a, b in itertools.combinations(galaxies,
                                                                                      r=2))

    def part02(self) -> int:
        '''
        Solution for part 02.

        :returns: A valid integer.
        '''

        galaxies = []
        for y, row in enumerate(self.data):
            for x, item in enumerate(row):
                if item == "#":
                    galaxies.append([x, y])

        galaxies = Engine.expand_galaxies(self.data, galaxies)

        return sum(Engine.manhattan_distance(a, b) for a, b in itertools.combinations(galaxies,
                                                                                      r=2))

    @staticmethod
    def expand_galaxies(universe, galaxies, fact=1_000_000) -> list[str]:
        galaxies_orig = copy.deepcopy(galaxies)

        for y, line in enumerate(universe):
            if "#" not in line:
                for i, g in enumerate(galaxies):
                    if galaxies_orig[i][1] > y:
                        g[1] += (fact-1)

        universe = Engine.transpose(universe)

        for x, line in enumerate(universe):
            if "#" not in line:
                for i, g in enumerate(galaxies):
                    if galaxies_orig[i][0] > x:
                        g[0] += (fact-1)

        return galaxies

    @staticmethod
    def expand_universe(universe: list[str]):
        expanded_universe = []
        for line in universe:
            if all(x == "." for x in line):
                expanded_universe.append(line)
            expanded_universe.append(line)

        universe = Engine.transpose(expanded_universe)

        expanded_universe = []
        for line in universe:
            if all(x == "." for x in line):
                expanded_universe.append(line)
            expanded_universe.append(line)

        universe = Engine.transpose(expanded_universe)
        return universe

    @staticmethod
    def manhattan_distance(a: tuple, b: tuple) -> int:
        return abs(a[0] - b[0]) + abs(a[1] - b[1])

    @staticmethod
    def transpose(it: list[str]):
        return zip(*it, strict=True)
