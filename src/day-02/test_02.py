#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import lib02


def __data() -> list[str]:
    return [
        'Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green',
        'Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue',
        'Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red',
        'Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red',
        'Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green'
    ]


def test_part_01() -> None:
    engine = lib02.Engine(__data())
    limits = {'red': 12, 'green': 13, 'blue': 14}

    assert 8 == engine.part_01(limits)


def test_part_02():
    engine = lib02.Engine(__data())

    assert 2286 == engine.part_02()
