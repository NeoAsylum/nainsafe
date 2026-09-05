---
typ: technik
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-09-01
fassung: 7, nachgebessert am 2026-09-03 gegen die drei Befunde der Runde 1 zu Paket 0011 (Abschnitt 16) und am 2026-09-04 gegen Paket 0026-klasse-2-preisbasis (T53, Abschnitt 17), dort in drei Läufen -- der zweite hat die Zahlen von T53 nachgerechnet und drei Stellen berichtigt (Umfangsliste in Abschnitt 17, zwei abgeschnittene Zahlen in T53), der dritte hat sie ein zweites Mal unabhängig gerechnet (keine Abweichung) und die Herkunft von N im durchgriff-Absatz von T53 vervollstaendigt (Reihe 1 mal Reihe 2 statt Reihe 1); die Entscheidung selbst ist unverändert; die Fassung folgt ADR 0011 und ventures/0016-.../aufgaben/0011-stack-auf-cpp.md, ausschliesslich die Stellen, die an der Sprache hängen; der Inhalt der Fassung 6 steht unverändert -- und am 2026-09-04 gegen Paket 0043-t48-groessen-gegenkraft-5 (T48 waechst von 17 auf 22 Groessen, T50 und Abschnitt 12 Punkt 3 sind geschlossen, Abschnitt 10 bekommt die Kostenzeile von Gegenkraft 5; Abschnitt 18)
preisbasis: Klasse 2 steht zu konstanten Preisen des Jahres 2015 (gemessen an Reihe 1, WDI "constant 2015 US$"); die 40 BACI-Handelsströme kommen laufend an und werden beim Jahrgangsbau mit einem Weltausfuhrpreisindex aus WDI darauf gebracht -- 0 Rechenschritte je Weltschritt, 0 zusätzliche Sollreihen, T47/T48/T50 unberührt (T53)
stack: C++20, übersetzt mit g++, Version in werkzeugkette.cmake festgenagelt, Bau über CMake, jede Fremdbibliothek als Quelltext unter fremd/ im Repo eingefroren (find_package und FetchContent verboten); Kern ohne jede Fremdabhängigkeit und ohne Gleitkommatyp; Oberfläche vertagt (ADR 0010)
ueberlauf: -fwrapv in jedem Profil, -fsanitize=undefined,address im Testprofil, __int128 für jeden Zwischenwert -- dazu geprüfte Arithmetik im Kern, nach Rechenart geschnitten (Verengung, Strichrechnung, Multiplikation ohne Division), weil -fwrapv genau die Überlaufprüfung des Sanitizers abschaltet (T7)
determinismus: i64-Festkomma mit deklarierter Skala je Größenklasse, feste Iterationsreihenfolge über Indexlisten, ein Wurzelstartwert mit abgeleiteten Strömen, Weltschritt ohne jede Ziehung
zustand: fester, allokationsfreier Wert, 310 i64 (2.480 Byte), Prüfsumme über kanonische Byteform
speicherstand: Jahrgang, Modus, Startwert, Aktionsfolge und Prüfsumme -- nicht der Zustand
kalibrierung: alle Zahlenwerte in einer Parameterdatei ausserhalb des Codes, mitgehasht
partie: R Runden, R ist eine Größe des Jahrgangs; im Prüfjahrgang 1997-2021 ist R = 24, eine Suchbotpartie kostet R × 61 = 1.464 Weltschritte
fondsvermoegen: Kasse + bewertete Positionen + bewertete Beteiligungen - Hebel, Beteiligungen zum Ausstiegswert; genau eine Funktion im Kern, gelesen von Abrechnung, Mandat, Todesart 1, Invariantentest und B (T47)
skalen: dreizehn Klassen, zwölf davon mit Zustandsadressen; jede der 310 Adressen trägt genau eine -- 3 Fondsgeld, 71 volkswirtschaftlich, 36 Raten, 22 Anteile, 22 Nominalindizes, 5 Wechselkurs, 5 Realindizes, 25 Personen, 32 Lobbydruck, 4 Instrumentenstufe, 83 Zähler, 2 Kennungen (T49)
skalenuebergaenge: genau drei, je eine benannte Funktion an genau einem Ort -- tsd_in_cent (Bewertung), lobbypunkte_aus_geld (Aktion 3), lobbypunkte_aus_schaden (Gegenkraft 5); cent_in_tsd hat keinen Aufrufer und gibt es nicht (T50)
abgeleitet: 22 Funktionen des Zustands im Kern (17 bis zum 2026-09-03, dazu die fünf aus dem Schaden in Gegenkraft 5 und dem Zollkeil), 3 im Prüfstand, abschliessend aufgezählt; ein Name in einer Formel, der weder Adresse (T15) noch Parameter (T27) noch Jahrgangskonstante (T23) noch abgeleitete Größe ist, ist ein Befund (T48)
suchbot: Zielgröße B nach T44 -- statische Ergebnisprognose des Zwischenzustands, im Zweig "überlebt" formelgleich mit der Ergebnisgröße von spiel.md, ohne freien Parameter
herkunft: jede der 310 Adressen trägt genau einen Herkunftseintrag aus fünf Arten; 136 Datenanker, 150 Entwurf, 11 Parameter, 2 Manifest, 11 Vorgabe (T45, T46) -- eine Lücke oder ein zweiter Eintrag bricht den Jahrgangsbau ab
tick_planwert: 10 Mikrosekunden je Weltschritt (Bandbreite 5 bis 30) -- geschätzt, nicht gemessen; es gibt noch keinen Kern
nachtlauf: 11.783.264 Weltschritte, 2,0 Minuten auf einem Kern beim Planwert, 9,8 Minuten im ungünstigen Fall
---

# Der Kern ist eine reine Ganzzahlfunktion ohne Ziehung -- damit ist Determinismus keine Disziplin, sondern eine Eigenschaft des Bauprofils.

Siebte Fassung, gegen `ventures/0016-.../aufgaben/0011-stack-auf-cpp.md` und **ADR 0011**.
Sie tauscht **die Bauart und sonst nichts**: Zustandsaufbau, 310 Adressen, dreizehn
Skalenklassen, Formeln, Herkunftseinträge und Jahrgangskonstanten stehen unverändert, weil
nichts davon an einer Sprache hängt. Berührt sind T1 bis T15 in Abschnitt 1 bis 4 und die
Stellen weiter hinten, die ein Sprachmerkmal beim Namen nannten.

Die Vorfassung begründete den Determinismus damit, dass er sich in Rust **vom Werkzeug**
erzwingen lasse. Der Betreiber hat am 2026-09-01 C++ entschieden, und die Überschrift oben
ist deshalb um ein Wort geändert: Was in Rust das Typsystem trug, tragen hier das Bauprofil
und drei Prüfregeln — die Gleitkommasperre (T4), die geprüfte Arithmetik (T7) und die
geordneten Behälter (T9). **Das ist der Unterschied, der beim Lesen wichtig ist:** Jede
dieser drei ist mechanisch nachweisbar, aber keine ist geschenkt. Wo die Vorfassung eine
Spracheigenschaft nannte, nennt diese eine Prüfung — und sagt dazu, was sie *nicht* deckt.

Die Abarbeitung der Prüfung zu `0001-entwurf-abnahme` steht am Ende der Datei und ist von
diesem Lauf nicht berührt. Die Abarbeitungen der ersten vier Prüfungen standen in den
Fassungen 2 bis 5 und sind dort je von der nächsten Prüfung unter deren Bedingung 5
abgenommen worden; sie stehen im Git-Verlauf und werden hier nicht wiederholt.

Die Vorgaben sind mit **T1** bis **T53** durchnummeriert. Der Builder weicht von keiner ab,
ohne dass ein ADR sie aufhebt; der Prüfer zitiert die Nummer, statt sie zu umschreiben.
**Die Nummern behalten über alle Fassungen ihre Bedeutung**, damit alle Prüfungen
zitierbar bleiben; neue Vorgaben tragen die nächsten freien Nummern und stehen dort, wo sie
inhaltlich hingehören. Die Nummerierung ist deshalb innerhalb der Abschnitte nicht
fortlaufend.

**Zwei Vorgaben tragen in dieser Fassung einen Buchstaben — T2b und T6b.** Sie sind keine
neuen Regeln, sondern die C++-Hälfte einer bestehenden: T2b sagt, was an die Stelle von
`#![forbid(unsafe_code)]` tritt, T6b schreibt die Divisionsform vor, an der die
Geschwindigkeitsmessung aus ADR 0011 hing. Ein Buchstabe statt einer neuen Nummer, damit die
Prüfungen der Runden 1 bis 6 zitierbar bleiben und niemand T2 gegen T60 nachschlagen muss.
Wirklich neu war in der Fassung 7 allein **T52** (Plattformunabhängigkeit der
Ganzzahlrechnung), und die Vorfassung brauchte sie nicht, weil Rust sie geschenkt hatte.
**T53** ist am 2026-09-04 mit Paket `0026-klasse-2-preisbasis` dazugekommen und steht hinter
T50, weil sie zu den Skalen gehört und nicht zur Sprache (Abschnitt 17).

**Die teuerste Lehre der Fassung 6, unverändert gültig: Der Abzählschritt aus T45 zählt
Adressen, und Befund 2 der Runde 6 lag zwischen zweien.** Die gemischten Skalen in
`beteiligung_wert` waren keine fehlende Adresse und keine fehlende Zahl, sondern eine
**fehlende Einheit an einer vorhandenen Größe**. Fassung 6 hat deshalb dieselbe Prüfung, die
Fassung 5 für die Herkunft von Hand ausgeführt hat, für die **Skala** ausgeführt — und dabei
gefunden, dass
T5 von sich sagt, die Bedeutung stehe „in dieser Tabelle und nirgends sonst", während **69
der 310 Adressen** in keiner ihrer Zeilen vorkamen: 25 Personengrößen, 5 Produktivitäten,
4 Regulierungsstände, 32 Druck- und Gegendruckfelder, die Sichtbarkeit des Fonds und die
beiden Kennungsfelder.

Die 32 Druckfelder sind darunter der teure Fall, und sie sind wörtlich Befund 2 ein zweites
Mal: Der anliegende Druck entsteht aus dem **Lobbybudget des Fonds** (US-Cent), der
Gegendruck aus dem **Schaden eines Sektors** (Tausend USD), und `spiel.md` verrechnet beide
in Schritt 3 gegeneinander. Ohne erklärte Einheit hätte der Bauagent zwei Skalen addiert,
die um den Faktor 100.000 auseinanderliegen — und diesmal hätte es nicht wie ein
Rechenfehler ausgesehen, sondern wie eine Gegenlobby, die nie greift.

Die Antwort sind **T49** (jede der 310 Adressen trägt genau eine Skalenklasse, abgezählt),
**T50** (die Skalengrenzen werden von benannten Funktionen an genau einem Ort überquert) und
**T48** (die abgeleiteten Größen, die keine Adresse sind, abschliessend aufgezählt — die
Menge, in der Befund 1 lag). Dieselbe Bauart wie T40, T44 und T45: nicht die fehlende Zahl
nachtragen, sondern die Stelle schliessen, an der sie fehlen konnte, und die Zusage einer
Tabelle dadurch prüfen, dass man sie einmal von Hand einlöst. Beide Summen gehen auf:
`3 + 71 + 36 + 22 + 22 + 5 + 5 + 25 + 32 + 4 + 83 + 2 = 310` neben
`136 + 150 + 11 + 2 + 11 = 310`.

## 1. Stack

**T1 — Kern, Datenschicht, Schnittstelle, Prüfstand und Werkzeuge in C++20**, übersetzt mit
`g++`, gebaut über CMake, Übersetzerkennung und -version in `werkzeugkette.cmake`
festgenagelt, **jede Fremdbibliothek nach T3 im Repo eingefroren**. Entschieden hat das der
Betreiber am 2026-09-01 (**ADR 0011**); diese Fassung trägt die Entscheidung nach und ersetzt
die Rust-Fassung der Vorfassungen.

**Die Kandidaten, an den Kriterien dieses Vorhabens gemessen.** Die Vorfassungen haben *für*
eine Sprache argumentiert statt *unter* Alternativen zu wählen; das ist der Befund, aus dem
ADR 0010 und die Tabellenpflicht dieser Rolle entstanden sind. Die vier gemessenen Zeilen
stammen aus `ventures/0016-…/messung-stack/BEFUND.md` (2026-09-01, erzeugt von
`agents/stackmessung.py`): dieselbe Festkomma-Aufgabe, vier Agenten, vier Sprachen.

| Sprache | Determinismus mechanisch erzwingbar | Agent trifft die Vorschrift | ns/Messschritt | Einzelprogramm beim Käufer | Speichersicher |
|---|---|---|---:|---|---|
| **C++20 (gewählt)** | **ja, aber zusammengesetzt** — drei Prüfregeln statt drei Spracheigenschaften (T4, T7, T9) | **erster Anlauf** | **947** | **ja** | **nein** |
| Rust | ja, vom Werkzeug — `overflow-checks`, `clippy::float_arithmetic`, `BTreeMap` | erster Anlauf | 494 | ja | ja |
| Java | teilweise — Gleitkomma nicht verbietbar, `HashMap` gestreut | erster Anlauf | **316** | nein, braucht JRE | ja |
| Python | nein | ja, aber ohne Übersetzungslauf | 50.383 | nein | ja |
| Go | nein — `float64` nicht verbietbar, Kartenreihenfolge absichtlich gestreut | *nicht gemessen* | *nicht gemessen* | ja | ja |
| C# | nein — nur durch Disziplin | *nicht gemessen* | *nicht gemessen* | mit Laufzeit | ja |

Go und C# sind **nicht gemessen**; ihre Zeilen stehen aus ADR 0010 und sind Argument, nicht
Zahl. Sie bleiben in der Tabelle, damit sichtbar ist, was geprüft wurde und was nicht.

**Was die Messung entschieden hat und was nicht.** Alle vier Umsetzungen trafen dieselbe
Prüfsumme `1163237642073673` beim ersten Anlauf, einschliesslich der Rundung auf halbe
Beträge von null weg bei negativen Werten. **Damit ist die Spalte „Agentenzuverlässigkeit"
für diese Domäne leer** — sie war das Hauptargument der Rust-Fassung und trägt nicht mehr.
Python scheidet an der Geschwindigkeit aus (in dieser Messung Faktor 53,2 gegenüber C++,
gerechnet als 50.383 / 947); zwischen den drei übersetzten Sprachen ist die Geschwindigkeit
gleichgültig, weil 11,78 Millionen Weltschritte überall Minuten sind (Abschnitt 10).
Java ist mit 316 ns die schnellste und fällt trotzdem heraus: Eine Laufzeitumgebung neben
einem Steam-Titel ist ein Auslieferungsproblem, das keine Rechenzeit aufwiegt.

**Der Einwand gegen die Wahl gehört dazu, und es sind zwei.** *Erstens:* C++ war in der
Messung 1,92-mal langsamer als Rust und 3,0-mal langsamer als Java (947 / 494 bzw.
947 / 316, beide in diesem Lauf gerechnet). Das ist eine Eigenschaft **dieser Umsetzung**,
nicht der Sprache — **T6b** sagt jetzt, woran es lag und wie es der Kern anders macht.
*Zweitens, und das ist der bleibende Preis:* C++ hat keine Speichersicherheit. In einer
Fabrik ohne menschliche Codedurchsicht ist das eine eigene Fehlerklasse, und sie zeigt sich
beim Käufer statt im Übersetzungslauf. Gegenmassnahmen sind der Adressen-Sanitizer im
Testprofil (T7), der Warnsatz mit `-Werror` und die Zeigerfreiheit des Kerns (**T2b**) — sie
decken Pfade ab, nicht alle Fälle. Das steht hier, damit es später nicht überrascht.

**Was jetzt fallen muss und was sich vertagen lässt.** Die Frage kostet nichts und spart am
meisten, also steht sie ausgeschrieben da:

| Festlegung | jetzt oder später | Grund |
|---|---|---|
| Sprache und Übersetzer des Kerns | **jetzt** | Jede Zeile Kern hängt daran; ein Wechsel später ist ein Neubau. |
| Ganzzahldisziplin (T4, T6, T7) | **jetzt** | Nicht nachrüstbar: Sie ist die Voraussetzung jedes Regressionstests. |
| Bausteinrichtung (T13) | **jetzt** | Sie ist zugleich der Kollisionsschnitt der Arbeitspakete (Abschnitt 13). |
| Oberfläche | **später** (ADR 0010) | Das Modell fragt die Sicht nie etwas; sie ist austauschbar, solange der Kern steht. Entschieden wird, wenn bekannt ist, was sie zeigen muss. |
| Parameterdatei-Leser | **später** | Er sitzt in `daten`, nicht im Kern; T3 nennt die Anforderung, nicht das Erzeugnis. |
| Parallelisierung des Prüfstands | **später** | T39 verlangt Ergebnisgleichheit mit einem und mit vielen Kernen — das bindet das Verfahren, nicht die Bibliothek. |

**T2 — Der Baustein `kern` hat null Fremdabhängigkeiten.** Kein Protokollkasten, keine
Zufallsbibliothek, keine Zeit, keine Ein- und Ausgabe. Ein Baustein ohne Abhängigkeiten kann
durch kein fremdes Versionsupdate sein Ergebnis ändern. **Die Standardbibliothek ist keine
Fremdabhängigkeit** — sie kommt mit dem Übersetzer, den `werkzeugkette.cmake` festnagelt.

*Wie das erzwungen wird, denn C++ hat keinen Abschnitt `[dependencies]`, der leer bleiben
könnte.* Die Entsprechung ist eine Eigenschaft der `CMakeLists.txt` des Kerns, und sie ist
mit **drei** Mustervergleichen nachweisbar. Zwei laufen über diese eine Datei: Der erste sucht
jede Anweisung, die fremden Code hereinholt oder ein weiteres Quellverzeichnis dazunimmt, der
zweite jede Bibliothek, die an `kern` gelinkt wird. Der dritte läuft über **alle übrigen**
`CMakeLists.txt` des Vorhabens und sucht dort `link_libraries(` sowie
`target_link_libraries(kern` — die zwei Formen, mit denen sich `kern` von aussen eine
Abhängigkeit anhängen lässt, ohne dass in seiner eigenen Datei eine Zeile steht (T13).
**Alle drei müssen leer ausgehen.** Ihr Wortlaut gehört in das Abnahmekriterium des jeweiligen
Pakets und ausdrücklich nicht in die geprüfte Datei: Eine Datei, die ihre eigenen Suchmuster
zitiert, lässt sie nie leer ausgehen.

*Warum der dritte Vergleich dazugehört und nicht Vorsicht ist:* Zwei Vergleiche über
`kern/CMakeLists.txt` prüfen die Datei und nicht die Eigenschaft. `link_libraries(fremd)`
eine Ebene höher gilt für jedes danach angelegte Ziel, also auch für `kern` aus
`add_subdirectory(kern)`; und seit CMake 3.13 — verlangt sind 3.22 — darf
`target_link_libraries(kern PRIVATE fremd)` in einem *anderen* Verzeichnis stehen als dem, in
dem `kern` angelegt wurde. In beiden Fällen bleiben die ersten zwei Vergleiche leer, und der
Kern linkt trotzdem eine Fremdbibliothek: T2 formal erfüllt, sachlich gebrochen. Das ist
dieselbe Lücke, die T13 auf der **Kopfseite** mit dem Verbot von `include_directories()`
schliesst — sie hat auf der Linkseite eine Zwillingsform, und die schliesst T13 jetzt mit.

**T2b — Was an die Stelle von `#![forbid(unsafe_code)]` tritt.** Das Attribut gibt es in C++
nicht, und das ist der Preis aus ADR 0011: Speichersicherheit ist hier eine **Prüfregel statt
einer Spracheigenschaft**. An seine Stelle treten drei Dinge, alle mechanisch, alle im
Bauprofil verankert statt in einer Verabredung:

1. **Der Warnsatz mit `-Werror`:** `-Wall -Wextra -Wconversion -Wsign-conversion -Wshadow
   -Wold-style-cast -Wcast-qual -Wuseless-cast -Wdouble-promotion -Wfloat-equal
   -Wnull-dereference -Wformat=2`. Was der Übersetzer als zweifelhaft erkennt, ist damit ein
   Bauabbruch und keine Zeile, die im Protokoll untergeht. **`-Wpedantic` steht bewusst
   nicht dabei:** Es warnt vor `__int128`, und `__int128` ist nach T6 verpflichtend. Ein
   Warnschalter, der eine Vorschrift anmeckert, wird abgeschaltet oder ignoriert — beides
   ist schlechter, als ihn nicht zu setzen.
2. **Der Adressen-Sanitizer im Testprofil** (T7, Massnahme 2). Er ist die einzige der drei,
   die Speicherfehler *findet* statt sie zu *erschweren*.
3. **Die Zeigerfreiheit als Grep-Regel:**
   `grep -rnE 'reinterpret_cast|const_cast|\bnew\b|\bdelete\b|\basm\b' kern/` liefert nichts.
   Der Kern kommt ohne rohe Zeiger und ohne eigene Speicherverwaltung aus — feste Grössen und
   `std::array` statt roher Felder (T15). Das ist keine Härtung, sondern eine Folge des
   Datenmodells: Ein Zustand ohne Zeiger hat keine Stelle, an der ein Zeiger falsch sein
   könnte.

**T3 — Die Abhängigkeiten ausserhalb des Kerns sind abschliessend aufgezählt, und zwar als
Anforderung, nicht als Erzeugnis.** Welche Bibliothek eine Anforderung erfüllt, entscheidet
das jeweilige Paket; dass es *keine weitere* gibt, entscheidet diese Vorgabe.

| Baustein | Anforderung | Lage |
|---|---|---|
| `daten` | Leser für `parameter.toml` und die Jahrgangsdateien, **ohne Gleitkomma** (T4) | offen; die Anforderung schliesst jeden Leser aus, der über `double` geht |
| `schnittstelle` | Protokollformat schreiben und lesen | offen; das Format steht in T17, nicht in einer Bibliothek |
| `pruefstand` | Parallelität über Partien | offen; Abschnitt 9 bindet die **Ergebnisgleichheit** mit einem und mit zweiunddreissig Kernen, nicht das Mittel — `std::thread` und `<execution>` erfüllen sie beide |
| `werkzeuge` | Datei-Prüfsummen für den Jahrgangsbau | offen; darf eine Fremdbibliothek sein, weil das Erzeugnis geprüft wird und nicht der Weg |
| `oberflaeche` | — | **vertagt** (ADR 0010) |

**Jede tatsächlich eingesetzte Bibliothek braucht einen ADR mit Lizenzzitat**, und keine
davon darf in den Kern (T2). Die frühere Liste dieser Vorgabe nannte sechs Fremdbibliotheken
namentlich; sie ist ersatzlos gestrichen, weil sie eine Wahl festschrieb, die niemand
treffen musste — und weil die Oberflächenzeile darin seit ADR 0010 ohnehin vertagt war.

**Und jede eingesetzte Bibliothek liegt im Repo, nicht auf dem Rechner des Übersetzenden.**
Das ist der Nachfolger von `cargo vendor`, und er hat beim Umschreiben auf C++ zunächst
gefehlt: Der Satz der Vorfassung hatte zwei Hälften — Werkzeugkette festgenagelt,
Abhängigkeiten eingefroren —, und nur die erste ist zu `werkzeugkette.cmake` geworden.
Konkret tritt an die Stelle der zweiten: Der Quelltext liegt unter `fremd/<name>/`, Fassung
und Commit-Kennung stehen in ihrem ADR, und übersetzt wird sie über
`add_subdirectory(fremd/<name>)` mit. **`find_package()`, `FetchContent`, `ExternalProject`
und `pkg_check_modules` sind im ganzen Vorhaben verboten** — sie binden den Bau an das, was
auf dem jeweiligen Rechner gerade installiert ist. Das Verbot ist die eigentliche Vorgabe und
nicht ein Zusatz zu T23: Ein `find_package(… REQUIRED)` **lädt nichts herunter**, verstösst
also gegen „der Bau lädt nichts aus dem Netz" nicht und richtet trotzdem genau den Schaden
an, den `cargo vendor` ausschloss.

*Warum das heute nichts kostet und trotzdem jetzt dasteht:* Das Vorhaben hat null
tatsächliche Fremdabhängigkeiten — T2 verbietet sie im Kern, und alle fünf Zeilen der Tabelle
oben stehen auf „offen" oder „vertagt". Es ist also nichts kaputt, sondern etwas unbewacht.
Die Zusage dahinter ist der Rückvergleich: Zwei Übersetzungen im Abstand von drei Monaten
müssen dasselbe Programm ergeben, sonst prüft T31 gegen einen Regressionsbestand, den niemand
identisch wiederherstellen kann — und der Parameterleser aus der ersten Tabellenzeile ist
genau die Sorte Bibliothek, deren Fassungswechsel eine Zahl um eine Stelle verschiebt, ohne
dass irgendetwas abbricht. Eine Vorgabe vor der ersten Bibliothek kostet einen Absatz;
dieselbe Vorgabe nach der ersten Bibliothek kostet einen Umbau.

**Ausdrücklich nicht gewählt:** Eine Spiel-Engine (Godot, Unity, Unreal) — sie bringt eine
Bildschleife, eine Zeitachse und eine eigene Zahlenwelt mit, also genau die drei Quellen
von Nichtreproduzierbarkeit, die hier ausgeschlossen werden sollen; das Spiel braucht
Tabellen, Verlaufsgraphen und eine Kettenansicht. Eine Netzoberfläche (Electron, Tauri) —
JavaScript kennt keinen Ganzzahltyp, und ein versehentliches `/` erzeugt still eine
Gleitkommazahl. Python — siehe die Rechnung in Abschnitt 10. Steamworks-SDK — für den
ersten Titel nicht nötig (keine Erfolge, kein Wolkenspeicher), also eine Abhängigkeit und
ein Konto weniger. **Ein Testrahmen** (GoogleTest, Catch2) — die Proben sind eigenständige
Programme mit `static_assert` und Rückgabewert, von CTest aufgerufen; das kostet keine
Abhängigkeit und macht die Hälfte der Prüfungen zu Übersetzungsfehlern statt zu
Laufzeitmeldungen.

## 2. Der deterministische Kern

**T4 — Keine Gleitkommazahl im Kern, in der Datenschicht und im Protokoll.** Kein `float`,
kein `double`, kein `long double`, kein `sqrt`, kein `pow`, kein `log`, kein `exp`.

**Die Sperre ist ein Übersetzungsfehler, kein Vorsatz.** Rust hätte hier
`#![deny(clippy::float_arithmetic)]` gehabt; die C++-Entsprechung ist `#pragma GCC poison`
in `kern/include/kern/sperre.hpp`. Ein vergifteter Bezeichner ist ab dieser Zeile ein harter
Fehler des Vorverarbeiters. Wer im Kern `double` schreibt, bekommt keinen Zahlenfehler in
Runde 400, sondern einen roten Übersetzungslauf. Vergiftet sind `float` und `double`
(`long double` sind zwei Token und damit miterfasst), die Wurzel-, Potenz-, Logarithmus- und
Exponentialfunktionen in allen drei Suffixformen und die Zeichenketten-Umwandler `atof`,
`strtod`, `strtof`, `strtold`.

**Die Einbauregel, und sie ist der ganze Trick:** `sperre.hpp` ist die **letzte** Zeile des
Include-Blocks jeder Kernquelle und steht in **keiner** `.hpp`. Die Vergiftung gilt ab der
Stelle, an der sie steht, bis zum Ende der Übersetzungseinheit — ein Standardkopf, der
danach eingebunden wird, zerbricht daran, weil etwa `<string>` ein `std::to_string` für
`double` deklariert. Eine Sperre in einem Kopf würde also nicht den Kern schützen, sondern
den Bau anhalten.

Nachweis, zwei Zeilen: `grep -c 'include "kern/sperre.hpp"' kern/src/*.cpp` gibt für jede
Quelle genau `1`, und `grep -rnE 'float|double' kern/` trifft nur `sperre.hpp`
selbst. Auch die Parameterdatei wird ohne Gleitkomma gelesen — Dezimalzeichenketten werden
direkt in skalierte Ganzzahlen zerlegt, nie über einen Gleitkommaumweg; in `daten` gilt
dieselbe Sperre.

**T5 — Jede Größenklasse hat eine deklarierte Skala.** Der Typ ist überall `i64` — im Kern
ein Aliasname für `std::int64_t`, damit die Breite an keiner Stelle vom Zielsystem abhängt —,
die Bedeutung steht in dieser Tabelle und nirgends sonst:

| # | Klasse | Einheit | Beispiel | Bereich |
|---:|---|---|---|---|
| 1 | Fondsgeld (Kasse, **Positionswert**, **Beteiligungswert**, Hebel, Anlegerbestand) | US-Cent | 4.200.000.000 = 42 Mio USD | ±9,2·10^16 USD |
| 2 | Volkswirtschaftliche Beträge (BIP, Wertschöpfung, Kapitalstock, Handelsstrom, **Korbwert**, Marktkorbwert) | Tausend USD zu konstanten Preisen **des Jahres 2015**; was in einer anderen Preisbasis ankommt, wird beim Jahrgangsbau nach **T53** darauf gebracht | 21.000.000.000 = 21 Bio USD | reichlich |
| 3 | Raten (Zins, Inflation, Zoll, Haushaltssaldo, Schuldenquote, Rendite, Überrendite, **`aufschlag`**) | Basispunkte (1 bp = 0,01 %) | 250 = 2,50 % | ±2 Mio % |
| 4 | Anteile (Sektoranteil, Marktanteil, Einfluss, Zustimmung, **Sichtbarkeit**, **Beteiligungsanteil**, `durchgriff`, **`stufenweite`**) | Zehntausendstel | 10.000 = 100 % | 0 bis 10.000 |
| 5 | Nominalindizes (Sektorpreise, Weltpreise, Preisniveau, **`anleihekurs`**) | Index, Startjahr = 10.000 | 12.500 = +25 % | > 0, siehe T8 und T50 |
| 6 | Wechselkurs | Index gegen USD, Startjahr = 10.000 | 8.000 = Aufwertung um 25 % | ≥ 1, siehe T8 und T50 |
| 7 | **Realindizes (Produktivität)** | Index, Startjahr = 10.000, **nie neu basiert** | 11.200 = +12 % | > 0 |
| 8 | **Personen** (Bevölkerung, Erwerbstätige, Beschäftigung je Sektor) | Personen | 82.000.000 | 0 … 10^10 |
| 9 | **Lobbydruck** (anliegender Druck, Gegendruck) | Lobbypunkte | 1.500 | 0 … `druck_max` |
| 10 | **Instrumentenstufe** (allein Finanzmarktregulierung) | Stufe | 3 | 0 … `regulierung_stufen` |
| 11 | Zähler und Restdauern (Aufsicht, Nachahmer, Restverzögerung, die drei Restdauern, `basiswechsel`, Runde, Mandatsstand, Positionsstufe) | Stück bzw. Runden | 3 = drei Runden | 0 … Obergrenze aus `parameter.toml`; Positionsstufe `−stufen_max … +stufen_max` |
| 12 | **Kennungen** (Jahrgangskennung, Parametersatz-Prüfsumme) | Bitmuster ohne Größenbedeutung | — | jede `i64`; **jede Arithmetik ausser Gleichheit ist ein Fehler** |
| 13 | Ergebnis einer Partie (**keine Zustandsadresse**) | Milli-Runden | 12.000 = Runde 12,0 | siehe T34 |

**Fünf Klassen sind in dieser Fassung neu, und sie sind es nicht aus Ordnungsliebe.** T5
sagt von sich, die Bedeutung stehe „in dieser Tabelle und nirgends sonst"; ich habe die
Zusage in diesem Lauf zum ersten Mal gegen alle 310 Adressen eingelöst und 69 gefunden, die
in keiner Zeile vorkamen. Welche das sind und wie die Zuordnung aufgeht, steht in **T49**;
was die neuen Klassen bedeuten, hier:

- **Personen (8).** 25 Adressen. Ohne eigene Klasse hätte ein Bauagent Erwerbstätige in
  Tausenden oder in Personen führen können, und die Produktivität hinge am Faktor 1.000.
- **Realindizes (7).** 5 Adressen. Die Trennung von Klasse 5 ist keine Feinheit, sondern
  eine Regel: T8 teilt bei einer Neubasierung die **nominalen** Größen eines Gebiets durch
  1.000. Die Produktivität ist real und darf nicht mitlaufen; stünde sie in Klasse 5, würde
  ein brasilianischer Basiswechsel die Produktivität um drei Größenordnungen senken.
- **Lobbydruck (9).** 32 Adressen, und der Grund steht oben im Vorspann: `druck` kommt aus
  dem Fondsbudget, `gegendruck` aus einem volkswirtschaftlichen Schaden, und Schritt 3
  verrechnet beide gegeneinander. Die gemeinsame Einheit ist der **Lobbypunkt**; die beiden
  Übergänge dorthin stehen in T50.
- **Instrumentenstufe (10).** 4 Adressen. Drei der vier Instrumente stehen in Basispunkten,
  weil ihr historischer Politikpfad in Basispunkten vorliegt; die Finanzmarktregulierung hat
  nach `spiel.md` keinen Anker und deshalb keine natürliche Einheit. Sie bekommt eine
  Stufenskala, und „höchstens ein Schritt je Runde" heisst dort **eine Stufe**, bei den
  anderen dreien `schrittweite[instrument]` Basispunkte aus `parameter.toml`.
- **Kennungen (12).** 2 Adressen. Das Verbot der Arithmetik ist der eigentliche Inhalt: Eine
  Prüfsumme, die versehentlich in eine Summe gerät, erzeugt eine Zahl, die keine Prüfung
  bemerkt, weil sie in keinem Wertebereich liegt.

**Zwei bestehende Klassen sind erweitert, und auch das ist kein Ordnungsschritt:**
**Fondsgeld (1)** und **volkswirtschaftliche Beträge (2)** führen jetzt `positionswert` und
`korbwert` ausdrücklich, auf beiden Seiten der Grenze. Das ist Befund 2 der Runde 6 an seiner
Wurzel — die beiden Namen standen in T47 in einer Formel, aber in keiner Klasse.

Einfluss und Zustimmung erscheinen dem Spieler als 0 bis 100 (so nennt sie `spiel.md`);
gespeichert sind sie in Zehntausendsteln, damit die Gegenkräfte unterhalb eines
sichtbaren Punktes noch rechnen können. Die Umrechnung findet in der Sicht statt.

Der Koeffizient heisst seit `spiel.md` Fassung 3 **`durchgriff`** und nicht mehr
`handelsanteil`. Er bleibt in der Klasse Anteile — anders als sein Vorgänger hält er ihren
Bereich jetzt per Konstruktion ein; die Bildungsregel steht in T23 Punkt 5.

**`stufenweite` steht seit `spiel.md` Fassung 5 in der Klasse Anteile und nicht in der
Klasse Fondsgeld**, und das ist die Entscheidung, an der Befund 2 hing: Eine Stufe ist
*`stufenweite` Zehntausendstel des Marktes*, an dem der Steckplatz hängt, kein Geldbetrag.
Damit ist der Anteil, den Gegenkraft 1 und der Preisstoß lesen, dieselbe Zahl wie die, aus
der der Positionswert entsteht, und der Zustand braucht keine zwanzig Einstandspreise.

**Das Basisjahr der Klasse 2 ist 2015, und es steht seit dieser Fassung als Jahreszahl da
statt als „das Basisjahr".** Bis zum 2026-09-04 nannte die Zeile ein Basisjahr, ohne eines zu
nennen; für 56 der 71 Adressen war damit unbestimmt, worauf sie sich bezieht, und ein
Bauagent hätte es wählen müssen. Gewählt ist **2015**, weil es das einzige in diesem Vorhaben
**gemessene** Basisjahr ist: Reihe 1 trägt am Weltbank-Endpunkt im Feld `Unitofmeasure` den
Wortlaut „constant 2015 US$" (zwei Endpunkte, zeichengleich gegengeprüft,
`daten/einheitenbefund-pwt-baci.md` Abschnitt 6, abgerufen 2026-09-02), und die Wertschöpfung
aller fünf Gebiete entsteht nach T23 Punkt 1 aus ihr. Ein anderes Basisjahr hätte geheissen,
die einzige gemessene Reihe umzurechnen, um zwei ungemessene zu treffen.

**Welche Klasse-2-Adresse in welcher Preisbasis ankommt und was mit ihr geschieht, steht in
T53** — namentlich für die 40 Handelsströme aus BACI, die als einzige gemessen in einer
**anderen** Basis ankommen.

**Zwischen Fondsskala und volkswirtschaftlicher Skala liegt der Faktor 100.000** (1 Tausend
USD = 100.000 US-Cent). Wo er überschritten wird, sagt **T50** — und er wird nur in **einer
Richtung** überschritten, weshalb es `cent_in_tsd` in dieser Fassung nicht mehr gibt.

**T49 — Jede der 310 Adressen trägt genau eine Skalenklasse, und die Zuordnung ist
abgezählt.** Das ist T45 eine Ebene tiefer, aus demselben Grund und mit demselben Verfahren:
Der Jahrgangsbau führt neben der Herkunftstabelle eine **Skalentabelle** über alle 310
Adressen; eine Adresse ohne Klasse und eine mit zwei Klassen brechen den Bau ab. Beide
Tabellen werden ins Manifest geschrieben, und beide müssen auf 310 summieren.

**Je spielbarem Land**, die 44 aus T15 nach Klasse:

| Klasse | Adressen | welche |
|---|---:|---|
| 2 volkswirtschaftlich | 6 | 3 Wertschöpfungen, 3 Sektorkapitalstöcke |
| 8 Personen | 5 | 3 Sektorbeschäftigungen, Bevölkerung, Erwerbstätige |
| 5 Nominalindizes | 4 | 3 Sektorpreise, Preisniveau |
| 7 Realindizes | 1 | Produktivität |
| 3 Raten | 7 | Inflation, Leitzins, Staatsschuld, Haushaltssaldo, 3 Instrumentenstände (Leitzins, Zoll, Haushalt) |
| 6 Wechselkurs | 1 | Wechselkurs |
| 4 Anteile | 2 | Zustimmung, Einfluss |
| 9 Lobbydruck | 8 | 4 anliegende Drücke, 4 Gegendrücke |
| 10 Instrumentenstufe | 1 | Stand der Finanzmarktregulierung |
| 11 Zähler | 9 | Aufsichtszähler, 4 Restverzögerungen, 3 Restdauern, `basiswechsel` |
| **Summe** | **44** | wie T15 |

**Die Restwelt** trägt davon 22: 6 volkswirtschaftlich, 5 Personen, 4 Nominalindizes,
1 Realindex, 4 Raten, 1 Wechselkurs, 1 Zähler — sie hat keine Instrumente, keine
Zustimmung, keinen Aufsichtszähler, keinen Einfluss und keine Restdauern.

**Die ganze Zerlegung**, gegen dieselben 310:

