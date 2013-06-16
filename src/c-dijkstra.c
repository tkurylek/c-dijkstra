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

int main(int argc, char **argv) {
	struct Node * nodes = NULL;
	struct Node startNode;
	struct NodeArrayList * unvisitedNodes;
	struct Node evaluationNode;
	struct Node endNode;
	int nodesCount, i = 0, j, totalDistanceToEndNode, *trail, appended;
	char * inputJson;
	int startNodeId = 1, endNodeId = 3;
	/* Zweryfikuj i pobierz JSON*/
	inputJson = readAndVerifyJson("/home/tomek/Pulpit/data.js");

	/* Pobierz ilość węzłów */
	nodesCount = countNodesFromJson(inputJson);

	/* Sprawdź czy nie ma problemów z podanym formatem danych*/
	if (!areAnyFormatErros(inputJson)) {
		/* Pobierz węzły */
		nodes = getNodesFromJson(inputJson);

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
			do {
				appended = 0; /*załóż, że lista się nie rozszerzy - dalsza analiza nie będzie konieczna */
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
				for (j = 0; j < evaluationNode.edgesCount; ++j) {
					totalDistanceToEndNode = evaluationNode.distance + evaluationNode.edges[j].distance;
					endNode = getNode(evaluationNode.edges[j].endNode, nodes, nodesCount);
					if (endNode.distance > totalDistanceToEndNode) {
						endNode.distance = totalDistanceToEndNode;
						trail[endNode.id] = evaluationNode.id; /* zapisz ślad*/
						unvisitedNodes = appendNodeArrayList(endNode, unvisitedNodes);
						appended = 1; /*lista została rozszerzona, konieczna będzie kolejna analiza*/
					}
				}
			} while (appended);
			/* Zwolnij arary-listę */
			free(unvisitedNodes->array);
			free(unvisitedNodes);
		}
		/* Zwolnij ślad */
		free(trail);
		/* Zwolnij węzły */
		for (i = 0; i < nodesCount; ++i) {
			free(nodes[i].edges);
		}
		free(nodes);
	}
	/* Zwolnij JSON wejściowy*/
	free(inputJson);
	return 0;
}
