#include <stdio.h>

int main(int argc, char **argv)
{
  int test = 0x6578;
  int *ptr = &test;
  printf("0x%x\n", *((char *)ptr));
  printf("0x%x\n", *((char *)ptr + 1));
}