```
Klasse  1 Fondsgeld           Kasse, Hebelstand, Anlegerbestand                  =   3
Klasse  2 volkswirtschaftlich 4×6 + 6 + 40 Handelsströme + markt.wert            =  71
Klasse  3 Raten               4×7 + 4 + markt.rendite + 3 Überrenditen           =  36
Klasse  4 Anteile             4×2 + Sichtbarkeit + Marktanteil + 12 Beteiligungsanteile = 22
Klasse  5 Nominalindizes      4×4 + 4 + 2 Weltpreise                             =  22
Klasse  6 Wechselkurs         4 + 1                                              =   5
Klasse  7 Realindizes         4 + 1                                              =   5
Klasse  8 Personen            4×5 + 5                                            =  25
Klasse  9 Lobbydruck          4×8                                                =  32
Klasse 10 Instrumentenstufe   4×1                                                =   4
Klasse 11 Zähler              4×9 + 1 + 12 Nachahmer + 20 Stufen + 12 Restdauern
                              + Runde + Mandatsstand                             =  83
Klasse 12 Kennungen           Jahrgangskennung, Parametersatz-Prüfsumme          =   2
                                                                                   ---
                                                                                   310
```

Gegengerechnet gegen die Gruppenzerlegung aus T15 (`198 + 56 + 52 + 4`) und gegen die
Herkunftszerlegung aus T45 (`136 + 150 + 11 + 2 + 11`). **Drei unabhängige Aufteilungen
derselben Menge, alle drei von Hand gerechnet** — eine Zahl, die nur einmal entsteht, ist
unbelegt, auch wenn sie stimmt.

**Zwei Adresspaare tragen denselben Wert, und das braucht eine Regel statt eines Zufalls.**
`land.<L>.leitzins` und `land.<L>.instrument.leitzins.stand` sind dieselbe Größe, ebenso
`land.<L>.haushaltssaldo` und `land.<L>.instrument.haushalt.stand`; T15 führt beide, weil
`spiel.md` beide aufzählt. Verbindlich ist deshalb: **Geschrieben wird der Instrumentenstand
in Schritt 3; die Aggregatgröße wird in Schritt 4 mit `lies_neu` vom Stand übernommen und
trägt die Ursache `Instrument{l, i}`.** Der Invariantentest (T30 Prüfung 2) prüft die
Gleichheit je Runde. Ohne diese Regel gäbe es zwei Herren über eine Zahl — derselbe
Fehlertyp, den T39 für `landespreis`, T23 Punkt 9 für die BACI-Konkordanz und T47 für das
Fondsvermögen schon geschlossen haben. Dass das Paar überhaupt existiert, ist eine
Beobachtung an `spiel.md` und steht in Abschnitt 12; es blockiert nichts.

**T50 — Es gibt genau drei Skalenübergänge, jeder hat eine benannte Funktion und genau
einen Aufrufort.** Ein Übergang ohne Namen ist die Fehlerart, an der Befund 2 der Runde 6
hing; ein Name ohne Ortsbindung ist derselbe Fehler eine Woche später.

| # | von | nach | Funktion | einziger Aufrufort |
|---:|---|---|---|---|
| 1 | volkswirtschaftlich (2) | Fondsgeld (1) | `tsd_in_cent(x) = x · 100.000` | äusserster Aufruf von `positionswert` und `beteiligung_wert` (T47) |
| 2 | Fondsgeld (1) | Lobbydruck (9) | `lobbypunkte_aus_geld(cent, rabatt) = mal_geteilt(cent, 10.000, lobbykosten · rabatt)` | Aktion 3, Schritt 2 |
| 3 | volkswirtschaftlich (2) | Lobbydruck (9) | `lobbypunkte_aus_schaden(tsd) = mal_geteilt(tsd, gegenlobby_satz, 10.000)` | Gegenkraft 5, Schritt 5 |

`lobbykosten` (US-Cent je Lobbypunkt, ≥ 1), `gegenlobby_satz` (Lobbypunkte je 10.000 Tausend
USD Schaden) und `beteiligungsrabatt` (Zehntausendstel; `rabatt` ist 10.000 ohne und
`beteiligungsrabatt` mit Beteiligung im betroffenen Sektor, also `1 ≤ beteiligungsrabatt ≤
10.000`) stehen nach T27 in `parameter.toml` und werden kalibriert, nicht entworfen. Ein
kleinerer Rabattwert heisst mehr Punkte für dasselbe Geld — das ist der „Bruchteil", den
`spiel.md` der Aktion 3 mit Beteiligung zusagt. **Der Rabatt sitzt am Preis eines
Lobbypunkts, nicht an der Punktzahl** — sonst wäre `einfluss`, nach `spiel.md` der Anteil
des Fonds am gesamten Lobbydruck, über Länder hinweg nicht mehr vergleichbar.

