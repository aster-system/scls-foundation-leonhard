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
// This file make the use of string simplier.
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

#ifndef SCLS_FOUNDATION_STRING
#define SCLS_FOUNDATION_STRING

// Define the end of a balise
#ifndef SCLS_BALISE_END
#define SCLS_BALISE_END '>'
#endif // SCLS_BALISE_END
// Define the end of a balise in a char array
#ifndef SCLS_BALISE_END_CHAR_ARRAY
#define SCLS_BALISE_END_CHAR_ARRAY ">"
#endif // SCLS_BALISE_END_CHAR_ARRAY
// Define the end of a balise in HTML in a char array
#ifndef SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY
#define SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY "&gt;"
#endif // SCLS_BALISE_END_PLAIN_TEXT_CHAR_ARRAY
// Define the end of a balise in HTML in a std::string
#ifndef SCLS_BALISE_END_PLAIN_TEXT_STD_STRING
#define SCLS_BALISE_END_PLAIN_TEXT_STD_STRING std::string("&gt;")
#endif // SCLS_BALISE_END_PLAIN_TEXT_STD_STRING
// Define the end of a balise in a std::string
#ifndef SCLS_BALISE_END_STD_STRING
#define SCLS_BALISE_END_STD_STRING std::string(">")
#endif // SCLS_BALISE_END_STD_STRING
// Define the start of a balise
#ifndef SCLS_BALISE_START
#define SCLS_BALISE_START '<'
#endif // SCLS_BALISE_START
// Define the start of a balise in a char array
#ifndef SCLS_BALISE_START_CHAR_ARRAY
#define SCLS_BALISE_START_CHAR_ARRAY "<"
#endif // SCLS_BALISE_START_CHAR_ARRAY
// Define the start of a balise in HTML in a char array
#ifndef SCLS_BALISE_START_PLAIN_TEXT_CHAR_ARRAY
#define SCLS_BALISE_START_PLAIN_TEXT_CHAR_ARRAY "&lt;"
#endif // SCLS_BALISE_START_PLAIN_TEXT_CHAR_ARRAY
// Define the start of a balise in HTML in a std::string
#ifndef SCLS_BALISE_START_PLAIN_TEXT_STD_STRING
#define SCLS_BALISE_START_PLAIN_TEXT_STD_STRING std::string("&lt;")
#endif // SCLS_BALISE_START_PLAIN_TEXT_STD_STRING
// Define the start of a balise in a std::string
#ifndef SCLS_BALISE_START_STD_STRING
#define SCLS_BALISE_START_STD_STRING std::string("<")
#endif // SCLS_BALISE_START_STD_STRING

