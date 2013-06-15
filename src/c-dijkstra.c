#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string-utils.h"
#include "JSON-reader.h"

struct Edge {
	unsigned int endNode;
	unsigned int distanceToEndNode;
};

struct Node {
	unsigned int id;
	unsigned int length;
	struct Edge * edges;
};

char * getNodeDefinitionParameter(char * parameterName, char * nodeDefinition) {
	char parameterPattern[20];
	/* Tworzy ciag "\""+parameterName+"\":" */
	strcpy(parameterPattern, "\"");
	strcat(parameterPattern, parameterName);
	strcat(parameterPattern, "\":");
	return substring(nodeDefinition, parameterPattern, ",\"");
}

int main(int argc, char **argv) {
	char * inputJson;
	int i;
	char** nodesDefinitions;
	char* tmp = NULL;
	inputJson = readAndVerifyJson("/home/tomek/Pulpit/data.js");
	printf("Char occurrences %s", inputJson);
	nodesDefinitions = splitString("}", inputJson);
	printf("Nodes definitions:\n");
	for (i = 0; i < countCharOccurrences('}', inputJson); ++i) {
		printf("%i => %s\n", i, nodesDefinitions[i]);
		tmp = getNodeDefinitionParameter("distances", nodesDefinitions[i]);
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
