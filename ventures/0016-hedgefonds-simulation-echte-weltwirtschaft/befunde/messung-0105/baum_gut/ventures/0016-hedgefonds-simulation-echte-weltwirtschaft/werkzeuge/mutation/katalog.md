# Der Katalog des Mutationslaufs

Jeder Fall hier ist eine Behauptung ueber eine Probe: *Wenn man diese eine Stelle im
Quelltext so verstellt, dann muss diese Probe rot werden.* Der Mutationslauf fuehrt die
Behauptung aus. Was hier steht, ist deshalb kein Bericht, sondern ein Riegel -- er wird
rot, sobald eine Probe aufhoert zu messen, was sie gemessen hat.

## Das Format

Ein Fall beginnt mit einer Zeile aus zwei Rautenzeichen und dem Wort `Fall`, danach die
Kennung und eine Beschreibung. Es folgen die Felder, um vier Leerzeichen eingerueckt,
und zwei Textbloecke zwischen Tildenzaeunen.

Das Wort ist Pflicht und keine Zierde: Ohne es waere jede Gliederung dieses Dokuments
ein Fall. Beim ersten Lauf las der Treiber die beiden Prosakopfzeilen hier als Faelle
mit den Kennungen `Das` und `Woher` -- laut, immerhin, aber ein Format, in dem man
nicht mehr gliedern darf, ist ein Format, das man umgeht.

| Feld | Bedeutung |
|---|---|
| `quelle` | die Quelldatei, relativ zur Wurzel des Vorhabens |
| `objekt` | die Objektdatei, relativ zum Baubaum -- aus ihr liest der Lauf die Uebersetzerschalter |
| `ziel` | das CMake-Ziel, das nach der Mutation neu gebunden wird |
| `probe` | der Name des ctest-Falls; ohne Angabe derselbe wie `ziel` |
| `urteil` | was herauskommen muss: `rot`, `gruen` oder `bau` |

Der Suchblock wird **roh** genommen, mit jeder Einrueckung. Kommt sein Text in der
Quelldatei nicht genau einmal vor, ist der Fall ein Fehlschlag und kein uebersprungener
Fall: Ein Muster, das sich nicht mehr findet, misst nichts mehr.

`urteil: bau` heisst, dass die Mutation schon den Uebersetzer nicht passiert. Das ist
ein eigenes Urteil, weil es ein anderer Riegel ist als eine rote Probe -- die
`static_assert`-Kette faengt Verschiebungen, bevor ein Test ueberhaupt laeuft.

## Woher diese neunzehn Faelle stammen

Siebzehn davon zaehlt der Pruefbericht zu Paket 0010 als Mutationen auf, die eine
richtige Zahl an eine falsche Beschriftung oder eine falsche Einheit an eine richtige
Zahl haengen und die **keine** Probe fing. Paket 0097 hat die Zusicherungen
nachgetragen, die sie fangen, und sie einmal von Hand gefahren -- mit einem Skript unter
`bau/`, das beim naechsten sauberen Bau fort war.

Die beiden uebrigen (`Z01`, `Z02`) sind die zwei anderen Kopfzeilen der drei
Zustandsebenen. Ihre Zusicherungen sind in Paket 0097 neu dazugekommen; ohne einen
Rotnachweis waeren sie Zierde.

---

## Fall M15 -- die Klassennamen 7 und 8 sind getauscht

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
"Realindex", "Personen",
~~~

~~~ersatz
"Personen", "Realindex",
~~~

## Fall M16 -- die Klasseneinheiten 8 und 9 sind getauscht

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    "Personen",
    "Lobbypunkte",
~~~

~~~ersatz
    "Lobbypunkte",
    "Personen",
~~~

## Fall M17 -- die Herkunftsnamen 0 und 1 sind getauscht

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    "Datenanker", "Entwurf", "Parameter", "Manifest", "Vorgabe",
~~~

~~~ersatz
    "Entwurf", "Datenanker", "Parameter", "Manifest", "Vorgabe",
~~~

## Fall M18 -- die Einheit der Klasse 2 wird zu einem Stueckzaehler

Der teuerste der siebzehn Faelle. Klasse 2 ist die groesste ueberhaupt -- 71 von 310
Adressen, jede Wertschoepfung, jeder Kapitalstock, jeder Handelsstrom, der Marktkorb.
Vor Paket 0097 uebersetzte diese Mutation und die Probe blieb bestanden; die Detailebene
schrieb danach fuer alle 71, ihre Zahl sei ein Stueckzaehler statt eines Betrags.

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    "Tausend USD zu konstanten Preisen 2015",
~~~

~~~ersatz
    "Stueck bzw. Runden",
~~~

## Fall M19 -- die Spalte Zoll liest den Haushaltsstand

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
        feld(blatt, " | Zoll ", z.lies(zustand::stelle_instrument(gebiet, Instrument::Zoll,
                                                                  InstrumentFeld::Stand)));
~~~

~~~ersatz
        feld(blatt, " | Zoll ", z.lies(zustand::stelle_instrument(gebiet, Instrument::Haushalt,
                                                                  InstrumentFeld::Stand)));
~~~

## Fall M20 -- die Spalte Zins liest das Aggregat statt des Instrumentenstands

