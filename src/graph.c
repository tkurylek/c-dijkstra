#include "graph.h"
/*public*/inline int countNodesFromJson(char * inputJson) {
	return countSubstringOccurrences(NODES_DEFINITIONS_SEPARATOR, inputJson);
}
/*public*/int containsNode(unsigned int nodeId, struct Node * nodes, int nodesCount) {
	int i;
	for (i = 0; i < nodesCount; ++i) {
		if (nodes[i].id == nodeId) {
			return 1;
		}
	}
	return 0;
}
/*public*/struct Node getNode(unsigned int nodeId, struct Node * nodes, int nodesCount) {
	int i;
	assert(containsNode(nodeId, nodes, nodesCount));
	for (i = 0; i < nodesCount; ++i) {
		if (nodes[i].id == nodeId) {
			return nodes[i];
		}
	}
	/*Teoretycznie nigdy nie powinien tutaj dotrzeć*/
	exit(INDETERMINABLE_NODE);
}
/*public*/struct NodeArrayList * newArrayList() {
	struct NodeArrayList * newArrayList;
	newArrayList = malloc(sizeof(struct NodeArrayList));
	newArrayList->length = 0;
	newArrayList->array = malloc(sizeof(struct Node));
	return newArrayList;
}

/*public*/struct NodeArrayList * appendNodeArrayList(struct Node nodeToBeAppended, struct NodeArrayList * arrayList) {
	int i;
	/* przydziel pamięć strukturze ArrayList*/
	struct NodeArrayList * newArrayList = malloc(sizeof(struct NodeArrayList));
	/* przydziel pamięć tablicy w ArrayList o jeden element większej niż poprzedniczka*/
	newArrayList->array = malloc((arrayList->length + 1) * sizeof(struct Node));
	/* Kopiuj wartosci */
	for (i = 0; i < arrayList->length; ++i) {
		newArrayList->array[i] = arrayList->array[i];
	}
	/* ustaw długość tablicy */
	newArrayList->length = arrayList->length + 1;
	/* dodaj na koniec węzeł*/
	newArrayList->array[newArrayList->length - 1] = nodeToBeAppended;
	/* Zwolnij starą array-listę */
	free(arrayList->array);
	free(arrayList);
	return newArrayList;
}

/*public*/struct NodeArrayList * removeElementFromNodeArrayList(struct Node node, struct NodeArrayList * arrayList) {
	int i, j = 0; /* Analogicznie do 'appendNodeArrayList', komentarze zbędne*/
	struct NodeArrayList * newArrayList = malloc(sizeof(struct NodeArrayList));
	newArrayList->array = malloc((arrayList->length - 1) * sizeof(struct Node));
	for (i = 0; i < arrayList->length; ++i) {
		if (node.id != arrayList->array[i].id) { /*... ale bez usuwanego elementu*/
			newArrayList->array[j++] = arrayList->array[i];
		}
	}
	newArrayList->length = arrayList->length - 1;
	free(arrayList->array);
	free(arrayList);
	return newArrayList;
}

/*public*/char * getParameterFromNodeDefinition(char * parameterName, char * nodeDefinition) {
	char parameterPattern[20];
	strcpy(parameterPattern, QUOTATION_MARK);
	strcat(parameterPattern, parameterName);
	strcat(parameterPattern, QUOTATION_MARK);
	strcat(parameterPattern, COLON);
	return substring(nodeDefinition, parameterPattern, COMMA_WITH_QUOTATION_MARK);
}

/*public*/int getNodeIdFromNodeDefinition(char * nodeDefinition) {
	int id;
	char* tmp = getParameterFromNodeDefinition(ID_PARAM, nodeDefinition);
	id = atoi(tmp);
	free(tmp);
	return id;
}

/*public*/inline char ** getNodesDefinitionFromJson(char * inputJson) {
	return splitStringBySubstring(NODES_DEFINITIONS_SEPARATOR, inputJson);
}

/*Zwraca mniejsza wartość z dwóch podanych*/
inline int getLowerValueOf(int valueA, int valueB) {
	if (valueA < valueB) {
		return valueA;
	} else if (valueA > valueB) {
	}
	return valueB;
}
/*Zwraca większą wartość z dwóch podanych*/
inline int getHigherValueOf(int valueA, int valueB) {
	if (valueA > valueB) {
		return valueA;
	} else if (valueA < valueB) {
	}
	return valueB;
}

int areAnySelfEndNodeAssignment(int endNode, int rootNodeId) {
	if (endNode == rootNodeId) {
		fprintf(stderr, "Błąd: Węzeł [%i] połączony z samym sobą!\n", rootNodeId);
		return SELF_END_NODE_ASSIGNMENT_ERROR;
	}
	return OK;
}

int areAnyNegativeDistance(int distance, int rootNodeId) {
	if (distance < 0) {
		fprintf(stderr, "Błąd: Węzeł [%i] posiada błędny dystans [%i]!\n", rootNodeId, distance);
		return NEGATIVE_DISTANCE;
	}
	return OK;
}
int areAnyNonExistingEndNodeAssignment(unsigned int endNode, struct Node *nodes, int nodesCount) {
	int foundEndNode = 0, i;
	for (i = 0; i < nodesCount; ++i) {
		if (endNode == nodes[i].id) {
			foundEndNode = 1;
			break;
		}
	}
	if (!foundEndNode) {
		fprintf(stderr, "Błąd: Nie odnaleziono wszystkich węzłów końcowych. Brak definicji węzła [%i]\n", endNode);
		return END_NODE_UNDETERMINED;
	}
	return OK;
}

