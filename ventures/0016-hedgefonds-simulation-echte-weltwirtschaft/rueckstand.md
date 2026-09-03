# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-03, spätabends. Fassung 16, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer entscheiden
lassen muss.

**Ein kurzer Lauf mit einem klaren Ergebnis.** Drei Prüfbefunde, alle drei `geprueft`, alle
drei in Runde 1 und keiner mit einem Rücklauf. Dazu eine Lieferung ohne Meldung, zwei
Vorschläge mit derselben Kennung und ein Paket, das aus einem Nebenbefund entsteht. Der
Rückstand wächst um drei Pakete und verliert keines.

## Was dieser Lauf getan hat

**Drei Abnahmen.** 0039 (Zollzeile Konjunktursockel), 0042 (Parameterdatei
Indexbegründung) und 0045 (Zwischenstände räumen) stehen auf `fertig`, jedes mit
`urteil: geprueft`, jedes in Runde 1. Zwei der drei Befunde tragen einen Nebenbefund, und
beide sind ausdrücklich an mich adressiert, nicht an den Bauagenten.

**Ein Übergang, den ich selbst getragen habe.** 0040 hat geliefert und konnte es nicht
melden. Achter Fall derselben Sorte.

**Zwei Vorschläge, zwei Annahmen, einer umnummeriert.** Beide waren sachlich richtig.

**Ein neues Paket aus einem Nebenbefund,** 0055, weil eine Tabelle, die als Regressionsfall
gebaut ist, zwei Zahlen zu einem Zustand führt.

## Die zwei Nebenbefunde gehören mir, nicht den Bauagenten

Das ist der Inhalt dieses Laufs, und es ist zweimal derselbe Fehler.

**0042.** Der Satz, den der Prüfer widerlegt, stand in *Was zu tun ist*, Punkt 2 **wörtlich
vorgeschrieben**. Der Bauagent hat geliefert, was mein Auftrag verlangte, und hätte den
Fehler innerhalb seines Pakets gar nicht abstellen können, ohne von seinem Auftrag
abzuweichen. Ein Rücklauf hätte keine bessere Datei erzeugt, sondern eine zweite Runde
desselben Satzes. Der Prüfer schreibt das selbst hin und urteilt trotzdem `geprueft` — genau
richtig.

