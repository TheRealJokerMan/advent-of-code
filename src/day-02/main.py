#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import lib02
import pathlib


def main() -> None:
    path = (pathlib.Path(__file__).parent / 'data.txt').resolve()

    if path.exists():
        with open(path, 'r') as f:
            engine = lib02.Engine(f.readlines())

            limits = {'red': 12, 'green': 13, 'blue': 14}
            print(f'Part 01 result == {engine.part_01(limits)}')

            print(f'Part 02 result == {engine.part_02()}')
    else:
        raise FileNotFoundError(f'Failed to open "{path}"')


if __name__ == '__main__':
    main()
