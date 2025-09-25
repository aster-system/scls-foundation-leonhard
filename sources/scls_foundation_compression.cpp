//******************
//
// scls_foundation_compression.cpp
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
// This file contains the source code of scls_foundation_compression.h.
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

#include "../scls_foundation_directory/scls_foundation_compression.h"

// The namespace "scls" is used to simplify the all.
namespace scls {
    //*********
	//
	// Huffman algorithm
	//
	//*********

	// Return Huffman pair to an std::string
	std::string huffmain_pair_to_std_string(__Huffman_Pair* needed_pair){
        std::string to_return = std::string();
        if(needed_pair->pair_0.get() != 0){
            to_return += std::string("P ");
            if(needed_pair->pair_1.get() != 0){to_return += std::string("P");}
            else {to_return += std::string("\"") + needed_pair->chr_0 + std::string("\"");}
        }
        else{to_return += std::string("\"") + needed_pair->chr_0 + std::string("\"") + std::string(" ") + std::string("\"") + needed_pair->chr_1 + std::string("\"");}
        return to_return;
	}

	// Do an huffman compression on a Byte_Set of datas
	std::shared_ptr<Huffman_Tree> compress_huffman(std::string to_compress){Bytes_Set bytes = Bytes_Set(to_compress);return compress_huffman(&bytes);}
    std::shared_ptr<Huffman_Tree> compress_huffman(Bytes_Set* to_compress) {
        std::shared_ptr<Huffman_Tree> to_return = std::make_shared<Huffman_Tree>();

        // Search each occurences in the Bytes_Set to compress
        int* occurences = new int[256];
        for(int i = 0;i<256;i++){occurences[i] = 0;}
        for(int i = 0;i<static_cast<int>(to_compress->datas_size());i++) {unsigned char chr = to_compress->data_at(i);occurences[chr]++;}
        int occurences_size = 0;for(int i = 0;i<256;i++){if(occurences[i] != 0){occurences_size++;}}

        // Creates the pairs
        std::vector<std::shared_ptr<__Huffman_Pair>> all_pairs;
        std::vector<std::shared_ptr<__Huffman_Pair>> pairs;
        unsigned int total_size = 256;
        for(unsigned int i = 0;i<total_size;i++) {
            // Get the minimum index
            int min_index_0 = 0;int min_index_occurence_0 = 0;int min_index_1 = 0;int min_index_occurence_1 = 0;
            for(int j = 0;j<256;j++){if(occurences[j] != 0 && (occurences[j] < occurences[min_index_0] || occurences[min_index_0] == 0)){min_index_0 = j;}}
            for(int j = 0;j<256;j++){if(j != min_index_0 && occurences[j] != 0 && (occurences[j] < occurences[min_index_1] || occurences[min_index_1] == 0)){min_index_1 = j;}}
            min_index_occurence_0 = occurences[min_index_0];min_index_occurence_1 = occurences[min_index_1];

            // Get the minimum pairs
            std::shared_ptr<__Huffman_Pair> min_pair_0 = 0;int min_pair_index_0 = 0;std::shared_ptr<__Huffman_Pair> min_pair_1 = 0;int min_pair_index_1 = 0;
            for(int j = 0;j<static_cast<int>(pairs.size());j++){if(min_pair_0 == 0 || pairs.at(j).get()->total_occurences < min_pair_0->total_occurences){min_pair_0 = pairs.at(j);min_pair_index_0=j;}}
            for(int j = 0;j<static_cast<int>(pairs.size());j++){if(j != min_pair_index_0 && (min_pair_1 == 0 || pairs.at(j).get()->total_occurences < min_pair_1->total_occurences)){min_pair_1 = pairs.at(j);min_pair_index_1=j;}}

            // Creates the pair
            std::shared_ptr<__Huffman_Pair> new_pair = std::make_shared<__Huffman_Pair>();
            // Get the good attributions
            if((min_pair_0.get() == 0 && min_pair_1 == 0) || (min_index_occurence_1 > 0 && min_pair_0.get()->total_occurences > min_index_occurence_1)){
                new_pair.get()->chr_0 = min_index_0;new_pair.get()->chr_1 = min_index_1;
                new_pair.get()->total_occurences = min_index_occurence_0 + min_index_occurence_1;

                // Delete the datas
                occurences[min_index_0] = 0;
                occurences[min_index_1] = 0;
            }
            else if(min_pair_0.get()->total_occurences < min_index_occurence_1 || min_index_occurence_1 <= 0){
                new_pair.get()->chr_0 = min_index_0;new_pair.get()->pair_0 = min_pair_0;
                new_pair.get()->total_occurences = min_index_occurence_0 + min_pair_0.get()->total_occurences;

                // Delete the datas
                if(min_pair_0 != 0){pairs.erase(pairs.begin() + min_pair_index_0);}
                occurences[min_index_0] = 0;
            }
            else {
                new_pair.get()->pair_0 = min_pair_0;new_pair.get()->pair_1 = min_pair_1;
                int total_occurences = 0;
                if(min_pair_0.get() != 0){total_occurences += min_pair_0.get()->total_occurences;}
                if(min_pair_1.get() != 0){total_occurences += min_pair_1.get()->total_occurences;}
                new_pair.get()->total_occurences = total_occurences;

                // Delete the datas
                if(min_pair_0 != 0){pairs.erase(pairs.begin() + min_pair_index_0);}
                if(min_pair_1 != 0){if(min_pair_index_0 < min_pair_index_1){min_pair_index_1--;}pairs.erase(pairs.begin() + min_pair_index_1);}
            }
            all_pairs.push_back(new_pair);pairs.push_back(new_pair);

            /*// Get the minimum chars
            unsigned int j = 0;
            char minimum_1 = 0;
            unsigned int minimum_occurences_1 = -1;
            //unsigned int minimum_pos_1 = 0;
            for(std::map<char, unsigned int>::iterator it = occurences.begin();it!=occurences.end();it++) {
                if(it->second < minimum_occurences_1) {
                    minimum_1 = it->first;
                    minimum_occurences_1 = it->second;
                    //minimum_pos_1 = j;
                }
                j++;
            }
            j = 0;
            char minimum_2 = 0;
            unsigned int minimum_occurences_2 = -1;
            //unsigned int minimum_pos_2 = 0;
            for(std::map<char, unsigned int>::iterator it = occurences.begin();it!=occurences.end();it++) {
                if(it->second < minimum_occurences_2 && it->first != minimum_1) {
                    minimum_2 = it->first;
                    minimum_occurences_2 = it->second;
                    //minimum_pos_2 = j;
                }
                j++;
            }

            // Get the minimum pairs
            std::shared_ptr<_Huffman_Pair>* minimum_pair_1 = 0;
            int minimum_pair_occurences_1 = -1;
            unsigned int minimum_pair_pos_1 = 0;
            for(int j = 0;j<static_cast<int>(pairs.size());j++) {
                if(static_cast<int>(pairs[j].get()->total_occurences) < minimum_pair_occurences_1) {
                    minimum_pair_1 = &pairs[j];
                    minimum_pair_occurences_1 = pairs[j].get()->total_occurences;
                    minimum_pair_pos_1 = j;
                }
            }
            std::shared_ptr<_Huffman_Pair>* minimum_pair_2 = 0;
            int minimum_pair_occurences_2 = -1;
            unsigned int minimum_pair_pos_2 = 0;
            for(int j = 0;j<static_cast<int>(pairs.size());j++) {
                if(static_cast<int>(pairs[j].get()->total_occurences) < minimum_pair_occurences_2 && pairs[j].get() != minimum_pair_1->get()) {
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
            //*/
        }

        // Says bakc the pairs
        for(int i = 0;i<static_cast<int>(all_pairs.size());i++) {
            std::cout << "E " << all_pairs.at(all_pairs.size() - (i + 1))->total_occurences << " " << huffmain_pair_to_std_string(all_pairs.at(all_pairs.size() - (i + 1)).get()) << std::endl;
        }

        return to_return;
    };
}
