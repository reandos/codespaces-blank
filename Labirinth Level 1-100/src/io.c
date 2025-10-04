#include "../include/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * io.c – Konsolen-Ein-/Ausgabe und Zufallsgenerator
 * -------------------------------------------------
 * Dieses Modul stellt einfache I/O-Funktionen bereit, die im gesamten Spiel
 * verwendet werden:
 *
 *   • io_read_line()    – liest Tastatureingaben (z. B. W/A/S/D)
 *   • io_clear_screen() – löscht den Bildschirm (ANSI-Codes)
 *   • io_seed_rng()     – initialisiert den Zufallszahlengenerator
 *   • io_rand01()       – liefert Zufallswert im Bereich [0.0, 1.0)
 *
 * Wird von game.c und maze.c genutzt.
 */

/* ------------------------------------------------------------
 * Liest eine Textzeile bis '\n' oder EOF aus stdin.
 * Rückgabewert: Anzahl gelesener Zeichen (ohne '\n'),
 * oder 0, wenn EOF oder keine Eingabe.
 * ------------------------------------------------------------ */
int io_read_line(char *buf, int bufsize) {
    if (!buf || bufsize <= 0) return 0;

    if (!fgets(buf, bufsize, stdin)) return 0; // EOF oder Fehler

    int len = 0;
    while (buf[len] != '\0') {
        if (buf[len] == '\n') { // Newline entfernen
            buf[len] = '\0';
            break;
        }
        len++;
    }
    return len;
}

/* ------------------------------------------------------------
 * Löscht den Terminalbildschirm (ANSI-Sequenzen):
 *   ESC[2J – löscht Bildschirm
 *   ESC[H  – setzt Cursor auf Position (1,1)
 * ------------------------------------------------------------ */
void io_clear_screen(void) {
    printf("\x1b[2J\x1b[H");
    fflush(stdout);
}

/* ------------------------------------------------------------
 * Initialisiert den Zufallszahlengenerator mit aktueller Zeit.
 * Wird typischerweise einmal im Programmstart aufgerufen.
 * ------------------------------------------------------------ */
void io_seed_rng(void) {
    srand((unsigned)time(NULL));
}

/* ------------------------------------------------------------
 * Gibt Zufallszahl im Bereich [0.0, 1.0) zurück.
 * ------------------------------------------------------------ */
double io_rand01(void) {
    return (double)rand() / (double)RAND_MAX;
}
