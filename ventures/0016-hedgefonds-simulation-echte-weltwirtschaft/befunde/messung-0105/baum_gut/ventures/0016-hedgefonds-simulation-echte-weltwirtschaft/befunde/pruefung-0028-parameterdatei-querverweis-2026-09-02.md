---
typ: pruefung
paket: 0028-parameterdatei-querverweis
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Beide Stellen nebeneinander gelesen -- der zweite Satz behauptet keine Gleichheit mehr und gibt die Regel aus `daten/adressen.md` woertlich richtig wieder; der erste Satz und die 25 Marken sind unveraendert; `git diff` an der Datei zeigt genau einen Hunk.
befunde: 0
---

# Pruefung 0028: der Querverweis in `parameter.toml`

Geprueft wurde gegen die drei Bedingungen im Abschnitt *Abnahme* des Pakets und gegen
nichts sonst. Der geaenderte Text steht in `parameter.toml` im Abschnitt *WIE DER PRUEFER
ZAEHLT*, im Absatz, der mit „Ein `*` hinter einem Schluesselnamen" beginnt (Stand
2026-09-02 Zeilen 145–157).

## Kriterium 1 — der zweite Satz behauptet keine Gleichheit mehr

**Erfuellt.** Die Behauptung „Dieselbe Kennzeichnung wie im Adressverzeichnis aus Paket
0007" ist ersetzt durch „**Verwandt, aber nicht dieselbe Kennzeichnung** wie im
Adressverzeichnis", und der Unterschied steht in einem Satz: dort an den Bestandteilen
(„ein Bestandteil ist neu erfunden"), hier an der ganzen Zeichenkette („nicht woertlich
belegt").

Wie ich das geprueft habe: Ich habe die vier Einzelaussagen des neuen Satzes gegen die
Stellen gelegt, auf die er verweist. Alle vier halten.

| Aussage in `parameter.toml` | gegengelesen in `daten/adressen.md` | Ergebnis |
|---|---|---|
| Fundstelle „Spaltenlegende `Adresse`" | Legendenzeile zur Spalte *Adresse* (Z. 29) | existiert, traegt die Regel |
| Fundstelle „*Befund 2*" | `### Befund 2 — 177 der 310 Adressen sind gebildet, nicht zitiert` (Z. 504) | existiert, traegt die Regel |
| „sitzt die Marke an den Bestandteilen" | woertlich: „Die Marke sitzt an den Bestandteilen, nicht an der ganzen Zeichenkette" (Z. 29) | woertlich deckungsgleich |
| „heisst ‚ein Bestandteil ist neu erfunden'" | woertlich: „**Markiert ist alles, wo ein Bestandteil neu erfunden ist.**" (Z. 515) | woertlich deckungsgleich |
| „weshalb `handel.US.CN.1` dort keine Marke traegt, obwohl diese Zeichenkette nirgends woertlich steht" | Tabellenzeile **Nr. 199**, `handel.US.CN.1`, Spalte *Marke* = `—`; Begruendung in der Legende: „denn `handel.DE.CN.1` steht in T17" | nachgezaehlt an der Tabelle, nicht aus der Legende uebernommen |

Das Beispiel `handel.US.CN.1` ist damit nicht nur zitiert, sondern in der Tabelle
gegengeprueft: Es ist tatsaechlich unmarkiert, und es ist tatsaechlich nicht woertlich
belegt — es traegt also die Unterscheidung, fuer die es dasteht. Genau diese Zeile ist der
Fall, an dem die alte Gleichsetzung zerbrach.

**Wonach ich hier zusaetzlich gesucht und was ich nicht als Befund gefuehrt habe:** Die
Legendenzeile in `adressen.md` formuliert die Regel als *Disjunktion* — „ein Bestandteil
ist neu erfunden — **oder** eine Zusammensetzung von Bestandteilen, die in keinem Dokument
gemeinsam vorkommt" —, und sie kennt eine Ausnahme fuer T46-Belege, aus der Marken ohne
neuen Bestandteil folgen (Nr. 63, 107, 151). Der Satz in `parameter.toml` gibt nur den
ersten Ast wieder. **Kein Befund**, und zwar aus einem Grund, nicht aus Nachsicht: Der
wiedergegebene Satz ist die fettgesetzte Selbstzusammenfassung, die `adressen.md` unter
*Befund 2* seiner eigenen Regel voranstellt. Eine Wiedergabe, die den Wortlaut der
Zusammenfassung der Zielstelle uebernimmt und zugleich beide Fundstellen nennt, gibt die
Regel nicht falsch wieder — sie verweist, statt sie zu ersetzen, und genau das verlangt
der Auftrag („verweis auf die Stelle im Adressverzeichnis, statt sie fuer gleich zu
erklaeren"). Wer hier die volle Disjunktion samt T46-Ausnahme verlangte, hoebe das
Kriterium an.

## Kriterium 2 — der erste Satz ist unveraendert

**Erfuellt.** Im `git diff` steht der erste Satz vollstaendig in den Kontextzeilen; die
Aenderung setzt erst hinter „uebrigen gebildet.**" ein. Fuer Schluesselnamen gilt „nicht
woertlich belegt" also unveraendert weiter.

Weil an diesem Satz 25 Markierungen in derselben Datei haengen, habe ich sie nachgezaehlt
statt sie vorauszusetzen — die drei Selbstproben der Datei und die Marken selbst:

- `grep -c '^[a-z_0-9]* *=.*PLATZHALTER'` → **46** (Soll 46)
- `grep -c '^[a-z_0-9]* *=.*FEST (T51)'` → **4** (Soll 4)
- Sternmarken im Kommentar, `` `<name>`* ``, auf 24 Zeilen; `regulierung_start` kommt
  zweimal vor (Z. 325 und 470), `aufsicht_schwelle_1/_2/_3` teilen sich eine Zeile.
  **25 verschiedene Namen** (Soll 25), und die Liste deckt sich Name fuer Name mit
  BEFUNDE Punkt 1: 2 + 3 + 1 + 2 + 1 + 4 Verzoegerungen + 12 Gruppe C = 25.

Die Marken sind also weder verschoben noch gezaehlt worden.

## Kriterium 3 — keine zweite Aenderung an der Datei

**Erfuellt.** Der Nachweis ist an der Datei gefuehrt, wie das Paket es verlangt:

```
git diff ebb9ce5 -- ventures/0016-.../parameter.toml
```

`ebb9ce5` ist der Vorgaenger des Baucommits; der Vergleich reicht damit vom Zustand *vor*
dem Paket bis in den heutigen Arbeitsbaum und schliesst alle spaeteren Commits sowie
uneingecheckte Aenderungen ein. Ergebnis: **genau ein Hunk**, `@@ -144,8 +144,16 @@`,
zwei Zeilen weg, zehn dazu, ausschliesslich im beschriebenen Absatz. Kein Wert, keine
Klasse, keine Schranke, kein Schluessel, kein Zeichen im Abschnitt `BEFUNDE` ist
angefasst.

**Ausdruecklich kein Befund:** Der Baucommit `89a4d12` traegt ausser `parameter.toml` noch
`daten/reihen.toml`, zwei Aufgabendateien und ein Logbuch. Das ist die fremde Arbeit, vor
der das Paket warnt; sie wird ueber `git diff --stat` sichtbar und ist genau deshalb dort
nicht zu bewerten. An `parameter.toml` selbst ist nichts Fremdes.

## Was ich nicht geprueft habe

Die **Gueltigkeit der Datei als TOML**. Ein Parser ist nicht gelaufen — das Paket schliesst
diesen Punkt aus, und ich behaupte nichts anderes.

## Nebenbefund ohne Ruecklaufrang → Vorschlag 0039

Der neue Text begruendet die Folgenlosigkeit des Unterschieds mit „weil ein Schluessel
**keine Gebiets- und Sektorindizes** traegt". `adressen.md` nennt an beiden Stellen
*drei* Indexarten — „Gebiets-, Sektor- und **Instrumenten**indizes" —, und die dritte
kommt in `parameter.toml` vor: vier Tabellen `[instrument.leitzins|zoll|haushalt|
regulierung]` mit je denselben drei Schluesselnamen, von der Datei selbst als „4 x 3 = 12"
Schluessel gezaehlt.

**Die Schlussfolgerung haelt trotzdem** — BEFUNDE Punkt 1 fuehrt alle zwoelf im woertlich
belegten Halb, beide Regeln ergeben dort „keine Marke", und die 25 Marken stehen richtig.
Falsch ist nicht das Ergebnis, sondern die Begruendung, und sie wird von vier
Tabellenkoepfen derselben Datei widerlegt.

**Das ist kein Ruecklauf gegen den Bauagenten.** Der Halbsatz steht im Auftrag von 0028
woertlich so vorgeschrieben („keine Gebiets- und Sektorindizes, also fallen die beiden
Regeln hier zusammen"); der Bauagent hat geschrieben, was das Paket verlangt. Der Einwand
gehoert damit an den Projektmanager und nicht in ein viertes Kriterium. Er steht als
`aufgaben/0039-parameterdatei-indexbegruendung.md`, `status: vorschlag`.
