---
typ: pruefung
paket: 0110-mutationslauf-als-wiederholbarer-riegel
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: alle drei Abnahmebedingungen am Baubaum selbst gefahren -- voller Lauf 19/19 mit zeichengleichem git status, Falschangabe und Trefferbremse an einer Katalog-Kopie in $TMPDIR nachgestellt
befunde: 0
---

# Pruefung 0110 -- Mutationslauf als wiederholbarer Riegel

Unabhaengig gemessen, ohne den Nachweis des Bauagenten (`befunde/messung-0110/`) zu
lesen. Stand: Arbeitsbaum nach Commit `2f5211e`; der Quelltext des Pakets liegt in
`bf0519b` und `228d9d7` (siehe Anmerkung 1).

## Bedingung 1 -- Ziel, Rueckgabewert, unveraenderter Baum: erfuellt

**Aufruf:** `cmake --build bau --target mutationslauf` am Arbeitsbereichs-Baubaum.
**Ausgabe:** Selbsttest des Kataloglesers 11 Faelle / 9 Fehlerarten gruen; Vorlauf
gruen; alle 19 Faelle `ok ... erreicht rot, erwartet rot`; `Nachlauf: 1 Probe(n) am
unveraenderten Baum -- gruen`; `mutationslauf: 19 von 19 Faellen wie erwartet`;
`Built target mutationslauf` (Code 0). Jeder Fall reisst dabei eine
**fallspezifische** Zusicherung (M15/M16/M18/N10 die Klassentabelle Zeile 852/870,
M19/M21/N02--N04 die Zeilenpruefungen um 1167, M20 Zeile 1228, N05--N09 je eine
eigene `zeile_endet_wert`, N11/Z01/Z02 je ihre Kopfzeile) -- nicht alle denselben
Anker.

**Rueckgabewert direkt gemessen:** `bau/werkzeuge/mutation/mutationstreiber <wurzel>
<bau> werkzeuge/mutation/katalog.md Z01` endet mit Code **0**; die beiden roten
Laeufe unten enden mit Code **1**.

**`git status --porcelain | sort` vor und nach dem vollen Lauf:** beide 31 Zeilen,
`diff` leer -- zeichengleich. Alle Wegwerfdateien liegen unter `bau/mutationslauf/`,
und `bau/` ist ignoriert. Der Rueckweg (Zeitstempel anfassen, Ziel neu bauen) laesst
den Inhalt der Quelldatei byteweise unveraendert.

## Bedingung 2 -- die neunzehn Faelle und die Trefferbremse: erfuellt

**Herkunft nachgeschlagen, nicht geglaubt:** Befund 1 der Pruefung zu Paket 0010
(`befunde/pruefung-0010-zustandsausgabe-drei-ebenen-2026-09-04.md`, Zeilen 145--161)
nennt genau siebzehn ueberlebende Mutationen: M15, M16, M17, M18, M19, M20, M21,
N02--N11. Der Katalog traegt exakt diese siebzehn, dazu Z01 und Z02 -- die zwei
Kopfzeilen (Uebersicht, Unterschied), deren dritte (Detail) als N11 schon unter den
siebzehn ist. Jeder Fall nennt `ziel: zustandsausgabe_probe` (Probe = Ziel per
Vorgabe) und `urteil: rot`, und jeder wurde im vollen Lauf rot.

**Trefferbremse:** Katalog-Kopie in `$TMPDIR` mit zwei Zusatzfaellen -- F97
(Suchmuster kommt 0-mal vor) und F98 (`feld(blatt`, kommt 22-mal vor). Aufruf des
Treibers mit Auswahl `F97 F98`: beide `FEHLER ... erreicht (keines)`, Meldung
`das Suchmuster kommt 0-mal/22-mal vor, nicht genau einmal`, Austrittscode 1. Ein
Fehlschlag, kein uebersprungener Fall.

## Bedingung 3 -- die Falschangabe: erfuellt

Katalog-Kopie in `$TMPDIR`, in der **nur** `urteil` von Fall M18 von `rot` auf
`gruen` gestellt ist (Ersetzung mit Trefferbremse `count==1` gebaut). Aufruf mit
Auswahl `M18`: `FEHLER M18 erreicht rot, erwartet gruen`, Nachlauf gruen,
`0 von 1 Faellen wie erwartet`, Austrittscode **1**. Derselbe Katalog ohne die
Falschangabe ist gruen (voller Lauf oben). Die Paketdatei selbst wurde fuer keine
dieser Proben angefasst.

## Wonach sonst gesucht wurde

- **Abschwaechung in der Versionsgeschichte:** `git diff bf0519b 228d9d7` auf
  `werkzeuge/mutation/` -- die Nachaenderung **haertet**: Fallkopf braucht das Wort
  `Fall` (vorher wurden zwei Prosakopfzeilen als Faelle gelesen), `ctest` bekommt
  `--no-tests=error`, die Fehlzeile wird ab der Marke geschnitten. Kein Urteil wurde
  auf `gruen` gestellt, kein Suchmuster veraendert, kein Fall entfernt.
- **`ctest` bleibt frei:** `ctest --test-dir bau -N` zaehlt weiterhin 14 Faelle,
  `mutationslauf` ist keiner davon -- die Entscheidung des Projektmanagers haelt.
- **Einhaengung:** `CMakeLists.txt` des Arbeitsbereichs fuehrt `werkzeuge/mutation`
  in `FABRIK_MITGLIEDER` (Zeile 61).
- **Vorlauf-Riegel:** im Treiber vorhanden und in jedem Messlauf gefahren; ein aus
  fremdem Grund roter Baum kann kein falsches Gruen erzeugen (Code prueft
  `zurueckgesetzt && nachlauf && gelungen == berichte.size()`).

## Anmerkungen ausserhalb der Abnahme (kein Befund gegen das Paket)

1. **Die Commit-Betreffs luegen.** Der Quelltext von 0110 liegt in `bf0519b`
   (Betreff `datenbauer: 0120`) und `228d9d7` (Betreff `architekt: 0116`); der
   Commit mit dem Betreff `testentwickler: 0110` (`2f5211e`) traegt nur Notizen,
   Paketdatei und Nachweis. Das Phaenomen ist als Vorschlag
   `0121-commit-schnitt-folgt-nicht-dem-paket` bereits gemeldet; dieser Fall ist ein
   weiterer Beleg dafuer.
2. **Das Urteil `bau` ist implementiert, aber nirgends gefahren.** Kein Katalogfall
   und kein Selbsttest erreicht den Zweig, in dem der Uebersetzer den Mutanten
   ablehnt (der Selbsttest deckt nur den Katalogleser). Die Abnahme verlangt es
   nicht; die naechste Katalogerweiterung sollte einen `bau`-Fall mitbringen -- die
   Pruefung zu 0010 nennt zwei Mutationen, die die `static_assert`-Kette faengt.
3. **Der vom Bauagenten gemeldete `ctest`-Befund hat jetzt ein Paket:** Vorschlag
   `0127-uebersetzungsbericht-ohne-proben-heisst-ok` (Baulauf meldet ein Mitglied
   ohne gefundene Proben als `ok`; ein pauschales `--no-tests=error` waere wegen des
   absichtlich probenfreien `werkzeuge/mutation` die falsche Behebung).
