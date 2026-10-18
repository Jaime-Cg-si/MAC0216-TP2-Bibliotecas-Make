#include "cli.h"
#include "IO.h"
#include "MSE.h"
#include "KNN.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define OPCAO_KNN 1
#define OPCAO_MSE 2

static const int OPCOES_FUNCIONALIDADES[] = {OPCAO_SAIDA_PROGRAMA, OPCAO_KNN, OPCAO_MSE};
static const int TAMANHO_VETOR_FUNCIONALIDADES = sizeof(OPCOES_FUNCIONALIDADES) / sizeof(OPCOES_FUNCIONALIDADES[0]);

/**
* @brief função auxiliar que exibe uma série de caracteres para separar o bloco de texto
* @param car: char que corresponde ao caracter a ser impresso
* @post printa 20x o caracter parâmetro e quebra a linha
*/
static void exibir_separador(char car){
    for (int i = 0; i < 20; i++){
        printf("%c", car);
    }
    printf("\n");
}

/**
* @brief    função auxiliar que exibe o comando para o usuário inserir o input
* @post     printa ">>Insira o número correspondete à funcionalidade desejada: " e não quebra linha
* @note     Não quebra a linha para que o usuário insira a opção ao lado do texto.
*/
static void exibir_texto_input(){
    printf(">>Insira o número correspondente à funcionalidade desejada: ");
}

/**
* @brief    Apresenta todas as opções de ação que o usuário pode tomar
* @post     Printa, no terminal, o índice das ações e como invocá-las. A função já lida com os "\\n"
* @note     Apenas exibe as funções, não é capaz de parsear a opção
* @warning  Deve ser atualizada sempre que uma nova funcionalidade é adicionada ao projeto
*/
static void exibir_funcionalidades_no_terminal(){

    printf(">>Para executar uma ação, digite o número correspondente.\n");
    printf("%d.\tKNN (K-Nearest Neighbours)\n", OPCAO_KNN);
    printf("%d.\tMSE (Mean Squared Error)\n", OPCAO_MSE);
    printf("%d.\tSair do programa\n", OPCAO_SAIDA_PROGRAMA);

}

/**
* @brief    Função auxiliar que limpa o buffer de entrada, para garantir a validez do input.
* @note     Consome todos os caracteres até encontrar o '\n' ou EOF
*/
static void limpar_buffer_input(){
    int caracter = getchar();

    while (caracter != '\n' && caracter != EOF){
        caracter = getchar();
    }
}

/**
* @brief    Função auxiliar que recebe um inteiro da stdin.
* @param    resposta: ponteiro para inteiro que corresponde ao inteiro lido.
* @param    mensagem_exibida: string que corresponde à mensagem exibida na stdout.
* @return   true caso tenha lido um inteiro. False caso o arquivo tenha acabado.
* @note     A função guarda o valor lido por meio do ponteiro resposta.
* @note     Repete o processo até o arquivo acabar ou ler um inteiro.
*/
static bool ler_inteiro(int* resposta, const char* mensagem_exibida){
    int retorno_scanf = 1;
    do{
        printf("%s ", mensagem_exibida);
        retorno_scanf = scanf("%d", resposta);
        printf("\n");
        if (retorno_scanf == EOF){
            return false;
        }
        limpar_buffer_input();
    }while(retorno_scanf == 0);
    return true;
}

/**
* @brief    Função auxiliar que recebe um número real da stdin.
* @param    resposta: ponteiro para double que corresponde ao número real lido.
* @param    mensagem_exibida: string que corresponde à mensagem exibida na stdout.
* @return   true caso tenha lido um número real. False caso o arquivo tenha acabado.
* @note     A função guarda o valor lido por meio do ponteiro resposta.
* @note     Repete o processo até o arquivo acabar ou ler um número real.
*/
static bool ler_double(double* resposta, const char* mensagem_exibida){
    int retorno_scanf = 1;

    do{
        printf("%s ", mensagem_exibida);
        retorno_scanf = scanf("%lf", resposta);
        printf("\n");
        if (retorno_scanf == EOF){
            return false;
        }
        limpar_buffer_input();

    }while (retorno_scanf == 0);

    return true;
}

