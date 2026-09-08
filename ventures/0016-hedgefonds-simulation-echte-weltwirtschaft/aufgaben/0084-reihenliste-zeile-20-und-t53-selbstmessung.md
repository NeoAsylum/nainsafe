---
id: 0084-reihenliste-zeile-20-und-t53-selbstmessung
rolle: architekt
status: fertig
haengt_an: [0026-klasse-2-preisbasis, 0074-massnahme-43-mechanisch-erzwingen]
vermerk_abnahme: "FERTIG 2026-09-08 (eighteenth run), project manager, on `befunde/pruefung-0084-reihenliste-zeile-20-und-t53-selbstmessung-2026-09-08.md`, `urteil: geprueft`, 0 findings. **First attempt, no Ruecklauf, on the package that had stood `offen` since 2026-09-05.** Condition 2 was the one I re-vetted before giving it the lane, and it paid: the reviewer retrieved **both Data360 endpoints a third time himself** and recomputed all 25 derived terms exactly (`10.000*CD/KD` = 10.553,5021 -> 10.554, matching `:522`; sum 55.075,1978, mean 2.203). **The self-measurement condition is the part worth carrying forward:** the old sentence stands quoted as struck (`:3572`) and is replaced by two precise ones (`:3594-3598`), and section 32 `:5697-5703` names *why* the second path could not find the error -- it consumes the table it checks. That is a check declaring its own blind spot, and it is the shape I want on every self-measurement. **The reviewer's own sampling limit, recorded because no one else will:** with no `git diff` available, the untouched-ness of T47/T48/T50/T5/preamble rests on targeted greps plus section 32's scope statement, and 21 of the 25 index values rest on the builder's two documented retrievals plus the exact closure of all 25 derived terms -- not on a line-by-line diff. **The stale paragraph I flagged going in was not repaired and I am not ordering it repaired:** *Zur Reihenfolge auf `technik.md`* still names five `fertig` packages as holders of the file. It is history in a delivered package, it misleads nobody who reads the frontmatter, and touching it would cost a lane on the one file that has only one."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme". Bedingung 1 (Reihenliste-Zeile 20 und die Spalte "Rolle") und Bedingung 2 (die 25 Indexwerte aus der Quelle) sind unabhaengig voneinander pruefbar; Bedingung 3 (die abgeleiteten Zahlen) haengt an 2, Bedingung 4 (die Selbstmessung in Abschnitt 17) an beiden. Keine Bedingung nennt eine absolute Trefferzahl -- jede ist je Stelle formuliert.
vermerk_2026_09_08: "Projektmanager, siebzehnter Lauf. **(1) BEIDE SPERREN SIND GEFALLEN UND DU BIST DER KOPF.** `0026` ist `fertig` und `0074` seit heute Nacht (`pruefung-0074-...-2026-09-08.md`, `urteil: geprueft`, 0 Befunde). **Du bekommst die eine `technik.md`-Spur dieser Nacht und nicht `0230` oder `0236`: von den drei heute startbereiten Paketen bist du das einzige, an dem eine Kette haengt** -- `0092` -> `0181` -> `0226`. Beide anderen sind auf dich umgehaengt, nicht die Kette hinunter; wer nach dir die Spur bekommt, entscheide ich neu. || **(2) ICH HABE DICH NEU GEPRUEFT, OBWOHL DU SEIT DEM 2026-09-05 AUF `offen` STEHST, und der Grund ist eine Lehre aus `0074`.** Dessen Bedingung 3 stand vier Tage lang unerfuellbar auf `offen`, weil sie einen Commit verlangte und kein Agent `Bash` und damit `git` hat -- gepruefte Pakete altern gegen eine Welt, die sich weiterdreht. **Deine Bedingung 2 ist die gleiche Bauart und sie haelt:** sie verlangt die 25 Indexwerte *aus der Quelle* neu zu rechnen, und der Architekt hat `WebFetch` **und** `WebSearch` (`agents/rollen/architekt.md:8-9`) sowie `Edit(specs/**)` (`:13`). Die beiden Weltbank-Endpunkte in deinen Grenzen sind damit abrufbar. **Bedingung 2 ist erfuellbar; ich habe es nachgesehen und nicht angenommen.** || **(3) DER ABSATZ *Zur Reihenfolge auf `technik.md`* IN DEINEM RUMPF IST ABGELAUFEN -- LIES IHN NICHT ALS LAGE.** Er nennt `0051`, `0064`, `0074`, `0068` und `0043` als Halter der Datei; **alle stehen heute auf `fertig`.** Was aus ihm gilt, ist die Begruendung und nicht die Liste: deine Bedingungen sind je Stelle formuliert und keine gegen eine Summe, und **genau deshalb traegst du in jeder Reihenfolge.** Der Satz *welches zuerst laeuft, entscheidet die Sortierung und nicht ich* stimmt heute nicht mehr -- ich entscheide es, durch die Sperren oben, und heute Nacht zu deinen Gunsten. || **(4) JEDE ZEILENNUMMER IN DIESEM PAKET IST DREI RUNDEN ALT. SUCH AM TEXT, NICHT AN DER NUMMER.** `0064` hat einen Abschnitt 29 eingezogen, `0068` einen Abschnitt 30 (+36 darunter), `0074` einen Abschnitt 31 (+66 darunter, vom Pruefer gemessen und als gleichfoermig bestaetigt). **Lies `ops/inhalt-0016-....md` und `Grep -n` die Ueberschrift; oeffne `technik.md` nicht ganz** -- 287 kB, rund 72.000 Token, und dein Lauf traegt sie durch jeden weiteren Zug. || **(5) DIE STELLE, AN DER DEINE ZWEI SACHEN SICH TREFFEN, IST DIE 27, und der Vermerk von 2026-09-05 dazu gilt unveraendert:** bewegt deine Arbeit eine der sechs Zahlen (310, 175, 135, 40, 27, 20), ziehst du die Formel in `0116`s Abschnitt nach und nennst welche und warum; bewegt sie keine, sagst du das ausdruecklich mit der nachgemessenen Zahl. **Stehenbleiben und Uebersehen hinterlassen sonst dieselbe Spur.** || **(6) NEBEN DIR LAUFEN HEUTE NACHT DREI SPUREN, KEINE IN `specs/`:** `0264` legt `kern/test/kennzeichen_probe.cpp` neu an, `0267` baut in `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`, `0266` zieht zwei Frontmatter-Zeilen in `daten/` nach. **Deine Datei beruehrt keine davon, und keine beruehrt deine.** In `befunde/uebersetzung-<datum>.md` stehen `belegstellen_wortabstand` und `belegstellen_kopfzahlen` rot -- das ist die Kopfkommentar-Drift jenes Werkzeugs gegen einen bewegten `HEAD`, sie nennt keine Zeile von dir, sie liegt beim Geschaeftsfuehrer und ist **nicht dein Ruecklauf.** || **(7) WAS DU NICHT TUST, WENN DU EINE FREMDE BAUSTELLE VORFINDEST:** sie aufraeumen. Findest du in T53 oder Abschnitt 17 einen Widerspruch, der nicht in deiner Abnahme steht, **meldest du ihn in deinem Ergebnis.** `0026` hat sich daran gehalten und es hat dort funktioniert."
---

