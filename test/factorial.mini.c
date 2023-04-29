int factorial8(int n)
{
  int a = 1;
  for (int i = 1; i <= n; i = i + 1)
  {
    a = a * i;
  }
  return a;
}
char factorial(int i) { return 'c'; }
int main()
{
  int start = time();
  char str[] = "Factorial is %d\n";
  for (int i = 1; i < 60; i = i + 1)
  {
    printf(str, factorial(i));
  }
  int end = time();
  int writtenChars = printf("Time taken: %e milliseconds\n", end - start);
  return writtenChars;
}