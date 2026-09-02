# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, siebter Baulauf. Fassung 6, geschrieben vom Projektmanager. Diese Datei
sagt, welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden lassen muss.

## Was dieser Lauf getan hat

**Zwei Prüfbefunde, beide `geprueft`, beide auf `fertig` nachgezogen.**

- **0008 (`kern::zustand`, 310 Felder)** — der Prüfer hat die Abnahme nicht nachgelesen,
  sondern von aussen nachgemessen: eigener `diff` der 310 Adressen gegen `daten/adressen.md`
  statt des Selbsttests, fünfzehn `stelle_*`-Werte ohne Übersetzer von Hand, und die drei
  veröffentlichten Prüfsummen in beliebig genauer Ganzzahlarithmetik **ausserhalb** des
  Programms neu aufgebaut. Damit ist der Kreis „das Programm prüft sich selbst" gebrochen.
- **0017 (Reihenliste, maschinenlesbar)** — alle sechs Bedingungen halten. Zwei davon sind
  in ihrem Wortlaut aber nicht erfüllbar, ohne eine Falschaussage zu erzeugen; das ist ein
  Befund gegen **mein** Abnahmekriterium, nicht gegen die Datei. Beide Umformulierungen
  stehen in 0017 unter „Status" und gelten ab jetzt.

**Damit fallen 0016 und 0020 von selbst frei** — beide hingen allein an 0008. Der Kern hat
wieder eine baubare Aufgabe, und alle vier Bauplätze sind mit echter Arbeit belegt.

**Drei neue Pakete, aus den Befunden dieser beiden Prüfungen und aus dem Plan:**

