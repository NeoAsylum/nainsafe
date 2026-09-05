# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-05 09:16. Fassung 26, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden muss.

**Der Betreiber hat vier Pakete selbst geschrieben, ich habe alle vier angenommen, und
danach die engste Datei des Vorhabens neu geordnet.** 113 Pakete: 26 offen, 6 gebaut,
79 fertig, 2 blockiert, **0 Vorschläge**. Keine einzige Abnahme — seit dem letzten Lauf
liegt kein neues Prüfurteil vor. Die Bauseite plant 4 von 8 Plätzen.

## Kein Prüfurteil seit dem letzten Lauf, und das ist die Lage, nicht ein Versäumnis

Sechs Pakete stehen auf `gebaut`: 0051, 0072, 0079, 0087, 0090, 0097. Für **keines** von
ihnen gibt es einen Befund. Nachgemessen, nicht angenommen: `ls befunde/` führt keine
Datei `pruefung-0051-*`, `pruefung-0072-*`, `pruefung-0087-*`, `pruefung-0090-*` oder
`pruefung-0097-*`; die einzige Datei zu 0079 stammt vom Rücklauf, den die letzte Fassung
schon verarbeitet hat, und das Paket ist seither neu gebaut worden (`f8c8598`).

Es gab also nichts nachzuziehen. Vier der sechs sind erst nach meinem letzten Lauf
geliefert worden — 0051, 0072, 0079 und 0087 —, die anderen zwei warteten schon. **Alle
sechs bekommen in diesem Durchgang einen Prüfplatz.** Das ist der Engpass des Vorhabens
in einer Zahl: An diesen sechs Urteilen hängen **acht** offene Pakete unmittelbar und
über die Ketten noch einmal so viele.

## Vier Pakete des Betreibers, alle angenommen

| Paket | Rolle | jetzt | Entscheidung |
|---|---|---|---|
| **0116** länderzahl-als-parameter | `architekt` | `offen` | `haengt_an: [0051]` ergänzt, **an die Spitze von `technik.md`** |
| **0117** politikpfad-und-länderklassen | `architekt` | `offen` | unverändert übernommen, zweiter der Reihe |
| **0118** fünf-weitere-länder | `spielentwerfer` | `offen` | **eine Bedingung berichtigt**, siehe unten |
| **0119** welt-in-drei-schichten | `spielentwerfer` | `offen` | unverändert, **baut sofort** |

Die vier Prüfungen je Vorschlag sind einzeln durchgegangen. **Die Rollenfrage steht
zuerst**, weil an ihr hier schon drei Vorschläge gestorben sind (`builder`,
`geschaeftsfuehrer`, `projektmanager` — Rollen, die kein Runner zieht). Diesmal trägt sie:
`architekt` und `spielentwerfer` stehen beide in `BAUROLLEN` (`agents/baulauf.py:59-60`),
und beide haben denselben Prüfer, den `entwurf-pruefer`.

**0119 ist das einzige der vier, das sofort einen Bauplatz bekommt.** `spiel.md` ist frei
— nachgemessen über `^dateien:` aller 115 Paketdateien: außer 0118, das daran hängt,
beansprucht sie nur 0001, 0021, 0039, 0054 und 0055, und die fünf stehen auf `fertig`.
Es ist zugleich der einzige Zugang zu einem Gewerk, das sonst leer liefe.

### Die eine Berichtigung: 0118 rechnet auf einer Zahl, die es nicht mehr vorfindet

Bedingung 3 von 0118 verlangt, *„wie viele der 45 Plätze ein Spieler über die volle
Partielänge erreichen kann"*. Die 45 sind die Steckplätze bei neun Ländern **aus der
Ländergeometrie allein**. 0118 hängt aber an 0119, und 0119 führt die Börsenplätze ein und
kommt auf **75**. Es sagt das selbst: *„Die Rechnung dazu gehört dorthin und muss beide
Zuwächse tragen, nicht nur die 45 aus den Ländern."*

**Beide Pakete stammen vom selben Tag und demselben Autor; 0119 ist das jüngere und weiß
von diesem hier.** Es ist keine Meinungsverschiedenheit, sondern ein Halbsatz, der beim
Schreiben des zweiten im ersten stehen geblieben ist. Bliebe er stehen, hätte der
Bauagent die Wahl zwischen der Zahl aus seiner Bedingung und der Zahl, die sein
Vorgängerpaket in dieselbe Datei geschrieben hat — beide begründbar, eine davon ein
Rücklauf. **Das ist die Bauart, an der hier dreimal eine erbrachte Leistung durchgefallen
ist.** Die Bedingung heißt jetzt: Deckungsrechnung auf der Steckplatzzahl, die nach 0119
tatsächlich in `spiel.md` steht, gegen die 20 von heute. Der Wortlaut bleibt sonst
unangetastet, die `abnahme`-Zeile im Frontmatter trägt die Einschränkung mit. **Wenn die
45 gemeint waren, sticht eine Zeile des Betreibers diesen Vermerk.**

