#include <iostream>
#include <iomanip>
using namespace std;

const double LOAN_RATE = 0.03;
const double INTEREST_RATE = 0.06;
const double TAX_RATE = 0.35;

bool continue_running() {
  string repeat("");
  while (repeat != "y" && repeat != "n") {
    cout << "Do you want to try again?(y,n) ";
    cin >> repeat;
  }
  return repeat == "y";
}

int get_value(string message) {
  int value;
  do {
    cout << message;
    cin >> value;
  } while (value < 1);
  return value;
}

double calc_initial_loan(int house_price, int down_payment) {
  return house_price - down_payment;
}

double calc_annual_tax(double annual_mortgage, double tax_savings) {
  return annual_mortgage - tax_savings;
}

double calc_annual_mortgage(double initial_loan_balance) {
  return (LOAN_RATE * initial_loan_balance) + (INTEREST_RATE * initial_loan_balance);
}

void print_value() {
  int house_price = get_value("Enter the price of the house: $");
  int downpayment = get_value("Enter the downpayment: $");
  double initial_loan_balance = calc_initial_loan(house_price, downpayment);

  // Initialize total annual mortgage cost
  double total_annual_mortgage_cost = 0;

  for (int year = 1; year <= 10; year++) {
    double annual_mortgage = calc_annual_mortgage(initial_loan_balance);
    double tax_savings = TAX_RATE * (INTEREST_RATE * initial_loan_balance);

    // Accumulate annual mortgage cost
    total_annual_mortgage_cost += calc_annual_tax(annual_mortgage, tax_savings);
  }

  cout << "Total annual mortgage cost after 10 years: $" << total_annual_mortgage_cost << endl;
}

int main(void) {
  do {
    print_value();
  } while (continue_running());
  return 0;
}
