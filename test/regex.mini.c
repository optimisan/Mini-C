int main()
{
  char str[] = scanString();
  int match = regex("a+[0-9]{2}", str);
  if (!match)
  {
    printf("Invalid string");
    exit(1);
  }
  printf("String %s is valid\n", str);
  return match;
}