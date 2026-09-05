# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-05 00:15. Fassung 24, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden muss.

**Vier Abnahmen, sieben Vorschläge entschieden, ein Widerspruch aufgelöst — und die
Werkzeugkette war rot, weil ich sie in der letzten Fassung selbst rot gemacht habe.**
97 Pakete: 19 offen, 1 gebaut, 71 fertig, 4 blockiert, **0 Vorschläge**. Alle vier
Bauplätze belegt, die Prüfstufe zum ersten Mal seit Tagen frei für 0027.

## Vier Abnahmen

| Paket | Rolle | Befund | jetzt |
|---|---|---|---|
| `0010-zustandsausgabe-drei-ebenen` | `kernbauer` | `geprueft`, 2 Nebenbefunde | `fertig` |
| `0043-t48-groessen-gegenkraft-5` | `architekt` | `geprueft`, 2 Zählfehler im Selbstbericht | `fertig` |
| `0069-t2-linkriegel-in-der-werkzeugkette` | `kernbauer` | `geprueft`, 1 Nebenbefund | `fertig` |
| `0073-belegstellenriegel-dateiname-weiter-links` | `testentwickler` | `geprueft`, 1 Nebenbefund | `fertig` |

**0010 ist Vorrang Nr. 5 und macht das Ergebnis von 0002 zum ersten Mal sichtbar.** Der
`kern-pruefer` hat es mit **fünfzig Mutationen** an den drei Dateien gemessen; zwanzig
überleben. Das ist kein Rücklaufgrund — kein einziger dieser Mutanten macht eine Zahl
falsch — aber es ist der beste Befund des Laufs, und er wird als 0097 gebaut.

**Vorrang Nr. 4 (0027) hat jetzt seinen Prüfplatz.** Das war die eine Sache, die dieser
Lauf mit einem Statusnachzug erledigen konnte: `reviewbereit()` sortiert nach der Zahl
bisheriger Urteile (`baulauf.py:240`), 0027 steht bei zwei und landete hinter vier
ungeprüften. Mit den vier Abnahmen oben ist es das einzige gebaute Paket und bekommt den
Platz. **Ich habe dafür nichts an ihm geändert.**

## Die Werkzeugkette war rot, und die Ursache war ich

Der `test-pruefer` schreibt es in den Befund zu 0073, damit es nicht untergeht:

> Bedingung 2: 24 Zitate gefunden, 19 aufgelöst, 8 Fundstellen übergangen.
> 5 Zitate zeigen auf eine Überschrift in rueckstand.md, die es nicht gibt.

Commit `81853b8` — Fassung 23 dieser Datei, von mir, 2026-09-04 22:26 — hat die Überschrift
*Was der Geschäftsführer entscheiden lassen muss* durch *An den Geschäftsführer* ersetzt.
Fünf Belegstellen in `daten/reihen.toml` und `daten/einheitenbefund-pwt-baci.md` zeigen
darauf. **Der Riegel hat genau das getan, wofür er gebaut wurde**; es ist der erste Befund
seiner Bedingung 2 gegen eine im laufenden Betrieb umbenannte Überschrift.

**Zwei Dinge folgen daraus, und ich habe beide getan.**

**Erstens: Die Überschrift steht wieder da** — unten, im Wortlaut. Das kostet mich nichts
und macht die Kette sofort grün. Der Preis, sie stehen zu lassen, wäre gewesen, dass in
diesem Durchgang vier Bauagenten gegen ein rotes Werkzeug messen und keiner von ihnen
etwas dafür kann. **Sie ist eine Stütze auf Zeit und fällt, sobald 0090 `fertig` ist.**

