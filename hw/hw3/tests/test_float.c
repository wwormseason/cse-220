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
        1e-6);
}

Test(construct_float_sf, negative_5_5)
{
    cr_assert_float_eq(
        construct_float_sf(0x01, 0x81, 0x300000),
        -5.5,
        1e-6);
}

Test(construct_float_sf, positive_255439)
{
    cr_assert_float_eq(
        construct_float_sf(0x00, 0x90, 0x7973C0),
        255439,
        1e-6);
}

Test(construct_float_sf, negative_255439)
{
    cr_assert_float_eq(
        construct_float_sf(0x01, 0x90, 0x7973C0),
        -255439,
        1e-6);
}

Test(construct_float_sf, positive_0_002588)
{
    cr_assert_float_eq(
        construct_float_sf(0x00, 0x76, 0x299B6F),
        0.002588,
        1e-6);
}

Test(construct_float_sf, negative_0_002588)
{
    cr_assert_float_eq(
        construct_float_sf(0x01, 0x76, 0x299B6F),
        -0.002588,
        1e-6);
}

Test(construct_float_sf, positive_0)
{
    cr_assert_float_eq(
        construct_float_sf(0x00, 0x00, 0x000000),
        0,
        1e-6);
}

Test(construct_float_sf, negative_0)
{
    cr_assert_float_eq(
        construct_float_sf(0x01, 0x00, 0x000000),
        0,
        1e-6);
}

Test(construct_float_sf, positive_3_141593)
{
    cr_assert_float_eq(
        construct_float_sf(0x00, 0x80, 0x490FDB),
        3.141593,
        1e-6);
}

Test(construct_float_sf, negative_3_141593)
{
    cr_assert_float_eq(
        construct_float_sf(0x01, 0x80, 0x490FDB),
        -3.141593,
        1e-6);
}