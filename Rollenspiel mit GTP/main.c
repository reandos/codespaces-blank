#include <stdio.h>
#include "character.h"
#include "monster.h"
#include "game.h"

int main(void) {
    // Spieler anlegen und anzeigen
    Character player;
    createCharacter(&player);
    displayCharacter(&player);

    // Monsterliste erstellen (Anzahl flexibel)
    int numMonsters = 3;
    Monster monsters[numMonsters];
    createMonsters(monsters, numMonsters);

    // Spiel starten
    startGame(&player, monsters, numMonsters);
    return 0;
}
