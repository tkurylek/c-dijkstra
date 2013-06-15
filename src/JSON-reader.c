#include "JSON-reader.h"

unsigned int getFileLength(FILE * file) {
	unsigned int length;
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	return length;
}

inline int containsWhitespaces(char _char) {
	return _char == ' ' || _char == '\n' || _char == '\t';
}

char * readAndVerifyJson(const char * filePath) {
	FILE * inputJsonFile = fopen(filePath, "r");
	JSON_checker jc = new_JSON_checker(20);
	unsigned int inputJsonFileLength, i;
	char * jsonContent, nextChar;
	/* Sprawdz czy plik zrodlowy istnieje */
	if (inputJsonFile == NULL ) {
		fprintf(stderr, "Nie odnaleziono pliku zrodlowego.");
		exit(1);
	}
	/* Przejdz na koniec pliku, aby dowiedziec sie ile znakow posiada*/
	inputJsonFileLength = getFileLength(inputJsonFile);

	/* skopiuj dane z pliku*/
	jsonContent = malloc(sizeof(char) * (inputJsonFileLength + 1));
	i = 0;
	while (1) {
		nextChar = getc(inputJsonFile);
		/* Sprawdz czy to juz koniec*/
		if (nextChar <= 0) {
			break;
		}
		/* Nie trac czasu i pomijaj biale znaki */
		if (containsWhitespaces(nextChar)) {
			continue;
		}
		/* weryfikuj czy JSON jest poprawny*/
		if (!JSON_checker_char(jc, nextChar)) {
			fprintf(stderr,
					"JSON_checker_char: Niepoprawna składnia pliku JSON przy znaku \"%c\"\n",
					nextChar);
			exit(1);
		}
		/* Zapisuj odczytywane dane */
		if (nextChar != '[' && nextChar != ']') { /*Nie potrzebujemy tych znakow*/
			jsonContent[i++] = (char) nextChar;
		}
	}
	/* zakoncz prace z plikiem*/
	fclose(inputJsonFile);
	jsonContent[i++] = '\0';
	if (!JSON_checker_done(jc)) {
		fprintf(stderr, "JSON_checker_end: Niepoprawna składnia pliku JSON\n");
		exit(1);
	}
	return jsonContent;
}
