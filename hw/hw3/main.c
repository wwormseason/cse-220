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
    printf("%d\n", ToggleBit(9, 0));
    printf("%d\n", ToggleBit(9, 3));
    printf("%d\n", ToggleBit(-3, 2));
    printf("%d\n", ToggleBit(0, 31));
    printf("%d\n", ToggleBit(10, 32));
    // printf("%d", GetMSB(8));
    // printf("%d", ClearBitRange(-73, 1, 3));
    // printf("%x", RotateLeft(0, 32));
    // printf("%d", SwapOddEvenBits(-23));
    // repr_convert('2', 'S', 0xfffffffb);
    return 0;
}
