#include <criterion/criterion.h>

#include "Myfloat.h"


Test(construct_float_sf, positive_5_5)
{
    /* sign_bit = 0x00 (positive), exponent = 0x81 (excess-127 -> 2),
       fraction = 0x300000. Expected IEEE-754 bit pattern is 0x40B00000,
       which is 5.5f. */
    cr_assert_float_eq(
        construct_float_sf(0x00, 0x81, 0x300000),
        5.5,
        1e-6
    );
}
