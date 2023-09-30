#include <iostream>
#include <limits>
using namespace std;

class Crud
{
private:
    const int TIME_PERIOD = 5;

public:
    int calculatePopulation(int initialSize, int days)
    {
        if (days < 10)
            return days < 0 ? 0 : initialSize;
        int a = initialSize, b = initialSize;
        for (int i = 10; i <= days; i += TIME_PERIOD)
            a = (b += a) - a;
        return b;
    }
};

int main()
{
    Crud crud;
    while (true)
    {
        int initialSize, days;
        cout << "\nEnter the initial size of crud population in pounds: ";
        if (cin >> initialSize && initialSize != 0)
        {
            cout << "\nEnter the number of days: ";
            if (cin >> days)
            {
                int result = crud.calculatePopulation(initialSize, days);
                cout << "\nAfter " << days << " days, the total population of Green Crud in pounds is " << result << " pounds\n";
            }
            else
                cerr << "\nInvalid Input!";
        }
        else
            cerr << "\nInvalid Input!";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        char repeat;
        cout << "Do you want to calculate again? (y/n): ";
        cin >> repeat;
        if (repeat != 'y' && repeat != 'Y')
            break;
    }
    return 0;
}
