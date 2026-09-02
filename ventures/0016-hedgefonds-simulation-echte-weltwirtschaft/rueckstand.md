# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, achter Baulauf. Fassung 7, geschrieben vom Projektmanager. Diese Datei
sagt, welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden lassen muss.

## Was dieser Lauf getan hat

**Zwei Prüfbefunde, einer `geprueft`, einer `zurueck`. Beide nachgezogen.**

- **0018 (Klärungsliste)** — `geprueft`, auf `fertig` gesetzt. Der Prüfer hat die Zahlen
  aus den Abschnittstabellen neu geholt statt aus den Summenzeilen und die Kaskade
  16 → 8 → 1 gegengerechnet. Alle vier Bedingungen halten.
- **0015 (Markierungssatz)** — `zurueck`, auf `offen` gesetzt, Befund im Paket. Der erste
  Satz der neuen Zelle ist richtig und bleibt; die zweite Hälfte stellt die Geschwisterregel
  **umgekehrt** auf und wird von zwei Zeilen derselben Tabelle widerlegt (Zeile 79 und 222,
  beide markiert). Umfang des Rücklaufs: ein Halbsatz.

**Drei neue Pakete.**

- **0024 Notenbanken unter Reihe 2b/2c** (datenbauer, `lizenzbefund-reihen.md`) — Befund 1
  der Prüfung zu 0018, ausdrücklich **kein** Rücklauf: Das Kriterium verlangte die zwei
  Lieferantengruppen für Reihe 1 und 2a, dort stehen sie. Unter 2b/2c zählt die Begründung
  drei offene Stellen, wo sieben offen sind — und widerspricht damit der Klärungsliste
  derselben Datei.
- **0025 Quelleneinheit PWT und BACI** (datenbauer, neue Befunddatei) — Befund 2 der
  Prüfung zu 0017, seit drei Fassungen als Punkt 3 hier stehend und bis heute ohne Paket.
  Drei ungemessene Größen: Einheit und Basisjahr des PWT-Kapitalstocks, Einheit **und
  Preisbasis** von BACI. **Das Paket hängt an nichts** und ist sofort baubar.
- **0026 Klasse 2, Preisbasis** (architekt, `technik.md`) — das Paket, das **0002
  entblockt**; dessen Entblockungssatz nennt wörtlich „eine Entscheidung des Architekten
  zur Klasse-2-Frage". Es hängt an 0011 (das `technik.md` besetzt hält) und an 0025 (das
  die Preisbasis misst, gegen die entschieden wird).

**Eine geschärfte Bedingung in 0019**, vor dem ersten Review und deshalb kein
Kriterienzuwachs: Der Übersetzungslauf muss die Probe wirklich ausführen. Warum, steht
unter „Was quer liegt".

## Wo die Pakete stehen

| Paket | Rolle | Status | woran es hängt |
|---|---|---|---|
| 0001 Entwurfsabnahme | spielentwerfer | `fertig` | — |
| 0002 Fondsbewertung | kernbauer | `blockiert` | **0026** (Klasse-2-Entscheidung) |
| 0003 Einheiten | kernbauer | `blockiert` | Betreiberfrage, ADR gegen T5 oder gar nicht |
| 0004 Gerüst + Festkomma | kernbauer | `fertig` | — |
| 0005 WDI-Lizenz | datenbauer | `fertig` | — |
| 0006 Deckung 1997 | datenbauer | `fertig` | — |
| 0007 Adressverzeichnis | datenbauer | `fertig` | — |
| 0008 Zustand, 310 Felder | kernbauer | `fertig` | — |
| 0009 `parameter.toml` | datenbauer | `gebaut`, im Review | Rücklauf 2 von 3, **zwei Läufe ohne Urteil** |
| 0010 Zustandsausgabe | kernbauer | `offen` | 0002 → 0026 |
| 0011 Stack auf C++ | architekt | `offen`, **eingeplant** | — |
| 0012 Zufall | kernbauer | `fertig` | — |
| 0013 Prüfsumme | kernbauer | `fertig` | — |
| 0014 Lizenz, übrige Reihen | datenbauer | `fertig` | — |
| 0015 Markierungssatz | datenbauer | **`offen`**, Rücklauf 1, **eingeplant** | — |
| 0016 `kern::schreiber` | kernbauer | `gebaut`, im Review | — |
| 0017 Reihenliste | datenbauer | `fertig` | — |
| 0018 Klärungsliste | datenbauer | **`fertig`** | — |
| 0019 Vorrat + Profile | testentwickler | `offen`, **eingeplant** | — |
| 0020 Wertebereichsschranken | testentwickler | `offen`, **eingeplant** | — |
| 0021 Schaden, Gegenkraft 5 | spielentwerfer | `offen` | wartet auf einen Platz |
| 0022 Reihenliste, Korrekturen | datenbauer | `gebaut`, im Review | — |
| 0023 Adressfund-Fehlerwert | kernbauer | `offen` | wartet auf einen Platz |
| 0024 Notenbanken 2b/2c | **datenbauer** | **neu**, `offen` | wartet auf einen Platz |
| 0025 Einheit PWT/BACI | **datenbauer** | **neu**, `offen`, startbereit | — |
| 0026 Klasse 2 | **architekt** | **neu**, `offen` | 0011, 0025 |

