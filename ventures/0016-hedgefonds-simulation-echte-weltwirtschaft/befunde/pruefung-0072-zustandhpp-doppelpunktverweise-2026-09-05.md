---
typ: pruefung
paket: 0072-zustandhpp-doppelpunktverweise
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Muster aus dem Rumpf ueber `zustand.hpp` -- null Fundstellen; beide Ersatzbelege von Hand in `technik.md` und `spiel.md` nachgeschlagen und zusaetzlich im A/B-Lauf des Belegstellenriegels als aufgeloestes Abschnittszitat nachgewiesen (36/36 auf 37/37)
befunde: 0
---

# Pruefung 0072 — die zwei Doppelpunktverweise sind weg, und der Ersatz haelt maschinell

## Bedingung 1: kein Dateiname mehr unmittelbar an Doppelpunkt und Zahl

Gemessen mit dem Muster aus dem Rumpf des Pakets — Dateiname mit zugelassener Endung,
unmittelbar gefolgt von Doppelpunkt und Zahl:

```
grep -nEo '[A-Za-z0-9_./-]+\.(md|hpp|cpp|h|cc|toml|txt|cmake|py|yml|yaml)[[:space:]]*:[[:space:]]*[0-9]+([-–][0-9]+)?' \
  kern/include/kern/zustand.hpp
→ (keine Fundstelle)
```

Gegenprobe mit dem groesstmoeglichen Netz, `:[0-9]` ueber die ganze Datei: **ebenfalls
null Treffer**, also nicht einmal ein Selbstverweis oder eine gelockerte Schreibweise.
Dieselbe Messung ueber `kern/` und `pruefstand/` insgesamt: null Treffer.

Zum Vergleich der Stand davor, im Arbeitsbaum zum Commit `90f1adb` nachgestellt:

```
kern/include/kern/zustand.hpp:224  `technik.md:477`
kern/include/kern/zustand.hpp:226  `spiel.md:212-213`
```

Beide Fundstellen des Pakets sind also da gewesen und sind fort. **Bedingung 1 erfuellt.**

## Bedingung 2: der Ersatz traegt Schluesselzeile beziehungsweise Abschnittsnamen

Die `abnahme` laesst je Verweis eines von beiden zu. Beides steht heute im Kommentar
ueber `enum class FondsGroesse` (`zustand.hpp:220-250`), und beides habe ich gegen die
Zieldatei nachgeschlagen:

| Verweis | Ersatz im Kommentar | in der Zieldatei gefunden |
|---|---|---|
| `technik.md` | die zitierte Schluesselzeile `"Kasse, Hebelstand, Sichtbarkeit, Anlegerbestand, Marktanteil"` | `technik.md:1142`, Tabellenzeile *Fonds, Aggregat* — wortgleich. Die Zeile liegt in T15, das bei `technik.md:1104` beginnt; die Zuschreibung „T15 zaehlt sie im Wortlaut auf" stimmt damit auch im Abschnitt |
| `spiel.md` | der Abschnittsname `"Der Fonds"` | `spiel.md:423`, `**Der Fonds:** Kasse, Positionen, Beteiligungen, Hebelstand, globale Sichtbarkeit, Anlegerbestand, Marktanteil, …` |

Keiner der beiden Ersatzbelege ist erfunden, und keiner zeigt daneben.

**Die Nebenbehauptung stimmt ebenfalls.** Der Kommentar sagt neu, beide alten Verweise
haetten „schon daneben" gezeigt. Nachgeschlagen im heutigen Bestand: `technik.md:477` ist
die Zeile *Handelsstroeme* aus der Preisbasistabelle (CEPII BACI), `spiel.md:212-213` der
negative Euro-Einlagesatz ab 2014 und `aufschlag_min`. Keine der beiden Stellen hat mit
den fuenf Fondsaggregaten zu tun. Die Behauptung ist belegt, nicht dazuerfunden.

### Zusatznachweis: der Riegel loest den neuen Beleg tatsaechlich auf

