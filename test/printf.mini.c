int strlen(char s[])
{
  // Since a character cannot be 0 or \0,
  // we use a[1] to represent \0
  char null[] = "a";
  int i = 0;
  while (s[i] != null[1])
  {
    i = i + 1;
  }
  return i;
}
int main()
{
  // char str[] = "12345678";
  char input[] = scanString();
  printf("Length of input string is %d\n", strlen(input));
  // char b = str[1];
  // printf("\n%c", b);
  return 0;
}