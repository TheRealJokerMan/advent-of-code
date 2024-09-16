#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import lib11


def __get_engine():
    data = [
        '....1........\n',
        '.........2...\n',
        '3............\n',
        '.............\n',
        '.............\n',
        '........4....\n',
        '.5...........\n',
        '.##.........6\n',
        '..##.........\n',
        '...##........\n',
        '....##...7...\n',
        '8....9.......\n',
    ]
    return lib11.Engine(data)


def test_day_11_part_01() -> None:
    engine = __get_engine()
    assert engine.part01() == 84


def test_day_11_part_02() -> None:
    engine = __get_engine()
    assert engine.part02() == 84
