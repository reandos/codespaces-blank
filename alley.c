#include <stdio.h>

int main() {
    // Notentabelle: 3 Schüler, je 4 Noten
    int noten[3][4] = {
        {3, 4, 2, 1},
        {2, 2, 3, 1},
        {4, 3, 4, 5}
    };

    printf("Schueler | Note 1 | Note 2 | Note 3 | Note 4 | Durchschnitt\n");
    printf("-----------------------------------------------------------\n");

    // Schleife über alle Schüler
    for (int i = 0; i < 3; i++) {
        int summe = 0;
        printf("   %d     |", i + 1);
        for (int j = 0; j < 4; j++) {
            printf("   %d   |", noten[i][j]);
            summe += noten[i][j];
        }
        float durchschnitt = summe / 4.0;
        printf("   %.2f\n", durchschnitt);
    }

    return 0;
