---
id: 0091-diff-ursachenkette-nach-t20
rolle: kernbauer
status: fertig
haengt_an: [0144-rundenkapazitaet-des-verlaufs-nicht-an-r, 0156-verlaufgroesse-auch-absolut-beschraenkt]
abnahme_befund: befunde/pruefung-0091-diff-ursachenkette-nach-t20-2026-09-06.md (urteil geprueft, kern-pruefer, 2026-09-06)
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/verlauf.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/verlauf.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/verlauf_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustandsausgabe.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/zustandsausgabe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/zustandsausgabe_probe.cpp]
abnahme: Zu einem Unterschied ueber mehr als eine Runde nennt die Ausgabe je geaenderter Adresse nicht nur alt, neu und Differenz, sondern die Ursachenkette aus T18, rueckwaerts aufgeloest bis zur ausloesenden Aktion oder Gegenkraft, mit Verzoegerung und Beitrag je Glied. Nachgewiesen an einer Partie ueber mindestens drei Runden, in der eine Aktion in Runde 1 eine Groesse in Runde 3 aendert: Die Kette nennt beide Glieder und die Verzoegerung dazwischen, und eine Adresse ohne Ursache kommt nicht vor.
---

## GEBAUT — 2026-09-06, Kernbauer

Gebaut ist die Rueckwaertsaufloesung und ihre Ausgabe, in sechs Dateien und ohne eine
siebte:

* `kern::verlauf::Aufloesung` -- der Schrittkasten, der von einem Schreibzugriff zu
  seiner Ursache geht. Er haelt einen Platz und keine Kette; ein Kettenwert waere ein
  halbes Megabyte fuer eine Kette, die drei Glieder hat. Dazu `Ende` (fuenf Enden) und
  `Verlauf::platz_der_runde`, die Frage neben dem abbrechenden `kette_der_runde`.
* `kern::zustandsausgabe::diff_mit_kette` -- die vierte Abfrage. Je geaenderter Adresse
  die **zeichengleiche** Wertzeile der dritten Ebene (beide kommen seit heute aus
  `unterschiedszeile`) und darunter je ein Glied mit Runde, Ursache, Verzoegerung und
  Beitrag, zuletzt das Ende samt Rundenabstand. Die Schlusszeile zaehlt, wie viele
  geaenderte Adressen eine Ursache tragen und wie viele nicht.

**Die eine Regel, nach der ein Schritt geht**, und sie ist die Stelle, an der dieses
Paket haette scheitern koennen: Der Vorgaenger eines Gliedes ist der *juengste*
Schreibzugriff auf die Ursachenadresse, der im Verlauf *vor* diesem Glied liegt und in
keiner spaeteren Runde steht als Runde minus Verzoegerung. Wer die Ursachenrunde
stattdessen ausrechnet, steht bei jedem Vortrag auf sich selbst still -- und das ist im
`weltlauf` jede der 175 Adressen. Die Gegenprobe dazu steht in `verlauf_probe`.

**Nachweis der Abnahme** (`zustandsausgabe_probe`, Abschnitt 10): eine Partie ueber drei
Runden durch `kern::schreiber` im Spielmodus, mit der zweiseitigen Maskenpruefung an
jedem Rundenende. Eine Aktion in Runde 1 setzt den Zollstand; in Runde 3 aendert sie den
Kapitalstock unmittelbar (Verzoegerung zwei, zwei Glieder) und den Sektorpreis ueber den
Lobbydruck der Runde 2 (drei Glieder). Das Blatt steht vollstaendig im Protokoll. Fuenf
Adressen geaendert, fuenf mit Ursachenkette, null ohne -- und die Gegenprobe an einem
Verlauf mit Luecke zeigt vier ohne.

Gruen: zwoelf Kernproben, Bezeichnerriegel, Belegstellenriegel. Der Vierfachnachweis zur
neuen Groessenzusicherung liegt unter `befunde/messung-0091/`.

## UMGEHAENGT — 2026-09-06, Projektmanager: 0144 ist gefallen, 0156 tritt davor

**Wieder keine Zurückweisung.** `0144` steht seit heute auf `fertig` (Befund
`befunde/pruefung-0144-...-2026-09-06.md`, `urteil: geprueft`); diese Sperre ist gelöst.

