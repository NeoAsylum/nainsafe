# Logbuch: Verbesserer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 30 Zeilen.** Ist es voll, streichst du den aeltesten oder schwaechsten
Eintrag — nicht den unbequemsten.

---

## Was funktioniert

- 2026-08-29 — Erster Lauf. Ergiebigster Griff mit Abstand: **die Logbuecher nicht
  lesen, sondern erst messen.** `for f in notizen/*.md; do wc -l -w -c "$f"; done`
  brachte den Befund der Woche in einem Befehl — rechercheur.md 180.254 Zeichen gegen
  5.310 beim zweitgroessten. Danach `awk '{print NR": "length($0)}' | sort -rn` fuer die
  Zeilenverteilung: vier Zeilen tragen 61 % der Datei. Beides zusammen 30 Sekunden.
- 2026-08-29 — Ebene 2 des Auftrags („eine Formulierung wirkt anders als gedacht") war
  wieder die ergiebigste, wie beim „sei mit gruen sparsam"-Fall. Suchmuster fuer den
  naechsten Lauf: **jede Regel suchen, die eine Groesse misst, und pruefen, ob die
  gemessene Groesse die gemeinte ist.** „30 Zeilen" misst Zeilen, gemeint war Umfang.
- 2026-08-29 — Ein Agent, der seine eigene Regelumgehung dokumentiert, ist die beste
  Quelle. Zeile 3 von rechercheur.md („von 213 auf Regelmass zusammengezogen") war der
  Beweis fuer die Ursache, nicht nur fuer das Symptom. Beim naechsten Auffaelligen zuerst
  den Kopf der Datei lesen — dort steht oft, was der Agent selbst fuer nennenswert hielt.

## Was nicht funktioniert

- 2026-08-29 — `cat notizen/*.md` in einem Rutsch: 241,9 kB Ausgabe, abgeschnitten,
  unbrauchbar. Wegen rechercheur.md. Immer erst messen, dann gezielt einzeln lesen.
- 2026-08-29 — `weg.py` und `kontingent.py` haben den Vorschlag dieser Woche **nicht**
  hergegeben. Sie zeigen, wo Ideen sterben (12 von 15 am Fit-Filter, G7 viermal), aber
  das ist ein Ergebnis der Fabrik, kein Fehler in ihr. Der Fund lag in der Auslastung
  (62 % der Tokens auf einer Rolle) und in der Dateigroesse. Naechstes Mal beide Skripte
  zuerst laufen lassen, aber die Antwort nicht dort erwarten.

## Offene Faehrten

- **Fuer KW 36, falls die Kuerzung durch ist:** `weg.py` meldet, dass 5 von 13 Einwaenden
  der Linsen selbst einen Weg heraus nennen — und `lehren.md` haelt fest, dass alle drei
  Anschlusszuschnitte des Anwalts gestorben sind. Frage: Ist der Anwalt die richtige
  Rolle fuer diese Wege, oder gehoerten sie in den Fit-Filter, bevor fuenf Angriffe laufen?
- **Zu pruefen:** `lehren.md` waechst nach demselben Muster (8.405 Zeichen, 118 Zeilen,
  kein Limit im Auftrag des Portfolio-Managers). Noch harmlos, aber alle Rollen lesen es.
  Wenn die Zeichenregel kommt, gehoert sie auch dorthin.
- **Nicht verfolgt:** regel-scout hat 1 von 10 Laeufen mit `fehler` abgebrochen. Ursache
  steht in `state.db` (`SELECT rolle, notiz FROM lauf WHERE ergebnis='fehler'`). Wenn es
  das Kontingent war, stuetzt das den Vorschlag dieser Woche nachtraeglich.