/*public*/int areAnyPostAssignmentErrors(struct Node *nodes, int nodesCount) {
	int i, errorCode = 0;
	unsigned int j;
	for (i = 0; i < nodesCount; ++i) {
		for (j = 0; j < nodes[i].edgesCount; ++j) {
			if (errorCode = errorCode /* operator przypisania _celowo_ w warunku */
			|| areAnySelfEndNodeAssignment(nodes[i].edges[j].endNode, nodes[i].id)
					|| areAnyNegativeDistance(nodes[i].edges[j].distance, nodes[i].id)
					|| areAnyNonExistingEndNodeAssignment(nodes[i].edges[j].endNode, nodes, nodesCount))
				return errorCode;
		}
	}
	return OK;
}

/*public*/int areAnyFormatErros(char * inputJson) {
	int i;
	struct Node * nodes = NULL;
	char** nodesDefinitions;
	int nodesCount;
	int resultCode = OK; /* Zakladamy, że nie było błedu*/
	nodesDefinitions = getNodesDefinitionFromJson(inputJson);
	nodesCount = countSubstringOccurrences(NODES_DEFINITIONS_SEPARATOR, inputJson);
	free(nodesDefinitions[nodesCount]); /* wynika z niedoskonałości speratora*/
	nodes = malloc(nodesCount * sizeof(struct Node));
	for (i = 0; i < nodesCount; ++i) {
		if (getNodeIdFromNodeDefinition(nodesDefinitions[i]) == 0) {
			fprintf(stderr, "Błąd: Nie podano 'id' dla jednego z węzłów.\n");
			fprintf(stderr, "\tWęzeł ten został zdefiniowany jako [%i] z kolei.\n", (i + 1));
			resultCode = INDETERMINABLE_NODE;
		}
		if (!contains(END_NODES_PARAM, nodesDefinitions[i])) {
			fprintf(stderr, "Błąd: Węzeł zawieszony w powietrzu!\n");
			fprintf(stderr, "\tBrak węzłów końcowych dla węzła zdefiniowanego jako [%i] z kolei.\n", (i + 1));
			resultCode = FLOATING_NODE;
		}
		if (!contains(END_NODES_PARAM, nodesDefinitions[i])) {
			fprintf(stderr, "Błąd: Węzeł zawieszony w powietrzu!\n");
			fprintf(stderr, "\tBrak dystansów między węzłem zdefiniowanym jako [%i] z kolei.\n", (i + 1));
			resultCode = FLOATING_NODE;
		}
		free(nodesDefinitions[i]);
	}
	free(nodesDefinitions);
	free(nodes);
	return resultCode;
}

/*public*/struct Node * getNodesFromJson(char * inputJson) {
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
	free(nodesDefinitions[nodesCount]); /*TODO: znaleźć lepszy separator*/

	/* Inicjalizuj węzły zgodnie z definicjami */
	nodes = malloc(nodesCount * sizeof(struct Node));
	for (i = 0; i < nodesCount; ++i) {
		nodes[i].id = getNodeIdFromNodeDefinition(nodesDefinitions[i]);

		/* pobierz surowa liste wezlow koncowych i dystansow. Jak ona wygląda? ano */
		/* np. rawEndNodes = "2,3,4,5" */
		rawEndNodes = getParameterFromNodeDefinition(END_NODES_PARAM, nodesDefinitions[i]);
		rawDistances = getParameterFromNodeDefinition(DISTANCES_PARAM, nodesDefinitions[i]);
		free(nodesDefinitions[i]);

		/* rozdziel wezly koncowe i dystanse. Co z tego będzie? ano  */
		/* np. endNodes = array of {2,3,4,5}*/
		endNodes = splitStringBySubstring(VALUES_SEPARATOR, rawEndNodes);
		distances = splitStringBySubstring(VALUES_SEPARATOR, rawDistances);

		/* przelicz liczbe dystansow i wezłów końcowych */
		endNodesCount = countSubstringOccurrences(VALUES_SEPARATOR, rawEndNodes) + 1;
		distancesCount = countSubstringOccurrences(VALUES_SEPARATOR, rawDistances) + 1;
		free(rawDistances);
		free(rawEndNodes);

		/* Sprawdz czy ilosci zadeklarowanych dystansow i wezlow koncowych sie zgadzaja*/
		/* Jeżeli nie - spróbuj wykorzystać chociaż poprawne deklaracje */
		edgesCount = getLowerValueOf(endNodesCount, distancesCount);
		if (endNodesCount != distancesCount) {
			printf("Ostrzeżenie: Podano różną ilość definicji węzłów końcowych");
			printf(" [%i] i dystansów [%i]\n", endNodesCount, distancesCount);
			printf("\tw węźle o id [%i]. Za ilość węzłów przyjęta zostanie wartość [%i].\n", nodes[i].id, edgesCount);
			printf("\tCzęść danych wejściowych zostanie pominięta:\n");
			/* Zwolnij pamięć pominiętych danych */
			for (j = edgesCount; j < distancesCount; ++j) {
				puts("\t\tPomijam dystans bez zadeklarowanego węzła końcowego...");
				free(distances[j]);
			}
			for (j = edgesCount; j < endNodesCount; ++j) {
				puts("\t\tPomijam wezęł końcowy bez zadekarowanego dystansu...");
				free(endNodes[j]);
			}
		}

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
