#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hunspell/hunspell.h>

#include "utils/hashtable.h"
#include "utils/utils.h"

void DFS(Hunhandle *spell_checker, HashTable *ht, FILE *file, char letras[4][4], int length, char visitados[4][4], int row, int col, int index, char *palavra_atual, Pos *posicao_atual, int *log) {
    if (row < 0 || row >= 4 || col < 0 || col >= 4) return;
    if (visitados[row][col]) return;
    if (index >= length) return;

    palavra_atual[index] = letras[row][col];
    posicao_atual[index].x = row;
    posicao_atual[index].y = col;
    visitados[row][col] = 1;

    if (index == length - 1) {
        palavra_atual[index + 1] = '\0';
        if (Hunspell_spell(spell_checker, palavra_atual) && !check(ht, palavra_atual)) {
            add(ht, palavra_atual);
            salvarPalavra(file, palavra_atual, posicao_atual, length);
            log[length-4]++;
        }
    } else {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    DFS(spell_checker, ht, file, letras, length, visitados, row + i, col + j, index + 1, palavra_atual, posicao_atual, log);
                }
            }
        }
    }

    visitados[row][col] = 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <max_tam> <letras> <arquivo de saída>\n", argv[0]);
        return 1;
    }

    int max_tam = atoi(argv[1]);
    if (strlen(argv[2]) != 16) {
        fprintf(stderr, "Erro: letras deve conter exatamente 16 caracteres\n");
        return 1;
    }

    FILE *file = abrirArquivo(argv[3]);
    HashTable *ht = init(5000);
    Hunhandle *spell_checker = Hunspell_create("/usr/share/hunspell/en_US.aff", "/usr/share/hunspell/en_US.dic");
    if (!spell_checker) {
        printf("Erro ao criar o spell checker\n");
        return 1;
    }

    char letras[4][4];
    char visitados[4][4] = {0};

    char palavra_atual[max_tam + 1];
    Pos posicao_atual[max_tam];

    int *log = (int *) calloc(max_tam-3, sizeof(int));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            letras[i][j] = argv[2][i * 4 + j];
        }
    }

    // Solver
    for (int length = 4; length <= max_tam; length++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                memset(visitados, 0, sizeof(visitados)); // Reinicializa a matriz de visitados para cada chamada
                DFS(spell_checker, ht, file, letras, length, visitados, i, j, 0, palavra_atual, posicao_atual, log);
            }
        }
    }

    // Resultados
    int total_palavras = 0;
    for (int i = 0; i < max_tam-3; i++) {
        printf("%d letras: %d\n", i+4, log[i]);
        total_palavras += log[i];
    }
    printf("\nTotal: %d\n", total_palavras);

    // Liberar memória e fechar arquivo
    fclose(file);
    Hunspell_destroy(spell_checker);
    freeHashTable(ht);
    free(log);

    return 0;
}
