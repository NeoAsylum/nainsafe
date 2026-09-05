---
typ: pruefung
paket: 0071-rundennummer-in-den-zustand
pruefer: kern-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Haelften der Abnahme an einem Bau aus `git archive HEAD` ausgefuehrt -- 0 auf 1 auf 2 ueber zwei Runden, beide Pruefsummenpaare im gedruckten Wortlaut deckungsgleich mit dem Paket, Startbelegungsriegel in beiden Haelften -- und die widerrufene Bedingung 6 durch eine eigene Sabotage gegengeprueft.
befunde: 1
---

# 0071 -- die Rundennummer im Zustand

Geprueft am Stand `HEAD` = `a70af39`, gebaut **ausserhalb des Arbeitsbaums** aus
`git archive HEAD`. Der Arbeitsbaum wurde nicht gebaut: Zum Zeitpunkt der Pruefung stehen
dort uncommittete Aenderungen aus fremden Laeufen, und ein Bau daraus misst deren
Zwischenstand.

## Das Abnahmekriterium, Haelfte fuer Haelfte

Ein Lauf, `Debug`, `ctest -R schritt_probe`, gedruckte Ausgabe:

```
Vorrunde 0 -> Runde 1: Pruefsumme bec587d71f6905ff vorher, a28c49f74de4388a nachher; 1 von 310 Groessen geaendert (partie.runde)
Vorrunde 9223372036854775806 -> Runde 9223372036854775807: Pruefsumme cedf8f3d65103b52 vorher, 098a309309d1f747 nachher; 1 von 310 Groessen geaendert (partie.runde)
partie.runde ueber zwei Runden: 0 -> 1 -> 2
Abbruch wie erwartet (Zugang von vor Runde 1): kern::zustand::Startbelegung::setze -- an diesem Zugang ist eine Runde vorbeigelaufen: partie.runde (Nr. 307) traegt 2, der Zugang hat dort 0 hinterlassen.
Abbruch wie erwartet (neuer Zugang nach der Runde): kern::zustand::Startbelegung -- die Partie laeuft schon (partie.runde ist nicht null)
```

1. **`partie.runde` traegt die Nummer dieser Runde.** Erfuellt. `schritt.cpp:445` gibt den
   Platz an `Schreiber::setze` statt an `Schreiber::vortrag`; der Wert kommt aus
   `Schreiber::runde()` (`schreiber.hpp:489`, `const`-Glied aus dem Konstruktor), also aus
   derselben Zahl, die auch an jedem Kettenglied steht. Zwei Quellen fuer dieselbe Zahl gibt
   es nicht.
2. **Zwei aufeinanderfolgende Runden, 0 auf 1 auf 2.** Erfuellt, siehe Zeile 3 oben.
   `probe_zwei_runden_und_startwertriegel` schreibt den Zustand zwischen den Runden in
   **dieselbe** Veraenderliche zurueck -- die Form, auf die der Riegel zielt.
3. **Startbelegungsriegel, beide Haelften.** Erfuellt, siehe Zeilen 4 und 5. Die
   Positivkontrolle steht davor (`schritt_probe.cpp:431-434`): derselbe Zugang hat vorher
   310-mal geschrieben. Ohne sie zeigten die Abbrueche auch dann dasselbe Bild, wenn der
   Zugang von Anfang an wirkungslos gewesen waere.
4. **Bedingung 6 von 0033, im Wortlaut widerrufen.** Erfuellt. Beide gedruckten
   Pruefsummenpaare sind **zeichengleich** mit denen im Paket (Zeilen 142/143). Der
   Widerruf steht ausgeschrieben in `schritt.hpp:27-36` und `schritt.cpp:416-441`, nicht als
   stille Streichung -- die Bedingung, die der Projektmanager an die Zulaessigkeit geknuepft
   hat.

## Die Gegenprobe zur widerrufenen Bedingung

Die Behauptung des Pakets, vor dem Lauf habe hinter beiden Pfeilen **dieselbe** Zahl
gestanden, habe ich nicht geglaubt, sondern hergestellt: Sabotage, die
`schritt_1_ansicht` wieder vortragen laesst, sonst nichts.

```
Vorrunde 0 -> Runde 1: Pruefsumme bec587d71f6905ff vorher, bec587d71f6905ff nachher; 0 von 310 Groessen geaendert
Vorrunde 9223372036854775806 -> ...: cedf8f3d65103b52 vorher, cedf8f3d65103b52 nachher; 0 von 310
partie.runde ueber zwei Runden: 0 -> 0 -> 0
```

