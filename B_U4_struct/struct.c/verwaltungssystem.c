#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 3     // Anzahl der zu verwaltenden Studenten

/*-----------------------------------------------------------
 *  Strukturdefinition
 *----------------------------------------------------------*/
typedef struct {
    int   matrikelnummer;
    char  name[50];
    float durchschnittsnote;
} Student;

/*-----------------------------------------------------------
 *  Funktionsprototypen
 *----------------------------------------------------------*/
void    printStudent(Student s);
Student  createStudent(int matrikelnummer,
                       const char name[],
                       float durchschnittsnote);

/*-----------------------------------------------------------
 *  Hauptprogramm
 *----------------------------------------------------------*/
int main(void)
{
    Student studenten[MAX_STUDENTS];

    /* Drei Studenten anlegen – hier statisch,
       könnte später auch per Benutzereingabe erfolgen */
    studenten[0] = createStudent(1001, "Anna Müller",   5.0f);
    studenten[1] = createStudent(1002, "Ben Schneider", 4.8f);
    studenten[2] = createStudent(1003, "Cem Yilmaz",    5.3f);

    /* Informationen ausgeben */
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        printStudent(studenten[i]);
    }

    return 0;
}

/*-----------------------------------------------------------
 *  Funktionsdefinitionen
 *----------------------------------------------------------*/
Student createStudent(int matrikelnummer,
                      const char name[],
                      float durchschnittsnote)
{
    Student s;
    s.matrikelnummer     = matrikelnummer;
    strncpy(s.name, name, sizeof(s.name) - 1);  // sicher kopieren
    s.name[sizeof(s.name) - 1] = '\0';          // Null-Terminierung
    s.durchschnittsnote  = durchschnittsnote;
    return s;
}

void printStudent(Student s)
{
    printf("Matrikelnummer : %d\n",   s.matrikelnummer);
    printf("Name           : %s\n",   s.name);
    printf("Durchschnitt   : %.2f\n\n", s.durchschnittsnote);
}