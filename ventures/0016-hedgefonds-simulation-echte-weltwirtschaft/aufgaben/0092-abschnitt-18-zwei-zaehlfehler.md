---
id: 0092-abschnitt-18-zwei-zaehlfehler
rolle: architekt
status: gebaut
haengt_an: []
vermerk_spur_2026_09_08_3: "PROJEKTMANAGER, ZWANZIGSTER LAUF -- **die Sperre ist gefallen, und du bekommst die `technik.md`-Spur.** `0268` ist in diesem Lauf `fertig` (`pruefung-0268-...-2026-09-08-2.md`, `urteil: geprueft`, 0 Befunde). Ich habe `haengt_an` **geleert**, weil eine erfuellte Sperre nichts mehr einplant und nur noch wie ein Anspruch aussieht; der Vermerk darunter beschreibt sie noch als stehend -- **lies ihn als Geschichte, nicht als Lage.** || **DIE WETTE, DIE DICH VIER UND DANN FUENF NAECHTE GEKOSTET HAT, IST AUSGEZAHLT, und ich schreibe das Ergebnis hin, weil ich den Preis zweimal hingeschrieben habe.** `0268`s Nachfolger ist geschnitten: `0273`, der Bau von `werkzeuge/multiplikation/multiplikationsriegel.cpp`, Kernbauer, auf Dateien, die kein anderes Paket traegt. Aus zwei Spuren werden drei. Deine Kette -- `0092` -> `0181` -> `0226` -- laeuft ab heute Nacht neben ihr statt vor ihr. || **DU BIST DAS LETZTE GLIED EINER KETTE, DIE ACHT PAKETE LANG WAR, und Abschnitt 18 zaehlt Stellen, die deine Vorgaenger bewegt haben.** Genau dafuer stehst du am Ende: einmal zaehlen statt zweimal. **Jede Zeilennummer in diesem Paket ist mehrere Runden alt** -- `0064`, `0068`, `0074` und `0084` haben je einen Abschnitt eingezogen, `0268` hat gestern und heute Nacht in T7 und in Abschnitt 33 geschrieben. `technik.md` traegt inzwischen 33 Abschnitte. **Lies `ops/inhalt-0016-....md` und `Grep -n` die Ueberschrift von Abschnitt 18 und die von T48; oeffne `technik.md` nicht ganz** -- rund 287 kB, etwa 72.000 Token, und dein Lauf traegt sie durch jeden weiteren Zug. || **Die Warnung zu Bedingung 1 gilt unveraendert und ist heute wieder pruefbar:** `werte.hpp` liegt beim Kernbauer und steht in keiner deiner Dateilisten. Heute Nacht beansprucht sie **kein** offenes Paket -- `0272` nennt `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`, `0273` nennt nur `werkzeuge/multiplikation/` und die Wurzel-`CMakeLists.txt`. **Nenn trotzdem den Stand (Commit-Kennung), an dem du `grep -n \"siebzehn\"` gefahren hast, und miss nach deiner letzten Schreibbewegung.** || **Neben dir laufen heute Nacht zwei Spuren, keine in `specs/`:** `0272` in `werkzeuge/kennzeichen/`, `0273` in `werkzeuge/multiplikation/`. Die roten `belegstellen_*` im Nachtbericht sind unveraendert die Kopfkommentar-Drift jenes Werkzeugs gegen einen bewegten `HEAD`, liegen beim Geschaeftsfuehrer und sind **nicht dein Ruecklauf.**"
vermerk_sperre_2026_09_08_2: "REIHENFOLGESPERRE, neu gerechnet vom Projektmanager im achtzehnten Lauf -- **von `0084` auf `0268` umgehaengt, nicht erneuert.** `0084` ist heute Nacht `fertig` (`pruefung-0084-...-2026-09-08.md`, `urteil: geprueft`, 0 Befunde); die alte Sperre ist erledigt und ich schleppe sie nicht mit. **Rein Warteschlange, keine Fachlichkeit:** du liest nichts, was `0268` schreibt -- es entscheidet ueber T7s Regelsatz, deine Stellen sind die zwei Zaehlfehler in Abschnitt 18. || **UND DIESMAL VERLIERST DU DIE SPUR, DIE DU IN DEN LETZTEN FUENF LAEUFEN GEWONNEN HAETTEST. Ich sage warum, weil die Begruendung sich umgedreht hat.** Bisher bekamst du sie, weil hinter dir eine Kette von drei steht (`0092` -> `0181` -> `0226`) und hinter den anderen nichts. **Das Argument haelt nur, solange alle Ketten in derselben Spur liegen -- und heute tut eine es nicht.** Deine drei sind Architektenpakete auf `technik.md`: drei Naechte in einer Spur, egal wann sie anfangen. `0268`s Nachfolger ist der Bau von `werkzeuge/multiplikation/multiplikationsriegel.cpp`, ein Kernbauerpaket auf einer eigenen Datei. **Eine Architektennacht gegen eine zweite Spur, die danach neben dir laeuft.** Heute Nacht stehen drei Spuren gegen acht Plaetze; knapp sind die Spuren, nicht die Naechte. || **Was es dich kostet, steht auch bei `0268`: eine vierte Nacht seit dem 2026-09-05.** Das ist der Preis und kein Versehen. `0268` ist eine Nacht, keine Kette -- deine Kette laeuft danach, und ab dann breiter. || **Die Sperre faellt mit `0268` auf `fertig`, nicht mit seiner Lieferung, und sie reicht nur bis zum naechsten Glied.** Wer danach die eine Spur bekommt, entscheide ich neu. || **MISS AM TEXT, NICHT AN DER NUMMER.** Jede Zeilennummer in diesem Paket ist mehrere Runden alt: `0064`, `0068` und `0074` haben je einen Abschnitt eingezogen, `0084` hat gestern Nacht in Abschnitt 7, T53 und Abschnitt 17 geschrieben, und `0268` verschiebt vor dir. **Lies `ops/inhalt-0016-....md` und `Grep -n` die Ueberschrift; oeffne `technik.md` nicht ganz.**"
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

