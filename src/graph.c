#include "graph.h"

char * getParameterFromNodeDefinition(char * parameterName,
		char * nodeDefinition) {
	char parameterPattern[20];
	/* Tworzy ciag "\""+parameterName+"\":" */
	strcpy(parameterPattern, QUOTATION_MARK);
	strcat(parameterPattern, parameterName);
	strcat(parameterPattern, QUOTATION_MARK);
	strcat(parameterPattern, COLON);
	return substring(nodeDefinition, parameterPattern,
			COMMA_WITH_QUOTATION_MARK);
}

int getNodeIdFromNodeDefinition(char * nodeDefinition) {
	int id;
	char* tmp = getParameterFromNodeDefinition(ID_PARAM, nodeDefinition);
	id = atoi(tmp);
	free(tmp);
	return id;
}

inline char ** getNodesDefinitionFromJson(char * inputJson) {
	return splitStringBySubstring(NODES_DEFINITIONS_SEPARATOR, inputJson);
}

struct Node * getNodesFromJson(char * inputJson) {
	struct Node * nodes = NULL;
	char** nodesDefinitions;
	int i, j;
	int nodesCount, edgesCount;
	char * rawEndNodes, *rawDistances;
	char ** endNodes, **distances;
	/* Rozdziel kolejne definicje węzłow */
	nodesDefinitions = getNodesDefinitionFromJson(inputJson);

	/* Przelicz definicje węzłów*/
	nodesCount = countSubstringOccurrences(NODES_DEFINITIONS_SEPARATOR,
			inputJson);
	free(nodesDefinitions[nodesCount]); /*TODO: niedoskonałość separatora*/

	/* Inicjalizuj węzły zgodnie z definicjami */
	nodes = malloc(nodesCount * sizeof(struct Node));
	for (i = 0; i < nodesCount; ++i) {
		nodes[i].id = getNodeIdFromNodeDefinition(nodesDefinitions[i]);

		/* TODO: Zweryfikowac czy endNodesCount = distancesCount*/

		/* pobierz surowa liste wezlow koncowych i dystansow*/
		/* np. rawEndNodes = "2,3,4,5" */
		rawEndNodes = getParameterFromNodeDefinition(END_NODES_PARAM,
				nodesDefinitions[i]);
		rawDistances = getParameterFromNodeDefinition(DISTANCES_PARAM,
				nodesDefinitions[i]);
		free(nodesDefinitions[i]);

		/* rozdziel wezly koncowe i dystanse */
		/* np. endNodes = array of {2,3,4,5}*/
		endNodes = splitStringBySubstring(VALUES_SEPARATOR, rawEndNodes);
		distances = splitStringBySubstring(VALUES_SEPARATOR, rawDistances);

		/* przelicz liczbe dystansow i wezłów końcowych */
		edgesCount = countSubstringOccurrences(VALUES_SEPARATOR, rawEndNodes)
				+ 1;
		free(rawDistances);
		free(rawEndNodes);

		/* Przypisz otrzymane wartosci do węzła*/
		nodes[i].edgesCount = edgesCount;
		nodes[i].edges = malloc(edgesCount * sizeof(struct Edge));
		for (j = 0; j < edgesCount; ++j) {
			nodes[i].edges[j].endNode = atoi(endNodes[j]);
			nodes[i].edges[j].distance = atoi(distances[j]);
			free(endNodes[j]);
			free(distances[j]);
		}
		free(endNodes);
		free(distances);
	}
	free(nodesDefinitions);
	return nodes;
}
int countNodesFromJson(char * inputJson) {
	return countSubstringOccurrences(NODES_DEFINITIONS_SEPARATOR, inputJson);
}