***Wie hoch* der Schaden eines Sektors ist, hat `spiel.md` am 2026-09-03 entschieden, und
der Satz, der hier bis zum 2026-09-04 offenliess, ist damit geschlossen.** Er lautete: *„Wie
hoch der Schaden eines Sektors ist, bleibt Sache von `spiel.md` und des Bauagenten; T50 legt
nur fest, in welcher Einheit er ankommt."* Die Rückgabe war richtig — hätte ich die Lücke
gefüllt, hätte Maß 2 meine Wahl gemessen —, und sie ist beantwortet: Der Abschnitt *Der
Schaden in Gegenkraft 5, als Rechenvorschrift* in `spiel.md` gibt die eine Regel („Verschiebung
des Preises, den das Instrument setzt, mal der Menge, auf die dieser Preis wirkt") und die
vier Zeilen dazu. Sie steht als **Nummer 22** in T48; der Bauagent wählt an dieser Stelle
nichts mehr. Was T50 unverändert festlegt, ist allein die Einheit, in der sie hier ankommt:
Klasse 2, Tausend USD. Die Skalenprobe dazu führt `spiel.md` selbst — Klasse 2 mal
Zehntausendstel durch 10.000 ist wieder Klasse 2, in allen vier Zeilen und über beide
Zwischenschritte der Zollzeile, **also entsteht kein vierter Skalenübergang.** Diese Tabelle
bleibt bei dreien.

**`cent_in_tsd` gibt es nicht.** Fassung 5 hat die Umkehrfunktion neben `tsd_in_cent`
genannt; sie hat in diesem Modell **keinen Aufrufer**, und der Grund ist eine Eigenschaft
des Entwurfs und kein Zufall: Der Fonds wirkt auf die Welt ausschliesslich über **Anteile in
Zehntausendsteln** (Preisstoß aus Aktion 1, Fußabdruck in Gegenkraft 1, Nachahmerzähler),
nie über einen Geldbetrag. Eine Umrechnungsfunktion ohne Aufrufer ist eine stehende
Einladung, sie irgendwo zu benutzen, wo sie nicht hingehört; sie ist deshalb gestrichen.
Fällt später eine Regel an, die sie braucht, ist das ein ADR.

**Wo die Übergänge erzwungen werden.** Alle drei Funktionen und alle abgeleiteten Größen aus
T48 stehen im Modul `kern::werte`; `tsd_in_cent` und die beiden Lobbyumrechnungen sind dort
privat. Ein Treffer von `grep -rn 'tsd_in_cent\|lobbypunkte_aus' kern/` ausserhalb dieses
einen Moduls ist ein Befund — dieselbe Bauart wie der Gleitkommanachweis aus T4, und ebenso
mechanisch.

**T53 — Was Klasse 2 für eine Reihe bedeutet, die in laufenden Preisen ankommt: Sie wird beim
Jahrgangsbau deflationiert, mit einem benannten Deflator aus einer bereits zugelassenen
Quelle, auf die Basis 2015.** Der Kern sieht davon nichts. Das ist die Entscheidung, auf die
Paket 0002 seit dem 2026-09-02 wartet.

**Wo jede der 71 Klasse-2-Adressen ankommt, gemessen und abgezählt.** Die Zerlegung ist die aus
T49 (`4×6 + 6 + 40 Handelsströme + markt.wert`), nach Preisbasis geschnitten statt nach Gebiet:

| Adressen | Zahl | Reihe | Quelle | Preisbasis, wie gemessen | was geschieht |
|---|---:|---|---|---|---|
| Wertschöpfung, 5 Gebiete × 3 | 15 | 1 über T23 P1 | WDI `NY.GDP.MKTP.KD` | **konstant, 2015** (gemessen 2026-09-02, zwei Endpunkte) | nichts — sie *ist* die Basis |
| Sektorkapitalstock, 5 × 3 | 15 | 3 über T23 P1 | PWT 11.0 | **ungemessen** (PDF-Sperre) | **ausgewiesene Nichtentscheidung**, unten |
| Handelsströme | 40 | 14 | CEPII BACI, Feld `v` | **laufend** (gemessen 2026-09-02, „in thousands current USD") | **Deflator**, unten |
| `markt.wert` | 1 | 19 | keine, T33 | folgt seinen Eingängen (12 `korbwert` + 4 `anleihewert`) | nichts |
| **Summe** | **71** | | | | wie T49 |

Nachgerechnet: `15 + 15 + 40 + 1 = 71`, und `15 + 15` ist die `4×6 + 6 = 30` aus T49, nach
Größe statt nach Gebiet aufgeteilt. **Genau eine Zeile ist gemessen in einer anderen Basis als
2015**, und sie trägt 40 der 71 Adressen.

**Die Zahl, die entscheidet — der Preisanteil allein reisst die Schwelle.** T42 misst den
Handelsblock mit dem MAPE gegen die Schwelle 2.000 (= 20 %). Das Modell führt den
Handelsstrom real (`spiel.md` stützt darauf ausdrücklich die Schadensvorschrift von
Gegenkraft 5: *„`handelsvolumen` steht nach T5 Klasse 2 zu konstanten Preisen"*), die Sollreihe
kommt nominal. Wie gross der Fehler ist, den das **allein** erzeugt, war bis heute ungemessen;
er ist es nicht mehr. Weltausfuhr in laufenden und in konstanten Preisen von 2015, beide von
der Weltbank, ihr Quotient ist ein USD-Ausfuhrpreisindex mit Basis 2015 = 10.000:

```
https://api.worldbank.org/v2/country/WLD/indicator/NE.EXP.GNFS.CD   "Exports of goods and services (current US$)"
https://api.worldbank.org/v2/country/WLD/indicator/NE.EXP.GNFS.KD   "Exports of goods and services (constant 2015 US$)"
                                                                     beide abgerufen 2026-09-04
```

| Jahr | 97 | 98 | 99 | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Index | 7.417 | 7.021 | 6.911 | 6.849 | 6.594 | 6.738 | 7.485 | 8.246 | 8.755 | 9.281 | 10.133 | 11.232 | 10.045 |

| Jahr | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Index | 10.682 | 11.989 | 11.840 | 11.798 | 11.592 | **10.000** | 9.570 | 10.022 | 10.553 | 10.254 | 10.158 | 11.549 |

Ein Modell, das die Mengen **fehlerfrei** trifft, startet auf dem BACI-Wert von 1997 und läuft
real weiter; die Sollreihe läuft mit dem Index. Sein Fehler je Stützstelle ist damit
`|1 − r(t)| / r(t)` mit `r(t) = Index(t)/Index(1997)`, und das Mittel über die 25 Stützstellen
des Prüfjahrgangs ist **2.203 Zehntausendstel gegen eine Schwelle von 2.000**. Am rechten Rand
allein sind es 3.578 (2021: `r = 1,5571`). **Der Prüfgegenstand Handelsblock fällt also durch,
bevor das Modell einen einzigen Fehler gemacht hat** — die Preisdrift allein verbraucht das
Fehlerbudget nicht zum Teil, sondern **ganz und mit 10 Prozent Überhang** (2.203 gegen 2.000).
Für Modellgüte bleibt nichts übrig.

Drei Vorbehalte gehören an dieselbe Stelle wie die Zahl. *Erstens* ist das der
**Welt**aggregatindex und nicht der Deflator der 40 bilateralen Ströme; er hat die richtige
Größenordnung und ist gemessen, er ist keine Vorhersage des tatsächlichen MAPE. *Zweitens*
ist 2.203 der **systematische Anteil**, zu dem der Modellfehler noch hinzukommt, nicht davon
ab. *Drittens* trägt das Argument auch bei einer kleineren Zahl: Eine Schwelle, die Modellgüte
messen soll und ihr Budget an eine Preisdrift verliert, die niemand modelliert hat, misst
etwas anderes als das, wofür sie dasteht.

**Die vier Wege nebeneinander, mit Preis.** Der Preis steht in Rechenschritten je Weltschritt
und in zusätzlichen Sollreihen, weil das die zwei Größen sind, an denen dieses Vorhaben
zugrunde gehen kann:

| Weg | Rechenschritte je Weltschritt | zusätzliche Sollreihen | weiterer Preis | Ergebnis |
|---|---:|---:|---|---|
| **1 Deflationieren (gewählt)** | **0** | **0** | einmalig 1.040 Umrechnungen je Jahrgangsbau; **+1 Reihe** (Nr. 20, 2 Indikatorcodes, 1 Gebiet, 25 Zahlen), **keine neue Quelle** | Handelsblock bleibt Prüfgegenstand, T47/T48/T50 unberührt |
| 2 Klasse wechseln | 0 in diesem Dokument | 0 | T5 **+1 Zeile**, T49-Zerlegung neu (71 → 31 + 40), T8 neu abzählen — **und eine Entscheidung in `spiel.md` vom 2026-09-03 wieder auf** | nicht meine Entscheidung, siehe unten |
| 3 Maß 4 einschränken | 0 | 0 | 16 → **15** Prüfgegenstände bei unveränderter Toleranz 2, also ein *schärferer* Test auf dem Rest; 40 der 71 Adressen ohne jede Prüfung; Kanal 3 ohne historischen Anker | billigster Bau, teuerster Verlust |
| 4 Quelle wechseln (IWF DOTS) | — | — | **nicht bezifferbar**: T26 lässt DOTS nur für Spieljahrgänge vor 1997 zu, der Prüfjahrgang beginnt 1997, und die Preisbasis von DOTS ist ungemessen (HTTP 403 in fünf Anläufen aus drei Rollen) | tauscht eine gemessene Schwierigkeit gegen eine ungemessene |

**Warum Weg 1 und nicht Weg 3**, obwohl beide im Kern null kosten: Weg 3 heisst nicht
„einschränken", sondern **streichen**. Bei einem Fehleranteil von 2.203 gegen 2.000 gibt es
keine Einschränkung, die den Handelsblock noch etwas prüfen liesse — eine eigene Schwelle
oberhalb von 2.203 wäre eine Schwelle, die jedes Modell besteht. Der Block trägt 40 der 71
Klasse-2-Adressen und ist der einzige historische Anker von **Kanal 3** (Instrument → Handel →
Weltpreis → Schaden → Gegendruck), den `spiel.md` unter seinen acht Kanälen führt. Weg 1
kauft ihn für 25 Zahlen aus einer Quelle, die ohnehin schon eingebunden ist.

**Warum Weg 2 nicht, und das ist kein Preisargument.** `spiel.md` hat am 2026-09-03 den
Konjunktursockel aus Gegenkraft 5 gestrichen und die Streichung ausdrücklich darauf gestützt,
dass `handelsvolumen` nach T5 Klasse 2 real ist — der Sockel *war* die Inflation mal dem
Handelsvolumen. Klasse 2 nominal zu stellen holt ihn zurück. **Was gespielt wird, steht in
`spiel.md`; ich widerspreche dort nicht.** Weg 2 ist damit nicht teuer, sondern nicht meiner.

**Der Deflator, benannt, mit Quelle und in Ganzzahlen.** Er wird eine Reihe des Jahrgangs, kein
Programmteil (T23), und keine Sollreihe — er wird gegen nichts verglichen:

```
preisindex_handel[t] = teile_gerundet( ausfuhr_laufend[t] · 10.000, ausfuhr_konstant[t] )

handel_konstant[a][b][s][t] = mal_geteilt( handel_laufend[a][b][s][t],
                                           10.000, preisindex_handel[t] )
```

`ausfuhr_laufend` ist `NE.EXP.GNFS.CD`, `ausfuhr_konstant` ist `NE.EXP.GNFS.KD`, beide für das
Gebiet `WLD`, beide Weltbank — also **Quelle Nr. 1 aus `daten.md`**, dieselbe Lizenz, dieselbe
Zitierpflicht, keine fünfte Quelle und kein Fall für den Datenkurator. Beide Rechnungen laufen
über T6; `ausfuhr_laufend[t] · 10.000` erreicht bei 2,8 · 10^13 USD rund 2,8 · 10^17 und bleibt
damit im `i64`. Der Faktor 1 aus dem Einheitenbefund bleibt unberührt: Er ist die
**Größenordnung**, der Deflator ist die **Preisbasis**, und die beiden sind zwei Fragen an
dieselbe Zeile.

**Ein Selbsttest, der zwei Zeilen kostet und die ganze Zuordnung trägt:**
`preisindex_handel[2015] = 10.000` **exakt**. Er gilt nicht aus Konvention, sondern weil die
beiden Reihen im Basisjahr denselben Wert führen (21.272.611.247.725,1 — in beiden Abrufen
zeichengleich). Weicht er ab, führen die zwei Indikatorcodes **nicht** dieselbe Basis, und der
Jahrgangsbau bricht ab, statt eine Preisbasis zu behaupten, die er nicht hat. Das ist dieselbe
Bauart wie die Abzählprüfungen aus T45 und T49: eine Zusage, die sich selbst nachweist.

**Die Umrechnung trifft die Sollreihe und die Startmatrix, und zwar mit demselben Index.** Nach
T23 Punkt 9 erzeugt **eine** Konkordanz die Handelsstartmatrix, die 40 Sollströme und `H` aus
Punkt 5; entsprechend deflationiert **ein** Index alle drei. Eine Sollreihe zu deflationieren
und die Startmatrix nicht wäre der Fehler, den T23 Punkt 9 für die Konkordanz schon
ausschliesst. Für den Prüfjahrgang ist der Faktor auf das Startjahr
`10.000 / 7.417 = 1,34825`.

**Reihe 16 (`durchgriff`) ist damit mitentschieden, und sie war die zweite Hälfte des
Widerspruchs.** `H` kommt nach T23 Punkt 5 aus derselben deflationierten Matrix. `N` ist die
Wertschöpfung des Sektors und entsteht nach T23 Punkt 1 aus **zwei** Reihen —
`wertschoepfung[g][s] = mal_geteilt(bip_start[g], sektoranteil[g][s], 10.000)`, also Reihe 1
mal dem Sektoranteil aus Reihe 2. **Die Preisbasis von `N` hängt allein an Reihe 1**, weil
Reihe 2 ein Anteil in Zehntausendsteln ohne Preisbasis ist. Beide Seiten stehen danach in
konstanten Preisen von 2015, und der Quotient trägt keinen Preisanteil mehr. **Der Zug hat eine Eigenschaft, die kein anderer Deflatorzuschnitt hätte:**
Weil *ein* Index auf *alle* 40 Ströme wirkt, wird jedes `H` mit demselben Faktor multipliziert,
`H/N` also für alle Gebiete und Sektoren mit demselben — und `durchgriff = 10.000 · H/(H+N)`
ist streng monoton in `H/N`. **Die Ordnung über Länder und Sektoren bleibt damit exakt
erhalten**, und genau sie ist das Einzige, was `spiel.md` von dieser Größe verlangt
(*„Sein Zahlenwert hat keine volkswirtschaftliche Bedeutung; er muss Länder und Sektoren
richtig ordnen"*). Der **Betrag** verschiebt sich, und zwar nach oben: Auf die beiden Fälle,
die `spiel.md` durchrechnet, wirkt der Faktor 1,34825 als `7.288 → 7.837` und
`5.464 → 6.189`. Beide Zahlen sind **Nachrechnungen auf `spiel.md`s Beispielwerten aus WDI 1995
und nicht die Werte des Jahrgangs** — sie zeigen die Größe der Verschiebung, nicht ihr
Ergebnis. Die Reihenfolge Landwirtschaft vor Industrie hält in beiden Fassungen.

**Ein per-Ausführer-Deflator wäre genauer und ist nicht zu haben — gemessen, nicht vermutet.**
`NE.EXP.GNFS.KD` liegt für die Volksrepublik China im Fenster 1997–2021 **allein für 2015** vor;
die übrigen 24 Stützstellen sind `null` (Abruf 2026-09-04, einzeln nachgefragt, weil eine erste
Sammelabfrage sich selbst widersprach). Für Brasilien, Deutschland und die USA ist die Reihe
vollständig. Die Wahl des Weltindex ist damit **erzwungen und nicht bevorzugt**, und das gehört
hierher, weil sie sonst wie Bequemlichkeit aussieht. Was übrig bleibt, ist der Abstand zwischen
dem Weltindex und den wahren bilateralen Deflatoren; er ist **ungemessen** und die ehrliche
Restgrösse dieses Wegs. Er ist zweiter Ordnung gegen die 2.203, die der Weg beseitigt — dass er
klein *ist*, behaupte ich nicht.

**Reihe 3 (PWT-Kapitalstock, 15 Adressen): ausgewiesene Nichtentscheidung.** Weder Einheit noch
Basisjahr sind gemessen; vier PDF-Abrufe aus drei Verzeichnissen kamen unlesbar an
(`daten/einheitenbefund-pwt-baci.md` Abschnitte 3 und 4). Ich entscheide hier **nichts**, weil
jede Wahl geraten wäre, und schreibe stattdessen die drei Teile hin, die die Entscheidung
tragen:

- **Die fehlende Zahl:** Einheit und Basisjahr der Kapitalstockvariablen in PWT 11.0. Es kostet
  **einen** lesbaren Auszug aus `pwt110_user_guide_to_data_files.pdf` (Dataverse-Kennung
  554025) oder aus dem Bezeichnungsblatt von `pwt110.xlsx` (554105).
- **Der Adressat:** der Datenbauer, und über ihn der Betreiber — die Sperre ist die
  Werkzeugkette und nicht die Quelle. Es ist die zweite Sperre dieser Art neben dem
  IWF-Volltext.
- **Die Folge, und sie ist nach Größe geordnet.** Die **Einheit** ist der schwere Teil: Steht
  der Kapitalstock in Millionen statt in Tausend USD, ist der Faktor 1.000 und nicht 1 — drei
  Größenordnungen, still. Das **Basisjahr** ist der leichte: Ein Unterschied zwischen 2015 und
  2017 oder 2021 verschiebt alle 15 Adressen um **denselben** Faktor in der Größenordnung
  weniger Prozent. Beides trifft **keine Sollreihe** — Reihe 3 ist nach der Reihenliste `Start`
  und trägt keinen Prüfgegenstand —, wirkt also nicht auf Maß 4, sondern über `korbwert` auf
  `marktkorb` und `fondsvermoegen`. Ein gemeinsamer Faktor auf allen 12 Körben kürzt sich in
  `fonds.marktanteil` heraus und wird bei `startkapital` und `stufenweite` mitkalibriert; **was
  er nicht tut, ist sich in `marktkorb` herauszukürzen**, denn dort stehen 12 Körbe neben 4
  `anleihewert`, die aus Reihe 1 kommen und nicht mitwandern. Die Mischung der 16 Marktwerte
  verschiebt sich also, und mit ihr das Verhältnis von Korb- zu Anleihesteckplätzen.
- **Solange das offen ist**, bleibt in `daten/reihen.toml` bei Reihe 3 `art = "ungemessen"`
  richtig, und der Jahrgangsbau darf für sie **keinen** Faktor einsetzen. T24 kennzeichnet
  Lücken, statt sie zu füllen; das ist hier der Fall.

**Die Folge für Paket 0002, ausgeschrieben, weil es daran hängt: T47, T48 und T50 bleiben
unberührt.** Kein Wort, keine Formel, keine Zeile in einer ihrer Tabellen ändert sich, und der
Grund ist eine Eigenschaft des gewählten Wegs und keine Zusage:

- **T47** rechnet ausschliesslich auf Zustandsgrößen. Die Deflationierung liegt in
  `werkzeuge/aufbereitung` und ist abgeschlossen, bevor der Kern die erste Zahl sieht. `wert`,
  `korbwert`, `anleihewert`, `waehrungswert`, `markt`, `stufenwert`, `positionswert`,
  `beteiligung_wert` und `fondsvermoegen` stehen unverändert.
- **T48** führt `handelsvolumen(l)` als Klasse 2. Das war bisher eine Behauptung und ist jetzt
  eine Tatsache — die Zeile ändert sich gerade deshalb **nicht**.
- **T50** zählt drei Skalenübergänge. Ein Deflator ist keiner: Er führt von Klasse 2 nach
  Klasse 2, und er läuft ausserhalb des Kerns. Es bleiben drei.

**`kern::werte` kann damit unverändert gebaut werden, und Paket 0002 kann unverändert zurück
auf `offen`.** Seine fünf Leser aus T47 Punkt 3 sehen dieselbe Zahl wie vorher; was sich
geändert hat, ist, was sie **bedeutet**. Das ist der ganze Zweck dieses Wegs: Die Korrektur
sitzt an der einzigen Stelle des Vorhabens, an der sie den teuersten Baustein nicht berührt.

**T6 — Genau eine Rundungsregel, `/` auf Zustandsgrößen ist verboten, und der Nenner null
ist ein harter Fehler.** Alle Divisionen laufen über `teile_gerundet(zaehler, nenner)` mit
Rundung **auf halbe Beträge von null weg**.

**Die Regel bleibt, ihre Begründung wechselt die Sprache.** Die Vorfassungen begründeten sie
mit Rusts Divisionsverhalten. C++ verhält sich seit C++11 genauso: `/` liefert für
ganzzahlige Operanden den algebraischen Quotienten mit abgeschnittenem Bruchteil, schneidet
also **gegen null** ab (ISO/IEC 14882, `[expr.mul]`; vor C++11 war es für negative Operanden
implementierungsabhängig, weshalb der Sprachstand aus T1 hier mitbindet und nicht nur eine
Bequemlichkeit ist). Damit gilt unverändert derselbe Einwand: Abschneiden gegen null ist über
dem Vorzeichen unsymmetrisch — bei einem Fonds, der nach `spiel.md` ausdrücklich long **und**
short sein können soll, würde es eine Richtung still bevorzugen und Maß 2 verfälschen.

Ebenso verpflichtend: `mal_geteilt(a, b, c)` rechnet `a·b/c` über einen
**`__int128`**-Zwischenwert (ADR 0011, Massnahme 3); die naive Form läuft bei Beträgen in
Cent mal Anteilen in Zehntausendsteln über. Ein nachträglicher Überlauftest käme dafür zu
spät — das Produkt wäre dann schon gebildet und nach T7 still umgebrochen.

**Schreibweise für den Rest des Dokuments:** `i128` steht überall als Kurzform für
`__int128`, so wie im Kern der gleichlautende Aliasname dafür steht. `__int128` ist eine
Erweiterung des Typsystems, nicht des Sprachmodus — es bleibt unter `-std=c++20` verfügbar,
und `-Wpedantic` ist nach T2b genau deswegen abgeschaltet.

**T6b — Die Divisionsform ist vorgeschrieben: Vorzeichen zuerst, dann genau eine
vorzeichenlose 128-Bit-Division auf den Beträgen.** Also `betrag()` auf Zähler und Nenner, ein
`unsigned __int128`-Quotient, der Rest als `az − ganz·an` statt als zweite Operation, die
Aufrundungsbedingung als `rest ≥ an − rest` statt als `2·rest ≥ an`, und das Vorzeichen zum
Schluss.

Das ist keine Geschmacksfrage, sondern die Antwort auf den Geschwindigkeitseinwand aus T1.
Die 947 ns der Messung sind **eine** Umsetzung, nicht die Sprache, und ADR 0011 vermutet als
Ursache einen fehlenden `__int128`. Das trifft nicht zu: Die gemessene C++-Fassung benutzt
`__int128` (`messung-stack/cpp/schritt.cpp`, Zeilen 21–31). Der nachweisbare Unterschied
liegt eine Ebene tiefer, und er steht im Erzeugnis statt in der Vermutung — `objdump -d` über
die beiden abgelegten Programme in diesem Lauf ausgeführt:

| Umsetzung | Divisionsform | Aufrufe der Übersetzerhilfe |
|---|---|---|
| `messung-stack/cpp/schritt` | signiert dividieren **und** Rest nehmen | `__divmodti4` |
| `messung-stack/rust/schritt` | Vorzeichen zuerst, dann Beträge dividieren | `__udivti3` |

Eine 128-Bit-Division ist auf x86-64 kein Befehl, sondern ein Aufruf in die Laufzeitbibliothek
des Übersetzers, und die **vorzeichenlose** Form ist die billigere: Die signierte normalisiert
zuerst die Vorzeichen und ruft dann dieselbe unsignierte Routine. Dazu kommt in der
C++-Fassung ein zusätzliches 128-Bit-Produkt für `rest_betrag * 2`, das die hier
vorgeschriebene Form nicht braucht — und das nach der eigenen Anmerkung in `festkomma.hpp`
bei einem Nenner nahe der `i128`-Grenze selbst überlaufen könnte.

**Was ich damit nicht behaupte:** Ich habe die schnellere Form nicht nachgemessen; der
Abstand von 1,92 könnte auch nur teilweise daran hängen. Die Vorgabe steht trotzdem, weil sie
unter jedem Übersetzer die kleinere Rechnung ist und weil sie den Überlauf in der
Aufrundungsbedingung gleich mit ausräumt. **Entschieden wird die Frage nicht hier, sondern
durch `ticks_je_sekunde` aus dem ersten Prüfstandsbefund** (Abschnitt 9, Berichtspflicht).

Mechanischer Nachweis: `objdump -d` über die Kernbibliothek darf `__divti3` und
`__divmodti4` **nicht** enthalten; erlaubt ist allein `__udivti3`. Die 64-Bit-Divisionen der
Zähler und Restdauern erzeugen keinen solchen Aufruf und stören die Prüfung nicht.

**`nenner == 0` bricht ab und wird nie still zu null.** Befund 2 der zweiten Prüfung
entstand genau an dieser Stelle: Ein Rückvergleich mit einem Fonds ohne Vermögen brauchte
dieses Vermögen als Nenner. Ein stiller Ersatzwert hätte den Fehler in eine falsche Zahl
verwandelt statt in einen Abbruch; die Behebung gehört nach T38 in den Modus und nicht in
die Divisionsregel, aber die Regel bleibt die Wand, gegen die ein solcher Fehler läuft.

**T7 — Überlauf erzeugt nie still eine falsche Zahl.** Die Vorgabe behält Nummer und Sinn;
ihr Mittel wechselt mit der Sprache. Rust hätte sie mit `overflow-checks = true` im
Freigabeprofil erledigt — **eine** Einstellung. In C++ sind es vier Massnahmen, drei davon
aus ADR 0011 und eine, die dort fehlt.

**Massnahme 1 — `-fwrapv` in jedem Profil.** Damit ist vorzeichenbehafteter Ganzzahlüberlauf
als Umbruch im Zweierkomplement **definiert**. Die eigentliche Gefahr ist nämlich nicht der
Überlauf, sondern was ein Optimierer aus seiner angeblichen Unmöglichkeit folgert: Ohne
`-fwrapv` darf er Vergleiche wegwerfen, die „nicht eintreten können", und aus einem
Zahlenfehler wird ein weggefallener Programmzweig. Der Schalter steht in
`werkzeugkette.cmake` und nicht nur im Runner — ein Determinismusschalter, der allein im
Nachtlauf gilt, ist keiner.

**Massnahme 2 — `-fsanitize=undefined,address` im Testprofil**, mit
`-fno-sanitize-recover=all`, damit ein Fund ein Abbruch wird und keine Meldung, die ein
grüner Testlauf überschreibt. Der Prüfstand läuft darüber. Weil ein Sanitizer nur findet,
was er selbst übersetzt hat, wird der Kern für die Proben ein **zweites Mal** übersetzt
(`kern_geprueft`); linkten die Proben die ungeprüfte Bibliothek, sicherte die Massnahme den
Testcode ab und nicht den Code, um den es geht.

> **Und hier ist ADR 0011 zu widersprechen, in genau einem Punkt.** Dort steht, ein Überlauf,
> der trotz `-fwrapv` unbeabsichtigt ist, werde durch Massnahme 2 „im Nachtlauf laut statt
> still". **Das trifft nicht zu.** Seit GCC 8 schaltet `-fwrapv` die Prüfung
> `-fsanitize=signed-integer-overflow` ab — der Sanitizer meldet nur *undefiniertes*
> Verhalten, und `-fwrapv` hat den Überlauf gerade definiert. Die beiden Massnahmen heben
> sich an dieser einen Stelle gegenseitig auf; genau deshalb hat der Linux-Kernel seine
> UBSan-Überlaufprüfungen wieder ausgebaut, nachdem er `-fno-strict-overflow` gesetzt hatte.
>
> **Was Massnahme 2 deshalb wirklich leistet — und es ist trotzdem viel:** Sie deckt den
> Adressen-Sanitizer ab und die übrigen UB-Klassen (Schiebeweiten, Ausrichtung,
> Feldgrenzen, Nullzeiger). Das ist genau die Fehlerklasse, die C++ nach T1 gegenüber Rust
> offen hat, und sie ist der Grund, die Massnahme unverändert zu behalten. Sie ist nur
> **nicht** die Antwort auf den Überlauf, als die ADR 0011 sie einführt.

**Massnahme 3 — `__int128` für jeden Zwischenwert** einer Multiplikation-Division, nie ein
nachträglicher Test auf Überlauf (T6, T6b).

**Massnahme 4 — geprüfte Arithmetik im Kern. Sie schliesst die Lücke, die Massnahme 2
offenlässt, und ohne sie hätte das Vorhaben keinen Ersatz für `overflow-checks = true`.**
Drei Formen, alle vom Übersetzer unabhängig, weil sie ausdrücklich prüfen statt sich auf
undefiniertes Verhalten zu verlassen. Sie sind nach der **Rechenart** geschnitten und nicht
nach der Stelle, damit keine Art zwischen ihnen liegen bleibt: die Verengung jedes
128-Bit-Zwischenwerts (1), die Strichrechnung auf `i64` (2), die Multiplikation ohne
folgende Division (3).

1. **Die Verengung von `__int128` auf `i64` ist der Prüfpunkt.** Jeder Wert, der aus einem
   128-Bit-Zwischenwert in eine Zustandsadresse zurückkehrt, läuft durch einen Wächter, der
   gegen `I64_MIN`/`I64_MAX` prüft und bei Verletzung **abbricht** statt zu kappen. Weil
   T6 jede Multiplikation-Division ohnehin über `__int128` führt, liegt der weitaus grösste
   Teil aller Überlaufgelegenheiten genau auf diesem Weg — die Prüfung ist damit kein
   Flickwerk, sondern sitzt an der Engstelle.
2. **Was nicht über `__int128` läuft — Additionen und Subtraktionen auf `i64` —, benutzt
   `__builtin_add_overflow` und `__builtin_sub_overflow`.** Sie rechnen in unendlicher
   Genauigkeit und melden, ob das Ergebnis in den Zieltyp passt; `-fwrapv` berührt sie
   nicht, weil sie kein undefiniertes Verhalten auslösen, sondern eines abfragen.
3. **Auch eine Multiplikation ohne nachfolgende Division läuft über `__int128` und den
   Wächter aus 4.1**, nämlich über `mal(a, b)` in `kern/include/kern/festkomma.hpp`, gebaut
   wie `mal_geteilt`: Produkt als `i128`, Rückkehr durch `intern::nach_i64`. Der
   Zwischenwert kann dabei nicht selbst überlaufen, weil `|a·b| ≤ 2^126`, also rund
   `8,5·10^37`, unter der `i128`-Grenze `1,7·10^38` bleibt — dasselbe Argument, das
   `potenz` in derselben Datei schon führt.

**Punkt 3 ist in dieser Fassung nachgetragen, und die Lücke davor war keine Formalie.** Die
Aufzählung nannte „Additionen und Subtraktionen" und liess damit die **blanke Multiplikation
zweier `i64`** zwischen den Massnahmen liegen: Massnahme 3 deckt die Multiplikation *mit*
nachfolgender Division, 4.1 die Verengung eines 128-Bit-Werts, 4.2 die Strichrechnung — und
Massnahme 1 macht ihren Überlauf gerade **definiert**, also still. `overflow-checks = true`
der Vorfassung deckte mit *einer* Einstellung jede Rechenart; hier wäre mit der Bauart ein
Stück Inhalt verschwunden. Der Weg in den Fehler steht im Dokument selbst:
`tsd_in_cent(x) = x · 100.000` (T50) hat keine Division, keinen 128-Bit-Zwischenwert und
keine Addition, `positionswert` rechnet davor `stufen · stufenwert` (T48) ebenso blank, und
das Ergebnis geht nach T47 unmittelbar ins Fondsvermögen — also in Abrechnung, Mandat,
Todesart 1 und die Botzielgröße `B`. Die Invariante `0 < markt.wert < 9,2·10^13` (T30
Prüfung 2) fängt davon **einen** Aufrufer ab, am Rundenende und nicht auf der Fondsseite; ein
Detektor nach der Tatsache ist nicht die Zusage, die T7 in seiner Überschrift gibt.

**Warum `mal` und nicht `__builtin_mul_overflow`:** Beides schliesst die Lücke. Der
`i128`-Weg hat denselben Abbruchpfad wie 4.1 statt eines zweiten, hält die ganze
Punktrechnung bei *einer* Regel, und `mal` steht neben `mal_geteilt` in der Datei, die T6
ohnehin als einzige Rechenstelle des Kerns ausweist.

**Die Vorgabe gilt für jede Multiplikation, nicht für eine Liste von Stellen.** Der
Weltschritt multipliziert schon in der Preismischung (T28) blank, dazu `fondsanteil`,
`anleihekurs` und `lobbypunkte_aus_geld` (T48, T50), und jede neue Formel bringt weitere; eine
Aufzählung wäre hier die Form, die beim nächsten Zusatz still falsch wird. Der Nachweis ist
deshalb eine **Zuordnung**, und ich habe sie in diesem Lauf einmal ausgeführt:
`grep -rn ' \* ' kern/src kern/include` liefert heute **52 Zeilen**, und jede fällt in eine
von vier zugelassenen Arten — Adressrechnung auf `Index`/`std::size_t` (`zustand.hpp`,
`zustand.cpp`), vorzeichenlose Rechnung in `zufall.hpp` und `pruefsumme.hpp` (die beiden
Ausnahmen unten), `i128`-Zwischenwert innerhalb von `festkomma.hpp`, oder Fliesstext in einem
Kommentar. Eine fünfte Art — zwei `i64` mit Größenbedeutung nach T5 — kommt heute **nicht**
vor, weil `kern::werte` noch nicht gebaut ist; genau dort entsteht sie. Ein solcher Treffer
ausserhalb von `festkomma.hpp` ist ein Befund. `kern/test` steht nicht unter der Regel,
sondern prüft sie; dort kommen sechs weitere Trefferzeilen dazu, davon zwei echte
Multiplikationen der Form `static_cast<i64>(platz) * 10`, mit denen eine Probe sich ihre
Eingabewerte aus einem Schleifenindex baut.

**Der Abbruch ist eine Ausnahme und kein `std::abort`**, und das aus zwei mechanischen
Gründen: Bei der Auswertung zur Übersetzungszeit macht ein `throw` den Ausdruck zu keiner
Konstante — ein `static_assert`, das den Abbruchpfad trifft, ist damit ein
**Übersetzungsfehler** statt eines unprüfbaren Falls; und ein Signal lässt CTest nicht als
erwartetes Ergebnis verbuchen, eine Ausnahme dagegen fängt die Probe und weist sie nach. Was
nicht nachweisbar ist, ist in dieser Fabrik nicht gebaut. Still ist der Abbruch trotzdem
nicht: Er hat keinen Rückgabewert, den jemand versehentlich weiterrechnet.

**Zwei Stellen brechen absichtlich um, und sie sind die Ausnahme von T7:** die Prüfsumme aus
T12 und der Zufallserzeuger aus T11. Beide rechnen auf **vorzeichenlosen** Typen, deren
Umbruch in C++ seit jeher definiert ist und deren Rechenvorschrift ihn ausdrücklich verlangt.
Sie bekommen keinen Wächter — ein Wächter dort wäre kein Schutz, sondern ein Fehler.

Die Kosten sind wenige Prozent und in Abschnitt 10 eingerechnet.

**Quellen zu Massnahme 2**, beide abgerufen am 2026-09-02:
GCC-Dokumentation zu `-fsanitize=signed-integer-overflow` und `-fno-sanitize-recover`
(<https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html>) — sie beschreibt die
Prüfung, **erwähnt die Wechselwirkung mit `-fwrapv` nicht**, weshalb sie hier steht;
der Beleg für die Abschaltung ist der Kernel-Patch „ubsan: remove overflow checks"
(<https://lkml.iu.edu/hypermail/linux/kernel/2102.1/03333.html>): *„Since GCC 8.0
-fsanitize=signed-integer-overflow doesn't work with -fwrapv. -fwrapv makes signed overflows
defines and GCC essentially disables ubsan checks."* Die Überlaufbausteine aus Massnahme 4
sind in
<https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html> beschrieben.

**T52 — Dieselbe Aktionsfolge ergibt auf jeder Zielplattform denselben Zustand, und in C++
ist das eine Vorgabe statt einer Selbstverständlichkeit.** *Neu in Fassung 7.*

Warum die Anforderung überhaupt noch gilt: Der Speicherstand ist unverändert **Startwert
plus Aktionsfolge** und nicht der Zustand (Frontmatter, **T22**). Ein Spielstand, der auf einem
Rechner geschrieben und auf einem anderen geladen wird, wird also **nachgerechnet** — läuft
die Rechnung dort anders, ist der Spielstand still ein anderer. T30 Prüfung 3 vergleicht die
Prüfsummen deshalb über die Zielplattformen hinweg; das bleibt so.

Rust hatte die Eigenschaft geschenkt, weil seine Ganzzahltypen überall dieselbe Breite
haben. C++ hat sie nicht geschenkt, und die vier Stellen, an denen sie verloren geht, sind
benannt:

1. **Nur Typen fester Breite aus `<cstdint>`** in jedem Wert, der eine Zustandsadresse
   erreicht oder in eine Formel eingeht: `std::int64_t`, `std::uint64_t`, `std::uint8_t`.
   **`int`, `long`, `unsigned` und `std::size_t` sind dort verboten.** `long` ist unter
   Windows 32 Bit und unter Linux 64 Bit — das ist die klassische Falle und die einzige
   dieser vier, die schweigend eine falsche Zahl erzeugt statt eines Warnhinweises.
2. **Kein `char` in einer Rechnung.** Ob `char` vorzeichenbehaftet ist, entscheidet die
   Zielarchitektur. Wo ein Byte gemeint ist, steht `std::uint8_t`.
3. **Kein Wert aus `sizeof` oder einer Ausrichtung** in einer Formel des Kerns.
4. **Schiebeoperationen** sind zulässig und der Zufallserzeuger braucht sie. Sie sind hier
   ungefährlich, **weil** T1 auf C++20 festlegt: Seit C++20 ist die
   Zweierkomplementdarstellung vorgeschrieben und das Rechtsschieben negativer Werte als
   arithmetisches Schieben definiert. Unter einem älteren Sprachstand wäre beides
   implementierungsabhängig. Das ist der zweite Grund, aus dem der Sprachstand aus T1 bindet
   und keine Bequemlichkeit ist — der erste steht in T6.

**Beobachtung an ADR 0011, gemeldet und nicht selbst entschieden:** Das erste Argument des
ADR lautet, die plattformübergreifende Reproduzierbarkeit falle weg, *wenn* der Spielstand
den Zustand speichert statt der Aktionsfolge. Diesen Wechsel ordnet der ADR in seinen Folgen
aber nicht an, und mein Arbeitspaket auch nicht. **Bis er angeordnet ist, gilt die
Anforderung** — deshalb steht T52 hier statt eines gestrichenen Absatzes. Der Wechsel wäre
eine Erleichterung, keine Notwendigkeit: Die vier Regeln oben sind mechanisch und kosten den
Bauagenten nichts, den sie nicht ohnehin zahlt.

**T40 — Die Partielänge R ist eine Größe des Jahrgangs, keine Konstante des Codes, und
keine aus ihr abgeleitete Zahl steht als Literal irgendwo.** Das ist die architektonische
Antwort auf Befund 1, und sie ist die einzige, die dessen eigentlichen Preis vermeidet: Die
falsche Zahl war billig, ihre Verbreitung in zwölf abgeleitete Größen war teuer.

`R = manifest.stuetzstellen − 1` wird beim Laden des Jahrgangs gebildet. Aus R und sonst
nichts entstehen zur Laufzeit:

| Abgeleitete Größe | Formel | bei R = 24 |
|---|---|---|
| Ergebnisband „Mandat erfüllt" | `1.000 … R × 1.000` | 1.000 … 24.000 |
| Ergebnisband „überlebt" | `(R+1) × 1.000 … (R+1) × 1.000 + 3.000` | 25.000 … 28.000 |
| Ergebnisband „Todesart" | `30.000 + 1.000 … 30.000 + R × 1.000` | 31.000 … 54.000 |
| Partiedrittel (Maß 1, Fenster von Maß 3) | `1…⌊R/3⌋`, `⌊R/3⌋+1…⌊2R/3⌋`, `⌊2R/3⌋+1…R` | 1-8, 9-16, 17-24 |
| Gewinnschwelle Maß 2 | `E(p) ≤ R × 1.000` | 24.000 |
| Suchbotpartie | `R × (1 + 60)` | 1.464 |
| Kosten Maß 1 je Startwert | `30 · R(R+1)/2 + R` | 9.024 |
| `exogen_ab_runde` je Reihe | `bruchjahr − startjahr + 1` | DE-Leitzins: 1999 − 1997 + 1 = 3 |

**Eine Schranke gehört dazu, weil die Ergebnisskala von `spiel.md` an einer Stelle ein
echtes Literal trägt** — die 30.000, ab der die Todesarten zählen. Der Jahrgangsbau bricht
mit `R > 26` ab, statt eine Skala zu erzeugen, in der ein Wert zwei Bedeutungen trägt.

**Die Schranke steht seit Fassung 5 unverändert bei `R ≤ 26`, ist seither aber scharf statt
grosszügig, und sie ist dort nachgerechnet worden.** `spiel.md` Fassung 4 hat die
Kappung des Fehlbetrags gestrichen; das Band „überlebt" endet dadurch bei
`(R+1) × 1.000 + 3.000` statt bei `+ 2.000`. Der niedrigste erreichbare Wert des Todesbandes
ist `30.000 + (R + 1 − R) × 1.000 = 31.000`, unabhängig von R. Disjunkt sind beide Bänder
also genau dann, wenn `(R+1) × 1.000 + 3.000 < 31.000`, das heisst `R < 27`. Bei `R = 26`
endet „überlebt" bei 30.000 und lässt 999 Milli-Runden Luft; bei `R = 27` fiele sein oberes
Ende mit dem unteren Ende des Todesbandes zusammen. **Das breitere Band kostet damit keine
Runde Partielänge** — dieselbe Schranke, aber ohne Reserve.

Für das Fenster 1997–2021 ist das folgenlos, und `spiel.md` lässt das Fenster nur enger
werden, nie weiter. Es ist eine Wand, keine Einschränkung — aber es ist eine, die vor dem
Bau sichtbar sein muss und nicht danach.

**T8 — Preisniveau und Wechselkurs werden geführt und neu basiert.** Der Prüfjahrgang
beginnt nach `spiel.md` Fassung 3 im Jahr **1997**, also lange nach dem Plano Real; dort
tritt die Neubasierung nie ein. Sie bleibt trotzdem, weil `spiel.md` die Jahrgänge vor 1997
ausdrücklich als **Spieljahrgänge** erhält und Brasilien zwischen 1980 und 1994 rund zwölf
Nullen gestrichen hat. Regel: Übersteigt der Preisindex eines Landes das 100.000-fache
seines Startwerts, werden Index, Wechselkurs und alle nominalen Größen dieses Landes durch
1.000 geteilt und der Zähler `basiswechsel` erhöht.

**Welche Größen das sind, ist seit T49 abzählbar und steht deshalb hier statt in einer
Auslegung: genau fünf je Gebiet** — die drei Sektorpreise, das Preisniveau (Klasse 5) und
der Wechselkurs (Klasse 6). Sonst nichts. Die volkswirtschaftlichen Beträge stehen nach T5
Klasse 2 **zu konstanten Preisen des Jahres 2015**, sind also real und laufen nicht mit — und
sie laufen aus einem **zweiten**, unabhängigen Grund nicht mit, der seit T53 hier stehen kann:
Klasse 2 ist in konstanten **US-Dollar** ausgedrückt, hat also gar keine Dimension in der
Landeswährung, die eine Währungsreform des Gastlandes treffen könnte. Für die 40
Handelsströme gilt das erst, seit T53 sie beim Jahrgangsbau auf dieselbe Basis bringt; vorher
kamen sie in laufenden Preisen an, und dieser Absatz behauptete für sie eine Eigenschaft, die
sie nicht hatten. Die
Produktivität steht in Klasse 7 und darf es nicht (sonst senkte ein brasilianischer
Basiswechsel die Produktivität um drei Größenordnungen); Raten, Anteile, Personen,
Lobbypunkte und Zähler haben keine Währungsdimension; das Fondsgeld steht in US-Cent, also
im Numéraire, und ist von einer Währungsreform des Gastlandes nicht berührt. „Alle nominalen
Größen dieses Landes" war bis Fassung 5 eine Formulierung, die der Bauagent hätte auslegen
müssen; es sind fünf Adressen, und sie stehen hier namentlich.

Weil sie im Prüfjahrgang nie greift, wäre sie ungeprüfter Code. **Auflage an den
Testentwickler:** Mindestens eine Partie im Regressionsbestand (T31) läuft auf einem
Spieljahrgang 1980 und durchläuft einen Basiswechsel. Ein Zweig, den der Nachtlauf nie
betritt, ist ein Zweig, den niemand kennt.

**Der Rückvergleich läuft für Preise und Wechselkurse auf Jahresänderungsraten in
Basispunkten, nicht auf Niveaus.** Ein prozentualer Fehler auf einem Niveau, das über zwei
Jahrzehnte um eine Größenordnung wandert, misst den Anfang und nicht die Maschine.
`spiel.md` hat diese Vorgabe in Fassung 3 übernommen und beziffert (300 bp); die
Rechenvorschrift steht in T42, einschliesslich der Korrektur, die eine Neubasierung
innerhalb der Reihe erzwingt.

**T9 — Feste Reihenfolge, keine streuenden Behälter.** Länder, Sektoren, Instrumente und
Handelspaare sind dichte Indexlisten: **`std::array` fester Länge**, angesprochen über eigene
Indextypen `LandId`, `SektorId`, `InstrumentId` — je ein `enum class : std::uint8_t` oder ein
Hüllentyp über `std::uint8_t`, damit zwei Indexarten sich nicht stillschweigend vermischen.
Ein blanker `int` als Index ist ein Befund.

**Verboten im Kern sind `std::unordered_map` und `std::unordered_set`.** Ihre
Durchlaufreihenfolge hängt von Streuwert, Einfügefolge und Standardbibliothek ab und ist
damit genau das, was T9 ausschliesst. Wird eine Zuordnung gebraucht, ist es **`std::map`**
oder **`std::set`** — die geordnete Entsprechung zu Rusts `BTreeMap`, mit einer
Durchlaufreihenfolge, die eine Eigenschaft des Schlüssels ist und keine des Speichers.

**Zwei Fallen, die C++ zusätzlich stellt und Rust nicht:**

- **`std::sort` ist nicht stabil.** Wo sortiert wird — der Prüfstand tut es in T39 —, ist
  entweder `std::stable_sort` zu nehmen oder nach einem Schlüssel zu sortieren, der die
  Elemente **eindeutig** ordnet. Eine Sortierung mit Gleichständen ist sonst eine
  Reihenfolge, die der Übersetzer wählt.
- **Die Auswertungsreihenfolge von Funktionsargumenten ist unbestimmt.** Solange die
  Argumentausdrücke des Kerns seiteneffektfrei sind, ist das folgenlos — und genau deshalb
  ist es eine Vorgabe: **Kein Argumentausdruck im Kern verändert etwas.** Kein `++i` und
  keine Zuweisung innerhalb eines Aufrufs.

Die sechs Schritte der Runde laufen in der Reihenfolge aus `spiel.md`, Abschnitt
„Die Schleife", und diese Reihenfolge steht als benannte Konstantenliste im Code, damit ein
Umstellen sichtbar wird.

**T10 — Der Weltschritt zieht nicht.** Nach `spiel.md` ist jede Regel eine Schwelle, ein
Zähler oder eine Rechnung; auch der Innerjahresausschlag folgt „deterministisch aus der
Jahresbewegung und der historischen Schwankungsbreite". Also gilt:
`schritt(zustand, aktionen, modus)` ist eine **reine Funktion ohne Zufallsargument**. Das
ist die billigste Art, Anforderung 1 zu erfüllen, und sie macht den Rückvergleich zu einer
exakt wiederholbaren Rechnung.

**T11 — Zufall gibt es nur an zwei Stellen, und er hängt an einem Wurzelstartwert.**
Erstens die Streuung der Startjahrgänge (ein Spiel soll nicht immer identisch beginnen),
zweitens die Bots und Stichproben des Prüfstands. Der Erzeuger ist selbst geschrieben —
SplitMix64 zur Ableitung, xoshiro256\*\* zur Erzeugung, zwanzig Zeilen, im Repo
festgeschrieben, **keine Fremdbibliothek** (T2): Ein Versionssprung eines fremden
Zufallskastens würde sonst jede gespeicherte Partie entwerten.

**Auch `<random>` aus der Standardbibliothek ist ausgeschlossen, und der Grund ist
schärfer als der allgemeine.** Der Standard legt die *Erzeuger* fest (`std::mt19937` liefert
überall dieselbe Folge), aber **nicht die Verteilungen**: Was
`std::uniform_int_distribution` aus einer Bitfolge macht, ist der Standardbibliothek
überlassen und unterscheidet sich zwischen libstdc++ und libc++. Ein Spielstand, der auf
einer Verteilung beruht, wäre damit an eine Standardbibliotheksfassung gebunden statt an
eine Rechenvorschrift. Die Reduktion auf einen Wertebereich wird deshalb im Kern
ausgeschrieben und ist Teil des geprüften Codes.

Jeder Strom wird **abgeleitet**, nicht fortgeschrieben:

```
strom = splitmix64(wurzelstartwert, jahrgang_id, parameter_pruefsumme,
                   zweck_id, runde, index)
```

Ein fortlaufender Strom hätte die Eigenschaft, dass eine einzige neue Ziehung irgendwo alle
späteren Ziehungen verschiebt und damit den ganzen Regressionsbestand rot macht, ohne dass
sich etwas Inhaltliches geändert hätte. Das ist die Vorgabe, an der später der Unterschied
zwischen „verbessern" und „verändern" hängt. Die `zweck_id` ist eine benannte Aufzählung
(`JAHRGANGSSTREUUNG`, `ZUFALLSBOT`, `BUENDELZIEHUNG`, `SUCHBOT_KANDIDATEN`) und wird nie
über eine Zahl geschrieben.

**Im Modus `weltlauf` wird kein einziger Strom gezogen** (T38): Es gibt keine Bots, keine
Stichproben und keine Jahrgangsstreuung. Der Rückvergleich ist damit nicht nur
reproduzierbar, sondern startwertfrei.

**T12 — Kanonische Byteform und Prüfsumme.** `Zustand` wird über eine ausdrücklich
geschriebene Funktion in Bytes gefasst (feste Feldreihenfolge, `i64` in Little-Endian),
**nie über die Speicheranordnung der Struktur**. Darüber läuft FNV-1a-64, ebenfalls im
Kern implementiert. Diese Prüfsumme ist die Währung aller Regressionstests.

**In C++ ist die Abkürzung besonders naheliegend und deshalb ausdrücklich verboten:** ein
`memcpy` über die Struktur oder ein `reinterpret_cast` auf `unsigned char*` sind zwei Zeilen
und liefern eine Prüfsumme, die Füllbytes zwischen den Feldern und die Bytefolge des
Zielsystems mitnimmt. Füllbytes haben keinen festgelegten Inhalt — dieselbe Partie ergäbe
auf demselben Rechner zwei Prüfsummen. Die Byteform wird Feld für Feld geschrieben, und der
`reinterpret_cast` steht ohnehin auf der Grep-Liste aus T2b.

## 3. Trennung von Modell und Darstellung

**T13 — Die Bausteinrichtung ist die Trennung, und CMake erzwingt sie.**

```
kern            (keine Abhängigkeit)      Zustand, Regeln, Kette, Festkomma, Zufall, Prüfsumme
  ^
daten           -> kern                   Jahrgang laden, Sollreihen, Parameterdatei
  ^
schnittstelle   -> kern, daten            Protokoll, drei Zustandsebenen, Partieformat
  ^          ^
konsole      pruefstand                   Binärprogramme: Text und Protokoll / Bots und Maße
  ^
oberflaeche  -> schnittstelle             Binärprogramm (vertagt, ADR 0010)
werkzeuge/aufbereitung -> daten           einmal je Jahrgang: Rohdaten -> Jahrgang
```

Jeder Baustein ist ein eigenes CMake-Ziel mit eigenem Verzeichnis; die Pfeile sind
`target_link_libraries`, und die Sichtbarkeit der Kopfverzeichnisse folgt ihnen. **Wer nicht
verlinkt ist, findet die Köpfe nicht** — `kern` kennt weder Bildschirm noch Datei noch Uhr,
und dass das Modell die Sicht nie etwas fragt, ist damit keine Verabredung, sondern
scheitert am Übersetzer, sobald es jemand versucht.

*Der Unterschied zur Vorfassung, damit er nicht unbemerkt bleibt:* Ihr Bauwerkzeug hätte die
Richtung erzwungen, weil ein Baustein ohne Eintrag in der Abhängigkeitsliste gar nicht erst
gefunden wird. CMake erzwingt sie nur, solange die Kopfverzeichnisse **`PRIVATE`** bzw. sauber `PUBLIC`
vergeben sind; ein globales `include_directories()` auf Arbeitsbereichsebene würde die
Trennung still aufheben, ohne dass ein Bau fehlschlägt. **`include_directories()` ist
deshalb im ganzen Vorhaben verboten**; Kopfverzeichnisse werden ausschliesslich über
`target_include_directories` am jeweiligen Ziel vergeben.

**Dasselbe gilt für die Linkseite, und das ist die zweite Hälfte desselben Gedankens.** Ein
`link_libraries()` ohne Ziel wirkt auf jedes danach angelegte Ziel des Verzeichnisses und
seiner Unterverzeichnisse, und seit CMake 3.13 darf `target_link_libraries(<ziel> …)` in
einer anderen `CMakeLists.txt` stehen als der, in der `<ziel>` entsteht. Beides hängt einem
Baustein eine Abhängigkeit an, ohne seine eigene Datei anzufassen — die Kopfseite verliert
dabei die Trennung, die Linkseite die Nullabhängigkeit des Kerns aus T2. **`link_libraries()`
ist deshalb im ganzen Vorhaben verboten, und `target_link_libraries(<ziel> …)` steht
ausschliesslich in der `CMakeLists.txt` des Verzeichnisses, in dem `<ziel>` mit
`add_library` oder `add_executable` angelegt wird.** Damit ist die Abhängigkeitsliste eines
Bausteins wieder an genau einer Stelle lesbar, und der dritte Mustervergleich aus T2 hat
etwas, wogegen er prüfen kann.

Das sind die zwei Stellen, an denen diese Bauart eine Prüfregel braucht, wo die alte eine
Werkzeugeigenschaft hatte.

**Innerhalb von `kern` gibt es ein Modul, dessen Schnitt eine Vorgabe ist und keine
Geschmacksfrage: der Namensraum `kern::werte` mit dem Kopf `kern/include/kern/werte.hpp`.**
Dort und nur dort stehen die abgeleiteten Größen aus T48 und die drei Skalenübergänge aus
T50; `tsd_in_cent`, `lobbypunkte_aus_geld` und `lobbypunkte_aus_schaden` liegen im
Unternamensraum `kern::werte::intern` und sind damit als nicht öffentlich gekennzeichnet.

Damit ist die öffentliche Schnittstelle dieses Moduls **dieselbe Liste**, die T48 aufzählt —
ein Prüfer legt die Deklarationen in `werte.hpp` ausserhalb von `intern` gegen die Tabelle
und ist fertig. Das ist der mechanische Nachweis, den Befund 1 der Runde 6 gebraucht hätte
und den der Abzählschritt aus T45 nicht liefern konnte, weil er Adressen zählt und keine
Funktionen.

*Die Grenze dieses Nachweises gehört dazu:* `intern` ist eine Kennzeichnung, keine Sperre —
C++ hat für Funktionen eines Namensraums kein `pub`. Ein Aufruf von aussen übersetzt. Die
Sperre ist deshalb die Grep-Regel aus T50: Ein Treffer von
`grep -rn 'tsd_in_cent\|lobbypunkte_aus' kern/` ausserhalb dieses einen Moduls ist ein
Befund. Zwei schwache Nachweise an derselben Stelle sind hier billiger als ein starker, den
die Sprache nicht hergibt.

**T14 — Die Textoberfläche ist Teil des Produkts, nicht Werkzeug.** `konsole` spielt das
Spiel vollständig — Zustand in drei Ebenen, Aktionen, Speichern, Laden. Sie ist zugleich
die Schnittstelle, über die Agenten spielen (Anforderung 3), und der Rückfallweg, falls
die grafische Oberfläche je klemmt. Was `oberflaeche` zeigt, muss aus der Ausgabe von
`konsole` ableitbar sein; ist es das nicht, gehört es in den Kern.

## 4. Datenmodell

**T15 — `Zustand` ist ein Wert fester Größe ohne Speicheranforderung: 310 `i64`, also
2.480 Byte.** Feste Felder, `std::array` fester Länge, **kein `std::vector`, kein
`std::string`, kein Zeiger, kein `std::unique_ptr`**. Das Kopieren ist damit ein
Speicherumzug von 2,5 kB (etwa 200 Nanosekunden) — die Voraussetzung dafür, dass der
Prüfstand Millionen von Nachspielen aus Zwischenständen startet.

**Zwei `static_assert` machen daraus eine geprüfte Eigenschaft statt einer Beschreibung**,
und beide gehören in denselben Kopf wie der Typ:

- `static_assert(std::is_trivially_copyable_v<Zustand>)` — sie fällt in dem Augenblick, in
  dem jemand ein `std::vector` oder einen eigenen Kopierkonstruktor einbaut. Das ist der
  billigste Wächter des ganzen Datenmodells: Er verteidigt nicht die Grösse, sondern die
  Eigenschaft, aus der die Grösse folgt.
- `static_assert(sizeof(Zustand) == 2480)` — sie fällt bei Füllbytes und bei jeder
  Adressenzahl ungleich 310. Zusammen mit T12 heisst das: Die Struktur *ist* füllbytefrei,
  und die Byteform wird trotzdem Feld für Feld geschrieben. Der Gürtel ersetzt die
  Hosenträger nicht — die Prüfsumme darf auch dann nicht an der Speicheranordnung hängen,
  wenn diese zufällig passt.

Fünf Gebiete (USA, China, Deutschland, Brasilien, Restwelt), drei Sektoren, davon zwei mit
Handelszeilen, vier Politikinstrumente. **Jede Zeile nennt ihre Herkunft in `spiel.md`,
damit die Summe nachzählbar ist:**

| Gruppe | Felder | Anzahl | Herkunft in `spiel.md` |
|---|---|---:|---|
| je Sektor (3×) | Wertschöpfung, Kapitalstock, Beschäftigung, Sektorpreis | 12 | „Der Zustand", Je Land |
| Aggregat | Bevölkerung, Erwerbstätige, Produktivität, Preisniveau, Inflation, Leitzins, Wechselkurs, Staatsschuld, Haushaltssaldo | 9 | ebd. |
| politisch | Zustimmung, Aufsichtszähler, Einfluss | 3 | ebd. |
| Instrumente (4×) | Stand, anliegender Druck, Gegendruck, Restverzögerung | 16 | ebd. |
| Restdauern | `marktverbot_rest`, `lobbykosten_rest`, `regierungsdruck_rest` | 3 | Gegenkraft 1 (dritte Schwelle) und Gegenkraft 2 |
| Buchhaltung | `basiswechsel` | 1 | T8; Herkunft nach T46 |
| **je spielbarem Land** | | **44** | |
| **vier spielbare Länder** | | **176** | |
| **Restwelt** | Sektoren 12 + Aggregat 9 + `basiswechsel` 1; **keine** Instrumente, Zustimmung, Aufsicht, Einfluss, Restdauern | **22** | „Die Restwelt" |
| Handel | Gebiet × Gegenüber × handelbarer Sektor = 5 × 4 × 2 | 40 | „Handel" |
| Weltpreise | je handelbarem Sektor | 2 | „Was für die Preisbildung gelten muss" |
| Nachahmerzähler | Land × Sektor = 4 × 3 | 12 | „Der Fonds" |
| Marktkorb | `markt.wert`, `markt.rendite` | 2 | „Der Fonds", Marktrendite; Regel in T33 |
| Fonds, Aggregat | Kasse, Hebelstand, Sichtbarkeit, Anlegerbestand, Marktanteil | 5 | „Der Fonds" |
| Fonds, Überrendite | letzte drei Runden | 3 | ebd. |
| Positionssteckplätze | 12 Land×Sektor, 4 Währung, 4 Anleihe | 20 | ebd., T16 |
| Beteiligungen | 12 Land×Sektor × (Anteil, Restdauer des Ausstiegs) | 24 | Aktion 2 |
| Partie | Runde, Jahrgangskennung, Parametersatz-Prüfsumme, Mandatsstand | 4 | — |
| **Summe** | | **310** | |

Nachrechnung: `4 × 44 + 22 = 198` für die Gebiete, `40 + 2 + 12 + 2 = 56` für die Welt,
`5 + 3 + 20 + 24 = 52` für den Fonds, `4` für die Partie. `198 + 56 + 52 + 4 = 310`.
`spiel.md` nennt dieselbe Zahl und verweist für die Aufstellung hierher. **Dieselben 310
Adressen sind in T45 ein zweites Mal aufgeteilt, diesmal nach ihrer Herkunft** — die beiden
Summen laufen über dieselbe Menge und müssen beide aufgehen; dass die zweite es in Fassung 4
nicht tat, ist der Grund für T46.

**Die Restwelt trägt vier Adressen, die keine Regel liest** (`leitzins`, `wechselkurs`,
`staatsschuld`, `haushaltssaldo`). Sie stehen hier, weil der Aggregatblock für alle fünf
Gebiete gleich gebaut ist — gleichförmige Adressierung nach T17, dieselbe Begründung wie der
dauerhaft leere Steckplatz aus T16. Ihre Behandlung steht in T46, ihre Schreibregel
(`Vortrag`, kein anderer Lesezugriff) ebenfalls.

**`landespreis` bekommt keine Zeile, und das ist die Behebung von Befund 6, nicht ihre
Umgehung.** Die Größe ist nach `spiel.md` der Sektorpreis der Vorrunde. Sie hat deshalb
keine eigene Adresse, sondern einen eigenen **Lesezugriff** — siehe T39. Ein Feld dafür
wäre eine zweite Kopie derselben Zahl und damit eine Gelegenheit, sie auseinanderlaufen zu
lassen.

**T16 — Positionen sind Steckplätze, keine Liste.** Es gibt genau zwanzig mögliche
Positionen; eine Position ist eine vorzeichenbehaftete Stufenzahl auf einem festen Platz,
null heisst „keine". Damit entfällt jede Frage nach Höchstzahl, Reihenfolge und
Zusammenlegung, und der Zustand bleibt vergleichbar (T12).

**Ein Steckplatz ist dauerhaft leer:** die Währung USA. Der US-Dollar ist der Numéraire,
eine Position darauf wäre gegen sich selbst gerichtet. Der Platz bleibt für die
gleichförmige Adressierung (T17), die Zulässigkeitsprüfung bietet ihn nie an (T32).
Spielbar sind 19 der 20 Plätze; wer 20 zählt, zählt Adressen, nicht Möglichkeiten.

**T17 — Jede Größe hat eine stabile Adresse.** `land.DE.sektor.2.preis`,
`land.BR.instrument.zoll.stand`, `fonds.position.CN.1`, `handel.DE.CN.1`, `markt.rendite`.
Diese Adressen erscheinen im Protokoll, in der Kette, in den Testvorlagen und in der
Oberfläche. Sie sind Teil der Schnittstellenversion: Wer eine umbenennt, macht den
Regressionsbestand ungültig und braucht einen ADR.

**T17b — Der Adressbaum hat keinen Knoten `gebiet`, und `gebiet.<G>.` ist eine
Sammelschreibweise dieses Dokuments.** Vier Stellen benutzen ein Präfix `gebiet.…`, wo eine
Aussage für alle fünf Gebiete zugleich gilt. Es ist **keine Adresse**: Es erscheint in keinem
Protokoll, in keiner Kette, in keiner Testvorlage und in keiner Oberfläche, und ein
`detail gebiet.US` gibt es nach T20 nicht. Aufgelöst wird es so, und die Auflösung ist
vollständig:

| `<G>` steht für | aufgelöstes Präfix | Adressen |
|---|---|---:|
| eines der vier spielbaren Länder | `land.US.`, `land.CN.`, `land.DE.`, `land.BR.` | 4 × 44 = 176 |
| die Restwelt | `restwelt.` — ohne Kürzel, weder `gebiet.RW.` noch `land.RW.` | 22 |
| **zusammen** | | **198** |

Die 198 sind dieselbe Zahl wie die Gebietsspalte der Nachrechnung zu T15
(`4 × 44 + 22 = 198` für die Gebiete). Die Schreibung des Platzhalters folgt der Regel, die
dieses Dokument für `land.<L>.` gegen `land.<l>.` schon benutzt: **Grossbuchstabe** heisst
„ein beliebiges Gebiet" im Fliesstext, **Kleinbuchstabe** heisst „der Wert dieses
Funktionsarguments" (T48, `landespreis(g, s)`). Aufgelöst wird in beiden Fällen gleich.

**Warum diese Richtung und nicht die umgekehrte** — vier Gründe, jeder für sich tragend:

1. **T17 zählt die Adressform selbst auf** und schreibt `land.DE.sektor.2.preis` und
   `land.BR.instrument.zoll.stand`; ein Knoten `gebiet` kommt dort nicht vor. T20 nennt für
   `detail` ebenso `land.US` und `land.CN.sektor.1`.
2. **T45 widerspräche T46 innerhalb desselben Abschnitts.** Die Zeile `Vorgabe(T-Nummer)`
   führt als Beispiel wörtlich „`restwelt.basiswechsel` → 0 (T8)" — eine der elf Adressen,
   auf die T46 wenige Absätze später abschliessend zeigt. Eine der beiden Stellen müsste
   falsch sein, und keine ist es.
3. **Die Restwelt trägt im Präfix kein Kürzel.** `RW` kommt allein in den 40 Handelsadressen
   vor (`handel.RW.US.1`), dort als Bestandteil zwischen zwei Punkten und nicht als
   Blockpräfix. Ein `gebiet.RW.` gäbe der Restwelt eine zweite Schreibweise, ohne eine Regel
   zu vereinfachen.
4. **Der Preis wären nicht fünf Adressen, sondern 198.** `basiswechsel` ist nach T15 ein Feld
   des Gebietsblocks wie `leitzins` und `preisniveau` auch. Wer es `gebiet.US.basiswechsel`
   nennt, muss `gebiet.US.leitzins` mitnennen — sonst trägt ein und derselbe Block zwei
   Präfixe. Zu Ende geführt benennt die Gegenrichtung 198 der 310 Adressen um, macht damit
   nach T17 den Regressionsbestand ungültig und braucht einen ADR. Der Gewinn wäre null:
   dieselben Größen unter anderen Namen.

**Die beiden Folgen, beide nachgesehen und beide passend — kein „vermutlich".**
`daten/adressen.md` führt die fünf `basiswechsel`-Zeilen als `land.US.basiswechsel`,
`land.CN.basiswechsel`, `land.DE.basiswechsel`, `land.BR.basiswechsel` und
`restwelt.basiswechsel`, laufende Nummern 44, 88, 132, 176 und 198. Das ist genau die
Auflösung der T46-Zeile; das Verzeichnis bleibt **unverändert**, und auch seine Markierungen
hängen nicht daran — es rechnet unter *Was hier offen bleibt und hier nicht entschieden wird*
selbst vor, dass beide denkbaren Antworten dieselben Marken ergeben. Was dort nachzutragen
bleibt, ist allein die Antwort selbst; das ist Arbeit am Verzeichnis und gehört in ein
eigenes Paket. `gebietspraefix()` in `kern/src/zustand.cpp` hängt für die vier spielbaren
Länder `land.`, das Gebietskürzel und einen Punkt an und für die Restwelt `restwelt.`; der
Kommentar über der Funktion sagt es wörtlich. Das ist die maschinelle Fassung dieser Regel —
**passend, keine Änderung am Kern und kein ADR.**

**Die vier Fundstellen, abschliessend.** Jede wird von der Regel aufgelöst, keine ist eine
Ausnahme:

| Stelle | Form | löst auf zu |
|---|---|---|
| **T28**, Absatz zur Preismischung, „mit `landespreis` = … nach T39" | `lies_alt(gebiet.<G>.sektor.<s>.preis)` | 15 Adressen — 5 Gebiete × 3 Sektorpreise |
| **T39**, letzter Absatz, „Damit hat `landespreis` seinen Ort" | `lies_alt(gebiet.<G>.sektor.<s>.preis)` | dieselben 15 |
| **T46**, erste Tabellenzeile | `gebiet.<G>.basiswechsel`, alle fünf Gebiete | 5 Adressen — laufende Nummern 44, 88, 132, 176, 198 |
| **T48**, Nummer 13, `landespreis(g, s)` | `lies_alt(gebiet.<g>.sektor.<s>.preis)` | dieselben 15, `g` als Argument |

Die 15 sind an `daten/adressen.md` abgezählt und nicht gerechnet: Die laufenden Nummern 4, 8,
12, 48, 52, 56, 92, 96, 100, 136, 140, 144, 180, 184 und 188 tragen einen Sektorpreis.

**Zwei der vier Stellen schrieben bis zu dieser Fassung `gebiet.sektor.preis`** — ohne
Platzhalter, also ohne zu sagen, welches Gebiet und welcher Sektor gemeint ist. Sie tragen
ihn jetzt. Die Adressmenge bleibt 310 und die Tabelle in T46 Zeile für Zeile, wie sie war:
Diese Festlegung ändert keine Adresse, sondern sagt, was eine Schreibweise bedeutet.

**Die Zählung vor und nach der Regel, damit sie niemand nachrechnen muss** — denn „vier
Stellen" oben und der Befund einer Volltextsuche sind nicht dieselbe Zahl, und ohne diesen
Absatz muss die Differenz jeder Leser selbst auflösen. **Gezählt wird als fester Text, nicht
als Ausdruck** (`grep -oF`; der Punkt ist ein Punkt und kein Platzhalter), und die drei
Muster stehen in der Tabelle mit **geschütztem** Punkt (`gebiet\.`). Beides zusammen sorgt
dafür, dass keine Zeile dieses Absatzes selbst ein Treffer ist: Er nennt die ungeschützte
Form nirgends, auch nicht als Gegenbeispiel. Die Zahlen der Spalte „jetzt" gelten deshalb
für das Dokument einschliesslich seiner selbst.

| Muster | vor dieser Festlegung | jetzt |
|---|---:|---:|
| `gebiet\.<G>\.` | 1 | 8 |
| `gebiet\.<g>\.` | 1 | 2 |
| `gebiet\.` — die loseste Form, alles zusammen | 4 | 17 |

**Die 17 ist am 2026-09-05 nachgezählt und stand in der Fassung `a127600` um eins zu
niedrig.** Dieser Absatz führte die ungeschützte Form damals als Gegenbeispiel mit („statt
…") und war damit selbst der achtzehnte Treffer, den die Tabelle nicht mitzählte. Er nennt
sie nicht mehr; gezählt sind jetzt 17, und die Aufteilung darunter geht auf.

**Vorher vier, und es waren genau die vier T-Nummern der Tabelle oben:** T39 und T28 in der
Kurzform ohne Platzhalter, T46 als `<G>`-Zeile, T48 als `<g>`-Formel. Nachzusehen in der
Fassung vor dieser Festlegung, `git show ce59b8b^:specs/0016-…/technik.md`.

**Nachher siebzehn, und keine davon ist eine fünfte Stelle.** Zehn tragen einen
Platzhalter: **fünf** stehen in T17b selbst (die Überschrift und die vier Zeilen der
Fundstellentabelle), die anderen **fünf** verteilen sich auf dieselben vier T-Nummern wie
vorher — T46 trägt zwei, die Tabellenzeile und den Absatz, der von dort auf diese Regel
zeigt. Die restlichen **sieben** stehen sämtlich in T17b und sind **Gegenbeispiele, keine
Verwendungen**: dreimal `gebiet\.US` und zweimal `gebiet\.RW\.` in der Begründung, warum es
diese Adressen nicht gibt, einmal `gebiet\.sektor` als Zitat der alten Kurzform und einmal
`gebiet\.` mit Auslassungszeichen im Einleitungssatz. `4 → 17`, davon `13`
neu: `5 + 1` in T17b und T46 mit Platzhalter, `7` als Gegenbeispiel. **Keine Ausnahme.**

**T18 — Die Kette wird erzeugt, nicht rekonstruiert — und jede Größe der Sollmaske wird je
Runde genau einmal geschrieben.** Die Felder von `Zustand` sind ausserhalb des Kerns nicht
schreibbar; innerhalb schreibt niemand direkt, sondern über
`Schreiber::setze(adresse, wert, ursache, verzoegerung, beitrag)`. Jeder Aufruf hängt einen
`Ursachensatz` an:

| Feld | Inhalt |
|---|---|
| `runde` | in welcher Runde geschrieben |
| `ziel` | Adresse nach T17 |
| `alt`, `neu` | Werte in der Skala der Größe |
| `ursache` | `Aktion{nr}` \| `Instrument{land,instr}` \| `Gegenkraft{art}` \| `Markträumung{sektor}` \| `Vortrag{adresse}` \| `Jahrgang` |
| `verzoegerung` | wie viele Runden zwischen Ursache und Wirkung lagen |
| `beitrag` | Anteil dieser Ursache an der Änderung, in Promille |

Der `Schreiber` führt ein Bitfeld über alle 310 Adressen. **Ein zweiter Schreibzugriff auf
dieselbe Adresse in derselben Runde ist ein harter Fehler**, kein überschreibender Wert.
Eine Adresse, die sich nicht ändert, wird trotzdem geschrieben, mit der Ursache
`Vortrag` — „unverändert" ist eine Aussage und keine Lücke.

Das ist die maschinelle Fassung der Vorgabe aus `spiel.md` und zugleich die billigste Art,
die dortige Behauptung über **acht** rundenübergreifende Rückkopplungskanäle prüfbar zu
machen: Eine Rückkopplung innerhalb der Runde erzeugt zwangsläufig einen zweiten
Schreibzugriff und stirbt hier, statt als neunter Kanal unbemerkt zu entstehen.

**Acht statt sieben seit `spiel.md` Fassung 5**, und der Zuwachs ist die Ausbeute des
Befundes 1: Kanal 8 ist *Vermögen → Lobbybudget → Instrument → Kurs → Bewertung → Vermögen*.
Er war die ganze Zeit da; sein Glied „Bewertung" wurde erst zu einem gerechneten Schritt,
als T47 und der Abschnitt *Was ein Korb wert ist* die Bewertungsformeln hinschrieben. Das
ist der Grund, warum eine fehlende **Funktion** teurer ist als eine fehlende Zahl: Sie
versteckt einen Rückkopplungskanal. Kosten:
40 Byte je Runde, ein Bittest je Schreibzugriff.

**T39 — Es gibt zwei Lesezugriffe, und der falsche stirbt sofort.** Der `Schreiber` hält
den Zustand der Vorrunde (`alt`, unveränderlich) und den entstehenden Zustand (`neu`):

- `lies_alt(adresse)` — der Wert am Ende der Vorrunde. Immer verfügbar.
- `lies_neu(adresse)` — der Wert dieser Runde. **Ist die Adresse in dieser Runde noch nicht
  geschrieben, ist das ein harter Fehler**, kein stiller Rückgriff auf `alt`.

Der stille Rückgriff wäre die gefährlichere Bequemlichkeit: Er macht das Ergebnis von der
Reihenfolge der sechs Schritte abhängig, ohne dass irgendwo steht, dass es das tut. Mit dem
Abbruch ist die Zyklenfreiheit der Rundenreihenfolge kein Versprechen mehr, sondern eine
Eigenschaft, die jeder Lauf nachweist — auch der beim Käufer.

Damit hat `landespreis` seinen Ort: In der Markträumung (T28) ist er
`lies_alt(gebiet.<G>.sektor.<s>.preis)`, Präfix nach T17b. In Runde 1 ist das der Startwert
des Jahrgangs, nach `spiel.md` der Index 10.000.

**T38 — Der Modus ist eine Eigenschaft des Laufs, nicht des Zustands — und er bringt eine
Sollmaske mit.** Das ist die Behebung von Befund 2 auf der Architekturseite.

`spiel.md` kennt zwei Modi: `spielmodus` und `weltlauf`. Der Modus steht **nicht** im
Zustand. Zwei Gründe, beide zwingend: Er wäre ein 311. Feld und widerspräche einer Zahl, die
`spiel.md` nennt; und er beschreibt nicht die Welt, sondern die Art, sie zu rechnen. Er ist
Argument von `schritt` (T10), steht im Kopf des Speicherstands (T22) und in jedem Befund.
Wer eine Partie im falschen Modus nachrechnet, bekommt keine falsche Zahl, sondern einen
Prüfsummenbruch beim Laden.

Zu jedem Modus gehört eine **Sollmaske**: die Menge der Adressen, die in diesem Modus je
Runde geschrieben werden. Am Rundenende prüft der `Schreiber` zweiseitig — jede Adresse der
Maske genau einmal geschrieben, keine Adresse ausserhalb der Maske berührt. Beides ist ein
harter Fehler, kein Bericht.

| Block | Adressen | in `weltlauf` |
|---|---:|---|
| je spielbarem Land: Sektoren (12), Aggregat (9), Zustimmung (1), Instrumentenstand (4), `basiswechsel` (1) | 27 × 4 = 108 | **ja** |
| je spielbarem Land: Aufsichtszähler (1), Einfluss (1), Instrumente ohne Stand (12), Restdauern (3) | 17 × 4 = 68 | nein |
| Restwelt | 22 | **ja** |
| Handel | 40 | **ja** |
| Weltpreise | 2 | **ja** |
| Nachahmerzähler | 12 | nein |
| Marktkorb | 2 | nein |
| Fonds (Aggregat 5, Überrendite 3, Steckplätze 20, Beteiligungen 24) | 52 | nein |
| Partie: Runde, Jahrgangskennung, Parametersatz-Prüfsumme | 3 | **ja** |
| Partie: Mandatsstand | 1 | nein |

Nachrechnung: `108 + 22 + 40 + 2 + 3 = 175` in der Maske, `68 + 12 + 2 + 52 + 1 = 135`
ausserhalb, `175 + 135 = 310`. Die Maske `spielmodus` umfasst alle 310.

Was ausserhalb der Maske liegt, behält seinen Startwert — so verlangt es `spiel.md`. Der
Fonds startet im Weltlauf also nicht mit Nullvermögen, sondern er wird **überhaupt nicht
gerechnet**: kein Vermögen, keine Rendite, keine Überrendite, kein Anlegerabzug, keine
Todesart. Der Nenner aus Befund 2 entsteht nicht, statt abgefangen zu werden. Der Prüfstand
weist die Maskengröße in jedem Befund aus.

Der Modus wirkt an genau vier Stellen und nirgends sonst — Schritt 2 und 6 der Runde
entfallen, aus Schritt 5 laufen nur Zustimmung und Regierungswechsel, und die
Politikinstrumente kommen in Schritt 3 aus dem Jahrgang statt aus dem Lobbydruck. Der
Regierungswechsel wird gerechnet und ausgewiesen, schreibt aber nichts; dass das Orakel an
dieser Stelle blind ist, gehört nach `spiel.md` in jeden Befund und steht deshalb in der
Befundvorlage, nicht in einer Fussnote.

**T19 — Die Kette gehört nicht in den Zustand.** `schritt` liefert
`(neuer_zustand, kette_dieser_runde)`; die Sitzung sammelt die Ketten in einem `Verlauf`.
So bleibt `Zustand` klein und vergleichbar, und der Prüfstand kann die Ketten wegwerfen,
wenn er nur Ergebnisse zählt. Die Aufnahmekapazität je Runde ist fest; wird sie erreicht,
ist das ein harter Fehler und keine stille Kürzung — eine gekürzte Kette wäre eine Lüge
gegenüber dem Käufer.

## 5. Die drei Zustandsebenen (G8)

**T20 — Drei Abfragen, zwei Ausgabeformen, eine Quelle.** Jede Ebene entsteht aus
demselben Datentyp und wird entweder als Text (für Menschen und Logbücher) oder als
JSON-Zeile (für Agenten und Oberfläche) ausgegeben. Ganzzahlen bleiben Ganzzahlen; die
Skala steht im Kopf der Antwort, geteilt wird erst in der Sicht.

- **`uebersicht`** — eine Zeile je Gebiet, eine je Fonds, eine für den Markt:
  `DE | BIP 3.412 | Zins 250bp | Zoll 380bp | Haushalt -210bp | Fondsanteil 420 | Einfluss 1.700`
- **`detail <adresse>`** — ein Objekt vollständig, für **jede** adressierbare Einheit nach
  T17, nicht nur für Länder: `land.US`, `fonds`, `land.BR.instrument.zoll`,
  `land.CN.sektor.1`, `markt`.
- **`diff <von> <bis>`** — je geänderter Größe alt, neu, Änderung **und die Ursachenkette
  aus T18**, rückwärts aufgelöst bis zur auslösenden Aktion oder Gegenkraft, mit
  Verzögerung und Beitrag je Glied. Der Unterschied zweier Zustände sagt *was*, die Kette
  sagt *warum*; ausgegeben wird beides, massgeblich ist die Kette.

## 6. Maschinenschnittstelle und Partieformat

**T21 — Ein Befehl je Zeile, eine JSON-Antwort je Zeile, über Standardein- und -ausgabe.**
Kein Netzdienst, kein Anschluss, keine Zugangsdaten — damit auch keine Berührung mit
Hausregel 2. Befehle: `neu {jahrgang, modus, startwert}`, `zustand {ebene, adresse}`,
`aktionen` (die zulässigen dieser Runde), `setze {aktionen: […]}`, `runde`,
`kette {von, bis}`, `speichern {pfad}`, `laden {pfad}`, `pruefsumme`.
Jede Antwort trägt `schema_version`. Eine mitgeschriebene Sitzung ist damit von selbst
eine Testvorlage.

**T32 — Die Liste der zulässigen Aktionen hat eine kanonische Ordnung, und sie ist Teil der
Schnittstellenversion.** Sortiert wird nach `(Aktionsart 1…5, Zielkennung, Stufe)`; die
Zielkennung ist die feste Indexordnung aus T9. Grund: Maß 1 zieht nach `spiel.md` Aktionen
**ohne Zurücklegen aus der Liste der in dieser Runde zulässigen Aktionen** (T35). Wäre die
Ordnung eine Nebenwirkung der Erzeugung, hinge die Entscheidungsdichte an einer
Schleifenreihenfolge, die niemand aufgeschrieben hat. Die Ordnung ändern entwertet den
Regressionsbestand und braucht einen ADR.

**Die Liste wird einmal je Runde gegen den Rundenanfangszustand gebildet**, nicht nach jeder
gesetzten Aktion neu. Nach `spiel.md` hat keine Aktion einen Zeitpunkt innerhalb der Runde;
eine Liste, die sich zwischen zwei Steckplätzen ändert, würde genau diesen Zeitpunkt
einführen. Was ein Bündel als Ganzes betrifft — derselbe Steckplatz zweimal, Kasse
überzogen, mehr als drei Aktionen —, prüft `buendel_zulaessig(zustand, buendel)` gegen
denselben Rundenanfangszustand. Zwei Prüfungen, beide zustandsfrei innerhalb der Runde.

**Zwei Zulässigkeitsbedingungen kommen mit `spiel.md` Fassung 5 hinzu, und beide folgen aus
der Anteilsskala.** Eine Aktion 1 oder 2, nach der `fondsanteil(l, s)` über **10.000** läge,
ist unzulässig — ein Anteil über hundert Prozent ist kein Anteil, und Gegenkraft 1 und der
Preisstoß lesen genau diese Zahl. Ebenso unzulässig ist eine Aktion, nach der
`|stufen(p)| > stufen_max` wäre. Beide werden **im Bündel** geprüft, nicht je Aktion: Drei
Aufstockungen desselben Steckplatzes in einer Runde sind einzeln zulässig und zusammen nicht.
Der Invariantentest (T30 Prüfung 2, Schranke 7) prüft danach, dass die Zulässigkeitsprüfung
gehalten hat — die Prüfung schützt den Spieler, der Test schützt vor der Prüfung.

**T22 — Ein Speicherstand ist Jahrgang, Modus, Startwert, Aktionsfolge und Prüfsumme, nicht
der Zustand.** Datei: `{schema_version, jahrgang_id, modus, daten_pruefsumme,
parameter_pruefsumme, startwert, aktionen: [[runde, aktion…]], end_pruefsumme}`. Beim Laden
wird die Partie nachgerechnet und die Prüfsumme verglichen; weicht sie ab, meldet das
Programm einen Determinismusbruch, statt weiterzuspielen. Drei Gewinne auf einmal: Der
Käufer bemerkt einen Determinismusfehler zuerst, der Regressionsbestand **ist** der
Speicherordner, und eine Datei bleibt unter zwei Kilobyte. Kosten: R Weltschritte beim
Laden, bei R = 24 also 0,24 Millisekunden.

## 7. Datenschicht

**T23 — Der Jahrgang ist ein Erzeugnis, kein Programmteil.** `werkzeuge/aufbereitung`
liest die eingefrorenen Rohdateien und schreibt `jahrgang-<jahr>.bin`,
`sollreihen-<jahr>.bin` und ein `manifest.toml` mit SHA-256 je Ein- und Ausgabe, Quelle,
Lizenz und Abrufdatum. Der Bau des Spiels lädt **nichts** aus dem Netz. Der Jahrgang
enthält:

1. **Startwerte** für jede Zustandsgröße mit Datenanker; die Größen ohne Anker kommen aus
   der Tabelle „Jede Größe ohne Datenanker" in `spiel.md`, aus `parameter.toml`, aus dem
   Manifest oder aus **T46**. Welche Adresse woher kommt, entscheidet T45, und die Zuordnung
   ist dort abgezählt.

   **Zwei Startwerte entstehen aus je zwei Reihen und nicht aus einer, und beide behalten
   den Rang `Datenanker`.** Reihe 1 liefert ein BIP je Gebiet, Reihe 3 einen Kapitalstock je
   Gebiet; T15 führt von beidem **drei** je Gebiet. Dieselbe Regel bildet beide, mit den auf
   10.000 normierten Sektoranteilen aus Reihe 2:

   ```
   wertschoepfung[g][s] = mal_geteilt(bip_start[g],          sektoranteil[g][s], 10.000)
   kapitalstock[g][s]   = mal_geteilt(kapitalstock_start[g], sektoranteil[g][s], 10.000)
   ```

   Der Herkunftseintrag lautet `Datenanker(1 × 2)` beziehungsweise `Datenanker(3 × 2)`; die
   Zählung in T45 ändert sich dadurch nicht, weil beide Adressgruppen dort schon als Anker
   geführt sind. Die Regel für den Kapitalstock ist in Fassung 6 nachgetragen — `spiel.md`
   Fassung 5 verlangt sie, weil der Korbwert seit dem am Sektorkapitalstock hängt und der
   damit zum ersten Mal eine Größe ist, die jemand ausrechnen muss. Der Aufteilungsfehler
   ist derselbe wie bei der Wertschöpfung und für den Rückvergleich folgenlos, weil die
   zwölf Sektoranteil-Sollreihen aus **derselben** Normierung entstehen.

   **Die Vorgabetabelle der Fassung 4 an dieser Stelle ist gestrichen, und das ist kein
   Rückzug, sondern die Vermeidung eines Abbruchs.** Sie führte
   `land.<L>.instrument.<I>.druck` und `…​.rest` mit Startwert 0, je 16 Adressen, weil
   `spiel.md` sie damals nicht führte. `spiel.md` Fassung 4 hat alle 32 in seine Tabelle
   aufgenommen. Stünden sie hier weiter als Herkunftseintrag, trügen sie **zwei** Einträge —
   und genau das bricht den Jahrgangsbau nach T45 ab. Ihre Herkunft ist ab sofort `Entwurf`.

   Was bleibt, ist die Begründung, weil sie den Wert erzwingt statt ihn zu wählen, und weil
   ein späterer Leser sonst nicht weiss, warum dort 0 steht: Beide sind Laufzähler von
   Schritt 3, Druck entsteht nach `spiel.md` ausschliesslich durch Aktion 3, und vor Runde 1
   hat keine Aktion stattgefunden. Trüge eine der Adressen zu Partiebeginn einen Wert
   ungleich null, gäbe es eine Ursache ohne Aktion, und die Kette aus T18 könnte sie in
   Runde 1 nicht benennen. Nur die vier spielbaren Länder tragen Instrumente (T15), daher
   je 16 und nicht je 20. **Dieser Absatz ist ein Nachweis, kein Herkunftseintrag;**
2. **Sollreihen** für die 31 Reihen aus `spiel.md` plus den Handelsblock über 40 Ströme, je
   Reihe mit der Klassifikation aus T37;
3. **historische Politikpfade** für Leitzins, Zollniveau und Haushaltssaldo. Der vierte
   Hebel, Finanzmarktregulierung, hat keinen Anker und steht im Weltlauf fest auf seinem
   Startwert — was das Orakel für dieses Instrument blind macht, und das gehört in jeden
   Befund;
4. **exogene Pfade** nach T25;
5. **Konstanten des Jahrgangs**: **vierzehn Werte** — `durchgriff[Gebiet][handelbarer
   Sektor]`, also zehn in Zehntausendsteln, und **`leitzins_start[l]`**, vier in
   Basispunkten. Die vier sind die erste Stützstelle des Politikpfads aus Reihe 9, also
   keine neue Datenanforderung; sie stehen hier, weil `anleihekurs` sie über die ganze
   Partie braucht und ein Rückgriff auf „den Leitzins in Runde 1" einen Zustand voraussetzte,
   den der Zustand nicht mehr hat. Bildungsregel für `durchgriff` mit `H` = Aus- plus Einfuhr des Sektors im Startjahr
   (aus BACI über die Konkordanz in Punkt 9) und `N` = seine Wertschöpfung (aus WDI):

   ```
   durchgriff = teile_gerundet(10.000 · H, H + N)
   ```

   Der Wertebereich 0 … 10.000 gilt damit für alle nichtnegativen `H`, `N` per
   Konstruktion; eine Kappung gibt es nicht und darf es nicht geben, weil sie den Fehler
   aus Befund 3 nur verstecken würde. **Der einzige undefinierte Fall ist `H + N = 0`** —
   ein Sektor ohne Wertschöpfung und ohne Handel. Der Jahrgangsbau setzt dann
   `durchgriff = 0` (der Sektorpreis folgt vollständig dem Landespreis, was für einen
   Sektor ohne Handel die richtige Aussage ist) und **meldet den Fall im Manifest als
   Befund**, weil ein Gebiet mit einem leeren Sektor eine Datenfrage aufwirft und keine
   Rechenfrage. Er tritt im Prüfjahrgang bei keinem der fünf Gebiete auf; die Regel steht
   hier, damit der Jahrgangsbau nicht an einer Division abbricht, deren Ursache er nicht
   nennt.

   **Und der Jahrgangsbau prüft eine Bedingung an den Parametersatz, die `spiel.md`
   Fassung 5 aufstellt und die genau dieses Fenster trifft:** `anleihekurs(l)` hat den Nenner
   `leitzins[l] + aufschlag`, der Leitzins hat deshalb die Untergrenze `1 − aufschlag`, und
   der historische Politikpfad muss sie einhalten. Der Jahrgangsbau rechnet

   ```
   aufschlag_min = 1 − min über alle l und t von leitzins_pfad[l][t]
   ```

   und weist einen Parametersatz mit `aufschlag < aufschlag_min` für diesen Jahrgang als
   **unzulässig** zurück, statt später durch null zu teilen. Für 1997–2021 ist das keine
   theoretische Schranke: Deutschland folgt dem Euroraum ab Runde 3 exogen, und die EZB hat
   ihren Einlagesatz am 2014-06-11 erstmals auf −0,10 % gesenkt und bis September 2019 auf
   **−0,50 %** (`ecb.europa.eu/press/pr/date/2014/html/pr140605_3.en.html` und
   `ecb.europa.eu/stats/policy_and_exchange_rates/key_ecb_interest_rates/html/index.en.html`,
   abgerufen 2026-09-01 vom Spielentwerfer, hier übernommen). Zieht der Jahrgang den
   Einlagesatz, ist `aufschlag_min = 1 − (−50) = 51` Basispunkte; zieht er den
   Hauptrefinanzierungssatz, der ab 2016 bei 0,00 % steht, ist `aufschlag_min = 1`. **Welche
   Reihe eingebettet wird, entscheidet der Jahrgangsbau; die Schranke rechnet er in beiden
   Fällen selbst aus, statt eine Zahl zu übernehmen.** Dieselbe Untergrenze gilt im
   `spielmodus` am Instrument selbst (T51) — sonst unterliefe sie eine Lobbyaktion, die kein
   Jahrgangsbau je zu sehen bekommt;
6. **abgeleitete Kennzahlen**: die mittlere absolute Jahresänderung je Land als
   Schwankungsbreite für den Innerjahresausschlag. Mittlere absolute Abweichung, nicht
   Standardabweichung — die bräuchte eine Wurzel und damit Gleitkomma (T4);
7. **Normierung**: die drei Sektoranteile je Gebiet und Jahr werden auf 10.000 normiert,
   weil die WDI-Anteile wegen der Gütersteuern abzüglich Subventionen nicht auf 100 Prozent
   summieren. Die Normierung — Verfahren und der je Gebiet und Jahr abgeschnittene Rest —
   steht im Manifest, und der Rückvergleich vergleicht normiert gegen normiert;
8. **Brüche**: je Reihe ein Feld `exogen_ab` und ein Feld `verkettet_ab`, beide als
   Jahreszahl gespeichert und nach T40 in eine Runde umgerechnet. Für Deutschland trägt der
   Leitzins `exogen_ab = 1999`, im Prüfjahrgang also **Runde 3**, und die Wechselkursreihe
   `verkettet_ab = 1999` mit dem unwiderruflichen Umrechnungskurs;
9. **die Konkordanz HS92 → Modellsektor**, als Tabelle im Manifest und nicht im Code
   (Befund 12). Sie lautet nach `spiel.md`: Kapitel **01–24 → Sektor 1 Landwirtschaft**,
   **25–97 → Sektor 2 Industrie**. Dieselbe Tabelle erzeugt `H` aus Punkt 5, die
   Handelsstartmatrix und die 40 Sollströme des Handelsblocks — deshalb ist ihr
   Zuordnungsfehler für den Rückvergleich folgenlos, und deshalb darf es sie nur einmal
   geben. Eine zweite Kopie im Code wäre die Gelegenheit, sie auseinanderlaufen zu lassen;
10. **die Restwelt als Rest**, in beiden Größen ausdrücklich gebildet: Ihre Aggregate sind
    die Weltreihe der Weltbank minus die vier Länder; ihre Handelszeilen sind die
    Gesamtein- und -ausfuhr eines Landes im Sektor minus die Ströme zu den drei anderen.
    **Je gerichtetem Paar steht genau eine Zahl** (BACI meldet den Ausfuhrwert; ein
    getrennter Einfuhrwert würde die Invariante „Summe aller Handelsbilanzen = 0" von der
    Datenqualität abhängig machen statt von der Bauart).

Größenordnung: 5 Gebiete × 25 Jahre × rund 30 Reihen × 8 Byte = 30 kB, Handel
`40 × 25 × 8` = 8 kB. Der ausgelieferte Datenteil bleibt je Jahrgang deutlich unter
100 kB und mit allen Jahrgängen deutlich unter einem Megabyte.

**T45 — Der Jahrgangsbau zählt die Adressen ab und bricht bei einer Lücke ab.** Das ist die
architektonische Antwort auf Befund 2, und sie ist die einzige, die dessen Wiederholung
ausschliesst. Zwei Tabellenzeilen nachzutragen behebt den Fall; sie nachzutragen und die
Stelle offenzulassen, an der niemand das Fehlen bemerkt, behebt ihn nicht.

Der Jahrgangsbau führt über **alle 310 Adressen aus T15** eine Herkunftstabelle mit genau
**fünf** zulässigen Einträgen. Vier standen in Fassung 4; die fünfte ist in dieser Fassung
hinzugekommen, weil das Auszählen zwei Adressen gefunden hat, deren Wert weder in einer
Reihe noch in einem Dokument steht, sondern vom Jahrgangsbau selbst gerechnet wird.

| Eintrag | Bedeutung | Adressen | Beispiel |
|---|---|---:|---|
| `Datenanker(nr)` | eine Reihe der Reihenliste weiter unten | 136 | `land.DE.sektor.2.wertschoepfung` → Reihe 1 × 2 |
| `Entwurf` | die Tabelle „Jede Größe ohne Datenanker" in `spiel.md` nennt einen **Zahlenwert** | 150 | `land.CN.aufsichtszaehler` → 0 |
| `Parameter(schluessel)` | `parameter.toml` nach T27 | 11 | `fonds.kasse` → `startkapital` |
| `Manifest(feld)` | vom Jahrgangsbau gerechnet und im Manifest ausgewiesen | 2 | `markt.wert` → Startkorb zu Startpreisen (T33) |
| `Vorgabe(T-Nummer)` | dieses Dokument, abschliessend aufgezählt in **T46** | 11 | `restwelt.basiswechsel` → 0 (T8) |
| **Summe** | | **310** | |

**Die Vorrangregel, ohne die die Summe nicht aufgeht.** Die Entwurfstabelle in `spiel.md`
nennt für einige Zeilen keinen Zahlenwert, sondern eine **Bezugsquelle** — „aus
`parameter.toml`" bei Zustimmung, Finanzmarktregulierung, Fondskasse, Anlegerbestand und
Parametersatz-Prüfsumme, „aus dem Manifest des Jahrgangs" bei der Jahrgangskennung. Nach dem
Wortlaut der Fassung 4 trügen diese Adressen zwei Einträge und brächen den Bau ab. Es gilt
deshalb: **Der Eintrag ist die Stelle, die den Wert *bestimmt*, nicht die, die ihn
erwähnt.** Verweist die Entwurfstabelle weiter, lautet der Eintrag `Parameter(…)`
beziehungsweise `Manifest(…)`; `Entwurf` bleibt den Zeilen vorbehalten, die eine Zahl
hinschreiben. Ein Verweis ist kein zweiter Eintrag.

**Eine Adresse ohne Eintrag bricht den Jahrgangsbau ab, eine Adresse mit zwei Einträgen
ebenso.** Der zweite Fall ist der wichtigere: Er ist die Stelle, an der eine Größe zwei
Herren bekäme und die beiden Werte auseinanderlaufen könnten — derselbe Fehlertyp, den T39
für `landespreis`, T23 Punkt 9 für die BACI-Konkordanz und T47 für das Fondsvermögen schon
geschlossen haben. Er ist in dieser Fassung einmal eingetreten und behoben: die 32
Druck- und Restverzögerungsadressen, die `spiel.md` Fassung 4 aufgenommen hat und die T23
Punkt 1 weiterhin führte.

**Wie die Zahlen der dritten Spalte entstanden sind, damit sie nachzählbar sind statt
geglaubt.** Je spielbarem Land tragen 21 Adressen einen Datenanker (9 Sektorgrößen ohne den
Preis, 8 Aggregatgrößen ohne den Wechselkurs, der Wechselkurs selbst, 3 Instrumentenstände),
20 den Eintrag `Entwurf` (3 Sektorpreise, Aufsichtszähler, Einfluss, 12 Druck-, Gegendruck-
und Restverzögerungsfelder, 3 Restdauern), 2 einen Parameterschlüssel (Zustimmung,
Finanzmarktregulierung) und 1 eine Vorgabe (`basiswechsel`) — zusammen die 44 aus T15. Für
die USA fällt der Wechselkurs vom Anker in die Vorgabe (Numéraire), also `3 × 21 + 20 = 83`
Anker. Die Restwelt trägt 13 Anker, 3 `Entwurf` und 6 Vorgaben. Dazu 40 Handelsströme mit
Anker.

```
Datenanker  83 + 13 + 40                                            = 136
Entwurf     4×20 + 3 + 2 + 12 + 1 + 6 + 24 + 20 + 2                 = 150
            (Länder, RW-Sektorpreise, Weltpreise, Nachahmer,
             markt.rendite, Fondsaggregate, Beteiligungen,
             Positionen, Runde und Mandatsstand)
Parameter   4×2 + Fondskasse + Anlegerbestand + Prüfsummenfeld      =  11
Manifest    markt.wert + Jahrgangskennung                           =   2
Vorgabe     T46                                                     =  11
                                                                      ---
                                                                      310
```

Die vollständige Tabelle — 310 Zeilen aus Adresse, Herkunft und Startwert — wird ins
Manifest geschrieben. Damit ist die Abnahmebedingung 2 des Arbeitspakets **maschinell
beantwortbar**, statt vier Dokumente nebeneinanderzulegen: Wer sie prüfen will, liest eine
Datei, die der Jahrgangsbau gar nicht erst hätte schreiben können, wenn eine Zeile fehlte.

Der Preis ist 310 Vergleiche, einmal je Datenlauf und nicht je Partie. Die naheliegende
Alternative — Startwert null, wenn nichts dasteht — wäre die teure gewesen: Sie hätte
Befund 2 der dritten Prüfung in eine Zahl verwandelt, die niemand mehr hinterfragt, und
zwar in genau die Zahl, die dort zufällig richtig ist.

**T46 — Die elf Adressen, deren Herkunft dieses Dokument ist, abschliessend.** Fassung 4
hat `Vorgabe(T-Nummer)` eingeführt und mit „derzeit allein T23 Punkt 1" beschrieben. Das war
falsch, und der Fehler ist erst beim Auszählen aufgefallen: Nach der Aufnahme der 32
Adressen in `spiel.md` hat T23 Punkt 1 gar keine Adresse mehr — dafür haben elf andere seit
jeher keinen zulässigen Eintrag gehabt, ohne dass es jemandem aufgefallen wäre. Sie stehen
hier mit Startwert, Grund und Regel im Lauf:

| Adresse | Zahl | Startwert | Grund und Regel im Lauf |
|---|---:|---:|---|
| `gebiet.<G>.basiswechsel`, alle fünf Gebiete | 5 | 0 | Zähler der Neubasierungen nach **T8**. Vor Runde 1 hat keine stattgefunden; im Lauf erhöht ihn allein die Regel aus T8. Keine Reihe kann ihn tragen, weil er eine Eigenschaft des Modells ist und nicht der Welt |
| `land.US.wechselkurs` | 1 | 10.000 | Der US-Dollar ist der Numéraire (**T5**). Reihe 10 trägt drei Länder, die USA definitionsgemäß nicht. Der Wert ist über die ganze Partie fest und wird je Runde mit der Ursache `Vortrag` geschrieben (T18) — dieselbe Bauart wie der dauerhaft leere Steckplatz aus T16 |
| `restwelt.leitzins`, `restwelt.staatsschuld`, `restwelt.haushaltssaldo` | 3 | 0 | Die Restwelt hat nach `spiel.md` keine Politikinstrumente, keine Regierung und keinen Aufsichtszähler; sie hat folglich auch keine Notenbank und keinen Haushalt. Diese drei Adressen und die nächste existieren nur, weil T15 der Restwelt denselben Aggregatblock gibt wie einem Land. **Keine Modellregel liest sie**, alle vier werden je Runde mit der Ursache `Vortrag` fortgeschrieben, damit die Sollmaske aus T38 aufgeht |
| `restwelt.wechselkurs` | 1 | 10.000 | Ebenso ungelesen, aber mit anderem Startwert: Die Restwelt rechnet im Numéraire, und ein Kurs eines Währungsaggregats gegen den Dollar hat keine Bedeutung. 10.000 statt 0, damit eine versehentliche Verwendung nicht durch null teilt, sondern die Zahl unverändert lässt |
| `restwelt.inflation` | 1 | 0 | Reihe 8 (Verbraucherpreise) trägt vier Länder, die Restwelt nicht. Im Lauf ist die Größe endogen wie überall — Jahresrate von `restwelt.preisniveau`, das Reihe 15 verankert. Nur ihr Startwert hat keine Quelle |

**Die erste Zeile nennt fünf Adressen und keine Schreibweise.** `gebiet.<G>.` ist die
Sammelschreibweise aus **T17b** und löst hier zu `land.US.basiswechsel`,
`land.CN.basiswechsel`, `land.DE.basiswechsel`, `land.BR.basiswechsel` und
`restwelt.basiswechsel` auf — laufende Nummern 44, 88, 132, 176 und 198 in
`daten/adressen.md`. Das ist keine Ausnahme von T17, sondern seine Anwendung: Fünf Zeilen
einzeln aufzuführen, wo sie sich nur im Gebiet unterscheiden, bläht die Tabelle und sagt
nichts mehr.

**Zwei Auflagen, ohne die die vier Restweltadressen eine stille Annahme wären.** Erstens:
Auf sie ist **ausser dem Vortrag selbst kein Lesezugriff zulässig**. Der `Schreiber` führt
sie in einer Liste `nur_vortrag`; ein `lies_alt` oder `lies_neu` darauf aus einer anderen
Ursache als `Vortrag{adresse}` ist ein harter Fehler, kein Bericht, und der Bruchtester
prüft es in Prüfung 5 und 6 mit. Sonst wüchse eine Modellregel auf einer Zahl, die niemand
gesetzt hat. Zweitens: Fällt später eine Regel an, die eine davon braucht, ist das ein ADR
und keine Zeile Code — dann bekommt die Adresse einen Datenanker oder eine begründete
Bildungsregel.

**Warum T46 überhaupt gebraucht wird und die Adressen nicht einfach entfallen.** Sie zu
streichen wäre die sauberere Architektur und ist ausgeschlossen: `spiel.md` nennt **310**
Größen und verweist für die Aufstellung hierher. 306 hier und 310 dort wäre ein Widerspruch
in einer Zahl, also genau der Fall, den Abnahmebedingung 3 ausschliesst — und ändern darf
ich `spiel.md` nicht. Vier Adressen, die nie gelesen werden, kosten 32 Byte und einen Test;
ein Widerspruch zwischen den beiden Dokumenten kostet einen Lauf.

**T24 — Lücken werden gekennzeichnet, nicht stillschweigend gefüllt — und der Prüfjahrgang
duldet keine.** Je Reihe, Land und Jahr ein Flag `gefuellt`. Die Füllregel steht im
Manifest (Fortschreibung des letzten bekannten Werts, lineare Ganzzahlinterpolation
zwischen Stützstellen), und **gefüllte Jahre zählen im Fehlermaß des Rückvergleichs nicht
mit**, sondern werden gezählt und ausgewiesen.

Zwei Schwellen:

- **Prüfjahrgang 1997–2021:** `spiel.md` verlangt jede der 31 Sollreihen und jeden der 40
  Handelsströme über **25 Stützstellen ohne Füllung**, also `gefuellt = 0`. Eine Reihe, die
  das nicht erfüllt, wird **nicht gefüllt und nicht stillschweigend übernommen**, sondern
  als Befund an den Spielentwerfer gemeldet, samt der beiden Auswege, die ihm zustehen:
  Reihe streichen oder Fenster kürzen. Nach T40 kostet die zweite Wahl nur eine Zahl im
  Manifest.
- **Spieljahrgänge:** Eine Sollreihe, die zu mehr als einem Fünftel gefüllt ist, gilt als
  nicht belastbar und wird im Befund als solche markiert.

**Der Verdachtsfall ist enger geworden, aber nicht geschlossen.** Fassung 2 hat hier die
chinesischen und brasilianischen Leitzinsreihen der neunziger Jahre genannt; `spiel.md`
Fassung 3 hat den Fall gegen `FR.INR.LEND` geprüft (China 1995–2023 lückenlos, Brasilien
ab 1997) und damit ein Indiz, keinen Beweis. `FR.INR.LEND` ist eine andere Reihe als der
IFS-Leitzins, und `imf.org` weist den Abruf mit HTTP 403 ab. Der Jahrgangsbau prüft es an
der Reihe, die tatsächlich eingebettet wird. **Das ist unverändert die wahrscheinlichste
Stelle, an der das Vorhaben an Daten scheitert** — nur ist sie jetzt billig, weil sie
niemanden mehr zwingt, ein Paket zweimal zu bauen.

**T25 — Die Grenze zwischen exogen und endogen ist die Grenze der Aussagekraft des
Orakels, und deshalb ist sie eng gezogen.**

| Größe | im Spiel | Begründung |
|---|---|---|
| Bevölkerung, Erwerbstätige | **exogen**, Pfad aus Daten | Demografie ist nach `spiel.md` ausdrücklich keine Spielgröße |
| Restwelt-Nachfrageniveau | **exogen**, Pfad aus Daten | Randbedingung des Modells; der Rückvergleich prüft die Restwelt folglich nicht |
| `durchgriff` | **exogen und konstant**, Konstante des Jahrgangs | so von `spiel.md` festgelegt, samt der dort benannten Vereinfachung: Chinas wachsende Handelsoffenheit bildet das Modell über Mengen ab, nicht über die Preisübertragung |
| Produktivität | **endogen**, nur Startwert aus PWT | Würde sie jährlich aus den Daten gelesen, wäre das BIP im Rückvergleich eine Wiedergabe der Sollreihe und der Test prüfte sich selbst |
| Preise, Zinswirkung, Handel, Staatsfinanzen, Zustimmung | **endogen** | das ist die Maschine, die geprüft werden soll |
| Politikinstrumente | im `spielmodus` endogen, im `weltlauf` auf die historischen Pfade gesetzt | so verlangt es `spiel.md` — mit der Folge aus T37 und der Maske aus T38 |

**T51 — Jedes Politikinstrument hat eine Schrittweite und einen Wertebereich, beide aus
`parameter.toml`, und der Wertebereich gilt in beiden Modi.** `spiel.md` sagt „Instrumente
bewegen sich um höchstens einen Schritt je Runde" und nennt für die Finanzmarktregulierung
keine Einheit; seit T5 Klasse 10 gibt es eine, und damit lässt sich der Satz aufschreiben:

| Instrument | Klasse | ein Schritt | Wertebereich |
|---|---|---|---|
| Leitzins | 3 Raten | `schrittweite[leitzins]` bp | `instrument_min[leitzins] … instrument_max[leitzins]`, und **`instrument_min[leitzins] ≥ 1 − aufschlag`** |
| Zollniveau | 3 Raten | `schrittweite[zoll]` bp | `0 … instrument_max[zoll]` |
| Haushaltssaldo | 3 Raten | `schrittweite[haushalt]` bp | `instrument_min … instrument_max` |
| Finanzmarktregulierung | 10 Instrumentenstufe | **1 Stufe** | `0 … regulierung_stufen` |

Nach jeder Bewegung in Schritt 3 gilt `stand = min(max(stand ± schritt, min), max)`; die
Kappung trägt die Ursache des auslösenden Drucks und nicht `Vortrag`, damit die Kette aus
T18 sagt, *dass* gekappt wurde. **Im `weltlauf` gilt die Schrittweite nicht** — der
historische Pfad ist dort die Wahrheit und darf in einem Jahr weiter springen —, **der
Wertebereich schon**: Verlässt der Pfad ihn, ist das ein Befund des Jahrgangsbaus und kein
stilles Kappen einer Sollgröße.

Die Zeile, an der das hängt, ist die zweite Spalte des Leitzinses. Ohne sie kann eine
Lobbyaktion den Zins unter `−aufschlag` drücken, und `anleihekurs` teilt in derselben Runde
durch null oder wechselt das Vorzeichen. Der Jahrgangsbau prüft die Bedingung gegen den
historischen Pfad (T23 Punkt 5), das Instrument prüft sie gegen den Spieler, und der
Invariantentest prüft sie gegen beide (T30 Prüfung 2). Drei Prüfungen für eine Schranke ist
nicht zu viel: Sie ist die einzige Stelle des Modells, an der ein Kurs unendlich wird.

**T26 — Ein gesperrter oder fehlender Datenanker ändert das Programm nicht, nur das
Manifest.** Drei Fälle, alle nach demselben Muster: Der Jahrgang trägt ein Modellkonstrukt,
das Manifest sagt es, der Befund wiederholt es.

| Fall | Ersatz | Folge für das Orakel |
|---|---|---|
| Aggregierter Zollsatz fällt unter die Drittanbieter-Ausnahme (die schwerste offene Frage aus `spiel.md`) | kein Zollpfad; der Weltlauf läuft mit konstantem Zoll | zwei statt drei verankerte Instrumente |
| Sektorale Beschäftigung (Reihe 7) gesperrt | Aufteilung nach Wertschöpfungsanteil | Startwert wird Modellkonstrukt, keine Sollreihe betroffen |
| **Spieljahrgang vor 1995 braucht eine Handelsmatrix, BACI beginnt 1995** | IWF-DOTS-Aggregate je Länderpaar, aufgeteilt nach den WDI-Sektoranteilen des Ausfuhrlandes | die Startmatrix ist ein Modellkonstrukt; Spieljahrgänge tragen ohnehin keinen Handelsblock im Rückvergleich (`spiel.md`) |

Der dritte Fall betrifft nach der Verschiebung auf 1997 nicht nur die Jahrgänge vor 1995,
sondern auch 1995 und 1996: Sie sind nach `spiel.md` Spiel-, aber keine Prüfjahrgänge und
tragen als US-Startwert die Sektorstruktur von 1997, gekennzeichnet als `gefuellt`.
Lizenz- und Deckungsrisiko sind damit eine Eigenschaft der Datenschicht, nie eine des Kerns.

### Die Reihenliste, die `spiel.md` vom Architekten verlangt

Damit der Datenbauer je Reihe das Feld „Source" prüfen kann. Quelle nach `daten.md`;
„Verdacht" heisst Drittanbieter-Ausnahme der Weltbank. Die Nummern 7, 8, 10 und 13, die
`spiel.md` zur Prüfung benennt, sind unverändert.

| Nr | Größe | Dimension | Modelleinheit | Quelle | Rolle | Verdacht |
|---:|---|---|---|---|---|---|
| 1 | BIP, konstante Preise | 4 + RW | Tsd USD | WDI / PWT | Start + Soll (4, frei) | nein |
| 2 | Wertschöpfungsanteil je Sektor: `NV.AGR.TOTL.ZS`, `NV.IND.TOTL.ZS`, `NV.SRV.TOTL.ZS` | (4+RW) × 3 | Zehntausendstel, auf 10.000 normiert | WDI | Start + Soll (12, frei, 8 unabhängig) | nein |
| 3 | Kapitalstock | 4 + RW | Tsd USD | PWT | Start | nein |
| 4 | Produktivität (TFP) | 4 + RW | Index | PWT | nur Start (T25) | nein |
| 5 | Bevölkerung | 4 + RW | Personen | WDI / PWT | exogener Pfad | nein |
| 6 | Erwerbstätige | 4 + RW | Personen | WDI / PWT | exogener Pfad | nein |
| 7 | Beschäftigung je Sektor | (4+RW) × 3 | Personen | WDI (ILO) | Start | **ja** |
| 8 | Verbraucherpreise | 4 | bp Jahresrate | WDI / IWF IFS | Start + Soll (4, frei) | **ja** (IWF-gestützt) |
| 9 | Leitzins | 4 | bp | IWF IFS | Start + Politikpfad + Soll (4, **gesetzt**) | nein |
| 10 | Wechselkurs gegen USD | 3 | Index | IWF IFS / WDI | Start + Soll (3, frei) | prüfen |
| 11 | Staatsschuldenquote | 4 | bp | IWF WEO | Start + Soll (4, **abgeleitet**) | nein |
| 12 | Haushaltssaldo | 4 | bp | IWF WEO | Start + Politikpfad | nein |
| 13 | Zollniveau, aggregiert | 4 | bp | WDI (aus WITS) | Start + Politikpfad | **ja, entscheidend** |
| 14 | Bilaterale Ströme nach HS92, aggregiert über die Konkordanz aus T23 Punkt 9 | 5 × 4 × 2 | Tsd USD | CEPII BACI | Start + Sollblock (frei) | nein |
| 15 | Preisniveau im Ländervergleich | 4 + RW | Index | PWT | Start (Numéraire) | nein |
| 16 | `durchgriff` | 5 × 2 | Zehntausendstel | BACI + WDI, abgeleitet nach T23 Punkt 5 | Konstante des Jahrgangs | nein |
| 17 | Sektorpreise | (4+RW) × 3 | Index | **keine** | endogen, kein Soll | — |
| 18 | Zustimmung | 4 | Zehntausendstel | **keine** | aus `parameter.toml` | — |
| 19 | Marktkorbwert und Marktrendite | 1 + 1 | Tsd USD / bp | **keine** | Startwert nach T33, endogen, kein Soll | — |

`NV.IND.MANF.ZS` (verarbeitendes Gewerbe) wird nach `spiel.md` **nicht** verwendet und ist
deshalb hier nicht aufgeführt. Die 31 Sollreihen sind die Zeilen 1, 2, 8, 9, 10 und 11
(4+12+4+4+3+4); der Handelsblock aus Zeile 14 kommt als eigener Block hinzu. Die vier
Größen ohne Datenanker sind die Zeilen 17, 18, 19 und das Instrument
Finanzmarktregulierung — genau die vier, die `spiel.md` unter „Die Grenze des Orakels"
aufzählt.

**Und hier steht die Zeile, deren Fehlen T46 nötig gemacht hat.** Die Spalte „Dimension"
ist zu lesen, wie sie dasteht: Zeile 8 trägt **4**, nicht 4 + RW; die Zeilen 9, 11 und 12
tragen **4**, Zeile 10 trägt **3**. Daraus folgt, dass elf Zustandsadressen von keiner Reihe
gedeckt sind — der US-Wechselkurs (Numéraire), fünf Aggregatgrößen der Restwelt und die fünf
Neubasierungszähler. Sie stehen in **T46**. Bis Fassung 4 stand das nirgends, weil niemand
die Dimensionen gegen T15 gelegt hat; die Prüfung der Runde 4 hat Bedingung 2 für erfüllt
erklärt und dabei auf dieselbe Lücke geschaut wie ich.

**T27 — Die Kalibrierdatei liegt ausserhalb des Codes, und jeder Schlüssel trägt eine
Skalenklasse.** Sämtliche Zahlenwerte, die `spiel.md` ausdrücklich der Kalibrierung
überlässt — Mandatsschwelle (`schwelle_v` und `schwelle_e`), drei Aufsichtsschwellen,
Nachahmergeschwindigkeit, Anlegerabzugsanteil, Startkapital, Startzustimmung, Startstand der
Finanzmarktregulierung, `ausstiegsabschlag` und `zwangsabschlag` (T47), Verzögerungen,
Elastizitäten — stehen in `parameter.toml`.

**Elf Schlüssel bekommen in dieser Fassung eine Einheit oder gibt es neu**, weil T49 und T50
sie sonst nicht einordnen könnten. Ein Parameterschlüssel ohne Klasse ist derselbe Fehler
wie eine Adresse ohne Klasse:

| Schlüssel | Klasse (T5) | Bedeutung | woher |
|---|---|---|---|
| `stufenweite` | 4 Anteile | Anteil des Marktes je Positionsstufe, **kein Geldbetrag** | `spiel.md` Fassung 5 |
| `stufen_max` | 11 Zähler | Betragsgrenze der Stufenzahl je Steckplatz | T16 |
| `ausstiegsabschlag`, `zwangsabschlag` | 4 Anteile | Abschläge auf den Beteiligungswert | T47 |
| `aufschlag` | 3 Raten | Abstand Leitzins ↔ Anleiherendite, `≥ aufschlag_min` (T23 Punkt 5) | **neu**, `spiel.md` Fassung 5 |
| `lobbykosten` | 1 Fondsgeld | US-Cent je Lobbypunkt, `≥ 1` | T50 |
| `beteiligungsrabatt` | 4 Anteile | Preisnachlass auf den Lobbypunkt bei Beteiligung, `1 … 10.000` | **neu**, T50 |
| `gegenlobby_satz` | 9 Lobbydruck | Lobbypunkte je 10.000 Tausend USD Schaden | **neu**, T50 |
| `druck_max` | 9 Lobbydruck | Obergrenze für Druck und Gegendruck je Instrument | **neu**, T5 Klasse 9 |
| `regulierung_stufen` | 10 Instrumentenstufe | Zahl der Stufen der Finanzmarktregulierung | **neu**, T5 Klasse 10 |
| `schrittweite[i]`, `instrument_min[i]`, `instrument_max[i]` | wie das Instrument | Bewegung je Runde und Wertebereich | **neu**, T51 |

`leitzins_start[l]` steht **nicht** hier, sondern im Jahrgang (T23 Punkt 5): Es ist keine
Kalibriergröße, sondern eine Messung. Die Zahl der Adressen mit Herkunft
`Parameter(schluessel)` bleibt bei elf (T45) — neue Schlüssel sind keine neuen Adressen.

Alle Werte werden als Dezimalzeichenketten in skalierte Ganzzahlen gelesen (T4)
und in eine Struktur mit benannten Feldern gefüllt, nie über eine Schleife über Schlüssel
(T9). Die Prüfsumme des Parametersatzes steht im Zustand und in jedem Speicherstand. Damit
ist Kalibrieren eine Datenänderung, die kein Übersetzen braucht — genau die Bauart, die
`spiel.md` an Democracy 4 belegt hat, und die Voraussetzung dafür, dass ein Agent über
Nacht tausend Parametersätze durchsucht (Abschnitt 10).

## 8. Markträumung und die beiden Renditen

**T28 — Feste Iterationszahl statt Konvergenzabbruch.** Der Weltpreis je handelbarem
Sektor wird durch **genau 40 Halbierungsschritte** über einem festen Preisintervall
gesucht, nicht bis zu einer Schranke. Ein Abbruch nach Genauigkeit macht die Laufzeit vom
Zustand abhängig und die Zahl der Schritte zu einem stillen Teil des Ergebnisses; eine
feste Zahl macht beides messbar und begrenzt. 40 Halbierungen über einem Intervall von
sechs Größenordnungen lösen bis unter ein Zehntausendstel auf — mehr Auflösung, als die
Preisskala aus T5 überhaupt darstellt.

Innerhalb jedes Halbierungsschritts stehen, in dieser Reihenfolge, der Zollkeil je Gebiet
auf dem Weltpreis und daraus der wirksame Sektorpreis als Mischung

```
preis = teile_gerundet(weltpreis_mit_zoll · durchgriff
                       + landespreis · (10.000 − durchgriff),  10.000)
```

mit `landespreis = lies_alt(gebiet.<G>.sektor.<s>.preis)` nach T39, Präfix nach T17b, in
Runde 1 also dem Startwert 10.000. Angebot und Nachfrage werden auf diesem Preis gebildet.

**Damit ist die Zulässigkeit der Halbierung belegt statt behauptet** — und das ist die
Behebung von Befund 6, nicht nur seine Beantwortung. Beide Gewichte sind nichtnegativ
(`durchgriff` liegt nach T23 Punkt 5 in 0 … 10.000), `landespreis` steht fest, während die
Halbierung läuft, und `preis` ist deshalb monoton wachsend im Weltpreis. Die
Überschussfunktion erbt diese Monotonie, es entsteht keine Fixpunktaufgabe, und ein Durchlauf
genügt. Die zweite Lesart des Prüfers — `landespreis` als räumender Inlandspreis derselben
Runde — hätte genau das zerstört; sie ist mit T39 nicht nur verworfen, sondern nicht mehr
formulierbar.

Dienstleistungen haben keine Handelszeile, keinen Weltpreis und `durchgriff = 0`; ihr
Sektorpreis ist die reine Fortschreibung des Vorrundenpreises durch die inländische
Räumung.

**T29 — Ganzzahlige Potenzen und Wurzeln über Newton auf `i128`.** Wo die
Produktionsfunktion einen Exponenten wie 1/3 braucht, wird `wurzel(x, n)` mit fester
Schrittzahl verwendet; Exponenten sind auf Brüche kleiner ganzer Zahlen beschränkt. Keine
Reihenentwicklung, kein Logarithmus, keine Tabelleninterpolation.

**T33 — Marktrendite und Fondsrendite werden über einen eingefrorenen Mengenkorb
gerechnet.** `spiel.md` hat die Auslegung entschieden: wertgewichtete Rendite aller
handelbaren Körbe zu Modellmarktwerten, gewichtet nach dem Markt und **nicht** nach dem
Bestand des Fonds. Die Regel, in Schritt 6 der Runde und nur im `spielmodus`:

1. Der **Marktkorb** umfasst die 12 Land×Sektor-Körbe und die 4 Staatsanleihen, jeweils zu
   Modellmarktwerten. Währungen tragen keine Marktkapitalisierung und gehen nicht ein; ihre
   Wirkung steckt in der Umrechnung der übrigen Körbe in den Numéraire. **Seit `spiel.md`
   Fassung 5 sind Menge und Kurs benannt**, und damit ist der Korb eine Rechnung statt einer
   Umschreibung — die Mengen sind Kapitalstock und Staatsschuld, die Kurse Sektorpreis,
   Anleihekurs und Wechselkurs (T48):

   ```
   marktkorb(m, k) = Σ über die 12 Land×Sektor  wert_(m,k)(kapitalstock[l][s], sektorpreis[l][s], l)
                   + Σ über die  4 Anleihen     wert_(m,k)(schuld(l),          anleihekurs(l),    l)
   ```

   `m` und `k` sagen, aus welcher Runde die Menge und aus welcher der Kurs gelesen wird;
   beide Summen laufen über die Indexordnung aus T9. Der Wert steht in der
   **volkswirtschaftlichen** Skala (T5 Klasse 2) und überquert keine Skalengrenze.
2. `markt.wert` trägt den Wert dieses Korbs am Ende der Vorrunde. **In Runde 1 ist es der
   Startwert aus dem Jahrgang** — der Wert des Startkorbs zu Startpreisen, vom Jahrgangsbau
   als `marktkorb(start, start)` gerechnet und im Manifest ausgewiesen. Damit ist die zweite
   Hälfte von Befund 2 der zweiten Prüfung geschlossen, unabhängig vom Modus.
3. Bewerte den **Mengenkorb der Vorrunde** zu den Preisen dieser Runde:
   `W_neu = marktkorb(alt, neu)`, also Mengen über `lies_alt` und Kurse über `lies_neu`
   (T39). `markt.rendite = teile_gerundet((W_neu − markt.wert) · 10.000, markt.wert)` in
   Basispunkten.
4. Erst danach wird `markt.wert = marktkorb(neu, neu)` gesetzt.

Mengenwachstum erzeugt damit keine Scheinrendite. **`markt.wert` ist nie null** — er ist
eine Summe positiver Mengen mal positiver Kurse, und beide Wertebereiche prüft der
Invariantentest (T30 Prüfung 2). Damit sieht die Division in Punkt 3 nie einen Nenner null,
ohne dass irgendwo ein Sonderfall stünde; das ist dieselbe Bauart wie Schritt (c) vor (d)
weiter unten.

**Die Fondsrendite entsteht in derselben Reihenfolge, und die Reihenfolge ist die Regel:**
(a) Positionen bewerten, (a') Beteiligungen bewerten, (b) Fondsvermögen bilden, (c) ist es
**null oder kleiner**, greift nach `spiel.md` Todesart 1 in derselben Runde und die Partie
endet ohne Renditebildung, (d) erst sonst wird die Rendite gebildet: Änderung des
Fondsvermögens gegenüber der Vorrunde, **bereinigt um Anlegerzu- und -abflüsse dieser
Runde** — sonst zählte frisches Anlegergeld als Leistung und der Anlegerabzug aus
Gegenkraft 3 verstärkte sich selbst. Die Überrendite ist die Differenz beider Größen in
Basispunkten und steht für drei Runden im Zustand.

Schritt (c) vor (d) ist keine Feinheit: Er ist der Grund, warum `teile_gerundet` in diesem
Modell nie einen Nenner null sieht, ohne dass irgendwo ein Sonderfall geprüft würde.

**T47 — Das Fondsvermögen ist genau eine Funktion, und jede Bewertung darin überquert die
Skalengrenze genau einmal, am äussersten Aufruf.** `spiel.md` Fassung 5 bildet `korbwert`
und `positionswert`, die Fassung 4 nur verwendet hatte (Befund 1 der Runde 6), und
entscheidet, auf welcher Seite der Grenze `korbwert` steht (Befund 2). Hier steht, wo
gerechnet wird.

**Die Marktwerte, alle in der volkswirtschaftlichen Skala** (T5 Klasse 2); `wert` ist die
eine Bewertungsformel, aus der alle drei Steckplatzarten entstehen:

```
wert(menge, kurs, g) = mal_geteilt(menge, kurs, wechselkurs[g])

korbwert(l, s)   = wert(kapitalstock[l][s], sektorpreis[l][s], l)
anleihewert(l)   = wert(schuld(l),          anleihekurs(l),    l)
waehrungswert(l) = wert(handelsvolumen(l),  10.000,            l)

markt(p)         = korbwert | anleihewert | waehrungswert, je nach Steckplatzart
stufenwert(p)    = mal_geteilt(markt(p), stufenweite, 10.000)
```

**Die beiden Fondswerte, in US-Cent** (T5 Klasse 1) — und genau hier liegt die Grenze:

```
positionswert(p)       = 0                                        falls stufen(p) = 0
                       = tsd_in_cent(stufen(p) · stufenwert(p))   sonst

beteiligung_wert(l, s) = tsd_in_cent(
                           mal_geteilt(mal_geteilt(korbwert(l, s), anteil[l][s], 10.000),
                                       10.000 − ausstiegsabschlag, 10.000))

fondsvermoegen(z) = kasse
                  + Σ über die 20 Steckplätze  positionswert(p)
                  + Σ über die 12 Land×Sektor  beteiligung_wert(l, s)
                  − hebelstand
```

Beide Summen laufen über die Indexordnung aus T9, nie über eine Menge. `korbwert(l, s)` ist
derselbe Wert, den auch der Marktkorb aus Punkt 1 dieses Abschnitts verwendet — **eine
Bewertung, nicht zwei**, sonst könnten Marktrendite und Fondsvermögen denselben Korb
verschieden ansetzen.

**Das ist die Behebung von Befund 2, und sie steht an der Wurzel und nicht in einer
Klammer.** Die Formel der Fassung 5 bestand aus zwei `mal_geteilt` mit einheitenlosen
Anteilen, war also skalenerhaltend: Was in Tausend USD hineinging, kam in Tausend USD
heraus und wurde als US-Cent verbucht — Faktor 100.000, Kasse fällt um das
Hunderttausendfache dessen, was das Beteiligungsvermögen steigt, Todesart 1 in derselben
Runde, Klasse 2 von Maß 2 von Bauart wegen chancenlos. `tsd_in_cent` um den äussersten
Aufruf schliesst das.

**Von den beiden Wegen, die der Prüfer offengelassen hat, ist der andere ausgeschlossen,
und die Begründung ist nicht meine.** `korbwert` gleich in Cent zu führen hiesse, denselben
Korb in zwei Skalen zu führen, denn T33 bewertet dieselben zwölf Körbe volkswirtschaftlich —
zwei Bewertungen für einen Korb, also genau das, was der Absatz darüber ausschliesst.
`spiel.md` Fassung 5 entscheidet das unter *Wo die Skalengrenze liegt* und weist mir nur
noch zu, **welche Funktion** es tut. Es ist `tsd_in_cent` aus T50, und sie hat in diesem
Dokument genau die zwei Aufruforte, die oben stehen.

**Die Reihenfolge der Rundungen ist verbindlich, weil sie das Ergebnis ändert.**
`stufen(p) · stufenwert(p)` und `mal_geteilt(markt(p), stufen(p) · stufenweite, 10.000)`
unterscheiden sich um bis zu `|stufen(p)|` Einheiten. Verbindlich ist die erste Form, weil
`spiel.md` sie so schreibt; die zweite wäre genauer und macht jeden Regressionsbestand
ungültig, der mit der ersten entstanden ist. Wer sie will, braucht einen ADR, keinen
besseren Grund.

**Zwei Wertebereichsschranken gehören dazu, sonst ist die Formel nur bei gutem Wetter
richtig.** Erstens teilt `wert` durch `wechselkurs[g]`: Ein Nenner null ist nach T6 ein
Abbruch, ein **negativer** Nenner wäre schlimmer — er drehte das Vorzeichen jeder Bewertung,
ohne dass irgendetwas abbräche. `wechselkurs[g] ≥ 1` ist deshalb eine Invariante (T30
Prüfung 2), keine Erwartung. Zweitens ist `tsd_in_cent` die einzige Stelle, an der ein `i64`
überlaufen kann: `x · 100.000` verlässt den Bereich ab `|x| > 9,2 · 10^13` Tausend USD. Der
grösste Wert, der dort ankommen kann, ist durch den ganzen Marktkorb beschränkt; bei einem
Weltkapitalstock in der Größenordnung von `4 · 10^11` Tausend USD — grob das Drei- bis
Vierfache eines Weltbruttoinlandsprodukts von rund `10^11` Tausend USD, als Größenordnung
und nicht als Messung — liegen gut zwei Größenordnungen dazwischen. Der Jahrgangsbau prüft
`marktkorb(start, start) < 9,2 · 10^13`, der Invariantentest prüft `markt.wert` je Runde
gegen dieselbe Schranke. Damit ist der Überlauf nicht bloß unwahrscheinlich, sondern
ausgeschlossen und geprüft.

**Was die Anteilsskala nach unten begrenzt, und warum das eine Auflage an den Selbstspieler
ist.** `stufenweite` ist ganzzahlig und mindestens 1; eine Stufe kostet deshalb mindestens
ein Zehntausendstel des Korbs, an dem sie hängt. Die sechzehn Marktwerte eines Jahrgangs
liegen weit auseinander — der Kapitalstock der Dienstleistungen in den USA gegen die
Landwirtschaft Brasiliens —, und **derselbe** `stufenweite`-Wert gilt für alle. Der
Jahrgangsbau weist deshalb den kleinsten und den grössten der sechzehn Startmarktwerte im
Manifest aus. Das ist die Zahl, die der Selbstspieler braucht, bevor er `startkapital` und
`stufenweite` sucht: Eine Stufe auf dem grössten Korb muss bezahlbar sein (sonst gewinnt
Klasse 1 nie), und erreichbare Stufenzahlen müssen die Aufsichtsschwellen erreichen (sonst
greift keine Gegenkraft und Maß 3 fällt auf null) — die beiden Bedingungen, die `spiel.md`
unter *Offene Entwurfsfragen* aufstellt, hier mit der Zahl versehen, an der man sie abliest.

Vier Eigenschaften, die diese Fassung binden, alle aus `spiel.md`:

1. **`ausstiegsabschlag` ist ein Schlüssel aus `parameter.toml`** (T27), kein Literal, und
   liegt in Zehntausendsteln. Der Abschlag steckt damit im Wertansatz und ist beim
   **Aufbau** bezahlt: Die Kasse gibt beim Einstieg den vollen Korbanteil ab, das
   Fondsvermögen fällt in derselben Runde um den Abschlag. Beim gewöhnlichen Ausstieg wird
   er **nicht ein zweites Mal** abgezogen; illiquide bleibt die Beteiligung über die zwei
   Runden, die `restdauer[l][s]` zählt.
2. **Der Zwangsverkauf aus Gegenkraft 1 zieht `zwangsabschlag` zusätzlich ab** — ein zweiter
   Parameterschlüssel, eine zusätzliche Strafe, keine Ersetzung des ersten.
3. **`fondsvermoegen` hat genau einen Aufrufort je Zweck und keinen zweiten Rechenweg.**
   Gelesen wird sie von der Abrechnung (Schritt 6), der Mandatsprüfung, Todesart 1, dem
   Invariantentest aus T30 Prüfung 2 und von `v(z)` in T44. Dass alle fünf dieselbe Zahl
   sehen, ist der Grund, warum „Fondsvermögen" durchgehend dasselbe heisst — *was der Fonds
   wert ist, wenn er hier aufhört*.
4. **Sie ist keine Zustandsadresse.** Der Zustand hält Kasse, Steckplätze, Anteile und
   Hebel; das Vermögen ist deren Funktion. Ein Feld dafür wäre eine zweite Kopie derselben
   Zahl — derselbe Fehlertyp, den T39 für `landespreis` und T23 Punkt 9 für die
   BACI-Konkordanz schon geschlossen haben. Die 310 aus T15 ändern sich deshalb nicht.

**Was ein Aufruf kostet, diesmal ausgezählt statt geschätzt.** Fassung 5 sprach von „wenigen
Dutzend Operationen"; der Prüfer der Runde 6 hat das unter *geprüft und nicht gezählt* als
zu klein bezeichnet und recht damit. Im ungünstigsten Fall — alle zwanzig Steckplätze
belegt, alle zwölf Beteiligungen ungleich null:

| Teil | Aufrufe | Operationen |
|---|---:|---:|
| `bip(l)` | 4 | 8 Additionen |
| `schuld(l)` | 4 | 4 `mal_geteilt` |
| `anleihekurs(l)` | 4 | 4 Additionen, 4 `teile_gerundet` |
| `anleihewert(l)` | 4 | 4 `mal_geteilt` |
| `handelsvolumen(l)` | 4 | 64 Additionen |
| `waehrungswert(l)` | 3 | 3 `mal_geteilt` |
| `korbwert(l, s)` | 12 | 12 `mal_geteilt` |
| `stufenwert(p)` | 20 | 20 `mal_geteilt` |
| `positionswert(p)` | 20 | 40 Multiplikationen |
| `beteiligung_wert(l, s)` | 12 | 24 `mal_geteilt`, 12 Multiplikationen |
| zwei Summen | 1 | 32 Additionen |
| **Summe** | | **rund 230, davon 71 `i128`-Divisionen** |

Gegen 7.500 Operationen je Weltschritt sind das **gut drei Prozent**, nicht drei Promille.
Der Planwert von 10 µs hat Bandbreite bis 30 und die Reserve rechnet mit 50; keine Zeile
von Abschnitt 10 bewegt sich. Zwei Vorgaben senken den tatsächlichen Preis weit darunter:
`positionswert` bricht bei `stufen(p) = 0` ab, bevor `markt(p)` überhaupt gerechnet wird
(die meisten Steckplätze sind die meiste Zeit leer), und **`korbwert(l, s)` wird je Aufruf
von `fondsvermoegen` einmal in ein Feld von zwölf gerechnet und von Steckplatz und
Beteiligung daraus gelesen** — nicht, um Zeit zu sparen, sondern weil „eine Bewertung, nicht
zwei" sonst nur ein Satz wäre und keine Eigenschaft des Codes.

**T48 — Die abgeleiteten Größen sind Funktionen des Zustands, keine Adressen, und sie sind
abschliessend aufgezählt.** Das ist die architektonische Antwort auf Befund 1 der Runde 6,
und sie ist die einzige, die dessen Wiederholung ausschliesst. Zwei Formeln nachzutragen
behebt den Fall; ihn zu beheben und die Menge offenzulassen, in der niemand ein Fehlen
bemerkt, behebt ihn nicht. T45 zählt **Adressen** ab und konnte die Lücke deshalb nicht
finden — `korbwert` war nie eine der 310. Diese Tabelle ist die Menge, in der er lag.

| # | Name | Klasse (T5) | Definition | steht in |
|---:|---|---:|---|---|
| 1 | `wert(menge, kurs, g)` | 2 | `mal_geteilt(menge, kurs, wechselkurs[g])` | T47 |
| 2 | `korbwert(l, s)` | 2 | `wert(kapitalstock[l][s], sektorpreis[l][s], l)` | T47 |
| 3 | `anleihewert(l)` | 2 | `wert(schuld(l), anleihekurs(l), l)` | T47 |
| 4 | `waehrungswert(l)` | 2 | `wert(handelsvolumen(l), 10.000, l)` | T47 |
| 5 | `markt(p)` | 2 | Fallunterscheidung über die drei Steckplatzarten aus T16 | T47 |
| 6 | `stufenwert(p)` | 2 | `mal_geteilt(markt(p), stufenweite, 10.000)` | T47 |
| 7 | `marktkorb(m, k)` | 2 | Σ 12 `korbwert` + Σ 4 `anleihewert`, Mengen aus `m`, Kurse aus `k` | T33 |
| 8 | `korbbestand(z)` | 2 | siehe unten | T47 |
| 9 | `bip(l)` | 2 | `Σ über die 3 Sektoren wertschoepfung[l][s]` | hier |
| 10 | `schuld(l)` | 2 | `mal_geteilt(bip(l), staatsschuld[l], 10.000)` | hier |
| 11 | `handelsvolumen(l, s)` | 2 | siehe unten; die einstellige Fassung `handelsvolumen(l)` ist ihre Summe über s ∈ {1, 2} | hier |
| 12 | `anleihekurs(l)` | 5 | siehe unten | hier |
| 13 | `landespreis(g, s)` | 5 | `lies_alt(gebiet.<g>.sektor.<s>.preis)` | T39 |
| 14 | `fondsanteil(l, s)` | 4 | `\|stufen(l, s)\| · stufenweite + anteil[l][s]` | hier |
| 15 | `positionswert(p)` | 1 | `tsd_in_cent(stufen(p) · stufenwert(p))`, 0 bei `stufen = 0` | T47 |
| 16 | `beteiligung_wert(l, s)` | 1 | Korbanteil abzüglich `ausstiegsabschlag`, dann `tsd_in_cent` | T47 |
| 17 | `fondsvermoegen(z)` | 1 | Kasse + Positionen + Beteiligungen − Hebel | T47 |
| 18 | `hub(l, i)` | **die des Instruments**: 3 für Zoll, Leitzins und Haushalt, 10 für die Regulierung | `\|lies_neu(land.<l>.instrument.<i>.stand) − lies_alt(dieselbe Adresse)\|` | hier |
| 19 | `keilhub(l, s)` | 5 | `mal_geteilt(welt.preis.<s>, hub(l, zoll), 10.000)` | hier |
| 20 | `preishub_zoll(l, s)` | 5 | `mal_geteilt(keilhub(l, s), durchgriff(l, s), 10.000)` | hier |
| 21 | `weltpreis_mit_zoll(g, s)` | 5 | `mal_geteilt(welt.preis.<s>, 10.000 + zollstand(g), 10.000)` | T28 |
| 22 | `schaden(l, i)` | 2 | `mal_geteilt(menge, verschiebung, 10.000)`, vier Zeilen, siehe unten | hier |

**Nummer 18 bis 22 sind am 2026-09-04 mit Paket `0043-t48-groessen-gegenkraft-5`
dazugekommen**, aus den Paketen 0021 (die Schadensvorschrift) und 0039 (die Zollzeile misst
nur noch den Keil). Sie sind der Fall, für den T48 gebaut wurde, ein zweites Mal: Der Entwurf
hat fünf Namen in Formeln eingeführt und seine eigene Nachziehtabelle meldete davon keinen.
Nummer 21 ist der ältere Fall — T28 **nennt** den Zollkeil („der Zollkeil je Gebiet auf dem
Weltpreis") und rechnet in seiner Preisformel mit `weltpreis_mit_zoll`, ohne ihn je zu
bilden; das war folgenlos, solange keine zweite Stelle ihn brauchte, und ist es seit Nummer 19
nicht mehr.

**Nummer 18 ist die einzige Größe der Tabelle ohne eine einzige Klasse, und das ist kein
Versehen.** `hub` ist skalen*erhaltend*: Es bildet den Betrag einer Differenz zweier Stände
**derselben** Adresse, und die Klasse des Ergebnisses ist die der Adresse. T49 gibt den vier
Instrumentenständen eines Landes nicht dieselbe Klasse — Zoll, Leitzins und Haushalt stehen
in Basispunkten (3), die Finanzmarktregulierung in Stufen (10). Eine erfundene gemeinsame
Klasse wäre hier die Fehlerart, gegen die T5 gebaut ist; die richtige Aussage ist die über
die Abbildung und nicht die über den Wert.

**Nummer 21 gilt für alle fünf Gebiete, und für die Restwelt ist `zollstand` null.** Der
Grund steht in den Daten und ist keine Wahl: T23 Punkt 5 führt `durchgriff` mit **5 × 2 = 10**
Werten (Reihenliste Nr. 16), die Restwelt nimmt an der Preisübertragung also teil und braucht
einen zollbelasteten Weltpreis; Instrumente hat sie nach T15 keine, ein `zollstand(RW)` ist
deshalb keine Adresse, sondern die Null. Ich entscheide das hier, statt es zurückzugeben, aus
demselben Grund wie die elf Startwerte in T46: Es ist keine Wahl zwischen zwei sinnvollen
Zahlen, sondern die einzige Belegung, mit der die Formel über ihren angeschriebenen
Definitionsbereich („je Gebiet") überhaupt total ist. Hält der Spielentwerfer sie für falsch,
ist es eine Zeile.

Die vier, die bisher nirgends standen:

```
bip(l)               = Σ über die 3 Sektoren  wertschoepfung[l][s]

handelsvolumen(l, s) = Σ über die 4 Gegenüber g   handel[l][g][s] + handel[g][l][s]
handelsvolumen(l)    = Σ über die 2 handelbaren Sektoren s   handelsvolumen(l, s)

anleihekurs(l)       = teile_gerundet(10.000 · (leitzins_start[l] + aufschlag),
                                      leitzins[l] + aufschlag)

korbbestand(z)       = Σ über die 12 Körbe     mal_geteilt(korbwert(l, s),  fondsanteil(l, s), 10.000)
                     + Σ über die  4 Anleihen  mal_geteilt(anleihewert(l),  |stufen(p)| · stufenweite, 10.000)
```

**`handelsvolumen` hat seit dem 2026-09-03 zwei Fassungen, und sie sind eine Größe.** Die
sektorweise ist die gebildete, die einstellige ihre Summe über die beiden handelbaren
Sektoren — nicht zwei Definitionen desselben Namens, sondern eine Definition und ihre
Aggregation. Das ist die Bedingung, unter der die Zollzeile von Gegenkraft 5 je Sektor
rechnen kann, ohne dass Nummer 4 (`waehrungswert(l) = wert(handelsvolumen(l), 10.000, l)`)
sich ändert: Dort steht weiterhin die einstellige Fassung, und sie bedeutet weiterhin
dasselbe. Der dritte Sektor kommt in keiner der beiden vor — er hat keine Handelszeile.

`handelsvolumen` liest **beide Richtungen** je Paar; die Zuordnung des dichten
Gegenüber-Index zum Gebietsindex ist die feste Abbildung aus T9 und steht im Code als
benannte Tabelle, nicht als Rechnung auf Indizes.

Die fünf aus Gegenkraft 5 und dem Zollkeil, in Rechenreihenfolge:

```
hub(l, i)            = | lies_neu(land.<l>.instrument.<i>.stand)
                       − lies_alt(land.<l>.instrument.<i>.stand) |

keilhub(l, s)        = mal_geteilt(welt.preis.<s>, hub(l, zoll), 10.000)
preishub_zoll(l, s)  = mal_geteilt(keilhub(l, s), durchgriff(l, s), 10.000)

weltpreis_mit_zoll(g, s) = mal_geteilt(welt.preis.<s>, 10.000 + zollstand(g), 10.000)

schaden(l, zoll)        = Σ über s ∈ {1, 2}  mal_geteilt(handelsvolumen(l, s), preishub_zoll(l, s), 10.000)
schaden(l, leitzins)    = mal_geteilt(schuld(l), hub(l, leitzins),  10.000)
schaden(l, haushalt)    = mal_geteilt(bip(l),    hub(l, haushalt),  10.000)
schaden(l, regulierung) = mal_geteilt(bip(l),    hub(l, regulierung) · regulierung_last, 10.000)
```

**`schaden` ist eine Funktion mit vier Zeilen und nicht vier Funktionen**, weil ihr Ergebnis
in allen vier Fällen Klasse 2 ist und ihre Stelligkeit dieselbe. Die Summe über die Sektoren
steht **innerhalb** der Zollzeile; nach aussen gibt auch sie eine Zahl je Land und
Instrument, und das ist die Zahl, die der dritte Skalenübergang aus T50 entgegennimmt.
`regulierung_last` ist der Parameterschlüssel aus T27 (Klasse 3, Basispunkte des BIP je
Regulierungsstufe); das Produkt `hub(l, regulierung) · regulierung_last` ist Stufen mal
Basispunkte je Stufe, also Klasse 3 — dieselbe Klasse wie die Verschiebung der beiden
mittleren Zeilen, und deshalb rechnen alle vier über denselben Nenner 10.000. Der Nenner von `anleihekurs` ist nach T51
nie null und nie negativ. **`fonds.marktanteil` ist keine abgeleitete Größe, sondern eine
Adresse**, in Schritt 6 geschrieben als `mal_geteilt(korbbestand(z), 10.000, markt.wert)` —
`spiel.md` schreibt dort `teile_gerundet(korbbestand · 10.000, markt.wert)`; das ist dieselbe
Zahl, aber die naive Form läuft nach T6 über, und deshalb ist die `i128`-Form verbindlich.

**Drei Größen liegen ausserhalb des Kerns** und stehen deshalb nicht in der Tabelle: `B(z)`,
`v(z)` und `e(z)` aus T44. Sie sind Prüfstandsgrößen, gehören dem Baustein `pruefstand` und
verlassen die Partie nie.

**Die Regel, die daraus folgt, und der mechanische Nachweis dazu.** Ein Name in einer Formel
dieses Dokuments oder in `spiel.md`, der weder eine Zustandsadresse aus T15 noch ein
Parameterschlüssel aus T27 noch eine Jahrgangskonstante aus T23 noch eine der
**zweiundzwanzig** Größen oben ist, **ist ein Befund und keine Bauentscheidung** — das ist
der Fall, den Befund 1 beschreibt, und der Grund, warum er teuer war: Wählt der Bauagent,
misst Maß 2 seine Wahl. Nachgewiesen wird es wie der Gleitkommaverzicht aus T4: Die
zweiundzwanzig Namen sind die öffentliche Schnittstelle des Moduls `kern::werte` (T13), und
die Deklarationen in `kern/include/kern/werte.hpp` ausserhalb von `namespace intern` gegen
diese Tabelle gelegt sind eine Prüfung von zwei Minuten. **Ich habe
sie in diesem Lauf einmal von Hand ausgeführt**, in der einzigen Form, die vor dem Bau
möglich ist: jede Formel aus `spiel.md` und aus diesem Dokument Name für Name gegen die vier
Mengen gelegt.

**Und diesmal ist die Liste, gegen die geprüft wurde, mit abgedruckt** — das ist die
Bedingung, unter der die Prüfung ein zweites Mal dasselbe ergibt. Erhoben mit
`rg -o '\b[a-z][a-z0-9_]{2,}\('` über `spiel.md`, danach jeder Treffer einzeln zugeordnet.
Übrig blieben die fünf oben; die **zweiundzwanzig Namen in den zehn Zeilen unten** sind
**keine** abgeleiteten Größen, und warum sie es nicht sind, steht daneben. Wer die Erhebung
wiederholt, darf genau diese Reste behalten und keinen weiteren:

| Name in `spiel.md` | keine abgeleitete Größe, sondern |
|---|---|
| `menge(l, i)`, `verschiebung(l, i)` | **Spaltenüberschriften der Schadenstabelle**, siehe den Absatz unten |
| `zollstand(g)` | `land.<g>.instrument.zoll.stand` in Funktionsschreibweise; für die Restwelt null (Nr. 21) |
| `stufen(p)`, `stufen(l, s)` | die Positionsstufe des Steckplatzes, `fonds.position.<l>.<s>` — eine Adresse aus T15, T5 Klasse 11, ebenfalls in Funktionsschreibweise. Sie stand schon vor diesem Paket unregistriert in den Formeln der Nummern 14 und 15; die Erhebung hat sie mitgefunden |
| `durchgriff(l, s)` | Jahrgangskonstante, T23 Punkt 5, zehn Werte |
| `welt.preis_start(s)` | Startwert des Jahrgangs, T23; steht nur in einer Kalibrierbedingung |
| `regulierung_last`, `druck_max`, `stufenweite`, `aufschlag` | Parameterschlüssel, T27 |
| `lobbypunkte_aus_schaden(tsd)` | dritter Skalenübergang, T50; **privat** in `kern::werte` und deshalb nicht in dieser Tabelle |
| `gegendruck_neu(l, i)` | der in Schritt 5 geschriebene Wert von `land.<l>.instrument.<i>.gegendruck`, also eine Adresse |
| `wmz(l, s)`, `preishub(l, s)` | Namen der **verworfenen** Vorfassung der Zollzeile. Sie stehen allein im Gegenbeispiel, mit dem `spiel.md` vorrechnet, was die Entscheidung vom 2026-09-03 beseitigt hat (8.472.000 statt null ohne jede Aktion) — ein Beleg, keine Vorschrift |
| `mal_geteilt`, `teile_gerundet`, `lies_neu`, `lies_alt`, `min`, `max`, `sgn`, `wurzel` | Rechenwerk und Zugriffsform, T6, T29, T39 |

**`menge` und `verschiebung` bekommen ausdrücklich keine Funktion, und der Grund ist T5
selbst.** Beide sind in `spiel.md` die Spaltenüberschriften einer Tabelle mit vier Zeilen,
nicht zwei Größen: `verschiebung` steht für die Zollzeile in Klasse 5 und für die drei
übrigen in Klasse 3, hat also kein einheitliches Ergebnis, das man deklarieren könnte —
genau die Eigenschaft, die T5 einer Größe abverlangt. `menge` ist immer Klasse 2, scheitert
aber an der **Stelligkeit**: In der Zollzeile ist sie `handelsvolumen(l, s)` und damit eine
Zahl je Sektor, in den drei übrigen `schuld(l)` beziehungsweise `bip(l)` und damit eine je
Land. Eine gemeinsame Funktion müsste sich entweder eine Klasse oder ein Argument
ausdenken. **Gebildet wird deshalb `schaden(l, i)`**, und die Fallunterscheidung liegt in
ihr — dieselbe Bauart wie `markt(p)` (Nr. 5), das die drei Steckplatzarten aus T16 ebenso
innen unterscheidet, statt drei Namen nach aussen zu geben.

## 9. Test- und Prüfstandsaufbau

**T30 — Acht Prüfungen, ein Aufruf.** `nacht` läuft der Reihe nach und bricht mit einem
Rückgabewert ungleich null ab, sobald eine Schwelle aus `spiel.md` gerissen ist. Was nicht
in einem Aufruf läuft, läuft nachts nicht.

| # | Prüfung | Gegenstand | Verantwortlich |
|---:|---|---|---|
| 1 | Einheitstests je Wirkungskette | jeder Pfeil aus `spiel.md` einzeln, auf einem Minimalzustand: Zoll rauf → Einfuhr runter → Preis rauf → Realeinkommen runter → Zustimmung runter. Dazu die Vorratsinvariante aus T43, geprüft für `k = 1` (fünf Runden) **und** `k = 3` (fünfzehn), damit die Verwechslung aus Befund 3 auch im Code auffällt | Testentwickler |
| 2 | Invariantentest | Summe aller Handelsbilanzen einschliesslich Restwelt = 0; Staatsschuld(t) = Staatsschuld(t−1) − Saldo; **Fondsvermögen = Kasse + bewertete Positionen + bewertete Beteiligungen − Hebel** (T47, gegen `fondsvermoegen()` und gegen eine im Test getrennt hingeschriebene Summe, damit der Test nicht die geprüfte Funktion wiederholt); die drei Sektoranteile je Gebiet summieren auf 10.000; kein Anteil ausserhalb 0…10.000; **die sieben Wertebereichsschranken aus T5/T49** (siehe darunter); jedes Partieergebnis in einem der drei Bänder aus T34 | Testentwickler |
| 3 | Determinismustest | derselbe Startwert, Modus und dieselbe Aktionsfolge ergeben dieselbe Prüfsumme — zweimal im Lauf, über Speichern und Laden hinweg, und auf jeder Zielplattform verglichen | Testentwickler |
| 4 | Regressionsbestand | gespeicherte Partien nach T22 rechnen bitgleich nach; zusätzlich eine Prüfsumme über die Kette, damit auch eine geänderte *Begründung* auffällt; mindestens eine Partie auf einem Spieljahrgang 1980 mit Basiswechsel (T8) | Testentwickler |
| 5 | Bruchlauf | 10.000 Partien mit dem Zufallsbot: kein Absturz, kein Überlauf, keine Invariantenverletzung, kein Kettenüberlauf, kein doppelter Schreibzugriff und keine Maskenverletzung (T18, T38, T39) | Bruchtester |
| 6 | **Beschränktheit** | **200 Runden ohne Spieler**; verlässt eine Größe ihren Wertebereich, gibt es einen **neunten** Rückkopplungskanal, und der ist ein Befund. Die Kanaltabelle in `spiel.md` zählt seit Fassung 5 **acht** | Bruchtester |
| 7 | Die drei Maße | Entscheidungsdichte, Strategievielfalt, Optimumsverschiebung nach den Rechenvorschriften in `spiel.md`, gegen die dortigen Schwellen: **0,4 je Partiedrittel**; **drei Klassen mit je einem Gewinner bei höchstens 25 % Abstand**; **Verschiebung ≥ 0,4** | Selbstspieler |
| 8 | Rückvergleich | im Modus `weltlauf` (T38), 31 Sollreihen plus Handelsblock, Fehlermaße nach T42, Abnahme über die **16 Prüfgegenstände mit Toleranz 2** nach T37 | Rückvergleicher |

**Die sieben Wertebereichsschranken, die Prüfung 2 je Runde prüft.** Sie folgen aus T5, T49
und T51 und stehen hier zusammen, damit der Testentwickler sie nicht aus zwölf
Tabellenzeilen zusammensuchen muss. Jede ist ein **harter Fehler**, kein Bericht:

| # | Schranke | Adressen | warum sie nicht bloß Kosmetik ist |
|---:|---|---:|---|
| 1 | `wechselkurs[g] ≥ 1` | 5 | Nenner jeder Bewertung (T47); null bricht ab, negativ dreht still jedes Vorzeichen |
| 2 | Nominalindizes `> 0` | 22 | Nenner der Ratenbildung in T42 und Faktor jeder Bewertung |
| 3 | `produktivitaet[g] > 0` | 5 | Faktor der Produktionsfunktion |
| 4 | `leitzins[l] + aufschlag ≥ 1` | 4 | Nenner von `anleihekurs`; die Schranke sitzt am Instrument (T51) |
| 5 | `0 < markt.wert < 9,2 · 10^13` | 1 | Nenner von `markt.rendite` und `marktanteil`, Überlaufschranke von `tsd_in_cent` (T47) |
| 6 | `0 ≤ druck, gegendruck ≤ druck_max` | 32 | Klasse 9; ohne Obergrenze ist Kanal 8 unbeschränkt |
| 7 | `0 ≤ fondsanteil(l, s) ≤ 10.000`, `\|stufen(p)\| ≤ stufen_max` | 12 + 20 | ein Anteil über 100 % ist kein Anteil; die Zulässigkeitsprüfung aus T32 hält ihn ein, der Test prüft, dass sie es tut |

Dazu die **zwei Gleichheiten** aus T49: `land.<L>.leitzins = land.<L>.instrument.leitzins.stand`
und `land.<L>.haushaltssaldo = land.<L>.instrument.haushalt.stand`, je Runde und je Land.

Schranke 1 und 5 sind die beiden, die ohne Test still falsch würden statt laut: Ein
negativer Wechselkurs macht aus jedem Gewinn einen Verlust, und ein Marktkorb jenseits der
Überlaufschranke stürzt zwar nach T7 ab, aber erst in `tsd_in_cent` und damit an einer
Stelle, an der niemand die Ursache sucht.

**Prüfung 6 läuft über das Ende des Jahrgangsfensters hinaus, und das braucht eine Regel.**
Die exogenen Pfade aus T25 tragen nur R+1 Stützstellen. Ab Runde R+1 werden sie **auf ihrem
letzten Wert eingefroren**, nicht fortgeschrieben, und der Lauf wird als `ueber_fenster`
gekennzeichnet. Einfrieren ist hier die schärfere Wahl: Läuft eine Größe danach weg, ist es
das Modell und nicht die Eingabe. Kosten: 200 Weltschritte.

**T31 — Der Regressionsbestand wird nie stillschweigend neu erzeugt.** Ein bewusst
geänderter Modellwert macht Prüfung 4 rot — das ist der Zweck. Die Erneuerung läuft
über einen eigenen Aufruf, der einen **Abweichungsbericht** schreibt: welche Partie,
welche Größe, alter und neuer Wert, welche Kettenglieder sich geändert haben. Dieser
Bericht ist der Gegenstand der Prüfung, nicht der neue Bestand.

**T34 — Die Ergebnisgröße ist ein `i64` in Milli-Runden; die Skala gehört `spiel.md`.**
Die dreiteilige Tabelle steht dort und wird hier **nicht** wiederholt, nicht ausgelegt und
nicht gedeckelt. Was der Architektur zusteht, ist ausschliesslich:

- Typ `i64`, Einheit Milli-Runden, **kleiner ist besser**;
- die Ordnung ist strikt total: Bei gleichem Ergebniswert entscheidet die Profilkennung,
  bei gleichem Profil der Stichprobenindex — nie die Auffindereihenfolge;
- der Median über eine gerade Anzahl ist der kleinere der beiden mittleren Werte
  (so `spiel.md`);
- **die Bereichsprüfung ist die Bandprüfung.** `spiel.md` verlangt: ein Ergebnis ausserhalb
  `1.000 … R × 1.000 + 30.000` — bei R = 24 also 1.000 … 54.000 — ist ein harter Fehler.
  Geprüft wird schärfer und ohne eigene Entscheidung, weil es aus derselben Tabelle folgt:
  Der Wert muss in **einem der drei Bänder** aus T40 liegen. Die Lücken dazwischen
  (24.001 … 24.999 und **28.001 … 30.999** bei R = 24) sind unerreichbar; ein Wert dort ist
  ein Rechenfehler und kein Ausreisser. Die Prüfung kostet zwei Vergleiche und findet genau
  die Kante, die Befund 10 an der Skala selbst gefunden hat. Die obere Lücke beginnt seit
  `spiel.md` Fassung 4 bei 28.001 und nicht mehr bei 27.001, weil die Kappung des
  Fehlbetrags entfallen ist (T40); der Bereich `1.000 … R × 1.000 + 30.000` ist davon
  unberührt, weil sein oberes Ende aus dem Todesband kommt.

**T35 — Die Ziehregel für Maß 1, ausgeschrieben, weil sie sonst am Zufallserzeuger hängt.**
`spiel.md` gibt vor: Bündelgröße gleichverteilt aus `{0,1,2,3}`, dann so viele Aktionen
ohne Zurücklegen gleichverteilt aus der Liste der zulässigen Aktionen, Doppelte im
Stichprobensatz bleiben. Das ist eindeutig bis auf das Verfahren, und ein anderes Verfahren
ergibt eine andere Stichprobe. Verbindlich ist deshalb:

1. `s = splitmix64(wurzelstartwert, jahrgang_id, parameter_pruefsumme, BUENDELZIEHUNG, t, i)`
   nach T11; `s` wird als xoshiro-Zustand fortgeschrieben, und zwar nur innerhalb dieser
   einen Ziehung.
2. `n = naechster(s) mod 4`. Ist `n` größer als die Länge `m` der Zulässigkeitsliste, gilt
   `n = m`.
3. Die Liste steht in der kanonischen Ordnung aus T32. Partielles Fisher-Yates:
   für `k = 0 … n−1` sei `j = k + (naechster(s) mod (m − k))`, tausche `L[k]` und `L[j]`.
   Das Bündel sind die ersten `n` Einträge.
4. Das Bündel wird vor dem Setzen nach Aktionskennung sortiert. Nach `spiel.md` hat keine
   Aktion einen Zeitpunkt innerhalb der Runde; die Sortierung stellt sicher, dass die
   Ziehreihenfolge das Ergebnis nicht berührt. Verletzt es `buendel_zulaessig` (T32), wird
   es auf das größte zulässige Anfangsstück gekürzt — nicht neu gezogen, weil eine
   Verwerfungsschleife die Zahl der Ziehungen zustandsabhängig machte.
5. **Die Vorratsfortschreibung der eingespeisten Runde** folgt `spiel.md`: `vi += 3·ai` am
   Rundenanfang mit dem `ai` des Referenzprofils, dann `vi −= 5` je tatsächlich gesetzter
   Aktion der Art `i`. Bei einem Bündel kleiner als drei driftet der Vorrat, und das ist
   gewollt — die Trägerpartie spielt danach mit dem Zustand weiter, den die Einspeisung
   hinterlassen hat, nicht mit einem zurechtgesetzten.

`naechster(s) mod k` ist verzerrt, sobald `k` kein Teiler von 2^64 ist. Die Verzerrung
liegt bei `m ≤ 2^32` unter 2^-32 und ist damit kleiner als jede Wirkung, die Maß 1 misst;
sie wird hier benannt statt behoben, aus demselben Grund wie in Punkt 4.

**T43 — Das Vorratsverfahren ist ein Baustein des Prüfstands, und es hat eine Invariante,
die es testbar macht.** `spiel.md` legt es fest (Vorrat `vi`, `vi += 3·ai` je Runde, drei
Steckplätze, `vi −= 5` je Steckplatz, größtes `vi` gewinnt, Gleichstand nach kleinerer
Kennung, `ai = 0` verbietet nicht, sondern schiebt ans Ende). Der Architektur stehen zwei
Dinge zu, und beide stehen hier:

- **Die Zulässigkeit, gegen die es prüft, ist die Liste aus T32** — einmal je Runde gegen
  den Rundenanfangszustand gebildet, beim Fortschreiten über die drei Steckplätze nur um
  die mit dem Bündel unverträglichen Einträge gekürzt. Kein Weltschritt, keine
  Zwischenrechnung.
- **Die Invariante, gegen die ein Einheitstest läuft:** Sind in fünf aufeinanderfolgenden
  Runden alle fünf Arten durchgehend zulässig, so steht der Vorratsvektor danach wieder auf
  `(0,0,0,0,0)`, und jede Art `i` hat genau `3·ai` der fünfzehn Steckplätze bekommen. Das
  gilt für **alle 126 Profile** — ich habe es für alle 126 durchgerechnet, und die von
  `spiel.md` selbst angegebene Probe des Referenzprofils (`1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 |
  3,4,5`) fällt dabei zeichengleich heraus. Damit ist das Verfahren nicht nur beschrieben,
  sondern hat einen Test, der eine falsche Implementierung in fünf Runden fängt statt in
  einer 24-Runden-Partie mit Median über zwanzig Startwerte.
- **Dieselbe Invariante in allgemeiner Form — und seit `spiel.md` Fassung 4 steht sie in
  beiden Dokumenten wörtlich gleich:** Nach `5k` Runden steht der Vorratsvektor wieder auf
  `(0,0,0,0,0)`, und Art `i` hat `3k·ai` der `15k` Steckplätze bekommen. Für `k = 1` sind
  das fünf Runden und `3·ai` von fünfzehn — genau der Fall, den `spiel.md` zwei Absätze
  darunter als Probe rechnet. Für `k = 3` sind es fünfzehn Runden und `9·ai` von
  fünfundvierzig. Der Satz, der in den Fassungen 2 und 3 von `spiel.md` „über 15 Runden
  … `3·ai`" sagte und beide Fälle mischte, ist dort ersetzt; die Stelle, die dreimal
  Befund war, ist geschlossen, und ich habe beide Sätze in diesem Lauf nebeneinandergelegt.
  Verbindlich für den Bau bleibt diese Invariante; der Einheitstest aus T30 Prüfung 1 prüft
  `k = 1` und `k = 3`, damit die Verwechslung auch dann auffällt, wenn jemand sie aus einer
  älteren Fassung in die Implementierung übernimmt.

**T41 — Wie das Profil die Kandidaten des Suchbots einschränkt.** Das war die Hälfte von
Befund 4, die mir gehörte: T35 schrieb die Ziehregel nur für Maß 1 aus. Verbindlich ist:

1. Das Vorratsverfahren (T43) liefert für die Runde die Artenfolge der drei Steckplätze.
   Der Suchbot sucht **über Ziele und Stufen, nie über Arten** (`spiel.md`).
2. Für Kandidat `c = 0 … 59` und Steckplatz `j = 1,2,3`: `Lj` ist die Teilliste der
   zulässigen Aktionen der Art des Steckplatzes in kanonischer Ordnung (T32), gekürzt um
   die mit den schon gewählten `x1 … xj−1` unverträglichen Einträge. Gezogen wird
   `xj = Lj[naechster(s) mod |Lj|]` mit
   `s = splitmix64(…, SUCHBOT_KANDIDATEN, runde, c)`.
3. Ein Steckplatz ohne zulässige Art entfällt; `|Lj| ≥ 1` gilt sonst immer, weil das
   Vorratsverfahren nur unter Arten wählt, die mindestens eine zulässige Aktion haben.

**Genau drei Ziehungen je Kandidat, genau 60 Kandidaten, keine Verwerfungsschleife, keine
Zählung eines Produktraums.** Doppelte Kandidaten bleiben — wie in Maß 1 —, sie kosten ein
Weltschritt und ändern kein Ergebnis. Der Preis ist damit fest bei `1 + 60` Weltschritten je
Runde, unabhängig davon, wie groß die Zulässigkeitsliste gerade ist; das ist dieselbe
Begründung wie bei T28 und der Grund, warum die Rechnung in Abschnitt 10 überhaupt trägt.

**T44 — Die Zielgröße des Suchbots ist die Ergebnisprognose des Zwischenzustands, und sie
ist abgeleitet, nicht erfunden.** T41 sagte, **welche** 60 Kandidaten entstehen, aber nicht,
**wonach** unter ihnen gewählt wird; der Gleichstandsbrecher setzte eine Vergleichsgröße
voraus, die kein Satz benannte. Solange sie fehlt, misst Maß 2 die Wahl des Bauagenten
statt das Spiel, und Maß 3 misst sie zweimal.

Nach genau einem Weltschritt läuft die Partie in aller Regel noch; die Ergebnisgröße von
`spiel.md` ist aber erst am Partieende definiert. Gebraucht wird also eine **statische**
Bewertung `B(z)` des Zwischenzustands, und sie beantwortet die Frage, die die Ergebnisgröße
selbst stellt: *Was ergäbe diese Partie, wenn sie hier endete?*

```
B(z) =  r × 1.000                      das Mandat ist in Runde r erfüllt
        30.000 + (R + 1 − d) × 1.000   in Runde d an einer Todesart gestorben
        (R + 1) × 1.000 + v(z) + e(z)  sonst — die Partie läuft weiter
```

**Alle drei Zeilen sind seit `spiel.md` Fassung 4 wörtlich die Ergebnisgröße aus `spiel.md`,
nur auf `z` gerechnet statt auf das Partieende.** Die dritte Zeile trug in Fassung 4 dieses
Dokuments noch das Literal `25.000`; sie steht jetzt als Formel in R, weil T40 keine
abgeleitete Zahl als Literal duldet und `(R+1) × 1.000` bei einem anderen Jahrgang eben
nicht 25.000 ist. Bei R = 24 ist es 25.000, also unverändert.

- `v(z) = teile_gerundet(max(0, schwelle_v − fondsvermoegen(z)) · 1.000, schwelle_v)` —
  fehlendes Vermögen in Promille seiner Schwelle. `fondsvermoegen` ist die Funktion aus
  **T47** und damit seit `spiel.md` Fassung 4 einschliesslich der zum Ausstiegswert
  bewerteten Beteiligungen; einen zweiten Rechenweg gibt es nicht.
- `e(z)` = Summe über die **zwei Länder mit dem höchsten Einfluss** (Gleichstand nach
  `LandId`) von `teile_gerundet(max(0, schwelle_e − einfluss[land]) · 1.000, schwelle_e)` —
  fehlender Einfluss in Promille seiner Schwelle. Zwei Länder, weil das Mandat zwei verlangt.
  `spiel.md` Fassung 4 hat dieselbe Regel für die Ergebnisgröße übernommen; beide Dokumente
  rechnen den Fehlbetrag jetzt mit **einer** Formel.

Beide Schwellen stehen bereits in `parameter.toml` (T27, Mandatsschwelle). **`B` hat damit
keinen freien Parameter** — keine Gewichtung, keinen eigenen Kalibrierwert, nichts, was ein
Bauagent wählen könnte. Genau das ist die Antwort auf den Einwand: Maß 2 misst nicht mehr
die Wahl des Bots, weil an dieser Stelle keine Wahl mehr besteht.

**Und `B` ist an `spiel.md` gebunden, nicht daneben gestellt.** Benennt der Entwurf die
Vergleichsgröße selbst, sticht seine Fassung diese hier, und T44 schrumpft auf die
Rechenvorschrift dazu. Ändert sich die Ergebnisgröße, ändert sich `B` mit ihr, ohne dass
jemand zwei Stellen nachführen müsste.

**Es gibt seit `spiel.md` Fassung 4 keine Abweichung mehr zwischen `B` und der
Ergebnisgröße, und das ist die eigentliche Nachricht dieser Fassung.** Fassung 4 dieses
Dokuments musste hier eine Kappung ausnehmen: `spiel.md` begrenzte damals jeden der beiden
Teile bei 1.000 Promille, und für eine Bewertungsfunktion wäre das tödlich gewesen — ein
Fonds, der zu Partiebeginn in beiden Ländern Einfluss null hat, säße bei gekappten 1.000,
und eine Verbesserung des ersten Landes von 0 auf 60 Prozent der Schwelle bliebe
**unsichtbar**. Der Spielentwerfer hat dieselbe Begründung eine Ebene höher gelten lassen
und die Kappung **ganz gestrichen**. Damit rechnen beide Dokumente in diesem Zweig
buchstabengleich, und die Stelle kann nicht mehr auseinanderlaufen.

Der Preis steht in T40 und T34 und ist zweimal eine Zahl (Bandende 27.000 → 28.000,
Lückengrenze 27.001 → 28.001). Die Schranke bleibt: `v ≤ 1.000`, solange der Fonds lebt
(bei `fondsvermoegen ≤ 0` greift Todesart 1 in derselben Runde, T33 und T47; die 1.000
erreicht nur die Rundung), und `e ≤ 2.000`, also `25.000 ≤ B ≤ 28.000` im laufenden Fall —
oberhalb des Bandes „Mandat erfüllt" (bis 24.000) und unterhalb des Todesbandes (ab 31.000).
**Daraus folgt eine Eigenschaft, die eine Bewertung haben muss und die man ihr nicht ansieht:
Der Bot zieht den Tod nie vor.** Der schlechteste laufende Zustand steht bei 28.000, der
beste Tod bei 31.000. `B` bleibt trotz der Formelgleichheit eine **botinterne** Größe: Sie
wird nie als Partieergebnis berichtet, und die Bandprüfung aus T34 gilt für sie nicht, weil
sie auf einem Zwischenzustand steht und nicht auf einem Partieende.

**Warum das den Lobbyweg nicht strukturell erschlägt** — die Frage, an der eine reine
Vermögensbewertung gescheitert wäre: Einfluss ist nach `spiel.md` der geglättete Anteil des
Fonds **am gesamten Lobbydruck** eines Landes, nicht die Wirkung des Instruments. Aktion 3
legt den Druck in derselben Runde an; sie hebt `einfluss` also schon in dem einen
Weltschritt, den der Bot vorausrechnet — gedämpft durch die Glättung, aber ungleich null und
monoton im eingesetzten Budget. Der Kassenabfluss hebt `v`, der Druck senkt `e`, und welche
Wirkung überwiegt, entscheidet der Zustand und nicht die Bauart der Bewertung. Klasse 3
**kann** damit Gewinner stellen; ob sie es tut, ist die Frage, die Maß 2 stellen soll, und
nicht die, die es beantwortet, bevor es läuft.

**Dieselbe Prüfung für die beiden anderen Klassen, weil eine einzeln geprüfte Klasse nichts
beweist.** Klasse 1 (Position) wirkt unmittelbar auf `fondsvermoegen` und damit auf `v`;
unproblematisch. **Klasse 2 (Beteiligung) hing an einer Frage, die `spiel.md` Fassung 4
entschieden hat: Die zwölf Beteiligungen zählen zum Fondsvermögen** (T47), bewertet zum
Ausstiegswert. Damit wirkt Aktion 2 auf `v` wie Aktion 1, nur illiquide und um den
Ausstiegsabschlag verringert, und `B` behandelt beide gleich. Die Erörterung der Fassung 4 —
was geschähe, wenn sie nicht dazuzählten — ist damit gegenstandslos und gestrichen; sie
hatte einen einzigen Zweck, nämlich die Frage sichtbar zu halten, bis sie beantwortet ist.

Ein zweiter Weg der Klasse 2 bleibt bei Tiefe 1 unsichtbar, und dieser Punkt bleibt
bestehen: Eine Beteiligung verbilligt nach `spiel.md` das Lobbying im selben Sektor, zahlt
sich also erst in einer späteren Runde aus. Das ist kein Fehler der Bewertung, sondern der
Preis eines Zuges Vorausschau — und damit das erste konkrete Argument für die Tiefe 2, die
Abschnitt 12 offen hält.

**Ordnung und Gleichstand.** Gewählt wird der Kandidat mit dem kleinsten `B`. Bei
Gleichstand entscheidet die lexikographisch kleinste Folge der Aktionskennungen des Bündels
in der kanonischen Ordnung aus T32, danach der kleinere Kandidatenindex `c` aus T41 — nie
die Auffindereihenfolge. Doppelte Kandidaten (T41 lässt sie ausdrücklich zu) tragen dieselbe
Kennungsfolge und denselben `B`; ihr Gleichstand fällt auf `c` und ist damit entschieden.

**Tiefe.** Bei Tiefe 1 wird `B` auf dem Zustand nach dem einen Weltschritt ausgewertet, und
es gibt **keine** Fortsetzung durch den Heuristikbot — die Wendung „Nachspiel mit dem
Heuristikbot als Fortsetzung" aus Fassung 3 war an dieser Stelle irreführend und ist der
Grund, warum der Befund entstehen konnte. Bei Tiefe `d > 1` ist der Wert eines
Zwischenknotens das Minimum von `B` über seine 60 Kandidaten, rekursiv bis zur Tiefe `d`;
das Spiel hat einen einzigen Spieler, es gibt also keinen Gegenzug und kein Maximum.

**Kosten, in dieser Fassung berichtigt.** Fassung 5 nannte „rund zwanzig
Ganzzahloperationen, also drei Promille" und zählte damit nur `v` und `e` selbst — der
Prüfer der Runde 6 hat das unter *geprüft und nicht gezählt* beanstandet und recht damit.
`v(z)` ruft `fondsvermoegen(z)`, und das sind nach der Auszählung in T47 rund **230**
Operationen, davon 71 `i128`-Divisionen; dazu eine Division für `v`, vier Vergleiche und
zwei Divisionen für `e`. Zusammen **rund 240 Ganzzahloperationen** gegen 7.500 je
Weltschritt, also gut **drei Prozent** statt drei Promille. Im Suchbot fallen sie 60-mal je
Runde an, gegen 61 Weltschritte — auch dort rund drei Prozent. Der Planwert von 10 µs hat
Bandbreite bis 30, die Reserve rechnet mit 50, und die Abkürzung bei leeren Steckplätzen
(T47) senkt den tatsächlichen Wert weiter. Die Kostenrechnung `R × (1 + 60) = 1.464` bleibt
unverändert — und genau dafür braucht es eine statische Bewertung. Ein Nachspiel bis Runde R
je Kandidat kostete `60 · Σ(R+1−t) + R = 60 · 300 + 24 = 18.024` Weltschritte je Partie, das
Zwölffache, und würfe Abschnitt 10 um.

**Die drei Bots:**

- **Zufallsbot(startwert)** — zulässige Aktionen gleichverteilt, Ziehung nach T35, ohne
  Profil. Für Prüfungen 5 und 6.
- **Heuristikbot(profil)** — Arten nach dem Vorratsverfahren (T43), innerhalb einer Art
  nach einer festen, dokumentierten Rangfolge. Keine Nachspiele, also billig. **Er ist auf
  dem Referenzprofil `(1,1,1,1,1)` die „feste Folgepolitik" von Maß 1.**
- **Suchbot(profil, kandidaten=60, tiefe=1)** — 60 Kandidaten nach T41, jeder um einen
  Weltschritt vorausgerechnet und **statisch bewertet nach T44**; gewählt wird das kleinste
  `B`, Gleichstand nach T44 und nie nach Auffindereihenfolge. Eine Fortsetzung durch den
  Heuristikbot gibt es bei Tiefe 1 nicht. Kosten je Partie `R × 61`, bei R = 24 also
  **1.464** Weltschritte.

**T36 — Was der Prüfstand zu Maß 2 und 3 fest verdrahtet.**

- **Profilliste.** Die 126 Profile werden in lexikographisch aufsteigender Ordnung von
  `(a1…a5)` erzeugt und **nullbasiert** durchnummeriert. Die **Profilkennung** ist dieser
  Index und der Gleichstandsbrecher aus `spiel.md`; sie ist Teil der Schnittstellenversion
  (T17). Zwei Festwerte als Anker für den Test, beide durchgerechnet: Das Referenzprofil
  `(1,1,1,1,1)` trägt die **Kennung 76**, und die Kennungen **0 bis 5** sind genau die sechs
  Profile `(0,0,0,a4,a5)`.
- **Strategiekern, vierwertig.** Aktionsart mit dem größten Anteil unter `{1 Position,
  2 Beteiligung, 3 Lobby}`, Gleichstand nach kleinerer Kennung; Hebel und Sichtbarkeit gehen
  nicht ein. **Sind alle drei null, ist der Kern `ohne`** — nicht 1. Das ist Befund 8, und
  er lässt sich nur an dieser Stelle beheben: Ein dreiwertiger Kern zwingt den
  Gleichstandsbrecher, eine Positionsstrategie zu behaupten, in der keine Position vorkommt.
  Profile mit Kern `ohne` laufen mit, ihr Ergebnis wird berichtet, und sie gehen in keine
  der beiden Abnahmehälften von Maß 2 ein; klassifiziert sind 120. Der Kern wird einmal je
  Profil berechnet und mit der Profilliste abgelegt, nicht je Lauf neu.
- **Fensterlogik von Maß 3.** Beide Läufe gehen über die volle Partie; die Fenster sind
  nach T40 das erste und das letzte Partiedrittel, ausserhalb gilt das Referenzprofil, und
  der Suchbot fährt innerhalb wie ausserhalb. Der Profilwechsel geschieht am Rundenanfang;
  **der Vorrat läuft über den Wechsel hinweg weiter und wird nicht zurückgesetzt**
  (`spiel.md`). Damit kostet ein Lauf dasselbe wie eine gewöhnliche Suchbotpartie, und die
  Rechnung in Abschnitt 10 trägt. Für Maß 3 sind alle 126 Profile wählbar, auch die sechs
  ohne Kern — dort misst der Vektorabstand und nicht die Klasse.
- **Was `B` aus T44 in beiden Maßen nicht ist.** Das Profilergebnis `E(p)`, der
  Gewinnvergleich gegen `R × 1.000` und die Argminima `p*` und `q*` laufen ausschliesslich
  über die **Ergebnisgröße** aus `spiel.md`, nie über `B`. `B` steuert den Bot innerhalb der
  Partie und verlässt sie nicht. Beide Maße hängen deshalb an T44 — das ist der Grund,
  warum sein Fehlen ein schwerer Befund war —, aber keines von beiden rechnet mit ihr.

**T37 — Der Rückvergleich weist je Sollreihe aus, ob sie überhaupt etwas prüfen kann — und
`spiel.md` hat entschieden, welche entscheiden.** Im Weltlauf werden die Politikinstrumente
auf die historisch tatsächlichen Werte gesetzt. Damit ist die Leitzinsreihe des Modells per
Konstruktion die Sollreihe; ihr Fehler ist null und ihre Richtungstreue eins, ohne dass das
Modell irgendetwas geleistet hätte.

| Klasse | Reihen | Zahl | Bedeutung |
|---|---|---:|---|
| `frei` | BIP (4), Sektoranteile (12), Verbraucherpreise (4), Wechselkurs (3) | 23 (19 unabhängig), dazu der Handelsblock | prüft die Maschine, entscheidet die Abnahme |
| `gesetzt` | Leitzins (4) | 4 | Eingabe des Laufs, Fehler null per Konstruktion; wird berichtet, entscheidet nichts |
| `abgeleitet` | Staatsschuldenquote (4) | 4 | Zähler folgt dem gesetzten Haushaltssaldo, nur der Nenner ist endogen; wird berichtet, entscheidet nichts |

**Die Abnahme läuft über 16 Prüfgegenstände mit Toleranz 2**, so von `spiel.md` Fassung 3
gesetzt; meine Rückfrage aus Fassung 2 ist damit beantwortet und aus Abschnitt 12
gestrichen. Prüfgegenstand ist nicht die Reihe, sondern die Größe:

| Prüfgegenstand | Zahl | zusammengefasst aus |
|---|---:|---|
| BIP je Land | 4 | je eine Reihe |
| Sektorstruktur je Land | 4 | die drei Anteilsreihen des Landes, **alle drei** müssen bestehen |
| Verbraucherpreise je Land | 4 | je eine Reihe |
| Wechselkurs je Land ausser USA | 3 | je eine Reihe |
| Handelsblock | 1 | 40 Ströme, Median des MAPE und Median der Richtungstreue; das schlechteste Fünftel wird ausgewiesen |
| **Summe** | **16** | |

Ein Prüfgegenstand besteht, wenn er beide für ihn geltenden Schwellen einhält. Der Lauf ist
bestanden, wenn höchstens zwei der sechzehn reissen; jeder gerissene wird einzeln benannt,
mit beiden Zahlen. Berichtet werden alle 31 Reihen plus die 40 Ströme, entscheiden tun die
sechzehn.

**T42 — Die drei Fehlermaße, ausgeschrieben, weil `spiel.md` sie beziffert und nicht
rechnet.** Alles in Ganzzahlen über `teile_gerundet` (T6). `S` ist die Zahl der
Stützstellen (im Prüfjahrgang 25), `V` die Menge der verwertbaren Stützstellen.

**Niveaureihen** (BIP, Sektoranteile, Staatsschuldenquote, 40 Handelsströme) —
mittlerer absoluter prozentualer Fehler in Zehntausendsteln, Schwelle **2.000 (= 20 %)**:

```
MAPE = Mittel über t ∈ V von  teile_gerundet(|modell(t) − soll(t)| · 10.000, |soll(t)|)
```

**`V` schliesst zwei Sorten Stützstelle aus, beide gezählt und ausgewiesen:** die mit
`gefuellt = 1` (so schon T24) und die mit `soll(t) = 0`. Der zweite Fall ist bei einem
bilateralen Agrarstrom zwischen zwei Ländern real, und ein Nullnenner ist nach T6 ein
Abbruch. Hat ein Strom weniger als die Hälfte verwertbarer Stützstellen, gilt er als nicht
prüfbar, geht in den Median des Handelsblocks nicht ein und wird als solcher berichtet. Die
Regel ändert keine Schwelle; sie definiert einen Fall, den `spiel.md` nicht kennt, nach dem
Muster, das T24 für gefüllte Jahre schon vorgibt.

**Ratenreihen** (Verbraucherpreise, Wechselkurs, Leitzins) — mittlerer absoluter Fehler auf
der Jahresänderungsrate, Schwelle **300 bp**:

```
rate(t) = teile_gerundet((wert(t) − wert(t−1)) · 10.000, wert(t−1))          in bp
MAE     = Mittel über t = 2 … S von |rate_modell(t) − rate_soll(t)|
```

**Eine Neubasierung nach T8 wird vor der Ratenbildung herausgerechnet:** Steigt
`basiswechsel` zwischen `t−1` und `t` um `d`, wird `wert(t)` für diese eine Rate mit
`1.000^d` multipliziert. Ohne diese Zeile meldete ein Basiswechsel einen Absturz um 99,9
Prozent als Modellfehler. Im Prüfjahrgang tritt sie nie ein — sie steht hier, weil T8 selbst
verlangt, dass kein Zweig ungeprüft bleibt, und die Regressionspartie von 1980 sie
mitnimmt.

**Richtungstreue** (alle Reihen) — Anteil der `S−1` Übergänge mit gleichem Vorzeichen, in
Zehntausendsteln, Schwelle **6.000 (= 0,6)**:

```
treue = teile_gerundet(#{t : sgn(Δmodell(t)) = sgn(Δsoll(t))} · 10.000, S − 1)
```

`sgn` ist die dreiwertige Vorzeichenfunktion auf Ganzzahlen; „beide unverändert" zählt
damit als Treffer und „einer unverändert, einer nicht" als Fehlschlag. Das folgt aus der
Schreibweise in `spiel.md` und ist keine Auslegung — auf Ganzzahlen gibt es keine andere.

**Parallelität ohne Preisgabe des Determinismus:** Jedes Nachspiel ist eine reine Funktion
von (Jahrgang, Parametersatz, Modus, Startwert, Politik, Runde, Stichprobenindex); der
abgeleitete Zufallsstartwert folgt aus genau diesem Tupel (T11). Ergebnisse werden in ein
vorab bemessenes Feld **an ihrem Index** abgelegt, nie angehängt. Jede Zusammenfassung läuft
über das sortierte Feld. Damit liefert der Prüfstand mit einem Kern und mit
zweiunddreissig dasselbe Ergebnis.

**Berichtspflicht:** Jeder Befund trägt `ticks_gesamt`, `sekunden`, `ticks_je_sekunde`, den
Modus und die Größe der Sollmaske. Die Schätzung des nächsten Abschnitts wird damit binnen
einer Nacht durch eine Messung ersetzt — und bleibt gemessen.

## 10. Was das Modell an Rechenzeit kostet

Ein Weltschritt umfasst geschätzt 7.500 elementare Ganzzahloperationen; den Löwenanteil
tragen die Markträumung (2 Sektoren × 40 Halbierungen, T28) und das Mitschreiben der
Kette (T18). Teuer sind darin die `i128`-Divisionen aus T6. **Planwert: 10 Mikrosekunden
je Schritt**, Bandbreite 5 bis 30. Die Spalte „ungünstig" rechnet mit 50 Mikrosekunden,
also dem Fünffachen des Planwerts — eine Reserve, keine Erwartung.

**Die Bewertung aus T47 ändert diese Schätzung nicht, und diesmal ist die Zahl gezählt statt
gerundet.** Ein voller Aufruf von `fondsvermoegen` kostet nach der Tabelle in T47 rund 230
Ganzzahloperationen, davon 71 `i128`-Divisionen; er fällt im `spielmodus` einmal je
Weltschritt in Schritt 6 an und im Suchbot zusätzlich je Kandidat. Das sind gut drei Prozent
eines Weltschritts, nicht die drei Promille der Fassung 5 — und weiterhin tief innerhalb der
Bandbreite 5 bis 30 µs, die der Planwert ohnehin trägt. **Im `weltlauf` fällt er gar nicht
an**, weil das Fondsteilsystem nach T38 nicht läuft; der Rückvergleich ist von der
Korrektur nicht berührt. Keine Zeile der Tabelle unten bewegt sich.

**Gegenkraft 5 kostet je Runde 106 Lesezugriffe, 16 Schreibzugriffe und 16 Aufrufe des
dritten Skalenübergangs, und auch diese Zahl ist gezählt.** Die Aufschlüsselung steht in
`spiel.md` im Abschnitt *Wo die Regel läuft, und warum Kanal 3 zyklenfrei bleibt*; sie ist
hier nachgezählt und stimmt überein:

| woher | gelesene Adressen | Zahl |
|---|---|---:|
| Schritt 3 | `lies_neu(land.<l>.instrument.<i>.stand)`, 4 Länder × 4 Instrumente | 16 |
| Schritt 4 | `lies_neu(welt.preis.<s>)`, s ∈ {1, 2} | 2 |
| Schritt 4 | `lies_neu(handel.<a>.<b>.<s>)`, der ganze Handelsblock | 40 |
| Schritt 4 | `lies_neu(land.<l>.sektor.<s>.wertschoepfung)`, für `bip`, 4 × 3 | 12 |
| Schritt 4 | `lies_neu(land.<l>.staatsschuld)`, für `schuld` | 4 |
| Vorrunde | `lies_alt(land.<l>.instrument.<i>.stand)`, für `hub` | 16 |
| Vorrunde | `lies_alt(land.<l>.instrument.<i>.gegendruck)`, für den Zerfall | 16 |
| | **Summe** | **106** |

`16 + 2 + 40 + 12 + 4 + 16 + 16 = 106`. **Gezählt sind unterschiedliche Adressen, nicht
Zugriffsvorgänge**, und an genau einer Zeile macht das einen Unterschied: Der Handelsblock
steht mit **40** und nicht mit 64. 64 wäre die Zahl der Vorgänge — vier Länder mal zwei
Sektoren mal acht Strömen je `handelsvolumen(l, s)` —, aber ein Strom zwischen zwei
spielbaren Ländern geht in zwei davon ein. Die 40 sind der Block vollständig: nach T15
`Gebiet × Gegenüber × handelbarer Sektor = 5 × 4 × 2`, und die vier `handelsvolumen`
zusammen berühren jedes geordnete Gebietspaar, weil an jedem Paar mindestens ein spielbares
Land beteiligt ist. Die 16 Schreibzugriffe sind die sechzehn `gegendruck`-Adressen, die 16
Aufrufe die des dritten Skalenübergangs aus T50 — je Adresse einer, sämtlich in Schritt 5,
und das ist zugleich der Nachweis für dessen „genau ein Aufrufort".

**Auf die Tabelle oben wirkt das nicht.** 106 Lesezugriffe und 16 Multiplikationen sind
gegen die geschätzten 7.500 Ganzzahloperationen eines Weltschritts rund anderthalb Prozent,
und Gegenkraft 5 lief in dieser Schätzung schon mit; neu ist nicht die Arbeit, sondern dass
sie abgezählt ist. **Zwei frühere Zahlen sind damit abgelöst**: die 120 der Fassung vom
2026-09-02 (sie zählte den Zollstand doppelt, obwohl die damalige Zollzeile ihn gar nicht
las) und die 112 des Prüfbefunds vom 2026-09-02 (richtig gerechnet, aber für die alte
Zollzeile). Der Weg von der einen zur anderen: `112 + 8 − 16 + 2 = 106` — der Zollstand
kommt mit `lies_neu` und `lies_alt` hinzu, beide Sektorpreiszeilen fallen ersatzlos weg, die
zwei Weltpreise treten an ihre Stelle.

**Der Planwert ist unverändert geschätzt und nicht gemessen.** Mein Logbuch verlangt, beim
nächsten Lauf zuerst den gemessenen `ticks_je_sekunde` zu lesen; es gibt ihn weiterhin
nicht. Unter `ventures/0016-…/kern/` stehen inzwischen Festkomma, Zufall, Prüfsumme,
Zustand und Schreiber, aber kein Weltschritt und kein Prüfstandslauf — gemessen ist damit
die Arithmetik, nicht die Schleife. Das bleibt die größte Unsicherheit dieses Abschnitts,
und sie steht in Abschnitt 12.

Grundlage ist die **R = 24-Runden-Partie** aus `spiel.md` Fassung 3. Alle Zeilen sind in
diesem Lauf gerechnet.

| Lauf | Weltschritte | bei 10 µs | ungünstig (50 µs) |
|---|---:|---:|---:|
| eine Partie, Heuristikbot | 24 | 0,24 ms | 1,2 ms |
| eine Partie, Suchbot (60 Kandidaten, 1 Zug voraus) | 1.464 | 15 ms | 73 ms |
| **1.000 Partien, Heuristikbot** | 24.000 | **0,24 s** | 1,2 s |
| **1.000 Partien, Suchbot** | 1.464.000 | **15 s** | 1,2 min |
| Entscheidungsdichte, K=30, ein Startwert | 9.024 | 0,090 s | 0,45 s |
| **Entscheidungsdichte, 50 Startwerte** | **451.200** | 4,5 s | 23 s |
| **Strategievielfalt, 126 Profile × 20 Startwerte** | **3.689.280** | 37 s | 3,1 min |
| **Optimumsverschiebung, zwei Fenster** | **7.378.560** | 1,2 min | 6,1 min |
| **Bruchlauf, 10.000 Zufallspartien** | **240.000** | 2,4 s | 12 s |
| **Beschränktheit, 200 Runden** | **200** | 2 ms | 10 ms |
| **Rückvergleich, ein Weltlauf** | **24** | 0,24 ms | 1,2 ms |
| **Regressionsbestand, 1.000 Partien** | **24.000** | 0,24 s | 1,2 s |
| **Nachtlauf gesamt** | **11.783.264** | **2,0 min** | **9,8 min** |

Die Zeilen im Einzelnen, damit die Summe nachzählbar ist: `Σ(R+1−t)` für `t = 1…24` ist
`300`, also `30 × 300 = 9.000` je Startwert, zuzüglich 24 Weltschritte für die
Trägerpartie ergibt **9.024**; mal 50 Startwerte **451.200**. `126 = C(9,4)`,
`1.464 = 24 × 61`, `3.689.280 = 126 × 20 × 1.464`, `7.378.560` das Doppelte davon. Die drei
Maße zusammen sind **11.519.040**, so wie `spiel.md` es rechnet. Der Nachtlauf addiert
Bruchlauf, Beschränktheit, Rückvergleich und Regressionsbestand:
`11.519.040 + 240.000 + 200 + 24 + 24.000 = 11.783.264`. Die beiden Zeilen „1.000 Partien"
sind Vergleichswerte und gehen nicht in die Summe ein.

Alles auf **einem** Kern. Mit acht Rechenkernen fällt der Nachtlauf auf rund
**15 Sekunden** beim Planwert und auf rund **1,2 Minuten** im ungünstigen Fall. Womit
parallelisiert wird, ist nach T3 offen und für dieses Dokument gleichgültig: Gebunden ist
nach Abschnitt 9, dass ein Lauf mit einem und mit zweiunddreissig Kernen dasselbe Ergebnis
liefert, nicht das Mittel, mit dem das erreicht wird.

**Die Antwort auf die Frage, die dieser Abschnitt beantworten soll: Ja, der Prüfstand kann
täglich laufen — und stündlich.** Der Engpass ist nicht die Rechenzeit, sondern das
Tokenbudget der Agenten, die die Befunde lesen.

**Die Kalibrierschleife.** Tausend Parametersätze über den vollen Maßsatz (11.519.040
Schritte je Satz) kosten 11,52 Milliarden Weltschritte, also **32,0 Stunden auf einem Kern
und 4,0 Stunden auf acht** — keine Nachtaufgabe. Nachtfähig ist die verkürzte Fassung:
Maß 1 mit 10 statt 50 Startwerten (90.240) und Maß 2 mit 5 statt 20 (922.320), Maß 3 gar
nicht, weil die Verschiebung des Optimums erst interessant ist, wenn Maß 1 und 2 halten.
Zusammen **1.012.560 Schritte je Parametersatz**, für tausend Sätze also **21 Minuten auf
acht Kernen**. Die Vorgabe an den Selbstspieler lautet deshalb: grob mit der verkürzten
Fassung suchen, die zehn besten Sätze mit der vollen nachrechnen.

**Die Gegenrechnung, die die Stackwahl trägt:** Derselbe Weltschritt kostet in Python
zwischen 0,75 und 3 Millisekunden, also das 75- bis 300-fache. Der Nachtlauf läge bei
**2,5 bis 9,8 Stunden** auf einem Kern. Er wäre damit nicht täglich, sondern gelegentlich —
und die Kalibrierschleife wäre auch in der verkürzten Fassung unmöglich. Das ist die Zahl,
an der die Wahl aus T1 hängt. Sie ist durch die kürzere Partie kleiner geworden, aber der
Abstand ist derselbe: Der Faktor entscheidet, nicht die Partielänge.

**Beim Käufer** kostet eine Runde einen Weltschritt: 10 Mikrosekunden. Der Speicherbedarf
sind 2,5 kB Zustand, unter 1 MB Jahrgänge und wenige hundert kB Kettenverlauf. Das
Produkt läuft auf allem und braucht keinen Server — die Kostenrechnung der Idee (keine
Kosten je Kunde) hält.

## 11. Auslieferung, und wo Geld anfängt

**Windows x86-64 zuerst**, Linux gleich mit (dasselbe Programm, andere Zielkennung),
**macOS nicht in Fassung eins**: Beglaubigung durch Apple kostet 99 USD im Jahr und wäre
eine Ausgabe nach Hausregel 1. Ebenso: Eine gehostete Bauumgebung ist **nicht** der
Vorgabeweg — gebaut und geprüft wird im Nachtlauf der Fabrik, auf dem Rechner des
Betreibers. Wer eine gehostete Kette will, schreibt eine Gate-Vorlage.

Die Plattformgleichheit wird nicht behauptet, sondern geprüft: Prüfung 3 vergleicht die
Prüfsummen aus dem Windows- und dem Linux-Lauf derselben Partien.

Aus `daten.md` folgt eine Auslieferungsauflage: `LIZENZEN.md` neben den Jahrgangsdateien,
eine Seite „Datenquellen" im Hauptmenü, ein Satz zur Bearbeitung („Die Ausgangsdaten wurden
aggregiert und in ganzzahlige Einheiten umgerechnet; die Quellen verantworten diese
Bearbeitung nicht") und der Hinweis, dass die IWF-Daten beim IWF kostenfrei erhältlich sind.
Alle drei Stellen werden aus dem Manifest des Jahrgangs erzeugt (T23), nicht von Hand
gepflegt — sonst weichen sie beim ersten Datenaktualisierungslauf von der Wahrheit ab.

## 12. Was ich nicht entschieden habe

Die Rückfragen der Fassungen 2 und 4 — Abnahme über 31 oder 23 Reihen, Zusammenfassung des
Handelsblocks, Beteiligungen im Fondsvermögen — sind von `spiel.md` Fassung 3 und 4
beantwortet und stehen in T37 und T47; sie sind hier gestrichen, weil eine beantwortete
Frage in dieser Liste nur noch Platz kostet. Offen bleibt:

- **Zwei Stellen in ADR 0011, die ich nicht selbst entscheiden kann. Beide blockieren
  nichts, beide gehören dem Betreiber.** *Erstens:* Massnahme 2 des ADR soll unbeabsichtigte
  Überläufe „laut statt still" machen; sie kann das nicht, weil `-fwrapv` aus Massnahme 1
  genau diese Sanitizer-Prüfung abschaltet (Beleg in T7). Ich habe die Lücke mit einer
  vierten Massnahme geschlossen statt den ADR zu ändern — das ist meine Entscheidung, die
  Frage, ob der ADR nachgeführt wird, nicht. *Zweitens:* Das erste Argument des ADR setzt
  voraus, dass der Spielstand künftig den **Zustand** speichert statt der Aktionsfolge; die
  Folgen des ADR ordnen diesen Wechsel nicht an. Bis dahin gilt T22 unverändert, und daraus
  folgt T52. Wird der Wechsel angeordnet, wird T52 billiger, aber nicht überflüssig.
- **Der Planwert von 10 Mikrosekunden je Weltschritt ist weiterhin geschätzt.** Den Kern
  gibt es inzwischen in Teilen — Festkomma, Zufall, Prüfsumme, Zustand, Schreiber —, aber
  keinen Weltschritt, also weiterhin keinen gemessenen `ticks_je_sekunde`. Liegt der
  gemessene Wert über 50 µs, trägt Abschnitt 10 nicht mehr, und dann ist die Markträumung
  anders zu bauen als über 40 Halbierungsschritte. Das ist die einzige Zahl dieses
  Dokuments, die eine Prüfung im Bau umwerfen kann — und seit T6b hängt an ihr zusätzlich
  die Frage, ob die Divisionsform den Abstand aus der Stackmessung erklärt.
- **Ob der Suchbot mit Tiefe 1 stark genug ist, damit Maß 2 das Spiel misst und nicht den
  Bot.** *Wonach* er sucht, ist seit T44 entschieden und hat keinen freien Parameter mehr;
  offen ist allein, *wie weit*. Neu gerechnet für R = 24: Tiefe 2 kostet je Partie
  `24 × (1 + 60 × 61) = 87.864`
  statt 1.464 Weltschritte, Maß 2 und 3 zusammen **664 Millionen**, also 1,8 Stunden auf
  einem Kern und **rund 14 Minuten auf acht** beim Planwert, im ungünstigen Fall 1,2 Stunden
  auf acht. Das sprengt den Nachtlauf nicht, es verlegt ihn. Tiefe 2 ist damit kein
  Ausschluss, sondern eine Entscheidung, die der Selbstspieler treffen darf, wenn Maß 2 mit
  Tiefe 1 keinen Gewinner in allen drei Klassen findet.
- **Die Zahlenwerte sämtlicher Schwellen und Elastizitäten.** Sie stehen nach T27 in der
  Parameterdatei und werden vom Selbstspieler gesucht, nicht von mir gesetzt.
- **Die konkrete Rangfolge im Heuristikbot** innerhalb einer Art. Modellierungsfrage des
  Selbstspielers; die Architektur verlangt nur, dass sie fest, dokumentiert und
  gleichstandsfrei ist.
- **Die Ausschlussregel für Stützstellen mit `soll = 0` (T42) habe ich entschieden, nicht
  offengelassen** — sie folgt dem Muster, das T24 für gefüllte Jahre schon setzt, und ohne
  sie bricht der Rückvergleich an einem bilateralen Nullstrom ab. Sie ändert keine Schwelle.
  Hält der Spielentwerfer sie für falsch, ist sie eine Zeile in T42 und sonst nichts.
- **Die elf Startwerte in T46 habe ich ebenso entschieden statt zurückgegeben**, und der
  Grund ist derselbe: Jeder von ihnen folgt aus einer Regel, die schon dasteht (Numéraire,
  Zähler ohne Vorgeschichte, Aggregatblock ohne Regierung), keiner ist eine Wahl zwischen
  zwei sinnvollen Zahlen. Eine Rückgabe hätte einen Lauf des Spielentwerfers gekostet und
  dieselben elf Zahlen ergeben. Hält er eine für falsch, ist es eine Tabellenzeile.
- **Die dreizehn Skalenklassen und die drei Übergänge habe ich entschieden statt
  zurückgegeben**, aus demselben Grund wie die elf Startwerte: Eine Einheit ist keine
  Spielfrage. Bei zweien ist der Spielraum trotzdem grösser als bei den übrigen, und ich
  nenne sie, damit sie nicht als selbstverständlich durchgehen — der **Lobbypunkt** (T50;
  jede andere gemeinsame Einheit für Druck und Gegendruck täte es auch, aber irgendeine muss
  es geben) und die **Instrumentenstufe** der Finanzmarktregulierung (T5 Klasse 10; sie
  könnte ebenso in Zehntausendsteln stehen, dann hiesse „ein Schritt" eine andere Zahl).
  Beide sind je eine Zeile, falls der Spielentwerfer sie anders will.

**Vier Beobachtungen an `spiel.md`, die ich melde statt zu ändern** (die Rolle verbietet
mir, dem Entwurf zu widersprechen; keine blockiert den Bau). **Punkt 3 ist seit dem
2026-09-04 erledigt und bleibt durchgestrichen stehen**, weil eine gelöschte Beobachtung
nicht mehr zeigt, dass die Rückgabe funktioniert hat:

1. Die Ergebnisskala trägt in der 30.000 ein echtes Literal, und das Band „überlebt" stösst
   seit dem Wegfall der Kappung dagegen, sobald `R ≥ 27` — die Schranke ist jetzt scharf
   statt grosszügig, in T40 nachgerechnet. Für 1997–2021 ist das folgenlos, und `spiel.md`
   lässt das Fenster nur enger werden. T40 zieht die Schranke bei `R ≤ 26` in den
   Jahrgangsbau, damit sie nicht erst in einer Ergebnisverteilung auffällt.
2. **Zwei Adresspaare tragen denselben Wert.** `land.<L>.leitzins` steht im Aggregatblock
   *und* als Instrumentenstand, `land.<L>.haushaltssaldo` ebenso; `spiel.md` zählt beide
   auf, T15 führt beide, und die Sollmaske aus T38 schreibt beide. Die sauberere Fassung
   hätte je Paar eine Adresse und käme auf **302 statt 310** (vier Länder mal zwei Paare;
   die Restwelt hat keine Instrumente) — das ist eine Zeile in `spiel.md` und deshalb nicht
   meine. Solange sie dasteht, gilt die Schreib- und Leseregel aus T49 und die
   Gleichheitsprüfung in T30 Prüfung 2. **Es blockiert nichts; ungeregelt wäre es der
   Fehlertyp „zwei Herren über eine Zahl", geregelt kostet es 64 Byte und einen Test.**
3. **~~„Schaden" in Gegenkraft 5 ist eine Größe ohne Rechenvorschrift.~~ Erledigt am
   2026-09-03 durch `spiel.md`, nachgetragen hier am 2026-09-04.** Der Punkt hat gefragt,
   welche der drei Zahlen — Preisverschiebung mal Menge, Wertschöpfungsverlust,
   Bewertungsverlust — gemeint ist. `spiel.md` hat **die erste** gewählt und die beiden
   anderen einzeln widerlegt (der Wertschöpfungsverlust ist gegenüber dem Zoll blind, weil
   Klasse 2 real ist; der Bewertungsverlust buchte Kanal 1 ein zweites Mal in Kanal 3). Die
   Vorschrift steht im Abschnitt *Der Schaden in Gegenkraft 5, als Rechenvorschrift*, die
   Größe als Nummer 22 in T48, die Einheit unverändert in T50. **Der Weg über die Rückgabe
   war der billigere:** Hätte ich die Zahl gefüllt, stünde in Maß 2 meine Wahl, und die
   Zollzeile hätte den Fehler bekommen, den `spiel.md` am 2026-09-03 an sich selbst gefunden
   und beseitigt hat — sie maß bis dahin die Inflation und buchte sie als Lobbyschaden.
   Zurückgegeben und einen Lauf gewartet zu haben, hat hier eine falsche Größe verhindert
   und keine Zeit gekostet.
4. **`fonds.sichtbarkeit` ist eine Adresse, Aktion 5 spricht von einer Position.**
   `spiel.md` lässt den Fonds „eine Position öffentlich offenlegen", der Zustand führt aber
   nur **eine** globale Sichtbarkeit und kein Offenlegungsmerkmal je Steckplatz. Ich lese das
   als Anteil in Zehntausendsteln (T5 Klasse 4), den Aktion 5 um einen Parameterschritt hebt
   oder senkt — das ist die einzige Lesart, die ohne neue Adressen auskommt. Meint der
   Entwurf eine Offenlegung je Steckplatz, kostet das zwanzig Adressen und damit die Zahl
   310; dann ist es keine Zeile mehr, sondern ein ADR.

## 13. Hinweis für den Projektmanager

Der Bausteinschnitt aus T13 ist zugleich der Kollisionsschnitt für Arbeitspakete: Zwei
gleichzeitig offene Pakete dürfen sich nicht im selben Baustein treffen. Die natürliche
Reihenfolge ist `kern` (Zustand, Festkomma, Zufall, Prüfsumme, Schreiber mit T18/T38/T39)
→ `daten` und `schnittstelle` parallel → `konsole` → Tests und `pruefstand` →
`oberflaeche`. Der Jahrgang (`werkzeuge/aufbereitung`) kann von Beginn an parallel laufen,
weil er nur gegen T5, T23 bis T26, T40, **T45/T46** und **T49/T51** gebaut wird und nichts
vom Kern braucht. Er trägt seit dieser Fassung zwei Prüfungen mehr, die das Vorhaben nicht
kippen, aber einen späten Abbruch ersparen: die Skalentabelle über alle 310 Adressen (T49)
und die Untergrenze `aufschlag ≥ aufschlag_min` gegen den historischen Leitzinspfad (T23
Punkt 5).

**Zwei Pakete sind vorzuziehen, weil sie Entwurfsrisiko tragen und nicht Bauaufwand:** der
Jahrgangsbau 1997 (T24 sagt, dass er scheitern kann — 25 Stützstellen ohne Füllung für alle
31 Reihen und alle 40 Handelsströme sind eine Behauptung, keine Tatsache, und der
IFS-Leitzins ist nur durch ein Indiz gestützt) und die Prüfung der vier WDI-Verdachtsreihen
7, 8, 10 und 13 auf die Drittanbieter-Ausnahme. Beide klären sich gegen Daten, nicht gegen
Code.

**Was gegenüber Fassung 2 billiger geworden ist:** Ein engeres Fenster kostet nach T40 eine
Zahl im Manifest und kein zweites Paket. Der Jahrgangsbau muss deshalb nicht mehr *vor* dem
Kern fertig sein, sondern nur vor dem ersten Rückvergleich — er bleibt trotzdem vorn, weil
er das Vorhaben kippen kann und nicht nur verzögern.

## 14. Befundabarbeitung — die vier früheren Prüfungen

**Erledigt und im Git-Verlauf.** Fassung 2 hat die acht Befunde der ersten Prüfung
beantwortet, Fassung 3 die zwölf der zweiten, Fassung 4 die drei der dritten, Fassung 5 die
zwei der vierten (Runde 4). Jede dieser Abarbeitungen ist von der jeweils nächsten Prüfung
unter deren Bedingung 5 ausdrücklich abgenommen worden; die Prüfung der Runde 6 sagt es für
Fassung 5 wörtlich: „Beide Befunde der Vorrunde sind beantwortet, je mit einer der drei
zulässigen Antworten … Beide habe ich gegen die Sache nachgeprüft, nicht gegen die
Behauptung."

Sie hier weiterzuschleppen kostete jeden Leser hundert Zeilen und brächte nichts, was
`git log -p specs/0016-…/technik.md` nicht genauer sagt. Gelöscht ist nichts: Alle vier
Abarbeitungen stehen unverändert in der Versionsgeschichte.

Was aus ihnen **fortwirkt**, steht nicht in einer Abarbeitungsliste, sondern in den
Vorgaben, die daraus entstanden sind — T38 bis T43 tragen die zwölf Antworten der zweiten
Prüfung als Regel statt als Bericht, T44 und T45 die drei der dritten, T46 und T47 die zwei
der vierten, und jede nennt an ihrer Stelle den Befund, der sie erzwungen hat.

## 15. Befundabarbeitung — Prüfung der Runde 6 vom 2026-09-01 und `spiel.md` Fassung 5

Zwei Befunde. Der Prüfer hat sie zwei Gewerken zugewiesen: Befund 1 dem Spielentwerfer,
Befund 2 mir. Beide sind einzeln abgearbeitet, weil die Rolle es verlangt und weil der
erste hier acht Stellen bewegt.

**Befund 1, `positionswert(p)` und `korbwert(l, s)` haben keine Entstehungsregel —
behoben, auf der Seite, der er gehörte, und hier vollständig aufgenommen.** `spiel.md`
Fassung 5 bildet beide Namen, dazu `anleihewert`, `waehrungswert` und den `anleihekurs`, den
der Prüfer im fünften Schritt seines Nachweises eigens benannt hatte. Ich habe die acht
Stellen abgearbeitet, die der Entwurf unter *Was der Architekt neu rechnen muss* auflistet;
hier steht, wo jede gelandet ist:

| aus `spiel.md` Fassung 5 | eingearbeitet in | nachgerechnet oder nachgewiesen |
|---|---|---|
| `korbwert`, `positionswert` und fünf weitere Namen werden gebildet | **T47**, aufgezählt in **T48** (neu) | 17 Funktionen im Kern, 3 im Prüfstand; vier (`bip`, `handelsvolumen`, `anleihekurs`, `korbbestand`) standen bis heute nirgends und stehen jetzt in T48. *Stand dieser Abarbeitung (2026-09-01); seit dem 2026-09-04 sind es 22, siehe Abschnitt 18* |
| Marktkorb mit Menge und Kurs statt „Modellmarktwerten" | **T33** Punkt 1 bis 4 | `marktkorb(m, k)`, Mengen über `lies_alt`, Kurse über `lies_neu` (T39) |
| Skalengrenze je Bewertung einmal, am äussersten Aufruf | **T47**, **T5**, **T50** (neu) | `tsd_in_cent` mit genau zwei Aufruforten; `cent_in_tsd` gestrichen, weil ohne Aufrufer |
| `stufenweite` ist ein Anteil, neuer Schlüssel `aufschlag` | **T5** Klassen 4 und 3, **T27** | elf Parameterschlüssel mit Skalenklasse, davon fünf neu; die 11 Adressen mit Herkunft `Parameter` bleiben 11 |
| `leitzins_start[l]` als Konstante des Jahrgangs | **T23** Punkt 5 | vierzehn Jahrgangskonstanten statt zehn, ohne neue Datenanforderung (erste Stützstelle von Reihe 9) |
| Kapitalstock je Sektor aus den normierten Anteilen | **T23** Punkt 1 | `Datenanker(3 × 2)`, dieselbe Regel wie bei der Wertschöpfung; T45 zählt unverändert 136 Anker |
| „sieben Kanäle" → acht, „achter Kanal" → neunter | **T18**, **T30** Prüfung 6 | zwei Stellen, beide Wortlaut |
| Leitzins-Untergrenze `1 − aufschlag` | **T51** (neu), **T23** Punkt 5, **T30** Prüfung 2 | `aufschlag_min = 1 − min(leitzins_pfad)`; beim EZB-Einlagesatz (−50 bp) sind das **51 bp**, beim Hauptrefinanzierungssatz **1 bp** |

**Und eine Sache habe ich über die Aufnahme hinaus getan, weil sie zu genau diesem Befund
gehört.** Der Prüfer schreibt: „T45s Abzählschritt findet sie nicht, weil sie **keine
Zustandsadresse** ist." Das ist der eigentliche Inhalt des Befundes, und er wäre mit zwei
nachgetragenen Formeln nicht beantwortet gewesen. **T48** zählt deshalb die Menge auf, in
der die Lücke lag — die Funktionen des Zustands —, gibt ihr eine Regel („ein Name, der
weder Adresse noch Parameter noch Jahrgangskonstante noch abgeleitete Größe ist, ist ein
Befund") und einen mechanischen Nachweis (die öffentliche Schnittstelle von `kern::werte`
gegen die Tabelle). Ich habe den Nachweis in diesem Lauf von Hand geführt, in der einzigen
Form, die vor dem Bau möglich ist; die vier Namen, die dabei herausfielen, stehen oben.

**Befund 2, `beteiligung_wert` liefert Tausend USD und wird als US-Cent verbucht — behoben,
und der Befund war richtig.** Die Formel der Fassung 5 bestand aus zwei `mal_geteilt` mit
einheitenlosen Anteilen und war damit skalenerhaltend; zwischen Ein- und Ausgabe liegt aber
der Faktor 100.000 aus T5. Die Behebung steht in **T47**: `tsd_in_cent` um den äussersten
Aufruf, dieselbe Klammer bei `positionswert`, und beides als **T50** festgeschrieben, damit
die Umrechnung einen Namen und einen Ort hat statt einer Gelegenheit.

**Die Wahl zwischen den beiden Wegen habe ich nicht getroffen, sondern übernommen.**
`spiel.md` Fassung 5 entscheidet sie unter *Wo die Skalengrenze liegt*: `korbwert` bleibt
volkswirtschaftlich, weil T33 denselben Korb bewertet und „eine Bewertung, nicht zwei" sonst
nur ein Satz wäre. Mir blieb, welche Funktion es tut und wo sie steht — und die Antwort
auf beides steht in T47 und T50.

**Die Zahlenprobe des Prüfers, mit der Behebung nachgerechnet.** Korb 21.000.000.000 (Tsd
USD), `anteil = 20`, `ausstiegsabschlag = 0`: innen `21.000.000.000 · 20 / 10.000 =
42.000.000` Tausend USD, das sind 42 Mrd USD und damit genau 0,2 % von 21 Bio USD; nach
`tsd_in_cent` **4.200.000.000.000 Cent**. Die Kasse gibt denselben Betrag ab, das
Fondsvermögen bleibt unverändert, Todesart 1 greift nicht. Der Fonds mit 42 Mio USD aus dem
Beispiel kann diese Beteiligung nicht kaufen — das ist jetzt richtigerweise eine
**Zulässigkeitsfrage** (Kasse überzogen, T32) und kein Partieende, und es ist genau die
Kalibrierbedingung, die `spiel.md` unter *Offene Entwurfsfragen* stellt.

**Derselbe Fehlertyp ein zweites Mal, an einer Stelle, die kein Befund war — und das ist der
teure Teil dieses Laufs.** Befund 2 war eine Größe mit zwei Skalen. Ich habe deshalb T5
gegen alle 310 Adressen gelegt, so wie Fassung 5 T45 gegen alle 310 gelegt hat, und **69
Adressen ohne Skalenklasse** gefunden. Darunter die 32 Druck- und Gegendruckfelder, und die
sind wörtlich Befund 2 noch einmal: `druck` entsteht aus dem Lobbybudget des Fonds
(US-Cent), `gegendruck` aus dem Schaden eines Sektors (Tausend USD), und `spiel.md` Schritt 3
verrechnet beide gegeneinander. **Der Unterschied zum ersten Mal ist, dass es nicht wie ein
Rechenfehler ausgesehen hätte, sondern wie eine Gegenlobby, die nie greift** — also wie ein
Balanceproblem, das der Selbstspieler wochenlang wegzukalibrieren versucht hätte. Die
Antwort sind die fünf neuen Klassen in **T5**, die abgezählte Zuordnung in **T49** und die
drei benannten Übergänge in **T50**.

**Die drei Punkte aus „Geprüft und nicht gezählt", weil der Prüfer sie an diesen Lauf
adressiert hat.**

1. **Die Kostenaussage zu `B` war zu klein — der Prüfer hat recht, und sie ist jetzt
   ausgezählt.** Nicht „rund zwanzig Operationen, drei Promille", sondern rund 240, davon 71
   `i128`-Divisionen, also gut drei Prozent eines Weltschritts. Nachgeführt in **T44**, in
   **T47** (mit der Auszählung je Teil) und in **Abschnitt 10**. Es war eine Zeile und kein
   Lauf, wie der Prüfer schrieb; die Auszählung hat trotzdem zwei Vorgaben erzeugt, die
   Rechenzeit sparen und zugleich eine Zusage einlösen — die Abkürzung bei `stufen(p) = 0`
   und die einmalige Berechnung der zwölf `korbwert` je Aufruf.
2. **`markt.wert` mit Herkunft `Manifest` trotz Erwähnung in der Entwurfstabelle.** Die
   Vorrangregel aus T45 löst das, der Prüfer hat es fallen lassen, der Spielentwerfer hat die
   Auflösung übernommen. Keine Änderung.
3. **`einfluss` als 0…100 in `spiel.md`, in Zehntausendsteln im Speicher.** Bleibt, wie es
   ist, und steht seit dieser Fassung zusätzlich in T49 als Klasse 4 — die Konvention ist
   damit nicht mehr nur in einem Absatz erklärt, sondern in einer Tabelle abgezählt.

**Was ich nicht entschieden habe, weil es nicht meine Rolle ist:** die Meldung des Prüfers
an den Projektmanager, dass der Rücklaufzähler mit Runde 6 bei 3 von 3 steht und die Tabelle
im Arbeitspaket seit Runde 3 nicht nachgeführt ist. Ich schreibe weder in das Arbeitspaket
noch urteile ich über `blockiert`. Was ich beitragen kann, ist die Sachlage: Befund 2 dieser
Runde war eine Skalenmischung mit Todesfolge für Klasse 2 von Maß 2, also kein
Genauigkeitsbefund; er ist behoben, und der Fehlertyp ist mit T48, T49 und T50 an drei
Stellen geschlossen statt an einer.

**Was diese Fassung nicht geändert hat:** R bleibt 24, die 310 Adressen bleiben 310, die
Herkunftszerlegung bleibt `136 + 150 + 11 + 2 + 11`, die Sollmaske 175 von 310, die
Ergebnisbänder, die vier Maße und ihre Schwellen, die drei Maße kosten 11.519.040
Weltschritte und der Nachtlauf 11.783.264. Ich habe alle Summen dieses Dokuments in diesem
Lauf erneut nachgerechnet — auch die, die ich nicht angefasst habe, weil eine Fassung, in
der die Kostenrechnung nicht angefasst wird, genau die ist, in der man es unterlässt. Neu
nachgerechnet sind die Skalenzerlegung (`3 + 71 + 36 + 22 + 22 + 5 + 5 + 25 + 32 + 4 + 83 +
2 = 310`, je Land `6 + 5 + 4 + 1 + 7 + 1 + 2 + 8 + 1 + 9 = 44`), die Operationszahl von
`fondsvermoegen` (230) und die Untergrenze `aufschlag_min` (51 bp).

## 16. Befundabarbeitung — Prüfung zu Paket `0011-stack-auf-cpp`, Runde 1 vom 2026-09-03

Drei Befunde, alle in dieser Datei, alle **behoben**. Kein Widerspruch, kein „anders gelöst":
Der Prüfer hat in allen drei Fällen recht, und in allen drei war der Fehler derselbe — beim
Übersetzen von Rust nach C++ ist eine Zusage von der Bauart mitgenommen worden, die an ihr gar
nicht hing. Was der Prüfer ausdrücklich nicht als Befund führt, ist nicht angefasst.

**Befund 1, der Ersatz für `overflow-checks` erreicht die blanke Multiplikation nicht —
behoben.** Massnahme 4 hat einen dritten Punkt bekommen: Jede Multiplikation zweier `i64`
ohne folgende Division läuft über `mal(a, b)` in `festkomma.hpp`, also über `__int128` und den
Wächter aus 4.1. Die Aufzählung der Massnahme ist zugleich vom Ort auf die **Rechenart**
umgestellt — Verengung, Strichrechnung, Multiplikation ohne Division —, denn eine Aufzählung
nach Stellen wird beim nächsten Zusatz wieder unvollständig, und genau das war passiert. Zwei
Dinge, die nicht im Befund standen und dazugehören: Ich habe `__builtin_mul_overflow` nicht
genommen und sage in T7, warum (ein Abbruchpfad statt zweier); und der Nachweis ist eine
Zuordnung statt einer Liste, in diesem Lauf einmal ausgeführt —
`grep -rn ' \* ' kern/src kern/include` gibt heute 52 Zeilen in vier zugelassenen Arten, keine
davon eine `i64`-Größenmultiplikation, weil `kern::werte` noch nicht gebaut ist.

**Befund 2, `cargo vendor` ist gestrichen statt neu gefasst — behoben.** T3 hat den Nachfolger
bekommen: Quelltext jeder Fremdbibliothek unter `fremd/<name>/`, Fassung und Commit-Kennung im
ADR, Einbindung über `add_subdirectory`; `find_package()`, `FetchContent`, `ExternalProject`
und `pkg_check_modules` sind verboten. T1 nennt die Vorgabe am Ort des alten Satzes und
verweist auf T3, damit die übersetzte Zusage dort wieder beide Hälften hat. Den Hinweis des
Prüfers, dass `find_package` **nichts herunterlädt** und deshalb an T23 vorbeigeht, habe ich
in die Vorgabe selbst geschrieben — er ist der Grund, warum ein Verbot des Ladens hier nicht
genügt.

**Befund 3, die Erzwingung von T2 liest nur `kern/CMakeLists.txt` — behoben, an beiden
Stellen.** T13 verbietet `link_libraries()` im ganzen Vorhaben und bindet
`target_link_libraries(<ziel> …)` an die `CMakeLists.txt` des Verzeichnisses, in dem `<ziel>`
angelegt wird — die Zwillingsform des dort schon stehenden Verbots von
`include_directories()`, wie der Prüfer es vorgezeichnet hat. T2 hat einen **dritten**
Mustervergleich bekommen, der über alle übrigen `CMakeLists.txt` läuft und `link_libraries(`
sowie `target_link_libraries(kern` sucht; ohne ihn wäre das Verbot eine Verabredung. Beides
gehört zusammen: T13 sagt, was nicht sein darf, T2 sagt, wie man es sieht.

**Gegen den heutigen Baum geprüft, nicht nur behauptet.** Die drei neuen Verbote sind keine
nachträgliche Verurteilung des Gebauten:
`grep -rnE 'link_libraries|include_directories|find_package|FetchContent' --include=CMakeLists.txt .`
gibt über das ganze Vorhaben **sechs** Zeilen — vier `target_include_directories` und zwei
`target_link_libraries(${name} PRIVATE …)`
für Probenziele, jede in der Datei, in der ihr Ziel entsteht. Kein Treffer auf
`link_libraries(`, `include_directories(` oder `find_package(`. Die Pakete 0004 und 0031 haben
also schon so gebaut; diese Fassung schreibt hin, was bisher Gewohnheit war.

**Zwei Meldungen an den Projektmanager, weil sie ausserhalb meines Verzeichnisses liegen und
ich dort nichts ändere.** Erstens: `festkomma.hpp` hat heute kein `mal(a, b)` — es ist die
einzige Zeile Code, die diese Nachbesserung nach sich zieht, und sie gehört in ein eigenes
kleines Paket samt Probe für den Abbruchfall. Zweitens: Die Abnahme von Paket 0004,
Bedingung 3, schreibt die zwei Mustervergleiche über `kern/CMakeLists.txt` wörtlich aus und
kennt den dritten deshalb nicht. Der Prüfer hat das gesehen und ausdrücklich gesagt, die
Lücke gehöre in die Vorgabe geschlossen; hier ist sie geschlossen. Ob 0004 nachgeführt wird,
entscheidet nicht der Architekt.

**Was diese Nachbesserung nicht geändert hat:** kein Wort an der Stacktabelle, an T6, T6b,
T2b, T9, den Massnahmen 1 bis 3, den 310 Adressen, den Formeln, den Maßen oder den
Kostenrechnungen. Der Umfang ist ein Punkt in T7, ein Absatz in T3 mit einem Halbsatz in T1
und je ein Absatz in T2 und T13 — das ist der Rücklauf und keine achte Fassung.

## 17. Paket `0026-klasse-2-preisbasis` — Umfang, und was ausdrücklich liegen bleibt

**Dieses Paket ist geliefert.** Zwei Läufe am 2026-09-04, Commits `77a84e8` und `d26eb3e`.
Ein dritter Lauf am selben Tag hat es erneut zugewiesen bekommen, weil `status: offen` im
Paket steht; er hat nichts neu entschieden, sondern nachgerechnet — unten unter „Dritter
Lauf". **Wer 0026 erneut eingeplant findet, liest zuerst diesen Abschnitt.**

**Kein Rücklauf.** Das Paket führt `Rückläufe: 0`, und unter
`ventures/0016-…/befunde/` liegt keine Prüfung zu diesem Gewerk mit `urteil: zurueck`. Es gibt
also keinen Befund abzuarbeiten; dieser Abschnitt hält stattdessen den Umfang fest, weil
Bedingung 5 der Abnahme ihn begrenzt.

**Zwei Läufe, ein Paket.** Der erste Lauf (2026-09-04 05:24, Commit `77a84e8`) hat die
Entscheidung geliefert; der zweite (2026-09-04, derselbe Tag) hat sie nachgerechnet und drei
Zahlen berichtigt. Der Grund für den zweiten Lauf liegt nicht am Gewerk: Das Paket stand nach
der Lieferung weiter auf `status: offen` und wurde deshalb erneut eingeplant
(`rueckstand.md`, „Was der Geschäftsführer entscheiden lassen muss", Punkt 2 — der fehlende
Satz „Setze `status: gebaut`" in der Rollendatei `architekt`). **Was der zweite Lauf inhaltlich
geändert hat, steht unten unter „Berichtigt"; die Entscheidung selbst ist unverändert.**

**Angefasst sind sechs Stellen und sonst keine.** Die Liste ist gegen die Hunks von
`git show 77a84e8 -- specs/0016-…/technik.md` abgezählt und nicht aus dem Gedächtnis
geschrieben — eine Umfangsangabe, die den eigenen Diff nicht deckt, verfehlt genau die
Bedingung, die sie belegen soll:

1. die Klasse-2-Zeile in **T5** samt zwei Absätzen dahinter (Basisjahr 2015, Verweis auf T53),
2. die neue Vorgabe **T53** hinter T50,
3. der Absatz in **T8**, der die Aufzählung der neu basierten Größen begründet,
4. dieser Abschnitt,
5. der **Vorspann** vor Abschnitt 1: „T1 bis T52" wird zu „T1 bis T53"; der Satz über die
   Buchstabennummern nannte als Beispiel für eine noch freie Nummer T53 und nennt jetzt T60,
   weil T53 vergeben ist; ein Absatz ordnet T53 ein. Diese Stelle ist **erzwungen**, nicht
   gewählt: Ein Vorspann, der die Vorgaben bei T52 enden lässt, widerspricht der Vorgabe, die
   vier Abschnitte weiter steht,
6. das **Frontmatter**: die Zeile `fassung`, weil sie sonst den Stand der Datei falsch angibt,
   und der neue Schlüssel `preisbasis`, weil die Kopfzeilen die tragenden Festlegungen führen
   und die Preisbasis seit T53 eine davon ist.

**Berichtigt im zweiten Lauf, ohne die Entscheidung zu berühren:** Der erste Lauf zählte die
Stellen 5 und 6 nicht auf und schrieb „vier Stellen und sonst keine" über eine Liste von sechs.
Dazu zwei Zahlen in T53, die abgeschnitten statt gerundet waren und damit gegen die einzige
Rundungsregel dieses Dokuments (T6) verstiessen: der Fehler am rechten Rand ist 3.577,80 und
steht jetzt als **3.578** statt als 3.577, und `r(2021) = 11.549/7.417 = 1,55710` steht jetzt
als **1,5571** statt als 1,5570. Der Kopfwert **2.203** (exakt 2.202,98) war richtig gerundet
und ist unverändert; das Argument hängt an keiner der beiden berichtigten Zahlen, die Schwelle
liegt bei 2.000 und der Kopfwert darüber. Alle Zahlen aus T53 sind im zweiten Lauf neu gerechnet worden — die 25 Stützstellen des
Index, der MAPE, der Startfaktor 10.000/7.417 = 1,34825, die beiden `durchgriff`-Fälle
(7.288 → 7.837 und 5.464 → 6.189), die Summe 15 + 15 + 40 + 1 = 71 und der `i64`-Kopfraum
(2,8 · 10^17 gegen 9,2 · 10^18) — und reproduzieren bis auf die zwei genannten Stellen.

**Dritter Lauf, 2026-09-04 — nachgerechnet statt neu entschieden.** Die 25 Stützstellen der
Indextabelle in T53 sind ein zweites Mal durch `10.000 · |7.417 − Index(t)| / Index(t)`
gerechnet worden, ohne die Zwischenwerte des zweiten Laufs anzusehen: Summe **55.074,54**
Zehntausendstel, Mittel **2.202,98** → 2.203, rechter Rand 2021 **3.577,80** → 3.578,
`r(2021) = 11.549/7.417 = 1,557098`, Startfaktor `10.000/7.417 = 1,348254`. Die beiden
`durchgriff`-Fälle reproduzieren über `H/N` als **7.836,99** → 7.837 und **6.189,15** →
6.189, die Summe als `15 + 15 + 40 + 1 = 71`, der `i64`-Kopfraum als 2,8 · 10^17 gegen
9,2 · 10^18. **Alle Zahlen aus T53 sind damit in zwei unabhängigen Läufen gerechnet**, und
keine hat sich geändert.

**Was der dritte Lauf trotzdem gefunden hat — eine Stelle, und sie sitzt am Übergang zu
`reihen.toml`.** T53 nannte für `N` nur Reihe 1; nach T23 Punkt 1 ist die Wertschöpfung
Reihe 1 **mal** dem Sektoranteil aus Reihe 2. `daten/reihen.toml` führt bei Reihe 16
umgekehrt `abgeleitet aus Reihe 14 (H) und Reihe 2 (N)` und nennt Reihe 1 nicht. Zwei
Dokumente gaben also zwei verschiedene und beide unvollständige Antworten auf dieselbe Frage,
und die Frage ist genau die, an der die Preisbasis hängt. T53 nennt jetzt beide Reihen und
sagt, welche von ihnen die Preisbasis trägt; die Gegenseite gehört in den Übertrag aus
Meldung 2. Das Argument des Absatzes ändert sich nicht — Reihe 2 trägt keine Preisbasis.

**Stand der drei Meldungen am 2026-09-04, nachgesehen statt vermutet.** Meldung 1 ist
angekommen: `0002` steht wieder auf `status: offen` und führt `haengt_an: [0008, 0026]`,
0008 ist `fertig`. Meldung 2 ist **halb** angekommen: das nächste Architektenpaket an der
Reihenliste ist als `0068` angelegt, **die Reihenliste-Zeile 20 und der Übertrag nach
`daten/reihen.toml` aber nicht** — eine Suche über alle Paketdateien nach „Reihe 20",
„Ausfuhrpreisindex" und „Deflator" findet ausser 0025 und 0026 selbst nichts. Solange das so
bleibt, führt `reihen.toml` bei Reihe 14 weiter den Widerspruch, den T53 aufgelöst hat, und
bei Reihe 16 die unvollständige Herkunft von oben. Meldung 3 (der lesbare PWT-Auszug) ist
unverändert offen.

Nicht angefasst: T42, T37, T47, T48, T50, T23, die Reihenliste, die 310 Adressen, die vier
Maße, die Kostenrechnungen und die Stacktabelle. Der dritte Lauf hat davon nichts berührt;
er hat innerhalb der oben aufgezählten sechs Stellen gearbeitet (T53, dieser Abschnitt, die
Zeile `fassung`) und keine siebte aufgemacht.

**Was hier hingehörte und trotzdem nicht hier steht — die Reihenliste.** T53 nennt eine neue
Reihe des Jahrgangs, und die Reihenliste in Abschnitt 7 führt sie nicht. Das ist bewusst:
Bedingung 5 nimmt die offenen Fragen aus `rueckstand.md` Punkt 6 und 7 ausdrücklich aus diesem
Paket heraus, und eine davon — das `frei` in der Spalte „Rolle" — sitzt in genau dieser
Tabelle. Zwei Pakete an einer Tabelle sind der Kollisionsfall, den der Zuschnitt vermeiden
soll. **Die Zeile steht deshalb hier, fertig für das nächste Architektenpaket:**

| Nr | Größe | Dimension | Modelleinheit | Quelle | Rolle | Verdacht |
|---:|---|---|---|---|---|---|
| 20 | Ausfuhrpreisindex der Welt, aus `NE.EXP.GNFS.CD` und `NE.EXP.GNFS.KD` | 1 | Zehntausendstel, 2015 = 10.000 | WDI | Umrechnung des Jahrgangs nach T53, **kein Soll** | nein |

Sie ändert die Sätze unter der Tabelle **nicht**: Die 31 Sollreihen bleiben die Zeilen 1, 2, 8,
9, 10 und 11, der Handelsblock bleibt ein eigener Block, und die vier Größen ohne Datenanker
bleiben die Zeilen 17, 18, 19 und die Finanzmarktregulierung. Reihe 20 ist eine
Umrechnungsgröße, keine geprüfte.

**Drei Meldungen, weil sie ausserhalb meines Verzeichnisses liegen.**

1. **An den Projektmanager, zu Paket 0002 (`kern::werte`, Fondsbewertung):** Sein
   Entblockungssatz verlangte *„eine Entscheidung des Architekten zur Klasse-2-Frage,
   schriftlich in `technik.md` oder in einem ADR"*. Sie steht in T53. **T47, T48 und T50 sind
   unberührt** — Umfang und Abnahme von 0002 brauchen keine Änderung, es kann unverändert
   zurück auf `offen`. Über 0002 hängt 0010 (Zustandsausgabe) mit daran.
2. **An den Projektmanager, zwei neue Pakete:** die Reihenliste-Zeile 20 oben (Architekt,
   zusammen mit `rueckstand.md` Punkt 6 und 7, weil dieselbe Tabelle) und der Übertrag nach
   `daten/reihen.toml` (Datenbauer): Reihe 14 bekommt den Deflatorschritt und verliert den
   Eintrag im Feld `offen`, der den Widerspruch führt; Reihe 16 bekommt die Antwort, dass
   `H` und `N` nach T53 dieselbe Preisbasis tragen; Reihe 20 kommt neu hinzu. Reihe 3 bleibt
   `art = "ungemessen"`.
3. **An den Datenbauer und über ihn an den Betreiber:** Einheit und Basisjahr des
   PWT-Kapitalstocks sind weiter ungemessen, und die Sperre ist die Werkzeugkette — vier
   PDF-Abrufe aus drei Verzeichnissen kamen unlesbar an. Es kostet **einen** lesbaren Auszug
   aus Dataverse 554025 oder 554105. Die Folge ist in T53 nach Größe geordnet: Die Einheit ist
   der schwere Teil (Faktor 1 gegen 1.000), das Basisjahr der leichte, und beide treffen keine
   Sollreihe.

**Was dieses Paket ausdrücklich nicht entschieden hat.** Die Höhe des Schadens in Gegenkraft 5
gehört `spiel.md` und dem Paket 0021. Ob Reihe 1 auf PWT wechselt, ist in `daten/reihen.toml`
als `quellenwahl = "offen"` geführt und bleibt es; wechselt sie, wandert mit ihr das gemessene
Basisjahr, und T53 ist die Stelle, an der das nachzuziehen wäre. Und die Restgrösse des
gewählten Wegs — der Abstand zwischen dem Weltausfuhrindex und den wahren bilateralen
Deflatoren der 40 Ströme — ist ungemessen und steht in T53 als solche.

## 18. Paket `0043-t48-groessen-gegenkraft-5` — Umfang und die Meldung an den Projektmanager

Vier Bedingungen, vier Stellen. Geändert sind **T48** (fünf Größen, die sektorweise Fassung
von Nummer 11, die Restetabelle), **T50** (der offengelassene Satz ist geschlossen),
**Abschnitt 10** (die Kostenzeile mit ihrer Lesetabelle) und **Abschnitt 12 Punkt 3** (die
Lücke ist keine mehr). Dazu die Zeile `abgeleitet:` im Frontmatter, die 17 nannte.

**Der Auftrag sprach von fünf Namen, gemeint waren sie am 2026-09-03 — es sind sechs, und
einer davon ist älter als das Paket.** Der Auftragstext nennt `hub`, `preishub`, `menge`,
`verschiebung` und `schaden`. Dazwischen ist Paket **0039** gelaufen: `preishub(l, s)` gibt
es nicht mehr, an seine Stelle sind `keilhub(l, s)` und `preishub_zoll(l, s)` getreten. Aus
fünf Namen wurden damit sechs, von denen zwei keine Größe wurden (`menge`, `verschiebung`,
Begründung in T48) und vier eine. Der fünfte Neuzugang, `weltpreis_mit_zoll`, stammt aus
keinem der beiden Pakete, sondern aus T28 dieses Dokuments: Die Preisformel der Markträumung
rechnet seit jeher mit ihm, gebildet wurde er nie. Gefunden hat ihn nicht das Lesen der
Auftragstabelle, sondern die Erhebung über `spiel.md`, die T48 jetzt mit abdruckt — der
Auftrag hätte ihn nicht gebracht.

**Die Abnahmebedingungen, einzeln:**

1. **Die Namensliste lässt keinen Rest.** Die Erhebung, ihre Zuordnung und die zwölf
   erlaubten Reste stehen in T48. Zwei Namen darin sind der unangenehme Fall und deshalb
   ausdrücklich aufgeführt: `wmz` und `preishub` stehen in `spiel.md` noch, aber allein im
   Gegenbeispiel, mit dem der Entwurf die verworfene Vorfassung vorrechnet. Wer sie für
   Vorschriften hält, trägt zwei tote Größen nach; wer sie stillschweigend übergeht,
   hinterlässt dem nächsten Prüfer denselben Zweifel. Sie stehen deshalb in der Restetabelle.
   **Die Erhebung hat nebenbei eine ältere Lücke gefunden**, die keinem der drei Pakete
   gehört: `stufen(p)` steht seit Fassung 5 in den Formeln der Nummern 14 und 15, ohne dass
   T48 je gesagt hätte, was es ist. Es ist eine Adresse in Funktionsschreibweise und steht
   jetzt als solche in der Restetabelle — ein Beleg dafür, dass die maschinelle Erhebung
   findet, was das Lesen einer Auftragstabelle nicht findet.
2. **`handelsvolumen`** steht als Nummer 11 in der sektorweisen Fassung, die einstellige
   daneben als deren Summe über s ∈ {1, 2}. Nummer 4 (`waehrungswert`) liest weiter die
   einstellige und ändert sich nicht.
3. **T50 und Abschnitt 12 Punkt 3** verweisen auf den Abschnitt in `spiel.md`. Der alte Satz
   steht an beiden Stellen im Wortlaut daneben, damit die Prüfungen, die ihn zitiert haben,
   zitierbar bleiben.
4. **Die Kostenzeile** nennt 106 Lesezugriffe, 16 Schreibzugriffe und 16 Aufrufe, mit der
   Lesetabelle darunter und der Summe ausgeschrieben. Ich habe sie in diesem Lauf
   nachgezählt statt übernommen; die eine Zeile, die nicht selbsterklärend ist, sind die 40
   des Handelsblocks, und warum es nicht 64 sind, steht dort.

**An den Projektmanager — welche der neuen Größen eine Schnittstelle in `kern::werte`
braucht.** Das ist die Angabe, aus der das Folgepaket zugeschnitten wird; es ist nicht meins.

| Größe | Schnittstelle in `kern::werte`? |
|---|---|
| `hub(l, i)` (Nr. 18) | **ja**, öffentlich. Argumente Land und Instrument, Ergebnis `i64` |
| `keilhub(l, s)` (Nr. 19) | **ja**, öffentlich |
| `preishub_zoll(l, s)` (Nr. 20) | **ja**, öffentlich |
| `weltpreis_mit_zoll(g, s)` (Nr. 21) | **ja**, öffentlich — und ihr Leser ist die Markträumung (T28), nicht Gegenkraft 5 |
| `schaden(l, i)` (Nr. 22) | **ja**, öffentlich, mit der Fallunterscheidung über die vier Instrumente innen |
| `handelsvolumen(l, s)` (Nr. 11) | **Formänderung an einer bestehenden.** Heute steht in `werte.hpp` `handelsvolumen(z, land)`; gebraucht werden beide Stelligkeiten, die einstellige gebildet aus der zweistelligen |
| `menge(l, i)`, `verschiebung(l, i)` | **nein**, und das ist eine Vorgabe und kein Vergessen. Begründung in T48 |
| `regulierung_last` | **nein** — Parameterschlüssel nach T27. Er gehört in `parameter.toml` (Datenbauer) und in die Struktur `Konstanten` in `werte.hpp`, wo `gegenlobby_satz` und `lobbykosten` schon stehen |

**Drei Stellen, die dadurch nachziehen und die nicht mir gehören.** Sie sind alle drei
mechanisch und keine ist eine Frage:

1. **`kern/include/kern/werte.hpp` sagt an drei Stellen „siebzehn"** — in der Kopfzeile
   (`//! kern::werte -- die siebzehn abgeleiteten Groessen aus T48`), im Absatz über den
   mechanischen Nachweis („Unten stehen siebzehn") und in der Überschrift des zweiten Blocks.
   Nach diesem Paket sind es zweiundzwanzig. Das ist Kernbauer-Arbeit, und es ist genau der
   Nachweis, den T48 vorschreibt: Wer den Kopf gegen die Tabelle legt, findet die fünf
   fehlenden Deklarationen. **Solange sie fehlen, ist der Nachweis nicht erfüllt** — der Kopf
   ist damit heute unvollständig und nicht falsch.
2. **Die Abnahme von Paket 0002** nennt die Zahl siebzehn wörtlich. Sie war zum Zeitpunkt
   ihrer Erfüllung richtig: 0002 stand am 2026-09-04 auf `fertig`, bevor dieses Paket lief —
   die Reihenfolge, die der Projektmanager dafür angeordnet hat, hat gehalten. Wer sie später
   liest, braucht diesen Absatz, sonst sieht die erfüllte Abnahme wie eine verletzte aus.
3. **`regulierung_last` fehlt in `parameter.toml`.** Folgepaket des Datenbauers, im Auftrag
   dieses Pakets schon benannt und hier nicht angefasst.

**Worauf ich unsicher bin, und es steht hier statt nur im Logbuch.** Nummer 21 ist die
einzige Stelle, an der ich etwas entschieden statt gemeldet habe: `zollstand(RW) = 0`. Der
Weg dorthin ist belegt — zehn `durchgriff`-Werte für fünf Gebiete, keine Instrumente für die
Restwelt —, aber der Definitionsbereich von `weltpreis_mit_zoll` steht nirgends
ausgeschrieben, weder in T28 noch in `spiel.md`; ich habe ihn aus dem Wort „je Gebiet" und
aus der Zahl zehn gelesen. Läuft die Markträumung in Wahrheit nur über die vier spielbaren
Länder, ist meine Zeile überflüssig und nicht falsch. Das ist die Stelle, an der ich einem
Prüfer widerspruchslos folgen würde.

## 19. Die Länderzahl als Parameter — Paket `0116`

**Was hier entschieden wird und was nicht.** Über die Zahl der Länder entscheidet dieser
Abschnitt **nichts**. `L = 4` bleibt, und die Begründung dafür steht in `spiel.md`; sie steht
nicht zur Disposition. Entschieden wird allein, ob ein weiteres Land später ein **Vorgang mit
bekannten Schritten** ist oder ein Umbau mit offenem Ende. Dazu gehören drei Dinge: die Formel
hinter jeder heute ausgeschriebenen Zahl (T54, T55), die Frage, wo die Identität eines Landes
wohnt (T56), und die Liste dessen, was **nicht** mitwächst (T57).

**Der Kern ist an dieser Stelle weiter als dieses Dokument.** `LAENDER`, `GEBIETE`,
`SEKTOREN`, `INSTRUMENTE` und `SEKTOREN_HANDELBAR` sind je eine `constexpr` in
`kern/include/kern/zustand.hpp`; die Blockanfänge werden daraus **gerechnet**
(`BASIS_RESTWELT = LAENDER * LAND_FELDER`) und von einer Kette aus `static_assert` gegen die
Gruppentabelle in T15 gehalten. Auch `daten/reihen.toml` führt je Reihe eine `dimension` und
schreibt sie als `"4 + RW"`, also als Größe und nicht als Konstante. Was fehlt, ist die
Gegenrichtung: In `specs/` stehen die abgeleiteten Zahlen als **Literale**, und nirgends steht
an einer Stelle, aus welcher Formel welche entsteht. Wer ein Land hinzufügt, muss sie heute
einzeln nachrechnen und in Prosa nachziehen. Genau das behebt T55.

### T54 — Drei Formgrössen, und alles andere folgt daraus

| Zeichen | Bedeutung | heute | Konstante im Kern |
|---|---|---:|---|
| `L` | spielbare Länder | 4 | `LAENDER` |
| `S` | Sektoren | 3 | `SEKTOREN` |
| `I` | Politikinstrumente | 4 | `INSTRUMENTE` |

Zwei weitere Größen sind **abgeleitet und keine eigene Wahl**: Die Zahl der Gebiete ist
`L + 1` — die Restwelt ist immer genau eine, wie viele Länder auch modelliert werden —, und
die Zahl der handelbaren Sektoren steht in den Formeln unten als `S − 1`.

**Zu `S − 1` gehört eine Warnung, und sie ist keine Förmlichkeit.** Der Kern führt
`SEKTOREN_HANDELBAR` als **eigene** Konstante, nicht als Rechenausdruck. Dass sie bei `S = 3`
denselben Wert hat wie `S − 1`, ist eine Tatsache über die heutige Sektorliste und keine
Regel: Wer einen vierten Sektor einführt, entscheidet dessen Handelbarkeit selbst und setzt
dann die Konstante ein, wo hier `S − 1` steht. **Für die Länderzahl, um die es in diesem
Abschnitt geht, ist der Unterschied ohne Folge** — die Zahl der handelbaren Sektoren hängt
nicht von `L` ab.

### T55 — Die Ableitungskette

Jede Zeile nennt ihre Fundstelle in diesem Dokument, damit die Formel gegen die Stelle gelegt
werden kann, die die Zahl heute ausschreibt.

| Größe | Formel in `L`, `S`, `I` | `L=4` | `L=9` | Fundstelle |
|---|---|---:|---:|---|
| Felder je spielbarem Land | `4S + 4I + 16` | 44 | 44 | T15 |
| Felder der Restwelt | `4S + 10` | 22 | 22 | T15 |
| Gebietsblock zusammen | `L(4S+4I+16) + 4S + 10` | 198 | 418 | T15, T17b |
| Handelsströme | `(L+1)·L·(S−1)` | **40** | 180 | T15, „Handel" |
| Weltpreise | `S − 1` | 2 | 2 | T15 |
| Nachahmerzähler | `L·S` | 12 | 27 | T15 |
| Positionssteckplätze | `L·(S+2)` | **20** | 45 | T16 |
| Beteiligungen | `2·L·S` | 24 | 54 | T15, Aktion 2 |
| von `L` unberührter Rest | `5S + 23` | 38 | 38 | T57 |
| **Zustand gesamt** | `L(4S+4I+16) + (L+1)L(S−1) + L(S+2) + 3LS + 5S + 23` | **310** | **740** | T15 |
| Sollmaske `weltlauf`, je Land | `4S + I + 11` | 27 | 27 | T38 |
| **Sollmaske `weltlauf`** | `L(4S+I+11) + (4S+10) + (L+1)L(S−1) + (S−1) + 3` | **175** | 450 | T38 |
| **ausserhalb der Sollmaske** | `L(3I+5) + L(S+2) + 3LS + 11` | **135** | 290 | T38 |
| Sollreihen | `L·(S+4) − 1` | **27** | 62 | Reihenliste zu T23, `reihen.toml` |

**Nachrechnung im Fliesstext, jede Zahl einmal von Hand eingesetzt.** Je Land
`4·3 + 4·4 + 16 = 44`, Restwelt `4·3 + 10 = 22`, zusammen `4·44 + 22 = 198`. Handel
`5·4·2 = 40`, Weltpreise `2`, Nachahmer `4·3 = 12`, Marktkorb `2` — die Welt also `56`.
Steckplätze `4·5 = 20`, Beteiligungen `2·4·3 = 24`, Fondsaggregat und Überrendite `5 + 3 = 8`
— der Fonds also `52`. Partie `4`. Summe `198 + 56 + 52 + 4 = 310`, dieselbe Zerlegung wie in
T15. Sollmaske `4·27 + 22 + 40 + 2 + 3 = 175`, ausserhalb `4·17 + 20 + 24 + 12 + 11 = 135`,
und beide zusammen wieder die Adressenzahl aus T15. Sollreihen `4·7 − 1 = 27`.

**Warum die Spalte `L = 9` danebensteht, obwohl dieser Abschnitt keine Länderzahl ändert.**
Sie ist keine Festlegung, sondern die einzige Probe, die etwas beweist. Heute gilt `L = I = 4`
— und deshalb ist jede Verwechslung von `L` und `I` bei den heutigen Werten **unsichtbar**:
`4S + 4I + 16` und `4S + 4L + 16` liefern beide 44. Erst bei `L ≠ I` fallen die beiden Formeln
auseinander. Die Werte der Spalte sind gegen eine **unabhängig** entstandene Rechnung gelegt,
die der Betreiber am 2026-09-05 in Paket `0118-fuenf-weitere-laender-auswaehlen` aufgeschrieben
hat: Länderblock 396, Handel 180, Nachahmer 27, Steckplätze 45, Beteiligungen 54, fester Rest
38, Zustand 740, Sollreihen 62. Alle acht Zahlen stimmen mit den Formeln überein. Das ist die
Gegenrechnung, die eine einmal gerechnete Zahl nicht hat.

**Zwei Zahlenpaare sehen bei `L = 4` gleich aus und sind es nicht.** Beide sind genau die
Sorte Falle, gegen die diese Tabelle geschrieben ist:

- **40 gegen 40.** Die 40 Handelsströme wachsen mit `(L+1)·L·(S−1)`; die **40
  Halbierungsschritte** der Markträumung aus T28 sind eine Genauigkeitsvorgabe und wachsen mit
  gar nichts. Wer beide für dieselbe Größe hält, macht aus einer Länderänderung eine Änderung
  am Lösungsverfahren.
- **27 gegen 27.** Die 27 Sollreihen wachsen mit `L(S+4) − 1`, die 27 Maskenadressen je Land
  aus T38 mit `4S + I + 11` — also gar nicht mit `L`. Bei `L = 9` stehen 62 gegen unverändert
  27.

**Woher die 27 Sollreihen kommen, und warum die Reihenliste 31 nennt.** Gezählt wird an
`daten/reihen.toml`, Stand 2026-09-05: `sollreihen_gesamt = 27`, aufgeteilt auf Reihe 1 (BIP,
`L`), Reihe 2 (Sektoranteile, `L·S`), Reihe 8 (Verbraucherpreise, `L`), Reihe 10 (Wechselkurs,
`L − 1`, weil der US-Dollar der Numéraire ist) und Reihe 11 (Staatsschuldenquote, `L`). Das
ergibt `L(S+4) − 1`. Der Fliesstext unter der Reihenliste in Abschnitt 7 nennt weiterhin 31 und
zählt Reihe 9 (Leitzins) mit vier Sollreihen mit; die Reihe hat ihre Sollrolle in Paket `0054`
verloren (`sollreihen = 0`, leere `t37_klasse`), und die Prosa ist nicht mitgezogen worden.
**Das ist kein Widerspruch zu dieser Formel, sondern die offene Arbeit von Paket
`0068-technikmd-reihe-9-ohne-sollrolle`**, das hinter diesem Paket in derselben Datei steht.
Ich fasse die Stelle nicht an; sie gehört ihm.

### T56 — Die Identität eines Landes bleibt eine namentliche Aufzählung

**Gewählt ist die erste der beiden Möglichkeiten: `Gebiet` und `Steckplatz` bleiben
namentliche Aufzählungen.** Sie werden **nicht** durch einen blanken Index plus Kürzeltabelle
ersetzt. Die eine Stelle, an der ein Land eingetragen wird, ist
**`kern/include/kern/zustand.hpp`**.

Vier Gründe, nachgemessen am 2026-09-05 und nicht vermutet:

1. **Die Aufzählung *ist* schon der Index.** `enum class Gebiet : std::uint8_t` trägt die Werte
   0 bis 4, die Adressarithmetik rechnet ausschliesslich mit `LAENDER` und `GEBIETE`, und die
   Kürzeltabelle existiert bereits: `GEBIET_KUERZEL` in `kern/src/zustand.cpp`. Es stehen also
   nicht zwei Verfahren zur Wahl, sondern ein Index **mit** Namensschicht gegen denselben Index
   **ohne** sie. Der Umbau brächte keine Rechnung in Ordnung, die heute falsch wäre.
2. **Ein falscher Index ist ein gültiger Wert, ein falscher Name nicht.** `Steckplatz{37}`
   übersetzt; `Steckplatz::Anleihe_BX` nicht. Dieses Vorhaben fängt seine Fehler mechanisch ab
   — `static_assert` auf die Blockgrenzen, Sollmaske je Runde, Bitfeld gegen den zweiten
   Schreibzugriff. Eine Prüfung zur Übersetzungszeit gegen eine zur Laufzeit zu tauschen, läuft
   dieser Bauart entgegen.
3. **Die Namen tragen die Proben.** Gezählt in `kern/`: `Gebiet::<Kürzel>` steht auf 42 Zeilen
   Quelltext (`werte.cpp` 25, `schritt.cpp` 6, `schreiber.cpp` 5, `zustand.cpp` 5,
   `zustandsausgabe.hpp` 1) und auf **141** Zeilen in den Proben (`werte_probe.cpp` 109,
   `schreiber_probe.cpp` 22, `zustand_probe.cpp` 9, `zustandsausgabe_probe.cpp` 1). Der
   Schwerpunkt liegt bei den Proben, und dort ist der Name die Aussage: `Gebiet::DE` sagt, was
   geprüft wird, `Gebiet{2}` sagt es nicht. Ein Umbau ersetzte 183 lesbare Zeilen durch 183
   nachschlagepflichtige, ohne eine Zahl zu bewegen.
4. **T17 macht die Adresse zum Bestandteil der Schnittstellenversion.** `fonds.position.CN.1`
   und `handel.DE.CN.1` tragen das Kürzel im Text. Die Identität eines Landes ist damit ohnehin
   schon namentlich; eine Aufzählung, deren Namen den Adressen folgen, ist die Fassung
   derselben Sache, die der Übersetzer prüfen kann.

**Der Preis dieser Wahl, ausgeschrieben, weil er real ist.** Bei `L = 5` bekommt
`enum class Steckplatz` fünf weitere Werte (`Sektor_XX_1` bis `_3`, `Waehrung_XX`,
`Anleihe_XX`), und weil die Plätze nach Art gruppiert sind, verschieben sich die
Ordnungszahlen der Währungs- und Anleiheplätze. Das ist Handarbeit, und Handarbeit driftet.

**Dagegen steht die Regel, die diese Wahl überhaupt erst tragfähig macht: Die Formel bewacht
die Aufzählung.** In `zustand.hpp` gehört je ein `static_assert` gegen T55 neben die betroffene
Konstante — `STECKPLAETZE == LAENDER * (SEKTOREN + 2)`,
`LAND_FELDER == 4 * SEKTOREN + 4 * INSTRUMENTE + 16`, `RESTWELT_FELDER == 4 * SEKTOREN + 10`,
und `STECKPLATZ_WAEHRUNG_ERSTER` sowie `STECKPLATZ_ANLEIHE_ERSTER` gegen `LAENDER * SEKTOREN`
beziehungsweise `LAENDER * (SEKTOREN + 1)`. Ein vergessener Eintrag bricht dann die
Übersetzung, statt eine Adresse still zu verschieben. **Ohne diese Zusicherungen wäre die Wahl
falsch** — sie sind der Grund, warum eine handgeführte Liste hier zulässig bleibt.

**Damit „die eine Stelle" wörtlich stimmt, muss eine Zeile umziehen.** `GEBIET_KUERZEL` steht
heute in `kern/src/zustand.cpp`, die Aufzählung in `kern/include/kern/zustand.hpp` — ein Land
hinzuzufügen berührt also zwei Dateien. Die Tabelle gehört als `constexpr std::array` neben
die Aufzählung in den Kopf, mit `static_assert(GEBIET_KUERZEL.size() == GEBIETE)`. Danach ist
der vollständige Vorgang für ein weiteres Land im Kern: ein Wert in `Gebiet` vor `RW`, `RW` um
eins höher, `LAENDER` um eins höher, ein Kürzel in `GEBIET_KUERZEL`, `S + 2` Werte in
`Steckplatz` — alles in einer Datei, alles von `static_assert` bewacht. Die Datenarbeit, die
daneben anfällt, steht in `0141-pruefliste-fuenftes-land` und ist der grössere Posten.

Beides — die Zusicherungen und der Umzug — ist **Entwurf, nicht Ausführung**, und braucht je
ein Kernbauer-Paket. Ich schreibe keinen Code.

### T57 — Was bei `L = 5` gleich bleibt

Von den Zustandsadressen sind **38 von `L` unberührt** (`5S + 23`, bei `S = 3` also 38) — und
das ist dieselbe Zahl, die Paket `0118` unabhängig als „fest" ausweist:

| bleibt gleich | Zahl | warum |
|---|---:|---|
| Restwelt-Block | `4S + 10` = 22 | Die Restwelt ist definitionsgemäss **eine**: die Welt abzüglich der Modellländer. Ein weiteres Land verkleinert ihren Inhalt, nicht ihre Adressenzahl |
| Fondsaggregat | 5 | Kasse, Hebelstand, Sichtbarkeit, Anlegerbestand, Marktanteil sind Eigenschaften des Fonds, nicht der Landkarte |
| Überrendite | 3 | drei Runden Gedächtnis, an die Todesbedingung gebunden |
| Marktkorb | 2 | ein Korb, ein Wert, eine Rendite — unabhängig davon, worüber er gebildet wird |
| Weltpreise | `S − 1` = 2 | je handelbarem Sektor einer, nicht je Land |
| Partie | 4 | Runde, Jahrgangskennung, Parametersatz-Prüfsumme, Mandatsstand |

Ausserhalb des Zustands bleibt ebenfalls unverändert, und hier liegt der eigentliche Punkt:
**die Todesarten**, die **drei Aktionen je Runde**, die **Partielänge `R`**, die dreizehn
Skalenklassen aus T5, die fünf Herkunftsarten aus T45, die 40 Halbierungsschritte aus T28 und
die vier Maße aus `agentenbau.md`. Sie sind an Spielbalance, Skalenordnung oder Messverfahren
gebunden — an keiner Stelle an die Ländergeometrie. Ein Land mehr ist für sie kein Ereignis.

**Eine Berichtigung gehört hierher, und sie betrifft die Steckplätze.** Der Auftragstext zu
`0116` nennt die zwanzig Steckplätze unter dem, was *nicht* mitwächst. Nach T15 und T16 sind
sie `L·(S+2)` — `L·S` Land×Sektor, `L` Währung, `L` Anleihe —, also **geometrisch und
wachsend**; und der Betreiber hat am 2026-09-05 in `0118` ausdrücklich „Weg A" gewählt: Die
Steckplätze wachsen mit `L`, bei `L = 9` auf 45. Beide Aussagen stammen vom selben Tag; die
jüngere sticht. **Was an den Steckplätzen wirklich nicht mitwächst, ist die Zahl der Aktionen
je Runde** — und genau daraus entsteht die Frage nach der Entscheidungsdichte, die `0118` zu
beantworten hat. Die Adressenzahl ist Geometrie, die Knappheit ist Balance; dieser Abschnitt
trennt beides und entscheidet nur das Erste.

Gleiches in halb: **der Fondsblock wächst zur Hälfte mit.** Von seinen 52 Adressen sind 8
`L`-frei (Aggregat 5, Überrendite 3), 44 sind Geometrie (Steckplätze `L(S+2)`, Beteiligungen
`2LS`). „Der Fondsblock wächst nicht" wäre für die kleinere Hälfte richtig und für die
grössere falsch.

### Was dieser Abschnitt nicht angefasst hat

Nichts. Er ist **ausschliesslich beschreibend**: Er trägt keine Zahl in einem bestehenden
Abschnitt nach, ändert keine Tabelle, keinen `static_assert` und keine Zeile Quelltext. Die
Formeln sind gegen die bestehenden Stellen gelegt und stimmen mit ihnen überein; die eine
Abweichung — 27 gegen 31 bei den Sollreihen — ist oben benannt und gehört Paket `0068`. Die
Länderzahl selbst, die Auswahl eines weiteren Landes und der Umbau des Kerns sind eigene
Pakete und hier nicht entschieden.
