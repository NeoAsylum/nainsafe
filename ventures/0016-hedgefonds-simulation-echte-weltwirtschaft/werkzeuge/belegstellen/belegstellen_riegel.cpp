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
//! ## Was der Riegel liest, und warum genau das
//!
//! Gelesen werden die **Bauquellen** des Vorhabens: Rumpf- und Kopfdateien, die
//! Bausteuerung und jede Bauliste. Ausgenommen sind die Verzeichnisse `bau` (vom
//! Uebersetzer erzeugt) und `befunde` (Berichte -- eine Zeilennummer darin ist ein
//! *Messwert vom Tag der Messung*, kein Verweis; sie soll gerade nicht nachgefuehrt
//! werden, sonst faelschte man einen Bericht).
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
//! Fundstellen**. Fuenf Sorten, alle unten einzeln mit Datei und Zeile genannt, damit
//! keine still bleibt:
//!
//!   * *ohne Dokumentnamen im Absatz* -- ein Verweis auf einen Abschnitt derselben
//!     Datei, oder auf eine Quelle ausserhalb dieses Vorhabens (eine Lizenz, ein RFC).
//!     Er traegt sein Ziel nicht bei sich; dieser Riegel prueft nur, was das tut.
//!   * *Ziel ausserhalb des Bestands* -- der naechstgelegene Name gehoert zu keiner
//!     Datei, die hier gelesen wird (ein Bericht unter `befunde/`, eine Netzadresse).
//!   * *Gliederungsziffer statt Ueberschrift* -- Paket 0079, oben begruendet. Die
//!     groesste der fuenf Gruppen und die harmloseste: Eine Nummer traegt keinen
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
//!   0034 -- `daten/adressen.md`, drei Stellen, alle mit Ziel in `technik.md`. Zwei
//!           **gefangen**: die Begruendung zur Spalte `Adresse` und die Herleitung zu
//!           den unmarkierten Geschwisterpaaren zitieren beide denselben fett
//!           ausgezeichneten Vorspann unter T49, und beide loesen auf. Sie fielen
//!           erst an, seit das Wort fuer einen Textblock in SCHLUESSEL steht.
//!           Die dritte -- die Tabellenueberschrift zu T46, im Satz mit "sagt es
//!           selbst" -- ist **nicht gefangen**; die Form steht unten.
//!           *Berichtigung vom 2026-09-04:* Bis dahin stand hier das Kopffeld
//!           `quellen` derselben Datei. Das ist eine echte und gefangene Belegstelle,
//!           aber sie stammt aus Paket 0004 und nicht aus 0034 -- `git log -S` auf
//!           den Wortlaut fuehrt zwei Tage daneben, weil die Arbeit eines Pakets hier
//!           regelmaessig im Commit des naechsten Laufs liegt und dessen Betreff den
//!           Namen des anderen Pakets traegt. Der Wortlauttreffer gehoert deshalb
//!           gegen das Datum des gesuchten Pakets gehalten, nicht fuer sich genommen.
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
//! **Drei Grenzen, ausgeschrieben, weil sie still waeren.**
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
//!
//! **Die zweite Luecke, aus demselben Grund ausgeschrieben: Das Schluesselwort steht
//! nicht unmittelbar vor der Anfuehrung.** Die dritte Belegstelle aus Paket 0034 nennt
//! ihr Schluesselwort, laesst dann aber fuenf Woerter folgen, ehe die Anfuehrung
//! beginnt -- der Bau ist "die <Schluesselwort> der Tabelle sagt es selbst:", und erst
//! danach kommt der zitierte Wortlaut. `ueberschrift_hinter` ueberspringt hinter dem
//! Schluesselwort nur Leerzeichen und einen Gegenschraegstrich; alles andere beendet
//! den Versuch, und die Stelle zaehlt danach nirgends -- auch nicht als uebergangen.
//!
//! An derselben Stelle steht ein zweites, davon unabhaengiges Hindernis: Der
//! Dokumentname steht dort **rechts** vom Zitat, in der Klammer dahinter, waehrend
//! dieser Riegel nur nach links sucht. Wer nur eines der beiden loest, fangt die
//! Stelle immer noch nicht.
//!
//! Beides ist keine Zeile, sondern eine Entscheidung mit eigenem Nachweis, und zwar
//! aus dem Grund, an dem schon 0047 haengt: Wer beliebig viele Woerter zwischen
//! Schluesselwort und Anfuehrung zulaesst, bindet jede Anfuehrung eines Satzes an das
//! naechstgelegene Schluesselwort und wird rot, wo nichts kaputt ist; wer zusaetzlich
//! nach rechts sucht, muss entscheiden, welcher der beiden Nachbarn gewinnt, und hat
//! dafuer heute kein Mass. Solange die Entscheidung nicht getroffen ist, bleibt diese
//! Form ungeschuetzt. Sie steht hier, damit die Zahlen unten niemand fuer
//! Vollstaendigkeit haelt; als Vorschlag liegt sie als Paket 0086 daneben.
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
//! Rueckgabe: 0 kein Befund, 1 Befunde gefunden, 2 Aufruf- oder Lesefehler.
//!
//! Vorgaben: T4 (kein Gleitkomma -- hier trivial, es wird nichts gerechnet),
//! ADR 0011 (C++20, g++). Kein Zeiger, kein rohes Feld, jeder Zugriff ueber Index.

