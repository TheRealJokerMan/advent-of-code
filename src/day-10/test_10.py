#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import lib10


def test_day_10_part_01() -> None:
    data = [
        '..F7.\n',
        '.FJ|.\n',
        'SJ.L7\n',
        '|F--J\n',
        'LJ...\n',
    ]

    engine = lib10.Engine(data)
    assert engine.part01() == 8


def test_day_10_part_02() -> None:
    data = [
        'FF7FSF7F7F7F7F7F---7\n',
        'L|LJ||||||||||||F--J\n',
        'FL-7LJLJ||||||LJL-77\n',
        'F--JF--7||LJLJIF7FJ-\n',
        'L---JF-JLJIIIIFJLJJ7\n',
        '|F|F-JF---7IIIL7L|7|\n',
        '|FFJF7L7F-JF7IIL---7\n',
        '7-L-JL7||F7|L7F-7F7|\n',
        'L.L7LFJ|||||FJL7||LJ\n',
        'L7JLJL-JLJLJL--JLJ.L\n',
    ]

    engine = lib10.Engine(data)
    assert engine.part02() == 10
