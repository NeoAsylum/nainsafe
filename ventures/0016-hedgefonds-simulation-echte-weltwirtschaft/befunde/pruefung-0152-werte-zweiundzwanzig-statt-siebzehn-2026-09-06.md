---
typ: pruefung
paket: 0152-werte-zweiundzwanzig-statt-siebzehn
pruefer: kern-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Alle fuenf Abnahmebedingungen einzeln mit eigenem mechanischem Aufruf -- Kopfzaehlung gegen die T48-Tabelle, beide Stelligkeiten von Nr. 11, ein Mutantensatz aus acht Faellen fuer die vier Zeilen von Nr. 22 und fuer Nr. 21, ctest in beiden Bauprofilen und in beiden Bauwegen, und die vier Sollwerte von Hand nachgerechnet.
befunde: 0
---

# Pruefung des Pakets 0152

## Gegenstand und Stand

Geprueft wurde der Stand `5bb537594072469322af4af7f2804319627f13e6`
(*„kernbauer: 0152-werte-zweiundzwanzig-statt-siebzehn (5 Dateien)", Lauf 1627,
2026-09-06 02:14:44 +0200*). Er ist zugleich der Arbeitsstand: `git status` meldet fuer
`kern/` nichts.

md5 der drei Paketdateien, zu Beginn und am Ende dieses Laufs unveraendert:

| Datei | md5 |
|---|---|
| `kern/include/kern/werte.hpp` | `1d65eaa910d63a39615393b4536fafa4` |
| `kern/src/werte.cpp` | `ea29677fc1935332a7a7a3cb5b455acb` |
| `kern/test/werte_probe.cpp` | `7ca7b7a27b8e67f381165feaec5f4a1e` |

Gebaut und gemessen wurde nicht im Arbeitsbaum, sondern in einem frischen Baum aus
`git archive` dieses Standes, unter `befunde/bau-pruefung-0152/`. Dieses Verzeichnis
faellt unter `.gitignore` Zeile 246 (`ventures/**/bau-*/`) und geht nicht mit in den
Bestand -- **alle Zahlen stehen deshalb hier in diesem Befund** und nicht nur dort.

## Der Mutantensatz

Aus dem Baum oben wurden `kern/` und `werkzeugkette.cmake` nach `mutant/` abgeschrieben,
Bauverzeichnis `mbau`, `Debug`, `FABRIK_SANITIZER=OFF`, Ziel `werte_probe`. Geaendert
wurde je Fall **genau eine** Stelle in `mutant/kern/src/werte.cpp`, danach zurueckgesetzt.

| Fall | Aenderung | Ergebnis |
|---|---|---|
| m0 | keine (Kontrollbaum) | **gruen**, Code 0, leere Ausgabe |
| m1 | Zollzeile nimmt `handelsvolumen(z, land)` statt `handelsvolumen(z, land, sektor)` | **rot**, 2 -- Zeile 1576 und 1646, `schaden(… Zoll) == 440'000` |
| m2 | Leitzinszeile nimmt `bip` statt `schuld` | **rot**, 1 -- Zeile 1621, `== 3'000` |
| m3 | Haushaltszeile nimmt `hub(…, Leitzins)` statt `hub(…, Haushalt)` | **rot**, 2 -- Zeile 1627 und 1660, `== 6'000` |
| m4 | Regulierungszeile nimmt das Literal `7` statt `konst.regulierung_last` | **rot**, 2 -- Zeile 1638 (`doppelt`) und 1642 (`ohne`) |
| m5 | `default:` vor `case Instrument::Zoll` -- das fuenfte Instrument faellt in die Zollzeile statt abzubrechen | **rot**, 3 -- Zeile 1665, 1668, 1669 |
| m6 | Nr. 21 additiv: `plus(weltpreis, zoll)` statt `mal_geteilt(weltpreis, plus(10'000, zoll), 10'000)` | **rot**, 3 -- Zeile 1465, 1466, 1477 |
| m7 | Nr. 21 liest fuer die Restwelt den Zollstand von DE statt der Null | **rot**, 2 -- Zeile 1482 und 1483 |
| m0b | Ruecksetzung | **gruen**, Code 0; `diff` gegen die Paketdatei leer |

