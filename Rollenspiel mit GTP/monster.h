#ifndef MONSTER_H
#define MONSTER_H

#include "character.h"   // Für StatusEffects

#define MAX_MONSTER_NAME 50

typedef struct {
    char name[MAX_MONSTER_NAME];
    int  health;           // Lebenspunkte des Monsters
    int  attack;           // Grundangriff des Monsters
    StatusEffects status;  // Zustände (Gift/Betäubung) beim Monster
} Monster;

void createMonster(Monster *monster, const char *name, int health, int attack); // Monster definieren: Name/HP/ATK
void displayMonster(const Monster *monster);                                     // Monsterwerte anzeigen
void createMonsters(Monster *monsters, int numMonsters);                         // Beispiel-Monsterliste füllen

#endif
