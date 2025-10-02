# Compiler + Flags
CC      := cc
CFLAGS  := -std=c11 -Wall -Wextra -O2
LDFLAGS :=

# Quellen/Artefakte
SRC := $(wildcard src/*.c)
OBJ := $(SRC:.c=.o)
BIN := labyrinth

# Default-Target
all: $(BIN)

# Linken
$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

# Kompilieren (generische Regel)
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Starten
run: $(BIN)
	./$(BIN)

# Aufräumen
clean:
	rm -f $(OBJ) $(BIN)

# Optional: Code formatieren (wenn clang-format installiert ist)
format:
	clang-format -i src/*.c src/*.h || true

.PHONY: all run clean format
