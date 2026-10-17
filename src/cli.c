#include "cli.h"
#include <stdio.h>
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
