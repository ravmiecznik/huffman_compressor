/*
 * main.cpp
 *
 *  Created on: 18 maj 2017
 *      Author: miecznik
 */




#include <stdint.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "binary_file_handler.h"
#include <typeinfo>
#include "huffman_tree.h"
#include "word_count.h"

using namespace std;

char help[] = "Missing parameters.\n"
		"Usage: \n"
		"\thuffmann_compressor file_path word_len";



int main(int argc, char* argv[]) {
	//char file_name[] = "/home/rafal/workspace_mars/huffman_compressor/Release/test.txt";
	if(argc > 2){
		char* file_name = argv[1];
		int word_len = atoi(argv[2]);
		FileInRamObj raw_file_to_compress(file_name);
		WordFreqArray word_frequency_array = count_words(&raw_file_to_compress, word_len);
	    Word word_array[word_frequency_array.words_array.len](word_len);
	    for(uint32_t i=0; i<word_frequency_array.words_array.len; i++){
	    	word_array[i] = Word(word_frequency_array.words_array[i].container, word_len);
	    }
	    uint32_t* freq_array = word_frequency_array.freq_array.array;
	    uint32_t array_size = word_frequency_array.freq_array.len;
	    compress_stats compressed_bytes = generate_huffman_codes_for_array(word_array, freq_array, array_size);

	    //print stats for huffman codes
	    cout << "compressed bytes " << compressed_bytes.total_size << endl;
	    cout << "max key len " << +compressed_bytes.max_dict_word_len << endl;
	    uint64_t dict_size = ((word_len*8 + compressed_bytes.max_dict_word_len) * word_frequency_array.freq_array.len)/8;
	    cout << "size after compression " << compressed_bytes.total_size + dict_size << endl;
	    return 0;
	}
	else{
		cout << help << endl;
	}
	return 0;
}

