#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string-utils.h"
#include "JSON-reader.h"
#include "graph.h"

int main(int argc, char **argv) {
	struct Node * nodes = NULL;
	int nodesCount, i;
	char * inputJson;

	/* Zweryfikuj i pobierz JSON*/
	inputJson = readAndVerifyJson("/home/tomek/Pulpit/data.js");
	nodesCount = countNodesFromJson(inputJson);
	nodes = getNodesFromJson(inputJson);
	for (i = 0; i < nodesCount; ++i) {
		free(nodes[i].edges);
	}
	free(nodes);
	free(inputJson);
	return 0;
}
