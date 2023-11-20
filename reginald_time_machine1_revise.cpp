#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string to_upper(string strvar) {
    for (char &c : strvar) {
        c = toupper(c);
    }
    return strvar;
}

bool repeat(string repeat = "") {
    while (repeat != "y" && repeat != "n") {
        cout << "Do you want to try again(y,n)? ";
        cin >> repeat;
        cin.ignore();
    } return repeat == "y";
}


int get_int_time(string message, int range) {
  int time;
  do {
    cout << message;
    cin >> time;
  } while (time < 0 or time > range);
  return time;
}

bool get_bool_period(string message) {
  string ampm;
  do {
    cout << message;
    cin >> ampm;
    ampm = to_upper(ampm);
  } while (not (ampm == "AM" || ampm == "PM"));
  return ampm == "AM";
}

int convert_to_minutes(int hours, int minutes, bool is_am) {
  return (hours % 12) * 60 + minutes + (not is_am) * (12 * 60);
}

int compute_difference(int start_hours, int start_minutes, bool start_is_am, int end_hours, int end_minutes, bool end_is_am) {
  int total_minutes;
  int start_time = convert_to_minutes(start_hours, start_minutes, start_is_am);
  int end_time = convert_to_minutes(end_hours, end_minutes, end_is_am);
  if (start_time < end_time) {
      total_minutes = end_time - start_time;
  } else {
      total_minutes = 24 * 60 - start_time + end_time;
  }
  return total_minutes;       
}

bool repeat_time(string repeat = "") {
    while (repeat != "y" && repeat != "n") {
        cout << "Do you want to travel more?(y,n): ";
        cin >> repeat;
    } return repeat == "y";
}

int get_add_time(string message, int range) {
    int num;
    do {
        cout << message;
        cin >> num;
    } while (range < 1 && range > 2);
    return num;
}

int compute_for_add_minutes(int time) {
    int minutes;

    do {

    int add_time = get_add_time("Travel forwards(1) or backwards(2): ", 2);

    if (add_time == 1) {
        cout << "Enter minutes to add: ";
        cin >> minutes;
        time = time + minutes;
    } else {
        cout << "Enter minutes to subtract: ";
        cin >> minutes;
        time = time - minutes;
    }

    } while (repeat_time());
    return time;
}


int main(void) {
    do {
        int start_hours = get_int_time("Enter start hours (0-12): ", 12);
        int start_minutes = get_int_time("Enter start minutes (0-59): ", 59);
        bool start_is_am = get_bool_period("Enter start time period (AM/PM)");

        int end_hours = get_int_time("Enter end hours (0-12): ", 12);
        int end_minutes = get_int_time("Enter end minutes (0-59): ", 59);
        bool end_is_am = get_bool_period("Enter end time period (AM/PM)");

        int total_minutes = compute_difference(start_hours, start_minutes, start_is_am, end_hours, end_minutes, end_is_am);
        cout << "Total minutes: " << total_minutes << endl;
        
        int future_time = compute_for_add_minutes(total_minutes);
        cout << "Total minutes: " << future_time << endl;


    } while (repeat());

    return 0;
}


/*
int hours, minutes;
bool isAM;

*/
