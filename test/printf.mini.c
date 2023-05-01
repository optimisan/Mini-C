int strlen(char s[])
{
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
  printf("Hello %c", 'c');
  char str[] = "some string here";
  printf("%d", strlen(str));
  return 0;
}