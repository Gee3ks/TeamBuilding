#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

double calculate_mortgage_cost(double loan_balance, double interest_rate)
{
    double interest_payment = interest_rate * loan_balance;
    double mortgage_cost = 0.03 * loan_balance + interest_payment;
    return mortgage_cost;
}

double calculate_tax_savings(double interestPayment)
{
    double tax_rate = 0.35;
    double tax_savings = tax_rate * interestPayment;
    return tax_savings;
}

double get_positive_value(const string &prompt_message)
{
    double num_value = 0;
    do
    {
        cout << prompt_message;
        if (cin >> num_value && num_value > 0.0)
        {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    } while (true);
    return num_value;
}

bool continue_running()
{
    string response = "";
    while (response != "y" && response != "n")
    {
        cout << "Do you want to continue? [y/n]: ";
        cin >> response;
    }
    return response == "y";
}

int main()
{

    do
    {
        const double interest_rate = 0.06;
        cout << fixed << setprecision(2);
        double price = get_positive_value("Enter house price: $");
        double down_payment = get_positive_value("Enter downpayment amount: $");

        double loan_balance = price - down_payment;
        int years = 10;

        for (int year = 1; year <= years; ++year)
        {
            double interest_payment = interest_rate * loan_balance;
            double mortgage_cost = calculate_mortgage_cost(loan_balance, interest_rate);
            double tax_savings = calculate_tax_savings(interest_payment);
            double after_tax_cost = mortgage_cost - tax_savings;

            loan_balance -= mortgage_cost; // Update loanBalance

            cout << "Year " << year << ":" << endl;
            cout << "  Mortgage Cost: $" << mortgage_cost << endl;
            cout << "  Tax Savings: $" << tax_savings << endl;
            cout << "  After-Tax Cost: $" << after_tax_cost << endl;
        }
    } while (continue_running());
    cout << "Program exiting." << endl;

    return 0;
}
