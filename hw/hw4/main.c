#include <stdio.h>

#include "strgPtr.h"
#include "caesar.h"

int main()
{
  // printf("%d", strgLen("System Fundamental"));
  char destination[20];
  // strgCopy("Computer Science", destination, 5);
  // strgChangeCase("CSE220");
  // printf("%d", strgDiff("abc", "abcd"));
  // strgInterleave("abc", "123", destination, 20);
  // printf("%d", encryptCaesar("System Fundamentals", destination, 30, 1));
  printf("%d", decryptCaesar("__EOM__", destination, 20, 5));
  return 0;
}
