#include "arguments-utils.h"

/*public*/int hasNotExpectedArgumentsNumber(int argc) {
	return argc - 1 != EXPECTED_ARGUMENT_COUNT;
}

int hasNotStartNode(int argc, char ** argv) {
	int i;
	for (i = 1; i < argc; ++i) {
		if (strcmp(argv[i], START_NODE_FLAG) == 0) {
			return FALSE;
		}
	}
	fprintf(stderr, "Brak zdefiniowanego parametru początkowego węzła.\n");
	return TRUE;
}
int hasNotEndNode(int argc, char ** argv) {
	int i;
	for (i = 1; i < argc; ++i) {
		if (strcmp(argv[i], END_NODE_FLAG) == 0) {
			return FALSE;
		}
	}
	fprintf(stderr, "Brak zdefiniowanego parametru końcowego węzła.\n");
	return TRUE;
}
int hasNotInputJson(int argc, char ** argv) {
	int i;
	for (i = 1; i < argc; ++i) {
		if (strcmp(argv[i], INPUT_JSON_FLAG) == 0) {
			return FALSE;
		}
	}
	fprintf(stderr, "Brak zdefiniowanego parametru pliku źródłowego w formacie JSON.\n");
	return TRUE;
}
/*public*/int areAnyUndefinedArguments(int argc, char ** argv) {
	return hasNotExpectedArgumentsNumber(argc) || hasNotStartNode(argc, argv) || hasNotEndNode(argc, argv)
			|| hasNotInputJson(argc, argv);
}

/*public*/void printHelp() {
	puts("Po nazwie programu proszę podać wartości następujących argumentów:");
	puts("\t -s id węzła początkowego");
	puts("\t -k id węzła końcowego");
	puts("\t -i ścieżka do pliku źródłowego w formacie JSON");
	puts("np. ./c-dijkstra -s 1 -k 4 -i /home/user/myGraph.js\n");
}

/*public*/char * getValueForFlag(char * flag, int argc, char **argv) {
	int i;
	for (i = 1; i < argc - 1; ++i) {
		if (countSubstringOccurrences(flag, argv[i]) == 1) {
			return argv[i + 1];
		}
	}
	return "\0";
}
