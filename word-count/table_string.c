#include "table_string.h"
#include "str_cmp.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETS
// DO NOT ADD ANY NEW FUNCTIONS BEFORE djb2
// Hash a character array to integer value between 0 and buckets-1.
// See here for more details: https://theartincode.stanis.me/008-djb2/
unsigned int djb2_word_to_bucket(char *word, int buckets) {
  if (!word) {
    printf("Invoked with null string");
    exit(EXIT_FAILURE);
  }
  unsigned long hash = 5381;
  uint32_t i;

  for (i = 0; i < strlen(word); i++)
    hash = ((hash << 5) + hash) + word[i];

  return hash & (buckets - 1);
}

// ADD YOUR HELPER FUNCTIONS AFTER djb2
/**
 * @brief Instantiate a table string
 *
 * @param buckets
 * @return table_string*
 */
table_string *table_string_allocate(unsigned int buckets) {
  table_string* tstr = (table_string*)malloc(sizeof(table_string));
  if (!tstr) {
    return NULL;
  }

  tstr->heads = (vs_entry_t**)malloc(buckets*sizeof(vs_entry_t*));
  if (!tstr->heads) {
    return NULL;
  }
  
  tstr->buckets = buckets; 

  for (int i = 0; i<buckets; i++){
    tstr->heads[i] = (vs_entry_t*) malloc(sizeof(vs_entry_t));
    tstr->heads[i]->value = NULL;
    tstr->heads[i]->next = NULL;
    tstr->heads[i]->lines = malloc(sizeof(int));
    tstr->heads[i]->size_of_lines = 1;
  }
  return tstr;
  // Instantiate a bucket number of heads
}

/**
 * @brief Insert the string pointed to by word into the table string.
 *   If word is already found increment count.
 *   If word is not found insert at the end of the corresponding bucket
 * @param ts - Pointer to table_string datastructure
 * @param word - Pointer to string to search for
 * @return * Find*
 */
void table_string_insert_or_add(table_string *ts, char *word, int line) {
  // Find the bucket for word. djb2 will return a value between 0-buckets-1.
  // Rule: buckets can only be power of 2.
  int bucket = djb2_word_to_bucket(word, ts->buckets);
  
  //head == null meaning it isnt initialized
  if (ts->heads[bucket]->value == NULL){
    ts->heads[bucket]->lines[0] = line;
    ts->heads[bucket]->value = word; 
    ts->heads[bucket]->next = NULL;
    return;
  } 

  vs_entry_t* cur = ts->heads[bucket];
  vs_entry_t* last; 
  while (cur != NULL) {

    //word in list
    if (my_str_cmp(ts->heads[bucket]->value, word) == 0){
      ts->heads[bucket]->size_of_lines++;
      int size = ts->heads[bucket]->size_of_lines;
      ts->heads[bucket]->lines = realloc(ts->heads[bucket]->lines, sizeof(int)*size);
      ts->heads[bucket]->lines[size-1] = line;
      return;
    }
    last = cur;
    cur = cur->next; 
  }

  //word not in list
  vs_entry_t* newTail = (vs_entry_t*)malloc(sizeof(vs_entry_t));
  newTail->value = word;
  newTail->next = NULL;
  newTail->size_of_lines = 1; 
  newTail->lines = malloc(sizeof(int));
  newTail->lines[0] = line; 
  last->next = newTail;
  // TODO:
  // Case head == NULL: bucket hasn't been initialized yet
  // Case word already in list, add to line array.
  // Case word not found, insert word and return.
  return;
}

void table_string_deallocate(table_string *ts) {
  //assuming each linked list is 1 node
  for (int i = 0; i<ts->buckets; i++){
    if (ts->heads[i]->value != NULL){
      free(ts->heads[i]->lines); 
      free(ts->heads[i]->value);
      free(ts->heads[i]->next); 
      free(ts->heads[i]);
    }

    else {
      free(ts->heads[i]->lines); 
      free(ts->heads[i]); 
    }
  }
  free(ts->heads);
  free(ts); 
  // TODO:
  // Free the linked list of each bucket
  // Free the array of head pointers
  // Free the structure itself
  return;
}

void table_string_print(table_string *ts) {
  for (int i = 0; i<ts->buckets;i++){
    vs_entry_t* entry = ts->heads[i];

    while (entry != NULL){
      if (entry->value != NULL){
        printf("%s:", entry->value);
        for (int n = 0; n<entry->size_of_lines; n++){
          printf(" %d", entry->lines[n]);
        }
        printf("\n");
      }
      entry = entry->next; 
    }
  }
  /** TODO:
   for each bucket
    for each entry in bucket
      print entry->word: line line line
  */
}
