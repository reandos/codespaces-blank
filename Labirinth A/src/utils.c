#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>   // für uintptr_t

// Initialisiert den Zufallsgenerator (nur einmal pro Programmaufruf)
void utils_seed_random(void) {
    static bool seeded = false;
    if (!seeded) {                                   // nur beim ersten Aufruf
        seeded = true;
        unsigned int seed = (unsigned int)(time(NULL) ^ (uintptr_t)&seeded);
        srand(seed);                                 // Zufallsgenerator starten
    }
}

// Liefert eine Zufallszahl im Bereich [min_inclusive, max_inclusive]
int utils_rand_int(int min_inclusive, int max_inclusive) {
    if (max_inclusive < min_inclusive) {             // falls vertauscht, umdrehen
        int tmp = min_inclusive;
        min_inclusive = max_inclusive;
        max_inclusive = tmp;
    }
    int span = max_inclusive - min_inclusive + 1;    // mögliche Werteanzahl
    return min_inclusive + (rand() % span);          // Wert in [min, max]
}

// Liefert true mit Wahrscheinlichkeit p (0.0–1.0)
bool utils_rand_chance(double probability) {
    if (probability <= 0.0) return false;            // niemals
    if (probability >= 1.0) return true;             // immer
    return ((double)rand() / (double)RAND_MAX) < probability;
}

// Speicher allozieren, beendet Programm bei Fehler
void* xmalloc(size_t size) {
    void* p = malloc(size);
    if (!p) {
        fprintf(stderr, "Out of memory (malloc %zu)\n", size);
        exit(EXIT_FAILURE);
    }
    return p;
}

// Speicher allozieren (n Elemente), beendet Programm bei Fehler
void* xcalloc(size_t n, size_t size) {
    void* p = calloc(n, size);
    if (!p) {
        fprintf(stderr, "Out of memory (calloc %zu x %zu)\n", n, size);
        exit(EXIT_FAILURE);
    }
    return p;
}
