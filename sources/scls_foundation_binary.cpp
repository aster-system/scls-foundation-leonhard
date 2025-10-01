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

	//*********
	//
	// The Bytes_Set class
	//
	//*********

	// Returns the bit to std::string
    std::string Bytes_Set::bits_to_std_string() {
        std::string to_return = std::string();

        for(int i = 0;i<datas_size() * 8;i++) {
            if(data_at_bit_directly(i)){to_return += '1';}
            else{to_return += '0';}
        }

        return to_return;
    }

    // Returns the char at a certain position
    bool Bytes_Set::data_at_bit_directly(int position) {
        int byte_position = position / 8;
        char final_data = std::pow(2, position % 8);
        return (a_datas[byte_position] & final_data) >> (position % 8);
    }

	// Put datas in the Bytes_Set
    void Bytes_Set::put_datas(Bytes_Set* datas_to_put, unsigned int offset) {
        if(offset + datas_to_put->datas_size() <= datas_size()) {
            for(int i = 0;i<static_cast<int>(datas_to_put->datas_size());i++) {
                a_datas[offset + i] =
                datas_to_put->a_datas[i];
            }
        }
    };

    // Sets the bit at a certain position
    void Bytes_Set::set_data_at_bit(int position, bool data) {
        int byte_position = position / 8;
        unsigned char temp = std::pow(2, 7 - position % 8);
        char final_data = *reinterpret_cast<char*>(&temp);
        //std::cout << "J " << (data ? "1" : "0") << " " << Bytes_Set::from_char(a_datas[byte_position]).bits_to_std_string() << std::endl;
        if(data){a_datas[byte_position] = (a_datas[byte_position] | final_data);}
        else{a_datas[byte_position] = (a_datas[byte_position] & ~final_data);}
        //std::cout << "I " << Bytes_Set::from_char(final_data).bits_to_std_string() << " " << Bytes_Set::from_char(a_datas[byte_position]).bits_to_std_string() << std::endl;
    }
}
