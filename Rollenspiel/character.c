#include <stdio.h>
#include "character.h"

// Erstellt den Spielercharakter mit Standardwerten
void createCharacter(Character *character)
{
    printf("Geben Sie den Namen Ihres Charakters ein: ");
    if (scanf("%49s", character->name) != 1) {
        fprintf(stderr, "Fehler bei der Eingabe des Namens!\n");
        return;
    }

    // Startwerte setzen
    character->health = 100;      // volle Lebenspunkte
    character->attack = 20;       // Standard-Angriffsstärke
    character->status.poisoned = 0; // kein Gift zu Beginn
    character->status.stunned  = 0; // nicht betäubt

    // Hinweis: Anzeige kommt in main.c nach dem Erstellen
}

// Gibt die Werte des Spielers auf der Konsole aus
void displayCharacter(const Character *character)
{
    printf("---- Spieler ----\n");
    printf("Name: %s\n", character->name);
    printf("Gesundheit: %d\n", character->health);
    printf("Angriff: %d\n", character->attack);
    printf("Status: Vergiftet=%u, Betäubt=%u\n",
           character->status.poisoned, character->status.stunned);
}
