#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import math
import re


class Engine(object):
    '''Generates the solution for day 08.'''

    def __init__(self, data: list[str]):
        self.instructions = data[0].strip()

        self.nodes = {}
        for line in data[2:]:
            node, left, right = re.findall('\\b\\w{3}\\b', line)
            self.nodes[node] = (left, right)

    def part01(self) -> int:
        '''
        Solution for part 01.

        :returns: A valid integer.
        '''

        return self.__compute('AAA', 'ZZZ')

    def part02(self) -> int:
        '''
        Solution for part 02.

        :returns: A valid integer.
        '''

        start_nodes = [node for node in self.nodes.keys() if re.match('\\w{2}A', node)]
        end_nodes = [node for node in self.nodes.keys() if re.match('\\w{2}Z', node)]

        steps = [self.__compute(node, end_nodes) for node in start_nodes]

        return math.lcm(*steps)

    def __compute(self, current_node: str, target_nodes: list[str]) -> int:
        index = 0
        result = 0

        while current_node not in target_nodes:
            left, right = self.nodes[current_node]

            if self.instructions[index] == 'L':
                current_node = left
            elif self.instructions[index] == 'R':
                current_node = right

            result += 1

            if (index + 1) == len(self.instructions):
                index = 0
            else:
                index += 1

        return result
