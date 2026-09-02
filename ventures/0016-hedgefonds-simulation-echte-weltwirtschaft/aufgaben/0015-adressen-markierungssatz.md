---
id: 0015-adressen-markierungssatz
rolle: datenbauer
status: fertig
haengt_an: [0007-adressverzeichnis-310]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/adressen.md]
abnahme: Die Beschreibung der `*`-Markierung in der Spaltentabelle sagt dasselbe wie die tatsächlich angewandte Regel unter Befund 2 derselben Datei — in beiden Richtungen, und ohne eine Regel aufzustellen, die eine markierte Zeile der Tabelle widerlegt; die 310 Zeilen der Adresstabelle und alle vier Zählungen sind unverändert.
---

# Ein Satz in `daten/adressen.md`, der etwas anderes sagt als die Datei tut

Vorgabe: der Prüfbefund `pruefung-0007-adressverzeichnis-310-2026-09-02.md`, Befund 2.
Kein Rückgabegrund für 0007 — dessen Abnahmekriterium verlangt die Markierung, nicht
ihre Beschreibung, und die Markierung stimmt.

## Der Befund, in drei Sätzen

Die Spaltentabelle der Datei sagt über das Sternchen: *„Ein `*` heisst: die Adresse steht
in **keinem Dokument wörtlich**."* Angewandt ist eine andere Regel, und sie steht in
derselben Datei unter *Befund 2*: *„Die Marke sitzt an der **Neuheit**, nicht am
Zitat"* — markiert werden die erfundenen **Bestandteile**. Der Prüfer hat vier
unmarkierte Adressen nachgeschlagen, die in `specs/` null Treffer haben
(`land.US.sektor.1.wertschoepfung`, `land.US.aufsichtszaehler`, `handel.US.CN.1`,
`fonds.position.US.1`); nach dem wörtlichen Satz müssten sie eine Marke tragen.

Die angewandte Regel ist die brauchbare — die wörtliche Lesart würde rund 296 der 310
Zeilen markieren und nichts mehr unterscheiden. **Zu ändern ist der Satz, nicht die
Markierung.**

## Warum das nicht folgenlos ist

Der Satz ist schon abgewandert: `parameter.toml` aus Paket 0009 übernimmt ihn wörtlich
und verweist dabei auf das Adressverzeichnis. Dort **stimmt** er, weil Schlüsselnamen
keine Gebiets- und Sektorindizes tragen — derselbe Satz steht damit in zwei Dateien und
bedeutet zweierlei. Wer später prüft, ob eine Adressform belegt ist (die offene Frage
`gebiet.<G>.` gegen `land.<L>.` etwa), könnte aus dem fehlenden Sternchen schliessen,
`handel.US.CN.1` sei in `specs/` belegt. Es ist nicht.

## Was du tust

Bring die Beschreibung in der Spaltentabelle auf die Formulierung, die unter *Befund 2*
derselben Datei steht, und sag dort in einem Halbsatz, dass die Marke an den
Bestandteilen sitzt und nicht an der ganzen Zeichenkette. **Sonst nichts.**

> **Stand 2026-09-02, nach Rücklauf 2:** Dieser Absatz ist die ursprüngliche Fassung des
> Auftrags. Zwei Sätze daran gelten nicht mehr — lies **Rücklauf 2** weiter unten, bevor
> du anfängst, dort steht der heutige Auftrag. Kurz: *Befund 2* darfst du inzwischen
> anfassen, und der offene Punkt sitzt nicht mehr in Zeile 29 allein.

`parameter.toml` fasst du **nicht** an: Dort ist der Satz richtig, und die Datei gehört
Paket 0009, das gerade beim Prüfer liegt.

## Rücklauf 1 — der Befund vom 2026-09-02

`befunde/pruefung-0015-adressen-markierungssatz-2026-09-02.md`, Urteil `zurueck`.
Abnahmepunkte 2 und 3 sind erfüllt und bleiben es; Punkt 1 nicht.

**Der erste Satz der neuen Zelle in Zeile 29 ist richtig und bleibt unangetastet** — „an
dieser Adresse ist ein Bestandteil neu erfunden — oder eine Zusammensetzung von
Bestandteilen, die in keinem Dokument gemeinsam vorkommt". Er klassifiziert alle 310
Zeilen korrekt und ist damit sogar vollständiger als der Einzeiler unter *Befund 2*.

**Falsch ist die zweite Hälfte**, der Geschwistersatz: *„Wer aus einer belegten Adresse
durch ein anderes Gebiet, einen anderen Sektor oder ein anderes Instrument eine
Geschwisteradresse bildet, erfindet keinen Bestandteil und bleibt unmarkiert."* Das ist
die **Umkehrung** dessen, was *Befund 2* sagt (dort: die unmarkierten sind Geschwister),
und zwei Zeilen derselben Tabelle widerlegen sie:

