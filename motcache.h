#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USAGE "\
Usage: %s <TEXTFILE>\n\
\n\
Solves a given 12x12 word search puzzle.\n\
\n\
If no argument is provided or if the puzzle isn't formatted correctly,\n\
the program prints this help and exit.\n\
"
#define RIGHT 1
#define LEFT -1
#define UP -12
#define DOWN 12
#define PUZZLE_LENGTH 144
#define MAX_WORD_LENGTH 12

enum error {
    OK                      = 0,
    ERREUR_NB_ARGS          = 1,
    ERREUR_FILE_FORMAT	    = 3,
    ERREUR_OPEN_FILE	    = 4,
    ERREUR_CLOSE_FILE	    = 5
};


/**
 * -----------------------
 * Function prototypes
 * -----------------------
 */

unsigned int count_words(char *file_name);

FILE* open_file(const char *filename);

void close_file(FILE *file);

void checkargs(int argc);

unsigned int count_only_words(FILE *fp, char *buffer);

void forward_puzzle(FILE *fp, char *buffer);

void load_puzzle(char *puzzle, char *file_name);

void load_words(char words[][MAX_WORD_LENGTH + 1], char *file_name);

void load_word(char words[][MAX_WORD_LENGTH + 1], FILE *fp, char *buffer);
