# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-03, nach dem Baulauf der Nacht. Fassung 14, geschrieben vom Projektmanager.
Diese Datei sagt, welche Pakete es gibt, warum in dieser Reihenfolge, und was der
Geschäftsführer entscheiden lassen muss.

**Dieser Lauf ist das Gegenteil des letzten.** Zwischen 15:20 und dem letzten Lauf hatte
kein Bau- oder Prüfagent gearbeitet; seitdem haben sieben geliefert. Es lagen **vier
Prüfbefunde** nach und **drei Vorschläge** zur Sichtung an. Beides ist abgearbeitet, die
Vorschlagsliste ist leer.

## Was dieser Lauf getan hat

**Drei Abnahmen.** 0031 (Warnsatz in die Werkzeugkette), 0032 (reihen.toml Notenbanken)
und 0033 (Schritt-Rundengerüst) stehen auf `fertig`, jedes mit `urteil: geprueft`. Alle
drei Befunde tragen je einen **Nebenbefund**, keiner davon ist ein Rücklaufgrund — sie
nachträglich in die Abnahme zu ziehen hiesse, ein bestandenes Kriterium anzuheben. Zwei
der drei sind stattdessen als eigenes Paket weitergeführt (0045, 0046), der dritte
brauchte keines: Er sagt, dass die Arbeit von 0033 in einem Commit mit dem Betreff von
0027 liegt — eine Feststellung zur Buchführung, nicht zur Sache.

**Ein Rücklauf, und es ist der teuerste.** 0011 steht wieder auf `offen`.

**Ein Übergang, den ich selbst getragen habe.** 0029 steht auf `gebaut`. Dazu unten.

**Drei Vorschläge, drei Annahmen.** Keiner war abzulehnen, keiner zusammenzufassen. Einer
war doppelt nummeriert, einer verlangte einen Nachweis, den sein Bauagent nicht führen
kann, und einer hatte eine Kollision übersehen, die der Scheduler nicht sieht.

## Der Rücklauf zu 0011 — die Kette bewegt sich nicht, aber sie ist kürzer geworden

`urteil: zurueck`, drei Befunde, Runde 1. **Alle drei sitzen in `technik.md`**, der
einzigen Datei in der `dateien`-Liste des Pakets, und sind laut Prüfer zusammen in einem
Lauf zu schliessen: ein Satz in T7 Massnahme 4.2, ein Satz in T1 oder T3, ein Satz in T2
oder T13.

Der schwerste ist der erste, und er ist kein Formfehler: Die Aufzählung der überlauf\-
gesicherten Operationen lässt die **blanke Multiplikation zweier `i64`** aus. Unter
`-fwrapv` bricht die still um, und der Weg von dort ins Fondsvermögen ist im Dokument
selbst nachgezeichnet (`tsd_in_cent` → `positionswert` → T47). Das ist genau die Sorte
Fehler, gegen die dieses Vorhaben gebaut ist: eine plausibel aussehende falsche Zahl, die
kein Test rot macht.

**Der Prüfer hat ausdrücklich kein Paket vorgeschlagen, und das war richtig.** Drei eigene
Kennungen würden sich mit 0011 auf `technik.md` schneiden. Der ganze Befund steht
stattdessen im Paket, samt der Liste dessen, was **nicht** anzufassen ist — die Neufassung
ist zum grössten Teil in Ordnung, und eine siebte Rundumerneuerung von `technik.md` ist
seit jeher verboten.

Was das für die Kette **0011 → 0026 → 0002 → 0010** heisst: Sie wartet eine Runde länger.
Aber sie wartet jetzt auf einen Bauagenten, nicht auf einen Prüfer — und 0011 ist der
erste Eintrag im Bauplan der nächsten Nacht.

## 0029 — geliefert, konnte es nicht melden

`pruefstand/src/vorrat_verfahren.cpp` (9.407 Byte) und
`pruefstand/test/vorrat_verfahren_probe.cpp` (31.138 Byte) tragen beide absichtlich
falschen Fassungen aus Bedingung 3 namentlich, und der Übersetzungsbericht des Tages führt
`vorrat_verfahren_probe` in **beiden** Bauwegen als `Passed`. Das Paket stand trotzdem auf
`offen` und hätte in dieser Nacht einen Bauplatz für Arbeit belegt, die es schon gibt.

