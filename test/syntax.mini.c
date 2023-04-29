#include <stdio.h>
int f(float a)
{
  return printf("%f\n", a);
}
int main()
{
  char b[] = "f2345";
  // float a = 4; // + 5.6;
  float c = b[1];
  float a = 24;
  f(a);
  // int print = 5;
  printf("%d\n", 4.5);
  return 4;
}