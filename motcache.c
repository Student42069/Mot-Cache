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

void loadpuzzle(char *puzzle, char *file_name) {
    FILE *fp = open_file(file_name);
    char buffer[MAX_WORD_LENGTH + 2];
    for (unsigned int i = 0; i < PUZZLE_LENGTH / MAX_WORD_LENGTH; ++i) {
        fgets(buffer, MAX_WORD_LENGTH + 2, fp);
        buffer[strlen(buffer)- 1] = '\0';
        strcat(puzzle, buffer);
    }
    close_file(fp);
}

void printtest(char *puzzle) {
    printf("%s\n", puzzle);
    printf("%d", (int)strlen(puzzle));
}

int main(int argc, char *argv[]) {
    checkargs(argc);
    char puzzle[PUZZLE_LENGTH + 1];
    loadpuzzle(puzzle, argv[1]);
    printtest(puzzle);
    //char words[num_words][MAX_WORD_LENGTH];
    return 0;
}