#include "cli.h"
#include <stdio.h>
#include <stdbool.h>


#define OPCAO_KNN 1
#define OPCAO_SAIDA_PROGRAMA -1


static const int OPCOES_FUNCIONALIDADES[] = {OPCAO_SAIDA_PROGRAMA, OPCAO_KNN};
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
    printf("%d.\tSair do programa\n", OPCAO_SAIDA_PROGRAMA);

}

int parsear_escolha_funcionalidade_usuario(const int* opcoes_funcionalidades_validas, const int tamanho_vetor_funcionalidades){

    if (tamanho_vetor_funcionalidades <= 0 || opcoes_funcionalidades_validas == NULL){
        return OPCAO_SAIDA_PROGRAMA;
    }

    int resposta_usuario = 0;

    do{
        exibir_texto_input();
        scanf("%d", &resposta_usuario);
    }while(validar_escolha_funcionalidade(resposta_usuario, opcoes_funcionalidades_validas, 
    tamanho_vetor_funcionalidades) == false);

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
