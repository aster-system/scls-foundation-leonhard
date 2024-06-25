//******************
//
// scls_foundation_core.h
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
// This file contains the core of the library.
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

#ifndef SCLS_FOUNDATION_CORE
#define SCLS_FOUNDATION_CORE

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
#include <stack>
#include <string>
#include <sys/time.h>
#include <vector>

#if defined(__WIN32__) || defined(__WIN64__)
#include <windows.h>
#endif // defined

// The namespace "scls" is used to simplify the all.
namespace scls
{
    //*********
	//
	// Debugging helper
	//
	//*********

	// Static vector of each authorized sender to be printed
	static std::vector<std::string> _authorized_sender = std::vector<std::string>();
	// Static vector of each authorized type to be printed
	static std::vector<std::string> _authorized_type = std::vector<std::string>();

	// Static bool, usefull in debugging to tell to SCLS if the "print" function is enable or not
	static bool _can_print = true;

	// Static string, separation between the sender and the message in the "print" function
	static std::string _sender_message_separation = " : ";
	// Static string, separation between the type and the sender in the "print" function
	static std::string _type_sender_separation = " -> ";

	// Return a reference to "_authorized_sender"
	inline std::vector<std::string>& authorized_sender() {return _authorized_sender;};

	// Return a reference to "_authorized_type"
	inline std::vector<std::string>& authorized_type() {return _authorized_type;};

	// Return the value of "_can_print".
	inline bool can_print() { return _can_print; };

	// Returns if a sender is authorized or not
	inline bool is_sender_authorized(std::string sender_to_test) {
        if(authorized_sender().size() == 0) return true;

        for(int i = 0;i<static_cast<int>(authorized_sender().size());i++) {
            if(authorized_sender()[i] == sender_to_test) return true;
        }
        return false;
	}

	// Returns if a type is authorized or not
	inline bool is_type_authorized(std::string type_to_test) {
        if(authorized_type().size() == 0) return true;

        for(int i = 0;i<static_cast<int>(authorized_type().size());i++) {
            if(authorized_type()[i] == type_to_test) return true;
        }
        return false;
	}

	// Return the value of "_sender_message_separation"
	inline std::string sender_message_separation () {return _sender_message_separation;};

	// Change the value of the static "_can_print" variable.
	inline void set_can_print(bool new_can_print) { _can_print = new_can_print; };

	// Change the value of the static "_sender_message_separation" variable.
	inline void set_sender_message_separation(std::string new_sender_message_separation) { _sender_message_separation = new_sender_message_separation; };

	// Change the value of the static "_type_sender_separation" variable.
	inline void set_type_sender_separation(std::string new_type_sender_separation) { _type_sender_separation = new_type_sender_separation; };

	// Return the value of "_type_sender_separation"
	inline std::string type_sender_separation () {return _type_sender_separation;};

	// Print the message in the console, coming from "sender" of type "type".
	template <typename Type_To_Print = std::string>
	inline void print(std::string type, std::string sender, Type_To_Print message) {
		if (can_print() && is_type_authorized(type) && is_sender_authorized(sender))
		{
			std::cout << type << _type_sender_separation << sender << _sender_message_separation << message << std::endl;
		}
	};

	//*********
	//
	// Datas structures manipulation
	//
	//*********

	// Return if a vector contains an element
	template<typename T>
	inline bool contains(std::vector<T> vec, T element) {
		for (int i = 0; i < static_cast<int>(vec.size()); i++) // Browse the vector element by element
		{
			if (vec[i] == element) return true; // If the vector contains the element, return true
		}
	    return false;
	};

	// Return the number occurrence of an element in a std::vector
	template<typename T>
	inline unsigned int count(std::vector<T> vec, T element) {
	    unsigned int occurrence = 0;
		for (int i = 0; i < static_cast<int>(vec.size()); i++) // Browse the vector element by element
		{
			if (vec[i] == element) occurrence++; // If the vector contains the element, add an occurrence
		}
	    return occurrence;
	};

	// Swap a char array
	inline void swap_char_array(char* array, unsigned int size) {
		for (int i = 0; i < floor(size / 2.0); i++)
		{
			char temp = array[i];
			array[i] = array[size - (i + 1)];
			array[size - (i + 1)] = temp;
		}
	};

	// Swap a vector
	template<typename T>
	inline std::vector<T> swap_vector(std::vector<T> v) {
	    for (int i = 0; i < floor((float)v.size() / 2.0); i++)
		{
			T temp = v[i];
			v[i] = v[v.size() - (i + 1)];
			v[v.size() - (i + 1)] = temp;
		}
		return v;
	};

	//*********
	//
	// Time handling
	//
	//*********

	// Returns the number of milliseconds since a long date
	inline long long time_ns() {
	    timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        return static_cast<long long>(ts.tv_nsec) + static_cast<long long>(ts.tv_sec) * 1000000000;
	};
}

#endif // SCLS_FOUNDATION_CORE
