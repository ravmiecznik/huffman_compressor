/*
 * binary_file_handler.h
 *
 *  Created on: 18 maj 2017
 *      Author: miecznik
 */

#ifndef BINARY_FILE_HANDLER_H_
#define BINARY_FILE_HANDLER_H_

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#ifndef	MAX_FILE_SIZE
	#define MAX_FILE_SIZE	0x8000
#endif

const char unable_to_open_file[] = "Unable to open file: ";
void lfill_str(char* str, char chr, uint16_t len);
bool dump_mem_to_file (char* file_name, char* buffer, uint32_t size);

class FileInRamObj{
public:
	uint8_t* content;
	streampos size;
	char* name;
	FileInRamObj(char* file_name);
	FileInRamObj() {};
	~FileInRamObj();
};




#endif /* BINARY_FILE_HANDLER_H_ */
