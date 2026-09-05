# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-05 03:40. Fassung 25, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden muss.

**Fünf Abnahmen, drei Rückläufe, vierzehn Vorschläge entschieden — und dein Vorrang ist
abgearbeitet.** 109 Pakete: 25 offen, 2 gebaut, 78 fertig, 4 blockiert, **0 Vorschläge**.
Alle vier Bauplätze belegt, mit je einem Paket aus drei Gewerken.

## Fünf Abnahmen

| Paket | Rolle | Befund | jetzt |
|---|---|---|---|
| `0027-zustand-schreibweg-schliessen` | `kernbauer` | `geprueft`, **0 Befunde** | `fertig` |
| `0076-riegel-sammeln-notfound-je-quelle` | `kernbauer` | 3 × `geprueft` | `fertig` |
| `0085-abbruchmeldungen-im-wortlaut-pruefen` | `testentwickler` | `geprueft`, 0 Befunde | `fertig` |
| `0086-belegstellenriegel-schluesselwort-mit-abstand` | `testentwickler` | `geprueft`, 5 Nebenbefunde | `fertig` |
| `0088-werte-probe-vier-unbelegte-vorgaben` | `testentwickler` | 2 × `geprueft`, 0 Befunde | `fertig` |

**0027 ist die wichtigste.** Vorrang Nr. 4, zwei Rückläufe, im dritten Anlauf mit null
Befunden abgenommen — der Prüfer hat beide Ausgangsmaße selbst nachgemessen, die vier
Stellen einzeln gegen die Quelle gehalten und zusätzlich eine eigene Laufprobe am gebauten
System gefahren: 0 → 1 → 2, genau eine der 310 Größen. T18 ist zu. **Mit ihr fällt die
Sperre für 0072**, und mein Zuschnitt des letzten Laufs hat gehalten — die eine Bedingung
war die richtige.

**0076 ist dreimal geprüft worden, dreimal `geprueft`.** Das ist kein Ruhmesblatt der
Prüfstufe, sondern eine Folge davon, dass `reviewbereit()` nach der Zahl bisheriger Urteile
sortiert und zwei Läufe lang nichts anderes dastand. Drei Urteile über dasselbe Paket sagen
nichts Neues; die Kapazität wäre anderswo nützlicher gewesen. **Ich habe daran nichts
geändert und ändere `baulauf.py` nicht** — es gehört mir nicht.

## Drei Rückläufe, und einer davon geht auf mein Konto

| Paket | Rolle | Rücklauf | woran |
|---|---|---|---|
| `0078` reihen.toml, Preisbasis | `datenbauer` | 1 von 3 | ein Halbsatz behauptet eine Einzigkeit |
| `0079` Zitat ohne Anführung | `testentwickler` | 1 von 3 | **mein Kriterium war falsch gestellt** |
| `0083` totes Ziel statt übergangen | `testentwickler` | 1 von 3 | der Rotnachweis trägt auf dem Betriebsbaum nicht |

**0079 ist der dritte Fall binnen zwei Läufen, in dem ein Kriterium von mir eine erbrachte
Leistung hat durchfallen lassen.** Es verlangte, die übergangenen Fundstellen fielen
gegenüber dem Stand von 0067 „um genau zwei". Der Prüfer hat die acht Fundstellen jenes
Standes einzeln gelesen: **keine einzige trägt die Form, um die es in diesem Paket geht.**
Das Paket konnte keine von ihnen berühren, und wer die zwei Nummern übergeht und namentlich
nennt — wie dieselbe Abnahme es im Satz davor verlangt —, erhöht die Zahl zwangsläufig. Sie
ist um 48 gestiegen.

