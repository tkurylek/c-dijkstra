#ifndef DIJKSTRA_UTILS_H_
#define DIJKSTRA_UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
/*
 * Ustawia nieskończenie duży dystans dla każdego węzła
 */
void setInfinityDistanceForEachNode(struct Node * nodes, int nodesCount);
/*
 * Znajduje i zwraca element z najmniejszym dystansem w liście
 */
struct Node findElementWithTheLowestDistanceInNodeArrayList(struct NodeArrayList * arrayList);
/*
 * Wypisuje w ładnym formacie ślad - najkrótsza scieżka w grafie
 */
void printTrail(int startNodeId, int endNodeId, int * trail);

#endif /* DIJKSTRA_UTILS_H_ */
