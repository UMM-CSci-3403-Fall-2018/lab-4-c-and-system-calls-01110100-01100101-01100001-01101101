#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

// initialize our counters
static int num_dirs, num_regular;

// boolean function check whether the given path is a directory
bool is_dir(const char* path) {
  struct stat buf;

  int i = stat(path, &buf);

  if(i < 0) {
    printf("error: this is not a directory. please try again.\n");
    exit(-1);
  } else {
    return S_ISDIR(buf.st_mode);
  }
}

/*
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

// recursive function that counts every subdirectory of the given path including its self.
void process_directory(const char* path) {
  // initialize the variables
  DIR *dir;
  struct dirent *entry;
  num_dirs++;

  // start opening the directory
  dir = opendir(path);
  if (dir == NULL) {
    perror("this is an error opening the directory");
    exit(-1);
  } else {
    // go into the subdirectory
    chdir(path);
    entry = readdir(dir);
    while (entry != NULL) {
      if (entry->d_name[0] != '.') {
	// recursive call
	process_path(entry->d_name);
      }
      entry = readdir(dir);
    }
    // go out the subdirectory
    chdir("..");
    // close the directory
    closedir(dir);
  }
}
// count files
void process_file(const char* path) {
  num_regular++;
}

// distribute the files and the path to different functions
void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  // execution call
  process_path(argv[1]);
  // print the results
  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
