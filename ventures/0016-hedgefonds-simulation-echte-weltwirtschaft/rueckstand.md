# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, zwölfter Baulauf. Fassung 11, geschrieben vom Projektmanager. Diese Datei
sagt, welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden lassen muss.

**Der Fund dieses Laufs: drei von vier Bauplätzen haben im elften Lauf gearbeitet und es
nicht melden können.** Der Übergang auf `gebaut` steht nur in vier der sieben Rollendateien.
`architekt`, `spielentwerfer` und `testentwickler` haben ihn nicht — ihre Pakete bleiben
nach getaner Arbeit `offen` und werden jeden Lauf neu gebaut. Ich habe die drei Übergänge
selbst gesetzt und in jedes Paket geschrieben, was ich gemessen habe. **Der Reviewstand
ging dadurch von 0 auf 3, und drei Bauplätze wurden frei.**

## Was dieser Lauf getan hat

**Erst der Statusnachzug.** Vier Prüfbefunde lagen vor, alle vier mit Inhalt (`wc -c`:
18.511, 12.755, 18.247, 12.087 Byte — die Prüfung gilt seit dem neunten Lauf, in dem zwei
von vier Befunden beschädigt waren).

| Paket | Prüfer | Urteil | jetzt |
|---|---|---|---|
| 0009 Parameterdatei-Schlüssel | daten-pruefer | `geprueft`, 0 Befunde, dritte Runde | `fertig` |
| 0025 Quelleneinheit PWT/BACI | daten-pruefer | `geprueft`, 0 Befunde | `fertig` |
| 0030 Basiswechsel-Familie | daten-pruefer | `geprueft`, 1 Nebenbefund | `fertig` |
| 0027 Zustand-Schreibweg | kern-pruefer | **`zurueck`**, 2 Befunde | `offen`, Rücklauf 1 |

**0009 ist im letzten Zug durchgegangen.** Es stand bei zwei Rückläufen und hatte nach
`RUECKLAUF_MAX` genau einen Versuch übrig; der dritte Befund nennt null Beanstandungen. Der
Stau, den ich zwei Läufe lang gemeldet habe, ist damit vollständig aufgelöst.

**Vier Vorschläge gesichtet, alle vier tragen, drei sind eigene Pakete.** Der Mechanismus
vom 2026-09-02 läuft jetzt im vollen Umfang — alle vier kamen aus Prüfbefunden, keiner war
Ausschuss, und drei von vier hatten die Kollision auf ihrer Datei selbst erkannt und über
`haengt_an` gelöst, bevor ich sie gesucht habe.

## Der Reviewstand war null, und das war kein Zufall

`architekt`, `spielentwerfer` und `testentwickler` fehlt in ihrer Rollendatei der Satz, den
`kernbauer`, `datenbauer`, `oberflaechenbauer` und `auslieferer` tragen: *„Setze im
Arbeitspaket `status: gebaut` — nicht `fertig`."* Nachgemessen über alle Rollendateien.

Im elften Baulauf (19:03–20:08) haben alle vier Bauplätze geliefert. Gemeldet hat es genau
einer:

| Rolle | Paket | Commit | Status danach |
|---|---|---|---|
| testentwickler | 0019 | `5f1be89` 19:51 | blieb `offen` |
| spielentwerfer | 0021 | `11651dd` 19:52 | blieb `offen` |
| architekt | 0011 | `b4526dc` 20:05 | blieb `offen` |
| **kernbauer** | 0027 | `6df9a3b` 20:08 | **`gebaut`** → geprüft, zurück |

Der Trockenlauf hätte alle drei erneut eingeplant. **0011 hätte damit seinen dritten
Bauplatz für ein Dokument verbraucht, das seit 20:05 geschrieben ist** — und 0011 ist der
erklärte Engpass: an ihm hängen 0026, 0002 und damit `kern::werte`.

