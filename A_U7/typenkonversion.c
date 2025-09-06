#include <stdio.h>
int main() 
{
    // Implizite Typkonvertierung (Automatic Type Conversion)
    int a = 10;
    double b = 5.5;
    double result;

    // Int wird implizit in double konvertiert
    result = a + b;
    printf("Implizite Typkonvertierung: %d + %.1f = %.1f\n", a, b, result);

    // Explizite Typkonvertierung (Type Casting)
    double x = 9.7;
    int y;

    // Double wird explizit in int konvertiert
    y = (int)x;
    printf("Explizite Typkonvertierung: (int)%.1f = %d\n", x, y);

    // Ein weiteres Beispiel für explizite Typkonvertierung
    char c = 'A';
    int ascii_value;

    // Char wird explizit in int konvertiert, um den ASCII-Wert zu erhalten
    ascii_value = (int)c;
    printf("ASCII-Wert von '%c' = %d\n", c, ascii_value);

    // Konvertierung von int zu float
    int m = 3;
    float n;

    // Int wird explizit in float konvertiert
    n = (float)m;
    printf("Explizite Typkonvertierung: (float)%d = %.1f\n", m, n);
    return 0;
}