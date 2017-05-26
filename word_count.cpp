/*
 * word_count.cpp
 *
 *  Created on: 19 maj 2017
 *      Author: miecznik
 */

#include "word_count.h"
#include <iomanip>
#include <sstream>


WordFreqArray::WordFreqArray(Word new_word): words_array(new_word.w_size) {
	/*
	 * create array with single elem
	 */
	word_size = new_word.w_size;
}

WordFreqArray::WordFreqArray(uint8_t size): words_array(size) {
	/*
	 * create empty array
	 */
	word_size = size;
}


bool WordFreqArray::count_next_elem(Word word_elem){
	int64_t index = words_array.find(word_elem);
	if(index==-1){
		words_array.append(word_elem);
		freq_array.append(1);
		return true;
	}else{
		freq_array[index]++;
		return false;
	}

	return true;
}

void WordFreqArray::sort(){
	for(uint32_t i=0; i<freq_array.len; i++){
		uint32_t min = freq_array[i];
		uint32_t min_index = i;
		for(uint32_t j=i; j<freq_array.len; j++){
			if(freq_array[j] < min){
				min = freq_array[j];
				min_index = j;
			}
		}
		freq_array.swap(i, min_index);
		words_array.swap(i, min_index);
	}
}

void put_word_content_to_cout(word* elem){
	uint8_t size = elem->word_size;
	stringstream tmp;
	stringstream hex_val;
	for(uint8_t i=0; i<size; i++)
		tmp << hex << +(uint8_t)(*(elem->word_ptr));
	hex_val << setfill('0') << setw(4) << tmp.str();
	cout << "0x" <<hex_val.str();
	cout << endl;
}

void put_word_content_to_cout(uint8_t* elem, uint8_t size, bool new_line, bool hex_format){
	stringstream tmp;
	stringstream hex_val;
	if(hex_format){
		for(uint8_t i=0; i<size; i++)
			tmp << hex << +(uint8_t)(elem[i]);
		hex_val << setfill('0') << setw(size*2) << tmp.str();
		cout << "0x" <<hex_val.str();
	}
	else{
		for(uint8_t i=0; i<size; i++)
			tmp << (elem[i]);
		hex_val << tmp.str();
		cout << hex_val.str();
	}
	if(new_line)
		cout << endl;
}


WordFreqArray count_words(FileInRamObj* file, uint8_t word_size){
	WordFreqArray w_array(word_size); //init WordFreqArray
	Word wrd(word_size);
	for(uint16_t i=0; i<file->size; i+=word_size){
		wrd = &file->content[i];
		w_array.count_next_elem(wrd);
	}
	w_array.sort();

	//print_word_freq_array(w_array);
	return w_array;
}

void print_word_freq_array(WordFreqArray array){
	uint32_t amount_of_bytes = 0;
	uint32_t word_count = array.words_array.len;
	uint32_t freq;
	Word tmp_w(array.word_size);
	for(uint32_t i=0; i<word_count; i++){
		tmp_w = array.words_array[i];
		freq = array.freq_array[i];
		put_word_content_to_cout(tmp_w.container, array.word_size, false, true);
		cout << " | " << freq << endl;
		amount_of_bytes+=freq;
	}
	amount_of_bytes *= array.word_size;
	cout << "Total " << +amount_of_bytes << endl;
}

