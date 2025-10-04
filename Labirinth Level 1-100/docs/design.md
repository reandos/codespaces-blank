Design-Dokument – Labirinth Level 1–100

1. Ziel & Überblick
Ein textbasiertes Konsolenspiel: Der Spieler P sucht den Schatz T in einem ASCII-Labyrinth.
Steuerung: W/A/S/D (Bewegung), Q (Beenden).
Darstellung optional farbig (ANSI): P rot, T gelb, Wände O grau.

2. Spielmechanik & Regeln
Level 1–10: Spielfeld 10x10
Level 11–25: N×N (z. B. Level 25 = 25×25)
Ab Level 26: Breite = N, Höhe = 25 (z. B. Level 50 = 50×25, Level 100 = 100×25)
Hindernisdichte: linear von 0.12 (L1) bis 0.45 (L100), maximal < 0.6.
Mindestabstand P↔T (Chebyshev): 
- L1–10 mindestens 5 
- ab L11 +1 pro Level 
- konservativ gekappt an min(width, height)
Bedingung: |dx| ≥ sep und |dy| ≥ sep
BFS-Prüfung garantiert Lösbarkeit. Wenn kein Pfad existiert, wird das Labyrinth neu erzeugt.
Kampagnenfluss: Start bei gewünschtem Level n, automatischer Übergang zu n+1 bis Level 100.
HUD zeigt: LABIRINTH LEVEL 1–100 | Level N (W×H) und Züge.

3. Architektur
config.h: Zeichen (CHAR_*), Titel, ANSI-Farben (USE_COLOR 1/0)
io.h/io.c: Eingabe, Bildschirm löschen, Zufall (seed, rand01)
level.h/level.c: Berechnung von width, height, density, min_sep nach Level-Regel
maze.h/maze.c: Raster, Wände, Platzierung P/T, BFS-Check, farbige Ausgabe, Bewegung
game.h/game.c: Spielloop, HUD, Level-Fortschritt
main.c: Startlogik (Kampagne oder freier Modus)
tests/smoke.c: Test für Maze-Erzeugung und BFS-Check

Datenstrukturen:
Vec2i { int x, y } – Position
Maze { int width, height; char** cells; Vec2i player, treasure; double density; int min_sep; }
Game { Maze* maze; bool running; int moves; int level; }

4. Kernalgorithmen
Maze-Erzeugung:
1. Raster füllen: Rand = Wand; Innen = Wand mit Wahrscheinlichkeit density.
2. P setzen: zufällige freie Zelle.
3. T setzen: zufällige freie Zelle mit Chebyshev ≥ min_sep.
4. BFS-Check: existiert Pfad? Wenn nein, neu generieren; wenn ja, P und T setzen.
BFS (4-Richtungen): prüft Erreichbarkeit; Queue aus Vec2i; Abbruch bei Ziel.
Bewegung: Eingabe (W/A/S/D), Kollisionstest; P bewegt sich um 1 Feld; Sieg bei P == T.

5. Benutzeroberfläche
ASCII-Zeichen: O=Wand, P=Spieler, T=Schatz, Leer=freies Feld.
Farben (wenn USE_COLOR=1): P rot, T gelb, O grau.
Jede Bewegung löscht und zeichnet das Spielfeld neu.
HUD zeigt Level, Spielfeldgröße und Züge.

6. Konfiguration
Farben: in config.h (USE_COLOR 1=an, 0=aus).
Freier Modus: Standardwerte DEFAULT_WIDTH/HEIGHT/DENSITY.
Grenzen: density auf 0.0–0.6 geklemmt, min_sep auf min(width,height) begrenzt.

7. Build, Start & Test
Build:
make
Start Kampagne:
./labyrinth 1      (Start bei Level 1)
./labyrinth 37     (Start bei Level 37)
Freier Modus:
./labyrinth <width> <height> <density>
Beispiel: ./labyrinth 30 15 0.20
Smoke-Test:
make smoke
./smoke
Der Smoke-Test prüft Maze-Erzeugung, Mindestabstand und BFS-Lösbarkeit.

8. Qualität & Grenzen
Lösbarkeit durch BFS garantiert.
Große Level (z. B. 100×25) benötigen mehr Zeit beim Erzeugen und Zeichnen.
min_sep konservativ begrenzt für stabile Platzierung bei height=25.
density < 0.6, damit Level begehbar bleiben.

9. Erweiterungen (Ausblick)
Seeds und Replay für reproduzierbare Level, Timer, Bestzeiten, Highscores.
Speichern/Laden, Portale, mehrere Start-/Schatzpunkte.
Alternative Zeichensätze, Themes, Debug-Anzeige (z. B. Pfadvisualisierung).

10. Dateistruktur (Soll)
include/   config.h, game.h, io.h, maze.h, level.h
src/       main.c, game.c, io.c, maze.c, level.c
tests/     smoke.c
docs/      design.txt, report.txt
assets/    sample_maps.txt
Makefile,  README.txt
