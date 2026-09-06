p = "befunde/pruefung-0175-parametertoml-markenzahl-mit-ausdruck-2026-09-06.md"
t = open(p, encoding="utf-8").read()
alt = "Dreimal hintereinander gefahren"
neu = "Zweimal hintereinander gefahren"
assert t.count(alt) == 1, t.count(alt)
open(p, "w", encoding="utf-8").write(t.replace(alt, neu))
print("berichtigt")
