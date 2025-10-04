#ifndef MAZE_H
#define MAZE_H

/*
 * maze.h – Labyrinth-Modul (Raster, Platzierung, Zeichnen, Bewegung)
 * -------------------------------------------------------------------
 * Verantwortlich für:
 *   - Datenstruktur des Spielfelds (ASCII-Raster + Positionen)
 *   - zufällige Erzeugung eines lösbaren Labyrinths (siehe maze_generate)
 *   - Zeichnen des Rasters (Farben kommen aus config.h)
 *   - Spielerbewegung (W/A/S/D) mit Kollision gegen Wände
 *
 * Wichtige Begriffe:
 *   density  : Anteil der Wandzellen (0..1), sinnvoll < 0.6
 *   min_sep  : Mindestabstand P↔T (Chebyshev: |dx|>=min_sep UND |dy|>=min_sep)
 */

#include <stdbool.h>

/* Integer-2D-Position (Spalte x, Zeile y) */
typedef struct { int x, y; } Vec2i;

/* Labyrinth-Zustand */
typedef struct {
    int   width, height;   /* Rastergröße in Zeichen */
    char **cells;          /* Zeiger auf Zeilen (height) mit je width Zeichen */
    Vec2i player;          /* Position des Spielers (CHAR_PLAYER) */
    Vec2i treasure;        /* Position des Schatzes (CHAR_TREASURE) */
    double density;        /* Wanddichte 0..1 (wird beim Füllen verwendet) */
    int   min_sep;         /* Mindestabstand P↔T (Chebyshev) */
} Maze;

/* Erzeugt ein leeres Maze-Objekt (allokiert Raster), klemmt Parameter auf sinnvolle Werte. */
Maze* maze_create(int width, int height, double density);

/* Gibt Speicher (Raster + Struktur) frei. */
void  maze_destroy(Maze *m);

/* Füllt das Raster zufällig, platziert P und T mit Mindestabstand und
 * prüft per BFS, dass ein Weg existiert. true bei Erfolg. */
bool  maze_generate(Maze *m);

/* Zeichnet das Raster in die Konsole (verwendet Farbcodes aus config.h). */
void  maze_draw(const Maze *m);

/* Versucht, den Spieler um 1 Feld zu bewegen (W/A/S/D). true bei erfolgreicher Bewegung. */
bool  maze_try_move_player(Maze *m, char dir);

/* Liefert true, wenn Spieler auf dem Schatz steht. */
bool  maze_is_win(const Maze *m);

#endif /* MAZE_H */
