#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "monster.h"
#include "attack.h"

// Fragt die Angriffsart vom Spieler ab (Physisch, Magisch, Fernkampf, Gift)
void selectAttack(AttackType *attackType);

// Fragt den Spieler, gegen welches lebende Monster er kämpfen will
void selectMonster(Monster *monsters, int numMonsters, int *selectedMonster);

// Hauptspielablauf: Spieler kämpft, bis er oder alle Monster tot sind
void startGame(Character *player, Monster *monsters, int numMonsters);

#endif
