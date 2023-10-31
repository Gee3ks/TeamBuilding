#include <iostream>
#include <string>
#include <iomanip>
#include <limits> // Include to be able to clear input buffer
using namespace std;

// Used Struct to let add mutliple data instances / object
struct Stock
{
    string brandName;
    int numberOfShares;
    double stockPrice;
    double numerator;
    double denominator;
};

// Function for gathering string input
string getString(const string &message)
{
    string userInput = "";
    cout << message;
    cin >> userInput;
    return userInput;
}

// function for gathering user input
// :numbers
double getValue(const string &message)
{
    double numVal(0);
    while (true)
    {
        cout << message;
        if (cin >> numVal && numVal > 0)
        {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid Value. Please Try Again!" << endl;
    }
    return numVal;
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
            brands[index].brandName = getString("Enter the name of the company: ");
            brands[index].numberOfShares = getValue("Enter number of shares: ");
            brands[index].stockPrice = getValue("Enter the price for single stock: $");
            brands[index].numerator = getValue("Enter value for numerator: ");
            brands[index].denominator = getValue("Enter value for denominator: ");
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
            double totalMarketStockVal = brand.stockPrice + (brand.numerator / brand.denominator);
            cout << brand.brandName << '\t' << totalMarketStockVal << "\t\t" << brand.numberOfShares << "\t\t" << totalMarketStockVal * brand.numberOfShares << endl;
        }

    } while (repeat());
    return 0;
}
