#ifndef MAZE_H
#define MAZE_H

#include <stdbool.h>

// 2D-Gitter (char-Zellen); 'O' = Hindernis, ' ' = frei
typedef struct {
    int width;
    int height;
    char **cells; // Index: [y][x]
} Maze;

// Erzeugt ein Labyrinth mit gegebener Größe und Hindernisdichte (0.0–0.6)
Maze* maze_create(int width, int height, double obstacle_density);

// Gibt alle allokierten Ressourcen wieder frei
void  maze_free(Maze* m);

// Zeichnet das Labyrinth samt Spieler (P) und Schatz (T)
void  maze_draw(const Maze* m, int player_x, int player_y, int treasure_x, int treasure_y);

// Prüft, ob (x,y) innerhalb der Grenzen liegt
bool  maze_is_inside(const Maze* m, int x, int y);

// Prüft, ob (x,y) begehbar ist (nicht 'O')
bool  maze_is_walkable(const Maze* m, int x, int y);

#endif // MAZE_H
