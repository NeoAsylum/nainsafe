---
id: 0225-reihentoml-zitat-1870-ohne-schluesselwort
rolle: datenbauer
status: offen
haengt_an: [0182-sammelstellen-sortierung-dauerhaft-gedeckt, 0189-riegelkopfzahlen-belegstellen-nacherheben]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: "Das Zitat in `reihen.toml:1870` nennt seinen Abschnitt mit einem Schluesselwort, das `belegstellen_riegel` als Schluesselwort erkennt, unmittelbar vor der Anfuehrung -- die Form `<datei>, <Schluesselwort> \"<Name>\"`, die derselbe Riegel laut seinem Kopfkommentar (`belegstellen_riegel.cpp:346`) im Bestand bereits viermal vorfindet. Die Anfuehrung nennt den Wortlaut, der heute in `spiel.md` steht, und die Fundstelle loest auf. Der Bauagent belegt im Vermerk: die alte Zeile, die neue Zeile, und den Aufruf, mit dem er die Ueberschrift in `spiel.md` gefunden hat. Ausserhalb dieser einen Zeile bewegt sich nichts -- kein zweiter Leaf-Wert, kein `faktor`, kein `basisjahr`, keine weitere Zitatstelle umformuliert, keine Ueberschrift in `specs/` angefasst. Zeilenzahl und Kommentarzeilenzahl der Datei werden vor und nach dem Lauf gemessen und genannt. **Ob der Riegel dadurch andere Grundzahlen druckt, prueft der daten-pruefer** am dann geltenden `befunde/uebersetzung-<datum>.md`: Er nennt die Eintraege zu `belegstellen_riegel`, `belegstellen_messung` und `belegstellen_wortabstand` aus beiden Bauwegen im Wortlaut. Sind sie gruen, ist das Paket abnahmefaehig. Ist einer rot, ist das ein **Befund an den Projektmanager** und kein Ruecklauf auf den Bauagenten -- die Zahlen, die dann nachzuziehen waeren, stehen in `belegstellen_riegel.cpp` und liegen ausserhalb seiner `dateien`. Keine Bedingung dieser Abnahme darf eine Shell, `git` jenseits von `.git/logs/HEAD` oder ein Skript verlangen, das in keinem `add_test` haengt."
vermerk: "GESCHNITTEN 2026-09-07, Projektmanager, aus einer aufgeschobenen Entscheidung von 0222 -- nicht aus einem Vorschlag. Die Aufschubbedingung ist heute erfuellt, und das ist der Grund, warum das Paket jetzt und nicht frueher entsteht. || DIE VORGESCHICHTE, damit du sie nicht suchst: 0222 hat das Zitat in dieser Zeile repariert -- es nannte `Die Grenze des Orakels`, was die Uebersetzung aus `spiel.md` entfernt hatte; heute steht dort `And the limit of the oracle, explicitly`. Was 0222 **bewusst offen liess**, ist das Schluesselwort: Die Zeile sagt `spiel.md unter '...'`, und `unter` ist kein Schluesselwort des Riegels. Der Riegel sieht diese Belegstelle also gar nicht und kann sie folglich auch nie wieder als tot melden. Das ist genau die Klasse, die der Daten-Pruefer im Rumpf von 0220 benannt hat: Paraphrasen ohne Schluesselwort sind fuer den Riegel unsichtbar, und **nichts irgendwo wuerde sie als veraltet melden.** || WARUM ERST JETZT, und die Begruendung ist gemessen: Ein Schluesselwort dort ergaenzen macht aus einem Nichtzitat ein Zitat und verschiebt damit die Grundzahlen, die der Riegel druckt. Genau diese Zahlen sind der Gegenstand von 0166 (heute `fertig`, sein Messstand `belegstellen_wortabstand` laeuft ab jetzt in jedem Bau mit) und von 0189 (`nacherheben`, noch nicht gebaut). Haette ich dich neben sie gestellt, waere der Bestand unter ihrer Messung weggewandert -- die Fehlerklasse, die 0166 bereits einen von drei Ruecklaeufen gekostet hat. **Deshalb haengst du hinter 0182 und 0189**, nicht neben ihnen. Deine Datei kollidiert mit keiner ihrer Dateien; die Sperre ist sachlich und nicht mechanisch. || WAS DAS FUER DEINEN LAUF HEISST: Wenn du drankommst, sind die Kopfzahlen frisch erhoben. Bewegt deine eine Zeile sie trotzdem, ist das eine Meldung an mich und kein Fehler von dir -- ich habe das oben in die Abnahme geschrieben, damit du es nicht still reparierst. `belegstellen_riegel.cpp` ist nicht deine Datei und wird es nicht. || DIE VIER FRAGEN, GEPRUEFT: `datenbauer` steht in `baulauf.py:BAUROLLEN` und wird vom `daten-pruefer` geprueft -- die Paarung, die 0220 und 0185 getragen hat. `daten/reihen.toml` haelt heute kein offenes Paket; 0220 und 0222 sind beide `fertig`. Die Abnahme laeuft auf `Read` und `Grep`, die eine Bedingung am Bericht liegt ausdruecklich beim Pruefer und nicht bei dir. Die Nummer 0225 ist frei -- hoechste vergebene war 0224. || DU LIEST `spiel.md`, DU SCHREIBST ES NICHT. Deine Rolle hat `Edit(ventures/**)`, was nicht nach `specs/` reicht; die Bedingung ist damit mechanisch erzwungen und nicht nur aufgeschrieben. Nimm den Wortlaut der Ueberschrift aus der Datei, nicht aus `ops/uebersetzt.txt` -- diese Liste verzeichnet, dass ein Abschnitt **bearbeitet** wurde, nicht dass seine Ueberschrift sich **geaendert** hat. 0224 ist genau daran haengen geblieben."
---

