/*
Written by Chris "Sol1taire" Wood
July 2021
*/

#include "csv.h"
#include <stdlib.h>
#include <string.h>

const long int MAX_BUFFER_SIZE = 10000; //Change as necessary

static int countFields(char* line, char delimiter) {
	int r = 0, i = 0;
	for (; line[i] != '\0' && line[i] != '\n'; i++) {
		if (line[i] == delimiter) r++;
	}
	if (i > 0) r++;
	return r;
}

char*** importCSV(char* path, char delimiter) {
	FILE* file = fopen(path, "r");
	char*** buffer = calloc(sizeof(char**), MAX_BUFFER_SIZE);
	int length = 0;

	while (1) {

		char** nextLine = csv_getNextLine(file, delimiter);
		if (feof(file)) break;
		
		buffer[length] = nextLine;
		length++;

		if (length % MAX_BUFFER_SIZE == 0) {
			char*** newBuffer = calloc(sizeof(char**), length + MAX_BUFFER_SIZE);
			memcpy(newBuffer, buffer, sizeof(char**) * length);
			free(buffer);
			buffer = newBuffer;
		}

	}

	if (!length) return NULL;
	else {
		char*** r = calloc(sizeof(char**), length + 1);
		memcpy(r, buffer, sizeof(char**) * length);
		free(buffer);
		return r;
	}
}

short exportCSV(char*** arr, char* path, char delimiter) {
	FILE* file = fopen(path, "w");

	for (int i = 0; arr[i] != NULL; i++) {
		if (!csv_exportLine(arr[i], file, delimiter)) return 0;
	}
	fclose(file);
	return 1;
}

char** csv_getNextLine(FILE* file, char delimiter) {
	char buffer[MAX_BUFFER_SIZE];
	fgets(buffer, MAX_BUFFER_SIZE, file);
	
	int numFields = countFields(buffer, delimiter);
	char** r = malloc(sizeof(char*) * (numFields + 1));

	int i, j, n;
	for (i = 0, j = 0, n = 0; buffer[i] != '\0'; i++) {

		if (buffer[i] == delimiter) {
			r[n] = calloc(sizeof(char*), i - j + 1);
			strncpy(r[n], buffer + j, i-j);
			n++;
			j = i + 1;
		}

	}
	if (buffer[j] != '\0' && buffer[j] != '\n') {
		r[n] = calloc(sizeof(char*), i - j);
		strncpy(r[n], buffer + j, i-j - 1);
	}
	r[numFields] = NULL;

	return r;
}

short csv_exportLine(char** arr, FILE* file, char delimiter) {
	for (int i = 0; arr[i] != NULL; i++) {
		fputs(arr[i], file);
		if (arr[i+1] != NULL) fputc(delimiter, file);
		else fputc('\n', file);
	}
	
	return 1;
}
