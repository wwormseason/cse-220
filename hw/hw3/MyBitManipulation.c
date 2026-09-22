#include <stdio.h>
#include "MyBitManipulation.h"

/*
 * Toggle the bit at position pos.
 *
 * Example:
 * ToggleBit(0,3) -> 8
 * Return original number if pos is invalid.
 */
int ToggleBit(int num, int pos)
{
    int bit_num = 1;
    for (int i = 0; i < pos; i++)
    {
        bit_num *= 2;
    }
    return (num ^ bit_num);
}

/*
 * Return the position of the most significant bit.
 *
 * Example:
 * GetMSB(8) -> 3
 *
 * Return -1 for zero.
 */
int GetMSB(int num)
{
    int count = 0;
    for (int i = num; i > 0; i /= 2)
    {
        count++;
    }
    if (count > 0)
    {
        return count - 1;
    }
    else
    {
        return -1;
    }
}

/*
 * Clear bits from start to end (inclusive).
 *
 * Example:
 * ClearBitRange(0xffffffff, 0, 7)
 * returns 0xffffff00
 *
 * Hint: if start is 0 and end is 31 you are clearing every bit in a
 * 32 bit value. A mask built as (1u << (end - start + 1)) - 1 needs a
 * shift by 32 in that case, and shifting a 32 bit type by 32 is
 * undefined behavior in C, it is not guaranteed to give you 0. Handle
 * that full range case on its own instead of relying on the shift.
 */
int ClearBitRange(int num, int start, int end)
{
    int count = 0;
    for (unsigned int i = num; i > 0; i /= 2)
    {
        count++;
    }
    if (count > (end - start + 1))
    {
        for (int j = start; j < end + 1; j++)
        {
            int mask = ~(1 << j);
            num = num & mask;
        }
        return num;
    }
    else
    {
        return 0;
    }
}

/*
 * Rotate bits left by d positions.
 *
 * Hint: after reducing d with d %= 32, d can come out to 0, which
 * also happens whenever the original d was itself a multiple of 32
 * (32, 64, and so on). A common rotate formula is
 * (x << d) | (x >> (32 - d)), but when d is 0 that means shifting by
 * 32, which is undefined behavior for a 32 bit type in C. Handle
 * d == 0 as its own case, where the answer is just num, instead of
 * relying on that shift to behave a particular way.
 */
int RotateLeft(int num, int d)
{
    if (d != 0)
    {
        return (num << d) | (num >> (32 - d));
    }

    return 0;
}

/*
 * Swap odd and even bit positions.
 */
int SwapOddEvenBits(int num)
{
    // TODO: implement

    return 0;
}
