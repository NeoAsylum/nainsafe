//! # Der Belegstellenriegel -- Paket 0059
//!
//! Sechs Pakete haben Belegstellen von Hand nachgezogen (0034, 0035, 0044, 0047,
//! 0050, 0057). Jedes war richtig; zusammen sind sie der Beleg, dass die
//! Handnachfuehrung den Fehler nur einholt und nicht abstellt. Paket 0050 hat vier
//! Belegstellen aufgezaehlt und fuer jede die richtige Zeile nachgeschlagen -- wenige
//! Stunden spaeter standen die Stellen anderswo. Die Korrektur war falsch, bevor sie
//! jemand ausfuehren konnte.
//!
//! ## Was dieses Programm prueft -- zwei Bedingungen, zwei Pakete
//!
//! Der Rumpf von 0059 nennt zwei Bedingungen; beim zweiten Abbruch am 2026-09-04 hat
//! der Projektmanager sie getrennt. Beide stehen jetzt hier, jede mit ihrem eigenen
//! Zaehlwerk und ihrer eigenen Meldung:
//!
//!   **Bedingung 1 -- keine Zeilennummer in eine fremde Datei** (Paket 0059). Wo im
//!   Text ein Dateiname steht, dem eine Zeilenangabe folgt, ist der Verweis nicht
//!   haltbar. Er zeigt heute vielleicht richtig; er zeigt morgen woandershin, ohne
//!   dass jemand etwas tut.
//!
//!   **Bedingung 2 -- jedes Abschnittszitat existiert wirklich** (Paket 0067). Wo ein
//!   Text eine Ueberschrift aus einer benannten Datei zitiert, steht in jener Datei
//!   eine Zeile mit genau dieser Ueberschrift. Sechs Pakete (0034, 0035, 0044, 0047,
//!   0050, 0057) haben Zeilennummern durch Ueberschriften ersetzt. Die Ersetzung hat
//!   das Problem verschoben, nicht abgestellt: Eine umbenannte Ueberschrift
//!   hinterlaesst einen toten Verweis, der beim Lesen richtig aussieht -- und der,
//!   anders als eine verrutschte Nummer, nicht einmal beim Nachschlagen auffaellt.
//!
//! Bedingung 2 ist die aufwendigere: Sie muss Ueberschriften aus fremden Dateien
//! lesen, waehrend Bedingung 1 ein Mustertreffer in derselben Zeile ist.
//!
//! Ein Beispiel, und es ist absichtlich echt statt erfunden: `spiel.md`, Abschnitt
//! "Die Schleife". Der Satz, den Sie gerade lesen, ist selbst ein Zitat der von
//! Bedingung 2 geprueften Form. Wer den Abschnitt dort umbenennt, macht diesen Riegel
//! an seiner eigenen Kopfzeile rot -- so wie Bedingung 1 sich selbst faengt, wenn
//! jemand hier eine Zeilenangabe hinschreibt.
//!
//! Ein zweites, ebenso echtes Beispiel, und es traegt das am 2026-09-04 dazugekommene
//! dritte Schluesselwort: `technik.md`, Absatz "Zwei Adresspaare tragen denselben
//! Wert, und das braucht eine Regel statt eines Zufalls". Auch dieses Zitat zaehlt
//! mit, auch es loest auf, und auch es ist der Rothebel fuer das, was es zeigt: Wer
//! den Wortlaut hier oder dort aendert, macht den Riegel rot.
//!
//! ## Bedingung 2: was als Zitat zaehlt
//!
//! Gesucht wird **je Absatz, nicht je Zeile**. Ein Absatz ist ein zusammenhaengender
//! Block gleichartiger Zeilen -- derselbe Kommentarkopf, keine Leerzeile dazwischen --,
//! zu einer Zeichenkette zusammengezogen. Das ist der Unterschied zu Bedingung 1 und
//! er ist gemessen: Die Pruefung von 0044 hat am 2026-09-04 festgestellt, dass die
//! Belegstelle in `schranken_probe.cpp` ihren Dateinamen vier Zeilen oberhalb der
//! Ueberschrift traegt. Eine zeilenweise Suche haette genau das Paket uebergangen, das
//! als Beispiel diente.
//!
//! Ein Zitat besteht aus drei Teilen, alle im selben Absatz:
//!
//!   1. ein Schluesselwort -- das Wort fuer einen Textabschnitt, das Wort fuer einen
//!      Textblock innerhalb eines Abschnitts oder das Wort fuer eine Ueberschrift,
//!      letzteres in beiden Schreibweisen (mit Umlaut und ohne). Das zweite ist am
//!      2026-09-04 dazugekommen und nicht aus Vollstaendigkeitsdrang: Paket 0034 hat
//!      zwei seiner drei Belegstellen mit ihm geschrieben, und ohne es blieben sie
//!      ungefangen -- die Zaehlung stieg dadurch von 21 auf 23;
//!   2. unmittelbar danach die Ueberschrift **in Anfuehrung**: gerade oder
//!      typografische Anfuehrungszeichen, einfache Anfuehrungszeichen, Akzente oder
//!      Sternchen. Ein `\` davor wird uebersprungen, damit ein Zitat in einer
//!      C++-Zeichenkette (`\"...\"`) mitzaehlt;
//!   3. **links davon im selben Absatz** ein Dokumentname. Der naechstgelegene, der
//!      sich im Bestand wiederfindet, gilt als Ziel.
//!
//! Teil 2 hat seit Paket 0079 eine zweite Gestalt: **kein Anfuehrungszeichen, sondern
//! ein Name, der im Satz weiterlaeuft.** Er wird nicht wortgleich verlangt, sondern
//! muss am Anfang einer Ueberschrift der Zieldatei stehen; wo er endet und wie er sich
//! von einer blossen Gliederungsziffer trennt, steht weiter unten in einem eigenen
//! Abschnitt.
//!
//! ## Wie streng "genau diese Ueberschrift" gemeint ist
//!
//! Eine **Ueberschriftszeile** in der Zieldatei ist eines von zweien: eine Zeile, die
//! mit einem oder mehreren Rautenzeichen und einem Leerzeichen beginnt (Markdown und,
//! in einer TOML-Datei, die Kommentarform, in der dort Gruppen ueberschrieben sind);
//! oder eine Zeile, die mit einem fett ausgezeichneten Vorspann beginnt. Der zweite
//! Fall ist keine Bequemlichkeit: `reihen.toml` zitiert drei solche Vorspaenne, und
//! ohne sie waere Bedingung 2 fuer zwei der sechs Pakete leer. Gemessen am 2026-09-04
//! mit einem Mutanten, der diese Form abschaltet: **6 der 24 Zitate fallen**, darunter
//! beide, die Paket 0034 hinterlassen hat -- sie zeigen auf denselben Vorspann unter
//! T49 und haetten ohne den zweiten Fall gar kein Ziel.
//!
//! Verglichen wird nach dieser Normierung, auf beiden Seiten gleich:
//!
//!   * Umlaute und Eszett werden umschrieben (`Groesse` und `Größe` sind dasselbe).
//!     Das ist kein Nachlass, sondern die Lage: Der Quelltext dieses Vorhabens ist
//!     umlautfrei, die Vorgaben sind es nicht. `parameter.toml` zitiert eine
//!     Ueberschrift aus `spiel.md`, die im Ziel ein `ö` und ein `ß` traegt.
//!   * Gedankenstriche werden zu zwei Bindestrichen, typografische Anfuehrungen zu
//!     geraden.
//!   * Auszeichnung faellt weg (Sternchen, Unterstrich, Akzent), Leerraum wird
//!     zusammengezogen -- damit eine ueber zwei Zeilen umgebrochene Ueberschrift
//!     dieselbe ist wie eine einzeilige.
//!   * Fuehrende Rautenzeichen faellen weg, damit ein Zitat sie mitfuehren darf.
//!   * Ein Punkt, Doppelpunkt, Komma oder Semikolon am Ende faellt weg.
//!   * **Gross- und Kleinschreibung nicht.** Sie umzuschreiben ist im Deutschen eine
//!     Umbenennung wie jede andere, und ein Riegel, der sie durchgehen laesst, prueft
//!     die Haelfte des Wortes.
//!
//! Was **nicht** geprueft wird: ob die Ueberschrift nur einmal vorkommt, und ob ein
//! Zusatz im Zitat ("Reihe 9", "Nummer 4", "Tabellenzeile") stimmt. Geprueft wird die
//! Existenz. Ein Zitat, das auf eine von drei gleichnamigen Stellen zeigt, bleibt
//! gruen -- die Ueberschrift gibt es ja.
//!
//! ## Wie "fremde Datei" gemessen wird
//!
//! Ein Treffer allein ist noch kein Befund. Erst wenn **auf derselben Zeile links vom
//! Treffer** ein Wort mit einer der Endungen unten steht und dessen Basisname nicht
//! die gerade gelesene Datei ist, zeigt die Zahl nach auswaerts. Das trennt zwei
//! Sorten sauber:
//!
//!   * Ein Dateiname mit einer Zeilenangabe dahinter -- ein Verweis nach auswaerts.
//!     Befund.
//!   * `stelle_basiswechsel(Gebiet::RW) == 197);` mit einer Zeilenangabe im
//!     Zeilenendkommentar -- kein Dateiname, also keine fremde Datei. Das ist die
//!     Nummer der Zeile in der Adresstabelle, und die `static_assert` daneben rechnet
//!     sie in derselben Zeile nach. Kein Befund, und zwar nicht aus Nachsicht,
//!     sondern weil dort nichts nach auswaerts zeigt.
//!
//! **Die Grenze dieser Messung, ausgeschrieben:** Eine nackte Zeilenangabe ohne
//! Dateinamen daneben faengt der Riegel nicht -- auch dann nicht, wenn drei Zeilen
//! darueber im Fliesstext eine Datei genannt wurde. Er sieht je Zeile, nicht je
//! Absatz. Wer ihn fuer "alle Verweise geprueft" haelt, irrt; er prueft die, die ihr
//! Ziel bei sich tragen. Die Zahl unten sagt deshalb beides: wie viele Muster
//! getroffen haben und wie viele davon einen Dateinamen trugen.
//!
//! ## Wie weit nach links gesucht wird -- Paket 0073
//!
//! Bis zum 2026-09-04 sah der Riegel den Dateinamen nur, wenn er **unmittelbar** links
//! stand: ein Lauf Nicht-Pfadzeichen, dann genau ein Wort. Stand dazwischen noch etwas,
//! galt der Verweis als "ohne Dateinamen" -- und ein Verweis ohne Dateinamen ist kein
//! Befund. Das war keine gedachte Luecke: Auf einem Baum von 50 Dateien und 12
//! Mustertreffern fand die enge Fassung **null** Verweise mit Dateinamen, die breite
//! **zwei**, und beide zwei sind echt. Es sind genau die Formen, die die sechs
//! Aufraeumpakete hinterlassen, wenn sie zur Haelfte greifen -- der Abschnitt ist
//! nachgetragen, die Nummer steht noch da. Ihr Wortlaut steht in `NAMENSFAELLE`, den
//! ersten beiden Zeilen; hier steht er nicht, weil eine abgeschriebene Beispielzeile
//! sich in diesem Kommentar selbst faenge.
//!
//! **Die Regel: es gilt der naechstgelegene Name.** Gesucht wird wortweise nach links;
//! das erste Wort mit zugelassener Endung gewinnt, und ueber es hinweg wird nicht
//! weitergesucht. Stehen zwei Namen auf der Zeile, ist der naeher am Treffer gemeint --
//! derselbe Grundsatz, nach dem `naechster_verweis` fuer Bedingung 2 arbeitet, und aus
//! demselben Grund: Wer darueber hinwegliest, bindet eine Zahl an eine Datei, die im
//! Satz gar nicht gemeint war.
//!
//! **Wo die Suche endet -- und warum es kein Abstand in Zeichen ist.** Sie endet am
//! Anfang des Satzes, in dem der Treffer steht. Ein Abstandsmass waere die naheliegende
//! Alternative gewesen, und es ist verworfen worden, weil sich seine Zahl hier nicht
//! messen laesst: Die beiden echten Formen liegen 17 und 47 Zeichen vom Namen entfernt.
//! Jede Schranke ueber 47 waere geraten, und eine geratene Schwelle in einem Messgeraet
//! ist schlimmer als eine weite Suche -- man traut ihr, ohne dass jemand sie geprueft
//! hat. Der Satz dagegen ist eine Grenze mit Bedeutung: Ein Verweis und sein Ziel
//! stehen im selben Satz. Ein Abbruch am Komma oder Semikolon schied aus, und auch das
//! ist gemessen und nicht geschmeckt -- die eine echte Form traegt ein Semikolon
//! zwischen Namen und Nummer, die andere ein Komma. Beide waeren damit wieder
//! durchgefallen.
//!
//! Dass die Suche breit ist, kostet auf dem gemessenen Baum nichts: 12 Treffer, zwei
//! Funde, kein falscher. Bliebe es dabei nicht, waere das ein Befund und keine
//! Einladung, die Schwelle nachzuziehen.
//!
//! ## Der Selbsttest, der bei jedem Aufruf mitlaeuft
//!
//! Acht Faelle in `NAMENSFAELLE` halten fest, was die Suche nach links finden **und
//! was sie durchlassen** muss; sie laufen vor jedem Lesen des Bestands, und ein
//! verfehlter Fall bricht den Lauf mit Code 2 ab. Die Haelfte davon sind Faelle mit
//! erwarteter Leermeldung -- die fuenf Stellen in `kern/src/zustand.cpp`, die ein
//! Rechenergebnis und keinen Dateiverweis tragen, ein Name jenseits des Satzendes und
//! ein Name rechts vom Treffer. Ohne sie wiese der Test nur nach, dass die Suche
//! *etwas* findet, und nicht, dass sie das Richtige findet.
//!
//! Nachgewiesen ist er: Auf die enge Fassung von vorher zurueckgestellt, fallen genau
//! die vier Faelle, die die Verbreiterung verlangt (1, 2, 3 und 8), und die vier
//! anderen bleiben gruen.
//!
//! Sechs weitere Tabellen sind seither dazugekommen und laufen ebenso bei jedem Aufruf
//! mit: `ZITATFAELLE` zur Form ohne Anfuehrung (Paket 0079), `ZIELFAELLE` zur Frage, wo
//! eine genannte Zieldatei liegt (Paket 0083), `ABSTANDSFAELLE` zum Wortabstand samt
//! Suche nach rechts (Paket 0086), `SATZFAELLE` zur Satzgrenze nach links (Paket 0079,
//! zweiter Teil), `URTEILSFAELLE` zu dem Schritt, an dem aus einer Art ein Urteil
//! wird (Paket 0106), und `ORDNUNGSFAELLE` zu der Ordnung, in der gemeldet wird
//! (Paket 0130). Die ersten vier halten vor allem den **roten** Fall fest, den der
//! Bestand nicht hergibt -- auf ihm loest heute jedes Zitat auf, der Riegel koennte
//! dort also nur zeigen, dass er gruen wird.
//!
//! Die fuenfte haelt etwas anderes, und sie schliesst den juengsten blinden Fleck
//! dieses Programms: **die Verdrahtung statt des Bausteins.** Die vier aelteren rufen
//! ihren Baustein unmittelbar auf; keine von ihnen kam an den Schritt heran, der aus
//! einer Art ein Urteil macht, weil der einen Gegenstand auf der Platte brauchte. Bis
//! zum 2026-09-05 liess er sich deshalb auf "immer aufgeloest" festnageln, ohne dass
//! ein Fall riss und ohne dass der Lauf ueber den Bestand rot wurde -- auch nicht auf
//! einer Kopie mit umbenannter Zielzeile. Seit Paket 0106 steht er als eigener Aufruf
//! da und hat sechs Faelle, und jeder einzelne ist einmal rot gemessen worden.
//!
//! Die sechste haelt etwas, das gar keinen Gegenstand auf der Platte braucht: **die
//! Ordnung, in der gemeldet wird.** Bis zum 2026-09-06 war sie die des Dateisystems --
//! zwei inhaltsgleiche Baeume, einer auf ext4 und einer auf tmpfs, ergaben dieselben
//! Zahlen und dieselben Funde in verschiedener Reihenfolge. Die Begruendung und die
//! drei Regeln, die die acht Faelle einzeln halten, stehen weiter unten bei
//! `vor_in_byteordnung`.
//!
//! ## Was der Riegel liest, und warum genau das
//!
//! Gelesen werden die **Bauquellen** des Vorhabens: Rumpf- und Kopfdateien, die
//! Bausteuerung und jede Bauliste. Ausgenommen sind die Verzeichnisse `bau` (vom
//! Uebersetzer erzeugt) und `befunde` (Berichte -- eine Zeilennummer darin ist ein
//! *Messwert vom Tag der Messung*, kein Verweis; sie soll gerade nicht nachgefuehrt
//! werden, sonst faelschte man einen Bericht). Von beiden werden seit Paket 0083 die
//! **Dateinamen** eingesammelt, nicht ihr Inhalt -- der eigene Teil weiter unten sagt,
//! wofuer.
//!
//! Der Schnitt bei `bau` kostet etwas, und das gehoert dazugesagt: Unter
//! `pruefstand/bau/pruefung-0019/` liegen Quelldateien, die keine Erzeugnisse sind.
//! Sie fallen mit heraus. Sie dort wegzuholen ist Aufraeumarbeit an fremdem Gebiet;
//! eine Ausnahme nach Pfadnamen waere die erste Zeile einer Ausnahmeliste. Beides tut
//! dieser Riegel nicht.
//!
//! Die Datendokumente unter `daten/` und die Parameterdatei sind fuer **Bedingung 1**
//! nicht darunter, und das ist eine benannte Grenze und keine Ausnahmeliste: Auf
//! `reihen.toml` und `einheitenbefund-pwt-baci.md` laeuft Paket 0057, auf die
//! Parameterdatei liefen 0035 und 0042. Ein Riegel, der sie dort mitnaehme, koennte
//! erst gruen werden, nachdem eine inhaltliche Aufraeumarbeit fertig ist -- genau das,
//! was das Arbeitspaket zu diesem Programm ausschliesst. Die Erweiterung ist eigene
//! Arbeit und liegt als Vorschlag daneben. Die Grenze steht hier ausgeschrieben, damit
//! niemand die Zahlen unten fuer "alles geprueft" haelt.
//!
//! Zu lesen sind sie fuer Bedingung 1 ohnehin nie noetig: Sie vergleicht den Verweis
//! mit nichts, sie verwirft ihn wegen seiner **Bauart**. Ob die Nummer heute trifft,
//! ist gleichgueltig -- sie traefe nicht aus Bauart, sondern aus Glueck.
//!
//! ## Was Bedingung 2 daueber hinaus liest, und warum der Schnitt anders liegt
//!
//! Bedingung 2 liest die Bauquellen **und** die Datendokumente: `parameter.toml` und
//! alles unter `daten/` mit der Endung `.md` oder `.toml`. Der Grund, warum der
//! Schnitt hier anders liegt als bei Bedingung 1, ist kein Sinneswandel: Vier der
//! sechs Pakete, um derentwillen dieses Programm existiert, haben ihre Ueberschriften
//! genau dort hinterlassen -- 0034 in `adressen.md`, 0035 in `parameter.toml`, 0047
//! und 0057 in `reihen.toml`. Ein Riegel, der sie auslaesst, prueft zwei von sechs.
//!
//! Und der Einwand von oben trifft Bedingung 2 nicht: Sie verlangt kein Aufraeumen,
//! sondern ein Nachschlagen. Ein Zitat dort ist entweder aufloesbar oder es ist tot;
//! im zweiten Fall ist es ein Befund und kein Rest einer laufenden Arbeit.
//!
//! **Was auch Bedingung 2 nicht liest, und warum:**
//!
//!   * `aufgaben/` -- ein Arbeitspaket beschreibt den Stand, als es zugeschnitten
//!     wurde. Es nachzufuehren faelschte es, genau wie bei `befunde/`.
//!   * Die Vorgaben unter `specs/`. Sie sind **Ziel** jedes zweiten Zitats und werden
//!     gelesen, aber nur nachgeschlagen: Ein Befund darin liesse sich hier nicht
//!     beheben, denn das Arbeitspaket zu diesem Programm verbietet das Aufraeumen in
//!     `specs/` ausdruecklich. Ein Riegel, dessen Rot niemand beheben darf, ist keiner.
//!
//! ## Die drei Zahlen von Bedingung 2, und was jede bedeutet
//!
//! Gemeldet werden **Zitate gefunden** und **davon aufgeloest**. Sind sie ungleich,
//! ist der Lauf rot: Jedes Zitat, dessen Ziel im Bestand steht, muss seine
//! Ueberschrift dort auch finden. Ist die erste Zahl null, bricht der Riegel ab statt
//! gruen zu melden -- dann stimmt das Muster nicht mehr, denn die sechs Pakete haben
//! nachweislich Zitate hinterlassen.
//!
//! Dazu eine dritte Zahl, und sie ist die ehrliche Haelfte: **uebergangene
//! Fundstellen**. Sechs Sorten, alle unten einzeln mit Datei und Zeile genannt, damit
//! keine still bleibt:
//!
//!   * *ohne Dokumentnamen im Absatz* -- ein Verweis auf einen Abschnitt derselben
//!     Datei, oder auf eine Quelle ausserhalb dieses Vorhabens (eine Lizenz, ein RFC).
//!     Er traegt sein Ziel nicht bei sich; dieser Riegel prueft nur, was das tut.
//!   * *Ziel in einem mit Absicht ungelesenen Ordner* -- der naechstgelegene Name zeigt
//!     selbst in einen Ordner, den dieser Riegel nicht liest (`befunde/`, `bau/`), und
//!     dort liegt unter dem genannten Pfad auch eine Datei. Paket 0083 hat diese Sorte
//!     von der naechsten getrennt; der eigene Teil weiter unten sagt, warum.
//!   * *Ziel ausserhalb beider Wurzeln* -- der Name spricht seinen Ort selbst aus:
//!     ein unbedingter Pfad, ein Aufstieg mit zwei Punkten. Dazu die Netzadresse, die
//!     ihre eigene Meldung hat.
//!   * *Gliederungsziffer statt Ueberschrift* -- Paket 0079, oben begruendet. Die
//!     groesste der sechs Gruppen und die harmloseste: Eine Nummer traegt keinen
//!     Wortlaut, an dem sich etwas nachschlagen liesse.
//!   * *einzelnes Zeichen statt Ueberschrift* -- ein Formelzeichen oder ein
//!     Platzhalter, ebenfalls oben begruendet.
//!   * *Zieldatei fuehrt keine Ueberschrift* -- der naechstgelegene Name gehoert zu
//!     einer Quell- oder Kopfdatei ohne jede Gliederung. Sie kann ein Zitat weder
//!     bestaetigen noch widerlegen; ein Rot dort waere ein Rot gegen den Riegel.
//!
//! Diese Fundstellen sind der ausgeschriebene blinde Fleck von Bedingung 2. Sie werden
//! gezaehlt und aufgezaehlt, aber nicht bewertet -- eine Zahl, die stumm bliebe, waere
//! genau die Sorte Riegel, gegen die dieses Paket geschrieben ist.
//!
//! ## Die sechs Pakete, einzeln abgehakt -- Stand 2026-09-04
//!
//! Gemessen, nicht angenommen: Die Belegstelle jedes der sechs Pakete ist im
//! Aenderungsverlauf seiner eigenen Datei nachgeschlagen worden. Genannt wird sie hier
//! ueber ihren Wortlaut und nicht ueber eine Zeilennummer -- eine Nummer neben einem
//! Dateinamen waere in dieser Datei die Sorte Verweis, die Bedingung 1 verbietet.
//!
//!   0034 -- `daten/adressen.md`, drei Stellen, alle mit Ziel in `technik.md`, seit dem
//!           2026-09-05 **alle drei gefangen**. Zwei davon seit dem 2026-09-04: die
//!           Begruendung zur Spalte `Adresse` und die Herleitung zu den unmarkierten
//!           Geschwisterpaaren zitieren beide denselben fett ausgezeichneten Vorspann
//!           unter T49, und beide loesen auf. Sie fielen erst an, seit das Wort fuer
//!           einen Textblock in SCHLUESSEL steht. Die dritte -- die
//!           Tabellenueberschrift zu T46, im Satz mit "sagt es selbst" -- braucht die
//!           beiden Lockerungen aus Paket 0086; die Form steht unten.
//!           *Berichtigung vom 2026-09-04, selbst berichtigt am 2026-09-05:* Bis dahin
//!           stand hier das Kopffeld `quellen` derselben Datei. Das ist eine echte und
//!           gefangene Belegstelle, aber sie stammt aus **Paket 0007-adressverzeichnis-310**
//!           und nicht aus 0034. Bis zum 2026-09-05 stand hier als Herkunft 0004 --
//!           und damit trug ausgerechnet der Absatz, der vor dieser Verwechslung warnt,
//!           selbst ein falsches Beispiel. Woran es nachpruefbar ist: an der
//!           `dateien`-Liste des Arbeitspakets, nicht am Betreff des Commits. Die von
//!           0004 nennt keine Datei unter `daten/`, die von 0007 nennt genau diese.
//!           Die 0004 stammte aus dem Betreff des Commits `a629f73`, und genau das ist
//!           der Fehler, vor dem der Absatz warnt: `git log -S` auf den Wortlaut fuehrt
//!           zwei Tage daneben, weil die Arbeit eines Pakets hier regelmaessig im
//!           Commit des naechsten Laufs liegt und dessen Betreff den Namen des anderen
//!           Pakets traegt. Der Wortlauttreffer gehoert deshalb gegen das Datum des
//!           gesuchten Pakets gehalten, nicht fuer sich genommen.
//!   0035 -- `parameter.toml`, in der Herkunftsbegruendung zu `hebelaufschlag`. Zwei
//!           Zitate, beide gefangen; das zweite traegt seinen Dateinamen eine Zeile
//!           oberhalb und faellt damit nur wegen der Absatzlesung an.
//!   0044 -- `kern/test/schranken_probe.cpp`, im Kommentarblock ueber
//!           `GRENZEN_BAUZEITPUNKT`. Gefangen. Das ist der Fall aus dem Nachtrag des
//!           Projektmanagers: Dateiname vier Zeilen ueber der Ueberschrift.
//!   0050 -- `pruefstand/test/vorrat_verfahren_probe.cpp`. Fuenf Zitate derselben
//!           Ueberschrift, alle gefangen -- darunter die Marke `BELEGSTELLE`, deren
//!           Anfuehrungszeichen in der Zeichenkette maskiert sind.
//!   0057 -- `daten/reihen.toml` und `daten/einheitenbefund-pwt-baci.md`. Vier Zitate,
//!           alle gefangen; drei in der geklammerten Form, die dieses Paket eingefuehrt
//!           hat, eines mit gemischter Anfuehrung.
//!   0047 -- `daten/reihen.toml`. **Gefangen seit Paket 0079** -- der naechste
//!           Abschnitt beschreibt, woran.
//!
//! ## Die Ueberschrift ohne Anfuehrung -- Paket 0079
//!
//! Paket 0047 hat seine Ueberschriften **ohne jede Anfuehrung** zitiert. In
//! `reihen.toml` steht dadurch viermal die Form `<datei>, <Schluesselwort> <Name>`, wo
//! der Name unmittelbar im Satz weiterlaeuft: einmal auf eine Ueberschrift ("Reihe 1"),
//! einmal auf eine Aufzaehlung ("2b und 2c") und zweimal auf eine blosse Nummer ("5",
//! "7"). Bis zum 2026-09-04 hat der Riegel diese vier still uebergangen. Sie zu fangen
//! heisst, den Namen bis zum naechsten Satzzeichen zu lesen -- und dann haben eine
//! Nummer und eine Ueberschrift dieselbe Gestalt.
//!
//! **Die Entscheidung faellt an einem einzigen Zeichen: dem Punkt hinter der
//! Gliederungsziffer.** Eine Datei, die ihre Abschnitte nummeriert, schreibt die Nummer
//! mit einem Punkt in die Ueberschrift und dahinter den Namen -- die Zusammenfassung
//! von `lizenzbefund-reihen.md` traegt so die Fuenf, der Datenteil von `technik.md` die
//! Sieben. Wer eine solche Ziffer zitiert, nennt die Nummer und nicht den Wortlaut.
//! Dieser eine Punkt entscheidet zweimal:
//!
//!   1. **Er ist keine Wortgrenze.** Ein Zitat gilt als aufgeloest, wenn es am Anfang
//!      einer Ueberschrift der Zieldatei steht; wo dort ein Punkt folgt, steht es das
//!      nicht. Die blosse Fuenf faellt damit durch, waehrend die Reihe mit ihrer Nummer
//!      und die Aufzaehlung mit ihrem "und" durchkommen -- beide sind Wortlaut.
//!   2. **Er ist der Nachweis, dass ueberhaupt nummeriert wird.** Eine Ziffer am Anfang
//!      eines Zitats gilt nur dann als Nummer, wenn die Zieldatei -- oder die
//!      zitierende, denn ein Verweis auf einen eigenen Abschnitt traegt links den
//!      falschen Nachbarn -- eine Ueberschrift mit genau dieser Ziffer und einem Punkt
//!      fuehrt, oder wenn das Zitat aus nichts als ihr besteht.
//!
//! Der zweite Teil ist der wichtigere, und er ist die Antwort auf den Einwand, an dem
//! dieses Paket haengt: **Eine gerade umbenannte Ueberschrift sieht nicht aus wie eine
//! Nummer.** Sie faellt nicht in die uebergangenen Fundstellen zurueck, sondern wird
//! ein Befund -- auch dann, wenn ihr Zitat mit einer Ziffer beginnt, denn die Zieldatei
//! nummeriert dann nicht mit ihr. Zwei Faelle in `ZITATFAELLE` halten genau das fest,
//! je einer fuer die Ueberschrift und einer fuer die Aufzaehlung.
//!
//! **Vier Grenzen, ausgeschrieben, weil sie still waeren.**
//!
//!   * *Kleinschreibung.* Ein Name ohne Anfuehrung beginnt mit einem Grossbuchstaben
//!     oder einer Ziffer. Folgt dem Schluesselwort ein Verhaeltniswort, ist es kein
//!     Zitat, sondern ein Satz -- die Stelle wird gar nicht erst gezaehlt. Ohne diese
//!     Grenze wuerde jeder laufende Satz, der das Wort fuehrt, an einer Gliederung
//!     nachgeschlagen.
//!   * *Ohne Dokumentnamen kein Zitat.* Die Anfuehrung ist die Ankuendigung "hier wird
//!     zitiert"; fehlt sie, bleibt der Dokumentname die einzige. Fundstellen ohne
//!     beides zaehlt der Riegel, aber er nennt sie nicht einzeln -- es waeren Dutzende,
//!     und keine von ihnen traegt ein Ziel.
//!   * *Ein einzelnes Zeichen.* Steht hinter dem Schluesselwort ein einzelner
//!     Buchstabe, ist es in diesem Vorhaben ein Formelzeichen oder ein Platzhalter.
//!     Gemessen und nicht vorsorglich: `rueckstand.md` sagt an einer Stelle sinngemaess,
//!     etwas habe dort unter einer bestimmten Ueberschrift gestanden und sei heute nicht
//!     mehr aufgefuehrt -- eine Aussage **ueber** ein Zitat und keines.
//!   * *Das Zeilenende.* Der Name endet spaetestens dort, wo seine Zeile endet --
//!     Paket 0105. Ohne diese vierte Grenze laeuft er ueber den Umbruch in den naechsten
//!     Halbsatz hinein, denn der Absatzbau macht aus dem Umbruch ein Leerzeichen wie
//!     jedes andere. Sie hat einen Preis, und er steht unten in einem eigenen Abschnitt
//!     ausgeschrieben.
//!
//! ## Die Satzgrenze nach links -- Paket 0079, zweiter Teil
//!
//! Die drei Grenzen oben genuegen nicht, und das ist gemessen: Am 2026-09-05 wurde der
//! Riegel rot an einem Satz in `rueckstand.md`, in dem etwas "einen \101bsa\164z
//! Rechtfertigung und sechs zusaetzliche Baulaeufe gekostet" hat -- das Schluesselwort
//! ist hier maskiert (`\101` ist `A`, `\164` ist `t`), weil dieser Absatz sonst genau
//! die Stelle waere, von der er handelt, und den Riegel an sich selbst rot machte. Das
//! Schluesselwort
//! steht da, der Name dahinter beginnt gross -- im Deutschen tut das jedes Hauptwort --,
//! und der naechstgelegene Dokumentname im Absatz stand **zwei Saetze weiter oben** und
//! handelte von etwas anderem. Der Riegel schlug einen halben Nebensatz als Ueberschrift
//! nach und meldete einen Befund an einer Stelle, an der nichts kaputt ist.
//!
//! **Die Regel dagegen ist keine neue, sondern die, die hier schon zweimal steht: Ein
//! Verweis und sein Ziel stehen im selben Satz.** Bedingung 1 sucht so nach links
//! (`satzanfang_vor`), Paket 0086 sucht so nach rechts (`satzende_nach`). Fuer die Form
//! **ohne** Anfuehrung gilt sie ab jetzt auch nach links. Der Grund steht schon im
//! zweiten Spiegelstrich oben und wird hier nur zu Ende gedacht: Die Anfuehrung ist die
//! Ankuendigung "hier wird zitiert"; fehlt sie, ist der Dokumentname die einzige, die
//! bleibt -- und eine Ankuendigung zwei Saetze weiter oben kuendigt nichts an.
//!
//! **Fuer die Form mit Anfuehrung aendert sich nichts.** Sie sucht weiter ueber den
//! ganzen Absatz, und das muss sie: Der Fall aus Paket 0067 -- `schranken_probe.cpp`,
//! Dateiname vier Zeilen ueber der Ueberschrift -- ist die gemessene Fassung und faellt
//! sonst. Ein Fall in `SATZFAELLE` haelt genau das fest; wer die Schranke unbedingt
//! macht, macht ihn rot.
//!
//! **Was sie kostet, gemessen am 2026-09-05** -- derselbe Stand, derselbe Baum, einmal
//! mit und einmal ohne die Schranke an der Aufrufstelle:
//!
//! | | ohne Schranke | mit Schranke |
//! |---|---|---|
//! | Zitate | 36 | 35 |
//! | davon aufgeloest | 35 | 35 |
//! | uebergangene Fundstellen | 56 | 47 |
//! | Fundstellen ohne Dokumentnamen | 44 | 54 |
//! | Befunde | 1 (falsch) | 0 |
//!
//! **Kein einziges aufgeloestes Zitat geht verloren** -- 35 bleiben 35. Was faellt, ist
//! der falsche Befund und neun uebergangene Fundstellen; alle neun sind
//! Gliederungsziffern und trugen ohnehin keinen Wortlaut. Sie verschwinden nicht,
//! sondern wechseln die Zahl: 44 plus neun plus der Befund sind die 54. Die Richtung
//! des Fehlers ist dieselbe wie bei `satzanfang_vor` und aus demselben Grund gewaehlt:
//! Zu streng laesst eine Stelle als "ohne Ziel" durch, zu nachsichtig bindet sie an die
//! falsche Datei. Nur das zweite macht etwas kaputt.
//!
//! **Was die Tabelle `SATZFAELLE` nicht abdeckt, und was es stattdessen tut.** Sie misst
//! `suchuntergrenze`, nicht die Aufrufstelle. Wer dort die Null von Hand einsetzt, laesst
//! den Selbsttest gruen -- gemessen. Der Bestand faengt es: Genau dieser Mutant wird am
//! 2026-09-05 rot an `rueckstand.md`. Beides zusammen deckt die Regel, keines allein.
//!
//! ## Der Name am Zeilenende -- Paket 0105
//!
//! Die Form **ohne** Anfuehrung hat eine Grenze, die die Form mit Anfuehrung nicht hat:
//! Ihren Namen begrenzt kein Zeichen, das jemand eigens hinschreibt, sondern erst das
//! naechste Satzzeichen. Gesucht wird aber **je Absatz**, und ein Absatz ist ein Block
//! gleichartiger Zeilen, zu einer Zeichenkette zusammengezogen -- der Umbruch wird darin
//! zu einem Leerzeichen wie jedes andere. Steht am Zeilenende kein Satzzeichen, laeuft
//! der Name in die naechste Zeile hinein, und der Riegel schlaegt einen halben Nebensatz
//! als Ueberschrift nach.
//!
//! **Gemessen und nicht gedacht.** Eine richtige Belegstelle in `rueckstand.md`, deren
//! Satz nach dem Namen umbricht, macht die Fassung von vorher rot und nennt als gesuchte
//! Ueberschrift den Namen samt der Fortsetzung. Richtet man dieselbe Fassung auf die
//! Wurzel des Repos, kommen fuenf Stellen dieser Art dazu; sie liegen heute in
//! `aufgaben/` und damit ausserhalb des Pruefwegs. Der Fehler ist mit Paket 0079
//! entstanden und war dort in keiner Bedingung genannt.
//!
//! **Die Regel: der Name endet spaetestens dort, wo seine Zeile endet.** Entschieden
//! wird an einer benannten Eigenschaft und nicht an einer Liste von Faellen -- gefragt
//! wird `Absatz::zeile_bei`, dieselbe Herkunftsliste, aus der auch die Meldung ihre
//! Nummer nimmt. Sie ist damit die einzige Stelle, an der der Umbruch im
//! zusammengezogenen Wortlaut ueberhaupt noch zu sehen ist.
//!
//! **Die Grenze ist die Zeile des Namens, nicht die des Schluesselworts.** Steht das
//! Wort am Zeilenende und der Name darunter, ist der Name trotzdem einer. Wer die Grenze
//! am Schluesselwort festmacht, findet dort gar keine Fundstelle mehr -- ein eigener
//! Fall in `ZITATFAELLE` haelt genau das fest.
//!
//! **Warum nicht der andere Weg.** Den Namen zu kuerzen, solange er sich nicht
//! nachschlagen laesst, faenge auch die im Zitat umgebrochene Ueberschrift -- macht aber
//! aus dem Vergleich eine Suche und braucht dafuer eine Untergrenze in Zeichen. Eine
//! geratene Schwelle in einem Messgeraet ist genau das, was dieser Kopf bei der Suche
//! nach links schon einmal verworfen hat, und hier laesst sie sich noch weniger messen:
//! Je kuerzer der gepruefte Anfang, desto mehr Umbenennungen ueberleben ihn.
//!
//! **Was die Regel kostet, ausgeschrieben.** Eine Ueberschrift, die im Zitat ueber zwei
//! Zeilen umgebrochen ist, wird nur noch bis zum Umbruch geprueft. Sie loest weiter auf,
//! denn verglichen wird ohnehin der Anfang -- aber der gepruefte Teil ist kuerzer, und
//! eine Umbenennung hinter dem Umbruch faellt nicht mehr auf. Die Richtung ist gewaehlt
//! und nicht uebersehen: Der Wortlaut bis zum Umbruch ist der einzige, von dem feststeht,
//! dass er zum Zitat gehoert. Ein vierter Fall in `ZITATFAELLE` schreibt diesen Preis aus.
//!
//! **Was sie nicht lockert -- und dort sitzt die Gefahr.** Sie kuerzt den Namen, sie
//! verzeiht ihn nicht: Was die Zieldatei nicht fuehrt, bleibt ein Befund. Gemessen an
//! derselben Stelle mit einer Ueberschrift, die es nicht gibt -- vorher rot, nachher rot,
//! und die Meldung nennt jetzt den gekuerzten Namen statt des halben Nebensatzes.
//!
//! **Was sie auf dem Bestand kostet: nichts.** Derselbe Baum, dieselbe Stunde, einmal
//! ohne und einmal mit der Regel -- 36 Zitate, 36 aufgeloest, 47 uebergangene
//! Fundstellen auf beiden Seiten, und die Aufzaehlung der uebergangenen Stellen ist
//! zeichengleich. Sie greift nur dort, wo vorher ein Umbruch mitgelesen wurde.
//!
//! **Dass die vier Faelle die Regel wirklich decken, ist mit zwei Mutanten gemessen**
//! und nicht behauptet -- je Haelfte der Regel einer, und kein Fall reisst bei beiden:
//! Faellt die Zeilengrenze ganz weg, reissen drei der vier (3 von 51 Faellen des ganzen
//! Selbsttests); haengt sie an der Zeile des Schluesselworts statt an der des Namens,
//! reisst allein der uebrige (1 von 51). Die 47 Faelle der anderen vier Tabellen bleiben
//! in beiden Laeufen gruen.
//!
//! ## Das Schluesselwort mit Abstand, der Name rechts -- Paket 0086
//!
//! Die dritte Belegstelle aus Paket 0034 nennt ihr Schluesselwort, laesst dann aber
//! **fuenf Woerter** folgen, ehe die Anfuehrung beginnt -- der Bau ist "die
//! <Schluesselwort> der Tabelle sagt es selbst:", und erst danach kommt der zitierte
//! Wortlaut. Und ihr Dokumentname steht **rechts** vom Zitat, in der Klammer dahinter.
//! Bis zum 2026-09-05 fiel sie an beidem durch und zaehlte nirgends, auch nicht als
//! uebergangen. Seither faengt der Riegel sie.
//!
//! **Dass keine der beiden Lockerungen allein genuegt, ist gemessen und nicht
//! nachgesprochen.** Am selben Baum, am 2026-09-05, je ein Mutant:
//!
//!     Fassung                   Zitate  aufgeloest  uebergangen
//!     keine von beiden              33          33           58
//!     nur der Wortabstand           33          33           59
//!     nur die Suche nach rechts     33          33           58
//!     beide                         34          34           58
//!
//! Der Wortabstand macht die Stelle **sichtbar** -- sie wandert unter die uebergangenen
//! Fundstellen, weil ihr Absatz links keinen Dokumentnamen nennt. Die Suche nach rechts
//! macht sie **aufloesbar**. Allein traegt keine ein einziges Zitat; die Rechtssuche
//! allein aendert nicht eine Zahl, und das ist zugleich der Beleg, dass sie keine
//! vorhandene Zuordnung umhaengt. Zusammen sind es genau ein Zitat mehr und keine
//! Fundstelle mehr.
//!
//! **Drei Riegel halten die Lockerung eng, und jeder hat seinen eigenen Nachweis.**
//! Ohne sie wird der Riegel rot, wo nichts kaputt ist -- der Einwand, an dem schon 0047
//! haengt, gilt unveraendert:
//!
//!   1. *Nur ankuendigende Anfuehrungszeichen.* Mit Abstand zaehlen die typografischen
//!      Anfuehrungen und die geklammerte Form, nicht Gegenstrich, Sternchen, einfaches
//!      oder gerades Anfuehrungszeichen. Gemessen am 2026-09-06 gegen den Stand
//!      `5d5e2d6` mit dem Mutanten `ohne-marken-rein`: ohne diese Trennung faengt der
//!      Riegel **elf Stellen zu Unrecht, zehn davon in seinem eigenen Quelltext** --
//!      51 statt 40 Zitate, weiterhin nur 40 aufgeloest, 59 statt 47 Fundstellen. Die
//!      zehn liegen zu zweit in diesem Kopfkommentar, einmal in `SATZFAELLE` und
//!      siebenmal in `ZITATFAELLE`; die elfte steht in `parameter.toml`.
//!
//!      **Diese Zahl zaehlt sich selbst mit, und genau daran ist ihre Vorgaengerin
//!      falsch geworden.** Sie stand hier als Fuenf, waehrend eine der beiden Stellen
//!      im Kopfkommentar erst danach entstand -- ein spaeteres Paket trug einen Satz
//!      nach, und die Sechs, die daraus wurde, hat niemand nachgemessen. Wer hier
//!      schreibt, veraendert moeglicherweise die Zahl, die er schreibt; sie ist
//!      nachzumessen und nicht fortzuschreiben. Der Aufruf, der sie liefert, steht
//!      unter `Klammer::kuendigt_an`, dort auch die Begruendung.
//!   2. *Das Satzende.* Es beendet die Suche, dieselbe Regel wie bei der Suche nach
//!      links. Nachgewiesen an Fall 3 in `ABSTANDSFAELLE`.
//!   3. *Ein zweites Schluesselwort.* Die Anfuehrung gehoert dem naeheren. Der Bestand
//!      misst diesen Riegel heute **nicht** -- er fuehrt keine Stelle dieser Bauart --,
//!      Fall 5 in `ABSTANDSFAELLE` baut sie eigens.
//!
//! **Die Schwelle fuenf ist gemessen.** Bei vier bleibt die Stelle ungefangen (58
//! Fundstellen wie ohne die Lockerung), bei fuenf faellt sie an (59); sechs und acht
//! aendern gegenueber fuenf nichts mehr -- der Bestand fuehrt zwischen fuenf und acht
//! Woertern keine weitere Form. Gewaehlt ist deshalb der kleinste Wert, der die
//! gemessene Stelle traegt, und nicht der groesste, der noch nichts kaputt macht.
//!
//! **Wer gewinnt, wenn links und rechts ein Name steht: der linke.** Die Frage ist
//! nicht offen gelassen, sondern zugunsten des Gemessenen entschieden -- die Linksregel
//! traegt einen Nachweis (das franzoesische Zitat in `lizenzbefund-reihen.md`), die
//! Rechtssuche keinen. Sie laeuft deshalb nur, wenn links nichts steht, und nur fuer
//! die Form **mit** Anfuehrung: ohne sie hat das Zitat keinen bestimmten rechten Rand.
//! Ihre Grenze ist das Satzende, und sie ist gemessen -- heute allein an Fall 6 in
//! `ABSTANDSFAELLE`. Der Mutant `rechts-ohne-satzgrenze-rein` laesst ihn reissen und
//! bricht mit Code 2 ab: rechts erwartet war kein Dateiname, gefunden wurde `spiel.md`.
//!
//! **Der Bestand misst diese Grenze nicht mehr mit.** Am 2026-09-06, gegen den Stand
//! `5d5e2d6`, nennt derselbe Mutant genau dieselben drei Zahlen wie der unveraenderte
//! Riegel -- 40 Zitate, 40 aufgeloest, 47 uebergangene Fundstellen, vorher wie nachher
//! die Summe 87. Bis hierher stand an dieser Stelle, ohne die Grenze binde eine
//! uebergangene Fundstelle einen weit entfernten Dateinamen an sich und werde zu
//! Unrecht rot; das ist am 2026-09-06 am Baum nicht mehr zu sehen. Was sich zwischen
//! den beiden Tagen bewegt hat, ist nicht nachgehalten -- der Fall in der Tabelle
//! traegt die Regel seither allein.
//!
//! **Was weiterhin ungefangen bleibt, damit die Zahlen unten niemand fuer
//! Vollstaendigkeit haelt:** ein Dokumentname rechts vom Zitat jenseits des Satzendes;
//! ein Name rechts bei der Form ohne Anfuehrung; und eine Anfuehrung, die mehr als
//! fuenf Woerter hinter ihrem Schluesselwort steht.
//!
//! ## Das tote Ziel -- Paket 0083
//!
//! Bis zum 2026-09-05 trug die Sorte "Ziel ausserhalb des Bestands" zwei Faelle, die
//! nichts miteinander zu tun haben. Der eine ist ein Verweis auf einen Pruefbericht
//! unter `befunde/` -- richtig uebergangen, denn dieser Ordner wird mit Absicht nicht
//! gelesen. Der andere ist ein Name, den es nirgends gibt -- also genau der tote
//! Verweis, gegen den dieser Riegel geschrieben ist. Beide waren gruen.
//!
//! **Was daran gefaehrlich ist, ist gemessen und nicht befuerchtet.** Am 2026-09-04 ist
//! der Riegel gegen eine Kopie der Vorgaben ohne `spiel.md` gelaufen: Statt 21 Zitaten
//! wurden 9 geprueft, zwoelf wanderten von einer Sekunde auf die andere unter die
//! uebergangenen Fundstellen, die beiden gemeldeten Zahlen blieben gleich, und der Test
//! bestand. Ein Riegel, dessen Abdeckung um die Haelfte fallen kann, ohne dass er es
//! sagt, macht jeden gruenen Lauf wertlos -- auch die der anderen Bedingungen.
//!
//! **Die Trennung.** Steht der naechstgelegene Name nicht im Bestand, wird gefragt, wo
//! er sonst liegt. Drei Antworten, und nur die letzte ist ein Befund:
//!
//!   1. Der Name **spricht seinen Ort selbst aus** -- er beginnt mit einem
//!      Schraegstrich oder steigt mit zwei Punkten aus der Wurzel heraus. Uebergangen.
//!   2. Der Name **zeigt in einen mit Absicht ungelesenen Ordner**, und unter dem
//!      genannten Pfad liegt dort auch eine Datei. Uebergangen, Meldung nennt den Namen.
//!   3. Sonst. Befund, Lauf rot.
//!
//! ### Die Ortsfrage wird am Ort entschieden, nicht am Namen -- Ruecklauf 2026-09-05
//!
//! Die erste Fassung dieser Trennung hat Fall 2 anders gestellt, naemlich als
//! *"traegt irgendwo unter beiden Wurzeln eine Datei diesen Basisnamen?"*. Sie ist
//! daran gescheitert, und der Grund ist der Bestand selbst: `bau/kp0010/quelle/` und
//! `bau/kp0027r3/quelle/` tragen vollstaendige Abschriften des Quellbaums samt der
//! Vorgaben, `befunde/messung-0069/baum/` eine weitere. Ein Name, den es nicht mehr
//! gibt, hat dort fast immer noch einen Zwilling -- **153 von 159 Namen des
//! Zielbestands**, gemessen am 2026-09-04. Die Namensfrage beantwortete sich damit
//! fast immer mit Ja, und der tote Verweis kam als uebergangener durch.
//!
//! Das war kein Randfall, sondern der Regelfall des Betriebs: `bau/` legt der Baulauf
//! selbst an, und geprueft wird **nach** dem Bauen. Der Rotnachweis der ersten Fassung
//! trug nur auf einer Kopie ohne Bauverzeichnis -- also auf einem Baum, auf dem der
//! Riegel nie laeuft. Gemessen mit derselben Binaerdatei, Vorgaben ohne `spiel.md`:
//! Arbeitsbaum mit `bau/` gruen und null tote Ziele, versionierte Kopie ohne `bau/`
//! rot und vierzehn.
//!
//! Seither lautet Fall 2 als **Ortsfrage**: Nennt der Verweis selbst einen ungelesenen
//! Ordner als einen seiner Pfadteile, und liegt unter diesem Pfad dort auch eine Datei?
//! Beides zusammen, und beides ist noetig. Der Ort allein hiesse, jeden erfundenen
//! Namen mit dem Vorsatz `befunde/` zu uebergehen; die Datei allein ist die Namensfrage
//! von eben. Eingesammelt werden dafuer die **Pfade** unter `bau/` und `befunde/` statt
//! der blossen Namen -- eine laengere Liste, die dafuer die gestellte Frage beantwortet.
//!
//! **Und der Preis, ausgeschrieben: Ein Verweis, der seinen Ordner nicht bei sich
//! traegt, gilt als tot.** Nennt ein Zitat blosses `pruefung-0009-....md` ohne den
//! Vorsatz `befunde/`, wird der Lauf rot, obwohl die Datei dort liegt. Das ist die
//! strenge der beiden Richtungen, und sie ist mit Absicht gewaehlt: Die nachsichtige
//! kostet genau die Abdeckung, um derentwillen dieses Paket angelegt wurde -- jeder
//! Name mit einem Zwilling unter `bau/` waere wieder unfaengbar. Der Preis der strengen
//! ist ein Zitat, das seinen Vorsatz ergaenzen muss, also eine Berichtigung von zwei
//! Woertern. Er wird ausserdem laut bezahlt: Die Meldung nennt den genannten Namen und
//! sagt, dass es ihn unter keiner der beiden Wurzeln gibt. Am 2026-09-05 traegt der
//! Bestand **eine** Fundstelle des zweiten Falls, und sie nennt ihren Ordner mit.
//!
//! Gelesen wird aus diesen Ordnern weiterhin keine einzige Datei; eine Zeilennummer in
//! einem Bericht bleibt ein Messwert vom Tag der Messung, und eine Gliederungsmarke
//! daraus wird nirgends nachgeschlagen. Versteckte Ordner (`.git`, `.claude`) bleiben
//! ganz aussen vor, und zwar aus einem anderen Grund: Dort liegt Maschinerie, kein
//! Dokument, das ein Zitat nennen koennte -- und der Baum unter `.git` ist der groesste
//! des Vorhabens.
//!
//! **Die Frage nach `aufgaben/`, die der Zuschnitt offen laesst, und meine Antwort:
//! nein, dieser Ordner wird nicht wie `befunde/` behandelt.** Der Grund ist nicht
//! Bequemlichkeit, sondern dass die beiden auf verschiedenen Seiten stehen. Ungelesen
//! ist `aufgaben/` nur als **zitierende** Menge -- ein Arbeitspaket beschreibt den
//! Stand, als es zugeschnitten wurde, und seine Verweise nachzufuehren faelschte es.
//! Als **Ziel** steht es heute im Bestand und wird nachgeschlagen. Es dort
//! herauszunehmen hiesse, Zitate, die heute aufloesen, kuenftig zu uebergehen -- eine
//! stille Verkleinerung der Abdeckung, also genau das, wogegen dieses Paket
//! geschrieben ist. Wer die Ordnerliste `UNGELESENE_ORDNER` erweitert, nimmt Ziele aus
//! dem Bestand und muss diese Rechnung aufmachen.
//!
//! **Was die Trennung kostet, ausgeschrieben.** Sie gilt fuer beide Zitatformen, auch
//! fuer die ohne Anfuehrung aus Paket 0079. Dort ist die Fundstelle mit einem
//! Wahrscheinlichkeitsurteil gefunden, und bisher hat das Nachschlagen des Ziels sie
//! stillschweigend bestaetigt: Was nirgends hinzeigte, verschwand unter den
//! uebergangenen Fundstellen. Kuenftig wird es rot. Das ist die richtige Richtung --
//! ein Absatz, der einen Dateinamen nennt, den es nicht gibt, ist auch dann ein Befund,
//! wenn das Zitat daneben keines war -- aber es ist eine neue Quelle von Rot, und sie
//! gehoert benannt, bevor sie jemanden ueberrascht. Am 2026-09-05 gibt es im ganzen
//! Bestand **eine** Fundstelle dieser Sorte, und sie faellt unter den zweiten Fall.
//!
//! ## Die Untergrenze -- Paket 0083, zweiter Teil
//!
//! Die Trennung oben faengt den Rueckgang auf der **Zielseite**: Faellt eine Zieldatei
//! weg, wird der Lauf rot. Sie faengt nicht den Rueckgang auf der **Fundseite** -- hoert
//! eine Menge zitierender Dateien auf, gelesen zu werden, entsteht kein Befund, die
//! beiden Zahlen bleiben gleich und nur ihre Hoehe faellt. Dagegen steht eine
//! Untergrenze im Quelltext; ihre Zahl, ihre Herkunft und was sie ausdruecklich **nicht**
//! faengt, stehen bei `AUFGELOEST_MINDESTENS`.
//!
//! ## Warum der Riegel seinen eigenen Quelltext mitliest
//!
//! Er tut es, und das ist Absicht: Nur so laesst sich der Rotnachweis fuehren, ohne
//! eine fremde Datei anzufassen. Eine eingefuegte Belegstelle in diesem Kommentar
//! macht ihn rot; dieselbe Zeile wieder heraus macht ihn gruen.
//!
//! ## Wenn er nichts gesehen hat
//!
//! Dann bricht er ab, statt gruen zu melden. Ein Riegel ohne Gegenstand ist kein
//! gruener Lauf -- dieselbe Lehre wie beim Warnsatz-Schlussriegel in
//! `werkzeugkette.cmake`, der bis zum 2026-09-04 "0 uebersetzende Ziele geprueft,
//! alle mit Warnsatz" melden konnte und dabei Code 0 gab.
//!
//! ## Aufruf
//!
//!     belegstellen_riegel <wurzel-des-vorhabens> [<wurzel-der-vorgaben>]
//!
//! Die Wurzel kommt von CMake und steht nicht im Programm. Ein fest eingebauter Pfad
//! liefe nur auf dem Rechner, auf dem er gebaut wurde.
//!
//! Die Wurzel der Vorgaben braucht erst Bedingung 2 -- dort liegen die Zieldateien der
//! meisten Zitate. Sie ist **wahlfrei**, und das ist eine Entscheidung des Pakets 0067
//! und keine Bequemlichkeit: Die `CMakeLists.txt` daneben gehoert Paket 0059 und steht
//! nicht in der Dateiliste von 0067. Wird kein zweites Argument uebergeben, wird die
//! Vorgabenwurzel aus der ersten abgeleitet -- Geschwisterverzeichnis `specs` mit
//! demselben Vorhabensnamen. Das ist kein eingebauter Pfad: Jeder Teil davon stammt
//! aus dem Argument, das CMake setzt. Findet sich dort kein Verzeichnis, bricht der
//! Riegel ab (Code 2), statt jedes Zitat in die Vorgaben als "Ziel ausserhalb des
//! Bestands" durchzuwinken -- das waere ein gruener Lauf ueber nichts.
//!
//! Rueckgabe: 0 kein Befund, 1 Befunde gefunden, 2 der Riegel selbst taugt nicht --
//! Aufruf- oder Lesefehler, ein verfehlter Fall des Selbsttests, kein einziges
//! gefundenes Zitat oder eine unterschrittene Untergrenze. Die Trennung ist die
//! zwischen "im Gemessenen steckt ein Fehler" und "das Messgeraet misst nicht".
//!
//! Vorgaben: T4 (kein Gleitkomma -- hier trivial, es wird nichts gerechnet),
//! ADR 0011 (C++20, g++). Kein Zeiger, kein rohes Feld, jeder Zugriff ueber Index.

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace {

namespace fs = std::filesystem;

// ---------------------------------------------------------------------------
// Die Marken
// ---------------------------------------------------------------------------

/// Die zugelassenen Endungen, als ein Streifen mit Trennpunkten statt als Liste.
/// Gesucht wird darin nach der Endung samt beiden Punkten, damit `md` nicht in
/// `cmd` trifft. Bewusst kurz: Was hier nicht steht, ist kein Verweisziel dieses
/// Vorhabens.
constexpr std::string_view ENDUNGEN = ".md.toml.cpp.hpp.txt.cmake.py.rs.";

/// Verzeichnisnamen, deren **Inhalt** nicht gelesen wird. Ihre Dateinamen werden seit
/// Paket 0083 trotzdem eingesammelt -- der Unterschied zwischen "gibt es dort" und "gibt
/// es nirgends" ist genau die Trennung, um derentwillen dieses Paket existiert.
/// Begruendung im Kopf.
constexpr std::array<std::string_view, 2> UNGELESENE_ORDNER = {"bau", "befunde"};

/// Die Zeichen, aus denen ein Dateiname bestehen darf. Absichtlich ohne Akzent- und
/// Anfuehrungszeichen: Ein Verweis steht regelmaessig zwischen Akzenten, und die
/// sollen den Namen begrenzen statt Teil von ihm zu werden.
bool ist_pfadzeichen(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
           || c == '.' || c == '_' || c == '-' || c == '/';
}

bool ist_ziffer(char c) { return c >= '0' && c <= '9'; }

// ---------------------------------------------------------------------------
// Die zwei Muster
// ---------------------------------------------------------------------------
//
// Aus dem Arbeitspaket, dort in der Schreibweise der Textsuche -- hier absichtlich
// nicht abgeschrieben, sondern beschrieben, weil eine abgeschriebene Musterzeile in
// diesem Kommentar sich selbst faengt:
//
//   * das Wort fuer eine Zeile, ein `n` darf folgen, dann ein Leerzeichen, dann
//     mindestens zwei Ziffern;
//   * der Buchstabe `Z` mit Punkt, ein Leerzeichen darf folgen, dann mindestens zwei
//     Ziffern.
//
// Von Hand gebaut statt mit `<regex>`: zwei Muster dieser Groesse sind zwanzig Zeilen,
// und `<regex>` zoege eine Maschine herein, deren Verhalten niemand hier nachliest.
// Die Vorgabe aus dem Rollenauftrag -- feste Groessen, Indexpruefung an jeder Grenze --
// laesst sich so ausserdem einhalten.
//
// Die Obergrenze von vier Ziffern aus der Suchschreibweise ist keine: Ein Muster ohne
// Anker trifft in einer fuenfstelligen Zahl ebenso. Geprueft wird deshalb **mindestens
// zwei Ziffern**, und die Laenge laeuft bis zum Ende des Ziffernlaufs -- sonst stuende
// in der Meldung eine abgeschnittene Zahl.

constexpr std::size_t ZIFFERN_MINDESTENS = 2;

/// Wie viele Ziffern ab `i` stehen.
std::size_t ziffernlauf(std::string_view zeile, std::size_t i) {
    std::size_t d = 0;
    while (i + d < zeile.size() && ist_ziffer(zeile[i + d])) {
        ++d;
    }
    return d;
}

/// Laenge des Treffers, der bei `i` **beginnt** -- oder 0, wenn dort keiner beginnt.
std::size_t musterlaenge(std::string_view zeile, std::size_t i) {
    // Zusammengesetzt statt als Literal, damit diese Uebersetzungseinheit das Muster
    // nicht selbst als Text traegt.
    constexpr std::string_view WORT = "Zeil\145";

    if (zeile.size() - i >= WORT.size() && zeile.substr(i, WORT.size()) == WORT) {
        std::size_t j = i + WORT.size();
        if (j < zeile.size() && zeile[j] == 'n') {
            ++j;
        }
        if (j < zeile.size() && zeile[j] == ' ') {
            ++j;
            const std::size_t d = ziffernlauf(zeile, j);
            if (d >= ZIFFERN_MINDESTENS) {
                return (j + d) - i;
            }
        }
        return 0;
    }

    if (zeile[i] == 'Z' && i + 1 < zeile.size() && zeile[i + 1] == '.') {
        std::size_t j = i + 2;
        if (j < zeile.size() && zeile[j] == ' ') {
            ++j;
        }
        const std::size_t d = ziffernlauf(zeile, j);
        if (d >= ZIFFERN_MINDESTENS) {
            return (j + d) - i;
        }
    }

    return 0;
}

// ---------------------------------------------------------------------------
// Der Dateiname links vom Treffer
// ---------------------------------------------------------------------------

/// Der letzte Punkt trennt die Endung -- aber nur, wenn danach kein Schraegstrich
/// mehr kommt. `a.b/c` hat keine Endung, `daten/adressen.md` hat `.md`.
bool endung_zugelassen(std::string_view wort) {
    const std::size_t punkt = wort.rfind('.');
    if (punkt == std::string_view::npos) {
        return false;
    }
    const std::string_view endung = wort.substr(punkt);
    if (endung.find('/') != std::string_view::npos) {
        return false;
    }
    const std::string gesucht = std::string(endung) + ".";
    return ENDUNGEN.find(gesucht) != std::string_view::npos;
}

/// Wo der Satz beginnt, in dem die Stelle `bis` liegt -- die Untergrenze der Suche
/// nach links. Begruendung im Kopf, dort im vierten Teil.
///
/// Ohne Anfuehrung genannt und nicht als Zitat: Bedingung 2 dieses Programms faende
/// eine zitierte Ueberschrift im eigenen Quelltext und fuehrte sie fortan unter den
/// uebergangenen Fundstellen -- eine Zahl, die Paket 0067 gehoert.
///
/// Ein Satzende ist ein Punkt, ein Ausrufe- oder ein Fragezeichen mit Leerraum
/// dahinter. Der Leerraum ist der tragende Teil der Bedingung und keine Feinheit: Ein
/// Punkt **ohne** ihn ist regelmaessig die Endung selbst, und ein Satzende mitten in
/// `technik.md` beendete die Suche vor jedem Fund.
///
/// Die Regel ist absichtlich zu streng statt zu nachsichtig: Eine Abkuerzung mit Punkt
/// beendet den Satz hier ebenfalls. Der Riegel sucht dann kuerzer als noetig und laesst
/// eine Stelle durch -- das ist die Richtung, in der ein Fehler nichts kaputt macht.
std::size_t satzanfang_vor(std::string_view zeile, std::size_t bis) {
    std::size_t anfang = 0;
    for (std::size_t k = 0; k + 1 < bis; ++k) {
        const char c = zeile[k];
        if (c != '.' && c != '!' && c != '?') {
            continue;
        }
        if (zeile[k + 1] == ' ' || zeile[k + 1] == '\t') {
            anfang = k + 2;
        }
    }
    return anfang;
}

/// Wo der Satz endet, in dem die Stelle `ab` liegt -- die Obergrenze der Suche nach
/// rechts (Paket 0086). Spiegelbild von `satzanfang_vor`, mit derselben Regel und
/// derselben Begruendung: Ein Verweis und sein Ziel stehen im selben Satz.
std::size_t satzende_nach(std::string_view text, std::size_t ab) {
    for (std::size_t k = ab; k + 1 < text.size(); ++k) {
        const char c = text[k];
        if (c != '.' && c != '!' && c != '?') {
            continue;
        }
        if (text[k + 1] == ' ' || text[k + 1] == '\t') {
            return k + 1;
        }
    }
    return text.size();
}

/// Der **naechstgelegene** Dateiname links von `bis` auf derselben Zeile.
///
/// Gesucht wird wortweise nach links bis zum Anfang des Satzes, nicht ueber genau ein
/// Wort. Der erste Fund gewinnt; ueber ihn hinweg wird nicht weitergesucht. Beides ist
/// im Kopf begruendet und beides traegt einen Fall in `NAMENSFAELLE`.
///
/// Leer, wenn im Satz links kein Wort mit zugelassener Endung steht.
std::string dateiname_davor(std::string_view zeile, std::size_t bis) {
    const std::size_t untergrenze = satzanfang_vor(zeile, bis);
    std::size_t grenze = bis;
    while (grenze > untergrenze) {
        // Erst ueber alles, was kein Pfadzeichen ist (Leerzeichen, Akzent,
        // Doppelpunkt), dann ueber das Wort selbst.
        std::size_t ende = grenze;
        while (ende > untergrenze && !ist_pfadzeichen(zeile[ende - 1])) {
            --ende;
        }
        std::size_t anfang = ende;
        while (anfang > untergrenze && ist_pfadzeichen(zeile[anfang - 1])) {
            --anfang;
        }
        if (anfang == ende) {
            return {};
        }

        std::string_view wort = zeile.substr(anfang, ende - anfang);

        // Ein Satzpunkt am Ende gehoert nicht zum Namen: `siehe technik.md.` traegt
        // die Endung `.md`, nicht `.md.`. Dasselbe fuer den Schraegstrich eines
        // Verzeichnisses.
        while (!wort.empty() && (wort.back() == '.' || wort.back() == '/')) {
            wort.remove_suffix(1);
        }
        if (endung_zugelassen(wort)) {
            return std::string(wort);
        }
        grenze = anfang;
    }
    return {};
}

std::string_view basisname(std::string_view pfad) {
    const std::size_t strich = pfad.rfind('/');
    if (strich == std::string_view::npos) {
        return pfad;
    }
    return pfad.substr(strich + 1);
}

/// Was eine Zeile hergibt: wo das Muster traf, wie lang der Treffer ist und welchen
/// Dateinamen die Zeile links davon nennt.
struct Zeilenfund {
    bool getroffen = false;
    std::size_t anfang = 0;
    std::size_t laenge = 0;
    std::string ziel;
};

/// Der naechste Fund ab `von`. Ein eigener Aufruf und keine Schleife im Leser, damit
/// der Selbsttest unten **denselben** Weg misst wie der Lauf ueber den Bestand. Eine
/// zweite, nachgebaute Zerlegung im Test hiesse, zwei Fassungen gegeneinander zu
/// pruefen, von denen nur eine im Ernstfall laeuft.
Zeilenfund fund_ab(std::string_view zeile, std::size_t von) {
    for (std::size_t i = von; i < zeile.size(); ++i) {
        const std::size_t laenge = musterlaenge(zeile, i);
        if (laenge == 0) {
            continue;
        }
        return Zeilenfund{true, i, laenge, dateiname_davor(zeile, i)};
    }
    return {};
}

// ---------------------------------------------------------------------------
// Der Selbsttest zur Suche nach links -- Paket 0073
// ---------------------------------------------------------------------------
//
// Warum als Tabelle im Programm und nicht als zweiter Testfall daneben: Die
// `CMakeLists.txt` gehoert Paket 0059 und steht nicht in der Dateiliste von 0073.
// Ein zweites `add_test` waere ein Schreibzugriff auf fremdes Gebiet. Die Tabelle
// hier laeuft dafuer bei **jedem** Aufruf mit -- ein Weg, der nicht vergessen werden
// kann, weil er kein eigener Befehl ist.
//
// Jede Zeile traegt ihre Herkunft. **Drei der acht** sind im Bestand gemessen und nicht
// erfunden -- die Faelle 1, 2 und 4; ihre genannte Stelle traegt den Wortlaut heute
// wirklich, am 2026-09-05 einzeln nachgeschlagen. Vier halten je eine Entscheidung
// fest, die sonst niemand nachlesen koennte, und der achte ist aus einem echten
// Arbeitspaket abgewandelt.
//
// **Der siebte Herkunftshinweis ist historisch, und das steht dort auch.** Bis zum
// 2026-09-05 sagte dieser Kopf "vier der acht", und Fall 7 nannte dafuer eine Datei,
// die seinen Wortlaut seit dem 2026-09-04 nicht mehr traegt. Die Zahl war damit
// richtig gezaehlt und falsch belegt. Berichtigt ist beides zusammen: die Zahl **und**
// die Angabe daneben -- nur die Zahl zu senken haette sie richtig gemacht und die
// Adresse weiter falsch gelassen.
//
// **Warum die Musterwoerter maskiert sind.** Der Riegel liest seinen eigenen
// Quelltext -- eine ausgeschriebene Beispielzeile faende er hier und meldete sich
// selbst. `\145` ist der Buchstabe `e`, `\132` der Buchstabe `Z`; zur Laufzeit steht
// das Wort da, im Dateitext nicht. Der Selbsttest prueft deshalb zuerst, dass jeder
// Fall ueberhaupt noch einen Mustertreffer hergibt: Verrutscht die Maskierung, wird
// er laut statt still gruen.

struct Namensfall {
    std::string_view zeile;
    /// Der Name, den der Riegel finden muss. **Leer heisst: er darf keinen finden** --
    /// die Haelfte des Maszstabs, ohne die eine Suche nur beweist, dass sie etwas
    /// findet, und nicht, dass sie das Richtige findet.
    std::string_view erwartet;
    std::string_view herkunft;
};

constexpr std::array<Namensfall, 8> NAMENSFAELLE = {{
    // --- Die zwei Formen, um derentwillen dieses Paket existiert -------------
    {"abschliessend (`technik.md`; am 2026-09-03 Zeil\145 1219,", "technik.md",
     "daten/adressen.md, Satz zur Tabelle T46 -- gemessen 2026-09-04: Datum dazwischen"},
    // Das `A` maskiert, damit dieser Fall nicht selbst zur Fundstelle von Bedingung 2
    // wird: Seit Paket 0079 faengt sie die Form ohne Anfuehrung, und ein Dateiname
    // steht hier unmittelbar links. Zur Laufzeit steht das Wort da, im Dateitext nicht.
    {"den Wortlaut der Reihenliste aus technik.md \101bschnitt 7, und die Reihenliste "
     "sagt dort in Zeil\145 1441 weiter",
     "technik.md",
     "daten/reihen.toml, Feld in_dieser_datei zu Reihe 9 -- gemessen 2026-09-04: "
     "acht Fuellwoerter und ein Komma dazwischen"},

    // --- Die Regel bei mehreren Namen ---------------------------------------
    {"laut daten/adressen.md und spiel.md steht in Zeil\145 88 der Wert", "spiel.md",
     "gebaut: der naechstgelegene Name gilt, ueber ihn hinweg wird nicht gesucht"},

    // --- Was weiterhin durchgehen muss --------------------------------------
    {"static_assert(stelle_basiswechsel(Gebiet::RW) == 197);   // Zeil\145 198", "",
     "kern/src/zustand.cpp -- eine von fuenf Stellen, die gruen bleiben muessen: "
     "die Nummer meint die Adresstabelle, kein Wort der Zeile ist ein Dateiname"},
    {"Siehe technik.md. Dort steht in Zeil\145 42 die Erklaerung", "",
     "gebaut: das Satzende beendet die Suche -- dies ist der Fall, der die Grenze "
     "misst, und ohne ihn waere sie behauptet"},
    {"in Zeil\145 42 von technik.md", "",
     "gebaut: gesucht wird nur nach links. Ein Name rechts vom Treffer bleibt "
     "ungefangen; das ist eine Luecke und keine Nachsicht"},

    // --- Was die enge Fassung schon konnte und weiter koennen muss ----------
    {"parameter.toml Zeil\145 304: druck_max = 1 # PLATZHALTER", "parameter.toml",
     "**historisch** -- die unmittelbare Form, die schon vor 0073 gefangen wurde. Sie "
     "stand in kern/test/schranken_probe.cpp und steht dort seit dem Commit 9bb7492 "
     "(Paket 0044, 2026-09-04) nicht mehr: Sechs Belegstellen dieser Bauart sind dort "
     "durch den Schluesselnamen ersetzt worden. Im gelesenen Baum ist der Wortlaut "
     "heute nirgends nachzuschlagen; der Fall selbst bleibt echt und unangetastet, "
     "falsch war allein die Adresse, unter der man ihn suchen wuerde"},
    {"sind gegen die Reihenliste und gegen technik.md dort \132. 1306 gehalten",
     "technik.md",
     "aufgaben/0006, abgewandelt: die zweite Musterform mit einem Wort dazwischen -- "
     "die Verbreiterung gilt fuer beide Muster, nicht nur fuer das erste"},
}};

/// Wie viele Faelle nicht wie erwartet ausgingen. Die Abweichungen stehen auf `stderr`.
std::size_t selbsttest_namenssuche() {
    std::size_t falsch = 0;
    for (std::size_t k = 0; k < NAMENSFAELLE.size(); ++k) {
        const Namensfall& fall = NAMENSFAELLE[k];
        const Zeilenfund fund = fund_ab(fall.zeile, 0);
        if (!fund.getroffen) {
            ++falsch;
            std::fprintf(stderr,
                         "Selbsttest %zu: kein Mustertreffer. Der Fall misst damit "
                         "nichts mehr -- vermutlich ist die Maskierung des Musterworts "
                         "verrutscht.\n      Zeile:    %.*s\n      Herkunft: %.*s\n",
                         k + 1, static_cast<int>(fall.zeile.size()), fall.zeile.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
            continue;
        }
        if (std::string_view(fund.ziel) != fall.erwartet) {
            ++falsch;
            std::fprintf(stderr,
                         "Selbsttest %zu: erwartet war %s, gefunden wurde %s.\n"
                         "      Zeile:    %.*s\n      Herkunft: %.*s\n", k + 1,
                         fall.erwartet.empty() ? "kein Dateiname"
                                               : std::string(fall.erwartet).c_str(),
                         fund.ziel.empty() ? "keiner" : fund.ziel.c_str(),
                         static_cast<int>(fall.zeile.size()), fall.zeile.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
        }
    }
    return falsch;
}

// ---------------------------------------------------------------------------
// Die Dateiauswahl
// ---------------------------------------------------------------------------

bool ist_quelldatei(const fs::path& pfad) {
    if (pfad.filename().string() == "CMakeLists.txt") {
        return true;
    }
    const std::string endung = pfad.extension().string();
    return endung == ".cpp" || endung == ".hpp" || endung == ".cmake";
}

/// Ein Datendokument -- was Bedingung 2 ueber die Bauquellen hinaus liest.
/// `parameter.toml` und alles unter `daten/`; die Begruendung steht im Kopf.
bool ist_datendokument(const fs::path& pfad) {
    const std::string endung = pfad.extension().string();
    return endung == ".md" || endung == ".toml";
}

/// Alles, was als **Ziel** eines Zitats nachgeschlagen werden kann. Weiter gefasst
/// als die beiden oben: Ein Zitat darf auf eine Datei zeigen, die selbst nichts
/// zitiert. Die Endungsliste ist dieselbe wie bei Bedingung 1, damit es nicht zwei
/// gibt, die auseinanderlaufen.
bool ist_zieldatei(const fs::path& pfad) {
    if (ist_quelldatei(pfad)) {
        return true;
    }
    const std::string name = pfad.filename().string();
    return endung_zugelassen(name);
}

bool ist_ungelesener_ordner(std::string_view ordner) {
    for (std::size_t i = 0; i < UNGELESENE_ORDNER.size(); ++i) {
        if (ordner == UNGELESENE_ORDNER[i]) {
            return true;
        }
    }
    return false;
}

/// Versteckte Ordner (`.git`, `.claude`). Sie werden gar nicht erst betreten, und das
/// ist seit Paket 0083 ein anderer Fall als der oben: Dort liegt Maschinerie und kein
/// Dokument, das ein Zitat nennen koennte. Ein Pruefbericht wird zitiert, ein
/// Git-Objekt nicht -- deshalb lohnt es nicht, ihre Namen fuer die Ortsfrage
/// mitzufuehren, und der Baum unter `.git` ist der groesste des Vorhabens.
bool ist_maschinerie(std::string_view ordner) {
    return !ordner.empty() && ordner.front() == '.';
}

/// Wo eine Datei liegt, deren Inhalt niemand liest -- eingesammelt wird ihr **Pfad**
/// unterhalb der Wurzel, mit Schraegstrichen und ohne die Wurzel davor.
///
/// Bis zum Ruecklauf vom 2026-09-05 stand hier der blosse Basisname, und genau daran ist
/// die erste Fassung dieses Pakets gescheitert: Die ungelesenen Ordner tragen
/// vollstaendige Abschriften des Quellbaums, also hat fast jeder Name dort einen
/// Zwilling. Ein Basisname beantwortet die Frage "gibt es diesen Namen irgendwo"; die
/// Frage, die gestellt ist, lautet "zeigt dieser Verweis dorthin". Die Begruendung im
/// Kopf, der Teil zur Ortsfrage.
using Ortsmenge = std::set<std::string>;

/// Absteigend, mit eigener Arbeitsliste statt `recursive_directory_iterator`: Dessen
/// `disable_recursion_pending` haengt am Zustand des Iterators, und ein Ordner voller
/// Maschinerie soll gar nicht erst geoeffnet werden.
///
/// Zwei Ausgaben aus einem Durchgang: die Dateien, die gelesen werden duerfen, und die
/// Pfade derer, die in einem mit Absicht ungelesenen Ordner liegen. Zwei Durchgaenge
/// ueber denselben Baum waeren zwei Ordnerlisten, die auseinanderlaufen koennen.
std::vector<fs::path> sammle_dateien_roh(const fs::path& wurzel, Ortsmenge& ungelesene,
                                         std::error_code& fehler) {
    std::vector<fs::path> gefunden;
    // Eingesammelt wird in einem Durchgang alles, was ueberhaupt gelesen werden kann;
    // welche Bedingung welche Teilmenge bekommt, entscheidet `main` an den Praedikaten
    // oben.
    struct Auftrag {
        fs::path pfad;
        bool ungelesen;
    };
    std::vector<Auftrag> offen;
    offen.push_back(Auftrag{wurzel, false});

    while (!offen.empty()) {
        const Auftrag auftrag = offen.back();
        offen.pop_back();

        fs::directory_iterator it(auftrag.pfad, fehler);
        if (fehler) {
            return gefunden;
        }
        const fs::directory_iterator ende;
        while (it != ende) {
            const fs::path eintrag = it->path();
            const std::string name = eintrag.filename().string();
            std::error_code art;
            if (fs::is_directory(eintrag, art)) {
                if (!ist_maschinerie(name)) {
                    // Einmal ungelesen, immer ungelesen: Ein Unterordner von `befunde`
                    // wird nicht dadurch lesbar, dass er anders heisst.
                    offen.push_back(
                        Auftrag{eintrag, auftrag.ungelesen || ist_ungelesener_ordner(name)});
                }
            } else if (fs::is_regular_file(eintrag, art) && ist_zieldatei(eintrag)) {
                if (auftrag.ungelesen) {
                    // Der Pfad unter der Wurzel, mit Schraegstrichen. `lexically_relative`
                    // und nicht ein Abschneiden der Wurzel als Zeichenkette: Der Baum
                    // wird von einem kanonisierten Pfad aus abgestiegen, aber die
                    // Trennzeichen sollen aus **einer** Stelle kommen.
                    ungelesene.insert(
                        eintrag.lexically_relative(wurzel).generic_string());
                } else {
                    gefunden.push_back(eintrag);
                }
            }
            it.increment(fehler);
            if (fehler) {
                return gefunden;
            }
        }
    }
    return gefunden;
}

// ---------------------------------------------------------------------------
// Die Ausgabeordnung -- Paket 0130
// ---------------------------------------------------------------------------
//
// Bis zum 2026-09-06 sortierte dieser Riegel nirgends. `std::sort` kam im ganzen
// Quelltext nicht vor, und damit war die Ordnung jeder Liste, die er ausgibt, die
// Auflistungsordnung des Dateisystems. Gemessen am 2026-09-05 bei der Pruefung von
// Paket 0120, mit **einem** selbst uebersetzten Programm ueber inhaltsgleiche Baeume:
// dieselben Kennzahlen, derselbe Rueckgabewert -- und die uebergangenen Fundstellen in
// zwei verschiedenen Ordnungen, je nachdem, ob der Baum auf ext4 oder auf tmpfs lag.
//
// Das ist keine Schoenheitsfrage, sondern eine Pruefbarkeitsluecke, und sie hat
// zugeschlagen. Viele Abnahmebedingungen dieses Vorhabens lauten "der Lauf danach zeigt
// gegenueber dem Lauf davor keinen Rueckschritt". Wer den Vorher-Stand herstellt, ohne
// eine fremde Datei anzufassen -- und die Hausregel laesst ihm keine Wahl --, legt ihn
// neben den Arbeitsbaum und vergleicht danach zwei Ausgaben, deren Zeilenunterschiede
// zu Dutzenden aus blossen Umsortierungen bestehen.
//
// Zweitens haengt an der Ordnung mehr als die Ordnung: `nimm_ziel_auf` traegt zu einem
// mehrfach vergebenen Basisnamen den **zuerst gesehenen** Pfad ein. Welcher das ist,
// entschied bis hierher das Dateisystem -- und mit ihm, welchen Pfad eine Meldung
// nennt. Sortiert wird deshalb an der Sammelstelle und nicht erst an der Ausgabe.
//
// Die Namensmenge der ungelesenen Ordner braucht nichts dergleichen: Sie ist ein
// `std::set<std::string>`, also schon nach `std::string::compare` geordnet -- und das
// ist derselbe zeichenweise Vergleich wie hier, weil `char_traits<char>::lt` seine
// Zeichen als `unsigned char` nimmt.
//
// Verglichen wird zeichenweise ueber die Byte-Folge. Drei Entscheidungen stecken darin,
// und jede hat unten ihren Fall:
//
//   * **Kein Gebietsschema.** Ein Vergleich ueber `strcoll` ordnete Gross- und
//     Kleinschreibung ineinander und haenge damit an einer Umgebungsvariablen des
//     ausfuehrenden Rechners -- genau die Sorte Abhaengigkeit, die hier wegsoll.
//   * **Kein Vergleich ueber `fs::path`.** Dessen Vergleich laeuft Bestandteil fuer
//     Bestandteil; `kern/src/werte.cpp` staende damit vor `kern.md`, obwohl der Punkt
//     (0x2E) vor dem Schraegstrich (0x2F) kommt. Gemeldet wird der Kurzname als
//     Zeichenkette, also wird auch nach ihr sortiert.
//   * **`unsigned char` und nicht `char`.** Auf dieser Werkzeugkette ist `char`
//     vorzeichenbehaftet; ein Name mit einem Umlaut traegt in UTF-8 Bytes ab 0x80 und
//     landete als negative Zahl **vor** allem anderen.

/// Vergleicht zwei Kurznamen zeichenweise ueber ihre Bytes -- Paket 0130.
///
/// Ausgeschrieben statt `links < rechts`: Die Bibliothek vergleicht ebenso, aber sie
/// ist nicht die Stelle, an der ein Selbsttest die Regel festhalten kann. Hier steht
/// sie als **ein** Aufruf da, den der Lauf ueber den Bestand und der Selbsttest
/// gleichermassen nehmen -- dieselbe Bauart wie bei `beurteile_zitat` in Paket 0106.
///
/// `constexpr`, damit die Tabelle unten schon beim Uebersetzen gegen sich selbst
/// geprueft werden kann.
constexpr bool vor_in_byteordnung(std::string_view links, std::string_view rechts) {
    const std::size_t gemeinsam =
        links.size() < rechts.size() ? links.size() : rechts.size();
    for (std::size_t i = 0; i < gemeinsam; ++i) {
        const unsigned char l = static_cast<unsigned char>(links[i]);
        const unsigned char r = static_cast<unsigned char>(rechts[i]);
        if (l != r) {
            return l < r;
        }
    }
    // Gleicher Anfang, verschiedene Laenge: das kuerzere zuerst. Ohne diese Zeile waeren
    // zwei Namen, von denen einer den anderen fortsetzt, gleichwertig -- und `std::sort`
    // duerfte sie in beliebiger Ordnung liegen lassen.
    return links.size() < rechts.size();
}

/// Bringt eine Liste von Kurznamen in die Ausgabeordnung -- Paket 0130.
void ordne_kurznamen(std::vector<std::string>& namen) {
    std::sort(namen.begin(), namen.end(),
              [](const std::string& links, const std::string& rechts) {
                  return vor_in_byteordnung(links, rechts);
              });
}

/// Sammelt wie oben und legt das Gesammelte in die Ausgabeordnung -- Paket 0130.
///
/// Sortiert wird nach dem **vollen** Pfad und nicht nach dem Kurznamen, den erst `main`
/// bildet. Das ist dieselbe Ordnung: Jeder Eintrag steht unter derselben Wurzel, der
/// Kurzname entsteht durch Wegnahme genau dieses gemeinsamen Vorsatzes, und ein
/// gemeinsamer Vorsatz aendert an einem zeichenweisen Vergleich nichts.
///
/// Der Sortierschritt steht hier und nicht im Rumpf oben, weil der Rumpf drei Ausgaenge
/// hat: zwei davon geben im Fehlerfall vorzeitig zurueck. Ein Aufrufer, der `fehler`
/// nicht prueft, bekaeme sonst je nach Ausgang eine geordnete oder eine ungeordnete
/// Liste.
std::vector<fs::path> sammle_dateien(const fs::path& wurzel, Ortsmenge& ungelesene,
                                     std::error_code& fehler) {
    std::vector<fs::path> gefunden = sammle_dateien_roh(wurzel, ungelesene, fehler);
    std::sort(gefunden.begin(), gefunden.end(),
              [](const fs::path& links, const fs::path& rechts) {
                  const std::string a = links.string();
                  const std::string b = rechts.string();
                  return vor_in_byteordnung(a, b);
              });
    return gefunden;
}

// ---------------------------------------------------------------------------
// Der Selbsttest zur Ausgabeordnung -- Paket 0130
// ---------------------------------------------------------------------------
//
// Was diese Tabelle prueft, was keine andere prueft: **dass die Ordnung der Ausgabe
// eine Regel hat und nicht das Dateisystem.** Sie ist die einzige, die ohne einen
// Gegenstand auf der Platte auskommt und trotzdem den Weg misst, den der Lauf ueber den
// Bestand nimmt -- `ordne_kurznamen` und die Sortierung in `sammle_dateien` nehmen
// denselben Aufruf.
//
// Die Vorlage ist mit Absicht unsortiert, und dass sie es ist, wird beim Uebersetzen
// geprueft: Stuende sie schon richtig da, bliebe der Fall auch dann gruen, wenn
// `ordne_kurznamen` gar nichts taete.
//
// Der Umlaut unten ist als Oktalfolge geschrieben (`\303\234` ist das grosse `U` mit
// zwei Punkten in UTF-8). Nicht wegen dieses Riegels -- das Wort ist keines seiner
// Schluesselwoerter --, sondern damit der Fall auch dann noch dieselben zwei Bytes
// traegt, wenn eine Werkzeugkette die Datei einmal anders liest, als sie geschrieben
// wurde. Ein Fall, der die Byte-Folge festhalten soll, darf nicht selbst an einer
// Umkodierung haengen.

struct Ordnungsfall {
    /// Ein Kurzname, wie der Riegel ihn meldet.
    std::string_view name;
    /// Sein Platz in der erwarteten Ordnung, von 1 an gezaehlt.
    std::size_t platz;
    /// Was diesen Fall von seinem Vorgaenger trennt -- die Regel, die er haelt.
    std::string_view herkunft;
};

constexpr std::array<Ordnungsfall, 8> ORDNUNGSFAELLE = {{
    {"kern/src/werte.cpp", 6,
     "gegen den Nachbarn darunter: gleicher Anfang bis zum Namen, dann `c` (0x63) vor "
     "`h` (0x68)"},
    {"\303\234bersicht.md", 8,
     "der Fall gegen `char`: das erste Byte ist 0xC3. Vorzeichenbehaftet verglichen "
     "waere es negativ, und dieser Name staende an Platz 1 statt am Ende"},
    {"daten/reihen.toml", 3, "gegen `kern...`: `d` (0x64) vor `k` (0x6B)"},
    {"CMakeLists.txt", 1,
     "der Fall gegen ein Gebietsschema: `C` (0x43) steht vor jedem Kleinbuchstaben. "
     "Eine Sortierung nach Sprachregeln zoege diesen Namen zwischen die beiden "
     "darunter"},
    {"kern.md", 5,
     "der Fall gegen einen Vergleich Bestandteil fuer Bestandteil: der Punkt (0x2E) "
     "steht vor dem Schraegstrich (0x2F), also kommt dieser Name vor `kern/...`. Ueber "
     "`fs::path` verglichen waere es umgekehrt"},
    {"aufgaben/0130-ordnung.md", 2, "gegen `CMakeLists.txt`: `a` (0x61) nach `C` (0x43)"},
    {"kern/src/werte.hpp", 7, "das Gegenstueck zum ersten Fall"},
    {"daten/reihen.toml.alt", 4,
     "der Fall zur gleichen Laenge: der Name darueber ist sein Anfang. Ohne die letzte "
     "Zeile in `vor_in_byteordnung` waeren beide gleichwertig und ihre Ordnung wieder "
     "offen"},
}};

/// Steht die Tabelle wirklich unsortiert da? Sonst prueft ihr Fall nichts.
constexpr bool ordnungsvorlage_ist_ungeordnet() {
    for (std::size_t k = 1; k < ORDNUNGSFAELLE.size(); ++k) {
        if (vor_in_byteordnung(ORDNUNGSFAELLE[k].name, ORDNUNGSFAELLE[k - 1].name)) {
            return true;
        }
    }
    return false;
}

/// Ist jeder Platz von 1 bis N genau einmal vergeben?
constexpr bool ordnungsplaetze_vollstaendig() {
    for (std::size_t platz = 1; platz <= ORDNUNGSFAELLE.size(); ++platz) {
        std::size_t treffer = 0;
        for (std::size_t k = 0; k < ORDNUNGSFAELLE.size(); ++k) {
            if (ORDNUNGSFAELLE[k].platz == platz) {
                ++treffer;
            }
        }
        if (treffer != 1) {
            return false;
        }
    }
    return true;
}

static_assert(ordnungsvorlage_ist_ungeordnet(),
              "ORDNUNGSFAELLE steht schon in der erwarteten Ordnung da. Der Fall waere "
              "damit auch fuer ein ordne_kurznamen gruen, das nichts tut.");
static_assert(ordnungsplaetze_vollstaendig(),
              "Die Plaetze in ORDNUNGSFAELLE sind keine luecken- und doppellose Folge "
              "von 1 bis zur Zahl der Faelle.");

/// Wie viele Faelle nicht wie erwartet ausgingen. Die Abweichungen stehen auf `stderr`.
std::size_t selbsttest_ordnung() {
    std::vector<std::string> namen;
    for (std::size_t k = 0; k < ORDNUNGSFAELLE.size(); ++k) {
        namen.push_back(std::string(ORDNUNGSFAELLE[k].name));
    }
    ordne_kurznamen(namen);

    std::size_t falsch = 0;
    for (std::size_t k = 0; k < ORDNUNGSFAELLE.size(); ++k) {
        const Ordnungsfall& fall = ORDNUNGSFAELLE[k];
        // Der Platz ist durch `ordnungsplaetze_vollstaendig` schon beim Uebersetzen auf
        // 1 bis N festgelegt. Geprueft wird er trotzdem: Ein Index, der aus einer
        // spaeter geaenderten Tabelle kommt, soll hier ein roter Fall sein und kein
        // Zugriff daneben.
        if (fall.platz == 0 || fall.platz > namen.size()) {
            ++falsch;
            std::fprintf(stderr,
                         "Ordnungsfall %zu: Platz %zu liegt ausserhalb der %zu Faelle.\n",
                         k + 1, fall.platz, namen.size());
            continue;
        }
        const std::string& gemessen = namen[fall.platz - 1];
        if (gemessen != fall.name) {
            ++falsch;
            std::fprintf(stderr,
                         "Ordnungsfall %zu: an Platz %zu steht '%s', erwartet war "
                         "'%.*s'.\n      Herkunft: %.*s\n",
                         k + 1, fall.platz, gemessen.c_str(),
                         static_cast<int>(fall.name.size()), fall.name.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
        }
    }
    return falsch;
}

// ---------------------------------------------------------------------------
// Die Pruefung
// ---------------------------------------------------------------------------

struct Befund {
    std::string datei;
    std::size_t zeilennummer = 0;
    std::string ziel;
    std::string stelle;
};

struct Zaehlwerk {
    std::size_t treffer = 0;
    std::size_t mit_dateinamen = 0;
};

/// Der Ausschnitt um den Treffer, damit die Meldung zeigt, was gemeint ist.
std::string ausschnitt(std::string_view zeile, std::size_t anfang, std::size_t laenge) {
    constexpr std::size_t VORLAUF = 28;
    const std::size_t von = anfang > VORLAUF ? anfang - VORLAUF : 0;
    return std::string(zeile.substr(von, (anfang + laenge) - von));
}

void pruefe_datei(const fs::path& pfad, const std::string& anzeigename,
                  std::vector<Befund>& befunde, Zaehlwerk& zaehlwerk) {
    std::ifstream strom(pfad);
    if (!strom) {
        return;
    }
    const std::string eigener_name = pfad.filename().string();

    std::string zeile;
    std::size_t nummer = 0;
    while (std::getline(strom, zeile)) {
        ++nummer;
        if (!zeile.empty() && zeile.back() == '\r') {
            zeile.pop_back();
        }
        for (std::size_t i = 0; i < zeile.size();) {
            const Zeilenfund fund = fund_ab(zeile, i);
            if (!fund.getroffen) {
                break;
            }
            ++zaehlwerk.treffer;

            if (!fund.ziel.empty()) {
                ++zaehlwerk.mit_dateinamen;
                if (basisname(fund.ziel) != eigener_name) {
                    befunde.push_back(Befund{
                        anzeigename, nummer, fund.ziel,
                        ausschnitt(zeile, fund.anfang, fund.laenge)});
                }
            }
            i = fund.anfang + fund.laenge;
        }
    }
}

// ---------------------------------------------------------------------------
// Bedingung 2, Teil 1: was ein Zitat ist
// ---------------------------------------------------------------------------

/// Die drei Schluesselwoerter, hinter denen eine Ueberschrift stehen darf.
/// Zusammengesetzt statt ausgeschrieben, aus demselben Grund wie bei Bedingung 1:
/// Ein ausgeschriebenes Schluesselwort traegt in einem Zeichenkettenliteral
/// unmittelbar hinter sich ein Anfuehrungszeichen. Der Riegel faende sich damit in
/// seinem eigenen Quelltext und suchte eine Ueberschrift, die es nirgends gibt.
constexpr std::array<std::string_view, 4> SCHLUESSEL = {
    "Abschnit\164", "Ueberschrif\164", "\303\234berschrif\164", "Absa\164z"};

/// Anfuehrung und Schluss, paarweise. Die deutschen Anfuehrungszeichen sind unten und
/// oben verschieden, und im Bestand kommen zu einem Anfang mehrere Schluesse vor --
/// deshalb mehrere Zeilen mit demselben Anfang. Die Reihenfolge entscheidet: Genommen
/// wird das erste Paar, dessen Anfang passt **und** dessen Schluss im selben Absatz
/// steht. Die typografischen Paare stehen deshalb vor dem geraden Schlusszeichen: Ein
/// gerades Anfuehrungszeichen kommt in einem Satz zu oft vor, um erste Wahl zu sein.
///
/// Dass es die gemischte Form ueberhaupt braucht, ist gemessen und nicht vermutet:
/// `einheitenbefund-pwt-baci.md` oeffnet mit dem tiefen Anfuehrungszeichen und
/// schliesst mit dem geraden. Ohne die letzten beiden Zeilen unten faende der Riegel
/// dieses Zitat nicht -- und, schlimmer, meldete es nicht einmal als uebergangen,
/// denn ohne Schluss ist es fuer ihn gar kein Zitat.
struct Klammer {
    std::string_view auf;
    std::string_view zu;
    /// Kuendigt dieses Anfangszeichen fuer sich genommen ein Zitat an? -- Paket 0086.
    ///
    /// Nur diese Paare gelten, wenn das Schluesselwort **nicht** unmittelbar vor der
    /// Anfuehrung steht. Der Grund ist die Arbeitsteilung zwischen den beiden Teilen
    /// eines Zitats: Bei Abstand null kuendigt das Schluesselwort selbst an, was folgt,
    /// und dann darf das Zeichen mehrdeutig sein. Mit Woertern dazwischen ist das
    /// Zeichen die einzige Ankuendigung, die bleibt -- und die vier ausgenommenen
    /// tragen in diesem Baum ueberwiegend eine andere Aufgabe: der Gegenstrich und das
    /// Sternchen zeichnen Code und Kursives aus, das gerade Anfuehrungszeichen eroeffnet
    /// jede Zeichenkette dieser Uebersetzungseinheit, das einfache steht im Genitiv.
    ///
    /// **Gemessen und nicht befuerchtet:** Ohne diese Trennung faengt der Riegel zehn
    /// Stellen in seinem eigenen Quelltext, alle falsch -- zwei im Kopfkommentar
    /// (`spiel.md` im Gegenstrich, ein Wort hinter dem Schluesselwort; dazu ein
    /// Werkzeugname im Gegenstrich, den ein spaeteres Paket dort nachgetragen hat),
    /// eine in `SATZFAELLE` und sieben in `ZITATFAELLE`, wo hinter
    /// `Namensart::Ueberschrift` ein Komma und danach ein Zeichenkettenliteral steht.
    ///
    /// Hinter diesem Wort darf in seinem Textblock kein zweiter Gegenstrich mehr
    /// folgen: Er schloesse die Anfuehrung, die das Schluesselwort davor eroeffnet,
    /// und der Riegel faende sich hier selbst -- gemessen am 2026-09-06, als der
    /// Name der elften Stelle noch eine Zeile weiter unten stand. Sie liegt
    /// ausserhalb dieser Datei, in der Parameterdatei des Vorhabens.
    ///
    /// So gemessen am 2026-09-06 gegen den Stand `5d5e2d6`, mit dem Mutanten
    /// `ohne-marken-rein` aus `kp0086-mutieren.py`. Er laesst den Selbsttest zum
    /// Wortabstand reissen und braucht deshalb den Filter, der den Zaehlzeilen ihre
    /// Abbruchwirkung nimmt -- sonst bricht der Lauf mit Code 2 ab, ehe der Bestand
    /// gelesen ist, und liefert gar keine Zahl. Der vollstaendige Aufruf steht im
    /// Rumpf des Arbeitspakets 0115.
    ///
    /// Die Aufteilung waechst mit den Falltabellen und ist deshalb nachzumessen und
    /// nicht abzuschreiben; die Gesamtzahlen stehen im Kopf, mit demselben Stand.
    bool kuendigt_an;
};

constexpr std::array<Klammer, 11> KLAMMERN = {{
    {"\"", "\"", false},
    {"\342\200\236", "\342\200\234", true},  // U+201E ... U+201C
    {"\342\200\236", "\342\200\235", true},  // U+201E ... U+201D
    {"\342\200\234", "\342\200\235", true},  // U+201C ... U+201D
    {"'", "'", false},
    {"\342\200\230", "\342\200\231", true},  // U+2018 ... U+2019
    {"`", "`", false},
    {"*", "*", false},
    {"\342\200\236", "\"", true},  // U+201E ... gerade
    {"\342\200\234", "\"", true},  // U+201C ... gerade
    // Die Form, die Paket 0057 in `reihen.toml` eingefuehrt hat: "Adresse plus Zitat
    // im Wortlaut", geklammert statt in Anfuehrung. Sie steht hier, weil 0057 eines
    // der sechs Pakete ist, um derentwillen dieser Riegel existiert -- ohne diese
    // Zeile fiele die Haelfte seiner Arbeit durch.
    {"(Zita\164: ", ")", true},
}};

/// Laenger als das kann eine Ueberschrift nicht sein. Ohne die Schranke greift ein
/// Anfuehrungszeichen ohne Partner in der Naehe bis ans Absatzende und macht aus einem
/// halben Satz eine "Ueberschrift".
constexpr std::size_t UEBERSCHRIFT_HOECHSTENS = 200;

bool ist_wortzeichen(char c) {
    const unsigned char z = static_cast<unsigned char>(c);
    return (z >= 'a' && z <= 'z') || (z >= 'A' && z <= 'Z') || (z >= '0' && z <= '9')
           || z >= 0x80;  // ein Folgebyte gehoert zum Buchstaben davor
}

/// Die Normierung, auf beiden Seiten des Vergleichs dieselbe. Begruendung im Kopf.
std::string normiere(std::string_view roh) {
    std::string umschrieben;
    for (std::size_t i = 0; i < roh.size();) {
        const unsigned char c = static_cast<unsigned char>(roh[i]);
        if (c == 0xC3 && i + 1 < roh.size()) {
            const unsigned char d = static_cast<unsigned char>(roh[i + 1]);
            bool getroffen = true;
            switch (d) {
                case 0xA4: umschrieben += "ae"; break;
                case 0xB6: umschrieben += "oe"; break;
                case 0xBC: umschrieben += "ue"; break;
                case 0x84: umschrieben += "Ae"; break;
                case 0x96: umschrieben += "Oe"; break;
                case 0x9C: umschrieben += "Ue"; break;
                case 0x9F: umschrieben += "ss"; break;
                default: getroffen = false; break;
            }
            if (getroffen) {
                i += 2;
                continue;
            }
        }
        if (c == 0xE2 && i + 2 < roh.size()
            && static_cast<unsigned char>(roh[i + 1]) == 0x80) {
            const unsigned char d = static_cast<unsigned char>(roh[i + 2]);
            if (d == 0x93 || d == 0x94) {  // Halbgeviert- und Geviertstrich
                umschrieben += "--";
                i += 3;
                continue;
            }
            if (d == 0x9C || d == 0x9D || d == 0x9E) {
                umschrieben += '"';
                i += 3;
                continue;
            }
            if (d == 0x98 || d == 0x99) {
                umschrieben += '\'';
                i += 3;
                continue;
            }
        }
        umschrieben += static_cast<char>(c);
        ++i;
    }

    std::string gestrafft;
    bool luecke = false;
    for (std::size_t i = 0; i < umschrieben.size(); ++i) {
        const char c = umschrieben[i];
        if (c == '*' || c == '_' || c == '`') {
            continue;
        }
        if (c == ' ' || c == '\t') {
            luecke = !gestrafft.empty();
            continue;
        }
        if (luecke) {
            gestrafft += ' ';
            luecke = false;
        }
        gestrafft += c;
    }

    std::size_t vorn = 0;
    while (vorn < gestrafft.size() && gestrafft[vorn] == '#') {
        ++vorn;
    }
    while (vorn < gestrafft.size() && gestrafft[vorn] == ' ') {
        ++vorn;
    }
    std::string fertig = gestrafft.substr(vorn);
    while (!fertig.empty()
           && (fertig.back() == '.' || fertig.back() == ':' || fertig.back() == ','
               || fertig.back() == ';')) {
        fertig.pop_back();
    }
    return fertig;
}

/// Ist diese Zeile der Zieldatei eine Ueberschriftszeile? Zwei Formen, beide im Kopf
/// begruendet: Rautenzeichen am Anfang, oder ein fett ausgezeichneter Vorspann.
bool ueberschrift_aus_zeile(std::string_view zeile, std::string& text) {
    std::size_t i = 0;
    while (i < zeile.size() && (zeile[i] == ' ' || zeile[i] == '\t')) {
        ++i;
    }
    if (i < zeile.size() && zeile[i] == '#') {
        std::size_t j = i;
        while (j < zeile.size() && zeile[j] == '#') {
            ++j;
        }
        if (j < zeile.size() && (zeile[j] == ' ' || zeile[j] == '\t')) {
            text = std::string(zeile.substr(j));
            return true;
        }
        return false;
    }
    if (zeile.size() - i >= 5 && zeile.substr(i, 2) == "**") {
        const std::size_t zu = zeile.find("**", i + 2);
        if (zu != std::string_view::npos && zu > i + 2) {
            text = std::string(zeile.substr(i + 2, zu - (i + 2)));
            return true;
        }
    }
    return false;
}

std::vector<std::string> lies_ueberschriften(const fs::path& pfad) {
    std::vector<std::string> gefunden;
    std::ifstream strom(pfad);
    if (!strom) {
        return gefunden;
    }
    std::string zeile;
    while (std::getline(strom, zeile)) {
        if (!zeile.empty() && zeile.back() == '\r') {
            zeile.pop_back();
        }
        std::string roh;
        if (ueberschrift_aus_zeile(zeile, roh)) {
            std::string normiert = normiere(roh);
            if (!normiert.empty()) {
                gefunden.push_back(normiert);
            }
        }
    }
    return gefunden;
}

// ---------------------------------------------------------------------------
// Bedingung 2, Teil 2: der Absatz
// ---------------------------------------------------------------------------

/// Welche Kommentarzeichen am Zeilenanfang abgestreift werden. In einer
/// Markdown-Datei keine: Dort ist das Rautenzeichen eine Ueberschrift und kein
/// Kommentar.
enum class Kopfart { Schraegstrich, Raute, Keine };

Kopfart kopfart(const fs::path& pfad) {
    if (pfad.filename().string() == "CMakeLists.txt") {
        return Kopfart::Raute;
    }
    const std::string endung = pfad.extension().string();
    if (endung == ".cpp" || endung == ".hpp") {
        return Kopfart::Schraegstrich;
    }
    if (endung == ".cmake" || endung == ".toml") {
        return Kopfart::Raute;
    }
    return Kopfart::Keine;
}

/// Ein Absatz: der Wortlaut am Stueck und zu jedem Zeichen die Zeile, aus der es
/// stammt. Die zweite Liste ist nicht Zierde -- ohne sie nennt die Meldung den Absatz
/// und nicht die Zeile, und der naechste Leser sucht wieder.
///
/// Seit Paket 0105 traegt sie eine zweite Aufgabe: Sie ist die **einzige** Stelle, an
/// der ein Zeilenumbruch im zusammengezogenen Wortlaut noch zu sehen ist. Im Text ist
/// er ein Leerzeichen wie jedes andere; in dieser Liste ist er der Sprung von einer
/// Nummer zur naechsten. Begruendung im Kopf, Abschnit\164 "Der Name am Zeilenende".
struct Absatz {
    std::string text;
    std::vector<std::size_t> zeile;

    /// Aus welcher Zeile stammt das Zeichen an `k`? Die Liste ist genauso lang wie der
    /// Wortlaut -- `haenge_zeile_an` fuellt beide im selben Schritt. Der Index wird
    /// trotzdem geprueft, wie an jeder Grenze dieses Programms; wo die Liste nichts
    /// sagt, lautet die Antwort `0` fuer jedes Zeichen, und dann liegt alles in
    /// derselben Zeile.
    std::size_t zeile_bei(std::size_t k) const {
        return k < zeile.size() ? zeile[k] : 0;
    }
};

/// Haengt den Inhalt einer Zeile an einen laufenden Absatz. Der Umbruch wird zu **einem**
/// Leerzeichen, und dieses Leerzeichen traegt bereits die Nummer der **neuen** Zeile --
/// daran endet ein Name ohne Anfuehrung.
///
/// Sie steht als eigener Aufruf da, damit der Selbsttest denselben Absatz baut, den der
/// Lauf ueber den Bestand liest. Eine zweite, nachgebaute Zusammenziehung im Test misst
/// eine Fassung, die nirgends laeuft.
void haenge_zeile_an(Absatz& absatz, std::string_view inhalt, std::size_t nummer) {
    if (!absatz.text.empty()) {
        absatz.text += ' ';
        absatz.zeile.push_back(nummer);
    }
    for (std::size_t k = 0; k < inhalt.size(); ++k) {
        absatz.text += inhalt[k];
        absatz.zeile.push_back(nummer);
    }
}

/// Trennt eine Zeile in Kommentarkopf und Inhalt. Der Kopf ist zugleich die Kennung
/// des Absatzes: Ein `///`-Block und ein `//`-Block daneben sind zwei Absaetze und
/// nicht einer, denn sie beschreiben Verschiedenes.
void zerlege_zeile(std::string_view zeile, Kopfart art, std::string& kopf,
                   std::string_view& inhalt) {
    std::size_t i = 0;
    while (i < zeile.size() && (zeile[i] == ' ' || zeile[i] == '\t')) {
        ++i;
    }
    std::string_view rest = zeile.substr(i);
    kopf.clear();
    if (art == Kopfart::Schraegstrich) {
        if (rest.size() >= 3 && (rest.substr(0, 3) == "//!" || rest.substr(0, 3) == "///")) {
            kopf = std::string(rest.substr(0, 3));
            rest.remove_prefix(3);
        } else if (rest.size() >= 2 && rest.substr(0, 2) == "//") {
            kopf = "//";
            rest.remove_prefix(2);
        }
    } else if (art == Kopfart::Raute) {
        if (!rest.empty() && rest.front() == '#') {
            kopf = "#";
            rest.remove_prefix(1);
        }
    }
    while (!rest.empty() && (rest.back() == ' ' || rest.back() == '\t')) {
        rest.remove_suffix(1);
    }
    std::size_t v = 0;
    while (v < rest.size() && (rest[v] == ' ' || rest[v] == '\t')) {
        ++v;
    }
    rest.remove_prefix(v);
    inhalt = rest;
}

std::vector<Absatz> lies_absaetze(const fs::path& pfad) {
    std::vector<Absatz> absaetze;
    std::ifstream strom(pfad);
    if (!strom) {
        return absaetze;
    }
    const Kopfart art = kopfart(pfad);

    std::string zeile;
    std::size_t nummer = 0;
    Absatz laufend;
    std::string letzter_kopf;
    bool offen = false;

    while (std::getline(strom, zeile)) {
        ++nummer;
        if (!zeile.empty() && zeile.back() == '\r') {
            zeile.pop_back();
        }
        std::string kopf;
        std::string_view inhalt;
        zerlege_zeile(zeile, art, kopf, inhalt);

        if (offen && (inhalt.empty() || kopf != letzter_kopf)) {
            absaetze.push_back(laufend);
            laufend = Absatz{};
            offen = false;
        }
        if (inhalt.empty()) {
            continue;
        }
        if (!offen) {
            letzter_kopf = kopf;
            offen = true;
        }
        haenge_zeile_an(laufend, inhalt, nummer);
    }
    if (offen) {
        absaetze.push_back(laufend);
    }
    return absaetze;
}

/// Der Absatz zu einem Fall der Selbsttesttabellen. Ein `\n` im Fall ist ein
/// Zeilenumbruch; alles andere geht denselben Weg wie eine gelesene Datei -- erst
/// `zerlege_zeile`, dann `haenge_zeile_an`.
///
/// Ein Fall ohne `\n` ergibt genau seinen eigenen Wortlaut in einer einzigen Zeile. Die
/// Tabellen, die es vor Paket 0105 schon gab, messen deshalb unveraendert weiter.
Absatz absatz_aus_fall(std::string_view fall) {
    Absatz absatz;
    std::size_t nummer = 0;
    std::size_t anfang = 0;
    while (anfang <= fall.size()) {
        std::size_t ende = fall.find('\n', anfang);
        if (ende == std::string_view::npos) {
            ende = fall.size();
        }
        ++nummer;
        std::string kopf;
        std::string_view inhalt;
        zerlege_zeile(fall.substr(anfang, ende - anfang), Kopfart::Keine, kopf, inhalt);
        if (!inhalt.empty()) {
            haenge_zeile_an(absatz, inhalt, nummer);
        }
        anfang = ende + 1;
    }
    return absatz;
}

// ---------------------------------------------------------------------------
// Bedingung 2, Teil 3: Ziel suchen und nachschlagen
// ---------------------------------------------------------------------------

/// Wo die Suche nach links endet -- die ganze Entscheidung an einer Stelle.
///
/// Sie steht als eigene Funktion da und nicht als Bedingung in der Leseschleife, damit
/// der Selbsttest **denselben** Weg misst, den der Lauf ueber den Bestand nimmt;
/// dieselbe Ueberlegung wie bei `fund_ab`, `zielart` und `namensart`.
///
/// Null heisst: der ganze Absatz. Das ist die von Paket 0067 gemessene Fassung und
/// bleibt es fuer die Form **mit** Anfuehrung.
std::size_t suchuntergrenze(std::string_view text, std::size_t bis,
                            bool ohne_anfuehrung) {
    return ohne_anfuehrung ? satzanfang_vor(text, bis) : 0;
}

/// Der **naechstgelegene** Verweis links von `bis` im selben Absatz -- und nur er.
///
/// Ueber einen Verweis hinweg wird nicht weitergesucht, auch nicht, wenn er sich nicht
/// aufloesen laesst. Der Grund ist gemessen: In `lizenzbefund-reihen.md` steht ein
/// Zitat aus einer franzoesischen Lizenzseite, deren Netzadresse eine Zeile darueber
/// steht; wer ueber sie hinwegliest, findet vier Zeilen weiter oben `daten.md` und
/// schlaegt eine franzoesische Ueberschrift in einer deutschen Vorgabe nach. Ein Ziel,
/// das dazwischenliegt, gehoert zum Satz -- die Suche endet dort und meldet das.
///
/// `netzadresse` sagt, welcher Sorte der Fund ist. Eine Netzadresse faellt am
/// doppelten Schraegstrich auf, den ein Pfad dieses Vorhabens nie traegt.
///
/// **`untergrenze` sagt, wo die Suche aufhoert.** Null heisst: der ganze Absatz, wie
/// Paket 0067 es gemessen hat. Die Form ohne Anfuehrung reicht stattdessen den
/// Satzanfang herein; warum, steht im Kopf unter der Satzgrenze nach links.
bool naechster_verweis(std::string_view text, std::size_t bis, std::size_t untergrenze,
                       std::string& name, bool& netzadresse) {
    std::size_t grenze = bis;
    while (grenze > untergrenze) {
        std::size_t ende = grenze;
        while (ende > untergrenze && !ist_pfadzeichen(text[ende - 1])) {
            --ende;
        }
        if (ende == untergrenze) {
            return false;
        }
        std::size_t anfang = ende;
        while (anfang > untergrenze && ist_pfadzeichen(text[anfang - 1])) {
            --anfang;
        }
        std::string_view wort = text.substr(anfang, ende - anfang);
        while (!wort.empty() && (wort.back() == '.' || wort.back() == '/')) {
            wort.remove_suffix(1);
        }
        if (endung_zugelassen(wort)) {
            name = std::string(wort);
            netzadresse = wort.find("//") != std::string_view::npos;
            return true;
        }
        grenze = anfang;
    }
    return false;
}

/// Der naechstgelegene Verweis **rechts** von `ab`, bis zum Ende des Satzes -- Paket
/// 0086. Rueckgabe und Bedeutung von `netzadresse` wie bei `naechster_verweis`.
///
/// **Wer gewinnt, wenn links und rechts ein Name steht: der linke.** Das ist die
/// Entscheidung, an der diese Lockerung haengt, und sie faellt so herum, weil die
/// Linksregel gemessen ist und diese hier nicht: Ohne sie band der Riegel ein
/// franzoesisches Zitat in `lizenzbefund-reihen.md` an die falsche Datei. Die Suche
/// nach rechts laeuft deshalb **nur, wenn links nichts steht** -- sie kann keine
/// vorhandene Zuordnung umhaengen, sondern nur eine fehlende ergaenzen. Damit ist die
/// Frage nach dem Vorrang nicht offen gelassen, sondern zugunsten des Gemessenen
/// beantwortet.
///
/// **Warum nur bis zum Satzende, waehrend die Suche nach links den ganzen Absatz
/// nimmt.** Nach links steht der Name **vor** der Ankuendigung und gehoert erkennbar zu
/// ihr; nach rechts steht hinter dem Zitat der weiterlaufende Text, und ohne Grenze
/// finge jede Anfuehrung den naechsten Dateinamen des Absatzes ein, gleich wie weit weg
/// er steht und wovon er handelt. Was die weitere Fassung kostet, ist gemessen und im
/// Kopf genannt.
///
/// **Und nur fuer die Form mit Anfuehrung.** Ohne sie hat das Zitat keinen bestimmten
/// rechten Rand -- der Name laeuft im Satz weiter, und wo er endet, ist geraten. Eine
/// Suche, die dort ansetzt, suchte im Zitat selbst.
bool verweis_rechts(std::string_view text, std::size_t ab, std::string& name,
                    bool& netzadresse) {
    const std::size_t obergrenze = satzende_nach(text, ab);
    std::size_t grenze = ab;
    while (grenze < obergrenze) {
        std::size_t anfang = grenze;
        while (anfang < obergrenze && !ist_pfadzeichen(text[anfang])) {
            ++anfang;
        }
        std::size_t ende = anfang;
        while (ende < obergrenze && ist_pfadzeichen(text[ende])) {
            ++ende;
        }
        if (anfang == ende) {
            return false;
        }
        std::string_view wort = text.substr(anfang, ende - anfang);
        while (!wort.empty() && (wort.back() == '.' || wort.back() == '/')) {
            wort.remove_suffix(1);
        }
        if (endung_zugelassen(wort)) {
            name = std::string(wort);
            netzadresse = wort.find("//") != std::string_view::npos;
            return true;
        }
        grenze = ende;
    }
    return false;
}

/// Eine Datei, auf die ein Zitat zeigen kann. `anzahl` traegt, wie oft ihr Basisname
/// im Bestand vorkommt: Ein mehrdeutiger Name wird nicht geraten.
struct Ziel {
    fs::path pfad;
    std::string anzeige;
    std::size_t anzahl = 0;
};

using Zielbestand = std::map<std::string, Ziel>;

void nimm_ziel_auf(Zielbestand& bestand, const fs::path& pfad,
                   const std::string& anzeige) {
    const std::string schluessel = pfad.filename().string();
    Ziel& eintrag = bestand[schluessel];
    if (eintrag.anzahl == 0) {
        eintrag.pfad = pfad;
        eintrag.anzeige = anzeige;
    }
    ++eintrag.anzahl;
}

// ---------------------------------------------------------------------------
// Bedingung 2, Teil 2b: wo das genannte Ziel liegt -- Paket 0083
// ---------------------------------------------------------------------------

/// Nennt der Name selbst einen Ort ausserhalb beider Wurzeln?
///
/// Gefragt wird an der **Gestalt des Namens**, nicht am Dateisystem, und das ist der
/// tragende Teil: Ein Name, der nicht im Bestand steht, ist entweder ein Verweis nach
/// draussen oder ein toter -- und nur der Name selbst kann sagen, welches von beiden.
/// Ein fuehrender Schraegstrich und ein Aufstieg mit zwei Punkten sind die beiden
/// Formen, in denen ein Pfad das ausspricht. Die dritte, die Netzadresse, faengt
/// `naechster_verweis` schon vorher an ihrem doppelten Schraegstrich ab.
bool nennt_ort_ausserhalb(std::string_view name) {
    if (!name.empty() && name.front() == '/') {
        return true;
    }
    if (name.size() >= 3 && name.substr(0, 3) == "../") {
        return true;
    }
    return name.find("/../") != std::string_view::npos;
}

/// Nennt der Name einen mit Absicht ungelesenen Ordner als einen seiner Pfadteile?
///
/// Gefragt wird -- wie bei `nennt_ort_ausserhalb` -- an der **Gestalt des Namens** und
/// nicht am Dateisystem. Das ist die Haelfte der Ortsfrage, die der Ruecklauf vom
/// 2026-09-05 verlangt: Ein Verweis zeigt nur dann in einen ungelesenen Ordner, wenn er
/// ihn ausspricht.
///
/// Ein Pfadteil zaehlt nur, wenn er **ganz** so heisst und ein Schraegstrich folgt.
/// `unbefunde/x.md` und `befunde.md` nennen deshalb keinen: Das eine traegt den Namen
/// als Endstueck eines laengeren Teils, das andere als Datei.
bool nennt_ungelesenen_ordner(std::string_view name) {
    std::size_t anfang = 0;
    for (std::size_t i = 0; i < name.size(); ++i) {
        if (name[i] != '/') {
            continue;
        }
        if (ist_ungelesener_ordner(name.substr(anfang, i - anfang))) {
            return true;
        }
        anfang = i + 1;
    }
    return false;
}

/// Liegt unter einem der eingesammelten Pfade eine Datei, die dieser Name meint?
///
/// Getroffen wird, wenn der genannte Pfad einer der eingesammelten **ist** oder dessen
/// Endstueck an einer Pfadgrenze. Das Endstueck ist noetig, weil ein Zitat den Weg von
/// der Wurzel nicht mitschreiben muss; die Pfadgrenze ist noetig, damit `ten/x.md` nicht
/// in `daten/x.md` trifft.
///
/// Eine lineare Suche und kein Index: Hierher kommt nur, wer die Frage oben schon mit Ja
/// beantwortet hat, und das sind je Lauf einstellig viele Namen.
bool liegt_in_ungelesenem_ordner(std::string_view name, const Ortsmenge& ungelesene) {
    for (Ortsmenge::const_iterator it = ungelesene.begin(); it != ungelesene.end(); ++it) {
        const std::string& ort = *it;
        if (ort.size() < name.size()) {
            continue;
        }
        const std::size_t versatz = ort.size() - name.size();
        if (ort.compare(versatz, name.size(), name) != 0) {
            continue;
        }
        if (versatz == 0 || ort[versatz - 1] == '/') {
            return true;
        }
    }
    return false;
}

/// Wo die genannte Zieldatei liegt. Die Sorte "nicht im Bestand" zerfaellt seit Paket
/// 0083 in drei, und nur die letzte ist ein Befund.
enum class Zielart {
    Gelesen,     ///< im Bestand -- es wird nachgeschlagen
    Ausserhalb,  ///< der Name nennt selbst einen Ort ausserhalb beider Wurzeln
    Ungelesen,   ///< der Name zeigt in einen ungelesenen Ordner, und dort liegt er auch
    Tot          ///< keiner der drei Faelle -- Befund
};

/// Die ganze Entscheidung an einer Stelle, damit der Selbsttest unten **denselben** Weg
/// misst wie der Lauf ueber den Bestand -- dieselbe Ueberlegung wie bei `fund_ab` und
/// `namensart`.
///
/// Die Reihenfolge entscheidet und ist keine Geschmackssache: Der Bestand zuerst, denn
/// eine Datei, die gelesen wird, ist gelesen, auch wenn eine gleichnamige unter
/// `befunde` liegt. Dann der Name, der seinen Ort selbst ausspricht. Erst danach die
/// Ortsfrage -- und die ist seit dem Ruecklauf vom 2026-09-05 **zweiteilig**: Der Name
/// muss den ungelesenen Ordner nennen, und unter dem genannten Pfad muss dort auch eine
/// Datei liegen. Ein Name, der seinen Ordner nicht bei sich traegt, ist tot; der Preis
/// dieser Richtung steht im Kopf.
///
/// **Von den vier Entscheidungen hier sind drei gemessen und eine nicht.** Faellt einer
/// der beiden Teile der Ortsfrage weg oder die Pfadgrenze in `liegt_in_...`, reissen
/// Faelle der Tabelle unten -- je Teil andere. Der **Vorrang des Aufstiegs** vor der
/// Ortsfrage reisst nichts, und der Grund steht beim letzten Fall der Tabelle: Die
/// beiden koennen nicht zugleich zutreffen.
Zielart zielart(std::string_view name, bool im_bestand, const Ortsmenge& ungelesene) {
    if (im_bestand) {
        return Zielart::Gelesen;
    }
    if (nennt_ort_ausserhalb(name)) {
        return Zielart::Ausserhalb;
    }
    if (nennt_ungelesenen_ordner(name) && liegt_in_ungelesenem_ordner(name, ungelesene)) {
        return Zielart::Ungelesen;
    }
    return Zielart::Tot;
}

// ---------------------------------------------------------------------------
// Der Selbsttest zur Ortsfrage -- Paket 0083
// ---------------------------------------------------------------------------
//
// Warum eine Tabelle im Programm und kein zweiter Testfall daneben: dieselbe Lage wie
// bei `NAMENSFAELLE` und `ZITATFAELLE`. Die `CMakeLists.txt` gehoert Paket 0059 und
// steht nicht in der Dateiliste dieses Pakets.
//
// **Was sie prueft, was der Bestand nicht hergibt: den roten Fall.** Der Bestand traegt
// am 2026-09-05 genau **eine** Fundstelle dieser Sorte, und sie ist keine tote -- der
// Riegel kann dort also nur zeigen, dass er gruen bleibt. Die Faelle 3 und 4 unten
// halten die Gegenprobe fest.
//
// **Seit dem Ruecklauf vom 2026-09-05 traegt die Spalte Pfade und keine Namen mehr.**
// Die fuenf Faelle ab dem sechsten sind die, an denen die erste Fassung gruen blieb: Sie
// alle nennen einen Namen, den es unter `bau/` oder `befunde/` als Zwilling gibt, und
// alle bis auf zwei muessen trotzdem tot sein.

struct Zielfall {
    std::string_view name;
    /// Steht der Name im gelesenen Bestand?
    bool im_bestand;
    /// Pfade unterhalb der Wurzel, die in mit Absicht ungelesenen Ordnern liegen,
    /// durch `|` getrennt.
    std::string_view ungelesene;
    Zielart erwartet;
    std::string_view herkunft;
};

constexpr std::array<Zielfall, 17> ZIELFAELLE = {{
    // --- Was gelesen wird, bleibt gelesen ------------------------------------
    {"daten/adressen.md", true, "", Zielart::Gelesen,
     "der Regelfall: alle aufgeloesten Zitate gehen hier durch"},
    {"adressen.md", true, "befunde/messung-0069/baum/daten/adressen.md",
     Zielart::Gelesen,
     "gebaut: derselbe Name liegt zugleich in einem ungelesenen Ordner. Der Bestand "
     "gewinnt -- sonst uebergeht der Riegel, was er lesen darf"},

    // --- Die eine echte Fundstelle dieser Sorte, und ihre Gegenprobe ---------
    {"befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md", false,
     "befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md",
     Zielart::Ungelesen,
     "parameter.toml -- die einzige Fundstelle dieser Sorte im Bestand, gemessen "
     "2026-09-05. Sie muss uebergangen bleiben"},
    {"befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md", false, "",
     Zielart::Tot,
     "dieselbe Stelle, den Bericht weggedacht: Der Ordner allein traegt nichts. Wer "
     "nur den Vorsatz prueft, uebergeht jeden erfundenen Namen mit diesem Vorsatz"},

    // --- Der erfundene Name --------------------------------------------------
    {"spiel-gibt-es-nicht.md", false,
     "bau/kp0010/quelle/specs/0016-hedgefonds/spiel.md|bau/kp0010/quelle/technik.md",
     Zielart::Tot,
     "gebaut: der Rotfall dieses Pakets. Ein aehnlicher Name im ungelesenen Ordner "
     "rettet ihn nicht"},

    // --- Der Ruecklauf vom 2026-09-05: der Ort entscheidet, nicht der Name ---
    {"spiel.md", false, "bau/kp0010/quelle/specs/0016-hedgefonds/spiel.md",
     Zielart::Tot,
     "gemessen: der Vorgang, an dem die erste Fassung gescheitert ist. Faellt spiel.md "
     "aus den Vorgaben, findet der Riegel den Namen unter bau/ wieder. Der Verweis "
     "zeigt nicht dorthin -- er ist tot"},
    {"specs/0016-hedgefonds/spiel.md", false,
     "bau/kp0010/quelle/specs/0016-hedgefonds/spiel.md", Zielart::Tot,
     "gemessen an daten/adressen.md: derselbe Vorgang mit einem laengeren Verweis. Er "
     "ist das Endstueck eines ungelesenen Pfades und nennt trotzdem keinen ungelesenen "
     "Ordner -- das Endstueck allein genuegt nicht"},
    {"bau/kp0010/quelle/specs/0016-hedgefonds/spiel.md", false,
     "bau/kp0010/quelle/specs/0016-hedgefonds/spiel.md", Zielart::Ungelesen,
     "gebaut: die Gegenrichtung derselben zwei Zeilen. Wer den Ordner mitschreibt, "
     "wird uebergangen -- sonst waere die Trennung nur eine strengere Sperre"},
    {"befunde/gibt-es-nicht-2026-09-05.md", false,
     "befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md",
     Zielart::Tot,
     "gebaut: der Ordner stimmt, die Datei liegt dort nicht. Die zweite Haelfte der "
     "Ortsfrage -- ohne sie deckt der Vorsatz befunde/ jeden toten Verweis zu"},
    {"unbefunde/spiel.md", false, "unbefunde/spiel.md", Zielart::Tot,
     "gebaut: ein Ordner, dessen Name auf den ungelesenen endet. Ein Pfadteil zaehlt "
     "nur, wenn er ganz so heisst"},
    {"befunde/x.md", false, "daten/unbefunde/x.md", Zielart::Tot,
     "gebaut: derselbe Griff auf der anderen Seite. Der genannte Pfad ist ein "
     "Endstueck des liegenden, aber nicht an einer Pfadgrenze -- ohne diese Pruefung "
     "traefe ten/x.md in daten/x.md"},
    {"befunde.md", false, "befunde.md", Zielart::Tot,
     "gebaut: der ungelesene Ordnername als Datei. Ohne folgenden Schraegstrich ist er "
     "kein Ordner"},
    {"daten/reihen.toml", false, "bau/kp0027r3/quelle/daten/reihen.toml", Zielart::Tot,
     "gebaut, und die Anwartschaft aus der Pruefung: 153 von 159 Namen des "
     "Zielbestands haben unter bau/ oder befunde/ einen Zwilling. Sobald ein "
     "geprueftes Zitat auf eine vorhabenseigene Datei zeigt, haengt alles an dieser "
     "Zeile"},

    // --- Was seinen Ort selbst ausspricht ------------------------------------
    {"/usr/share/doc/lizenz.md", false, "", Zielart::Ausserhalb,
     "gebaut: ein unbedingter Pfad. Er nennt einen Ort, den keine der beiden Wurzeln "
     "enthaelt -- kein Befund, sondern ein Verweis nach draussen"},
    {"../../CLAUDE.md", false, "", Zielart::Ausserhalb,
     "gebaut: der Aufstieg aus der Wurzel heraus, die zweite Form derselben Sache"},
    {"werkzeuge/../daten/gibt-es-nicht.md", false, "", Zielart::Ausserhalb,
     "gebaut: der Aufstieg steht mitten im Pfad. Ein solcher Name kommt hier nur an, "
     "wenn sein Basisname nicht im Bestand steht; er faellt dann nach draussen statt in "
     "die Befunde -- die nachsichtige Richtung, in der ein Fehler einen ungeprueften "
     "Verweis kostet und kein falsches Rot"},
    {"../befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md", false,
     "befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md",
     Zielart::Ausserhalb,
     "gebaut: derselbe Bericht, aus der Wurzel heraus genannt. Er faellt nach draussen. "
     "Dass die Reihenfolge der beiden Pruefungen das entscheidet, ist ausdruecklich "
     "NICHT gemessen -- vertauscht man sie, aendert sich kein Fall und kein Lauf. Beide "
     "koennen nicht zugleich zutreffen: Ein eingesammelter Pfad beginnt nie mit einem "
     "Schraegstrich und traegt nie zwei Punkte, also findet ein Name, der seinen Ort "
     "nach draussen ausspricht, dort nie eine Datei. Die Reihenfolge ist Ordnung und "
     "keine Regel; diese Zeile haelt den Ausgang fest, nicht ihren Grund"},
}};

Ortsmenge zerlege_orte(std::string_view spalte) {
    Ortsmenge menge;
    std::string laufend;
    for (std::size_t z = 0; z <= spalte.size(); ++z) {
        if (z == spalte.size() || spalte[z] == '|') {
            if (!laufend.empty()) {
                menge.insert(laufend);
            }
            laufend.clear();
        } else {
            laufend += spalte[z];
        }
    }
    return menge;
}

/// Wie viele Faelle nicht wie erwartet ausgingen. Die Abweichungen stehen auf `stderr`.
std::size_t selbsttest_zielart() {
    std::size_t falsch = 0;
    for (std::size_t k = 0; k < ZIELFAELLE.size(); ++k) {
        const Zielfall& fall = ZIELFAELLE[k];
        const Zielart art =
            zielart(fall.name, fall.im_bestand, zerlege_orte(fall.ungelesene));
        if (art != fall.erwartet) {
            ++falsch;
            std::fprintf(stderr,
                         "Zielfall %zu: die Art ist %d, erwartet war %d.\n"
                         "      Name:     %.*s\n      Herkunft: %.*s\n",
                         k + 1, static_cast<int>(art), static_cast<int>(fall.erwartet),
                         static_cast<int>(fall.name.size()), fall.name.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
        }
    }
    return falsch;
}

struct Zitatbefund {
    std::string datei;
    std::size_t zeilennummer = 0;
    std::string ziel;
    std::string ueberschrift;
};

struct Uebergangen {
    std::string datei;
    std::size_t zeilennummer = 0;
    std::string grund;
    std::string ueberschrift;
};

struct Zitatzaehlwerk {
    std::size_t zitate = 0;
    std::size_t aufgeloest = 0;
    /// Wie viele der Zitate ohne Anfuehrung standen -- Paket 0079. Eine eigene Zahl,
    /// damit sich die neue Form von der alten trennen laesst, ohne sie zu zaehlen.
    std::size_t ohne_anfuehrung = 0;
    /// Wie viele Fundstellen ohne Anfuehrung gar kein Zitat waren, weil ihr Absatz
    /// keinen Dokumentnamen nennt. Sie stehen nicht in der Aufzaehlung unten -- es
    /// waeren Hunderte --, aber sie bleiben nicht stumm.
    std::size_t ohne_ziel = 0;
};

/// Wie viele Zitate mindestens aufloesen muessen -- Paket 0083.
///
/// **Eine Zahl im Quelltext und keine aus der Bestandsgroesse abgeleitete Schranke.**
/// Der Grund ist der gemessene Fall selbst: Faellt eine Vorgabendatei weg, faellt die
/// Zahl der aufgeloesten Zitate um die Haelfte, waehrend der Bestand um **eine** Datei
/// schrumpft. Eine Schranke, die am Bestand haengt, wandert dabei um ein Hundertstel
/// mit und verdeckt genau das, was sie fangen soll. Der Preis der festen Zahl ist, dass
/// sie gepflegt werden muss; er wird laut bezahlt -- ein roter Lauf mit Begruendung --
/// und nicht still.
///
/// **Woher die Zahl kommt.** Sie ist gezaehlt und nicht gegriffen: Es sind die
/// aufgeloesten Zitate der sechs Pakete, um derentwillen dieser Riegel existiert, wie
/// sie oben einzeln abgehakt sind -- 0034 zwei, 0035 zwei, 0044 eines, 0047 zwei
/// (die beiden anderen sind Gliederungsziffern), 0050 fuenf, 0057 vier. Unterschreitet
/// der Lauf sie, deckt der Riegel seinen eigenen Anlass nicht mehr ab.
///
/// **Was sie deshalb nicht faengt, ausgeschrieben:** einen Rueckgang von heute 36 auf
/// 17. Das ist Absicht und kein Versehen. Eine Schranke dicht unter dem Tagesstand
/// wuerde bei jeder rechtmaessig entfernten Belegstelle rot und beim naechsten Lauf
/// nachgezogen -- eine Schwelle, die man nachzieht, misst nichts mehr. Der
/// Rueckgang **auf der Zielseite** haengt ohnehin nicht an dieser Zahl: Ein
/// weggefallenes Ziel ist seit diesem Paket ein Befund und kein stiller Abgang.
///
/// **Dass die Zahl hier bleibt, ist seit dem 2026-09-05 gemessen und nicht behauptet.**
/// Der Ruecklauf jenes Tages hat zu Recht angemerkt, dass beide Haelften des Netzes
/// denselben Einbruch durchliessen: Vorgaben ohne `spiel.md` gaben 24 aufgeloeste
/// Zitate, und 24 steht ueber 16. Gefangen wird dieser Einbruch seither von der
/// Ortsfrage und nicht von der Untergrenze -- derselbe Eingriff gibt heute 15 tote
/// Ziele und einen roten Lauf. Die Untergrenze deckt weiter allein die Fundseite ab,
/// wofuer sie da ist; sie hochzuziehen, damit sie die Zielseite mit abdeckte, hiesse
/// eine Schwelle zu pflegen, fuer die es einen Riegel gibt.
constexpr std::size_t AUFGELOEST_MINDESTENS = 16;

/// Laenge des Schluesselworts, das bei `i` **beginnt** -- oder 0.
std::size_t schluessellaenge(std::string_view text, std::size_t i) {
    if (i > 0 && ist_wortzeichen(text[i - 1])) {
        return 0;
    }
    for (std::size_t k = 0; k < SCHLUESSEL.size(); ++k) {
        const std::string_view wort = SCHLUESSEL[k];
        if (text.size() - i >= wort.size() && text.substr(i, wort.size()) == wort) {
            return wort.size();
        }
    }
    return 0;
}

/// Die Anfuehrung, die **bei `j`** beginnt, samt ihrem Inhalt. Rueckgabe ist die Stelle
/// hinter dem Schlusszeichen, oder `npos`, wenn dort keine Anfuehrung steht.
///
/// Eigener Aufruf seit Paket 0086: Die Stelle, an der gesucht wird, ist seither nicht
/// mehr nur die eine unmittelbar hinter dem Schluesselwort.
std::size_t klammer_ab(std::string_view text, std::size_t j, std::string& roh,
                       bool nur_ankuendigende) {
    if (j >= text.size()) {
        return std::string_view::npos;
    }
    for (std::size_t k = 0; k < KLAMMERN.size(); ++k) {
        const Klammer klammer = KLAMMERN[k];
        if (nur_ankuendigende && !klammer.kuendigt_an) {
            continue;
        }
        if (text.size() - j < klammer.auf.size()
            || text.substr(j, klammer.auf.size()) != klammer.auf) {
            continue;
        }
        const std::size_t inhalt = j + klammer.auf.size();
        const std::size_t zu = text.find(klammer.zu, inhalt);
        if (zu == std::string_view::npos || zu == inhalt
            || zu - inhalt > UEBERSCHRIFT_HOECHSTENS) {
            continue;
        }
        roh = std::string(text.substr(inhalt, zu - inhalt));
        while (!roh.empty() && roh.back() == '\\') {
            roh.pop_back();
        }
        return zu + klammer.zu.size();
    }
    return std::string_view::npos;
}

/// Wo die Anfuehrungssuche hinter `i` ansetzt: ueber Leerzeichen hinweg und ueber einen
/// Gegenschraegstrich, mit dem eine C++-Zeichenkette ihr Anfuehrungszeichen maskiert.
std::size_t hinter_leerraum(std::string_view text, std::size_t i) {
    std::size_t j = i;
    while (j < text.size() && text[j] == ' ') {
        ++j;
    }
    if (j < text.size() && text[j] == '\\') {
        ++j;
    }
    return j;
}

/// Liest die Ueberschrift, die bei `i` in Anfuehrung stehen soll. Rueckgabe ist die
/// Laenge des ganzen Zitatteils ab `i`, oder 0, wenn dort keine Anfuehrung steht.
std::size_t ueberschrift_hinter(std::string_view text, std::size_t i, std::string& roh) {
    const std::size_t ende = klammer_ab(text, hinter_leerraum(text, i), roh, false);
    return ende == std::string_view::npos ? 0 : ende - i;
}

/// Wie viele Woerter zwischen dem Schluesselwort und der Anfuehrung stehen duerfen --
/// Paket 0086.
///
/// **Die Zahl ist gemessen und nicht gegriffen.** Sie ist der Abstand der einen Form,
/// um derentwillen dieses Paket existiert: Die dritte Belegstelle aus Paket 0034 in
/// `daten/adressen.md` nennt ihr Schluesselwort und laesst fuenf Woerter folgen, ehe die
/// Anfuehrung beginnt. Was jeder Schritt von null bis acht traegt und kostet, steht im
/// Kopf; gewaehlt ist der kleinste Wert, der die gemessene Form fangt, und nicht der
/// groesste, der noch nichts kaputt macht -- eine Schwelle mit Luft nach oben ist eine
/// geratene.
constexpr std::size_t WORTABSTAND_HOECHSTENS = 5;

/// Endet das Wort, das bei `ende` aufhoert, den Satz? Dieselbe Regel wie in
/// `satzanfang_vor`: Punkt, Ausrufe- oder Fragezeichen mit Leerraum dahinter.
bool schliesst_satz(std::string_view text, std::size_t anfang, std::size_t ende) {
    if (ende <= anfang) {
        return false;
    }
    const char c = text[ende - 1];
    if (c != '.' && c != '!' && c != '?') {
        return false;
    }
    return ende >= text.size() || text[ende] == ' ' || text[ende] == '\t';
}

/// Die Ueberschrift, die **ein bis `WORTABSTAND_HOECHSTENS` Woerter** hinter `i` in
/// Anfuehrung steht -- Paket 0086. Rueckgabe wie bei `ueberschrift_hinter`.
///
/// **Warum ein eigener Aufruf und nicht eine Schleife in jenem.** Der Abstand null ist
/// die sichere Form: Dort kuendigt das Schluesselwort die Anfuehrung unmittelbar an.
/// Erst wenn weder sie noch der Name ohne Anfuehrung dort steht, wird weiter gesucht --
/// so aendert diese Lockerung keine einzige Fundstelle, die der Riegel vorher schon
/// eingeordnet hat, sondern nur solche, die er gar nicht sah.
///
/// **Wo die Suche endet.** Am Satzende, gemessen an derselben Regel wie die Suche nach
/// links, und spaetestens nach der genannten Zahl Woerter. Beides zusammen ist die
/// Antwort auf den Einwand, an dem diese Lockerung haengt: Wer beliebig weit sucht,
/// bindet jede Anfuehrung eines Absatzes an das naechstgelegene Schluesselwort.
///
/// **Und sie endet an einem zweiten Schluesselwort.** Steht zwischen dem Schluesselwort
/// und der Anfuehrung ein weiteres, gehoert die Anfuehrung dem naeheren -- derselbe
/// Grundsatz, nach dem die Suche nach Namen arbeitet, und aus demselben Grund. Der
/// Schaden ohne ihn ist doppelt: Das ferne Schluesselwort naehme dem nahen die
/// Anfuehrung weg **und** ruecke die Leseschleife ueber es hinweg (`i` springt um den
/// ganzen Zitatteil), so dass das nahe gar nicht mehr an die Reihe kaeme. Diese
/// Lockerung verloere damit Zitate, statt welche zu gewinnen.
///
/// **Was daran gemessen ist und was nicht, ausgeschrieben.** Auf dem Bestand vom
/// 2026-09-05 aendert sein Abschalten **nichts** -- 33 Zitate, 59 Fundstellen, mit und
/// ohne. Der Bestand fuehrt heute keine Stelle dieser Bauart. Nachgewiesen ist der
/// Riegel deshalb nicht am Bestand, sondern an Fall 5 in `ABSTANDSFAELLE`, der die Form
/// eigens baut; ohne ihn waere er Zierde. Er steht hier trotzdem, weil die Lockerung
/// selbst die Bauart erst moeglich macht, die er faengt.
std::size_t ueberschrift_mit_abstand(std::string_view text, std::size_t i,
                                     std::string& roh) {
    std::size_t j = i;
    for (std::size_t woerter = 0; woerter < WORTABSTAND_HOECHSTENS; ++woerter) {
        // Ein Wort ueberspringen: erst der Leerraum davor, dann das Wort selbst.
        std::size_t anfang = j;
        while (anfang < text.size() && (text[anfang] == ' ' || text[anfang] == '\t')) {
            ++anfang;
        }
        std::size_t ende = anfang;
        while (ende < text.size() && text[ende] != ' ' && text[ende] != '\t') {
            ++ende;
        }
        if (ende == anfang) {
            return 0;  // nichts mehr da
        }
        if (schliesst_satz(text, anfang, ende)) {
            return 0;
        }
        for (std::size_t k = anfang; k < ende; ++k) {
            if (schluessellaenge(text, k) != 0) {
                return 0;
            }
        }
        j = ende;
        const std::size_t schluss = klammer_ab(text, hinter_leerraum(text, j), roh, true);
        if (schluss != std::string_view::npos) {
            return schluss - i;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Bedingung 2, Teil 1b: der Name ohne Anfuehrung -- Paket 0079
// ---------------------------------------------------------------------------

/// Zeichen, an dem ein Name ohne Anfuehrung spaetestens endet. Der Halbgeviert- und
/// der Geviertstrich stehen bewusst **nicht** darunter: Die Zieldateien fuehren sie
/// mitten in ihren Ueberschriften, und wer an ihnen abbraeche, schnitte den Namen vor
/// seinem Ende ab.
///
/// Ein Punkt zaehlt nur mit Leerraum dahinter -- dieselbe Regel wie bei der Suche nach
/// links und aus demselben Grund: Ein Punkt ohne ihn steht regelmaessig in einer
/// Jahreszahl, einer Fassungsnummer oder einer Endung.
bool ist_namensende(std::string_view text, std::size_t i) {
    const unsigned char c = static_cast<unsigned char>(text[i]);
    if (c == ',' || c == ';' || c == ':' || c == '(' || c == ')' || c == '['
        || c == ']' || c == '"' || c == '\'' || c == '`' || c == '!' || c == '?'
        || c == '|' || c == '\\') {
        return true;
    }
    if (c == '.') {
        return i + 1 >= text.size() || text[i + 1] == ' ' || text[i + 1] == '\t';
    }
    // Die typografischen Anfuehrungszeichen (U+2018, U+2019, U+201C bis U+201E).
    // Der Gedankenstrich (U+2013, U+2014) teilt ihr erstes Byte und faellt hier
    // absichtlich nicht darunter.
    if (c == 0xE2 && i + 2 < text.size()
        && static_cast<unsigned char>(text[i + 1]) == 0x80) {
        const unsigned char d = static_cast<unsigned char>(text[i + 2]);
        return d == 0x98 || d == 0x99 || d == 0x9C || d == 0x9D || d == 0x9E;
    }
    return false;
}

/// Beginnt hier ein Name? Ein Grossbuchstabe oder eine Ziffer. Das ist die
/// Eigenschaft, an der sich ein zitierter Name vom laufenden Satz trennt: Eine
/// Ueberschrift dieses Vorhabens beginnt mit dem einen oder dem anderen, ein
/// Verhaeltniswort im Satz mit keinem von beiden.
bool ist_namensanfang(std::string_view text, std::size_t i) {
    const unsigned char c = static_cast<unsigned char>(text[i]);
    if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
        return true;
    }
    if (c == 0xC3 && i + 1 < text.size()) {
        const unsigned char d = static_cast<unsigned char>(text[i + 1]);
        return d == 0x84 || d == 0x96 || d == 0x9C;  // die drei grossen Umlaute
    }
    return false;
}

/// Der Name ohne Anfuehrung hinter dem Schluesselwort. Rueckgabe ist die Laenge des
/// ganzen Teils ab `i` samt der Leerzeichen davor, oder 0, wenn dort keiner steht.
///
/// **Mindestens ein Leerzeichen** ist Bedingung, und es traegt mehr, als es aussieht:
/// Ohne es faenden sich die zusammengesetzten Woerter mit, die dieser Quelltext selbst
/// in Menge fuehrt -- und der Riegel suchte dann eine Ueberschrift hinter der eigenen
/// Wortmitte.
///
/// **Der Name endet spaetestens dort, wo seine Zeile endet** -- Paket 0105. Die Grenze
/// ist die Zeile des ersten Zeichens des Namens und nicht die des Schluesselworts: Steht
/// das Wort am Zeilenende und der Name darunter, ist der Name trotzdem einer.
std::size_t name_ohne_anfuehrung(const Absatz& absatz, std::size_t i, std::string& roh) {
    const std::string_view text = absatz.text;
    std::size_t j = i;
    while (j < text.size() && text[j] == ' ') {
        ++j;
    }
    if (j == i || j >= text.size() || !ist_namensanfang(text, j)) {
        return 0;
    }
    const std::size_t heimatzeile = absatz.zeile_bei(j);
    std::size_t ende = j;
    while (ende < text.size() && ende - j < UEBERSCHRIFT_HOECHSTENS
           && absatz.zeile_bei(ende) == heimatzeile && !ist_namensende(text, ende)) {
        ++ende;
    }
    while (ende > j && (text[ende - 1] == ' ' || text[ende - 1] == '\t')) {
        --ende;
    }
    if (ende == j) {
        return 0;
    }
    roh = std::string(text.substr(j, ende - j));
    return ende - i;
}

// ---------------------------------------------------------------------------
// Der Selbsttest zum Wortabstand und zur Suche nach rechts -- Paket 0086
// ---------------------------------------------------------------------------
//
// Warum als Tabelle im Programm und nicht als zweiter Testfall daneben: dieselbe
// Begruendung wie bei den drei Tabellen davor -- die `CMakeLists.txt` gehoert Paket
// 0059 und steht nicht in der Dateiliste dieses Pakets.
//
// **Diese Tabelle traegt mehr als die anderen**, und das ist kein Ehrgeiz, sondern die
// Lage: Von den drei Riegeln, die diese Lockerung eingrenzen, sind zwei am Bestand
// gemessen (die Trennung der Zitatmarken kostet ohne sie fuenf falsche Befunde, die
// Satzgrenze rechts einen), der dritte aber **nicht** -- der Bestand fuehrt heute keine
// Stelle mit zwei Schluesselwoertern vor einer Anfuehrung. Fall 5 baut sie. Ohne ihn
// waere jener Riegel eine Behauptung.
//
// Das Schluesselwort ist in jeder Zeile maskiert (`\101` ist `A`, `\164` ist `t`), aus
// demselben Grund wie in den Tabellen davor: Zur Laufzeit steht das Wort da, im
// Dateitext nicht -- sonst faende der Riegel diese Faelle beim Lesen des eigenen
// Quelltexts und meldete sich selbst. Der Selbsttest prueft deshalb zuerst, dass jede
// Zeile ueberhaupt noch ein Schluesselwort hergibt.

struct Abstandsfall {
    std::string_view zeile;
    /// Die Ueberschrift, die mit Abstand hinter dem Schluesselwort gefunden werden
    /// muss. **Leer heisst: keine** -- ohne diese Haelfte wiese die Tabelle nur nach,
    /// dass die Lockerung *etwas* faengt, und nicht, dass sie das Richtige faengt.
    std::string_view erwartet;
    /// Der Dokumentname rechts vom Zitat. Nur geprueft, wenn oben eine Ueberschrift
    /// erwartet wird; leer heisst auch hier: es darf keiner gefunden werden.
    std::string_view rechts;
    std::string_view herkunft;
};

constexpr std::array<Abstandsfall, 8> ABSTANDSFAELLE = {{
    // --- Die Form, um derentwillen dieses Paket existiert ---------------------
    {"T46 zaehlt seine elf Vorgabeadressen abschliessend auf -- die \303\234berschrif\164"
     " der Tabelle sagt es selbst: \342\200\236T46 -- Die elf Adressen, deren Herkunft "
     "dieses Dokument ist, abschliessend\342\200\234 (`technik.md`; am 2026-09-03,",
     "T46 -- Die elf Adressen, deren Herkunft dieses Dokument ist, abschliessend",
     "technik.md",
     "daten/adressen.md, Herleitung zu land.CN.wechselkurs -- die dritte Belegstelle aus "
     "Paket 0034, gemessen 2026-09-05. Fuenf Woerter Abstand, Dokumentname rechts: beide "
     "Lockerungen zusammen, und keine allein reicht"},

    // --- Wo die Schwelle endet -----------------------------------------------
    // Die Wortzahlen sind nachgezaehlt und nicht geschaetzt: Beide Faelle sind beim
    // Rotnachweis am 2026-09-05 zuerst **nicht** rot geworden, weil die gezaehlte Zahl
    // nicht die gebaute war -- der eine hatte acht Woerter statt sechs, den anderen
    // stoppte die Wortzahl statt des Satzendes. Ein Fall, der aus dem falschen Grund
    // gruen ist, misst die Regel nicht, die sein Text behauptet.
    {"die \303\234berschrif\164 der Tabelle sagt es hier selbst: "
     "\342\200\236Ein Wort zu weit\342\200\234 (`technik.md`)", "", "",
     "gebaut: sechs Woerter dazwischen (der, Tabelle, sagt, es, hier, selbst:). Der "
     "Fall, der die Schwelle misst -- ohne ihn waere sie behauptet und nicht gewaehlt"},
    {"die \303\234berschrif\164 der Tabelle. Dann folgt \342\200\236Ein neuer "
     "Satz\342\200\234 (`technik.md`)", "", "",
     "gebaut: das Satzende faellt auf das zweite Wort und beendet die Suche, waehrend "
     "die Anfuehrung im vierten noch innerhalb der fuenf laege. Dieselbe Regel wie bei "
     "der Suche nach links und aus demselben Grund"},

    // --- Was nur bei Abstand null durchgeht ----------------------------------
    {"eine \303\234berschrif\164 aus `spiel.md`, die im Ziel ein Eszett traegt", "", "",
     "werkzeuge/belegstellen/belegstellen_riegel.cpp, Kopfkommentar -- gemessen "
     "2026-09-05: Ohne die Trennung der Zitatmarken faengt sich der Riegel hier selbst. "
     "Der Gegenstrich zeichnet Code aus und kuendigt kein Zitat an"},

    // --- Der Riegel, den der Bestand nicht hergibt ---------------------------
    {"laut \303\234berschrif\164 steht der \101bschni\164\164 \342\200\236Die "
     "Schleife\342\200\234 in `spiel.md`", "", "",
     "gebaut: zwei Schluesselwoerter vor einer Anfuehrung. Sie gehoert dem naeheren -- "
     "das ferne nimmt sie ihm sonst weg und ruecke die Leseschleife ueber es hinweg. "
     "Der einzige der drei Riegel, den der Bestand am 2026-09-05 nicht misst"},

    // --- Die Suche nach rechts, einzeln --------------------------------------
    {"laut \101bschni\164\164 mit dem Titel \342\200\236Die Schleife\342\200\234 "
     "und dann noch etwas Text. Aber `spiel.md` steht im naechsten Satz",
     "Die Schleife", "",
     "gebaut: der Name steht rechts, aber hinter dem Satzende. Der Fall, der die "
     "Satzgrenze der Rechtssuche misst -- ohne sie wird eine Fundstelle im Bestand zu "
     "Unrecht rot, gemessen 2026-09-05"},
    {"laut \101bschni\164\164 mit dem Titel \342\200\236Die Schleife\342\200\234, "
     "nachzulesen in `spiel.md` und sonst nirgends",
     "Die Schleife", "spiel.md",
     "gebaut: der Regelfall der Rechtssuche -- Name im selben Satz, hinter dem Zitat"},
    {"laut \101bschni\164\164 mit dem Titel \342\200\236Die Schleife\342\200\234, "
     "und dahinter steht ueberhaupt kein Dokumentname mehr",
     "Die Schleife", "",
     "gebaut: rechts steht nichts. Die erwartete Leermeldung, ohne die der Fall "
     "darueber nur zeigte, dass die Suche etwas findet"},
}};

/// Wie viele Faelle nicht wie erwartet ausgingen. Die Abweichungen stehen auf `stderr`.
///
/// Gemessen wird derselbe Weg, den der Lauf ueber den Bestand nimmt: erst das
/// Schluesselwort mit `schluessellaenge`, dann `ueberschrift_mit_abstand`, dann
/// `verweis_rechts` hinter dem Zitatteil. Ein im Test nachgebauter Weg pruefte zwei
/// Fassungen, von denen nur eine laeuft.
std::size_t selbsttest_abstand() {
    std::size_t falsch = 0;
    for (std::size_t k = 0; k < ABSTANDSFAELLE.size(); ++k) {
        const Abstandsfall& fall = ABSTANDSFAELLE[k];

        std::size_t i = 0;
        std::size_t schluessel = 0;
        while (i < fall.zeile.size()) {
            schluessel = schluessellaenge(fall.zeile, i);
            if (schluessel != 0) {
                break;
            }
            ++i;
        }
        if (schluessel == 0) {
            ++falsch;
            std::fprintf(stderr,
                         "Selbsttest Abstand %zu: kein Schluesselwort. Der Fall misst "
                         "damit nichts mehr -- vermutlich ist die Maskierung "
                         "verrutscht.\n      Zeile:    %.*s\n      Herkunft: %.*s\n",
                         k + 1, static_cast<int>(fall.zeile.size()), fall.zeile.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
            continue;
        }

        std::string roh;
        const std::size_t zitatteil =
            ueberschrift_mit_abstand(fall.zeile, i + schluessel, roh);
        const std::string_view gefunden =
            zitatteil == 0 ? std::string_view{} : std::string_view(roh);
        if (gefunden != fall.erwartet) {
            ++falsch;
            std::fprintf(stderr,
                         "Selbsttest Abstand %zu: erwartet war %s, gefunden wurde %s.\n"
                         "      Zeile:    %.*s\n      Herkunft: %.*s\n", k + 1,
                         // Kein ausgeschriebenes Schluesselwort in dieser Meldung: Es
                         // traegt hier unmittelbar ein Anfuehrungszeichen hinter sich,
                         // und der Riegel faende sich damit in seinem eigenen
                         // Quelltext -- gemessen 2026-09-05, er meldete eine
                         // uebergangene Fundstelle, deren gesuchter Name die halbe
                         // naechste Anweisung war.
                         fall.erwartet.empty() ? "keinen Wortlaut"
                                               : std::string(fall.erwartet).c_str(),
                         zitatteil == 0 ? "keine" : roh.c_str(),
                         static_cast<int>(fall.zeile.size()), fall.zeile.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
            continue;
        }
        if (zitatteil == 0) {
            continue;  // ohne Zitat gibt es rechts nichts nachzuschlagen
        }

        std::string name;
        bool netzadresse = false;
        const bool hat =
            verweis_rechts(fall.zeile, i + schluessel + zitatteil, name, netzadresse);
        const std::string_view rechts = hat ? std::string_view(name) : std::string_view{};
        if (rechts != fall.rechts) {
            ++falsch;
            std::fprintf(stderr,
                         "Selbsttest Abstand %zu: rechts erwartet war %s, gefunden "
                         "wurde %s.\n      Zeile:    %.*s\n      Herkunft: %.*s\n", k + 1,
                         fall.rechts.empty() ? "kein Dateiname"
                                             : std::string(fall.rechts).c_str(),
                         hat ? name.c_str() : "keiner",
                         static_cast<int>(fall.zeile.size()), fall.zeile.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
        }
    }
    return falsch;
}

// ---------------------------------------------------------------------------
// Der Selbsttest zur Satzgrenze nach links -- Paket 0079, zweiter Teil
// ---------------------------------------------------------------------------
//
// Warum als Tabelle im Programm und nicht als zweiter Testfall daneben: dieselbe
// Begruendung wie bei den vier Tabellen davor -- die `CMakeLists.txt` gehoert Paket
// 0059 und steht nicht in der Dateiliste dieses Pakets.
//
// **Was sie festhaelt, ist die Gegenprobe zu sich selbst.** Jeder Fall sagt zweierlei:
// was die Suche mit der Schranke findet und was sie ohne sie faende. Ein Fall, dessen
// beide Spalten gleich lauten, misst die Schranke nicht -- er misst, dass sie nichts
// wegnimmt, und auch das gehoert dazu. Zwei der fuenf Faelle unten lauten verschieden;
// sie sind es, die rot werden, wenn jemand die Schranke herausnimmt oder sie auf die
// Form mit Anfuehrung ausdehnt.
//
// Die Schluesselwoerter sind maskiert (`\101` ist `A`, `\164` ist `t`), aus demselben
// Grund wie in den Tabellen davor.

struct Satzfall {
    std::string_view zeile;
    /// Nimmt diese Stelle den Weg ohne Anfuehrung? Davon haengt die Schranke ab, und
    /// deshalb wird sie gemessen und nicht angenommen.
    bool ohne_anfuehrung;
    /// Der Dokumentname, den die Suche auf dem Weg findet, den der Lauf nimmt.
    /// **Leer heisst: keiner** -- die Haelfte, ohne die der Fall nur zeigte, dass die
    /// Suche etwas findet.
    std::string_view gebunden;
    /// Der Dokumentname, den dieselbe Suche ueber den ganzen Absatz faende. Lautet er
    /// anders als oben, ist dieser Fall ein Rothebel fuer die Schranke.
    std::string_view ungebunden;
    std::string_view herkunft;
};

constexpr std::array<Satzfall, 5> SATZFAELLE = {{
    // --- Der Fall, um dessentwillen die Schranke da ist -----------------------
    {"`werkzeugkette.cmake` haelt seit dem 2026-09-04 die Messung. Die Zahl ist von "
     "dort gewandert -- sie hat einen \101bsa\164z Rechtfertigung und sechs "
     "zusaetzliche Baulaeufe gekostet",
     true, "", "werkzeugkette.cmake",
     "rueckstand.md, Abnitt zur Zielzahl -- gemessen am 2026-09-05, und zwar als roter "
     "Lauf: Der Dokumentname steht zwei Saetze weiter oben und hat mit dem Wort hier "
     "nichts zu tun. Ohne die Schranke wird diese Stelle ein Befund an einem Satz, an "
     "dem nichts kaputt ist"},

    // --- Der Regelfall, den die Schranke nicht anruehrt -----------------------
    {"daten/lizenzbefund-reihen.md, \101bschni\164\164 Reihe 1, den Block unter der "
     "Zwischenzeile",
     true, "daten/lizenzbefund-reihen.md", "daten/lizenzbefund-reihen.md",
     "daten/reihen.toml, Feld schnitt_2_offen -- Paket 0047. Name und Wort stehen im "
     "selben Satz; das ist die Lage, in der die Form ohne Anfuehrung ueberhaupt "
     "vorkommt"},

    // --- Dass die Schranke nur den neuen Weg bindet ---------------------------
    {"Der Bau steht in `schranken_probe.cpp` und wird dort gerechnet. Der "
     "\101bschni\164\164 \342\200\236Die Schleife\342\200\234 sagt, wie oft",
     false, "schranken_probe.cpp", "schranken_probe.cpp",
     "gebaut nach kern/test/schranken_probe.cpp, dem Fall aus Paket 0067: Dateiname "
     "vier Zeilen ueber der Anfuehrung. Mit Anfuehrung gilt der ganze Absatz weiter -- "
     "wer die Schranke unbedingt macht, macht diesen Fall rot und nimmt Paket 0067 "
     "seine gemessene Fassung"},

    // --- Was die Schranke kostet, ausgeschrieben ------------------------------
    {"Nachzulesen ist das alles in `spiel.md`. \101bschni\164\164 Die Schleife sagt "
     "es dann genauer",
     true, "", "spiel.md",
     "gebaut: der Preis der Schranke. Steht der Name im Satz davor, bleibt die Stelle "
     "ohne Ziel -- gezaehlt, aber nicht bewertet. Die Richtung ist gewollt und dieselbe "
     "wie bei `satzanfang_vor`: zu streng laesst eine Stelle durch, zu nachsichtig "
     "bindet sie an die falsche Datei"},

    // --- Die erwartete Leermeldung -------------------------------------------
    {"Hier steht ueberhaupt kein Dokumentname, und dann folgt \101bsa\164z Sieben mit "
     "seinem Namen",
     true, "", "",
     "gebaut: ohne diesen Fall waeren die zwei leeren Spalten oben auch dann gruen, "
     "wenn die Suche gar nichts mehr faende"},
}};

/// Wie viele Faelle nicht wie erwartet ausgingen. Die Abweichungen stehen auf `stderr`.
///
/// Gemessen wird derselbe Weg, den der Lauf ueber den Bestand nimmt: erst das
/// Schluesselwort, dann die beiden unmittelbaren Zitatformen, dann `suchuntergrenze`
/// und `naechster_verweis`. Die Form mit Wortabstand bleibt aussen vor -- sie kann den
/// Weg ohne Anfuehrung nicht auswaehlen und aendert an der Schranke nichts.
std::size_t selbsttest_satzgrenze() {
    std::size_t falsch = 0;
    for (std::size_t k = 0; k < SATZFAELLE.size(); ++k) {
        const Satzfall& fall = SATZFAELLE[k];
        // Derselbe Weg wie im Ernstfall, seit Paket 0105 auch beim Zusammenziehen: Der
        // Absatz wird gebaut und nicht nachgebaut. Ein Fall ohne `\n` ergibt genau
        // seinen eigenen Wortlaut, die fuenf Faelle unten messen also unveraendert.
        const Absatz absatz = absatz_aus_fall(fall.zeile);
        const std::string_view zeile = absatz.text;

        std::size_t i = 0;
        std::size_t schluessel = 0;
        while (i < zeile.size()) {
            schluessel = schluessellaenge(zeile, i);
            if (schluessel != 0) {
                break;
            }
            ++i;
        }
        if (schluessel == 0) {
            ++falsch;
            std::fprintf(stderr,
                         "Selbsttest Satzgrenze %zu: kein Schluesselwort. Der Fall "
                         "misst damit nichts mehr -- vermutlich ist die Maskierung "
                         "verrutscht.\n      Zeile:    %.*s\n      Herkunft: %.*s\n",
                         k + 1, static_cast<int>(fall.zeile.size()), fall.zeile.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
            continue;
        }

        std::string roh;
        bool ohne = false;
        if (ueberschrift_hinter(zeile, i + schluessel, roh) == 0) {
            ohne = name_ohne_anfuehrung(absatz, i + schluessel, roh) != 0;
        }
        if (ohne != fall.ohne_anfuehrung) {
            ++falsch;
            std::fprintf(stderr,
                         "Selbsttest Satzgrenze %zu: der Weg ohne Anfuehrung war %s, "
                         "genommen wurde er %s.\n      Zeile:    %.*s\n"
                         "      Herkunft: %.*s\n", k + 1,
                         fall.ohne_anfuehrung ? "erwartet" : "nicht erwartet",
                         ohne ? "doch" : "nicht",
                         static_cast<int>(fall.zeile.size()), fall.zeile.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
            continue;
        }

        std::string name;
        bool netzadresse = false;
        const bool hat = naechster_verweis(zeile, i, suchuntergrenze(zeile, i, ohne),
                                           name, netzadresse);
        const std::string_view gebunden =
            hat ? std::string_view(name) : std::string_view{};
        if (gebunden != fall.gebunden) {
            ++falsch;
            std::fprintf(stderr,
                         "Selbsttest Satzgrenze %zu: gebunden erwartet war %s, gefunden "
                         "wurde %s.\n      Zeile:    %.*s\n      Herkunft: %.*s\n",
                         k + 1,
                         fall.gebunden.empty() ? "kein Dateiname"
                                               : std::string(fall.gebunden).c_str(),
                         hat ? name.c_str() : "keiner",
                         static_cast<int>(fall.zeile.size()), fall.zeile.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
            continue;
        }

        std::string weit;
        const bool hat_weit = naechster_verweis(zeile, i, 0, weit, netzadresse);
        const std::string_view ungebunden =
            hat_weit ? std::string_view(weit) : std::string_view{};
        if (ungebunden != fall.ungebunden) {
            ++falsch;
            std::fprintf(stderr,
                         "Selbsttest Satzgrenze %zu: ungebunden erwartet war %s, "
                         "gefunden wurde %s.\n      Zeile:    %.*s\n"
                         "      Herkunft: %.*s\n", k + 1,
                         fall.ungebunden.empty() ? "kein Dateiname"
                                                 : std::string(fall.ungebunden).c_str(),
                         hat_weit ? weit.c_str() : "keiner",
                         static_cast<int>(fall.zeile.size()), fall.zeile.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
        }
    }
    return falsch;
}

/// Das erste Wort einer normierten Zeichenkette.
std::string_view erstes_wort(std::string_view text) {
    const std::size_t raum = text.find(' ');
    return raum == std::string_view::npos ? text : text.substr(0, raum);
}

/// Ein Wort aus Ziffern mit hoechstens einem Buchstaben dahinter -- die Gestalt einer
/// Gliederungsziffer.
bool ist_ziffernwort(std::string_view wort) {
    if (wort.empty() || !ist_ziffer(wort.front())) {
        return false;
    }
    std::size_t k = 0;
    while (k < wort.size() && ist_ziffer(wort[k])) {
        ++k;
    }
    if (k == wort.size()) {
        return true;
    }
    return k + 1 == wort.size() && ist_wortzeichen(wort[k]);
}

/// Steht `kandidat` am Anfang von `ueberschrift`, und endet er dort an einer
/// Wortgrenze?
///
/// **Der Punkt gilt nicht als Wortgrenze.** An diesem einen Zeichen haengt die ganze
/// Unterscheidung zwischen einer Gliederungsziffer und einem Namen; die Begruendung
/// steht im Kopf.
bool ist_wortpraefix(const std::string& ueberschrift, const std::string& kandidat) {
    if (kandidat.empty() || ueberschrift.size() < kandidat.size()) {
        return false;
    }
    if (ueberschrift.compare(0, kandidat.size(), kandidat) != 0) {
        return false;
    }
    if (ueberschrift.size() == kandidat.size()) {
        return true;
    }
    const char n = ueberschrift[kandidat.size()];
    return n != '.' && !ist_wortzeichen(n);
}

/// Fuehrt die Zieldatei eine Ueberschrift, die mit genau dieser Ziffer und einem Punkt
/// beginnt? Das ist die zweite Haelfte derselben Eigenschaft, an der oben schon der
/// Wortpraefix haengt: Der Punkt zeigt an, dass diese Datei ihre Abschnitte ueberhaupt
/// nummeriert. Ohne ihn ist eine Ziffer am Anfang eines Zitats keine Nummer, sondern der
/// Anfang eines Namens -- und ein Name, der nicht aufgeht, ist ein Befund.
bool fuehrt_gliederungsziffer(std::string_view ziffer,
                              const std::vector<std::string>& ueberschriften) {
    for (std::size_t u = 0; u < ueberschriften.size(); ++u) {
        const std::string& ueberschrift = ueberschriften[u];
        if (ueberschrift.size() > ziffer.size()
            && ueberschrift.compare(0, ziffer.size(), ziffer) == 0
            && ueberschrift[ziffer.size()] == '.') {
            return true;
        }
    }
    return false;
}

/// Was ein Name ohne Anfuehrung ist, wenn die Ueberschriften der Zieldatei vorliegen.
enum class Namensart {
    Ueberschrift,   ///< steht am Anfang einer Ueberschrift -- aufgeloest
    Ziffer,         ///< eine Gliederungsziffer -- uebergangen, ohne Wortlaut
    Einzelzeichen,  ///< ein Formelzeichen oder ein Platzhalter -- uebergangen
    Ohne_Gliederung,///< die Zieldatei fuehrt keine Ueberschrift -- uebergangen
    Tot             ///< ein Name, den die Zieldatei nicht fuehrt -- Befund
};

/// Die ganze Entscheidung an einer Stelle. Sie steht als eigene Funktion da, damit der
/// Selbsttest unten **denselben** Weg misst wie der Lauf ueber den Bestand -- dieselbe
/// Ueberlegung wie bei `fund_ab` und aus demselben Grund.
Namensart namensart(const std::string& gesucht,
                    const std::vector<std::string>& ueberschriften,
                    const std::vector<std::string>& eigene) {
    // Eine Zieldatei ohne jede Ueberschrift kann ein Zitat weder bestaetigen noch
    // widerlegen. Das ist kein gedachter Fall: `rueckstand.md` verweist an einer Stelle
    // auf einen eigenen Abschnitt, und der naechstgelegene Dokumentname im Absatz ist
    // eine Kopfdatei des Kerns. Der Riegel wuerde dort rot an einer Sache, die nicht
    // kaputt ist -- er uebergeht sie und nennt den Grund.
    if (ueberschriften.empty()) {
        return Namensart::Ohne_Gliederung;
    }
    for (std::size_t u = 0; u < ueberschriften.size(); ++u) {
        if (ist_wortpraefix(ueberschriften[u], gesucht)) {
            return Namensart::Ueberschrift;
        }
    }
    // Die zitierende Datei zaehlt bei der Ziffer mit, und das ist gemessen: In
    // `einheitenbefund-pwt-baci.md` steht ein Verweis auf einen **eigenen** Abschnitt,
    // waehrend der naechstgelegene Dokumentname im Absatz eine fremde Datei nennt. Wer
    // nur die Zieldatei fragt, wird dort rot an einem Verweis, der stimmt.
    const std::string_view kopfwort = erstes_wort(gesucht);
    if (ist_ziffernwort(kopfwort)
        && (kopfwort.size() == gesucht.size()
            || fuehrt_gliederungsziffer(kopfwort, ueberschriften)
            || fuehrt_gliederungsziffer(kopfwort, eigene))) {
        return Namensart::Ziffer;
    }
    if (kopfwort.size() == 1 && !ist_ziffer(kopfwort.front())) {
        return Namensart::Einzelzeichen;
    }
    return Namensart::Tot;
}

// ---------------------------------------------------------------------------
// Der Schritt, an dem aus einer Art ein Urteil wird -- Paket 0106
// ---------------------------------------------------------------------------
//
// **Warum das eine eigene Funktion ist.** Bis zum 2026-09-05 stand dieser Schritt
// mitten in `pruefe_zitate`, und er war der einzige des Programms, den kein Fall hielt.
// Die Tabellen weiter unten rufen `namensart` unmittelbar auf und messen damit den
// Baustein -- welche Art ein Name hat --, nie die Verdrahtung, die daraus ein Urteil
// macht. Gemessen hiess das: `steht_da` liess sich durch `true` ersetzen, in beiden
// Zweigen, und weder der Selbsttest noch der Lauf ueber den Bestand wurde rot -- auch
// nicht auf einer Kopie mit umbenannter Zielzeile. Ein Riegel, dessen Urteilsschritt
// kein Test haelt, sieht in jedem Lauf aus wie einer, der prueft.
//
// Herausgezogen ist der Schritt messbar, **ohne dass der Selbsttest eine Datei
// braucht**: Was er wissen muss, sind zwei Listen und ein Name. Der Lauf ueber den
// Bestand ruft dieselbe Funktion -- ein im Test nachgebauter Urteilsschritt maesse eine
// Fassung, die nirgends laeuft.

/// Was aus einer Fundstelle wird, deren Zieldatei feststeht.
struct Zitaturteil {
    /// Der gesuchte Name steht in der Zieldatei. Nur gefragt, wenn `grund` leer ist.
    bool steht_da = false;
    /// Nicht leer: die Stelle wird uebergangen und zaehlt gar nicht erst als Zitat.
    std::string grund;
};

/// Die drei Ausgaenge, die `pruefe_zitate` aus einem Urteil zieht.
enum class Zitatausgang {
    Aufgeloest,   ///< zaehlt als Zitat und als aufgeloest
    Befund,       ///< zaehlt als Zitat und kommt in die Befundliste
    Uebergangen   ///< zaehlt gar nicht als Zitat, kommt in die Aufzaehlung der Gruende
};

/// Der Ausgang zu einem Urteil. Eine eigene Funktion aus demselben Grund wie
/// `namensart`: Der Lauf ueber den Bestand und der Selbsttest benutzen **denselben**
/// Aufruf.
///
/// Die Reihenfolge ist die ganze Aussage. Ist ein Grund gesetzt, hat `steht_da` keine
/// Wirkung mehr -- deshalb fragt der Selbsttest nach dem Ausgang und nicht nach
/// `steht_da` fuer sich.
Zitatausgang ausgang(const Zitaturteil& urteil) {
    if (!urteil.grund.empty()) {
        return Zitatausgang::Uebergangen;
    }
    return urteil.steht_da ? Zitatausgang::Aufgeloest : Zitatausgang::Befund;
}

/// Aus der Art wird ein Urteil: aufgeloest, Befund oder uebergangen mit Grund.
///
/// Mit Anfuehrung ist der Name abgegrenzt und wird wortgleich verlangt; ohne sie ist
/// er es nicht, und die Zieldatei grenzt ihn ab -- er muss am Anfang einer ihrer
/// Ueberschriften stehen. `zielanzeige` ist die Zieldatei, wie sie ein Leser sucht;
/// sie steht nur in einem der drei Gruende.
Zitaturteil beurteile_zitat(bool ohne_anfuehrung, const std::string& gesucht,
                            const std::vector<std::string>& liste,
                            const std::vector<std::string>& eigene,
                            const std::string& zielanzeige) {
    Zitaturteil urteil;
    if (ohne_anfuehrung) {
        const Namensart art = namensart(gesucht, liste, eigene);
        if (art == Namensart::Ziffer) {
            urteil.grund = "Gliederungsziffer statt Ueberschrift: "
                           + std::string(erstes_wort(gesucht));
        } else if (art == Namensart::Einzelzeichen) {
            urteil.grund = "einzelnes Zeichen statt Ueberschrift: "
                           + std::string(erstes_wort(gesucht));
        } else if (art == Namensart::Ohne_Gliederung) {
            urteil.grund = "Zieldatei fuehrt keine Ueberschrift: " + zielanzeige;
        }
        urteil.steht_da = art == Namensart::Ueberschrift;
    } else {
        for (std::size_t u = 0; u < liste.size() && !urteil.steht_da; ++u) {
            urteil.steht_da = liste[u] == gesucht;
        }
    }
    return urteil;
}

// ---------------------------------------------------------------------------
// Der Selbsttest zur Form ohne Anfuehrung -- Paket 0079
// ---------------------------------------------------------------------------
//
// Warum eine Tabelle im Programm und kein zweiter Testfall daneben: dieselbe Lage wie
// bei `NAMENSFAELLE`. Die `CMakeLists.txt` gehoert Paket 0059 und steht nicht in der
// Dateiliste dieses Pakets.
//
// **Was sie prueft, was der Bestand nicht hergibt: den roten Fall.** Auf dem Korpus
// dieses Vorhabens loest jedes Zitat ohne Anfuehrung auf -- der Riegel kann dort also
// nur zeigen, dass er gruen wird. Zeile 2 und Zeile 4 unten halten die Gegenprobe: Wird
// die Ueberschrift in der Zieldatei umbenannt, faellt der Name **nicht** in die
// uebergangenen Fundstellen zurueck, sondern wird ein Befund. Genau das ist die Antwort
// auf den Einwand aus dem Kopf.
//
// Die Schluesselwoerter sind maskiert (`\101` ist der Buchstabe `A`): Ohne die Maskierung
// waeren diese Zeilen selbst Fundstellen im eigenen Quelltext, und die Tabelle zaehlte
// in einer Zahl mit, die sie messen soll.

struct Zitatfall {
    /// Der Wortlaut des Falls. Ein `\n` darin ist ein **Zeilenumbruch** und kein
    /// Leerzeichen -- Paket 0105. Zusammengezogen wird er von `absatz_aus_fall`, also
    /// von demselben Aufruf, den der Lauf ueber den Bestand benutzt.
    std::string_view zeile;
    /// Die Ueberschriften der Zieldatei, durch `|` getrennt.
    std::string_view ueberschriften;
    /// Die Ueberschriften der **zitierenden** Datei, ebenso getrennt. Meist leer; sie
    /// traegt nur den Fall, in dem der naechstgelegene Name nicht das Ziel ist.
    std::string_view eigene;
    Namensart erwartet;
    /// Leer heisst: die Stelle ist gar keine Fundstelle (`name_ohne_anfuehrung` gibt 0).
    std::string_view erwarteter_name;
    std::string_view herkunft;
};

constexpr std::array<Zitatfall, 13> ZITATFAELLE = {{
    // --- Die zwei Ueberschriften aus Paket 0047, im Wortlaut ------------------
    {"lizenzbefund-reihen.md, \101bschnitt Reihe 1, den Block unter der Zwischenzeile",
     "Reihe 1 - BIP, konstante Preise - unklar|Reihe 2 - Wertschoepfungsanteil je Sektor",
     "", Namensart::Ueberschrift, "Reihe 1",
     "daten/reihen.toml, Feld schnitt_2_offen -- Paket 0047"},
    {"lizenzbefund-reihen.md, \101bschnitt Reihe 1, den Block unter der Zwischenzeile",
     "Reihe 1a - BIP, konstante Preise - unklar|Reihe 2 - Wertschoepfungsanteil je Sektor",
     "", Namensart::Tot, "Reihe 1",
     "dieselbe Zeile, Ueberschrift umbenannt: der Name faellt nicht in die uebergangenen "
     "Fundstellen zurueck, sondern wird ein Befund -- und er bleibt es, obwohl eine "
     "andere Ueberschrift mit demselben ersten Wort beginnt"},
    {"lizenzbefund-reihen.md, \101bschnitt 2b und 2c, den Block unter der Zwischenzeile",
     "2b und 2c - NV.IND.TOTL.ZS und NV.SRV.TOTL.ZS|2a - NV.AGR.TOTL.ZS",
     "", Namensart::Ueberschrift, "2b und 2c",
     "daten/reihen.toml, Feld schnitt_2_offen -- Paket 0047: eine Aufzaehlung, die mit "
     "einer Ziffer beginnt und trotzdem ein Name ist"},
    {"lizenzbefund-reihen.md, \101bschnitt 2b und 2c, den Block unter der Zwischenzeile",
     "2b, 2c und 2d - NV.IND.TOTL.ZS und NV.SRV.TOTL.ZS|2a - NV.AGR.TOTL.ZS",
     "", Namensart::Tot, "2b und 2c",
     "dieselbe Zeile, Ueberschrift umbenannt -- Befund und nicht Ziffer, obwohl der Name "
     "mit einer Ziffer beginnt: die Zieldatei nummeriert nicht mit ihr"},

    // --- Die zwei Nummern aus Paket 0047 --------------------------------------
    {"daten/lizenzbefund-reihen.md, \101bschnitt 5\"", "5. Zusammenfassung|Reihe 1 - BIP",
     "", Namensart::Ziffer, "5",
     "daten/reihen.toml, Feld beleg unter zaehlung.lizenz -- Paket 0047. Der Punkt "
     "hinter der Fuenf ist die ganze Unterscheidung: ohne ihn waere sie ein Name"},
    {"daten/lizenzbefund-reihen.md, \101bschnitt 3 und 5 -- der IWF-Volltext ist "
     "ungelesen, der Suchauszug",
     "3. Die vier Nicht-WDI-Quellen|5. Zusammenfassung", "", Namensart::Ziffer,
     "3 und 5 -- der IWF-Volltext ist ungelesen",
     "daten/reihen.toml, Feld bestritten_durch: zwei Nummern in einem Satz. Der Name "
     "reicht bis zum Komma und steht an keinem Ueberschriftenanfang -- die Ziffer davor "
     "entscheidet, nicht die Laenge"},

    // --- Was uebergangen wird, obwohl es aussieht wie ein toter Name -----------
    {"reihen.toml Schritt 1, \101bschnitt 6 an die Stelle der Frage",
     "1. BACI-Handelswert|Reihe 14", "6. Reihe 16 -- mitbeantwortet",
     Namensart::Ziffer, "6 an die Stelle der Frage",
     "daten/einheitenbefund-pwt-baci.md: ein Verweis auf einen **eigenen** Abschnitt, "
     "waehrend der naechstgelegene Name eine fremde Datei nennt. Ohne die dritte Spalte "
     "waere das ein Befund an einer Stelle, die stimmt"},
    {"werte.hpp und was daraus folgt, \101bschnitt 18 nennt drei von sechs Stellen", "",
     "", Namensart::Ohne_Gliederung, "18 nennt drei von sechs Stellen",
     "rueckstand.md: die Zieldatei ist eine Kopfdatei und fuehrt keine einzige "
     "Ueberschrift -- sie kann das Zitat weder bestaetigen noch widerlegen"},

    // --- Was gar keine Fundstelle ist ------------------------------------------
    {"spiel.md, \101bschnitt zur Partielaenge R und was daraus folgt", "Die Schleife", "",
     Namensart::Tot, "",
     "daten/reihen.toml, Feld beleg zu zaehlung.soll: ein Kleinbuchstabe hinter dem "
     "Schluesselwort -- laufender Satz, kein Zitat"},

    // --- Der Zeilenumbruch -- Paket 0105 ---------------------------------------
    //
    // Die vier Faelle unten sind die einzigen der Tabelle mit einem `\n`. Sie messen
    // **zwei** Haelften der Regel, und das ist am 2026-09-05 mit zwei Mutanten
    // getrennt gemessen worden -- kein Fall reisst bei beiden:
    //
    //   Faellt die Zeilengrenze ganz weg, reissen die Faelle 1, 2 und 4 dieser Gruppe
    //   an der Namensspalte (3 von 51 des ganzen Selbsttests). Fall 4 ist der, der
    //   den Preis der Regel ausschreibt -- er misst sie damit mit und laeuft nicht
    //   bloss mit.
    //
    //   Haengt die Grenze an der Zeile des Schluesselworts statt an der des Namens,
    //   reisst allein Fall 3 (1 von 51), und zwar mit leerer Namensspalte: Die Stelle
    //   ist dann gar keine Fundstelle mehr.
    //
    // Beim ersten Anlauf griff der zweite Mutant daneben und lief gruen durch. Der
    // Grund steht in `haenge_zeile_an` und gehoert hierher, weil er die Tabelle
    // erklaert: Das Leerzeichen, zu dem der Umbruch wird, traegt bereits die Nummer
    // der **neuen** Zeile. Wer an der Stelle unmittelbar hinter dem Schluesselwort
    // fragt, fragt deshalb schon die Zeile des Namens.
    {"lizenzbefund-reihen.md, \101bschnitt Reihe 1\n"
     "und wird dort nicht bestritten",
     "Reihe 1 - BIP, konstante Preise - unklar|Reihe 2 - Wertschoepfungsanteil je Sektor",
     "", Namensart::Ueberschrift, "Reihe 1",
     "der Fall, um dessentwillen dieses Paket existiert -- gemessen am 2026-09-05 als "
     "roter Lauf an einer angehaengten Belegstelle in `rueckstand.md`. Ohne die Regel "
     "lautet der gesuchte Name 'Reihe 1 und wird dort nicht bestritten' und die Stelle "
     "wird ein Befund, an dem nichts kaputt ist"},
    {"lizenzbefund-reihen.md, \101bschnitt Reihe 1\n"
     "und wird dort nicht bestritten",
     "Reihe 1a - BIP, konstante Preise - unklar|Reihe 2 - Wertschoepfungsanteil je Sektor",
     "", Namensart::Tot, "Reihe 1",
     "dieselben zwei Zeilen, Ueberschrift umbenannt: **die Lockerung laesst keine tote "
     "Belegstelle durch.** Sie kuerzt den Namen, sie verzeiht ihn nicht -- was die "
     "Zieldatei nicht fuehrt, bleibt ein Befund"},
    {"lizenzbefund-reihen.md, \101bschnitt\n"
     "Reihe 1, der Block unter der Zwischenzeile",
     "Reihe 1 - BIP, konstante Preise - unklar", "", Namensart::Ueberschrift, "Reihe 1",
     "gebaut: das Schluesselwort am Zeilenende, der Name darunter. Die Grenze ist die "
     "Zeile des **Namens** und nicht die des Schluesselworts -- wer sie am Schluesselwort "
     "festmacht, findet hier gar keine Fundstelle mehr und macht diesen Fall rot"},
    {"lizenzbefund-reihen.md, \101bschnitt Reihe 2\n"
     "Erwerbstaetige",
     "Reihe 2 - Wertschoepfungsanteil je Sektor|Reihe 6 - Erwerbstaetige", "",
     Namensart::Ueberschrift, "Reihe 2",
     "gebaut: **der Preis der Regel, ausgeschrieben.** Der abgegrenzte Name ist nur noch "
     "der Teil bis zum Umbruch, und er loest auf, obwohl die zweite Zeile etwas anderes "
     "nennt. Je frueher der Umbruch, desto kuerzer der gepruefte Anfang. Die Richtung ist "
     "gewaehlt und nicht uebersehen: Der Wortlaut bis zum Umbruch ist der einzige, von "
     "dem feststeht, dass er zum Zitat gehoert"},
}};

/// Die Ueberschriftenliste eines Falls, normiert wie beim Lesen einer echten Datei.
/// Leere Stuecke fallen heraus -- eine leere Spalte heisst "keine Ueberschrift".
std::vector<std::string> zerlege_liste(std::string_view spalte) {
    std::vector<std::string> liste;
    std::string laufend;
    for (std::size_t z = 0; z <= spalte.size(); ++z) {
        if (z == spalte.size() || spalte[z] == '|') {
            const std::string fertig = normiere(laufend);
            if (!fertig.empty()) {
                liste.push_back(fertig);
            }
            laufend.clear();
        } else {
            laufend += spalte[z];
        }
    }
    return liste;
}

/// Wie viele Faelle nicht wie erwartet ausgingen. Die Abweichungen stehen auf `stderr`.
std::size_t selbsttest_ohne_anfuehrung() {
    std::size_t falsch = 0;
    for (std::size_t k = 0; k < ZITATFAELLE.size(); ++k) {
        const Zitatfall& fall = ZITATFAELLE[k];
        // Der Absatz wird gebaut wie im Ernstfall -- Paket 0105. Ein `\n` im Fall ist
        // ein Zeilenumbruch; ohne ihn steht hier genau der Wortlaut des Falls.
        const Absatz absatz = absatz_aus_fall(fall.zeile);
        // Das Schluesselwort wird gesucht wie im Ernstfall und nicht abgezaehlt: Sonst
        // pruefte der Fall eine Stelle, die `schluessellaenge` gar nicht findet.
        std::size_t hinter = 0;
        bool gefunden = false;
        for (std::size_t i = 0; i < absatz.text.size() && !gefunden; ++i) {
            const std::size_t laenge = schluessellaenge(absatz.text, i);
            if (laenge > 0) {
                hinter = i + laenge;
                gefunden = true;
            }
        }
        std::string roh;
        std::string gesucht;
        if (gefunden && name_ohne_anfuehrung(absatz, hinter, roh) > 0) {
            gesucht = normiere(roh);
        }
        if (!gefunden) {
            ++falsch;
            std::fprintf(stderr,
                         "Zitatfall %zu: kein Schluesselwort getroffen -- vermutlich ist "
                         "die Maskierung verrutscht.\n      Zeile: %.*s\n",
                         k + 1, static_cast<int>(fall.zeile.size()), fall.zeile.data());
            continue;
        }
        if (gesucht != std::string(fall.erwarteter_name)) {
            ++falsch;
            std::fprintf(stderr,
                         "Zitatfall %zu: der abgegrenzte Name ist '%s', erwartet war "
                         "'%.*s'.\n      Herkunft: %.*s\n",
                         k + 1, gesucht.c_str(),
                         static_cast<int>(fall.erwarteter_name.size()),
                         fall.erwarteter_name.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
            continue;
        }
        if (gesucht.empty()) {
            continue;  // keine Fundstelle -- die Art wird gar nicht erst gefragt
        }
        const Namensart art = namensart(gesucht, zerlege_liste(fall.ueberschriften),
                                        zerlege_liste(fall.eigene));
        if (art != fall.erwartet) {
            ++falsch;
            std::fprintf(stderr,
                         "Zitatfall %zu: die Art ist %d, erwartet war %d.\n"
                         "      Name:     %s\n      Herkunft: %.*s\n",
                         k + 1, static_cast<int>(art), static_cast<int>(fall.erwartet),
                         gesucht.c_str(), static_cast<int>(fall.herkunft.size()),
                         fall.herkunft.data());
        }
    }
    return falsch;
}

// ---------------------------------------------------------------------------
// Der Selbsttest zum Urteilsschritt -- Paket 0106
// ---------------------------------------------------------------------------
//
// **Was diese Tabelle prueft, was keine andere prueft: die Verdrahtung.** `ZITATFAELLE`
// oben ruft `namensart` unmittelbar auf und misst, welche Art ein Name hat; hier wird
// gemessen, was `beurteile_zitat` daraus macht. Zwischen beidem lag bis zum 2026-09-05
// nichts -- der Grund steht bei der Funktion.
//
// **Gemessen wird der Ausgang und nicht `steht_da` fuer sich.** Ist ein Grund gesetzt,
// zaehlt die Stelle gar nicht erst als Zitat, und `steht_da` hat dann keine Wirkung
// mehr. Eine Erwartung an einen wirkungslosen Wert liesse Mutanten an Faellen sterben,
// die sie gar nicht treffen -- das waere eine Messung, die nichts misst.
//
// **Je Zweig zwei Faelle, und beide Richtungen.** Ein Mutant, der immer aufloest
// (`steht_da = true`), und einer, der nie aufloest (`steht_da = false`), muessen an
// **verschiedenen** Faellen sterben; sonst belegt ihr Sterben nur, dass die Tabelle als
// Ganzes reisst.
//
// **Warum die Gliederungsziffer keinen Fall bekommt und die beiden anderen Gruende
// schon.** Am 2026-09-05 im Lauf ueber den Bestand gezaehlt: 37 uebergangene
// Fundstellen tragen den Ziffergrund, **null** den Grund fuer das einzelne Zeichen und
// **null** den fuer eine Zieldatei ohne jede Gliederung. Die Ziffer ist am Bestand
// gehalten -- faellt ihr Zweig weg, wird der Lauf an 37 Stellen rot. Die beiden anderen
// sind es nicht mehr, und bei einem von ihnen ist auch belegt, wodurch: Der Satz in
// `rueckstand.md`, an dem die Regel zum einzelnen Zeichen hing, ist umformuliert
// worden. Genau der Vorgang, den ein wandernder Anker beschreibt.
//
// Die Schluesselwoerter sind maskiert wie ueberall sonst in dieser Datei (`\125` ist
// der Buchstabe `U`): Ohne die Maskierung waeren die erwarteten Gruende unten selbst
// Fundstellen im eigenen Quelltext.

struct Urteilsfall {
    /// Stand die Fundstelle ohne Anfuehrung da? Das ist die Weiche.
    bool ohne_anfuehrung;
    /// Der abgegrenzte Name, so wie ihn `pruefe_zitate` uebergibt.
    std::string_view gesucht;
    /// Die Ueberschriften der Zieldatei, durch `|` getrennt.
    std::string_view ueberschriften;
    /// Die Ueberschriften der **zitierenden** Datei, ebenso getrennt.
    std::string_view eigene;
    /// Die Zieldatei, wie sie ein Leser sucht. Steht nur in einem der Gruende.
    std::string_view zielanzeige;
    Zitatausgang erwartet;
    /// Leer, wenn die Stelle nicht uebergangen wird.
    std::string_view erwarteter_grund;
    std::string_view herkunft;
};

constexpr std::array<Urteilsfall, 6> URTEILSFAELLE = {{
    // --- Ohne Anfuehrung: aus der Art wird ein Urteil --------------------------
    {true, "Reihe 1",
     "Reihe 1 - BIP, konstante Preise - unklar|Reihe 2 - Wertschoepfungsanteil je Sektor",
     "", "daten/lizenzbefund-reihen.md", Zitatausgang::Aufgeloest, "",
     "derselbe Wortlaut wie Zitatfall 1, eine Ebene hoeher gemessen: Die Art ist 'steht "
     "am Anfang', und der Lauf muss daraus 'aufgeloest' machen. Wer den Schritt auf "
     "'nicht aufgeloest' festnagelt, macht aus jeder gefangenen Belegstelle des "
     "Bestands einen Befund"},
    {true, "Reihe 1",
     "Reihe 1a - BIP, konstante Preise - unklar|Reihe 2 - Wertschoepfungsanteil je Sektor",
     "", "daten/lizenzbefund-reihen.md", Zitatausgang::Befund, "",
     "dieselbe Zeile, Zieltitel umbenannt -- der Fall, um dessentwillen dieses Paket "
     "existiert. Wer den Schritt auf 'aufgeloest' festnagelt, laesst diese tote "
     "Belegstelle durch und bleibt trotzdem gruen: am 2026-09-05 gemessen, im "
     "Selbsttest und im Lauf ueber eine Kopie des Bestands"},

    // --- Mit Anfuehrung: der Name wird wortgleich verlangt ---------------------
    {false, "Reihe 1 - BIP, konstante Preise - unklar",
     "Reihe 1 - BIP, konstante Preise - unklar|Reihe 2 - Wertschoepfungsanteil je Sektor",
     "", "daten/lizenzbefund-reihen.md", Zitatausgang::Aufgeloest, "",
     "die aeltere Form, seit Paket 0067: wortgleich in der Liste, also aufgeloest"},
    {false, "Reihe 1",
     "Reihe 1 - BIP, konstante Preise - unklar|Reihe 2 - Wertschoepfungsanteil je Sektor",
     "", "daten/lizenzbefund-reihen.md", Zitatausgang::Befund, "",
     "gleicher Name und gleiche Liste wie im ersten Fall, nur mit Anfuehrung: **Hier "
     "ist der Anfang zu wenig.** Der Fall haelt die beiden Zweige auseinander -- "
     "gleicher Eingang, verschiedener Ausgang -- und er ist der einzige, an dem ein "
     "'immer aufgeloest' im Zweig mit Anfuehrung stirbt"},

    // --- Die beiden Gruende, die der Bestand nicht mehr traegt -----------------
    {true, "X und ist in der vorliegenden Fassung jener Datei",
     "Rueckstand - 0016-hedgefonds-simulation-echte-weltwirtschaft|Die Ketten: sechs "
     "Dateigruppen, und jede Sperre ist echt",
     "", "rueckstand.md", Zitatausgang::Uebergangen,
     "einzelnes Zeichen statt \125eberschrift: X",
     "der Wortlaut, an dem diese Regel entstand: 'Die Sache stand am 2026-09-02 in "
     "rueckstand.md unter dem Titel X und ist in der vorliegenden Fassung jener Datei "
     "nicht mehr aufgefuehrt' -- eine Aussage ueber ein Zitat und keines. Der Satz ist "
     "seither umformuliert, und am 2026-09-05 traegt keine einzige uebergangene "
     "Fundstelle des Bestands diesen Grund mehr"},
    {true, "18 nennt drei von sechs Stellen", "", "", "kern/include/kern/werte.hpp",
     Zitatausgang::Uebergangen,
     "Zieldatei fuehrt keine \125eberschrift: kern/include/kern/werte.hpp",
     "derselbe Wortlaut wie Zitatfall 8: Die Zieldatei ist eine Kopfdatei ohne jede "
     "Gliederung und kann ein Zitat weder bestaetigen noch widerlegen. Faellt dieser "
     "Zweig weg, wird aus einer uebergangenen Fundstelle ein Befund -- und ein Rot "
     "dort waere ein Rot gegen den Riegel"},
}};

/// Die drei Ausgaenge im Klartext, in der Reihenfolge von `Zitatausgang`.
constexpr std::array<std::string_view, 3> AUSGANGSNAMEN = {"aufgeloest", "Befund",
                                                           "uebergangen"};

/// Wie viele Faelle nicht wie erwartet ausgingen. Die Abweichungen stehen auf `stderr`.
std::size_t selbsttest_urteil() {
    std::size_t falsch = 0;
    for (std::size_t k = 0; k < URTEILSFAELLE.size(); ++k) {
        const Urteilsfall& fall = URTEILSFAELLE[k];
        const Zitaturteil urteil =
            beurteile_zitat(fall.ohne_anfuehrung, normiere(fall.gesucht),
                            zerlege_liste(fall.ueberschriften),
                            zerlege_liste(fall.eigene), std::string(fall.zielanzeige));
        const std::size_t gemessen = static_cast<std::size_t>(ausgang(urteil));
        const std::size_t erwartet = static_cast<std::size_t>(fall.erwartet);
        // Beide Werte stammen aus `Zitatausgang` und liegen damit unter der Groesse
        // der Namensliste. Geprueft wird es trotzdem: Waechst die Aufzaehlung einmal
        // und die Liste nicht mit, ist das hier ein roter Fall und kein Ueberlauf.
        if (gemessen >= AUSGANGSNAMEN.size() || erwartet >= AUSGANGSNAMEN.size()) {
            ++falsch;
            std::fprintf(stderr,
                         "Urteilsfall %zu: unbekannter Ausgang %zu (erwartet %zu) -- "
                         "AUSGANGSNAMEN passt nicht mehr zu Zitatausgang.\n",
                         k + 1, gemessen, erwartet);
            continue;
        }
        if (gemessen != erwartet) {
            ++falsch;
            std::fprintf(stderr,
                         "Urteilsfall %zu: der Ausgang ist '%.*s', erwartet war "
                         "'%.*s'.\n      Name:     %.*s\n      Herkunft: %.*s\n",
                         k + 1, static_cast<int>(AUSGANGSNAMEN[gemessen].size()),
                         AUSGANGSNAMEN[gemessen].data(),
                         static_cast<int>(AUSGANGSNAMEN[erwartet].size()),
                         AUSGANGSNAMEN[erwartet].data(),
                         static_cast<int>(fall.gesucht.size()), fall.gesucht.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
            continue;
        }
        if (urteil.grund != std::string(fall.erwarteter_grund)) {
            ++falsch;
            std::fprintf(stderr,
                         "Urteilsfall %zu: der Grund ist '%s', erwartet war '%.*s'.\n"
                         "      Name:     %.*s\n      Herkunft: %.*s\n",
                         k + 1, urteil.grund.c_str(),
                         static_cast<int>(fall.erwarteter_grund.size()),
                         fall.erwarteter_grund.data(),
                         static_cast<int>(fall.gesucht.size()), fall.gesucht.data(),
                         static_cast<int>(fall.herkunft.size()), fall.herkunft.data());
        }
    }
    return falsch;
}

void pruefe_zitate(const fs::path& pfad, const std::string& anzeigename,
                   const Zielbestand& bestand, const Ortsmenge& ungelesene,
                   std::map<std::string, std::vector<std::string>>& ueberschriften,
                   std::vector<Zitatbefund>& befunde,
                   std::vector<Zitatbefund>& tote_ziele,
                   std::vector<Uebergangen>& uebergangen, Zitatzaehlwerk& zaehlwerk) {
    const std::vector<Absatz> absaetze = lies_absaetze(pfad);
    // Die eigenen Ueberschriften, erst gelesen, wenn eine Fundstelle ohne Anfuehrung
    // danach fragt. Begruendung in `namensart`.
    std::vector<std::string> eigene_ueberschriften;
    for (std::size_t a = 0; a < absaetze.size(); ++a) {
        const Absatz& absatz = absaetze[a];
        for (std::size_t i = 0; i < absatz.text.size();) {
            const std::size_t schluessel = schluessellaenge(absatz.text, i);
            if (schluessel == 0) {
                ++i;
                continue;
            }
            std::string roh;
            bool ohne_anfuehrung = false;
            std::size_t zitatteil = ueberschrift_hinter(absatz.text, i + schluessel, roh);
            if (zitatteil == 0) {
                // Paket 0079: die Form ohne Anfuehrung. Weitergerueckt wird danach nur
                // ueber das Schluesselwort und nicht ueber den Namen -- steht im Namen
                // ein zweites Schluesselwort, soll es seine eigene Fundstelle bleiben.
                if (name_ohne_anfuehrung(absatz, i + schluessel, roh) == 0) {
                    // Paket 0086: erst jetzt, wenn beide unmittelbaren Formen nichts
                    // hergeben, wird die Anfuehrung mit Wortabstand gesucht. Die
                    // Reihenfolge ist die ganze Vertraeglichkeit dieser Lockerung.
                    zitatteil = ueberschrift_mit_abstand(absatz.text, i + schluessel, roh);
                    if (zitatteil == 0) {
                        i += schluessel;
                        continue;
                    }
                } else {
                    ohne_anfuehrung = true;
                    zitatteil = 0;
                }
            }
            const std::size_t nummer = absatz.zeile[i];
            const std::string gesucht = normiere(roh);

            std::string name;
            bool netzadresse = false;
            std::string grund;
            // Ohne Anfuehrung endet die Suche nach links am Satzanfang, mit ihr nicht.
            // Der Grund steht im Kopf und ist derselbe wie bei der Suche nach rechts:
            // Die Anfuehrung ist die Ankuendigung "hier wird zitiert"; fehlt sie, ist
            // der Dokumentname die einzige, die bleibt -- und eine Ankuendigung zwei
            // Saetze weiter oben kuendigt nichts an.
            const std::size_t untergrenze =
                suchuntergrenze(absatz.text, i, ohne_anfuehrung);
            bool gefunden =
                naechster_verweis(absatz.text, i, untergrenze, name, netzadresse);
            if (!gefunden && !ohne_anfuehrung) {
                // Paket 0086: der Dokumentname rechts vom Zitat. Nur als Rueckfall,
                // damit die gemessene Linksregel den Vorrang behaelt.
                gefunden = verweis_rechts(absatz.text, i + schluessel + zitatteil, name,
                                          netzadresse);
            }
            if (!gefunden) {
                if (ohne_anfuehrung) {
                    // Ohne Anfuehrung **und** ohne Dokumentnamen ist die Stelle kein
                    // Zitat, sondern ein Satz. Die Anfuehrung ist die Ankuendigung
                    // "hier wird zitiert"; fehlt sie, ist der Dokumentname die einzige,
                    // die bleibt. Gezaehlt wird sie trotzdem, damit die Grenze eine
                    // Zahl hat.
                    ++zaehlwerk.ohne_ziel;
                    i += schluessel;
                    continue;
                }
                // Letztes Zeichen maskiert, aus demselben Grund wie in SCHLUESSEL:
                // Ausgeschrieben stuende hier ein Schluesselwort mit einem
                // Anfuehrungszeichen unmittelbar dahinter, und der Riegel faende sich
                // in seinem eigenen Quelltext -- gemessen, er meldete dann eine
                // uebergangene Fundstelle, deren gesuchter Name die halbe naechste
                // Anweisung war.
                grund = "kein Dokumentname im Absa\164z";
            } else if (netzadresse) {
                grund = "naechstes Ziel ist eine Netzadresse: " + name;
            } else {
                const Zielbestand::const_iterator es =
                    bestand.find(std::string(basisname(name)));
                const Zielart ort = zielart(name, es != bestand.end(), ungelesene);
                if (ort == Zielart::Ausserhalb) {
                    grund = "Ziel ausserhalb beider Wurzeln: " + name;
                } else if (ort == Zielart::Ungelesen) {
                    grund = "Ziel in einem mit Absicht ungelesenen Ordner: " + name;
                } else if (ort == Zielart::Tot) {
                    // Der Befund, um dessentwillen Paket 0083 existiert: Es gibt unter
                    // keiner der beiden Wurzeln einen Ort dieses Namens. Gezaehlt wird
                    // die Stelle als Zitat, aber nicht als aufgeloest -- so bleibt der
                    // Satz wahr, dass ungleiche Zahlen einen roten Lauf bedeuten.
                    ++zaehlwerk.zitate;
                    if (ohne_anfuehrung) {
                        ++zaehlwerk.ohne_anfuehrung;
                    }
                    tote_ziele.push_back(
                        Zitatbefund{anzeigename, nummer, name, gesucht});
                } else if (es->second.anzahl != 1) {
                    grund = "Zielname mehrdeutig, " + std::to_string(es->second.anzahl)
                            + " Dateien heissen so: " + name;
                } else {
                    const std::string schluesselpfad = es->second.pfad.string();
                    if (ueberschriften.find(schluesselpfad) == ueberschriften.end()) {
                        ueberschriften[schluesselpfad] =
                            lies_ueberschriften(es->second.pfad);
                    }
                    const std::vector<std::string>& liste = ueberschriften[schluesselpfad];
                    // Die eigenen Ueberschriften erst hier, und nur ohne Anfuehrung --
                    // dieselbe Bedingung und dieselbe Stelle wie vor Paket 0106.
                    if (ohne_anfuehrung && eigene_ueberschriften.empty()) {
                        eigene_ueberschriften = lies_ueberschriften(pfad);
                    }
                    // Der Urteilsschritt steht seit Paket 0106 als eigener Aufruf da,
                    // damit `URTEILSFAELLE` ihn halten kann. Begruendung dort.
                    const Zitaturteil urteil =
                        beurteile_zitat(ohne_anfuehrung, gesucht, liste,
                                        eigene_ueberschriften, es->second.anzeige);
                    grund = urteil.grund;
                    const Zitatausgang wie = ausgang(urteil);
                    if (wie != Zitatausgang::Uebergangen) {
                        ++zaehlwerk.zitate;
                        if (ohne_anfuehrung) {
                            ++zaehlwerk.ohne_anfuehrung;
                        }
                        if (wie == Zitatausgang::Aufgeloest) {
                            ++zaehlwerk.aufgeloest;
                        } else {
                            befunde.push_back(Zitatbefund{anzeigename, nummer,
                                                          es->second.anzeige, gesucht});
                        }
                    }
                }
            }
            if (!grund.empty()) {
                uebergangen.push_back(Uebergangen{anzeigename, nummer, grund, gesucht});
            }
            i += schluessel + zitatteil;
        }
    }
}

}  // namespace

namespace {

/// Der Pfad, wie ihn ein Leser sucht: ohne die Wurzel davor.
std::string kurzname(const fs::path& pfad, const std::string& wurzeltext,
                     const std::string& vorsatz) {
    std::string name = pfad.string();
    if (name.size() > wurzeltext.size()
        && name.compare(0, wurzeltext.size(), wurzeltext) == 0) {
        name.erase(0, wurzeltext.size() + 1);
    }
    return vorsatz + name;
}

/// Liegt diese Datei unter dem genannten Ordner der Wurzel?
bool liegt_unter(const std::string& kurz, std::string_view ordner) {
    return kurz.size() > ordner.size() && kurz.compare(0, ordner.size(), ordner) == 0
           && kurz[ordner.size()] == '/';
}

}  // namespace

int main(int argc, char** argv) {
    // Der Selbsttest laeuft vor allem anderen und braucht kein Argument: Stimmt die
    // Suche nach links nicht, ist jede Zahl weiter unten wertlos -- auch und gerade
    // eine gruene.
    const std::size_t fehlgeschlagen = selbsttest_namenssuche()
                                       + selbsttest_ohne_anfuehrung()
                                       + selbsttest_urteil()
                                       + selbsttest_zielart()
                                       + selbsttest_abstand()
                                       + selbsttest_satzgrenze()
                                       + selbsttest_ordnung();
    if (fehlgeschlagen > 0) {
        std::fprintf(stderr,
                     "\nbelegstellen_riegel: %zu von %zu Faellen des Selbsttests sind "
                     "nicht wie erwartet\nausgegangen. Der Riegel hat den Bestand gar "
                     "nicht erst gelesen -- ein Messgeraet,\ndas seine eigenen Faelle "
                     "verfehlt, misst auch fremde nicht.\n",
                     fehlgeschlagen,
                     NAMENSFAELLE.size() + ZITATFAELLE.size() + URTEILSFAELLE.size()
                         + ZIELFAELLE.size() + ABSTANDSFAELLE.size()
                         + SATZFAELLE.size() + ORDNUNGSFAELLE.size());
        return 2;
    }
    std::fprintf(stdout,
                 "belegstellen_riegel, Selbsttest: %zu Faelle zur Suche nach links, %zu "
                 "zur Form\nohne Anfuehrung, %zu zum Urteilsschritt, %zu zur Ortsfrage, "
                 "%zu zum Wortabstand samt\nSuche nach rechts, %zu zur Satzgrenze "
                 "nach links und %zu zur Ausgabeordnung,\nalle wie erwartet.\n",
                 NAMENSFAELLE.size(), ZITATFAELLE.size(), URTEILSFAELLE.size(),
                 ZIELFAELLE.size(), ABSTANDSFAELLE.size(), SATZFAELLE.size(),
                 ORDNUNGSFAELLE.size());

    const std::vector<std::string> argumente(argv, argv + argc);
    if (argumente.size() != 2 && argumente.size() != 3) {
        std::fprintf(stderr,
                     "Aufruf: belegstellen_riegel <wurzel-des-vorhabens> "
                     "[<wurzel-der-vorgaben>]\n"
                     "Die Wurzel kommt von CMake; ein eingebauter Pfad liefe nur auf "
                     "einem Rechner.\n");
        return 2;
    }

    std::error_code fehler;
    const fs::path wurzel = fs::weakly_canonical(fs::path(argumente[1]), fehler);
    if (fehler || !fs::is_directory(wurzel, fehler)) {
        std::fprintf(stderr, "belegstellen_riegel: '%s' ist kein Verzeichnis.\n",
                     argumente[1].c_str());
        return 2;
    }

    // Die Vorgabenwurzel: wahlfrei uebergeben, sonst aus der ersten abgeleitet.
    // Begruendung im Kopf, Abschnitt zum Aufruf.
    fs::path vorgaben;
    if (argumente.size() == 3) {
        vorgaben = fs::weakly_canonical(fs::path(argumente[2]), fehler);
    } else {
        vorgaben = fs::weakly_canonical(
            wurzel.parent_path().parent_path() / "specs" / wurzel.filename(), fehler);
    }
    if (fehler || !fs::is_directory(vorgaben, fehler)) {
        std::fprintf(stderr,
                     "belegstellen_riegel: '%s' ist kein Verzeichnis.\n"
                     "Dort werden die Vorgaben erwartet -- ohne sie liefe jedes Zitat in "
                     "die Vorgaben als 'Ziel ausserhalb des Bestands' durch, und der "
                     "Riegel meldete gruen ueber nichts. Zweites Argument setzen, wenn "
                     "die Vorgaben woanders liegen.\n",
                     vorgaben.string().c_str());
        return 2;
    }

    std::error_code lesefehler;
    // Die Pfade aus den ungelesenen Ordnern beider Wurzeln in **einer** Menge: Die
    // Frage, die sie beantworten, kennt keine Wurzel -- ein Zitat schreibt den Weg von
    // der Wurzel nicht mit, und welche der beiden gemeint war, steht nirgends.
    Ortsmenge ungelesene;
    const std::vector<fs::path> gelesen = sammle_dateien(wurzel, ungelesene, lesefehler);
    if (lesefehler) {
        std::fprintf(stderr, "belegstellen_riegel: Lesefehler unter '%s': %s\n",
                     wurzel.string().c_str(), lesefehler.message().c_str());
        return 2;
    }
    const std::vector<fs::path> gelesen_vorgaben =
        sammle_dateien(vorgaben, ungelesene, lesefehler);
    if (lesefehler) {
        std::fprintf(stderr, "belegstellen_riegel: Lesefehler unter '%s': %s\n",
                     vorgaben.string().c_str(), lesefehler.message().c_str());
        return 2;
    }

    // Drei Mengen aus einem Durchgang. Welche wofuer, steht im Kopf.
    const std::string wurzeltext = wurzel.string();
    const std::string vorgabentext = vorgaben.string();

    std::vector<fs::path> bauquellen;
    std::vector<std::string> bauquellen_namen;
    std::vector<fs::path> zitierende;
    std::vector<std::string> zitierende_namen;
    std::size_t datendokumente = 0;
    Zielbestand bestand;

    for (std::size_t i = 0; i < gelesen.size(); ++i) {
        const std::string kurz = kurzname(gelesen[i], wurzeltext, "");
        nimm_ziel_auf(bestand, gelesen[i], kurz);
        if (ist_quelldatei(gelesen[i])) {
            bauquellen.push_back(gelesen[i]);
            bauquellen_namen.push_back(kurz);
            zitierende.push_back(gelesen[i]);
            zitierende_namen.push_back(kurz);
        } else if (ist_datendokument(gelesen[i]) && !liegt_unter(kurz, "aufgaben")) {
            zitierende.push_back(gelesen[i]);
            zitierende_namen.push_back(kurz);
            ++datendokumente;
        }
    }
    for (std::size_t i = 0; i < gelesen_vorgaben.size(); ++i) {
        nimm_ziel_auf(bestand, gelesen_vorgaben[i],
                      kurzname(gelesen_vorgaben[i], vorgabentext, "specs/"));
    }

    // Ein Riegel, der nichts gesehen hat, hat nichts geprueft. Begruendung im Kopf.
    if (bauquellen.empty()) {
        std::fprintf(stderr,
                     "belegstellen_riegel: keine einzige Bauquelle unter '%s' gefunden. "
                     "Der Riegel hat damit nichts geprueft -- das ist kein gruener Lauf, "
                     "sondern ein Riegel ohne Gegenstand.\n",
                     wurzel.string().c_str());
        return 2;
    }

    // -----------------------------------------------------------------------
    // Bedingung 1 -- Paket 0059
    // -----------------------------------------------------------------------
    std::vector<Befund> befunde;
    Zaehlwerk zaehlwerk;
    for (std::size_t i = 0; i < bauquellen.size(); ++i) {
        pruefe_datei(bauquellen[i], bauquellen_namen[i], befunde, zaehlwerk);
    }

    std::fprintf(stdout,
                 "belegstellen_riegel, Bedingung 1 (Zeilennummer in eine fremde Datei): "
                 "%zu Bauquellen gelesen, %zu Zeilenverweise getroffen, davon %zu mit "
                 "Dateinamen daneben.\n",
                 bauquellen.size(), zaehlwerk.treffer, zaehlwerk.mit_dateinamen);

    // -----------------------------------------------------------------------
    // Bedingung 2 -- Paket 0067
    // -----------------------------------------------------------------------
    std::map<std::string, std::vector<std::string>> ueberschriften;
    std::vector<Zitatbefund> zitatbefunde;
    std::vector<Zitatbefund> tote_ziele;
    std::vector<Uebergangen> uebergangen;
    Zitatzaehlwerk zitatzaehlwerk;
    for (std::size_t i = 0; i < zitierende.size(); ++i) {
        pruefe_zitate(zitierende[i], zitierende_namen[i], bestand, ungelesene,
                      ueberschriften, zitatbefunde, tote_ziele, uebergangen,
                      zitatzaehlwerk);
    }

    std::fprintf(stdout,
                 "belegstellen_riegel, Bedingung 2 (Abschnittszitat): %zu Bauquellen und "
                 "%zu Datendokumente gelesen, %zu Dateien im Zielbestand, %zu Pfade in "
                 "ungelesenen Ordnern; %zu Zitate der geprueften Form gefunden, %zu "
                 "davon aufgeloest (Untergrenze %zu), %zu Fundstellen uebergangen.\n"
                 "Davon ohne Anfuehrung: %zu Zitate; weitere %zu Fundstellen ohne "
                 "Anfuehrung nennen in ihrem Absatz keinen Dokumentnamen und sind "
                 "deshalb keine Zitate.\n",
                 bauquellen.size(), datendokumente, bestand.size(), ungelesene.size(),
                 zitatzaehlwerk.zitate, zitatzaehlwerk.aufgeloest, AUFGELOEST_MINDESTENS,
                 uebergangen.size(), zitatzaehlwerk.ohne_anfuehrung,
                 zitatzaehlwerk.ohne_ziel);

    if (!uebergangen.empty()) {
        std::fprintf(stdout,
                     "\nUebergangen -- der ausgeschriebene blinde Fleck von Bedingung 2. "
                     "Diese\nFundstellen tragen ihr Ziel nicht bei sich; sie werden "
                     "gezaehlt und genannt,\naber nicht bewertet:\n\n");
        for (std::size_t i = 0; i < uebergangen.size(); ++i) {
            const Uebergangen& u = uebergangen[i];
            std::fprintf(stdout, "  %s:%zu  (%s)\n      gesucht war: %s\n",
                         u.datei.c_str(), u.zeilennummer, u.grund.c_str(),
                         u.ueberschrift.c_str());
        }
    }

    // Ein Muster, das nichts mehr trifft, ist kein bestandener Lauf. Die sechs Pakete
    // 0034, 0035, 0044, 0047, 0050 und 0057 haben nachweislich Zitate hinterlassen.
    if (zitatzaehlwerk.zitate == 0) {
        std::fprintf(stderr,
                     "\nbelegstellen_riegel: kein einziges Abschnittszitat gefunden. Das "
                     "ist ein Befund\ngegen das Muster und keine bestandene Bedingung -- "
                     "sechs Pakete haben\nnachweislich welche hinterlassen.\n");
        return 2;
    }

    // Die zweite Haelfte derselben Vorsorge -- Paket 0083. Null ist der auffaellige
    // Fall; der gefaehrliche ist der Rueckgang, der die Zahlen gleich laesst. Faellt
    // die Menge der zitierenden Dateien weg statt der Ziele, entsteht kein einziger
    // Befund und der Lauf bliebe gruen ueber der Haelfte seines Gegenstands.
    if (zitatzaehlwerk.aufgeloest < AUFGELOEST_MINDESTENS) {
        std::fprintf(stderr,
                     "\nbelegstellen_riegel: nur %zu Zitate haben aufgeloest, die "
                     "Untergrenze im Quelltext\nsteht bei %zu. Das ist ein Befund gegen "
                     "die Abdeckung und keine bestandene\nBedingung: Die Zahl ist die "
                     "Summe der Belegstellen der sechs Pakete, um\nderentwillen dieser "
                     "Riegel existiert. Entweder wird eine Menge nicht mehr\ngelesen, "
                     "die gelesen werden sollte -- dann ist das die Ursache --, oder die "
                     "sechs\nPakete sind rechtmaessig aufgeraeumt worden. Nur im zweiten "
                     "Fall wird die\nUntergrenze gesenkt, und zwar mit Begruendung an "
                     "ihrer Stelle.\n",
                     zitatzaehlwerk.aufgeloest, AUFGELOEST_MINDESTENS);
        return 2;
    }

    // -----------------------------------------------------------------------
    // Das Urteil
    // -----------------------------------------------------------------------
    if (befunde.empty() && zitatbefunde.empty() && tote_ziele.empty()) {
        std::fprintf(stdout,
                     "\nKein Verweis zeigt mit einer Zeilennummer in eine fremde Datei, "
                     "und jedes der\n%zu Abschnittszitate findet seine Zieldatei und "
                     "darin seine Ueberschrift.\n",
                     zitatzaehlwerk.aufgeloest);
        return 0;
    }

    if (!befunde.empty()) {
        std::fprintf(stderr,
                     "\n%zu Verweis(e) zeigen mit einer Zeilennummer in eine fremde "
                     "Datei:\n\n",
                     befunde.size());
        for (std::size_t i = 0; i < befunde.size(); ++i) {
            const Befund& b = befunde[i];
            std::fprintf(stderr, "  %s:%zu  -> %s\n      %s\n", b.datei.c_str(),
                         b.zeilennummer, b.ziel.c_str(), b.stelle.c_str());
        }
        std::fprintf(stderr,
                     "\nEine Zeilennummer in eine fremde Datei wandert, ohne dass jemand "
                     "etwas tut.\nSie wird ersetzt -- durch einen Bezeichner, eine "
                     "Abschnittsueberschrift oder eine\nSchluesselzeile im Wortlaut --, "
                     "nicht ausgenommen und nicht nachgezogen.\n");
    }

    if (!tote_ziele.empty()) {
        std::fprintf(stderr,
                     "\n%zu Abschnittszitat(e) nennen eine Zieldatei, die es unter "
                     "keiner der beiden\nWurzeln gibt:\n\n",
                     tote_ziele.size());
        for (std::size_t i = 0; i < tote_ziele.size(); ++i) {
            const Zitatbefund& z = tote_ziele[i];
            std::fprintf(stderr,
                         "  zitierend: %s:%zu\n  genannte Zieldatei: %s\n"
                         "  gesuchter Wortlaut: %s\n\n",
                         z.datei.c_str(), z.zeilennummer, z.ziel.c_str(),
                         z.ueberschrift.c_str());
        }
        std::fprintf(stderr,
                     "Diese Sorte ist bis Paket 0083 unter den uebergangenen "
                     "Fundstellen gelandet und\nblieb damit gruen. Sie ist keine: Ein "
                     "Ziel, das es nicht gibt, ist der tote\nVerweis, gegen den dieser "
                     "Riegel geschrieben ist. Entweder ist die Datei\numbenannt oder "
                     "verschoben worden -- dann wird der Verweis nachgezogen --, oder\n"
                     "sie hiess nie so.\n\nLiegt sie mit Absicht in einem ungelesenen "
                     "Ordner (`bau/`, `befunde/`), gehoert\ndieser Ordner in den "
                     "Verweis: Seit dem 2026-09-05 wird die Ortsfrage an dem Ort\n"
                     "entschieden, auf den der Verweis zeigt, und nicht daran, ob "
                     "irgendwo eine Datei\ndesselben Namens liegt. Die ungelesenen "
                     "Ordner tragen Abschriften des Quellbaums;\nwer nach dem blossen "
                     "Namen fragt, bekommt dort fast immer ein Ja und uebergeht\ngenau "
                     "den toten Verweis, den er sucht. Ein Zitat, dem nur der Vorsatz "
                     "fehlt, wird\nalso um zwei Woerter ergaenzt und steht danach oben "
                     "unter den uebergangenen\nFundstellen.\n");
    }

    if (!zitatbefunde.empty()) {
        std::fprintf(stderr,
                     "\n%zu Abschnittszitat(e) finden ihre Ueberschrift nicht:\n\n",
                     zitatbefunde.size());
        for (std::size_t i = 0; i < zitatbefunde.size(); ++i) {
            const Zitatbefund& z = zitatbefunde[i];
            // Drei Angaben, und alle drei werden gebraucht: wer zitiert, worin
            // nachgeschlagen wurde und wonach. Eine Meldung, die nur sagt, ein Verweis
            // sei tot, zwingt den naechsten Leser zur Suche.
            std::fprintf(stderr,
                         "  zitierend: %s:%zu\n  nachgeschlagen in: %s\n"
                         "  gesuchte Ueberschrift: %s\n\n",
                         z.datei.c_str(), z.zeilennummer, z.ziel.c_str(),
                         z.ueberschrift.c_str());
        }
        std::fprintf(stderr,
                     "Entweder ist die Ueberschrift dort umbenannt worden -- dann wird "
                     "das Zitat\nnachgezogen --, oder sie stand nie so da. Beides wird "
                     "berichtigt und nicht\nausgenommen. Die Schreibweise ist bis auf "
                     "Umlautumschrift, Auszeichnung und\nLeerraum wortgleich zu nehmen; "
                     "Gross- und Kleinschreibung zaehlt.\n");
    }
    return 1;
}
