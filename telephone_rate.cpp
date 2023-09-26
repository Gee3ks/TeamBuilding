#include <iostream>
#include <string>
#include <vector>
#include <limits> // must include to clear or ignore user input invalid
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
                    // compare the first two letters in user input string
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
                cerr << "Invalid Input!" << '\n';
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
            cout << "\nCall Duration in Minutes: ";
            if (cin >> callDuration)
            {
                if (callDuration < 1)
                {
                    cerr << "\nInvalid!";
                }
                return true;
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
        // Variables for computing the bill
        int totalMinutes;
        double totalBill;

        // Extract hours and minutes from _time
        int toInt = stoi(_time.substr(0, 2));
        int toInt1 = stoi(_time.substr(3, 2));

        // Calculate the total duration in minutes
        int totalDur = callDuration + toInt1;

        // Calculate the total time gap in hours
        int totalTimeGap = toInt + callDuration;
        string timeFormat = "";

        if (toInt >= 1 && toInt <= 12)
        {
            timeFormat = " AM";
        }
        else if (toInt >= 12 && toInt < 24)
        {
            timeFormat = " PM";
        }
        else if (toInt > 24)
        {
            toInt -= 12;
            timeFormat = " AM";
        }

        // Calculate the new end time
        int newHours = toInt + (callDuration / 60);
        int newMinutes = toInt1 + (callDuration % 60);

        int endTimeHr = toInt;
        int endTimeMn = toInt1;

        if (callDuration == 60)
        {
            endTimeHr += 1;
        }
        else if (callDuration < 60 || callDuration > 60)
        {
            endTimeHr += 1;
            endTimeMn = ((callDuration + toInt1) % 60);
        }

        // if (newMinutes >= 60)
        // {
        //     newHours += 1;
        //     newMinutes -= 60;
        // }

        // Convert call duration to minutes
        int toMinutes = callDuration;

        // Message for printing the results
        string processMessage = "\n***** SHOWING RESULTS ****";
        string appliedPrice = "";
        switch (_day[0])
        {
        case 'M':
        case 'T':
        case 'W':
        case 'F':
            if (toInt >= 8 && toInt <= 18)
            {
                appliedPrice = " 0.40$/min";
                totalBill = toMinutes * 0.40;
                break;
            }
            else if ((toInt >= 1 && toInt < 8) || (toInt >= 18 && toInt < 24))
            {
                appliedPrice = " 0.25$/min";
                totalBill = toMinutes * 0.25;
                break;
            }
        case 'S':
            appliedPrice = " 0.15$/min";
            totalBill = toMinutes * 0.15;
            break;
        }

        cout << processMessage;
        cout << "\n\nDay: " << _day1;
        cout << "\n\nApplied:" << appliedPrice;
        cout << "\n\nCall Duration: " << callDuration << " Minutes.";
        cout << "\n\nFrom: " << _time << timeFormat;
        cout << " - " << (endTimeHr < 10 ? "0" : "") << endTimeHr << ":"
             << (endTimeMn < 10 ? "0" : "") << endTimeMn << timeFormat;
        cout << "\n\nTotal Bill: " << totalBill << "$" << '\n';
        cout << "\n\n**********************";
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

    while (true)
    {
        cout << "\nDo you want to continue? (y/n): ";
        char choice;
        cin >> choice;

        // transform user char input to uppercase
        choice = toupper(choice);

        // variable for the loop to run
        bool isChoiceValid = false;
        for (char &c : validChoices)
        {
            if (c == choice)
            {
                isChoiceValid = true;
                if (choice == 'Y')
                {
                    tel.runProcess();
                }
                else if (choice == 'N')
                {
                    cout << "\nThank You for using! (r) Group 3!";
                    cout << "\nExiting Program.";
                    return 0;
                }
            }
        }

        if (!isChoiceValid)
        {
            cerr << "\nInvalid Choice!";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return 0;
}
