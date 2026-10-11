CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -std=c11 -Iinclude
LDFLAGS = -lm

SRC_DIR = src
OBJ_DIR = obj
BIN     = ML

# Pega todos os .c em src/ automaticamente
SRCS    = $(wildcard $(SRC_DIR)/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))


$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $(BIN) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria a pasta obj/ se não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: clean
