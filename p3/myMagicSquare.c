///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2023, Nawaf Alsrehin
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
    int size;
    // prompt a question to get user input
    printf("Enter magic square's size (odd integer >=3)\n");
    scanf("%i", &size);
    if (size < 3){
        printf("Magic square size must be >= 3.\n");
        exit(1);
    }
    if ((size & 1) != 1){
        printf("Magic square size must be odd.\n");
        exit(1);
    }

    return size;
} 
   
/* TODO:
 * Makes a magic square of size n using the alternate 
 * Siamese magic square algorithm from assignment and 
 * returns a pointer to the completed MagicSquare struct.
 *
 * n the number of rows and columns
 */
MagicSquare *generateMagicSquare(int n) {
    // allocate memory on heap for a MagicSquare structure pointer
    MagicSquare *psquare = (MagicSquare *) malloc(sizeof(MagicSquare));
    if (psquare == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    psquare->size = n;
    // allocate memory on heap for rows of 2D array
    psquare->magic_square = (int **) malloc(psquare->size * sizeof(int *));
    if (psquare->magic_square == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    // allocate memory on heap for cols of 2D array
    for (int i = 0; i < n; i++){
        *(psquare->magic_square + i) =
                (int *) malloc(psquare->size * sizeof (int));
        if (*(psquare->magic_square + i) == NULL){
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }

    int initializer = 0;  // plus one for each iteration
    int col = psquare->size - 1;  // col set to the initial value
    int row = psquare->size / 2;  // row set to the initial value
    // iterating the square
    for (int i = 0; i < n * n; i++) {
        if (i != 0){  // after the first iteration, increase row and col by 1
            row++;
            col++;
            if (row == n){  // if reached to the edge, reset to one
                row = 0;
            }
            if (col == n){  // if reached to the edge, reset to one
                col = 0;
            }
        }
        // fill the value on the cell if its value has not been initialized
        // default value is 0
        if (*(*(psquare->magic_square + row) + col) == 0){
            // update value
            *(*(psquare->magic_square + row) + col) = ++initializer;
        }
        // if initialized already, fill the cell right left to the original cell
        // as illustrated in the example for this project
        else{
            row = row - 1;
            col = col - 2;
            if (row < 0){  // if reached to the edge, set row = n - (- row )
                row = n + row;
            }
            if (col < 0){  // if reached to the edge, set col = n - (- col )
                col = n + col;
            }
            // update value
            *(*(psquare->magic_square + row) + col) = ++initializer;
        }
    }
    return psquare;
}

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    // declare a pointer that points to FILE
    FILE *file = fopen(filename, "w");
    if (file == NULL){
        printf("Error opening the file.\n");
        exit(1);
    }
    int size = magic_square->size;
    fprintf(file, "%i\n", size);  // output the size first to output file
    // iterate the whole magic_square and write the output file
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            fprintf(file, "%i", *(*(magic_square->magic_square + i) + j));
            if (j != size - 1){
                // between each number, there is a comma
                fprintf(file, ",");
            }
        }
        // change to next line when current row is outputted
        fprintf(file, "\n");
    }
    // close file
    int result = fclose(file);
    if (result != 0){
        printf("Error closing the file.\n");
        exit(1);
    }
}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the square to the output filename
 * 
 * Be su
 *
 * Add description of required CLAs here
 */
int main(int argc, char **argv) {
    // TODO: Check input arguments to get output filename
    if (argc != 2){
        printf("Usage: ./myMagicSquare <output_filename>\n");
        exit(1);
    }
    char *filename = *(argv + 1);
    // TODO: Get magic square's size from user
    int size = getSize();
    // TODO: Generate the magic square by correctly interpreting 
    //       the algorithm(s) in the write-up or by writing or your own.  
    //       You must confirm that your program produces a 
    //       Magic Sqare as described in the linked Wikipedia page.
    MagicSquare *magic_square = generateMagicSquare(size);
    // TODO: Output the magic square
    fileOutputMagicSquare(magic_square, filename);
    // free all allocated memory
    for (int i = 0; i < size; i++){
        free(*(magic_square->magic_square + i));
        *(magic_square->magic_square + i) = NULL;
    }
    // free allocated memory
    free(magic_square->magic_square);
    magic_square->magic_square = NULL;
    free(magic_square);
    magic_square = NULL;

    return 0;
} 

// S23

