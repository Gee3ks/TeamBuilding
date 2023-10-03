#include <iostream>
using namespace std;

bool repeat(string repeat = "") {
  while (repeat != "y" && repeat != "n") {
    cout << "Do you want to continue (y,n)? ";
    cin >> repeat;
  }
  return repeat == "y";       
}

int get_value(string message) {
  int value;
  do {
    cout << message;
    cin >> value;
  } while (value < 0);
  return value;
}

// n = 0, 1, 2, 3, 4, 5, 6,  7,  8,  9, 10, ..
// f = 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...
uint64_t fibonacci(int number) {
  if (number < 3) {
    return 1 * (number > 0);
  }
  uint64_t fib0 = 1;
  uint64_t fib1 = 1;
  uint64_t results;
  for (int index = 3; index <= number; index++) {
    results = fib0 + fib1;
    fib0 = fib1;
    fib1 = results;
  }
  return results;
}

int main(void) {
  const int TIME_PERIOD = 5;
  do {
    int initial_population = get_value("Enter initial population size in pounds: ");
    int number_of_days = get_value("Enter the number of day(s): ");
    cout  << "Green curd total population in pounds: "
          << initial_population * fibonacci(number_of_days / TIME_PERIOD + 1)
          << endl;
  } while (repeat());

  return 0;
}
