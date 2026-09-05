---
id: 0091-diff-ursachenkette-nach-t20
rolle: kernbauer
status: blockiert
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/verlauf.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/verlauf.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/verlauf_probe.cpp]
abnahme: Zu einem Unterschied ueber mehr als eine Runde nennt die Ausgabe je geaenderter Adresse nicht nur alt, neu und Differenz, sondern die Ursachenkette aus T18, rueckwaerts aufgeloest bis zur ausloesenden Aktion oder Gegenkraft, mit Verzoegerung und Beitrag je Glied. Nachgewiesen an einer Partie ueber mindestens drei Runden, in der eine Aktion in Runde 1 eine Groesse in Runde 3 aendert: Die Kette nennt beide Glieder und die Verzoegerung dazwischen, und eine Adresse ohne Ursache kommt nicht vor.
---

# GESPERRT — 2026-09-05, Projektmanager: `vorschlag` → `blockiert`

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
