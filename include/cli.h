#ifndef CLI_H
#define CLI_H

/**
* @brief    Recebe o número correspondente ao método de Machine Learning escolhido pelo usuário
* @param    opcoes_funcionalidades_validas: vetor de inteiros correspondente aos índices das funcionalidades disponíveis
* @warning  Não verifica se o vetor opcoes_funcionalidades_validas está vazio. Presume que existe pelo menos um valor.
* @return   O número (válido) escolhido pelo usuário
* @note     Não retorna enquanto o usuário não escolher uma opção válida
*/
int parsear_escolha_funcionalidade_usuario(int* opcoes_funcionalidades_validas);


/**
* @brief    Função principal, responsável pelo fluxo de chamadas das funções desta API
* @warning  Depende da saída de outras rotinas. Implementar algum sistema de contagem de tempo?
* @note     Repete o ciclo: Exibe funcionalidades -> Recebe o input da funcionalidade -> Invoca a funcionalidade
*/
void cli_run();



#endif //CLI_H