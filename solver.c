#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hunspell/hunspell.h>

void debug(int i) {
    printf("Debug %d\n", i);
}

typedef struct {
    int x;
    int y;
} Pos;

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

void DFS(Hunhandle *spell_checker, FILE *file, char letras[4][4], int length, char visitados[4][4], int row, int col, int index, char *palavra_atual, Pos *posicao_atual) {
    if (row < 0 || row >= 4 || col < 0 || col >= 4) return;
    if (visitados[row][col]) return;
    if (index >= length) return;

    palavra_atual[index] = letras[row][col];
    posicao_atual[index].x = row;
    posicao_atual[index].y = col;
    visitados[row][col] = 1;

    if (index == length - 1) {
        palavra_atual[index + 1] = '\0';
        if (Hunspell_spell(spell_checker, palavra_atual)) {
            salvarPalavra(file, palavra_atual, posicao_atual, length);
        }
    } else {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    DFS(spell_checker, file, letras, length, visitados, row + i, col + j, index + 1, palavra_atual, posicao_atual);
                }
            }
        }
    }

    visitados[row][col] = 0;
}

int main() {
    Hunhandle *spell_checker = Hunspell_create("/usr/share/hunspell/en_US.aff", "/usr/share/hunspell/en_US.dic");
    if (!spell_checker) {
        printf("Erro ao criar o spell checker\n");
        return 1;
    }

    FILE *file = abrirArquivo("validas.txt");

    int max_tam;
    char letras[4][4];

    printf("Tamanho máximo das palavras: ");
    scanf("%d", &max_tam);

    printf("Letras no board: ");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            scanf(" %c", &letras[i][j]);
        }
    }

    char visitados[4][4] = {0}; // Inicializa a matriz de visitados
    char palavra_atual[max_tam + 1];
    Pos posicao_atual[max_tam];

    for (int length = 4; length <= max_tam; length++) {
        // Realiza a DFS para validar e salvar palavras encontradas
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                memset(visitados, 0, sizeof(visitados)); // Reinicializa a matriz de visitados para cada chamada
                DFS(spell_checker, file, letras, length, visitados, i, j, 0, palavra_atual, posicao_atual);
            }
        }
    }

    fclose(file);
    Hunspell_destroy(spell_checker);

    return 0;
}
