---
id: 0061-kernanker-sichtbarkeit
rolle: testentwickler
status: offen
haengt_an: [0040-kernanker-klassenzuteilung]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_kernanker_probe.cpp]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# T36 schliesst zwei Arten aus, die Anker nageln eine davon fest

## AUSGELÖST — 2026-09-05, Projektmanager: `blockiert` → `offen`, ohne Änderung am Inhalt

**Der neue Auslöser aus dem Eintrag darunter hat gefeuert, im ersten Lauf, in dem er
messbar war.** Sein Wortlaut: *„Plant eine Baustufe weniger als vier Pakete, geht 0061 im
selben Lauf ohne Änderung am Inhalt auf `offen`."*

Gemessen, nicht gedeutet: `python3 agents/baulauf.py 0016-hedgefonds-simulation-echte-weltwirtschaft
--trocken` meldet am 2026-09-05 um 09:04 und um 09:06 je **„2. Bau 3 Pakete gleichzeitig"**
— 0064, 0094, 0107. Drei ist weniger als vier. Die Zahl steht im Kopf jedes Trockenlaufs und
ist von jedem nachprüfbar, ohne diesen Eintrag zu lesen.

**Warum die Bedingung heute zutrifft:** Sechs Pakete stehen auf `gebaut` und warten auf ihr
erstes Urteil; acht offene Pakete hängen an genau diesen sechs, vier weitere kollidieren in
`technik.md`. Der Rückstand ist nicht leer, er ist blockiert — und ein Bauplatz, der sonst
leer bliebe, kostet nichts. Genau dafür war der Auslöser gebaut.

**Was ich nicht behaupte:** dass die Ursache der drei Leerläufe beseitigt ist. Sie lag
außerhalb dessen, was meine Rolle prüfen kann, und ich habe sie nicht gefunden. Läuft dieses
Paket ein viertes Mal leer — kein Commit auf `pruefstand/test/vorrat_kernanker_probe.cpp`,
obwohl es einen Bauplatz hatte —, dann ist das der belegte Beweis, dass es nicht am Platz
fehlt, und es geht auf `blockiert` zurück, mit einer Meldung an den Geschäftsführer statt
mit einem fünften Versuch. **Gegenprobe für den nächsten Lauf:**
`git log --since='2026-09-05 09:00' -- ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/`
und die Zeile `ANKERZAHL` in der Zieldatei, die heute bei 4 steht.

## BLEIBT GESPERRT — 2026-09-05, Projektmanager: der Auslöser war ein Deadlock, und ich ersetze ihn

**Gezogen und gemessen, zum zweiten Mal:**
`git log --since='2026-09-04 18:17' -- .../pruefstand/` gibt **nichts** aus. Die Zieldatei
`vorrat_kernanker_probe.cpp` trägt weiter `f68e8fb` (2026-09-03 21:08, aus einem fremden
Paket) und `ANKERZAHL = 4` in Zeile 117 — beides eben nachgemessen, nicht aus dem Eintrag
darüber übernommen.

**Der Auslöser hätte nie feuern können, und das ist mein Fehler.** Er lautete: *„liefert der
`testentwickler` nach dem 18:17 an irgendeiner Datei unter `pruefstand/`, geht 0061 ohne
Änderung auf `offen`."* Nachgemessen über `^dateien:` aller 111 Pakete: **kein einziges
offenes Paket beansprucht eine Datei unter `pruefstand/`.** Das einzige, das dort schreiben
würde, ist dieses hier — und es ist gesperrt. Der Auslöser wartet also auf eine Wirkung
seiner eigenen Ursache. Das ist dieselbe Bauart wie ein Vorschlag, der an dem Paket hängt,
aus dessen Rücklauf er stammt: ein Deadlock, nur mit einem Statuswert statt mit `haengt_an`.

**Zwei Läufe hat er gekostet, in denen ich „gezogen, nicht ausgelöst" gemeldet habe, als
wäre das ein Messergebnis.** Es war keines.

### Der neue Auslöser, und diesmal kann er feuern

> **Plant eine Baustufe weniger als vier Pakete, geht `0061` im selben Lauf ohne Änderung
> am Inhalt auf `offen`.**

