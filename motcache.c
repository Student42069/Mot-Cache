#include "motcache.h"

void close_file(FILE *fptr) {
	if (fclose(fptr) == EOF) {
		printf("Erreur dans la fermeture du fichier.\n");
		exit(ERREUR_CLOSE_FILE);
	}
}

FILE* open_file(const char *file_name) {
	FILE *fptr = fopen(file_name, "r");
	
	if (fptr == NULL) {
		printf("Erreur dans l'ouverture du fichier.\n");
		exit(ERREUR_OPEN_FILE);
	}
	return fptr;
}

void checkargs(int argc) {
	if (argc != 2) {
		printf("%s\n", "nombre arguments invalide");
		printf(USAGE, "./motcache");
		exit(ERREUR_NB_ARGS);
	}
}

void load_puzzle(char *puzzle, char *file_name) {
	FILE *fp = open_file(file_name);
	char buffer[MAX_WORD_LENGTH + 2];
	for (unsigned int i = 0; i < PUZZLE_LENGTH / MAX_WORD_LENGTH; ++i) {
		fgets(buffer, MAX_WORD_LENGTH + 2, fp);
		buffer[strlen(buffer)- 1] = '\0';
		strcat(puzzle, buffer);
	}
	close_file(fp);
}

// void printtest(char *puzzle) {
//     printf("%s\n", puzzle);
//     printf("%d", (int)strlen(puzzle));
// }

unsigned int count_words(char *file_name) {
	FILE *fp = open_file(file_name);
	char buffer[MAX_WORD_LENGTH + 2];
	forward_puzzle(fp, buffer);
	unsigned int count = count_only_words(fp, buffer);
	close_file(fp);
	return count;
}

unsigned int count_only_words(FILE *fp, char *buffer) {
	unsigned int count = 0;
	do {
		fgets(buffer, MAX_WORD_LENGTH + 2, fp);
		if (strlen(buffer) > 1) count++;
	} while (!feof(fp));
	return count;
}

void forward_puzzle(FILE *fp, char *buffer) {
	for (unsigned int i = 0; i < PUZZLE_LENGTH / MAX_WORD_LENGTH; ++i)
		fgets(buffer, MAX_WORD_LENGTH + 2, fp);
}

void load_words(char words[][MAX_WORD_LENGTH + 1], char *file_name) {
	FILE *fp = open_file(file_name);
	char buffer[MAX_WORD_LENGTH + 2];
	forward_puzzle(fp, buffer);
	load_word(words, fp, buffer);
	close_file(fp);
}

void load_word(char words[][MAX_WORD_LENGTH + 1], FILE *fp, char *buffer) {
	unsigned int count = 0;
	do {
		fgets(buffer, MAX_WORD_LENGTH + 2, fp);
		if (strlen(buffer) > 1) {
			buffer[strlen(buffer)- 1] = '\0';
			strcpy(words[count++], buffer);
		}
	} while (!feof(fp));
}

void print_words(char words[][MAX_WORD_LENGTH + 1], unsigned int num_words) {
	for (unsigned int i = 0; i < num_words; ++i) {
		printf("%s\n", words[i]);
	}
}

int main(int argc, char *argv[]) {
	checkargs(argc);
	char puzzle[PUZZLE_LENGTH + 1];
	load_puzzle(puzzle, argv[1]);
	// printtest(puzzle);
	// unsigned int num_words = count_words(argv[1]);
	// printf("%d", num_words);
	char words[count_words(argv[1])][MAX_WORD_LENGTH + 1];
	load_words(words, argv[1]);
	// print_words(words, num_words);
	
	return 0;
}