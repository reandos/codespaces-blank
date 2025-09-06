#include <stdio.h>

int main() {
    int zahl1, zahl2;

    // Benutzer-Eingabe
    printf("Gib die erste Zahl ein: ");
    scanf("%d", &zahl1);

    printf("Gib die zweite Zahl ein: ");
    scanf("%d", &zahl2);

    // Vergleich und Ausgabe
    if (zahl1 > zahl2) {
        printf("Die Grössere Zahl ist: %d\n", zahl1);
    } else if (zahl2 > zahl1) {
        printf("Die Grössere Zahl ist: %d\n", zahl2);
    } else {
        printf("Beide Zahlen sind gleich: %d\n", zahl1);
    }

    return 0;
}