**Zweitens: 0090 baut die Kopplung weg, und der Auftrag ist enger als der Vorschlag.** Ich
habe die vier Fundstellen im Wortlaut gelesen, und sie sind nicht das, wonach sie im
Riegelbefund aussehen. Alle sagen sinngemäß: *„Die Sache stand am 2026-09-02 in
`rueckstand.md` unter der Überschrift X und ist in der vorliegenden Fassung jener Datei
nicht mehr aufgeführt."* Das sind **historische Aussagen**. Sie werden nicht dadurch
richtig, dass die Überschrift wieder existiert — sie hängen von vornherein am falschen
Anker. Der vom Vorschlag angebotene Weg 1 („Zitat auf eine lebende Überschrift nachziehen")
ist deshalb nicht der schlechtere, sondern der falsche, und ist aus dem Paket heraus.

Die Heilung ist eine bekannte Bauart: **0095 hat für den Namensfall 7 im selben Lauf genau
dieselbe vorgeschlagen** — Bezug als historisch ausweisen, den Commit nennen, der den
Wortlaut entfernt hat. Zweimal am selben Tag, an zwei unabhängigen Stellen.

**Die Falle, die daraus entsteht, steht im Paket:** Der Vorher-Stand des Bauagenten ist
durch meine Stütze grün. Der Nachweis, an dem 0090 hängt, ist deshalb die **Gegenprobe** an
einer Kopie außerhalb des Repos, in der die Überschrift gelöscht ist.

## Sieben Vorschläge, alle entschieden

| Paket | Rolle | jetzt | warum |
|---|---|---|---|
| **0090** rueckstand-überschrift | `datenbauer` | `offen` | drei Änderungen, siehe oben |
| **0091** diff-ursachenkette-t20 | `kernbauer` | **`blockiert`** | T19-Träger existiert nicht |
| **0092** abschnitt-18-zählfehler | `architekt` | `offen` | unverändert, mit Warnung |
| **0094** linkschalterform | `kernbauer` | `offen` | `haengt_an` um 0076 ergänzt |
| **0095** namensfall-7-herkunft | `testentwickler` | `fertig` | zusammengefasst in 0086 |
| **0097** zustandsausgabe-probe | `testentwickler` | `offen` | unverändert |
| **0098** diff-kennungen | ~~`projektmanager`~~ → `kernbauer` | `offen` | entschieden, siehe unten |

**Die Zahlenfalle zum neunten Mal, in 0090.** Die Abnahme verlangte, „die Zahl der
aufgelösten Zitate steigt von 19 auf 24, bei unveränderten 24 gefundenen und 8
übergangenen". Alle drei Zahlen stammen aus einer Summe des Riegels, und 0079, 0083 und
0086 schreiben in dieselbe Summe. Geprüft wird jetzt die Bedingung, gemessen gegen den
unmittelbar vorhergehenden Stand desselben Baums.

**0095 ist der zweite Fall binnen zwei Tagen, in dem ein Vorschlag selbst darum bittet,
nicht einzeln eingeplant zu werden** — nach 0089. Er hat die Nachbarpakete gelesen, bevor
er seine eigene Nummer verteidigt hat: dieselbe Rolle, dieselbe einzige Datei, derselbe
Kopfkommentar wie 0086, das noch nicht angefangen ist. Das ist der beste Grund für eine
Zusammenfassung, den es gibt. Ich habe vorher nachgemessen, dass 0086 auf `offen` steht,
null Rückläufe hat und seine Nebenzeilen-Grenze sich Wort für Wort mit 0095 deckt.

**Zwei Reihenfolgesperren gesetzt, beide gegen dieselbe Falle.** 0094 hängt jetzt an 0076,
0098 an 0097 — jeweils **als Kollisionsschutz gekennzeichnet, nicht als sachliche
Abhängigkeit**. Der Grund ist in beiden Fällen derselbe: `startbereit()` vergleicht die
Dateilisten nur unter `offen` (`baulauf.py:273`). Sobald das vordere Paket auf `gebaut`
steht, ist sein Anspruch unsichtbar, und das hintere wird eingeplant, während sein Prüfer
an derselben Datei am dann geltenden `HEAD` misst. Daran ist 0027 zweimal schuldlos
gescheitert. Beide Vorschläge hatten die Kollision selbst benannt und ausdrücklich mir
überlassen; hier ist die Entscheidung.

## Der Widerspruch, den ich aufgelöst habe — und warum das keine Entwurfsentscheidung war

0098 kam mit `rolle: projektmanager` und legte mir zwei Zweige vor: `diff` subtrahiert auf
den beiden Kennungen, T5 Klasse 12 verbietet auf ihnen jede Arithmetik außer der
Gleichheit. Gemessen: `partie.parameter_pruefsumme` alt `-6917529027641081856`, neu
`4611686018427387904`, ausgewiesene Differenz `11529215046068469760` — und dahinter in
derselben Zeile die Klassenangabe *„Bitmuster ohne Größenbedeutung"*.

**Es gilt T5.** Die Begründung in drei Sätzen:

Von den beiden Zweigen steht mir nur einer offen. Der andere ändert `technik.md`, und über
den Entwurf entscheide ich nicht. **Aber ich muss ihn auch nicht an dich weiterreichen,
denn der Widerspruch ist gar keiner zwischen zwei Vorgaben:** T5 ist die Vorgabe, die
andere Seite ist die `abnahme`-Zeile von 0010 — und **die habe ich geschrieben.** Sie sagt
„jede Adresse … mit Differenz" und macht keine Ausnahme, obwohl T5 vorher dastand. Ein
Kriterium von mir, das eine Vorgabe überschreibt, ist mein Fehler und nicht der Entwurf.

Das ist derselbe Fall wie die T50-Bedingung in der Abnahme von 0002 in der letzten
Fassung: **das Kriterium war meines und war falsch.** Zweimal in zwei Läufen. Der
Bauagent von 0010 hat nichts falsch gemacht; er hat sein Kriterium wörtlich genommen, und
das war die zulässige Lesart.

## Was der Geschäftsführer entscheiden lassen muss

> **Diese Überschrift trägt vorerst eine technische Last.** Fünf Belegstellen in
> `daten/` zitieren sie; bis **0090** `fertig` ist, macht ihr Wegfall die Werkzeugkette
> rot. Danach ist sie wieder frei — und `rueckstand.md` sollte nie wieder ein
> Zitatanker sein.

**1. Der T19-Träger fehlt, und ich lege ihn nicht von mir aus an.** `technik.md:1287` (T20)
verlangt zur Unterschiedsebene die Ursachenkette, „rückwärts aufgelöst bis zur auslösenden
Aktion oder Gegenkraft, mit Verzögerung und Beitrag je Glied" — und nennt sie im Satz
darunter das Maßgebliche gegenüber den Zahlen. Gebaut ist mit 0010 die andere Hälfte.

Nachgemessen: T19 (`technik.md:1277`) legt den Träger fest — *„die Sitzung sammelt die
Ketten in einem `Verlauf`"*. Den gibt es nicht. Elf Kopfdateien, acht Quellen unter `kern/`,
kein `verlauf.hpp`. Und kein Paket baut ihn: `grep -rlE 'verlauf|T19|Ursachenkette'` über
`aufgaben/` trifft acht Dateien, alle zur Kette *einer* Runde.

**Deshalb steht 0091 auf `blockiert` und nicht auf `offen`:** Seine Dateiliste nennt drei
Dateien, die es nicht gibt, kollidiert also mit nichts — `startbereit()` würde es sofort
einplanen und der Kernbauer bekäme einen unbaubaren Auftrag. **Es hängt nichts daran**, die
Sperre hält nichts auf. Der T19-Träger wäre ein neues Gewerk, dein Vorrang nennt ihn nicht,
und die Reihenfolge gegen „die eine Zahl" ist deine Entscheidung, nicht meine. Sagst du ja,
entsperrt 0091 mit ihm.

**2. Der Bauplatz nach Dienstalter, zum vierten Mal gemessen — und diesmal ist es ein
ganzes Gewerk.** Nachgemessen mit `--trocken --gleichzeitig 12`: **sieben Pakete sind
startbereit, vier bekommen einen Platz.**

| Platz | Paket | Rolle |
|---|---|---|
| 1 | `0051-t46-gebietspraefix-entscheiden` | architekt |
| 2 | `0076-riegel-sammeln-notfound-je-quelle` | kernbauer |
| 3 | `0078-reihentoml-preisbasis-nach-t53-nachziehen` | datenbauer |
| 4 | `0079-belegstellenriegel-zitat-ohne-anfuehrung` | testentwickler |
| — | `0085-abbruchmeldungen-im-wortlaut-pruefen` | **testentwickler, Datei frei** |
| — | `0088-werte-probe-vier-unbelegte-vorgaben` | **testentwickler, Datei frei** |
| — | `0097-zustandsausgabe-probe-zuordnungen-festnageln` | **testentwickler, Datei frei** |

Die drei Verlierer sind **dieselbe Rolle** und schneiden sich **in keiner einzigen Datei** —
weder miteinander noch mit den vier Gewinnern. Der Testentwickler könnte in diesem
Durchgang vier Pakete gleichzeitig abarbeiten und bekommt eines. Ursache ist wie beim
letzten Mal `sorted(glob)` (`baulauf.py:210, 301`).

**0088 verliert zum zweiten Plan in Folge** — das Paket, das die vier Lücken im gerade
abgenommenen Kern schließt. **0097 verliert im selben Lauf, in dem sein Anlass gemessen
wurde:** siebzehn Mutationen überleben die Zustandsausgabenprobe zu Unrecht, darunter eine,
die 71 der 310 Adressen mit einer falschen Einheit beschriftet.

Ich sperre dafür nichts künstlich, und ich ändere `baulauf.py` nicht — beides gehört mir
nicht. **Das ist der vierte Fall; die drei vorigen hießen 0027, 0027 und 0088.** Wenn dir
die Reihenfolge wichtiger ist als das Dienstalter, ist das eine Änderung an `baulauf.py`
und deine Entscheidung.

**3. `0041` trägt weiter `rolle: geschaeftsfuehrer`** und steht auf `blockiert`. Diese Rolle
ist nicht in `BAUROLLEN`; kein Runner zieht das Paket je. Dritte Fassung in Folge
unverändert, hier nur, damit es nicht aus dem Blick fällt.

**4. Die T50-Fehlalarme aus der letzten Fassung sind unverändert offen.** Ich lege dafür
weiter kein Paket an; ob ein sechstes Architektenpaket an `technik.md` den Vorrang wert
ist, entscheidest du.

## 0061 bleibt gesperrt — der angekündigte Auslöser ist gezogen und hat nicht ausgelöst

Die letzte Fassung hat angekündigt: *„liefert der `testentwickler` nach dem 18:17 an
irgendeiner Datei unter `pruefstand/`, geht 0061 ohne Änderung auf `offen`."*

**Gezogen und gemessen:** `git log --since='2026-09-04 18:17' -- .../pruefstand/` gibt
**nichts** aus. Der Testentwickler hat seither dreimal geliefert — 0073, 0067, 0077 —, und
keine dieser Lieferungen berührt `pruefstand/`. Der letzte Eintrag an der Zieldatei
`vorrat_kernanker_probe.cpp` bleibt `f68e8fb` vom 2026-09-03 aus einem fremden Paket.

Der Auslöser bleibt für den nächsten Lauf stehen, unverändert.

## Was der nächste Lauf zuerst anfasst

1. **Prüfbefund zu 0027 auswerten.** Es hat diesmal den Platz. Zwei Rückläufe von drei —
   wird es `zurueck`, ist **vor** dem dritten Lauf der Zuschnitt fällig, nicht nach ihm,
   sonst geht 0072 mit fest. Wird es `geprueft`, fällt mit `zustand.hpp` die Sperre für
   0072.
2. **Kein Folgepaket zu `werte.hpp` schneiden, bevor 0092 `fertig` ist.** Der
   Annahmevermerk von 0043 hat es umgekehrt angekündigt — das war vor dem Befund. Abschnitt
   18 nennt drei von sechs Stellen mit „siebzehn" nicht; ein Folgepaket aus dieser Liste
   erbt den Zählfehler. Der Vermerk steht in 0092.
3. **Angekündigter Auslöser 0061** (siehe oben) — erneut ziehen.
4. **0090 nicht für erledigt halten, weil der Riegel grün meldet.** Die Überschrift ist
   meine Stütze, nicht sein Werk. Erst mit seiner Gegenprobe fällt sie.
5. **Fällig, sobald 0084 abgenommen ist:** Übertrag der Reihe 20 nach `daten/reihen.toml`
   (Datenbauer). 0078 hat sie ausdrücklich herausgehalten. **Reihenfolge beachten** —
   `reihen.toml` trägt dann schon 0078 und 0090.
6. **Befund 3 aus der Prüfung von 0002 lesen, bevor Schritt 6 zugeschnitten wird.**
   `marktkorb(m, k)` ist für T33 Punkt 3 heute nicht aufrufbar. Unverändert aus der letzten
   Fassung: Weder der Prüfer noch ich raten, an welcher der zwei Stellen die Heilung liegt.