#include <array>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <map>
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

/// Verzeichnisnamen, die nicht betreten werden. Begruendung im Kopf.
constexpr std::array<std::string_view, 2> GESPERRTE_ORDNER = {"bau", "befunde"};

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
// Jede Zeile traegt ihre Herkunft. Vier der acht sind im Bestand gemessen und nicht
// erfunden; die uebrigen vier halten je eine Entscheidung fest, die sonst niemand
// nachlesen koennte.
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
     "kern/test/schranken_probe.cpp -- die unmittelbare Form, die schon vor 0073 "
     "gefangen wurde"},
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

bool ist_gesperrt(std::string_view ordner) {
    for (std::size_t i = 0; i < GESPERRTE_ORDNER.size(); ++i) {
        if (ordner == GESPERRTE_ORDNER[i]) {
            return true;
        }
    }
    // Versteckte Ordner (`.git`, `.claude`) sind keine Bauquellen.
    return !ordner.empty() && ordner.front() == '.';
}

/// Absteigend, mit eigener Arbeitsliste statt `recursive_directory_iterator`: Dessen
/// `disable_recursion_pending` haengt am Zustand des Iterators, und ein gesperrter
/// Ordner soll gar nicht erst geoeffnet werden.
std::vector<fs::path> sammle_dateien(const fs::path& wurzel, std::error_code& fehler) {
    std::vector<fs::path> gefunden;
    // Eingesammelt wird in einem Durchgang alles, was ueberhaupt gelesen werden kann;
    // welche Bedingung welche Teilmenge bekommt, entscheidet `main` an den Praedikaten
    // oben. Zwei Durchgaenge ueber denselben Baum waeren zwei Ordnerlisten, die
    // auseinanderlaufen koennen.
    std::vector<fs::path> offen;
    offen.push_back(wurzel);

    while (!offen.empty()) {
        const fs::path verzeichnis = offen.back();
        offen.pop_back();

        fs::directory_iterator it(verzeichnis, fehler);
        if (fehler) {
            return gefunden;
        }
        const fs::directory_iterator ende;
        while (it != ende) {
            const fs::path eintrag = it->path();
            std::error_code art;
            if (fs::is_directory(eintrag, art)) {
                if (!ist_gesperrt(eintrag.filename().string())) {
                    offen.push_back(eintrag);
                }
            } else if (fs::is_regular_file(eintrag, art) && ist_zieldatei(eintrag)) {
                gefunden.push_back(eintrag);
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
};

constexpr std::array<Klammer, 11> KLAMMERN = {{
    {"\"", "\""},
    {"\342\200\236", "\342\200\234"},  // U+201E ... U+201C
    {"\342\200\236", "\342\200\235"},  // U+201E ... U+201D
    {"\342\200\234", "\342\200\235"},  // U+201C ... U+201D
    {"'", "'"},
    {"\342\200\230", "\342\200\231"},  // U+2018 ... U+2019
    {"`", "`"},
    {"*", "*"},
    {"\342\200\236", "\""},  // U+201E ... gerade
    {"\342\200\234", "\""},  // U+201C ... gerade
    // Die Form, die Paket 0057 in `reihen.toml` eingefuehrt hat: "Adresse plus Zitat
    // im Wortlaut", geklammert statt in Anfuehrung. Sie steht hier, weil 0057 eines
    // der sechs Pakete ist, um derentwillen dieser Riegel existiert -- ohne diese
    // Zeile fiele die Haelfte seiner Arbeit durch.
    {"(Zita\164: ", ")"},
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
struct Absatz {
    std::string text;
    std::vector<std::size_t> zeile;
};

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
        } else {
            laufend.text += ' ';
            laufend.zeile.push_back(nummer);
        }
        for (std::size_t k = 0; k < inhalt.size(); ++k) {
            laufend.text += inhalt[k];
            laufend.zeile.push_back(nummer);
        }
    }
    if (offen) {
        absaetze.push_back(laufend);
    }
    return absaetze;
}

// ---------------------------------------------------------------------------
// Bedingung 2, Teil 3: Ziel suchen und nachschlagen
// ---------------------------------------------------------------------------

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
bool naechster_verweis(std::string_view text, std::size_t bis, std::string& name,
                       bool& netzadresse) {
    std::size_t grenze = bis;
    while (grenze > 0) {
        std::size_t ende = grenze;
        while (ende > 0 && !ist_pfadzeichen(text[ende - 1])) {
            --ende;
        }
        if (ende == 0) {
            return false;
        }
        std::size_t anfang = ende;
        while (anfang > 0 && ist_pfadzeichen(text[anfang - 1])) {
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

/// Liest die Ueberschrift, die bei `i` in Anfuehrung stehen soll. Rueckgabe ist die
/// Laenge des ganzen Zitatteils ab `i`, oder 0, wenn dort keine Anfuehrung steht.
std::size_t ueberschrift_hinter(std::string_view text, std::size_t i, std::string& roh) {
    std::size_t j = i;
    while (j < text.size() && text[j] == ' ') {
        ++j;
    }
    // Ein Zitat in einer C++-Zeichenkette traegt sein Anfuehrungszeichen maskiert.
    if (j < text.size() && text[j] == '\\') {
        ++j;
    }
    for (std::size_t k = 0; k < KLAMMERN.size(); ++k) {
        const Klammer klammer = KLAMMERN[k];
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
        return (zu + klammer.zu.size()) - i;
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
std::size_t name_ohne_anfuehrung(std::string_view text, std::size_t i, std::string& roh) {
    std::size_t j = i;
    while (j < text.size() && text[j] == ' ') {
        ++j;
    }
    if (j == i || j >= text.size() || !ist_namensanfang(text, j)) {
        return 0;
    }
    std::size_t ende = j;
    while (ende < text.size() && ende - j < UEBERSCHRIFT_HOECHSTENS
           && !ist_namensende(text, ende)) {
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

constexpr std::array<Zitatfall, 9> ZITATFAELLE = {{
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
        // Das Schluesselwort wird gesucht wie im Ernstfall und nicht abgezaehlt: Sonst
        // pruefte der Fall eine Stelle, die `schluessellaenge` gar nicht findet.
        std::size_t hinter = 0;
        bool gefunden = false;
        for (std::size_t i = 0; i < fall.zeile.size() && !gefunden; ++i) {
            const std::size_t laenge = schluessellaenge(fall.zeile, i);
            if (laenge > 0) {
                hinter = i + laenge;
                gefunden = true;
            }
        }
        std::string roh;
        std::string gesucht;
        if (gefunden && name_ohne_anfuehrung(fall.zeile, hinter, roh) > 0) {
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

void pruefe_zitate(const fs::path& pfad, const std::string& anzeigename,
                   const Zielbestand& bestand,
                   std::map<std::string, std::vector<std::string>>& ueberschriften,
                   std::vector<Zitatbefund>& befunde,
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
                if (name_ohne_anfuehrung(absatz.text, i + schluessel, roh) == 0) {
                    i += schluessel;
                    continue;
                }
                ohne_anfuehrung = true;
                zitatteil = 0;
            }
            const std::size_t nummer = absatz.zeile[i];
            const std::string gesucht = normiere(roh);

            std::string name;
            bool netzadresse = false;
            std::string grund;
            if (!naechster_verweis(absatz.text, i, name, netzadresse)) {
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
                if (es == bestand.end()) {
                    grund = "Ziel ausserhalb des Bestands: " + name;
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
                    // Mit Anfuehrung ist der Name abgegrenzt und wird wortgleich
                    // verlangt; ohne sie ist er es nicht, und die Zieldatei grenzt ihn
                    // ab -- er muss am Anfang einer ihrer Ueberschriften stehen.
                    bool steht_da = false;
                    if (ohne_anfuehrung) {
                        if (eigene_ueberschriften.empty()) {
                            eigene_ueberschriften = lies_ueberschriften(pfad);
                        }
                        const Namensart art =
                            namensart(gesucht, liste, eigene_ueberschriften);
                        if (art == Namensart::Ziffer) {
                            grund = "Gliederungsziffer statt Ueberschrift: "
                                    + std::string(erstes_wort(gesucht));
                        } else if (art == Namensart::Einzelzeichen) {
                            grund = "einzelnes Zeichen statt Ueberschrift: "
                                    + std::string(erstes_wort(gesucht));
                        } else if (art == Namensart::Ohne_Gliederung) {
                            grund = "Zieldatei fuehrt keine Ueberschrift: "
                                    + es->second.anzeige;
                        }
                        steht_da = art == Namensart::Ueberschrift;
                    } else {
                        for (std::size_t u = 0; u < liste.size() && !steht_da; ++u) {
                            steht_da = liste[u] == gesucht;
                        }
                    }
                    if (grund.empty()) {
                        ++zaehlwerk.zitate;
                        if (ohne_anfuehrung) {
                            ++zaehlwerk.ohne_anfuehrung;
                        }
                        if (steht_da) {
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
    const std::size_t fehlgeschlagen =
        selbsttest_namenssuche() + selbsttest_ohne_anfuehrung();
    if (fehlgeschlagen > 0) {
        std::fprintf(stderr,
                     "\nbelegstellen_riegel: %zu von %zu Faellen des Selbsttests sind "
                     "nicht wie erwartet\nausgegangen. Der Riegel hat den Bestand gar "
                     "nicht erst gelesen -- ein Messgeraet,\ndas seine eigenen Faelle "
                     "verfehlt, misst auch fremde nicht.\n",
                     fehlgeschlagen, NAMENSFAELLE.size() + ZITATFAELLE.size());
        return 2;
    }
    std::fprintf(stdout,
                 "belegstellen_riegel, Selbsttest: %zu Faelle zur Suche nach links und "
                 "%zu zur Form\nohne Anfuehrung, alle wie erwartet.\n",
                 NAMENSFAELLE.size(), ZITATFAELLE.size());

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
    const std::vector<fs::path> gelesen = sammle_dateien(wurzel, lesefehler);
    if (lesefehler) {
        std::fprintf(stderr, "belegstellen_riegel: Lesefehler unter '%s': %s\n",
                     wurzel.string().c_str(), lesefehler.message().c_str());
        return 2;
    }
    const std::vector<fs::path> gelesen_vorgaben = sammle_dateien(vorgaben, lesefehler);
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
    std::vector<Uebergangen> uebergangen;
    Zitatzaehlwerk zitatzaehlwerk;
    for (std::size_t i = 0; i < zitierende.size(); ++i) {
        pruefe_zitate(zitierende[i], zitierende_namen[i], bestand, ueberschriften,
                      zitatbefunde, uebergangen, zitatzaehlwerk);
    }

    std::fprintf(stdout,
                 "belegstellen_riegel, Bedingung 2 (Abschnittszitat): %zu Bauquellen und "
                 "%zu Datendokumente gelesen, %zu Dateien im Zielbestand; %zu Zitate der "
                 "geprueften Form gefunden, %zu davon aufgeloest, %zu Fundstellen "
                 "uebergangen.\n"
                 "Davon ohne Anfuehrung: %zu Zitate; weitere %zu Fundstellen ohne "
                 "Anfuehrung nennen in ihrem Absatz keinen Dokumentnamen und sind "
                 "deshalb keine Zitate.\n",
                 bauquellen.size(), datendokumente, bestand.size(),
                 zitatzaehlwerk.zitate, zitatzaehlwerk.aufgeloest, uebergangen.size(),
                 zitatzaehlwerk.ohne_anfuehrung, zitatzaehlwerk.ohne_ziel);

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

    // -----------------------------------------------------------------------
    // Das Urteil
    // -----------------------------------------------------------------------
    if (befunde.empty() && zitatbefunde.empty()) {
        std::fprintf(stdout,
                     "\nKein Verweis zeigt mit einer Zeilennummer in eine fremde Datei, "
                     "und jedes der\n%zu Abschnittszitate findet seine Ueberschrift.\n",
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