`python3 agents/baulauf.py 0016-… --trocken` meldet 10 offen, 3 gebaut, 11 fertig, 2
blockiert — Summe 26, also alle Paketdateien, kein Frontmatterfehler.

## Die Reihenfolge und warum sie so ist

```
0011 Stack [architekt] ──┐
                         ├─> 0026 Klasse 2 ──> 0002 Werte ──> 0010 Ausgabe
0025 Einheit PWT/BACI ───┘        (entblockt die längste Kette des Vorhabens)

0008 [FERTIG] ──> 0016 Schreiber [im Review]
              ├─> 0020 Schranken [eingeplant]
              └─> 0023 Fehlerwert [wartet]

0015 Rücklauf [eingeplant]   0019 Vorrat [eingeplant]   0021 Schaden ──> später: schritt
0024 Notenbanken [wartet]                               0022 [im Review]
```

Der Rückstand ist zum zweiten Mal tiefer als die Bank: zehn offene Pakete, vier Bauplätze.
Was das kostet, steht unter Punkt 2 — und es kostet seit diesem Lauf mehr als Wartezeit.

## Was der Geschäftsführer entscheiden lassen muss

**1. Drei Rollen können `gebaut` nicht melden, und sie halten drei der vier Bauplätze.**
Das ist der Engpass des letzten Plans, mit zwei Korrekturen und einer Zahl.

*Korrektur an der Zählung:* `grep -n 'status: gebaut' agents/rollen/*.md` findet **vier**
Rollendateien mit dem Satz, nicht zwei — `kernbauer.md:83`, `datenbauer.md:85`,
**`auslieferer.md:110`** und **`oberflaechenbauer.md:81`**. Es fehlen also drei Rollen,
nicht fünf: `testentwickler`, `architekt`, `spielentwerfer`. (In `architekt.md` und
`spielentwerfer.md` kommt das Wort „gebaut" nur in der Prosa vor, in
`testentwickler.md` gar nicht.) Für Weg *A* heisst das drei Stellen statt fünf.

*Die Zahl, die der Plan noch nicht hatte:* Der Trockenlauf plant **0011 (architekt), 0015
(datenbauer), 0019 und 0020 (testentwickler)**. Drei dieser vier Pakete gehören Rollen
ohne den Satz. Also kann in diesem Lauf **genau ein** Paket überhaupt vorankommen, und
die anderen drei werden zum wiederholten Mal gebaut und bezahlt, ohne je einen Prüfer zu
erreichen. Es ist kein Stau mehr, sondern ein Laufband: 0011, 0019 und 0020 halten ihre
Plätze dauerhaft, und 0021, 0023, 0024, 0025, 0026 kommen nie dran.

*Die Empfehlung des Plans (Weg B, der Runner setzt `gebaut` selbst, wenn der Bauagent mit
0 zurückkommt und die Dateien aus `dateien` sich geändert haben) trägt auch die Korrektur:*
Sie prüft sich mit — 0020 hat in diesem Lauf keine Datei geschrieben und bliebe zu Recht
`offen`, während Weg A es fälschlich als `gebaut` gemeldet hätte. **Kein Gate.**

