int abs(int a)
{
  if (a < 0)
  {
    return -a;
  }
  return a;
}
int main()
{
  int start = time();
  int chosen = rand(0, 100);
  printf("I have chosen a number between 0 and 100. Can you guess it?\nEnter your guess: ");
  int guessed = scanInt();
  int difference = abs(chosen - guessed);
  while (guessed != chosen)
  {
    int newDiff = abs(chosen - guessed);
    if (newDiff < difference)
    {
      printf("Warmer\n");
    }
    else
    {
      printf("Colder\n");
    }
    difference = newDiff;
    printf("Enter your guess: ");
    guessed = scanInt();
  }
  int end = time();
  printf("You are correct!\nTime taken is %f seconds.", (end - start) / 1000.0);
  return 0;
}