//******************
//
// scls_foundation_compression.h
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
// This file contains some datas to do data compression, essentially with Deflate algorithm.
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

#ifndef SCLS_FOUNDATION_COMPRESSION
#define SCLS_FOUNDATION_COMPRESSION

#include "scls_foundation_binary.h"

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// Huffman algorithm
	//
	//*********

	struct _Huffman_Pair {
        char chr_0 = 0;
        char chr_1 = 0;
        _Huffman_Pair* pair_0 = 0;
        _Huffman_Pair* pair_1 = 0;
        unsigned int total_occurences = 0;
	};

	class Huffman_Tree {
        // Class representing an Huffman tree
    public:
        Huffman_Tree(){};
	};

	// Do an huffman compression on a Byte_Set of datas
    static Huffman_Tree compress_huffman(Bytes_Set* to_compress) {
        Huffman_Tree to_return = Huffman_Tree();

        std::map<char, unsigned int> occurences = std::map<char, unsigned int>();
        for(int i = 0;i<static_cast<int>(to_compress->datas_size());i++) {
            char chr = to_compress->data_at(i);
            bool defined = false;
            for(std::map<char, unsigned int>::iterator it = occurences.begin();it!=occurences.end();it++) {
                if(it->first == chr) {
                    it->second++;
                    defined = true;
                    break;
                }
            }
            if(!defined) occurences[chr] = 1;
        }

        std::vector<_Huffman_Pair> pairs = std::vector<_Huffman_Pair>();
        unsigned int total_size = occurences.size();

        for(unsigned int i = 0;i<total_size;i++) {
            unsigned int j = 0;
            char minimum_1 = 0;
            unsigned int minimum_occurences_1 = -1;
            unsigned int minimum_pos_1 = 0;
            for(std::map<char, unsigned int>::iterator it = occurences.begin();it!=occurences.end();it++) {
                if(it->second < minimum_occurences_1) {
                    minimum_1 = it->first;
                    minimum_occurences_1 = it->second;
                    minimum_pos_1 = j;
                }
                j++;
            }
            j = 0;
            char minimum_2 = 0;
            unsigned int minimum_occurences_2 = -1;
            unsigned int minimum_pos_2 = 0;
            for(std::map<char, unsigned int>::iterator it = occurences.begin();it!=occurences.end();it++) {
                if(it->second < minimum_occurences_2 && it->first != minimum_1) {
                    minimum_2 = it->first;
                    minimum_occurences_2 = it->second;
                    minimum_pos_2 = j;
                }
                j++;
            }

            if(minimum_pos_1 > minimum_pos_2) {
                occurences.erase(minimum_1);
                occurences.erase(minimum_2);
            }
            else {
                occurences.erase(minimum_2);
                occurences.erase(minimum_1);
            }

            std::cout << "P " << minimum_1 << " " << minimum_2 << std::endl;
        }

        return to_return;
    };
}

#endif // SCLS_FOUNDATION_COMPRESSION
