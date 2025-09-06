#!/bin/bash
# Kompiliert alle .c-Dateien im aktuellen Ordner und startet das Spiel, wenn fehlerfrei

gcc -Wall -o rollenspiel *.c

if [ $? -eq 0 ]; then
    echo "Kompilierung erfolgreich. Starte Spiel..."
    ./rollenspiel
else
    echo "Kompilierung fehlgeschlagen."
fi