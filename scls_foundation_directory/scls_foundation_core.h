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

#include <algorithm>
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
namespace scls {
    //*********
	//
	// Debugging helper
	//
	//*********

	// Getters and setters of the debugging system
    std::vector<std::string>& authorized_sender();
	std::vector<std::string>& authorized_type();
	bool can_print();
    bool is_sender_authorized(std::string sender_to_test);
	bool is_type_authorized(std::string type_to_test);
	std::string sender_message_separation();
	void set_can_print(bool new_can_print);
	void set_sender_message_separation(std::string new_sender_message_separation);
    void set_type_sender_separation(std::string new_type_sender_separation);
    std::string type_sender_separation();

	// Print the message in the console, coming from "sender" of type "type".
	template <typename Type_To_Print = std::string>
	static void print(std::string type, std::string sender, Type_To_Print message) {if (can_print() && is_type_authorized(type) && is_sender_authorized(sender)) {std::cout << type << type_sender_separation() << sender << sender_message_separation() << message << std::endl;}};
	template <typename Type_To_Print = std::string>
	static void print(std::string sender, Type_To_Print message) {print<Type_To_Print>("SCLS Information", sender, message);};

    //*********
	//
	// Datas structures manipulation
	//
	//*********

	// Swap a char array
    void swap_char_array(char* array, unsigned int array_size);
}

#endif // SCLS_FOUNDATION_CORE
