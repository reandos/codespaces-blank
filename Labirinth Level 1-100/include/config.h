#ifndef CONFIG_H
#define CONFIG_H

/* =====================================================================
 *  config.h  –  Globale Spielkonfiguration
 * ---------------------------------------------------------------------
 *  Enthält alle zentralen Konstanten für das Labirinth-Spiel:
 *   • Standardgröße und Dichte für freien Modus
 *   • Zeichen, die für Spielfelder verwendet werden
 *   • Farbdefinitionen für die Konsolenausgabe (ANSI)
 *
 *  Wenn man im Spiel Farben ändern oder abschalten möchte,
 *  wird das hier eingestellt.
 * ===================================================================== */

// --- Standardwerte für den freien Modus -------------------------------
#define DEFAULT_WIDTH    20      // Standardbreite, wenn kein Level-Modus
#define DEFAULT_HEIGHT   10      // Standardhöhe
#define DEFAULT_DENSITY  0.18    // Wanddichte (0.0 bis 0.6 sinnvoll)

// --- Spielfeld-Zeichen ------------------------------------------------
#define CHAR_EMPTY    ' '   // leeres Feld
#define CHAR_WALL     'O'   // Wandblock
#define CHAR_PLAYER   'P'   // Spieler
#define CHAR_TREASURE 'T'   // Schatz

// --- Titelanzeige (nur kosmetisch) -----------------------------------
#define GAME_TITLE "Labirinth Level 1-100"

// =====================================================================
//  Farbkonfiguration (ANSI-Farben)
// ---------------------------------------------------------------------
//  USE_COLOR = 1  → Farben aktiv
//  USE_COLOR = 0  → Farben aus (Monochrom)
// =====================================================================
#ifndef USE_COLOR
#define USE_COLOR 1
#endif

#if USE_COLOR
    // ANSI Escape-Sequenzen für farbige Ausgabe:
    #define COLOR_RESET  "\x1b[0m"   // Standardfarbe wiederherstellen
    #define COLOR_RED    "\x1b[31m"  // Spieler (P)
    #define COLOR_YELLOW "\x1b[33m"  // Schatz (T)
    #define COLOR_GRAY   "\x1b[90m"  // Wände (O)
#else
    // Falls Farben deaktiviert: keine Farbcodes ausgeben
    #define COLOR_RESET  ""
    #define COLOR_RED    ""
    #define COLOR_YELLOW ""
    #define COLOR_GRAY   ""
#endif

#endif
