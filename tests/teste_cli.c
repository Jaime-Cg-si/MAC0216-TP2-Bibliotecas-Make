#include "cli.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static int numero_sucessos  = 0;
static int numero_fracassos = 0;

/**
* @brief Função para exibir e contabilizar uma instância de teste genérica
* @param resultado_teste: valor booleano correspondente ao resultado do teste
* @param descricao_instancia: string com a instância de teste realizada
*/
static void verificar_resultado_teste(bool resultado_teste, const char* descricao_instancia){

    if (resultado_teste == true){
        printf("PASSOU: ");
        numero_sucessos++;
    }

    else{
        printf("FALHOU: ");
        numero_fracassos++;
    }

    printf("%s\n", descricao_instancia);
}

/**
* @brief    Testa a função validar_escolha_funcionalidade.
* @par      Para cada instância do teste, invoca a validar_escolha_funcionalidade(...) e exibe os resultados
* @note     Possui seu próprio vetor de funcionalidades
*/
static void grupo_testes_input_funcionalidade(){

    int vetor_funcionalidades[] = {1, 2, 3, -1, 4};
    int tamanho_vetor_funcionalidades = sizeof(vetor_funcionalidades) / sizeof(int);
    int vetor_unitario[] = {5};
    int tamanho_vetor_unitario = sizeof(vetor_unitario) / sizeof(int);
    int* vetor_null = NULL;

    /*
    Teste 01 - Uso padrão.
    Instância: funcionalidade válida.
    Valor esperado de retorno de validar_escolha: true.
    */
    bool resultado_teste1 = validar_escolha_funcionalidade(2, vetor_funcionalidades, tamanho_vetor_funcionalidades);
    verificar_resultado_teste(resultado_teste1 == true, "opc 2 em {1,2,3, -1, 4} (tamanho 5) -> true");

    /*
    Teste 02 - Uso padrão.
    Instância: funcionalidade inválida.
    Valor esperado de retorno de validar_escolha: false.
    */
    bool resultado_teste2 = validar_escolha_funcionalidade(0, vetor_funcionalidades, tamanho_vetor_funcionalidades);
    verificar_resultado_teste(resultado_teste2 == false, "opc 0 em {1,2,3, -1, 4} (tamanho 5) -> false");

    /*
    Teste 03 - Uso limite.
    Instância: primeira funcionalidade do vetor.
    Valor esperado: true
    */
    bool resultado_teste3 = validar_escolha_funcionalidade(1, vetor_funcionalidades, tamanho_vetor_funcionalidades);
    verificar_resultado_teste(resultado_teste3 == true, "opc 1 em {1,2,3,-1,4} (tam. 5) -> true");

    /*
    Teste 04 - Uso limite.
    Instância: última funcionalidade do vetor.
    Valor esperado: true
    */
    bool resultado_teste4 = validar_escolha_funcionalidade(4, vetor_funcionalidades, tamanho_vetor_funcionalidades);
    verificar_resultado_teste(resultado_teste4 == true, "opc 4 em {1,2,3,-1,4} (tam. 5) -> true");

    /*
    Teste 05 - Uso limite.
    Instância: Vetor com uma única funcionalidade.
    Valor esperado: true.
    */
    bool resultado_teste5 = validar_escolha_funcionalidade(5, vetor_unitario, tamanho_vetor_unitario);
    verificar_resultado_teste(resultado_teste5 == true, "opc 5 em {5} (vetor unitario) -> true");

    /*
    Teste 06 - Uso inválido.
    Instância: Vetor NULL com tamanho positivo.
    Valor esperado: false.
    */
    bool resultado_teste6 = validar_escolha_funcionalidade(5, vetor_null, tamanho_vetor_funcionalidades);
    verificar_resultado_teste(resultado_teste6 == false, "opc. 5 em NULL (vetor null) -> false");

    /*
    Teste 07 - Uso inválido.
    Instância: Vetor com tamanho 0.
    Valor esperado: false.
    */
    bool resultado_teste7 = validar_escolha_funcionalidade(3, vetor_funcionalidades, 0);
    verificar_resultado_teste(resultado_teste7 == false, "opc 3 em {1,2,3,-1,4} (tam. 0) -> false");

    /*
    Teste 08 - Uso inválido.
    Instância: Vetor de tamanho negativo.
    Valor esperado: false.
    */
    bool resultado_teste8 = validar_escolha_funcionalidade(4, vetor_funcionalidades, -1);
    verificar_resultado_teste(resultado_teste8 == false, "opc 4 em {1,2,3,-1,4} (tamanho -1) -> false");

    /*
    Teste 09 - Uso inválido.
    Instância: Vetor com tamanho especificado errado.
    Valor esperado: false.
    */
    bool resultado_teste9 = validar_escolha_funcionalidade(4, vetor_funcionalidades, 4);
    verificar_resultado_teste(resultado_teste9 == false, "opc 4 em {1,2,3,-1,4} (tamanho 4) -> false");
}

