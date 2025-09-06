#include <stdio.h>
#include "character.h"
#include "monster.h"
#include "game.h"

int main(void)
{
    Character player;         // Spielercharakter
    Monster monsters[3];      // Liste der Monster
    int numMonster = 3;       // Anzahl der Monster

    printf("Willkommen zum textbasierten Rollenspiel Spieler gegen Monster:\n\n");

    // Spielercharakter erstellen
    createCharacter(&player);

    // Drei Monster mit Namen, HP und ATK-Werten definieren
    createMonster(&monsters[0], "Monster 1", 83, 10);
    createMonster(&monsters[1], "Monster 2", 55, 5);
    createMonster(&monsters[2], "Monster 3", 70, 8);

    printf("\nDas Spiel beginnt....\n");

    // Hauptspiel starten
    startGame(&player, monsters, numMonster);

    return 0;
}
