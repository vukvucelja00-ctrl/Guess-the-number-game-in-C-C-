# Guess the Number: C vs C++

A terminal number-guessing game written in two languages, C and C++, to
compare how they handle the same problem.

## Features

- random number from 1 to 100
- input validation (rejects non-numbers and out-of-range values without crashing)
- attempt counter
- play again (y/n)

## Build & run

```bash
clang -std=c17 -Wall -Wextra c/main.c -o guess_c && ./guess_c
clang++ -std=c++20 -Wall -Wextra cpp/main.cpp -o guess_cpp && ./guess_cpp
```

## Example

```text
Enter your number: 50
Higher, try again!
Enter your number: abc
You have to enter the number between 1 and 100!
Enter your number: 75
Lower, try again!
...
Well done, you got it!
You tried: 6 times
Do you want to try again?
y/n: n
```

## C vs C++

### Reading a number and clearing invalid input

**C:**

```c
if (scanf("%d", &number) != 1 || number < 1 || number > 100) {
    printf("You have to enter the number between 1 and 100!\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    continue;
}
```

**C++:**

```cpp
if (!(std::cin >> number) || number < 1 || number > 100) {
    std::cout << "You have to enter the number between 1 and 100!\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    continue;
}
```

In C, `scanf` returns how many values it read, so `!= 1` means the input
was not a number. The leftover characters are removed one by one with
`getchar()`. In C++, the stream itself remembers that reading failed:
`clear()` resets that state and `ignore()` skips the rest of the line.

### Reading a single character

**C:**

```c
scanf(" %c", &repeat);
```

**C++:**

```cpp
std::cin >> repeat;
```

After reading a number, the Enter key (`'\n'`) is still left in the input
buffer. In C, `"%c"` reads *any* character, including that leftover `'\n'`,
so the program would skip the question. The space in `" %c"` tells `scanf`
to skip all whitespace first. In C++, `std::cin >> repeat` skips whitespace
automatically, so no extra step is needed.

### Brace initialization

**C:**

```c
int number = 0;
int x = 3.7;   // compiles, x silently becomes 3
```

**C++:**

```cpp
int number{};  // guaranteed to be 0
int x{3.7};    // compile error: narrowing from double to int
```

C++11 added brace initialization. Empty braces always give zero, and the
compiler refuses conversions that would lose data (narrowing). C does not
have this syntax at all (`int x{5};` does not compile in C), so
initialization uses `=` and narrowing happens silently.

## Common pitfalls

- **Reading input twice.** `if (!(std::cin >> number))` already reads
  *and* checks the input. Adding a separate `std::cin >> number;` before it
  makes the program read two numbers and silently discard the first one.
- **Off-by-one in the random range.** `rand() % (limit + 1)` gives 0 to 100,
  so the game can pick a number the player is not allowed to enter.
  `rand() % limit + 1` gives 1 to 100. The position of the parentheses
  changes the result, because `%` is evaluated before `+`.
- **State leaking between games.** Variables declared outside the outer
  loop keep their values. The attempt counter must be reset at the start
  of each game, and the "play again" answer must be read *before* it is
  validated, otherwise the previous answer passes the check.
- **`=` vs `==` in C.** The buffer-clearing loop needs assignment:
  `(c = getchar()) != '\n'`. Writing `c == getchar()` compares instead of
  storing the character, so `c` never changes and the loop never ends.
  The parentheses are required, because `!=` is evaluated before `=`.