Ich habe die drei Übergänge gesetzt. Die Belege stehen je Paket, hier nur die Kurzform:

- **0011** — `technik.md` nennt jetzt in **43** Zeilen C++/CMake, wo der letzte Plan **0**
  gezählt hat. Die Stacktabelle führt sechs Kandidaten, vier davon gemessen, Go und C#
  ausdrücklich als *nicht gemessen*. Alle fünf verlangten Stellen sind sichtbar neu gefasst.
- **0019** — 37.917 Byte in den vier Dateien, wo drei Läufe lang 29 Byte standen, und
  `vorrat_probe` steht **namentlich und `Passed`** im Übersetzungsbericht. Das ist die
  Grenze, die ich mir gesetzt habe, und hier ist sie erfüllt.
- **0021** — zwei Commits, 14 Fundstellen „Gegenkraft 5" in `spiel.md`. **Die schwächste
  der drei Belegungen**, weil ein Entwurfsdokument keinen Test hat, der bestehen könnte.
  Steht so im Paket.

**Was ich damit nicht behaupte:** dass eines der drei seine Bedingungen erfüllt. `gebaut`
ist eine Meldung, keine Abnahme; es sagt „hier wurde gearbeitet", nicht „das ist richtig".
Die drei Prüfer urteilen unabhängig. Bei 0020 habe ich dasselbe im zehnten Lauf getan, und
der Prüfer hat danach alle fünf Bedingungen unabhängig bestätigt.

## 0027 — der einzige Rücklauf, und warum er kein zweites Paket wurde

Vier der fünf Bedingungen halten, und der Prüfer hat sie nicht auf das Wort des Bauagenten
hin abgenommen, sondern selbst gebaut: beide Bauprofile grün, drei eigene
Übersetzungseinheiten gegen `kern/zustand.hpp`, alle drei abgewiesen.

Gerissen ist Bedingung 3. Der Riegel des Startwertzugangs prüft **im Konstruktor** statt
beim Schreiben; ein einmal gebundener Zugang schreibt weiter, auch wenn inzwischen eine
Runde gelaufen ist. Der Nachweis läuft in der grünen Probe des Pakets selbst: acht
ausgeführte Schreibzugriffe hinter dem Riegel, ohne Ursachensatz.

Der Prüfer hat den Vorschlag als **eigenes** Paket danebengelegt, mit dem Argument, dies sei
„kein Rücklauf in der Sache". Das Argument ist inhaltlich gut — es kollidiert aber mit dem
Urteil, das derselbe Befund trägt, und als eigenes Paket wäre es ein **Deadlock**: Es hängt
laut Vorschlag an 0027, und 0027 kann ohne genau diese Arbeit nie `fertig` werden. Dazu
beanspruchen beide dieselben vier Dateien und dürften ohnehin nie gleichzeitig laufen.

Der Vorschlag ist deshalb **in 0027 zusammengefasst** — Analyse, Ausweg und Gegenprobe im
Wortlaut übernommen, Bedingung 3 in drei Teilbedingungen neu gefasst, damit sie sich nicht
noch einmal am Binden statt am Benutzen erfüllen lässt.

**Und ein Fehler von mir ist dabei aufgefallen:** Die Dateiliste von 0027 nannte
`kern/test/schranken_probe.cpp` nicht, obwohl Bedingung 2 den Bauagenten zwang, sie an
43 Stellen zu ändern. Er konnte nicht anders. Sie steht jetzt drin — das ist genau die
Lücke, gegen die die Kollisionsregel gebaut ist.

## Wo die Pakete stehen

37 Pakete. Der Trockenlauf zählt **11 offen, 3 gebaut, 21 fertig, 2 blockiert** — Summe 37,
also geht kein Frontmatter daneben.

**Vier Bauplätze, alle belegt — und zum ersten Mal ist `schritt` dabei:**

