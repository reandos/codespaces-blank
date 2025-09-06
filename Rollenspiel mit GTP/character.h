#ifndef CHARACTER_H
#define CHARACTER_H

#define MAX_NAME_LENGTH 50

typedef struct {
    unsigned int poisoned : 1; // Vergiftung aktiv?
    unsigned int stunned  : 1; // Betäubt (eine Runde aussetzen)?
} StatusEffects;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int  health;               // Lebenspunkte des Spielers
    int  attack;               // Grundangriff des Spielers
    StatusEffects status;      // Zustände (Gift/Betäubung)
} Character;

void createCharacter(Character *character);          // Spieler erstellen (Name, Startwerte)
void displayCharacter(const Character *character);   // Spielerwerte anzeigen
void resetCharacterStats(Character *character);      // Spieler auf Startwerte zurücksetzen

#endif
