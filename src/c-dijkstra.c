/** valgrind -v --num-callers=20 --leak-check=yes  --track-origins=yes --leak-resolution=high --show-reachable=yes ./c-dijkstra
HEAP SUMMARY:
     in use at exit: 0 bytes in 0 blocks
   total heap usage: 54 allocs, 54 frees, 1,957 bytes allocated
 All heap blocks were freed -- no leaks are possible
 ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
 used_suppression:      2 dl-hack3-cond-1
 ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string-utils.h"
#include "JSON-reader.h"
#include "graph.h"

int main(int argc, char **argv) {
	struct Node * nodes = NULL;
	int nodesCount, i;
	char * inputJson;

	/* Zweryfikuj i pobierz JSON*/
	inputJson = readAndVerifyJson("/home/tomek/Pulpit/data.js");
	nodesCount = countNodesFromJson(inputJson);
	nodes = getNodesFromJson(inputJson);
	for (i = 0; i < nodesCount; ++i) {
		free(nodes[i].edges);
	}
	free(nodes);
	free(inputJson);
	return 0;
}