Jede der vier Zeilen von Nr. 22 hat damit ihren eigenen roten Fall, und keine faellt mit
einer anderen zusammen. m0 und m0b sind der Nachweis, dass der Apparat nicht alles rot
macht: Der Kontrollbaum ist am Ende byteweise wieder die Paketdatei und trotzdem gruen.

## Bedingung 1 -- Nr. 21 und Nr. 22 oeffentlich, `menge` und `verschiebung` nicht

**Erfuellt.**

`weltpreis_mit_zoll` steht in `werte.hpp:442`, `schaden` in `werte.hpp:482`, beide hinter
Nr. 20 und damit in der Reihenfolge der T48-Tabelle. Beide tragen die Kommentarform der
Nummern 1 bis 20: fette Nummer, die Formel im Wortlaut von `technik.md`, die T5-Klasse.
Nachgezaehlt: eine Suche nach `^/// \*\*T48 Nr\. [0-9]+` liefert 23 Marken in der Folge
1…10, 11, 11, 12…22 -- also lueckenlos und in Tabellenordnung.

`menge` und `verschiebung` als Groessen gibt es nirgends. Eine Suche nach
`\b(menge|verschiebung)\s*\(` ueber das ganze `kern/` trifft **eine** Stelle:
`werte.hpp:445`, die Zeile, die die T48-Formel zitiert. Keine Deklaration, keine
Definition, auch nicht im anonymen Namensraum von `werte.cpp` -- die vier Zeilen stehen
unmittelbar in `schaden`.

*Zwei Lesarten, und die gewaehlte:* Die Bedingung sagt „eine Suche nach beiden Namen im
oeffentlichen Teil des Kopfes, die leer ausgeht". Woertlich geht sie **nicht** leer aus --
`werte.hpp:175` hat `zustand::i64 menge` als Argumentnamen von Nr. 1, und das ist der
Name, den T48 der Formel `wert(menge, kurs, g)` selbst gibt; `marktkorb` hat `mengen`.
Beide standen vor diesem Paket dort und sind keine Groessen. Gemeint ist ersichtlich die
Suche nach einer *Deklaration* dieses Namens, und die geht leer aus.

## Bedingung 2 -- Nr. 11 in beiden Stelligkeiten, die einstellige aus der zweistelligen

**Erfuellt.**

Die Richtung stimmt und ist am Quelltext ablesbar, nicht nur an der Zahl:
`werte.cpp:719` fuehrt die Bereichspruefung des Gebiets, den Sektorriegel und die
Gegenuebertabelle; `werte.cpp:735` summiert allein ueber `SEKTORLISTE_HANDELBAR` und ruft
dabei die zweistellige Fassung. Die einstellige liest keine Adresse selbst.

Die Probe `probe_handelsvolumen_beide_stelligkeiten` legt fuer DE acht Handelsadressen je
Sektor auf 5.000.000 und 12.500.000 und haelt beide Fassungen gegeneinander **und** gegen
ausgeschriebene Zahlen. Von Hand nachgerechnet: vier Gegenueber mal zwei Richtungen sind
acht Adressen, also 40.000.000 und 100.000.000, zusammen 140.000.000 -- genau die drei
Zahlen der Probe. Die beiden Sektorwerte sind absichtlich verschieden, sonst bestuende die
Summe auch gegen eine Fassung, die einen Sektor doppelt zaehlt.

Bestand: `handelsvolumen` hat ausserhalb der drei Paketdateien keinen Aufrufer -- die
Suche ueber das Vorhaben trifft nur `werte.hpp`, `werte.cpp`, `werte_probe.cpp` und
Textdateien (die uebrigen Treffer liegen in abgelegten Messbaeumen unter `befunde/`).
Der einzige Leser der einstelligen Fassung ist Nr. 4 (`waehrungswert`), und der
uebersetzt unveraendert. Der ganze Arbeitsbereich baut ohne eine einzige Warnung.

## Bedingung 3 -- die vier Zeilen von Nr. 22, einzeln nachgewiesen

**Erfuellt**, und zwar nicht nur nach Augenschein: Zu jeder der vier Zeilen gibt es einen
Mutanten, der genau sie verdirbt und die Probe rot macht, und dazu einen unveraenderten
Kontrollbaum, der gruen bleibt (`mutanten.md`, m0 bis m5, m0b).

