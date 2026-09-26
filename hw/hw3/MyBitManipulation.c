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
    if (pos >= 31)
    {
        return num; // special circumstance
    }
    int mask = 1 << pos;        // create mask for bit at index pos
    int toggled = (num ^ mask); // use mask on num

    return toggled;
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
    if (num < 0)
    {
        return 31; // special circumstance
    }
    else if (num == 0)
    {
        return -1; // special circumstance
    }
    int count = 0;
    for (int i = num; i > 0; i /= 2)
    {
        count++; // index of MSB of num
    }
    return count - 1;
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
    if (start < 0 || end > 31 || start > end)
    {
        return num; // special circumstances
    }
    int count = 0;
    for (unsigned int i = num; i > 0; i /= 2)
    {
        count++; // get index of MSB of num
    }
    if (count > (end - start + 1) && (start == 0))
    {
        for (int j = start; j < end + 1; j++)
        {
            int mask = ~(1 << j); // create mask for jth bit
            num = num & mask;     // use mask on num
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
    if (d == 0)
    {
        return num;
    }
    if (d > 32)
    {
        d %= 32;
    }
    int left = (num << d);         // original shift
    int right = (num >> (32 - d)); // discarded bits
    int rotated = left | right;    // discarded bits added to the back
    return rotated;
}

/*
 * Swap odd and even bit positions.
 */
int SwapOddEvenBits(int num)
{
    for (int i = 0; i < 32; i += 2)
    {
        int i_bit = (num >> i) & 1;                                                          // get ith bit
        int i1_bit = (num >> (i + 1)) & 1;                                                   // get i + 1th bit
        num = num - (i_bit << i) + (i1_bit << i) - (i1_bit << (i + 1)) + (i_bit << (i + 1)); // replace ith bit with i + 1th bit and i + 1th bit with ith bit
    }
    return num;
}
