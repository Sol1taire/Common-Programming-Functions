/*
Written by Chris "Sol1taire" Wood
Because if I ever have to write another CSV parser I'm going to lose my friggin' mind.
This version uses vectors and std::strings. If you want the one using raw arrays and C strings, use the raw C version.
July 2021
*/

#ifndef CSV_H
#define CSF_H

#include <vector>
#include <string>
#include <fstream>
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;

namespace cpf {

	vector<vector<string>> importCSV(string path, char delimiter = ','); //Imports an entire CSV file as a 2D vector of strings (not recommended for large files)
	bool exportCSV(vector<vector<string>> arr, string path, char delimiter = ','); //Exports a 2D vector of strings to a file in CSV format. Returns false on failure
	vector<string> csv_getNextLine(ifstream&, char delimiter = ','); //Gets the next line of a CSV file as a vector
	bool csv_exportLine(vector<string> arr, ofstream&, char delimiter = ','); //Prints a single line to an ifstream in CSV format

}

#endif
