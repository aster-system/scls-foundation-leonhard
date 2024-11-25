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
#include "scls_foundation_string.h"

#ifndef SCLS_FOUNDATION_FILE_INIT
#if defined(__WIN32__) || defined(__WIN64__)
    #define SCLS_FOUNDATION_FILE_INIT std::string scls::clipboard_datas() {\
	    std::string to_return = "";\
	    if(!OpenClipboard(0)) return "";\
        char* datas = reinterpret_cast< char*>(GetClipboardData(CF_TEXT));\
        CloseClipboard();\
        if(datas == 0) return "";\
        to_return = datas;\
	    return to_utf_8(to_return);\
	} std::string scls::current_user_home_directory() {\
	    std::string to_return = "";\
        char* user_ca = getenv("USERPROFILE");\
	    if(user_ca == 0) return "";\
	    to_return = user_ca;\
	    to_return = replace(to_return, "\\", "/");\
	    return to_return;\
	} std::string scls::current_user_document_directory() { return scls::current_user_home_directory() + "/Documents"; }
#elif defined(__linux__)
    #define SCLS_FOUNDATION_FILE_INIT std::string scls::clipboard_datas() {\
	    std::string to_return = "";\
	    return to_utf_8(to_return);\
	} std::string scls::current_user_home_directory() {\
	    std::string to_return = "";\
        char* user_ca = getenv("HOME");\
	    if(user_ca == 0) return "";\
	    to_return = user_ca;\
	    to_return = replace(to_return, "\\", "/");\
	    return to_return;\
	} std::string scls::current_user_document_directory() { return scls::current_user_home_directory() + "/Documents"; }
#endif // defined
#endif // SCLS_FOUNDATION_FILE_INIT

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// Get datas about files
	//
	//*********

	// Get the datas in the clipboard
    std::string clipboard_datas();

	// Cut a path between its parent path
    std::vector<std::string> cut_path(std::string path, bool full_path = false);
	// Return the content of a directory in a vector of string.
    std::vector<std::string> directory_content(std::string path, bool sub_directory = false);

	// Return the extension / name of the file
    std::string file_extension(std::string path, bool with_point = false);
    std::string file_name(std::string path, bool with_extension = false);

    // Returns the parent path of a path
    std::string path_parent(std::string path);

    //*********
	//
	// Get specials files
	//
	//*********

	// Returns the home path of the user
    std::string current_user_home_directory();
    std::string current_user_document_directory();

    //*********
	//
	// Read and write in files
	//
	//*********

	// Return the content of a file.
    std::string read_file(std::string path);

	// Write something in a file.
    void write_in_file(std::string path, std::string to_write, std::ios::openmode opening_mode = std::ios::out);
    void write_in_file(std::string path, String to_write, std::ios::openmode opening_mode = std::ios::out);
}

#endif // SCLS_FOUNDATION_FILE