- **0021 „Schaden" in Gegenkraft 5** (spielentwerfer, `spiel.md`) — das ist die Empfehlung
  A des Plans, mit **einer Abweichung in der Rolle**: Der Plan schlägt ein Architektenpaket
  vor, `technik.md` Zeile 264 sagt aber wörtlich, *„wie hoch der Schaden eines Sektors ist,
  bleibt Sache von `spiel.md`"*, und der Architekt hat die Lücke ausdrücklich nicht gefüllt
  („Fülle ich sie, misst Maß 2 meine Wahl"). Für den Spielentwerfer gilt dieser Einwand
  nicht — die Gegenkräfte sind sein Gewerk. Zweiter Grund: 0011 hält `technik.md` besetzt,
  ein zweites Architektenpaket wäre kollidiert und gar nicht erst eingeplant worden.
- **0022 Reihenliste, drei Korrekturen** (datenbauer, `reihen.toml`) — Befunde 1, 4 und 5
  der Prüfung zu 0017. Alle drei sind Aussagen **über** die Daten, die gegen ihre eigene
  Quelldatei nicht halten, und alle drei stehen in Blöcken, die später jemand als Beleg
  zitiert. Der schwerste: `[pruefweg].toml_geprueft` behauptet einen Parserlauf, den die
  Rolle nicht ausführen kann.
- **0023 Fehlerwert von `adresse_zu_index`** (kernbauer, `zustand`-Trio) — Befunde 3 und 1
  der Prüfung zu 0008. `{false, 0}` bei unbekannter Adresse, und Platz 0 ist
  `land.US.sektor.1.wertschoepfung`; wer `.gefunden` nicht auswertet, schreibt still auf
  eine getragene Größe. Das ist genau die Bauart, gegen die `festkomma.hpp:42-49` in
  diesem Kern ausdrücklich entschieden hat.

## Wo die Pakete stehen

| Paket | Rolle | Status | woran es hängt |
|---|---|---|---|
| 0001 Entwurfsabnahme | spielentwerfer | `fertig` | — |
| 0002 Fondsbewertung | kernbauer | `blockiert` | Klasse-2-Entscheidung (Punkt 3) |
| 0003 Einheiten | kernbauer | `blockiert` | Betreiberfrage, ADR gegen T5 oder gar nicht |
| 0004 Gerüst + Festkomma | kernbauer | `fertig` | — |
| 0005 WDI-Lizenz | datenbauer | `fertig` | — |
| 0006 Deckung 1997 | datenbauer | `fertig` | — |
| 0007 Adressverzeichnis | datenbauer | `fertig` | — |
| 0008 Zustand, 310 Felder | kernbauer | **`fertig`** | — |
| 0009 `parameter.toml` | datenbauer | `gebaut`, im Review | Rücklauf 2 von 3 |
| 0010 Zustandsausgabe | kernbauer | `offen` | 0002 (blockiert) + zwei Entwurfsfragen |
| 0011 Stack auf C++ | architekt | `offen`, **eingeplant** | — |
| 0012 Zufall | kernbauer | `fertig` | — |
| 0013 Prüfsumme | kernbauer | `fertig` | — |
| 0014 Lizenz, übrige Reihen | datenbauer | `fertig` | — |
| 0015 Markierungssatz | datenbauer | `gebaut`, im Review | — |
| 0016 `kern::schreiber` | kernbauer | `offen`, **eingeplant** | — |
| 0017 Reihenliste | datenbauer | **`fertig`** | — |
| 0018 Klärungsliste | datenbauer | `gebaut`, im Review | — |
| 0019 Vorrat + Profile | testentwickler | `offen`, **eingeplant** | — |
| 0020 Wertebereichsschranken | testentwickler | `offen`, **eingeplant** | — |
| 0021 Schaden, Gegenkraft 5 | **spielentwerfer** | **neu**, `offen`, startbereit | — |
| 0022 Reihenliste, Korrekturen | **datenbauer** | **neu**, `offen`, startbereit | — |
| 0023 Adressfund-Fehlerwert | **kernbauer** | **neu**, `offen`, startbereit | — |

`python3 agents/baulauf.py 0016-… --trocken` meldet 8 offen, 3 gebaut, 10 fertig, 2
blockiert — Summe 23, also alle Paketdateien, kein Frontmatterfehler.

## Die Reihenfolge und warum sie so ist

```
0011 Stack [architekt] ──> (Reihe-2-Rundung, `frei` in Spalte Rolle: technik.md ist besetzt)

0008 Zustand [FERTIG] ──> 0016 Schreiber   [eingeplant]
                      ├─> 0020 Schranken   [eingeplant]
                      ├─> 0023 Fehlerwert  [wartet auf einen Platz]
                      └─> 0002 Werte [BLOCKIERT] ──> 0010 Ausgabe

0019 Vorrat [eingeplant]        0021 Schaden ──> später: schritt
0022 Korrekturen                (beide warten auf einen Platz)
```

**Zum ersten Mal ist der Rückstand tiefer als die Bank.** Bisher war die Frage, ob genug
baubare Arbeit da ist; jetzt ist mehr da, als der Runner gleichzeitig zieht. Das ist die
gesündere Lage — sie kostet aber genau das, was Punkt 2 unten beschreibt.

## Was der Geschäftsführer entscheiden lassen muss

**1. Ein TOML-Parser gehört in den Runner.** Unverändert seit Fassung 4, jetzt **viermal**
gemessen über zwei Pakete: `python3` mit `tomllib` wird in dieser Umgebung abgewiesen, dem
Datenbauer wie dem Prüfer. Abnahme 4 von 0009 und Bedingung 6 von 0017 verlangen beide
gültiges TOML, und beide sind bis heute nur strukturell belegt. Drei Zeilen neben
`uebersetzen()`, die jede `*.toml` durch `tomllib` schicken. Kein Gate.

Neu daran ist die Folge, die 0017 sichtbar gemacht hat: Die Datei hat den fehlenden Nachweis
nicht offengelassen, sondern **behauptet** — `[pruefweg].toml_geprueft` nennt einen Lauf, den
es nicht gab. Ein fehlendes Werkzeug erzeugt nicht nur eine Lücke, es erzeugt eine
Falschaussage an der Stelle, an der die Lücke unbequem ist.

**2. Der Scheduler hat keine Vorfahrt, und diesmal kostet es die Engpassfrage.** Unverändert
in der Sache, aber zum ersten Mal mit Preis. `baulauf.py:267` nimmt `startbereit(...)[:4]`,
und `startbereit` läuft über `sorted(ordner.glob("*.md"))` — reine Dateinamen-Reihenfolge.
Der Trockenlauf zieht 0011, 0016, 0019, 0020. **0021, das Paket zur Engpassfrage des letzten
Plans, ist Sechster in der Namensfolge und läuft nicht.** Ebenso wenig 0022 und 0023.

Die in Fassung 5 vorgeschlagene Regel („je Rolle höchstens zwei Plätze") hilft hier
**nicht** — ich habe es nachgerechnet, sie ändert an dieser Auswahl keine Zeile. Was hilft,
ist ein Reihum: **erst ein Paket je Rolle, dann die freien Plätze auffüllen.** Dann zieht
derselbe Lauf 0011 (architekt), 0016 (kernbauer), 0019 (testentwickler) und **0021
(spielentwerfer)** statt des zweiten Testentwicklerpakets — fünf Gewerke statt vier, und die
Engpassfrage läuft eine Runde früher. Der Zuschnitt der Pakete ändert sich dafür nicht.

Ich plane weiterhin nicht um: Ein Paket künstlich zu blockieren, damit ein anderes drankommt,
wäre eine Lüge im Statusfeld, und rückwärts zu nummerieren verstösst gegen die Konvention.

**3. Klasse 2 misst zweierlei — laufende und konstante Preise.** Unverändert und weiter die
schwerste offene Sache. T5 nennt Klasse 2 „Tausend USD zu konstanten Preisen", darin liegen
die 40 Handelsströme aus CEPII BACI („thousands current USD"). Maß 4 misst so Inflation statt
Modellgüte. **Sie blockiert 0002 und über 0002 das Paket 0010.**

Neu und dieselbe Sache eine Ebene tiefer, aus Befund 2 der Prüfung zu 0017: **Die
Quelleneinheit von PWT (Reihe 3) und BACI (Reihe 14) hat bis heute niemand gemessen.** Beide
müssen vor dem Jahrgangsbau stehen, BACI zusätzlich mit der Preisbasis — sonst ist
`durchgriff` (Reihe 16) ein Quotient aus zwei verschiedenen Einheiten und damit
bedeutungslos. `reihen.toml` führt beide Reihen richtigerweise als `ungemessen` mit
ausgeschriebener Frage, statt eine `1` hinzuschreiben, die bei PWT um den Faktor 1.000 falsch
und stumm wäre.

**4. Klasse 4 — trägt sie ihren Deckel auch für Regler?** Unverändert offen; fünf
Klasse-4-Schlüssel in `parameter.toml` tragen `>= 0` ohne obere Schranke, obwohl T5 der
Klasse 0 bis 10.000 gibt. Der Datenbauer hat sie in zwei Rückläufen wie angewiesen nicht
angefasst.

**5. Reihe 9 und R = 19.** Unverändert; Reihe streichen oder Quelle ersetzen, beides
entscheidet der Spielentwerfer. Die drei Varianten sind durchgerechnet, keine reisst `R ≤ 26`.

**6. Wo die Zustandsausgabe wohnt, und woher sie zwei Spalten nimmt.** 0010 legt die drei
Ebenen in `kern`, T13 gibt sie `schnittstelle` — unverändert. Dazu neu aus der Prüfung zu
0008: **Die Abnahme von 0010 verlangt je Adresse Wert, Skalenklasse *und* Herkunft; der Kern
trägt die beiden letzten nicht**, `daten/adressen.md` schon. Eine zweite Tabelle über
dieselben 310 Adressen wäre die Sorte Doppelführung, gegen die T17 argumentiert. Nicht
dringend — 0010 hängt ohnehin an 0002 —, aber es ist die zweite offene Frage an demselben
Paket, und beide gehören dem Architekten.

**7. Zwei Entwurfsfragen für den Architekten, sobald 0011 durch ist.** Unverändert: Das
`frei` in der Spalte „Rolle" der Reihenliste ist die T37-Klasse und kein Lizenzurteil
(Warnung vor einer Reparatur, die die Verbindung zu T37 zerschösse), und: Rundet Reihe 2 vor
oder nach der Normierung? Beide liegen in `technik.md`, das 0011 gerade besetzt hält; sie
werden ein Paket, sobald 0011 `fertig` ist. **Kein Bedarf an einer Entscheidung, nur an
Reihenfolge** — steht hier, damit es nicht vergessen wird.

**8. Wandert das Vorratsverfahren später aus `pruefstand` heraus?** Unverändert, blockiert
nichts. T43 nennt es einen Baustein des Prüfstands, T30 Prüfung 5 und 6 geben dem Bruchtester
Läufe, die es je Runde brauchen. Dieselbe Verdrahtungsfrage stellt sich für die Prüffunktion
aus 0020.

## Was quer liegt, aber keine Entscheidung braucht

**Der Ausfall sitzt jetzt auf dem Prüfplatz, nicht auf dem Bauplatz.** Von vier Prüfungen des
letzten Laufs sind zwei ohne Ergebnis geblieben: **0015 hat keine Befunddatei**, und
**0009 Runde 3 ist eine 0-Byte-Datei**. Beide Pakete stehen deshalb weiter auf `gebaut` und
gehen in diesem Lauf erneut in den Review — das ist richtig so, ein fehlendes Urteil ist kein
Urteil. Für 0009 heisst es zugleich: Der Rücklaufzähler steht weiter bei **zwei von drei**,
weil `rueckläufe()` `urteil` liest und die leere Datei keines trägt. Der nächste `zurueck`
macht das Paket festgefahren; dann ist mein Abnahmekriterium zu prüfen und nicht die Arbeit.

**Die Rohdaten hat niemand.** Unverändert: `daten/` enthält fünf Textbefunde und keine
Datenzeile; `werkzeuge/aufbereitung` liest nach T23 „die eingefrorenen Rohdateien". Kein
Bauagent kann das erledigen, und deshalb hat der Jahrgangsbau 1997 kein Paket — obwohl T13
ihn als eines der beiden vorzuziehenden nennt, weil er das Vorhaben kippen kann. Ein Paket
dafür anzulegen hiesse, ein Abnahmekriterium zu schreiben, das die Rolle nicht nachweisen
kann. Kein Gate: `daten.md` sagt für alle vier tragenden Quellen ausdrücklich keine
Registrierung und kein Abonnement. Es ist dieselbe Hand am Runner wie Punkt 1.

**Drei Rollen haben kein Paket, und das ist diesmal richtig.** `oberflaechenbauer` steht in
T13 als letzter Kasten der natürlichen Reihenfolge; `auslieferer` hat nichts auszuliefern;
die drei Prüfrollen (`selbstspieler`, `rueckvergleicher`, `bruchtester`) brauchen eine
gespielte Partie und damit `schritt`. Ich schreibe es hin, weil das Gegenteil mich letzten
Lauf einen Fehler gekostet hat: `testentwickler` stand in denselben Tabellen und war
baubar — der Unterschied ist, dass diese fünf eine Voraussetzung haben, die nachweisbar
fehlt, und nicht bloss kein Paket.

**Ein Commit trägt zum zweiten Mal die falsche Paketkennung.** `770e7b4` heisst „kernbauer:
0012-…" und enthält ausschliesslich die drei `zustand`-Dateien, also die Arbeit an **0008**.
Der Kern-Prüfer ist von selbst darauf gestossen. Das Ergebnis kostet es nichts, die Historie
schon. Für mich bleibt es eine Arbeitsregel und keine Bitte an den Runner: **Vor jedem
Nachzug in die Zieldatei sehen, nicht in den Commit-Betreff.**

**Der Übersetzungslauf ist grün** (`befunde/uebersetzung-2026-09-02.md`). Grün heisst
weiterhin „die Zahlen passen zueinander", nicht „die Zahlen sind richtig". Mit 0019 kommt
eine dritte `CMakeLists.txt` dazu; im Paket steht ausgeschrieben, dass sie **allein**
durchlaufen muss.
