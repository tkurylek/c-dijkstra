#include "dijkstra-utils.h"

/*public*/void setInfinityDistanceForEachNode(struct Node * nodes, int nodesCount) {
	int i;
	for (i = 0; i < nodesCount; ++i) {
		nodes[i].distance = INFITITY;
	}
}
/*public*/struct Node findElementWithTheLowestDistanceInNodeArrayList(struct NodeArrayList * arrayList) {
	int i, targetIndex = 0;
	unsigned int lowestDistanceSoFar = -1;
	for (i = 0; i < arrayList->length; ++i) {
		if (lowestDistanceSoFar > arrayList->array[i].distance) {
			lowestDistanceSoFar = arrayList->array[i].distance;
			targetIndex = i;
		}
	}
	return arrayList->array[targetIndex];
}
/*public*/void printTrail(int startNodeId, int endNodeId, int * trail) {
	int i;
	i = endNodeId;
	puts("Najkrótsza scieżka:");
	printf("(%i)", i);
	while (i != startNodeId) {
		printf("<--(%i)", trail[i]);
		i = trail[i];
	}
	puts("");
}
