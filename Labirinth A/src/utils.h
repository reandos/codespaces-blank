#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>

// Initialisiert den Zufallsgenerator (einmalig)
void utils_seed_random(void);

// Ganzzahl im Bereich [min, max] (inklusive) liefern
int  utils_rand_int(int min_inclusive, int max_inclusive);

// Mit Wahrscheinlichkeit p (0..1) true zurückgeben
bool utils_rand_chance(double probability);

// Speicherallokatoren mit Abbruch bei Fehler (einfaches Fehler-Handling)
void* xmalloc(size_t size);
void* xcalloc(size_t n, size_t size);

#endif // UTILS_H
