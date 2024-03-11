//******************
//
// basix_file.h
//
//******************
// Presentation :
//
// Basix is a little project containing base functions for Matix.
// It can also be use in any projects.
// This file contains some mathematical functions.
//

#ifndef BASIX_MATH
#define BASIX_MATH

// The namespace "basix" is used to simplify the all.
namespace basix
{
	// Apply the Paeth function to a left, above and upper left values
	inline float paeth_function(float left, float above, float upper_left)
	{
		float p = left + above - upper_left;
		float pa = abs(p - left);
		float pb = abs(p - above);
		float pc = abs(p - upper_left);
		if (pa <= pb && pa <= pc) return left;
		else if (pb <= pc) return above;
		else return upper_left;
	}

	// Normalize a value between "min" and "max" included
	inline double normalize_value(double number, double min, double max)
	{
		double to_add = (max - min) + 1;
		while (number < min) number += to_add;
		while (number > max) number -= to_add;
		return number;
	}

	// Return the size of a number
	inline int sign(float number) { return number < 0 ? -1 : (number == 0 ? 0 : 1); };
}

#endif
