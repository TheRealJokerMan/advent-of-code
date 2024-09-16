#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#


class Engine(object):
    '''Generates the solution for day 09.'''

    def __init__(self, data: list[str]):
        self.data = [[int(x) for x in line.split()] for line in data]

    def part01(self) -> int:
        '''
        Solution for part 01.

        :returns: A valid integer.
        '''

        return sum(self.extrapolate(sequence)[1] for sequence in self.data)

    def part02(self) -> int:
        '''
        Solution for part 02.

        :returns: A valid integer.
        '''

        return sum(self.extrapolate(sequence)[0] for sequence in self.data)

    def extrapolate(self, values: list[int]):
        differences = [b-a for a, b in zip(values, values[1:])]
        previous_value = values[0]
        next_value = values[-1]
        if any(differences):
            first_diff, last_diff = self.extrapolate(differences)
            previous_value -= first_diff
            next_value += last_diff
        return previous_value, next_value
