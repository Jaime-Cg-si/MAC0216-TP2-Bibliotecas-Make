#include "../include/KNN.h"
#include "../include/IO.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



knn * carregar_knn(matriz * m) {
    if (m == NULL || m->data == NULL) return NULL;

    knn * k = malloc(sizeof(knn));
    k->n_features = m->c - 1;
    k->n_samples = m->l;

    k->max_feature = malloc(k->n_features * sizeof(double));
    k->min_feature = malloc(k->n_features * sizeof(double));

    k->samples = malloc(k->n_samples * sizeof(sample *));

    // define todos os elementos de max_feature e min_feature como o valor maximo e minimo possivel para double respectivamente
    for (int i = 0; i < k->n_features; i++) {
        k->max_feature[i] = DBL_MIN;
        k->min_feature[i] = DBL_MAX;

    }

    // atribuicao da j-esima feature e classe na i-esima amostra
    for (int i = 0; i < k->n_samples; i++) {
        k->samples[i] = malloc(sizeof(sample));
        k->samples[i]->features = malloc(k->n_features * sizeof(double));

        for (int j = 0; j < k->n_features; j++) {
            k->samples[i]->features[j] = m->data[i][j];
            k->samples[i]->classe = (int)m->data[i][k->n_features];

            if (k->max_feature[j] < k->samples[i]->features[j]) {
                k->max_feature[j] = k->samples[i]->features[j];
            }

            if (k->min_feature[j] > k->samples[i]->features[j]) {
                k->min_feature[j] = k->samples[i]->features[j];
            }
        }
    }


    return k;
}
int rodar_knn(knn * v, sample sample_wo_class, int k) {
    return 0;
}
