#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

  int number;
  const int limit = 100;
  char repeat;

  printf("Welcome to the 'guess the number' game\n"
         "You have to guess the number between 1 and 100\n");

  srand(time(0));

  do {
    int counter = 0;
    int random_number = rand() % limit + 1;

    while (true) {
      printf("Enter your number: ");

      if (scanf("%d", &number) != 1 || (number < 1 || number > 100)) {
        printf("You have to enter the number between 1 and 100!\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        continue;
      }
      counter++;
      if (number < random_number) {
        printf("Higher, try again!\n");
      } else if (number > random_number) {
        printf("Lower, try again!\n");
      } else {
        printf("Well done, you got it!\n");
        break;
      }
    }
    printf("You tried: %d times\n", counter);

    printf("Do you want to try again: \n");
    printf("y/n: ");

    scanf(" %c", &repeat);
    while (repeat != 'y' && repeat != 'n') {
      printf("You have to answer yes or no\n");
      scanf(" %c", &repeat);
    }

  } while (repeat == 'y');
  return 0;
}