**2. Der Scheduler hat keine Vorfahrt.** Unverändert in der Sache
(`baulauf.py:267`, `startbereit(...)[:4]` über `sorted(glob("*.md"))`), aber Punkt 1 macht
daraus einen Dauerzustand statt einer Verzögerung. Der Reihum-Vorschlag aus Fassung 6
(erst ein Paket je Rolle, dann auffüllen) ändert an der Auswahl dieses Laufs **nichts** —
sie enthält bereits drei Gewerke. Er hilft erst, wenn Punkt 1 gelöst ist. Ich melde ihn
deshalb weiter, aber nicht mehr als dringend.

Ich plane weiterhin nicht um: Ein Paket künstlich zu blockieren, damit ein anderes drankommt,
wäre eine Lüge im Statusfeld, und rückwärts zu nummerieren verstösst gegen die Konvention.

**3. Ein TOML-Parser gehört in den Runner.** Unverändert, jetzt **viermal** gemessen über
zwei Pakete: `python3` mit `tomllib` wird in dieser Umgebung abgewiesen, dem Datenbauer wie
dem Prüfer. Abnahme 4 von 0009 und Bedingung 6 von 0017 verlangen beide gültiges TOML, und
beide sind bis heute nur strukturell belegt. Drei Zeilen neben `uebersetzen()`. Kein Gate.

**4. Klasse 2 misst zweierlei — laufende und konstante Preise.** Unverändert die schwerste
offene Sache, aber sie hat seit diesem Lauf einen Weg: **0025 misst, 0026 entscheidet,
0002 wird frei.** Keine Betreiberentscheidung nötig, nur Bauplätze — siehe Punkt 1.

**5. Klasse 4 — trägt sie ihren Deckel auch für Regler?** Unverändert offen; fünf
Klasse-4-Schlüssel in `parameter.toml` tragen `>= 0` ohne obere Schranke, obwohl T5 der
Klasse 0 bis 10.000 gibt. Der Datenbauer hat sie in zwei Rückläufen wie angewiesen nicht
angefasst.

**6. Reihe 9 und R = 19.** Unverändert; Reihe streichen oder Quelle ersetzen, beides
entscheidet der Spielentwerfer. Die drei Varianten sind durchgerechnet, keine reisst `R ≤ 26`.

**7. Wo die Zustandsausgabe wohnt, und woher sie zwei Spalten nimmt.** Unverändert: 0010
legt die drei Ebenen in `kern`, T13 gibt sie `schnittstelle`; und die Abnahme von 0010
verlangt je Adresse Wert, Skalenklasse *und* Herkunft, während der Kern die beiden letzten
nicht trägt. Zusammen mit der Rundungsfrage bei Reihe 2 und dem `frei` in der Spalte
„Rolle" (das die T37-Klasse ist und kein Lizenzurteil) ist das **das nächste
Architektenpaket nach 0026** — alle drei liegen in `technik.md`, und die Datei trägt einen
Halter zur Zeit. Kein Bedarf an einer Entscheidung, nur an Reihenfolge.

**8. Wandert das Vorratsverfahren später aus `pruefstand` heraus?** Unverändert, blockiert
nichts. Dieselbe Verdrahtungsfrage stellt sich für die Prüffunktion aus 0020.

## Was quer liegt, aber keine Entscheidung braucht

**Der Übersetzungslauf ist grün und übersetzt eine Datei nicht, die nicht übersetzt.** Das
ist der teuerste Fund dieses Laufs. `pruefstand/` enthält seit dem letzten Lauf vier
Dateien aus 0019, davon drei unbrauchbar: `src/vorrat.cpp` bricht nach 25 Zeilen mitten in
`namespace pruefstand::vorrat {` ab, `test/vorrat_probe.cpp` ist eine Zeile
`// PLATZHALTER`, und `CMakeLists.txt` ist eine Zeile `# PLATZHALTER`. Weil die
`CMakeLists.txt` kein Ziel erzeugt, übersetzt niemand die abgebrochene Quelle:
`uebersetzung-2026-09-02.md` meldet für diesen Kasten einen leeren Bauabschnitt und *„No
tests were found!!!"* — und trotzdem `ergebnis: ok`. **Ein Prüfstand, den `ctest` nicht
aufruft, ist im Bericht von einem, den es nicht gibt, nicht zu unterscheiden.** Das Paket
0019 trägt deshalb seit diesem Lauf eine siebte Bedingung (der Testlauf muss die Probe
namentlich mit `Passed` zeigen) und einen Abschnitt, der den Torso beschreibt — damit der
nächste Lauf ihn nicht für eine Vorgängerfassung hält, gegen die er weiterbaut.

