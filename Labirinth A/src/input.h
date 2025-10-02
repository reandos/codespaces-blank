#ifndef INPUT_H
#define INPUT_H

// Mögliche Befehle des Spielers
typedef enum {
    CMD_NONE = 0, // ungültig / keine Eingabe
    CMD_UP,
    CMD_LEFT,
    CMD_DOWN,
    CMD_RIGHT,
    CMD_QUIT
} Command;

// Liest eine Eingabezeile und wandelt das erste relevante Zeichen in einen Command um
Command input_read_command(void);

#endif // INPUT_H
