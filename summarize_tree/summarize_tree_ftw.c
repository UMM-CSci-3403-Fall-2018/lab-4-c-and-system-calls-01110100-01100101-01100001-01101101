#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>

// initialize our counters
static int num_dirs, num_regular;

// check if the typeflag matches file or direcotry, and add the amount of that type according to the match. return 0.
static int callback(const char *fpath, const struct stat *sb, int typeflag) {
  if (typeflag == FTW_F) {
    num_regular++;
  } else if (typeflag == FTW_D) {
    num_dirs++;
  }
  return 0;
}

// define the maximum depth of the ftw()
#define MAX_FTW_DEPTH 16

int main(int argc, char** argv) {
  // check if we have the correct amount of imput argument
  if (argc != 2) {
    printf ("wrong number of argument! please try again!\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  // calling ftw with direcotry, our callback, and the maximum depth
  ftw(argv[1], callback, MAX_FTW_DEPTH);

  // print out our result
  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);
  
}
