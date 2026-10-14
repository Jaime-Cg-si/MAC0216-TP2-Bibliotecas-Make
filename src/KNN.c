#include "KNN.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"


knn * carregar_knn(matriz * m) {
    if (m == NULL || m->data == NULL) return NULL;

    knn * k = malloc(sizeof(knn));
    k->n_features = m->c - 1;
    k->n_samples = m->l;
    k->num_classes = k->n_samples; //ISSO É PROVISORIO!
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
//funcao usada no qsort
int comparar(const void *a, const void *b) {
    k_vizinho *ia = (k_vizinho *)a;
    k_vizinho *ib = (k_vizinho *)b;

    if (ia->dist > ib->dist) return 1;
    if (ia->dist < ib->dist) return -1;
    return 0;
}

int rodar_knn(knn * v, sample * sample_wo_class, int k) {

    k_vizinho * k_distancia = malloc(v->n_samples * sizeof(k_vizinho));

    for (int i = 0; i < v->n_samples; i++) {
        k_distancia[i].idx = i;

        //calcula a distancia euclidiana normalizada
        double dist = 0.0;
        for (int j = 0; j < v->n_features; j++) {
            double max = v->max_feature[j];
            double min = v->min_feature[j];

            if (v->max_feature[j] < sample_wo_class->features[j]) {
                max = sample_wo_class->features[j];
            }

            if (v->min_feature[j] > sample_wo_class->features[j]) {
                min = sample_wo_class->features[j];
            }
            // normalizacao das j-esima features das amostras do dataset e da amostra sem classe
            double v_sample_norm = 0.0;
            double sample_wo_norm = 0.0;

            if (max != min) {
            v_sample_norm = (v->samples[i]->features[j] - min)/ (max - min);
            sample_wo_norm = (sample_wo_class->features[j] - min)/ (max - min);
            }

            dist += (v_sample_norm - sample_wo_norm) * (v_sample_norm - sample_wo_norm);
        }

        dist = sqrt(dist);

        k_distancia[i].dist = dist;
    }

    qsort(k_distancia, v->n_samples, sizeof(k_vizinho), comparar);


    int num_classes = v->num_classes;
    int *qtd_classes = calloc(num_classes, sizeof(int));


    for (int i = 0; i < k; i++) {
        int idx = k_distancia[i].idx;
        int classe_da_amostra = v->samples[idx]->classe;
        qtd_classes[classe_da_amostra]++;
    }


    int classe_vencedora = 0;
    for (int c = 1; c < num_classes; c++) {
        if (qtd_classes[c] > qtd_classes[classe_vencedora]) {
            classe_vencedora = c;
        }
    }

    return classe_vencedora;
}
