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

#define BASIX_NAME "Basix"

#include <iostream>
#include <math.h>
#include <string>
#include <vector>

// The namespace "basix" is used to simplify the all.
namespace basix
{
    // Variables used to define a float separation character
	static std::string _float_character = "";
	static std::string _non_float_character = "";

	//*********
	//
	// Debugging helper (100% developed)
	//
	//*********

	// Static vector of each authorized sender to be printed
	static std::vector<std::string> _authorized_sender = std::vector<std::string>();
	// Static vector of each authorized type to be printed
	static std::vector<std::string> _authorized_type = std::vector<std::string>();

	// Static bool, usefull in debugging to tell to Basix if the "print" function is enable or not
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

	// Cut a string in a vector where there are the "cut" part
	inline std::vector<std::string> cut_string(std::string string, std::string cut, bool erase_blank = false) {
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

		if (last_string.size() > 0) { result.push_back(last_string); } // Add the last non-cutted element
		return result;
	};

	// Inverse a char array
	inline void inverse_char_array(char* array, unsigned int size) {
		for (int i = 0; i < floor(size / 2.0); i++)
		{
			char temp = array[i];
			array[i] = array[size - (i + 1)];
			array[size - (i + 1)] = temp;
		}
	};

	// Join a vector of string into one string.
	inline std::string join_string(std::vector<std::string> strings, std::string separation) {
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
		return join_string(cut_string(str, to_replace), new_str);
	};

	// Convert a string to a double
	inline double string_to_double(std::string str) {
		if (_float_character == "")
		{
			_float_character = ".";
			_non_float_character = ",";
			if (std::stod("0.25") != 0.25) // Test if the "." is the separation character
			{
				_float_character = ",";
				_non_float_character = ".";
			}
		}

		return std::stod(replace(str, _non_float_character, _float_character));
	}

	// Swap a buffer
	template<typename T>
	inline std::vector<T> swap_vector(std::vector<T> v) {
	    for (int i = 0; i < floor((float)v.size() / 2.0); i++)
		{
			T temp = v[i];
			v[i] = v[v.size() - (i + 1)];
			v[i + 1] = temp;
		}
		return v;
	};

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
    inline std::string to_utf_8(std::string character) {
        std::string result = "";
        for(int i = 0;i<static_cast<int>(character.size());i++)
        {
            if(~character[i] & 0b10000000)
            {
                result += character[i];
            }
            else if((character[i] & 0b11100000) == 0b11100000)
            {
                unsigned short final_character_1 = 0;
                unsigned short final_character_2 = 0;
                unsigned short final_character_3 = 0;
                final_character_1 = (character[i]) & 0b00001111; final_character_1 = final_character_1 << 11; i++;
                final_character_2 = (character[i]) & 0b00011111; final_character_2 = final_character_2 << 6; i++;
                final_character_3 = character[i] & 0b00111111;
                result += static_cast<char>(final_character_1 + final_character_2 + final_character_3);
            }
            else if((character[i] & 0b11000000) == 0b11000000)
            {
                unsigned short final_character_1 = 0;
                unsigned short final_character_2 = 0;
                final_character_1 = (character[i]) & 0b00011111; final_character_1 = final_character_1 << 6; i++;
                final_character_2 = character[i] & 0b00111111;
                result += static_cast<char>(final_character_1 + final_character_2);
            }
        }
        return result;
    };
}

#endif
