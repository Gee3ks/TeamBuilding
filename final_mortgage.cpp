#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

const double LOAN_RATE = 0.03;
const double INTEREST_RATE = 0.06;
const double TAX_RATE = 0.35;

void clear_input()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool continue_running()
{
    string repeat("");
    while (repeat != "y" && repeat != "n")
    {
        cout << "Do you want to try again?(y,n) ";
        cin >> repeat;
    }
    return repeat == "y";
}

int get_value(string message)
{
    int value;
    do
    {
        cout << message;
        if (cin >> value && value > 0)
        {
            break;
        }
        clear_input();

    } while (value < 1);

    return value;
}

double calc_initial_loan(int house_price, int down_payment)
{
    return house_price - down_payment;
}

double calc_annual_tax(int annual_mortgage, int tax_savings)
{
    return annual_mortgage - tax_savings;
}

double calc_annual_mortgage(int initial_loan_balance)
{
    return (LOAN_RATE * initial_loan_balance) + (INTEREST_RATE * initial_loan_balance);
}

void print_value()
{
    double interest_rate, mortgage_cost, tax_savings, after_tax_cost;
    double house_price = get_value("Enter house price: $");
    double down_payment = get_value("Enter down-payment amount: $");
    double loan_balance = house_price - down_payment;
    const int year_count = 10;
    for (int year = 1; year <= year_count; year++)
    {
        interest_rate = 0.06 * loan_balance;
        mortgage_cost = 0.03 * loan_balance + interest_rate;
        tax_savings = 0.35 * interest_rate;
        after_tax_cost = mortgage_cost - tax_savings;
        loan_balance -= 0.03 * loan_balance;
        cout << "Year " << year << endl;
        cout << "After tax cost: $" << after_tax_cost << endl;
    }
}

int main(void)
{
    do
    {
        print_value();

    } while (continue_running());
    return 0;
}

/*
int initial_loan_balance = house_price - downpayment;
const double loan_rate = 0.03;
const double interest_rate = 0.06;
const double tax_rate = 0.35;
double annual_mortgage = (loan_rate * initial_loan_balance) + (interest_rate * initial_loan_balance);
double tax_savings = tax_rate * (interest_rate * initial_loan_balance)


cout << "Annual after tax cost: " << annual_mortgage - tax_savings << endl;
*/
