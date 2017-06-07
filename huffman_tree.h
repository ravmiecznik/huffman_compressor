/*
 * huffman_tree.h
 *
 *  Created on: 25 maj 2017
 *      Author: miecznik
 */

#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

#include <stdint.h>
#include "array.h"

struct compress_stats{
	/*
	 * structure used to collect statistics about compression
	 * total_size: number of bits after coding
	 *
	 */
	uint64_t total_size;
	uint8_t max_dict_word_len;
};

compress_stats generate_huffman_codes_for_array(Word data[], uint32_t freq[], uint32_t size);



#endif /* HUFFMAN_TREE_H_ */
