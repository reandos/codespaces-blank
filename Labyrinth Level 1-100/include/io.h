#ifndef IO_H
#define IO_H

/*
 * io.h – Konsolen-Ein-/Ausgabe und Zufallsfunktionen
 * ---------------------------------------------------
 * Aufgaben:
 *   - Einlesen von Tastatureingaben (z. B. W, A, S, D, Q)
 *   - Löschen des Terminalbildschirms (ANSI-Sequenzen)
 *   - Initialisierung und Nutzung des Zufallszahlengenerators
 *
 * Verwendung:
 *   Wird von maze.c (für Zufallswände/Positionen) und game.c
 *   (für Eingabeverarbeitung + Bildschirmupdate) benutzt.
 */

/* Liest eine Zeile Text (bis Enter oder EOF).
 * Gibt die Länge ohne '\n' zurück oder 0, wenn nichts gelesen wurde. */
int io_read_line(char *buf, int bufsize);

/* Löscht den Terminalbildschirm (ANSI-Sequenz "\x1b[2J\x1b[H") */
void io_clear_screen(void);

/* Initialisiert den Zufallszahlengenerator mit Systemzeit (srand(time)) */
void io_seed_rng(void);

/* Liefert Zufallswert zwischen 0.0 und 1.0 (gleichmäßig verteilt) */
double io_rand01(void);

#endif /* IO_H */
