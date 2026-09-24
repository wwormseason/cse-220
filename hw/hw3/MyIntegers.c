#include "MyIntegers.h"
#include <stdio.h>

/*
Convert between:

'S' = sign magnitude

'2' = two's complement


Print:

hex value:
xxxxxxxx

error:
error

undefined:
undefined
*/

/*
 * Hint: the two trickiest cases are the ones the assignment calls out
 * as "undefined" and "always output positive zero".
 *   - Two's complement 0x80000000 (the most negative int) has no
 *     matching sign/magnitude value, since sign/magnitude only goes
 *     down to -(2^31 - 1). That is the case you print "undefined" for
 *     when converting two's complement to sign/magnitude.
 *   - Sign/magnitude has two zeros, 0x00000000 and 0x80000000 (a sign
 *     bit of 1 with a magnitude of 0). Both represent the value 0, so
 *     whichever representation you are converting into, make sure
 *     zero always comes out as 0x00000000, never with the sign bit
 *     set.
 */
void repr_convert(
    char source_repr,
    char target_repr,
    uint32_t repr)
{
    if (target_repr == '2')
    {
        if (source_repr == 'S')
        {
            repr = repr << 1;
            repr = repr >> 1;
            repr = repr ^ 0xFFFFFFFF;
            repr = repr + 1;
        }
        else if (source_repr == '2')
        {
            // do nothing ᕕ( ᐛ )ᕗ
        }
        else
        {
            print("error");
            return;
        }
    }
    else if (target_repr == 'S')
    {
        if (source_repr == '2')
        {
            repr = repr - 1;
            int placeholder = repr << 1;
            placeholder = placeholder >> 1;
            placeholder = placeholder ^ 0xFFFFFFFF;
            int sign = repr >> 31;
            sign = sign << 31;
            repr = placeholder + sign;
        }
        else if (source_repr == 'S')
        {
        }
        else
        {
            print("error");
            return;
        }
    }
    else
    {
        print("error");
        return;
    }
    printf("%x", repr);

    // TODO: implement
}