Die vier Sollwerte im Quelltext habe ich unabhaengig nachgerechnet, mit der Rundungsregel
aus T6 (halbe Betraege von null weg) und den `durchgriff`-Werten aus `K_ZOLL`
(DE: 7.288 und 5.464):

| Zeile | Rechnung | Soll |
|---|---|---:|
| `zoll` | `hub = |430−380| = 50`; `keilhub(1) = 11.000·50/10.000 = 55`, `preishub(1) = 55·7.288/10.000 = 40,084 → 40`; `keilhub(2) = 10.400·50/10.000 = 52`, `preishub(2) = 52·5.464/10.000 = 28,4128 → 28`; `40.000.000·40/10.000 = 160.000` plus `100.000.000·28/10.000 = 280.000` | 440.000 |
| `leitzins` | `schuld = 1.000.000·6.000/10.000 = 600.000`; `hub = |300−250| = 50`; `600.000·50/10.000` | 3.000 |
| `haushalt` | `bip = 200.000+300.000+500.000 = 1.000.000`; `hub = |40−100| = 60`; `1.000.000·60/10.000` | 6.000 |
| `regulierung` | `hub = |5−2| = 3`; `3·7 = 21`; `1.000.000·21/10.000` | 2.100 |

Alle vier stimmen mit den Zahlen im Quelltext ueberein. Der Haushaltsfall laeuft
absichtlich abwaerts (100 → 40) und belegt damit, dass `hub` der Betrag ist. Zustand B --
Zollstand unveraendert bei bewegten Weltpreisen -- ergibt exakt null, mit der Gegenprobe
voran, dass die Weltpreise sich sehr wohl bewegt haben.

Das fuenfte Instrument bricht ab: `werte.cpp:996` hinter dem `switch`, mit
`festkomma::abbruch`, das nach `festkomma.hpp:62` `[[noreturn]]` ist. Die Meldung nennt
`kern::werte::schaden` und die Kennung 9, und die Probe prueft zusaetzlich, dass sie
`kern::werte::hub` **nicht** nennt. `Instrument` ist nach `zustand.hpp:141` ein
`enum class ... : std::uint8_t`, der Testwert 9 also darstellbar und der Fall definiert.
Mutant m5 (`default:` vor der Zollzeile) macht die Probe rot -- der Nachweis ist echt.

Die Regulierungszeile liest `konst.regulierung_last` und kein Literal. Die Probe belegt
das in beide Richtungen (doppelter Satz verdoppelt, Satz null macht stumm), und Mutant m4
-- Literal `7` an derselben Stelle -- faellt an genau diesen zwei Zeilen.

## Bedingung 4 -- der Zaehlnachweis aus T48

**Erfuellt.**

Eine Suche nach `siebzehn` in `werte.hpp` geht leer aus. An den vier genannten Stellen
steht jetzt `zweiundzwanzig` (Zeile 2, 16, 29, 152), dazu an zwei weiteren, die den Satz
mitfuehren (Zeile 39, 41).

Zwei unabhaengige Zaehlungen des Kopfes:

* `^\[\[nodiscard\]\]` → **23** Deklarationen
* `^/// \*\*T48 Nr\. N` → **23** Marken, davon **22** verschiedene Nummern (Nr. 11 zweimal)

*Zwei Lesarten, und die gewaehlte:* Woertlich verlangt die Bedingung, dass „die Zahl der
Deklarationen ausserhalb von `intern`" mit dem Zahlwort uebereinstimmt -- das waeren 23
gegen zweiundzwanzig. Diese Lesart ist mit Bedingung 2 desselben Pakets nicht zugleich
erfuellbar, denn die verlangt die zweite Stelligkeit. Sie ist ausserdem gegen die Vorgabe:
`technik.md` Zeile 2139--2145 nennt die beiden Fassungen ausdruecklich *„nicht zwei
Definitionen desselben Namens, sondern eine Definition und ihre Aggregation"*, und Zeile
2188--2192 zaehlt **zweiundzwanzig Namen**. Gezaehlt werden also Nummern, nicht Zeilen.
Genau das steht seit diesem Paket auch im Kopf selbst (Zeile 32--37), und die Zahl dort
ist damit nachgezaehlt und nicht uebernommen. Ein `namespace intern` gibt es in
`werte.hpp` nicht; alle 23 Deklarationen sind oeffentlich.

