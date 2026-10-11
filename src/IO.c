#include "../include/IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Carrega um arquivo CSV para uma matriz.
 *
 * Lê o arquivo especificado em 'path' e preenche uma matriz de doubles
 * com 'l' linhas e 'c' colunas. Assume que o arquivo tem exatamente
 * esse formato, sem cabeçalho.
 *
 * @param path Caminho do arquivo CSV.
 * @param l Número de linhas da matriz.
 * @param c Número de colunas da matriz.
 * @return Ponteiro para a struct matriz preenchida, ou NULL em caso de erro.
 */

matriz * carregar_csv(const char * path, int l, int c) {

    matriz * m = malloc(sizeof(matriz));

    double **dados = malloc(l * sizeof(double *));

    for (int i = 0; i < l; i++) dados[i] = malloc((c * sizeof(double)));

    m->c = c;
    m->l = l;

    FILE *f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "erro ao abrir %s\n", path);
        return NULL;
    }
    char linha[4096];

    for (int i = 0; i < l; i++) {
        if (!fgets(linha, sizeof linha, f)) break;

        char *tok = strtok(linha, ",\n\r");
        for (int j = 0; j < c; j++) {
            if (!tok) break;
            dados[i][j] = atof(tok);
            tok = strtok(NULL, ",\n\r");
        }
    }
    m->data = dados;
    return m;
}


