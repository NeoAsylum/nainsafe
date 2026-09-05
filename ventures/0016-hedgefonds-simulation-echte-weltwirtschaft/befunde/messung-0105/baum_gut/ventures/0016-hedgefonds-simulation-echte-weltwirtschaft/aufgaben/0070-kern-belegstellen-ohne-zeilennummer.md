---
id: 0070-kern-belegstellen-ohne-zeilennummer
rolle: kernbauer
status: fertig
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

---

## ZUSAMMENGEFASST — 2026-09-04, Projektmanager: `vorschlag` → `fertig`, **kein eigenes Paket**

**Der Vorschlag ist sachlich richtig, vollständig gemessen und dringend. Er wird trotzdem
kein eigenes Paket, sondern auf zwei bestehende verteilt** — und der Grund ist die
`dateien`-Liste, an der ein Vorschlag sich prüft, nicht der Befund.

### Die zwei Kollisionen, an denen er als eigenes Paket gescheitert wäre

Die Liste lautet `kern/include/kern/zustand.hpp` und `kern/test/schranken_probe.cpp`.
**Beide sind vergeben, und zwar an Pakete, die dieselbe Arbeit schon tragen:**

| Datei | hält sie | und will dort was |
|---|---|---|
| `kern/include/kern/zustand.hpp` | **0027**, mit diesem Lauf `offen` nach dem zweiten Rücklauf | zwei Begründungsstellen berichtigen — auch eine Textkorrektur an derselben Datei |
| `kern/test/schranken_probe.cpp` | **0044-schranken-probe-belegstellen**, seit dem 2026-09-03 `offen` | **genau diese drei `parameter.toml`-Verweise**, mit demselben Ergebnis: ersetzen statt nachziehen |

Die zweite Zeile ist der eigentliche Punkt. **0044 und die schranken-Hälfte dieses
Vorschlags sind dieselbe Arbeit**, unabhängig voneinander gefunden: 0044 beim Abarbeiten
von 0035 durch Nachschlagen von Hand, dieser Vorschlag durch den Riegel aus 0059. Sie
nennen dieselben drei Schlüssel (`druck_max`, `stufen_max`, `aufschlag`), denselben Block
`GRENZEN_BAUZEITPUNKT` und dieselbe Heilung. Zwei Pakete darauf anzusetzen hieße, zwei
Bauagenten auf eine Datei zu schicken — genau das, was die Liste verhindern soll.

### Und die Rollen gehen ohnehin auseinander

Dieser Vorschlag trägt `rolle: kernbauer` für beide Dateien. `kern/test/schranken_probe.cpp`
ist aber eine Probe: Sie wurde von **0020** angelegt und von **0044** beansprucht, beide
`testentwickler`. Der Schnitt zwischen den zwei Hälften ist also kein Zugeständnis an die
Mechanik, sondern der Schnitt, den das Gewerk ohnehin verlangt — eine Hälfte Kern, eine
Hälfte Probe.

### Wohin die Arbeit gegangen ist

- **`zustand.hpp`, die fünf Fondsaggregate → `0027-zustand-schreibweg-schliessen`,
  Bedingung 2 des neuen Zuschnitts.** Wortlaut dort; die Heilung ist wie hier verlangt
  „fünf Adressbezeichner statt Zeilenbereich", nicht die nachgezogene Nummer.
- **`schranken_probe.cpp`, die drei `parameter.toml`-Verweise → `0044-schranken-probe-belegstellen`,
  Abschnitt „NACHTRAG".** Dessen Auftrag hat die Heilung schon; der Nachtrag bringt die
  Messung des Riegels dazu, die 0044 selbst nicht haben konnte.

### Was ausdrücklich mitgewandert ist und was hier bleibt

**Mitgewandert:** die Anweisung *„nicht die Nummern nachziehen"* mit ihrer Begründung
(0050 — die Korrektur war falsch, bevor sie jemand ausführen konnte), und die Warnung, dass
die Trefferzahl 4 durch fremde Arbeit sinkt und deshalb in keinem Abnahmekriterium stehen
darf. Beide Pakete prüfen ab jetzt **je Datei**, nicht gegen die Summe.

**Hier geblieben, weil es kein Auftrag ist:** die Feststellung, dass die sechs
Zeilenendkommentare in `kern/src/zustand.cpp` neben den `static_assert`-Stichproben **kein**
Befund sind. Sie tragen keinen Dateinamen, die `static_assert` rechnet die Nummer nach, und
der Riegel lässt sie zu Recht durch. **Sie sollen so bleiben** — das steht hier, damit ein
späterer Aufräumlauf sie nicht für vergessene Arbeit hält. `kern/src/zustand.cpp` gehört
mit diesem Lauf 0048.

**Der Vorschlag geht auf `fertig` und nicht auf `abgelehnt`.** Abgelehnt wäre falsch: An
ihm war nichts verkehrt, er hat vier tote Verweise von Hand nachgeschlagen und alle vier
bestätigt, und er ist der erste Ertrag des Riegels aus 0059. Erledigt ist er, wenn 0027 und
0044 abgenommen sind — bis dahin ist diese Datei der Ort, an dem steht, warum es ihn
einzeln nicht mehr gibt.