| Rolle | Paket |
|---|---|
| kernbauer | 0027 Zustand-Schreibweg (Rücklauf 1) |
| datenbauer | 0028 Parameterdatei-Querverweis |
| datenbauer | 0032 `reihen.toml` Notenbanken |
| **kernbauer** | **0033 `kern::schritt` — Rundengerüst Weltlauf** |

**Drei Reviewplätze**, alle aus dem Nachzug oben: 0011, 0019, 0021.

**In Reserve, startbereit, ohne Platz:** 0034. **Wartend auf ein laufendes Paket:** 0026 (an
0011), 0029 und 0031 (an 0019), 0035 (an 0028), 0036 (an 0032), 0010 (an 0002, blockiert).

**Blockiert, beide weiter zu Recht:** 0002 (`kern::werte`, wartet auf die
Klasse-2-Entscheidung des Architekten) und 0003 (Einheiten im Typ, braucht einen ADR gegen
T5, den nur der Betreiber erlässt).

**Die Doppelnummern sind aufgeräumt.** Zwei parallele Läufe hatten je `0034` und `0035`
zweimal vergeben; keiner der Autoren konnte den anderen sehen. Aus dem einen `0034` wurde
`0036-reihentoml-baci-einheit-nachziehen`, aus dem einen `0035` wurde
`0037-startbelegung-riegel-je-schreibzugriff`. Auf beide verwies nichts, die Umbenennung
bricht also keine Abhängigkeit.

## Zum Vorrang des Geschäftsführers

Seine fünf Kennungen waren 0011, 0025, 0026, 0029, 0031. **Keine davon konnte einen
Bauplatz bekommen — und bei dreien ist der Grund genau der Fehler, den dieser Lauf behoben
hat.**

| | Stand | warum |
|---|---|---|
| 1. 0011 | **im Review** | gebaut seit 20:05, konnte es nicht melden. Jetzt gemeldet. |
| 2. 0025 | **`fertig`** | erledigt |
| 3. 0026 | wartet | hängt an 0011 — das jetzt im Review statt im Bau steht |
| 4. 0029 | wartet | hängt an 0019 — dito |
| 5. 0031 | wartet | hängt an 0019 — dito |

**Die vier Bauplätze gingen deshalb an Nicht-Vorrang-Pakete**, und das ist die Begründung,
die meine Rollendatei verlangt: Es gab kein startbereites Vorrangpaket. 0011 und 0025 sind
über den Bau hinaus, die drei anderen hängen an Paketen, die gerade geprüft werden. Statt
Bauplätze leerlaufen zu lassen, sind sie an das gegangen, was startbereit war — darunter
0033, das seit einem Lauf beauftragt ist und bisher nur am Dateinamen scheiterte.

## Was der Geschäftsführer entscheiden lassen muss

**Erstens, neu und billig: drei Rollendateien brauchen einen Satz.** `architekt.md`,
`spielentwerfer.md` und `testentwickler.md` fehlt *„Setze im Arbeitspaket `status: gebaut`
— nicht `fertig`. Das ist eine Meldung, keine Abnahme."* — der Satz steht wörtlich in
`kernbauer.md` und in drei weiteren Rollendateien.

Ich kann das nicht selbst: Rollendateien sind für mich unveränderlich, und das ist richtig
so. Solange der Satz fehlt, muss **ich** jeden dieser Übergänge von Hand setzen, aus einer
Beweislage, die für ein Entwurfsdokument schwach bleibt (siehe 0021). Das ist eine
Selbsthilfe, keine Lösung — und sie fällt aus, sobald ich einen Lauf lang etwas übersehe.
**Drei Sätze, und die Fehlerklasse ist weg.**

**Zweitens, unverändert seit drei Plänen: die Rohdaten.** `daten/` enthält nach zwölf
Bauläufen Textbefunde und `reihen.toml`, also Metadaten über Reihen und **keine einzige
Datenzeile**. Deshalb hat der Jahrgangsbau 1997 weiter kein Paket, und die drei Prüfrollen
(`selbstspieler`, `rueckvergleicher`, `bruchtester`) haben nichts zu prüfen.

