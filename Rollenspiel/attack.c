#include <stdio.h>
#include "attack.h"

// Spieler greift Monster an
void performAttack(Character *attacker, Monster *defender, AttackType attackType)
{
    int schaden = 0;
    printf("---- Kampf (Spieler greift an) ----\n");

    // Schaden abhängig von der Angriffsart berechnen
    switch (attackType) {
        case PHYSICAL: schaden = attacker->attack; break;                 // normal
        case MAGICAL:  schaden = (int)(attacker->attack * 1.5); break;    // stärker
        case RANGED:   schaden = (attacker->attack * 4) / 5; break;       // leichter
        case POISON:   schaden = (attacker->attack * 7) / 10; break;      // mit Gift
    }

    if (schaden < 0) schaden = 0;
    defender->health -= schaden;
    if (defender->health < 0) defender->health = 0;

    printf("Schaden am Monster: %d (HP verbleibend: %d)\n", schaden, defender->health);
}

// Monster greift Spieler an
void performMonsterAttack(Monster *attacker, Character *defender)
{
    printf("---- Kampf (Monster greift an) ----\n");
    int schaden = attacker->attack;
    defender->health -= schaden;
    if (defender->health < 0) defender->health = 0;
    printf("%s verursacht %d Schaden. Spieler-HP: %d\n", attacker->name, schaden, defender->health);
}