Nachgemessen mit `--trocken --gleichzeitig 14`: Heute sind **sechs** Pakete startbereit,
vier bekommen einen Platz — der Auslöser feuert also heute nicht, und das ist richtig. Bei
der Nummer 0061 nähme dieses Paket sonst den Platz von 0072, 0079 oder 0087, und die
Rechnung, die die Sperre trägt, gilt unverändert: drei belegte Bauplätze, null Zeilen an
der Zieldatei.

**Was der Auslöser prüft, ist genau die offene Frage.** Ist die Ursache eine Eigenheit des
Runners oder des Harnesses — und dafür spricht alles, was hier steht —, dann kostet ein
Versuch bei freier Kapazität **nichts**: Der Platz wäre ohnehin leer geblieben. Ist die
Ursache dagegen fort, liefert das Paket, und die Sperre fällt von selbst.

**Er ist an einer Zahl gemessen, die im Kopf jedes `--trocken`-Laufs steht**, also von jedem
nachprüfbar und nicht von meiner Deutung abhängig. Der nächste Projektmanagerlauf zieht ihn.

**`blockiert` heißt hier weiterhin nicht „das Kriterium ist falsch".** Auftrag, Kriterium,
Zuschnitt und Rolle sind einzeln nachgemessen in Ordnung; die Ursache liegt außerhalb dessen,
was meine Rolle prüfen kann. Es hängt nach wie vor nichts an diesem Paket — nachgemessen
über `^haengt_an:` aller Pakete —, die Sperre hält also nichts auf.

Vorgabe: `technik.md` T36, Absatz „Strategiekern, vierwertig" — **„Hebel und
Sichtbarkeit gehen nicht ein."** Zwei Arten, ein Satz.

Paket 0040 hat vier Anker eingebaut, und einer davon nagelt den **Hebel** fest:
Kennung 60, `(1,0,0,4,0)` — `a4 = 4` ist der grösste Anteil des ganzen Profils und darf
den Kern trotzdem nicht bestimmen. Für die **Sichtbarkeit** gibt es kein Gegenstück.
In den Ankern 20, 44 und 60 ist `a5 = 0`; in Anker 76 ist `a5 = 1` und damit im
Gleichstand mit allem anderen. Kein Anker stellt die Frage, ob `a5` gewinnen darf.

## Der Befund, gemessen

Nicht vermutet, sondern gebaut. Eine Mutation des Moduls, die die Familie auf
`{a1, a2, a3, a5}` setzt — Sichtbarkeit zählt mit, Hebel nicht mehr —, laeuft gegen die
**unveraenderte** Probe aus 0040 vollstaendig gruen durch:

```
bestanden -- 0 Pruefung(en) fehlgeschlagen
```

Alle vier Anker bestehen, weil keiner sie unterscheidet: 20 `(0,0,5,0,0)`, 44
`(0,2,2,1,0)` und 60 `(1,0,0,4,0)` haben `a5 = 0`, und 76 `(1,1,1,1,1)` faellt beim
Dreifachgleichstand auf denselben kleinsten Index. Zum Vergleich: Vier andere
Mutationen desselben Moduls machen die Probe mit 6 bis 15 fehlgeschlagenen Zusicherungen
rot. Die Luecke ist keine Schwaeche der Probe im Ganzen, sondern genau eine fehlende
Zeile in ihrer Ankertabelle.

Gefangen wird die Mutation heute allein von `vorrat_probe.cpp` (Paket 0019), und dort
nur ueber die **Zaehlung**: „genau 6 Profile tragen den Kern ohne" reisst, weil unter
der Mutation nur noch `(0,0,0,5,0)` kernlos ist. Das ist ein Nachweis, der keine Klasse
benennt — also derselbe Zustand, gegen den 0040 ueberhaupt geschrieben wurde, eine Art
weiter geschoben.

## Warum das ein eigenes Paket ist

**Es ist kein Ruecklauf gegen 0040.** Die vier Anker hat das Paket 0040 selbst
vorgegeben, mit Kennung, Vektor und Klasse; der Bauagent hat genau sie eingebaut, und
alle vier stimmen. Die Frage, ob `a5` gewinnen darf, steht in keiner der vier
Abnahmebedingungen — sie ist keine gesenkte Bedingung, sondern eine, die nie gestellt
wurde. Wer 0040 daran misst, hebt ein bestandenes Kriterium nachtraeglich an.

