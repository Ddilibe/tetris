#!/usr/bin/env python3
"""
Binary Calculations for 23×18 = 414-bit structures.

This module generates very large binary patterns represented as integers.
Each structure is a 23-row × 18-column grid (total = 414 bits),
used for Tetris-related bitmasking and collision computations.

Main features:
- Generate a pattern with 1s down a specific column.
- Generate a pattern with 18 ones across a specific row.
- Display the 414-bit structure in readable 23×18 grid form.
- Demonstrate matrix rotation (used for Tetris piece rotation logic).
"""

from pprint import pprint

ROWS = 23  # number of rows in the bit matrix
COLS = 18  # number of columns
TOTAL_BITS = ROWS * COLS  # total = 414 bits


def get_col_pattern_number(k: int) -> int:
    """
    Return a 414-bit integer with 1s placed vertically down column `k`.

    Args:
        k (int): The column index (1-based).

    Returns:
        int: A 414-bit integer with bits set in column `k`.

    Raises:
        ValueError: If column index is out of range.

    Explanation:
        We treat the entire 23×18 bit matrix as one continuous 414-bit number.
        Bit layout is row-major from top-left → bottom-right.
        For a given column `k`, we set bit at every row on that column.
    """
    if not (1 <= k <= COLS):
        raise ValueError(f"Column index k must be between 1 and {COLS}.")

    col_index = k - 1  # convert to 0-based index
    result_number = 0

    for r in range(ROWS):
        # Compute absolute bit index from MSB
        bit_position = (TOTAL_BITS - 1) - (r * COLS + col_index)

        # Set that bit in result_number
        result_number |= 1 << bit_position

    return result_number


def get_row_pattern_number(r_target: int) -> int:
    """
    Create a 414-bit integer with all 18 bits set to 1 across row `r_target`.

    Args:
        r_target (int): Row index (1-based).

    Returns:
        int: A 414-bit integer with 18 ones in the target row.

    Raises:
        ValueError: If row index is invalid.

    Explanation:
        - A row is a contiguous block of 18 bits.
        - Create a block `111111111111111111` (18 ones).
        - Shift it into its correct position inside the 414-bit number.
    """
    if not (1 <= r_target <= ROWS):
        raise ValueError(f"Row index r_target must be between 1 and {ROWS}.")

    block_of_ones = (1 << COLS) - 1  # 2^18 - 1 = 18 ones
    shift_amount = TOTAL_BITS - (r_target * COLS)

    return block_of_ones << shift_amount


def display_binary(value: int) -> None:
    """
    Print a 414-bit integer in human-readable 23×18 binary matrix form.

    Args:
        value (int): A large integer representing the entire bit matrix.

    Explanation:
        - Convert to a binary string.
        - Zero-pad to 414 bits.
        - Print row by row (18 bits each).
    """
    bin_str = bin(value)[2:].zfill(TOTAL_BITS)

    print("\n=== Binary (23 rows × 18 bits) ===")
    for r in range(ROWS):
        start = r * COLS
        end = start + COLS
        print(bin_str[start:end])


def rotate_matrix():
    """
    Demonstrates matrix rotation logic used in Tetris piece rotation.

    Example matrix:
        [ [1,1,0],
          [0,1,0],
          [0,1,0] ]

    This function prints the original matrix and a (mistaken) rotated version.
    Note:
        The rotation logic in this demo is intentionally incorrect.
        It prints results to help debug Tetris rotation issues.
    """
    matrix = [[1, 1, 0], [0, 1, 0], [0, 1, 0]]

    # Ensure square matrix
    assert len(matrix) == len(matrix[0]), "Must be a square matrix"

    pprint(matrix, indent=2, depth=6, width=20)

    matrix2 = [[0] * 3 for _ in range(3)]
    n = len(matrix)

    print(len(matrix2))

    # Incorrect rotation (debug demonstration)
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            matrix2[i][j] = matrix[n - 1 - j][j]

    pprint(matrix2, indent=2, depth=6, width=20)


if __name__ == "__main__":

    # Generate column patterns (demo)
    num = 1
    for i in range(1, 18):
        value = get_col_pattern_number(num)
        print(f"COL_{i} {value}")

    # Uncomment to see binary layout
    # display_binary(value)
