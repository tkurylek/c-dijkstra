#ifndef ARGUMENTS_UTILS_H_
#define ARGUMENTS_UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define EXPECTED_ARGUMENT_COUNT 6
#define START_NODE_FLAG "-s"
#define END_NODE_FLAG "-k"
#define INPUT_JSON_FLAG "-i"

enum ExitCodes {
	TRUE = 1, FALSE = 0
};
/*
 *  Sprawdza czy ilosc argumentów się zgadza
 */
int hasNotExpectedArgumentsNumber(int argc);
/*
 *  Sprawdza czy nie ma niezdefiniowanych argumentów
 */
int areAnyUndefinedArguments(int argc, char ** argv);
/*
 * Wypisuje tekst z pomocą
 */
void printHelp();
/*
 * Zwraca wartość przypisaną do danej flagi, lub pusty ciąg
 * jeżeli nie znaleziono flagi
 */
char * getValueForFlag(char * flag, int argc, char **argv);

#endif /* ARGUMENTS_UTILS_H_ */
