#include "cli.h"
#include "MSE.h"
#include "IO.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define OPCAO_KNN 1
#define OPCAO_MSE 2

static const int OPCOES_FUNCIONALIDADES[] = {OPCAO_SAIDA_PROGRAMA, OPCAO_KNN, OPCAO_MSE};
static const int TAMANHO_VETOR_FUNCIONALIDADES = sizeof(OPCOES_FUNCIONALIDADES) / sizeof(OPCOES_FUNCIONALIDADES[0]);

static void exibir_separador(char car){
    for (int i = 0; i < 20; i++){
        printf("%c", car);
    }
    printf("\n");
}

static void exibir_texto_input(){
    printf(">>Insira o número correspondente à funcionalidade desejada: ");
}

static void exibir_funcionalidades_no_terminal(){
    printf(">>Para executar uma ação, digite o número correspondente.\n");
    printf("%d.\tKNN (K-Nearest Neighbours)\n", OPCAO_KNN);
    printf("%d.\tMSE (Mean Squared Error)\n", OPCAO_MSE);
    printf("%d.\tSair do programa\n", OPCAO_SAIDA_PROGRAMA);
}

static void limpar_buffer_input(){
    int caracter = getchar();

    while (caracter != '\n' && caracter != EOF){
        caracter = getchar();
    }
}

static void executar_fluxo_mse(){
    char caminho[256];
    int linhas, colunas, col_real, col_pred;

    printf("Digite o caminho do arquivo CSV (ex: exemplos/a.csv): ");
    if (scanf("%255s", caminho) != 1) {
        limpar_buffer_input();
        return;
    }
    printf("Digite a quantidade de linhas e colunas do CSV (ex: 5 3): ");
    if (scanf("%d %d", &linhas, &colunas) != 2) {
        limpar_buffer_input();
        return;
    }
    printf("Digite o indice da coluna real e da coluna predita (ex: 0 1): ");
    if (scanf("%d %d", &col_real, &col_pred) != 2) {
        limpar_buffer_input();
        return;
    }
    limpar_buffer_input();

    matriz *m = carregar_csv(caminho, linhas, colunas);
    if (m == NULL) {
        printf("Erro ao carregar o arquivo CSV.\n");
        return;
    }

    double mse = calcular_mse_matriz(m, col_real, col_pred);
    if (mse < 0.0) {
        printf("Erro ao calcular o MSE (verifique os indices das colunas).\n");
    } else {
        printf("Resultado do MSE: %.6f\n", mse);
    }

    // Libera a memoria alocada pela matriz
    if (m->data != NULL) {
        for (int i = 0; i < m->l; i++) {
            free(m->data[i]);
        }
        free(m->data);
    }
    free(m);
}

int parsear_escolha_funcionalidade_usuario(const int* opcoes_funcionalidades_validas, const int tamanho_vetor_funcionalidades){

    if (tamanho_vetor_funcionalidades <= 0 || opcoes_funcionalidades_validas == NULL){
        return OPCAO_SAIDA_PROGRAMA;
    }

    int resposta_usuario = 0;

    int itens_lidos;
    do{
        exibir_texto_input();
        itens_lidos = scanf("%d", &resposta_usuario);
        if (itens_lidos == EOF){
            return OPCAO_SAIDA_PROGRAMA;
        }

        limpar_buffer_input();
    }while(itens_lidos == 0 || validar_escolha_funcionalidade(resposta_usuario, opcoes_funcionalidades_validas, 
    tamanho_vetor_funcionalidades) == false );

    return resposta_usuario;
}

void cli_run(){

    //Apresentação do programa
    exibir_separador('$');
    printf("\tPROGRAMA DE MACHINE LEARNING\n");
    exibir_separador('$');
    exibir_funcionalidades_no_terminal();
    exibir_separador('#');

    int resposta_usuario = parsear_escolha_funcionalidade_usuario(OPCOES_FUNCIONALIDADES, TAMANHO_VETOR_FUNCIONALIDADES);

    //loop principal
    while (resposta_usuario != OPCAO_SAIDA_PROGRAMA){
        if (resposta_usuario == OPCAO_MSE) {
            executar_fluxo_mse();
        }
        exibir_separador('#');
        exibir_funcionalidades_no_terminal();
        resposta_usuario = parsear_escolha_funcionalidade_usuario(OPCOES_FUNCIONALIDADES, TAMANHO_VETOR_FUNCIONALIDADES);
    }
}

bool validar_escolha_funcionalidade(int opcao_funcionalidade_escolhida, const int* opcoes_funcionalidades_validas, int tamanho_vetor_funcionalidades){

    if (tamanho_vetor_funcionalidades <= 0 || opcoes_funcionalidades_validas == NULL) return false;

    for (int i = 0; i < tamanho_vetor_funcionalidades; i++){
        if (opcao_funcionalidade_escolhida == opcoes_funcionalidades_validas[i]){
            return true;
        }
    }

    return false;
}
