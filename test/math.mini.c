int assert(int condition)
{
  if (!condition)
  {
    printf("Assertion failed\n");
    exit(1);
  }
  return 0;
}
int main()
{
  int a = 4 + 24 / 6 * 2 - 2;
  assert(a == 10);
  int mod = 24 % 7;
  assert(mod == 3);
  assert(a == 10 && mod == 3);
  assert(a == 10 || mod == 3);
  assert(!(!(a == 10 && mod == 3)));
  assert(5 > 4 && 4 >= 4 && 23 < 24 && 24 <= 24 && 24 >= 24 && 24 <= 24);
  printf("All tests passed", 3);
  return 0;
}