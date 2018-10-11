#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUF_SIZE 1024

bool is_vowel(char letter);
int determineLength(char *str);
int copy_non_vowels(int num_chars, char* in_buf, char* out_buf);
void disemvowel(FILE* inputFile, FILE* outputFile);

int main(int argc, char *argv[]) {
    FILE *inputFile;
    FILE *outputFile;

    // If there are no files provided, program will assume standard input is being provided.
    // If there is one file providedm, program will take data from the file and output to standard output
    // If two files are provided, program will take data from input file and write it to the output file
    // If an invalid number of arguments are provided, program will get mad and quit
    if(argc == 1) {
      inputFile = stdin;
      outputFile = stdout;
      disemvowel(inputFile, outputFile);
    } else if(argc == 2) {
      inputFile = fopen(argv[1], "r");
      outputFile = stdout;
      disemvowel(inputFile, outputFile);
    } else if(argc == 3) {
      // Open files specificed in arguments
      inputFile = fopen(argv[1], "r");
      outputFile = fopen(argv[2], "w");
      disemvowel(inputFile, outputFile);
    } else {
      printf("Wrong number of inputs! Try again!\n");
      exit(-1);
    }

    // Close the input and output files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

// Takes the input and output files and reads the input file
// and feeds that to copy_non_vowels and then writes the results
// to the out_buf
void disemvowel(FILE* inputFile, FILE* outputFile) {
    char in_buf[BUF_SIZE];
    char out_buf[BUF_SIZE];

    // Initial read of the input
    int numRead = fread(in_buf, sizeof(char), BUF_SIZE, inputFile);

    // As long as there is data to read, disemvowel with copy_non_vowels,
    // write it to the output file and find the number of items read
    while(numRead > 0) {
      int n = copy_non_vowels(numRead, in_buf, out_buf);
      fwrite(out_buf, sizeof(char), n, outputFile);
      numRead = fread(in_buf, sizeof(char), BUF_SIZE, inputFile);
    }
}

// Takes the in_buf, removes the vowels and puts it in the out_buf
int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
   int j = 0;

   // Loops through the in_buf and if in_buf[i]
   // isn't a vowel, add it to the out_buf
   for(int i = 0; i < num_chars; i++) {
     if (!(is_vowel(in_buf[i]))) {
	      out_buf[j] = in_buf[i];
	      j++;
     }
   }

   return j;
}

// Takes a char and determines if it's a vowel
bool is_vowel(char letter) {
    letter = tolower(letter);
        switch(letter) {
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                        return true;
                default :
                        return false;
        }
}