/**
* @brief    Função auxiliar que lê o caminho de um arquivo digitado pelo usuário.
* @param    caminho: vetor onde o caminho lido é armazenado, sem o '\n' final.
* @param    tamanho_caminho: número de posições do vetor caminho.
* @param    mensagem_exibida: texto da pergunta, exibido antes de cada tentativa (sem quebrar a linha).
* @return   true se um caminho não vazio foi lido; false se a entrada terminou (EOF).
* @note     Lê a linha inteira, então caminhos com espaços são aceitos.
* @note     Aceita caminhos de até tamanho_caminho - 2 caracteres. Caminhos maiores e linhas vazias
*           são recusados: o usuário é avisado e a pergunta se repete.
* @warning  Em caso de false, o conteúdo de caminho não deve ser usado.
*/
static bool ler_caminho_arquivo(char* caminho, int tamanho_caminho, const char* mensagem_exibida){
    char* retorno_fgets;

    while (true){

        printf("%s ", mensagem_exibida);
        retorno_fgets = fgets(caminho, tamanho_caminho, stdin);
        printf("\n");

        if (retorno_fgets == NULL){
            return false;
        }

        char* quebra_linha = strchr(caminho, '\n');
        if (quebra_linha != NULL){
            *quebra_linha = '\0';
        }
        else{
            limpar_buffer_input();
            if((int)strlen(caminho) == tamanho_caminho-1){
                printf("Caminho longo demais, digite novamente.\n");
                limpar_buffer_input();
                continue;
            }
        }
        if (caminho[0] == '\0'){
            printf("Caminho vazio, digite novamente.\n");
            continue;
        }
        return true;
    }
}

