#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import lib09


def test_day_09_part_01() -> None:
    data = [
        '0 3 6 9 12 15\n',
        '1 3 6 10 15 21\n',
        '10 13 16 21 30 45\n'
    ]

    engine = lib09.Engine(data)
    assert engine.part01() == 114


def test_day_09_part_02() -> None:
    data = [
        '5  10  13  16  21  30  45\n',
        '5   3   3   5   9  15\n',
        '-2   0   2   4   6\n',
        '2   2   2   2\n',
        '0   0   0\n'
    ]

    engine = lib09.Engine(data)
    assert engine.part02() == 3
