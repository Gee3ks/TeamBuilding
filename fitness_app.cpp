// File Name: fitness_app.cpp
// Author: Group 1
// Final Project
// Description: Fitness App program
// Last Changed: December 14, 2023

#include <iostream>
#include <map>
#include <limits>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

// Function for calculating BMI
double compute_bmi(double weight, double height)
{
    return weight / (height * height);
}

// Generic function for gathering positive number inputs
double get_value(string message)
{
    double value;
    do
    {
        cout << message;
        cin >> value;
    } while (value <= 0);
    return value;
}

// Function to convert any string value to lowercase
void to_lower(string &strvar)
{
    for (char &c : strvar)
    {
        c = tolower(c);
    }
}

// Function for getting user string input with specific choices
string get_answer(string message, string choices, string answer = " ")
{
    while (choices.find(answer) == string::npos)
    {
        cout << message;
        cin >> answer;
        to_lower(answer);
    }
    return answer;
}

// Function to classify BMI based on predefined ranges
string bmi_classification(double bmi)
{
    // BMI classification ranges and labels
    map<double, string> adult_bmi = {
        {16, "Severe Thinness"},
        {17.0, "Moderate Thinness"},
        {18.5, "Mild Thinness"},
        {25.0, "Normal"},
        {30.0, "Overweight"},
        {35.0, "Obese Class I"},
        {40.0, "Obese Class II"},
        {999.9, "Obese Class III"},
    };

    // Return BMI classification based on the provided value
    return adult_bmi.upper_bound(bmi)->second;
}

// Function to calculate total calories from food choices
double food_calories(void)
{
    map<string, double> foods = {
        {"apple", 95.0},
        {"banana", 105.0},
        {"chicken breast", 165.0},
        {"salmon", 206.0},
        {"broccoli", 55.0},
    };

    cout << endl
         << "### Food Choices ###" << endl;
    double total_calories = 0.0;
    do
    {
        // Display food choices and gather user input
        cout << "Food to choice and it's calories: " << endl;
        for (auto food : foods)
        {
            cout << "\t" << food.first << " = " << food.second << endl;
        }
        string food_choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        do
        {
            cout << "Enter the name of your choice: ";
            getline(cin, food_choice);
            to_lower(food_choice);
        } while (not foods[food_choice]);
        double quantity = get_value("Enter quantity: ");
        total_calories = total_calories + foods[food_choice] * quantity;
        cout << "Running Total Calories: " << total_calories << endl;
    } while (get_answer("Do you want to add more food(y,n)?: ", "yn") == "y");

    return total_calories;
}

// Function to gather calories from non-workout activities
double non_workout_calories(void)
{
    cout << endl
         << "### Non Workout Activities ###" << endl;
    double total_calories = 0.0;
    do
    {
        // Gather non-workout activity details
        string activity;
        cout << "Enter non workout activity: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, activity);
        double calories_burn = get_value("Calories burned: ");
        total_calories = total_calories + calories_burn;
        cout << "Running Total Calories: " << total_calories << endl;
    } while (get_answer("Do you want to add more non workout activities(y,n)?: ", "yn") == "y");

    return total_calories;
}

// Function to gather calories from workout activities
double workout_calories(void)
{
    map<string, double> workouts = {
        {"pushups", 0.3},
        {"situps", 0.5},
        {"squats", 0.32},
        {"pullups", 1.0},
        {"chinups", 0.05},
    };

    cout << endl
         << "### Workout Activities ###" << endl;
    double total_calories = 0.0;
    do
    {
        // Display workout choices and gather user input
        cout << "Workouts to choice and it's calories: " << endl;
        for (auto workout : workouts)
        {
            cout << "\t" << workout.first << " = " << workout.second << endl;
        }
        string workout_choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        do
        {
            cout << "Enter the name of your choice: ";
            getline(cin, workout_choice);
            to_lower(workout_choice);
        } while (not workouts[workout_choice]);
        double reps = get_value("Enter number of reps: ");
        double sets = get_value("Enter number of sets: ");
        total_calories = total_calories + workouts[workout_choice] * reps * sets;
        cout << "Running Total Calories: " << total_calories << endl;
    } while (get_answer("Do you want to add more workouts(y,n)?: ", "yn") == "y");

    return total_calories;
}

// Function to get the date from the user
tm get_date(string message)
{
    tm date = {};
    cout << message;
    cin >> get_time(&date, "%m/%d/%Y");
    return date;
}

// Function to calculate end date based on start date and days
string end_date_str(tm &start_date, double days)
{
    time_t start_time = mktime(const_cast<tm *>(&start_date));
    start_time = start_time + static_cast<long long>(days * 24 * 60 * 60);
    tm end_date = *localtime(&start_time);
    stringstream formatted_date;
    formatted_date << setfill('0') << setw(2) << end_date.tm_mon + 1 << "/"
                   << setfill('0') << setw(2) << end_date.tm_mday << "/"
                   << end_date.tm_year + 1900;

    return formatted_date.str();
}

// Main function
int main(void)
{
    // Gather initial user information
    double current_weight = get_value("Enter current weight (kg): ");
    double current_height = get_value("Enter current height (m): ");
    double bmi = compute_bmi(current_weight, current_height);
    string classification = bmi_classification(bmi);

    // Gather calories information
    double total_food_calories = food_calories();
    double total_non_workout_calories = non_workout_calories();
    double total_workout_calories = workout_calories();
    double calories_per_day = total_food_calories - total_non_workout_calories - total_workout_calories;

    // Constants
    const double calories_per_kg = 7700.0;

    // Display summary
    cout << endl
         << "### SUMMARY ###" << endl;
    cout << "Number Of Calories Per Kilogram: " << calories_per_kg << endl;
    cout << "Current Weight: " << current_weight << endl;
    cout << "Current Height: " << current_height << endl;
    cout << "Body Mass Index: " << bmi << endl;
    cout << "Classification: " << classification << endl;
    cout << "Total Food Calories: " << total_food_calories << endl;
    cout << "Total Non Workout Calories: " << total_non_workout_calories << endl;
    cout << "Total Workout Calories: " << total_workout_calories << endl;
    cout << "Consumed Calories Per Day : " << calories_per_day << endl;

    // Gather additional user information
    double desired_weight = get_value("Enter desired weight (kg): ");
    tm start_date = get_date("Enter start date (mm/dd/yyyy): ");

    // Display analysis based on desired weight and calories
    cout << endl
         << "### Analysis ###" << endl;
    if (desired_weight > current_weight)
    {
        if (calories_per_day > 0)
        {
            double days_to_achieve = (desired_weight - current_weight) * calories_per_kg / calories_per_day;
            cout << "Desired gaining weight is achievable in " << days_to_achieve << " day(s)\n";
            cout << "End date is " << end_date_str(start_date, days_to_achieve) << endl;
        }
        else
        {
            cout << "Desired gaining weight is not achievable based on calories consumed per day\n";
        }
    }
    else if (desired_weight < current_weight)
    {
        if (calories_per_day < 0)
        {
            double days_to_achieve = (desired_weight - current_weight) * calories_per_kg / calories_per_day;
            cout << "Desired losing weight is achievable in " << days_to_achieve << " days\n";
            cout << "End date is " << end_date_str(start_date, days_to_achieve) << endl;
        }
        else
        {
            cout << "Desired losing weight is not achievable based on calories consumed per day\n";
        }
    }
    else
    {
        cout << "Desired weight is equal to current weight\n";
    }

    return 0;
}
