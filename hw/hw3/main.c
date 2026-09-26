#include <stdio.h>

#include "MyBitManipulation.h"
#include "MyIntegers.h"
#include "Myfloat.h"

int main()
{

    /*
       Use this file for your own quick, manual checks with printf,
       for example while debugging construct_float_sf.

       This file is not graded. Your actual test cases belong in
       tests/, using Criterion, and are run with make test.
    */
    // printf("%d\n", ToggleBit(0, 3));
    // printf("%d\n", ToggleBit(5, 33));
    // printf("%d\n", ToggleBit(0, 31));
    // printf("%d\n", ToggleBit(3, 0));
    // printf("%d\n", ToggleBit(-3, 2));
    // printf("%d\n", GetMSB(16));
    // printf("%d\n", GetMSB(2147483648));
    // printf("%d\n", GetMSB(0));
    // printf("%d\n", GetMSB(-1));
    // printf("%d\n", ClearBitRange(-73, 1, 3));
    // printf("%d\n", ClearBitRange(10, -1, 5));
    // printf("%d\n", ClearBitRange(27, 6, 33));
    // printf("%d\n", ClearBitRange(223, 6, 3));
    // printf("%d\n", ClearBitRange(31, 0, 4));
    // printf("%d\n", RotateLeft(-5, 1));
    // printf("%d\n", RotateLeft(1, 31));
    // printf("%d\n", RotateLeft(10, 35));
    // printf("%d\n", RotateLeft(19, 0));
    // printf("%d\n", SwapOddEvenBits(255));
    // printf("%d\n", SwapOddEvenBits(2));
    // printf("%d\n", SwapOddEvenBits(21));
    // printf("%d\n", SwapOddEvenBits(0));
    // printf("%f\n", construct_float_sf(0x01, 0x00, 0x000000));
    // repr_convert('2', 'S', 0xffffffff);
    // repr_convert('S', '2', 0x80000001);
    // repr_convert('2', 'S', 0x80000000);
    // repr_convert('S', '2', 0x80000000);
    // repr_convert('2', 'S', 0x7fffffff);
    // repr_convert('S', '2', 0x7fffffff);
    // repr_convert('2', 'S', 0xfffffffb);
    // repr_convert('S', '2', 0x80000005);
    // repr_convert('S', 'S', 0x80000000);
    // repr_convert('F', '2', 0x00394812);
    // repr_convert('2', 'F', 0x00394812);
    repr_convert('S', '2', 0x80000001);
    fflush(stdout);
    return 0;
}