/**
* @brief    Função para desalocar memória de uma matriz
* @param    m: ponteiro para a matriz
*/
static void liberar_matriz(matriz* m){
    if (m == NULL) return;
    for (int i = 0; i < m->l; i++){
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

/** 
* @brief    Função que coordena todo o fluxo do MSE
*/
static void fluxo_mse(){

    // 1. Recebimento do CSV
    char caminho[256];
    char mensagem_csv[] = "Insira o caminho do arquivo CSV:";
    bool caminho_valido = ler_caminho_arquivo(caminho, sizeof(caminho), mensagem_csv);
    if (caminho_valido == false){
        printf("Erro no recebimento do caminho do arquivo. Voltando ao menu...\n");
        return;
    }

    // 2. Recebimento número de linhas
    int numero_linhas = 0;
    char mensagem_linha[] = "Insira o número de linhas:";
    bool num_lin_valido = ler_inteiro(&numero_linhas, mensagem_linha);
    if (num_lin_valido == false){
        printf("Erro no recebimento do número de linhas. Voltando ao menu...\n");
        return;
    }
    while (numero_linhas <= 0){
        printf("Número de linhas não pode ser <= 0.\n");
        num_lin_valido = ler_inteiro(&numero_linhas, mensagem_linha);
        if (num_lin_valido == false){
        printf("Erro no recebimento do número de linhas. Voltando ao menu...\n");
        return;
    }
    }

    // 3. Recebendo número de colunas
    int numero_colunas = 0;
    char mensagem_coluna[] = "Insira o número de colunas:";
    bool num_col_valido = ler_inteiro(&numero_colunas, mensagem_coluna);
    if (num_col_valido == false){
        printf("Erro no recebimento do número de colunas. Voltando ao menu...\n");
        return;
    }
    while (numero_colunas <= 0){
        printf("Número de colunas não pode ser <= 0.\n");
        num_col_valido = ler_inteiro(&numero_colunas, mensagem_coluna);
        if (num_col_valido == false){
        printf("Erro no recebimento do número de colunas. Voltando ao menu...\n");
        return;
    }
    }

    // 4. Coluna com os valores observador
    int numero_coluna_observacao = 0;
    char mensagem_coluna_observacao[] = "Insira qual a coluna dos valores reais:";
    bool num_col_obs = ler_inteiro(&numero_coluna_observacao, mensagem_coluna_observacao);
    if (num_col_obs == false){
        printf("Erro no recebimento do índice da coluna dos valores reais. Voltando ao menu...\n");
        return;
    }

    // 5. Coluna com os valores preditivos
    int numero_coluna_previsao = 0;
    char mensagem_coluna_previsao[] = "Insira qual a coluna dos valores preditos:";
    bool num_col_predito = ler_inteiro(&numero_coluna_previsao, mensagem_coluna_previsao);
    if (num_col_predito == false){
        printf("Erro no recebimento do índice da coluna dos valores preditos. Voltando ao menu...\n");
        return;
    }

    // 6. Carregando CSV
    matriz* matriz_input = carregar_csv(caminho, numero_linhas, numero_colunas);

    if (matriz_input == NULL){
        printf("Erro ao carregar arquivo CSV. Voltando para o menu...\n");
        return;
    }

    // 7. Cálculo do MSE
    double resultado_mse = calcular_mse_matriz(matriz_input, numero_coluna_observacao, numero_coluna_previsao);
    if (resultado_mse < 0.0){
        printf("Erro ao calcular MSE. Voltando para o menu...\n");
        liberar_matriz(matriz_input);
        return;
    }

    // 8. Display do resultado
    printf("Resultado do MSE entre as colunas %d (valores reais) e %d (previsões): %.6f\n", numero_coluna_observacao, numero_coluna_previsao, resultado_mse);
    liberar_matriz(matriz_input);
}

/**
* @brief    Função para liberar memória de um knn
* @param    v: ponteiro para o knn
*/
static void liberar_knn(knn* v){
    if (v == NULL) return;

    if (v->samples != NULL){
        for (int i = 0; i < v->n_samples; i++){
            if (v->samples[i] != NULL){
                free(v->samples[i]->features);
                free(v->samples[i]);
            }
        }
        free(v->samples);
    }
    free(v->max_feature);
    free(v->min_feature);
    free(v);
}


/**
* @brief    Função que coordena todo o fluxo do KNN
*/
static void fluxo_knn(){
    //1. Receber arquivo
    char caminho[256];
    bool caminho_valido = ler_caminho_arquivo(caminho, sizeof(caminho), "Insira o caminho do arquivo CSV:");
    if (caminho_valido == false){
        printf("Erro ao receber caminho. Voltando ao menu...\n");
        return;
    }

    //2. Receber número linhas
    int numero_linhas;
    bool num_lin_valido = ler_inteiro(&numero_linhas,"Insira o número de linhas:");
    if (num_lin_valido == false){
        printf("Erro ao receber número de linhas. Voltando ao menu...\n");
        return;
    }
    while (numero_linhas <= 0){
        printf("Número de linhas inválido.\n");
        num_lin_valido = ler_inteiro(&numero_linhas, "Insira o número de linhas:");
        if (num_lin_valido == false){
        printf("Erro ao receber número de linhas. Voltando ao menu...\n");
        return;
        }
    }

    //3. Receber número colunas
    int numero_colunas;
    bool num_col_valido = ler_inteiro(&numero_colunas, "Insira o número de colunas:");
    if (num_col_valido == false){
        printf("Erro ao receber número de colunas. Voltando ao menu...\n");
        return;
    }
    while (numero_colunas <2){
        printf("Número inválido de colunas. Digite um valor >=2\n");
        num_col_valido = ler_inteiro(&numero_colunas, "Insira o número de colunas:");
        if (num_col_valido == false){
        printf("Erro ao receber número de colunas. Voltando ao menu...\n");
        return;
        }
    }

    //4. Carregar CSV
    matriz* matriz_input = carregar_csv(caminho, numero_linhas, numero_colunas);
    if (matriz_input == NULL){
        printf("Erro ao carregar arquivo CSV. Voltando ao menu...\n");
        return;
    }

    //5. Montar KNN
    knn* knn_input = carregar_knn(matriz_input);
    if (knn_input == NULL){
        printf("Erro ao carregar KNN. Voltando ao menu...\n");
        liberar_matriz(matriz_input);
        return;
    }

    //6. Liberar matriz
    liberar_matriz(matriz_input);

    //7. Receber k
    int k;
    bool k_valido = ler_inteiro(&k, "Insira o valor de k:");
    if (k_valido == false){
        printf("Erro ao receber valor de k. Voltando ao menu...\n");
        liberar_knn(knn_input);
        return;
    }
    while (k < 1 || k > knn_input->n_samples){
        printf("Número k inválido. Escolha um valor entre [1,%d].\n", knn_input->n_samples);
        k_valido = ler_inteiro(&k, "Insira o valor de k:");
        if (k_valido == false){
        printf("Erro ao receber valor de k. Voltando ao menu...\n");
        liberar_knn(knn_input);
        return;
        }
    }

    //8. Receber amostra nova
    sample amostra;
    amostra.classe = -1;
    amostra.features = malloc(knn_input->n_features * sizeof(double));
    if (amostra.features == NULL){
        printf("Erro ao alocar memória para a amostra. Voltando ao menu...\n");
        liberar_knn(knn_input);
        return;
    }

    char pergunta[64];
    for(int i = 0; i < knn_input->n_features; i++){
        snprintf(pergunta, sizeof(pergunta), "Valor da característica %d:", i+1);
        bool valor_lido = ler_double(&amostra.features[i], pergunta);
        if (valor_lido == false){
            printf("Erro ao receber a amostra. Voltando ao menu...\n");
            free(amostra.features);
            liberar_knn(knn_input);
            return;
        }
    }

    //9. Classificar a amostra
    int classe_prevista = rodar_knn(knn_input, &amostra, k);
    printf("Classe prevista para a amostra (k = %d): %d\n", k, classe_prevista);

    free(amostra.features);
    liberar_knn(knn_input);
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
        switch (resposta_usuario) {
            case OPCAO_KNN:
                fluxo_knn();
                break;
            case OPCAO_MSE:
                fluxo_mse();
                break;
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
