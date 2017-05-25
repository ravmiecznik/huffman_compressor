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
#include "word_count.h"
#include "array.h"
#include <typeinfo>

using namespace std;

char help[] = "Missing parameters.\n"
		"Usage: \n"
		"\thuffmann_compressor file_path word_len";


int main(int argc, char* argv[]) {
	//char file_name[] = "/home/rafal/workspace_mars/huffman_compressor/Release/test.txt";
	if(argc > 2){
		char* file_name = argv[1];
		int word_len = atoi(argv[2]);
		FileInRamObj file_in_ram(file_name);
		count_words(&file_in_ram, word_len);
	}
	else{
		cout << help << endl;
	}
	return 0;
}

