#ifndef MSE_H
#define MSE_H

#include "IO.h"

/**
 * @brief Calcula a Soma dos Erros Quadraticos (SSE - Sum of Squared Errors).
 *
 * Calcula o somatorio de (y_real[i] - y_pred[i])^2 para i de 0 ate n-1.
 *
 * @param y_real Ponteiro para o vetor com os valores reais (observados).
 * @param y_pred Ponteiro para o vetor com os valores preditos pelo modelo.
 * @param n Quantidade de elementos nos vetores (deve ser > 0).
 * @return double Valor do SSE (>= 0.0), ou -1.0 em caso de erro (ponteiros NULL ou n <= 0).
 */
double calcular_sse(const double *y_real, const double *y_pred, int n);

/**
 * @brief Calcula o Erro Quadratico Medio (MSE - Mean Squared Error) entre dois vetores.
 *
 * Calcula a media aritmetica dos quadrados das diferencas entre os valores reais
 * e os valores preditos: (1/n) * somatorio((y_real[i] - y_pred[i])^2).
 *
 * @param y_real Ponteiro para o vetor com os valores reais (observados).
 * @param y_pred Ponteiro para o vetor com os valores preditos pelo modelo.
 * @param n Quantidade de elementos nos vetores (deve ser > 0).
 * @return double Valor do MSE (>= 0.0), ou -1.0 em caso de erro (ponteiros NULL ou n <= 0).
 */
double calcular_mse(const double *y_real, const double *y_pred, int n);

/**
 * @brief Calcula a Raiz do Erro Quadratico Medio (RMSE - Root Mean Squared Error).
 *
 * Calcula a raiz quadrada do MSE, retornando a metrica de erro na mesma unidade
 * dos dados originais.
 *
 * @param y_real Ponteiro para o vetor com os valores reais (observados).
 * @param y_pred Ponteiro para o vetor com os valores preditos pelo modelo.
 * @param n Quantidade de elementos nos vetores (deve ser > 0).
 * @return double Valor do RMSE (>= 0.0), ou -1.0 em caso de erro (ponteiros NULL ou n <= 0).
 */
double calcular_rmse(const double *y_real, const double *y_pred, int n);

/**
 * @brief Calcula o Erro Quadratico Medio (MSE) diretamente a partir de uma struct matriz.
 *
 * Percorre todas as linhas da matriz 'm' comparando os valores da coluna 'col_real'
 * com os valores da coluna 'col_pred'. Ideal para uso direto apos carregar_csv().
 *
 * @param m Ponteiro para a struct matriz carregada via IO.h.
 * @param col_real Indice da coluna que contem os valores reais (0 <= col_real < m->c).
 * @param col_pred Indice da coluna que contem os valores preditos (0 <= col_pred < m->c).
 * @return double Valor do MSE (>= 0.0), ou -1.0 em caso de erro (matriz nula, dados nulos,
 *         dimensoes invalidas ou indices de coluna fora dos limites).
 */
double calcular_mse_matriz(const matriz *m, int col_real, int col_pred);

#endif // MSE_H
