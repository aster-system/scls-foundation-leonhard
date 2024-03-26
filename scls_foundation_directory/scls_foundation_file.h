//******************
//
// scls_foundation_file.h
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
// This file contains things to do some file manipulation.
//

#ifndef SCLS_FOUNDATION_FILE
#define SCLS_FOUNDATION_FILE

#include "scls_foundation_binary.h"

// The namespace "scls" is used to simplify the all.
namespace scls
{
    //*********
	//
	// Get datas about files
	//
	//*********

	// Return the content of a directory in a vector of string.
	inline std::vector<std::string> directory_content(std::string path, bool sub_directory = false) {
		std::vector<std::string> result;
		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
		{
			std::string path = entry.path().string();
			if (sub_directory && std::filesystem::is_directory(path))
			{
				std::vector<std::string> sub = directory_content(path, true);
				for (int i = 0; i < static_cast<int>(sub.size()); i++) result.push_back(sub[i]);
			}
			else
			{
				result.push_back(path);
			}
		}
		return result;
	};

	// Return the extension of the file
	inline std::string file_extension(std::string path, bool with_point = false) {
	    std::filesystem::path p = path; std::string extension = p.extension().string();;
	    if(with_point || extension.size() == 0 || extension[0] != '.')return extension;
	    return extension.substr(1, extension.size() - 1);
    };

	// Return the name of the file
	inline std::string file_name(std::string path, bool with_extension = false) {
	    std::filesystem::path p = path; std::string name = p.filename().string();
	    if(with_extension) return name;
	    return name.substr(0, name.size() - file_extension(path, true).size());
    };

    //*********
	//
	// Read and write in files
	//
	//*********

	// Return the content of a file.
	inline std::string read_file(std::string path) {
		std::string file_content = ""; unsigned int total_size = 0;
		char* content = read_entire_file_binary(path, total_size);

		if(content != 0) {
            for(unsigned int i = 0;i<total_size;i++) file_content += content[i];
            delete[] content; content = 0;
		}

		return file_content;
	};

	// Write something in a file.
	inline void write_in_file(std::string path, std::string to_write, std::ios::openmode opening_mode = std::ios::out) {
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
			print("Error", "SCLS", "The file \"" + path + "\" can't be written in error -> " + e.what() + ".");
		}
	}
}

#endif // SCLS_FOUNDATION_FILE
