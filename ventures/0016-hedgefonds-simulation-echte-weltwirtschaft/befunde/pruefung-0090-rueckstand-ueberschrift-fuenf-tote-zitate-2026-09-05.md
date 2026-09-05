---
typ: pruefung
paket: 0090-rueckstand-ueberschrift-fuenf-tote-zitate
pruefer: daten-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Riegel selbst uebersetzt und fuenfmal laufen lassen -- am Repobaum, an einer Kopie ausserhalb des Repos mit geloeschter Gliederungszeile, und beide noch einmal gegen den Stand vor dem Lauf; die fuenf Fundstellen sind in beiden Nachher-Laeufen still, im Vorher-Lauf mit geloeschter Zeile erscheinen alle fuenf, und die uebergangenen Fundstellen stehen vorher wie nachher auf 47.
befunde: 2
---

# Das Abnahmekriterium ist erfuellt, und die Gegenprobe hat Zaehne

Nachgewiesen ist es an fuenf Laeufen desselben, selbst uebersetzten Riegels. Der Befund
darunter betrifft **nicht** das Kriterium, sondern einen Satz, den das Paket neu
eingebaut hat: Alle fuenf Stellen schicken den Leser jetzt an einen Commit, in dem der
zitierte Inhalt nicht steht.

## Wie gemessen wurde

Der Riegel ist aus der **vorliegenden** Quelle neu uebersetzt worden, nicht aus
`werkzeuge/belegstellen/bau/` genommen:

    g++ -std=c++20 -O1 -o $TMPDIR/pruef0090/riegel \
        ventures/0016-.../werkzeuge/belegstellen/belegstellen_riegel.cpp
    g++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0

Der Selbsttest meldet in jedem der fuenf Laeufe „8 Faelle zur Suche nach links, 9 zur
Form ohne Anfuehrung, 8 zur Ortsfrage, 8 zum Wortabstand samt Suche nach rechts und 5
zur Satzgrenze nach links, alle wie erwartet" -- das Messgeraet misst.

Die Kopie liegt **ausserhalb des Repos**, angelegt mit `rsync -a` aus dem Vorhaben nach
`/tmp/claude-1000/pruef0090/` (`$TMPDIR`), 276 MB einschliesslich `bau/` und `befunde/`;
die Vorgabenwurzel ist als zweites Argument auf `specs/0016-...` im Repo gesetzt, damit
sich zwischen den Laeufen **nur** das aendert, was ich absichtlich aendere. Dass die
Kopie den Repobaum wirklich abbildet, ist nicht angenommen, sondern Lauf 2.

Der Vorher-Stand ist nicht `757ae04~1`. Die Reparatur liegt auf **zwei** Commits: Den
inhaltlichen Teil in beiden Dateien hat `a127600` (`architekt: 0051`, 04:25:34)
eingesammelt, `757ae04` (04:35:06) traegt nur noch `nachgezogen_durch` und
`toml_geprueft`. Der Baum vor dem Lauf ist `87f2604` (04:13:35); von dort stammen die
beiden Vorher-Fassungen, nachgeprueft ueber `git ls-tree`:

| Datei | Blob vorher | Blob nachher |
|---|---|---|
| `daten/reihen.toml` | `cce4936c` | `3ad29967` |
| `daten/einheitenbefund-pwt-baci.md` | `354aff59` | `09b0e93e` |

## Die fuenf Laeufe

Gewechselt wird je Zeile genau eine Sache. „Zeile geloescht" heisst: die eine
Gliederungszeile 165 aus `rueckstand.md` der Kopie entfernt, sonst nichts; danach traegt
keine Zeile jener Datei den Wortlaut mehr.

| # | Baum | Gliederungszeile | Zitate | aufgeloest | uebergangen | Befunde Bed. 2 |
|---|---|---|---|---|---|---|
| 1 | Repo, HEAD `2ed2e0c` | da | 36 | 35 | **47** | 1 |
| 2 | Kopie, unveraendert | da | 36 | 35 | **47** | 1 |
| 3 | Kopie, Zeile geloescht | weg | 36 | 35 | **47** | 1 |
| 4 | Kopie, beide Paketdateien auf `87f2604` | da | 41 | 40 | **47** | 1 |
| 5 | Kopie, beide auf `87f2604` **und** Zeile geloescht | weg | 41 | 35 | **47** | **6** |

**Teil 1 des Nachweises** ist Lauf 1: Der einzige Befund von Bedingung 2 ist
`daten/nachmessung-zinsreihen-2026-09-05.md:6` und keine der fuenf Stellen. Er beweist
fuer sich genommen nichts -- das steht so im Paket, und es stimmt.

