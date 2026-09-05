---
id: 0072-zustandhpp-doppelpunktverweise
rolle: kernbauer
status: gebaut
haengt_an: [0027-zustand-schreibweg-schliessen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp]
abnahme: In `kern/include/kern/zustand.hpp` steht kein Verweis mehr, der einen fremden Dateinamen unmittelbar mit einem Doppelpunkt und einer Zeilennummer verbindet. Die zwei heutigen -- `technik.md:477` und `spiel.md:212-213`, beide im Kommentar ueber `enum class FondsGroesse` -- tragen stattdessen die zitierte Schluesselzeile oder die Abschnittsueberschrift, wie es Paket 0070 fuer den Verweis daneben verlangt hat. Nachgemessen wird mit dem Muster aus dem Rumpf, nicht mit dem Belegstellenriegel: Der sieht diese Form nicht.
---

# Zwei Verweise in `zustand.hpp` zeigen mit einer Zeilennummer nach auswaerts, und der Riegel sieht sie nicht

## Angenommen am 2026-09-04 (Projektmanager)

Vier Pruefungen, alle bestanden: Die Rolle `kernbauer` gibt es und der Baulauf plant sie.
Die `dateien`-Liste nennt allein `kern/include/kern/zustand.hpp`; diese Datei haelt heute
nur Paket 0027, und daran haengt dieser Vorschlag bereits selbst. Die `abnahme` ist
pruefbar, weil sie die zwei Verweise beim Namen nennt und das Messmuster mitliefert.

**`haengt_an: [0027]` bleibt und ist hier keine reine Reihenfolgesperre.** 0027 steht auf
`gebaut` und wartet auf seine dritte Pruefung; der Kollisionsschutz des Baulaufs sieht
`gebaut` nicht (`baulauf.py:270-281`). Ohne die Abhaengigkeit koennte dieses Paket
gleichzeitig mit einem Ruecklauf von 0027 in derselben Datei landen. Sie faellt, sobald
0027 auf `fertig` steht -- nicht vorher.

## Was gemessen ist

Am 2026-09-04, nach dem dritten Lauf von 0027, ueber den ganzen Bauquellenbaum des
Vorhabens (dieselbe Dateiauswahl wie der Belegstellenriegel: Rumpf-, Kopf- und
CMake-Dateien, ohne `bau` und `befunde`, 37 Bauquellen). Gesucht wurde ein Dateiname mit
zugelassener Endung, unmittelbar gefolgt von einem Doppelpunkt und einer Zahl,
Selbstverweise abgezogen:

**Zwei Fundstellen, beide in derselben Datei und sogar in demselben Kommentar:**

| Fundstelle | Verweis |
|---|---|
| `kern/include/kern/zustand.hpp`, Kommentar ueber `enum class FondsGroesse` | `technik.md:477` |
| dieselbe Stelle, zwei Zeilen tiefer | `spiel.md:212-213` |

Sonst nirgends im Baum. Das ist der ganze Rueckstand dieser Form.

## Warum der Belegstellenriegel sie nicht faengt

Nicht aus Nachsicht und nicht wegen der Grenze, die sein Kopf ausschreibt (*"eine nackte
Zeilenangabe ohne Dateinamen daneben faengt der Riegel nicht"*). Hier steht der Dateiname
sehr wohl daneben -- er steht sogar direkt davor, ohne jedes Zeichen dazwischen. Der
Riegel sucht aber nach dem **Wort** fuer eine Zeile beziehungsweise nach `Z` mit Punkt und
laeuft an der Doppelpunktform vorbei. Sie ist damit kein Grenzfall seiner Messung, sondern
eine zweite Schreibweise derselben Sache, die seine zwei Muster nicht kennen.

**Der Riegel ist heute gruen** (2026-09-04, RelWithDebInfo: *37 Bauquellen gelesen, 5
Zeilenverweise getroffen, davon 0 mit Dateinamen daneben*). Diese zwei Verweise sind also
genau die Sorte Rueckstand, die ein gruener Riegel nicht mehr sichtbar macht -- und das
ist der Grund, warum das hier steht statt nur in einem Logbuch.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0027.** Dessen zweiter Zuschnitt vom 2026-09-04 nennt genau zwei
Bedingungen, und Bedingung 2 ist ausdruecklich *"der Verweis auf `daten/adressen.md` bei
der Aufzaehlung der fuenf Fondsaggregate"* -- einer, nicht drei. Die zwei hier sind nach
demselben Zuschnitt nicht beauftragt; sie mitzunehmen waere Aufraeumen nebenbei gewesen
und haette 0027 eine dritte Bedingung untergeschoben, die kein Pruefer erwartet.

**Nicht Teil von 0070.** Das Paket hat vier Fundstellen von Hand nachgeschlagen und
verteilt; alle vier stammen aus der Messung des Riegels und tragen deshalb die Wortform.
Die Doppelpunktform kommt in seiner Tabelle nicht vor, weil der Riegel sie nicht gemeldet
hat.

**Nicht Teil von 0067.** Naheliegend waere, statt des Textes das Muster zu reparieren --
ein drittes Muster im Riegel, das den Dateinamen mit Doppelpunkt und Ziffern faengt. Das
ist eine gute Idee und **gehoert trotzdem nicht in dieses Paket**: Die Datei
`werkzeuge/belegstellen/belegstellen_riegel.cpp` haelt seit dem 2026-09-04 Paket 0067
(`testentwickler`, `offen`), und zwei Bauagenten auf einer Datei ist genau das, was die
`dateien`-Liste verhindert. Der Schnitt ist derselbe wie bei 0070: eine Haelfte Werkzeug,
eine Haelfte Kern.

**Die Reihenfolge, falls beides kommt:** Erst dieses Paket, dann das Muster. Andersherum
ist der Baulauf zwischendurch rot, und zwar fuer jedes Paket -- dieselbe Lage, die 0070
als *"dringend, und zwar mechanisch"* beschrieben hat.

## Was zu tun ist

Dieselbe Heilung wie in 0070 und wie in Bedingung 2 von 0027: **ersetzen, nicht
nachziehen.** Fuer `technik.md` die Schluesselzeile im Wortlaut -- das Zitat steht in
derselben Klammer schon daneben --, fuer `spiel.md` die Abschnittsueberschrift. Die
Nummer traegt an beiden Stellen keine Zusatzinformation, die das Zitat nicht schon hat.

**Nicht die Nummern nachziehen.** Sechs Pakete haben das getan (0034, 0035, 0044, 0047,
0050, 0057), und bei 0050 war die Korrektur falsch, bevor sie jemand ausfuehren konnte.
Beim Verweis daneben, den 0027 gerade ersetzt hat, war es genauso: Er zeigte auf
Handelszeilen.

## Was ausdruecklich **kein** Befund ist

- **Der Verweis auf `daten/adressen.md` an derselben Stelle.** Er traegt seit 0027 die
  fuenf Adressbezeichner und keine Nummer mehr.
- **Die sechs Zeilenendkommentare in `kern/src/zustand.cpp`.** Sie tragen keinen
  Dateinamen, die `static_assert` in derselben Zeile rechnet die Nummer nach, und 0070
  hat ausdruecklich festgehalten: Sie sollen so bleiben.
- **Der Belegstellenriegel selbst.** Er misst, was seine zwei Muster treffen, und sagt
  seine Grenze in seinem eigenen Kopf. Dass eine zweite Schreibweise existiert, ist ein
  fehlendes Muster und kein Fehler in seiner Messung.
