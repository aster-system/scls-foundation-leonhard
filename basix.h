//******************
// 
// basix.h
// 
//******************
// presentation :
// 
// Basix is a little project containing base functions for Matix.
// It can also be use in any projects.
//

#pragma once

#include <bitset>
#include <codecvt>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <zlib/zlib.h>

// ZLib mandatory stuff
#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) _setmode(_fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

// The namespace "basix" is used to simplify the all.
namespace basix
{
	// Static bool, usefull in debugging to tell to Basix if the "print" function works or not
	static bool _can_print = true;

	// Variables used to define a float separation character
	static std::string _float_character = "";
	static std::string _non_float_character = "";

	// Return the size of a number
	inline int sign(float number) { return number < 0 ? -1 : (number == 0 ? 0 : 1); };

	// Return the value of "_can_print".
	inline bool can_print() { return _can_print; };

	// Cut a string in a vector where there are the "cut" part
	inline std::vector<std::string> cut_string(std::string string, std::string cut, bool erase_blank = false)
	{
		std::string last_string = ""; // String since the last cut
		std::string last_string_cut = ""; // String of the "cut" size which allows to know where to cut
		std::vector<std::string> result = std::vector<std::string>();
		for (int i = 0; i < string.size(); i++) // Browse the string char by char
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
			number_1 = ((static_cast<int64_t>(result[offset    ]) << 56) & 0xff00000000000000);
			number_2 = ((static_cast<int64_t>(result[offset + 1]) << 48) & 0x00ff000000000000);
			number_3 = ((static_cast<int64_t>(result[offset + 2]) << 40) & 0x0000ff0000000000);
			number_4 = ((static_cast<int64_t>(result[offset + 3]) << 32) & 0x000000ff00000000);
			number_5 = ((static_cast<int64_t>(result[offset + 4]) << 24) & 0x00000000ff000000);
			number_6 = ((static_cast<int64_t>(result[offset + 5]) << 16) & 0x0000000000ff0000);
			number_7 = ((static_cast<int64_t>(result[offset + 6]) << 8) &  0x000000000000ff00);
			number_8 = ((static_cast<int64_t>(result[offset + 7]))      &  0x00000000000000ff);
		}
		else
		{
			number_1 = ((static_cast<int64_t>(result[offset + 7]) << 56) & 0xff00000000000000);
			number_2 = ((static_cast<int64_t>(result[offset + 6]) << 48) & 0x00ff000000000000);
			number_3 = ((static_cast<int64_t>(result[offset + 5]) << 40) & 0x0000ff0000000000);
			number_4 = ((static_cast<int64_t>(result[offset + 4]) << 32) & 0x000000ff00000000);
			number_5 = ((static_cast<int64_t>(result[offset + 3]) << 24) & 0x00000000ff000000);
			number_6 = ((static_cast<int64_t>(result[offset + 2]) << 16) & 0x0000000000ff0000);
			number_7 = ((static_cast<int64_t>(result[offset + 1]) << 8)  & 0x000000000000ff00);
			number_8 = ((static_cast<int64_t>(result[offset]))           & 0x00000000000000ff);
		}