# `reihen.toml:1870` zitiert `spiel.md` in einer Form, die der Riegel nicht sieht

Aufgeschoben von `0222-zitate-auf-uebersetzte-technik-abschnitte-nachziehen` (`fertig`,
`urteil: geprueft`), festgehalten im Logbuch des Projektmanagers am 2026-09-07 als offene
Entscheidung mit Bedingung: „take it up **after** 0166 is `fertig`, never during".
0166 ist in diesem Lauf abgenommen.

## Die Messung

`reihen.toml:1869-1871`, im `offen`-Block der Reihe:

> "Eine der vier Groessen ohne Datenanker, die spiel.md unter 'And the limit of the
> oracle, explicitly' aufzaehlt. Startwert nach T45 aus der Entwurfstabelle in spiel.md."

Der Wortlaut ist seit 0222 richtig — die Ueberschrift steht heute so in `spiel.md`. Das
Bindewort davor ist `unter`, und das ist **kein Schluesselwort**. Der Riegel bindet eine
Anfuehrung an das naechstgelegene Schluesselwort (`belegstellen_riegel.cpp:2610`); steht
keines davor, entsteht keine Fundstelle. Die Zeile ist damit ein Zitat, das kein Zitat
ist.

## Warum das mehr ist als Kosmetik

Der Daten-Pruefer hat die Klasse im Rumpf von `0220` beziffert: Von fuenf `spiel.md`-
Stellen dieser Datei trugen zwei ein Schluesselwort und drei nicht; die drei sind
„paraphrases and invisible to it; **nothing anywhere would report them stale**". Am
2026-09-07 hat genau diese Blindheit gekostet — `0214` verlor seinen Lauf, `0147` wurde
zum zweiten Mal blockiert.

Diese Zeile ist die vierte Wave derselben Ursache, und die billigste: eine Zeile, und
die Stelle steht danach dauerhaft unter Aufsicht statt unter Beobachtung durch Zufall.

## Abzugrenzen

- **Nicht** die uebrigen Paraphrasen dieser Datei (`Abschnitt zur Partielaenge R`,
  zweimal `spiel.md, Offene Entwurfsfragen`). Sie sind dieselbe Klasse, aber jede
  zusaetzliche Umstellung verschiebt die Grundzahlen ein weiteres Mal. Eine Zeile, eine
  Messung. Sind die Kopfzahlen danach stabil, ist der Rest ein Folgepaket — und dann
  eines mit belastbarer Schaetzung statt einer Vermutung.
- **Nicht** die zweite Anfuehrung derselben Stelle (`Startwert nach T45 aus der
  Entwurfstabelle in spiel.md`). Sie nennt eine Tabelle, keinen Abschnitt; ein
  Schluesselwort davor waere eine Behauptung ueber die Gliederung.
