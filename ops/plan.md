# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02 19:30, nach dem zehnten Baulauf (18:51–19:26, Läufe 272–280).

## Wo das Vorhaben steht

**Der Prüfstand hat seit 19:13 seinen ersten Test** — `vorrat_probe … Passed`. Das
„No tests were found!!!", das in fünf meiner Pläne stand, ist weg; sieben grüne Tests,
sechs im Kern, einer im Prüfstand. Von 32 Paketen sind 14 `fertig`, 6 `gebaut`, 8 `offen`,
2 `blockiert`, 2 `vorschlag`.

Zwei Pakete, die vier Läufe lang totlagen, sind gefallen: **0019** nach der Teilung durch
den Projektmanager — vier Dateien, 30.835 Byte, wo drei Läufe lang 29 Byte standen — und
**0021** mit 384 Zeilen in `spiel.md`. Der Review lieferte drei von vier Urteilen statt
einem von vier; der Engpass meines letzten Plans ist erledigt.

Ein Bauplatz blieb leer: der Architekt. Der Betreiber hat die Ursache um 19:13 gefunden
und die Rollendatei geändert.

## Der Engpass

**Der Architekt — eine Rolle, eine Datei, vier Fragen in der Schlange, seit 34 Stunden
keine Zeile.**

`technik.md` ist zuletzt am 2026-09-01 09:17 geschrieben worden. Seither hat der Architekt
zwei Bauplätze verbraucht und nichts geliefert; beim letzten meldete er, jedes
Schreibwerkzeug sei gesperrt — eine falsche Diagnose, die gründlich aussah.

Vier Fragen liegen in derselben Datei, und `technik.md` trägt genau einen Bauplatz:
0011 (Stack auf C++), 0026 (Klasse 2, laufende gegen konstante Preise), wo die
Zustandsausgabe wohnt, und das Präfix `gebiet.` gegen `land.`/`restwelt.`.

Daran hängt der ganze Kern: **`kernbauer` hat gerade kein einziges startbereites Paket**
(0002 und 0003 blockiert, 0010 hängt an 0002, 0027 wartet auf das Urteil zu 0023). Und
die Kette zur Spielrunde läuft vollständig durch den Architekten:
**0011 → 0026 → 0002 (`werte`) → `schritt`.**

## Was quer liegt

- **`schritt` hat kein Arbeitspaket.** 32 Pakete, keines nennt `kern/src/schritt.cpp` im
  Feld `dateien` (`grep "^dateien:" aufgaben/*.md | grep -c schritt` → 0). Die Zahl, die
  ich seit vier Plänen melde, kann nicht steigen, weil ihre eine Hälfte nie beauftragt
  wurde. `werte` ist blockiert, `schritt` ist ungefragt — den Unterschied haben meine
  bisherigen Pläne verwischt. **Sechster Fall der vom Betreiber benannten Fehlerklasse**
  (`953bbf5`): ein Kasten im Zielbild, den der Ablauf nicht erreicht.
- **`technik.md` sagt weiter Rust.** 10 Zeilen nennen Rust, `cargo` oder `rustc`, 0 Zeilen
  nennen C++ (`grep -c -i`, gezählt sind Zeilen). Der Kern steht seit ADR 0011 vollständig
  in C++. Jedes Kernpaket bezahlt die Übersetzung erneut, und ein Prüfer, der `specs/`
  gegen den Code hält, misst gegen den falschen Text.
- **0025 ist der einzige Reviewplatz ohne Urteil** — und sitzt direkt auf der
  Engpasskette: 0026 hängt an 0011 **und** 0025.
- **Beide Vorschläge tragen.** 0031 (`FABRIK_STRENGE` steht zweimal wortgleich, bei sieben
  Kästen siebenmal) und 0032 (`reihen.toml` zählt drei, wo sieben offen sind) kommen aus
  der Hand, die drangesessen hat. Klein, und beide hängen an einem Paket, das gerade
  durchgeht.
- Unverändert: kein `ops/baulauf.log`; 18 `.tmp`-Dateien im Repo (vor drei Läufen 14).

## Was der Betreiber entscheiden muss

**Die Rohdaten.** `daten/` enthält nach zehn Bauläufen fünf Textbefunde und `reihen.toml`
— Metadaten über Reihen, **keine einzige Datenzeile**. Ein Simulator der echten
Weltwirtschaft ohne die echte Weltwirtschaft: Der Jahrgangsbau 1997 hat deshalb kein
Paket, und die drei Prüfrollen haben nichts zu prüfen. Kein Gate — `daten.md` nennt für
alle vier tragenden Quellen ausdrücklich keine Registrierung und kein Abonnement, also
kein Geld und keine Anmeldung.

Die Frage ist, welche Hand lädt:

- **A — der Runner bekommt einen Ladeschritt.** Einmal Arbeit am Skript, danach hat jeder
  Datenbauer echte Zeilen.
- **B — der Betreiber lädt die vier Quellen einmal von Hand** nach `…/daten/roh/`.

**Empfehlung B.** Eine Viertelstunde statt einer Runner-Änderung, heute Abend machbar —
und sie beantwortet die Frage, die A voraussetzt: ob die vier Quellen so aussehen, wie
`daten.md` sie beschreibt. Fällt dabei etwas auf, ist A danach billig; fällt nichts auf,
wäre A ins Blaue gebaut worden.

Meine Empfehlung aus den letzten vier Plänen (Runner schreibt `ops/baulauf.log`) stufe ich
zur Notiz herab: nicht falsch, aber der Betreiber hat die Frage am 19:13 von Hand aus dem
Rückgabetext des Architekten beantwortet.

## Vorrang

1. **0011** — der Architekt ist der Engpass, und dies ist die Probe auf die Rollenänderung
   von 19:13. Geht es durch, fällt die Rust/C++-Divergenz mit.
2. **0025** — das fehlende Urteil. Ohne es kann 0026 auch mit fertigem 0011 nicht starten.
3. **0026** — sobald 0011 und 0025 stehen: entblockt 0002 und damit `werte`.
4. **0029** — die einzige Bauarbeit, die ohne den Architekten läuft. Hält den zweiten
   Bauplatz besetzt und baut den Prüfstand weiter, der gerade seinen ersten Test bekam.
5. **0031** — klein, und der erste Vorschlag eines Agenten überhaupt. Ihn anzunehmen lehrt
   den Mechanismus, solange er noch einen Fall hat.

**Ohne Kennung, an den Projektmanager:** `schritt` braucht ein Paket. Bauen lässt es sich
erst nach 0002 — schreiben lässt es sich jetzt. Es ist das einzige fehlende Paket, das die
eine Zahl erklärt.

## Die eine Zahl

**Sieben von neun Kernkästen tragen Code, den fünften Lauf in Folge unverändert.** Neu ist
der Grund: `werte` (78 Byte) ist blockiert, `schritt` (63 Byte) ist nie beauftragt worden.
Eine Spielrunde ist noch immer nie gerechnet worden.
