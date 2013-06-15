#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string-utils.h"
#include "JSON-reader.h"

int main(int argc, char **argv) {
	char * inputJson;
	int i;
	char** nodesDefinitions;
	char* tmp = NULL;

	inputJson = readAndVerifyJson("/home/tomek/Pulpit/data.js");
	nodesDefinitions = splitString("}", inputJson);

	printf("Nodes definitions:\n");
	for (i = 0; i < countCharOccurrences('}', inputJson); ++i) {
		printf("%i => %s\n", i, nodesDefinitions[i]);
		printf("\t id w tym ciagu jest na pozycji: %i\n",
				endingIndexOf("id", nodesDefinitions[i]));
		tmp = substring(nodesDefinitions[i], "length\":", ",\"");
		printf("\n TMP : %s \n", tmp);
		free(tmp);
	}
	for (i = 0; i < countCharOccurrences('}', inputJson); ++i) {
		free(nodesDefinitions[i]);
	}
	free(nodesDefinitions);
	free(inputJson);
	return 0;
}
