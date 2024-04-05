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

// The namespace "scls" is used to simplify the all.
namespace scls
{
    //*********
	//
	// Mathematical functions
	//
	//*********

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
