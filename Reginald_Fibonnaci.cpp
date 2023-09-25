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

int fibonacci(int number) {
  if (number < 2) {
    return 1 * (number == 1);
  }
  return fibonacci(number - 1) + fibonacci(number - 2);
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
