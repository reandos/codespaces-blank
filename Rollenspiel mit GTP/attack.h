#ifndef ATTACK_H
#define ATTACK_H

#include "character.h"
#include "monster.h"

// Angriffsarten (Pflicht: PHYSICAL, MAGICAL; frei: RANGED, POISON)
typedef enum {
    PHYSICAL,
    MAGICAL,
    RANGED,
    POISON
} AttackType;

void performAttack(Character *attacker, Monster *defender, AttackType attackType); // Spieler greift Monster an
void performMonsterAttack(Monster *attacker, Character *defender);                 // Monster greift Spieler an

#endif
