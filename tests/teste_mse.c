#include "MSE.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-6

static int quase_igual(double a, double b) {
    return fabs(a - b) < EPSILON;
}

void testar_caminho_normal() {
    double real[] = {10.0, 20.0, 30.0};
    double pred[] = {12.0, 19.0, 27.0};
    // Diferencas: -2, 1, 3 -> Quadrados: 4, 1, 9 -> Soma (SSE) = 14.0 -> MSE = 14/3 = 4.666667

    double sse = calcular_sse(real, pred, 3);
    double mse = calcular_mse(real, pred, 3);
    double rmse = calcular_rmse(real, pred, 3);

    assert(quase_igual(sse, 14.0));
    assert(quase_igual(mse, 14.0 / 3.0));
    assert(quase_igual(rmse, sqrt(14.0 / 3.0)));
    printf("[OK] MSE - Caminho normal\n");
}

void testar_valores_limite() {
    // Predicao perfeita (erro zero) e vetor de tamanho 1
    double real[] = {5.5};
    double pred[] = {5.5};

    assert(quase_igual(calcular_sse(real, pred, 1), 0.0));
    assert(quase_igual(calcular_mse(real, pred, 1), 0.0));
    assert(quase_igual(calcular_rmse(real, pred, 1), 0.0));
    printf("[OK] MSE - Valores limite (erro zero e n=1)\n");
}

void testar_entradas_invalidas() {
    double vetor[] = {1.0, 2.0};

    // Ponteiros nulos
    assert(calcular_sse(NULL, vetor, 2) == -1.0);
    assert(calcular_mse(vetor, NULL, 2) == -1.0);
    assert(calcular_rmse(NULL, NULL, 2) == -1.0);

    // Tamanho n <= 0
    assert(calcular_mse(vetor, vetor, 0) == -1.0);
    assert(calcular_mse(vetor, vetor, -5) == -1.0);

    // Matriz nula ou colunas invalidas
    assert(calcular_mse_matriz(NULL, 0, 1) == -1.0);
    printf("[OK] MSE - Entradas nulas e invalidas\n");
}

void testar_mse_matriz() {
    // Simula uma matriz 2x2 como a gerada pelo IO.h
    matriz m;
    m.l = 2;
    m.c = 2;
    m.data = malloc(2 * sizeof(double *));
    for (int i = 0; i < 2; i++) {
        m.data[i] = malloc(2 * sizeof(double));
    }
    // Linha 0: real = 2.0, pred = 4.0 (erro^2 = 4.0)
    m.data[0][0] = 2.0;
    m.data[0][1] = 4.0;
    // Linha 1: real = 5.0, pred = 1.0 (erro^2 = 16.0)
    m.data[1][0] = 5.0;
    m.data[1][1] = 1.0;

    // MSE esperado = (4.0 + 16.0) / 2 = 10.0
    assert(quase_igual(calcular_mse_matriz(&m, 0, 1), 10.0));
    // Coluna fora do limite deve retornar -1.0
    assert(calcular_mse_matriz(&m, 0, 5) == -1.0);

    for (int i = 0; i < 2; i++) free(m.data[i]);
    free(m.data);
    printf("[OK] MSE - Calculo direto da struct matriz\n");
}

int main() {
    printf("=== Iniciando testes do modulo MSE ===\n");
    testar_caminho_normal();
    testar_valores_limite();
    testar_entradas_invalidas();
    testar_mse_matriz();
    printf("=== Todos os testes do MSE passaram com sucesso! ===\n");
    return 0;
}