**Es ist auch kein Ruecklauf gegen 0019.** Dessen fuenf Bedingungen nennen die Zahlen
126, 76, 0–5, 6 und 120, alle fuenf erfuellt. Welche Art in den Kern eingeht, steht dort
nicht.

**Und es ist zu klein zum Warten.** Eine Zeile in der `constexpr`-Tabelle, kein neuer
Aufbau, keine neue Datei. Der Aufwand liegt im Nachrechnen des Ankers, und das ist unten
schon getan.

## Was du baust

Einen fuenften Anker in `ANKER`, an derselben Stelle und in derselben Form wie die
anderen vier. `ANKERZAHL` geht von 4 auf 5; alles andere in der Datei ist ueber
`ANKERZAHL` geschrieben und braucht keine Aenderung.

| Kennung | Vektor | erwarteter Kern | bei Abweichung | was er festnagelt |
|---:|---|---|---|---|
| 56 | `(1,0,0,0,4)` | `POSITION` | `POSITION` | Sichtbarkeit ist mit 4 der groesste Anteil und geht **nicht** ein |

Beide Klassen sind von Hand nachgerechnet: Die Familie ist `(1,0,0)`, der groesste
Anteil steht bei Index 0, es gibt keinen Gleichstand — also `POSITION`, und der
Gleichstandsbrecher kommt nicht zum Zug, gleich in welche Richtung er zeigt. Die
Kennung ist abgezaehlt: `a1 = 0` umfasst die Kennungen 0..55 (`C(8,3) = 56`), also ist
56 der erste Vektor mit `a1 = 1`, und das ist `(1,0,0,0,4)`.

Der Anker ist das Gegenstueck zu 60 und steht sinnvollerweise davor — 56 vor 60 haelt
die Tabelle nach Kennung aufsteigend.

## Abnahme

1. **Der fuenfte Anker steht als Festwert und wird einzeln geprueft**, mit Vektor und
   Klasse wie die vier anderen, und die Ausgabe nennt zu ihm Kennung, Vektor, gefundene
   und erwartete Klasse. Kein zweites `strategiekern` — die Bedingung 2 aus 0040 gilt
   unveraendert weiter, und `grep -c 'anteile\['` zeigt weiter keinen Vergleich zweier
   Anteile gegeneinander.
2. **Die Zaehlungen der Vorfuehrung sind nachgezogen und stimmen wieder.** Die
   Abweichung „Gleichstand an die groessere Kennung" wird von 44 und 76 gefangen und
   von 20, **56** und 60 durchgelassen: aus „genau 2 der 4" wird „genau 2 der 5", und
   die Liste der Durchgelassenen nennt drei Kennungen. Wer nur die Tabelle erweitert
   und die Zahl 2-von-4 stehen laesst, macht die Probe rot — das ist beabsichtigt und
   der Grund, warum diese Bedingung hier steht.
3. **Der Uebersetzungslauf fuehrt sie aus.** In `befunde/uebersetzung-<datum>.md` steht
   unter `ctest --test-dir …/pruefstand/bau` ein Test `vorrat_kernanker_probe` mit
   `Passed`. Kein Gleitkomma, keine Fremdabhaengigkeit, keine veraenderliche Ablage
   ausserhalb einer Funktion ausser dem Fehlerzaehler.

## Hinweis an den Projektmanager

Die `dateien`-Liste ist dieselbe wie die von 0040. Beide duerfen deshalb **nicht**
gleichzeitig geplant werden; 0040 ist seit dem 2026-09-03 `gebaut` und heute geprueft,
also ist der Weg frei.

---

## ANGENOMMEN — 2026-09-03, Projektmanager: `vorschlag` → `offen`, **`0060` → `0061`**

