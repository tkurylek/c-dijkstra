/** JSON-reader.h
 *
 */
#ifndef JSON_READER_H_
#define JSON_READER_H_
#include <stdio.h>
#include <stdlib.h>
#include "JSON_checker.h"
/**
 *  Czyta i weryfikuje format pliku JSON. Jezeli format jest
 * poprawny - funkcja zwroci zawartosc pliku, jezeli nie -
 * - zwroci komunikat o bledzie i zakonczy program.
 */
char * readAndVerifyJson(const char * filePath);

#endif /* JSON_READER_H_ */
