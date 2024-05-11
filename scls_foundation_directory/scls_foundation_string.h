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
	inline bool contains(std::string str, std::string part) {
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

	// Return the number occurrence of a string in an another string
	inline unsigned int count(std::string str, std::string part) {
	    std::string last_string = ""; // String since the last cut
	    unsigned int occurence = 0;
		for (int i = 0; i < static_cast<int>(str.size()); i++) // Browse the string char by char
		{
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

    // Convert a char to an UTF-8
    inline std::string to_utf_8(const char* character, unsigned int text_size) {
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

    // Convert a string to an UTF-8
    inline std::string to_utf_8(std::string str) {
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

        // Cuts the String by an another string
        inline std::vector<std::string> cut(std::string part_to_cut, bool erase_blank = false, bool erase_last_if_blank = true) {
            return cut_string(a_content, part_to_cut, erase_blank, erase_last_if_blank);
        };

        // Returns the String to a char array
        inline const char* to_char_array() const {return a_content.c_str();};
        // Returns the String to a std::string
        inline std::string to_std_string() const {return a_content;};

        // Operator = overload with a char*
        String& operator=(const char* other) {
            a_content = other;
            return *this;
        };
        // Operator = overload with a std::string
        String& operator=(const std::string& other) {
            a_content = other;
            return *this;
        };
        // Operator = overload with an other String
        String& operator=(const String& other) {
            a_content = other.a_content;
            return *this;
        };
    private:
        // Content of the string
        std::string a_content = "";
	};

	// Flux output operator of String
	std::ostream& operator<<(std::ostream& strm, const String& str) {
	    const char* to_out = str.to_char_array();
        strm << to_out;
        return strm;
    }
}

#endif // SCLS_FOUNDATION_STRING