Grund ist der bekannte: `architekt`, `spielentwerfer` und `testentwickler` fehlt in ihrer
Rollendatei der Satz „Setze `status: gebaut`". **Fünfter Fall, den ich von Hand trage.**
Ich habe hingeschrieben, was ich gemessen habe und was nicht — über die fünf Bedingungen
urteilt der `test-pruefer`, nicht ich.

**Gegenprobe für die anderen zwei derselben Bauart, damit dies keine Vermutung bleibt:**
0040 hat seine Zieldatei überhaupt nicht (`vorrat_kernanker_probe.cpp` existiert nicht),
0039 nennt seinen eigenen zentralen Begriff („Konjunktursockel") null mal in `spiel.md`.
Beide Läufe waren wirklich leer, beide bleiben `offen`. Gemessen wurde an der Zieldatei,
nicht am Commit-Betreff — die Betreffzeilen dieser Nacht tragen nachweislich fremde Arbeit.

## Die drei Vorschläge

| | Rolle | Entscheidung |
|---|---|---|
| 0044 Schranken-Probe Belegstellen | testentwickler | `offen`, `haengt_an` ergänzt |
| 0045 Zwischenstände aus `daten/` räumen | datenbauer | `offen`, unverändert |
| 0046 Warnsatzriegel für künftige Mitglieder | kernbauer | `offen`, umnummeriert, Bedingung 1 berichtigt |

**0044 hatte eine Kollision übersehen, und zwar die unsichtbare Sorte.** Es beansprucht
`kern/test/schranken_probe.cpp` und schreibt richtig, dass die Datei in keiner
`dateien`-Liste von 0035 steht — aber sie steht in der von **0027**, und 0027 ist `gebaut`,
nicht `fertig`. Der Kollisionsschutz des Baulaufs vergleicht `dateien` nur unter `offen`;
ein Paket auf `gebaut` hält seine Dateien faktisch, für den Scheduler aber unsichtbar.
Ohne den Nachtrag hätten 0044 und ein Rücklauf von 0027 dieselbe Datei überschrieben.

**0046 war doppelt nummeriert.** Zwei Prüfer haben im Abstand von einer Minute je einen
Vorschlag als `0045` angelegt (19:33 `daten-pruefer`, 19:34 `kern-pruefer`) und konnten die
Nummer des anderen nicht sehen — dieselbe Ursache wie bei 0039/0040 vorige Woche. Der
frühere behält die Nummer. Kein `haengt_an` und kein Bericht verwies auf den alten Namen;
mit `grep` über alle Pakete und `ops/plan.md` nachgeprüft, alter Name steht im Paket.

**0046 verlangte ausserdem einen Nachweis, den sein Bauagent vielleicht nicht führen kann.**
Bedingung 1 wollte ein Wegwerf-Verzeichnis „ausserhalb des Repos". Am selben Tag in beide
Richtungen gemessen: Der Prüfer von 0011 konnte dort nichts anlegen („Permission … denied")
und musste seine Übersetzungsprobe ausfallen lassen; der Prüfer von 0033 hat einen Bau
ausserhalb des Repos ausgeführt. Es hängt am Modus des Laufs. Die Bedingung ist deshalb
**inhaltlich unverändert**, aber der Ort ist gestaffelt — `$TMPDIR`, sonst ein Ort im Repo
ausserhalb jedes `file(GLOB …)`-Kastens und ausserhalb `bau/`, sonst eine **ausgewiesene
Nichtmessung**. Eine Nichtmessung, die als solche dasteht, ist richtig; eine behauptete
Messung wäre falsch.

## Gemessen, nicht angenommen

| | vorher | nachher |
|---|---|---|
| vorschlag | 3 | **0** |
| offen | 10 | 13 |
| gebaut | 7 | 4 |
| fertig | 24 | **27** |
| blockiert | 2 | 2 |
| Bauplätze belegt | 3 | **4 von 4** |
| Prüfplätze belegt | 4 von 4 | 4 von 4 |

46 Paketdateien vorher wie nachher; die Kopfzeile des Trockenlaufs geht auf. **Der
Prüfstau, den der Bericht von 15:10 als Kapazitätsengpass gemeldet hatte, war zur Hälfte
mein nicht eingetragener Nachzug** — von sieben `gebaut` hatten drei ihr Urteil bereits.
Nach dem Eintragen sind vier Prüfplätze mit vier neuen Paketen belegt, und kein Bauplatz
steht leer.

## Der Rückstand

**Im Bau (4):** 0011 Stack auf C++ (architekt, **Vorrang 1**), 0036 reihen.toml
BACI-Einheit (datenbauer), 0038 Meldung mit Adresse (kernbauer), 0039 Zollzeile
Konjunktursockel (spielentwerfer).

**Im Review (4):** 0027 Zustand-Schreibweg (kern-pruefer), 0029 Vorratsverfahren-Invariante
(test-pruefer), 0034 Belegstellen ohne Zeilennummern (daten-pruefer), 0035
Parameterdatei-Belegstellen (daten-pruefer).

**Startbereit in Reserve (3):** 0040 Kernanker Klassenzuteilung (testentwickler), 0045
Zwischenstände räumen (datenbauer), 0046 Warnsatzriegel (kernbauer). Sieben startbereite
Pakete auf vier Plätze — kein Bauagent läuft leer, auch wenn 0011 wieder zurückkommt.

**Wartend auf ein laufendes Paket (6):** 0026 (an 0011), 0002 (an 0026), 0010 (an 0002),
0042 (an 0035), 0043 (an 0011 und 0039), 0044 (an 0035 und 0027).

**Blockiert (2):** 0003 (Einheiten im Typ, braucht einen ADR gegen T5), 0041
(`baulauf.py`, keine zuständige Rolle). Unverändert beide zu Recht: Für keines gibt es ein
Paket, auf das es hängen könnte.

## Zum Vorrang des Geschäftsführers

Seine fünf Kennungen waren 0011, 0026, 0019, 0028, 0034. **Ich bin ihm gefolgt, und die
Liste hat sich dabei zum grössten Teil von selbst erledigt:** 0019 und 0028 waren schon
`fertig`, 0034 steht im Review, 0011 ist mit dem Rücklauf der erste Eintrag im Bauplan.
0026 wartet unverändert auf 0011 — das ist keine Abweichung, sondern der Inhalt seines
Punktes 2.

**Keine Abweichung zu begründen.** Die drei Vorschläge, die ich zusätzlich angenommen habe,
stehen in Reserve hinter seiner Reihenfolge und verdrängen keinen seiner Punkte.

## Was der Geschäftsführer entscheiden lassen muss

1. **Die Rohdaten — und die Frist ist jetzt bezifferbar.** `daten/` enthält weiter keine
   Datenzeile. Von den Datenbaupaketen arbeiten 0036, 0042, 0044 und 0045 an Belegstellen,
   Begründungen und Aufräumarbeiten in Textdateien. **Danach hat der Datenbauer ohne
   geladene Quellen nichts mehr zu tun** — das ist unverändert Empfehlung B (der Betreiber
   lädt die vier Quellen einmal von Hand).
2. **0041 braucht eine Hand.** Eine Zeile in `agents/baulauf.py`, Neustart des Tageslaufs,
   dazu ein `rm -rf` auf `pruefstand/bau/pruefung-0019/`. Wortlaut im Paket. Unverändert
   seit vier Plänen, und keine der 46 Aufgaben darf `agents/` schreiben.
3. **Die Prüfplätze nicht erhöhen.** Diesmal mit Beleg statt mit einer Prognose: Der
   gemeldete Engpass war zur Hälfte ein Buchführungsfehler von mir. Vier Prüfplätze haben
   in einer Nacht vier Urteile geliefert. *Die Zahl im Runner zu erhöhen hätte Geld
   gekostet und den Stau nicht behoben.*

**Klein gehalten, weil nicht fällig:** Den drei Rollendateien `architekt`, `spielentwerfer`
und `testentwickler` fehlt weiter der Satz „Setze `status: gebaut`". Diesmal ist er
aufgetreten (0029) und hat mich einen Handgriff gekostet, nicht einen Bauplatz.

## Die eine Zahl

**Acht von neun Kernkästen tragen Code; `werte` fehlt weiter (78 Byte).** Die Kette dorthin
ist unverändert vier Glieder lang — 0011 → 0026 → 0002 → 0010 —, aber ihr erstes Glied hat
diese Nacht zum ersten Mal ein Urteil bekommen, und das Urteil nennt drei Sätze, die es
schliessen.

Eine Spielrunde ist noch immer nie gerechnet worden. Der Nachweis dafür bleibt derselbe
und kann von keinem Agenten erfunden werden: 175 Ursachensätze und eine
FNV-1a-64-Prüfsumme, die sich nicht bewegt hat.
