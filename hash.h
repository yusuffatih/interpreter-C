#ifndef HASH_H
#define HASH_H

#define CAPACITY 16 // first capacity

typedef char *Key;
typedef char *Value;

typedef struct H_Value {
    Key key;
    Value value;
} H_Value;

typedef struct H_Table {
    char **values;
    char **keys;
    int count;
    int capacity;
} H_Table;

void initH_Table(H_Table *table);
void endH_Table(H_Table *table);
void growCapacity(H_Table *table);
void set(H_Value hval, H_Table *table);
char *get(Key key, H_Table *table);
unsigned int hash(Key key, H_Table *table);
int hasH_Table(Key key, H_Table *table);

#endif