Das woertlich zitierte Stueck T48 im Kopf habe ich gegen `technik.md` gehalten -- es ist
wortgleich.

## Bedingung 5 -- der Bestand bleibt gruen

**Erfuellt.** Alles in einem frischen Baum aus `git archive` des Bau-Standes, mit `specs`
und `decisions`.

| Lauf | Ergebnis |
|---|---|
| Arbeitsbereich, `FABRIK_SANITIZER=OFF`, `ctest` | 18 von 18 bestanden, 5,0 s |
| Arbeitsbereich, `FABRIK_SANITIZER=ON`, `ctest` | 18 von 18 bestanden, 8,1 s |
| Alleinbau `kern/`, `OFF`, `ctest -R werte_probe` | 1 von 1 bestanden |
| beide Uebersetzungen | **null** Zeilen mit `warning` oder `error` |

Darin enthalten: `belegstellen_riegel` (0,29 s), `bezeichner_riegel` (0,13 s),
`schlussriegel_nachbau` (4,50 s), alle bestanden. Der Sperrebindungsriegel laeuft beim
Konfigurieren und meldet *„10 Kernquelle(n) und 12 Probe(n) geprueft, jede bindet
`kern/sperre.hpp` als letzten #include"*; das Konfigurieren endete mit Code 0. Dazu der
Warnsatz-Schlussriegel mit 20 uebersetzenden Zielen und 340 Schaltereintraegen.

Ausserhalb der drei Paketdateien hat der Commit **keine Quelldatei** angefasst. Die beiden
uebrigen Eintraege des Commits sind `notizen/kernbauer.md` und die eine Zeile
`status: offen` → `gebaut` in der Paketdatei selbst. Beides ist die stehende Form jedes
Baulaufs -- ich habe es an `0151` (`e0682a1`) und `0156` (`9fd8c3f`) gegengeprueft, beide
tun genau dasselbe.

## Die vier Fragen dieser Rolle

**1. Determinismus.** Kein Gleitkomma: `float`, `double`, `long double` kommen in
`werte.cpp` nicht vor. Keine ungeordnete Menge: Die zwei neuen Schleifen laufen ueber
`SEKTORLISTE_HANDELBAR` und `GEGENUEBER[g]`, beides `constexpr std::array` mit fester
Ordnung (`werte.cpp:310` und `:350`). Kein Zufall, keine Zeit, keine Adresse im Ergebnis.
Der uebliche Profilvergleich der Probenausgabe traegt hier nichts: `werte_probe` schweigt
im Erfolgsfall, beide Ausgaben sind leer.

Eine Stelle habe ich eigens angesehen und fuer harmlos befunden: Nr. 11 addiert seit
diesem Paket in anderer Gruppierung als vorher -- erst alle Gegenueber eines Sektors, dann
der zweite Sektor, statt beide Sektoren je Gegenueber. Dieselben 16 Summanden, dieselbe
Summe; unterscheiden koennte sich nur, ob ein Zwischenwert `plus` zum Abbruch bringt, und
das ist bei diesen Groessenordnungen kein Fall. Die Umgruppierung ist genau das, was die
Vorgabe verlangt.

**2. Rueckkopplungen.** Nr. 22 ist ein Baustein und keine Schleife; die Schranke der
Lobbyschleife (`druck_max`) sitzt in Gegenkraft 5, die noch nicht gebaut ist. Innerhalb
des Pakets waechst nichts unbegrenzt still: `plus` und `mal` sind die geprueften
Fassungen aus `festkomma`, `mal_geteilt` rechnet ueber `i128`. Ein Ueberlauf bricht ab,
er wickelt sich nicht.

**3. Zustandsausgabe.** Von diesem Paket nicht beruehrt und richtig so: Nr. 21 und Nr. 22
sind abgeleitete Groessen und keine der 310 Adressen, sie gehoeren nach T48 ausdruecklich
nicht in den Zustand. `zustandsausgabe.cpp` ist unveraendert.

