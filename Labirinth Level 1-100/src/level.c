#include "../include/level.h"

/*
 * level.c – Berechnung der Level-Parameter (1–100)
 * ------------------------------------------------
 * Verantwortlich für:
 *   • Festlegen der Spielfeldgröße (Breite/Höhe)
 *   • Bestimmen der Wanddichte (density)
 *   • Setzen des Mindestabstands zwischen Spieler (P) und Schatz (T)
 *
 * Logik:
 *   - Level 1–10 : 10x10
 *   - Level 11–25: quadratisch wachsend (NxN, z. B. 25x25)
 *   - Ab 26      : Breite wächst weiter, Höhe bleibt 25 (z. B. 50x25)
 *   - Dichte steigt linear mit Level (max. 0.45)
 *   - Mindestabstand wächst ebenfalls mit Level, wird aber auf
 *     Spielfeldgröße begrenzt, damit die Platzierung immer möglich bleibt.
 */

/* Lineare Interpolation zwischen a und b (für density-Berechnung) */
static double lerp(double a, double b, double t) {
    return a + (b - a) * t;
}

/* Liefert alle Parameter für das angegebene Level (1..100) */
int level_params_from_level(int level, LevelParams *out) {
    if (!out) return 0;
    if (level < 1) level = 1;
    if (level > 100) level = 100;

    /* --- Spielfeldgröße --- */
    int width, height;
    if (level <= 10) {
        width = height = 10;
    } else if (level <= 25) {
        width = height = level;     // 11x11 .. 25x25
    } else {
        width = level;              // 26..100
        height = 25;                // fix ab Level 26
    }
    out->width = width;
    out->height = height;

    /* --- Wanddichte --- 
     * Dichte steigt von 0.12 (Level 1) bis 0.45 (Level 100)
     * (linear interpoliert über 99 Level-Schritte)
     */
    double t = (level - 1) / 99.0;
    out->density = lerp(0.12, 0.45, t);

    /* --- Mindestabstand (Chebyshev-Abstand) ---
     * Start: 5 Felder (Level 1–10)
     * Ab Level 11: wächst um +1 pro Level
     * Maximalwert wird konservativ begrenzt,
     * damit auch bei Höhe 25 gültige Platzierungen existieren.
     */
    int sep = (level <= 10) ? 5 : (5 + (level - 10));

    int min_side = (out->width < out->height) ? out->width : out->height;
    int sep_max = min_side - 5;   // Abstand darf Rand nicht überreizen
    if (sep_max < 1) sep_max = 1;

    if (sep > sep_max) sep = sep_max;
    if (sep < 1) sep = 1;
    out->min_sep = sep;

    return 1;
}
