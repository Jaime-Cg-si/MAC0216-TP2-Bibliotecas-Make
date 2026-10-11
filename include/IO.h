#ifndef IO_H
#define IO_H

typedef struct matriz {
    //c = quantidade de colunas. l = quantidade de linha
    double ** data;
    int l;
    int c;
}matriz;

matriz * carregar_csv(const char * path, int l, int c);


#endif
