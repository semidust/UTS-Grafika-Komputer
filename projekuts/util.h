#pragma once

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string readFile(string fileName) {
	std::cout << "Reading file " << fileName << std::endl;
	string fileText;

	ifstream myFile(fileName);

	string tempText;

	while (getline(myFile, tempText)) {
		fileText += tempText + "\n";
	}

	std::cout << fileText << std::endl;

	return fileText;
}