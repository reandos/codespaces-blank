#include "maze.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// Füllt das Gitter mit Hindernissen basierend auf der Dichte
static void maze_fill_obstacles(Maze* m, double density) {
    for (int y = 0; y < m->height; ++y) {
        for (int x = 0; x < m->width; ++x) {
            m->cells[y][x] = utils_rand_chance(density) ? 'O' : ' ';
        }
    }
}

Maze* maze_create(int width, int height, double obstacle_density) {
    // Parameter begrenzen (sinnvolle Minimal-/Maximalwerte)
    if (width < 5) width = 5;
    if (height < 5) height = 5;
    if (obstacle_density < 0.0) obstacle_density = 0.0;
    if (obstacle_density > 0.6) obstacle_density = 0.6;

    // Struktur anlegen
    Maze* m = (Maze*)malloc(sizeof(Maze));
    if (!m) return NULL;
    m->width = width;
    m->height = height;

    // 2D-Array (Zeiger auf Zeilen) allozieren
    m->cells = (char**)malloc((size_t)height * sizeof(char*));
    if (!m->cells) { free(m); return NULL; }

    for (int y = 0; y < height; ++y) {
        m->cells[y] = (char*)malloc((size_t)width * sizeof(char));
        if (!m->cells[y]) { // bei Fehler: bereits allozierte Zeilen freigeben
            for (int k = 0; k < y; ++k) free(m->cells[k]);
            free(m->cells);
            free(m);
            return NULL;
        }
    }

    maze_fill_obstacles(m, obstacle_density); // Hindernisse setzen
    return m;
}

void maze_free(Maze* m) {
    if (!m) return;
    for (int y = 0; y < m->height; ++y) free(m->cells[y]); // Zeilen freigeben
    free(m->cells);
    free(m);
}

bool maze_is_inside(const Maze* m, int x, int y) {
    return x >= 0 && y >= 0 && x < m->width && y < m->height;
}

bool maze_is_walkable(const Maze* m, int x, int y) {
    if (!maze_is_inside(m, x, y)) return false;
    return m->cells[y][x] != 'O';
}

void maze_draw(const Maze* m, int player_x, int player_y, int treasure_x, int treasure_y) {
    // obere Kante
    printf("+ ");
    for (int x = 0; x < m->width; ++x) printf("-");
    printf(" +\n");

    // Inhalte Zeile für Zeile
    for (int y = 0; y < m->height; ++y) {
        printf("| ");
        for (int x = 0; x < m->width; ++x) {
            if (x == player_x && y == player_y) {       // Spieler
                putchar('P');
            } else if (x == treasure_x && y == treasure_y) { // Schatz
                putchar('T');
            } else {
                char c = m->cells[y][x];
                putchar(c ? c : ' ');
            }
        }
        printf(" |\n");
    }

    // untere Kante
    printf("+ ");
    for (int x = 0; x < m->width; ++x) printf("-");
    printf(" +\n");
}
