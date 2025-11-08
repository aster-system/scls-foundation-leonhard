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

	// Returns the bytes for a specific character
    std::string __Huffman_Pair::bytes_for_chr_str(char needed_chr){std::shared_ptr<Bytes_Set>current_data=bytes_for_chr(needed_chr);std::string b=current_data.get()->bits_to_std_string();return b.substr(b.size() - (hierarchy_position + 1), hierarchy_position + 1);}
    std::shared_ptr<Bytes_Set> __Huffman_Pair::bytes_for_chr(char needed_chr) {
        std::shared_ptr<Bytes_Set> needed_bytes = std::make_shared<Bytes_Set>((hierarchy_position + 1) / 8 + 1);needed_bytes.get()->fill(0);
        bytes_for_this(needed_bytes.get(), 1);
        if(chr_0 == needed_chr && pair_0.get() == 0){needed_bytes.get()->set_data_at_bit(0, false);}
        else{needed_bytes.get()->set_data_at_bit(0, true);}
        return needed_bytes;
    }
    void __Huffman_Pair::bytes_for_this(Bytes_Set* to_add, int offset) {
        if(parent() != 0) {
            if(parent()->pair_0.get() == this){to_add->set_data_at_bit(offset, false);}
            else{to_add->set_data_at_bit(offset, true);}
            parent()->bytes_for_this(to_add, offset + 1);
        }
    }

    // Sets the parent of this pair
    void __Huffman_Pair::set_parent(std::shared_ptr<__Huffman_Pair> new_pair_parent) {
        pair_parent = new_pair_parent;
        hierarchy_position = new_pair_parent.get()->hierarchy_position + 1;
    }

	// Return Huffman pair to an std::string
	std::string huffmain_pair_to_std_string(__Huffman_Pair* needed_pair){
        std::string to_return = std::string();
        if(needed_pair->pair_0.get() != 0){
            to_return += std::string("P ");
            if(needed_pair->pair_1.get() != 0){to_return += std::string("P");}
            else {to_return += std::string("\"") + needed_pair->chr_0 + std::string("\"");}
        }
        else{to_return += std::string("\"") + needed_pair->chr_0 + std::string("\"") + std::string(" ") + std::string("\"") + needed_pair->chr_1 + std::string("\"");}
        return std::to_string(needed_pair->hierarchy_position) + std::string(" ") + to_return;
	}

	// Do an huffman compression on a Byte_Set of datas
	std::shared_ptr<Huffman_Tree> generate_huffman_tree(std::string to_compress){Bytes_Set bytes = Bytes_Set(to_compress);return generate_huffman_tree(&bytes);}
    std::shared_ptr<Huffman_Tree> generate_huffman_tree(Bytes_Set* to_compress) {
        std::shared_ptr<Huffman_Tree> to_return = std::make_shared<Huffman_Tree>();

        // Search each occurences in the Bytes_Set to compress
        int* first_position = new int[256];int* occurences = new int[256];
        for(int i = 0;i<256;i++){first_position[i] = -1;occurences[i] = 0;}
        for(int i = 0;i<static_cast<int>(to_compress->datas_size());i++) {unsigned char chr = to_compress->data_at(i);occurences[chr]++;if(first_position[chr] <= -1){first_position[chr] = i;}}
        int occurences_size = 0;for(int i = 0;i<256;i++){if(occurences[i] != 0){occurences_size++;}}

        // Creates the pairs
        std::vector<std::shared_ptr<__Huffman_Pair>> all_pairs;
        std::vector<std::shared_ptr<__Huffman_Pair>> pairs;
        std::vector<std::shared_ptr<__Huffman_Pair>> pairs_by_chr = std::vector<std::shared_ptr<__Huffman_Pair>>(256);
        unsigned int total_size = 256;
        for(unsigned int i = 0;i<total_size;i++) {
            // Get the minimum index
            int min_index_0 = -1;int min_index_occurence_0 = 0;int min_index_1 = -1;int min_index_occurence_1 = 0;
            for(int j = 0;j<256;j++){if(occurences[j] != 0 && (min_index_0 < 0 || occurences[j] < occurences[min_index_0] || (occurences[j] == occurences[min_index_0] && first_position[j] < first_position[min_index_0]))){min_index_0 = j;}}
            for(int j = 0;j<256;j++){if(j != min_index_0 && occurences[j] != 0 && (min_index_1 < 0 || occurences[j] < occurences[min_index_1] || (occurences[j] == occurences[min_index_1] && first_position[j] < first_position[min_index_1]))){min_index_1 = j;}}
            if(min_index_0 > 0){min_index_occurence_0 = occurences[min_index_0];}
            if(min_index_1 > 0){min_index_occurence_1 = occurences[min_index_1];}

            // Get the minimum pairs
            std::shared_ptr<__Huffman_Pair> min_pair_0 = 0;int min_pair_index_0 = -1;std::shared_ptr<__Huffman_Pair> min_pair_1 = 0;int min_pair_index_1 = -1;
            for(int j = 0;j<static_cast<int>(pairs.size());j++){if(min_pair_0 == 0 || pairs.at(j).get()->total_occurences <= min_pair_0->total_occurences){min_pair_0 = pairs.at(j);min_pair_index_0=j;}}
            for(int j = 0;j<static_cast<int>(pairs.size());j++){if(j != min_pair_index_0 && (min_pair_1 == 0 || pairs.at(j).get()->total_occurences <= min_pair_1->total_occurences)){min_pair_1 = pairs.at(j);min_pair_index_1=j;}}

            // Break sequence
            if(min_index_1 <= -1 && min_pair_index_1 <= -1 && (min_index_0 <= -1 || min_pair_index_0 <= -1)){break;}

            // Creates the pair
            std::shared_ptr<__Huffman_Pair> new_pair = std::make_shared<__Huffman_Pair>();
            // Get the good attributions
            if(min_index_0 != -1 && min_index_1 != -1 && (min_index_occurence_1 > 0 && (min_pair_0.get() == 0 || static_cast<int>(min_pair_0.get()->total_occurences) > min_index_occurence_1))){
                new_pair.get()->chr_0 = min_index_0;new_pair.get()->chr_1 = min_index_1;
                new_pair.get()->position = std::min(first_position[min_index_0], first_position[min_index_1]);
                new_pair.get()->total_occurences = min_index_occurence_0 + min_index_occurence_1;
                pairs_by_chr[min_index_0] = new_pair;pairs_by_chr[min_index_1] = new_pair;

                // Delete the datas
                occurences[min_index_0] = 0;
                occurences[min_index_1] = 0;
            }
            else if(min_index_0 != -1 && (static_cast<int>(min_pair_0.get()->total_occurences) < min_index_occurence_1 || min_index_occurence_1 <= 0)){
                new_pair.get()->chr_0 = min_index_0;new_pair.get()->pair_0 = min_pair_0;
                new_pair.get()->position = std::min(first_position[min_index_0], min_pair_0.get()->position);
                new_pair.get()->total_occurences = min_index_occurence_0 + min_pair_0.get()->total_occurences;
                pairs_by_chr[min_index_0] = new_pair;

                // Delete the datas
                if(min_pair_0 != 0){min_pair_0.get()->set_parent(new_pair);}
                pairs.erase(pairs.begin() + min_pair_index_0);occurences[min_index_0] = 0;
            }
            else {
                if(min_pair_0.get()->total_occurences < min_pair_1.get()->total_occurences || min_pair_0.get()->position < min_pair_1.get()->position){new_pair.get()->pair_0 = min_pair_0;new_pair.get()->pair_1 = min_pair_1;}
                else{new_pair.get()->pair_0 = min_pair_1;new_pair.get()->pair_1 = min_pair_0;}
                new_pair.get()->position = new_pair.get()->pair_0.get()->position;
                int total_occurences = 0;
                if(min_pair_0.get() != 0){total_occurences += min_pair_0.get()->total_occurences;}
                if(min_pair_1.get() != 0){total_occurences += min_pair_1.get()->total_occurences;}
                new_pair.get()->total_occurences = total_occurences;

                // Delete the datas
                if(min_pair_0 != 0){min_pair_0.get()->set_parent(new_pair);}
                if(min_pair_1 != 0){min_pair_1.get()->set_parent(new_pair);}
                if(min_pair_index_0 < min_pair_index_1){min_pair_index_1--;}
                pairs.erase(pairs.begin() + min_pair_index_0);pairs.erase(pairs.begin() + min_pair_index_1);
            }
            all_pairs.push_back(new_pair);pairs.push_back(new_pair);
        }

        // Check the pairs
        for(int i = 0;i<static_cast<int>(all_pairs.size());i++){
            __Huffman_Pair* needed_parent = all_pairs.at(all_pairs.size() - (i + 1)).get()->parent();
            if(needed_parent == 0){all_pairs.at(all_pairs.size() - (i + 1)).get()->hierarchy_position = 0;}
            else{all_pairs.at(all_pairs.size() - (i + 1)).get()->hierarchy_position = needed_parent->hierarchy_position + 1;}
        }

        // Says back the pairs
        for(int i = 0;i<static_cast<int>(all_pairs.size());i++) {
            //std::cout << "E " << all_pairs.at(all_pairs.size() - (i + 1))->total_occurences << " " << huffmain_pair_to_std_string(all_pairs.at(all_pairs.size() - (i + 1)).get()) << std::endl;
        }

        // Get the current result
        for(int i = 0;i<static_cast<int>(to_compress->datas_size());i++){
            char current_chr = to_compress->data_at(i);
            std::shared_ptr<Bytes_Set> current_data;__Huffman_Pair* current_pair = pairs_by_chr[current_chr].get();
            if(current_pair != 0){std::cout << "U " << current_chr << " " << current_pair->hierarchy_position << " " << current_pair->bytes_for_chr_str(current_chr) << std::endl;}
        }

        // Return the result
        to_return.get()->set_pairs(pairs);
        return to_return;
    };
}
