//******************
// 
// basix_file.h
// 
//******************
// Presentation :
// 
// Basix is a little project containing base functions for Matix.
// It can also be use in any projects.
// This file contains things to do some file manipulation.
//
//******************
// Warning :
// 
// The <filesystem> module needs C++ 20 at least.
//

#pragma once

#include <codecvt>
#include <filesystem>
#include <fstream>
#include <locale>
#include <sstream>

#include "basix_data_structure.h"

// The namespace "basix" is used to simplify the all.
namespace basix
{
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
		return static_cast<unsigned int>(in.tellg());
	}

	// Returns if a path is a directory or not
	inline bool path_is_directory(std::string path) { return ((file_datas(path).st_mode & S_IFDIR) == S_IFDIR); };

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
}