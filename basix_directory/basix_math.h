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

#pragma once

// The namespace "basix" is used to simplify the all.
namespace basix
{
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