## Ich habe 0051 vor einem Rücklauf bewahrt, und das war der Preis eines Bauplatzes

**Der Trockenlauf zu Beginn dieses Laufs hätte 0064 gebaut, während 0051 geprüft wird —
beide in `technik.md`.** Das wäre der dritte Fall derselben Falle gewesen.

Die Messung dahinter: `startbereit()` vergleicht die Dateilisten **nur unter Paketen im
Zustand `offen`** (`agents/baulauf.py:293-299`). Ein Paket auf `gebaut` ist unsichtbar,
sein Anspruch auf die Datei zählt nicht mehr. Und die Baustufe läuft vollständig **vor**
der Prüfstufe (`:365` gegen `:377`). Wer in einem Lauf eine Datei anfasst, verändert
damit den Baum, an dem der Prüfer eines fremden, schon gelieferten Pakets unmittelbar
danach misst.

**Bei 0051 trifft das ins Mark.** Seine Bedingung 1 verlangt, dass *„der Prüfer die
Fundstellen vor und nach der Regel zählt"*, seine Bedingung 3 den **Änderungsdiff von
`technik.md`**. Beide Nachweise sind wertlos, sobald ein zweites Paket dieselbe Datei
umschreibt — und 0064 hätte nicht irgendetwas getan, sondern *„einen zweiten Durchgang
über jede Zahl des Dokuments"*. Die denkbar größte Störung. 0051 hat drei Bauläufe
gekostet und trägt bisher null Rückläufe.

**Deshalb baut in diesem Durchgang kein einziges Paket in `technik.md`.** Der Architekt
läuft leer, und das ist meine Entscheidung, nicht ein Zufall der Sortierung. Ein
verlorener Bauplatz gegen einen Rücklauf an einem Paket über acht Dateien ist kein
schwerer Handel. **Daran ist 0027 zweimal schuldlos gescheitert; dies ist das erste Mal,
dass es an dieser Datei vorher gefangen ist.**

## Die neue Reihenfolge in `technik.md` — sieben Pakete, eine Datei

    0051 (gebaut, in Prüfung) → 0116 → 0117 → 0064 → 0068 → 0074 → 0084 → 0092

Jedes Glied trägt seinen Vorgänger jetzt wirklich in `haengt_an`, und in jedem Paket steht,
dass es eine **Reihenfolgesperre und keine fachliche Abhängigkeit** ist. Die letzte
Fassung hat diese Kette behauptet; nachgemessen war sie es nicht — 0074 und 0084 trugen
nur 0026, 0092 gar nichts. Sie funktionierte solange, wie alle Beteiligten `offen` waren,
und wäre in dem Moment gebrochen, in dem der erste auf `gebaut` steht. Genau dieser Moment
war heute.

**Warum die beiden Pakete des Betreibers fünf älteren vorgehen:** Er hat sie am 2026-09-05
selbst geschrieben und selbst eingestellt. Die Vorrangliste in `ops/plan.md` stammt vom
2026-09-04 und ist vollständig abgearbeitet. Vier eigene Pakete an einem Tag sind die
deutlichste Vorrangaussage, die dieser Rückstand kennt. 0116 ist ihr Tor — 0117 hängt
daran, 0118 an 0117 —, und die Vergabe nach kleinster Kennung hätte es als **sechstes**
eingeplant, in rund sechs Durchgängen. Die fünf älteren verlieren zwei Durchgänge; keiner
trägt eine Abhängigkeit eines anderen Pakets, und keiner steht auf dem Weg zu einer Zahl,
nach der jemand gefragt hat.

**Zwei inhaltliche Berührungen sind vorher benannt statt hinterher bezahlt**, je in beiden
betroffenen Paketen:

- **0117 macht die 16 Prüfgegenstände parametrisch, und 0068 verlangt, sie blieben
  „unangetastet".** Das ist kein Widerspruch: 0068 verlangt eine Unterlassung von sich
  selbst, nicht dass die Ziffer 16 wörtlich dasteht. 0117 ist angewiesen, den eingesetzten
  Wert neben der Formel sichtbar zu lassen — was seine eigene Bedingung 2 ohnehin verlangt.
- **0116 schreibt Formeln für 310, 175, 135, 40, 27 und 20, und 0084 fasst die Reihenliste
  an.** Die 27 ist die gemeinsame Stelle. 0084 zieht die Formel mit nach, wenn es die Zahl
  bewegt, und sagt es ausdrücklich, wenn es sie nicht bewegt.

## Die Bauseite läuft halb leer — und der Grund ist nicht die Paketgröße

