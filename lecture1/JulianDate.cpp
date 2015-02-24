// Convert a Julian day in a given year to the associated month and day.
#include <iostream>
const int DaysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// Function prototypes.  In general, if function A calls function B, function B
// must be defined "before" A or function B's prototype must be specified before A.
void month_and_day(int julian_day, int year, int & month, int & day);
void output_month_name(int month);

int main() {    // The main function handles the I/O.
    int julian, year, month, day_in_month;
    std::cout << "Please enter two integers giving the Julian date and the year: ";
    std::cin >> julian >> year;
    month_and_day(julian, year, month, day_in_month);
    std::cout << "The date is ";
    output_month_name(month);
    std::cout << " " << day_in_month << ", " << year << std::endl;
    return 0;
}

// Function returns true if the given year is a leap year and returns false otherwise.
bool is_leap_year(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

// Compute the month and day corresponding to the Julian day within the given year.
void month_and_day(int julian_day, int year, int &month, int &day) {
    bool month_found = false;
    month = 1;
    // Subtracting the days in each month from the Julian day, until the
    // remaining days is less than or equal to the total days in the month.
    while (!month_found) {
        int days_this_month = DaysInMonth[month];
        if (month == 2 && is_leap_year(year))  // Add one if it is a leap year.
            ++days_this_month;
        if (julian_day <= days_this_month)
            month_found = true;   // Done!
        else {
            julian_day -= days_this_month;
            ++month; 
        }
    }
    day = julian_day;
}

void output_month_name(int month) { // Output a string giving the name of the month.
    switch (month) {
        case 1: std::cout << "January"; break;
        case 2: std::cout << "February"; break;
        case 3: std::cout << "March"; break;
        case 4: std::cout << "April"; break;
        case 5: std::cout << "May"; break;
        case 6: std::cout << "June"; break;
        case 7: std::cout << "July"; break;
        case 8: std::cout << "August"; break;
        case 9: std::cout << "September"; break;
        case 10: std::cout << "October"; break;
        case 11: std::cout << "November"; break;
        case 12: std::cout << "December"; break;
        default: std::cout << "Illegal month";
    };
}