Die `abnahme` schliesst den Belegstellenriegel als Messgeraet ausdruecklich aus, weil
seine Muster die Doppelpunktform nicht sehen. Genau deshalb ist er als *zweite* Frage
interessant: Ist der Ersatz nur formal zulaessig, oder ist er nachschlagbar?

A/B im Wegwerf-Arbeitsbaum zu `90f1adb`, **identischer Baum, allein `zustand.hpp`
verschieden**, mit dem heute uebersetzten Riegel:

| Stand | Bedingung 1 | Bedingung 2 |
|---|---|---|
| alter Kommentar (`technik.md:477`, `spiel.md:212-213`) | 5 Zeilenverweise, **0 mit Dateinamen daneben** | 36 Zitate gefunden, **36 aufgeloest** |
| neuer Kommentar (`Absatz "Der Fonds"`) | 5 Zeilenverweise, **0 mit Dateinamen daneben** | 37 Zitate gefunden, **37 aufgeloest** |

Zwei Dinge auf einmal:

1. **Der neue Beleg wird gefunden und aufgeloest** (+1 gefunden, +1 aufgeloest). Der
   Riegel hat „Der Fonds" also nicht nur als Zitatform erkannt, sondern in `spiel.md`
   gegen eine wirkliche Ueberschriftszeile nachgeschlagen. Aus einer Nummer, die niemand
   pruefen kann, ist ein maschinell gepruefter Beleg geworden — mehr, als die `abnahme`
   verlangt.
2. **Die Praemisse des Pakets ist unabhaengig bestaetigt.** Im alten Stand stand
   `technik.md:477` woertlich in der Datei, und Bedingung 1 meldete trotzdem „0 mit
   Dateinamen daneben". Der Riegel lief an der Doppelpunktform vorbei, genau wie das
   Paket behauptet hat.

