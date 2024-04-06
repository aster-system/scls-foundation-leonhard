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

    // Format a path to the SCLS format
    static std::string format_path(std::string path) {
        std::vector<std::string> cutted = cut_string(join_string(cut_string(path, "/", true), "\\"), "\\", true);
        std::vector<std::string> cutted_final = std::vector<std::string>();

        for(int i = 0;i<static_cast<int>(cutted.size());i++) {
            if(cutted[i] == ".." && i > 0) {
                cutted_final.pop_back();
                continue;
            }
            else if(cutted[i] == ".") continue;
            cutted_final.push_back(cutted[i]);
        }

        return join_string(cutted_final, "/");
    }

    // Return the way to got to the second path from the first path, assuming they are in the same disk, and (even better), the same set of directory, starting from the same path
    static std::string go_from_path_to_path(std::string first_path, std::string second_path) {
        std::vector<std::string> cutted_1 = cut_string(join_string(cut_string(first_path, "/", true), "\\"), "\\", true); if(contains(cutted_1[cutted_1.size() - 1], ".")) cutted_1.pop_back();
        std::vector<std::string> cutted_2 = cut_string(join_string(cut_string(second_path, "/", true), "\\"), "\\", true); if(contains(cutted_2[cutted_2.size() - 1], ".")) cutted_2.pop_back();

        std::string final_path = "";

        if(cutted_1.size() > cutted_2.size()) {
            for(int i = 0;i<cutted_1.size()-cutted_2.size();i++) final_path += "../";

            int level = 0;
            for(int i = 0;i<cutted_2.size();i++) {
                if(cutted_2[i] != cutted_1[i]) break;
                level++;
            }

            for(int i = 0;i<cutted_2.size() - level;i++) {
                final_path += "../";
            }

            for(int i = level;i<cutted_2.size();i++) {
                final_path += cutted_2[i] + "/";
            }
        }
        else final_path = "";
        #define TO_FINISH_HERE

        return final_path;
    }

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
