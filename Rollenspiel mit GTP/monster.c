#include <stdio.h>
#include <string.h>
#include "monster.h"

void createMonster(Monster *monster, const char *name, int health, int attack) {
    // Monster definieren: Name, Lebenspunkte, Angriff, Status zurücksetzen
    snprintf(monster->name, sizeof(monster->name), "%s", name);
    monster->health = health;
    monster->attack = attack;
    monster->status.poisoned = 0;
    monster->status.stunned  = 0;
}

void displayMonster(const Monster *monster) {
    // Kurze Monsteranzeige inkl. Zustände
    printf("%s (HP: %d, ATK: %d", monster->name, monster->health, monster->attack);
    if (monster->status.poisoned || monster->status.stunned) {
        printf(", Status:");
        if (monster->status.poisoned) printf(" Vergiftet");
        if (monster->status.stunned)  printf(" Betäubt");
    }
    printf(")\n");
}

void createMonsters(Monster *monsters, int numMonsters) {
    // Beispiel-Liste (kannst du anpassen/erweitern)
    if (numMonsters >= 1) createMonster(&monsters[0], "Goblin", 50, 10);
    if (numMonsters >= 2) createMonster(&monsters[1], "Troll", 80, 15);
    if (numMonsters >= 3) createMonster(&monsters[2], "Drache", 120, 25);
}
