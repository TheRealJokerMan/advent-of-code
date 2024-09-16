#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import lib08


def test_day_08_part_01() -> None:
    data = [
        'LLR\n',
        '\n',
        'AAA = (BBB, BBB)\n',
        'BBB = (AAA, ZZZ)\n',
        'ZZZ = (ZZZ, ZZZ)\n',
    ]

    engine = lib08.Engine(data)
    assert engine.part01() == 6


def test_day_08_part_02() -> None:
    data = [
        'LR\n',
        '\n',
        '11A = (11B, XXX)\n',
        '11B = (XXX, 11Z)\n',
        '11Z = (11B, XXX)\n',
        '22A = (22B, XXX)\n',
        '22B = (22C, 22C)\n',
        '22C = (22Z, 22Z)\n',
        '22Z = (22B, 22B)\n',
        'XXX = (XXX, XXX)\n',
    ]

    engine = lib08.Engine(data)
    assert engine.part02() == 6
