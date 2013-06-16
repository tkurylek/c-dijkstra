#include "graph.h"

char * getParameterFromNodeDefinition(char * parameterName,
		char * nodeDefinition) {
	char parameterPattern[20];
	/* Tworzy ciag "\""+parameterName+"\":" */
	strcpy(parameterPattern, "\"");
	strcat(parameterPattern, parameterName);
	strcat(parameterPattern, "\":");
	return substring(nodeDefinition, parameterPattern, ",\"");
}

int getNodeIdFromNodeDefinition(char * nodeDefinition) {
	int id;
	char* tmp = getParameterFromNodeDefinition("id", nodeDefinition);
	id = atoi(tmp);
	free(tmp);
	return id;
}

inline char ** getNodesDefinitionFromJson(char * inputJson) {
	return splitStringBySubstring("}", inputJson);
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
	nodesCount = countSubstringOccurrences("}", inputJson);
	free(nodesDefinitions[nodesCount]); /*TODO: niedoskonałość separatora*/

	/* Inicjalizuj węzły zgodnie z definicjami */
	nodes = malloc(nodesCount * sizeof(struct Node));
	for (i = 0; i < nodesCount; ++i) {
		nodes[i].id = getNodeIdFromNodeDefinition(nodesDefinitions[i]);
		/* TODO: Zweryfikowac czy endNodesCount = distancesCount*/
		/* pobierz surowa liste wezlow koncowych i dystansow*/
		/* np. rawEndNodes = 2,3,4,5 */
		rawEndNodes = getParameterFromNodeDefinition("endNodes",
				nodesDefinitions[i]);
		rawDistances = getParameterFromNodeDefinition("distances",
				nodesDefinitions[i]);
		free(nodesDefinitions[i]);

		/* rozdziel wezly koncowe i dystanse */
		/* np. endNodes = array of {2,3,4,5}*/
		endNodes = splitStringBySubstring(",", rawEndNodes);
		distances = splitStringBySubstring(",", rawDistances);

		/* przelicz liczbe dystansow i wezłów końcowych */
		edgesCount = countSubstringOccurrences(",", rawEndNodes) + 1;
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
	return countSubstringOccurrences("}", inputJson);
}
