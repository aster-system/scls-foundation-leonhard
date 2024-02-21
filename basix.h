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
#include <filesystem>
#include <fstream>
#include <intrin.h>
#include <iostream>
#include <locale>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <zlib/zlib.h>

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

	// Return the content of a directory in a vector of string.
	inline std::vector<std::string> directory_content(std::string path) { std::vector<std::string> result; for (const auto& entry : std::filesystem::directory_iterator(path)) result.push_back(entry.path().string()); return result; };

	// Return the datas about a file (assuming the file exists).
	inline struct stat file_datas(std::string path) { struct stat sb; bool result = (stat(path.c_str(), &sb) == 0); return sb; };

	// Returns if a file exists.
	inline bool file_exists(std::string path) { struct stat sb; bool result = (stat(path.c_str(), &sb) == 0); return result; };

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

	// Returns if a path is a directory or not
	bool path_is_directory(std::string path)
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
	}

	// Return the content of a file in binary
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
			file.seekg(0, file.beg);
			file.close();
		}
		catch (std::ifstream::failure e) { print("Error", "System", "The file \"" + path + "\" can't be opened, error -> " + e.what() + "."); }
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

	// Write binary data in a file
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

	// Struct representing datas about a PNG chunk
	struct PNG_Chunk {
		// Positionf of the chunk in the file
		unsigned int position = 0;
		// Name of the chunk
		std::string name = "";
		// Size of the chunk
		unsigned int size = 0;
	};

	class PNG_Image
	{
		// Class representing a PNG image handler
	public:
		// PNG_Image constructor
		PNG_Image() {};
		// Get every chunks into a PNG image
		std::vector<PNG_Chunk> get_all_chunks_from_path(std::string path)
		{
			std::vector<PNG_Chunk> to_return = std::vector<PNG_Chunk>();
			if (file_exists(path) && !path_is_directory(path))
			{
				// Create the necessary things to read the PNG file
				std::vector<char*> header = std::vector<char*>();
				std::string name = "";
				std::vector<unsigned int> size = std::vector<unsigned int>();
				unsigned int size_offset = 0;

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

					// Load some chunks
					if (name == "pHYs")
					{
						load_pHYS_from_path(path, chunk);
					}
					else if (name == "IDAT")
					{
						load_IDAT_from_path(path, chunk);
					}
					std::cout << "Name " << name << " size " << chunk_size << " " << chunk.position << std::endl;
				}
			}
			return to_return;
		};
		// Load the base data of an image from a path
		inline bool load_base_from_path(std::string path)
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
				float signature[8];
				signature[0] = 137;
				signature[1] = 80;
				signature[2] = 78;
				signature[3] = 71;
				signature[4] = 13;
				signature[5] = 10;
				signature[6] = 26;
				signature[7] = 10;
				for (int i = 0; i < header.size(); i++)
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
		inline bool load_from_path(std::string path)
		{
			if (load_base_from_path(path))
			{
				get_all_chunks_from_path(path);
				std::cout << ":) " << get_width() << " " << get_height() << " " << get_bit_depht() << " " << get_color_type() << std::endl;
				std::cout << "-> " << get_physical_unit() << " " << get_physical_width_ratio() << " " << get_physical_height_ratio() << std::endl;
				std::cout << "-> " << get_compression_method() << " " << get_filter_method() << " " << get_interlace_method() << std::endl;
			}
			else
			{
				return false;
			}
		};
		// Load a IDAT chunk grom a path
		inline bool load_IDAT_from_path(std::string path, PNG_Chunk chunk)
		{
			if (file_exists(path) && !path_is_directory(path) && chunk.name == "IDAT")
			{
				// Create the necessary things to read the PNG file
				std::vector<char*> header = std::vector<char*>();
				std::vector<unsigned int> size = std::vector<unsigned int>();

				// Read into the chunk
				for (int i = 0; i < chunk.size; i++)
				{
					header.push_back((char*)(new unsigned char(0)));
					size.push_back(sizeof(unsigned char));
				}
				read_file_binary(path, header, size, chunk.position);
				int MAXINSAMPLE = pow(2, 8) - 1;
				int MAXOUTSAMPLE = pow(2, 8) - 1;
				for (int i = 0; i < 9; i++)
				{
					char result = (*header[i]) >> 3;
					std::cout << "IDAT " << i << " : " << (int)result << std::endl;
				}
				delete_binary(header);

				std::cout << "A " << zlibVersion() << std::endl;
			}
			else
			{
				return false;
			}
		};
		// Load the pHYS chunk from a path
		inline bool load_pHYS_from_path(std::string path, PNG_Chunk chunk)
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
		// PNG_Image destructor
		~PNG_Image() {};

		// Getters and setters
		inline unsigned int get_bit_depht() { return a_bit_depth; };
		inline unsigned int get_color_type() { return a_color_type; };
		inline unsigned int get_compression_method() { return a_compression_method; };
		inline unsigned int get_filter_method() { return a_filter_method; };
		inline unsigned int get_height() { return a_height; };
		inline unsigned int get_interlace_method() { return a_interlace_method; };
		inline std::string get_path() { return a_path; };
		inline unsigned int get_physical_height_ratio() { return a_physical_height_ratio; };
		inline unsigned int get_physical_unit() { return a_physical_unit; };
		inline unsigned int get_physical_width_ratio() { return a_physical_width_ratio; };
		inline unsigned int get_width() { return a_width; };
	private:
		// Bit depth of the image
		unsigned int a_bit_depth = 0;
		// Color type of the image
		unsigned int a_color_type = 0;
		// Compression method of the image
		unsigned int a_compression_method = 0;
		// Filter method of the image
		unsigned int a_filter_method = 0;
		// Height of the image
		unsigned int a_height = 0;
		// Interlace method of the image
		unsigned int a_interlace_method = 0;
		// Path of the image
		std::string a_path = "";
		// Physical height of the image
		unsigned int a_physical_height_ratio = 0;
		// Physical unit of the image (0 = unknow, 1 = meter)
		unsigned int a_physical_unit = 0;
		// Physical width of the image
		unsigned int a_physical_width_ratio = 0;
		// Width of the image
		unsigned int a_width = 0;
	};
}