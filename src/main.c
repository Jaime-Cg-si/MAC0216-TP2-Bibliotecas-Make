#include "../include/KNN.h"
#include "../include/IO.h"
#include <stdio.h>
int main(int argv, char * argc[]) {
    matriz * m = carregar_csv("build/a.csv", 2, 2);
    printf("%.2f", m->data[1][0]);
    return 0;
}
