/**
 * Wyszukiwanie najkrótszej ścieżki w grafie za pomocą
 * algorytmu Dijkstry.
 *
 * Tomasz Kuryłek
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string-utils.h"
#include "JSON-reader.h"
#include "graph.h"
#include "dijkstra-utils.h"
#include "arguments-utils.h"

void freeNodes(struct Node * nodes, int nodesCount) {
	int i;
	/* Zwolnij węzły */
	for (i = 0; i < nodesCount; ++i) {
		free(nodes[i].edges);
	}
	free(nodes);
}

int main(int argc, char **argv) {
	struct Node * nodes = NULL;
	struct NodeArrayList * unvisitedNodes;
	struct Node startNode, endNode, evaluationNode;
	int nodesCount, i = 0, *trail;
	unsigned int totalDistanceToEndNode;
	char * inputJson;
	int startNodeId = 1, endNodeId = 3;

	if (areAnyUndefinedArguments(argc, argv)) {
		puts("Nie podano poprawnych parametrów. Zapoznaj się z pomocą:");
		printHelp();
		return 1;
	}

	/* Zweryfikuj i pobierz JSON*/
	inputJson = readAndVerifyJson(getInputJson(argc, argv));

	/* Pobierz ilość węzłów */
	nodesCount = countNodesFromJson(inputJson);

	/* Sprawdź czy nie ma problemów z podanym formatem danych*/
	if (!areAnyFormatErros(inputJson)) {
		/* Pobierz węzły */
		nodes = getNodesFromJson(inputJson);

		/* sprawdz czy startNode istnieje w pliku wejsciowym */
		startNodeId = getStartNode(argc, argv);
		if (!containsNode(startNodeId, nodes, nodesCount)) {
			fprintf(stderr, "Podany węzeł początkowy [%i] nie jest zadeklarowany w pliku wejściowym\n", startNodeId);
			freeNodes(nodes, nodesCount);
			free(inputJson);
			exit(1);
		}

		/* sprawdz czy endNode istnieje w pliku wejsciowym */
		endNodeId = getEndNode(argc, argv);
		if (!containsNode(endNodeId, nodes, nodesCount)) {
			fprintf(stderr, "Podany węzeł końcowy [%i] nie jest zadeklarowany w pliku wejściowym\n", endNodeId);
			freeNodes(nodes, nodesCount);
			free(inputJson);
			exit(1);
		}

		/* Sprawdź czy węzły zostały prawidłowo ustawione */
		if (!areAnyPostAssignmentErrors(nodes, nodesCount)) {
			/* inicjuj ślad, w którym będziemy zapisywać najkrótszą ścieżkę*/
			trail = malloc((nodesCount + 1) * sizeof(int));
			/* ustaw nieskończony dystans dla wszystkich węzłów ...*/
			setInfinityDistanceForEachNode(nodes, nodesCount);
			startNode = getNode(startNodeId, nodes, nodesCount);
			/* ... oprócz początkowego*/
			startNode.distance = 0;
			/* lista zawierająca węzły do analizy */
			unvisitedNodes = newArrayList();

			/* dodaj węzeł początkowy do analizy - od niego zaczniemy*/
			unvisitedNodes = appendNodeArrayList(startNode, unvisitedNodes);

			while (unvisitedNodes->length > 0) {
				evaluationNode = findElementWithTheLowestDistanceInNodeArrayList(unvisitedNodes);
				/* sprawdź czy to już koniec grafu */
				if (evaluationNode.id == endNodeId) {
					/* drukuj scieżkę i całkowity dystans*/
					printTrail(startNodeId, endNodeId, trail);
					printf("Dystans potrzebny na przebycie grafu: %i\n", evaluationNode.distance);
					break;
				}
				unvisitedNodes = removeElementFromNodeArrayList(evaluationNode, unvisitedNodes);
				/* analizuj krawędzie węzła*/
				for (i = 0; i < evaluationNode.edgesCount; ++i) {
					totalDistanceToEndNode = evaluationNode.distance + evaluationNode.edges[i].distance;

					/* Pobierz węzeł końcowy z unvisited lub glownej listy */
					if (containsNode(evaluationNode.edges[i].endNode, unvisitedNodes->array, unvisitedNodes->length)) {
						endNode = getNode(evaluationNode.edges[i].endNode, unvisitedNodes->array, unvisitedNodes->length);
					} else {
						endNode = getNode(evaluationNode.edges[i].endNode, nodes, nodesCount); /* pobierz z głównej listy*/
					}
					if (endNode.distance > totalDistanceToEndNode) {
						endNode.distance = totalDistanceToEndNode;
						trail[endNode.id] = evaluationNode.id; /* zapisz ślad*/
						unvisitedNodes = appendNodeArrayList(endNode, unvisitedNodes);
					}
				}
			}

			/* Zwolnij arary-listę */
			free(unvisitedNodes->array);
			free(unvisitedNodes);
			/* Zwolnij ślad */
			free(trail);
		}
		/* Zwolnij węzły */
		freeNodes(nodes, nodesCount);
	}
	/* Zwolnij JSON wejściowy*/
	free(inputJson);
	return 0;
}