**4. Raender.** Nenner ist ueberall das Literal 10.000, nie null. Die Bereichspruefungen
melden unter dem Namen der Groesse und liegen vor der Rechnung; der Riegel gegen die
Restwelt steht in `schaden` vor der Zollzeile, was die Probe eigens fuer eine Zeile mit
und eine ohne Sektorschleife nachweist. Rundung: beide Stufen von Nr. 20 runden einzeln,
und das ist die Vorgabe -- ich habe die zusammengezogene Form nicht verlangt.

Einen Rand habe ich gefunden, der niemandem gehoert: `weltpreis_mit_zoll` bildet
`plus(10.000, zollstand)` ohne Untergrenze. Gemessen mit einem Zusatzpruefsatz in der
**Abschrift** der Probe, gegen einen unveraenderten `werte.cpp` -- beide Zusicherungen
halten, der Lauf ist gruen:

```
zollstand(DE) = -12'000, welt.preis.1 = 11'000  ->  weltpreis_mit_zoll = -2'200
zollstand(DE) = -10'000, welt.preis.1 = 11'000  ->  weltpreis_mit_zoll =      0
```

Kein Abbruch, keine Meldung. Das ist die Formel aus T48 Zeichen fuer Zeichen, das Paket
hat sie so bestellt, und keine Abnahmebedingung spricht davon. Es ist deshalb kein Grund
zurueckzugeben, aber es ist ein eigenes Paket: Vorschlag `0172`.

## Was ich gesucht und nicht gefunden habe

Damit die Pruefung von einer, die nicht stattfand, unterscheidbar bleibt: gesucht wurde
nach einem stillen Rueckgriff auf die Vorrunde (Nr. 21 nimmt einen `Zustand`, und das ist
begruendet -- die Marktraeumung sucht den Weltpreis gerade erst, es gibt dort weder alt
noch neu); nach einer Zeile von Nr. 22, die die Menge oder den Hub einer anderen nimmt
(vier Mutanten, alle rot); nach einem Literal statt des Parameterschluessels (m4, rot);
nach einer stillen Aufnahme des fuenften Instruments (m5, rot); nach einer zweiten
Definition des Handelsvolumens statt einer Aggregation (nicht der Fall, am Quelltext);
nach einem verschobenen Zaehlnachweis (23 gegen 22, beide Zaehlungen unabhaengig);
nach einer Abweichung der Formeln von T48 und `spiel.md` (Zeichen fuer Zeichen gleich);
nach Gleitkomma und ungeordneter Iteration (keines); nach einem Aufrufer, der nicht mehr
uebersetzt (keiner).

## Zwei Meldungen, die kein `zurueck` sind

**Der Definitionsbereich von Nr. 21 ist weiterhin offen, und der Vorbehalt steht richtig
im Kommentar.** Das Paket hat genau das verlangt. Ein Fund fuer den Geschaeftsfuehrer, der
in `technik.md` Zeile 3262--3269 noch nicht steht: `spiel.md` Zeile 331 schreibt die
Formel als `weltpreis_mit_zoll(**l**, s)`, `technik.md` T48 Zeile 2094 als
`weltpreis_mit_zoll(**g**, s)`. Die beiden Vorgaben sind an dieser Stelle nicht nur
schweigsam, sondern uneins. Das entscheidet der Entwurf und nicht der Bau.

**Ein Kommentar ist beim Herausziehen von `pruefe_handelssektor` verrutscht.**
`werte.cpp:389--397` beschreibt `pruefe_landessektor` („Land und Sektor der beiden
Zollkeilgroessen"), steht seit diesem Paket aber ohne Leerzeile vor dem neuen Kommentar
von `pruefe_handelssektor` und gehoert damit zu der Funktion, die weder ein Land prueft
noch nur den Zollkeilgroessen dient. `pruefe_landessektor` hat gar keinen Kommentar mehr.
Keine Abnahmebedingung spricht davon, und die Riegel sind gruen -- deshalb Vorschlag
`0173` und kein `zurueck`.

## Urteil

`geprueft`. Alle fuenf Abnahmebedingungen sind erfuellt, jede mit eigenem mechanischem
Nachweis. Null Befunde gegen das Paket; zwei Vorschlaege, die ausserhalb seiner Abnahme
liegen.
