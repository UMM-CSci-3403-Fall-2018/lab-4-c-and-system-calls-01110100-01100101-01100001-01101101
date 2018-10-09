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

    // Open files specificed in arguments
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");

    // Run disemvowel
    disemvowel(inputFile, outputFile);

    // Close the input and output files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

// Takes the input and output files and reads the input file
// and feeds that to copy_non_vowels and then writes the results
// to the out_buf
void disemvowel(FILE* inputFile, FILE* outputFile) {
    char* in_buf[BUF_SIZE];
    char* out_buf[BUF_SIZE];

    // Find the inital number of items read from the inputFile
    int readNum = fread(in_buf, sizeof(in_buf), BUF_SIZE, inputFile);

    // As long as there is data to read, disemvowel with copy_non_vowels,
    // write it to the output file and find the number of items read
    while(readNum > 0) {
      int tmp = copy_non_vowels(strlen(in_buf), in_buf, out_buf);
      fwrite(out_buf, sizeof(out_buf), BUF_SIZE, outputFile);
      readNum = fread(in_buf, sizeof(in_buf), BUF_SIZE, inputFile);
    }
}

// Takes the in_buf, removes the vowels and puts it in the out_buf
int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
   out_buf = (char*) calloc(determineLength(in_buf), sizeof(char));
   int j = 0;

   // Loops through the in_buf and if in_buf[i]
   // isn't a vowel, add it to the out_buf
   for(int i = 0; i < num_chars; i++) {
     if (!(is_vowel(in_buf[i]))) {
	      out_buf[j] = in_buf[i];
	      j++;
     }
   }

   // Setting the null terminator after the string in out_buf
   out_buf[j] = '\0';

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

// Takes a char string and determines it's length without vowels in it
// so we know how big to allocate for the disemvoweled string
int determineLength(char *str) {
  int count = 0;

  for(unsigned int i = 0; i < strlen(str); i++) {
	   if (str[i] != is_vowel(str[i])) {
	      count++;
	 	}
	}

	return count;
}
