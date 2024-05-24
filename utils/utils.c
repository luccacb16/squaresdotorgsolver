#include "utils.h"

FILE *abrirArquivo(char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "w");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    return file;
}

void salvarPalavra(FILE *file, char *palavra, Pos *posicoes, int length) {
    fprintf(file, "%s | ", palavra);
    for (int j = 0; j < length; j++) {
        fprintf(file, "(%d, %d)", posicoes[j].x, posicoes[j].y);
        if (j < length - 1) {
            fprintf(file, " -> ");
        }
    }
    fprintf(file, "\n");
}