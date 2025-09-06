#include <stdio.h>
#include "attack.h"

void performAttack(Character *attacker, Monster *defender, AttackType attackType) {
    int damage = 0;

    // Schaden berechnen & direkt anwenden
    switch (attackType) {
        case PHYSICAL:  // Physisch: Schaden = Angriff
            damage = attacker->attack;
            printf("Physischer Angriff! Schaden: %d\n", damage);
            break;

        case MAGICAL:   // Magisch: Schaden = 1.5 × Angriff
            damage = (int)(attacker->attack * 1.5);
            printf("Magischer Angriff! Schaden: %d\n", damage);
            break;

        case RANGED:    // Fernkampf: etwas geringer, hier -5 (nicht negativ werden)
            damage = attacker->attack - 5;
            if (damage < 0) damage = 0;
            printf("Fernkampfangriff! Schaden: %d\n", damage);
            break;

        case POISON:    // Gift: Sofortschaden + Status einschalten (DoT kommt in game.c)
            damage = attacker->attack / 2;
            if (damage < 0) damage = 0;
            defender->status.poisoned = 1; // wichtig: DoT aktivieren
            printf("Giftangriff! Sofortschaden: %d (Gegner ist vergiftet)\n", damage);
            break;
    }

    defender->health -= damage;
    if (defender->health < 0) defender->health = 0;
}

void performMonsterAttack(Monster *attacker, Character *defender) {
    // Monsterangriff (ohne Sonderlogik; Betäubung würdest du hier prüfen, falls du sie nutzt)
    int damage = attacker->attack;
    printf("%s greift an! Schaden: %d\n", attacker->name, damage);
    defender->health -= damage;

    // Falls Spieler irgendwann vergiftet wäre: DoT auf Spieler anwenden
    if (defender->status.poisoned) {
        printf("Gift wirkt! %s verliert 3 HP.\n", defender->name);
        defender->health -= 3;
    }

    if (defender->health < 0) defender->health = 0;
}
