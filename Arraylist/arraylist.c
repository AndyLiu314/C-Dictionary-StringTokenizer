
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "arraylist.h"

////////////////////////////////////////////////////////////////////////////////
//Functions that you need to implement:

/*
 * Append the value x to the end of the arraylist. If necessary, double the
 * capacity of the arraylist.
 */
void arraylist_add(arraylist *a, void *x)
{
    if (a!=NULL && x!=NULL){
        if (a->length >= a->buffer_size) {
            //this is to resize the arraylist and double its buffer
            void** temp = realloc(a->buffer, 2*a->buffer_size);
            temp = a->buffer; 
            a->buffer_size = 2*a->buffer_size; 
        }
        a->buffer[a->length] = x;
        a->length++;
    }
}

/*
 * Store x at the specified index of the arraylist. Previously stored values
 * should be moved back rather than overwritten. It is undefined behavior to
 * insert an element with an index beyond the end of an arraylist.
 */
void arraylist_insert(arraylist *a, unsigned int index, void *x)
{
    memmove(&a->buffer[index+1], &a->buffer[index], (a->length-index)*sizeof(a->buffer));
    a->buffer[index] = x;
    a->length++;
}

/*
 * Free any memory used by that arraylist.
 */
void arraylist_free(arraylist *a)
{
    // Hint: How many times is malloc called when creating a new arraylist?
    // TODO
    free(a->buffer);
    free(a);
    a == NULL;
    return; 

}

////////////////////////////////////////////////////////////////////////////////

arraylist *arraylist_new()
{
    arraylist *a = (arraylist *)malloc(sizeof(arraylist));
    a->buffer = (void **)malloc(4 * sizeof(void *));
    a->buffer_size = 4;
    a->length = 0;

    return a;
}

void arraylist_remove(arraylist *a, unsigned int index)
{
    for (unsigned int i = index; i < a->length - 1; i++)
        a->buffer[i] = a->buffer[i + 1];

    --a->length;
}

void *arraylist_get(arraylist *a, unsigned int index)
{
    return a->buffer[index];
}

void arraylist_print(arraylist *a)
{
    printf("[");
    if (a->length > 0)
    {
        for (unsigned int i = 0; i < a->length - 1; i++)
            printf("%d, ", *(int *)arraylist_get(a, i));
        printf("%d", *(int *)arraylist_get(a, a->length - 1));
    }

    printf("]\n");
}

void arraylist_output(arraylist *a, char *output, int *pos)
{
    int index = 0;
    sprintf(output + *pos, "[");
    ++*pos;
    if (a->length > 0)
    {
        for (unsigned int i = 0; i < a->length - 1; i++)
        {
            index = sprintf(output + *pos, "%d, ", *(int *)arraylist_get(a, i));
            (*pos) = (*pos) + index;
        }
        index = sprintf(output + *pos, "%d", *(int *)arraylist_get(a, a->length - 1));
        (*pos) = (*pos) + index;
    }
    sprintf(output + *pos, "]\n");
    (*pos) = (*pos) + 2;
}
