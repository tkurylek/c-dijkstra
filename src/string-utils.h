/** string-utils.h
 * Wszystko to czego brakowalo mi w C podczas operacji na ciagach.
 */
#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Sprawdza czy 'suspect' znajduje sie w 'string'. Podobnie jak
 * strstr, ale o wiele czytelniej.
 *
 * Zwraca:
 * 		1 - jezeli ciag zawiera podciag
 * 		0 - jezeli ciag nie zawiera podciagu
 */
inline int contains(char * suspect, char * string);
/**
 * Zwraca koncowa pozycje podciagu 'suspect' w ciagu 'string' lub
 * -1 jezeli 'suspect' nie znajduje sie w 'string'.
 *
 * Przyklad:
 * 		endingIndexOf("id", "my id is 21") zwraca 5
 */
int endingIndexOf(char * suspect, char * string);
/**
 * Zwraca pozycje podciagu 'suspect' w ciagu 'string' lub -1
 * jezeli 'suspect' nie znajduje sie w 'string'
 *
 * Przyklad:
 * 		indexOf("id", "my id is 21") zwraca 3
 */
int indexOf(char * suspect, char * string);
/**
 * Zwraca podciag ciagu 'string' od ciągu 'startingString' do ciągu 'endingString'.
 * Jeżeli podciąg 'startingString' nie znajduje się w ciągu, cięcie rozpocznie się od
 * początku ciągu. Natomiast jeżeli 'endingString' nie znajduje się w ciągu, cięcie
 * zakończy się wraz z końcem ciągu głównego.
 *
 * UWAGA: Zwracany podciag jest dynamicznie przydzielony i powinien zostac zwolniony!
 *
 * Przyklad:
 * 		substring("Ala ma kota", "Ala", "kota") zwraca " ma "
 * 		substring("Ala ma kota", "Bartek", "kota") zwraca "Ala ma "
 * 		substring("Ala ma kota", "Bartek", "psa") zwraca "Ala ma kota"
 */
char * substring(char * string, char * startingString, char * endingString);
/**
 * Zwraca liczbę wystąpień znaku '_char' w ciągu 'string'.
 */
int countCharOccurrences(char _char, char * string);
/**
 * Zwraca liczbę wystąpień podciągu 'suspect' w ciągu 'string'.
 */
int countSubstringOccurrences(char * suspect, char * string);
/**
 * Rozdziela ciąg 'string' na tablicę po separatorze 'separator'.
 * UWAGA: Zwracany tablica jest dynamicznie przydzielona i powinna zostac zwolniona!
 */
char ** splitStringBySubstring(char * separator, char * string);

#endif /* STRING_UTILS_H_ */
