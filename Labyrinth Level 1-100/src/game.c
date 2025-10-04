#include "../include/game.h"
#include "../include/io.h"
#include "../include/config.h"
#include "../include/level.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * game.c – zentrale Spiellogik
 * ----------------------------
 * Verantwortlich für:
 *   • Initialisierung und Verwaltung des Spielzustands
 *   • Spielloop (Ein-/Ausgabe, Bewegung, Levelwechsel)
 *   • Anzeige von Kopfzeile, Spielfeld und Status
 *
 * Module:
 *   - io.c     → Eingabe & Bildschirm
 *   - maze.c   → Spielfeld-Erzeugung und -Zeichnung
 *   - level.c  → Berechnung der Level-Parameter
 */

#define INPUT_BUF 64  // Eingabepuffergröße für Benutzereingaben

/* ------------------------------------------------------------
 * Kopfzeile mit aktuellem Level, Spielfeldgröße und Steuerung
 * ------------------------------------------------------------ */
static void print_header(const Game *g) {
    if (g && g->maze) {
        if (g->level >= 1)
            printf("===== LABIRINTH LEVEL 1–100 | Level %d (%dx%d) =====\n",
                   g->level, g->maze->width, g->maze->height);
        else
            printf("===== LABYRINTH – Freier Modus (%dx%d) =====\n",
                   g->maze->width, g->maze->height);
    } else {
        printf("===== LABYRINTH =====\n");
    }
    printf("Steuerung: W / A / S / D  |  Q = Beenden\n\n");
}

/* ------------------------------------------------------------
 * Hilfsfunktionen
 * ------------------------------------------------------------ */

// Setzt Basiszustand (neues Spiel oder neues Level)
static bool init_common(Game *g) {
    if (!g) return false;
    g->running = true;
    g->moves = 0;
    return true;
}

// Lädt oder ersetzt das aktuelle Level mit neuen Maze-Daten
static bool load_level(Game *g, int level) {
    if (!g) return false;

    LevelParams p;
    if (!level_params_from_level(level, &p))
        return false;

    Maze *nm = maze_create(p.width, p.height, p.density);
    if (!nm) return false;

    nm->min_sep = p.min_sep;

    if (!maze_generate(nm)) {
        maze_destroy(nm);
        return false;
    }

    if (g->maze) maze_destroy(g->maze);
    g->maze = nm;
    g->level = level;
    g->moves = 0;
    g->running = true;
    return true;
}

/* ------------------------------------------------------------
 * Öffentliche API-Funktionen
 * ------------------------------------------------------------ */

// Freier Modus (ohne Levelsystem)
bool game_init(Game *g, int w, int h, double density) {
    if (!g) return false;
    memset(g, 0, sizeof(*g));

    g->maze = maze_create(w, h, density);
    if (!g->maze) return false;

    g->maze->min_sep = 5; // Standardabstand
    if (!maze_generate(g->maze)) {
        maze_destroy(g->maze);
        g->maze = NULL;
        return false;
    }

    g->level = 0; // 0 = freier Modus
    return init_common(g);
}

// Kampagnenmodus (1..100)
bool game_init_level(Game *g, int level) {
    if (!g) return false;
    memset(g, 0, sizeof(*g));

    if (!load_level(g, level))
        return false;

    return init_common(g);
}

// Gibt Speicher frei und beendet das Spiel
void game_shutdown(Game *g) {
    if (!g) return;
    maze_destroy(g->maze);
    g->maze = NULL;
    g->running = false;
}

/* ------------------------------------------------------------
 * Anzeige & Eingabeverarbeitung
 * ------------------------------------------------------------ */

// Bild neu zeichnen (Kopfzeile + Maze + Züge)
void game_draw(const Game *g) {
    if (!g || !g->maze) return;
    io_clear_screen();
    print_header(g);
    maze_draw(g->maze);
    printf("\nZuege: %d\n", g->moves);
}

// Einen Eingabeschritt verarbeiten (W/A/S/D/Q)
void game_step(Game *g, const char *line) {
    if (!g || !g->maze || !line || !*line) return;

    char c = line[0];
    if (c == 'q' || c == 'Q') { // Spiel abbrechen
        g->running = false;
        return;
    }

    // Bewegung prüfen
    if (maze_try_move_player(g->maze, c))
        g->moves++;
    else
        printf("\nUngueltige Eingabe. Bitte W/A/S/D oder Q.\n");

    // Siegbedingung prüfen
    if (maze_is_win(g->maze))
        g->running = false;
}

/* ------------------------------------------------------------
 * Hauptschleife – Spiel läuft hier
 * ------------------------------------------------------------ */
void game_loop(Game *g) {
    if (!g || !g->maze) return;
    char buf[INPUT_BUF];

    // --- Kampagnenmodus: automatische Level-Fortsetzung ---
    if (g->level >= 1) {
        for (;;) {
            while (g->running) {
                game_draw(g);
                printf("> Bewegung (W/A/S/D): ");
                fflush(stdout);

                int n = io_read_line(buf, (int)sizeof buf);
                if (n <= 0) { g->running = false; break; } // EOF/Ctrl+D
                game_step(g, buf);
            }

            game_draw(g);

            if (maze_is_win(g->maze)) {
                printf("\n🎉 Level %d geschafft! Du hast den Schatz in %d Zuegen gefunden.\n",
                       g->level, g->moves);

                if (g->level >= 100) {
                    printf("🏆 Glueckwunsch! Du hast alle 100 Level abgeschlossen!\n");
                    break;
                }

                int next = g->level + 1;
                printf("\nWeiter zu Level %d ... (Enter druecken)\n", next);
                fflush(stdout);
                io_read_line(buf, (int)sizeof buf);

                if (!load_level(g, next)) {
                    printf("❌ Fehler beim Laden von Level %d. Spiel endet.\n", next);
                    break;
                }
                continue;
            } else {
                printf("\nSpiel beendet auf Level %d.\n", g->level);
                break;
            }
        }
        return;
    }

    // --- Freier Modus (manuell gestartet) ---
    while (g->running) {
        game_draw(g);
        printf("> Bewegung (W/A/S/D): ");
        fflush(stdout);

        int n = io_read_line(buf, (int)sizeof buf);
        if (n <= 0) { g->running = false; break; }

        game_step(g, buf);
    }

    game_draw(g);

    if (maze_is_win(g->maze))
        printf("\nGeschafft! Du hast den Schatz in %d Zuegen gefunden.\n", g->moves);
    else
        printf("\nSpiel beendet.\n");
}
