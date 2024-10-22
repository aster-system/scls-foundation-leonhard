//******************
//
// scls_foundation_math.h
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
// This file contains some mathematical functions.
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

#ifndef SCLS_FOUNDATION_MATH
#define SCLS_FOUNDATION_MATH

#include "scls_foundation_string.h"

#ifndef SCLS_PI
#define SCLS_PI 3.1415926535
#endif // SCLS_PI
#ifndef SCLS_HALP_PI
#define SCLS_HALF_PI 1.5707963267948966
#endif // SCLS_HALP_PI

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// Mathematical functions
	//
	//*********

	// Partitions a number and return each numbers of the partition
	inline std::vector<long long> partition_number(long long number_to_partition, long long number_of_partitions) {
	    std::vector<long long> to_return = std::vector<long long>();

	    // Format the datas as needed
	    if(number_of_partitions == 0) return to_return;
	    char sign = 1;
	    if(number_of_partitions < 0) sign *= -1;
	    number_of_partitions = abs(number_of_partitions);

	    // Calculate the main value to add at each iteration
        long long round_partition_size = static_cast<long long>(static_cast<double>(number_to_partition) / static_cast<double>(number_of_partitions));
        long long rest = number_to_partition % number_of_partitions;

        // Calculate the rest to add at each iterations
        long long rest_to_add = static_cast<long long>(static_cast<double>(rest) / static_cast<double>(number_of_partitions));
        long long rest_of_rest = rest % number_of_partitions;

        // Calculate the rest of the rest to add at each iterations
        double rest_of_rest_to_add = 0;
        if(rest_of_rest != 0) rest_of_rest_to_add = static_cast<double>(number_of_partitions) / static_cast<double>(rest_of_rest);

        // Create the partition
        double current_rest_of_rest = static_cast<double>(rest_of_rest_to_add) / 2.0;
        unsigned int current_rest_added = 0;
        for(long long i = 0;i<number_of_partitions;i++) {
            long long to_add = 0;
            if(rest_of_rest_to_add != 0 && current_rest_of_rest >= rest_of_rest_to_add && current_rest_added < rest_of_rest) {
                to_add++;
                current_rest_added++;
                current_rest_of_rest -= rest_of_rest_to_add;
            }
            current_rest_of_rest++;
            to_return.push_back((round_partition_size + rest_to_add + to_add) * sign);
        }
        return to_return;
	};

	// Apply the Paeth function to a left, above and upper left values
	inline double paeth_function(double left, double above, double upper_left) {
		double p = left + above - upper_left;
		double pa = abs(p - left);
		double pb = abs(p - above);
		double pc = abs(p - upper_left);
		if (pa <= pb && pa <= pc) return left;
		else if (pb <= pc) return above;
		return upper_left;
	}

	//*********
	//
	// Get mathematicals datas
	//
	//*********

	// Normalize a value between "min" and "max" included
	inline double normalize_value(double number, double min, double max) { if(max == min) return 0; else if(max < min) std::swap(min, max); double t = (max - min) + 1; while (number < min) number += t; while (number > max) number -= t; return number; }

	// Return the size of a number
	inline int sign(double number) { return number < 0 ? -1 : (number == 0 ? 0 : 1); };
}

#endif // SCLS_FOUNDATION_MATH
