---
id: 0152-werte-zweiundzwanzig-statt-siebzehn
rolle: kernbauer
status: fertig
haengt_an: [0151-werte-die-drei-hubgroessen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/werte.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: Die fuenf Bedingungen unter "Abnahme".
---

# T48 Nr. 21, Nr. 22, die zweistellige Nr. 11 -- und danach heisst der Kopf „zweiundzwanzig"

**Angelegt am 2026-09-06 vom Projektmanager**, aus derselben Vorgabe wie `0151`
(`technik.md` Zeile 3231--3260). `0151` hat die drei Hubgroessen gebaut; dieses Paket
schliesst die Menge und macht den Zaehlnachweis aus T48 zum ersten Mal wieder wahr.

**`haengt_an: 0151` ist beides** -- fachlich (Nr. 22 liest `hub` aus Nr. 18) und zugleich
die Reihenfolgesperre auf denselben drei Dateien.

## Die Vorgabe

`technik.md` T48, Tabelle ab Zeile 2072:

| # | Name | Klasse (T5) | Definition |
|---:|---|---:|---|
| 11 | `handelsvolumen(l, s)` | 2 | siehe T48; die einstellige Fassung `handelsvolumen(l)` ist ihre Summe ueber s ∈ {1, 2} |
| 21 | `weltpreis_mit_zoll(g, s)` | 5 | `mal_geteilt(welt.preis.<s>, 10.000 + zollstand(g), 10.000)` |
| 22 | `schaden(l, i)` | 2 | `mal_geteilt(menge, verschiebung, 10.000)`, vier Zeilen, siehe T48 |

Dazu die drei Festlegungen der Tabelle in Zeile 3236--3243, die keine Bauentscheidung
mehr sind:

- **Nr. 21 und Nr. 22 sind oeffentlich.** Bei Nr. 22 steht die Fallunterscheidung ueber die
  vier Instrumente **innen**, nicht beim Aufrufer.
- **Nr. 11 ist eine Formaenderung an einer bestehenden Groesse.** Heute steht in
  `werte.hpp` `handelsvolumen(z, land)`; *„gebraucht werden beide Stelligkeiten, die
  einstellige gebildet aus der zweistelligen"*. Die Richtung ist vorgegeben -- die
  einstellige ruft die zweistellige, nicht umgekehrt.
- **`menge(l, i)` und `verschiebung(l, i)` bekommen keine oeffentliche Schnittstelle**, und
  `technik.md` Zeile 3242 sagt dazu: *„**nein**, und das ist eine Vorgabe und kein
  Vergessen."* Sie gehoeren nach `intern` oder in den anonymen Namensraum von `werte.cpp`.
- **`regulierung_last` ist ein Feld in der Struktur `Konstanten`** in `werte.hpp, „wo
  `gegenlobby_satz` und `lobbykosten` schon stehen" (Zeile 3243) -- mit demselben
  Kommentarkopf wie diese beiden und dem Verweis auf T27.

## Die eine Stelle, an der die Vorgabe selbst unsicher ist

`technik.md` Zeile 3262--3269 meldet sie ausdruecklich und benennt sie als die Stelle, an
der der Architekt *„einem Pruefer widerspruchslos folgen wuerde"*: **der Definitionsbereich
von `weltpreis_mit_zoll`.** Der Entwurf hat `zollstand(RW) = 0` gesetzt, weil die Restwelt
keine Instrumente hat, aber der Bereich steht weder in T28 noch in `spiel.md`
ausgeschrieben. Laeuft die Marktraeumung nur ueber die vier spielbaren Laender, ist die
Zeile ueberfluessig und nicht falsch.

**Bau die Fassung, die dasteht** -- fuenf Gebiete, `zollstand(RW) = 0` -- und **schreib den
Vorbehalt als Kommentar an die Funktion**, mit Verweis auf `technik.md` Zeile 3262. Loes
ihn nicht auf: Das ist eine Entwurfsfrage, und sie geht als Meldung an den
Geschaeftsfuehrer, nicht in diesen Lauf.

## Abnahme

1. **Nr. 21 und Nr. 22 stehen oeffentlich in `werte.hpp`**, in der Reihenfolge der
   T48-Tabelle und in der Kommentarform, die Nr. 1 bis 20 dort tragen. `menge` und
   `verschiebung` stehen **nicht** ausserhalb von `intern`; nachpruefbar durch eine Suche
   nach beiden Namen im oeffentlichen Teil des Kopfes, die leer ausgeht.
2. **Nr. 11 traegt beide Stelligkeiten, und die einstellige ist aus der zweistelligen
   gebildet.** Nachgewiesen durch eine Probe, die fuer mindestens ein Land beide Fassungen
   aufruft und `handelsvolumen(l)` gegen die von Hand gebildete Summe der zweistelligen
   ueber s ∈ {1, 2} haelt. Jeder bestehende Aufrufer der alten einstelligen Fassung
   uebersetzt weiter oder ist mitgezogen; der Bestand bleibt gruen.
3. **Die vier Zeilen von Nr. 22 sind einzeln nachgewiesen**, je mit einem von Hand
   gerechneten Sollwert im Quelltext, und ein fuenftes, unbekanntes Instrument bricht ab,
   statt eine der vier Zeilen zu nehmen. Die Zeile fuer die Regulierung liest
   `regulierung_last` aus `Konstanten` und kein Literal.
4. **Der Zaehlnachweis aus T48 stimmt wieder.** In `werte.hpp` steht an allen vier Stellen,
   an denen heute „siebzehn" steht (Zeile 2, 16, 28 und die Zwischenueberschrift in Zeile
   115), das nachgezaehlte Zahlwort -- nach `0151` und diesem Paket zweiundzwanzig.
   **Nachgezaehlt, nicht uebernommen:** Eine Suche nach „siebzehn" in `werte.hpp` geht leer
   aus, und die Zahl der Deklarationen ausserhalb von `intern` stimmt mit ihr ueberein.
   Steht am Ende eine andere Zahl als zweiundzwanzig, ist das ein Befund und die Zahl im
   Kopf folgt der Zaehlung, nicht diesem Paket.
5. **Der Bestand bleibt gruen.** `ctest` in beiden Bauprofilen (`FABRIK_SANITIZER=ON` und
   `OFF`), Belegstellen-, Bezeichner- und Sperrebindungsriegel mit Code 0; ausserhalb der
   drei Paketdateien null geaenderte Zeilen.

## Zwei Stellen, die du melden und nicht anfassen sollst

- **Die Abnahme von Paket `0002` nennt die Zahl siebzehn woertlich** und war zum Zeitpunkt
  ihrer Erfuellung richtig (`technik.md` Zeile 3255--3258). `0002` steht auf `fertig` und
  wird hier nicht angefasst; wer die alte Abnahme spaeter liest, findet die Erklaerung im
  Entwurf.
- **Der Definitionsbereich von `weltpreis_mit_zoll`** -- siehe oben. Kommentar ja,
  Aufloesung nein.
