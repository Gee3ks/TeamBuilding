#include <iostream>
using namespace std;

bool repeat(string repeat = ""){
    
    while (repeat != "n" && repeat != "y")
    {
        cout << "Do you want to try again[y,n]. ";
        cin >> repeat;
    }

    return repeat == "y";
}

//Function to get Integer Inputs
int get_value(string message){
    int input;
    {
        cout << message;
        cin >> input;
    } while (input < 0);

    return input;
}

//Function to get Character Input
bool get_character(string message){
    char input;
    do
    {
        cout << message;
        cin >> input;
    } while (input != 'A' && input != 'P' && input != 'Y' && input != 'N');
    
    if (input == 'A' || input == 'Y')
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

//Function that solves everything
int blackBox(int startHour, int startMinutes, bool startIsAm , int endHour, int endMinutes, bool endIsAm, bool endIsNextDay){

    //Converting the hour input of the user to minutes for easy calculations
    int startMin = (startHour * 60) + startMinutes;
    int endMin = (endHour * 60) + endMinutes;
    
    //nested if to check for multiple inputs
    //first "if" checks if the end time is on the next day or not
    //second column "if" checks if the starting time is AM or PM 
    //third column "if" checks uf the ending time is AM or PM
    if (endIsNextDay == true)//Next day Claculations
    {
        if (startIsAm == true)
        {
            if (endIsAm == true)
            {
                //returns regularly if both the starting time and the ending time is AM
                return endMin - startMin;
            }
            else{
                //returns when the end time is PM the next day and the starting time is AM
                return 1440 + ((endMin + 720) - startMin);
            }
            
        }
        else
        {
            if (endIsAm == true)
            {
                //return when the starting time is PM and the ending time is AM the Next day
                return endMin - (startMin + 720);
            }
            else{
                //returns when the start time is PM and the end time is PM the next day
                return 1440 + (endMin + 720) - (startMin + 720);
            }
        }
    }
    
    else//Same day Calculations
    {
        if (startIsAm == true)
        {
            if (endIsAm == true)
            {
                //returns when both Times is AM
                return endMin - startMin;
            }
            else{
                //returns when the start time is AM and the end time is PM
                return (endMin + 720) - startMin;
            }
            
        }
        else
        {
            if (endIsAm == true)
            {
                //returns when the start time is PM and the end time is Am, this is redundant as the calculations is done on the next day tree
                return (endMin - (startMin + 720));
            }
            else{
                //returns when both times are PM the same day
                return (endMin + 720) - (startMin + 720);
            }
        }
    }
    


    
}

int main(void){
    int startHour, startMinutes, endHour, endMinutes, timeDifference;
    bool startIsAm, endIsAm, endIsNextDay;

    do
    {
        // the following lines 114 to 116 is to get the input for the starting time and if it's in the morning or not
        startHour = get_value("What is the starting Hour[0-11]: ");
        startMinutes = get_value("What is the starting minute[0-59]: ");
        startIsAm = get_character("What time of the day is it[A for AM / P for PM]: ");

        // checks if the end time is on the next day or not
        endIsNextDay = get_character("Is your end time the next day[Y for yes / N for No]: ");

        // the following lines 122 to 124 is to get the input for the ending time and if it's in the morning or not
        endHour = get_value("What is the starting Hour[0-11]: ");
        endMinutes = get_value("What is the starting minute[0-59]: ");
        endIsAm = get_character("What time of the day is it[A for AM / P for PM]: ");

        //solves everything using the function
        timeDifference = blackBox(startHour, startMinutes, startIsAm, endHour, endMinutes, endIsAm, endIsNextDay);

        //outputs the outcomes
        cout << "Time started: " << startHour << ':' << startMinutes << '\n';
        cout << "Time ended: " << endHour << ':' << endMinutes << '\n';
        cout << "Time Difference is " << timeDifference << " minutes." << '\n';
    } while (repeat());
    


    return 0;
}
