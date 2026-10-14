#include "KNN.h"
#include "IO.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argv, char * argc[]) {
    matriz * m = carregar_csv("exemplos/a.csv", 5, 3);

    knn * a = carregar_knn(m);
    sample * x = malloc(sizeof(sample));
    x->features = malloc(2*sizeof(double));
    x->features[0] = 15.2;
    x->features[1] = 0.2;
    printf("CLASSE: %d\n", rodar_knn(a,x, 2 ));
    return 0;

}