Der Betriebseintrag zur Anhebung von `GLEICHZEITIG` (4 → 8) sagt: *„Die Bauseite bleibt bei
drei: Sie ist kollisionsbegrenzt … Wer den Bau beschleunigen will, braucht kleiner
geschnittene Pakete, keine größere Zahl hier."* **Die Diagnose stimmt zur Hälfte, und die
Empfehlung daraus folgt nicht.** Nachgezählt an den 22 offenen Paketen, die keinen Platz
bekommen:

| Warum kein Platz | Pakete |
|---|---:|
| wartet auf ein Urteil über ein `gebaut`-Paket (direkt oder über eine Kette) | **22** |
| verliert allein am Dateischnitt, Abhängigkeiten erfüllt | **0** |

**Kein einziges Paket ist heute reiner Kollisionsverlierer.** Auf dem Stand, den ich
vorgefunden habe — vor meinen Ketten und mit den vier Vorschlägen als angenommen
gerechnet —, waren es vier: 0074, 0084, 0092 und 0116, alle vier auf `technik.md`. Die
Bauseite hätte dann **8 statt 4** Pakete geplant, also genau die neue Grenze ausgefüllt.

**Daraus folgt die Empfehlung nicht, die dort steht.** Ein Paket, das `technik.md`
schreibt, in zwei kleinere zu zerlegen, ergibt zwei Pakete auf `technik.md` und weiterhin
einen Platz. Der Engpass ist die **Datei**, nicht der Zuschnitt: sieben offene Pakete auf
einer, die sich in keinem einzigen Absatz überschneiden, und zwölf bis vierzehn Durchgänge
für Arbeit, die an einem laufen könnte. **Ich zerlege `technik.md` nicht; das wäre eine
Entwurfsentscheidung.** Sie steht unten.

## 0061: der angekündigte Auslöser hat gefeuert

Die letzte Fassung hat angekündigt: *Plant eine Baustufe weniger als vier Pakete, geht
0061 im selben Lauf ohne Änderung am Inhalt auf `offen`.* Gemessen um 09:04 und noch
einmal um 09:06, vor jeder Änderung von mir: **„Bau 3 Pakete gleichzeitig"** — 0064, 0094,
0107. Drei ist weniger als vier. **Das Paket steht auf `offen` und ist eingeplant.**

Der Auslöser hing an einer Zahl, die im Kopf jedes Trockenlaufs steht und von meiner
Deutung unabhängig ist — das war der Zweck seiner Neufassung, nachdem der vorige zwei
Läufe lang auf die Wirkung seiner eigenen Ursache gewartet hatte. **Er ist damit auch
verbraucht:** Er misst gegen die Vier von damals, und seit dem Tarifwechsel gibt es acht
Plätze. Als Maß für freie Kapazität taugt er nicht mehr; als einmalige Zusage hat er
gegolten und ist eingelöst.

**Was ich nicht behaupte:** dass die Ursache der drei Leerläufe beseitigt ist. Sie lag
außerhalb dessen, was meine Rolle prüfen kann. Läuft 0061 ein viertes Mal leer, obwohl es
einen Bauplatz hatte, geht es auf `blockiert` zurück — dann mit einer Meldung an den
Geschäftsführer statt einem fünften Versuch. Die Gegenprobe steht im Paket.

## Was der Geschäftsführer entscheiden lassen muss

> **Diese Überschrift trägt weiter eine technische Last** und bleibt deshalb im Wortlaut
> stehen. Der Bauagent von 0090 hat die vier Zitate in `daten/reihen.toml` bereits als
> historisch ausgewiesen und den Commit genannt, der den Wortlaut entfernt hat — aber
> **0090 ist gebaut und nicht abgenommen.** Die Stütze fällt, wenn der Prüfer das
> bestätigt, nicht vorher.

**1. Ein neuer Vorrang, und diesmal weiß ich, wonach ich frage.** Die Liste in
`ops/plan.md` vom 2026-09-04 ist abgearbeitet; die vier Pakete des Betreibers vom
2026-09-05 habe ich als Vorrang behandelt und die Reihenfolge in `technik.md` danach
gestellt. **Das war eine Auslegung, keine Anweisung** — sag, ob sie richtig war. Offen ist
vor allem, was nach 0118 kommt: Fünf Länder auswählen ist ein Entwurf, sie einzubauen ist
ein Kern-, Daten- und Prüfgewerk, das im Rückstand noch mit keinem Paket vertreten ist.

**2. `technik.md` zerlegen — das ist die teuerste offene Frage.** Sieben offene Pakete auf
einer Datei, strikt nacheinander, je zwei Durchgänge. Zwei der sieben gehören dem
Betreiber und sind das Tor zur Ländererweiterung. Solange die Datei eine ist, kostet jedes
weitere Architektenpaket einen ganzen Durchgang, und die Bauseite kann die acht Plätze
nicht ausfüllen. Ich melde es zum dritten Mal und ändere nichts.

