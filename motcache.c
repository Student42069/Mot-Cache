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
	puzzle[0] = '\0';
	// printf("%s\n", puzzle);
	for (unsigned int i = 0; i < PUZZLE_LENGTH / MAX_WORD_LENGTH; ++i) {
		fgets(buffer, MAX_WORD_LENGTH + 2, fp);
		buffer[strlen(buffer)- 1] = '\0';
		strcat(puzzle, buffer);
	}
	close_file(fp);
}

void printtest(char *puzzle) {
    printf("%s\n", puzzle);
    printf("%d\n", (int)strlen(puzzle));
}

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

void update_unused_letters(char *unused_letters, unsigned int *used_positions, int num_found) {
    int i;
	for (i = 0; i < num_found; i++) {
		unsigned int pos = used_positions[i];
		unused_letters[pos] = ' ';
	}
}

unsigned int check(char *word, char *puzzle, char *unused_letters, unsigned int position, unsigned int direction) {
	char found[13] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
	found[0] = puzzle[position];
	unsigned int used_positions[MAX_WORD_LENGTH];
	used_positions[0] = position;
	// printf("%s", found);
	// printf("%s\n", word);
	while (strstr(word, found) != NULL) {
		position = position + direction;
		used_positions[strlen(found)] = position;
		char cToStr[2];
		cToStr[1] = '\0';
		cToStr[0] = puzzle[position];
		// printf("%s", cToStr);
		// if (position % 12 == 0)
		// 	break;
		
		strcat(found, cToStr);
		// printf("%s : %s : %d : %d\n", found, word, (int)strlen(found), (int)strlen(word));
		if (strcmp(word, found) == 0) {
			// puts("Trouve !!");
			update_unused_letters(unused_letters, used_positions, (int)strlen(found));
			return 1;
		}
	}
	// puts("Non !");
	return 0;
}

unsigned int search_word(char *word, char *puzzle, char *unused_letters) {
	// printf("%d", (int)strlen(word));
	unsigned int position;
	for (position = 0; position < strlen(puzzle); ++position) {
		if (puzzle[position] == word[0]) {
			// printf("%d : %c\n", position, puzzle[0]);
			if ((12 - (position % 12)) >= strlen(word))
				if (check(word, puzzle, unused_letters, position, RIGHT)) {
					// printf("Mot trouve horizontal -->> !! : %s\n", word);
					return 1;
				}
			if (((position % 12) + 1) >= strlen(word))
				if (check(word, puzzle, unused_letters, position, LEFT)) {
					// printf("Mot trouve horizontal <<-- !! : %s\n", word);
					return 1;
				}
			if (((position / 12) + 1) >= strlen(word))
				if (check(word, puzzle, unused_letters, position, UP)) {
					// printf("Mot trouve vertical vers le haut !! : %s\n", word);
					return 1;
				}
			if (12 - ((position / 12) >= strlen(word)))
				if (check(word, puzzle, unused_letters, position, DOWN)) {
					// printf("Mot trouve vertical vers le bas !! : %s\n", word);
					return 1;
				}
		}
	}
	return 0;
}

void print_unused_letters(char *unused_letters) {
	long unsigned int i;
	for (i = 0; i < strlen(unused_letters); ++i)
		if (unused_letters[i] != ' ')
			printf("%c", unused_letters[i]);
	puts("");
}

void solve_puzzle(char *puzzle, char words[][MAX_WORD_LENGTH + 1], unsigned int num_words) {
	char unused_letters[strlen(puzzle)];
	strcpy(unused_letters, puzzle);
	unsigned int i;
	// printf("%d", (int) num_words);
	for (i = 0; i < num_words; i++)
		if (!search_word(words[i], puzzle, unused_letters))
			printf("Un mot n'a pas ete trouve, cela ne devrait pas se produire :( %s\n", words[i]);
	print_unused_letters(unused_letters);
}

int main(int argc, char *argv[]) {
	checkargs(argc);
	char puzzle[PUZZLE_LENGTH + 1];
	load_puzzle(puzzle, argv[1]);
	// printtest(puzzle);
	unsigned int num_words = count_words(argv[1]);
	// printf("%d", num_words);
	char words[num_words][MAX_WORD_LENGTH + 1];
	load_words(words, argv[1]);
	// print_words(words, num_words);
	solve_puzzle(puzzle, words, num_words);
	// printtest(puzzle);
	return 0;
}