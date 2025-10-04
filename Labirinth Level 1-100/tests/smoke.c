#include "../include/maze.h"
#include "../include/io.h"
#include "../include/level.h"
#include <stdio.h>

/*
 * smoke.c – Mini-Testprogramm für die Maze-Generierung
 * ----------------------------------------------------
 * Zweck:
 *   Testet unabhängig vom eigentlichen Spiel, ob:
 *     - Levelparameter korrekt berechnet werden
 *     - Maze erfolgreich erstellt und gezeichnet werden kann
 *     - Das BFS-System eine lösbare Karte erzeugt
 *
 * Nutzung:
 *   make smoke && ./smoke
 */

int main(void) {
    printf("=== SMOKE TEST: Maze-Generierung ===\n\n");

    io_seed_rng();  // Zufall initialisieren

    int level = 15; // Beispiel: Level 15
    LevelParams p;
    if (!level_params_from_level(level, &p)) {
        fprintf(stderr, "Fehler: Levelparameter konnten nicht geladen werden.\n");
        return 1;
    }

    printf("Erzeuge Level %d (%dx%d, Dichte %.2f, Mindestabstand %d)\n",
           level, p.width, p.height, p.density, p.min_sep);

    Maze *m = maze_create(p.width, p.height, p.density);
    if (!m) {
        fprintf(stderr, "Fehler: Maze konnte nicht erstellt werden.\n");
        return 1;
    }

    m->min_sep = p.min_sep;
    if (!maze_generate(m)) {
        fprintf(stderr, "Fehler: Maze konnte nicht generiert werden (keine Loesung gefunden).\n");
        maze_destroy(m);
        return 1;
    }

    maze_draw(m);
    maze_destroy(m);

    printf("\n✅ Smoke-Test abgeschlossen – Maze wurde erfolgreich erstellt und gezeichnet.\n");
    return 0;
}
