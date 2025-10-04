Labirinth Level 1–100 (C, Konsole)

Ein textbasiertes Labyrinth-Spiel. Ziel ist es, mit P den Schatz T zu erreichen.
Steuerung: W / A / S / D (Bewegung), Q (Beenden)

------------------------------------------------------------
FEATURES / LEVEL-LOGIK
------------------------------------------------------------
- Level 1–10:  Spielfeld ist 10x10.
- Level 11–25: Feldgröße wächst quadratisch (z. B. Level 20 = 20×20, Level 25 = 25×25).
- Ab Level 26: Nur die Breite wächst weiter (z. B. Level 50 = 50×25, Level 100 = 100×25).
- Hindernisdichte steigt linear von Level 1 bis 100 (spielbar begrenzt < 0.6).
- Mindestabstand P–T in X und Y (Chebyshev):
  • Level 1–10 → mind. 5  
  • Danach +1 pro Level (bis zum Limit der Feldhöhe)
- BFS-Check:  Jedes Level ist garantiert lösbar.
- Farben:
  • P = rot • T = gelb • O = grau (umschaltbar in config.h)
- Kampagne:  Nach Sieg in Level N startet automatisch Level N + 1 (bis 100).
- Kopfzeile zeigt aktuelles Level + Spielfeldgröße (z. B. „Level 37 (37×25)“).

------------------------------------------------------------
VORAUSSETZUNGEN
------------------------------------------------------------
- C-Compiler (z. B. gcc)
- make
- Terminal mit ANSI-Unterstützung (für Farben und Clear-Screen)

------------------------------------------------------------
BUILD
------------------------------------------------------------
make
  → Baut die ausführbare Datei „labyrinth“.

Optionaler Test (Maze/IO-Modul):
make smoke
./smoke

------------------------------------------------------------
SPIEL STARTEN
------------------------------------------------------------
Kampagne ab Level 1:
./labyrinth 1

Direktes Level (1..100):
./labyrinth <level>
Beispiel:
./labyrinth 37

Freier Modus (ohne Kampagne):
./labyrinth <width> <height> <density>
Beispiel:
./labyrinth 30 15 0.2

------------------------------------------------------------
ENTWICKLER-TEST (SMOKE TEST)
------------------------------------------------------------
Der Smoke-Test überprüft unabhängig vom eigentlichen Spiel,
ob das Maze korrekt generiert und gezeichnet werden kann.

Bauen:
make smoke

Starten:
./smoke

Ausgabe:
- Zeigt ein zufälliges Labyrinth eines Beispiel-Levels (z. B. Level 15)
- Testet Wanddichte, Mindestabstand und BFS-Erreichbarkeit
- Gibt nach erfolgreichem Lauf:
  „✅ Smoke-Test abgeschlossen – Maze wurde erfolgreich erstellt und gezeichnet.“

------------------------------------------------------------
MAKE-KOMMANDOS (KURZREFERENZ)
------------------------------------------------------------
make              – Kompiliert das Spiel (Standard)
make run          – Startet Spiel bei Level 1
make runl L=37    – Startet direkt bei Level 37
make smoke        – Erstellt und linkt den Smoke-Test
make clean        – Löscht *.o, *.d, Binaries (labyrinth, smoke)
make rebuild      – clean + make (Neuaufbau)
make reset        – Voll-Reset (clean + temporäre Dateien)
make debug        – Zeigt Build-Parameter
make tidy         – Alias für clean
make help         – Zeigt Hilfeübersicht

------------------------------------------------------------
TASTEN
------------------------------------------------------------
W = hoch  
A = links  
S = runter  
D = rechts  
Q = beenden

------------------------------------------------------------
ORDNERSTRUKTUR (EMPFOHLEN)
------------------------------------------------------------
include/ → Header (config.h, game.h, io.h, maze.h, level.h)
src/     → Quellen (main.c, game.c, io.c, maze.c, level.c)
tests/   → Smoke-Test (smoke.c)
docs/    → Dokumente (design.md usw.)
assets/  → optionale Zusatzdaten
Makefile  
README.txt

------------------------------------------------------------
HINWEISE
------------------------------------------------------------
- Bei großen Leveln (z. B. 100×25) kann die Erzeugung und Ausgabe etwas langsamer sein.
- Die Hindernisdichte bleibt unter 0.6, damit Level immer lösbar bleiben.
- Farben lassen sich in config.h mit USE_COLOR (1 = an, 0 = aus) umschalten.
- Nach jedem Sieg im Kampagnenmodus erscheint eine kurze Pause.  
  Mit Enter geht es weiter zum nächsten Level.
