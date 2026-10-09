#include <stdio.h>

#include "strgPtr.h"
#include "caesar.h"

int main()
{
  // printf("%d", strgLen("\0"));
  char destination[40];
  char s[] = "kinginyellow";
  strgCopy("Computer Science", destination, 5);
  // strgChangeCase(s);
  //  printf("%d", strgDiff("abc", "abcd"));
  //  strgReverseLetters(s);
  // strgInterleave("abc", "123567", destination, 20);
  // printf("%d", encryptCaesar("kids these days be like: omfgtscasf", destination, 30, 1));
  // printf("%d", decryptCaesar("__EOM__", destination, 20, 5));
  return 0;
}