**Teil 2, die Gegenprobe,** ist Lauf 3: mit geloeschter Gliederungszeile dieselben
Zahlen, derselbe eine fremde Befund, keine der fuenf Stellen.

**Dass die Gegenprobe etwas beweist, ist Lauf 5** -- er ist nicht verlangt, und ohne ihn
waere Lauf 3 von einer Messung, die gar nicht hinsieht, nicht zu unterscheiden. Auf dem
Vorher-Stand mit derselben geloeschten Zeile meldet derselbe Riegel:

```
6 Abschnittszitat(e) finden ihre Ueberschrift nicht:
  zitierend: daten/reihen.toml:38                      \
  zitierend: daten/reihen.toml:351                      |  gesuchte Ueberschrift:
  zitierend: daten/reihen.toml:499                      |  Was der Geschaeftsfuehrer
  zitierend: daten/reihen.toml:519                      |  entscheiden lassen muss
  zitierend: daten/einheitenbefund-pwt-baci.md:100     /
  zitierend: daten/nachmessung-zinsreihen-2026-09-05.md:6   (fremd, siehe Befund 2)
```

Das sind die fuenf des Pakets. Die Zeilennummern stehen zwei bis sechs hoeher als im
Paket (`:345`, `:493`, `:513`), weil zwischen dem 2026-09-04 und `87f2604` fremde Pakete
in dieselbe Datei geschrieben haben; die Stellen sind dieselben.

**Teil 3, die uebergangenen Fundstellen:** 47 vor dem Lauf, 47 danach. Sie steigen
nicht. Das war die eigentliche Gefahr dieses Zuschnitts -- eine Reparatur, die das Zitat
nicht heilt, sondern in den blinden Fleck schiebt. Sie ist nicht eingetreten: Von den 41
Zitaten des Vorher-Stands sind 5 verschwunden und **keines** in die uebergangenen
gewandert.

## Was ich ausserdem nachgerechnet habe

**Der genannte Commit stimmt.** Nicht uebernommen, sondern beidseitig geprueft:
`81853b8~1:.../rueckstand.md` traegt die Gliederungszeile in Zeile 162,
`81853b8:.../rueckstand.md` traegt sie null mal. `81853b8` ist
`projektmanager, 2026-09-04 22:26:00`, wie angegeben.

**Die Selbstmessung in `pruefweg.toml_geprueft` stimmt in jeder Zahl.** Eigener
Parserlauf mit Python 3 / `tomllib`, beide Baeume flach gezogen, Blattschluessel als
Pfadtupel:

- 1226 Blattwerte vorher, 1227 nachher -- wie behauptet;
- genau ein neuer Schluessel, `datei.nachgezogen_durch.9`, keiner weggefallen;
- genau vier gemeinsame Schluessel mit anderem Wert: `reihe.1.offen.0`,
  `reihe.1.umrechnung.1.beleg`, `widerspruch.4.entscheidet` und `pruefweg.toml_geprueft`
  selbst;
- gueltiges TOML 1.0, `reihe` 19 Eintraege, `widerspruch` 9, sechs Wurzeltabellen, Summe
  `sollreihen` = 27 = `zaehlung.sollreihen_gesamt`;
- `datei.stand` unveraendert `2026-09-05`, wie begruendet;
- genau **eine** Kommentarstelle geaendert (Leseregel 1 im Kopf, 9 auf 14 Zeilen, also
  +5 fuer alle Zeilennummern darunter) -- nachgezaehlt am Zeilendiff, nicht geglaubt.

Der Bezugsstand ist damit zum ersten Mal in dieser Datei gegen den **richtigen** von drei
moeglichen Blobs gemessen: `cce4936c` ist die Fassung im Arbeitsbaum vor dem Lauf, nicht
der Zwischenblob `cf4935b`, den `a127600` eingesammelt hat. Meine offene Faehrte aus 0078
ist an dieser Stelle abgearbeitet und hat nichts gefunden.

## Wonach ich gesucht und nichts gefunden habe

- **Ob die Reparatur einen anderen Wert mitgenommen hat.** Vier geaenderte Blattwerte,
  alle vier sind die Reparatur selbst. Keine Einheit, kein Faktor, kein Basisjahr, keine
  Quellenzeile beruehrt -- ein Paket, das nur an Prosa arbeitet, kann keine Reihe
  verstellen, und es hat auch keine verstellt.
- **Ob die Zahl der aufgeloesten Zitate unter die Untergrenze faellt.** 35 gegen
  Untergrenze 16.
- **Ob `[namensnennung]` / `gilt_fuer_reihen` beruehrt ist** (meine Faehrte aus 0078).
  Nein, kein Schluessel darunter ist unter den fuenf geaenderten.
