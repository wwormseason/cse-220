#include <stdio.h>

#include "strgPtr.h"
#include "caesar.h"

int main()
{
  // printf("%d", strgLen("System Fundamental"));
  char destination[40];
  char s[] = "CSE220";
  // strgCopy("Computer Science", destination, 5);
  // strgChangeCase(s);
  // printf("%d", strgDiff("abc", "abcd"));
  // strgReverseLetters(s);
  // strgInterleave("abc", "123", destination, 20);
  printf("%d", encryptCaesar("kids these days be like: omfgtscasf", destination, 30, 1));
  // printf("%d", decryptCaesar("__EOM__", destination, 20, 5));
  return 0;
}
