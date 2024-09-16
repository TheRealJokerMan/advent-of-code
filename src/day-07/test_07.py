#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import lib07


def __get_engine() -> lib07.Engine:
    data = [
        '32T3K 765',
        'T55J5 684',
        'KK677 28',
        'KTJJT 220',
        'QQQJA 483',
    ]

    return lib07.Engine(data)


def test_day_07_part_01() -> None:

    engine = __get_engine()
    assert engine.part01() == 6440


def test_day_07_part_02() -> None:

    engine = __get_engine()
    assert engine.part02() == 5905
