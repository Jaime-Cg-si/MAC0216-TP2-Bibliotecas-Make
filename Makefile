.PHONY: clean install test all run exibe_variaveis

#Variáveis de diretório
INCLUDE_DIR := include
APP_DIR     := app
SRC_DIR     := src
TESTS_DIR   := tests
BIN_DIR     := bin
BUILD_DIR   := build

#Variáveis de compilação
CC       := gcc
CFLAGS   := -Wall -Wextra -g -std=c11
CPPFLAGS := -I$(INCLUDE_DIR)

#Processo de descoberta dos arquivos-fonte (.c)
ARQ_SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ_SRC := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(ARQ_SRC))

ARQ_APP := $(wildcard $(APP_DIR)/*.c)
OBJ_APP := $(patsubst $(APP_DIR)/%.c,$(BUILD_DIR)/%.o,$(ARQ_APP))

#Variável do arquivo executável
EXE := $(BIN_DIR)/biblioteca_ml
all: $(EXE)

exibe_variaveis:
	@echo "### VARIÁVEIS DE DIRETÓRIOS ###"
	@echo "[$(INCLUDE_DIR)]"
	@echo "[$(APP_DIR)]"
	@echo "[$(SRC_DIR)]"
	@echo "[$(TESTS_DIR)]"
	@echo "[$(BIN_DIR)]"
	@echo "[$(BUILD_DIR)]"
	@echo "### VARIÁVEIS DE COMPILAÇÃO ###"
	@echo "[$(CC)]"
	@echo "[$(CFLAGS)]"
	@echo "[$(CPPFLAGS)]"
	@echo "### DESCOBERTA DE ARQUIVOS .C ###"
	@echo "[ARQ_SRC = $(ARQ_SRC)]"
	@echo "[OBJ_SRC = $(OBJ_SRC)]"
	@echo "[ARQ_APP = $(ARQ_APP)]"
	@echo "[OBJ_APP = $(OBJ_APP)]"
