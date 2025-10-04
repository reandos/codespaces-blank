#ifndef LEVEL_H
#define LEVEL_H

/*
 * level.h – Level-Parameter ableiten
 * -----------------------------------
 * Aufgabe:
 *   Ermittelt aus einer Levelnummer (1..100) die Spielfeld-Parameter:
 *     - width, height  : Spielfeldgröße
 *     - density        : Wanddichte (0..1)
 *     - min_sep        : Mindestabstand P↔T (Chebyshev: |dx|>=sep UND |dy|>=sep)
 *
 * Hinweise zur Skalierung (implementiert in level.c):
 *   - Level 1..10:   10x10
 *   - Level 11..25:  NxN (quadratisch wachsend, z. B. L25 = 25x25)
 *   - Level 26..100: Breite wächst weiter (N), Höhe bleibt 25 (z. B. L50 = 50x25)
 *   - density steigt mit dem Level (konservativ begrenzt, damit spielbar)
 *   - min_sep wächst mit dem Level und wird sinnvoll an die Feldgröße gekappt
 */

typedef struct {
    int    width;     // Spielfeldbreite
    int    height;    // Spielfeldhöhe
    double density;   // Wanddichte 0..1
    int    min_sep;   // Mindestabstand P↔T (Chebyshev)
} LevelParams;

/* Befüllt 'out' mit den Parametern für 'level' (1..100).
 * Rückgabewert: 1 = ok, 0 = ungültiges Level oder out==NULL. */
int level_params_from_level(int level, LevelParams *out);

#endif /* LEVEL_H */
