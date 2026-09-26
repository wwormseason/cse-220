#include <stdio.h>
#include "Myfloat.h"

float construct_float_sf(
    char sign_bit,
    char exponent,
    unsigned int fraction)
{

   unsigned int f = 0; /* DO NOT CHANGE */

   /*
      Construct IEEE-754
      single precision float.

      sign:
      bit 31

      exponent:
      bits 30-23

      fraction:
      bits 22-0
   */

   /*
      Hint: char is signed on most machines, so a value like 0x81
      passed in for sign_bit or exponent will arrive here as a
      negative number, not as 129. That is expected, do not "fix" it
      by changing the parameter types. Cast to unsigned int and mask
      with 0xFF before shifting it into place, for example
      ((unsigned int)exponent & 0xFF), and sign extension takes care
      of recovering the original bit pattern for you.
   */
   unsigned int sign = ((unsigned int)(sign_bit & 0x01) << 31); // isolate sign bit
   unsigned int exp = ((unsigned int)(exponent & 0xFF) << 23);  // isolate exponent
   unsigned int frac = (fraction & 0x7FFFFF);                   // isolate fraction
   if ((exp | frac) == 0)
   {
      sign = 0; // special circumstance
   }
   f = sign | exp | frac; // combination of all parts

   return *(float *)&f; /* DO NOT CHANGE */
}
