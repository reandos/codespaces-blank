#include <stdio.h>
#include "game.h"
#include "attack.h"

// Zählt, wie viele Monster noch leben
static int countAliveMonsters(Monster *monsters, int n) {
    int alive = 0;
    for (int i = 0; i < n; ++i)
        if (monsters[i].health > 0)
            ++alive;
    return alive;
}

// Fragt den Spieler nach der Angriffsart (1-4)
void selectAttack(AttackType *attackType)
{
    int wahl;
    printf("\nWähle die Angriffsart:\n");
    printf("  1: Physisch (normaler Schaden)\n");
    printf("  2: Magisch (stärkerer Schaden)\n");
    printf("  3: Fernkampf (leichter Schaden, evtl. Betäubung)\n");
    printf("  4: Gift (schwächerer Schaden, verursacht DoT)\n");
    do {
        printf("Eingabe (1-4): ");
        if (scanf("%d", &wahl) != 1) { while (getchar()!='\n'); wahl = 0; }
    } while (wahl < 1 || wahl > 4);

    *attackType = (AttackType)(wahl - 1); // AttackType-Enum startet bei 0
}

// Lässt den Spieler ein lebendes Monster zum Angriff auswählen
void selectMonster(Monster *monsters, int numMonsters, int *selectedMonster)
{
    printf("\nVerfügbare Monster:\n");
    for (int i = 0; i < numMonsters; ++i) {
        printf("  %d) %s (HP: %d, ATK: %d)\n", i + 1, monsters[i].name, monsters[i].health, monsters[i].attack);
    }

    int wahl;
    do {
        printf("Gegen welches Monster kämpfen? (1-%d): ", numMonsters);
        if (scanf("%d", &wahl) != 1) { while (getchar()!='\n'); wahl = 0; }
    } while (wahl < 1 || wahl > numMonsters || monsters[wahl-1].health <= 0);

    *selectedMonster = wahl - 1;
}

// Hauptspielschleife: Kämpfe bis Spieler oder alle Monster tot sind
void startGame(Character *player, Monster *monsters, int numMonsters)
{
    // Spiel läuft, solange Spieler lebt und noch Monster übrig sind
    while (player->health > 0 && countAliveMonsters(monsters, numMonsters) > 0) {
        int idx;
        selectMonster(monsters, numMonsters, &idx);
        Monster *m = &monsters[idx];

        // Kampf gegen das gewählte Monster
        while (player->health > 0 && m->health > 0) {
            AttackType type;
            selectAttack(&type);          // Spieler wählt Angriff
            performAttack(player, m, type); // Spieler greift Monster an

            if (m->health <= 0) {
                printf("%s wurde besiegt!\n", m->name);
                break; // Monster tot → nächsten Gegner wählen
            }

            performMonsterAttack(m, player); // Monster greift zurück
            if (player->health <= 0) {
                printf("Der Spieler wurde besiegt!\n");
                break; // Spieler tot → Spielende
            }
        }
    }

    // Ergebnisnachricht
    if (player->health > 0)
        printf("\nAlle Monster besiegt – du gewinnst!\n");
    else
        printf("\nDu hast verloren.\n");
}
