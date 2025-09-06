#include <stdio.h>

// Funktionsdefinitionen
int addiere(int a, int b) {
    return a + b;
}

int subtrahiere(int a, int b) {
    return a - b;
}

int multipliziere(int a, int b) {
    return a * b;
}

int dividiere(int a, int b) {
    if (b == 0) {
        printf("Fehler: Division durch 0 ist nicht erlaubt.\n");
        return 0; // oder einen speziellen Fehlercode
    }
    return a / b;
}

// Hauptfunktion
int main() {
    int a = 8, b = 2;

    printf("Addiere: %d + %d = %d\n", a, b, addiere(a, b));
    printf("Subtrahiere: %d - %d = %d\n", a, b, subtrahiere(a, b));
    printf("Multipliziere: %d * %d = %d\n", a, b, multipliziere(a, b));
    printf("Dividiere: %d / %d = %d\n", a, b, dividiere(a, b));

    // Test Division durch 0
    printf("Dividiere: %d / %d = %d\n", a, 0, dividiere(a, 0));

    return 0;
}
