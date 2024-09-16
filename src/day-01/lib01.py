#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import re


class Engine(object):
    '''Generates the solution for day 01.'''

    def __init__(self, data: list[str] = None):
        self.data = data

    def part01(self, data: list[str] = None) -> int:
        '''
        Solution for part 01.

        :param data: The input data. If not supplied, we be sourced from the data passed to the
                     constructor.
        :returns: A valid integer.
        '''

        data = data or self.data
        result = 0

        for entry in data:
            first = self.__find_first(entry)
            if not first:
                continue

            last = self.__find_last(entry)
            if not last:
                continue

            result += (first * 10) + last

        return result

    def part02(self, data: list[str] = None) -> int:
        '''
        Solution for part 02.

        :param data: The input data. If not supplied, we be sourced from the data passed to the
                     constructor.
        :returns: A valid integer.
        '''

        def __convert(n):
            mapping = {
                'one': '1',
                'two': '2',
                'three': '3',
                'four': '4',
                'five': '5',
                'six': '6',
                'seven': '7',
                'eight': '8',
                'nine': '9'
            }

            return mapping[n] if n in mapping else n

        data = data or self.data
        result = 0

        for entry in data:
            digits = list(map(__convert, re.findall(
                r'(?=(one|two|three|four|five|six|seven|eight|nine|\d))', entry)))
            result += int(digits[0] + digits[-1])

        return result

    def __find(self, data: str, pattern: re.Pattern[str]) -> int:
        if (m := pattern.search(data)):
            return int(m.group(0))
        return None

    def __find_first(self, data: str) -> int:
        return self.__find(data, re.compile(r'(\d)'))

    def __find_last(self, data: str) -> int:
        return self.__find(data, re.compile(r'(\d)(?!.*\d)'))
