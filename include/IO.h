#ifndef IO_H
#define IO_H

typedef struct {
    //c = quantidade de colunas. l = quantidade de linha
    double ** data;
    int l;
    int c;
}matriz;

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

matriz * carregar_csv(const char * path, int l, int c);


#endif
