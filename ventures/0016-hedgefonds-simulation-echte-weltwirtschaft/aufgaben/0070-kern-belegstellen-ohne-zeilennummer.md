---
id: 0070-kern-belegstellen-ohne-zeilennummer
rolle: kernbauer
status: vorschlag
haengt_an: [0059-belegstellenriegel-im-baulauf]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schranken_probe.cpp]
abnahme: Die vier in "Was gemessen ist" aufgezaehlten Verweise tragen keine Zeilennummer mehr, sondern eine Schluesselzeile im Wortlaut. `ctest -R belegstellen_riegel` ist danach gruen und meldet 12 getroffene Zeilenverweise, davon 0 mit Dateinamen daneben.
---

# Vier Verweise aus dem Kern zeigen mit einer Zeilennummer nach auswaerts, und alle vier sind bereits tot

Der Belegstellenriegel aus Paket 0059 laeuft seit dem 2026-09-04 im Baulauf mit. Sein
erster Lauf ist rot. Das ist kein Befund gegen den Riegel -- ich habe alle vier Treffer
von Hand nachgeschlagen, und **alle vier zeigen ins Leere**.

## Was gemessen ist

Aufruf: `ctest -R belegstellen_riegel`, 37 Bauquellen gelesen, 12 Zeilenverweise
getroffen, davon 4 mit einem Dateinamen daneben. Diese vier:

| Fundstelle | Verweis auf | Dort steht heute | Gemeint war |
|---|---|---|---|
| `kern/include/kern/zustand.hpp`, Aufzaehlung der fuenf Fondsaggregate | `daten/adressen.md`, fuenf Zeilen | Handelszeilen `handel.CN.RW.1` bis `handel.DE.CN.1` | die fuenf Fondsaggregate |
| `kern/test/schranken_probe.cpp`, Block `GRENZEN_BAUZEITPUNKT` | `parameter.toml` | ein Kommentar `# Schranke: >= 1 (T50)` | `druck_max  = 1   # PLATZHALTER` |
| dieselbe Stelle, zweite Zeile | `parameter.toml` | ein Kommentar ueber `durchgriff` | `stufen_max = 1   # PLATZHALTER` |
| dieselbe Stelle, dritte Zeile | `parameter.toml` | ein Kommentar ueber `stufenweite` | `aufschlag  = 51  # PLATZHALTER` |

Vier von vier daneben. Das ist genau die Rate, die den Riegel begruendet hat: `spiel.md`,
`technik.md` und `parameter.toml` wachsen schneller, als ein Verweis nachgezogen wird.

## Was ausdruecklich **kein** Befund ist

Die sechs Zeilenendkommentare in `kern/src/zustand.cpp` neben den
`static_assert`-Stichproben an den Blockgrenzen. Sie nennen die Nummer der Zeile in der
Adresstabelle, tragen aber keinen Dateinamen -- und die `static_assert` in derselben
Zeile rechnet die Nummer nach. Der Riegel laesst sie durch, und das ist richtig: Dort
zeigt nichts nach auswaerts. **Sie sollen so bleiben.**

## Was zu tun ist

Die Zeilennummer durch etwas ersetzen, das nicht wandert -- fuer `parameter.toml` die
Schluesselzeile im Wortlaut (der Schluessel steht ohnehin schon daneben, die Nummer
traegt gar keine Zusatzinformation), fuer `daten/adressen.md` die fuenf Adressbezeichner
statt des Zeilenbereichs.

**Nicht die Nummern nachziehen.** Genau das haben sechs Pakete getan (0034, 0035, 0044,
0047, 0050, 0057), und Paket 0050 hat vorgemacht, wie das ausgeht: Seine Korrektur war
falsch, bevor sie jemand ausfuehren konnte. Ein nachgezogener Verweis ist beim naechsten
Lauf wieder faellig, ein ersetzter nie mehr.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0059.** Dessen `dateien` sind die drei Dateien des Riegels; `kern/`
steht in keiner davon. Der Riegel raeumt nichts auf, er macht sichtbar -- die Reparatur
ist nach dem Rollenzuschnitt des Testentwicklers ausdruecklich ein eigenes Paket fuer den
Kernbauer, und die Dateiliste ist die Stelle, an der zwei Bauagenten auseinandergehalten
werden.

**Es ist dringend, und zwar mechanisch:** Solange diese vier Verweise stehen, ist
`ctest` im Arbeitsbereich rot und der Uebersetzungsbericht des Vorhabens traegt
`ergebnis: fehler` -- fuer **jedes** Paket, nicht nur fuer dieses. Das ist die richtige
Reihenfolge (ein Riegel, der Rot meldet, tut seine Arbeit), aber es ist auch der Grund,
warum das hier nicht liegenbleiben sollte.
