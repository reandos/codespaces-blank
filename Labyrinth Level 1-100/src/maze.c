#include "../include/maze.h"
#include "../include/io.h"
#include "../include/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * maze.c – Labyrinthlogik (Erzeugung, Prüfung, Darstellung, Bewegung)
 * -------------------------------------------------------------------
 * Dieses Modul verwaltet das Spielfeld (Raster) und enthält:
 *   • Erzeugung eines zufälligen, lösbaren Labyrinths
 *   • BFS-Prüfung auf Erreichbarkeit von Spieler → Schatz
 *   • Farbige Ausgabe des Spielfelds
 *   • Spielerbewegung per W/A/S/D
 *
 * genutzte Daten:
 *   - CHAR_* und Farbcodes aus config.h
 *   - Zufall aus io_rand01()
 */

// ============================================================
//  Speicherverwaltung (Erstellen & Freigeben des Rasters)
// ============================================================
static char **alloc_grid(int w, int h) {
    char **rows = (char**)calloc((size_t)h, sizeof(char*));
    if (!rows) return NULL;
    for (int y = 0; y < h; ++y) {
        rows[y] = (char*)calloc((size_t)w, sizeof(char));
        if (!rows[y]) return NULL;
    }
    return rows;
}

static void free_grid(char **cells, int h) {
    if (!cells) return;
    for (int y = 0; y < h; ++y) free(cells[y]);
    free(cells);
}

Maze* maze_create(int width, int height, double density) {
    if (width  < 5) width  = 5;
    if (height < 5) height = 5;
    if (density < 0.0) density = 0.0;
    if (density > 0.6) density = 0.6;

    Maze *m = (Maze*)calloc(1, sizeof(Maze));
    if (!m) return NULL;

    m->width   = width;
    m->height  = height;
    m->density = density;
    m->min_sep = 5; // wird ggf. von Level überschrieben
    m->cells   = alloc_grid(width, height);
    if (!m->cells) { free(m); return NULL; }
    return m;
}

void maze_destroy(Maze *m) {
    if (!m) return;
    free_grid(m->cells, m->height);
    free(m);
}

// ============================================================
//  Hilfsfunktionen (Prüfungen & Zufall)
// ============================================================
static bool maze_is_inside_impl(const Maze *m, int x, int y) {
    return x >= 0 && y >= 0 && x < m->width && y < m->height;
}

bool maze_is_win(const Maze *m) {
    return (m->player.x == m->treasure.x) && (m->player.y == m->treasure.y);
}

// Füllt Raster zufällig mit Wänden (inkl. Rand)
static void fill_random(Maze *m) {
    for (int y = 0; y < m->height; ++y) {
        for (int x = 0; x < m->width; ++x) {
            if (x == 0 || y == 0 || x == m->width - 1 || y == m->height - 1)
                m->cells[y][x] = CHAR_WALL; // feste Randwände
            else
                m->cells[y][x] = (io_rand01() < m->density) ? CHAR_WALL : CHAR_EMPTY;
        }
    }
}

// Sucht zufällige freie Zelle (innerhalb des Spielfeldes)
static Vec2i random_empty_cell(const Maze *m) {
    for (int tries = 0; tries < 10000; ++tries) {
        int x = 1 + (rand() % (m->width  - 2));
        int y = 1 + (rand() % (m->height - 2));
        if (m->cells[y][x] == CHAR_EMPTY)
            return (Vec2i){x, y};
    }
    return (Vec2i){1, 1};
}

// Mindestabstand (Chebyshev)
static int respects_sep(Vec2i a, Vec2i b, int sep) {
    int dx = abs(a.x - b.x);
    int dy = abs(a.y - b.y);
    return (dx >= sep) && (dy >= sep);
}

