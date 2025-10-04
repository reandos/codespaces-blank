#ifndef GAME_H
#define GAME_H

/*
 * game.h – Spielsteuerung (High-Level)
 * ------------------------------------
 * Verantwortlich für:
 *  - Lebenszyklus des Spiels (init/shutdown)
 *  - Spielloop inkl. Eingabeverarbeitung
 *  - Levelmodus (1..100) mit automatischem Weiterblättern
 *
 * Hinweis:
 *  - Die Spielfeldgröße, Dichte und Mindestabstände kommen aus level.c.
 *  - Das Zeichnen der ASCII-Map (inkl. Farben) macht maze.c.
 */

#include <stdbool.h>
#include "maze.h"

typedef struct {
    Maze *maze;     // aktives Labyrinth (Raster + P/T + Logik)
    bool running;   // true, solange das aktuelle Level läuft
    int  moves;     // Anzahl der erfolgreichen Züge im aktuellen Level
    int  level;     // 0 = freier Modus, 1..100 = Kampagne
} Game;

/* Freier Modus (manuelle Größe/Dichte, kein automatischer Levelwechsel) */
bool game_init(Game *g, int w, int h, double density);

/* Kampagnenmodus (Level 1..100, automatischer Wechsel zu level+1) */
bool game_init_level(Game *g, int level);

/* Ressourcen freigeben (Maze löschen, Flags zurücksetzen) */
void game_shutdown(Game *g);

/* Bildschirm aktualisieren: Kopfzeile + Maze + Status */
void game_draw(const Game *g);

/* Eine Eingabezeile verarbeiten (W/A/S/D bzw. Q) */
void game_step(Game *g, const char *input_line);

/* Hauptschleife des Spiels (inkl. Level-Fortschritt im Kampagnenmodus) */
void game_loop(Game *g);

#endif /* GAME_H */
