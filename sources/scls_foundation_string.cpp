//******************
//
// scls_foundation_string.cpp
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
// This file contaisn the source code of scls_foundation_string.h.
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

// Include the good header file
#include "../scls_foundation_directory/scls_foundation_string.h"

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// "std::string" manipulation
	//
	//*********

	// Variables used to define a float separation character
	std::string __float_character = "";
	std::string __non_float_character = "";

	// Test and choose the separation character in a double
    void __test_separation_character() {__float_character = ".";__non_float_character = ",";if (std::stod("0.25") != 0.25){__float_character = ",";__non_float_character = ".";}};

	// Convert a char array to a string and return it
    std::string char_array_to_string(const char* c_a, unsigned int c_a_size) {std::string result = "";for(unsigned int i = 0;i<c_a_size;i++) {result += c_a[i];}return result;}

	// Return if a string contains an another string
    bool contains_string(std::string str, std::string part) {
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
    bool contains_string(std::string str, std::string part, std::string out_of) {
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
    bool contains_string(std::string str, std::string part, std::string out_of_start, std::string out_of_end) {
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
    unsigned int count_string(std::string str, std::string part) {
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
    unsigned int count_string(std::string str, std::string part, std::string out_of) {
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
    unsigned int count_string(std::string str, std::string part, std::string out_of_start, std::string out_of_end) {
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
    std::vector<std::string> cut_string(std::string string, std::string cut, bool erase_blank, bool erase_last_if_blank) {
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
    std::vector<std::string> cut_string_out_of(std::string str, std::string cut, std::string out_of, bool erase_blank, bool erase_last_if_blank) {
		// If the loop is out of the string or not
	    bool in_out_of = false;
		std::string last_string = ""; // String since the last cut
		// Last sequence of string for check with out offset
		std::string last_string_cut = ""; // String of the "cut" size which allows to know where to cut
		std::vector<std::string> result = std::vector<std::string>();
		for (int i = 0; i < static_cast<int>(str.size()); i++) { // Browse the string char by char
            last_string_cut += str[i];

            // If the string which allows to know where to cut is too long, cut him
			if (last_string_cut.size() > cut.size()) {
				last_string_cut = last_string_cut.substr(1, cut.size());
			}

			// Check the off-part
            if(i >= static_cast<int>(out_of.size()) && str.substr(i - static_cast<int>(out_of.size()), static_cast<int>(out_of.size())) == out_of) { in_out_of = !in_out_of; }

            // If the string which allows to know where to cut is equal to the part to cut, do a cut
			if (last_string_cut == cut && !in_out_of) {
				std::string final_string = last_string.substr(0, last_string.size() - (cut.size() - 1));
				if (erase_blank) {
					if (final_string != "") {
						result.push_back(final_string);
					}
				}
				else {
					result.push_back(final_string);
				}
				last_string = "";
				last_string_cut = "";
			}
			else {
				last_string += str[i];
			}
		}

		if (last_string.size() > 0 || !erase_last_if_blank) { result.push_back(last_string); } // Add the last non-cutted element
		return result;
	};

	// Cut a string in a vector where there are the "cut" part out of 2 different string
    std::vector<std::string> cut_string_out_of_2(std::string str, std::string cut, std::string out_of_start, std::string out_of_end, bool erase_blank, bool erase_last_if_blank) {
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
    std::string join_string(std::vector<std::string> strings, std::string separation) {
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
    std::string lowercase_string(std::string str) {for(int i = 0;i<static_cast<int>(str.size());i++) {if(str[i] >= 65 && str[i] <= 90){str[i] += 32;}}return str;};

	// Replace a string in an another string.
    std::string replace(std::string str, std::string to_replace, std::string new_str) {return join_string(cut_string(str, to_replace, false, false), new_str);};

	// Returns if a string is a number or not
    bool string_is_number(char to_test) {return to_test == '0' || to_test == '1' || to_test == '2' || to_test == '3' || to_test == '4' || to_test == '5' || to_test == '6' || to_test == '7' ||to_test == '8' || to_test == '9';};
    bool string_is_number(std::string to_test) {for(int i = 0;i<static_cast<int>(to_test.size());i++){if(!string_is_number(to_test[i]))return false;}return true;}
    // Convert a string to a double
    double string_to_double(std::string str) {if (__float_character == "") {__test_separation_character();}return std::stod(replace(str, __non_float_character, __float_character));}

    //*********
	//
	// "std::string" formatting
	//
	//*********

	// Capitalize a character of a std::string
	std::string capitalise_letter(std::string str, int position) {
	    if(utf_8_level(str[position]) == 0){char to_convert = str[position];to_convert-=32;str = str.substr(0, position) + to_convert + str.substr(position + 1, str.size() - (position + 1)); }
	    return str;
	}

	// Format a number to a text
    std::string format_number_to_text(double number_to_format, int max_size) {
	    std::string to_return = std::to_string(number_to_format);
	    to_return = replace(to_return, ",", ".");

	    // Delete the useless "0"
	    while(to_return.size() > 0 && to_return[to_return.size() - 1] == '0') {
            to_return = to_return.substr(0, to_return.size() - 1);
	    }

	    // Delete the useless "."
	    if(to_return[to_return.size() - 1] == '.'){to_return = to_return.substr(0, to_return.size() - 1);}
	    if(max_size != -1 && number_to_format - floor(number_to_format) != 0) {
            // Delete the useless numbers
            int decimal_size = 0; for(;decimal_size<static_cast<int>(to_return.size());decimal_size++){if(to_return[decimal_size]=='.'){break;}}
            decimal_size++;
            while(to_return.size() > 0 && static_cast<int>(to_return.size()) - decimal_size > max_size) {to_return = to_return.substr(0, to_return.size() - 1);}
	    }

        return to_return;
	};
	std::string format_number_to_text_strict(double number_to_format, int unit_size, int decimal_size) {
	    std::string to_return = std::to_string(number_to_format);
	    to_return = replace(to_return, ",", ".");
	    std::vector<std::string> splited = cut_string(to_return, std::string("."));
	    if(splited.size() == 1){splited.insert(splited.begin(), std::string(""));}

	    // Handle unit part
	    while(splited[0].size() > 0 && static_cast<int>(splited[0].size()) > unit_size){splited[0] = splited[0].substr(1, splited[0].size() - 1);}
	    while(static_cast<int>(splited[0].size()) < unit_size){splited[0].insert(splited[0].begin(), '0');}
	    if(decimal_size == 0){return splited[0];}

	    // Handle decimal part
	    while(splited[1].size() > 0 && static_cast<int>(splited[1].size()) > decimal_size){splited[1] = splited[1].substr(0, splited[1].size() - 1);}
	    while(static_cast<int>(splited[1].size()) < decimal_size){splited[1].push_back('0');}

        return splited[0] + std::string(".") + splited[1];
	}

    // Format a std::string and its break lines
    std::string format_string_break_line(std::string str, std::string new_break_line) {
	    std::string nl = ""; nl += static_cast<char>(10);
	    std::string np = ""; np += static_cast<char>(13);
	    std::string nb = np + nl;
	    if(new_break_line != nb) {str = replace(str, nb, new_break_line);}
	    if(new_break_line != nl && new_break_line != nb) {str = replace(str, nl, new_break_line);}
	    if(new_break_line != np && new_break_line != nb) {str = replace(str, np, new_break_line);}
	    return str;
	};
    std::string format_string(std::string str) {return format_string_break_line(str, "");};
	// Format a std::string and its tabulations
    std::string format_string_tabulations(std::string str, std::string new_tabulation) {std::string nl = ""; nl += static_cast<char>(9);if(new_tabulation != nl) str = replace(str, nl, new_tabulation);return str;};

	// Format an unformatted text to a plain text
    std::string format_string_as_plain_text(std::string str) {
	    std::string to_return = "";
	    // Handle each characters
	    for(int i = 0;i<static_cast<int>(str.size());i++) {
            if(str[i] == '&') {
                // A special character is handled
                if(i + 1 < static_cast<int>(str.size()) && str[i + 1] == '&') {to_return += "&";i++;}
                else {
                    // Get the needed character
                    std::string special = ""; i++;
                    while(i < static_cast<int>(str.size()) && str[i] != ';') {
                        special += str[i];
                        i++;
                    }
                    if(special == "gt") {to_return += ">";}
                    else if(special == "lt") {to_return += "<";}
                    else if(special == "nbsp") {to_return += " ";}
                }
            } else {to_return += str[i];}
	    } return to_return;
	};
	// Format a plain text to an unformatted text
    std::string format_string_from_plain_text(std::string str) {
	    std::string to_return = "";
	    // Handle each characters
	    for(int i = 0;i<static_cast<int>(str.size());i++) {
            if(str[i] == '&') { to_return += std::string("&&"); }
            else if(str[i] == '<') { to_return += std::string("&lt;"); }
            else if(str[i] == '>') { to_return += std::string("&gt;"); }
            else {to_return += str[i];}
	    } return to_return;
	};

	// Remove the comment in a text, out of a text
    std::string remove_comment_out_of(std::string str, std::string out_of) {
        std::string to_return = "";
        std::vector<std::string> cutted = cut_string(str, "\n");
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            std::vector<std::string> cutted_for_comment = cut_string_out_of(cutted[i], "//", out_of);
            if(cutted_for_comment.size() > 0)to_return += cutted_for_comment[0];
            if(i < static_cast<int>(cutted.size() - 1)) to_return += "\n";
        }
        return to_return;
    };

    // Remove spaces from a text
    std::string remove_space(std::string str) {std::string to_return = "";for(int i = 0;i<static_cast<int>(str.size());i++) {if(str[i] != ' ') to_return += str[i];}return to_return;};

    //*********
	//
	// Text encoding system
	//
	//*********

	// Adds a specific character in UTF-8 with his UTF-8 code
	void add_utf_8(std::string& to_add, unsigned int code) {
	    // Convert the number
        std::string result = std::string("");
        if(code > 127) {
            if(code < 2047) {
                unsigned char first_part = 0;
                unsigned char second_part = 0;

                first_part = (code & 0b00000000000000000000000000111111) | 0b10000000;
                second_part = ((code >> 6) & 0b00000000000000000000000000011111) | 0b11000000;
                result += second_part;
                result += first_part;
            }
            else {
                unsigned char first_part = 0;
                unsigned char second_part = 0;
                unsigned char third_part = 0;

                first_part = (code & 0b00000000000000000000000000111111) | 0b10000000;
                second_part = ((code >> 6) & 0b00000000000000000000000000011111) | 0b11000000;
                third_part = ((code >> 12) & 0b00000000000000000000000000001111) | 0b11100000;
                result += third_part;
                result += second_part;
                result += first_part;
            }
        }
        else {result += static_cast<unsigned char>(code);}
        // Add the part
        to_add += result;
	}

	// Convert a string in UTF-8 code point to an UTF-8
    std::string to_utf_8(std::string str) {
        std::string result = "";
        for(int i = 0;i<static_cast<int>(str.size());i++) {
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
    bool is_character_utf_8(char chr) {if(chr & 0b10000000)return true;return false;};
    unsigned char utf_8_level(char character) {if(~character & 0b10000000)return 0;else if((character & 0b11100000) == 0b11000000)return 1;else if((character & 0b11110000) == 0b11100000)return 2;return 3;};
    std::string to_utf_8_code_point(std::string str) {
        std::string result = "";
        for(int i = 0;i<static_cast<int>(str.size());i++) {
            if(~str[i] & 0b10000000) {
                result += str[i];
            }
            else if((str[i] & 0b11100000) == 0b11100000) {
                unsigned short final_character_1 = 0;
                unsigned short final_character_2 = 0;
                unsigned short final_character_3 = 0;
                final_character_1 = (str[i]) & 0b00001111; final_character_1 = final_character_1 << 11; i++;
                final_character_2 = (str[i]) & 0b00011111; final_character_2 = final_character_2 << 6; i++;
                final_character_3 = str[i] & 0b00111111;
                result += static_cast<char>(final_character_1 + final_character_2 + final_character_3);
            }
            else if((str[i] & 0b11000000) == 0b11000000) {
                unsigned short final_character_1 = 0;
                unsigned short final_character_2 = 0;
                final_character_1 = (str[i]) & 0b00011111; final_character_1 = final_character_1 << 6; i++;
                final_character_2 = str[i] & 0b00111111;
                result += static_cast<char>(final_character_1 + final_character_2);
            }
        }
        return result;
    };
    std::string to_utf_8_code_point(const char* character, unsigned int text_size) {
        std::string result = "";
        unsigned int current_pos = 0;
        for(int i = 0;i<static_cast<int>(text_size);i++) {
            if(~character[current_pos] & 0b10000000) {
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

    // Returns the offset of size between two position in an utf 8 and code point text
    unsigned int code_point_utf_8_size_offset(std::string utf_8, int analyse_end_utf_8) {
        unsigned int to_return = 0;
        if(analyse_end_utf_8 == -1) {
            for(int i = 0;i<static_cast<int>(utf_8.size());i++) {
                if(static_cast<int>(utf_8[i]) >= 128) {to_return++;}
            }
        } else {
            for(int i = 0;i<static_cast<int>(utf_8.size()) && i < analyse_end_utf_8;i++) {
                if(static_cast<int>(utf_8[i]) >= 128) {to_return++;}
            }
        } return to_return;
    };
    unsigned int utf_8_code_point_size_offset(std::string utf_8, int analyse_end_code_point) {
        unsigned int to_return = 0;
        if(analyse_end_code_point <= -1) {
            for(int i = 0;i<static_cast<int>(utf_8.size());i++) {
                if(!(~utf_8[i] & 0b10000000)) {to_return++;i++;}
            }
        } else {
            for(int i = 0;i<static_cast<int>(utf_8.size()) && i < analyse_end_code_point + static_cast<int>(to_return);i++) {
                if(!(~utf_8[i] & 0b10000000)) {to_return++;i++;}
            }
        } return to_return;
    };

    //*********
	//
	// XML system
	//
	//*********

	// Format a text for being usable with XLM
    std::string format_for_xml(std::string content) {
	    // Erase the first spaces (if there are)
	    while(static_cast<int>(content.size()) > 0) {
            if(content[0] == ' ' || content[0] == '\n' || content[0] == static_cast<char>(9)) {
                content = content.substr(1, content.size() - 1);
            }
            else break;
	    }

	    // Erase the break line and space before the balises
	    int i = 0;
	    while(i < static_cast<int>(content.size())) {
            if(i > 0) {
                if(content[i - 1] == '>' && (content[i] == ' ' || content[i] == '\n')) {
                    content.erase(content.begin() + i); continue;
                }
            }
            i++;
	    }
	    return content;
	};

    // Returns the name of an attribute of a balise
    std::string attribute_name(std::string attribute) {
        std::string to_return = "";
        for(int i = 0;i<static_cast<int>(attribute.size()) && attribute[i] != '=';i++) {
            to_return += attribute[i];
        }

        return to_return;
    };

    // Returns the value of an attribute of a balise
    std::string attribute_value(std::string attribute) {
        int i = 0;
        for(;i<static_cast<int>(attribute.size()) && attribute[i] != '=';i++) {} i++;
        std::string to_return = "";
        if(i<static_cast<int>(attribute.size())) to_return = attribute.substr(i, attribute.size() - i);

        return to_return;
    };

	// Return the name of a formatted balise
    std::string balise_name(std::string balise_formatted) {
	    if(balise_formatted[0] == '<') balise_formatted = balise_formatted.substr(1, balise_formatted.size() - 1);
	    if(balise_formatted[0] == '/') balise_formatted = balise_formatted.substr(1, balise_formatted.size() - 1);
	    if(balise_formatted[balise_formatted.size() - 1] == '>') balise_formatted = balise_formatted.substr(0, balise_formatted.size() - 1);
	    // Remove useless spaces
	    while(balise_formatted.size() > 0 && balise_formatted[0] == ' ') {
            balise_formatted = balise_formatted.substr(1, balise_formatted.size() - 1);
	    }

	    std::vector<std::string> cutted = cut_string(balise_formatted, " ");
	    if(cutted.size() <= 0) return "";
	    return cutted[0];
	};

	// Returns if a formated balise is a closing balise or not
    bool closing_balise(std::string balise) {return balise.size() > 1 && balise[1] == '/';}

	// Cut a balise by its attributes
    std::vector<std::string> cut_balise_by_attributes(std::string str) {
	    // Cut the balise
	    std::vector<std::string> result = cut_string(str, " ", true);
	    if(result.size() > 0)result.erase(result.begin());

	    // Erase the last '>' if necessary
        if(result.size() > 0 && result[result.size() - 1][result[result.size() - 1].size() - 1] == '>') result[result.size() - 1].erase(result[result.size() - 1].end() - 1);

	    return result;
	};

	// Cut a balise by its attributes out of a certain pattern
    std::vector<std::string> cut_balise_by_attributes_out_of(std::string str, std::string out) {
	    // Cut the balise
	    std::vector<std::string> result = cut_string_out_of(str, " ", out, true);
        int result_size = result.size() - 1;
	    if(result_size >= 0){result.erase(result.begin());}

	    // Erase the last '>' if necessary
	    result_size = result.size() - 1;
        if(result_size >= 0 && result[result_size][result[result_size].size() - 1] == '>'){result[result_size] = result[result_size].substr(0, result[result_size].size() - 1);}

	    return result;
	};

	// Cut a string by its balises (including the balises in the vector)
    std::vector<_Text_Balise_Part> cut_string_by_balise(std::string str, bool erase_blank, bool erase_last_if_blank) {
	    bool last_is_balise = false;
		std::string last_string = ""; // String since the last cut
		std::vector<_Text_Balise_Part> result = std::vector<_Text_Balise_Part>();

		// Browse the string char by char
		for (int i = 0; i < static_cast<int>(str.size()); i++) {
		    if(str[i] == '<') {
                _Text_Balise_Part part_to_add;
                part_to_add.content = last_string;
                part_to_add.start_position = i;
                if(!last_is_balise && last_string == "") {
                    if(!erase_blank && (result.size() > 0 || (i + 1 < static_cast<int>(str.size()) && str[i + 1] == '/')))result.push_back(part_to_add);
                }
                else {result.push_back(part_to_add);}
                last_string = "";
                part_to_add.content = "";

                int balise_level = 1;
                i++;
                while(i < static_cast<int>(str.size())) {
                    if(str[i] == '<') balise_level++;
                    else if(str[i] == '>') {
                        balise_level--;
                        if(balise_level <= 0) break;
                    }
                    last_string += str[i];
                    i++;
                }

                part_to_add.balise_content = std::string("<") + last_string + std::string(">");
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

	// Cut a string by its balises (including the balises in the vector) out of a certain pattern
    std::vector<_Text_Balise_Part> cut_string_by_balise_out_of(std::string str, std::string out, bool erase_blank, bool erase_last_if_blank) {
	    bool can_cut = true;
	    bool last_is_balise = false;
		std::string last_string = ""; // String since the last cut
		std::vector<_Text_Balise_Part> result = std::vector<_Text_Balise_Part>();

		for (int i = 0; i < static_cast<int>(str.size()); i++) { // Browse the string char by char
            if(i >= static_cast<int>(out.size()) && i <= static_cast<int>(str.size()) - static_cast<int>(out.size()) &&
               str.substr(i - static_cast<int>(out.size()), static_cast<int>(out.size())) == out) can_cut = !can_cut;
            else if(str[i] == '<' && can_cut) {
                _Text_Balise_Part part_to_add;
                part_to_add.content = last_string;
                part_to_add.start_position = i;
                if(!last_is_balise && last_string == "") {
                    if(!erase_blank && (result.size() > 0 || (i + 1 < static_cast<int>(str.size()) && str[i + 1] == '/')))result.push_back(part_to_add);
                }
                else result.push_back(part_to_add);
                last_string = "";

                int balise_level = 1;
                bool can_stop = true;
                i++;
                while(i < static_cast<int>(str.size())) {
                    // Check the "out" character
                    if(i >= static_cast<int>(out.size()) && i <= static_cast<int>(str.size()) - static_cast<int>(out.size()) && str.substr(i - static_cast<int>(out.size()), static_cast<int>(out.size())) == out) can_stop = !can_stop;

                    if(str[i] == '<' && can_stop) balise_level++;
                    else if(str[i] == '>' && can_stop) {
                        balise_level--;
                        if(balise_level <= 0) break;
                    }
                    last_string += str[i];
                    i++;
                }

                part_to_add.balise_content = std::string("<") + last_string + std::string(">");
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
    std::string formatted_balise(std::string str) {
	    // Remove useless spaces
	    while(str.size() > 0 && str[0] == ' ') {
            str = str.substr(1, str.size() - 1);
	    }
	    while(str.size() > 0 && str[str.size() - 1] == ' ') {
            str = str.substr(0, str.size() - 1);
	    }

	    if(str.size() < 2 || str[0] != '<' || str[str.size() - 1] != '>') return "";

	    // Get the position of the / if there is one
        int slash_position = 0;
        bool slash_position_founded = false;
        if(str[1] == '/') { slash_position = 1; slash_position_founded = true; }
        else if(str[str.size() - 2] == '/') { slash_position = str.size() - 2; }

        // Format the balise
        std::string final_balise = "";
        if(slash_position_founded) final_balise = std::string("<") + "/" + str.substr(slash_position + 1, str.size() - (2 + slash_position)) + std::string(">");
        else final_balise = std::string("<") + str.substr(1, str.size() - 2) + std::string(">");

        // Format the formatted balise (help)
	    while(final_balise.size() > 0 && final_balise[0] == ' ') {
            final_balise = final_balise.substr(1, final_balise.size() - 1);
	    }
	    while(final_balise.size() > 0 && final_balise[final_balise.size() - 1] == ' ') {
            final_balise = final_balise.substr(0, final_balise.size() - 1);
	    }

        return final_balise;
	};


    // Cut a balise by its XML attributes out of a certain pattern
    std::vector<XML_Attribute> cut_balise_by_xml_attributes_out_of(std::string str, std::string out) {
	    // Cut the balise
	    std::vector<std::string> result = cut_balise_by_attributes_out_of(str, out);
	    std::vector<XML_Attribute> to_return = std::vector<XML_Attribute>();

	    // Create the attributes
	    for(int i = 0;i<static_cast<int>(result.size());i++) {
            // Create the attribute
            std::vector<std::string> cutted = cut_string_out_of(result[i], "=", "\"");
            XML_Attribute current_attribute;
            current_attribute.name = attribute_name(result[i]);
            current_attribute.value = attribute_value(result[i]);

            // Remove the quotes
            if(current_attribute.value.size() > 1 && current_attribute.value[0] == '\"' && current_attribute.value[current_attribute.value.size() - 1] == '\"') {
                current_attribute.value = current_attribute.value.substr(1, current_attribute.value.size() - 2);
                current_attribute.value_use_quotes = true;
            }

            // Add the attribute
            if(current_attribute.name != std::string("")){to_return.push_back(current_attribute);}
	    }

	    return to_return;
	};

	// Returns the first balise with the name
	XML_Text* XML_Text::balise_by_name(std::string name){return balise_by_name_shared_ptr(name).get();}
    std::shared_ptr<XML_Text> XML_Text::balise_by_name_shared_ptr(std::string name) {
        for(int i = 0;i<static_cast<int>(sub_texts().size());i++) {
            if(sub_texts().at(i).get()->xml_balise_name() == name) {return sub_texts().at(i);}
            std::shared_ptr<XML_Text> child = sub_texts().at(i).get()->balise_by_name_shared_ptr(name);
            if(child.get() != 0){return child;}
        }
        return std::shared_ptr<XML_Text>();
    }

	// Checks the include in the text
    void XML_Text::check_include(std::string path) {
        // Analyse each balises
        for(int i = 0;i<static_cast<int>(sub_texts().size());i++) {
            std::shared_ptr<XML_Text> current_text = sub_texts()[i];
            std::string current_balise_name = current_text.get()->xml_balise_name();

            // Add an include
            if(current_balise_name == "include") {
                // Include a part to the XML loading
                std::string src = std::string("");
                for(int j = 0;j<static_cast<int>(current_text.get()->xml_balise_attributes().size());j++) {
                    std::string current_attribute_name = current_text.get()->xml_balise_attributes()[j].name;
                    std::string current_attribute_value = current_text.get()->xml_balise_attributes()[j].value;
                    if(current_attribute_value.size() > 0 && current_attribute_value[0] == '\"'){current_attribute_value = current_attribute_value.substr(1, current_attribute_value.size() - 1);}
                    if(current_attribute_value.size() > 0 && current_attribute_value[current_attribute_value.size() - 1] == '\"'){current_attribute_value = current_attribute_value.substr(0, current_attribute_value.size() - 1);}
                    if(current_attribute_name == "src") {
                        // Get the src of the include
                        src = current_attribute_value;
                    }
                }

                // Include the part
                std::string base_src = src;
                if(!std::filesystem::exists(src)){std::filesystem::path p = path;src = p.parent_path().string() + "/" + src;}
                if(std::filesystem::exists(src)) {
                    unsigned int total_size = 0;
                    char* binary_content = read_entire_file_binary(src, total_size);
                    std::string content_to_parse = std::string();
                    if(binary_content != 0) {
                        for(unsigned int i = 0;i<total_size;i++){
                            if(binary_content[i]!=static_cast<char>(10)&&binary_content[i]!=static_cast<char>(13)){content_to_parse += binary_content[i];}
                            else if(i <= 0 || (binary_content[i - 1]!=static_cast<char>(10)&&binary_content[i - 1]!=static_cast<char>(13))){content_to_parse += ' ';}
                        }
                        delete[] binary_content; binary_content = 0;
                    }

                    // Add the new balises
                    std::shared_ptr<XML_Text> content = std::make_shared<XML_Text>(balise_container_shared_ptr(), content_to_parse);
                    if(content.get()->sub_texts().size() > 0) {
                        sub_texts()[i] = content.get()->sub_texts()[0];
                        for(int j = 1;j<static_cast<int>(content.get()->sub_texts().size());j++){sub_texts().insert(sub_texts().begin() + i + 1, content.get()->sub_texts()[j]);i++;}
                    }
                }
                else {print("Warning", "SCLS XML System", "The \"" + base_src + "\" path you want to include does not exist.");}
            }
            else{current_text.get()->check_include(path);}
        }
    }

    // Parse the text
    void XML_Text::parse_text(std::string new_text) {
        // Cut by balises
        std::vector<_Text_Balise_Part> cutted = cut_string_by_balise(new_text, true);
        a_sub_xml_texts.clear();

        // Create each sub-text
        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i].balise_content.size() > 0 && cutted[i].balise_content[0] == '<') {
                // Create the balise
                std::string needed_balise = formatted_balise(cutted[i].balise_content);
                std::string needed_balise_name = balise_name(needed_balise);
                std::vector<XML_Attribute> needed_balise_attributes = cut_balise_by_xml_attributes_out_of(needed_balise, "\"");
                Balise_Datas* datas = balise_container()->defined_balise(needed_balise_name);
                if(datas != 0 && datas->has_content) {
                    // The part is the end of an opened balise

                    // Get the content of the balise
                    std::string balise_content = "";
                    unsigned int current_level = 1; i++;
                    while(i<static_cast<int>(cutted.size())) {
                        if(cutted[i].balise_content.size() > 0 && cutted[i].balise_content[0] == '<') {
                            std::string current_balise = formatted_balise(cutted[i].balise_content);
                            std::string current_balise_name = balise_name(current_balise);
                            if(current_balise_name == needed_balise_name) {
                                if(closing_balise(current_balise)){current_level--;}
                                else{current_level++;}

                                if(current_level <= 0){break;}
                                else{balise_content += cutted[i].total_content();}
                            }
                            else { balise_content += cutted[i].total_content(); }
                        }
                        else { balise_content += cutted[i].total_content(); }
                        i++;
                    } balise_content = format_for_xml(balise_content);

                    // Create the balise
                    std::shared_ptr<XML_Text> to_add = std::make_shared<XML_Text>(a_balise_container, needed_balise_name, needed_balise_attributes, balise_content);
                    if(datas != 0){to_add.get()->set_xml_balise_datas(datas);}
                    a_sub_xml_texts.push_back(to_add);
                }
                else {
                    // The part is a single balise
                    // Create the balise
                    std::shared_ptr<XML_Text> to_add = std::make_shared<XML_Text>(a_balise_container, needed_balise_name, needed_balise_attributes, cutted[i].content);
                    if(datas != 0){to_add.get()->set_xml_balise_datas(datas);}
                    else{Balise_Datas current_data = Balise_Datas(false);to_add.get()->set_xml_balise_datas(&current_data);}
                    a_sub_xml_texts.push_back(to_add);
                }
            }
            else {
                std::string content = format_for_xml(cutted[i].total_content());
                if(static_cast<int>(cutted.size()) <= 1) {a_xml_text = content;}
                else {
                    if(content != "") {
                        // The part is not a balise
                        std::shared_ptr<XML_Text> to_add = std::make_shared<XML_Text>(a_balise_container, content, true);
                        a_sub_xml_texts.push_back(to_add);
                    }
                }
            }
        }
    };

    // Returns the full text in the XML text
    std::string XML_Text::full_text(bool add_balise) const {
        std::string to_return = std::string();
        if(add_balise && a_balise_name != ""){to_return = xml_balise();}

        if(only_text()){to_return = to_return + text();}
        else if(a_balise_datas.has_content) {
            // Add the inner text
            for(int i = 0;i<static_cast<int>(a_sub_xml_texts.size());i++){to_return += a_sub_xml_texts[i].get()->full_text();}
        }

        // Add the closing balise
        if(add_balise && a_balise_name != "" && a_balise_datas.has_content){to_return += xml_balise_end();}

        return to_return;
    }

    // Removes the first balise with a precise name and returns it
    std::shared_ptr<XML_Text> XML_Text::remove_balise_by_name(std::string name) {
        std::shared_ptr<XML_Text> to_return;
        for(int i = 0;i<static_cast<int>(sub_texts().size());i++) {
            if(sub_texts().at(i).get()->xml_balise_name() == name) {
                to_return = sub_texts().at(i);
                sub_texts().erase(sub_texts().begin() + i);
                break;
            }
        }
        return to_return;
    }

    // Replace all balise with another balise
    void XML_Text::replace_balise_by_name(std::string name, std::string new_balise_name, std::vector<XML_Attribute>& new_balise_attributes) {
        for(int i = 0;i<static_cast<int>(sub_texts().size());i++) {
            if(sub_texts().at(i).get()->xml_balise_name() == name) {
                sub_texts().at(i).get()->set_xml_balise_name(new_balise_name);
                sub_texts().at(i).get()->xml_attributes() = new_balise_attributes;
            }
            sub_texts().at(i).get()->replace_balise_by_name(name, new_balise_name, new_balise_attributes);
        }
    }
    void XML_Text::replace_balise_by_name(std::string name, std::string new_name){std::vector<XML_Attribute> new_balise_attributes = cut_balise_by_xml_attributes_out_of(new_name, "\"");std::string new_balise_name = balise_name(new_name);replace_balise_by_name(name, new_balise_name, new_balise_attributes);}

    // Returns the text in the balise
    std::string XML_Text::xml_balise() const {
        std::string attribute = "";
        for(int i = 0;i<static_cast<int>(a_balise_attributes.size());i++){
            attribute += a_balise_attributes.at(i).name + std::string("=");

            // Add the value
            bool contains_space = scls::contains_string(a_balise_attributes.at(i).value, std::string(" "));
            if(contains_space){attribute += "\"";}
            attribute += a_balise_attributes.at(i).value;
            if(contains_space){attribute += "\"";}

            if(i < static_cast<int>(a_balise_attributes.size())){attribute+=std::string(" ");}}
            if(attribute.size()>0){attribute=std::string(" ")+attribute;
        }
        return std::string("<") + xml_balise_name() + attribute + std::string(">");
    };

    // Returns the position of the first plain text character in a unformatted text from before a position
    unsigned int __Balise_Container::first_plain_text_character_before_position_in_informatted_text(const std::string& text_to_convert, int position) {
        if(text_to_convert[position] == '>') {
            // Remove balises
            while(text_to_convert[position] != '<' && position > 0) { position--; }
        } else if(text_to_convert[position] == ';') {
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
        } else if(text_to_convert[position] == '&') {
            // Handle & character
            position--;
        } return position;
    };
    // Returns a html text in plain text
    std::string __Balise_Container::plain_text(std::string text_to_convert) {
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
    // Returns a unformatted text position in a plain text
    unsigned int __Balise_Container::plain_text_position_to_unformatted_text_position(std::string text_to_convert, int position) {
        int final_position = 0;
        for(int i = 0;i<static_cast<int>(text_to_convert.size()) && i < position;i++) {
            if(text_to_convert[final_position] == '<') {
                // Remove balises
                while(text_to_convert[final_position] != '>' && final_position < static_cast<int>(text_to_convert.size())) final_position++;
            }
            else if(text_to_convert[final_position] == '&') {
                // Check if a simple & must be added
                if(final_position + 1 < static_cast<int>(text_to_convert.size()) && text_to_convert[final_position + 1] == '&') {final_position++;}
                else {
                    // Remove special insertion
                    std::string part_content = "";
                    const int start_position = final_position;
                    while(text_to_convert[final_position] != ';' && final_position < static_cast<int>(text_to_convert.size())) {
                        part_content += text_to_convert[final_position];
                        final_position++;
                    } part_content = part_content.substr(1, part_content.size() - 1);

                    if(!(part_content == "lt" || part_content == "gt") || final_position >= static_cast<int>(text_to_convert.size())) {
                        final_position = start_position;
                    }
                }
            } final_position++;
        } return final_position;
    };

    // Returns the balise of the block or a blank string if it is not
    std::string __Balise_Container::__block_balise(std::vector<_Text_Balise_Part>& cutted) {
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
    // Cut a block by its sub_blocks and spaces
    std::vector<_Text_Balise_Part> __Balise_Container::__cut_block(std::string block_text) {
        std::vector<_Text_Balise_Part> first_cutted = cut_string_by_balise(block_text, false, true);
        std::vector<_Text_Balise_Part> cutted = std::vector<_Text_Balise_Part>();
        for(int i = 0;i<static_cast<int>(first_cutted.size());i++) {
            if(first_cutted[i].balise_content.size() > 0 && first_cutted[i].balise_content[0] == '<') {
                // This part is a balise
                std::string needed_balise_name = balise_name(formatted_balise(first_cutted[i].balise_content));
                _Text_Balise_Part to_add = first_cutted[i];
                if(contains_defined_balise(needed_balise_name)) {
                    Balise_Datas* datas = defined_balise(needed_balise_name);
                    if(datas->has_content) {
                        // The balise contains a content
                        i++; int level = 1;
                        while(i<static_cast<int>(first_cutted.size())) {
                            if(first_cutted[i].balise_content.size() > 0 && first_cutted[i].balise_content[0] == '<') {
                                std::string formated = formatted_balise(first_cutted[i].balise_content);
                                std::string current_balise_name = balise_name(formated);
                                if(current_balise_name == needed_balise_name) {
                                    if(closing_balise(formated)) {level--;} else {level++;}
                                    if(level <= 0){to_add.balise_end_content = first_cutted[i].total_content();break;}
                                } to_add.content += first_cutted[i].total_content();
                            } else {
                                to_add.content += first_cutted[i].total_content();
                            } i++;
                        }
                    }
                } cutted.push_back(to_add);
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
    std::vector<std::string> __Balise_Container::__cut_multi_block(std::string block_text) {
        std::vector<_Text_Balise_Part> first_cutted = cut_string_by_balise(block_text, false, true);
        std::string last_text = "";
        std::vector<std::string> to_return = std::vector<std::string>();
        for(int i = 0;i<static_cast<int>(first_cutted.size());i++) {
            if(first_cutted[i].balise_content.size() > 0 && first_cutted[i].balise_content[0] == '<') {
                // A sub-block is here
                std::string current_balise_name = balise_name(formatted_balise(first_cutted[i].balise_content));
                if(contains_defined_balise(current_balise_name) && defined_balise(current_balise_name)->is_paragraph) {
                    // Save the last empty paragraph
                    to_return.push_back(last_text); last_text = "";

                    i++;
                    unsigned int level = 1;
                    std::string total_text = "";
                    while(i<static_cast<int>(first_cutted.size())) {
                        if(first_cutted[i].balise_content.size() > 0 && first_cutted[i].balise_content[0] == '<') {
                            first_cutted[i].balise_content = formatted_balise(first_cutted[i].balise_content);
                            std::string next_balise_name = balise_name(first_cutted[i].balise_content);
                            if(next_balise_name == current_balise_name) {
                                if(closing_balise(first_cutted[i].balise_content)) {level--;}else {level++;}
                                if(level <= 0) break;
                            }
                        }
                        total_text += first_cutted[i].total_content();
                        i++;
                    }

                    // Create the block datas
                    to_return.push_back(total_text);
                }
                else {
                    last_text += first_cutted[i].total_content();
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

    // Load the built-ins balises for the GUI loading
    void __Balise_Container::__load_built_in_balises_gui() {
        std::shared_ptr<Balise_Datas> current_balise;
        // Create the <choice> style
        current_balise = std::make_shared<Balise_Datas>();
        current_balise.get()->has_content = true;
        set_defined_balise("choice", current_balise);
        // Create the <content> style
        current_balise = std::make_shared<Balise_Datas>();
        current_balise.get()->has_content = true;
        set_defined_balise("content", current_balise);
        // Create the <gui_object> style
        current_balise = std::make_shared<Balise_Datas>();
        current_balise.get()->has_content = true;
        set_defined_balise("gui_object", current_balise);
        // Create the <sub_choice> style
        current_balise = std::make_shared<Balise_Datas>();
        current_balise.get()->has_content = true;
        set_defined_balise("sub_choice", current_balise);
        // Create the <when> style
        current_balise = std::make_shared<Balise_Datas>();
        current_balise.get()->has_content = true;
        set_defined_balise("when", current_balise);
    }

    // Load the built-ins balises for the window loading
    void __Balise_Container::__load_built_in_balises_window() {
        std::shared_ptr<Balise_Datas> current_balise;
        // Create the <page_2d> style
        current_balise = std::make_shared<Balise_Datas>();
        current_balise.get()->has_content = true;
        set_defined_balise("page_2d", current_balise);
    }

    // Create an XML simply from a text (the returned XML is not a balise itself, but has balises children)
	std::shared_ptr<XML_Text> xml(std::shared_ptr<__Balise_Container> balises, std::string content) {std::shared_ptr<XML_Text> to_return = std::make_shared<XML_Text>(balises, content);return to_return;}

    //*********
	//
	// The String class
	//
	//*********

    // Flux output operator of String
    std::ostream& operator<<(std::ostream& strm, const String& str) {const char* to_out = str.to_char_array();strm << to_out;return strm;}
}
