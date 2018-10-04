#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUF_SIZE 1024

bool is_vowel(char letter) {
    letter = tolower(letter);
        switch(letter) {
                case 'a':
                        return true;
                case 'e':
                        return true;
                case 'i':
                        return true;
                case 'o':
                        return true;
                case 'u':
                        return true;
                default :
                        return false;
        }
}


int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
   int j = 0;

   for(int i = 0; i < num_chars; i++) {
     if (!(is_vowel(in_buf[i]))) {
	out_buf[j] = in_buf[i];
	j++;
     }
    }
	
    out_buf[j] = '\0';

    return j - 1;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
    long size;

    fseek(inputFile, 0L, SEEK_END);
    size = ftell(inputFile);
    rewind(inputFile);

    char* outbuf = (char*) calloc(size + 1, sizeof(char));

    char* inbuf = (char*) calloc(size + 1, sizeof(char));
    if (!inbuf) {
      fclose(inputFile);
      fputs("memory alloc fails", stderr);
      exit(1);
    }

    if (1 != fread(inbuf, size, 1, inputFile)){
      fclose(inputFile);
      free(inbuf);
      fputs("entire read fails", stderr);
      exit(1);
    }
    
    int new_size = copy_non_vowels(strlen(inbuf), inbuf, outbuf);
}

int main(int argc, char *argv[]) { 
    FILE *inputFile; 
    FILE *outputFile;

    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");

    disemvowel(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0; 
}
