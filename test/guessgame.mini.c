int verifyId()
{
  printf("To play this game, enter your BITS ID: ");
  char id[] = scanString();
  if (regex("202[0-9][A-Z0-9]{4}[0-9]{4}H", id))
  {
    return 1;
  }
  printf("Invalid ID. Please try again.\n");
  exit(1);
  return 0;
}
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
  verifyId();
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