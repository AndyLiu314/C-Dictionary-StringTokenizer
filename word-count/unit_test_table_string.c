/* To build:
Dry run
make -n unit_test_table_string
To actually build
make unit_test_vector_string
 */
#include "table_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  // Array of strings. Each entry in strings is a char*
  const char *strings[3];
  strings[0] = "Hello";
  strings[1] = "Worlde";
  strings[2] = "Worlde";


  // buckets have to be power of 2
  int buckets = 2;
  table_string *vs = table_string_allocate(2);
  char *entry = NULL;

  /*
  char* name = "andaaau";
  char* name2 = "liao";
  char* name3 = "liao";
  char* name4 = "liaoa";
  char* name5 = "andaaau";
  printf("%i\n", (djb2_word_to_bucket(name, 16)));
  printf("%i\n", (djb2_word_to_bucket(name2, 16)));
  printf("%i\n", (djb2_word_to_bucket(name3, 16)));
  printf("%i\n", (djb2_word_to_bucket(name4, 16)));
  printf("%i\n", (djb2_word_to_bucket(name5, 16)));
  */

  
  for (int i = 0; i < 3; i++) {
    // Things to note.
    // entry is overwritten here. Only vector string remembers the pointer to be
    // freed.
    // +1 here is for \0 terminating strings.
    entry = (char *)malloc(sizeof(char) * strlen(strings[i]) + 1);
    // Memcpy all characters along with \0 terminating string characters.
    memcpy(entry, strings[i], strlen(strings[i]) + 1);
    // Entry has been inserted. Note that to free, now you have to deallocate
    // from within table_string.
    table_string_insert_or_add(vs, entry, 0); // Using 0 as a default line number
  }
  table_string_print(vs);

  /*
  char** test = malloc(sizeof(char*)*3);
  for (int k = 0; k<3; k++){
    if (test[k] == NULL){
      printf("NULL\n");
    }
  }

  char* word = "cray";
  char* word1 = "afhawpgangjawg:";

  word = word1;

  printf("%s\n", word);
  */

  table_string_deallocate(vs);
}
