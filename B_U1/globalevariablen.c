#include <stdio.h>




// Funktion zum Einzahlen eines Betrags
void einzahlen()
{
  float betrag; // Lokale Variable
  printf("Geben Sie den Betrag zum Einzahlen ein: ");
  scanf("%f", &betrag);

  // Einzahlen
  kontostand += betrag; // Der globale Kontostand wird verändert

  printf("Neuer Kontostand nach Einzahlung: %.2f\n", kontostand);
}

// Funktion zum Abheben eines Betrags
void abheben()
{
  float betrag; // Lokale Variable
  printf("Geben Sie den Betrag zum Abheben ein: ");
  scanf("%f", &betrag);

  // Abheben
  if (betrag <= kontostand)
  {
    kontostand -= betrag; // Der globale Kontostand wird verändert
    printf("Neuer Kontostand nach Abhebung: %.2f\n", kontostand);
  }
  else
  {
    printf("Nicht genügend Guthaben!\n");
  }
}

int main()
{
  printf("Startkontostand: %.2f\n", kontostand);

  // Einzahlung durchführen
  einzahlen();

  // Abhebung durchführen
  abheben();

  // Endkontostand anzeigen
  printf("Endkontostand: %.2f\n", kontostand);

  return 0;
}