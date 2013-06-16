#include "string-utils.h"

/*public*/inline int contains(char * suspect, char * string) {
	return strstr(string, suspect) != NULL ;
}

/*public*/int endingIndexOf(char * suspect, char * string) {
	char * found = strstr(string, suspect);
	if (found != NULL ) {
		/* Zwroc pozycje suspect w string*/
		return found - string + strlen(suspect);
	}
	return -1; /* Nie znaleziono suspect w string */
}

/*public*/int indexOf(char * suspect, char * string) {
	char * found = strstr(string, suspect);
	if (found != NULL ) {
		/* Zwroc pozycje suspect w string*/
		return found - string;
	}
	return -1; /* Nie znaleziono suspect w string */
}

/*public*/char * substring(char * string, char * startingString, char * endingString) {
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

/*public*/int countSubstringOccurrences(char * suspect, char * string) {
	unsigned int occurences = 0;
	unsigned int timesMatched = 0;
	unsigned int i, j;
	for (i = 0; i < strlen(string); ++i) {
		for (j = 0; j < strlen(suspect); ++j) {
			if(suspect[j] == string[i]) {
				timesMatched++;
				i++;
			} else {
				timesMatched = 0;
			}
			if(timesMatched >= strlen(suspect)) {
				occurences++;
				timesMatched = 0;
				break;
			}
		}
	}
	return occurences;
}

/*public*/int countCharOccurrences(char _char, char * string) {
	unsigned int occurrences = 0;
	unsigned int i;
	for (i = 0; i < strlen(string); ++i) {
		if (string[i] == _char) {
			occurrences++;
		}
	}
	return occurrences;
}

/*public*/char ** splitStringBySubstring(char * separator, char * string) {
	char * token, *copy, *toFree, **arrayOfStrings;
	int i, seperatorOccurences;
	seperatorOccurences = countSubstringOccurrences(separator, string);
	/* Rezerwuj pamiec dla tablicy powstalej po podzieleniu ciagu*/
	arrayOfStrings = malloc((seperatorOccurences+1)* sizeof(char*));
	for (i = 0; i < seperatorOccurences+1; ++i) {
		/* Zakladamu tutaj najgorszy scenariusz, czyli  tablica jednoelementowa z calym ciagiem w pierwszym elemencie*/
		arrayOfStrings[i] = malloc((strlen(string)+1) * sizeof(char));
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
