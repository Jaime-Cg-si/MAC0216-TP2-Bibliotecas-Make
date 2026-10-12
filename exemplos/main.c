#include "KNN.h"
#include "IO.h"
#include <stdio.h>

int main(int argv, char * argc[]) {
    matriz * m = carregar_csv("a.csv", 4, 3);
    printf("%d\n", m->l);

    knn * a = carregar_knn(m);
    printf("%.2f", a->max_feature[4]);

}
