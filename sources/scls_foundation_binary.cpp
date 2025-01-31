//******************
//
// scls_foundation_binary.cpp
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
// This file contains the source code of scls_foundation_binary.h.
//
//******************
// Warning :
//
// Using binary can cause troubles if you don't know what you do.
// Be very careful with that.
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
#include "../scls_foundation_directory/scls_foundation_binary.h"

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// Binary handling (hidden functions)
	//
	//*********

	// Extract a 2 bytes variable (short) from a char array
    short __extract_2bytes_from_char_array(char* result, unsigned int offset, bool big_endian) {
		short number_1 = 0;
		short number_2 = 0;
		if (big_endian) {
			number_1 = ((static_cast<short>(result[offset]) << 8) & 0xff00);
			number_2 = (static_cast<short>(result[offset + 1]) & 0xff);
		}
		else
		{
			number_1 = ((static_cast<short>(result[offset + 1]) << 8) & 0xff00);
			number_2 = (static_cast<short>(result[offset]) & 0xff);
		}

		return number_1 + number_2;
	};

	// Extract a 2 bytes variable (unsigned short) from a char array
    unsigned short __extract_u2bytes_from_char_array(char* result, unsigned int offset, bool big_endian) {
		unsigned short number_1 = 0;
		unsigned short number_2 = 0;
		if (big_endian)
		{
			number_1 = ((static_cast<unsigned short>(result[offset]) << 8) & 0xff00);
			number_2 = (static_cast<unsigned short>(result[offset + 1]) & 0xff);
		}
		else
		{
			number_1 = ((static_cast<unsigned short>(result[offset + 1]) << 8) & 0xff00);
			number_2 = (static_cast<unsigned short>(result[offset]) & 0xff);
		}

		return number_1 + number_2;
	};

	// Extract a 4 bytes variable from a char array
    int __extract_4bytes_from_char_array(char* result, unsigned int offset, bool big_endian) {
		int number_1 = 0;
		int number_2 = 0;
		int number_3 = 0;
		int number_4 = 0;
		if (big_endian)
		{
			number_1 = ((static_cast<int>(result[offset + 0]) << 24) & 0xff000000);
			number_2 = ((static_cast<int>(result[offset + 1]) << 16) & 0x00ff0000);
			number_3 = ((static_cast<int>(result[offset + 2]) << 8) & 0x0000ff00);
			number_4 = (static_cast<int>(result[offset + 3]) & 0x000000ff);
		}
		else
		{
			number_1 = ((static_cast<int>(result[offset + 3]) << 24) & 0xff000000);
			number_2 = ((static_cast<int>(result[offset + 2]) << 16) & 0x00ff0000);
			number_3 = ((static_cast<int>(result[offset + 1]) << 8) & 0x0000ff00);
			number_4 = (static_cast<int>(result[offset]) & 0x000000ff);
		}

		return number_1 + number_2 + number_3 + number_4;
	};

	// Extract a 4 bytes unsigned variable from a char array
    unsigned int __extract_u4bytes_from_char_array(char* result, unsigned int offset, bool big_endian) {
		unsigned int number_1 = 0;
		unsigned int number_2 = 0;
		unsigned int number_3 = 0;
		unsigned int number_4 = 0;
		if (big_endian)
		{
			number_1 = ((static_cast<unsigned int>(result[offset + 0]) << 24) & 0xff000000);
			number_2 = ((static_cast<unsigned int>(result[offset + 1]) << 16) & 0x00ff0000);
			number_3 = ((static_cast<unsigned int>(result[offset + 2]) << 8) & 0x0000ff00);
			number_4 = (static_cast<unsigned int>(result[offset + 3]) & 0x000000ff);
		}
		else
		{
			number_1 = ((static_cast<unsigned int>(result[offset + 3]) << 24) & 0xff000000);
			number_2 = ((static_cast<unsigned int>(result[offset + 2]) << 16) & 0x00ff0000);
			number_3 = ((static_cast<unsigned int>(result[offset + 1]) << 8) & 0x0000ff00);
			number_4 = (static_cast<unsigned int>(result[offset]) & 0x000000ff);
		}

		return number_1 + number_2 + number_3 + number_4;
	};

	// Extract a 8 bytes variable from a char array
    int64_t __extract_8bytes_from_char_array(char* result, unsigned int offset, bool big_endian) {
		int64_t number_1 = 0;
		int64_t number_2 = 0;
		int64_t number_3 = 0;
		int64_t number_4 = 0;
		int64_t number_5 = 0;
		int64_t number_6 = 0;
		int64_t number_7 = 0;
		int64_t number_8 = 0;
		if (big_endian)
		{
			number_1 = ((static_cast<int64_t>(result[offset]) << 56) & 0xff00000000000000);
			number_2 = ((static_cast<int64_t>(result[offset + 1]) << 48) & 0x00ff000000000000);
			number_3 = ((static_cast<int64_t>(result[offset + 2]) << 40) & 0x0000ff0000000000);
			number_4 = ((static_cast<int64_t>(result[offset + 3]) << 32) & 0x000000ff00000000);
			number_5 = ((static_cast<int64_t>(result[offset + 4]) << 24) & 0x00000000ff000000);
			number_6 = ((static_cast<int64_t>(result[offset + 5]) << 16) & 0x0000000000ff0000);
			number_7 = ((static_cast<int64_t>(result[offset + 6]) << 8) & 0x000000000000ff00);
			number_8 = ((static_cast<int64_t>(result[offset + 7])) & 0x00000000000000ff);
		}
		else
		{
			number_1 = ((static_cast<int64_t>(result[offset + 7]) << 56) & 0xff00000000000000);
			number_2 = ((static_cast<int64_t>(result[offset + 6]) << 48) & 0x00ff000000000000);
			number_3 = ((static_cast<int64_t>(result[offset + 5]) << 40) & 0x0000ff0000000000);
			number_4 = ((static_cast<int64_t>(result[offset + 4]) << 32) & 0x000000ff00000000);
			number_5 = ((static_cast<int64_t>(result[offset + 3]) << 24) & 0x00000000ff000000);
			number_6 = ((static_cast<int64_t>(result[offset + 2]) << 16) & 0x0000000000ff0000);
			number_7 = ((static_cast<int64_t>(result[offset + 1]) << 8) & 0x000000000000ff00);
			number_8 = ((static_cast<int64_t>(result[offset])) & 0x00000000000000ff);
		}

		return number_1 + number_2 + number_3 + number_4 + number_5 + number_6 + number_7 + number_8;
	};

	// Extract a double variable from a char array
    double __extract_double_from_char_array(char* result, unsigned int offset, bool big_endian) {
		int64_t number_1 = __extract_8bytes_from_char_array(result, offset, big_endian);
		double* d = (double*)(&number_1);
		double number = (*d);

		return number;
	};

	// Convert an integer to a char array and put it in the char array
    void __put_2bytes_to_char_array(short n, char* result, unsigned int offset, bool big_endian) {
		if (big_endian)
		{
			result[offset + 1] = (n & 0x000000ff);
			result[offset] = (n & 0x0000ff00) >> 8;
		}
		else
		{
			result[offset] = (n & 0x000000ff);
			result[offset + 1] = (n & 0x0000ff00) >> 8;
		}
	}

	// Convert an integer to a char array and put it in the char array
    void __put_2bytes_to_char_array(unsigned short n, char* result, unsigned int offset, bool big_endian) {
		if (big_endian)
		{
			result[offset + 1] = (n & 0x000000ff);
			result[offset] = (n & 0x0000ff00) >> 8;
		}
		else
		{
			result[offset] = (n & 0x000000ff);
			result[offset + 1] = (n & 0x0000ff00) >> 8;
		}
	}

	// Convert an integer to a char array and put it in the char array
    void __put_4bytes_to_char_array(int n, char* result, unsigned int offset, bool big_endian) {
		if (big_endian)
		{
			result[offset + 3] = (n & 0x000000ff);
			result[offset + 2] = (n & 0x0000ff00) >> 8;
			result[offset + 1] = (n & 0x00ff0000) >> 16;
			result[offset] = (n & 0xff000000) >> 24;
		}
		else
		{
			result[offset] = (n & 0x000000ff);
			result[offset + 1] = (n & 0x0000ff00) >> 8;
			result[offset + 2] = (n & 0x00ff0000) >> 16;
			result[offset + 3] = (n & 0xff000000) >> 24;
		}
	}

	// Convert an unsigned integer to a char array and put it in the char array
    void __put_4bytes_to_char_array(unsigned int n, char* result, unsigned int offset, bool big_endian) {
		if (big_endian)
		{
			result[offset + 3] = (n & 0x000000ff);
			result[offset + 2] = (n & 0x0000ff00) >> 8;
			result[offset + 1] = (n & 0x00ff0000) >> 16;
			result[offset] = (n & 0xff000000) >> 24;
		}
		else
		{
			result[offset] = (n & 0x000000ff);
			result[offset + 1] = (n & 0x0000ff00) >> 8;
			result[offset + 2] = (n & 0x00ff0000) >> 16;
			result[offset + 3] = (n & 0xff000000) >> 24;
		}
	}

	// Convert an integer to a char array and put it in the char array
    void __put_8bytes_to_char_array(int64_t n, char* result, unsigned int offset, bool big_endian) {
		if (big_endian)
		{
			result[offset + 7] = static_cast<char>(n & 0x00000000000000ff);
			result[offset + 6] = static_cast<char>((n & 0x000000000000ff00) >> 8);
			result[offset + 5] = static_cast<char>((n & 0x0000000000ff0000) >> 16);
			result[offset + 4] = static_cast<char>((n & 0x00000000ff000000) >> 24);
			result[offset + 3] = static_cast<char>((n & 0x000000ff00000000) >> 32);
			result[offset + 2] = static_cast<char>((n & 0x0000ff0000000000) >> 40);
			result[offset + 1] = static_cast<char>((n & 0x00ff000000000000) >> 48);
			result[offset] = static_cast<char>((n & 0xff00000000000000) >> 56);
		}
		else
		{
			result[offset] = static_cast<char>((n & 0x00000000000000ff));
			result[offset + 1] = static_cast<char>((n & 0x000000000000ff00) >> 8);
			result[offset + 2] = static_cast<char>((n & 0x0000000000ff0000) >> 16);
			result[offset + 3] = static_cast<char>((n & 0x00000000ff000000) >> 24);
			result[offset + 4] = static_cast<char>((n & 0x000000ff00000000) >> 32);
			result[offset + 5] = static_cast<char>((n & 0x0000ff0000000000) >> 40);
			result[offset + 6] = static_cast<char>((n & 0x00ff000000000000) >> 48);
			result[offset + 7] = static_cast<char>((n & 0xff00000000000000) >> 56);
		}
	}

	// Convert a float to a char array and put it in the char array
    void __put_4bytes_float_to_char_array(float n, char* result, unsigned int offset, bool big_endian) {int* n_p = (int*)(&n);__put_4bytes_to_char_array(*n_p, result, offset, big_endian);}

	// Convert an double to a char array and put it in the char array
    void __put_8bytes_double_to_char_array(double n, char* result, unsigned int offset, bool big_endian) {int64_t* n_p = (int64_t*)(&n);__put_8bytes_to_char_array(*n_p, result, offset, big_endian);}

    //*********
	//
	// Binary handling
	//
	//*********

	// Reflect the bits into a char and return it
    char reflect_char(char x) {
        for(int i = 0;i<4;i++) {
            char n1 = (x >> i) & 1;
            char n2 = (x >> (7 - i)) & 1;

            x -= (n1 << i) + (n2 << (7 - i));

            n1 = (n1 << (7 - i));
            n2 = (n2 << i);

            x += n1 + n2;
        }

        return x;
    }

    // Reflect the bits into an unsigned char and return it
    unsigned char reflect_char(unsigned char x) {
        for(int i = 0;i<4;i++) {
            unsigned char n1 = (x >> i) & 1;
            unsigned char n2 = (x >> (7 - i)) & 1;

            x -= (n1 << i) + (n2 << (7 - i));

            n1 = (n1 << (7 - i));
            n2 = (n2 << i);

            x += n1 + n2;
        }

        return x;
    }

    // Reflect the bits into an unsigned int and return it
    int reflect_int(int x) {
        for(int i = 0;i<16;i++) {
            int n1 = (x >> i) & 1;
            int n2 = (x >> (31 - i)) & 1;

            x -= (n1 << i) + (n2 << (31 - i));

            n1 = (n1 << (31 - i));
            n2 = (n2 << i);

            x += n1 + n2;
        }

        return x;
    }

    // Reflect the bits into an unsigned int and return it
    unsigned int reflect_int(unsigned int x) {
        for(int i = 0;i<16;i++) {
            unsigned int n1 = (x >> i) & 1;
            unsigned int n2 = (x >> (31 - i)) & 1;

            x -= (n1 << i) + (n2 << (31 - i));

            n1 = (n1 << (31 - i));
            n2 = (n2 << i);

            x += n1 + n2;
        }

        return x;
    }

    // Return the content of a file in binary with a char array
    void read_file_binary(std::string path, char* datas, unsigned int size, unsigned int start_pos) {
		std::string file_content;
		std::ifstream file;
		// ensure ifstream objects can throw exceptions:
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			file.open(path, std::ios::binary);
			file.seekg(start_pos, file.beg);
			file.read(datas, size);
			file.close();
		} catch (std::ifstream::failure& e) { print("Error", "System", "The file \"" + path + "\" can't be opened, error -> " + e.what() + "."); }
	};

	// Read and return the content of all a binary file
    char* read_entire_file_binary(std::string path, unsigned int& total_size) {
	    // Get the size of the file
	    if(!std::filesystem::exists(path)) return 0;
		total_size = static_cast<unsigned int>(std::filesystem::file_size(path));

		// Get the content of the file
		char* file = new char[total_size];
		read_file_binary(path, file, total_size);

		return file;
	};

	// Write binary data in a file from a char array
    void write_in_file_binary(std::string path, char* to_write, unsigned int size, std::ios::openmode opening_mode) {
		std::ofstream file;
		file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		try {
			file.open(path, opening_mode);
			file.write(to_write, size);
			file.close();
		} catch (std::ofstream::failure& e) {
			print("Error", "System", "The file \"" + path + "\" can't be written in error -> " + e.what() + ".");
		}
	}

    //*********
	//
	// CRC calculation
	//
	//*********

	// Map of each loaded CRC table
    std::map<std::string, CRC_32B_Datas> _loaded_crc_32b_algorithms = std::map<std::string, CRC_32B_Datas>();

	// Return if a CRC 32 bits table is loaded or not
    bool contains_crc_32b(std::string name) {
        for(std::map<std::string, CRC_32B_Datas>::iterator it = _loaded_crc_32b_algorithms.begin();it != _loaded_crc_32b_algorithms.end();it++) {
            if(it->first == name) return true;
        }
	    return false;
	};

	// Make the entire CRC table of a 32 bits CRC algorithm
    void make_crc_32b_table(std::string name, unsigned int polymonial, bool reflect_input, bool reflect_output, unsigned int starting_value, unsigned int xor_final) {
		if(contains_crc_32b(name)) {
            print("Warning", "SCLS CRC generator", "The CRC 32 bits algorithm \"" + name + "\" you want to create already exist.");
            return;
		}

		// Create the CRC_32B_Datas
		CRC_32B_Datas datas; datas.polymonial = polymonial; datas.reflect_input = reflect_input; datas.reflect_output = reflect_output;
		datas.starting_value = starting_value; datas.xor_final = xor_final;

		// Create the CRC values
		unsigned int c = 0;
		for (int n = 0; n < 256; n++)
		{
			c = static_cast<unsigned int>(n);
			for (int k = 0; k < 8; k++)
			{
				if (c & 1) c = static_cast<unsigned int>(reflect_int(datas.polymonial)) ^ (c >> 1);
				else c = c >> 1;
			}
			datas.crc_values[n] = static_cast<unsigned int>(c);
		}

		// Set the datas
		_loaded_crc_32b_algorithms[name] = datas;
	};

	// Returns a reference to the CRC 32 bits algorithm with the name
    CRC_32B_Datas* get_crc_32b_data(std::string name) {
        if(contains_crc_32b(name)) return &_loaded_crc_32b_algorithms[name];
        print("Warning", "SCLS CRC handler", "The \"" + name + "\" CRC 32 bits algorithm you want to get does not exist.");
        return 0;
	};

	// Return the CRC of the char array
    unsigned int crc_32b(char* buf, int len, std::string crc_name) {
	    // Check if the CRC algorithm exists
	    if (!contains_crc_32b(crc_name)) {
            if(crc_name != "png") {
                print("Warning", "SCLS CRC handler", "The \"" + crc_name + "\" CRC 32 bits algorithm you want to process does not exist.");
                return 0;
            }
            make_crc_32b_table(crc_name, PNG_CRC_POLYMONIAL, true, true, 0xffffffff, 0xffffffff);
	    }

	    // Create the CRC
	    CRC_32B_Datas* datas = get_crc_32b_data(crc_name);
	    unsigned int c = datas->starting_value;
	    if(datas->reflect_input)
        {
            for (int n = 0; n < len; n++) {
                c = datas->crc_values[(c ^ buf[n]) & 0xff] ^ (c >> 8);
            }
        }
        else {
            for (int n = 0; n < len; n++) {
                c = datas->crc_values[(c ^ reflect_char(buf[n])) & 0xff] ^ (c >> 8);
            }
        }
        if(!datas->reflect_output) c = reflect_int(c);

		return c ^ datas->xor_final;
	};

    // Return the CRC of the char array
    unsigned int crc_32b(unsigned char* buf, int len, std::string crc_name) {
	    // Check if the CRC algorithm exists
	    if (!contains_crc_32b(crc_name)) {
            if(crc_name != "png") {
                print("Warning", "SCLS CRC handler", "The \"" + crc_name + "\" CRC 32 bits algorithm you want to process does not exist.");
                return 0;
            }
            make_crc_32b_table(crc_name, PNG_CRC_POLYMONIAL, true, true, 0xffffffff, 0xffffffff);
	    }

	    // Create the CRC
	    CRC_32B_Datas* datas = get_crc_32b_data(crc_name);
	    unsigned int c = datas->starting_value;
	    if(datas->reflect_input)
        {
            for (int n = 0; n < len; n++)
            {
                c = datas->crc_values[(c ^ buf[n]) & 0xff] ^ (c >> 8);
            }
        }
        else
        {
            for (int n = 0; n < len; n++)
            {
                c = datas->crc_values[(c ^ reflect_char(buf[n])) & 0xff] ^ (c >> 8);
            }
        }
        if(!datas->reflect_output) c = reflect_int(c);

		return c ^ datas->xor_final;
	};
}