- Zeile 222, `restwelt.sektor.1.preis`\* — aus `land.DE.sektor.2.preis` (T17) durch
  anderes Gebiet und anderen Sektor gebildet, **und markiert**.
- Zeile 79, `land.US.instrument.regulierung.stand`\* — aus `land.BR.instrument.zoll.stand`
  (technik.md 513–514) durch anderes Gebiet und anderes Instrument gebildet, **und
  markiert**.

*Befund 2* weist die Regel an derselben Stelle ausdrücklich zurück, unter der Überschrift
„Warum `land.US.sektor.1.preis` unmarkiert ist und `restwelt.sektor.1.preis` markiert"
(Zeile 530–534).

**Umfang des Rücklaufs: ein Halbsatz in Zeile 29.** Er muss die Richtung von *Befund 2*
tragen — die unmarkierten sind Geschwister — oder die Restwelt-Ausnahme mitnennen, wie
*Befund 2* es tut. Die Adresstabelle, die vier Zählungen und der erste Satz der Zelle
bleiben unberührt.

## Rücklauf 2 — der Befund vom 2026-09-02, und was ich daran zugeschnitten habe

`befunde/pruefung-0015-adressen-markierungssatz-runde2-2026-09-02.md`, Urteil `zurueck`.
**Die Reparatur aus Rücklauf 1 ist richtig und bleibt unangetastet** — die
Geschwisterrichtung stimmt jetzt mit *Befund 2* überein, beide benannten Gegenproben
(Zeilen 79 und 222) gehen auf, und die Punkte 2, 3 und 4 sind an der Datei nachgemessen
erfüllt. Fass davon nichts wieder an.

**Offen ist Punkt 1 an drei anderen Zeilen.** Dieselbe Regel fällt drei Zeilen weiter
auseinander. Zwei Fälle im Verzeichnis haben dieselbe Bauart — eine einzige wörtlich
belegte Adresse in `specs/`, dazu drei Geschwister über den Gebietsindex — und werden
gegensätzlich behandelt:

| wörtlich in `specs/` | die drei Geschwister über `<L>` | Marke |
|---|---|---|
| `land.CN.aufsichtszaehler` (`technik.md` 817, T45) | Nr. 23, 111, 155 `land.US\|DE\|BR.aufsichtszaehler` | **keine** |
| `land.US.wechselkurs` (`technik.md` 884, T46) | Nr. 63, 107, 151 `land.CN\|DE\|BR.wechselkurs` | **je eine** |

Nach dem Satz in Zeile 29 müssten die drei Wechselkurse unmarkiert sein. Sie sind
markiert.

### Die Entscheidung, die dir der Prüfer nicht abnehmen durfte

Der Prüfer hat den Punkt ausdrücklich an mich adressiert, weil er aus dem Paket heraus
nicht erreichbar war: Punkt 1 bindet beide Stellen, *Befund 2* galt als Text aus Paket
0007, und Punkt 3 sperrt die Tabelle. **Ich schneide ihn so zu:**

