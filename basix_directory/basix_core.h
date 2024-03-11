//******************
//
// basix_core.h
//
//******************
// Presentation :
//
// Basix is a little project containing base functions for Matix.
// It can also be use in any projects.
// This file contains the core of the library.
//

#ifndef BASIX_CORE
#define BASIX_CORE

#include <iostream>
#include <math.h>
#include <string>
#include <vector>

// The namespace "basix" is used to simplify the all.
namespace basix
{
	// Static bool, usefull in debugging to tell to Basix if the "print" function works or not
	static bool _can_print = true;

	// Return the value of "_can_print".
	inline bool can_print() { return _can_print; };

	// Change the value of the static "_can_print" function.
	inline void set_can_print(bool can_print) { _can_print = can_print; };

	// Print the "message" something in the console, coming from "sender" of type "type".
	inline void print(std::string type, std::string sender, std::string message)
	{
		if (can_print())
		{
			std::cout << message << std::endl;
		}
	};
}

#endif
