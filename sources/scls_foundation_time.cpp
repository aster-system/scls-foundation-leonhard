//******************
//
// scls_foundation_time.cpp
//
//******************
// Presentation :
//
// SCLS is a project containing base functions for C++.
// It can also be use in any projects.
//
// The Foundation "Leonhard" part represents the foundation of SCLS.
// It is named after the "Father of modern mathematics", Leonhard Euler.
//
// This file contains the source code of "scls_foundation_time.h".
//
//******************
//
// License (LGPL V3.0) :
//
// Copyright (C) 2024 by Aster System, Inc. <https://aster-system.github.io/aster-system/>
// This file is part of SCLS.
// SCLS is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// SCLS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with SCLS. If not, see <https://www.gnu.org/licenses/>.
//

#include "../scls_foundation_directory/scls_foundation_time.h"

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// The Date class
	//
	//*********

    // Returns the number of milliseconds since a long date
    long long time_ns() {timespec ts;clock_gettime(CLOCK_REALTIME, &ts);return static_cast<long long>(ts.tv_nsec) + static_cast<long long>(ts.tv_sec) * 1000000000;};

    // Returns if a year is bissextile or not
    bool year_is_bissextile(long long year){return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;};

    // Conversion of times to other
    int month_duration[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    long long second_since_1970_at_time_in_year(long long year){
        long long diff_year = std::abs(year - 1970);
        long long bissextile = 1;long long bissextile_100 = 70;long long bissextile_400 = 370;long long multiplier = 1;
        if(year < 1970){multiplier = -1;bissextile=2;bissextile_100=30;bissextile_400=30;};
        return ((diff_year * 365 + (diff_year + bissextile) / 4 + (diff_year + bissextile_400) / 400 - (diff_year + bissextile_100) / 100) * SCLS_SECONDS_IN_DAY) * multiplier;
    }
    long long second_since_start_year_at_month(int year, int month){int result=0;for(int i = 0;i<month;i++){result+=month_duration[i];}if(year_is_bissextile(year)&&month>1){result++;}return result * SCLS_SECONDS_IN_DAY;}

    // Returns the number of weeks in a month
    int weeks_in_month(int year, int month){int day = Date(year, month).week_position() + month_duration[month];return std::ceil(day / 7);}

    // Date constructor
    Date::Date(){};
    Date::Date(int year, int month):a_time(second_since_1970_at_time_in_year(year) + second_since_start_year_at_month(year, month)){};
    Date::Date(int year, int month, int day):a_time(second_since_1970_at_time_in_year(year) + second_since_start_year_at_month(year, month) + day * SCLS_SECONDS_IN_DAY){};
    Date::Date(const Date& date_copy):a_time(date_copy.a_time){}

    // Adds days to the date
    void Date::add_days(long long days){a_time += days * SCLS_SECONDS_IN_DAY;}

    // Returns the date to an std::string
    std::string Date::to_std_string(){return std::to_string(day()) + std::string("/") + std::to_string(month()) + std::string("/") + std::to_string(year());};

    // Month / year of the date
    int Date::day(){
        long long needed_time = number_of_second_since_start_of_year();
        for(int i = 0;i<12;i++){
            long long current_month_duration = month_duration[i];if(i == 1 && year_is_bissextile(year())){current_month_duration++;}
            if(needed_time < current_month_duration * SCLS_SECONDS_IN_DAY){break;}
            needed_time -= current_month_duration * SCLS_SECONDS_IN_DAY;
        }
        return needed_time / SCLS_SECONDS_IN_DAY;
    }
    int Date::month(){
        int current_month = 0;long long needed_time = number_of_second_since_start_of_year();
        for(;current_month<12;current_month++){
            int current_month_duration = month_duration[current_month];if(current_month == 1 && year_is_bissextile(year())){current_month_duration++;}
            if(needed_time < current_month_duration * SCLS_SECONDS_IN_DAY){break;}
            needed_time -= current_month_duration * SCLS_SECONDS_IN_DAY;
        }
        return current_month;
    }
    int Date::year(){
        if(a_time >= 0) {
            long long needed_time = a_time;int needed_year = 0;
            for(int i = 1970;i<10000;i++){
                long long needed_duration = 365 * SCLS_SECONDS_IN_DAY;if(year_is_bissextile(i)){needed_duration+=SCLS_SECONDS_IN_DAY;}
                if(needed_time < needed_duration){break;}
                needed_year++;needed_time-=needed_duration;
            }
            return 1970 + needed_year;
        }

        long long needed_time = a_time;int needed_year = 0;
        for(int i = 1970;i>=0;i--){
            long long needed_duration = 365 * SCLS_SECONDS_IN_DAY;if(year_is_bissextile(i)){needed_duration+=SCLS_SECONDS_IN_DAY;}
            if(needed_time < needed_duration){break;}
            needed_year++;needed_time+=needed_duration;
        }
        return 1970 - needed_year;
    }

    // Returns the number of second since the start of the year
    long long Date::number_of_second_since_start_of_year() {
        if(a_time >= 0) {
            long long needed_time = a_time;
            for(int i = 1970;i<10000;i++){
                long long needed_duration = 365 * SCLS_SECONDS_IN_DAY;if(year_is_bissextile(i)){needed_duration+=SCLS_SECONDS_IN_DAY;}
                if(needed_time < needed_duration){break;}
                needed_time-=needed_duration;
            }
            return needed_time;
        }

        long long needed_time = a_time;
        for(int i = year();i<1970;i++){
            long long needed_duration = 365 * SCLS_SECONDS_IN_DAY;if(year_is_bissextile(i)){needed_duration+=SCLS_SECONDS_IN_DAY;}
            if(needed_time < needed_duration){break;}
            needed_time+=needed_duration;
        }
        return needed_time;
    }

    // Week position of the date
    int Date::week_position(){if(a_time < 0){return 7 + (a_time / SCLS_SECONDS_IN_DAY + 3) % 7;}return (a_time / SCLS_SECONDS_IN_DAY + 3) % 7;}

    // Operators
    bool operator<(Date date_1, Date date_2){return date_1.seconds_since_1970() < date_2.seconds_since_1970(); }

    // Returns the date of easter at year
    Date ascension_date_at_year(int year){Date needed_date = easter_date_at_year(year);needed_date.add_days(39);return needed_date;}
    Date pentecost_date_at_year(int year){Date needed_date = easter_date_at_year(year);needed_date.add_days(49);return needed_date;}
	Date easter_date_at_year(int year) {
	    int n = year % 19;int c = year / 100;int u = year % 100;
	    int s = c / 4;int t = c % 4;int p = (c + 8) / 25;int q = (c - p + 1) / 3;
        int e = (19 * n + c - s - q + 15) % 30;int b = u / 4;int d = u % 4;
        int l = (2 * t + 2 * b - e - d + 32) % 7;int h = (n + 11 * e + 22 * l) / 451;
        int m = (e + l - 7 * h + 114) / 31;int j = (e + l - 7 * h + 114) % 31;
        if(m == 3){return Date(year, 2, j + 1);}return Date(year, 3, j + 1);
	}

    // Returns the last day of a month
    Date last_day_of_month(int year, int month){return Date(year, month, month_duration[month] - 1);}
}
