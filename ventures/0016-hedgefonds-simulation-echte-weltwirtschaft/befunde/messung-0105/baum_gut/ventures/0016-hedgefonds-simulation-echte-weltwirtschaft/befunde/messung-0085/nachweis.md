---
typ: messung
paket: 0085-abbruchmeldungen-im-wortlaut-pruefen
rolle: testentwickler
datum: 2026-09-05
bezugsstand: dd94ab9434bc802e8e67cb89b95c45ed9eb7ea65
ergebnis: gebaut
---

# Jede Abbruchstelle in `schritt_probe` nennt jetzt ihren Riegel

## Wie viele Stellen es sind

Die Abnahme sagt „jede Stelle, die einen Abbruch erwartet", und der Projektmanager hat
ausdruecklich verlangt, die Zahl selbst zu zaehlen. Gezaehlt auf dem Bezugsstand oben:

**Fuenf Stellen im Quelltext, sieben ausgefuehrte Erwartungen.**

| Stelle | Funktion | ausgefuehrt |
|---|---|---|
| Runde nach der letzten zaehlbaren | `probe_runden` | 1 |
| Zugang von vor Runde 1 | `probe_zwei_runden_und_startwertriegel` | 1 |
| neuer Zugang nach der Runde | `probe_zwei_runden_und_startwertriegel` | 1 |
| Modus spielmodus | `probe_spielmodus_bricht_ab` | 1 |
| Rundennummer ausserhalb des Zaehlbaren | `probe_rundennummer` | 3 |

Der Rumpf des Pakets nannte „heute vier" und zaehlte danach sechs auf. Beides trifft
nicht; der Projektmanager hat das vorweggenommen und die Zahl ausdruecklich nicht zur
Bedingung gemacht. Der Unterschied zu seiner Sechs ist `probe_rundennummer`: Das ist eine
Schleife ueber drei Nummern, also **eine** Stelle im Quelltext und **drei** ausgefuehrte
Faelle. Nach der Aenderung fuehren alle fuenf Stellen ueber denselben Aufruf, und alle
sieben Faelle pruefen den Wortlaut.

## Was gebaut wurde

`bricht_ab_mit(was, kennzeichen, zeile, tun)` in `kern/test/schritt_probe.cpp`, gerufen
ueber `BRICHT_AB_MIT`, damit die Fehlermeldung die Zeile der **Aufrufstelle** nennt und
nicht die eine Zeile in der Vorlage. Es fuehrt `tun` aus und unterscheidet drei Ausgaenge:
kein Abbruch, Abbruch mit fremdem Wortlaut, Abbruch mit dem erwarteten. Alles am Wortlaut
geschieht **innerhalb** des Fangblocks -- `what()` zeigt in die Ausnahme, und die ist
hinter der schliessenden Klammer fort.

Verglichen wird nicht der ganze Wortlaut, sondern eine kleine Menge Textstuecke je Stelle.
Der Grund steht im Paket: Ein Volltextvergleich ginge bei jeder Umformulierung rot und
erzoege dazu, die erwartete Zeichenkette nachzuziehen statt hinzusehen.

Die Wahl der Stuecke folgt einer Regel und keiner Liste: **je ein Stueck fuer den Kasten,
der geworfen hat, und eins fuer die Ursache, die ihn vom Nachbarriegel trennt.** Der
Kastenname allein reicht an keiner der beiden `Startbelegung`-Stellen, weil er in beiden
Meldungen steht; die Ursache allein reicht an den negativen Rundennummern nicht, weil der
Halbsatz ueber die Runde vor der ersten wortgleich auch im Fangnetzriegel des `Schreiber`
steht.

| Stelle | erwartete Stuecke |
|---|---|
| Runde nach der letzten zaehlbaren | `kern::schritt`, `groesste int64_t` |
| Zugang von vor Runde 1 | `kern::zustand::Startbelegung::setze`, `eine Runde vorbeigelaufen` |
| neuer Zugang nach der Runde | `kern::zustand::Startbelegung`, `die Partie laeuft schon` |
| Modus spielmodus | `kern::schritt`, `spielmodus`, `310`, `kein Paket` |
| `partie.runde = -1` | `kern::schritt`, `damit negativ` |
| `partie.runde` = kleinster int64_t | `kern::schritt`, `damit negativ` |
| `partie.runde` = groesster int64_t | `kern::schritt`, `groesste int64_t` |

Die drei hinteren Stuecke beim `spielmodus` standen vorher schon da (Bedingung 7 aus 0033:
die Meldung muss sagen, warum). Sie sind unveraendert uebernommen und nur um den
Kastennamen ergaenzt -- abgeschwaecht wurde nichts.

Bei `probe_rundennummer` haengt die Erwartung **am Fall und nicht an der Schleife**
(`Rundenfall`-Tabelle). Das ist keine Formsache: Die beiden negativen Nummern sterben an
einem anderen Riegel als `I64_MAX`, und eine Schleife mit einer gemeinsamen Erwartung
koennte den Unterschied nicht sehen. Sabotage 2 unten macht genau das sichtbar.

Ein Aufruf ohne Kennzeichen zaehlt als fehlgeschlagen. Sonst waere das leere Feld der
bequeme Weg zurueck zu genau der Pruefung, die dieses Paket abschafft.

## Der Nachweis: drei ausgefuehrte Sabotagen

Gebaut und gelaufen mit dem Testprofil (`kern_geprueft`, also
`-fsanitize=undefined,address`) in einem eigenen Bauverzeichnis unter `$TMPDIR`.

### Ausgangslage

