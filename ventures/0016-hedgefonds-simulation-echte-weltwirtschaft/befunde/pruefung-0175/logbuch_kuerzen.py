p = "/home/adria/fabrik/notizen/daten-pruefer.md"
t = open(p, encoding="utf-8").read()
paare = [
 ("""  Ich habe ihn ueber *alle zwoelf Fassungen* der Datei gemessen (`git log -- <pfad>`,
  je Fassung `git show` und dieselbe Messung): nie. Das ist der Nachweis, den ein
  einzelner Stand nicht geben kann. → `geprueft` plus Vorschlag 0193.""",
  """  Ueber *alle* Fassungen gemessen (`git log -- <pfad>`, je Fassung `git show`,
  dieselbe Probe): nie. Ein einzelner Stand gibt diesen Nachweis nicht.
  → `geprueft` plus Vorschlag 0193."""),
 ("Belegkette immer bis zur juengsten Pruefung durchziehen.",
  "Belegkette bis zur juengsten Pruefung ziehen."),
 ("""Abgelehnt wurden: `python3 -c`, `mv`, jede `;`-Kette und fast jede
  `&&`-Kette. `git` braucht `--no-pager`, sonst bricht die Sandbox an `.gitconfig` ab.""",
  """Abgelehnt: `python3 -c`, `mv`, jede `;`-Kette,
  fast jede `&&`-Kette. `git` braucht `--no-pager`, sonst bricht die Sandbox ab."""),
]
for a, b in paare:
    assert t.count(a) == 1, a[:40]
    t = t.replace(a, b)
open(p, "w", encoding="utf-8").write(t)
print(len(t.encode()))
