#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

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
    char* disemvoweledStr;
    int c;
    int d;
    while(1) {
      int c = fgetc(inputFile);
      if(feof(inputFile)) {
	break;
      }
    }

    while(1) {
      int d = fgetc(outputFile);
      if(feof(outputFile)) {
	break;
      }
    }
   
    disemvoweledStr = copy_non_vowels(strlen(c), c, d);
}

int main(int argc, char *argv[]) { 
    FILE *inputFile; 
    FILE *outputFile;

    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");

    while(1) {
      int c = fgetc(inputFile);
      if(feof(inputFile)) {
	break;
      }
      
    }

    disemvowel(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0; 
}
