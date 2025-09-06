#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 3

/*-----------------------------------------------------------
 * Strukturdefinitionen
 *----------------------------------------------------------*/
typedef struct {
    int tag;
    int monat;
    int jahr;
} Geburtstag;

typedef struct {
    int matrikelnummer;
    char name[50];
    float durchschnittsnote;
    Geburtstag geburtstag;  // verschachtelte Struktur
} Student;

/*-----------------------------------------------------------
 * Funktionsprototypen
 *----------------------------------------------------------*/
void printStudent(Student s);
Student createStudent(int matrikelnummer, const char name[], float durchschnittsnote,
                      int tag, int monat, int jahr);

/*-----------------------------------------------------------
 * Hauptfunktion
 *----------------------------------------------------------*/
int main(void) {
    Student studenten[MAX_STUDENTS];

    studenten[0] = createStudent(1001, "Anna Müller",   4.7f, 12, 5, 2000);
    studenten[1] = createStudent(1002, "Ben Schneider", 4.3f, 3,  11, 1999);
    studenten[2] = createStudent(1003, "Cem Yilmaz",    5.3f, 25, 2, 2001);

    for (int i = 0; i < MAX_STUDENTS; i++) {
        printStudent(studenten[i]);
    }

    return 0;
}

/*-----------------------------------------------------------
 * Student erstellen
 *----------------------------------------------------------*/
Student createStudent(int matrikelnummer, const char name[], float durchschnittsnote,
                      int tag, int monat, int jahr) {
    Student s;
    s.matrikelnummer = matrikelnummer;
    strncpy(s.name, name, sizeof(s.name) - 1);
    s.name[sizeof(s.name) - 1] = '\0';
    s.durchschnittsnote = durchschnittsnote;

    s.geburtstag.tag = tag;
    s.geburtstag.monat = monat;
    s.geburtstag.jahr = jahr;

    return s;
}

/*-----------------------------------------------------------
 * Studentendaten ausgeben
 *----------------------------------------------------------*/
void printStudent(Student s) {
    printf("Matrikelnummer : %d\n", s.matrikelnummer);
    printf("Name           : %s\n", s.name);
    printf("Durchschnitt   : %.2f\n", s.durchschnittsnote);
    printf("Geburtstag     : %02d.%02d.%04d\n\n",
           s.geburtstag.tag, s.geburtstag.monat, s.geburtstag.jahr);
}