// ============================================================
//  BFS – Prüft, ob von Spieler zu Schatz ein Weg existiert
// ============================================================
static bool bfs_reachable(const Maze *m, Vec2i start, Vec2i goal) {
    int w = m->width, h = m->height;
    int N = w * h;

    unsigned char *vis = (unsigned char*)calloc((size_t)N, 1);
    Vec2i *q = (Vec2i*)malloc((size_t)N * sizeof(Vec2i));
    if (!vis || !q) { free(vis); free(q); return false; }

    int head = 0, tail = 0;
    q[tail++] = start;
    vis[start.y * w + start.x] = 1;

    const int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    while (head < tail) {
        Vec2i v = q[head++];
        if (v.x == goal.x && v.y == goal.y) { free(vis); free(q); return true; }

        for (int i = 0; i < 4; ++i) {
            int nx = v.x + dirs[i][0];
            int ny = v.y + dirs[i][1];
            if (!maze_is_inside_impl(m, nx, ny)) continue;
            if (m->cells[ny][nx] == CHAR_WALL) continue;

            int idx = ny * w + nx;
            if (!vis[idx]) {
                vis[idx] = 1;
                q[tail++] = (Vec2i){nx, ny};
            }
        }
    }

    free(vis);
    free(q);
    return false;
}

// ============================================================
//  Maze-Generierung (zufällig, aber garantiert lösbar)
// ============================================================
bool maze_generate(Maze *m) {
    if (!m) return false;

    const int MAX_TRIES = 4000; // mehr Versuche für große Level

    for (int attempt = 0; attempt < MAX_TRIES; ++attempt) {
        fill_random(m);

        // Spieler setzen
        m->player = random_empty_cell(m);

        // Schatz setzen mit Mindestabstand
        int placed = 0;
        for (int t = 0; t < 4000; ++t) {
            Vec2i cand = random_empty_cell(m);
            if (cand.x == m->player.x && cand.y == m->player.y) continue;
            if (!respects_sep(cand, m->player, m->min_sep)) continue;
            m->treasure = cand;
            placed = 1;
            break;
        }
        if (!placed) continue;

        // Prüfen, ob Schatz erreichbar ist
        if (!bfs_reachable(m, m->player, m->treasure)) continue;

        // Positionen setzen
        m->cells[m->player.y][m->player.x]     = CHAR_PLAYER;
        m->cells[m->treasure.y][m->treasure.x] = CHAR_TREASURE;
        return true;
    }
    return false;
}

// ============================================================
//  Ausgabe (Farbe) & Spielerbewegung
// ============================================================
void maze_draw(const Maze *m) {
    for (int y = 0; y < m->height; ++y) {
        for (int x = 0; x < m->width; ++x) {
            char c = m->cells[y][x];
            switch (c) {
                case CHAR_PLAYER:
                    printf(COLOR_RED "%c" COLOR_RESET, c); break;
                case CHAR_TREASURE:
                    printf(COLOR_YELLOW "%c" COLOR_RESET, c); break;
                case CHAR_WALL:
                    printf(COLOR_GRAY "%c" COLOR_RESET, c); break;
                default:
                    putchar(c); break;
            }
        }
        putchar('\n');
    }
}

// Tasteneingabe zu Bewegungsvektor umwandeln
static Vec2i delta_from_dir(char dir) {
    switch (toupper((unsigned char)dir)) {
        case 'W': return (Vec2i){ 0, -1};
        case 'A': return (Vec2i){-1,  0};
        case 'S': return (Vec2i){ 0,  1};
        case 'D': return (Vec2i){ 1,  0};
        default:  return (Vec2i){ 0,  0};
    }
}

// Spieler um 1 Feld bewegen (falls kein Hindernis)
bool maze_try_move_player(Maze *m, char dir) {
    Vec2i d = delta_from_dir(dir);
    if (d.x == 0 && d.y == 0) return false;

    int nx = m->player.x + d.x;
    int ny = m->player.y + d.y;

    if (!maze_is_inside_impl(m, nx, ny)) return false;
    if (m->cells[ny][nx] == CHAR_WALL)    return false;

    if (!(m->player.x == m->treasure.x && m->player.y == m->treasure.y))
        m->cells[m->player.y][m->player.x] = CHAR_EMPTY;

    m->player.x = nx;
    m->player.y = ny;
    m->cells[ny][nx] = CHAR_PLAYER;
    return true;
}
