#include <stdio.h>
#include "character.h"

void createCharacter(Character *character)
{
    // Name einlesen
    printf("Geben Sie den Namen Ihres Charakters ein: ");
    if (scanf("%49s", character->name) != 1) {
        fprintf(stderr, "Fehler bei der Eingabe des Namens!\n");
        return;
    }

    // Startwerte setzen
    character->health = 100;
    character->attack = 20;
    character->status.poisoned = 0;
    character->status.stunned  = 0;
}

void displayCharacter(const Character *character)
{
    // Spielerwerte + Zustände ausgeben
    printf("---- Character ----\n");
    printf("Name: %s\n", character->name);
    printf("Gesundheit: %d\n", character->health);
    printf("Angriff: %d\n", character->attack);
    printf("Status: Vergiftet: %u, Betäubt: %u\n",
           character->status.poisoned, character->status.stunned);
}

void resetCharacterStats(Character *character)
{
    // Neustart: Werte zurücksetzen (Name bleibt)
    character->health = 100;
    character->attack = 20;
    character->status.poisoned = 0;
    character->status.stunned  = 0;
}
