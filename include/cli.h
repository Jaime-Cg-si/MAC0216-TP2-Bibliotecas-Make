#ifndef CLI_H
#define CLI_H
#include <stdbool.h>

#define OPCAO_SAIDA_PROGRAMA (-1)

/**
* @brief    Recebe o número correspondente ao método de Machine Learning escolhido pelo usuário
* @param    opcoes_funcionalidades_validas: vetor constante de inteiros correspondente aos índices das funcionalidades disponíveis
* @param    tamanho_vetor_funcionalidades : inteiro constante que corresponde ao número de opções válidas do programa.
* @return   O número (válido) escolhido pelo usuário ou, em caso de erro (vetor nulo, tamanho <= 0, EOF), a opção de encerramento do programa
* @note     Não retorna enquanto o usuário não escolher uma opção válida.
*/
int parsear_escolha_funcionalidade_usuario(const int* opcoes_funcionalidades_validas, const int tamanho_vetor_funcionalidades);


/**
* @brief    Função principal, responsável pelo fluxo de chamadas das funções desta API
* @warning  Depende da saída de outras rotinas. Implementar algum sistema de contagem de tempo?
* @note     Repete o ciclo: Exibe funcionalidades -> Recebe o input da funcionalidade -> Invoca a funcionalidade
*/
void cli_run();

/**
* @brief    Função de validação do input do usuário sobre as funcionalidades
* @param    opcao_funcionalidade_escolhida: inteiro que simboliza a escolha do usuário
* @param    opcoes_funcionalidades_validas: vetor de inteiros constante contendo os números correspondentes às funcionalidades do programa
* @param    tamanho_vetor_funcionalidades : inteiro não negativo que representa o número de elementos do vetor opcoes_funcionalidades_validas
* @return   Verdadeiro caso a opção seja válida. Falso caso a opção seja inválida, o vetor tenha tamanho negativo ou nulo ou o ponteiro seja NULL.
*/
bool validar_escolha_funcionalidade(int opcao_funcionalidade_escolhida, const int* opcoes_funcionalidades_validas, int tamanho_vetor_funcionalidades);



#endif //CLI_H