#include "scls_foundation_binary.h"

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// std::string manipulation
	//
	//*********

	// Variables used to define a float separation character
	static std::string _float_character = "";
	static std::string _non_float_character = "";

	// Test and choose the separation character in a double
	inline void _test_separation_character() {
	    _float_character = ".";
        _non_float_character = ",";
        if (std::stod("0.25") != 0.25) // Test if the "." is the separation character
        {
            _float_character = ",";
            _non_float_character = ".";
        }
	};

	// Convert a char array to a string and return it
	inline std::string char_array_to_string(const char* c_a, unsigned int c_a_size) {
        std::string result = "";
        for(unsigned int i = 0;i<c_a_size;i++) {
            result += c_a[i];
        }
        return result;
	}

	// Return if a string contains an another string
	inline bool contains_string(std::string str, std::string part) {
	    std::string last_string = ""; // String since the last cut
		for (int i = 0; i < static_cast<int>(str.size()); i++) // Browse the string char by char
		{
			last_string += str[i];
			if (last_string.size() > part.size()) // If the string which allows to know where to cut is too long, cut him
			{
				last_string = last_string.substr(1, part.size());
			}

			if (last_string == part) // If the string which allows to know where to find the equality is true, return true
			{
				return true;
			}
		}
	    return false;
	};

	// Returns if a string contains an another string out of a string
    inline bool contains_string(std::string str, std::string part, std::string out_of) {
        // If the loop is out of the string or not
	    bool in_out_of = false;
	    // Last sequence of string for check with part
	    std::string last_string = "";
	    // Last sequence of string for check with out offset
	    std::string last_string_out_of_offset = "";
		for (int i = 0; i < static_cast<int>(str.size()); i++) // Browse the string char by char
		{
		    // Check the last string with out of offset start
		    last_string_out_of_offset += str[i];
		    if(last_string_out_of_offset.size() > out_of.size()) {
                last_string_out_of_offset = last_string_out_of_offset.substr(last_string_out_of_offset.size() - out_of.size(), out_of.size());
		    }

		    // Check the last string
		    last_string += str[i];
			if (last_string.size() > part.size())
			{
				last_string = last_string.substr(last_string.size() - part.size(), part.size());
			}

			if(last_string_out_of_offset == out_of) {
                last_string = "";
                last_string_out_of_offset = "";
                in_out_of = !in_out_of;
			}

			if (last_string == part && !in_out_of) // If the string which allows to know where to find the equality is true, return true
			{
				return true;
			}
		}
	    return false;
	};

	// Returns if a string contains an another string out of 2 different string
    inline bool contains_string(std::string str, std::string part, std::string out_of_start, std::string out_of_end) {
	    // If the loop is out of the string or not
	    int in_out_of = 0;
	    // Last sequence of string for check with part
	    std::string last_string = "";
	    // Last sequence of string for check with out offset end
	    std::string last_string_out_of_offset_e = "";
	    // Last sequence of string for check with out offset start
	    std::string last_string_out_of_offset_s = "";
		for (int i = 0; i < static_cast<int>(str.size()); i++) { // Browse the string char by char
            // Check the last string with out of offset start
		    last_string_out_of_offset_e += str[i];
		    if(last_string_out_of_offset_e.size() > out_of_end.size()) {
                last_string_out_of_offset_e = last_string_out_of_offset_e.substr(last_string_out_of_offset_e.size() - out_of_end.size(), out_of_end.size());
		    }
		    // Check the last string with out of offset start
		    last_string_out_of_offset_s += str[i];
		    if(last_string_out_of_offset_s.size() > out_of_start.size()) {
                last_string_out_of_offset_s = last_string_out_of_offset_s.substr(last_string_out_of_offset_s.size() - out_of_start.size(), out_of_start.size());
		    }

		    // Check the last string
		    last_string += str[i];
			if (last_string.size() > part.size()) {
				last_string = last_string.substr(last_string.size() - part.size(), part.size());
			}

			if(last_string_out_of_offset_s == out_of_start) {
                last_string = "";
                last_string_out_of_offset_e = "";
                last_string_out_of_offset_s = "";
                in_out_of++;
			}
			else if(last_string_out_of_offset_e == out_of_end) {
			    last_string = "";
			    last_string_out_of_offset_e = "";
			    last_string_out_of_offset_s = "";
                if(in_out_of > 0) in_out_of--;
			}

			if (last_string == part && in_out_of == 0) // If the string which allows to know where to find the equality is true, return true
			{
				return true;
			}
		}
	    return false;
	};

	// Returns the number occurrence of a string in an another string
	inline unsigned int count_string(std::string str, std::string part) {
	    std::string last_string = ""; // String since the last cut
	    unsigned int occurence = 0;
		for (int i = 0; i < static_cast<int>(str.size()); i++) { // Browse the string char by char
			last_string += str[i];
			if (last_string.size() > part.size()) // If the string which allows to know where to cut is too long, cut him
			{
				last_string = last_string.substr(1, part.size());
			}

			if (last_string == part) // If the string which allows to know where to find the equality is true, return true
			{
			    last_string = "";
				occurence++;
			}
		}
	    return occurence;
	};

	// Returns the number occurrence of a string in an another string out of a string
	inline unsigned int count_string(std::string str, std::string part, std::string out_of) {
	    // If the loop is out of the string or not
	    bool in_out_of = false;
	    // Last sequence of string for check with part
	    std::string last_string = "";
	    // Last sequence of string for check with out offset
	    std::string last_string_out_of_offset = "";
	    unsigned int occurence = 0;
		for (int i = 0; i < static_cast<int>(str.size()); i++) { // Browse the string char by char
            // Check the last string with out of offset start
		    last_string_out_of_offset += str[i];
		    if(last_string_out_of_offset.size() > out_of.size()) {
                last_string_out_of_offset = last_string_out_of_offset.substr(last_string_out_of_offset.size() - out_of.size(), out_of.size());
		    }

			last_string += str[i];
			if (last_string.size() > part.size()) // If the string which allows to know where to cut is too long, cut him
			{
				last_string = last_string.substr(1, part.size());
			}

            if(last_string_out_of_offset == out_of) {
                last_string = "";
                last_string_out_of_offset = "";
                in_out_of = !in_out_of;
			}

			if (last_string == part && !in_out_of) // If the string which allows to know where to find the equality is true, return true
			{
			    last_string = "";
				occurence++;
			}
		}
	    return occurence;
	};

	// Returns the number occurrence of a string in an another string out of 2 different string
	inline unsigned int count_string(std::string str, std::string part, std::string out_of_start, std::string out_of_end) {
	    // If the loop is out of the string or not
	    int in_out_of = 0;
	    // Last sequence of string for check with part
	    std::string last_string = "";
	    // Last sequence of string for check with out offset end
	    std::string last_string_out_of_offset_e = "";
	    // Last sequence of string for check with out offset start
	    std::string last_string_out_of_offset_s = "";
	    unsigned int occurence = 0;
		for (int i = 0; i < static_cast<int>(str.size()); i++) { // Browse the string char by char
            // Check the last string with out of offset start
		    last_string_out_of_offset_e += str[i];
		    if(last_string_out_of_offset_e.size() > out_of_end.size()) {
                last_string_out_of_offset_e = last_string_out_of_offset_e.substr(last_string_out_of_offset_e.size() - out_of_end.size(), out_of_end.size());
		    }
		    // Check the last string with out of offset start
		    last_string_out_of_offset_s += str[i];
		    if(last_string_out_of_offset_s.size() > out_of_start.size()) {
                last_string_out_of_offset_s = last_string_out_of_offset_s.substr(last_string_out_of_offset_s.size() - out_of_start.size(), out_of_start.size());
		    }

			last_string += str[i];
			if (last_string.size() > part.size()) // If the string which allows to know where to cut is too long, cut him
			{
				last_string = last_string.substr(1, part.size());
			}

            if(last_string_out_of_offset_s == out_of_start) {
                last_string = "";
                last_string_out_of_offset_e = "";
                last_string_out_of_offset_s = "";
                in_out_of++;
			}
			else if(last_string_out_of_offset_e == out_of_end) {
			    last_string = "";
			    last_string_out_of_offset_e = "";
			    last_string_out_of_offset_s = "";
                if(in_out_of > 0) in_out_of--;
			}

			if (last_string == part && in_out_of == 0) // If the string which allows to know where to find the equality is true, return true
			{
			    last_string = "";
				occurence++;
			}
		}
	    return occurence;
	};

	// Cut a string in a vector where there are the "cut" part
	inline std::vector<std::string> cut_string(std::string string, std::string cut, bool erase_blank = false, bool erase_last_if_blank = true) {
		std::string last_string = ""; // String since the last cut
		std::string last_string_cut = ""; // String of the "cut" size which allows to know where to cut
		std::vector<std::string> result = std::vector<std::string>();
		for (int i = 0; i < static_cast<int>(string.size()); i++) // Browse the string char by char
		{
			last_string_cut += string[i];
			if (last_string_cut.size() > cut.size()) // If the string which allows to know where to cut is too long, cut him
			{
				last_string_cut = last_string_cut.substr(1, cut.size());
			}

			if (last_string_cut == cut) // If the string which allows to know where to cut is equal to the part to cut, do a cut
			{
				std::string final_string = last_string.substr(0, last_string.size() - (cut.size() - 1));
				if (erase_blank)
				{
					if (final_string != "")
					{
						result.push_back(final_string);
					}
				}
				else
				{
					result.push_back(final_string);
				}
				last_string = "";
				last_string_cut = "";
			}
			else
			{
				last_string += string[i];
			}
		}

		if (last_string.size() > 0 || !erase_last_if_blank) { result.push_back(last_string); } // Add the last non-cutted element
		return result;
	};

	// Cut a string in a vector where there are the "cut" part out of a string
	inline std::vector<std::string> cut_string_out_of(std::string str, std::string cut, std::string out_of, bool erase_blank = false, bool erase_last_if_blank = true) {
		// If the loop is out of the string or not
	    bool in_out_of = false;
		std::string last_string = ""; // String since the last cut
		// Last sequence of string for check with out offset
	    std::string last_string_out_of_offset = "";
		std::string last_string_cut = ""; // String of the "cut" size which allows to know where to cut
		std::vector<std::string> result = std::vector<std::string>();
		for (int i = 0; i < static_cast<int>(str.size()); i++) { // Browse the string char by char
            // Check the last string with out of offset start
		    last_string_out_of_offset += str[i];
		    if(last_string_out_of_offset.size() > out_of.size()) {
                last_string_out_of_offset = last_string_out_of_offset.substr(last_string_out_of_offset.size() - out_of.size(), out_of.size());
		    }

			last_string_cut += str[i];
			if (last_string_cut.size() > cut.size()) // If the string which allows to know where to cut is too long, cut him
			{
				last_string_cut = last_string_cut.substr(1, cut.size());
			}

            if(last_string_out_of_offset == out_of) {
                last_string_cut = "";
                last_string_out_of_offset = "";
                in_out_of = !in_out_of;
			}

			if (last_string_cut == cut && !in_out_of) // If the string which allows to know where to cut is equal to the part to cut, do a cut
			{
				std::string final_string = last_string.substr(0, last_string.size() - (cut.size() - 1));
				if (erase_blank)
				{
					if (final_string != "")
					{
						result.push_back(final_string);
					}
				}
				else
				{
					result.push_back(final_string);
				}
				last_string = "";
				last_string_cut = "";
			}
			else
			{
				last_string += str[i];
			}
		}

		if (last_string.size() > 0 || !erase_last_if_blank) { result.push_back(last_string); } // Add the last non-cutted element
		return result;
	};

	// Cut a string in a vector where there are the "cut" part out of 2 different string
	inline std::vector<std::string> cut_string_out_of_2(std::string str, std::string cut, std::string out_of_start, std::string out_of_end, bool erase_blank = false, bool erase_last_if_blank = true) {
		// If the loop is out of the string or not
	    int in_out_of = 0;
		std::string last_string = ""; // String since the last cut
		// Last sequence of string for check with out offset end
	    std::string last_string_out_of_offset_e = "";
	    // Last sequence of string for check with out offset start
	    std::string last_string_out_of_offset_s = "";
		std::string last_string_cut = ""; // String of the "cut" size which allows to know where to cut
		std::vector<std::string> result = std::vector<std::string>();
		for (int i = 0; i < static_cast<int>(str.size()); i++) { // Browse the string char by char
            // Check the last string with out of offset start
		    last_string_out_of_offset_e += str[i];
		    if(last_string_out_of_offset_e.size() > out_of_end.size()) {
                last_string_out_of_offset_e = last_string_out_of_offset_e.substr(last_string_out_of_offset_e.size() - out_of_end.size(), out_of_end.size());
		    }
		    // Check the last string with out of offset start
		    last_string_out_of_offset_s += str[i];
		    if(last_string_out_of_offset_s.size() > out_of_start.size()) {
                last_string_out_of_offset_s = last_string_out_of_offset_s.substr(last_string_out_of_offset_s.size() - out_of_start.size(), out_of_start.size());
		    }

			last_string_cut += str[i];
			if (last_string_cut.size() > cut.size()) // If the string which allows to know where to cut is too long, cut him
			{
				last_string_cut = last_string_cut.substr(1, cut.size());
			}

            if(last_string_out_of_offset_s == out_of_start) {
                last_string_cut = "";
                last_string_out_of_offset_e = "";
                last_string_out_of_offset_s = "";
                in_out_of++;
			}
			else if(last_string_out_of_offset_e == out_of_end) {
			    last_string_cut = "";
			    last_string_out_of_offset_e = "";
			    last_string_out_of_offset_s = "";
                if(in_out_of > 0) in_out_of--;
			}

			if (last_string_cut == cut && in_out_of == 0) // If the string which allows to know where to cut is equal to the part to cut, do a cut
			{
				std::string final_string = last_string.substr(0, last_string.size() - (cut.size() - 1));
				if (erase_blank)
				{
					if (final_string != "")
					{
						result.push_back(final_string);
					}
				}
				else
				{
					result.push_back(final_string);
				}
				last_string = "";
				last_string_cut = "";
			}
			else
			{
				last_string += str[i];
			}
		}

		if (last_string.size() > 0 || !erase_last_if_blank) { result.push_back(last_string); } // Add the last non-cutted element
		return result;
	};

	// Join a vector of string into one string.
	inline std::string join_string(std::vector<std::string> strings, std::string separation = "") {
		std::string result = "";
		for (int i = 0; i < static_cast<int>(strings.size()); i++)
		{
			result += strings[i]; // Concatenate each strings
			if (i != static_cast<int>(strings.size()) - 1)
			{
				result += separation; // Add the separation between strings
			}
		}

		return result;
	}

	// Return the string with only lower case
	inline std::string lowercase_string(std::string str) {
        for(int i = 0;i<static_cast<int>(str.size());i++)
        {
            if(str[i] >= 65 && str[i] <= 90)
            {
                str[i] += 32;
            }
        }
        return str;
	};

	// Replace a string in an another string.
	inline std::string replace(std::string str, std::string to_replace, std::string new_str) {
		return join_string(cut_string(str, to_replace, false, false), new_str);
	};

	// Convert a string to a double
	inline double string_to_double(std::string str) {
		if (_float_character == "") {
			_test_separation_character();
		}

		return std::stod(replace(str, _non_float_character, _float_character));
	}

    // Format a text
	inline std::string format_string(std::string str) {
	    std::string nl = ""; nl += static_cast<char>(10);
	    std::string np = ""; np += static_cast<char>(13);
	    str = replace(str, nl, "");
	    str = replace(str, np, "");
	    return str;
	};

	// Format a text to plain text
	inline std::string format_string_as_plain_text(std::string str) {
	    std::string gt = "&gt;";
	    std::string lt = "&lt;";
	    std::string sp = "&nbsp;";
	    str = replace(str, gt, SCLS_BALISE_END_CHAR_ARRAY);
	    str = replace(str, lt, SCLS_BALISE_START_CHAR_ARRAY);
	    str = replace(str, sp, " ");
	    return str;
	};

	// Format a text from plain text
	inline std::string format_string_from_plain_text(std::string str) {
	    std::string eol = "\n";
	    std::string np = ""; np += static_cast<char>(13);
	    str = replace(str, eol, "</br>");
	    str = replace(str, np, "");
	    return str;
	};

	//*********
	//
	// Text encoding system
	//
	//*********

	// Convert a string in UTF-8 code point to an UTF-8
    inline std::string to_utf_8(std::string str) {
        std::string result = "";
        for(int i = 0;i<static_cast<int>(str.size());i++)
        {
            unsigned char number = str[i];
            if(number < 128) {
                result += number;
            }
            else {
                unsigned char first_part = 0;
                unsigned char second_part = 0;

                first_part = (number & 0b00111111) | 0b10000000;
                second_part = ((number & 0b11000000) >> 6) | 0b11000000;
                result += second_part;
                result += first_part;
            }
        }
        return result;
    };

	// Convert a string in UTF-8 to an UTF-8 code point
    inline std::string to_utf_8_code_point(std::string str) {
        std::string result = "";
        for(int i = 0;i<static_cast<int>(str.size());i++)
        {
            if(~str[i] & 0b10000000)
            {
                result += str[i];
            }
            else if((str[i] & 0b11100000) == 0b11100000)
            {
                unsigned short final_character_1 = 0;
                unsigned short final_character_2 = 0;
                unsigned short final_character_3 = 0;
                final_character_1 = (str[i]) & 0b00001111; final_character_1 = final_character_1 << 11; i++;
                final_character_2 = (str[i]) & 0b00011111; final_character_2 = final_character_2 << 6; i++;
                final_character_3 = str[i] & 0b00111111;
                result += static_cast<char>(final_character_1 + final_character_2 + final_character_3);
            }
            else if((str[i] & 0b11000000) == 0b11000000)
            {
                unsigned short final_character_1 = 0;
                unsigned short final_character_2 = 0;
                final_character_1 = (str[i]) & 0b00011111; final_character_1 = final_character_1 << 6; i++;
                final_character_2 = str[i] & 0b00111111;
                result += static_cast<char>(final_character_1 + final_character_2);
            }
        }
        return result;
    };

	// Convert a char to an UTF-8
    inline std::string to_utf_8_code_point(const char* character, unsigned int text_size) {
        std::string result = "";
        unsigned int current_pos = 0;
        for(int i = 0;i<static_cast<int>(text_size);i++)
        {
            if(~character[current_pos] & 0b10000000)
            {
                result += character[current_pos];
            }
            else if((character[current_pos] & 0b11100000) == 0b11100000)
            {
                unsigned short final_character_1 = 0;
                unsigned short final_character_2 = 0;
                unsigned short final_character_3 = 0;
                final_character_1 = (character[current_pos]) & 0b00001111; final_character_1 = final_character_1 << 11; current_pos++;
                final_character_2 = (character[current_pos]) & 0b00011111; final_character_2 = final_character_2 << 6; current_pos++;
                final_character_3 = character[current_pos] & 0b00111111;
                result += static_cast<char>(final_character_1 + final_character_2 + final_character_3);
            }
            else if((character[current_pos] & 0b11000000) == 0b11000000)
            {
                unsigned short final_character_1 = 0;
                unsigned short final_character_2 = 0;
                final_character_1 = (character[current_pos]) & 0b00011111; final_character_1 = final_character_1 << 6; current_pos++;
                final_character_2 = character[current_pos] & 0b00111111;
                result += static_cast<char>(final_character_1 + final_character_2);
            }
            current_pos++;
        }
        return result;
    };

	//*********
	//
	// Balise system
	//
	//*********

	// Part of a text gotten by a balising cut
    struct _Text_Balise_Part {
        // Content of the part
        std::string content = "";
        // Position of the start of the balise (of the first char of the content)
        unsigned int start_position = 0;
    };

	// Return the name of a formatted balise
	inline std::string balise_name(std::string balise_formatted) {
	    if(balise_formatted[0] == SCLS_BALISE_START) balise_formatted = balise_formatted.substr(1, balise_formatted.size() - 1);
	    if(balise_formatted[0] == '/') balise_formatted = balise_formatted.substr(1, balise_formatted.size() - 1);
	    if(balise_formatted[balise_formatted.size() - 1] == SCLS_BALISE_END) balise_formatted = balise_formatted.substr(0, balise_formatted.size() - 1);
	    // Remove useless spaces
	    while(balise_formatted.size() > 0 && balise_formatted[0] == ' ') {
            balise_formatted = balise_formatted.substr(1, balise_formatted.size() - 1);
	    }

	    return cut_string(balise_formatted, " ")[0];
	};

	// Cut a string by its balises (including the balises in the vector)
	inline std::vector<_Text_Balise_Part> cut_string_by_balise(std::string str, bool erase_blank = false, bool erase_last_if_blank = true) {
	    bool last_is_balise = false;
		std::string last_string = ""; // String since the last cut
		std::vector<_Text_Balise_Part> result = std::vector<_Text_Balise_Part>();

		for (int i = 0; i < static_cast<int>(str.size()); i++) // Browse the string char by char
		{
		    if(str[i] == SCLS_BALISE_START) {
                _Text_Balise_Part part_to_add;
                part_to_add.content = last_string;
                part_to_add.start_position = i;
                if(!last_is_balise && last_string == "") {
                    if(!erase_blank && (result.size() > 0 || (i + 1 < static_cast<int>(str.size()) && str[i + 1] == '/')))result.push_back(part_to_add);
                }
                else result.push_back(part_to_add);
                last_string = "";

                int balise_level = 1;
                i++;
                while(i < static_cast<int>(str.size())) {
                    if(str[i] == SCLS_BALISE_START) balise_level++;
                    else if(str[i] == SCLS_BALISE_END) {
                        balise_level--;
                        if(balise_level <= 0) break;
                    }
                    last_string += str[i];
                    i++;
                }

                part_to_add.content = SCLS_BALISE_START + last_string + SCLS_BALISE_END;
                result.push_back(part_to_add);
                last_is_balise = true;
                last_string = "";
                continue;
		    }

		    last_is_balise = false;
			last_string += str[i];
		}

		if (last_string.size() > 0 || !erase_last_if_blank) {
            _Text_Balise_Part part_to_add;
            part_to_add.content = last_string;
            result.push_back(part_to_add);
        } // Add the last non-cutted element
		return result;
	};

	// Format a balise and return it
	inline std::string formatted_balise(std::string str) {
	    // Remove useless spaces
	    while(str.size() > 0 && str[0] == ' ') {
            str = str.substr(1, str.size() - 1);
	    }
	    while(str.size() > 0 && str[str.size() - 1] == ' ') {
            str = str.substr(0, str.size() - 1);
	    }

	    // Get the position of the / if there is one
        int slash_position = 0;
        bool slash_position_founded = false;
        while(str[slash_position] < static_cast<int>(str.size())) {
            if(str[slash_position] == '/') {
                slash_position_founded = true;
                break;
            }
            slash_position++;
        }

        // Format the balise
        std::string final_balise = "";
        if(slash_position_founded) final_balise = SCLS_BALISE_START + "/" + str.substr(slash_position + 1, str.size() - (2 + slash_position)) + SCLS_BALISE_END;
        else final_balise = SCLS_BALISE_START + str.substr(1, str.size() - 2) + SCLS_BALISE_END;

        // Format the formatted balise (help)
	    while(final_balise.size() > 0 && final_balise[0] == ' ') {
            final_balise = final_balise.substr(1, final_balise.size() - 1);
	    }
	    while(final_balise.size() > 0 && final_balise[final_balise.size() - 1] == ' ') {
            final_balise = final_balise.substr(0, final_balise.size() - 1);
	    }

        return final_balise;
	};

	// Balise in a text
    struct Balise_Datas {
        // If the balise
        bool has_content = true;
        // If the balise is a break of line or not
        bool is_break_line = false;
        // If the balise is a paragraph or not
        bool is_paragraph = false;
        // Name of the balise
        std::string name = "";
    };

	class _Balise_Container {
        // Class faciliting the handle of balises
    public:

        // Most simple _Balise_Container constructor
        _Balise_Container() {

        };
        // _Balise_Container destructor
        ~_Balise_Container() {

        };

        // Returns the position of the first plain text character in a unformatted text from before a position
        unsigned int first_plain_text_character_before_position_in_informatted_text(const std::string& text_to_convert, unsigned int position) {
            if(text_to_convert[position] == '>') {
                // Remove balises
                while(text_to_convert[position] != '<' && position > 0) { position--; }
            }
            else if(text_to_convert[position] == ';') {
                // Remove special insertion
                std::string part_content = "";
                const unsigned int start_position = position;
                while(position >= 0 && text_to_convert[position] != '&') {
                    part_content = text_to_convert[position] + part_content;
                    position--;
                } part_content = part_content.substr(0, part_content.size() - 1);

                if(!(part_content == "lt" || part_content == "gt") || position < 0) {
                    position = start_position;
                }
            }
            return position;
        };
        // Returns a html text in plain text
        std::string plain_text(std::string text_to_convert) {
            std::string final_text = "";
            std::stack<std::string> found_balises = std::stack<std::string>();
            std::string last_balise = "";
            text_to_convert = replace(format_string(text_to_convert), "</br>", "\n");
            for(int i = 0;i<static_cast<int>(text_to_convert.size());i++) {
                if(text_to_convert[i] == '<') {
                    std::string balise = "";
                    unsigned int start = i;
                    while(text_to_convert[i] != '>' && i < static_cast<int>(text_to_convert.size())) {
                        balise += text_to_convert[i];
                        i++;
                    }
                    balise += ">";
                    balise = formatted_balise(balise);

                    if(start != 0) {
                        // Check the balise
                        std::string current_balise_name = balise_name(balise);

                        if(contains_defined_balise(current_balise_name)) {
                            if(defined_balise(current_balise_name)->is_paragraph &&
                               final_text != "" &&
                               i < static_cast<int>(text_to_convert.size()) - 1 &&
                               (!contains_defined_balise(last_balise) ||
                               !defined_balise(last_balise)->is_paragraph)) {
                                final_text += "\n";
                            }
                            else if(defined_balise(current_balise_name)->is_break_line) {
                                final_text += "\n";
                            }
                        }

                        // Check in the balise stack
                        if(balise[1] == '/') {
                            if(found_balises.size() > 0 && found_balises.top() == current_balise_name) {
                                found_balises.pop();
                            }
                        }
                        else found_balises.push(current_balise_name);
                        last_balise = current_balise_name;
                    }
                }
                else {
                    final_text += text_to_convert[i];
                    last_balise = "";
                }
            }

            final_text = format_string_as_plain_text(final_text);
            return final_text;
        };
        // Returns a plain text position to unformatted text position
        unsigned int plain_text_position_to_unformatted_text_position(std::string text_to_convert, unsigned int position) {
            unsigned int final_position = 0;
            for(int i = 0;i<static_cast<int>(text_to_convert.size()) && i < position;i++) {
                if(text_to_convert[final_position] == '<') {
                    // Remove balises
                    while(text_to_convert[final_position] != '>' && final_position < static_cast<int>(text_to_convert.size())) final_position++;
                }
                else if(text_to_convert[final_position] == '&') {
                    // Remove special insertion
                    std::string part_content = "";
                    const unsigned int start_position = final_position;
                    while(text_to_convert[final_position] != ';' && final_position < static_cast<int>(text_to_convert.size())) {
                        part_content += text_to_convert[final_position];
                        final_position++;
                    } part_content = part_content.substr(1, part_content.size() - 1);

                    if(!(part_content == "lt" || part_content == "gt") || final_position >= static_cast<int>(text_to_convert.size())) {
                        final_position = start_position;
                    }
                }
                final_position++;
            }
            return final_position;
        };
        // Return the size of the text
        inline unsigned int plain_text_size(std::string text_to_check) { return plain_text(text_to_check).size(); };

        // Returns the balise of the block or a blank string if it is not
        std::string _block_balise(std::vector<_Text_Balise_Part>& cutted) {
            if(cutted.size() == 0) return "";

            // Check for the main balise of the block
            std::string to_return = "";
            if(cutted[0].content[0] == '<') {
                std::string block_balise_name = balise_name(cutted[0].content);

                // Check if the block is an entire balise
                unsigned int level = 0;
                for(int i = 0;i<static_cast<int>(cutted.size())-1;i++) {
                    if(cutted[i].content.size() > 2 && cutted[i].content[0] == '<' && cutted[i].content[cutted[i].content.size() - 1] == '>') {
                        std::string parsed_balise_name = balise_name(cutted[i].content);
                        if(parsed_balise_name == block_balise_name) {
                            if(cutted[i].content[1] == '/') {
                                level--;
                                if(level == 0) break;
                            }
                            else {
                                level++;
                            }
                        }
                    }
                }

                // If the block can be an entire balise
                if(level == 1) {
                    if(contains_defined_balise(block_balise_name)) {
                        to_return = block_balise_name;
                    }
                }
            }
            return to_return;
        };
        // If the generator contains the style of a balise
        inline bool contains_defined_balise(std::string balise_name) {
            for(std::map<std::string, std::shared_ptr<Balise_Datas>>::iterator it = a_defined_balises.begin();it!=a_defined_balises.end();it++){
                if(it->first == balise_name) return true;
            }
            return false;
        };
        // Cut a block by its sub_blocks and spaces
        std::vector<_Text_Balise_Part> _cut_block(std::string block_text) {
            std::vector<_Text_Balise_Part> first_cutted = cut_string_by_balise(block_text, false, true);
            std::vector<_Text_Balise_Part> cutted = std::vector<_Text_Balise_Part>();
            for(int i = 0;i<static_cast<int>(first_cutted.size());i++) {
                if(first_cutted[i].content.size() > 0 && first_cutted[i].content[0] == '<') {
                    // Erase the last blank character if necessary
                    std::string current_balise_name = balise_name(formatted_balise(first_cutted[i].content));
                    cutted.push_back(first_cutted[i]);
                }
                else if(first_cutted[i].content == "") {
                    _Text_Balise_Part part_to_add; cutted.push_back(part_to_add);
                }
                else {
                    std::vector<std::string> space_cutted = cut_string(first_cutted[i].content, " ", false, true);
                    for(int j = 0;j<static_cast<int>(space_cutted.size());j++) {
                        _Text_Balise_Part part_to_add;
                        part_to_add.content = space_cutted[j];
                        cutted.push_back(part_to_add);

                        if(j < static_cast<int>(space_cutted.size()) - 1 || first_cutted[i].content[first_cutted[i].content.size() - 1] == ' ') {
                            _Text_Balise_Part part_to_add;
                            part_to_add.content = " ";
                            cutted.push_back(part_to_add);
                        }
                    }
                }
            }
            return cutted;
        };
        // Cut a multi-block by sub-blocks
        std::vector<std::string> _cut_multi_block(std::string block_text) {
            std::vector<_Text_Balise_Part> first_cutted = cut_string_by_balise(block_text, false, true);
            std::string last_text = "";
            std::vector<std::string> to_return = std::vector<std::string>();
            for(int i = 0;i<static_cast<int>(first_cutted.size());i++) {
                if(first_cutted[i].content.size() > 0 && first_cutted[i].content[0] == '<') {
                    // A sub-block is here
                    std::string current_balise_name = balise_name(formatted_balise(first_cutted[i].content));
                    if(contains_defined_balise(current_balise_name) && defined_balise(current_balise_name)->is_paragraph) {
                        // Save the last empty paragraph
                        to_return.push_back(last_text); last_text = "";

                        i++;
                        unsigned int level = 1;
                        std::string total_text = "";
                        while(i<static_cast<int>(first_cutted.size())) {
                            if(first_cutted[i].content[0] == '<') {
                                first_cutted[i].content = formatted_balise(first_cutted[i].content);
                                std::string next_balise_name = balise_name(first_cutted[i].content);
                                if(next_balise_name == current_balise_name) {
                                    if(first_cutted[i].content[1] == '/') {
                                        level--;
                                        if(level == 0) break;
                                    }
                                    else {
                                        level++;
                                    }
                                }
                            }
                            total_text += first_cutted[i].content;
                            i++;
                        }

                        // Create the block datas
                        to_return.push_back(total_text);
                    }
                    else {
                        last_text += first_cutted[i].content;
                    }
                }
                else {
                    last_text += first_cutted[i].content;
                }
            }
            // Save the last paragraph if necessary
            if(last_text != "") { to_return.push_back(last_text); last_text = ""; }
            return to_return;
        };
        // Return the style of a balise
        inline Balise_Datas* defined_balise(std::string balise_name) { return a_defined_balises[balise_name].get(); };
        // Set a balise to the container
        template <typename O = Balise_Datas>
        inline void set_defined_balise(std::string name, const std::shared_ptr<O>& balise_datas) { a_defined_balises[name] = balise_datas; };

        // Load the built-ins balises
        virtual void _load_built_in_balises() {
            std::shared_ptr<Balise_Datas> current_balise = std::make_shared<Balise_Datas>();
            // Create the <br> style
            current_balise.get()->is_break_line = true;
            set_defined_balise("br", current_balise);
            // Create the <div> style
            current_balise = std::make_shared<Balise_Datas>();
            current_balise.get()->is_paragraph = true;
            set_defined_balise("div", current_balise);
            // Create the <p> style
            current_balise = std::make_shared<Balise_Datas>();
            current_balise.get()->is_paragraph = true;
            set_defined_balise("p", current_balise);
            // Create the <h1> style
            current_balise = std::make_shared<Balise_Datas>();
            current_balise.get()->is_paragraph = true;
            set_defined_balise("h1", current_balise);
            // Create the <h2> style
            current_balise = std::make_shared<Balise_Datas>();
            current_balise.get()->is_paragraph = true;
            set_defined_balise("h2", current_balise);
        }
    private:
        // List of each defined balises
        std::map<std::string, std::shared_ptr<Balise_Datas>> a_defined_balises = std::map<std::string, std::shared_ptr<Balise_Datas>>();
    };

    //*********
	//
	// The String class
	//
	//*********

	class String {
	    // Class representing a SCLS string
    public:// Most simple String constructor
        String() : a_content("") {};
        // Most simple String constructor with "char*"
        String(char* content) : a_content(content) {};
        // Most simple String constructor with "std::string"
        String(std::string content) : a_content(content) {};

        // Return if the String contains an another string
        inline bool contains(std::string part) { return contains_string(a_content, part); };
        // Returns if a string contains an another string out of a string
        inline bool contains(std::string part, std::string out_of) {return contains_string(a_content, part, out_of);};
        // Returns if a string contains an another string out of 2 different string
        inline bool contains(std::string part, std::string out_of_start, std::string out_of_end) {return contains_string(a_content, part, out_of_start, out_of_end);};
        // Returns the number occurrence of a string in an another string
        inline unsigned int count(std::string part) {return count_string(a_content, part);};
        // Returns the number occurrence of a string in an another string out of a string
        inline unsigned int count(std::string part, std::string out_of) {return count_string(a_content, part, out_of);};
        // Returns the number occurrence of a string in an another string out of 2 different string
        inline unsigned int count(std::string part, std::string out_of_start, std::string out_of_end) {return count_string(a_content, part, out_of_start, out_of_end);};
        // Cuts the String by an another string
        inline std::vector<std::string> cut(std::string part_to_cut, bool erase_blank = false, bool erase_last_if_blank = true) { return cut_string(a_content, part_to_cut, erase_blank, erase_last_if_blank); };
        // Cuts the String by an another string out of a string
        inline std::vector<std::string> cut_out_of(std::string part_to_cut, std::string out_of, bool erase_blank = false, bool erase_last_if_blank = true) { return cut_string_out_of(a_content, part_to_cut, out_of, erase_blank, erase_last_if_blank); };
        // Cuts the String by an another string out of 2 different string
        inline std::vector<std::string> cut_out_of_2(std::string part_to_cut, std::string out_of_start, std::string out_of_end, bool erase_blank = false, bool erase_last_if_blank = true) { return cut_string_out_of_2(a_content, part_to_cut, out_of_start, out_of_end, erase_blank, erase_last_if_blank); };
        // Cuts the String by balises (including the balises in the vector)
        inline std::vector<_Text_Balise_Part> cut_by_balise(bool erase_blank = false, bool erase_last_if_blank = true){ return cut_string_by_balise(a_content, erase_blank, erase_last_if_blank); };
        // Formats the string
        inline void format() {a_content = format_string(a_content);};
        // Returns the String formatted
        inline String formatted() {return String(format_string(a_content));};
        // Returns the String formatted for display
        inline String formatted_as_plain_text() {return String(format_string_as_plain_text(a_content));};
        // Returns the String formatted from plain text
        inline String formatted_from_plain_text() {return String(format_string_from_plain_text(a_content));};

        // Returns the String to a char array
        inline const char* to_char_array() const {return a_content.c_str();};
        // Returns the String to a std::string
        inline std::string to_std_string() const {return a_content;};

        // Operator = overload with a char*
        inline String& operator=(const char* other) {
            a_content = other;
            return *this;
        };
        // Operator = overload with a std::string
        inline String& operator=(const std::string& other) {
            a_content = other;
            return *this;
        };
        // Operator = overload with an other String
        inline String& operator=(const String& other) {
            a_content = other.a_content;
            return *this;
        };

        // Operator += overload with char*
        inline String& operator+=(const char* second) { a_content += second; return *this; };
        // Operator += overload with std::string
        inline String& operator+=(const std::string second) { a_content += second; return *this; };
        // Operator += overload with String
        inline String& operator+=(const String second) { a_content += second.a_content; return *this; };

        // Operator == overload with char*
        inline bool operator==(const char* second) const { return a_content.c_str() == second; };
        // Operator == overload with std::string
        inline bool operator==(const std::string& second) const { return a_content == second; };
        // Operator == overload with String
        inline bool operator==(const String& second) const { return a_content == second.a_content; };
    private:
        // Content of the string
        std::string a_content = "";
	};

	// Flux output operator of String
	inline std::ostream& operator<<(std::ostream& strm, const String& str) {
	    const char* to_out = str.to_char_array();
        strm << to_out;
        return strm;
    }
}

#endif // SCLS_FOUNDATION_STRING
