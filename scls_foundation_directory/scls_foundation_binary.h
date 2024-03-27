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

#ifndef SCLS_FOUNDATION_BINARY
#define SCLS_FOUNDATION_BINARY

#include "scls_foundation_core.h"
#include "scls_foundation_math.h"

// The namespace "scls" is used to simplify the all.
namespace scls
{
    //*********
	//
	// Binary handling
	//
	//*********

	// Extract a 2 bytes variable (short) from a char array
	inline short extract_2bytes_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false) {
		short number_1 = 0;
		short number_2 = 0;
		if (big_endian)
		{
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
	inline unsigned short extract_u2bytes_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false) {
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
	inline int extract_4bytes_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false) {
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
	inline unsigned int extract_u4bytes_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false) {
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
	inline int64_t extract_8bytes_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false) {
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
	inline double extract_double_from_char_array(char* result, unsigned int offset = 0, bool big_endian = false) {
		int64_t number_1 = extract_8bytes_from_char_array(result, offset, big_endian);
		double* d = (double*)(&number_1);
		double number = (*d);

		return number;
	};

	// Convert an integer to a char array and put it in the char array
	inline void put_2bytes_to_char_array(short n, char* result, unsigned int offset = 0, bool big_endian = false) {
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
	inline void put_2bytes_to_char_array(unsigned short n, char* result, unsigned int offset = 0, bool big_endian = false) {
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
	inline void put_4bytes_to_char_array(int n, char* result, unsigned int offset = 0, bool big_endian = false) {
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
	inline void put_4bytes_to_char_array(unsigned int n, char* result, unsigned int offset = 0, bool big_endian = false) {
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
	inline void put_8bytes_to_char_array(int64_t n, char* result, unsigned int offset = 0, bool big_endian = false) {
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

	// Convert an double to a char array and put it in the char array
	inline void put_8bytes_double_to_char_array(double n, char* result, unsigned int offset = 0, bool big_endian = false) {
		int64_t* n_p = (int64_t*)(&n);
		put_8bytes_to_char_array(*n_p, result, offset, big_endian);
	}

	//*********
	//
	// Binary file handling
	//
	//*********

	// Return the content of a file in binary with a char array
	inline void read_file_binary(std::string path, char* datas, unsigned int size, unsigned int start_pos = 0) {
		std::string file_content;
		std::ifstream file;
		// ensure ifstream objects can throw exceptions:
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			file.open(path, std::ios::binary);
			file.seekg(start_pos, file.beg);
			file.read(datas, size);
			file.close();
		}
		catch (std::ifstream::failure e) { print("Error", "System", "The file \"" + path + "\" can't be opened, error -> " + e.what() + "."); }
	};

	// Read and return the content of all a binary file
	inline char* read_entire_file_binary(std::string path, unsigned int& total_size) {
	    // Get the size of the file
	    if(!std::filesystem::exists(path)) return 0;
		total_size = static_cast<unsigned int>(std::filesystem::file_size(path));

		// Get the content of the file
		char* file = new char[total_size];
		read_file_binary(path, file, total_size);

		return file;
	};

	// Write binary data in a file from a char array
	inline void write_in_file_binary(std::string path, char* to_write, unsigned int size, std::ios::openmode opening_mode = std::ios::out | std::ios::binary) {
		std::ofstream file;
		file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		try
		{
			file.open(path, opening_mode);
			file.write(to_write, size);
			file.close();
		}
		catch (std::ofstream::failure e)
		{
			print("Error", "System", "The file \"" + path + "\" can't be written in error -> " + e.what() + ".");
		}
	}

    //*********
	//
	// The Bytes_Set class
	//
	//*********

	class Bytes_Set {
	    // Very easy way to handle binary with C++
    public:
        // Bytes_Set constructor
        Bytes_Set() {};
        // Bytes_Set constructor taking existing datas
        Bytes_Set(char* new_datas, unsigned int new_datas_size) : Bytes_Set() {
            a_datas = new_datas;
            a_datas_size = new_datas_size;
        };
        // Bytes_Set copy constructor
        Bytes_Set(const Bytes_Set& binary) : Bytes_Set() {
            add_datas(binary.datas(), binary.datas_size());
        };
        // Bytes_Set destructor
        ~Bytes_Set() {free_memory();};

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
        inline void add_data(char data) {
            add_datas(&data, 1);
        };
        inline void add_double(double data, bool big_endian = false) {
            char* final_datas = new char[8];
            put_8bytes_double_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 8);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_float(float data, bool big_endian = false) {
            add_double(static_cast<double>(data), big_endian);
        };
        inline void add_short(short data, bool big_endian = false) {
            char* final_datas = new char[2];
            put_2bytes_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 2);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_ushort(unsigned short data, bool big_endian = false) {
            char* final_datas = new char[2];
            put_2bytes_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 2);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_int(int data, bool big_endian = false) {
            char* final_datas = new char[4];
            put_4bytes_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 4);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_int64(int64_t data, bool big_endian = false) {
            char* final_datas = new char[8];
            put_8bytes_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 8);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_uint(unsigned int data, bool big_endian = false) {
            char* final_datas = new char[4];
            put_4bytes_to_char_array(data, final_datas, 0, big_endian);
            add_datas(final_datas, 4);
            delete[] final_datas; final_datas = 0;
        };
        inline void add_string(std::string data) {
            add_datas(data.c_str(), static_cast<unsigned int>(data.size()));
        };

        // Return the char at a certain position
        inline char data_at(unsigned int position) {
             if(position < 0 || position >= datas_size()) {
                scls::print("Error", "SCLS", "Datas \"" + std::to_string(position) + "\" out of range in the Binary object.");
                return 0;
            }
            return a_datas[position];
        }

        // Extract datas from the object (with differents types)
        inline char* extract_datas(unsigned int extract_size, unsigned int offset = 0, bool inverse = false) {
            char* extracted_datas = new char[extract_size];
            for(unsigned int i = 0;i<extract_size;i++) {
                extracted_datas[i] = data_at(offset + i);
            }
            if(inverse) {scls::swap_char_array(extracted_datas, extract_size);}
            return extracted_datas;
        }
        inline char extract_data(unsigned int offset = 0) {
            return data_at(offset);
        };
        inline double extract_double(unsigned int offset = 0, bool big_endian = false) {
            return extract_double_from_char_array(a_datas, offset, big_endian);
        };
        inline float extract_float(unsigned int offset = 0, bool big_endian = false) {
            return static_cast<float>(extract_double(offset, big_endian));
        };
        inline int extract_int(unsigned int offset = 0, bool big_endian = false) {
            return extract_4bytes_from_char_array(a_datas, offset, big_endian);
        };
        inline int64_t extract_int64(unsigned int offset = 0, bool big_endian = false) {
            return extract_8bytes_from_char_array(a_datas, offset, big_endian);
        };
        inline short extract_short(unsigned int offset = 0, bool big_endian = false) {
            return extract_2bytes_from_char_array(a_datas, offset, big_endian);
        }
        inline std::string extract_string(unsigned int extract_size, unsigned int offset = 0) {
            std::string extracted_datas = "";
            for(unsigned int i = 0;i<extract_size;i++) {
                extracted_datas += data_at(offset + i);
            }
            return extracted_datas;
        }
        inline unsigned int extract_uint(unsigned int offset = 0, bool big_endian = false) {
            return extract_u4bytes_from_char_array(a_datas, offset, big_endian);
        }
        inline unsigned short extract_ushort(unsigned int offset = 0, bool big_endian = false) {
            return extract_u2bytes_from_char_array(a_datas, offset, big_endian);
        }

        // Free the memory of the datas
        inline void free_memory() {
            if(datas() != 0) {
                delete[] a_datas;
                a_datas = 0; a_datas_size = 0;
            }
        };

        // File manipulation
        // Read the datas from a file
        inline bool load_from_file(std::string path) {
            if(std::filesystem::exists(path)) {
                free_memory();
                unsigned int total_size = 0;
                a_datas = read_entire_file_binary(path, total_size);
                a_datas_size = total_size;
                return true;
            }
            scls::print("Error", "SCLS", "The path \"" + path + "\" you want to open does not exist.");
            return false;
        };
        // Save the datas in a file
        inline void save(std::string path) {
            write_in_file_binary(path, datas(), datas_size());
        };

        // Operator overloading
        // Operator to access to a char
        char operator[] (unsigned int position) {
            return data_at(position);
        };

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