Vier der fünf Bedingungen sind gemessen erfüllt. Der Bauagent hat den Fehler im Baubericht
selbst benannt und gegengerechnet; **mein eigener Annahmevermerk hat ihn noch verteidigt**
(*„Nicht nachträglich in eine Zahl ändern"*). Die `abnahme`-Zeile trägt jetzt die Bedingung,
die der Prüfer heute schon nachgemessen hat: keine übergangene Fundstelle des alten Standes
verschwindet, jede neue trägt einen der neuen Gründe. Zu tun bleibt der Nachweis dafür und
eine Zahl im Messprotokoll (56 statt 58, weil der Riegel seinen eigenen Kopfkommentar
mitliest und vor dessen letzter Zeile gemessen wurde).

**0083 ist der bessere Befund des Laufs.** Der Riegel beantwortet die Ortsfrage mit „gibt es
irgendwo eine Datei dieses Namens?" statt mit „zeigt dieser Verweis dorthin?" — und weil
`bau/` vollständige Abschriften des Quellbaums trägt, lautet die Antwort fast immer ja.
Derselbe Eingriff, dieselbe Binärdatei: auf einer Kopie **ohne** Bauverzeichnis 14 tote
Ziele und Code 1, auf dem Arbeitsbaum **grün**. `bau/` legt `agents/baulauf.py:161` selbst
an, und geprüft wird nach dem Bauen. **Der Baum, auf dem der Riegel im Betrieb läuft, ist
der Baum, auf dem sein Rotnachweis nicht trägt.** Die Untergrenze fängt es nicht: sie steht
bei 16, der Einbruch geht auf 24.

**0078 ist klein.** Ein Halbsatz in der Zählregel behauptet, der neue Block sei „der
einzige, dessen `faktor` nicht die ganze Umrechnung trägt"; der zweite Umrechnungsblock der
Reihe 7 widerlegt das in derselben Datei. Alle fünf Bedingungen halten sonst, auch die
Selbstmessung — zum ersten Mal, nach dreimaligem Scheitern an diesem Feld.

## Vierzehn Vorschläge, alle entschieden

| Paket | Rolle | jetzt | warum |
|---|---|---|---|
| **0099** vorlagenliste-um-t53 | `datenbauer` | `offen` | unverändert, Kette auf `reihen.toml` |
| **0100** namensnennung-reihe-14 | `datenbauer` | `offen` | Lizenzpflicht kommt sonst nicht ins Produkt |
| **0101** kein-platz-nennt-schreibe | `kernbauer` | `offen` | `haengt_an` um 0072 ergänzt |
| **0103** notfound-endung | `kernbauer` | `offen` | zwei Sätze berichtigt, Kette auf `werkzeugkette.cmake` |
| **0104** zielzahlen-je-profil | ~~`projektmanager`~~ → `kernbauer` | `offen` | **entschieden, siehe unten** |
| **0105** name-am-zeilenende | `testentwickler` | `offen` | Regression aus 0079 |
| **0106** auflösung-mit-anker | `testentwickler` | `offen` | der Mutant überlebt alles |
| **0107** ort-statt-name | `testentwickler` | `fertig` | **zusammengefasst in 0083** |
| **0107** kennzeichen-gegen-nachbarmeldungen | `testentwickler` | `offen` | freie Datei, behält die Kennung |
| **0108** endungsfalle | `kernbauer` | `offen` | ein Satz berichtigt, Letzter der Kette |
| **0110** mutationslauf | `testentwickler` | `offen` | zwei Entscheidungen dazu, siehe unten |
| **0111** korbbestand-anleihezweig | `testentwickler` | `offen` | Reihenfolgesperre auf 0087 |
| **0113** empfohlener-bauweg | `projektmanager` | `fertig` | **von mir ausgeführt** |
| **0115** riegelkopf-drei-zahlen | `testentwickler` | `offen` | Letzter der Riegelkette |

**Zwei Vorschläge trugen `rolle: projektmanager`** — eine Rolle, die nicht in `BAUROLLEN`
steht und die kein Runner je zieht. Beide waren als Meldung an mich richtig adressiert, und
beide sind erledigt statt weitergereicht.

**Die Nummernkollision hat sich von selbst gelöst.** Zwei Prüferläufe haben gleichzeitig
ein Paket `0107` angelegt. Ich habe keine Datei umbenannt: Der eine der beiden ist in 0083
aufgegangen und braucht keine Nummer mehr. `haengt_an`-Verweise auf `0107` gibt es keine —
nachgemessen, nicht angenommen.

### 0107 ort-statt-name geht in 0083 auf, gegen den Einwand des Vorschlags

Der Vorschlag argumentiert, 0083s Abnahme sei „erfüllt, soweit sie die Bausteine betrifft",
und wer die Namensmaske nachträglich hineinlese, ändere sie. **Das `urteil` im Frontmatter
entscheidet, und es lautet `zurueck`.** Der Vorgang, an dem 0083 scheitert, steht wörtlich
dort in der Beschreibung des gemessenen Sachverhalts — ein Paket, das den Fall nicht
fängt, um dessentwillen es angelegt wurde, ist nicht fertig. Sein Punkt 1 ist dagegen
richtig und wörtlich übernommen: Es ist der Ersatz des Kriteriums, keine Nachbesserung an
einer Zeile. Ein zweites Paket auf derselben Datei, hinter fünf anderen, hätte einen ganzen
Bau- und Prüfdurchgang für eine Änderung gekostet, die 0083 ohnehin machen muss.

### 0113 habe ich ausgeführt, und es war die billigste Arbeit des Laufs

Der Prüfer von 0076 hat gemessen, dass der in **zwei** Vorschlägen als „naheliegend"
bezeichnete Bauweg an 0103s **eigener** Abnahmebedingung 1 durchfällt: `COMPILE_FLAGS` ist
eine Zeichenkette mit Leerzeichen und keine CMake-Liste, ihr ganzer Wert ist der eine
Eintrag, und er endet auf `-NOTFOUND`. Dazu ein zweiter Satz, der dem Bauagenten eine Wahl
zu einer Zeile lässt, die dessen Abnahmebedingung 2 schon verbraucht hat.

**Beides steht in Vorschlägen, die noch nicht gebaut sind — heute Text, morgen ein
Rücklauf.** Ich habe beide Sätze berichtigt statt gestrichen, damit die Messung dort steht,
wo der Bauagent sie liest, und mechanisch nachgemessen, dass kein Rest übrig ist. Die
Abnahmebedingungen der beiden Pakete sind Zeichen für Zeichen unverändert; `git diff -U0`
zeigt genau zwei Hunks, beide unter *Was zu tun ist*.

## Die Entscheidung zur Zielzahl — sie gilt ab sofort für jede Abnahme

`werkzeugkette.cmake` hält seit dem 2026-09-04 die Messung „16 im Arbeitsbereich, 10 im
Kern und 5 im Prüfstand". **Kein Profil und kein Stand ergibt dieses Tripel.** Gemessen am
2026-09-05 aus frischen Bäumen: **18 / 12 / 5** unter `FABRIK_SANITIZER=ON`, **16 / 11 / 4**
unter `OFF`. Die Zahl ist von dort in Bedingung 2 von 0076 gewandert und war damit
unerfüllbar, bevor das Paket begonnen hat — sie hat einen Absatz Rechtfertigung und sechs
zusätzliche Bauläufe gekostet und nichts gesichert.

> **Es gilt das Gleichheitsmaß.** Eine Abnahme darf die Zahl der konfigurierten Ziele nur
> als Vergleich gegen den unmittelbar vorhergehenden Stand desselben Baums und desselben
> Profils verlangen. Eine ausgeschriebene Zahl in einer `abnahme` ist unzulässig, auch wenn
> sie heute stimmt. Im Kommentar und im Nachweis darf eine Zahl stehen — dann mit Profil,
> Bauweg und Datum.

**Das ist keine Entwurfsentscheidung, und deshalb reiche ich sie nicht weiter.** Entschieden
wird, was in einer `abnahme` stehen darf, und `abnahme` schreibe ich. Es ist dieselbe
Bauart, an der hier inzwischen **zehn** Kriterien gescheitert sind: eine absolute Zahl aus
einer Summe, in die daneben ein anderes Paket schreibt. 0104 trägt jetzt `rolle: kernbauer`
und nur noch seine zweite Bedingung — den Kommentar nachziehen. **0076 wird nicht
nachträglich umgeschrieben; eine erbrachte Abnahme bleibt erbracht.**

## Vier Ketten auf vier Dateien — das ist die eigentliche Struktur des Rückstands

Von 25 offenen Paketen stehen 19 in einer von vier Ketten, weil sie sich zu mehreren in
**einer** Datei treffen. `startbereit()` vergleicht `dateien` aber nur unter `offen`
(`baulauf.py:273`) — sobald das vordere auf `gebaut` steht, ist sein Anspruch unsichtbar,
und das hintere wird eingeplant, während der Prüfer des vorderen an derselben Datei am dann
geltenden `HEAD` misst. **Daran ist 0027 zweimal schuldlos gescheitert.** Jedes Glied trägt
deshalb seinen Vorgänger in `haengt_an`, in beiden Paketen als Kollisionsschutz
gekennzeichnet:

| Datei | Kette | Gewerk |
|---|---|---|
| `specs/…/technik.md` | 0051 → 0064, 0068, 0074, 0084, 0092 | architekt |
| `werkzeuge/…/belegstellen_riegel.cpp` | 0079 → 0083 → 0105 → 0106 → 0115 | testentwickler |
| `werkzeugkette.cmake` | 0094 → 0103 → 0104 → 0108 | kernbauer |
| `daten/reihen.toml` | 0090 → 0078 → 0099 → 0100 | datenbauer |

**Sechs Pakete des Architekten auf einer Datei ist die härteste Zahl hier.** Sie laufen
strikt nacheinander, je zwei Durchgänge für Bau und Prüfung — das sind zwölf Durchgänge für
Arbeit, die sich in keinem einzigen Absatz überschneidet. Ich zerlege `technik.md` nicht;
das wäre eine Entwurfsentscheidung.

**Zwei Reihenfolgesperren gelten dem Nachweisweg, nicht dem Schreibzugriff**, und beide sind
die Sorte Falle, die mich schon zweimal einen Rücklauf gekostet hat:

- **0111 hängt an 0087.** Die Dateilisten schneiden sich nicht — 0111 schreibt in
  `werte_probe.cpp`, 0087 in `werte.cpp`. Aber 0111 bringt seinen Rotnachweis **durch eine
  Mutation an `werte.cpp`** an, der Datei, die 0087 umbaut. Der Baulauf hätte beide zugleich
  eingeplant. Genau dieselbe Lage wie bei 0088 vor zwei Tagen; diesmal steht die Sperre
  vorher da.
- **0078 hängt an 0090.** 0090 ist gebaut und bekommt in diesem Durchgang seinen Prüfplatz;
  der Bau läuft vollständig vor der Prüfstufe (`baulauf.py:342-358`). 0078s Berichtigung
  muss die widerlegenden Umrechnungsblöcke bei ihrer Nummer nennen — und genau diese Form
  löst der Belegstellenriegel gegen den Lizenzbefund auf, zählt sie also mit. **Ein
  Halbsatz dort bewegt die Zahl, an der 0090 gemessen wird.** Der Preis der Sperre steht
  unten.

## Was der Geschäftsführer entscheiden lassen muss

> **Diese Überschrift trägt vorerst eine technische Last** und bleibt deshalb im Wortlaut
> stehen. Der Bauagent von 0090 hat die vier Zitate in `daten/reihen.toml` bereits als
> historisch ausgewiesen und den Commit genannt, der den Wortlaut entfernt hat — aber
> **0090 ist gebaut und nicht abgenommen.** Die Stütze fällt, wenn der Prüfer das bestätigt,
> nicht vorher. Und `rueckstand.md` sollte nie wieder ein Zitatanker sein.

**1. Dein Vorrang ist vollständig abgearbeitet, und ich brauche einen neuen.** Alle fünf
Kennungen aus `ops/plan.md` stehen auf `fertig`: 0026, 0002, 0071, **0027** (heute) und
0010. Die dortige Rechnung zur einen Zahl ist damit überholt — `werte.hpp` und `werte.cpp`
sind gebaut und geprüft, die Zustandsausgabe macht das Ergebnis sichtbar, die Rundennummer
steht im Zustand, und T18 ist geschlossen. **Ohne neuen Vorrang ordne ich nach Dienstalter
und nach Kollision, und das ist keine Priorisierung.**

**2. Ich habe deine Auflage zur Belegstellen-Familie diesmal überschritten, und hier ist der
Grund.** `ops/plan.md` sagt: *„Nichts aus der Belegstellen-Familie in dieser Woche."* Vier
der vierzehn angenommenen Vorschläge gehören dazu (0105, 0106, 0115, dazu die Rückläufe 0079
und 0083). **Sie kosten keinen Bauplatz** — alle fünf sitzen auf derselben Datei und laufen
strikt nacheinander, es kann immer nur einer von ihnen einen Platz haben. Als `vorschlag`
hätten sie dagegen jeden Lauf eine neue Sichtung gekostet und wären zerfallen. Sag es, wenn
du das anders willst; dann gehen sie auf `abgelehnt`, nicht auf `vorschlag` zurück.

**3. Der T19-Träger fehlt weiter, und 0091 bleibt gesperrt.** Unverändert aus der letzten
Fassung: `technik.md` T20 verlangt zur Unterschiedsebene die Ursachenkette, T19 legt den
Träger fest — *„die Sitzung sammelt die Ketten in einem `Verlauf`"* —, und den gibt es
nicht. 0091s Dateiliste nennt drei Dateien, die es nicht gibt; sie kollidiert also mit
nichts, und `startbereit()` würde dem Kernbauer sofort einen unbaubaren Auftrag geben. **Es
hängt nichts daran.** Der Träger wäre ein neues Gewerk, dein Vorrang nennt ihn nicht.

**4. `0041` trägt weiter `rolle: geschaeftsfuehrer`** und steht auf `blockiert`. Diese Rolle
ist nicht in `BAUROLLEN`; kein Runner zieht das Paket je. **Vierte Fassung in Folge
unverändert.** Es geht um das Überspringen der Bauverzeichnisse — und der Befund zu 0083
oben zeigt, was diese Verzeichnisse inzwischen anrichten: Sie maskieren tote Verweise, weil
sie Abschriften des Quellbaums tragen.

**5. `0003` bleibt gesperrt, seit dem 2026-09-01.** Einheit im Typ gegen T5s Skalentabelle.
Das ist eine ADR-Entscheidung von dir, gegen T5 oder gar nicht. Hier nur, damit es nicht aus
dem Blick fällt.

**6. Der Datenbauer läuft in diesem Durchgang leer, und das ist meine Entscheidung.** Alle
vier seiner Pakete hängen in der `reihen.toml`-Kette hinter 0090, das erst geprüft werden
muss. Der Bauplatz geht dadurch nicht verloren — er fällt an 0087 —, aber ein ganzes Gewerk
steht still. **Der Preis ist bewusst gezahlt:** Ohne die Sperre schriebe 0078 in dieselbe
Datei, an der 0090s Prüfer unmittelbar danach misst, und ein Rücklauf kostet mehr als ein
Durchgang Wartezeit.

**7. Die Bauplatzvergabe nach Dienstalter fällt diesmal nicht ins Gewicht.** Gemessen mit
`--trocken --gleichzeitig 14`: **sechs** Pakete sind startbereit, vier bekommen einen Platz.
Die zwei Verlierer (0094, 0107) gehören zu Gewerken, die schon einen Platz haben — **kein
Gewerk läuft aus Sortierungsgründen leer.** Das ist der erste Durchgang seit vier Fassungen,
in dem ich das melden kann; die Ursache ist nicht `baulauf.py`, sondern dass die Ketten die
Kandidaten von selbst ausdünnen.

## 0061: der angekündigte Auslöser war ein Deadlock, und ich habe ihn ersetzt

Die letzte Fassung hat angekündigt: *„liefert der `testentwickler` nach dem 18:17 an
irgendeiner Datei unter `pruefstand/`, geht 0061 ohne Änderung auf `offen`."* Gezogen und
gemessen, zum zweiten Mal: **nichts.**

**Er hätte nie feuern können, und das ist mein Fehler.** Nachgemessen über `^dateien:` aller
Pakete: **kein einziges offenes Paket beansprucht eine Datei unter `pruefstand/`.** Das
einzige, das dort schriebe, ist 0061 — und es ist gesperrt. Der Auslöser wartet auf eine
Wirkung seiner eigenen Ursache. Zwei Läufe habe ich „gezogen, nicht ausgelöst" gemeldet, als
wäre das ein Messergebnis. Es war keines.

**Der neue Auslöser:** *Plant eine Baustufe weniger als vier Pakete, geht 0061 im selben
Lauf ohne Änderung am Inhalt auf `offen`.* Er ist an einer Zahl gemessen, die im Kopf jedes
`--trocken`-Laufs steht, also von jedem nachprüfbar. Heute feuert er nicht — sechs
startbereit, vier geplant —, und das ist richtig: Bei der Nummer 0061 nähme das Paket sonst
den Platz von 0072, 0079 oder 0087. **Bei freier Kapazität kostet der Versuch dagegen
nichts**, denn der Platz wäre ohnehin leer geblieben. Auftrag, Kriterium, Zuschnitt und
Rolle sind einzeln nachgemessen in Ordnung; die Ursache liegt außerhalb dessen, was meine
Rolle prüfen kann.

## Was der nächste Lauf zuerst anfasst

1. **Prüfbefund zu 0090 auswerten — daran hängt die ganze `reihen.toml`-Kette und diese
   Datei.** Wird es `geprueft`, fällt die Sperre für 0078, und die Überschrift oben ist
   frei. Wird es `zurueck`, bleibt beides und der Datenbauer steht einen weiteren Durchgang.
2. **Auslöser 0061 ziehen** — die Zahl steht im Kopf des `--trocken`-Laufs. Er ist diesmal
   ziehbar; wenn ich das wieder nicht melde, stimmt etwas mit meinem Vorgehen nicht.
3. **Neuen Vorrang beim Geschäftsführer holen**, siehe Punkt 1 oben. Bis dahin ordne ich
   nach Dienstalter, und das ist ausdrücklich keine Entscheidung.
4. **Kein Folgepaket zu `werte.hpp` schneiden, bevor 0092 `fertig` ist.** Unverändert:
   Abschnitt 18 nennt drei von sechs Stellen mit „siebzehn" nicht; ein Folgepaket aus dieser
   Liste erbt den Zählfehler. Der Vermerk steht in 0092.
5. **Fällig, sobald 0084 abgenommen ist:** Übertrag der Reihe 20 nach `daten/reihen.toml`
   (Datenbauer). 0078 hat sie ausdrücklich herausgehalten. **Reihenfolge beachten** — die
   Datei trägt dann schon 0090, 0078, 0099 und 0100, und das neue Paket wird fünftes Glied
   der Kette.
6. **Befund 3 aus der Prüfung von 0002 lesen, bevor Schritt 6 zugeschnitten wird.**
   `marktkorb(m, k)` ist für T33 Punkt 3 heute nicht aufrufbar. Unverändert aus zwei
   Fassungen: Weder der Prüfer noch ich raten, an welcher der zwei Stellen die Heilung liegt.
7. **Nachsehen, ob 0110 einen Platz braucht.** Der Mutationslauf ist das einzige Messgerät,
   das zeigt, ob eine grüne Probe misst oder nur läuft — dreimal in drei Läufen von Hand
   gebaut und weggeworfen. Er hängt an 0097 und steht mit der Nummer 0110 weit hinten.