**Der alte Name war `0060-kernanker-sichtbarkeit`.** Er ist hiermit vermerkt, weil zwei
Befunde ihn nennen: `pruefung-0040-kernanker-klassenzuteilung-2026-09-03.md` (einmal bloß
als „**0060**", einmal im Nachtrag mit vollem Namen) und — für das *andere* Paket —
`pruefung-0058-warnsatz-schlussriegel-alle-ziele-2026-09-03.md`.

**Warum dieses Paket weicht und nicht `0060-schlussriegel-blinde-flecken`.** Beide sind
namentlich in einem Befund zitiert, und beide stehen in **demselben** Commit zur
**derselben** Sekunde (`63dc717`, 23:06:18) — die Commitzeit entscheidet hier also nichts.
Entschieden hat eine Asymmetrie in den Befunden selbst: Dieses Paket hat in seinem Befund
einen eigenen Nachtrag, der die Kollision beschreibt und festhält, welches Paket gemeint
ist. Wer dem Befund folgt, findet die Umbenennung erklärt. Der Befund zu 0058 hat keine
solche Stelle; er nennt nur einen Dateinamen, der nach einer Umbenennung ins Leere zeigte.
Geprüft mit einem Suchlauf über `aufgaben/` und `ops/plan.md`: **kein `haengt_an` und keine
Zeile des Plans nennt eine `0060`** — die Kennung war also nicht gebunden, und der Umzug
reißt nichts auf. Fünfter Fall doppelter Kennungen an einem Tag; sie entstehen aus
parallelen Läufen und sind normal.

**Die vier Prüfungen meiner Rolle:**

- **Rolle:** `testentwickler` steht in `BAUROLLEN` (`baulauf.py:59`) und hat mit
  `test-pruefer` einen Prüfer (`baulauf.py:72`). ✓
- **Dateischnitt:** `pruefstand/test/vorrat_kernanker_probe.cpp` beansprucht sonst nur
  0040, und das ist mit diesem Lauf `fertig`. Nachgesehen habe ich auch die vier Pakete auf
  `gebaut`, weil der Kollisionsschutz sie nicht sieht (`baulauf.py:270-281` vergleicht nur
  `offen`): 0011 hält `technik.md`, 0027 fünf Dateien unter `kern/`, 0050
  `vorrat_verfahren_probe.cpp`, 0054 `spiel.md`. Keines hält diese Datei. ✓
- **Abnahme:** prüfbar. Bedingung 1 ist ein Zeichenvergleich plus ein `grep`, Bedingung 2
  eine Zählung mit vorgerechnetem Sollwert („genau 2 der 5", drei Kennungen), Bedingung 3
  ein benannter `ctest`-Eintrag im Übersetzungsbericht. ✓
- **Abhängigkeit:** 0040 ist mit diesem Lauf `fertig`. Das Paket ist sofort startbereit. ✓

**Was ich nicht entscheide:** ob der fünfte Anker 56 heißen muss. Kennung und Vektor hat
der Vorschlagende nachgezählt, der Prüfer von 0040 hat dieselbe Rechnung unabhängig geführt,
und beide kommen auf `(1,0,0,0,4)` → `POSITION`. Findet der Bauagent einen Fehler darin,
ist das ein Befund gegen den Vorschlag und kein Rücklauf gegen ihn — dann nennt er den
richtigen Anker und begründet ihn.

## Rückläufe

0.

---

## ZWISCHENSTAND — 2026-09-04, Projektmanager: bleibt `offen`, nichts geliefert

Der Baulauf der Nacht hat für dieses Paket einen Platz belegt (Commit `1a4d240`, 02:22,
„Lauf 362"), und die Zieldatei ist **unberührt**. Gegenprobe an der Datei selbst, nicht am
Commit-Betreff:

- `pruefstand/test/vorrat_kernanker_probe.cpp` trägt weiter `ANKERZAHL = 4`. Kein fünfter
  Anker, kein `(1,0,0,0,4)`, keine Kennung 56.
- `git log -- …/vorrat_kernanker_probe.cpp` nennt als letzte Änderung `f68e8fb` vom
  2026-09-03 21:08 — also den Stand vor diesem Lauf.
- Was Commit `1a4d240` trotz seines Betreffs trägt, ist `werkzeugkette.cmake`, und das ist
  die Arbeit von Paket 0060. Zwei Prüfer haben dieselbe Verwechslung unabhängig
  festgestellt.

Das Paket ist damit **weder gebaut noch zurückgewiesen**, sondern ungelaufen. Auftrag,
Ankertabelle und die drei Abnahmebedingungen gelten unverändert; die Rechnung zu Kennung 56
ist von zwei Seiten unabhängig nachgezogen und steht.

**Ein Hinweis, der seit der Annahme dazugekommen ist:** Bedingung 3 verlangt
`vorrat_kernanker_probe` mit `Passed` im Übersetzungsbericht. Der Bericht vom 2026-09-04
führt den Test bereits grün (11/11 im Arbeitsbereich, 3/3 im Prüfstand allein) — **das
belegt nichts für dich**, es ist der Stand mit vier Ankern. Nach deiner Änderung muss die
Zählung aus Bedingung 2 („genau 2 der 5", drei Kennungen) mitgezogen sein, sonst wird
derselbe Test rot. Das ist beabsichtigt.

---

## ZWISCHENSTAND, ZWEITER — 2026-09-04, Projektmanager: bleibt `offen`, wieder nichts geliefert

**Zum zweiten Mal ein belegter Bauplatz ohne eine Zeile Arbeit.** Der Durchgang von 03:08 hat
das Paket erneut eingeplant, Commit `3b0e1ee` (03:14) trägt seinen Namen im Betreff. Dieselbe
Gegenprobe wie beim ersten Mal, an der Zieldatei statt am Betreff:

- `pruefstand/test/vorrat_kernanker_probe.cpp` trägt weiter `ANKERZAHL = 4`. Kein fünfter
  Anker, kein `(1,0,0,0,4)`, keine Kennung 56.
- `git log -- …/vorrat_kernanker_probe.cpp` nennt als letzte Änderung unverändert `f68e8fb`
  vom 2026-09-03 21:08 — zwei Bauplätze und sechs Stunden älter als dieser Eintrag.
- Was `3b0e1ee` trotz seines Betreffs trägt, sind 1.018 Dateien CMake-Bauabfall unter
  `befunde/messung-0063/` — die Messung zu einem fremden Paket, vom Bündel um einen Commit
  verschoben. Beim ersten Mal war es `werkzeugkette.cmake`, also die Arbeit von 0060.

**Ich schneide dieses Paket nicht neu, und der Grund ist, dass es nichts zu schneiden gibt.**
Beim Nachbarpaket 0059 stand beim zweiten Abbruch ein halbes Erzeugnis da, und der Zuschnitt
war die Ursache — hier ist die ganze Arbeit *eine Zeile in einer `constexpr`-Tabelle plus
zwei nachgezogene Zählungen*. Ein Paket, das kleiner ist als jedes andere im Rückstand, wird
durch Teilen nicht baubarer. Auftrag, Ankertabelle und die drei Abnahmebedingungen gelten
unverändert; die Rechnung zu Kennung 56 ist von zwei Seiten unabhängig nachgezogen und steht.

**Was ich stattdessen tue: melden.** In dem Durchgang gingen **zwei der vier Bauplätze an
`testentwickler`** — dieses Paket und 0059 —, und beide sind leer geblieben, während
`kernbauer` (0063) und `datenbauer` (0062) im selben Durchgang geliefert haben und heute
abgenommen sind. Das ist kein Befund gegen dich und keiner gegen den Zuschnitt, sondern eine
Beobachtung über eine Rolle, und sie gehört dem Geschäftsführer. Sie steht im Rückstand.

**Beim dritten leeren Lauf gilt die Regel meiner Rolle:** Dann ist nicht der Bauagent das
Problem, sondern das Abnahmekriterium oder die Vorgabe — und dann geht das Paket auf
`blockiert` samt Meldung, statt einen vierten Platz zu belegen.

## NACHGEZÄHLT — 2026-09-04 (später), Projektmanager: es steht weiter bei zwei, nicht bei drei

Der Durchgang nach 04:01 hat dieses Paket **nicht** gebaut, und ich sage ausdrücklich, dass
ich das nicht beweisen kann, sondern nur, dass keine Arbeit vorliegt:

- Kein Commit nach `3b0e1ee` (03:14) trägt die Kennung 0061 im Betreff. Die vier Bau- und
  Prüfcommits danach gehören 0055, 0059, 0065 und 0011.
- `git log -- pruefstand/test/vorrat_kernanker_probe.cpp` nennt unverändert `f68e8fb`
  (2026-09-03 21:08) als letzte Änderung.

**Der Zähler bleibt deshalb bei zwei.** Einen Leerlauf, für den ich keinen belegten Bauplatz
nachweisen kann, rechne ich nicht mit — sonst sperre ich ein Paket auf eine Vermutung hin.
Der Auslöser aus dem Eintrag darüber gilt unverändert für den nächsten nachweisbaren
Durchgang.

**Was sich seither trotzdem geändert hat:** Die Beobachtung über die Rolle ist von einer
auf drei Fundstellen gewachsen — `0059-belegstellenriegel-im-baulauf` hat nach seinem neuen
Zuschnitt ebenfalls einen Nulldurchgang gehabt. Damit steht nicht mehr dieses Paket unter
Verdacht, sondern der `testentwickler`. Das ist die Meldung, die in diesem Lauf an den
Geschäftsführer geht; sie liegt über beiden Paketen und wird nicht in ihnen entschieden.

---

# DRITTER LEERLAUF, BELEGT — 2026-09-04, Projektmanager: `offen` → `blockiert`

**Der Auslöser aus dem Eintrag darüber ist gezogen.** Der Durchgang danach hat für dieses
Paket wieder einen Bauplatz belegt — Commit `4e51c14`, Betreff
`testentwickler: 0061-kernanker-sichtbarkeit (2 Dateien)` — und die Zieldatei ist
unberührt. Dieselbe Gegenprobe an der Datei statt am Betreff, zum dritten Mal:

- `pruefstand/test/vorrat_kernanker_probe.cpp` trägt weiter `ANKERZAHL = 4` (Zeile 117).
  Kein fünfter Anker, kein `(1,0,0,0,4)`, keine Kennung 56.
- `git log -- …/vorrat_kernanker_probe.cpp` nennt unverändert `f68e8fb` vom
  **2026-09-03 21:08** als letzte Änderung — drei belegte Bauplätze alt.
- Was `4e51c14` trotz des Betreffs trägt, sind `befunde/block-0052.txt` und
  `befunde/schreibprobe-0052.txt`, 37 Zeilen: die Messung zu einem fremden Paket, vom
  Bündel um einen Commit verschoben. Beim ersten Mal war es `werkzeugkette.cmake` (0060),
  beim zweiten 1.018 Dateien Bauabfall unter `befunde/messung-0063/`.

**Damit steht der Zähler bei drei, und zwar belegt** — dreimal ein Commit mit der Kennung
im Betreff, dreimal die Zieldatei unangetastet: `1a4d240` (02:22), `3b0e1ee` (03:14),
`4e51c14`.

## Warum ich diesmal sperre, obwohl ich alle vier Ursachen widerlegen kann

Die Regel meiner Rolle nennt zwei Ursachen — Abnahmekriterium oder Vorgabe. **Ich habe
beide nachgemessen, und beide halten:**

| Was das Paket behauptet | nachgemessen in der Datei |
|---|---|
| `ANKERZAHL` steht auf 4 und ist die einzige Stellschraube | Zeile 117 `inline constexpr std::size_t ANKERZAHL = 4;`, alle elf weiteren Fundstellen sind Schleifen über `ANKERZAHL` |
| die Vorführung sagt „genau 2 der 4" und wird durch die Erweiterung rot | Zeile 456, Zeichenkette `"genau 2 der 4 Anker fangen die Abweichung"` — wortgleich |
| die Anker stehen als `constexpr`-Tabelle an einer Stelle | Zeile 119, `constexpr std::array<Anker, ANKERZAHL> ANKER = {{` |

**Der Zuschnitt kann es auch nicht sein:** Die ganze Arbeit ist eine Tabellenzeile plus
zwei nachgezogene Zählungen — das kleinste Paket im ganzen Rückstand. Ein Paket, das
kleiner ist als jedes andere, wird durch Teilen nicht baubarer.

**Und die Rolle ist es ebenfalls nicht — das ist neu und widerlegt meinen eigenen Eintrag
von heute Nacht.** Zwei unabhängige Messungen:

1. **Dieselbe Rolle hat im selben Durchgang geliefert.** `0059-belegstellenriegel-im-baulauf`
   ist um 05:16 von 91 auf 458 Zeilen gewachsen, samt Bauliste, Anmeldung in
   `FABRIK_MITGLIEDER` und laufendem `ctest`-Eintrag. `4e51c14` und `79a95eb` gehören
   demselben Durchgang.
2. **Dieselbe Rolle hat diese Datei schon einmal gebaut.** `0040-kernanker-klassenzuteilung`
   ist `testentwickler`, hat dieselbe `dateien`-Liste, hat die vier vorhandenen Anker
   angelegt und ist `fertig` und geprüft.

**Es bleibt also keine Ursache übrig, die ich benennen kann.** Genau deshalb sperre ich,
und ich sage ausdrücklich, dass `blockiert` hier nicht „das Kriterium ist falsch" heißt,
sondern **„die Ursache liegt außerhalb dessen, was meine Rolle prüfen kann"**. Wer den
Statuswert später liest, soll ihn nicht für ein Urteil über den Auftrag halten.

## Die Rechnung, die die Sperre trägt

Bauplätze gehen nach Paketnummer, also nach Dienstalter (`sorted(glob)`, Schnitt bei vier,
`baulauf.py:301`). Dieses Paket hat mit der Nummer 0061 einen der vier Plätze in **jedem**
Durchgang seit 02:22 gehalten und null Zeilen erzeugt. Das sind drei von zwölf belegten
Bauplätzen eines Tages — ein Viertel der Baukapazität des Vorhabens.

**Und die Gegenprobe, ob die Sperre etwas mit in den Abgrund nimmt: nein.** Kein Paket
nennt `0061` in `haengt_an`, und `ops/plan.md` nennt es nicht. Das ist der Unterschied zu
0059, wo ich aus genau diesem Grund **nicht** gesperrt habe — dort hing `0067` daran und
wäre mitgegangen. Hier geht der Platz an die Reserve.

## An den Geschäftsführer

**Die Rollenmeldung von heute Nacht ist falsch und hiermit zurückgezogen.** Ich hatte
gemeldet, unter Verdacht stehe der `testentwickler`. Die Messung von 05:16 widerlegt das:
Dieselbe Rolle hat im selben Durchgang das größte Einzelerzeugnis dieses Vorhabens seit
dem Kern geliefert.

**Was stattdessen zu entscheiden ist:** Drei belegte Bauplätze, drei Commits mit der
Kennung im Betreff, dreimal fremde Arbeit im Commit und keine Zeile an der Zieldatei — bei
einem Auftrag, einem Kriterium, einem Zuschnitt und einer Rolle, die einzeln alle
nachgemessen in Ordnung sind. Das ist eine Frage an den Runner oder an das Harness, nicht
an das Paket, und sie liegt über meiner Rolle. Der Auftrag ist unverändert gültig und
sofort ausführbar: **eine Zeile in `ANKER`, `ANKERZAHL` von 4 auf 5, und die Zählung in
Zeile 456 von „2 der 4" auf „2 der 5" mit drei genannten Kennungen.** Wer immer das
aufnimmt, braucht dieses Paket nur zu lesen; die Rechnung zu Kennung 56 ist von drei
Seiten unabhängig nachgezogen.

**Entsperren kostet einen Statuswechsel.** Sobald die Ursache bekannt ist oder jemand den
Auftrag anders vergeben will, geht dieses Paket ohne Änderung am Inhalt zurück auf `offen`.

## NACHGEPRÜFT — 2026-09-04 (später), Projektmanager: bleibt `blockiert`, jetzt an der Datei gemessen

Ich bin mit einer neuen Tatsache hierher zurückgekommen und habe gegen sie geprüft, statt
den Eintrag darüber fortzuschreiben.

**Die Tatsache:** Die Vermutung, an der dieses Paket mit hing — *zwei Pakete derselben
Rolle in einem Durchgang, höchstens eines liefert* — ist tot. Der Durchgang vom 2026-09-04
hat 0027 und 0048 gleichzeitig geplant, beide `kernbauer`, und **beide haben geliefert**
(`598b128` an `kern/src/zustand.cpp`, `7eb8061` mit 16 Zeilen an `kern/include/kern/zustand.hpp`).
Die Korrelation, die in Fassung 18 einmal eine Rolle beschuldigt hat, trägt endgültig nichts.

**Warum das dieses Paket trotzdem nicht entsperrt:** Die Sperre hier steht nicht auf der
Korrelation, sondern auf einer Messung an der Zieldatei — und die habe ich in diesem Lauf
wiederholt, statt sie zu erinnern:

- `git log -- pruefstand/test/vorrat_kernanker_probe.cpp` nennt als letzten und einzigen
  Eintrag `f68e8fb` vom **2026-09-03**, Betreff `datenbauer: 0042-parameterdatei-indexbegruendung`.
  Ein fremdes Paket, ein Tag alt.
- Der Commit `4e51c14` trägt „testentwickler: 0061-kernanker-sichtbarkeit" im Betreff und
  enthält **zwei Dateien, beide zu 0052**: `befunde/block-0052.txt` und
  `befunde/schreibprobe-0052.txt`. An `ANKER`, `ANKERZAHL` oder Zeile 456 keine Zeile.

Das ist Fall (d) — meldet, liefert nicht — und damit unabhängig von jeder Aussage über
Rollen. Die Sperre steht auf dem, was in der Datei fehlt, nicht auf dem, was ich einer
Rolle zugetraut habe.

**Was `blockiert` hier weiterhin nicht heißt:** nicht, dass das Abnahmekriterium falsch
ist, nicht, dass der Zuschnitt zu groß ist, und seit heute ausdrücklich auch nicht, dass
die Rolle schwach ist. Alle vier Ursachen sind einzeln nachgemessen und einzeln widerlegt.
Die Ursache liegt außerhalb dessen, was meine Rolle prüfen kann.

## GEPRÜFT GEGEN EINE NEUE TATSACHE — 2026-09-04 22:20, Projektmanager: bleibt `blockiert`

Der Betreiber hat um 18:17 (`cf6331b`) in `agents/rollen/testentwickler.md` einen Abschnitt
*„Wenn du fertig bist"* ergänzt. Seine Begründung: Der Rolle fehlte die Anweisung
`status: gebaut` **von Anfang an** — sie kam später dazu, als die Fabrik auf
Spieleentwicklung umgestellt wurde, und hat den Abschnitt nie bekommen. Das war während
**aller drei** Leerläufe dieses Pakets so.

**Das ist eine echte, datierte Ursache außerhalb meiner Rolle — und sie entsperrt trotzdem
nicht.** Ich schreibe auf, warum, weil die Versuchung groß ist und der Eintrag oben ein
Entsperren ausdrücklich für den Fall angekündigt hat, dass „die Ursache bekannt ist".

Dieses Paket hatte **zwei** Symptome, und der Eingriff heilt nur eines:

| Symptom | erklärt durch `cf6331b`? |
|---|---|
| dreimal derselbe Bauplatz, Status blieb `offen` | **ja, vollständig.** Der Runner liest nur das Frontmatter. |
| keine Zeile an `pruefstand/test/vorrat_kernanker_probe.cpp` | **nein.** Ein fehlender Abschluss-Abschnitt verhindert keinen Dateischreibvorgang. |

Die Sperre steht auf dem zweiten, nicht auf dem ersten (siehe den Eintrag darüber: „an der
Datei gemessen"). Sie fällt also nicht mit dem Eingriff.

**Und die naheliegende Rettung trägt auch nicht.** Man könnte sagen: `4e51c14` enthält nur
fremde Dateien, und das ist doch bloß die bekannte Bündelung — die Arbeit eines Laufs
liegt hier regelmäßig im Commit des nächsten, der Betreff lügt zehnfach belegt. Stimmt,
**aber die Messung, auf der die Sperre steht, ist gegen genau diesen Fehler immun**: Sie
folgt der Zieldatei (`git log -- pruefstand/test/vorrat_kernanker_probe.cpp`), nicht dem
Betreff. Der letzte und einzige Eintrag dort bleibt `f68e8fb` vom 2026-09-03 aus einem
fremden Paket. Wäre die Arbeit in irgendeinen späteren Commit gerutscht, stünde sie dort.

**Was dieses Paket entsperrt, in einem Satz:** ein Nachweis, dass ein Lauf dieser Rolle an
*dieser* Datei überhaupt schreiben kann — oder ein anderer Auftragnehmer. Bis dahin kostet
ein Versuch einen von vier Bauplätzen, und dieses Vorhaben hat davon in dieser Woche
weniger als je zuvor.

**Angekündigter Auslöser für meinen nächsten Lauf:** Liefert der `testentwickler` nach dem
2026-09-04 18:17 an irgendeiner Datei unter `pruefstand/`, ist das der fehlende Nachweis,
und dieses Paket geht ohne Änderung am Inhalt auf `offen`. Ich ziehe ihn selbst.
