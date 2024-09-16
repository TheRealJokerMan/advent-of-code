#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#


class Engine(object):
    '''Generates the solution for day 10.'''

    DirectionCoordinates = [(0, -1), (1, 0), (0, 1), (-1, 0)]
    DirectionShapes = ['7|F', 'J-7', 'L|J', 'F-L']

    def __init__(self, data: list[str]):
        self.data = list(map(str.strip, data))

    def part01(self) -> int:
        '''
        Solution for part 01.

        :returns: A valid integer.
        '''

        loop, _ = self.__find_loop()
        return len(loop) // 2

    def part02(self) -> int:
        '''
        Solution for part 02.

        :returns: A valid integer.
        '''

        def adjacent(x, y):
            return {
                (x+dx, y+dy)
                for dy in [-1, 0, 1]
                for dx in [-1, 0, 1]
                if dx or dy
            }

        loop, enclosed = self.__find_loop()
        current = enclosed
        while current:
            current = {adj for x, y in current for adj in adjacent(x, y)}
            current -= enclosed | loop
            enclosed |= current
        return len(enclosed)

    def __find_loop(self):
        maze, (x, y) = self.__parse(self.data)
        direction = self.__find_starting_direction(maze, x, y)
        loop = set()
        left_side = set()
        right_side = set()

        while True:
            loop.add((x, y))
            coordinates = Engine.DirectionCoordinates[direction]
            side_dx = (1, 0, -1, 0)[direction]
            side_dy = (0, 1, 0, -1)[direction]
            for dx, dy in [(0, 0), coordinates]:
                x, y = x + dx, y + dy
                left_side.add((x - side_dx, y - side_dy))
                right_side.add((x + side_dx, y + side_dy))

            pipe = maze[x, y]

            if pipe == 'S':
                enclosed = min(left_side, right_side, key=max)
                return loop, enclosed - loop

            turn = Engine.DirectionShapes[direction].index(pipe) - 1
            direction = (direction + turn + 4) % 4

    def __find_starting_direction(self, maze, x, y):
        for direction, acceptable in enumerate(Engine.DirectionShapes):
            dx, dy = Engine.DirectionCoordinates[direction]
            pos = (x + dx, y + dy)
            if pos in maze and maze[pos] in acceptable:
                return direction

    def __parse(self, lines):
        maze = {
            (x, y): c
            for y, line in enumerate(lines)
            for x, c in enumerate(line)
        }
        start = next(xy for xy, c in maze.items() if c == 'S')
        return maze, start
