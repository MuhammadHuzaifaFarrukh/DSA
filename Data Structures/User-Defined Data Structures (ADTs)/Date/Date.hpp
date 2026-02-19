#pragma once
#include <iostream>

using namespace std;

class Date
{
    int day, month, year;

public:
    Date() : day(0), month(0), year(0) {}
    void SetDay(int d)
    {
        if (d < 0 || d > 30)
        {
            cout << "Invalid Day" << endl;
        }
        else
        {
            day = d;
        }
    }
    void SetMonth(int m)
    {
        if (m < 0 || m > 12)
        {
            cout << "Invalid Month " << endl;
        }
        else
        {
            month = m;
        }
    }
    void SetYear(int y)
    {
        if (y < 0)
        {
            cout << "Invalid Year " << endl;
        }
        else
        {
            year = y;
        }
    }
    int getDay() const
    {
        return day;
    }
    int getMonth() const
    {
        return month;
    }
    int getYear() const
    {
        return year;
    }
    void displayDate()
    {
        cout << day << "/" << month << "/" << year << endl;
    }

    //Simpler Method
    //Convert all into days and decompress , back into original

    void addDays(int days)
    {
        if (days < 0)
        {
            cout << "Days cannot be negative " << endl;
            return;
        }

        // 1. Convert Y/M/D into one giant number of days
        // We use (month-1) and (day-1) to make the math 0-indexed.
        // This makes the modulo/division work perfectly.
        long totalDays = (long)this->year * 360 + (this->month - 1) * 30 + (this->day - 1);

        // 2. Add the new days
        totalDays += days;

        // 3. Extract Y/M/D back out
        this->year = totalDays / 360;                // How many full 360-day blocks
        this->month = ((totalDays % 360) / 30) + 1;  // Remainder days converted to 30-day blocks
        this->day = (totalDays % 30) + 1;            // Remaining days
    }

    //A bit Difficult Method for this :
//    void addDays(int days)
//    {
//        if (days < 0)
//        {
//            cout << "Days cannot be negative " << endl;
//            return ;
//        }
//
//        // 1. Add total days to current day
//        int total_days = this->day + days;
//
//        // 2. Calculate how many full months (30 days each) are in total_days
//        // Subtracting 1 before division and adding 1 after is a trick
//        // to handle the "day 30" case correctly so it doesn't become day 0.
//        if (total_days > 30)
//        {
//            int extra_months = (total_days-1) / 30; //Although total_days/30 is fine , due to the above condition for total_days>30 , however when total_days are 60 or more multiple of 30 then it will enter the loop and do logical error so we do (-1) for that check only
//            this->month += extra_months;
//            // (a-b)%n + b keeps the answer same but also handles the case for a%n == 0 so to keep the answer in the range from 1 to 30 we use this formula
//            // (a%30)+1 also keeps in range 1 to 30 but changes the answer everytime and fails to handle edge case as well
//            this->day = ((total_days - 1) % 30) + 1;    // (-1) and (+1) are done only to handle the day 0 , they won''t affect the answer
//        }
//        else
//        {
//            this->day = total_days;
//        }
//
//        // 3. Handle Year Overflow
//        if (this->month > 12)
//        {
//            //Same Logic for Year as for month
//            int extra_years = (this->month - 1) / 12;
//            this->year += extra_years;
//            this->month = ((this->month - 1) % 12) + 1;
//        }
//    }


    //Simpler method
    //Convert all into days then back again

    void subtractDays(int days)
    {
        if (days < 0)
        {
            cout<<"Days cannot be Negative "<<endl;
            return;
        }

        // 1. Convert everything to total days from "Year 0"
        // We use (month-1) and (day-1) to make it 0-indexed for clean math
        long totalDays = (long)this->year * 360 + (this->month - 1) * 30 + (this->day - 1);

        // 2. Subtract the days
        totalDays -= days;

        // Handle the case where the date goes before "Year 0" if necessary
        if (totalDays < 0)
        {
            cout << "Date out of range!" << endl;
            return;
        }

        // 3. Convert back to Y / M / D
        this->year = totalDays / 360;
        this->month = ((totalDays % 360) / 30) + 1; // +1 to return to 1-12
        this->day = (totalDays % 30) + 1;           // +1 to return to 1-30
    }

    //A bit Difficult Method for this :
//    void subtractDays(int days)
//    {
//        if (days < 0)
//        {
//            cout<<"Days cannot be Negative "<<endl;
//            return;
//        }
//
//        // 1. Calculate how many full months we are jumping back
//        // We use (days - day) to see how far past the current month's start we go
//        if (days >= this->day)
//        {
//            int monthsToSubtract = (days - this->day) / 30 + 1;
//            this->month -= monthsToSubtract;
//        }
//
//        // 2. The "Magic" Positive Modulo for Days
//        // We add a large multiple of 30 to ensure the result is positive
//        // before taking the modulo.
//        this->day = ((this->day - days - 1) % 30 + 30) % 30 + 1;
//
//        // 3. Subtract Years if month went to 0 or negative
//        if (this->month <= 0)
//        {
//            int yearsToSubtract = (abs(this->month) / 12) + 1;
//            this->year -= yearsToSubtract;
//            // Map month back to 1-12 range
//            this->month = (this->month % 12 + 12) % 12;
//            if (this->month == 0) this->month = 12;
//        }
//    }

};

//Shift of -1 and +1 actually helps as compiler handles edge cases of month/day zero or negative differently
//For actual date/month , we will not shift of -1 for that
//If this were a time(h,m,s) conversion program , we wouldn't do shift of -1 and +1 because time is naturally 0-based index
//For time , hours,minutes,seconds are actually 0-base indexed so no need to do shifting
