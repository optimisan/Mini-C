// #include <stdio.h>
// int sum(int a, int b)
// {
//   return a + b;
// }
// int teststring()
// {
//   char str[] = "from string %c";
//   // int a[] = {1, 2};
//   char b = str[0];
//   printf("justsome string here\n");
//   // return a[0][a[0][0]];
//   return -1;
// }
// int f2(int b)
// {
//   return b + 1;
// }
// int f1(int a, int b)
// {
//   int t = f2(a);
//   return t + b;
// }
// int testtime()
// {
//   float a = time();
//   // printf("%d", a);
//   int first = f2(3);
//   // int t = f1(1, 2);
//   float b = time();
//   printf("\n%f", b - a);
//   return 0;
// }
/*multi //*/ //*/
int factorial(int n)
{
  int a = 1;
  for (int i = 1; i <= n; i = i + 1)
  {
    a = a * i;
  }
  return a;
}
int main()
{
  int start = time();
  char str[] = "Factorial is %d\n";
  for (int i = 1; i < 20; i = i + 1)
  {
    printf(str, factorial(i));
  }
  int end = time();
  int writtenChars = printf("Time taken: %d milliseconds\n", end - start);
  return writtenChars;
}
// // Type: Mini C
/*
int main1(float a, int ab)
{
  if (2)
  {
    return 4;
    int k = 7;
  }
  else
    return 5 == 5;
}
*/