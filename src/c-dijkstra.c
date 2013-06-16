#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string-utils.h"
#include "JSON-reader.h"
#include "graph.h"

#define INFITITY 2147483647;

void setInfinityDistanceForEachNode(struct Node * nodes, int nodesCount) {
	int i;
	for (i = 0; i < nodesCount; ++i) {
		nodes[i].distance = INFITITY
		;
	}
}

struct Node * getNode(unsigned int nodeId, struct Node * nodes, int nodesCount) {
	int i;
	for (i = 0; i < nodesCount; ++i) {
		if (nodes[i].id == nodeId) {
			return &nodes[i];
		}
	}
	return NULL ;
}

int main(int argc, char **argv) {
	struct Node * nodes = NULL;
	struct Node * startNode;
	int nodesCount, i;
	char * inputJson;
	int startNodeId = 13;
	int endNodeId = 3;

	/* Zweryfikuj i pobierz JSON*/
	inputJson = readAndVerifyJson("/home/tomek/Pulpit/data.js");
	nodesCount = countNodesFromJson(inputJson);

	/* Sprawdź czy nie ma problemów z podanym formatem danych*/
	if (!areAnyFormatErros(inputJson)) {
		/* Pobierz węzły*/
		nodes = getNodesFromJson(inputJson);

		/* Sprawdź czy węzły zostały prawidłowo ustawione */
		if (!areAnyPostAssignmentErrors(nodes, nodesCount)) {
			setInfinityDistanceForEachNode(nodes, nodesCount);
			startNode = getNode(startNodeId, nodes, nodesCount);
			startNode->distance = 0;
		}

		/* Zwolnij węzły */
		for (i = 0; i < nodesCount; ++i) {
			free(nodes[i].edges);
		}
		free(nodes);
	}
	/* Zwolnij JSON*/
	free(inputJson);
	return 0;
}
