#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Pos;

FILE *abrirArquivo(char *nome_arquivo);
void salvarPalavra(FILE *file, char *palavra, Pos *posicoes, int length);

#endif // UTILS_H