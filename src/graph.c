#include "graph.h"

char * getParameterFromNodeDefinition(char * parameterName, char * nodeDefinition) {
	char parameterPattern[20];
	/* Tworzy ciag "\""+parameterName+"\":" */
	strcpy(parameterPattern, QUOTATION_MARK);
	strcat(parameterPattern, parameterName);
	strcat(parameterPattern, QUOTATION_MARK);
	strcat(parameterPattern, COLON);
	return substring(nodeDefinition, parameterPattern, COMMA_WITH_QUOTATION_MARK);
}

int getNodeIdFromNodeDefinition(char * nodeDefinition) {
	int id;
	char* tmp = getParameterFromNodeDefinition(ID_PARAM, nodeDefinition);
	id = atoi(tmp);
	if (id == 0) {
		fprintf(stderr, "Błąd: Nie podano 'id' dla jednego z węzłów.\n");
		exit(1);
	}
	free(tmp);
	return id;
}

inline char ** getNodesDefinitionFromJson(char * inputJson) {
	return splitStringBySubstring(NODES_DEFINITIONS_SEPARATOR, inputJson);
}

inline int getLowerValueOf(int valueA, int valueB) {
	if (valueA < valueB) {
		return valueA;
	} else if (valueA > valueB) {
	}
	return valueB;
}

inline int getHigherValueOf(int valueA, int valueB) {
	if (valueA > valueB) {
		return valueA;
	} else if (valueA < valueB) {
	}
	return valueB;
}

void preventSelfEndNodeAssignment(int endNode, int rootNodeId) {
	if (endNode == rootNodeId) {
		fprintf(stderr, "Błąd: Węzeł [%i] połączony z samym sobą!\n", rootNodeId);
		exit(1);
	}
}

void preventNegativeDistance(int distance, int rootNodeId) {
	if (distance <= 0) {
		fprintf(stderr, "Błąd: Węzeł [%i] posiada błędny dystans [%i]!\n", rootNodeId, distance);
		exit(1);
	}
}

void preventNonExistingEndNodeAssignment(struct Node *nodes, int nodesCount) {
	int i, x;
	unsigned int j;
	int foundEndNodes = 0;
	int declaredEndNodes = 0;
	for (i = 0; i < nodesCount; ++i) {
		for (j = 0; j < nodes[i].edgesCount; ++j) {
			for (x = 0; x < nodesCount; ++x) {
				if (nodes[i].edges[j].endNode == nodes[x].id) {
					foundEndNodes++;
					break;
				}
			}
			declaredEndNodes++;
		}
	}
	if (foundEndNodes != declaredEndNodes) {
		fprintf(stderr,
				"Błąd: Błędne definicje węzłów końcowych. Znaleziono zaledwie %i węzłów z deklarowanych %i.\n",
				foundEndNodes, declaredEndNodes);
		exit(1);
	}
}

struct Node * getNodesFromJson(char * inputJson) {
	struct Node * nodes = NULL;
	char** nodesDefinitions;
	int i, j;
	int nodesCount, edgesCount, distancesCount, endNodesCount;
	char * rawEndNodes, *rawDistances;
	char ** endNodes, **distances;
	/* Rozdziel kolejne definicje węzłow */
	nodesDefinitions = getNodesDefinitionFromJson(inputJson);

	/* Przelicz definicje węzłów*/
	nodesCount = countSubstringOccurrences(NODES_DEFINITIONS_SEPARATOR, inputJson);
	free(nodesDefinitions[nodesCount]); /*TODO: niedoskonałość separatora*/

	/* Inicjalizuj węzły zgodnie z definicjami */
	nodes = malloc(nodesCount * sizeof(struct Node));
	for (i = 0; i < nodesCount; ++i) {
		nodes[i].id = getNodeIdFromNodeDefinition(nodesDefinitions[i]);

		/* pobierz surowa liste wezlow koncowych i dystansow*/
		/* np. rawEndNodes = "2,3,4,5" */
		if (!contains(END_NODES_PARAM, nodesDefinitions[i])) {
			fprintf(stderr, "Błąd: Węzeł zawieszony w powietrzu!\n");
			fprintf(stderr, "\tBrak węzłów końcowych dla węzła o id [%i]\n", nodes[i].id);
			exit(1);
		}
		rawEndNodes = getParameterFromNodeDefinition(END_NODES_PARAM, nodesDefinitions[i]);
		if (!contains(DISTANCES_PARAM, nodesDefinitions[i])) {
			fprintf(stderr, "Błąd: Węzeł zawieszony w powietrzu!\n");
			fprintf(stderr, "\tBrak dystansów między węzłem o id [%i]\n", nodes[i].id);
			exit(1);
		}
		rawDistances = getParameterFromNodeDefinition(DISTANCES_PARAM, nodesDefinitions[i]);
		free(nodesDefinitions[i]);

		/* rozdziel wezly koncowe i dystanse */
		/* np. endNodes = array of {2,3,4,5}*/
		endNodes = splitStringBySubstring(VALUES_SEPARATOR, rawEndNodes);
		distances = splitStringBySubstring(VALUES_SEPARATOR, rawDistances);

		/* przelicz liczbe dystansow i wezłów końcowych */
		endNodesCount = countSubstringOccurrences(VALUES_SEPARATOR, rawEndNodes) + 1;
		distancesCount = countSubstringOccurrences(VALUES_SEPARATOR, rawDistances) + 1;
		free(rawDistances);
		free(rawEndNodes);

		edgesCount = getLowerValueOf(endNodesCount, distancesCount);
		/* Sprawdz czy ilosci zadeklarowanych dystansow i wezlow koncowych sie zgadzaja*/
		if (endNodesCount != distancesCount) {
			printf("Ostrzeżenie: Podano różna ilość definicji węzłów końcowych");
			printf(" [%i] i dystansów [%i]\n", endNodesCount, distancesCount);
			printf("\tW węźle o id [%i]. Za ilość węzłów przyjęta zostanie wartość [%i].\n",
					nodes[i].id, edgesCount);
			printf("\tCzęść danych wejściowych zostanie pominięta!\n");
			/* Zwolnij pamięć pominiętych danych */
			for (j = edgesCount; j < distancesCount; ++j) {
				puts("\t\tPomijam dystans bez zadeklarowanego węzła końcowego!");
				free(distances[j]);
			}
			for (j = edgesCount; j < endNodesCount; ++j) {
				puts("\t\tPomijam wezęł końcowy bez zadekarowanego dystansu!");
				free(endNodes[j]);
			}
		}

		/* Przypisz otrzymane wartosci do węzła*/
		nodes[i].edgesCount = edgesCount;
		nodes[i].edges = malloc(edgesCount * sizeof(struct Edge));
		for (j = 0; j < edgesCount; ++j) {
			nodes[i].edges[j].endNode = atoi(endNodes[j]);
			nodes[i].edges[j].distance = atoi(distances[j]);
			preventSelfEndNodeAssignment(nodes[i].edges[j].endNode, nodes[i].id);
			preventNegativeDistance(nodes[i].edges[j].distance, nodes[i].id);
			free(endNodes[j]);
			free(distances[j]);
		}

		free(endNodes);
		free(distances);
	}
	/* Sprawdź czy wszyskie węzły końcowe wskazują na istnejące węzły*/
	preventNonExistingEndNodeAssignment(nodes, nodesCount);
	free(nodesDefinitions);
	return nodes;
}
int countNodesFromJson(char * inputJson) {
	return countSubstringOccurrences(NODES_DEFINITIONS_SEPARATOR, inputJson);
}
