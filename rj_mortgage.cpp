#include <iostream>
#include <iomanip>
using namespace std;

const double LOAN_RATE = 0.03;   
const double INTEREST_RATE = 0.06;
const double TAX_RATE = 0.35;

bool repeat(string repeat = "") {
    while (repeat != "y" && repeat != "n") {
        cout << "Do you want to try again?(y,n) ";
        cin >> repeat;
        cin.ignore();
    } return repeat == "y";
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

double calc_annual_tax(int annual_mortgage, int tax_savings) {
    return annual_mortgage - tax_savings;
}

double calc_annual_mortgage(int initial_loan_balance) {
    return (LOAN_RATE * initial_loan_balance) + (INTEREST_RATE * initial_loan_balance);
}

void print_value() {
    int house_price = get_value("Enter the price of the house: $");
    int downpayment = get_value("Enter the downpayment: $");
    double initial_loan_balance = house_price - downpayment;

    double annual_mortgage = calc_annual_mortgage(initial_loan_balance);
    double tax_savings = TAX_RATE * (INTEREST_RATE * initial_loan_balance);

    cout << "Annual after tax cost: $" << calc_annual_tax(annual_mortgage, tax_savings) << endl;

    for (int year = 1; year <=10; year++) {
        cout << "Year: " << year << " $" << calc_annual_tax(annual_mortgage, tax_savings) << endl;
    }

}

int main(void) {
    do {

        print_value();

    } while (repeat());
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
