#include "game.h"
#include "utils.h"
#include <stdio.h>

// Wählt eine zufällige begehbare Zelle und gibt deren Koordinaten zurück
static void place_random_empty_cell(const Maze* m, int* out_x, int* out_y) {
    while (1) { // so lange versuchen, bis eine freie Zelle gefunden wurde
        int x = utils_rand_int(0, m->width - 1);
        int y = utils_rand_int(0, m->height - 1);
        if (maze_is_walkable(m, x, y)) { *out_x = x; *out_y = y; return; }
    }
}

bool game_init(Game* g, int width, int height, double obstacle_density) {
    if (!g) return false;

    utils_seed_random();                                // Zufall initialisieren
    g->maze = maze_create(width, height, obstacle_density); // Labyrinth anlegen
    if (!g->maze) return false;

    place_random_empty_cell(g->maze, &g->player_x, &g->player_y); // Spieler setzen
    do {                                                          // Schatz setzen (nicht auf Spieler)
        place_random_empty_cell(g->maze, &g->treasure_x, &g->treasure_y);
    } while (g->treasure_x == g->player_x && g->treasure_y == g->player_y);

    g->moves = 0;     // Zähler zurücksetzen
    g->running = true; // Spiel aktiv
    return true;
}

// Kurze Hilfezeile ausgeben
static void print_help(void) {
    printf("Steuerung: W/A/S/D + Enter. Q = Beenden.\n");
}

// Zeichnet Spielfeld + Statuszeile
static void draw_and_status(const Game* g) {
    maze_draw(g->maze, g->player_x, g->player_y, g->treasure_x, g->treasure_y);
    printf("Zuege: %d\n", g->moves);
    print_help();
}

void game_loop(Game* g) {
    if (!g || !g->maze) return;

    printf("Willkommen zum Labyrinth! Finde den Schatz (T).\n\n");
    draw_and_status(g); // Startzustand anzeigen

    while (g->running) {
        printf("> ");                      // Prompt
        Command cmd = input_read_command(); // Befehl lesen (W/A/S/D/Q)

        if (cmd == CMD_NONE) {            // Ungültige Eingabe
            printf("Ungueltige Eingabe. Nur W/A/S/D oder Q.\n");
            continue;
        }
        if (cmd == CMD_QUIT) {            // Benutzer beendet Spiel
            printf("Spiel beendet.\n");
            break;
        }

        // Richtung aus Befehl ableiten
        int dx = 0, dy = 0;
        switch (cmd) {
            case CMD_UP:    dy = -1; break;
            case CMD_LEFT:  dx = -1; break;
            case CMD_DOWN:  dy =  1; break;
            case CMD_RIGHT: dx =  1; break;
            default: break;
        }

        // Zielposition ermitteln
        int nx = g->player_x + dx;
        int ny = g->player_y + dy;

        // Grenzen und Hindernisse prüfen
        if (!maze_is_inside(g->maze, nx, ny)) {
            printf("Am Rand! Bewegung nicht moeglich.\n");
        } else if (!maze_is_walkable(g->maze, nx, ny)) {
            printf("Blockiert durch Hindernis (O).\n");
        } else {
            g->player_x = nx; // Position übernehmen
            g->player_y = ny;
            g->moves++;       // Zug zählen
        }

        // Siegbedingung: Spieler auf Schatz?
        if (g->player_x == g->treasure_x && g->player_y == g->treasure_y) {
            maze_draw(g->maze, g->player_x, g->player_y, g->treasure_x, g->treasure_y);
            printf("\nGlueckwunsch! Du hast den Schatz in %d Zuegen gefunden.\n", g->moves);
            g->running = false;
            break;
        }

        draw_and_status(g); // Neuen Zustand anzeigen
    }
}

void game_cleanup(Game* g) {
    if (!g) return;
    maze_free(g->maze); // Labyrinth freigeben
    g->maze = NULL;
}