Im heutigen Gesamtbaum steht der Riegel auf Ausgang 1, aber **nicht wegen dieser Datei**:
Das eine ungeloeste Zitat ist `daten/nachmessung-zinsreihen-2026-09-05.md:6` gegen
`daten/deckungsbefund-1997.md` („Die Reihenliste nennt IWF IFS"). `zustand.hpp` kommt in
keiner der drei Fehlerlisten des Riegels vor — weder unter den ungeloesten Zitaten noch
unter den uebergangenen Fundstellen. Das ist ein Rueckstand ausserhalb dieses Pakets und
gehoert dem Datenzweig.

## Die vier Fragen des Kern-Pruefers

Der Eingriff ist kommentarrein — das ist gemessen, nicht angenommen. Der Teil des
Commits `9e46cfa`, der `zustand.hpp` betrifft, ist **ein einziger Hunk**, und die Liste
der geaenderten Zeilen ohne `///` am Anfang ist **leer**:

```
git show 9e46cfa -- …/kern/include/kern/zustand.hpp | grep -c '^@@'          → 1
… | grep -E '^[+-]' | grep -v '^[+-][+-][+-]' | grep -vE '^[+-]///'          → (leer)
```

1. **Determinismus.** Keine Zustandsfortschreibung beruehrt. Kein Gleitkomma, keine
   Iteration ueber ungeordnete Mengen, kein zweiter Zufallsstrom, keine Zeit- oder
   Adresswerte dazugekommen — es ist keine Anweisung dazugekommen.
2. **Rueckkopplungen.** Unberuehrt, aus demselben Grund.
3. **Zustandsausgabe.** Hier habe ich trotzdem nachgerechnet, weil der geaenderte
   Kommentar seit 0027 die *einzige* Dokumentation der Aggregatreihenfolge ist und ein
   falscher Kommentar den naechsten Bauagenten in die falsche Adresse schreiben laesst.
   `enum class FondsGroesse` fuehrt unveraendert `Kasse=0 … Marktanteil=4`,
   `FONDSGROESSEN` ist 5, `BASIS_FONDS` ist 254, und `stelle_fonds` rechnet
   `BASIS_FONDS + f`. Gegen `daten/adressen.md`: Zeilen 255 bis 259 fuehren
   `fonds.kasse`, `fonds.hebelstand`, `fonds.sichtbarkeit`, `fonds.anlegerbestand`,
   `fonds.marktanteil` in genau dieser Folge. Die Nullbasis des Index gegen die
   Einserbasis der Adresstabelle habe ich an der Nachbargruppe gegengeprueft:
   `BASIS_MARKT` = 252 laut `static_assert BASIS_MARKT + MARKTGROESSEN == BASIS_FONDS`,
   und die Adressen 253 und 254 sind `markt.wert` und `markt.rendite`. Die Abbildung
   stimmt an beiden Enden. Auch `spiel.md:423` nennt die fuenf in derselben Folge, nur
   mit `Positionen` und `Beteiligungen` dazwischen — der Kommentarsatz „Alle Vorgaben
   nennen dieselbe Folge" haelt.
4. **Zahlenraender.** Unberuehrt. Die Bereichswache in `stelle_fonds`
   (`f >= FONDSGROESSEN` → `festkomma::abbruch`) steht unveraendert.

Zusaetzlich uebersetzt: `g++ -std=c++20 -fsyntax-only -I kern/include
kern/include/kern/zustand.hpp` laeuft durch (nur die erwartete
`-Wpragma-once-outside-header`-Warnung, weil der Kopf als Hauptdatei uebersetzt wird).

## Wonach ich gesucht und nichts gefunden habe

- Eine dritte Doppelpunktstelle in derselben Datei oder anderswo in `kern/` und
  `pruefstand/` — keine.
- Ein Ersatzbeleg, der auf eine nicht vorhandene Ueberschrift zeigt — beide schlagen an.
- Ein Beleg, der die Doppelpunktform nur umschreibt („Zeile 477 von technik.md") statt
  sie zu ersetzen — nicht vorhanden; der alte Wortlaut ist gestrichen, nicht umgestellt.
- Ein Widerspruch zwischen dem neuen Kommentartext und der Aufzaehlung darunter — keiner;
  siehe Frage 3.
- Ein Nachziehen statt Ersetzen, wie es das Paket ausdruecklich verbietet — nicht
  geschehen; im neuen Text steht keine Nummer mehr.
- Eine Nebenwirkung auf die drei ausdruecklich ausgenommenen Stellen: der
  `daten/adressen.md`-Verweis traegt weiter die fuenf Bezeichner, die sechs
  Zeilenendkommentare in `kern/src/zustand.cpp` sind unberuehrt, und die zwei Muster des
  Riegels sind unveraendert (`belegstellen_riegel.cpp` sagt weiter „Die zwei Muster").

## Ein Vorschlag ausserhalb dieses Pakets

Beim Nachweis, *was* dieses Paket geaendert hat, bin ich haengengeblieben: Der Commit
mit dem Betreff `kernbauer: 0072-zustandhpp-doppelpunktverweise` (`2de4de7`) enthaelt
`zustand.hpp` **nicht**, und die Aenderung steckt stattdessen in `9e46cfa` mit dem
Betreff `architekt: 0051-…`. Das ist kein Fehler dieses Pakets, kostet aber jeden
Pruefer denselben Umweg und macht ein paketweises Zuruecknehmen unmoeglich. Dazu liegt
`aufgaben/0121-commit-schnitt-folgt-nicht-dem-paket.md` als `vorschlag` bereit.

## Anmerkung zur Werkstatt

Fuer den A/B-Lauf habe ich zwei Wegwerf-Arbeitsbaeume unter `$TMPDIR` angelegt und wieder
entfernt. `git worktree prune` scheitert auf diesem Dateisystem mit *Device or resource
busy* — auch fuer den fremden Rest `alt0023`, der schon vorher dalag. Die Auschecks sind
weg, nur die Notiz unter `.git/worktrees/` bleibt und ist als `prunable` markiert; kein
verfolgter Pfad ist beruehrt.