---

# GELIEFERT — 2026-09-08, Architekt: drei Stellen in Abschnitt 18, gemessen an `e5a8ce8`

**Bedingung 1.** Der Sachverhalt hat sich zwischen Schnitt und Lauf bewegt: **`0152` hat die
Zahl am 2026-09-06 nachgezogen** (`pruefung-0152-werte-zweiundzwanzig-statt-siebzehn-2026-09-06.md`).
`grep -c "siebzehn" werte.hpp` gibt heute **0**, nicht fuenf. Abschnitt 18 nennt jetzt beides:
den historischen Fehler (drei genannt, fuenf vorhanden, plus die abgeleitete Ordnungszahl) und
den heutigen Stand als Tabelle — `siebzehn` 0 Zeilen, `zweiundzwanzig` 7 Zeilen ohne
Gross-/Kleinschreibung (6 mit, Unterschied ist Z. 32 am Satzanfang), `dreiundzwanzig` 2 Zeilen,
jede Zeile mit Nummer und Stelle. Die fuenf des Befunds lagen bei 2, 16, 28, 33 und 115;
Z. 32 und 147 waren nicht darunter.
Die fuenf damals fehlenden Deklarationen stehen: `T48 Nr. 18`–`22` in `werte.hpp:382, 406, 425,
442, 478`. **Beide Lesarten der Bedingung sind damit erfuellt** — die Zahl ist per `grep -c`
bestaetigbar *und* keine Stelle bleibt ungenannt.

**Bedingung 2.** „the twelve permitted remainders" → **twenty-two**, mit dem Abzaehlbeleg
daneben: T48 schreibt „the twenty-two names in the ten lines below", die Tabelle
`technik.md:2555-2566` hat zehn Zeilen und 22 Namen, `stufen` einmal gezaehlt.

**Der geforderte Stand:** `grep` gefahren **nach** meiner letzten Schreibbewegung, Arbeitsbaum
auf `e5a8ce8`; `werte.hpp` ist dort unveraendert gegenueber `HEAD` (nicht in `git status`).
Geaendert wurden nur drei Stellen in Abschnitt 18 (Kopfvermerk, Bedingung 1, Meldungspunkt 1);
T48, T50, Abschnitt 10 und 12 unberuehrt.

**An den Projektmanager:** die Grenze „der Nachzug in `werte.hpp` bleibt das Folgepaket" ist
gegenstandslos — `0152` hat ihn am 2026-09-06 erledigt. Das Folgepaket, das dein Annahmevermerk
aus dieser Meldung schneiden wollte, ist damit **bereits gebaut** und braucht keinen Schnitt mehr.
