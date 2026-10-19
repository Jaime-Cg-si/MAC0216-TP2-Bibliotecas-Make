# MAC0216 - TÉCNICAS DE PROGRAMAÇÃO: TRABALHO PRÁTICO 2 - BIBLIOTECA/MAKEFILE

### Integrantes

- Felipe Brancalhão Curcio: 16985106
- Jaime Cavalcanti Guedes: 16875204
- João Pedro Silva Amadio: 13672533
- Murilo Santos de Castro: 17015895

## 1. Objetivo do trabalho prático

O objetivo deste trabalho é desenvolver uma aplicação, juntamente com um sistema
de documentação e compilação (na forma estática e dinâmica), voltada para a área
de *Machine Learning* (ML). Ela conta com a implementação de duas técnicas de
ML: *K-Nearest Neighbors* (KNN) e *Mean Squared Error* (MSE). Além disso, há
rotinas de E/S e de interação com o usuário por meio da linha de comando. O
código é escrito na linguagem C, visando primariamente a especificação C11, e
utiliza um Makefile para gerenciar a compilação. Por padrão, é utilizado o
compilador GCC.

## 2. Divisão dos 4 módulos funcionais

A aplicação é dividida em quatro módulos de acordo com as suas funcionalidades:

- **Entrada/Saída e Padronização:** Recebimento, tratamento e saída de
  informações e dados por parte do programa.
- **KNN:** Classificação de amostras usando *K-Nearest Neighbors*
- **MSE:** Cálculo da soma de erros (SSE - *Sum of Squared Errors*), erro
  quadrático médio (MSE - *Mean Squared Error*) e raiz do erro quadrático médio
  (RMSE - *Root Mean Squared Error*) entre vetores.
- **CLI:** Criação e gerenciamento da linha de comando (*Command Line
  Interface*).

## 3. Comandos do Makefile

A aplicação pode ser compilada com o seguinte comando:

    make

ou, equivalentemente:

    make all

A regra padrão `all` gera dois executáveis, um dinâmico e um estático, além das
bibliotecas correspondentes. Os executáveis são gerados em
`bin/machinelearning_dinamico` e `bin/machinelearning_estatico` respectivamente,
e as bibliotecas em `lib/libmachinelearning.a` (estática) e
`lib/libmachinelearning.so` (dinâmica).

A aplicação pode ser executada com este comando (usa o executável dinâmico):

    make run

Para instalar a aplicação, rode este comando com um parâmetro opcional `PREFIX`:

    make install PREFIX="$HOME/local"

A instalação copia ambos os executáveis para `$PREFIX/bin` e ambas as
bibliotecas para `$PREFIX/lib`, e também os headers `.h` em `$PREFIX/include`. O
prefixo padrão de instalação é exatamente esse mostrado no comando acima.

Para rodar os testes:

    make test

Para remover todos os artefatos gerados compilação (executáveis, bibliotecas e
arquivos objeto):

    make clean

### 3.1. Comandos adicionais

A regra `exibe_variaveis` printa os valores de todas as variáveis do Makefile:

    make exibe_variaveis