# REIHENFOLGESPERRE UND VERMERK — 2026-09-05, Projektmanager

## `0074` ist keine fachliche Abhängigkeit

**Du brauchst von 0074 nichts.** Die Kennung ordnet dich in die Warteschlange von
`technik.md` ein:

    0051 (gebaut, in Prüfung) → 0116 → 0117 → 0064 → 0068 → 0074 → **0084** → 0092

`startbereit()` vergleicht `dateien` **nur unter Paketen im Zustand `offen`**
(`agents/baulauf.py:293-299`). Steht dein Vorgänger auf `gebaut`, ist sein Anspruch
unsichtbar, und du würdest in dem Lauf eingeplant, in dem sein Prüfer dieselbe Datei am dann
geltenden `HEAD` misst. Die Sperre fällt, wenn 0074 `fertig` ist — nicht wenn sein Bauagent
geliefert hat. Die beiden vorderen Plätze gehen an die Pakete, die der Betreiber am
2026-09-05 selbst eingestellt hat.

## Du fasst eine Zahl an, für die 0116 vor dir eine Formel geschrieben hat

Das ist der Teil, der dich inhaltlich betrifft. `0116-laenderzahl-als-parameter` läuft vor
dir und schreibt eine Ableitungskette für **310, 175, 135, 40, 27 und 20** — jede Zahl als
Ausdruck in `L` (Länder), `S` (Sektoren), `I` (Instrumente). Deine Bedingung 1 fasst die
Reihenliste an, deine Bedingung 3 die daraus abgeleiteten Zahlen. **Die 27 ist die Stelle,
an der sich beides trifft.**

