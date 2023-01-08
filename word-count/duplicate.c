#include <ctype.h>
#include <dedup.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <table_string.h>
#include <vector_char.h>

/* Read file into a characater buffer */
char *readfile(char *filename) {
  char *source;
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) { /* Error */
    printf("Error reading file");
    exit(1);
  }
  if (fp != NULL) {
    /* Go to the end of the file. */
    if (fseek(fp, 0L, SEEK_END) == 0) {
      /* Get the size of the file. */
      long bufsize = ftell(fp);
      if (bufsize == -1) { /* Error */
        printf("Error reading file");
      }
      /* Allocate our buffer to that size. */
      source = malloc(sizeof(char) * (bufsize + 1));
      /* Go back to the start of the file. */
      if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */
      }
      /* Read the entire file into memory. */
      size_t newLen = fread(source, sizeof(char), bufsize, fp);
      if (ferror(fp) != 0) {
        printf("Error reading file");
      } else {
        source[newLen++] = '\0'; /* Just to be safe. */
      }
    }
  }
  fclose(fp);
  return source;
}

int main(int argc, char **argv) {
  char *source = NULL;

  if (argc != 3) {
    printf("./dedup.bin [FILE PATH1] [FILE PATH2]");
    exit(1);
  }
  char *source1 = readfile(argv[1]);
  char *source2 = readfile(argv[2]);
  /**
   * @brief Read file into source.
   * source is a character array with file contents
   * It is null terminated
   */

  // argv[1] name of file1
  // argv[2] name of file2
  /** Start processing file and separate into words */
  /** Create Table String 1 with file in argv[1] */
  /** Create Table string 2 with file in argv[2] */
  /** Find common words between ts1 and ts2 */
  /** Deallocate **/
  return 0;
}