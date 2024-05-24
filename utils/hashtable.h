#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char *palavra;
    int tam;
} Palavra;

typedef struct {
    Palavra *palavras;
    int tam;
} HashTable;

int hash_djb2(char *str, int tam);
HashTable *init(int tam);
void add(HashTable *ht, char *palavra);
int check(HashTable *ht, char *palavra);
void freeHashTable(HashTable *ht);

#endif // HASHTABLE_H
