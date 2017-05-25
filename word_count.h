/*
 * word_count.h
 *
 *  Created on: May 19, 2017
 *      Author: rafal
 */

#ifndef WORD_COUNT_H_
#define WORD_COUNT_H_

#include "binary_file_handler.h"
#include <cstring>
#include "array.h"

#ifndef WORD_LEN_BYTES
	#define	WORD_LEN_BYTES	2
#endif
#ifndef MAX_FILE_SIZE
	#define	MAX_FILE_SIZE	0x8000
#endif

class word{
/*
 * makes a variable length word
 */
public:
	uint8_t* word_ptr;
	uint8_t word_size;
	word(uint8_t *a, uint8_t size){
		word_size = size;
		word_ptr = a;
	}
};



//struct word_freq{
//	uint8_t* w;
//	uint32_t freq;
//};


void put_word_content_to_cout(word* elem);
void put_word_content_to_cout(uint8_t* elem, uint8_t size);
void put_word_content_to_cout(uint8_t* elem, uint8_t size, bool new_line=true, bool hex_format=false);

class WordFreqArray{
	/*
	 * This class will collect unique words.
	 */
private:
	//word_freq* check_if_elem_in_array(word* elem);
	void add_new_elem(Word elem);
public:
	WordArray	words_array;
	Array<uint32_t>	freq_array;
	uint8_t  word_size;							//word size
	WordFreqArray(Word);						//inits WordFreqArray with first element
	WordFreqArray(uint8_t size);				//inits WordFreqArray with no elements, creates a pointer to array
	bool count_next_elem(Word elem);		//will add or count a new word into array
	uint32_t get_num_of_elems();
	void operator<(Word elem){
		count_next_elem(elem);
	}
};

void print_word_freq_array(WordFreqArray);
void count_words(FileInRamObj* file, uint8_t word_size = 2);



#endif /* WORD_COUNT_H_ */
