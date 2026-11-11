#include <stdio.h>

int main(int argc, char **argv)
{
  int i = 0;
  int j = 1;
  int k = -1;
  double x = 0.5;
  double y = 0.0;
  printf("%f\n", x * 3);
  printf("%f\n", 3 || j | k);
  printf("%d\n", x * 3 && 3 || j | k);
}
