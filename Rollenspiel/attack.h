#ifndef ATTACK_H
#define ATTACK_H

#include "character.h"
#include "monster.h"

// Angriffsarten, die der Spieler wählen kann
typedef enum {
    PHYSICAL, // normaler Schaden, kein Effekt
    MAGICAL,  // erhöhter Schaden
    RANGED,   // etwas weniger Schaden, evtl. Betäubung
    POISON    // etwas weniger Schaden, Gift-DoT
} AttackType;

// Führt einen Angriff vom Spieler auf ein Monster aus
void performAttack(Character *attacker, Monster *defender, AttackType attackType);

// Führt einen Angriff vom Monster auf den Spieler aus
void performMonsterAttack(Monster *attacker, Character *defender);

#endif
