#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

class TelePhoneBill
{
private:
    string _time;
    int callDuration;
    string _day, _day1;
    vector<string> daysInTheWeek = {"MO", "TU", "WE", "TH", "FR", "SA", "SU"};

public:
    bool getUserInput()
    {
        bool isDayFound = false; // Initialize isDayFound

        while (true)
        {
            cout << "\nEnter the Day the Call was made: (Mo - Su): ";

            if (cin >> _day)
            {
                // Convert input to uppercase
                for (char &c : _day)
                {
                    c = toupper(c);
                }

                // Check if the day is valid
                for (const string &word : daysInTheWeek)
                {
                    if (_day.substr(0, 2) == word)
                    {
                        isDayFound = true;
                        _day1 = word;
                        break;
                    }
                }

                if (isDayFound)
                {
                    return true;
                }
                else
                {
                    cerr << "Invalid day. Please try again." << endl;
                }
            }
            else
            {
                cerr << "Invalid Input!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    bool parseTime()
    {
        while (true)
        {
            cout << "\nCall Start Time: (HH:MM): ";
            if (cin >> _time)
            {
                if (_time.length() == 5 && _time[2] == ':' &&
                    (isdigit(_time[0]) && isdigit(_time[1])) &&

                    (isdigit(_time[3]) && isdigit(_time[4])))
                {
                    int hours = stoi(_time.substr(0, 2));
                    int minutes = stoi(_time.substr(3, 5));

                    if (hours >= 0 && hours <= 24 && minutes >= 0 && minutes <= 60)
                    {
                        return true;
                    }
                }
                cerr << "\nInvalid Format!";
                cerr << "\n24:60\n";
            }
            else
            {
                cerr << "\nInvalid Input!";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    bool getDuration()
    {

        while (true)
        {
            cout << "\nCall Duration in Hours: (1-12): ";
            if (cin >> callDuration)
            {
                if ((callDuration + stoi(_time.substr(0, 2))) > 24)
                {
                    cerr << "\nOut of range!";
                }
                else
                {
                    return true;
                }
            }
            else
            {
                cerr << "\nInvalid Input!";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    void calculateTimeGap()
    {
        // variables for computing the bill
        int totalMinutes;
        double totalBill;

        // sliced from the _time variable
        int toInt = stoi(_time.substr(0, 2));
        int toInt1 = stoi(_time.substr(3, 4));

        // variable for time format
        int totalTimeGap = toInt + callDuration;
        string timeFormat = "";
        if (totalTimeGap > 12 && totalTimeGap <= 24)
        {
            timeFormat = " PM";
        }
        else if (totalTimeGap >= 1 && totalTimeGap <= 12)
        {
            timeFormat = " AM";
        }

        // conditions to set for initial time format
        string timeFormat1 = "";
        if (toInt > 12)
        {
            timeFormat1 = "PM";
        }
        else if (toInt >= 1 && toInt <= 12)
        {
            timeFormat1 = "AM";
        }

        // convert callduration in hours to minutes
        int toMinutes = callDuration * 60;

        // message for printing the results
        string processMessage = "\n***** SHOWING RESULTS ****";
        switch (_day[0]) // used the _time[0] for the operation
        {
        case 'M':
        case 'T':
        case 'W':
        case 'F':
            if (toInt >= 8 && toInt <= 18)
            {
                // rate for weekday between 8 am and 6 pm
                totalBill = toMinutes * 0.40;

                cout << processMessage;
                cout << "\n\nDay: " << _day1;
                cout << "\n\nApplied: 0.40$/min";
                cout << "\n\nCall Duration: " << callDuration << " Hours.";
                cout << "\n\nFrom: "
                     << _time << timeFormat1
                     << " - " << toInt + callDuration << ":" << toInt1 << timeFormat;
                cout << "\n\nTotal Bill: " << totalBill << "$" << '\n';
                cout << "\n\n**********************";
                break;
            }
            else if ((toInt >= 1 && toInt < 8) || (toInt >= 18 && toInt <= 24))
            {
                // rates for weekday before 8 am or after 6 pm
                totalBill = toMinutes * 0.25;

                cout << processMessage;
                cout << "\n\nDay: " << _day1;
                cout << "\n\nApplied: 0.25$/min";
                cout << "\n\nCall Duration: " << callDuration << " Hours.";
                cout << "\n\nFrom: "
                     << _time << timeFormat1
                     << " - " << toInt + callDuration << ":" << toInt1 << timeFormat;
                cout << "\n\nTotal Bill: " << totalBill << "$" << '\n';
                cout << "\n\n**********************";
                break;
            }
        case 'S':
            // rate for weekends
            totalBill = toMinutes * 0.25;

            cout << processMessage;
            cout << "\n\nDay: " << _day1;
            cout << "\n\nApplied: 0.25$/min";
            cout << "\n\nCall Duration: " << callDuration << " Hours.";
            cout << "\n\nFrom: "
                 << _time << timeFormat1
                 << " - " << toInt + callDuration << ":" << toInt1 << timeFormat;
            cout << "\n\nTotal Bill: " << totalBill << "$" << '\n';
            cout << "\n\n**********************";
            break;
            break;
        }
    }

    void runProcess()
    {
        cout << "\nWelcome to Telephone Billing System!\n\n";
        cout << "****** Rates ****** ";
        cout << "\nWeek day | Mon - Fri | (Between 8AM - 6PM) = .40$/min ";
        cout << "\nWeek day | Mon - Fri (Before 8 am or After 6PM) = .25$/min";
        cout << "\nWeekends | Sat - Sun (Any time of the Day) = .25$/min";
        cout << "\n_____________________________________________\n";
        // encapsulated the functions
        getUserInput();
        parseTime();
        getDuration();
        calculateTimeGap();
    }
};

int main()
{
    // collection of valid inputs
    char validChoices[2] = {'Y', 'N'};
    // class instance
    TelePhoneBill tel;

    // variable for the loop to run or not
    bool _run = true;
    while (_run)
    {
        tel.runProcess();
        cout << "\nDo you want to continue? (y/n): ";
        char choice;
        cin >> choice;

        // transform user char input to uppercase
        choice = toupper(choice);

        for (char &c : validChoices)
        {
            if (c == choice)
            {
                if (choice == 'Y')
                {
                    _run = true;
                }
                else if (choice == 'N')
                {
                    cout << "\nThank You for using! (r) Group 3!";
                    cout << "\nExiting Program.";

                    _run = false;
                }
                else
                {
                    cerr << "\nInvalid Input!";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
    }
    return 0;
}
