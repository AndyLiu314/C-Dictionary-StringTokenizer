#include "vector_string.h"
#include "str_cmp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
/////////////////////////////////////////

*/
/**
 * @brief Memory allocate a vector string so that we can start inserting entries
 * into it.
 *
 */
vector_string *vector_string_allocate() {
  vector_string* vstr = (vector_string *)malloc(sizeof(vector_string));
  if (!vstr){
    return NULL;
  }

  vstr->head = NULL;
  vstr->tail = NULL;
  return vstr;
}

/**
 * @brief Search the vector string pointed to by vs and return true if the
 * vs_entry.value == key, else return false.
 * TODO:
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */
bool vector_string_find(vector_string *vs, char *key) { 
  vs_entry_t* cur = vs->head;
  while (cur != NULL) {
    if (my_str_cmp(cur->value,key)==0){
      return true;
    }
    cur = cur-> next;
  }
  return false; 
}

/**
 * @brief TODO: Insert the string pointed to by key into the vector string.
 *  char* is externally allocated. You do not have to allocate internally
 *
 * @param vs - Pointer to vector_string datastructure
 * @param key - Pointer to string to search for
 * @return * Find*
 */
void vector_string_insert(vector_string *vs, char *key) {
  if (vs == NULL){
    return;
  }

  vs_entry_t* newTail = (vs_entry_t*)malloc(sizeof(vs_entry_t));
  if (newTail == NULL){
    return;
  }

  newTail->value = key;
  newTail->next = NULL;

  if (vs->head == NULL) {
    vs->head = newTail;
    vs->tail = newTail;
  } else {
    vs->tail->next = newTail;
    vs->tail = newTail;
  }
  // Insert the string into the tail of the list.
}
/**
 * @brief Remove all entries and cleanup vector string
 * TODO: Remove all entries. Remember head and tail are pointers.
 * Remember to remove vs as well; not just entries. or you will have memory
 * leaks.
 * @param vs: Pointer to vector_string struct
 */
void vector_string_deallocate(vector_string *vs) {
  vs_entry_t* cur;
  while (vs->head != NULL) {
    cur = vs->head;
    vs->head = cur->next;
    free(cur);
  }
  free(vs);
}

/**
 * @brief Print all value in each entry of the vector string, in the following
 * format. In this case hello and world are the unique words in the file.
 * 1. hello
 * 2. world
 * @param vs
 */
void vector_string_print(vector_string *vs) {
  vs_entry_t *entry = vs->head;

  int count = 1;
  while (entry!=NULL){
    printf("%d. %s\n", count, entry->value);
    entry = entry->next;
    count++;
  }
}