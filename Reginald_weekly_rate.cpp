#include <iostream>
using namespace std;

// 60 minutes in 1 hour, convert all hours to minutes
const int SIX_PM = 18 * 60; 
const int EIGHT_AM = 8 * 60;
const int TWENTY_FOUR_HOURS = 24 * 60;
const double RATE_OF_ON_HOURS = 0.40;
const double RATE_OF_OFF_HOURS = 0.25;
const double RATE_OF_WEEKENDS = 0.15;
const string DAY_OF_THE_WEEK[] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};

bool repeat(string repeat = "") {
  while (repeat != "y" && repeat != "n") {
    cout << "Do you want to continue (y,n)? ";
    cin >> repeat;
  }
  return repeat == "y";
}

string day_of_the_week_string() {
    string days_string = "";
    for (int index = 0; index < 7; index++) {
      days_string = days_string + DAY_OF_THE_WEEK[index] + ((index < 6) ? "," : "");
    }
    return days_string;
}

string convert_to_lower(string var_string) {
  for (int index = 0; index < var_string.length(); index++) {
    var_string[index] = tolower(var_string[index]);
  }
  return var_string;
}

int get_day_of_the_week() {
  do {
    string day_of_the_week;
    cout << "Enter day of the week (" << day_of_the_week_string() << "): ";
    cin >> day_of_the_week;
    for (int index = 0; index < 7; index++) {
      if (convert_to_lower(day_of_the_week) == convert_to_lower(DAY_OF_THE_WEEK[index])) {
        return index;
      }
    }
  } while (true);
}

bool is_string_digit(string var_string) {
  return isdigit(var_string[0]) and isdigit(var_string[1]);
}

bool validate_hours(string hours) {
  return is_string_digit(hours) and stoi(hours) < 24;
}

bool validate_minutes(string minutes) {
  return is_string_digit(minutes) and stoi(minutes) < 60;
}

int get_call_started() {
  do {
    string call_started;
    cout << "Enter call started (HH:MM): ";
    cin >> call_started;
    if ((call_started.length() == 5) and (call_started[2] == ':')) {
      string hours_string = call_started.substr(0, 2);
      string minutes_string = call_started.substr(3, 2);
      if (validate_hours(hours_string) and validate_minutes(minutes_string)) {
        return stoi(hours_string) * 60 + stoi(minutes_string);
      }
    }
  } while (true);
}

int get_length_of_calls() {
  int length_of_calls;
  do {
    cout << "Enter length of call in minutes: ";
    cin >> length_of_calls;
  } while (length_of_calls < 1);
  return length_of_calls;
}

double get_total_costs(int day_of_the_week, int call_started, int length_of_calls) {

  double total_costs = 0;

  do {

    int remaining_minutes_for_the_day = TWENTY_FOUR_HOURS - call_started;

    if (remaining_minutes_for_the_day > length_of_calls) {
      remaining_minutes_for_the_day = length_of_calls;
    }

    if (day_of_the_week < 5 ) {

      // Monday to Friday rate computation here
      int minutes_multiplier;
      int minutes_remaining = remaining_minutes_for_the_day;

      if (call_started < EIGHT_AM) {
        minutes_multiplier = EIGHT_AM - call_started;
        if (minutes_multiplier > minutes_remaining) {
          minutes_multiplier = minutes_remaining;
        }
        total_costs += RATE_OF_OFF_HOURS * minutes_multiplier;
        minutes_remaining -= minutes_multiplier;
        call_started = EIGHT_AM;
      }

      if (call_started <= SIX_PM) {
        minutes_multiplier = SIX_PM - call_started;
        if (minutes_multiplier > minutes_remaining) {
          minutes_multiplier = minutes_remaining;
        }
        total_costs += RATE_OF_ON_HOURS * minutes_multiplier;
        minutes_remaining -= minutes_multiplier;
        call_started = SIX_PM;
      }

      minutes_multiplier = TWENTY_FOUR_HOURS - call_started;
      if (minutes_multiplier > minutes_remaining) {
        minutes_multiplier = minutes_remaining;
      }
      total_costs += RATE_OF_OFF_HOURS * minutes_multiplier;

    } else {

      // Saturday to Sunday rate computation here
      total_costs += RATE_OF_WEEKENDS * remaining_minutes_for_the_day;

    }

    // Next day roll over
    call_started = 0;
    day_of_the_week = (day_of_the_week + 1) % 7;
    length_of_calls -= remaining_minutes_for_the_day;

  } while (length_of_calls > 0);

  return total_costs;
}

int main(void) {
  do {
    int day_of_the_week = get_day_of_the_week();
    int call_started = get_call_started();
    int length_of_calls = get_length_of_calls();
    cout  << "Total costs: "
          << get_total_costs(day_of_the_week, call_started, length_of_calls)
          << endl;
  } while (repeat());

  return 0;
}

/*
off hours =  0 to 8  = 0 to 479 minutes
on hours  =  8 to 18 = 480 to 1080 minutes
off hours = 18 to 24 = 1081 to 1440 minutes

  off       on            off   
0 - 479, 480 - 1080, 1081 - 1439

*/
