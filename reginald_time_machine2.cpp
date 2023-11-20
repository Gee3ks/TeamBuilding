#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

bool repeat(string repeat = "") {
    while (repeat != "y" && repeat != "n") {
        cout << "Do you want to try again(y,n)? ";
        cin >> repeat;
        cin.ignore();
    } return repeat == "y";
}

string to_upper(string strvar) {
    for (char &c : strvar) {
        c = toupper(c);
    }
    return strvar;
}

bool validate_hours(int hours) {
    return (hours >= 0) && (hours <= 12);
}

bool validate_minutes(int minutes) {
    return (minutes >= 0) && (minutes <= 59);
}

bool validate_ampm(string ampm) {
    return (ampm == "AM" || ampm == "PM");
}

int get_time(string message) {
    string timestr, ampm;
    char colon;
    int hours, minutes;
    do {
        cout << message;
        getline(cin, timestr);
        istringstream iss(timestr);
        iss >> hours >> colon >> minutes >> ampm;
        ampm = to_upper(ampm);
    } while (not (validate_hours(hours) && validate_minutes(minutes) && validate_ampm(ampm)));

    return (hours % 12) * 60 + minutes + (ampm == "PM") * (12 * 60);
}

int compute_difference(int start_time, int end_time) {
    int total_minutes;
    if (start_time < end_time) {
        total_minutes = end_time - start_time;
    } else {
        total_minutes = 24 * 60 - start_time + end_time;
    }
    return total_minutes;       
}

int main(void) {
    do {
        int start_time = get_time("Enter start time (HH:MM AM/PM): ");
        int end_time = get_time("Enter end time (HH:MM AM/PM): ");
        cout << "Total minutes: " << compute_difference(start_time, end_time) << endl;

    } while (repeat());
    return 0;
}


/*
int hours, minutes;
bool isAM;

*/
