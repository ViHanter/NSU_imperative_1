#include "myblas.h"

void dcopy(int n, const double *X, double *Y) {
    for (int i = 0; i < n; i++) Y[i] = X[i];
}

void dswap(int n, double *X, double *Y) {
    for (int i = 0; i < n; i++) {
        double t = X[i];
        X[i] = Y[i];
        Y[i] = t;
    }
}

void dscal(int n, double alpha, double *X) {
    for (int i = 0; i < n; i++) X[i] *= alpha;
}

void daxpy(int n, double alpha, const double *X, double *Y) {
    for (int i = 0; i < n; i++) Y[i] += alpha * X[i];
}

double ddot(int n, const double *X, const double *Y) {
    double s = 0.0;
    for (int i = 0; i < n; i++) s += X[i] * Y[i];
    return s;
}