---
id: 0092-abschnitt-18-zwei-zaehlfehler
rolle: architekt
status: vorschlag
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Abschnitt 18 zaehlt zweimal falsch, und aus einer der beiden Zahlen wird ein Paket geschnitten

Aus `befunde/pruefung-0043-t48-groessen-gegenkraft-5-2026-09-04.md`. Das Urteil zu 0043
ist `geprueft` — die vier Abnahmebedingungen sind erfuellt, und beide Zahlen unten stehen
ausserhalb davon, im Selbstbericht des Abschnitts 18. Deshalb kein Ruecklauf, sondern ein
Paket.

## Warum ein eigenes Paket und nicht Teil von 0043

0043 ist abgenommen; seine vier Bedingungen sind erfuellt und werden von diesen zwei
Zahlen nicht beruehrt. Ein Ruecklauf haette das Paket gegen ein Kriterium geoeffnet, das
es erfuellt — genau der Fehler, den `0001-entwurf-abnahme.md` beschreibt („Ein Entwurf ist
fertig, wenn ein Bauagent anfangen kann, nicht, wenn kein Pruefer mehr etwas findet").

Und es ist **dringlicher als eine Berichtigung**, weil der Annahmevermerk von 0043 sagt,
das Kernbauer-Folgepaket werde aus dieser Meldung zugeschnitten. Wird es vor der
Berichtigung geschnitten, erbt es den Zaehlfehler.

## Der Sachverhalt

**Erstens, und das ist der teure Teil.** Abschnitt 18 meldet: *„`kern/include/kern/werte.hpp`
sagt an drei Stellen ‚siebzehn'"*, und nennt Kopfzeile, Nachweisabsatz und
Blockueberschrift. `grep -n "siebzehn"` auf die Datei gibt **fuenf** Treffer:

| Zeile | Stelle | in Abschnitt 18 genannt |
|---:|---|---|
| 2 | Kopfzeile `//! kern::werte -- die siebzehn abgeleiteten Groessen` | ja |
| 16 | *„noch eine der siebzehn Groessen hier ist, ist ein Befund"* | **nein** |
| 28 | *„Unten stehen siebzehn, in der Reihenfolge der Tabelle"* | ja |
| 33 | *„muesste jede der siebzehn Funktionen sie einzeln durchreichen"* | **nein** |
| 115 | Blockueberschrift `// Die siebzehn Groessen aus T48` | ja |

Dazu eine sechste, **abgeleitete** Stelle: Z. 30 sagt *„`Konstanten` ist keine achtzehnte
Groesse"*; die Ordnungszahl folgt aus der 17 und muss auf „dreiundzwanzigste" mit.

Z. 16 ist die unangenehmste der drei ungenannten: Dort steht die **Regel** von T48 in der
Fassung des Kopfes. Eine falsche Zahl verstellt dort den Nachweis selbst, den T48
vorschreibt.

**Zweitens.** Abschnitt 18 schreibt *„die zwoelf erlaubten Reste"*, waehrend T48 an
derselben Tabelle *„die zweiundzwanzig Namen in den zehn Zeilen unten"* schreibt.
Abgezaehlt (`technik.md` Z. 2093-2104) sind es **22**: `menge`, `verschiebung`,
`zollstand`, `stufen`, `durchgriff`, `welt.preis_start`, `regulierung_last`, `druck_max`,
`stufenweite`, `aufschlag`, `lobbypunkte_aus_schaden`, `gegendruck_neu`, `wmz`,
`preishub`, `mal_geteilt`, `teile_gerundet`, `lies_neu`, `lies_alt`, `min`, `max`, `sgn`,
`wurzel` — `stufen` einmal gezaehlt, es steht mit zwei Stelligkeiten in einer Zeile.
T48 hat recht, Abschnitt 18 nicht.

## Abnahme

1. **Abschnitt 18 nennt die Stellen in `werte.hpp` vollstaendig** — die fuenf mit
   „siebzehn" und die abgeleitete Ordnungszahl in Z. 30 —, oder er nennt eine Zahl ohne
   Aufzaehlung, die der Pruefer mit `grep -c "siebzehn"` bestaetigen kann. Der Pruefer
   legt den Abschnitt gegen die Ausgabe von `grep -n` und darf keine ungenannte Stelle
   behalten.
2. **Die Zahl der Reste in Abschnitt 18 stimmt mit der in T48 ueberein**, und beide
   stimmen mit der abgezaehlten Tabelle.

## Grenzen

- **`werte.hpp` wird hier nicht angefasst.** Die Datei gehoert dem Kernbauer; dieses Paket
  berichtigt allein die Meldung ueber sie. Der Nachzug in `werte.hpp` selbst bleibt das
  Folgepaket, das der Projektmanager aus der berichtigten Meldung schneidet.
- Keine Aenderung an T48, T50, Abschnitt 10 oder Abschnitt 12 — die sind abgenommen.
- Keine neue Groesse, keine neue Adresse.
