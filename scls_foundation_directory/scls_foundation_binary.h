//******************
//
// scls_foundation_binary.h
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
// This file contains stuff used to do some binary manipulation.
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

#ifndef SCLS_FOUNDATION_BINARY
#define SCLS_FOUNDATION_BINARY

#include <map>
#include "scls_foundation_core.h"
#include "scls_foundation_math.h"

#define PNG_CRC_POLYMONIAL 0x04c11db7

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// Binary handling (hidden functions)
	//
	//*********

	// Extract a 2 bytes variable (unsigned or signed short) from a char array
    short __extract_2bytes_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false);
	unsigned short __extract_u2bytes_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false);
	// Extract a 4 bytes variable (unsigned or signed int) from a char array
    int __extract_4bytes_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false);
    unsigned int __extract_u4bytes_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false);
	// Extract a 8 bytes variable from a char array
    int64_t __extract_8bytes_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false);
	// Extract a double variable from a char array
    double __extract_double_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false);

	// Convert an (possible unsigned) integer to a char array and put it in the char array
    void __put_2bytes_to_char_array(short n, char* result, unsigned int offset = 0, bool big_endian = false);
    void __put_2bytes_to_char_array(unsigned short n, char* result, unsigned int offset = 0, bool big_endian = false);
	// Convert an (possible unsigned) integer to a char array and put it in the char array
    void __put_4bytes_to_char_array(int n, char* result, unsigned int offset = 0, bool big_endian = false);
	void __put_4bytes_to_char_array(unsigned int n, char* result, unsigned int offset = 0, bool big_endian = false);
    // Convert an integer to a char array and put it in the char array
    void __put_8bytes_to_char_array(int64_t n, char* result, unsigned int offset = 0, bool big_endian = false);
	// Convert a double / float to a char array and put it in the char array
    void __put_4bytes_float_to_char_array(float n, char* result, unsigned int offset = 0, bool big_endian = false);
    void __put_8bytes_double_to_char_array(double n, char* result, unsigned int offset = 0, bool big_endian = false);

    //*********
	//
	// Binary handling
	//
	//*********

	// Reflect the bits into a (possibly unsigned) char and return it
    char reflect_char(char x);
    unsigned char reflect_char(unsigned char x);
    // Reflect the bits into an (possibly unsigned) int and return it
    int reflect_int(int x);
    unsigned int reflect_int(unsigned int x);

	//*********
	//
	// Binary file handling
	//
	//*********

	// Return the content of a file in binary with a char array (passed as an argument or returned)
    void read_file_binary(std::string path, char* datas, unsigned int size, unsigned int start_pos = 0);
    char* read_entire_file_binary(std::string path, unsigned int& total_size);
	// Write binary data in a file from a char array
    void write_in_file_binary(std::string path, char* to_write, unsigned int size, std::ios::openmode opening_mode = std::ios::out | std::ios::binary);

	//*********
	//
	// CRC calculation
	//
	//*********

	struct CRC_32B_Datas {
	    // Struct representing datas about a CRC table

	    // All values generated for this CRC
	    unsigned int crc_values[256];
	    // Value of the polymonial of the CRC
	    unsigned int polymonial = PNG_CRC_POLYMONIAL;
	    // If the input datas is reflected or not
	    bool reflect_input = true;
	    // If the output datas is reflected or not
	    bool reflect_output = true;
	    // Starting value of the CRC
	    unsigned int starting_value = 0xffffffff;
	    // Value of the final XOR applied to the CRC
	    unsigned int xor_final = 0xffffffff;
	};

	// Return if a CRC 32 bits table is loaded or not
    bool contains_crc_32b(std::string name);
	// Make the entire CRC table of a 32 bits CRC algorithm
    void make_crc_32b_table(std::string name, unsigned int polymonial, bool reflect_input, bool reflect_output, unsigned int starting_value, unsigned int xor_final);
	// Returns a reference to the CRC 32 bits algorithm with the name
    CRC_32B_Datas* get_crc_32b_data(std::string name);
	// Return the CRC of a (possibly unsigned) char array
    unsigned int crc_32b(char* buf, int len, std::string crc_name);
    unsigned int crc_32b(unsigned char* buf, int len, std::string crc_name);

    //*********
	//
	// The Bytes_Set class
	//
	//*********

	class Bytes_Set {
	    // Very easy way to handle binary with C++
    public:

        //*********
        //
        // Bytes_Set main members
        //
        //*********

        // Bytes_Set constructor
        Bytes_Set() {};
        // Bytes_Set constructor creating empty datas
        Bytes_Set(unsigned int new_datas_size) : Bytes_Set() {a_datas = new char[new_datas_size];a_datas_size = new_datas_size;};
        // Bytes_Set constructor taking existing datas
        Bytes_Set(char* new_datas, unsigned int new_datas_size) : Bytes_Set() {a_datas = new_datas;a_datas_size = new_datas_size;};
        // Bytes_Set copy constructor
        Bytes_Set(const Bytes_Set& binary) : Bytes_Set() {add_datas(binary.datas(), binary.datas_size());};
        // Bytes_Set destructor
        ~Bytes_Set() {free_memory();};

        // Fills the Bytes_Set with a single value
        void fill(char value){for(int i = 0;i<static_cast<int>(a_datas_size);i++){a_datas[i] = value;}};

        //*********
        //
        // Datas manipulation
        //
        //*********

        // Add datas to the object (with differents types)
        inline void add_datas(char* datas_to_add, unsigned int datas_to_add_size) {
            unsigned int final_size = datas_size() + datas_to_add_size;
            char* final_datas = new char[final_size];
            for(unsigned int i = 0;i<datas_size();i++) {
                final_datas[i] = datas()[i];
            }
            for(unsigned int i = 0; i < datas_to_add_size;i++) {
                final_datas[i + datas_size()] = datas_to_add[i];
            }
            free_memory();
            a_datas = final_datas;
            a_datas_size = final_size;
        };
        inline void add_datas(const char* datas_to_add, unsigned int datas_to_add_size) {
            unsigned int final_size = datas_size() + datas_to_add_size;
            char* final_datas = new char[final_size];
            for(unsigned int i = 0;i<datas_size();i++) {
                final_datas[i] = datas()[i];
            }
            for(unsigned int i = 0; i < datas_to_add_size;i++) {
                final_datas[i + datas_size()] = datas_to_add[i];
            }
            free_memory();
            a_datas = final_datas;
            a_datas_size = final_size;
        };
        inline void add_datas(const unsigned char* datas_to_add, unsigned int datas_to_add_size) {add_datas(reinterpret_cast<const char*>(datas_to_add), datas_to_add_size);};
        inline void add_datas(const Bytes_Set& datas_to_add) {add_datas(datas_to_add.datas(), datas_to_add.datas_size());};
        inline void add_data(char data) {add_datas(&data, 1);};
        inline void add_double(double data, bool big_endian = false) {
            char* final_datas = new char[8];
            __put_8bytes_double_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 8);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_float(float data, bool big_endian = false) {
            char* final_datas = new char[4];
            __put_4bytes_float_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 4);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_short(short data, bool big_endian = false) {
            char* final_datas = new char[2];
            __put_2bytes_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 2);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_ushort(unsigned short data, bool big_endian = false) {
            char* final_datas = new char[2];
            __put_2bytes_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 2);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_int(int data, bool big_endian = false) {
            char* final_datas = new char[4];
            __put_4bytes_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 4);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_int64(int64_t data, bool big_endian = false) {
            char* final_datas = new char[8];
            __put_8bytes_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 8);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_uint(unsigned int data, bool big_endian = false) {
            char* final_datas = new char[4];
            __put_4bytes_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 4);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_string(std::string text) {add_datas(text.c_str(), static_cast<unsigned int>(text.size()));};

        // Return the char at a certain position
        inline char data_at(unsigned int position) const {if(position >= datas_size()) {scls::print("Error", "SCLS", "Datas \"" + std::to_string(position) + "\" out of range in the Binary object.");return 0;} return data_at_directly(position);};
        inline char data_at_directly(unsigned int position) const {return a_datas[position];};

        // Extract datas from the object (with differents types)
        inline Bytes_Set* extract_bytes_set(unsigned int extract_size, unsigned int offset = 0) const {
            // Asserts
            if(offset >= datas_size()){return 0;}
            else if(offset + extract_size >= datas_size()){extract_size = datas_size() - offset;}

            Bytes_Set* extracted_datas = new Bytes_Set(extract_size);
            for(unsigned int i = 0;i<extract_size;i++) {extracted_datas->set_data_at_directly(i, data_at_directly(offset + i));}
            return extracted_datas;
        }
        inline std::shared_ptr<Bytes_Set> extract_bytes_set_shared_ptr(unsigned int extract_size, unsigned int offset = 0)const{return std::shared_ptr<Bytes_Set>(extract_bytes_set(extract_size, offset));};
        inline char* extract_datas(unsigned int extract_size, unsigned int offset = 0, bool inverse = false) const {
            char* extracted_datas = new char[extract_size];
            for(unsigned int i = 0;i<extract_size;i++) {
                extracted_datas[i] = data_at(offset + i);
            }
            if(inverse) {scls::swap_char_array(extracted_datas, extract_size);}
            return extracted_datas;
        }
        inline double extract_double(unsigned int offset = 0, bool big_endian = false) const {return __extract_double_from_char_array(a_datas, offset, big_endian);};
        inline float extract_float(unsigned int offset = 0, bool big_endian = false) const {return static_cast<float>(extract_double(offset, big_endian));};
        inline int extract_int(unsigned int offset = 0, bool big_endian = false) const {return __extract_4bytes_from_char_array(a_datas, offset, big_endian);};
        inline int64_t extract_int64(unsigned int offset = 0, bool big_endian = false) const {return __extract_8bytes_from_char_array(a_datas, offset, big_endian);};
        inline short extract_short(unsigned int offset = 0, bool big_endian = false) const {return __extract_2bytes_from_char_array(a_datas, offset, big_endian);}
        inline std::string extract_string(unsigned int extract_size, unsigned int offset = 0) const {
            std::string extracted_datas = "";
            for(unsigned int i = 0;i<extract_size;i++) {
                extracted_datas += data_at(offset + i);
            }
            return extracted_datas;
        }
        inline std::string extract_string_all() const{return extract_string(datas_size());};
        inline unsigned int extract_uint(unsigned int offset = 0, bool big_endian = false) const {return __extract_u4bytes_from_char_array(a_datas, offset, big_endian);}
        inline unsigned short extract_ushort(unsigned int offset = 0, bool big_endian = false) const {return __extract_u2bytes_from_char_array(a_datas, offset, big_endian);}

        // Put datas in the Bytes_Set
        inline void put_datas(Bytes_Set* datas_to_put, unsigned int offset = 0) {
            if(offset + datas_to_put->datas_size() <= datas_size()) {
                for(int i = 0;i<static_cast<int>(datas_to_put->datas_size());i++) {
                    a_datas[offset + i] = datas_to_put->a_datas[i];
                }
            }
        };
        inline void put_double(double value, unsigned int offset = 0, bool big_endian = false) {if(offset + 8 < datas_size()) __put_8bytes_double_to_char_array(value, a_datas, offset, big_endian);};
        inline void put_uint(unsigned int value, unsigned int offset = 0, bool big_endian = false) {if(offset + 4 < datas_size()) __put_4bytes_to_char_array(value, a_datas, offset, big_endian);};

        // Free the memory of the datas
        inline void free_memory() {if(datas() != 0) {delete[] a_datas;a_datas = 0; a_datas_size = 0;}};

        // Set the char at a certain position
        inline void set_data_at_directly(unsigned int position, char new_data) {a_datas[position] = new_data;};
        inline void set_data_at(unsigned int position, char new_data) {
             if(position < 0 || position >= datas_size()) {
                scls::print("Error", "SCLS", "Datas \"" + std::to_string(position) + "\" out of range in the Binary object.");
                return;
            } set_data_at_directly(position, new_data);
        }

        // File manipulation
        // Read the datas from a file
        inline bool load_from_file(std::string path) {
            if(std::filesystem::exists(path)) {
                free_memory();
                unsigned int total_size = 0;
                a_datas = read_entire_file_binary(path, total_size);
                a_datas_size = total_size;
                return true;
            } scls::print("Error", "SCLS", "The path \"" + path + "\" you want to open does not exist."); return false;
        };
        // Save the datas in a file
        inline void save(std::string path) const { write_in_file_binary(path, datas(), datas_size()); };

        // Operator overloading
        // Operator to access to a char
        char operator[] (unsigned int position) { return data_at(position); };

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline char* datas() const {return a_datas;};
        inline unsigned int datas_size() const {return a_datas_size;};
    private:
        // Binary datas in the object
        char* a_datas = 0;
        // Size of the entire datas in the object
        unsigned int a_datas_size = 0;
	};
}

#endif // SCLS_FOUNDATION_BINARY
