#include <iostream>
#include <string>
#include <iomanip>
#include <limits> // Include to be able to clear input buffer
using namespace std;

// Used Struct to let add mutliple data instances / object
struct Stock
{
    string brand_name;
    int number_of_shares;
    double stock_price;
    double numerator;
    double denominator;
};

// Function for gathering string input
string get_input_str(const string &prompt)
{
    string user_input_str = "";
    cout << prompt;
    cin >> user_input_str;
    return user_input_str;
}

// function for gathering user input
// :numbers
double get_value(const string &prompt)
{
    double num_val(0);
    while (true)
    {
        cout << prompt;
        if (cin >> num_val && num_val > 0)
        {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid Value. Please Try Again!" << endl;
    }
    return num_val;
}

// Function for repeating the program flow
bool repeat()
{
    string response("");
    while (response != "y" && response != "n")
    {
        cout << "Do you want to continue? (y/n): ";
        cin >> response;
    }
    return response == "y";
}

int main(void)
{

    do
    {
        // Speecified the struct range
        // In this case, 2 (2 companies only)
        Stock brands[2];

        // Loop two times
        for (int index = 0; index < 2; index++)
        {
            brands[index].brand_name = get_input_str("Enter the name of the company: ");
            brands[index].number_of_shares = get_value("Enter number of shares: ");
            brands[index].stock_price = get_value("Enter the price for single stock: $");
            brands[index].numerator = get_value("Enter value for numerator: ");
            brands[index].denominator = get_value("Enter value for denominator: ");
        }

        fixed;
        showpoint;
        setprecision(2);

        // Print the results
        cout << "\nStock Name\t"
             << "Market Price\t"
             << "Total Shares\t"
             << "Market Value\t\n";
        for (const Stock &brand : brands)
        {
            double total_market_stock_value = brand.stock_price + (brand.numerator / brand.denominator);
            cout << brand.brand_name << '\t' << total_market_stock_value << "\t\t" << brand.number_of_shares << "\t\t" << total_market_stock_value * brand.number_of_shares << endl;
        }

    } while (repeat());
    return 0;
}
