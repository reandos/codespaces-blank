# ============================================================
#  Makefile – Labirinth Level 1–100
# ============================================================
# Dieses Makefile steuert den kompletten Build-Prozess.
# Es kompiliert das Spiel, verwaltet den Smoke-Test
# und bietet Komfort-Kommandos (run, clean, debug, usw.).
# ------------------------------------------------------------
# Wichtig:
#   • Jede Befehlszeile MUSS mit einem echten Tab beginnen!
#   • Pfade und Namen entsprechen deiner Projektstruktur.
# ============================================================

# ------------------------------------------------------------
# Compiler & Optionen
# ------------------------------------------------------------
CC      := gcc
CSTD    := -std=c11
WARN    := -Wall -Wextra -Wshadow -Wconversion
OPT     := -O2
INC     := -Iinclude
CFLAGS  := $(CSTD) $(WARN) $(OPT) $(INC)
LDFLAGS :=

# ------------------------------------------------------------
# Quellen und Ausgabedateien
# ------------------------------------------------------------
SRC := \
	src/main.c \
	src/game.c \
	src/maze.c \
	src/io.c \
	src/level.c

OBJ := $(SRC:.c=.o)
DEP := $(OBJ:.o=.d)

BIN := labyrinth

# ------------------------------------------------------------
# Standardziel (wird bei „make“ ohne Argument gebaut)
# ------------------------------------------------------------
.PHONY: all
all: $(BIN)
	@echo "✅ Build abgeschlossen: Starte mit ./$(BIN) 1"

# ------------------------------------------------------------
# Linkschritt (führt alle .o-Dateien zusammen)
# ------------------------------------------------------------
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

# ------------------------------------------------------------
# Kompilierung einzelner C-Dateien → .o + .d (Abhängigkeitsdateien)
# ------------------------------------------------------------
src/%.o: src/%.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# ------------------------------------------------------------
# Smoke-Test (Mini-Test für Maze/IO)
# ------------------------------------------------------------
SMOKE_SRC := tests/smoke.c src/maze.c src/io.c src/level.c
SMOKE_OBJ := $(SMOKE_SRC:.c=.o)

.PHONY: smoke
smoke: $(SMOKE_OBJ)
	$(CC) $(SMOKE_OBJ) -o smoke $(LDFLAGS)
	@echo "👉 Smoke-Test erstellt. Starte mit: ./smoke"

# ------------------------------------------------------------
# Komfort-Kommandos
# ------------------------------------------------------------
.PHONY: run runl
run: $(BIN)
	./$(BIN) 1

# Beispiel: make runl L=37  → startet Level 37
L ?= 1
runl: $(BIN)
	./$(BIN) $(L)

# ------------------------------------------------------------
# Aufräumen und Wartung
# ------------------------------------------------------------
.PHONY: clean rebuild tidy reset debug help

clean:
	@rm -f $(OBJ) $(SMOKE_OBJ) $(DEP) $(BIN) smoke
	@echo "🧹 Clean abgeschlossen."

rebuild: clean all

tidy: clean

# Voll-Reset (löscht temporäre Dateien, Caches, Logs)
reset: clean
	@find . -type f -name "*~" -delete
	@find . -type f -name "#*#" -delete
	@find . -type f -name "*.log" -delete
	@find . -type f -name "*.tmp" -delete
	@echo "🗑️  Reset abgeschlossen."

# Debug-Ausgabe für Build-Fehleranalyse
debug:
	@echo "CC       = $(CC)"
	@echo "CFLAGS   = $(CFLAGS)"
	@echo "SRC      = $(SRC)"
	@echo "OBJ      = $(OBJ)"
	@echo "BIN      = $(BIN)"
	@echo "LDFLAGS  = $(LDFLAGS)"

# Kurze Übersicht der verfügbaren Targets
help:
	@echo "================ Makefile Hilfe ================"
	@echo "make            – Kompiliert das Spiel (Standard)"
	@echo "make run        – Startet Spiel bei Level 1"
	@echo "make runl L=37  – Startet direkt bei Level 37"
	@echo "make smoke      – Erstellt und startet den Smoke-Test"
	@echo "make clean      – Löscht .o/.d/Binaries"
	@echo "make rebuild    – Clean + Build"
	@echo "make reset      – Vollständiger Reset (inkl. temporärer Dateien)"
	@echo "make debug      – Zeigt Build-Parameter"
	@echo "make tidy       – Alias für clean"
	@echo "================================================"

# ------------------------------------------------------------
# Automatische Einbindung der Abhängigkeitsdateien
# ------------------------------------------------------------
-include $(DEP)
