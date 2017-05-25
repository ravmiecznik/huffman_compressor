/*
 * binary_file_handler.cpp
 *
 *  Created on: 18 maj 2017
 *      Author: miecznik
 */
/*
 * main.cpp
 *
 *  Created on: 18 maj 2017
 *      Author: miecznik
 */

#include "binary_file_handler.h"

using namespace std;


void lfill_str(char* str, char chr, uint16_t len){
	/*
	 * Function will left fill *str with provided chr and given len
	 */
	uint32_t str_len = 0;
	uint16_t i;
	while(str[str_len] != '\0')
		str_len ++;
	for(i=len-1; i>str_len; i--, str_len--){
		str[i] = str[str_len];
		str[str_len] = chr;
	}
}

bool dump_mem_to_file (char* file_name, char* buffer, uint32_t size) {
	ofstream myfile (file_name,  ios::trunc | ios::out | ios::binary);
	if (myfile.is_open())
	{
		cout << "Writing file:" << file_name << endl;
		myfile << buffer;
		cout << "Writing file:" << file_name << " done." << endl;
		myfile.close();
	}
	else cout << unable_to_open_file << file_name << endl;
	return 0;
}

FileInRamObj::FileInRamObj(char* file_name){
	cout << "File to open: " << file_name << endl;
	name = file_name;
	ifstream file (file_name, ios::in|ios::binary|ios::ate);
	if (file.is_open())
		{
		file.seekg (0, file.end);
		size = file.tellg();
		if(size > MAX_FILE_SIZE)
			cout << "ERR: file size not match to required file !!"<< endl;
		content = new uint8_t [size];
		file.seekg (0, ios::beg);
		file.read ((char*)content, size);
		file.close();
		cout << "File size: " << size << endl;
	}
	else cout << unable_to_open_file << file_name << endl;
}

FileInRamObj::~FileInRamObj(){
	delete content;
	cout << "Clean: " << name <<endl;
}

