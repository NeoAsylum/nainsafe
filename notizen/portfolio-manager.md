# Logbuch: portfolio-manager

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Höchstens 30 Zeilen.

---

## Was funktioniert

- 2026-08-29 — **Erst `anwalt.md` lesen, dann zählen — und nur die Frontmatter-Zeilen
  `entkraeftet/loesbar/teuer/unloesbar` zählen.** Der Anwalt hat das Urteil je Linse
  bereits gefällt; die fünf Angriffsdateien musste ich in diesem Lauf gar nicht öffnen.
  Das spart drei Viertel der Lesezeit. Nachlesen lohnt nur, wenn der Anwalt eine Linse
  auf `loesbar` dreht — dort ist die Begründung die eigentliche Entscheidung.
- 2026-08-29 — **Die Anschlusszuschnitte gegen `ideas/*.md` prüfen, bevor man sie
  weiterreicht.** Alle drei „Andere Idee daraus" dieser Woche waren bereits ausgearbeitet
  und gestorben (0006, 0014, 0015) oder vom Ideator vorab widerlegt. Hätte ich sie
  ungeprüft ins Portfolio kopiert, hätte der Ideator dreimal dasselbe Nichts gefunden.
  Suchmuster: `ablehnungsgrund`-Zeilen aller Ideen am Stück lesen, dazu `notizen/ideator.md`.
- 2026-08-29 — **Die Logbücher der Rollen sind die bessere Quelle für Lehren als die
  Ablehnungsgründe.** Die Ablehnung sagt, woran eine Idee starb; das Logbuch sagt, welches
  Suchmuster es herausgefunden hat. Für „Folgerung für Rolle X" brauche ich Letzteres.
- 2026-08-29 — `ops/auslastung.md` beantwortet die Kostenfrage vollständig. Nicht selbst
  im Journal zählen; die Datei war aktuell (erzeugt am Lauftag).

## Was nicht funktioniert

- 2026-08-29 — **`agents/repo.py` hat keinen CLI-Einstieg**, nur importierbare Funktionen
  (`bereit_zur_bewertung()`, `angriffe()`). `python3 agents/repo.py status` gibt nichts
  aus. Nächstes Mal direkt die Frontmatter der Ideen greppen, das kostet einen Aufruf.
- 2026-08-29 — Zusammengesetzte Bash-Befehle (`cmd && cmd`, `for`-Schleifen) wurden
  verweigert. Einzelbefehle und die Dateiwerkzeuge liefen. Nicht erneut damit planen.
- 2026-08-29 — `notizen/rechercheur.md` ist mit ~92.000 Tokens auf 52 Zeilen nicht am
  Stück lesbar. Ich habe nur die erste Seite gebraucht; wer dort etwas sucht, greppt.

## Offene Faehrten

- 2026-08-29 — **Der Trichter ist leer, nicht verstopft.** Null Kandidaten, null aktive
  Vorhaben, alle drei WIP-Plätze frei. Wenn nächste Woche wieder keine neuen Signale
  ankommen, laufen Ideator, Fit-Filter und fünf Linsen ins Leere — und das sind die
  teuersten Läufe der Fabrik. Beim nächsten Lauf zuerst prüfen, ob `signals/` gewachsen ist.
- 2026-08-29 — Ungeprüft geblieben: ob die Score-Summen überhaupt noch etwas taugen. Alle
  drei Kandidaten lagen bei 16 bis 18 Punkten und starben trotzdem eindeutig; der
  bestbewertete (0012, 18) starb am klarsten. Die Punkte kommen vor der Prüfung, die
  Einwände danach — beim nächsten Mal beobachten, ob die Reihenfolge je stimmt.
- 2026-08-29 — Für einen künftigen Lauf zu klären: Was passiert mit einer `widerlegt`-Idee,
  wenn ihr Widerlegungsgrund selbst veraltet? 0012 hängt an einem Verordnungstext, 0009 an
  einem Wettbewerberpreis. Beides kann sich ändern; ein Wiedervorlagedatum kennt das
  Statusmodell nicht.
