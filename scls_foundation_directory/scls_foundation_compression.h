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

	struct __Huffman_Pair {
        char chr_0 = 0;
        char chr_1 = 0;
        std::shared_ptr<__Huffman_Pair> pair_0;
        std::shared_ptr<__Huffman_Pair> pair_1;
        unsigned int total_occurences = 0;
	};

	class Huffman_Tree {
        // Class representing an Huffman tree
    public:
        Huffman_Tree(){};

        // Returns the pairs in the tree
        std::vector<std::shared_ptr<__Huffman_Pair>>& pairs() {return a_pairs;};
    private:
        // Each pairs in the tree
        std::vector<std::shared_ptr<__Huffman_Pair>> a_pairs = std::vector<std::shared_ptr<__Huffman_Pair>>();
	};

	// Do an huffman compression on a Byte_Set of datas
    std::shared_ptr<Huffman_Tree> compress_huffman(Bytes_Set* to_compress);
    std::shared_ptr<Huffman_Tree> compress_huffman(std::string to_compress);
}

#endif // SCLS_FOUNDATION_COMPRESSION
