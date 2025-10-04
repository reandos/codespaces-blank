#include "../include/game.h"
#include "../include/config.h"
#include "../include/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * main.c – Programmeinstieg
 * --------------------------
 * Verantwortlich für:
 *   - Initialisierung des Zufallszahlengenerators
 *   - Auswerten der Kommandozeilenparameter
 *   - Start des Spiels im gewünschten Modus
 *
 * Modi:
 *   1. Kampagnenmodus:  ./labyrinth <level 1..100>
 *      → startet Level <n> mit automatischem Fortschritt bis 100
 *
 *   2. Freier Modus:    ./labyrinth <width> <height> <density>
 *      → manuelle Spielfeldgröße, kein Levelsystem
 *
 *   (Density = Anteil der Wände, typischer Bereich 0.0–0.6)
 */

// ------------------------------------------------------------
// Eingabe-Konvertierungen (Hilfsfunktionen)
// ------------------------------------------------------------

// Konvertiert Zeichenkette zu int mit Standardwert (def)
static int to_int(const char *s, int def) {
    if (!s || !*s) return def;
    char *end;
    long v = strtol(s, &end, 10);
    if (*end != '\0') return def;
    return (int)v;
}

// Konvertiert Zeichenkette zu double mit Standardwert (def)
static double to_double(const char *s, double def) {
    if (!s || !*s) return def;
    char *end;
    double v = strtod(s, &end);
    if (*end != '\0') return def;
    if (v < 0.0) v = 0.0;
    if (v > 0.6) v = 0.6;
    return v;
}

// Zeigt Nutzungshinweis an (bei falschen Argumenten)
static void usage(const char *exe) {
    fprintf(stderr,
        "Usage:\n"
        "  %s <level 1..100>\n"
        "  %s <width> <height> <density 0..0.6>\n",
        exe, exe);
}

// ------------------------------------------------------------
// Hauptfunktion – Einstiegspunkt des Programms
// ------------------------------------------------------------
int main(int argc, char **argv) {
    // Zufallszahlengenerator initialisieren (einmalig)
    io_seed_rng();

    Game g;

    /* --------------------------------------------------------
     * Modus 1: Kampagne – ./labyrinth <level>
     * -------------------------------------------------------- */
    if (argc == 2) {
        int level = to_int(argv[1], -1);
        if (level >= 1 && level <= 100) {
            if (!game_init_level(&g, level)) {
                fprintf(stderr, "Fehler: Level %d konnte nicht initialisiert werden.\n", level);
                return 1;
            }
            game_loop(&g);
            game_shutdown(&g);
            return 0;
        } else {
            usage(argv[0]);
            return 1;
        }
    }

    /* --------------------------------------------------------
     * Modus 2: Freier Modus – ./labyrinth <width> <height> <density>
     * -------------------------------------------------------- */
    if (argc == 4) {
        int w = to_int(argv[1], DEFAULT_WIDTH);
        int h = to_int(argv[2], DEFAULT_HEIGHT);
        if (w < 5) w = 5;
        if (h < 5) h = 5;
        double d = to_double(argv[3], DEFAULT_DENSITY);

        if (!game_init(&g, w, h, d)) {
            fprintf(stderr, "Fehler: Initialisierung fehlgeschlagen.\n");
            return 1;
        }
        game_loop(&g);
        game_shutdown(&g);
        return 0;
    }

    // Kein gültiger Modus -> Hilfe anzeigen
    usage(argv[0]);
    return 1;
}
