#ifndef KNN_H
#define KNN_H

/* FUNCIONAMENTO DO KNN
 *
 * knn *base = carregar_csv("dados.csv");
 * Sample nova = ler_amostra_nova();
 * int classe = run(base, nova, k);
 * printf("%d\n", classe);
 */

#include "IO.h"
typedef struct sample {
    int classe;
    double *features;
}sample;

typedef struct knn {

    int n_samples;
    int n_features;
    sample **samples;
    //esses arrays servem para armazenar o maior e menor valor da i-esima feature, para que depois seja feita a normalizacao do valor
    double *max_feature;
    double *min_feature;
}knn;


/**
 * @brief Carrega uma matriz e retorna um KNN com amostras.
 *
 * Compila uma matriz considerando cada linha como uma amostra e cada coluna como feature. A ultima coluna representa a classe da amostra.
 *
 * @param m Matriz carregada com amostras.
 * @return Ponteiro para o knn carregado com amostras.
 */
knn * carregar_knn(matriz * m);


/**
 * @brief Retorna a classe de uma amostra usando o KNN.
 *
 * Calcula a distancia (euclidiana) entre cada amostra, avalia a classe das que estao mais proximas e atribui a classe predominante à amostra avaliada.
 *
 * @param v KNN com as amostras carregadas.
 * @param sample_wo_class amostra sem classe a ser classificada.
 * @param k o 'k' de KNN, ou seja, a quantidade de vizinhos avaliado.
 * @return Classe da amostra sem classe.
 */
int rodar_knn(knn * v, sample sample_wo_class, int k);



#endif
