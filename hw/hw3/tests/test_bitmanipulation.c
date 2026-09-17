#include <criterion/criterion.h>

#include "MyBitManipulation.h"


Test(ToggleBit, example)
{
    cr_assert_eq(
        ToggleBit(0,3),
        8
    );
}


Test(GetMSB, example)
{
    cr_assert_eq(
        GetMSB(16),
        4
    );
}