Der Fall, um dessentwillen Paket 0097 eine zweite, absichtlich halb gerechnete Belegung
gebaut hat. In der Grundbelegung tragen beide Adressen dieselbe Zahl, und dann ist diese
Mutation von aussen nicht zu sehen. Wird dieser Fall gruen, ist die zweite Belegung
verlorengegangen.

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
        feld(blatt, " | Zins ", z.lies(zustand::stelle_instrument(gebiet, Instrument::Leitzins,
                                                                  InstrumentFeld::Stand)));
~~~

~~~ersatz
        feld(blatt, " | Zins ", z.lies(zustand::stelle_aggregat(gebiet, Aggregat::Leitzins)));
~~~

## Fall M21 -- die Spalte Regulierung faellt weg

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
        feld(blatt, " | Regulierung ",
             z.lies(zustand::stelle_instrument(gebiet, Instrument::Regulierung,
                                               InstrumentFeld::Stand)));
~~~

~~~ersatz
        blatt.text(" | Regulierung -");
~~~

## Fall N02 -- die Spalte BIP liest fuer jedes Gebiet das der USA

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    feld(blatt, " | BIP ", werte::bip(z, gebiet));
~~~

~~~ersatz
    feld(blatt, " | BIP ", werte::bip(z, Gebiet::US));
~~~

## Fall N03 -- die Spalte Zustimmung faellt weg

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
        feld(blatt, " | Zustimmung ",
             z.lies(zustand::stelle_politisch(gebiet, PolitischeGroesse::Zustimmung)));
~~~

~~~ersatz
        blatt.text(" | Zustimmung -");
~~~

## Fall N04 -- die Spalte Aufsicht liest den Einfluss

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
             z.lies(zustand::stelle_politisch(gebiet, PolitischeGroesse::Aufsichtszaehler)));
~~~

~~~ersatz
             z.lies(zustand::stelle_politisch(gebiet, PolitischeGroesse::Einfluss)));
~~~

## Fall N05 -- eine der drei Ueberrenditen faellt weg

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    for (std::size_t n = 1; n <= UEBERRENDITE_RUNDEN; ++n) {
~~~

~~~ersatz
    for (std::size_t n = 1; n < UEBERRENDITE_RUNDEN; ++n) {
~~~

## Fall N06 -- der Korbwert liest die Marktrendite

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    feld(blatt, "Markt | Korbwert ", z.lies(zustand::stelle_markt(MarktGroesse::Wert)));
~~~

~~~ersatz
    feld(blatt, "Markt | Korbwert ", z.lies(zustand::stelle_markt(MarktGroesse::Rendite)));
~~~

## Fall N07 -- die Kasse liest den Hebelstand

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    feld(blatt, " | Kasse ", z.lies(zustand::stelle_fonds(FondsGroesse::Kasse)));
~~~

~~~ersatz
    feld(blatt, " | Kasse ", z.lies(zustand::stelle_fonds(FondsGroesse::Hebelstand)));
~~~

## Fall N08 -- der Jahrgang liest den Mandatsstand

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    feld(blatt, " | Jahrgang ", z.lies(zustand::stelle_partie(PartieFeld::JahrgangId)));
~~~

~~~ersatz
    feld(blatt, " | Jahrgang ", z.lies(zustand::stelle_partie(PartieFeld::Mandatsstand)));
~~~

## Fall N09 -- die gedruckte Sektornummer der Weltpreise ist um eins verschoben

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
        blatt.zahl(static_cast<i64>(s));
~~~

~~~ersatz
        blatt.zahl(static_cast<i64>(s) + 1);
~~~

## Fall N10 -- die Einheit der Klasse 13 ist verstellt

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    "Milli-Runden",
~~~

~~~ersatz
    "Milli-Stunden",
~~~

## Fall N11 -- die Kopfzeile der Detailebene ist eine andere

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    blatt.text("Detail (Ebene 2 von 3, T20) -- Bereich ");
~~~

~~~ersatz
    blatt.text("Detailebene -- Bereich ");
~~~

## Fall Z01 -- die Kopfzeile der Uebersichtsebene ist eine andere

Nicht aus den siebzehn. Die Zusicherung auf diese Kopfzeile ist in Paket 0097 neu
dazugekommen und braucht ihren eigenen Rotnachweis.

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    blatt.text("Uebersicht (Ebene 1 von 3, T20) -- jede Zahl in der Skala ihrer Klasse, "
~~~

~~~ersatz
    blatt.text("Uebersichtsebene -- jede Zahl in der Skala ihrer Klasse, "
~~~

## Fall Z02 -- die Kopfzeile der Unterschiedsebene ist eine andere

Wie `Z01`: neu in Paket 0097, deshalb hier.

    quelle:  kern/src/zustandsausgabe.cpp
    objekt:  kern/CMakeFiles/kern_geprueft.dir/src/zustandsausgabe.cpp.o
    ziel:    zustandsausgabe_probe
    urteil:  rot

~~~suche
    blatt.text("Unterschied (Ebene 3 von 3, T20) -- alter Wert, neuer Wert, Differenz");
~~~

~~~ersatz
    blatt.text("Unterschiedsebene -- alter Wert, neuer Wert, Differenz");
~~~