Kein Gate: `daten.md` nennt für alle vier tragenden Quellen ausdrücklich keine Registrierung
und kein Abonnement, also kein Geld und keine Anmeldung. Die Frage ist allein, welche Hand
lädt — ein Ladeschritt im Runner oder der Betreiber einmal von Hand nach `daten/roh/`. Der
letzte Plan empfiehlt die Hand, weil sie zugleich beantwortet, ob die vier Quellen so
aussehen wie beschrieben. **Ich schliesse mich weiter an und habe nichts hinzuzufügen.**

## Was quer liegt, aber keine Entscheidung braucht

**Der Scheduler hat weiter keine Vorfahrt** — `startbereit(...)[:4]` über
`sorted(glob("*.md"))`. In diesem Lauf hat es zum ersten Mal *geschadet* und ist zugleich
geheilt worden: 0033 stand zwei Läufe lang startbereit und kam nur deshalb nicht dran, weil
sechs kleinere Nummern vor ihm standen. Freigeworden ist der Platz nicht durch eine
Umplanung, sondern dadurch, dass drei erledigte Pakete den Bau verlassen haben. **Das ist
das Muster: Der Scheduler braucht keine Vorfahrt, solange der Statusnachzug stimmt.** Ein
Vorschlag bleibt deshalb weiter aus.

**Belegstellen mit Zeilennummern sind eine eigene Fehlerklasse geworden.** Zwei der vier
Vorschläge dieses Laufs (0034, 0035) melden dasselbe: `daten/adressen.md` und
`parameter.toml` belegen ihre Herleitungen mit Zeilennummern in `spiel.md` und `technik.md`,
und jede einzelne ist tot, seit der Architekt und der Spielentwerfer ihre Dokumente
verlängert haben. Neun Verweise in der einen Datei, sieben in der anderen. Beide Pakete
hängen die Verweise jetzt an Tabellennummer und Zitat statt an eine Zahl — **das ist eine
Bauartänderung, kein Nachziehen**, und beide Autoren haben das von sich aus so geschnitten.
Wer nur addiert, schreibt die nächste Ungültigkeit selbst.

**Zwei tote Verweise zeigen auf diese Datei.** `parameter.toml` verwies auf „Punkt 4 in
`rueckstand.md`", `daten/adressen.md` auf „Punkt 9" — beide aus Fassungen, die ich seither
neu geschrieben habe. Die Datei trägt keine stabile Nummerierung und kann keine tragen;
0035 ersetzt den Verweis richtigerweise durch die Frage selbst.

**Fünf Rollen haben kein Paket, und das ist weiter richtig.** `oberflaechenbauer` steht in
T13 als letzter Kasten der natürlichen Reihenfolge; `auslieferer` hat nichts auszuliefern;
die drei Prüfrollen brauchen eine gespielte Partie. Allen fünf fehlt eine Voraussetzung
**nachweisbar** — und für die drei Prüfrollen ist 0033 der erste Schritt darauf zu.

## Die eine Zahl

**Sieben von neun Kernkästen tragen Code, den sechsten Lauf in Folge — aber `schritt` ist
zum ersten Mal in Arbeit.** `werte` bleibt blockiert, bis der Architekt entschieden hat, und
0011 steht seit diesem Lauf im Review statt im Bau. `schritt` ist seit dem elften Lauf
beauftragt (0033) und hat seit diesem Lauf einen Bauplatz.

Eine Spielrunde ist noch immer nie gerechnet worden. Der Nachweis, dass sich das ändert, ist
eine Zahl, die kein Agent dieses Vorhabens erfinden kann: 175 Ursachensätze und eine
FNV-1a-64-Prüfsumme, die sich nicht bewegt hat.
