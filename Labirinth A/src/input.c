#include "input.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

Command input_read_command(void) {
    char buf[128];

    if (!fgets(buf, sizeof(buf), stdin)) // Zeile einlesen
        return CMD_NONE;

    // Erstes nicht-Whitespace-Zeichen suchen
    char c = 0;
    for (size_t i = 0; i < strlen(buf); ++i) {
        if (!isspace((unsigned char)buf[i])) { c = buf[i]; break; }
    }
    if (!c) return CMD_NONE;

    // Großbuchstaben-Variante vergleichen
    c = (char)toupper((unsigned char)c);
    switch (c) {
        case 'W': return CMD_UP;
        case 'A': return CMD_LEFT;
        case 'S': return CMD_DOWN;
        case 'D': return CMD_RIGHT;
        case 'Q': return CMD_QUIT;
        default:  return CMD_NONE;
    }
}
