#ifndef KNN_H
#define KNN_H

/* FUNCIONAMENTO DO KNN
 *
 * knn *base = carregar_csv("dados.csv");
 * Sample nova = ler_amostra_nova();
 * int classe = run(base, nova, k);
 * printf("%d\n", classe);
 */

typedef struct sample {
    int classe;
    double *features;
}sample;

typedef struct knn {

    int n_samples;
    int n_features;
    sample *samples;
    //esses arrays servem para armazenar o maior e menor valor da i-esima feature, para que depois seja feita a normalizacao do valor
    double *max_feature;
    double *min_feature;
}knn;

knn * carregar_knn(double **, int n_samples, int n_features);

int run(knn * v, sample sample_wo_class, int k); //sample_wo_class = amostra sem classe



#endif
