#
# Copyright (c) 2023 Jamie Kenyon. All Rights Reserved.
# SPDX-License-Identifier: MIT.
#

import lib10
import pathlib


def main() -> None:
    path = (pathlib.Path(__file__).parent / 'data.txt').resolve()

    if path.exists():
        with open(path, 'r') as f:
            engine = lib10.Engine(f.readlines())

            print(f'Part 01 result: {engine.part01()}')
            print(f'Part 02 result: {engine.part02()}')
    else:
        raise FileNotFoundError(f'Failed to open "{path}"')


if __name__ == '__main__':
    main()
