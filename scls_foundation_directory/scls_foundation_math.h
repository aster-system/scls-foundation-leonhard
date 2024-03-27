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
	inline double normalize_value(double number, double min, double max) { if(max == min) return 0; else if(max < min) std::swap(min, max); double t = (max - min); while (number < min) number += t; while (number >= max) number -= t; return number; }

	// Return the size of a number
	inline int sign(double number) { return number < 0 ? -1 : (number == 0 ? 0 : 1); };
}

#endif // SCLS_FOUNDATION_MATH
