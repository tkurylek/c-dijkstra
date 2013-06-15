#include "string-utils.h"

inline int contains(char * suspect, char * string) {
	return strstr(string, suspect) != NULL ;
}

int endingIndexOf(char * suspect, char * string) {
	char * found = strstr(string, suspect);
	if (found != NULL ) {
		/* Zwroc pozycje suspect w string*/
		return found - string + strlen(suspect);
	}
	return -1; /* Nie znaleziono suspect w string */
}

int indexOf(char * suspect, char * string) {
	char * found = strstr(string, suspect);
	if (found != NULL ) {
		/* Zwroc pozycje suspect w string*/
		return found - string;
	}
	return -1; /* Nie znaleziono suspect w string */
}

char * substring(char * string, char * startingString, char * endingString) {
	char * substring = NULL, *tmp = NULL;
	int endingIndexOfStartingChar;
	int indexOfEndingChar;
	/* Sprawdz skad zaczac ciecie */
	if (!contains(startingString, string)) {
		endingIndexOfStartingChar = 0;
	} else {
		endingIndexOfStartingChar = endingIndexOf(startingString, string);
	}
	/* przydziel pamiec na ciag wyciety od 'startingString' do konca ciagu */
	tmp = malloc(
			(strlen(string) - endingIndexOfStartingChar + 1) * sizeof(char));
	/* wytnij ciag */
	strncpy(tmp, string + endingIndexOfStartingChar,
			strlen(string) - endingIndexOfStartingChar);
	tmp[strlen(string) - endingIndexOfStartingChar] = '\0';
	/* ustal miejsce zakonczenia ciecia; jezeli brak to tnij do konca ciagu */
	if (!contains(endingString, tmp)) {
		indexOfEndingChar = strlen(tmp);
	} else {
		indexOfEndingChar = indexOf(endingString, tmp);
	}
	/* tnij od poczatku do 'endingString' lub konca ciagu */
	substring = malloc((indexOfEndingChar + 1) * sizeof(char));
	strncpy(substring, tmp, indexOfEndingChar);
	substring[indexOfEndingChar] = '\0';
	free(tmp); /* zwolnij pamiec */
	return substring;
}

int countCharOccurrences(char _char, char * string) {
	int occurrences = 0;
	unsigned int i;
	for (i = 0; i < strlen(string); ++i) {
		if (string[i] == _char) {
			occurrences++;
		}
	}
	return occurrences;
}

char ** splitString(char * separator, char * string) {
	char * token, *copy, *toFree, **arrayOfStrings;
	int i, seperatorOccurences;
	seperatorOccurences = countCharOccurrences(separator[0], string);
	/* Rezerwuj pamiec dla tablicy powstalej po podzieleniu ciagu*/
	arrayOfStrings = malloc(seperatorOccurences * sizeof(char*));
	for (i = 0; i < seperatorOccurences; ++i) {
		/* Zakladamu tutaj najgorszy scenariusz, czyli  tablica jednoelementowa z calym ciagiem w pierwszym elemencie*/
		arrayOfStrings[i] = malloc(strlen(string) * sizeof(char));
	}
	i = 0;
	copy = strdup(string);
	if (copy != NULL ) {
		toFree = copy;
		while ((token = strsep(&copy, separator)) != NULL ) {
			if (strlen(token) != 0) {
				strcpy(arrayOfStrings[i++], token);
			}
		}
		free(toFree);
	}
	return arrayOfStrings;
}
