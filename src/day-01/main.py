#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import lib01
import pathlib


def main() -> None:
    path = (pathlib.Path(__file__).parent / 'data.txt').resolve()

    if path.exists():
        with open(path, 'r') as f:
            data = f.readlines()
            engine = lib01.Engine()

            print(f'Part 01 result: {engine.part01(data)}')
            print(f'Part 02 result: {engine.part02(data)}')
    else:
        raise FileNotFoundError(f'Failed to open "{path}"')


if __name__ == '__main__':
    main()