**Vierte Messung am Prüfplatz, und diesmal besser: 2 von 4 leer war der letzte Lauf, 0 von
4 wäre dieser.** Nach dem Nachzug stehen nur noch drei Pakete auf `gebaut` (0009, 0016,
0022) — alle drei bekommen einen Prüfer, ein Prüfplatz bleibt frei. **0009 hat jetzt zwei
Läufe hintereinander keine Prüfung bekommen** (Runde 3 ist eine 0-Byte-Datei) und steht
weiter bei zwei von drei Rückläufen, weil `rueckläufe()` `urteil` liest und eine leere
Datei keines trägt. Der nächste `zurueck` macht es festgefahren; dann ist mein
Abnahmekriterium zu prüfen und nicht die Arbeit.

**Der Commit-Betreff ist für dieses Vorhaben keine Zuordnung mehr, das ist jetzt belegt.**
Beide Prüfer dieses Laufs sind unabhängig darauf gestossen: `efac2b1` heisst „datenbauer:
0015-…" und enthält die vollständige Leistung von **0018**; `b324cce` mit dem Betreff 0018
berührt nur ein Logbuch. Der Prüfer der 0015 hat daraus die richtige Folge gezogen — die
Abnahmebedingung „`git diff --stat` zeigt eine Änderung" ist als Nachweis unbrauchbar. Sie
ist im Rücklauf durch eine Bedingung an der Datei ersetzt. **Für mich bleibt es eine
Arbeitsregel:** Vor jedem Nachzug in die Zieldatei sehen, nicht in den Commit-Betreff.

**14 `.tmp`-Dateien liegen im Repo**, inzwischen auch zwei in `aufgaben/` (`.kopf.tmp`,
`.paket.tmp`, beide mit `status: gebaut` im Kopf). Sie sind unschädlich, weil
`startbereit()` über `glob("*.md")` läuft und sie nicht sieht. Gemeldet, weil es wächst und
weil ein Bauagent, der sich mit Zwischendateien behilft, den ganzen Schreibpfad committet.

**Die Rohdaten hat niemand.** Unverändert: `daten/` enthält Textbefunde und keine
Datenzeile; `werkzeuge/aufbereitung` liest nach T23 „die eingefrorenen Rohdateien". Deshalb
hat der Jahrgangsbau 1997 weiter kein Paket, obwohl T13 ihn als vorzuziehend nennt.
**0025 ist der Teil davon, der ohne Rohdaten geht** — die Einheit steht in der
Dokumentation, nicht in den Daten. Kein Gate: `daten.md` sagt für alle vier tragenden
Quellen ausdrücklich keine Registrierung und kein Abonnement. Es ist dieselbe Hand am
Runner wie Punkt 3.

**Drei Rollen haben kein Paket, und das ist weiter richtig.** `oberflaechenbauer` steht in
T13 als letzter Kasten der natürlichen Reihenfolge (`kern` → `daten`/`schnittstelle` →
`konsole` → Tests und `pruefstand` → `oberflaeche`); `auslieferer` hat nichts
auszuliefern; die drei Prüfrollen (`selbstspieler`, `rueckvergleicher`, `bruchtester`)
brauchen eine gespielte Partie und damit `schritt`. Allen fünf fehlt eine Voraussetzung
nachweisbar — das ist der andere Fall als eine Rolle, die baubar wäre und kein Paket hat.

**`schritt` hat weiter kein Paket, und das ist die eine Zahl.** Es braucht die
Rechenvorschrift für „Schaden" (0021, wartet auf einen Platz) **und** `kern::werte` (0002,
blockiert bis 0026). Solange `schritt` zwei Zeilen hat, rechnet das Spiel nicht, gleich wie
viele Pakete durchgehen. Beide Zulieferer stehen jetzt im Rückstand und beide hängen an
Punkt 1.
