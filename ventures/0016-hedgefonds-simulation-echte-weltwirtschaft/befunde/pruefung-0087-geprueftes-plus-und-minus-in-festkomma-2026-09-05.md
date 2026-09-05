---
typ: pruefung
paket: 0087-geprueftes-plus-und-minus-in-festkomma
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln -- die beiden Gestaltbedingungen mechanisch am Quelltext, die Nachweisbedingung durch fuenf eigene Mutationen an `festkomma.hpp`, jede einzeln gebaut und gefahren, jede rot an der erwarteten Zeile.
befunde: 0
---

# Woran gemessen wurde

Alles auf einem frischen Export ausserhalb des Repos
(`git archive HEAD ventures/0016-... specs decisions`), nicht im Arbeitsbaum -- der
traegt Pruefbaeume fremder Pakete unter `bau/`. Uebersetzer g++ 15.2.0, also die in
`werkzeugkette.cmake` festgenagelte Fassung.

| Bauweg | Profil | Ergebnis |
|---|---|---|
| `kern` allein | `FABRIK_SANITIZER=ON` | 10 von 10 gruen |
| `kern` allein | `FABRIK_SANITIZER=OFF` | 10 von 10 gruen |
| Arbeitsbereich | `FABRIK_SANITIZER=ON` | 13 von 14 gruen, `belegstellen_riegel` rot (unten) |

`festkomma_probe` gibt in beiden Profilen dieselbe Zeile aus
(`kern::festkomma -- alle Proben bestanden.`).

# Die drei Bedingungen, einzeln

**1 -- `plus` und `minus` stehen als geprueftes Paar in `festkomma.hpp` neben `mal`.**
Erfuellt. Die Reihenfolge der Definitionen in der Datei: `teile_gerundet` (135),
`mal_geteilt` (155), `plus` (199), `minus` (215), `mal` (258). Beide sind `constexpr`,
beide ueber `__builtin_add_overflow`/`__builtin_sub_overflow` gebaut, beide mit
Abbruch statt Kappung -- also Massnahme 4.2 im Wortlaut von `technik.md` T7, und im
Dateiaufbau vor 4.3.

**2 -- `werte.cpp` hat keine eigene Fassung mehr.** Erfuellt. In `werte.cpp` stehen
nur noch vier `using`-Zeilen (55--58), keine Definition. Die staerkere Messung ist
eine Mengenaussage statt einer Stichprobe: Die beiden Ueberlaufbausteine kommen im
**ganzen** Kern und im Pruefstand als Code genau zweimal vor, beide in
`festkomma.hpp` (202, 218); die drei weiteren Treffer sind Zitate in Kommentaren
derselben Datei. Es gibt also keine zweite Rechenstelle, nicht nur keine in
`werte.cpp`.

Der Vergleich gegen den Vorher-Stand zeigt, dass der Umzug den Rechenweg nicht
angefasst hat: `git diff ceebee3..HEAD` auf `werte.cpp` ist ausschliesslich das
Entfernen der beiden lokalen Fassungen samt ihrer `static_assert`-Zeile; die zwoelf
Aufrufstellen sind zeichengleich. `festkomma.hpp` und `festkomma_probe.cpp` sind
gegenueber `6bea52a` **reine Zusaetze** (+58 und +111 Zeilen, null Loeschungen) --
an den vorhandenen Rechenarten kann sich damit von der Bauart her nichts geaendert
haben.

Der Meldungstext hat sich geaendert (`kern::werte::plus -- Summe ...` ->
`plus: Summe ...`). Der alte Wortlaut kommt im ganzen Repo nur noch im Logbuch des
Bauagenten und in einem eingefrorenen Messbaum unter `befunde/messung-0069/` vor,
also in keiner lebenden Quelle und in keinem Dokument.

**3 -- `festkomma_probe` weist beide Abbruchpfade an den Raendern von i64 nach, je
eine Positivkontrolle davor.** Erfuellt, und ich habe es nicht am Lesen entschieden,
sondern an fuenf eigenen Mutationen -- bewusst andere als die des Bauagenten, weil
eine Wiederholung seiner Auswahl nur seine Auswahl prueft. Jede Mutation einzeln,
jede auf einem eigenen Wegwerfbaum, Profil `ON`:

| Mutation an `festkomma.hpp` | Urteil |
|---|---|
| unveraendert (Kontrolle) | gruen |
| `plus` faengt nur den oberen Rand (`&& b > 0`) | rot (Probe), Zeile 279 |
| `minus` faengt nur den oberen Rand (`&& b < 0`) | rot (Probe), Zeile 283 |
| `plus` kappt auf `I64_MAX`/`I64_MIN` statt abzubrechen | rot (Probe), Zeilen 277 und 279 |
| beide Riegel melden denselben Text | rot (Probe), Zeilen 281 und 283 |
| `minus` bricht einen Schritt zu frueh ab | rot (Uebersetzung), `static_assert` Zeile 90 |

