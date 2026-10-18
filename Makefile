.PHONY: clean install test all run exibe_variaveis

#Variáveis de diretório
INCLUDE_DIR := include
APP_DIR     := app
SRC_DIR     := src
TESTS_DIR   := tests
BIN_DIR     := bin
BUILD_DIR   := build
DADOS_DIR   := $(TESTS_DIR)/dados
LIB_DIR     := lib

#Variáveis de compilação
CC       := gcc
CFLAGS   := -Wall -Wextra -g -std=c11
CPPFLAGS := -I$(INCLUDE_DIR) -MMD -MP
LDLIBS   := -lm
PICFLAGS := -fPIC
AR       := ar
ARFLAGS  := rcs


#Processo de descoberta dos arquivos-fonte (.c)
ARQ_SRC   := $(wildcard $(SRC_DIR)/*.c)
OBJ_SRC   := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(ARQ_SRC))

ARQ_APP   := $(wildcard $(APP_DIR)/*.c)
OBJ_APP   := $(patsubst $(APP_DIR)/%.c,$(BUILD_DIR)/%.o,$(ARQ_APP))

ARQ_TESTS := $(wildcard $(TESTS_DIR)/*.c)
OBJ_TESTS := $(patsubst $(TESTS_DIR)/%.c,$(BUILD_DIR)/%.o,$(ARQ_TESTS))

#Processo de criação dos arquivos .d, responsáveis por informar as dependências dos arquivos
ARQ_D := $(patsubst $(BUILD_DIR)/%.o,$(BUILD_DIR)/%.d,$(OBJ_SRC) $(OBJ_APP) $(OBJ_TESTS))


#Variável do arquivo executável
EXE := $(BIN_DIR)/biblioteca_ml
EXE_TESTS := $(patsubst $(TESTS_DIR)/%.c,$(BIN_DIR)/%,$(ARQ_TESTS))

#Variáveis das bibliotecas
LIB_NOME        := machinelearning
LIB_ESTATICA    := $(LIB_DIR)/lib$(LIB_NOME).a
LIB_DINAMICA    := $(LIB_DIR)/lib$(LIB_NOME).so
EXE_ESTATICO    := $(BIN_DIR)/$(LIB_NOME)_estatico
EXE_DINAMICO    := $(BIN_DIR)/$(LIB_NOME)_dinamico

# Prefixo de instalação (para a regra install)
# Por padrão usa um diretório na home para não precisar de sudo
PREFIX := $(HOME)/.local

#Regra para execução de todo o processo
all: $(EXE)

#Regra para a criação da biblioteca estática
$(LIB_ESTATICA): $(OBJ_SRC) | $(LIB_DIR)
	rm -f $(@)
	$(AR) $(ARFLAGS) $(@) $(^)

#Regra para execução dos testes automatizados
test: $(EXE_TESTS)
	@erro=0; \
	for arq in $(^); do \
	echo "Executando $$arq..."; \
	nome_arq=$$(basename $$arq); \
	nome_arq_entrada=$(DADOS_DIR)/$$nome_arq.entrada; \
	nome_arq_saida=$(DADOS_DIR)/$$nome_arq.saida; \
	if [ ! -f $$nome_arq_entrada ]; then \
	nome_arq_entrada=/dev/null; \
	fi; \
	if [ -f $$nome_arq_saida ]; then \
	nome_arq_saida_obtida=$(BUILD_DIR)/$$nome_arq.obtida; \
	$$arq < $$nome_arq_entrada > $$nome_arq_saida_obtida || erro=1; \
	if diff -u $$nome_arq_saida $$nome_arq_saida_obtida;then \
	echo "Mesma saída"; \
	else \
	echo "Saídas diferentes."; \
	erro=1; \
	fi; \
	else \
	$$arq < $$nome_arq_entrada || erro=1; \
	fi; \
	done; \
	echo "Código de saída do teste: $$erro"; \
	exit $$erro

run: $(EXE)
	@exec $(EXE)

install: $(EXE)
	mkdir --parents $(DESTDIR)$(PREFIX)/bin
	cp --force $(EXE) $(DESTDIR)$(PREFIX)/bin

#Regra auxiliar para a exibição dos valores de todas as variáveis
exibe_variaveis:
	@echo "### VARIÁVEIS DE DIRETÓRIOS ###"
	@echo "[$(INCLUDE_DIR)]"
	@echo "[$(APP_DIR)]"
	@echo "[$(SRC_DIR)]"
	@echo "[$(TESTS_DIR)]"
	@echo "[$(BIN_DIR)]"
	@echo "[$(BUILD_DIR)]"
	@echo "[$(LIB_DIR)]"
	@echo "### VARIÁVEIS DE COMPILAÇÃO ###"
	@echo "[$(CC)]"
	@echo "[$(CFLAGS)]"
	@echo "[$(CPPFLAGS)]"
	@echo "### VARIÁVEIS DE BIBLIOTECA ###"
	@echo "[$(LIB_NOME)]"
	@echo "[$(LIB_ESTATICA)]"
	@echo "[$(LIB_DINAMICA)]"
	@echo "[$(EXE_ESTATICO)]"
	@echo "[$(EXE_DINAMICO)]"
	@echo "### DESCOBERTA DE ARQUIVOS .C ###"
	@echo "[ARQ_SRC = $(ARQ_SRC)]"
	@echo "[OBJ_SRC = $(OBJ_SRC)]"
	@echo "[ARQ_APP = $(ARQ_APP)]"
	@echo "[OBJ_APP = $(OBJ_APP)]"
	@echo "[ARQ_TESTS = $(ARQ_TESTS)]"
	@echo "[OBJ_TESTS =  $(OBJ_TESTS)]"

#Regra para criação dos diretórios build/ ; bin/ ; lib/
$(BUILD_DIR) $(BIN_DIR) $(LIB_DIR):
	mkdir -p $(@)

#Regra padrão para a compilação .c->.o dos arquivos em src/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(PICFLAGS) -c $(<) -o $(@)

#Regra padrão para a compilação .c->.o dos arquivos em app/
$(BUILD_DIR)/%.o: $(APP_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(<) -o $(@)

#Regra padrão para a compilação .c->.o dos arquivos em tests/
$(BUILD_DIR)/%.o: $(TESTS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(<) -o $(@)

#Regra para a geração do executável final
$(EXE): $(OBJ_SRC) $(OBJ_APP) | $(BIN_DIR)
	$(CC) $(^) -o $(@) $(LDLIBS)

#Regra padrão estática para a geração do executável dos testes
$(EXE_TESTS): $(BIN_DIR)/%: $(BUILD_DIR)/%.o $(OBJ_SRC) | $(BIN_DIR)
	$(CC) $(^) -o $(@) $(LDLIBS)



#Regra auxiliar para limpar os diretórios build e bin
clean: 
	rm -rf $(BIN_DIR)
	rm -rf $(BUILD_DIR)
	rm -rf $(LIB_DIR)

-include $(ARQ_D)
