#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import lib01


def test_day_01_part_01() -> None:
    data = [
        '1abc2',
        'pqr3stu8vwx',
        'a1b2c3d4e5f',
        'treb7uchet',
    ]

    engine = lib01.Engine(data)
    assert engine.part01() == 142


def test_day_01_part_02() -> None:
    data = [
        'two1nine',
        'eightwothree',
        'abcone2threexyz',
        'xtwone3four',
        '4nineeightseven2',
        'zoneight234',
        '7pqrstsixteen',
    ]

    engine = lib01.Engine(data)
    assert engine.part02() == 281
