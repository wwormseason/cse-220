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

Test(repr_convert, twos_complement_to_sign_magnitude, .init = redirect_stdout_setup)
{
    repr_convert('2', 'S', 0x80000000);
    fflush(stdout);

    cr_assert_stdout_eq_str("00000000\n");
}

Test(repr_convert, sign_magnitude_to_sign_magnitude, .init = redirect_stdout_setup)
{
    repr_convert('S', 'S', 0x80000000);
    fflush(stdout);

    cr_assert_stdout_eq_str("00000000\n");
}

Test(repr_convert, twos_complement_to_sign_magnitude, .init = redirect_stdout_setup)
{
    repr_convert('2', 'S', 0x7fffffff);
    fflush(stdout);

    cr_assert_stdout_eq_str("7fffffff\n");
}

Test(repr_convert, sign_magnitude_to_twos_complement, .init = redirect_stdout_setup)
{
    repr_convert('S', '2', 0x7fffffff);
    fflush(stdout);

    cr_assert_stdout_eq_str("7fffffff\n");
}

Test(repr_convert, invalid_to_twos_complement, .init = redirect_stdout_setup)
{
    repr_convert('F', '2', 0x00394812);
    fflush(stdout);

    cr_assert_stdout_eq_str("error\n");
}

Test(repr_convert, sign_magnitude_to_invalid, .init = redirect_stdout_setup)
{
    repr_convert('2', 'F', 0x00394812);
    fflush(stdout);

    cr_assert_stdout_eq_str("error\n");
}

Test(repr_convert, twos_complement_to_twos_complement, .init = redirect_stdout_setup)
{
    repr_convert('2', '2', 0x59f2ca50);
    fflush(stdout);

    cr_assert_stdout_eq_str("x59f2ca50\n");
}

Test(repr_convert, twos_complement_to_twos_complement, .init = redirect_stdout_setup)
{
    repr_convert('2', 'S', 0x80000000);
    fflush(stdout);

    cr_assert_stdout_eq_str("undefined\n");
}

Test(repr_convert, sign_magnitude_to_sign_magnitude, .init = redirect_stdout_setup)
{
    repr_convert('S', 'S', 0x00000000);
    fflush(stdout);

    cr_assert_stdout_eq_str("00000000\n");
}

Test(repr_convert, sign_magnitude_to_twos_complement, .init = redirect_stdout_setup)
{
    repr_convert('S', '2', 0x80000005);
    fflush(stdout);

    cr_assert_stdout_eq_str("fffffffb\n");
}