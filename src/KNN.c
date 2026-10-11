#include "../include/KNN.h"
#include "../include/IO.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



knn * carregar_knn(matriz m){
    /**
     * @brief Carrega uma matriz e retorna um KNN com amostras.
     *
     * Compila uma matriz considerando cada linha como uma amostra e cada coluna como feature. A ultima coluna representa a classe da amostra.
     *
     * @param m Matriz carregada com amostras.
     * @return Ponteiro para o knn carregado com amostras.
     */
    return NULL;
}
int rodar_knn(knn * v, sample sample_wo_class, int k) {
    /**
     * @brief Retorna a classe de uma amostra usando o KNN.
     *
     * Calcula a distancia entre cada amostra, avalia a classe das que estao mais proximas e atribui a classe predominante à amostra avaliada.
     *
     * @param v KNN com as amostras carregadas.
     * @param sample_wo_class amostra sem classe a ser classificada.
     * @param k o 'k' de KNN, ou seja, a quantidade de vizinhos avaliado.
     * @return Classe da amostra sem classe.
     */


    return 0;
}