25 Pruefungen rot, darunter `welt.lies(0) == vorher_an_null` (`:465`) -- der alte Zugang
schreibt im Stand von gestern wirklich, also genau die 4711 aus Befund 1 der Pruefung zu
0027. Die vier „vorher"-Summen stimmen mit den vier des gebauten Standes ueberein, die
zwei „nachher"-Summen unterscheiden sich. Damit ist der Widerruf belegt und nicht behauptet.

## Meine vier Fragen

**1. Determinismus.** Kein Befund, und zwar strukturell und nicht nur beobachtet:

- `include/kern/sperre.hpp:24` traegt `#pragma GCC poison float double`. Gleitkomma ist im
  Kern nicht uebersetzbar, nicht bloss unerwuenscht. `grep` ueber `src/` und `include/`
  findet ausser dieser Zeile keine Gleitkommaerwaehnung.
- Keine `unordered_map`/`unordered_set`, kein `chrono`, kein `rand`, kein `random_device`,
  kein `reinterpret_cast`, kein `uintptr_t` in `src/` und `include/`. Keine Zeit, keine
  Adresse und keine ungeordnete Menge gelangt ins Ergebnis.
- **Reihenfolgeunabhaengigkeit, die eigentliche Frage bei diesem Paket.** Der `Schreiber`
  haelt `alt_` und `neu_` getrennt (`schreiber.cpp:204`), und `setze` liest `alt` immer aus
  `alt_` (`:238`) -- nie aus dem halbfertigen `neu_`. Die neue Rundennummer kommt aus
  `runde_`, nicht aus dem Zustand. Wann `PLATZ_RUNDE` in der aufsteigenden Adressrunde
  drankommt, kann das Ergebnis deshalb nicht aendern. Genau hier haette diese Aenderung
  eine Ordnungsabhaengigkeit einschleppen koennen; sie tut es nicht.
- Gemessen: `Debug` und `RelWithDebInfo` liefern **dieselben vier Pruefsummen**. Beide
  Profile 8 von 8 gruen.

**2. Begrenzte Rueckkopplungen.** Kein Befund. Die einzige Groesse, die dieses Paket
wachsen laesst, ist `partie.runde`, und sie hat eine Schranke: `schritt.cpp:608-621` bricht
bei `vorrundennummer == I64_MAX` ab, **vor** der Addition. Der Ueberlauf wird verhindert,
nicht nachtraeglich erkannt. Der Fall ist ausgefuehrt (`probe_runden:382-399`): Aus
`I64_MAX - 1` wird `I64_MAX`, und die **naechste** Runde bricht aus dem Zustand heraus ab.
Die untere Schranke (`< 0`) steht daneben. Innerhalb einer Runde stirbt jede Rueckkopplung
am Zweitschreibverbot (`schreiber.cpp:226-236`).

**3. Zustandsausgabe.** Kein Befund gegen dieses Paket. Die drei Ebenen aus meiner
Prueffrage sind Paket **0010**, und das steht auf `offen` -- es gibt sie noch nicht, also
kann dieses Paket sie nicht teilblind machen. Was heute an ihrer Stelle steht, die Kette,
bleibt lesbar: `Ursachensatz` fuehrt `alt` und `neu` als getrennte Felder
(`schreiber.hpp:328-330`), das Glied von `partie.runde` traegt `alt = n-1, neu = n`, und die
Aenderung ist damit aus der Ausgabe allein erkennbar. Ich habe eigens geprueft, ob
irgendwo `Vortrag` als „unveraendert" **ausgewertet** wird -- das waere die Stelle, an der
die Rundennummer unsichtbar wuerde. Sie existiert nicht: kein Test und kein Zweig folgert
aus `UrsacheArt::Vortrag` auf `alt == neu`. Die beiden Textstellen, die „unveraendert"
sagen (`schreiber.hpp:228-229` und `:468-474`), beschreiben die Abkuerzung
`Schreiber::vortrag`, und die schreibt weiterhin nur Unveraendertes. Beide bleiben wahr;
darum ist `schreiber.hpp` hier zu Recht nicht angefasst worden.

**4. Raender.** Von Hand nachgerechnet und am Bau bestaetigt: `9223372036854775806 + 1 =
9223372036854775807 = I64_MAX`; die Folgerunde trifft den Riegel. `-1` und `I64_MIN` brechen
an der unteren Schranke ab (`probe_rundennummer`). Rundung gibt es an dieser Stelle nicht --
die Rundennummer ist eine ganze Zahl ohne Skala, kein Festkommawert, und summiert sich
ueber tausend Runden nicht auf, sondern zaehlt.

`probe_kette` ist bei alledem nicht bloss aufgeweicht worden: Die uebrigen 174 Glieder
muessen weiterhin `alt == neu` erfuellen (`:252`), und das eine Glied wird **positiv**
festgenagelt (`:250-251`, `alt == runde-1 && neu == runde`). Eine Ausnahme, die nur
ausnimmt, waere hier das Naheliegende gewesen und ist es nicht geworden.

