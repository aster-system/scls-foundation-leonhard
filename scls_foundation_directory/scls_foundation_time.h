//******************
//
// scls_foundation_time.h
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
// This file allows some complex manipulations with time and dates.
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

#ifndef SCLS_FOUNDATION_TIME
#define SCLS_FOUNDATION_TIME

#include "scls_foundation_core.h"

#define SCLS_SECONDS_IN_DAY 86400
#define SCLS_SECONDS_IN_YEAR 31536000

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// The Date class
	//
	//*********

	// Duration of each month
	extern int month_duration[];

    // Returns the number of milliseconds since a long date
    long long time_ns();

    // Conversion of times to other
    long long second_since_1970_at_time_in_year(long long year);
    long long second_since_start_year_at_month(int month);

    // Returns the number of weeks in a month
    int weeks_in_month(int year, int month);

    class Date {
    public:
        // Date constructor
        Date();
        Date(int year, int month);
        Date(int year, int month, int day);
        Date(const Date& date_copy);

        // Adds days to the date
        void add_days(long long days);

        // Day / month / year of the date
        int day();
        int month();
        int year();

        // Returns the number of second since the start of the year
        long long number_of_second_since_start_of_year();

        // Returns the date to an std::string
        std::string to_std_string();

        // Week position of the date
        int week_position();

        // Getters and setters
        inline long long seconds_since_1970() const {return a_time;};
    private:
        // Nanosecondes since 1970
        long long a_time;
    };

    // Operators
    bool operator<(Date date_1, Date date_2);

    // Returns the date of easter at year
    Date ascension_date_at_year(int year);
	Date easter_date_at_year(int year);
	Date pentecost_date_at_year(int year);

    // Returns the last day of a month
    Date last_day_of_month(int year, int month);
}

#endif // SCLS_FOUNDATION_TIME
