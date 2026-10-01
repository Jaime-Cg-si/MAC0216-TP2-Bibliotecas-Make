#include "cli.h"
#include <stdio.h>

/**
* @brief função auxiliar que exibe uma série de #### para separar o bloco de texto
* @post printa #################### e quebra a linha
*/
static void exibir_separador(){
    for (int i = 0; i < 20; i++){
        printf("#");
    }
    printf("\n");
}

void exibir_funcionalidades_no_terminal(){
    exibir_separador();

    printf(">>Para executar uma ação, digite o número correspondente.\n");
    printf("1.\tKNN (K-Nearest Neighbours)\n");
    printf("-1.\tSair do programa\n");

    exibir_separador();
}