/**
* @brief    Testa a função parsear_escolha_funcionalidade_usuario.
* @note     Possui seu próprio vetor de funcionalidades.
*/
static void grupo_testes_parsear_escolha_funcionalidade(){
    int vetor_opcoes[] = {1, 2, -1};
    int tamanho_vetor_opcoes = sizeof(vetor_opcoes) / sizeof(vetor_opcoes[0]);

    /*
    Teste 01 - Uso inválido.
    Instância: Vetor NULL.
    Consome: nenhum dado do arquivo.
    Valor esperado: OPCAO_SAIDA_PROGRAMA.
    */
    int resultado_teste1 = parsear_escolha_funcionalidade_usuario(NULL, tamanho_vetor_opcoes);
    verificar_resultado_teste(resultado_teste1 == OPCAO_SAIDA_PROGRAMA, "vetor NULL (tamanho 3) -> OPCAO_SAIDA_PROGRAMA");

    /*
    Teste 02 - Uso inválido.
    Instância: Vetor de tamanho 0.
    Consome: nenhum dado do arquivo.
    Valor esperado: OPCAO_SAIDA_PROGRAMA.
    */
    int resultado_teste2 = parsear_escolha_funcionalidade_usuario(vetor_opcoes, 0);
    verificar_resultado_teste(resultado_teste2 == OPCAO_SAIDA_PROGRAMA, "vetor de tamanho 0 -> OPCAO_SAIDA_PROGRAMA");

    /*
    Teste 03 - Uso padrão.
    Instância: Opção válida como primeiro input.
    Consome: 1 (linha 1).
    Valor esperado: 1.
    */
    int resultado_teste3 = parsear_escolha_funcionalidade_usuario(vetor_opcoes, tamanho_vetor_opcoes);
    verificar_resultado_teste(resultado_teste3 == 1, "opc 1 em {1, 2, -1} (tam. 3) -> 1");

    /*
    Teste 04 - Uso limite.
    Instância: Opção inválida, depois válida.
    Consome: 7; 2 (linhas 2, 3).
    Valor esperado: 2.
    */
    int resultado_teste4 = parsear_escolha_funcionalidade_usuario(vetor_opcoes, tamanho_vetor_opcoes);
    verificar_resultado_teste(resultado_teste4 == 2, "opc 7; 2 em {1,2,-1} (tam. 3) -> 2");

    /*
    Teste 05 - Uso limite.
    Instância: Opção não-numérica (sequência abc) ; Opção válida.
    Consome: abc; 1 (linhas 4; 5).
    Valor esperado: 1.
    */
    int resultado_teste5 = parsear_escolha_funcionalidade_usuario(vetor_opcoes, tamanho_vetor_opcoes);
    verificar_resultado_teste(resultado_teste5 == 1, "opc abc; 1 em {1,2,-1} (tam. 3)-> 1");

    /*
    Teste 06 - Uso limite.
    Instância: Opção válida misturada com inválida.
    Consome: 1abc (linha 6).
    Valor esperado: 1.
    */
    int resultado_teste6 = parsear_escolha_funcionalidade_usuario(vetor_opcoes, tamanho_vetor_opcoes);
    verificar_resultado_teste(resultado_teste6 == 1, "opc 1abc em {1,2,-1} (tam. 3) -> 1");

    /*
    Teste 07 - Uso limite.
    Instância: Fim de arquivo.
    Consome: nenhum dado do arquivo.
    Valor esperado: OPCAO_SAIDA_PROGRAMA.
    */
    int resultado_teste7 = parsear_escolha_funcionalidade_usuario(vetor_opcoes, tamanho_vetor_opcoes);
    verificar_resultado_teste(resultado_teste7 == OPCAO_SAIDA_PROGRAMA, "opc EOF em {1,2,-1} (tam. 3) -> OPCAO_SAIDA_PROGRAMA");
}

int main(){

    grupo_testes_input_funcionalidade();
    grupo_testes_parsear_escolha_funcionalidade();
    
    printf("Pontuação total: %d/%d\n", numero_sucessos, numero_sucessos+numero_fracassos);
    if (numero_fracassos != 0){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}