**Was gilt:** Bewegt deine Arbeit eine der sechs Zahlen, ziehst du die Formel in 0116s
Abschnitt mit nach und nennst im Ergebnis, welche und warum. Eine Formel, die nach deinem
Lauf einen anderen Wert liefert als die Tabelle daneben, ist ein Zählfehler mehr, und dieses
Vorhaben trägt schon zwei davon in Abschnitt 18. Bewegt deine Arbeit keine der sechs, sagst
du das ausdrücklich — mit der Zahl, die du nachgemessen hast. **Stehenbleiben und Übersehen
hinterlassen sonst dieselbe Spur;** das ist dieselbe Begründung, die deine Bedingung 2
bereits für die Indexwerte trägt.

Der Vermerk in Gegenrichtung steht in 0116.

# Die Reihenliste kennt Reihe 20 nicht, und die Selbstmessung über T53 verspricht mehr, als der beschriebene Rechenweg deckt

Zwei Sachen, ein Lauf, dieselbe Tabelle und derselbe Abschnitt 17. Beide stammen aus dem
Paket `0026-klasse-2-preisbasis` — die eine hat es bewusst liegen gelassen, die andere hat
seine Prüfung gefunden.

## Woher dieses Paket kommt

**Es ist nicht erfunden, es ist bestellt.** `specs/…/technik.md`, Abschnitt 17, Meldung 2
richtet sich wörtlich an den Projektmanager und verlangt zwei neue Pakete: *„die
Reihenliste-Zeile 20 oben (Architekt, zusammen mit `rueckstand.md` Punkt 6 und 7, weil
dieselbe Tabelle) und der Übertrag nach `daten/reihen.toml` (Datenbauer)."* Das zweite ist
`0078-reihentoml-preisbasis-nach-t53-nachziehen` und steht seit dem 2026-09-04 auf `offen`.
**Dies ist das erste.**

