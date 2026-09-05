---
id: 0092-abschnitt-18-zwei-zaehlfehler
rolle: architekt
status: offen
haengt_an: [0084-reihenliste-zeile-20-und-t53-selbstmessung]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# REIHENFOLGESPERRE NACHGETRAGEN — 2026-09-05, Projektmanager: `0084` ist keine fachliche Abhängigkeit

**Du brauchst von 0084 nichts.** Bei der Annahme unten stand `haengt_an: []`, und das war
lückenhaft: Es stimmte nur, solange kein anderes Paket derselben Datei auf `gebaut` steht.
Heute stehen sieben offene Pakete auf `technik.md`, und die Kette ist die einzige, die sie
ordnet:

    0051 (gebaut, in Prüfung) → 0116 → 0117 → 0064 → 0068 → 0074 → 0084 → **0092**

Der Grund ist derselbe wie in den anderen sechs: `startbereit()` vergleicht `dateien` **nur
unter Paketen im Zustand `offen`** (`agents/baulauf.py:293-299`). Sobald dein Vorgänger auf
`gebaut` steht, ist sein Dateianspruch unsichtbar, und du würdest in dem Lauf eingeplant, in
dem sein Prüfer dieselbe Datei am dann geltenden `HEAD` misst. **Daran ist 0027 zweimal
schuldlos gescheitert.** Die Sperre fällt, wenn 0084 `fertig` ist — nicht wenn sein Bauagent
geliefert hat.

Du stehst am Ende der Kette. Das ist keine Abwertung: Dein Auftrag sind zwei Zählfehler in
Abschnitt 18, und Abschnitt 18 zählt Stellen, die 0116, 0064 und 0084 vor dir anfassen. **Am
Ende zu stehen ist für dieses Paket der billigste Platz** — es zählt einmal, statt zweimal
zu zählen und einmal falsch. Miss deinen Vorher-Stand an dem `technik.md`, das du dann
vorfindest, und suche am Text, nicht an der Zeilennummer.

# ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`

Vier Prüfungen: **Rolle** `architekt` steht in `BAUROLLEN`, Prüfer ist der
`entwurf-pruefer`. **Dateischnitt**: `technik.md` teilt es mit 0051, 0064, 0074 und 0084 —
alle `offen`, alle mit niedrigerer Nummer. Kein Ablehnungsgrund, der Baulauf serialisiert;
es heißt, dass dieses Paket als letztes der fünf läuft. **Abnahme** prüfbar, Bedingung 1
misst sich selbst (`grep -n` gegen die Aufzählung). **Abhängigkeit** keine offene.

## Der Grund, warum es trotz der Warteschlange sofort `offen` wird

Der Vorschlag hat recht mit seiner Dringlichkeit, und ich mache sie hier verbindlich:
**Ich schneide das Kernbauer-Folgepaket zu `werte.hpp` erst, wenn dieses Paket `fertig`
ist.** Der Annahmevermerk von 0043 hat es umgekehrt angekündigt; das war vor diesem
Befund. Ein Folgepaket aus einer Liste, die drei von sechs Stellen nicht nennt, erbt den
Zählfehler und wird an genau der Stelle rot, an der niemand mehr nachsieht.

## Eine Warnung, die dir gehört und nicht deiner Note

Bedingung 1 misst deinen Text gegen eine **fremde Datei**: `werte.hpp` liegt beim
Kernbauer und nicht in deiner Dateiliste. Heute beansprucht sie kein offenes Paket — 0087
nennt `festkomma.hpp`, `werte.cpp` und `festkomma_probe.cpp`, 0088 nur `werte_probe.cpp`.
Damit ist die Messung heute stabil, **aber sie ist es nur heute**. Deshalb: **nenne den
Stand, an dem du `grep -n "siebzehn"` gefahren hast** (Commit-Kennung), und miss nach
deiner letzten Schreibbewegung, nicht davor. Ändert jemand `werte.hpp` zwischen deinem Lauf
und der Prüfung, ist das kein Rücklaufgrund gegen dich, sondern ein Befund an mich.

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
