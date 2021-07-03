/*
Written by Chris "Sol1taire" Wood
July 2021
*/

#include "csv.h"

vector<vector<string>> cpf::importCSV(string path, char delimiter) {
	ifstream file(path);
	vector<vector<string>> r;
	
	while(file) {
		vector<string> row = csv_getNextLine(file, delimiter);
		if (row.size()) r.push_back(row);
	}

	return r;
}


bool cpf::exportCSV(vector<vector<string>> arr, string path, char delimiter) {
	ofstream file(path);
	if (!file) return false;

	for (vector<string> v : arr) csv_exportLine(v, file, delimiter);

	return true;
}

vector<string> cpf::csv_getNextLine(ifstream& file, char delimiter) {
	string line;
	getline(file, line);

	vector<string> r;

	size_t i = 0, j = 0;
	for (; i < line.size(); i++) {
		if (line[i] == delimiter) {
			r.push_back(line.substr(j, i-j));
			j = i + 1;
		}	
	}
	if (j < line.size()) r.push_back(line.substr(j, i-j));

	return r;
}

bool cpf::csv_exportLine(vector<string> arr, ofstream& file, char delimiter) {
	if (!file) return false;

	for (int i = 0; i < arr.size(); i++) {
		file << arr[i];
		if (i < arr.size() - 1) file << delimiter;
	}

	file << '\n';

	return true;
}