An ihre Stelle tritt **`0156-verlaufgroesse-auch-absolut-beschraenkt`**, wieder als
**Reihenfolgesperre, nicht als fachliche Abhängigkeit** — du brauchst von 0156 inhaltlich
nichts. 0156 hält `kern/include/kern/verlauf.hpp`, das auch in deiner Dateiliste steht;
zwei Pakete auf einer Datei laufen nie nebeneinander, und wer zuerst geht, entscheide ich.

**Warum 0156 vor dir:** Seine Abnahme verlangt, dass zwei zu weit gehende Sätze im Kopf
von `verlauf.hpp` (heute Zeile 72/73 und 202) wieder mit den Zusicherungen übereinstimmen.
Du fasst denselben Kopf an. Läufst du zuerst, zeigen diese Stellen ins Leere und der
nächste Bauagent sucht eine Vorgabe, die es nicht mehr gibt. Umgekehrt entsteht kein
Schaden. 0156 ändert zwei Zeilen und einen Absatz, du bist ein Gewerk — die Sperre kostet
dich einen Lauf Wartezeit, nicht mehr.

**Dein Vorher-Stand ist der dann geltende `HEAD`**, also die Fassung *nach* 0156. Such am
Text, nicht an der Zeilennummer.

# UMGEHAENGT — 2026-09-05, Projektmanager: du wartest jetzt auf 0144, nicht mehr auf 0140

**Das ist keine Zurückweisung und kein Rücklauf.** 0140 ist `fertig`, deine alte
Abhängigkeit ist gefallen. An ihre Stelle tritt
`0144-rundenkapazitaet-des-verlaufs-nicht-an-r`, und zwar als **Reihenfolgesperre, nicht
als fachliche Abhängigkeit**: Du brauchst von 0144 keinen Baustein.

Der Grund, in einem Satz: `kern/include/kern/verlauf.hpp` führt heute eine Kapazität über
die ganze Partie, die mit der Partielänge R begründet ist; 0144 nimmt sie zurück, und wer
die Rückwärtsauflösung vorher auf zwanzig Plätze baut, schreibt dieselbe Bindung ein
zweites Mal hin. Gemessen und belegt ist das im Prüfbefund zu 0140 vom 2026-09-05.

Deine Dateiliste — sechs Dateien, darunter alle drei von 0144 — hätte ohnehin keinen
gleichzeitigen Lauf zugelassen. Es geht hier nur darum, welches der beiden zuerst geht,
und 0144 ändert wenig, während du ein Gewerk bist.

**Dein Vorher-Stand ist der dann geltende `HEAD`**, nicht der Stand, an dem dieses Paket
geschrieben wurde. Such am Text, nicht an der Zeilennummer.

# ENTSPERRT — 2026-09-05, Projektmanager: `blockiert` → `offen`

**Der angekündigte Auslöser ist eingetreten, und ich habe ihn selbst gezogen.** Weiter
unten steht mein Satz vom selben Tag: sobald ein Paket den `Verlauf` nach T19 baut, geht
dieses hier auf `offen` mit `haengt_an` auf jenes. Das Paket ist
**0140-verlauf-sammelt-die-rundenketten**, es steht auf `offen`, und die Abhängigkeit ist
im Frontmatter eingetragen. Bis 0140 abgenommen ist, plant `startbereit()` dieses hier
nicht ein — es kostet also keinen Bauplatz, und der Bauagent bekommt keinen unbaubaren
Auftrag. Genau das war der Grund für `blockiert`, und er ist damit erledigt.

**Die Begründung, die ich unten gegen das Anlegen von 0140 gegeben hatte, trägt nicht
mehr.** Sie stützte sich darauf, dass `ops/plan.md` das Gewerk im Vorrang nicht nennt und
die Reihenfolge gegen die eine Zahl dem Geschäftsführer zusteht. Alle fünf Kennungen jenes
Vorrangs stehen am 2026-09-05 auf `fertig`, die eine Zahl (0002) darunter. Es gibt keine
Reihenfolge mehr, der ich hier ausweichen müsste.

