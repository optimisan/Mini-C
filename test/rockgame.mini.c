int main()
{
  int player = 0, computer = 0;
  int rounds = 3;
  char play[][1] = {"Rock", "Paper", "Scissors"};
  while (rounds)
  {
    rounds = rounds - 1;
    int choice = rand(0, 2);
    printf("Enter 0 for Rock, 1 for Paper, 2 for Scissors: ");
    player = scanInt();
    printf("You chose %s\n", play[player]);
    printf("Computer chose %s\n", play[choice]);
    if ((player == 0 && choice == 2) || (player == 1 && choice == 0) || (player == 2 && choice == 1))
    {
      printf("You win!\n");
      player = player + 1;
    }
    else if (player == choice)
    {
      printf("Draw!\n");
    }
    else
    {
      printf("You lose!\n");
      computer = computer + 1;
    }
  }
  printf("You won %d times\n", player);
  printf("Computer won %d times\n", computer);
  if (player > computer)
  {
    printf("You win the game!\n");
  }
  else if (player == computer)
  {
    printf("Draw!\n");
  }
  else
  {
    printf("You lose the game!\n");
  }
  return 0;
}