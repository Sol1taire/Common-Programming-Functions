/*
Written by Chris "Sol1taire" Wood
Because if I ever have to write another CSV parser I'm going to lose my friggin' mind.
July 2021
*/

#ifndef CSV_H
#define CSV_H

#include <stdio.h>

char*** importCSV(char* path, char delimiter); //Imports an entire CSV file as a 2D array of strings (not recommended for large files)
short exportCSV(char*** arr, char* path, char delimiter); //Exports a 2D array of strings to a file in CSV format. Returns false on failure
char** csv_getNextLine(FILE*, char delimiter); //Gets the next line of a CSV file as an array
short csv_exportLine(char** arr, FILE*, char delimiter); //Prints a single line to a file in CSV format

#endif