Die dritte und die vierte Zeile sind die beiden, auf die es ankommt. Ein Waechter,
der **kappt**, wirft nicht -- eine Probe, die nur "es ist etwas geflogen" prueft,
bliebe dabei gruen; hier faellt sie. Und ein einziger gemeinsamer Meldungstext fuer
beide Riegel ist die plausibelste Vereinfachung, die jemand spaeter vornaehme; auch
sie faellt, weil `ABBRUCH_MELDET` den Wortlaut vergleicht und die beiden Nadeln
einander nicht enthalten. Die letzte Zeile ist die Gegenprobe zur Positivkontrolle:
Ein zu vorsichtiger Waechter kommt gar nicht erst bis zum Test.

Die Raender von Hand nachgerechnet, alle vier stimmen:
`plus(I64_MAX-1, 1) = I64_MAX`, `plus(I64_MIN+1, -1) = I64_MIN`,
`minus(I64_MAX-1, -1) = I64_MAX`, `minus(I64_MIN+1, 1) = I64_MIN` -- und
`minus(-1, I64_MIN) = I64_MAX`, der eine Fall, in dem `plus(a, -b)` falsch abbraeche.
Die Positivkontrollen stehen im Quelltext **vor** den Abbruchnachweisen, sowohl im
`static_assert`-Block (84--101) als auch in `main` (258--284).

# Wonach ich sonst gesucht habe, ohne fuendig zu werden

**Determinismus.** Kein Gleitkomma, keine ungeordnete Menge, kein Zeit- oder
Adressbezug in den beiden neuen Funktionen; `__builtin_*_overflow` fragt nur ein
Bitmuster ab und wird von `-fwrapv` nicht beruehrt. Der starke Nachweis ist hier der
Doppelweg: Dieselben vier Randwerte laufen einmal beim **Uebersetzen** durch die
`constexpr`-Auswertung und einmal zur **Laufzeit** durch `undurchsichtig()` unter den
Sanitizern -- und liefern dasselbe. Beide Profile ergeben dieselbe Ausgabe.

**Rueckkopplung.** Keine: Beide Funktionen sind zustandslos und `constexpr`, sie
koennen keine Schleife schliessen.

**Geschwister.** Die eigentliche Frage hinter diesem Paket ist nicht "steht `plus`
jetzt richtig", sondern "gibt es noch eine Strichrechnung auf `i64`, die an T7 4.2
vorbeilaeuft". Suche ueber `kern/src` und `kern/include/kern`: **eine** Stelle,
`schritt.cpp:622` (`vorrundennummer + 1`). Sie ist kein Befund -- der Ueberlauf wird
zwoelf Zeilen davor **verhindert** statt nachtraeglich erkannt, mit eigener Meldung,
und haengt damit nicht an `-fwrapv`. Alles andere sind Adressrechnungen auf `Index`
und `std::size_t`. Der Kern ist an dieser Vorgabe nach diesem Paket sauber.

**Die vier Pruefungen aus 0088** in `werte_probe` sind gruen, in beiden Profilen --
ihr Zweck an dieser Stelle, naemlich der Nachweis, dass der Umzug an den siebzehn
Groessen nichts geaendert hat.

# Kein Befund von mir, aber gemessen

`belegstellen_riegel` ist am geprueften `HEAD` rot. Er gehoert **nicht** zu diesem
Paket, und das ist gemessen und nicht geschlossen: Auf einem zweiten Baum aus
demselben `HEAD`, bei dem allein die drei Dateien dieses Pakets auf ihren
Vorher-Stand zurueckgedreht sind (`6bea52a`, `6bea52a`, `ceebee3`), meldet er Zahl
fuer Zahl dasselbe -- 36 Zitate gefunden, 35 aufgeloest, 47 Fundstellen uebergangen,
dieselbe eine offene Fundstelle `daten/nachmessung-zinsreihen-2026-09-05.md:6`. Die
liegt seit heute als Paket `0120-abschnittszitat-nachmessung-zinsreihen` vor
(die Nummer ist an diesem Tag mehrfach vergeben, der Name traegt); ich lege dafuer
keinen zweiten Vorschlag an.

Nebenbefund aus derselben Gegenprobe: Der zurueckgedrehte Baum uebersetzt und laeuft
gruen. Das bestaetigt unabhaengig, was der Bauagent selbst hingeschrieben hat --
Bedingung 2 ist heute durch keine Messung gesichert. Daraus wird Vorschlag 0122.

# Zwei Vorschlaege

* **0122** -- die beiden Ueberlaufbausteine in `sperre.hpp` vergiften, damit
  Bedingung 2 kein Lesebefund mehr ist. Gebaut und an beiden Seiten gemessen, bevor
  ich ihn abgegeben habe.
* **0123** -- der Kopf von `mal` in `festkomma.hpp` sagt "Heute ohne Aufrufer ...
  weil `kern::werte` nicht gebaut ist". Beides ist seit Paket 0002 falsch; `mal` hat
  fuenf Aufrufer in `werte.cpp`.

Beide sind ausserhalb der Abnahme dieses Pakets und keine Minderung des Urteils.
