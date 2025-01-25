#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// This hash table implementation does not have deleting! If you fullfill an index it will always be full and will not be able to reuse!

static void resetMem(H_Table *table, size_t start, size_t end) {
    for (int i = start; i < end; i++) {
        table->values[i] = NULL;
        table->keys[i] = NULL;
    }
}

int hasH_Table(Key key, H_Table *table) {
    unsigned int idx = hash(key, table);
    
    if(idx < table->capacity) {
        if(table->values[idx] != NULL && !strcmp(table->keys[idx], key)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        printf("INDEX OUT OF RANGE ERROR!");
        exit(1);
    }
}

void initH_Table(H_Table *table) {
    table->values = (Value *)malloc(sizeof(Value) * CAPACITY);
    table->keys = (Key *)malloc(sizeof(Key) * CAPACITY);
    if (table->values == NULL || table->keys == NULL) {
        printf("MALLOC ERROR OCCURED");
        exit(1);
    }
    table->count = 0;
    table->capacity = CAPACITY;
    resetMem(table, table->count, table->capacity);
}

void endH_Table(H_Table *table) {

    // TODO !

    for (int i = 0; i < table->capacity; i++) {
        if(table->values[i] != NULL) {
            free(table->values[i]); 
        }
    }
    free(table->values);
    free(table->keys);
}

unsigned int hash(Key key, H_Table *table) {
    //djb2 algo
    unsigned long hash = 5381; 
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % table->capacity;
}

void set(H_Value hval, H_Table *table) {
    unsigned int idx = hash(hval.key, table);
    if (idx < table->capacity) {
        growCapacity(table);
        table->count += 1;
        table->values[idx] = hval.value;
        table->keys[idx] = hval.key;
    } else {
        printf("INDEX OUT OF RANGE ERROR!");
        exit(1);
    }
}

char *get(Key key, H_Table *table) {
    unsigned int idx = hash(key, table);

    if(idx < table->capacity) {
        return (table->values[idx]); 
    } else {
        printf("INDEX OUT OF RANGE ERROR!");
        exit(1);
    }
}

void growCapacity(H_Table *table) {

    float loadFactor = ((float)table->count / table->capacity);

    if(loadFactor >= 0.7) {
        table->values = (Value *)realloc(table->values, sizeof(Value) * table->capacity * 2);

        table->keys = (Key *)realloc(table->keys, sizeof(Key) * table->capacity * 2);

        if (table->values == NULL || table->keys == NULL) {
            printf("MALLOC ERROR OCCURED!");
            exit(1);
        }
        resetMem(table, table->capacity, (table->capacity * 2));
        table->capacity *= 2;
    }   
}