`schritt_probe` gruen, alle sieben Faelle mit ihrem Wortlaut gedruckt. Danach die zwoelf
Proben, die heute uebersetzen: `100% tests passed, 0 tests failed out of 12`.

### Sabotage 1 -- die vom Paket verlangte

Der Block `if (vorrundennummer == festkomma::I64_MAX)` in `kern/src/schritt.cpp` ersatzlos
gestrichen. Vorher blieb die Probe darunter gruen; jetzt:

```
FEHLGESCHLAGEN Zeile 485: Runde nach der letzten zaehlbaren -- es hat abgebrochen, aber der falsche Riegel.
  erwartetes Textstueck: "kern::schritt"
  angekommene Meldung:   "kern::schreiber -- eine Runde vor der ersten gibt es nicht"
FEHLGESCHLAGEN Zeile 646: partie.runde = groesster int64_t -- es hat abgebrochen, aber der falsche Riegel.
  erwartetes Textstueck: "kern::schritt"
  angekommene Meldung:   "kern::schreiber -- eine Runde vor der ersten gibt es nicht"
```

Rot, und die rote Zeile nennt beide Zeichenketten. Rot werden **genau die zwei** Faelle,
die diesen Riegel erwarten; die uebrigen fuenf bleiben gruen. Damit ist auch gezeigt, dass
die Sicherung nicht pauschal anschlaegt.

### Sabotage 2 -- der Nachbarriegel, zur Probe auf die Falltabelle

Der Block `if (vorrundennummer < 0)` gestrichen. Er faellt nicht unter die Abnahme, ist
aber die Gegenprobe darauf, dass die Erwartung wirklich je Fall gilt und nicht je Schleife:

```
FEHLGESCHLAGEN Zeile 646: partie.runde = -1 -- kein Abbruch.
  erwartet war eine Meldung mit: "kern::schritt"
  angekommen ist:         (nichts, der Aufruf kam durch)
FEHLGESCHLAGEN Zeile 646: partie.runde = kleinster int64_t -- es hat abgebrochen, aber der falsche Riegel.
  erwartetes Textstueck: "kern::schritt"
  angekommene Meldung:   "kern::schreiber -- eine Runde vor der ersten gibt es nicht"
```

Drei Dinge auf einmal: Beide Fehlerausgaenge des Aufrufs feuern (kein Abbruch, falscher
Riegel), der dritte Fall derselben Zeile bleibt gruen, und die beiden negativen Nummern
sterben nachweislich verschieden -- bei `-1` wird `diese_runde` null und der `Schreiber`
nimmt sie an, bei `I64_MIN` bleibt sie negativ und er weist sie ab. Ohne den aeusseren
Riegel laeuft eine Runde mit `partie.runde = -1` also **still durch**. Das ist kein Befund
gegen `kern::schritt` -- der Riegel steht ja --, aber es ist der Grund, warum die
Erwartung nicht an der Schleife haengen darf.

### Sabotage 3 -- die beiden `Startbelegung`-Haelften gegeneinander

Die erwarteten Stuecke der beiden Haelften in der Probe **vertauscht**. Beide werfen
weiterhin, beide aus `Startbelegung`, beide `std::domain_error` -- eine Pruefung auf den
Kastennamen allein bliebe gruen. Sie werden rot:

```
FEHLGESCHLAGEN Zeile 551: Zugang von vor Runde 1 -- es hat abgebrochen, aber der falsche Riegel.
  erwartetes Textstueck: "die Partie laeuft schon"
  angekommene Meldung:   "kern::zustand::Startbelegung::setze -- an diesem Zugang ist eine Runde vorbeigelaufen: ..."
FEHLGESCHLAGEN Zeile 558: neuer Zugang nach der Runde -- es hat abgebrochen, aber der falsche Riegel.
  erwartetes Textstueck: "kern::zustand::Startbelegung::setze"
  angekommene Meldung:   "kern::zustand::Startbelegung -- die Partie laeuft schon (partie.runde ist nicht null); Startwerte gibt es nur vor der ersten Runde"
```

(Die erste angekommene Meldung ist hier gekuerzt; im Lauf steht sie in ganzer Laenge.)

### Nach den Sabotagen

Alle drei zurueckgenommen. `git diff` auf `kern/src/schritt.cpp` ist nach jeder Ruecknahme
leer geprueft worden -- die Datei gehoert keinem Paket dieses Laufs und geht unveraendert
aus ihm hervor. Danach wieder gruen, zwoelf von zwoelf.

## Was ich nicht messen konnte, und warum

**Ein Gesamtbau lief nicht durch, aus fremder Ursache.** `werkzeuge/belegstellen/belegstellen_riegel.cpp`
und `kern/test/werte_probe.cpp` standen waehrend meines Laufs in einem Zwischenstand
zweier gleichzeitig laufender Pakete (`git status`: beide `M`, von mir nicht angefasst);
der Riegel uebersetzt in diesem Zustand nicht. Ich habe deshalb alle Ziele ausser diesen
beiden gebaut und alle zwoelf uebrigen Proben laufen lassen. Es ist **kein Befund** --
weder gegen jene Pakete, die noch mitten in der Arbeit sind, noch gegen dieses.

Die Folge fuer den Pruefer: Der Belegstellenriegel hat diese Datei in meinem Lauf nicht
gelesen. Neue Belegstellen habe ich keine gesetzt; die vorhandenen Verweise auf
`kern/src/schritt.cpp` standen schon da und sind unveraendert, und Zeilennummern nennt die
Datei keine.

**Der Determinismustest ueber Speichern und Laden fehlt weiterhin.** Er steht nicht in
diesem Paket. `probe_zweimal_dasselbe` deckt nur zwei Aufrufe im selben Prozess ab.
