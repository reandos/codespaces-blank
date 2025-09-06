#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "monster.h"
#include "attack.h"

void startGame(Character *player, Monster *monsters, int numMonsters);           // Gesamtablauf
void selectAttack(AttackType *attackType);                                       // Menü: Angriff wählen
void selectMonster(Monster *monsters, int numMonsters, int *selectedMonster);    // Menü: Monster wählen
int  postVictoryMenu(Character *player, Monster *monsters, int numMonsters);     // Sieg-Menü: weiter/neu/exit

#endif
