#include <stdio.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "MyIntegers.h"


static void redirect_stdout_setup(void)
{
    cr_redirect_stdout();
}


Test(repr_convert, sign_magnitude_to_twos_complement, .init = redirect_stdout_setup)
{
    /* 'S' -> '2': sign/magnitude 0x80000001 (sign = 1, magnitude = 1,
       value = -1). Two's complement of -1 is 0xffffffff. */
    repr_convert('S', '2', 0x80000001);
    fflush(stdout);

    cr_assert_stdout_eq_str("ffffffff\n");
}