		return number_1 + number_2 + number_3 + number_4 + number_5 + number_6 + number_7 + number_8;
	};

	// Extract a double variable from a char array
	inline double extract_double_from_char_array(char* result, unsigned int offset = 0, bool inverse = false)
	{
		int64_t number_1 = extract_8bytes_from_char_array(result, offset, inverse);
		double* d = (double*)(&number_1);
		double number = (*d);

		return number;
	};

	// Return the datas about a file (assuming the file exists).
	inline struct stat file_datas(std::string path) { struct stat sb; bool result = (stat(path.c_str(), &sb) == 0); return sb; };

	// Returns if a file exists.
	inline bool file_exists(std::string path) { struct stat sb; bool result = (stat(path.c_str(), &sb) == 0); return result; };

	// Returns the name of a file (assuming the file exists).
	inline std::string file_name(std::string path)
	{
		std::vector<std::string> cutted = cut_string(path, "/");
		cutted = cut_string(cutted[cutted.size() - 1], "\\");
		cutted = cut_string(cutted[cutted.size() - 1], ".");
		return cutted[0];
	};

	// Returns the size of a file (assuming the file exists).
	inline unsigned int file_size(std::string path)
	{
		std::ifstream in(path, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}

	// Put a char array into an other char array
	inline void put_bytes_to_char_array(char* to_put, char* result, unsigned int size, unsigned int offset = 0)
	{
		for (int i = 0; i < size; i++)
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
			result[offset + 7] = (n & 0x00000000000000ff);
			result[offset + 6] = (n & 0x000000000000ff00) >> 8;
			result[offset + 5] = (n & 0x0000000000ff0000) >> 16;
			result[offset + 4] = (n & 0x00000000ff000000) >> 24;
			result[offset + 3] = (n & 0x000000ff00000000) >> 32;
			result[offset + 2] = (n & 0x0000ff0000000000) >> 40;
			result[offset + 1] = (n & 0x00ff000000000000) >> 48;
			result[offset] = (n & 0xff00000000000000) >> 56;
		}
		else
		{
			result[offset] = (n & 0x00000000000000ff);
			result[offset + 1] = (n & 0x000000000000ff00) >> 8;
			result[offset + 2] = (n & 0x0000000000ff0000) >> 16;
			result[offset + 3] = (n & 0x00000000ff000000) >> 24;
			result[offset + 4] = (n & 0x000000ff00000000) >> 32;
			result[offset + 5] = (n & 0x0000ff0000000000) >> 40;
			result[offset + 6] = (n & 0x00ff000000000000) >> 48;
			result[offset + 7] = (n & 0xff00000000000000) >> 56;
		}
	}

	// Convert an double to a char array and put it in the char array
	inline void put_8bytes_double_to_char_array(double n, char* result, unsigned int offset = 0, bool inverse = false)
	{
		int64_t* n_p = (int64_t*)(&n);
		put_8bytes_to_char_array(*n_p, result, offset, inverse);
	}

	// Inverse a char array
	inline void inverse_char_array(char* array, unsigned int size)
	{
		for (int i = 0; i < floor(size / 2.0); i++)
		{
			char temp = array[i];
			array[i] = array[size - (i + 1)];
			array[size - (i + 1)] = temp;
		}
	};

	// Join a vector of string into one string.
	inline std::string join_string(std::vector<std::string> strings, std::string separation)
	{
		std::string result = "";
		for (int i = 0; i < strings.size(); i++)
		{
			result += strings[i]; // Concatenate each strings
			if (i != strings.size() - 1)
			{
				result += separation; // Add the separation between strings
			}
		}

		return result;
	}

	// Normalize a value between "min" and "max" included
	inline double normalize_value(double number, double min, double max)
	{
		double to_add = (max - min) + 1;
		while (number < min) number += to_add;
		while (number > max) number -= to_add;
		return number;
	}

	// Apply the Paeth function to a left, above and upper left values
	inline float paeth_function(float left, float above, float upper_left)
	{
		float p = left + above - upper_left;
		float pa = abs(p - left);
		float pb = abs(p - above);
		float pc = abs(p - upper_left);
		if (pa <= pb && pa <= pc) return left;
		else if (pb <= pc) return above;
		else return upper_left;
	}

	// Returns if a path is a directory or not
	inline bool path_is_directory(std::string path)
	{
		return ((file_datas(path).st_mode & S_IFDIR) == S_IFDIR);
	};

	// Print the "message" something in the console, coming from "sender" of type "type".
	inline void print(std::string type, std::string sender, std::string message)
	{
		if (can_print())
		{
			std::cout << message << std::endl;
		}
	};

	// Return the content of a file.
	inline std::string read_file(std::string path)
	{
		std::string file_content;
		std::ifstream file;

		// ensure ifstream objects can throw exceptions:
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<char>));
			file.open(path);
			std::stringstream stream; stream << file.rdbuf();
			file.close();
			file_content = stream.str();
		}
		catch (std::ifstream::failure e) { print("Error", "System", "The file \"" + path + "\" can't be opened."); }

		return file_content;
	};

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

	// Replace a string in an another string.
	inline std::string replace(std::string str, std::string to_replace, std::string new_str)
	{
		return join_string(cut_string(str, to_replace), new_str);
	}

	// Change the value of the static "_can_print" function.
	inline void set_can_print(bool can_print) { _can_print = can_print; };

	// Convert a string to a float
	inline float string_to_float(std::string str)
	{
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
	inline std::vector<T> swap_vector(std::vector<T> v)
	{
		for (int i = 0; i < floor((float)v.size() / 2.0); i++)
		{
			T temp = v[i];
			v[i] = v[v.size() - (i + 1)];
			v[i + 1] = temp;
		}
		return v;
	};

	// Compress data from a char array without returning the result
	inline int _compress_binary(char* to_compress, unsigned int to_compress_size, char* output, unsigned int output_size, unsigned int& total_output_size, unsigned int compression_level = 9)
	{
		// Create compression ENV
		int ret = 0;
		z_stream strm;
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		strm.avail_in = 0;
		strm.next_in = Z_NULL;
		ret = deflateInit(&strm, compression_level);
		if (ret != Z_OK) return ret;
		strm.avail_in = to_compress_size;
		strm.next_in = (Bytef*)(to_compress);
		bool stream_end = false;

		// Set output
		strm.avail_out = output_size;
		strm.next_out = (Bytef*)output;

		// Compress data
		do
		{
			// Do the decompression
			ret = deflate(&strm, Z_FINISH);
			if (ret == Z_STREAM_ERROR)
			{
				(void)deflateEnd(&strm);
				return -1;
			}

			switch (ret)
			{
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;
				break;
			case Z_MEM_ERROR:
				(void)deflateEnd(&strm);
				return -2;
			case Z_BUF_ERROR:
				(void)deflateEnd(&strm);
				return -5;
			case Z_STREAM_END:
				stream_end = true;
				break;
			}
		} while (strm.avail_out == 0 && !stream_end);
		(void)deflateEnd(&strm);

		total_output_size = strm.total_out;

		return 1;
	};

	// Compress data from a char array and return the result
	inline char* compress_binary(char* to_compress, unsigned int to_compress_size, unsigned int& output_size, unsigned int compression_level = 9)
	{
		char* output = new char[to_compress_size + 1000];

		unsigned int ret = _compress_binary(to_compress, to_compress_size, output, to_compress_size + 1000, output_size, compression_level);
		if (ret != 1) return 0;

		char* final = new char[output_size];
		for (int i = 0; i < output_size; i++) final[i] = output[i];

		delete[] output;

		return final;
	}

	// Uncompress data from a char array
	inline int uncompress_binary(char* to_uncompress, unsigned int to_uncompress_size, char* output, unsigned int output_size)
	{
		// Create compression ENV
		int ret = 0;
		z_stream strm;
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		strm.avail_in = 0;
		strm.next_in = Z_NULL;
		ret = inflateInit(&strm);
		if (ret != Z_OK) return ret;
		strm.avail_in = to_uncompress_size;
		strm.next_in = (Bytef*)(to_uncompress);
		bool stream_end = false;

		// Uncompress data
		do
		{
			// Set output
			strm.avail_out = output_size;
			strm.next_out = (Bytef*)output;

			// Do the decompression
			ret = inflate(&strm, Z_NO_FLUSH);
			if (ret == Z_STREAM_ERROR)
			{
				(void)inflateEnd(&strm);
				return -1;
			}

			switch (ret)
			{
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;
				break;
			case Z_MEM_ERROR:
				(void)inflateEnd(&strm);
				return -2;
			case Z_STREAM_END:
				stream_end = true;
				break;
			}
		} while (strm.avail_out == 0 && !stream_end);
		(void)inflateEnd(&strm);

		return 1;
	};

	// Write something in a file.
	inline void write_in_file(std::string path, std::string to_write, std::ios::openmode opening_mode = std::ios::out)
	{
		std::ofstream file;
		file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		try
		{
			file.open(path, opening_mode);
			file << to_write;
			file.close();
		}
		catch (std::ofstream::failure e)
		{
			print("Error", "System", "The file \"" + path + "\" can't be written in error -> " + e.what() + ".");
		}
	}

	// Write binary data in a file from a char vector
	inline void write_in_file_binary(std::string path, std::vector<char*> to_write, std::ios::openmode opening_mode = std::ios::out | std::ios::binary)
	{
		std::ofstream file;
		file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		try
		{
			file.open(path, opening_mode);
			for(int i = 0;i<to_write.size();i++)
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

	// Return the content of a directory in a vector of string.
	inline std::vector<std::string> directory_content(std::string path, bool sub_directory = false)
	{
		std::vector<std::string> result;
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			std::string path = entry.path().string();
			if (sub_directory && path_is_directory(path) && file_exists(path))
			{
				std::vector<std::string> sub = directory_content(path, true);
				for (int i = 0; i < sub.size(); i++) result.push_back(sub[i]);
			}
			else
			{
				result.push_back(path);
			}
		}
		return result;
	};

	// Struct representing datas about a PNG chunk
	struct PNG_Chunk {
		// Positionf of the chunk in the file
		unsigned int position = 0;
		// Name of the chunk
		std::string name = "";
		// Size of the chunk
		unsigned int size = 0;
	};

	// Struct representing a pixel in a PNG image
	struct PNG_Pixel {
		// Alpha value of the pixel
		unsigned char alpha = 0;
		// Blue value of the pixel
		unsigned char blue = 0;
		// Green value of the pixel
		unsigned char green = 0;
		// Red value of the pixel
		unsigned char red = 0;
	};

	class Image
	{
		// Class representing a PNG image handler
	public:
		// PNG_Image constructor
		Image() {};
		// PNG_Image constructor
		Image(unsigned short width, unsigned short height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255, unsigned int color_type = 6)
		{
			a_color_type = color_type;
			a_height = height;
			a_width = width;

			fill(red, green, blue, alpha);
		};
		// PNG_Image copy constructor
		Image(Image& copy) : Image()
		{
			a_bit_depth = copy.a_bit_depth;
			a_color_type = copy.a_color_type;
			a_compression_method = copy.a_compression_method;
			a_filter_method = copy.a_filter_method;
			a_height = copy.a_height;
			a_interlace_method = copy.a_interlace_method;
			a_path = copy.a_path;
			a_physical_height_ratio = copy.a_physical_height_ratio;
			a_physical_unit = copy.a_physical_unit;
			a_physical_width_ratio = copy.a_physical_width_ratio;
			a_pixels = copy.a_pixels;
			a_width = copy.a_width;
		};
		// Return the data of the image in a unsigned char*
		inline unsigned char* data()
		{
			return a_pixels;
		}
		// Returns the data of the image filtered in a unsigned char*
		inline unsigned char* data_filtered()
		{
			unsigned char* datas = new unsigned char[get_height() * get_width() * get_components() + get_height()];
			for (int i = 0; i < get_height(); i++)
			{
				for (int j = 0; j < get_width() * get_components() + 1; j++)
				{
					if (j == 0)
					{
						datas[i * (get_width() * get_components() + 1)] = 0;
					}
					else
					{
						datas[i * (get_width() * get_components() + 1) + j] = data()[i * get_width() * get_components() + (j - 1)];
					}
				}
			}
			return datas;
		};
		// Returns the data of the image under the PNG format
		inline char* data_png(unsigned int &total_size)
		{
			total_size = 8;

			// Create the IDHR chunk
			std::string name = "IHDR";
			unsigned int idhr_size = 13;
			unsigned int idhr_total_size = 25;
			char* idhr = new char[idhr_total_size];
			char* chunk_size = new char[4]; put_4bytes_to_char_array(idhr_size, chunk_size); inverse_char_array(chunk_size, 4);
			for (int i = 0; i < 4; i++) idhr[i] = chunk_size[i];
			for (int i = 0; i < name.size(); i++) idhr[4 + i] = name[i];
			put_4bytes_to_char_array(get_width(), chunk_size); inverse_char_array(chunk_size, 4);
			for (int i = 0; i < 4; i++) idhr[8 + i] = chunk_size[i];
			put_4bytes_to_char_array(get_height(), chunk_size); inverse_char_array(chunk_size, 4);
			for (int i = 0; i < 4; i++) idhr[12 +  i] = chunk_size[i];
			idhr[16] = (unsigned char)get_bit_depht();
			idhr[17] = (unsigned char)get_color_type();
			idhr[18] = (unsigned char)get_compression_method();
			idhr[19] = 0;// (unsigned char)get_filter_method();
			idhr[20] = 0;// (unsigned char)get_interlace_method();
			for (int i = 0; i < 4; i++) idhr[21 + i] = 0;
			total_size += idhr_total_size;

			// Creathe the pHYS chunk
			name = "pHYS";
			unsigned int phys_size = 9;
			unsigned int phys_total_size = 21;
			char* phys = new char[phys_total_size];
			put_4bytes_to_char_array(phys_size, chunk_size); inverse_char_array(chunk_size, 4);
			for (int i = 0; i < 4; i++) phys[i] = chunk_size[i];
			for (int i = 0; i < name.size(); i++) phys[4 + i] = name[i];
			put_4bytes_to_char_array(get_physical_width_ratio(), chunk_size); inverse_char_array(chunk_size, 4);
			for (int i = 0; i < 4; i++) phys[8 + i] = chunk_size[i];
			put_4bytes_to_char_array(get_physical_height_ratio(), chunk_size); inverse_char_array(chunk_size, 4);
			for (int i = 0; i < 4; i++) phys[12 + i] = chunk_size[i];
			phys[16] = get_physical_unit();
			for (int i = 0; i < 4; i++) phys[17 + i] = 0;
			total_size += phys_total_size;

			// Create the IDAT chunk
			name = "IDAT";
			unsigned int idat_size = 0;
			char* idat_uncompressed = (char*)data_filtered();
			char* idat_compressed = compress_binary(idat_uncompressed, get_height() * get_width() * get_components() + get_height(), idat_size, 9);
			delete[] idat_uncompressed;
			unsigned int idat_total_size = idat_size + 12;
			char* idat = new char[idat_total_size];
			put_4bytes_to_char_array(idat_size, chunk_size); inverse_char_array(chunk_size, 4);
			for (int i = 0; i < 4; i++) idat[i] = chunk_size[i];
			for (int i = 0; i < name.size(); i++) idat[4 + i] = name[i];
			for (int i = 0; i < idat_size; i++) idat[8 + i] = idat_compressed[i];
			for (int i = 0; i < 4; i++) idat[(idat_size - 4) + i] = 0;
			delete[] idat_compressed;
			total_size += idat_total_size;

			// Create the IEND chunk
			name = "IEND";
			unsigned int iend_total_size = 12;
			char* iend = new char[iend_total_size];
			for (int i = 0; i < 4; i++) iend[i] = 0;
			for (int i = 0; i < name.size(); i++) iend[4 + i] = name[i];
			for (int i = 0; i < 4; i++) iend[8 + i] = 0;
			total_size += iend_total_size;

			// Create the datas
			// Create the signature
			unsigned int pos = 0;
			char* datas = new char[total_size];
			std::vector<float> signature = get_png_signature();
			for (int i = 0; i < signature.size(); i++) datas[i] = (char)signature[i];
			pos += signature.size();
			// Create the IDHR chunk
			for (int i = 0; i < idhr_total_size; i++) datas[pos + i] = idhr[i];
			pos += idhr_total_size;
			// Create the pHYS chunk
			for (int i = 0; i < phys_total_size; i++) datas[pos + i] = phys[i];
			pos += phys_total_size;
			// Create the IDAT chunk
			for (int i = 0; i < idat_total_size; i++) datas[pos + i] = idat[i];
			pos += idat_total_size;
			// Create the IEND chunk
			for (int i = 0; i < iend_total_size; i++) datas[pos + i] = iend[i];
			pos += iend_total_size;

			// Free the memory
			delete[] chunk_size;
			delete[] idat;
			delete[] idhr;
			delete[] iend;
			delete[] phys;

			return datas;
		}
		// Draw a line on the image
		void draw_line(unsigned short x_1, unsigned short y_1, unsigned short x_2, unsigned short y_2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255, unsigned short width = 1)
		{
			if (width == 1 || true)
			{
				float distance_x = x_2 - x_1;
				float distance_y = y_2 - y_1;
				float distance = ceil(sqrt(pow(distance_x, 2) + pow(distance_y, 2)));

				float x_y_ratio = distance_x / distance_y;

				if (abs(x_y_ratio) < 1)
				{
					// Normalize positions
					if (y_1 > y_2)
					{
						unsigned short temp = y_1;
						y_1 = y_2;
						y_2 = temp;
						temp = x_1;
						x_1 = x_2;
						x_2 = temp;
					}

					float actual_x = x_1;
					float actual_y = y_1;

					while (actual_y < y_2)
					{
						actual_y++;
						actual_x += x_y_ratio;
						set_pixel(actual_x, actual_y, red, green, blue, alpha, width);
					}
				}
				else
				{
					// Normalize positions
					if (x_1 > x_2)
					{
						unsigned short temp = x_1;
						x_1 = x_2;
						x_2 = temp;
						temp = y_1;
						y_1 = y_2;
						y_2 = temp;
					}

					float actual_x = x_1;
					float actual_y = y_1;

					float y_x_ratio = distance_y / distance_x;
					while(actual_x < x_2)
					{
						actual_y += y_x_ratio;
						actual_x++;
						set_pixel(actual_x, actual_y, red, green, blue, alpha, width);
					}
				}
			}
		};
		// Draw a rectangle on the image
		void draw_rect(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
		{
			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					set_pixel(x + i, y + j, red, green, blue, alpha);
				}
			}
		};
		// Delete the pixels in the memory
		void free_memory()
		{
			if (a_pixels != 0)
			{
				delete[] a_pixels;
				a_pixels = 0;
			}
		};
		// Fill the image with one color
		void fill(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
		{
			free_memory();
			a_pixels = new unsigned char[get_width() * get_height() * get_components() + 1];
			for (int i = 0; i < get_height(); i++)
			{
				for (int j = 0; j < get_width(); j++)
				{
					set_pixel(j, i, red, green, blue, alpha);
				}
			}
		};
		// Fill a rectangle on the image
		void fill_triangle(unsigned short x_1, unsigned short y_1, unsigned short x_2, unsigned short y_2, unsigned short x_3, unsigned short y_3, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
		{
			// 3 should be the point with the largest X value
			if (x_1 > x_3)
			{
				unsigned short temp = x_1;
				x_1 = x_3;
				x_3 = temp;
				temp = y_1;
				y_1 = y_3;
				y_3 = temp;
			}

			// 3 should be the point with the largest X value
			if (x_2 > x_3)
			{
				unsigned short temp = x_2;
				x_2 = x_3;
				x_3 = temp;
				temp = y_2;
				y_2 = y_3;
				y_3 = temp;
			}

			// 2 should be the point with the largest Y value of 1 and 2
			if (y_1 > y_2)
			{
				unsigned short temp = x_2;
				x_2 = x_1;
				x_1 = temp;
				temp = y_2;
				y_2 = y_1;
				y_1 = temp;
			}

			float distance_x_1_2 = x_2 - x_1;
			float distance_y_1_2 = y_2 - y_1;

			float actual_x = x_1;
			float actual_y = y_1;
			float ratio_x_y = distance_x_1_2 / distance_y_1_2;
			float ratio_y_x = abs(distance_y_1_2 / distance_x_1_2);

			unsigned short iter = 0;

			while (actual_y < y_2 && iter < 1000)
			{
				if (abs(ratio_x_y) < 1)
				{
					actual_y++;
					actual_x += ratio_x_y;
				}
				else
				{
					actual_y += ratio_y_x;
					if(distance_x_1_2 > 0) actual_x++;
					else actual_x--;
				}

				draw_line(floor(actual_x), floor(actual_y), x_3, y_3, red, green, blue, alpha, 2);
				draw_line(floor(actual_x), ceil(actual_y), x_3, y_3, red, green, blue, alpha, 2);
				draw_line(ceil(actual_x), floor(actual_y), x_3, y_3, red, green, blue, alpha, 2);
				draw_line(ceil(actual_x), ceil(actual_y), x_3, y_3, red, green, blue, alpha, 2);
				iter++;
			}
		};
		// Flip the image on the X axis
		inline void flip_x()
		{
			unsigned char* line1 = new unsigned char[get_width()];
			unsigned int max = get_height();

			for (int i = 0; i < floor((float)max / 2.0);i++)
			{
				// Red
				for (int j = 0; j < get_width(); j++) line1[j] = a_pixels[(i * get_width() + j) * get_components()];
				for (int j = 0; j < get_width(); j++) a_pixels[(i * get_width() + j) * get_components()] = a_pixels[((max - (i + 1)) * get_width() + j) * get_components()];
				for (int j = 0; j < get_width(); j++) a_pixels[((max - (i + 1)) * get_width() + j) * get_components()] = line1[j];

				// Green
				for (int j = 0; j < get_width(); j++) line1[j] = a_pixels[(i * get_width() + j) * get_components() + 1];
				for (int j = 0; j < get_width(); j++) a_pixels[(i * get_width() + j) * get_components() + 1] = a_pixels[((max - (i + 1)) * get_width() + j) * get_components() + 1];
				for (int j = 0; j < get_width(); j++) a_pixels[((max - (i + 1)) * get_width() + j) * get_components() + 1] = line1[j];
				
				// Blue
				for (int j = 0; j < get_width(); j++) line1[j] = a_pixels[(i * get_width() + j) * get_components() + 2];
				for (int j = 0; j < get_width(); j++) a_pixels[(i * get_width() + j) * get_components() + 2] = a_pixels[((max - (i + 1)) * get_width() + j) * get_components() + 2];
				for (int j = 0; j < get_width(); j++) a_pixels[((max - (i + 1)) * get_width() + j) * get_components() + 2] = line1[j];
				
				// Alpha
				for (int j = 0; j < get_width(); j++) line1[j] = a_pixels[(i * get_width() + j) * get_components() + 3];
				for (int j = 0; j < get_width(); j++) a_pixels[(i * get_width() + j) * get_components() + 3] = a_pixels[((max - (i + 1)) * get_width() + j) * get_components() + 3];
				for (int j = 0; j < get_width(); j++) a_pixels[((max - (i + 1)) * get_width() + j) * get_components() + 3] = line1[j];
			}

			delete[] line1;
		};
		// Flip the image on the Y axis
		inline void flip_y()
		{
			unsigned char* line1 = new unsigned char[get_height()];
			unsigned int max = get_width();

			for (int i = 0; i < floor((float)max / 2.0); i++)
			{
				// Red
				for (int j = 0; j < get_height(); j++) line1[j] = a_pixels[(i + j * get_width()) * get_components()];
				for (int j = 0; j < get_height(); j++) a_pixels[(i + j * get_width()) * get_components()] = a_pixels[((max - (i + 1)) + j * get_width()) * get_components()];
				for (int j = 0; j < get_height(); j++) a_pixels[((max - (i + 1)) + j * get_width()) * get_components()] = line1[j];

				// Green
				for (int j = 0; j < get_height(); j++) line1[j] = a_pixels[(i + j * get_width()) * get_components() + 1];
				for (int j = 0; j < get_height(); j++) a_pixels[(i + j * get_width()) * get_components() + 1] = a_pixels[((max - (i + 1)) + j * get_width()) * get_components() + 1];
				for (int j = 0; j < get_height(); j++) a_pixels[((max - (i + 1)) + j * get_width()) * get_components() + 1] = line1[j];

				// Blue
				for (int j = 0; j < get_height(); j++) line1[j] = a_pixels[(i + j * get_width()) * get_components() + 2];
				for (int j = 0; j < get_height(); j++) a_pixels[(i + j * get_width()) * get_components() + 2] = a_pixels[((max - (i + 1)) + j * get_width()) * get_components() + 2];
				for (int j = 0; j < get_height(); j++) a_pixels[((max - (i + 1)) + j * get_width()) * get_components() + 2] = line1[j];

				// Alpha
				for (int j = 0; j < get_height(); j++) line1[j] = a_pixels[(i + j * get_width()) * get_components() + 3];
				for (int j = 0; j < get_height(); j++) a_pixels[(i + j * get_width()) * get_components() + 3] = a_pixels[((max - (i + 1)) + j * get_width()) * get_components() + 3];
				for (int j = 0; j < get_height(); j++) a_pixels[((max - (i + 1)) + j * get_width()) * get_components() + 3] = line1[j];
			}

			delete[] line1;
		};
		// Get every chunks into a PNG image
		std::vector<PNG_Chunk> get_all_chunks_from_path(std::string path)
		{
			std::vector<PNG_Chunk> to_return = std::vector<PNG_Chunk>();
			if (file_exists(path) && !path_is_directory(path))
			{
				// Create the necessary things to read the PNG file
				std::vector<char*> header = std::vector<char*>();
				a_idat_chunk.clear();
				std::string name = "";
				std::vector<unsigned int> size = std::vector<unsigned int>();
				unsigned int size_offset = 0;

				unsigned int iter = 0;

				// Check each chunks in the file
				while (name != "IEND")
				{
					header.clear();
					size.clear();
					name = "";
					header.push_back((char*)(new unsigned int(0)));
					size.push_back(sizeof(unsigned int));
					for (int i = 0; i < 4; i++)
					{
						header.push_back((new char(0)));
						size.push_back(sizeof(char));
					}
					read_file_binary(path, header, size, 8 + size_offset);
					unsigned int chunk_size = *((int*)header[0]);
					chunk_size = _byteswap_ulong(chunk_size);
					for (int i = 0; i < 4; i++)
					{
						name += *header[i + 1];
					}
					delete_binary(header);
					PNG_Chunk chunk;
					chunk.position = size_offset + 16;
					chunk.name = name;
					chunk.size = chunk_size;
					size_offset += chunk_size + 12;
					to_return.push_back(chunk);

					if (name == "pHYs")
					{
						load_pHYS_from_path(path, chunk);
					}
					else if (name == "IDAT" && is_loadable())
					{
						a_idat_chunk.push_back(chunk);
					}
					else if (name == "sRGB")
					{
						load_sRGB_from_path(path, chunk);
					}
					else if (name == "PLTE" || name == "bKGD") // Not implemented yet
					{
						a_loadable = false;
					}

					iter++;
				}

				fill(0, 0, 0);

				// Load IDAT chunks
				if (a_idat_chunk.size() > 0 && is_loadable())
				{
					a_error_load = load_IDAT_from_path(path);
					if (a_error_load != 1) a_loadable = false;
				}
			}
			return to_return;
		};
		// Return the pixel located in a position in the image
		PNG_Pixel get_pixel(unsigned short x, unsigned short y)
		{
			PNG_Pixel to_return;
			if (x >= 0 && x < get_width() && y >= 0 && y < get_height())
			{
				unsigned int position = (y * get_width() + x) * get_components();
				to_return.red = a_pixels[position];
				to_return.green = a_pixels[position + 1];
				to_return.blue = a_pixels[position + 2];
				to_return.alpha = a_pixels[position + 3];
			}
			return to_return;
		}
		// Load the base data of an image from a path
		bool load_base_from_path(std::string path)
		{
			if (file_exists(path) && !path_is_directory(path))
			{
				// Create the necessary things to read the PNG file
				std::vector<char*> header = std::vector<char*>();
				std::vector<unsigned int> size = std::vector<unsigned int>();
				for (int i = 0; i < 8; i++)
				{
					header.push_back((char*)(new unsigned char(0)));
					size.push_back(sizeof(unsigned char));
				}
				read_file_binary(path, header, size);

				// Check if the signature is correct (137 80 78 71 13 10 26 10 for png files)
				std::vector<float> signature = get_png_signature();
				for (int i = 0; i < signature.size(); i++)
				{
					if (signature[i] != *((unsigned char*)header[i])) return false;
				}
				delete_binary(header);

				// Check the first chunk of the file
				// Get the size of the chunk
				size.clear();
				header.push_back((char*)(new unsigned int(0)));
				size.push_back(sizeof(unsigned int));
				read_file_binary(path, header, size, 8);
				unsigned int chunk_size = *((int*)header[0]);
				chunk_size = _byteswap_ulong(chunk_size);
				delete_binary(header);
				if (chunk_size != 13) return false;
				// Get the datas of the chunk
				size.clear();
				for (int i = 0; i < 2; i++)
				{
					header.push_back((char*)(new unsigned int(0)));
					size.push_back(sizeof(unsigned int));
				}
				for (int i = 0; i < 5; i++)
				{
					header.push_back((char*)(new unsigned char(0)));
					size.push_back(sizeof(unsigned char));
				}
				read_file_binary(path, header, size, 16);
				unsigned int chunk_height = *((int*)header[1]);
				a_height = _byteswap_ulong(chunk_height);
				unsigned int chunk_width = *((int*)header[0]);
				a_width = _byteswap_ulong(chunk_width);
				a_bit_depth = *(header[2]);
				a_color_type = *(header[3]);
				a_compression_method = *(header[4]);
				a_filter_method = *(header[5]);
				a_interlace_method = *(header[6]);
				delete_binary(header);
			}
			else
			{
				return false;
			}
		}
		// Load the image from a path
		bool load_from_path(std::string path)
		{
			if (load_base_from_path(path))
			{
				get_all_chunks_from_path(path);
			}
			else
			{
				return false;
			}
		};
		// Load the image from a set of PNG binary data
		inline bool load_from_binary_PNG(char* datas, unsigned int size)
		{
			write_in_file_binary("_temp.png", datas, size);

			bool result = load_from_path("_temp.png");

			std::filesystem::remove("_temp.png");

			return result;
		};
		// Load a IDAT chunk grom a path
		char load_IDAT_from_path(std::string path)
		{
			std::vector<PNG_Chunk>& chunk = a_idat_chunk;
			if (file_exists(path) && !path_is_directory(path))
			{
				if (a_pixels == 0) return -1;

				// Get the size of the chunks
				unsigned int current_size = 0;
				for (int i = 0; i < chunk.size(); i++)
				{
					current_size += chunk[i].size;
				}

				// Create the necessary things to read the PNG file
				char* header = new char[current_size];
				char* header_part = new char[current_size];
				unsigned int total_size = 0;
				current_size = 0;

				// Read into the chunk
				for (int i = 0; i < chunk.size(); i++)
				{
					read_file_binary(path, header_part, chunk[i].size, chunk[i].position);
					total_size += chunk[i].size;

					for (int j = 0; j < chunk[i].size; j++)
					{
						(header[current_size + j]) = (header_part[j]);
					}
					current_size += chunk[i].size;
					delete[] header_part;
					header_part = new char[a_chunk_size];
				}
				delete[] header_part;
				header_part = 0;

				// Set binary mode
				(void)SET_BINARY_MODE(stdin);
				(void)SET_BINARY_MODE(stdout);

				// Define compression variables
				unsigned char components = get_components();
				int level = get_compression_method();
				int ret = 0;
				unsigned have = 0;
				unsigned int out_size = (get_width() * get_height() * components) + get_height();
				unsigned char* out = new unsigned char[out_size];
				ret = uncompress_binary(header, current_size, (char*)out, out_size);

				if (ret != 1)
				{
					delete[] header;
					delete[] out;
					return ret;
				}

				// Process data
				a_processing_last_position = a_processed_data + 1;
				unsigned char component_size = get_components();
				unsigned int current_collumn = -1;
				unsigned int current_line = -1;
				unsigned short data_number = have - get_height();
				PNG_Pixel last_pixel;
				unsigned int part = -1;
				unsigned int y_pixel = 0;
				for (int i = 0; i < out_size; i++)
				{
					if (part >= 0 && part < get_width() * component_size)
					{
						unsigned char component = part % component_size;
						if (component == 0) // Apply red component
						{
							a_processed_data++;
							current_collumn++;
							set_pixel_red(current_collumn, current_line, (unsigned char)(out[i]));
						}
						else if (component == 1) // Apply green component
						{
							set_pixel_green(current_collumn, current_line, (unsigned char)(out[i]));
						}
						else if (component == 2) // Apply blue component
						{
							set_pixel_blue(current_collumn, current_line, (unsigned char)(out[i]));
						}
						else if (component == 3) // Apply alpha component
						{
							set_pixel_alpha(current_collumn, current_line, (unsigned char)(out[i]));
						}
						part++;
					}
					else
					{
						if (a_processed_data > 0)
						{
							if (a_filter_type == 1) // Apply sub filtering
							{
								for (int i = 1; i < get_width(); i++)
								{
									PNG_Pixel pixel = get_pixel(i - 1, current_line);
									set_pixel_red(i, current_line, get_pixel(i, current_line).red + pixel.red);
									set_pixel_green(i, current_line, get_pixel(i, current_line).green + pixel.green);
									set_pixel_blue(i, current_line, get_pixel(i, current_line).blue + pixel.blue);
									set_pixel_alpha(i, current_line, get_pixel(i, current_line).alpha + pixel.alpha);
								}
							}
							else if (a_filter_type == 2 && a_processed_data > get_width()) // Apply up filtering
							{
								for (int i = 0; i < get_width(); i++)
								{
									PNG_Pixel pixel = get_pixel(i, current_line - 1);
									set_pixel_red(i, current_line, get_pixel(i, current_line).red + pixel.red);
									set_pixel_green(i, current_line, get_pixel(i, current_line).green + pixel.green);
									set_pixel_blue(i, current_line, get_pixel(i, current_line).blue + pixel.blue);
									set_pixel_alpha(i, current_line, get_pixel(i, current_line).alpha + pixel.alpha);
								}
							}
							else if (a_filter_type == 3) // Apply average filtering
							{
								if (a_processed_data > get_width())
								{
									for (int i = 0; i < get_width(); i++)
									{
										PNG_Pixel final_pixel;
										PNG_Pixel pixel1;
										if (i == 0)
										{
											pixel1.red = 0;
											pixel1.green = 0;
											pixel1.blue = 0;
											pixel1.alpha = 0;
										}
										else
										{
											pixel1 = get_pixel(i - 1, current_line);
										}
										PNG_Pixel pixel2 = get_pixel(i, current_line - 1);
										set_pixel_red(i, current_line, get_pixel(i, current_line).red + floor(((float)pixel1.red + (float)pixel2.red) / 2.0));
										set_pixel_green(i, current_line, get_pixel(i, current_line).green + floor(((float)pixel1.green + (float)pixel2.green) / 2.0));
										set_pixel_blue(i, current_line, get_pixel(i, current_line).blue + floor(((float)pixel1.blue + (float)pixel2.blue) / 2.0));
										set_pixel_alpha(i, current_line, get_pixel(i, current_line).alpha + floor(((float)pixel1.alpha + (float)pixel2.alpha) / 2.0));
									}
								}
							}
							else if (a_filter_type == 4 && current_line > 0) // Apply paeth filtering
							{
								for (int i = 0; i < get_width(); i++)
								{
									if (i == 0)
									{
										PNG_Pixel pixel = get_pixel(i, current_line - 1);
										set_pixel_red(i, current_line, get_pixel(i, current_line).red + pixel.red);
										set_pixel_green(i, current_line, get_pixel(i, current_line).green + pixel.green);
										set_pixel_blue(i, current_line, get_pixel(i, current_line).blue + pixel.blue);
										set_pixel_alpha(i, current_line, get_pixel(i, current_line).alpha + pixel.alpha);
									}
									else
									{
										PNG_Pixel pixel2 = get_pixel(i - 1, current_line);
										PNG_Pixel pixel3 = get_pixel(i - 1, current_line - 1);
										PNG_Pixel pixel1 = get_pixel(i, current_line - 1);
										set_pixel_red(i, current_line, get_pixel(i, current_line).red + paeth_function(pixel1.red, pixel2.red, pixel3.red));
										set_pixel_green(i, current_line, get_pixel(i, current_line).green + paeth_function(pixel1.green, pixel2.green, pixel3.green));
										set_pixel_blue(i, current_line, get_pixel(i, current_line).blue + paeth_function(pixel1.blue, pixel2.blue, pixel3.blue));
										set_pixel_alpha(i, current_line, get_pixel(i, current_line).alpha + paeth_function(pixel1.alpha, pixel2.alpha, pixel2.alpha));
									}
								}
							}
						}

						a_filter_type = out[i];
						current_collumn = -1;
						current_line++;
						part = 0;
					}
				}

				if (a_processed_data > 0)
				{
					if (a_filter_type == 1) // Apply sub filtering
					{
						for (int i = 1; i < get_width(); i++)
						{
							PNG_Pixel pixel = get_pixel(i - 1, current_line);
							set_pixel_red(i, current_line, get_pixel(i, current_line).red + pixel.red);
							set_pixel_green(i, current_line, get_pixel(i, current_line).green + pixel.green);
							set_pixel_blue(i, current_line, get_pixel(i, current_line).blue + pixel.blue);
							set_pixel_alpha(i, current_line, get_pixel(i, current_line).alpha + pixel.alpha);
						}
					}
					else if (a_filter_type == 2 && a_processed_data > get_width()) // Apply up filtering
					{
						for (int i = 0; i < get_width(); i++)
						{
							PNG_Pixel pixel = get_pixel(i, current_line - 1);
							set_pixel_red(i, current_line, get_pixel(i, current_line).red + pixel.red);
							set_pixel_green(i, current_line, get_pixel(i, current_line).green + pixel.green);
							set_pixel_blue(i, current_line, get_pixel(i, current_line).blue + pixel.blue);
							set_pixel_alpha(i, current_line, get_pixel(i, current_line).alpha + pixel.alpha);
						}
					}
					else if (a_filter_type == 3) // Apply average filtering
					{
						if (a_processed_data > get_width())
						{
							for (int i = 0; i < get_width(); i++)
							{
								PNG_Pixel final_pixel;
								PNG_Pixel pixel1;
								if (i == 0)
								{
									pixel1.red = 0;
									pixel1.green = 0;
									pixel1.blue = 0;
									pixel1.alpha = 0;
								}
								else
								{
									pixel1 = get_pixel(i - 1, current_line);
								}
								PNG_Pixel pixel2 = get_pixel(i, current_line - 1);
								set_pixel_red(i, current_line, get_pixel(i, current_line).red + floor(((float)pixel1.red + (float)pixel2.red) / 2.0));
								set_pixel_green(i, current_line, get_pixel(i, current_line).green + floor(((float)pixel1.green + (float)pixel2.green) / 2.0));
								set_pixel_blue(i, current_line, get_pixel(i, current_line).blue + floor(((float)pixel1.blue + (float)pixel2.blue) / 2.0));
								set_pixel_alpha(i, current_line, get_pixel(i, current_line).alpha + floor(((float)pixel1.alpha + (float)pixel2.alpha) / 2.0));
							}
						}
					}
					else if (a_filter_type == 4 && a_processed_data > get_width()) // Apply paeth filtering
					{
						for (int i = 0; i < get_width(); i++)
						{
							if (i == 0)
							{
								PNG_Pixel pixel = get_pixel(i, current_line - 1);
								set_pixel_red(i, current_line, get_pixel(i, current_line).red + pixel.red);
								set_pixel_green(i, current_line, get_pixel(i, current_line).green + pixel.green);
								set_pixel_blue(i, current_line, get_pixel(i, current_line).blue + pixel.blue);
								set_pixel_alpha(i, current_line, get_pixel(i, current_line).alpha + pixel.alpha);
							}
							else
							{
								PNG_Pixel pixel2 = get_pixel(i - 1, current_line);
								PNG_Pixel pixel3 = get_pixel(i - 1, current_line - 1);
								PNG_Pixel pixel1 = get_pixel(i, current_line - 1);
								set_pixel_red(i, current_line, get_pixel(i, current_line).red + paeth_function(pixel1.red, pixel2.red, pixel3.red));
								set_pixel_green(i, current_line, get_pixel(i, current_line).green + paeth_function(pixel1.green, pixel2.green, pixel3.green));
								set_pixel_blue(i, current_line, get_pixel(i, current_line).blue + paeth_function(pixel1.blue, pixel2.blue, pixel3.blue));
								set_pixel_alpha(i, current_line, get_pixel(i, current_line).alpha + paeth_function(pixel1.alpha, pixel2.alpha, pixel2.alpha));
							}
						}
					}
				}

				// Free memory
				delete[] header;
				delete[] out;
			}
			else
			{
				return -4;
			}
			return 1;
		};
		// Load the pHYS chunk from a path
		bool load_pHYS_from_path(std::string path, PNG_Chunk chunk)
		{
			if (file_exists(path) && !path_is_directory(path) && chunk.name == "pHYs" && chunk.size == 9)
			{
				// Create the necessary things to read the PNG file
				std::vector<char*> header = std::vector<char*>();
				std::vector<unsigned int> size = std::vector<unsigned int>();

				// Read into the chunk
				for (int i = 0; i < 2; i++)
				{
					header.push_back((char*)(new unsigned int(0)));
					size.push_back(sizeof(unsigned int));
				}
				header.push_back((new char(0)));
				size.push_back(sizeof(char));
				read_file_binary(path, header, size, chunk.position);
				unsigned int physical_height = *((unsigned int*)header[1]);
				a_physical_height_ratio = _byteswap_ulong(physical_height);
				unsigned int physical_width = *((unsigned int*)header[0]);
				a_physical_width_ratio = _byteswap_ulong(physical_width);
				a_physical_unit = *header[2];
				delete_binary(header);
			}
			else
			{
				return false;
			}
		};
		// Load the sRGB chunk from a path
		bool load_sRGB_from_path(std::string path, PNG_Chunk chunk)
		{
			if (file_exists(path) && !path_is_directory(path) && chunk.name == "sRGB" && chunk.size == 1)
			{
				// Create the necessary things to read the PNG file
				std::vector<char*> header = std::vector<char*>();
				std::vector<unsigned int> size = std::vector<unsigned int>();

				// Read into the chunk
				header.push_back((new char(0)));
				size.push_back(sizeof(char));
				read_file_binary(path, header, size, chunk.position);
				a_srgb_value = (*header[0]);

				return true;
			}
			else
			{
				return false;
			}
		}
		// Return the x parameter normalized according to the image
		inline unsigned short normalized_x(unsigned short x)
		{
			return x;
		}
		// Return the y parameter normalized according to the image
		inline unsigned short normalized_y(unsigned short y)
		{
			return y;
		}
		// Save the image into the PNG format
		inline void save_png(std::string path)
		{
			unsigned int size = 0;
			char* datas = data_png(size);
			write_in_file_binary(path, datas, size);
			delete datas;
		}
		// PNG_Image destructor
		~Image() { free_memory(); };

		// Getters and setters
		inline unsigned int get_bit_depht() { return a_bit_depth; };
		inline unsigned int get_color_type() { return a_color_type; };
		inline unsigned char get_components() { if (get_color_type() == 6) return 4; return 3; };
		inline unsigned int _get_current_x_processing(unsigned int offset = 0) { return ((a_processed_data - 1) - offset) % get_width(); };
		inline unsigned int _get_current_y_processing(unsigned int offset = 0) { return floor(((float)(a_processed_data - 1) - (float)offset) / (float)get_width()); };
		inline unsigned int get_compression_method() { return a_compression_method; };
		inline std::vector<float> get_png_signature()
		{
			std::vector<float> signature;
			signature.push_back(137);
			signature.push_back(80);
			signature.push_back(78);
			signature.push_back(71);
			signature.push_back(13);
			signature.push_back(10);
			signature.push_back(26);
			signature.push_back(10);

			return signature;
		};
		inline char get_error_load() { return a_error_load; };
		inline unsigned int get_filter_method() { return a_filter_method; };
		inline unsigned int get_height() { return a_height; };
		inline unsigned int get_interlace_method() { return a_interlace_method; };
		inline std::string get_path() { return a_path; };
		inline unsigned int get_physical_height_ratio() { return a_physical_height_ratio; };
		inline unsigned int get_physical_unit() { return a_physical_unit; };
		inline unsigned int get_physical_width_ratio() { return a_physical_width_ratio; };
		inline unsigned int get_width() { return a_width; };
		inline bool is_flipped_x() { return a_flipped_x; };
		inline bool is_flipped_y() { return a_flipped_y; };
		inline bool is_loadable() { return a_loadable; };
		inline void set_pixel(unsigned short x, unsigned short y, PNG_Pixel pixel)
		{
			unsigned int position = (y * get_width() + x) * get_components();
			a_pixels[position] = pixel.red;
			a_pixels[position + 1] = pixel.green;
			a_pixels[position + 2] = pixel.blue;
			a_pixels[position + 3] = pixel.alpha;
		}
		inline void set_pixel(unsigned short x, unsigned short y, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255, unsigned short width = 1)
		{
			if (x < 0 || y < 0 || x >= get_width() || y >= get_height()) return;

			if (width == 0) return;
			else if (width == 1)
			{
				unsigned int position = (y * get_width() + x) * get_components();
				alpha = normalize_value(alpha, 0, 255);
				blue = normalize_value(blue, 0, 255);
				green = normalize_value(green, 0, 255);
				red = normalize_value(red, 0, 255);
				a_pixels[position] = red;
				a_pixels[position + 1] = green;
				a_pixels[position + 2] = blue;
				a_pixels[position + 3] = alpha;
			}
			else
			{
				draw_rect(x - ((float)width / 2.0), y - ((float)width / 2.0), width, width, red, green, blue, alpha);
			}
		}
		inline void set_pixel_alpha(unsigned short x, unsigned short y, unsigned char alpha)
		{
			alpha = normalize_value(alpha, 0, 255);
			a_pixels[(y * get_width() + x) * get_components() + 3] = alpha;
		}
		inline void set_pixel_blue(unsigned short x, unsigned short y, unsigned char blue)
		{
			blue = normalize_value(blue, 0, 255);
			a_pixels[(y * get_width() + x) * get_components() + 2] = blue;
		}
		inline void set_pixel_green(unsigned short x, unsigned short y, unsigned char green)
		{
			green = normalize_value(green, 0, 255);
			a_pixels[(y * get_width() + x) * get_components() + 1] = green;
		}
		inline void set_pixel_red(unsigned short x, unsigned short y, unsigned char red)
		{
			red = normalize_value(red, 0, 255);
			a_pixels[((y * get_width()) + x) * get_components()] = red;
		}
private:
		// Bit depth of the image
		unsigned int a_bit_depth = 8;
		// Size of a chunk to decode an image
		unsigned int a_chunk_size = pow(2, 24) - 1;
		// Color type of the image
		unsigned int a_color_type = 6;
		// Compression method of the image
		unsigned int a_compression_method = 0;
		// Error during the loading (1 = normal)
		char a_error_load = 1;
		// Filter method of the image
		unsigned int a_filter_method = 0;
		// Filter type of the image
		unsigned char a_filter_type = 0;
		// If the image is flipped by the X axis
		bool a_flipped_x = false;
		// If the image is flipped by the Y axis
		bool a_flipped_y = false;
		// Height of the image
		unsigned int a_height = 0;
		// Vector of all the IDAT chunks in the image
		std::vector<PNG_Chunk> a_idat_chunk = std::vector<PNG_Chunk>();
		// Interlace method of the image
		unsigned int a_interlace_method = 0;
		// If the image can be loaded or not
		bool a_loadable = true;
		// Path of the image
		std::string a_path = "";
		// Physical height of the image
		unsigned int a_physical_height_ratio = 10000;
		// Physical unit of the image (0 = unknow, 1 = meter)
		unsigned int a_physical_unit = 1;
		// Physical width of the image
		unsigned int a_physical_width_ratio = 10000;
		// Pixel of the image
		unsigned char* a_pixels = 0;
		// Number of data processed
		unsigned int a_processed_data = 0;
		// Starting position of the last processing
		unsigned int a_processing_last_position = 0;
		// Value of the sRGB chunk
		unsigned char a_srgb_value = 0;
		// Width of the image
		unsigned int a_width = 0;
	};
}