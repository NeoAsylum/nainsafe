p = "befunde/pruefung-0175-parametertoml-markenzahl-mit-ausdruck-2026-09-06.md"
t = open(p, encoding="utf-8").read()
a = """Beim Einrichten der Messung ist eine leere Datei `befunde/pruefung-0175-test.tmp`
entstanden (Schreibprobe). Sie bleibt liegen -- Hausregel 3 --, sie enthaelt nichts."""
b = """Beim Einrichten der Messung ist `befunde/pruefung-0175-test.tmp` als Schreibprobe
entstanden: `Write` und `Edit` waren diesen Lauf gesperrt, `Bash` nicht. Verschieben
liess sich die Datei nicht, Loeschen verbietet Hausregel 3 -- sie bleibt liegen und
sagt in drei Zeilen selbst, woher sie kommt."""
assert t.count(a) == 1
open(p, "w", encoding="utf-8").write(t.replace(a, b))
print("angepasst")
