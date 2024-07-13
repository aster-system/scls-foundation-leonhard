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
        std::shared_ptr<_Huffman_Pair> pair_0;
        std::shared_ptr<_Huffman_Pair> pair_1;
        unsigned int total_occurences = 0;
	};

	class Huffman_Tree {
        // Class representing an Huffman tree
    public:
        Huffman_Tree(){};

        // Returns the pairs in the tree
        std::vector<std::shared_ptr<_Huffman_Pair>>& pairs() {return a_pairs;};
    private:
        // Each pairs in the tree
        std::vector<std::shared_ptr<_Huffman_Pair>> a_pairs = std::vector<std::shared_ptr<_Huffman_Pair>>();
	};

	// Do an huffman compression on a Byte_Set of datas
    static std::shared_ptr<Huffman_Tree> compress_huffman(Bytes_Set* to_compress) {
        std::shared_ptr<Huffman_Tree> to_return = std::make_shared<Huffman_Tree>();

        //Search each occurences in the Bytes_Set to compress
        std::map<char, unsigned int> occurences = std::map<char, unsigned int>();
        for(int i = 0;i<to_compress->datas_size();i++) {
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

        // Creates the pairs
        std::vector<std::shared_ptr<_Huffman_Pair>>& pairs = to_return.get()->pairs();
        unsigned int total_size = occurences.size() - 1;
        for(int i = 0;i<total_size;i++) {
            // Get the minimum chars
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

            // Get the minimum pairs
            std::shared_ptr<_Huffman_Pair>* minimum_pair_1 = 0;
            int minimum_pair_occurences_1 = -1;
            unsigned int minimum_pair_pos_1 = 0;
            for(int j = 0;j<static_cast<int>(pairs.size());j++) {
                if(pairs[j].get()->total_occurences < minimum_pair_occurences_1) {
                    minimum_pair_1 = &pairs[j];
                    minimum_pair_occurences_1 = pairs[j].get()->total_occurences;
                    minimum_pair_pos_1 = j;
                }
            }
            std::shared_ptr<_Huffman_Pair>* minimum_pair_2 = 0;
            int minimum_pair_occurences_2 = -1;
            unsigned int minimum_pair_pos_2 = 0;
            for(int j = 0;j<static_cast<int>(pairs.size());j++) {
                if(pairs[j].get()->total_occurences < minimum_pair_occurences_2 && pairs[j].get() != minimum_pair_1->get()) {
                    minimum_pair_2 = &pairs[j];
                    minimum_pair_occurences_2 = pairs[j].get()->total_occurences;
                    minimum_pair_pos_2 = j;
                }
            }

            std::cout << "J " << pairs.size() << " " << minimum_pair_1 << " " << minimum_pair_2 << " " << minimum_pair_occurences_1  << std::endl;

            // Use the neeeded datas
            char checked_char[2];
            checked_char[0] = minimum_1;
            checked_char[1] = minimum_2;
            unsigned int checked_char_occurences[2];
            checked_char_occurences[0] = minimum_occurences_1;
            checked_char_occurences[1] = minimum_occurences_2;
            std::shared_ptr<_Huffman_Pair>* checked_pair[2];
            checked_pair[0] = minimum_pair_1;
            checked_pair[1] = minimum_pair_2;
            unsigned int checked_pair_occurences[2];
            checked_pair_occurences[0] = minimum_pair_occurences_1;
            checked_pair_occurences[1] = minimum_pair_occurences_2;
            unsigned int checked_pair_positions[2];
            checked_pair_positions[0] = minimum_pair_pos_1;
            checked_pair_positions[1] = minimum_pair_pos_2;
            unsigned char current_checked_char = 0;
            unsigned char current_checked_pair = 0;
            std::shared_ptr<_Huffman_Pair> current_pair = std::make_shared<_Huffman_Pair>();
            // First test
            if(checked_char_occurences[current_checked_char] < checked_pair_occurences[current_checked_pair] || checked_pair[current_checked_pair] == 0) {
                current_pair.get()->total_occurences += checked_char_occurences[current_checked_char];
                if(current_checked_char == 0) current_pair.get()->chr_0 = minimum_1;
                else current_pair.get()->chr_1 = minimum_2;
                occurences.erase(checked_char[current_checked_char]);
                current_checked_char++;
            } else {
                current_pair.get()->total_occurences += checked_pair_occurences[current_checked_pair];
                if(current_checked_pair == 0) current_pair.get()->pair_0 = *minimum_pair_1;
                else current_pair.get()->pair_1 = *minimum_pair_2;
                pairs.erase(pairs.begin() + checked_pair_positions[current_checked_pair]);
                current_checked_pair++;
            }
            // Second test
            if(checked_char_occurences[current_checked_char] < checked_pair_occurences[current_checked_pair] || checked_pair[current_checked_pair] == 0) {
                current_pair.get()->total_occurences += checked_char_occurences[current_checked_char];
                if(current_checked_char == 0) current_pair.get()->chr_0 = minimum_1;
                else current_pair.get()->chr_1 = minimum_2;
                occurences.erase(checked_char[current_checked_char]);
                current_checked_char++;
            } else {
                current_pair.get()->total_occurences += checked_pair_occurences[current_checked_pair];
                if(current_checked_pair == 0) current_pair.get()->pair_0 = *minimum_pair_1;
                else current_pair.get()->pair_1 = *minimum_pair_2;
                pairs.erase(pairs.begin() + checked_pair_positions[current_checked_pair]);
                current_checked_pair++;
            }

            // Create the pair
            pairs.push_back(current_pair);
            std::cout << "P " << pairs.size() << " " << current_pair.get()->chr_0 << " " << current_pair.get()->chr_1 << " " << current_pair.get()->pair_0.get() << " " << current_pair.get()->pair_1.get() << std::endl;
        }

        return to_return;
    };
}

#endif // SCLS_FOUNDATION_COMPRESSION
