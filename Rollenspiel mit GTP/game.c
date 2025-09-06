#include <stdio.h>
#include "game.h"

// Eingabepuffer leeren (für saubere scanf-Nutzung)
static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Menü: Angriff wählen
void selectAttack(AttackType *attackType) {
    int choice;
    printf("Wähle Angriffsart:\n");
    printf("1. Physisch (Basis-Schaden)\n");
    printf("2. Magisch (1.5x Schaden)\n");
    printf("3. Fernkampf (etwas weniger Schaden)\n");
    printf("4. Gift (Sofortschaden + DoT)\n");
    printf("Auswahl: ");
    if (scanf("%d", &choice) != 1) {
        clearInputBuffer();
        choice = 1;
    }
    clearInputBuffer();

    switch (choice) {
        case 1: *attackType = PHYSICAL; break;
        case 2: *attackType = MAGICAL;  break;
        case 3: *attackType = RANGED;   break;
        case 4: *attackType = POISON;   break;
        default: *attackType = PHYSICAL; break;
    }
}

// Menü: Monster wählen (zeigt nur lebende)
void selectMonster(Monster *monsters, int numMonsters, int *selectedMonster) {
    printf("\nWähle ein Monster:\n");
    for (int i = 0; i < numMonsters; i++) {
        if (monsters[i].health > 0) {
            printf("%d. ", i + 1);
            displayMonster(&monsters[i]);
        }
    }
    printf("Auswahl: ");
    if (scanf("%d", selectedMonster) != 1) {
        clearInputBuffer();
        *selectedMonster = -1;
    } else {
        clearInputBuffer();
        *selectedMonster -= 1; // 1-basierte Eingabe -> 0-basiert
    }
}

// Sieg-Menü: weiterkämpfen / neu starten / beenden
// Rückgabe: 1=weiter, 2=neu, 3=exit
int postVictoryMenu(Character *player, Monster *monsters, int numMonsters) {
    printf("\n=== Status nach dem Kampf ===\n");
    displayCharacter(player);

    printf("\nVerbleibende Monster:\n");
    int remaining = 0;
    for (int i = 0; i < numMonsters; i++) {
        if (monsters[i].health > 0) {
            displayMonster(&monsters[i]);
            remaining++;
        }
    }
    if (remaining == 0) printf("(Keine – alle besiegt)\n");

    int choice = 0;
    do {
        printf("\nWas möchtest du tun?\n");
        printf("1. Weiterkämpfen (nächstes Monster wählen)\n");
        printf("2. Neu starten (Werte resetten, alle Monster neu)\n");
        printf("3. Beenden\n");
        printf("Auswahl: ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            choice = 0;
        } else {
            clearInputBuffer();
        }
    } while (choice < 1 || choice > 3);

    return choice;
}

// Gesamtablauf des Spiels
void startGame(Character *player, Monster *monsters, int numMonsters) {
    for (;;) { // erlaubt Neustarts über das Sieg-Menü
        // Prüfen: leben noch Monster?
        int aliveMonsters = 0;
        for (int i = 0; i < numMonsters; i++) {
            if (monsters[i].health > 0) aliveMonsters++;
        }

        if (aliveMonsters == 0) {
            printf("\nAlle Monster besiegt! Du hast gewonnen!\n");
            int ch = postVictoryMenu(player, monsters, numMonsters);
            if (ch == 2) {
                resetCharacterStats(player);
                createMonsters(monsters, numMonsters);
                continue;
            } else if (ch == 3) {
                printf("Spiel beendet.\n");
                break;
            } else {
                printf("Es sind keine Monster mehr übrig. Spiel beendet.\n");
                break;
            }
        }

        // Monster wählen
        int selectedMonster;
        selectMonster(monsters, numMonsters, &selectedMonster);
        if (selectedMonster < 0 || selectedMonster >= numMonsters || monsters[selectedMonster].health <= 0) {
            printf("Ungültige Auswahl.\n");
            continue;
        }

        // Vor dem Kampf: Spielerwerte zeigen
        printf("\n--- Vor dem Kampf ---\n");
        displayCharacter(player);
        printf("---------------------\n");

        // Kampfschleife
        while (player->health > 0 && monsters[selectedMonster].health > 0) {
            AttackType attackType;
            selectAttack(&attackType);

            // Deine Attacke
            performAttack(player, &monsters[selectedMonster], attackType);

            // Gift-DoT auf Monster
            if (monsters[selectedMonster].health > 0 && monsters[selectedMonster].status.poisoned) {
                printf("%s leidet unter Gift und verliert 3 HP!\n", monsters[selectedMonster].name);
                monsters[selectedMonster].health -= 3;
                if (monsters[selectedMonster].health < 0) monsters[selectedMonster].health = 0;
            }

            // Status nach deiner Attacke anzeigen
            printf("\n[Status nach deiner Attacke]\n");
            displayMonster(&monsters[selectedMonster]);
            displayCharacter(player);
            printf("-----------------------------\n");

            // Monster greift an, falls noch am Leben
            if (monsters[selectedMonster].health > 0) {
                performMonsterAttack(&monsters[selectedMonster], player);

                // Status nach Monsterattacke anzeigen
                printf("\n[Status nach Monster-Attacke]\n");
                displayMonster(&monsters[selectedMonster]);
                displayCharacter(player);
                printf("-----------------------------\n");
            }
        }

        // Kampfende: Auswertung
        if (player->health <= 0) {
            printf("\nDu wurdest besiegt! Spiel vorbei.\n");
            int ch = postVictoryMenu(player, monsters, numMonsters);
            if (ch == 2) {
                resetCharacterStats(player);
                createMonsters(monsters, numMonsters);
                continue;
            } else {
                printf("Spiel beendet.\n");
                break;
            }
        } else {
            printf("\n%s wurde besiegt!\n", monsters[selectedMonster].name);
            int ch = postVictoryMenu(player, monsters, numMonsters);
            if (ch == 1) {
                continue;
            } else if (ch == 2) {
                resetCharacterStats(player);
                createMonsters(monsters, numMonsters);
                continue;
            } else {
                printf("Spiel beendet.\n");
                break;
            }
        }
    }
}