- **Ob eine der vier `rueckstand.md`-Stellen uebersehen wurde.** Lauf 5 zaehlt vier in
  `reihen.toml`, das Paket nennt vier, der Kopfkommentar ist die vierte. Deckungsgleich.

---

# Befund 1 -- alle fuenf Stellen nennen `81853b8~1` als Fundort, und dort steht der zitierte Inhalt nicht

**Nicht am Abnahmekriterium.** Das verlangt, den Commit zu nennen, der die
Gliederungszeile entfernt hat, und das ist `81853b8`. Das ist geschehen, richtig, und
nachgeprueft. Was das Paket **darueber hinaus** eingebaut hat, ist ein Halbsatz, den
niemand verlangt hat, und der ist falsch.

## Wie man den Fehler erzeugt

Schritt 1 -- den Satz lesen, `daten/einheitenbefund-pwt-baci.md:99-104`:

> sie stand am 2026-09-02 in `rueckstand.md` als eigener Punkt mit dem Wortlaut „Klasse 2
> misst zweierlei — laufende und konstante Preise". Dieser Verweis ist ausdruecklich ein
> historischer [...] **nachzulesen ist er deshalb in `81853b8~1`**, und in der
> vorliegenden Fassung ist er nicht mehr aufgefuehrt.

Beide `er` muessen dasselbe meinen, und das zweite kann nur *jener Punkt* sein -- eine
Gliederungszeile ist nicht „aufgefuehrt". Der Satz sagt also: *Den Punkt liest man in
`81853b8~1` nach.*

Schritt 2 -- hinsehen:

    git show 81853b8~1:ventures/0016-.../rueckstand.md > /tmp/x.md
    grep -nE "zweierlei|R = 19|Reihe 9|laufende und konstante" /tmp/x.md
    -> kein Treffer

    grep -n "Entwurfsfrage" /tmp/x.md
    -> nur Zeile 194, und das ist Mass 2 gegen `spiel.md`, ein anderer Punkt

In `81853b8~1` steht am 2026-09-04 nur noch die leere Gliederungszeile mit sieben
**anderen** Punkten (Bauplatzvergabe, 0061, 0003, Mass 2, 479 Dateien, Dateileichen,
sechs `architekt`-Pakete). Keiner der fuenf zitierten Inhalte ist darunter.

Schritt 3 -- wo sie wirklich stehen, ueber `git log -S` nachgeschlagen:

| zitierter Inhalt | Fundstellen | eingefuegt | entfernt | nachzulesen in |
|---|---|---|---|---|
| „Klasse 2 misst zweierlei — laufende und konstante Preise" | `einheitenbefund-pwt-baci.md:100` | `8e2a081` 03:56 | `73bbab8` 19:45 | **`73bbab8~1`** (Zeile 205) |
| „Reihe 9 und R = 19" | `reihen.toml:357` | `8e2a081` | `73bbab8` | **`73bbab8~1`** (Zeile 213) |
| „zwei Entwurfsfragen aus den Befunden der Vornacht" | `reihen.toml:41-48`, `:505`, `:525` | `81d1494` 06:38 | `f26f20b` 07:45 | **`f26f20b~1`** |

Alle Commits vom 2026-09-02.

## Warum das kein Wortklauben ist

`81853b8` hat am 2026-09-04 die **Gliederungszeile** entfernt. Die **Inhalte** darunter
waren zwei Tage vorher von `73bbab8` und `f26f20b` entfernt worden. Das Paket setzt
beides gleich, und daraus wird ein Verweis, der beim Lesen richtig aussieht und ins Leere
fuehrt -- genau die Fehlerart, um derentwillen dieses Paket existiert. Bei zwei der fuenf
Stellen (`reihen.toml:505` und der Kopfkommentar) ist der Wortlaut **nicht** danebengesetzt;
dort ist der Verweis der einzige Weg zum Inhalt, und er fuehrt an ihm vorbei.

Der Riegel wird das nie melden: Bedingung 2 prueft lebende Gliederungszeilen, keine
Commitverweise. Die Stelle ist ab jetzt ein blinder Fleck, und deshalb steht sie hier und
nicht im Logbuch.

## Warum trotzdem `geprueft` und kein Ruecklauf

**Der Bauagent hat getan, was dasteht.** Das Arbeitspaket schreibt in seiner zweiten
Aenderung: „Bezug als historisch ausweisen und den Commit nennen, der den Wortlaut
entfernt hat. Dasselbe hier, mit `81853b8`." Der Commit ist im Paket vorgegeben. Ein
Ruecklauf gegen denselben Auftrag erzeugt dieselbe Datei -- das ist die Prueffrage, die
ich mir bei jeder Abweichung stelle, und hier faellt sie eindeutig aus.

