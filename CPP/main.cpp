#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

int main() {

  int number{};
  const int limit{100};
  char repeat{};

  srand(time(0));

  do {

    int random_number = rand() % limit + 1;
    int counter{0};

    while (true) {
      std::cout << "Enter the number between 1 and 100: ";
      if (!(std::cin >> number) || (number < 1 || number > 100)) {
        std::cout << "You have to enter the number between 1 and  100" << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }

      counter++;

      if (number < random_number)
        std::cout << "Higher, try again! " << "\n";
      else if (number > random_number)
        std::cout << "Lower, try again! " << "\n";

      else {
        std::cout << "You got it, well done! " << "\n";
        break;
      }
    }
    std::cout << "You have tried " << counter << " times" << "\n";

    std::cout << "Do you want to try again? " << "\n";
    std::cout << "y/n: ";
    std::cin >> repeat;

    while (repeat != 'y' && repeat != 'n') {
      std::cout << "You have to answer y or n: ";
      std::cin >> repeat;
    }

  } while (repeat == 'y');

  return 0;
}