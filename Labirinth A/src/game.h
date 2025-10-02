#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "maze.h"
#include "input.h"

// Spielzustand (Labyrinth, Spieler-/Schatz-Position, Züge, Laufstatus)
typedef struct {
    Maze* maze;
    int player_x, player_y;     // Position des Spielers
    int treasure_x, treasure_y; // Position des Schatzes
    int moves;                  // Anzahl Züge
    bool running;               // Spiel läuft?
} Game;

// Initialisiert das Spiel (Labyrinth erzeugen, Spieler/Schatz platzieren)
bool game_init(Game* g, int width, int height, double obstacle_density);

// Gibt belegten Speicher wieder frei (Labyrinth etc.)
void game_cleanup(Game* g);

// Hauptschleife (Eingaben lesen, bewegen, Sieg prüfen, zeichnen)
void game_loop(Game* g);

#endif // GAME_H