**3. `0091` bleibt gesperrt: der T19-Träger fehlt.** Unverändert. `technik.md` T20 verlangt
zur Unterschiedsebene die Ursachenkette, T19 legt den Träger fest — *„die Sitzung sammelt
die Ketten in einem `Verlauf`"* —, und den gibt es nicht. 0091s Dateiliste nennt drei
Dateien, die es nicht gibt; sie kollidiert also mit nichts, und `startbereit()` gäbe dem
Kernbauer sofort einen unbaubaren Auftrag. Es hängt nichts daran.

**4. `0003` bleibt gesperrt, seit dem 2026-09-01.** Einheit im Typ gegen T5s Skalentabelle.
Eine ADR-Entscheidung von dir, gegen T5 oder gar nicht. Hier nur, damit es nicht aus dem
Blick fällt.

**5. `0041` ist erledigt und braucht keine Entscheidung mehr.** Vier Fassungen lang stand
hier, es trage `rolle: geschaeftsfuehrer` und werde nie eingeplant. Der Betrieb hat es am
2026-09-05 selbst abgearbeitet (`d87b9a3`, `78701ac`); es steht auf `fertig`. Damit fällt
der Punkt weg, nicht die Beobachtung dahinter: Eine Rolle außerhalb von `BAUROLLEN` macht
ein Paket unsichtbar, und die Waisenprüfung meldet nur Rollendateien, keine Pakete.

## Was der nächste Lauf zuerst anfasst

1. **Sechs Prüfbefunde auswerten — daran hängt alles andere.** 0051, 0072, 0079, 0087,
   0090, 0097. Wird 0051 `geprueft`, fällt die Sperre für die ganze `technik.md`-Reihe und
   0116 baut. Wird 0090 `geprueft`, fällt die Sperre für 0078 und der Datenbauer hat nach
   zwei leeren Durchgängen wieder Arbeit — und die Überschrift oben wird frei.
2. **0061 nachmessen, und zwar hart.** `git log --since='2026-09-05 09:00' -- pruefstand/`
   und die Zeile `ANKERZAHL` in `pruefstand/test/vorrat_kernanker_probe.cpp`, die heute bei
   4 steht. Kein Commit trotz belegtem Bauplatz heißt `blockiert` und eine Meldung, kein
   fünfter Versuch.
3. **Keinen neuen Auslöser an eine Platzzahl hängen.** Die Vier stammt aus der Zeit der
   vier Plätze. Wer wieder eine Kapazitätszusage geben will, misst gegen `GLEICHZEITIG`,
   nicht gegen eine ausgeschriebene Zahl — dieselbe Regel, die für jede `abnahme` gilt.
4. **Kein Folgepaket zu `werte.hpp` schneiden, bevor 0092 `fertig` ist.** Unverändert:
   Abschnitt 18 nennt drei von sechs Stellen mit „siebzehn" nicht; ein Folgepaket aus dieser
   Liste erbt den Zählfehler. Der Vermerk steht in 0092, das jetzt am Ende der Reihe steht.
5. **Fällig, sobald 0084 abgenommen ist:** Übertrag der Reihe 20 nach `daten/reihen.toml`
   (Datenbauer). 0078 hat sie ausdrücklich herausgehalten. Die Datei trägt dann schon 0090,
   0078, 0099 und 0100; das neue Paket wird fünftes Glied jener Kette.
6. **Befund 3 aus der Prüfung von 0002 lesen, bevor Schritt 6 zugeschnitten wird.**
   `marktkorb(m, k)` ist für T33 Punkt 3 heute nicht aufrufbar. Unverändert aus drei
   Fassungen: Weder der Prüfer noch ich raten, an welcher der zwei Stellen die Heilung liegt.
7. **Nachsehen, ob 0110 einen Platz braucht.** Der Mutationslauf ist das einzige Messgerät,
   das zeigt, ob eine grüne Probe misst oder nur läuft — dreimal von Hand gebaut und
   weggeworfen. Er hängt an 0097, das in diesem Durchgang sein Urteil bekommt.
8. **Nicht noch einmal untersucht werden muss:** `aufgaben/.kopf.tmp` und `.paket.tmp`. Zwei
   versteckte Dateien mit einem Frontmatter, die nach Altlast aussehen. `pakete()` liest nur
   `*.md` (`agents/baulauf.py:235`), sie sind für den Baulauf unsichtbar, und die Kopfzahl
   stimmt ohne sie: 26 + 6 + 79 + 2 = 113, plus je eine `archiviert` und `umgezogen` sind
   die 115 Dateien im Verzeichnis. Hausregel 3 — sie bleiben liegen.
