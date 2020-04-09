#ifndef CATEGORIZER_HPP
#define CATEGORIZER_HPP

#include <iostream>
#include <fstream>

#endif

void ClearInfo()
{
	file.clear();
	filePath = "";
	width = 0;
	heght = 0;
	for (int k = 0; k < 257; k++) {
		histogram[k] = 0;
		alphabet[k] = 0;
	}
}
