//******************
//
// basix_binary.h
//
//******************
// Presentation :
//
// Basix is a little project containing base functions for Matix.
// It can also be use in any projects.
// This file contains stuff used to do some binary manipulation.
//
//******************
// Warning :
//
// Using binary can cause troubles if you don't know what you do.
// Be very careful with that.
//

#ifndef BASIX_BINARY
#define BASIX_BINARY

#include "basix_core.h"
#include "basix_data_structure.h"
#include "basix_file.h"
#include "basix_math.h"

// The namespace "basix" is used to simplify the all.
namespace basix
{
	// Delete each element into an unused binary list
	inline void delete_binary(std::vector<char*>& datas)
	{
		for (int i = 0; i < datas.size(); i++) delete datas[i];
		datas.clear();
	}

	// Extract a 2 bytes variable (short) from a char array
	inline short extract_2bytes_from_char_array(char* result, unsigned int offset = 0, bool inverse = false)
	{
		short number_1 = 0;
		short number_2 = 0;
		if (inverse)
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

	// Extract a 4 bytes variable from a char array
	inline int extract_4bytes_from_char_array(char* result, unsigned int offset = 0, bool inverse = false)
	{
		int number_1 = 0;
		int number_2 = 0;
		int number_3 = 0;
		int number_4 = 0;
		if (inverse)
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

	// Extract a 8 bytes variable from a char array
	inline int64_t extract_8bytes_from_char_array(char* result, unsigned int offset = 0, bool inverse = false)
	{
		int64_t number_1 = 0;
		int64_t number_2 = 0;
		int64_t number_3 = 0;
		int64_t number_4 = 0;
		int64_t number_5 = 0;
		int64_t number_6 = 0;
		int64_t number_7 = 0;
		int64_t number_8 = 0;
		if (inverse)
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

	// Extract a char array variable from a char array
	inline char* extract_char_array_from_char_array(char* result, unsigned int size, unsigned int offset = 0)
	{
		char* to_return = new char[size];
		for (int i = 0; i < size; i++) to_return[i] = result[offset + i];
		return to_return;
	};

	// Extract a double variable from a char array
	inline double extract_double_from_char_array(char* result, unsigned int offset = 0, bool inverse = false)
	{
		int64_t number_1 = extract_8bytes_from_char_array(result, offset, inverse);
		double* d = (double*)(&number_1);
		double number = (*d);

		return number;
	};

	// Put a char array into an other char array
	inline void put_bytes_to_char_array(char* to_put, char* result, unsigned int size, unsigned int offset = 0)
	{
		for (unsigned int i = 0; i < size; i++)
		{
			result[offset + i] = to_put[i];
		}
	};

	// Put a string into an other char array
	inline void put_string_to_char_array(std::string to_put, char* result, unsigned int offset = 0)
	{
		for (int i = 0; i < to_put.size(); i++)
		{
			result[offset + i] = to_put[i];
		}
	};

	// Convert an integer to a char array and put it in the char array
	inline void put_2bytes_to_char_array(short n, char* result, unsigned int offset = 0, bool inverse = false)
	{
		if (inverse)
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
	inline void put_4bytes_to_char_array(int n, char* result, unsigned int offset = 0, bool inverse = false)
	{
		if (inverse)
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
	inline void put_8bytes_to_char_array(int64_t n, char* result, unsigned int offset = 0, bool inverse = false)
	{
		if (inverse)
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
	inline void put_8bytes_double_to_char_array(double n, char* result, unsigned int offset = 0, bool inverse = false)
	{
		int64_t* n_p = (int64_t*)(&n);
		put_8bytes_to_char_array(*n_p, result, offset, inverse);
	}

	// Return the content of a file in binary with vector of char
	inline void read_file_binary(std::string path, std::vector<char*>& datas, std::vector<unsigned int> size, unsigned int start_pos = 0)
	{
		std::string file_content;
		std::ifstream file;
		// ensure ifstream objects can throw exceptions:
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			file.open(path, std::ios::binary);
			file.seekg(start_pos, file.beg);
			for (int i = 0; i < datas.size(); i++)
			{
				file.read(datas[i], size[i]);
			}
			file.close();
		}
		catch (std::ifstream::failure e) { print("Error", "System", "The file \"" + path + "\" can't be opened, error -> " + e.what() + "."); }
	};

	// Return the content of a file in binary with a char array
	inline void read_file_binary(std::string path, char* datas, unsigned int size, unsigned int start_pos = 0)
	{
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
	inline char* read_entire_file_binary(std::string path)
	{
		unsigned int total_size = file_size(path);
		char* file = new char[total_size];
		read_file_binary(path, file, total_size);

		return file;
	};

	// Swap an unsigned int with his binary
	inline unsigned int swap_unsigned_int(unsigned int n)
	{
		char* bytes = new char[4];
		put_4bytes_to_char_array(n, bytes, 0, true);
		unsigned int result = extract_4bytes_from_char_array(bytes);
		delete[] bytes; bytes = 0;
		return result;
	};

	// Write binary data in a file from a char vector
	inline void write_in_file_binary(std::string path, std::vector<char*> to_write, std::ios::openmode opening_mode = std::ios::out | std::ios::binary)
	{
		std::ofstream file;
		file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		try
		{
			file.open(path, opening_mode);
			for (int i = 0; i < to_write.size(); i++)
			{
				file.write(to_write[i], sizeof(i));
			}
			file.close();
		}
		catch (std::ofstream::failure e)
		{
			print("Error", "System", "The file \"" + path + "\" can't be written in error -> " + e.what() + ".");
		}
	}

	// Write binary data in a file from a char array
	inline void write_in_file_binary(std::string path, char* to_write, unsigned int size, std::ios::openmode opening_mode = std::ios::out | std::ios::binary)
	{
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
}

#endif BASIX_BINARY