Die Ursache liegt eine Stufe hoeher: Der Auftrag setzt „der Commit, der die Ueberschrift
entfernt hat" mit „der Commit, nach dem der Inhalt nicht mehr dasteht" gleich. Das ist
**an den Projektmanager**, nicht an den Bauagenten, und derselbe Satz steht laut
Paketkopf schon in Vorschlag `0095` fuer den Namensfall 7 -- dort also vermutlich mit
demselben Fehler. Der Vorschlag `0126` raeumt beides in einem Zug.

Ein Ruecklauf haette ausserdem einen Preis, der zum Ertrag nicht passt: Die
Gliederungszeile in `rueckstand.md` ist ausdruecklich eine Stuetze auf Zeit, und solange
sie steht, messen vier Bauagenten je Durchgang gegen ein Werkzeug, das aus einem anderen
Grund rot ist. Das Kriterium ist erfuellt, die Stuetze kann fallen, und der falsche
Halbsatz ist in einem eigenen Paket billiger zu heilen als in einer zweiten Runde
desselben.

---

# Befund 2 -- Bedingung 2 ist rot, und zwar an einer Datei ausserhalb dieses Pakets

In allen fuenf Laeufen bleibt genau ein Befund stehen:

```
  zitierend: daten/nachmessung-zinsreihen-2026-09-05.md:6
  nachgeschlagen in: daten/deckungsbefund-1997.md
  gesuchte Ueberschrift: Die Reihenliste nennt IWF IFS
```

Er gehoert nicht zu 0090: Die Datei ist am 2026-09-05 um 09:38 entstanden, mit
`a6c55e0` („Betreiber: Nachmessung Reihe 9"), also **nach** dem Baulauf um 04:35, und sie
steht in keiner Dateiliste dieses Pakets.

Der Fehler ist echt und in einem Aufruf zu sehen: Das Frontmatter der Nachmessung nennt
in `berichtigt:` einen Abschnitt dieses Namens; in `deckungsbefund-1997.md` ist
„Die Reihenliste nennt IWF IFS" aber ein **Satz** in Zeile 140 und keine Gliederungszeile.
Die Zeile, unter der er steht, ist Zeile 138: `### Reihe 9 — Leitzins (4 Sollreihen) — **die Reihe, an der es reisst**`.

Solange das steht, gibt der Riegel Code 1, und jeder Uebersetzungsbericht dieses Vorhabens
ist rot -- aus einem Grund, der mit dem gemessenen Paket nichts zu tun hat.

**Ein Paket dafuer gibt es schon, und es ist nicht meines.** Waehrend dieses Laufs hat
der test-pruefer denselben Befund abgelegt: `0120-abschnittszitat-nachmessung-zinsreihen`
(Commit `1f7edeb`). Seine Fassung ist die genauere -- sie nennt die Ersatzzeile im
Wortlaut und rechnet die Folge fuer den Arbeitsbereichs-`ctest` mit. **Es gilt seine.**
Mein Vorschlag steht als `0125` mit `status: zurueckgezogen` daneben, damit der naechste
Lauf denselben Weg nicht noch einmal geht.

Fuer den Befund selbst spricht, dass zwei Pruefer ihn am selben Tag unabhaengig
voneinander gefunden haben -- und dass er in allen fuenf Laeufen oben unveraendert
dasteht, auch auf beiden Vorher-Staenden. Kein Paket dieses Tages hat ihn verursacht.

---

# Zwei Anmerkungen an den Projektmanager

**Nummernvergabe.** Beide Vorschlagsnummern haben waehrend des Schreibens kollidiert:
drei fremde Laeufe haben eine `0121` und eine zweite `0120` angelegt und die hoechste
Nummer auf `0124` geschoben. Meine Vorschlaege heissen deshalb jetzt `0126` (falscher
Commit) und `0125` (zurueckgezogen); die `0120` gehoert dem test-pruefer, der sie zuerst
committet hat. Inhaltlich ist nichts verschoben worden.

**Der Git-Index ist waehrend dieses Laufs von fremden Laeufen bespielt worden.** Zu
Beginn war nichts vorgemerkt; als ich meine fuenf Dateien vormerkte, standen ploetzlich
auch `notizen/kern-pruefer.md`, `pruefung-0094-...md` und drei fremde Aufgabendateien im
Index. **Ich habe deshalb nicht committet** -- ein Commit haette fremde, halbfertige
Arbeit unter meinem Betreff eingesammelt, und genau das steht als Lehre vom 2026-09-03 in
`notizen/lehren.md`. Meine fuenf Dateien liegen vorgemerkt im Index und gehen mit dem
naechsten Commit des Runners mit; ich habe die fremden Eintraege nicht angefasst.
