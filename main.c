/*
 *
 Write a program that reads in a file containing several lines of text and then prints only those strings that end with the letters ?ed?.

The program should do the following:

1. Prompt the user for the name of a text file (if the file does not exist, display an error message and re-prompt)
2. Read in a series of strings from the text file and store these in an array of strings, dynamically allocating memory for each element
3. Loop through the populated string array and find elements that end with the characters "ed"
4. Display on screen a list of only those strings that end with "ed"
 *
 */
#include <stdio.h>
#include <string.h>     /* For string functions */
#include <stdlib.h>     /* For dynamic memory allocation */

FILE* inputFile();
int wordsnumber(FILE* inputFile);
char **read_strings(FILE* inputFile, int* count);
void printwords(char *arraywords, char searchstring[]);

    int main(void)
    {
        char**      array    = NULL;    /* Array of read lines */
        int         line_count;         // Total number of read lines
// Prompt the user for the name of a text file

        FILE* inputFileName;
        inputFileName=inputFile();

        /* Read lines from file. */
        array = read_strings(inputFileName, &line_count);

        for (int i = 0; i < line_count; i++) {

             printwords(array[i], "ed");
        }
        /* Cleanup. */
        fclose(inputFileName);
        for (int i = 0; i < line_count; i++) {
            free(array[i]);
        }
        free(array);


        return 0;
    }

    FILE* inputFile(){
    char inputfilename[200]; // input filename
    printf("Insert the name of the Input file:  "); // prompt to insert the input file name
    scanf("%s",inputfilename);

    FILE *fp1; // Input file
//if the file doesn’t exist:
    while((fp1 = fopen(inputfilename, "r")) == NULL){
        fprintf(stderr,"Error opening the file, please try again: ");
        scanf("%s",inputfilename);
    }

 //       printf("OK %s",inputfilename);
        return fp1;

}

    char **read_strings(FILE* inputFile, int* count){
    char** array = NULL;        /* Array of lines */
    int    i;                   /* Loop counter */
    char   word[100];           /* Buffer to read each line */
    int    word_count;          /* Total number of lines */
    int    word_length;         /* Length of a single line */

    /* Clear output parameter. */
    *count = 0;

    /* Get the count of lines in the file */
    word_count = wordsnumber(inputFile);


    /* Move to the beginning of file. */
    rewind(inputFile);

    /* Allocate an array of pointers to strings
     * (one item per line). */
    array = malloc(word_count * sizeof(char *));
    if (array == NULL) {
        return NULL; /* Error */
    }

    /* Read each line from file and deep-copy in the array. */
    for (i = 0; i < word_count; i++) {
        /* Read the current line. */
      //  fgets(line, sizeof(line), inputFile);
        fscanf(inputFile,"%s",word);

        /* Allocate space to store a copy of the line. +1 for NUL terminator */
        array[i] = malloc((size_t) (word_length + 1));

        /* Copy the line into the newly allocated space. */
        strcpy(array[i], word);
    }

    /* Write output param */
    *count = word_count;

    /* Return the array of lines */
    return array;

}

    int wordsnumber(FILE* inputFile){

        int wordCount=0;
   //     int ch;
        char word;
        while((fscanf(inputFile,"%s",word))!=EOF) {

                ++wordCount;

    }
        printf("word count: %d", wordCount);
        return wordCount;
}

void printwords(char *arraywords, char searchstring[]){

    if( strlen(arraywords)>1 && !strcmp(arraywords+strlen(arraywords)-2,"ed") )
        printf("found: %s\n",arraywords);

}