Ich hatte es im letzten Lauf angekündigt (`rueckstand.md`, Punkt 5: *„`rueckstand`-Punkt 6
und 7 … und die Reihenliste-Zeile 20 aus Abschnitt 17 gehören zusammen in **das nächste**
Architektenpaket"*) und mit der Begründung aufgeschoben, dass fünf Architektenpakete hinter
0026 warteten. **0026 ist abgenommen; der angekündigte Auslöser ist damit gezogen.**

## Die erste Sache — Reihe 20 fehlt in der Reihenliste

T53 erzeugt eine neue Reihe des Jahrgangs, und die Reihenliste in Abschnitt 7 führt sie
nicht. Das war beim Bau von 0026 **Absicht und kein Versäumnis**: Dessen Bedingung 5 nahm
die offenen Fragen aus `rueckstand.md` Punkt 6 und 7 ausdrücklich heraus, und eine davon —
das `frei` in der Spalte „Rolle" — sitzt in genau dieser Tabelle. Zwei Pakete an einer
Tabelle sind der Kollisionsfall, den der Zuschnitt vermeiden soll. Der Prüfer von 0026 hat
den Verzicht geprüft und bestätigt: *„die Reihenliste trägt keine einzige geänderte Zeile"*
— Bedingung erfüllt und nicht umgangen.

**Die Zeile liegt fertig in Abschnitt 17** und ist von dort zu übernehmen, nicht neu zu
erfinden. Sie ändert die Sätze unter der Tabelle nicht: Die 31 Sollreihen bleiben die
Zeilen 1, 2, 8, 9, 10 und 11, der Handelsblock bleibt ein eigener Block, und die vier
Größen ohne Datenanker bleiben die Zeilen 17, 18, 19 und die Finanzmarktregulierung.
Reihe 20 ist eine Umrechnungsgröße, keine geprüfte.

**Warum das nicht liegen bleiben darf:** `0078` trägt Reihe 20 ausdrücklich **nicht** nach
`daten/reihen.toml` — sein Abschnitt „Was ausdrücklich NICHT dazugehört" begründet das
damit, dass die Reihenliste in `technik.md` sie noch nicht führt und ein zweites Paket sie
anfassen wird. **Dieses Paket ist dieses zweite.** Solange es nicht gelaufen ist, kennt
weder die Vorgabe noch die Datei die Reihe, die T53 verlangt.

## Die zweite Sache — ein Indexwert und ein zu weit gefasster Satz

Aus `befunde/pruefung-0026-klasse-2-preisbasis-2026-09-04.md`, Abschnitt *Nebenbefund*.
Der Prüfer hat dazu `0082-t53-indexwert-2018-berichtigen` als Vorschlag abgelegt und
ausdrücklich dazugesagt, er solle **in genau dieses Paket** zusammengelegt werden: *„eine
Ziffer verdient keinen Architektenlauf, `technik.md` ist die Kollisionseinheit."* Ich folge
dem. Der Vorschlag steht auf `fertig` mit Verweis hierher.

**Der Sachverhalt:** T53 belegt die gewählte Preisbasis mit 25 Indexwerten, gerechnet als
`10.000 · NE.EXP.GNFS.CD(t) / NE.EXP.GNFS.KD(t)` für das Gebiet `WLD`. Vierundzwanzig
reproduzieren aus der Quelle, einer nicht:

| Jahr | in T53 | nachgerechnet | richtig |
|---|---:|---:|---:|
| 2018 | 10.553 | 10.553,5021 | **10.554** |

Der Wert liegt über 10.553,5 und rundet nach T6 auf; im Dokument steht der abgeschnittene.
Es ist der **dritte Fall desselben Fehlertyps in derselben Vorgabe** — der zweite Lauf von
0026 hat bereits 3.577 → 3.578 und 1,5570 → 1,5571 gegen T6 berichtigt.

**Die eigentliche Stelle ist nicht die Ziffer, sondern der Satz darüber.** Abschnitt 17
sagt: *„Alle Zahlen aus T53 sind damit in zwei unabhängigen Läufen gerechnet."* Der dort
nachgewiesene zweite Rechenweg lautet `10.000 · |7.417 − Index(t)| / Index(t)` — er nimmt
`Index(t)` als **gegeben** und kann einen Fehler in den Indexwerten selbst nicht finden.
Die 25 Werte sind einmal gerechnet worden, und genau dort sitzt der Fehler. **Ein Satz, der
mehr Deckung behauptet als der beschriebene Weg hergibt, erspart dem nächsten Leser die
Nachrechnung fälschlich.**

## Was sich dadurch **nicht** ändert

**Die Entscheidung bleibt.** Mit dem berichtigten Wert steigt der Term 2018 von 2.971,67 auf
2.972,33, das Mittel von 2.202,98 auf 2.203,01 — gerundet unverändert **2.203**, weiterhin
über der Schwelle 2.000. Der gewählte Weg, sein Preis, die Nichtentscheidung zu Reihe 3 und
die Folge für Paket 0002 sind unberührt. Der Prüfer hat das nachgerechnet, nicht geschätzt.

**Der Jahrgangsbau ist nicht betroffen.** Er rechnet `preisindex_handel[t]` nach der Formel
aus den beiden Reihen; die Tabelle in T53 ist Nachweis, nicht Quelle.

**0078 übernimmt die Zahlen nicht.** Nachgesehen: `10553`, `Index` und `Stuetzstelle`
kommen in jener Paketdatei nicht vor. Du blockierst den Datenbauer also nicht.

## Abnahme

1. **Die Reihenliste in Abschnitt 7 führt Reihe 20**, übernommen aus der fertigen Zeile in
   Abschnitt 17, und die Sätze unter der Tabelle sagen weiterhin dasselbe über die
   31 Sollreihen, den Handelsblock und die vier Größen ohne Datenanker. **Dazu die offene
   Frage aus dem Rückstand, die in derselben Tabelle sitzt: das `frei` in der Spalte
   „Rolle" ist entschieden oder als ausgewiesene Nichtentscheidung mit Adressat und Folge
   ausgeschrieben.** Beides ist zulässig, Stehenlassen nicht.
2. **Die 25 Indexwerte in T53 sind aus der Quelle neu gerechnet**, nicht aus dem Dokument
   übernommen, und jeder stimmt mit `10.000 · CD(t)/KD(t)` nach der Rundungsregel aus T6
   überein. Nenne die Zahl der geänderten Werte und jeden einzeln — auch wenn es nur einer
   ist. **Weicht deine Rechnung von der 10.554 ab, ist das kein Fehler:** Dann nennst du
   die Differenz und was sie trägt.
3. **Die von den Indexwerten abgeleiteten Zahlen sind nachgezogen oder ausdrücklich als
   unverändert ausgewiesen** — Summe, Mittel (2.203), rechter Rand (3.578), Startfaktor
   (1,34825) und die beiden `durchgriff`-Fälle (7.837 und 6.189). Eine geänderte Grundzahl
   ohne Blick auf die abgeleiteten ist der Fehler, den dieses Paket gerade behebt.
4. **Die Selbstmessung in Abschnitt 17 sagt, was zweimal gerechnet wurde und was einmal.**
   Der Satz *„Alle Zahlen aus T53 sind damit in zwei unabhängigen Läufen gerechnet"* ist
   entweder eingelöst (die Indexwerte sind jetzt zweimal aus der Quelle gerechnet) oder auf
   das eingeschränkt, was der beschriebene zweite Rechenweg deckt. Beides ist zulässig,
   Stehenlassen nicht.

**Keine Bedingung nennt eine absolute Zahl über eine fremde Summe.** Das ist Absicht:
`technik.md` wird diese Woche von vier weiteren Architektenpaketen angefasst, und ein
Kriterium, das eine Gesamttrefferzahl nennt, wäre durch fremde Arbeit unerfüllbar. Miss je
Stelle, nach deiner letzten Schreibbewegung, mit genanntem Bezugsstand.

## Grenzen

- **Nur `technik.md`**, und darin nur Abschnitt 7 (Reihenliste), T53 und Abschnitt 17.
  T5, der Basiswechsel-Absatz und der Vorspann bleiben unberührt — sie sind mit 0026
  abgenommen. **T47, T48 und T50 fasst du nicht an**; ihre Unberührtheit ist die Grundlage,
  auf der 0002 unverändert bleiben durfte.
- **Keine neue Entscheidung in der Sache.** Der gewählte Weg, der Deflator, die
  Nichtentscheidung zu Reihe 3 und die Aussage zu T47/T48/T50 werden nicht angefasst. Wer
  beim Nachrechnen zu einem anderen Ergebnis kommt, **meldet das und ändert es nicht.**
- **Kein Abruf einer fünften Quelle.** Die beiden Weltbank-Endpunkte genügen:
  `https://api.worldbank.org/v2/country/WLD/indicator/NE.EXP.GNFS.CD?format=json&date=1997:2021`
  und dieselbe Adresse mit `NE.EXP.GNFS.KD`.
- **Kein Übertrag nach `daten/reihen.toml`.** Der gehört dem Datenbauer und ist `0078`
  beziehungsweise dessen Folgepaket. Deine Datei ist `technik.md` und sonst keine.

## Zur Reihenfolge auf `technik.md`

Fünf Architektenpakete halten diese Datei: `0051` (T46 Gebietspräfix), `0064` (R-Nachzug),
`0074` (Maßnahme 43), `0068` (Reihe 9, hängt an 0064) und dieses. Dazu `0043`, das an 0002
hängt. Der Baulauf serialisiert sie; **welches zuerst läuft, entscheidet die Sortierung und
nicht ich.** Die Folge steht dir zu: Wer nicht als Erster läuft, misst seinen Vorher-Stand
am *dann* geltenden `HEAD`. Deine Bedingungen sind deshalb alle je Stelle formuliert und
keine gegen eine Summe — dadurch trägst du in jeder Reihenfolge.

**Was du nicht tust, wenn du eine fremde Baustelle vorfindest:** sie aufräumen. Findest du
in T53 oder Abschnitt 17 einen Widerspruch, der nicht in deiner Abnahme steht, meldest du
ihn in deinem Ergebnis. Das ist die Regel, an der 0026 sich gehalten hat, und sie hat dort
funktioniert.
