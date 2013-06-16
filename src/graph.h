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
#define INFITITY 2147483647;

enum ExitCode {
	OK = 0 /* Poprawne zakonczenie funkcji */
	,SELF_END_NODE_ASSIGNMENT_ERROR /* zwracany podczas przypisania węzła do samego siebie */
	,NEGATIVE_DISTANCE /* zwracany podczas ustawienia ujemnegu dystansu między węzłami*/
	,END_NODE_UNDETERMINED /* zwracany, gdy nie można odnaleźć węzła końcowego*/
	,FLOATING_NODE /*zwracany, gdy węzeł nie posiada połączeń z innymi*/
	,INDETERMINABLE_NODE /*zracany, gdy węzeł nie posiada indentyfikatora*/
};

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
 * 		distance - dystans węzła
 * 		edges - krawędzie wychodzące od węzła
 */
struct Node {
	unsigned int id;
	unsigned int distance;
	unsigned int edgesCount;
	struct Edge * edges;
};
/**
 * Lista oparta na tablicy z dynamiczną zmianą rozmiaru
 * zamiast nudnej już listy LinkedList.
 */
struct NodeArrayList {
	struct Node * array;
	int length;
};
/*
 * Tworzy nową _dynamiczną_ listę i zwraca ją.
 */
struct NodeArrayList * newArrayList();
/*
 * Usuwa podany element z listy i zwraca ją.
 */
struct NodeArrayList * removeElementFromNodeArrayList(struct Node node,
		struct NodeArrayList * arrayList);
/*
 * Rozszerza listę o podany element i zwraca ją.
 */
struct NodeArrayList * appendNodeArrayList(struct Node node, struct NodeArrayList * arrayList);
/**
 *	Wyszukuje i zwraca węzeł o podanym id z podanej tablicy.
 */
struct Node getNode(unsigned int nodeId, struct Node * nodes, int nodesCount);
/**
 * Weryfikuje, czy podane źródło 'inputJson' jest poprawnym źródłem
 * definicji węzłów. Zwracany jest kod błędu różny od zera w przypadku
 * niepowodzenia, lub 0 jeżeli weryfikacja przebiegła pomyślne.
 *
 * Zobacz: enum ExitCode
 */
int areAnyFormatErros(char * inputJson);
/**
 * Weryfikuje węzły pod względem poprawności danych. Zwracany jest
 * kod błędu różny od zera w przypadku niepowodzenia, lub 0 jeżeli
 * weryfikacja przebiegła pomyślne.
 *
 * Zobacz: enum ExitCode
 */
int areAnyPostAssignmentErrors(struct Node *nodes, int nodesCount);
/**
 * Zwraca definicje wszystkich węzłów przechowywanych w 'inputJson'
 * Definicja węzła to ciąg znaków zawierający wszystkie informacje
 * o węźle.
 */
inline char ** getNodesDefinitionFromJson(char * inputJson);
/**
 * Zwraca id węzła na podstawie informacji
 * zawartych w definicji węzła 'nodeDefinition
 */
int getNodeIdFromNodeDefinition(char * nodeDefinition);
/**
 * Zwraca wartość parametru 'parameterName' na podstawie informacji
 * zawartych w definicji węzła 'nodeDefinition'.
 */
char * getParameterFromNodeDefinition(char * parameterName, char * nodeDefinition);
/**
 * Zwraca tablicę węzłów na podstawie danych 'inputJson' w formacie JSON.
 * UWAGA: Nie sprawdza błędów! Zobacz: 'areAnyFormatErros' i
 * 'areAnyPostAssignmentErrors', aby uniknąć nieprzyjemności.
 */
struct Node * getNodesFromJson(char * inputJson);
/**
 * Zwraca ilość węzłów jakie można odczytać z 'inputJson'.
 *
 */
int countNodesFromJson(char * inputJson);

#endif /* GRAPH_H_ */
