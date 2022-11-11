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
    ERREUR_FILE_FORMAT      = 3,
    ERREUR_OPEN_FILE        = 4,
    ERREUR_CLOSE_FILE       = 5
};


/**
 * -----------------------
 * Function prototypes
 * -----------------------
 */

/**
 *  Closes a file and handles error cases
 *
 *  @param file pointer to the file to close
 */
void close_file(FILE *file);

/**
 *  Opens a file and handles error cases
 * 
 *  @param file_name name of the file
 *
 *  @return pointer to the file
 */
FILE* open_file(const char *file_name);

/**
 *  Verifies the number of parameters in argv.
 *  Exits the program if it there isn't 2 parameters.
 *
 *  @param argc  Parameter count
 */
void checkargs(int argc);

/**
 *  Loads the matrix of letters into a
 *  contiguous array of caracters
 *
 *  @param puzzle where the letters shall be stored
 *  @param file_name name of the file from which to retrieve the grid
 */
void load_puzzle(char *puzzle, const char *file_name);

/**
 *  Handles skipping over the grid of letters and counting the words
 *
 *  @param file_name name of the file where to count words
 */
unsigned int count_words(const char *file_name);

/**
 *  Counts the number of words to find in the matrix
 *
 *  @param fp pointer to a file
 */
unsigned int count_only_words(FILE *fp);

/**
 *  Skipping over the grid of letters
 *
 *  @param file_name name of the file
 */
void forward_puzzle(FILE *fp);

/**
 *  Handles opening the file, skipping over the grid, 
 *  then loading the words to search and closing the file
 *
 *  @param words array where all the words should be stored
 *  @param file_name name of the file
 */
void load_words(char words[][MAX_WORD_LENGTH + 1], const char *file_name);

/**
 *  Loads all the words in the file into the array words
 *
 *  @param words array where all the words should be stored
 *  @param fp pointer to the file
 */
void load_word(char words[][MAX_WORD_LENGTH + 1], FILE *fp);

/**
 *  Updates the array (string) of unused/used letters from the grid
 *
 *  @param unused_letters copy of the puzzle array of caracters, but all the used letters are ' '
 *  @param used_positions array containing all the indexes of used letter forming the word
 *  @param num_found length of the used_position array
 */
void update_unused_letters(char *unused_letters, const unsigned int *used_positions, const unsigned int num_found);

/**
 *  Checks if the current concatenation of letters is identical to the word we are looking for.
 *
 *  @param word the word we are currently searching for in the grid
 *  @param found the concatenation of caraters up to the previous caracter
 *  @param unused_letters copy of the puzzle array of caracters, but all the used letters are ' '
 *  @param used_positions array containing all the indexes of used letter forming the word
 *  @param char_to_string a caracter tranformed into a string to use strcat()
 *
 *  @return 1 if found, 0 if not found
 */
unsigned int is_found(const char *word, char *found, char *unused_letters, const unsigned int *used_positions, const char *char_to_string);

/**
 *  Main function that search the grid. Forming a words in a giving direction until the
 *  concatenation of caracters either is equal to the word we are searching or 
 *  the last added letter isn't the one we are looking for.
 *
 *  @param word the word we are currently searching for in the grid
 *  @param puzzle array containing the caracters of the grid
 *  @param unused_letters copy of the puzzle array of caracters, but all the used letters are ' '
 *  @param position the current position from which the search begins
 *  @param direction direction in which to search :
 *                   right(+1), left(-1), up(-12) or down(-12) in a 12x12 grid
 *
 *  @return 1 if found, 0 if not found
 */
unsigned int check(const char *word, const char *puzzle, char *unused_letters, unsigned int position, const unsigned int direction);

/**
 *  Verifies if a search can be done to the right and the calls check(RIGHT).
 *  Meaning if the lenght of a row minus the current column is more or equal
 *  to the lenght of the word we are looking for.
 *
 *  @param word the word we are currently searching for in the grid
 *  @param puzzle array containing the caracters of the grid
 *  @param unused_letters copy of the puzzle array of caracters, but all the used letters are ' '
 *  @param position the current position from which the search begins
 *
 *  @return 1 if found, 0 if not found
 */
unsigned int check_right(const char *word, const char *puzzle, char *unused_letters, const unsigned int position);

/**
 *  Verifies if a search can be done to the left and the calls check(LEFT).
 *  Meaning if the index of the current column is more or equual to the lenght
 *  of the word we are currently looking for.
 *
 *  @param word the word we are currently searching for in the grid
 *  @param puzzle array containing the caracters of the grid
 *  @param unused_letters copy of the puzzle array of caracters, but all the used letters are ' '
 *  @param position the current position from which the search begins
 *
 *  @return 1 if found, 0 if not found
 */
unsigned int check_left(const char *word, const char *puzzle, char *unused_letters, const unsigned int position);

/**
 *  Verifies if a search can be done upwards and the calls check(UP).
 *  Meaning if the index of the current row is more or equal than the lenght 
 *  of the word we are looking for.
 *
 *  @param word the word we are currently searching for in the grid
 *  @param puzzle array containing the caracters of the grid
 *  @param unused_letters copy of the puzzle array of caracters, but all the used letters are ' '
 *  @param position the current position from which the search begins
 *
 *  @return 1 if found, 0 if not found
 */
unsigned int check_up(const char *word, const char *puzzle, char *unused_letters, const unsigned int position);

/**
 *  Verifies if a search can be done upwards and the calls check(DOWN).
 *  Meaning if the numbers of rows minus the index of the current row is more or equal
 *  than the lenght of the word we are searching.
 *
 *  @param word the word we are currently searching for in the grid
 *  @param puzzle array containing the caracters of the grid
 *  @param unused_letters copy of the puzzle array of caracters, but all the used letters are ' '
 *  @param position the current position from which the search begins
 *
 *  @return 1 if found, 0 if not found
 */
unsigned int check_down(const char *word, const char *puzzle, char *unused_letters, const unsigned int position);

/**
 *  Goes throught all the caracters in puzzle[] and if it matches the first letter
 *  of the word we are searching, it calls check_up(), check_down(), check_right(), check_left(). 
 *
 *  @param word the word we are currently searching for in the grid
 *  @param puzzle array containing the caracters of the grid
 *  @param unused_letters copy of the puzzle array of caracters, but all the used letters are ' '
 *
 *  @return 1 if found, 0 if not found
 */
unsigned int search_word(const char *word, const char *puzzle, char *unused_letters);

/**
 *  Prints all the unused letters in puzzle[]
 *
 *  @param unused_letters copy of the puzzle array of caracters, but all the used letters are ' '
 */
void print_unused_letters(const char *unused_letters);

/**
 *  Prints a error message if a words wasn't found and exit the program
 *
 *  @param words array of all the words to be found
 *  @param i the index of the word that wasn't found
 */
void handle_not_found(const char words[][MAX_WORD_LENGTH + 1], const unsigned int i);

/**
 *  Calls search_word() for every word in the array of words to find
 *
 *  @param puzzle array containing the caracters of the grid
 *  @param words array of words to search for in the grid
 *  @param num_words length of the words[] array
 */
void solve_puzzle(const char *puzzle, const char words[][MAX_WORD_LENGTH + 1], const unsigned int num_words);