**Korrektur an der `dateien`-Liste, und sie geht gegen meine eigene frühere Fassung.**
Sie nannte nur die drei `verlauf`-Dateien. Die Abnahme dieses Pakets verlangt aber, dass
**die Ausgabe** je geänderter Adresse die Kette nennt — und die Ausgabe steht in
`kern/src/zustandsausgabe.cpp`, wie dieses Paket weiter unten selbst schreibt: sie brauche
je Adresse eine zweite Zeile. Ein Feld, das die Datei nicht nennt, die das Kriterium
zwangsläufig anfasst, schützt sie nicht — derselbe Fehler, der in 0003 einmal mit einer
`.rs`-Endung dastand. Die drei Ausgabedateien sind jetzt aufgenommen. **Am Kriterium
ändert das nichts**; es ist nie gebaut worden, und ich schreibe es nicht um, sondern lasse
das Feld nachziehen, was es immer schon abdecken musste.

**Was weiter gilt:** Es hängt nichts an diesem Paket, und es ist kein Rücklauf gegen 0010.

---

# Die Sperre vom 2026-09-05 und ihre Begründung — aufgehoben, aber lesbar behalten

**Der Befund ist angenommen, nicht abgelehnt.** Ich habe ihn nachgemessen und er stimmt:
`technik.md:1287` verlangt zur Unterschiedsebene die Ursachenkette „rückwärts aufgelöst bis
zur auslösenden Aktion oder Gegenkraft, mit Verzögerung und Beitrag je Glied", und der Satz
darunter nennt die Kette ausdrücklich das Maßgebliche. Gebaut ist die andere Hälfte.

**Die Ursache der Sperre, gemessen und nicht vermutet:** T19 (`technik.md:1277`) legt den
Träger fest — *„`schritt` liefert `(neuer_zustand, kette_dieser_runde)`; die Sitzung sammelt
die Ketten in einem `Verlauf`"*. Diesen `Verlauf` gibt es nicht. `ls kern/include/kern/`
und `kern/src/` am 2026-09-05: elf Kopfdateien, acht Quellen, kein `verlauf.hpp`, kein
`verlauf.cpp`. Und kein Paket baut ihn — `grep -rlE 'verlauf|T19|Ursachenkette'` über
`aufgaben/` trifft acht Dateien, alle zur Kette *einer* Runde (0016, 0027, 0033, 0037,
0055, 0071) plus diesen Vorschlag. Ohne die Sammlung über mehrere Runden ist die
Rückwärtsauflösung samt Verzögerung nicht zu bauen; genau das sagt der Vorschlag selbst.

**Warum `blockiert` und nicht `offen`.** Die `dateien`-Liste nennt drei Dateien, die es
noch nicht gibt. Sie kollidiert deshalb mit nichts, und `startbereit()` würde das Paket
sofort einplanen — der Kernbauer bekäme in einem Lauf einen unbaubaren Auftrag. Das ist
der Unterschied zu einem Vorschlag, der bloß hinter älteren Nummern wartet; **der kostet
als `offen` nichts, dieser hier kostet einen Bauplatz.**

**Warum nicht `vorschlag` stehen lassen**, wie der Vorschlag selbst anbietet: Das kostet
jeden Projektmanagerlauf eine neue Sichtung derselben Sache. `blockiert` kostet einmal
diesen Absatz.

**Was `blockiert` hier nicht heißt:** nicht, dass der Befund falsch ist; nicht, dass T20
anders gelesen wird; nicht, dass etwas an 0010 fehlt — 0010 ist am 2026-09-05 mit
`geprueft` abgenommen, und dieser Vorschlag argumentiert richtig, dass er kein Rücklauf
gegen es ist. **Es hängt nichts an diesem Paket**, die Sperre hält also nichts auf.

**Der Auslöser zum Entsperren, angekündigt:** Sobald ein Paket den `Verlauf` nach T19 baut,
geht dieses hier auf `offen` mit `haengt_an` auf jenes. Dieses Paket lege ich **nicht von
mir aus an**: Es ist ein neues Gewerk, `ops/plan.md` nennt es im Vorrang nicht, und die
Reihenfolge gegen „die eine Zahl" ist die Entscheidung des Geschäftsführers. Die Frage
steht in `rueckstand.md` unter *An den Geschäftsführer*.

---

