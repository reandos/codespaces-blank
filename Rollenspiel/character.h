#ifndef CHARACTER_H
#define CHARACTER_H

#define MAX_NAME_LENGTH 50

// Statuswerte, die auf einen Charakter wirken können
typedef struct {
    unsigned int poisoned : 1; // 1 = vergiftet, 0 = nicht
    unsigned int stunned  : 1; // 1 = betäubt, 0 = nicht
} StatusEffects;

// Spielercharakter mit Name, Lebenspunkten, Angriffswert und aktuellem Status
typedef struct {
    char name[MAX_NAME_LENGTH]; // Name des Spielers
    int health;                 // Lebenspunkte (HP)
    int attack;                 // Angriffsstärke
    StatusEffects status;       // Effekte wie Gift oder Betäubung
} Character;

// Erstellt den Spielercharakter mit Standardwerten
void createCharacter(Character *character);

// Zeigt die Werte des Charakters auf der Konsole an
void displayCharacter(const Character *character);

#endif