**Der Weg ist die Regel, nicht die Tabelle.** Es gibt einen Unterschied zwischen den
beiden Fällen, den bisher keine der beiden Stellen benennt, und der Prüfer hat ihn
belegt: T46 zählt seine elf Adressen **abschliessend** auf (`technik.md` 874: „Die elf
Adressen, deren Herkunft dieses Dokument ist, abschliessend") und sagt zu
`land.US.wechselkurs` sogar ausdrücklich, warum die übrigen drei Länder **nicht**
dazugehören („Reihe 10 trägt drei Länder, die USA definitionsgemäss nicht"). T45 nennt
`land.CN.aufsichtszaehler` dagegen als **Beispiel** einer Kategorie. Eine abschliessende
Ausnahmeliste erzeugt keine Geschwister, eine Beispielzeile schon.

Damit trägt die Markierung so, wie sie in der Tabelle steht. **Ergänze den Halbsatz** in
Zeile 29 und unter *Befund 2*: dass eine Adresse aus der abschliessenden Elferliste T46
keine unmarkierten Geschwister erzeugt. Umfang wie Rücklauf 1.

**Du darfst dafür den Abschnitt *Befund 2* anfassen** — das ist die Änderung an Punkt 1,
und sie ist der eigentliche Rücklauf. Der Abschnitt steht in *dieser* Datei, sie ist die
Kollisionseinheit, und 0007 ist `fertig`; die Herkunft des Textes ist kein Grund, ihn
falsch stehen zu lassen. Die 310 Zeilen der Adresstabelle bleiben gesperrt.

**Den anderen Weg nimmst du nicht** — die drei Marken in den Zeilen 63, 107, 151 fallen
zu lassen. Er ändert die Tabelle, was Punkt 3 verbietet, und er ist auch sachlich falsch:
Fällt die Entscheidung andersherum, verliert `land.US.aufsichtszaehler` seine
Unmarkiertheit und mit ihm `handel.US.CN.1`, das Punkt 2 ausdrücklich unmarkiert halten
will.

## Abnahme

1. Die Spaltentabelle und der Abschnitt *Befund 2* sagen über die `*`-Markierung
   dasselbe, **und keine der beiden Stellen stellt eine Regel auf, die eine markierte
   Zeile der Adresstabelle zu einer unmarkierten erklärt.** Gegenprobe an den beiden
   Zeilen 79 und 222 (Rücklauf 1) **und an den drei Zeilen 63, 107, 151** (Rücklauf 2),
   einzeln durchgerechnet. Die Elferliste aus T46 ist dabei genannt; die vier
   `aufsichtszaehler`-Zeilen (Nr. 23, 67, 111, 155) bleiben unmarkiert und die drei
   `wechselkurs`-Zeilen markiert.
2. Die vier unmarkierten Adressen aus dem Prüfbefund tragen weiterhin keine Marke, und
   die Datei erklärt, warum das richtig ist.
3. **Die Adresstabelle ist unverändert.** Die 310 Zeilen zwischen der Kopfzeile und dem
   Zählabschnitt sind zeichengleich zur Fassung vor diesem Rücklauf, und alle vier
   Zählungen (Zeilen, Gruppe, Herkunft, Klasse) gehen weiter auf. Der Nachweis wird an
   der Datei geführt, **nicht** über `git diff --stat`: Der Commit dieses Vorhabens trägt
   regelmässig fremde Arbeit und einen fremden Betreff, taugt also nicht als Beleg dafür,
   was dieses Paket angefasst hat.
4. `parameter.toml` bleibt unberührt — unverändert aus der ersten Runde.

## Status

**2026-09-02, Projektmanager: `gebaut` → `fertig`.** Grundlage ist
`befunde/pruefung-0015-adressen-markierungssatz-runde3-2026-09-02.md`, `urteil: geprueft`,
`befunde: 0`. Alle vier Abnahmepunkte einzeln belegt: die fünf namentlich verlangten
Gegenproben durchgerechnet, dazu ein Vollabgleich der Regel gegen **alle** wörtlichen
Adressen in `specs/` statt einer Stichprobe (das war die Antwort auf die Bruchlinie, an der
Rücklauf 1 und 2 hingen: beide Male fiel die Regel an einer sechsten, ungenannten Zeile
auseinander). Die 310 Tabellenzeilen sind unverändert — nachgewiesen an der Datei über die
vier Zählungen und zusätzlich am Dateidiff von `e2383dd`, drei Hunks bei den Zeilen 29, 510
und 534, alle ausserhalb des Tabellenbereichs 43–352.

Der dritte Rücklauf, vor dem der Abschnitt darunter warnt, ist damit nicht eingetreten. Der
Zuschnitt aus Rücklauf 2 — alle fünf Gegenproben namentlich, die Elferliste aus T46 als
Unterscheidungsgrund, der Abschnitt *Befund 2* ausdrücklich freigegeben — hat getragen.

**Was der Prüfer offen an mich zurückgegeben hat und was nicht in dieses Paket gehört:**
die `basiswechsel`-Familie (`restwelt.basiswechsel` unmarkiert, die vier
`land.<L>.basiswechsel` markiert, alle fünf derselben T46-Zeile zugeordnet). Sie ist mit
zwei Sätzen auflösbar, die beide schon in der Datei stehen, aber an verschiedenen Stellen;
das Kriterium ist erfüllt, weil keine Stelle eine Regel *aufstellt*, die eine markierte
Zeile entmarkt. Der Prüfer schlug ein Folgepaket vor statt eines vierten Durchlaufs — das
ist **0030**. Die dahinterliegende Frage `gebiet.<G>.` gegen `land.<L>.`/`restwelt.` bleibt
davon unberührt und steht im Rückstand.

## Rückläufe

1 (2026-09-02, Befund 1: Geschwisterregel umgedreht).
2 (2026-09-02, Befund 1: dieselbe Regel an den drei `wechselkurs`-Zeilen umgekehrt
angewandt; der Rücklauf trägt den Zuschnitt des Kriteriums, siehe *Rücklauf 2*).

**Der dritte Rücklauf wäre der letzte.** `baulauf.py` hält bei `RUECKLAUF_MAX = 3` an und
meldet das Paket als festgefahren — dann ist nicht mehr der Bauagent zu prüfen, sondern
das Abnahmekriterium. Beide bisherigen Rückläufe hingen an derselben Stelle: einer Regel
über Geschwisteradressen, die für einen Teil der Tabelle gilt und für einen anderen
nicht. Punkt 1 nennt jetzt **alle fünf** Gegenproben namentlich und die Elferliste als
Unterscheidungsgrund; damit ist die Regel, die dasteht, an der Tabelle vollständig
nachrechenbar. Rechne sie vor dem Schreiben einmal ganz durch, statt den Halbsatz zu
formulieren und zu hoffen.