**Und es ist die zweite Stufe derselben Kette.** 0042 ist aus einem wörtlich
vorgeschriebenen Halbsatz der Prüfung zu 0028 entstanden; dieser Halbsatz ist jetzt wieder
einer geworden. Die Regel dagegen steht ab heute in meinem Logbuch und im Nachfolgepaket:
**An einer Stelle, die eine Begründung formuliert, schreibe ich die Prüfbedingung vor und
nicht den Wortlaut.** Der Vorschlagende hat das von sich aus so gebaut („Der Wortlaut ist
deine Entscheidung, nicht die dieses Auftrags"); ich habe nichts daran geändert.

**0039.** Hier liegt der Fehler nicht in meiner Vorgabe, sondern in der gebauten Datei — die
Vergleichszahl 32.850.000 ist richtig gerechnet und falsch beschriftet. Der Prüfer stuft ihn
als „Schwere: gering, kein Rücklaufgrund" ein, weil er keine der drei Abnahmebedingungen
berührt. **Das `urteil` im Frontmatter entscheidet, nicht der Fließtext:** Ein Nebenbefund
bei `geprueft` hebt kein bestandenes Kriterium an. Er wird deshalb gebaut, aber als eigenes
Paket 0055 und nicht als Rücklauf.

**Ich habe den Widerspruch selbst nachgemessen, statt ihn zu übernehmen.** Die Tabelle
*Zwei Zustände, zwei Zahlen* gibt Zustand B ein Handelsvolumen von 40.000.000 / 100.000.000,
zusammen 1,4·10^8; der Vergleichssatz drei Absätze darunter rechnet mit 1,5·10^9. Zehneinhalb
mal so groß, beide Stellen im selben Abschnitt. Der Befund trägt.

## 0040 — geliefert, konnte es nicht melden

Achter Fall: `architekt`, `spielentwerfer` und `testentwickler` fehlt in ihrer Rollendatei
der Satz „Setze `status: gebaut`", den die vier anderen Baurollen tragen. Das Paket wäre
`offen` geblieben und hätte in der nächsten Nacht einen Bauplatz für Arbeit belegt, die
getan ist — und hätte kein Urteil bekommen, denn der Prüfplatz hängt an `gebaut`.

**Gemessen an der Zieldatei, nicht am Statusfeld.** `pruefstand/test/vorrat_kernanker_probe.cpp`
existiert mit 467 Zeilen, trägt 14-mal paketeigene Bezeichner, und
`befunde/uebersetzung-2026-09-03.md` führt `vorrat_kernanker_probe` **namentlich** als
`Passed` (Test 9 von 11). Das ist der strengere der beiden Wege — bei Code setze ich `gebaut`
nur, wenn der Übersetzungsbericht die Probe namentlich als bestanden führt.

**Was der grüne Lauf nicht belegt**, und was deshalb im Paket steht: keine der vier
Abnahmebedingungen. Grün heißt „die Zahlen passen zueinander", nicht „sie sind richtig".
Ob die Anker Festwerte sind und nicht Rechenergebnisse, prüft der `test-pruefer`.

## Die zwei Vorschläge

| | Rolle | Entscheidung |
|---|---|---|
| 0053 Indexbegründung Regulierungsfall | datenbauer | `offen`, Kennung behalten |
| 0054 Partielänge R entscheiden (war 0053) | spielentwerfer | `offen`, umnummeriert |

**Die doppelte `0053` ist aufgelöst.** Vierter Fall an einem Tag; sie entstehen aus
parallelen Läufen und sind normal. Diesmal war **beides** zitiert — jeder Vorschlag steht
namentlich in dem Befund, aus dem er stammt —, also entschied die Commitzeit: `f2a9893`
(21:20) gegen `e3fa560` (21:23), drei Minuten. Kein `haengt_an` und keine Zeile in
`ops/plan.md` nennt eine 0053; der Suchlauf über das Repo ergab genau sechs Fundstellen, die
beiden Paketköpfe, die beiden Befunde und zwei Logbucheinträge. Der Umzug reißt nichts auf.
Alter Name steht im Paket.

**0054 und 0055 wollen dieselbe Datei, und ich habe sie nicht zusammengelegt.** 0054
entscheidet die Partielänge, 0055 berichtigt eine Beschriftung in der Zollzeile — die beiden
haben sachlich nichts miteinander zu tun, und keiner verschiebt die Belegstellen des
anderen. 0055 hat 0054 in `haengt_an` und läuft dahinter. Zusammengelegt wären es sieben
Bedingungen in einem Lauf; das ist der Zuschnitt, an dem 0019 dreimal abgebrochen ist.

## Gemessen, nicht angenommen

| | vorher | nachher |
|---|---|---|
| vorschlag | 2 | **0** |
| offen | 12 | 14 |
| gebaut | 7 | 5 |
| fertig | 31 | **34** |
| blockiert | 2 | 2 |
| Bauplätze belegt | **3 von 4** | **4 von 4** |
| Prüfplätze belegt | 4 von 4 | 4 von 4 |

55 Paketdateien, und die Kopfzeile des Trockenlaufs geht auf (14 + 5 + 34 + 2 = 55).

**Der leere Bauplatz war der Kern dieses Laufs, und die Rechnung dazu ist knapp.** Beim
Aufschlagen waren drei Pakete startbereit, davon eines (0040) in Wahrheit schon gebaut — es
wäre also ein zweites Mal bezahlt worden und hätte nur zwei echte Plätze gefüllt. Die beiden
angenommenen Vorschläge sind beide **sofort** startbereit: 0053 hängt an 0042, 0054 an 0006,
beide seit heute bzw. seit dem 2026-09-02 `fertig`, und beide Dateilisten (`parameter.toml`,
`spiel.md`) schneiden weder ein `offen`- noch ein `gebaut`-Paket. Erst damit sind es vier.

**Diesmal ohne Reserve.** Genau vier Pakete sind startbereit, und wenn ein Bauagent
scheitert, bleibt der Platz leer. Ich habe keines künstlich nachgelegt: Alle neun wartenden
Pakete warten auf eine echte Abhängigkeit, und ein Paket zu erfinden, das nicht aus `specs/`
folgt, ist mir verboten. Der Weg zu Reserve führt über Abnahmen, nicht über Umsortieren —
zum fünften Mal derselbe Beleg.

**0027 fällt aus dem Review, und das kostet.** `reviewbereit()` sortiert nach der Zahl
bisheriger Urteile und schneidet bei vier ab (`baulauf.py:311`). Fünf Pakete stehen auf
`gebaut`; 0038, 0040 und 0046 haben null Rückläufe, 0011 und 0027 je einen, und bei
Gleichstand entscheidet die Kennung. 0027 ist damit das fünfte. **An ihm hängen 0044 und
0048** — es rückt in der übernächsten Nacht von selbst nach, sobald eines der vier ein
Urteil hat.

## Der Rückstand

**Im Bau (4):** 0047 reihen.toml Kopf/Widerspruch (datenbauer), 0050 Vorratsprobe
Belegstellen (testentwickler), 0053 Indexbegründung Regulierungsfall (datenbauer), 0054
Partielänge R entscheiden (spielentwerfer).

**Im Review (4):** 0038 Meldung mit Adresse (kern-pruefer), 0040 Kernanker-Klassenzuteilung
(test-pruefer), 0046 Warnsatzriegel (kern-pruefer), 0011 Stack auf C++ (entwurf-pruefer,
**Vorrang 1**).

**Startbereit in Reserve (0).** Siehe oben.

**Wartend auf ein laufendes Paket (10):** 0026 (an 0011), 0002 (an 0026), 0010 (an 0002),
0043 (an 0011), 0044 (an 0027), 0048 (an 0038 und 0027), 0049 (an 0047), 0051 (an 0011),
0052 (an 0011), 0055 (an 0054).

**Blockiert (2):** 0003 (Einheiten im Typ, braucht einen ADR gegen T5), 0041 (`baulauf.py`,
keine zuständige Rolle). Beide zu Recht: Für keines gibt es ein Paket, auf das es hängen
könnte.

**0043 ist heute ein Glied kürzer geworden.** Es hing an 0021, 0039 und 0011; mit der
Abnahme von 0039 wartet es nur noch auf 0011.

**Die Kette zu `werte` ist unverändert vier Glieder lang** — 0011 → 0026 → 0002 → 0010.
An 0011 hängen **fünf** Pakete (0026, 0043, 0051, 0052 und über 0026 auch 0002). Es ist die
einzige Kennung des Vorhabens, an der so viel hängt, und es steht zum zweiten Mal im Review.

## Zum Vorrang des Geschäftsführers

Seine fünf Kennungen waren 0011, 0026, 0019, 0028, 0034. **Vier davon sind erledigt** — 0019,
0028 und 0034 stehen auf `fertig`, 0011 steht im Review. **Keine Abweichung zu begründen:**
0026, sein Punkt 2, wartet unverändert auf 0011, und genau das sagt sein eigener Text. Von
seinen fünf ist keines startbereit, deshalb gehen die vier Bauplätze an Pakete, die er nicht
genannt hat.

**Die Vorrangliste ist damit abgearbeitet und für den nächsten Lauf leer.** Sie braucht eine
neue.

**Seine beiden Aufträge ohne Kennung sind erledigt.** Die doppelten Nummern sind aufgelöst,
und 0041 ist am heutigen Vormittag zum zweiten Mal an den Betreiber zurückgegeben worden —
mit einem eingetretenen statt einem erwarteten Schaden. Ein dritter Durchgang bringt nichts
Neues; die Sache liegt beim Betreiber.

## Was der Geschäftsführer entscheiden lassen muss

1. **Die Rohdaten, und die Frist ist abgelaufen.** `daten/` enthält weiter keine Datenzeile —
   sechs Dateien plus das neue Verzeichnis `zwischenstaende/`, davon fünf Befunde und ein
   Katalog. Nach 0047, 0049 und 0053 hat der Datenbauer ohne geladene Quellen **nichts mehr
   zu tun**; das sind drei Pakete, also etwa eine Nacht bei zwei Datenbauplätzen. Das ist
   eines weniger als in der letzten Fassung, weil 0042 und 0045 heute abgenommen wurden.
   Unverändert Empfehlung B: Der Betreiber lädt die vier Quellen einmal von Hand. **Das ist
   der Punkt, der als nächster einen Bauplatz leerlaufen lässt**, und er ist der einzige auf
   dieser Liste, der Geld oder Betreiberzeit kostet.
2. **Den drei Rollendateien fehlt der Satz „Setze `status: gebaut`".** Achter Fall, wieder
   von Hand getragen. Er kostet keinen Bauplatz mehr, seit ich ihn jeden Lauf prüfe — aber er
   kostet jeden Lauf diese Prüfung, und heute hätte er ohne sie einen der vier Bauplätze mit
   fertiger Arbeit belegt.
3. **Zwei Punktdateien liegen im Aufgabenverzeichnis:** `aufgaben/.kopf.tmp` und
   `aufgaben/.paket.tmp`. **Akuter Schaden null**, gemessen: `baulauf.py:215` liest
   `ordner.glob("*.md")`, die beiden werden nicht gelesen, und die Kopfzeile des Trockenlaufs
   zählt genau die 55 `.md`-Dateien. Löschen darf ich nicht (Hausregel 3). Ich melde sie, weil
   sie zur selben Familie gehören wie 0041 — Erzeugnis, das im Quellverzeichnis liegen
   bleibt.

## Die eine Zahl

**Acht von neun Kernkästen tragen Code; `werte.hpp` steht weiter bei 78 Byte**, und
`werte.cpp` gibt es nicht.

Eine Spielrunde ist noch immer nie gerechnet worden. Was sich in diesem Lauf bewegt hat, ist
nicht die Zahl und diesmal auch nicht der Weg zu ihr — 0011 steht seit dem Vorlauf im Review
und hat dort noch kein Urteil. Bewegt hat sich der **Entwurf**: Die Zollzeile misst seit
heute nur noch den Keil, und mit 0054 ist zum ersten Mal ein Paket offen, das die älteste
unbeantwortete Frage des Entwurfs beantwortet — wie lang eine Partie ist. Solange sie offen
ist, sind alle vier Maßvorschriften vorläufig und der Selbstspieler kann keine davon messen.
