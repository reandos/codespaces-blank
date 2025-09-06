#include <stdio.h>

// Funktion mit auto-Variable
void meineFunktion() {
    auto int a = 5;    // 'a' ist eine automatische Variable (wird bei jedem Aufruf neu erstellt)
    int b = 10;        // auch ohne 'auto' automatisch (Standard)

    printf("Wert von a: %d\n", a);  // gibt immer 5 aus
    printf("Wert von b: %d\n", b);  // gibt immer 10 aus
}


int main() {
    printf("Erster Aufruf:\n");
    meineFunktion();   // Variablen a und b werden erstellt und nach Ende wieder gelöscht

    printf("\nZweiter Aufruf:\n");
    meineFunktion();   // a und b werden NEU erstellt → wieder 5 und 10

    return 0;
}
