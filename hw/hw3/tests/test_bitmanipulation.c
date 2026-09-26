#include <criterion/criterion.h>

#include "MyBitManipulation.h"

Test(ToggleBit, example)
{
    cr_assert_eq(
        ToggleBit(0, 3),
        8);
    cr_assert_eq(
        ToggleBit(5, 33),
        5);
    cr_assert_eq(
        ToggleBit(0, 31),
        2147483648);
    cr_assert_eq(
        ToggleBit(3, 0),
        2);
}

Test(GetMSB, example)
{
    cr_assert_eq(
        GetMSB(16),
        4);
    cr_assert_eq(
        GetMSB(2147483648),
        31);
    cr_assert_eq(
        GetMSB(0),
        -1);
    cr_assert_eq(
        GetMSB(-1),
        31);
}

Test(ClearBitRange, example)
{
    cr_assert_eq(
        ClearBitRange(10, -1, 5),
        10);
    cr_assert_eq(
        ClearBitRange(27, 6, 33),
        27);
    cr_assert_eq(
        ClearBitRange(223, 6, 3),
        223);
    cr_assert_eq(
        ClearBitRange(31, 0, 4),
        0);
}

Test(RotateLeft, example)
{
    cr_assert_eq(
        RotateLeft(1, 31),
        2147483648);
    cr_assert_eq(
        RotateLeft(10, 35),
        80);
    cr_assert_eq(
        RotateLeft(19, 0),
        19);
}

Test(SwapOddEvenBits, example)
{
    cr_assert_eq(
        SwapOddEvenBits(255),
        255);
    cr_assert_eq(
        SwapOddEvenBits(2),
        1);
    cr_assert_eq(
        SwapOddEvenBits(21),
        42);
    cr_assert_eq(
        SwapOddEvenBits(0),
        0);
}