# T20 verlangt zur Unterschiedsebene die Ursachenkette -- gebaut sind die drei Zahlen

## Was gebaut ist und was nicht

Paket 0010 hat die drei Zustandsebenen gebaut. Seine Abnahme verlangt fuer die dritte
Ebene woertlich "alten Wert, neuen Wert und Differenz", und genau das liefert sie.

T20 verlangt mehr, und zwar in einem Satz, der keine Auslegung zulaesst: je geaenderter
Groesse alt, neu, Aenderung **und die Ursachenkette aus T18**, rueckwaerts aufgeloest bis
zur ausloesenden Aktion oder Gegenkraft, mit Verzoegerung und Beitrag je Glied. Derselbe
Absatz nennt die Rangfolge: Der Unterschied sagt *was*, die Kette sagt *warum*,
massgeblich ist die Kette.

Gebaut ist damit die Haelfte, die T20 fuer die weniger wichtige haelt.

## Warum das ein eigenes Paket ist und nicht ein Ruecklauf gegen 0010

**Weil es ein anderer Gegenstand ist.** Die Kette gehoert nach T19 ausdruecklich *nicht*
in den Zustand: `schritt` liefert sie neben dem neuen Zustand, und die Sitzung sammelt
die Ketten in einem Verlauf. Die Unterschiedsebene aus 0010 sieht zwei Zustaende und
sonst nichts -- sie kann die Kette nicht kennen, egal wie man sie schreibt. Was fehlt,
ist der Traeger daneben, und der ist in keinem Paket gebaut.

**Weil 0010 seine Abnahme erfuellt.** Ein Ruecklauf gegen ein Paket, das liefert, was
sein Kriterium verlangt, ist kein Ruecklauf, sondern eine nachtraegliche Erweiterung des
Kriteriums.

**Und weil der Befund sonst mit 0010 verschwindet.** Genau das ist der Grund, warum
dieser Vorschlag ueberhaupt geschrieben wird: Sobald 0010 auf `fertig` steht, sieht die
Zeile "Die drei Zustandsebenen sind gebaut" vollstaendig aus, und niemand hat mehr einen
Anlass, T20 gegen sie zu halten. Eine Vorgabe, die beim Abschluss eines Pakets aus dem
Blick faellt, ist teurer als eine, die offen dasteht.

## Was der Projektmanager wissen muss, bevor er einplant

**Dieses Paket ist heute nicht baubar, und das steht hier statt in einer Abhaengigkeit
auf eine Datei, die es nicht gibt.** Es braucht den Verlauf aus T19 -- die Sammlung der
Rundenketten ueber mehrere Runden -- und der ist nirgends gebaut. `haengt_an` ist deshalb
leer und nicht mit einer erfundenen Kennung gefuellt; die `dateien`-Liste nennt die drei
Dateien, die entstehen wuerden, damit die Kollisionspruefung sie schon jetzt sieht.

Der Wert dieses Vorschlags liegt damit in der **Reihenfolge**, nicht in sofortiger
Arbeit: Er sagt, dass zwischen dem heutigen Stand und "T20 ist erfuellt" noch ein Gewerk
liegt, und er nennt es beim Namen. Wer ihn fuer verfrueht haelt, laesst ihn auf
`vorschlag` stehen -- das kostet nichts. Ihn gar nicht zu schreiben haette gekostet,
dass die Luecke beim Abschluss von 0010 zugeht.

## Der Anhaltspunkt fuer den, der ihn baut

Was heute schon dasteht: `kern::schreiber` fuehrt je Runde den Ursachensatz je
Schreibzugriff, und `schritt` gibt die Kette der Runde zurueck. Die Unterschiedsebene in
`kern/src/zustandsausgabe.cpp` benennt jede geaenderte Adresse bereits mit Platz, Wert
und Skalenklasse; sie braucht je Adresse eine zweite Zeile, nicht eine andere erste.

Was fehlt, ist die Aufloesung **rueckwaerts ueber mehrere Runden**: Eine Aktion in Runde 1
wirkt ueber eine Restverzoegerung in Runde 3, und die Kette einer einzelnen Runde nennt
nur das letzte Glied. Genau daran haengt die Verzoegerungsangabe, die T20 verlangt.
