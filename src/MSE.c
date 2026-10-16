#include "MSE.h"
#include <math.h>
#include <stddef.h>

static int validar_vetores(const double *y_real, const double *y_pred, int n) {
    if (y_real == NULL || y_pred == NULL || n <= 0) {
        return 0;
    }
    return 1;
}

static int validar_matriz_colunas(const matriz *m, int col_real, int col_pred) {
    if (m == NULL || m->data == NULL) {
        return 0;
    }
    if (m->l <= 0 || m->c <= 0) {
        return 0;
    }
    if (col_real < 0 || col_real >= m->c || col_pred < 0 || col_pred >= m->c) {
        return 0;
    }
    return 1;
}

double calcular_sse(const double *y_real, const double *y_pred, int n) {
    if (!validar_vetores(y_real, y_pred, n)) {
        return -1.0;
    }

    double soma = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = y_real[i] - y_pred[i];
        soma += diff * diff;
    }

    return soma;
}

double calcular_mse(const double *y_real, const double *y_pred, int n) {
    double sse = calcular_sse(y_real, y_pred, n);
    if (sse < 0.0) {
        return -1.0;
    }

    return sse;
}

double calcular_rmse(const double *y_real, const double *y_pred, int n) {
    double mse = calcular_mse(y_real, y_pred, n);
    if (mse < 0.0) {
        return -1.0;
    }

    return sqrt(mse);
}

double calcular_mse_matriz(const matriz *m, int col_real, int col_pred) {
    if (!validar_matriz_colunas(m, col_real, col_pred)) {
        return -1.0;
    }

    double soma = 0.0;
    for (int i = 0; i < m->l; i++) {
        if (m->data[i] == NULL) {
            return -1.0;
        }
        double diff = m->data[i][col_real] - m->data[i][col_pred];
        soma += diff * diff;
    }

    return soma / (double)(m->l);
}
