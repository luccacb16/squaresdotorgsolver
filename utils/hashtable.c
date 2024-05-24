#include "hashtable.h"

int hash_djb2(char *str, int tam) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % tam;
}

HashTable *init(int tam) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    ht->tam = tam;
    ht->palavras = (Palavra *) malloc(tam * sizeof(Palavra));

    for (int i = 0; i < tam; i++) {
        ht->palavras[i].palavra = NULL;
        ht->palavras[i].tam = 0;
    }

    return ht;
}

void add(HashTable *ht, char *palavra) {
    int index = hash_djb2(palavra, ht->tam);

    if (ht->palavras[index].palavra == NULL) {
        ht->palavras[index].palavra = (char *) malloc((strlen(palavra) + 1) * sizeof(char));
        strcpy(ht->palavras[index].palavra, palavra);
        ht->palavras[index].tam = strlen(palavra);
    }
}

int check(HashTable *ht, char *palavra) {
    return ht->palavras[hash_djb2(palavra, ht->tam)].palavra != NULL;
}

void freeHashTable(HashTable *ht) {
    for (int i = 0; i < ht->tam; i++) {
        if (ht->palavras[i].palavra != NULL) {
            free(ht->palavras[i].palavra);
        }
    }

    free(ht->palavras);
    free(ht);
}
