/*
 * Prosta struktura grafu
 */
#ifndef GRAPH_H_
#define GRAPH_H_
#include <stdio.h>
#include <stdlib.h>
#include "string-utils.h"

/* stałe */
#define QUOTATION_MARK "\""
#define COLON ":"
#define COMMA_WITH_QUOTATION_MARK ",\""
#define ID_PARAM "id"
#define END_NODES_PARAM "endNodes"
#define DISTANCES_PARAM "distances"
#define VALUES_SEPARATOR ","
#define NODES_DEFINITIONS_SEPARATOR "}"

/**
 * Struktura reprezentująca krawędz każdego węzła
 * 		endNode - id węzła z którym krawędź jest powiązana
 * 		distance - dystans jaki należy przebyć, aby trafić do węzła 'endNode"
 */
struct Edge {
	unsigned int endNode;
	unsigned int distance;
};
/**
 * Struktura reprezentująca węzeł.
 * 		id - identyfikator węzła
 * 		edgesCount - ilość krawędzi wychodzących od węzła
 * 		edges - krawędzie wychodzące od węzła
 */
struct Node {
	unsigned int id;
	unsigned int edgesCount;
	struct Edge * edges;
};
/**
 * Zwraca wartość parametru 'parameterName' na podstawie informacji
 * zawartych w definicji węzła 'nodeDefinition'.
 */
char * getParameterFromNodeDefinition(char * parameterName,
		char * nodeDefinition);
/**
 * Zwraca id węzła na podstawie informacji
 * zawartych w definicji węzła 'nodeDefinition
 */
int getNodeIdFromNodeDefinition(char * nodeDefinition);
/**
 * Zwraca tablicę węzłów na podstawie danych 'inputJson' w formacie JSON.
 */
struct Node * getNodesFromJson(char * inputJson);
/**
 * Zwraca definicje wszystkich węzłów przechowywanych w 'inputJson'.
 */
inline char ** getNodesDefinitionFromJson(char * inputJson);
/**
 * Zwraca ilość węzłów jakie można odczytać z 'inputJson'.
 */
int countNodesFromJson(char * inputJson);

#endif /* GRAPH_H_ */
