//  This program converts a day and month within a given year to the
//  Julian day.

#include <iostream>


//  This is a constant array of integer values.  The array entry
//  associated with index i is the number of days in the ith month of
//  the year.  Since C++ array indices start at 0 and month counting
//  starts at 1, there are 13 locations in the array, and the
//  first location is given a default value of 0.
const int DaysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 
    31, 31, 30, 31, 30, 31 };


//  Function returns true if the given year is a leap year and
//  returns false otherwise.
bool is_leap_year( int year )
{
    return year % 4 == 0 && ( year % 100 != 0 || year % 400 == 0 );
}


//  Calculate and return the Julian day associated with the given
//  month and day of the year.
int julian_day( int month, int day, int year )
{
    int jday = 0;
    for ( unsigned int m=1; m<month; ++m )
    {
        jday += DaysInMonth[m];
        if ( m == 2 && is_leap_year(year)) ++jday;  // February 29th
    }
    jday += day;
    return jday;
}

bool check( int month, int day, int year){
    if(month < 1 || month > 12)   // check month
        return false;
    // else if (month == 2 && !is_leap_year(year) && day = 28) // check February 29 
        
    else if (day > DaysInMonth[month]) // check days
        return false;
    else return true;
}

int main()
{
    std::cout << "Please enter three integers (a month, a day and a year): ";
    int month, day, year;
    std::cin >> month >> day >> year;
    if(check(month, day, year)){
        std::cout << "That is Julian day " << julian_day( month, day, year ) << std::endl;
    }
    else{
        std::string fal1;
        int fal2;
        if(month < 1 || month > 12){
            fal1 = "month";
            fal2 = month;
        }
        else if (day > DaysInMonth[month]){
            fal1 = "day";
            fal2 = day;
        }
        std::cout << "ERROR bad " << fal1 << ": " << fal2 << std::endl;
    }
    return 0;
}