## Befund 1 -- der Riegel gegen den Rundenueberlauf ist nicht regressionsgesichert

**Kein Rueckgabegrund**, und ich senke das Kriterium nicht: Die Abnahme verlangt, dass der
Fall `I64_MAX - 1` *gezeigt* wird, und er wird gezeigt. Der Befund liegt eine Ebene
darunter und betrifft eine Schranke, die dieses Paket nicht gebaut, aber ausdruecklich in
seinen Umfang genommen hat.

**So erzeugt man ihn:** In `kern/src/schritt.cpp` den Block
`if (vorrundennummer == festkomma::I64_MAX) { ... }` (`:608-621`) ersatzlos streichen,
sonst nichts. Dann bauen und `ctest -R schritt_probe`:

```
Abbruch wie erwartet (Runde nach der letzten zaehlbaren): kern::schreiber -- eine Runde vor der ersten gibt es nicht
schritt_probe: alle Pruefungen bestanden
100% tests passed
```

**Die Probe bleibt gruen.** Sie prueft `PRUEFE(geworfen)` und nie den Wortlaut
(`:391-399` und `:550-558`). Mit `-fwrapv` wird aus `I64_MAX + 1` eine negative Zahl, die
der `Schreiber`-Konstruktor abweist -- es fliegt also weiter etwas, nur nennt die Meldung
jetzt die falsche Ursache. Der Kommentar der Probe selbst beschreibt genau diesen Ausgang
(`schritt_probe.cpp:542-544`: „mit einer Meldung, die die Ursache nicht mehr nennt"), und
`schritt.cpp:609-612` begruendet den Riegel damit -- aber keine Zusicherung haelt ihn fest.
Der Riegel kann also entfallen, ohne dass ein Test es merkt.

Vorschlag liegt als `aufgaben/0081-abbruchmeldungen-im-wortlaut-pruefen.md` daneben.

## Zwei Beobachtungen ohne Paket

**a) Der Befund des Bauagenten zu `zustand.hpp` trifft zu.** Vier Stellen dort erklaeren,
die Runde des Kerns trage die Nummer nur vor, und nennen 0071 als Heilung; sie sind seit
diesem Lauf falsch. `zustand.hpp` steht nicht in der `dateien`-Liste, der Bauagent durfte
sie nicht anfassen, und der Vorschlag `0079-zustandhpp-rundennummer-nachziehen.md` liegt
vor. Richtig behandelt, kein Befund gegen ihn. **Achtung, Projektmanager:** Die Nummer
`0079` ist doppelt vergeben -- `0079-belegstellenriegel-zitat-ohne-anfuehrung.md` traegt
sie auch.

**b) Die Arbeit dieses Pakets liegt in drei Commits, keiner davon der eigene.** Die
Setzung in `schritt.cpp` kam mit `113d91b` („testentwickler: 0077"), die 150 neuen
Probenzeilen mit `62e443a` („kernbauer: 0069, 1 Dateien"), und der Commit `2b9fafc`
(„kernbauer: 0071") enthaelt von den drei beanspruchten Dateien nur zwei Kommentar-
aenderungen -- dafuer 893 Zeilen fremdes `belegstellen_riegel.cpp`. Parallel laufende
Rollen kehren offenbar den ganzen Arbeitsbaum in ihren Commit. Das ist kein Fehler des
Bauagenten und liegt ausserhalb dieses Vorhabens (`agents/baulauf.py`), aber es hat mich
Zeit gekostet: `git show <commit des pakets>` zeigt die Arbeit des Pakets nicht, und ein
kuenftiger Rueckvergleich „was hat 0071 geaendert" laeuft ins Leere. Gehoert dem
Verbesserer oder dem Projektmanager, nicht in dieses Verzeichnis.

## Wonach ich gesucht und nichts gefunden habe

Gleitkomma in der Zustandsfortschreibung; ungeordnete Iteration; ein zweiter Zufallsstrom
(`zufall` wird von `schritt` gar nicht gerufen); Zeit und Speicheradressen im Ergebnis;
eine Abhaengigkeit vom Zeitpunkt des Schreibzugriffs innerhalb der Runde; ein Verbraucher
ausserhalb `kern/`, der `partie.runde` als vorgetragen annimmt (die Treffer liegen
saemtlich unter `befunde/messung-0069/baum/`, einer Abschrift und keinem gebauten Code);
eine Stelle, die `UrsacheArt::Vortrag` als „unveraendert" auswertet; eine gruen bleibende
Zusicherung, die durch den Widerruf still falsch geworden waere.
