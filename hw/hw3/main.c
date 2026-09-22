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
    // printf("%d", ToggleBit(0, 3));
    // printf("%d", GetMSB(16));
    // printf("%x", ClearBitRange(0xffffffff, 0, 7));
    printf("%x", ClearBitRange(0xffffffff, 0, 7));
    return 0;
}
