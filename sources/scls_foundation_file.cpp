//******************
//
// scls_foundation_file.cpp.
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
// This file contains the source code of scls_foundation_file.h.
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
#include "../scls_foundation_directory/scls_foundation_file.h"

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// Get datas about files
	//
	//*********

	// Cut a path between its parent path
    std::vector<std::string> cut_path(std::string path, bool full_path) {
        std::filesystem::path p = path;
        std::filesystem::path parent = p.parent_path();
        std::vector<std::string> to_return = std::vector<std::string>();
        do {
            if(full_path) to_return.push_back(p.string());
            else to_return.insert(to_return.begin(), p.filename().string());
            p = parent;
            parent = p.parent_path();
        } while(p != parent);
        to_return.push_back(p.root_name().string());
        return to_return;
    };

	// Return the content of a directory in a vector of string.
    std::vector<std::string> directory_content(std::string path, bool sub_directory) {
		std::vector<std::string> result;
		if(!std::filesystem::exists(path)) {
            print("Error", "SCLS", "The path \"" + path + "\" you want to get the directory content does not exists.");
            return result;
		}
		else if(!std::filesystem::is_directory(path)) {
            print("Error", "SCLS", "The path \"" + path + "\" you want to get the directory content is not a directory.");
            return result;
		}

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
    std::string file_extension(std::string path, bool with_point) {
	    std::filesystem::path p = path; std::string extension = p.extension().string();;
	    if(with_point || extension.size() == 0 || extension[0] != '.')return extension;
	    return extension.substr(1, extension.size() - 1);
    };

	// Return the name of the file
    std::string file_name(std::string path, bool with_extension) {
	    std::filesystem::path p = path; std::string name = p.filename().string();
	    if(with_extension) return name;
	    return name.substr(0, name.size() - file_extension(path, true).size());
    };

    // Returns the parent path of a path
    std::string path_parent(std::string path) { std::filesystem::path p = path; return p.parent_path().string(); };

    //*********
	//
	// Read and write in files
	//
	//*********

	// Return the content of a file.
    std::string read_file(std::string path) {
		std::string file_content = ""; unsigned int total_size = 0;
		char* content = read_entire_file_binary(path, total_size);

		if(content != 0) {
            for(unsigned int i = 0;i<total_size;i++) file_content += content[i];
            delete[] content; content = 0;
		}

		return file_content;
	};

	// Write something in a file.
    void write_in_file(std::string path, std::string to_write, std::ios::openmode opening_mode) {
		std::ofstream file;
		file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		try {
			file.open(path, opening_mode);
			file << to_write;
			file.close();
		} catch (std::ofstream::failure& e) {
			print("Error", "SCLS", "The file \"" + path + "\" can't be written in error -> " + e.what() + ".");
		}
	}

	// Write something in a file with String
    void write_in_file(std::string path, String to_write, std::ios::openmode opening_mode) {write_in_file(path, to_write.to_std_string(), opening_mode);};
}
