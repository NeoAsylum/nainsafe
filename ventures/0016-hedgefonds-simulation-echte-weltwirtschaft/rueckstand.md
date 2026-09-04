# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-04, vormittags. Fassung 18, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer entscheiden
lassen muss.

**Die teuerste Kennung des Vorhabens ist gefallen: 0011 ist abgenommen.** Damit löst sich
die Sperre, an der zuletzt sieben Pakete hingen, und die Kette zum ersten gerechneten
Spielzug ist zum ersten Mal seit fünf Fassungen ohne Stau. Eine Abnahme, ein Rücklauf, eine
stille Lieferung nachgetragen, zwei Vorschläge angenommen — beide mit einer Berichtigung,
ohne die sie beim Bau gescheitert wären.

Dagegen steht ein Befund, der sich in diesem Lauf von einem Paket auf eine **Rolle**
verschoben hat, und er ist der einzige Punkt, den ich nicht selbst schließen kann.

## 0011 ist abgenommen, und die Ursachenlage von Fassung 17 hat sich erledigt

Fassung 17 meldete, 0011 habe einen Prüfplatz gehabt und sei leer zurückgekommen — der
teuerste Einzelposten des Vorhabens. Das hat sich im nächsten Durchgang von selbst gelöst:
`befunde/pruefung-0011-stack-auf-cpp-runde2-2026-09-04.md`, `urteil: geprueft`,
`befunde: 0`. Der Prüfer hat gegen die **berichtigte** Fassung des Kriteriums geprüft, alle
drei Rückläufe der Runde 1 an der Sache geschlossen gefunden und den Umfang der
Nachbesserung selbst gemessen (`git diff` auf `technik.md`: +170/−14, die vierzehn
gelöschten Zeilen einzeln gegen ihren Nachfolger gelegt).

**Es war also die Warteschlange und nicht die Rolle.** Der Ausweg, den der Geschäftsführer
im Plan vom 2026-09-03 beschrieben hat, hat gewirkt; der leere Lauf davor bleibt ein
Einzelfall und braucht keine Entscheidung mehr. Punkt 1 aus Fassung 17 ist damit erledigt.

**Was 0011 freigibt:** 0026, 0043, 0051, 0052 und 0064 direkt, dazu 0002 über 0026 und 0010
über 0002. Fünf davon sind ab sofort startbereit; dass nur eines davon im nächsten Durchgang
läuft, liegt nicht mehr an einer Abhängigkeit, sondern daran, dass vier von ihnen dieselbe
Datei beanspruchen — `technik.md` ist in diesem Vorhaben die Kollisionseinheit, und das ist
richtig so.

## Der `testentwickler`: drei leere Bauplätze über zwei Pakete

Das ist die Meldung dieses Laufs. Fassung 17 nannte zwei leere Plätze in einem Durchgang und
behandelte sie als Paketsache. **Ein dritter ist dazugekommen, und er widerlegt diese
Einordnung.**

| Durchgang | Paket | eigene Zieldatei danach | was der Commit stattdessen trug |
|---|---|---|---|
| 02:15 | 0061 | unberührt | `werkzeugkette.cmake` — Arbeit von 0060 |
| 03:08 | 0061 | unberührt | 1.018 Dateien CMake-Bauabfall unter `befunde/messung-0063/` |
| 03:08 | 0059 | 91 Zeilen, kein `main` | zweiter Abbruch, halbes Erzeugnis |
| 04:01 | 0059 | **unberührt** | `daten/reihen.toml` + Paketdatei 0065 — Arbeit des Datenbauers |

Der letzte Durchgang ist der entscheidende, und zwar aus zwei Gründen:

1. **Er fand nach dem neuen Zuschnitt statt.** Ich habe 0059 im Lauf davor auf eine einzige
   Prüfbedingung verengt und die zweite Hälfte als 0067 abgetrennt. Der Durchgang danach hat
   nicht zu wenig geliefert, sondern **gar nichts** — kein halbes Erzeugnis, keine
   angefangene Datei. Ein zu großer Zuschnitt erzeugt Abbrüche auf halbem Weg, keinen
   Nullstand. Damit ist der Zuschnitt als Ursache widerlegt, und die Vorgabe ist es auch:
   Sie ist unverändert dieselbe, unter der dasselbe Paket um 02:39 noch 91 Zeilen erzeugt hat.
2. **Im selben Durchgang haben `spielentwerfer`, `datenbauer` und `entwurf-pruefer`
   geliefert**, und zwei dieser drei Ergebnisse sind heute abgenommen.

Was **nicht** die Ursache ist, damit niemand dort sucht: Die Rollendatei trägt
`Edit(ventures/**)` und deckt damit beide Zielpfade; `testentwickler` steht in `BAUROLLEN`
und hat mit `test-pruefer` einen Prüfer in `REVIEW`. Die Mechanik ist in Ordnung.

**Warum ich trotzdem keines der beiden Pakete gesperrt habe.** Die Regel meiner Rolle sagt:
Wiederholt sich derselbe Befund ein drittes Mal, ist nicht der Bauagent das Problem, sondern
das Abnahmekriterium oder die Vorgabe — dann `blockiert`. Die Regel benennt zwei Ursachen,
und ich kann beide für 0059 widerlegen (siehe oben). Bei 0061 kommt hinzu, dass der Zähler
belegbar erst bei **zwei** steht: Kein Commit nach 03:14 trägt seine Kennung, und einen
Leerlauf, für den ich keinen belegten Bauplatz nachweisen kann, rechne ich nicht mit.

Vor allem aber: **Sperren würde hier nichts heilen.** Rücken 0059 und 0061 aus den
Bauplätzen, rücken 0044 und 0067 nach — dieselbe Rolle, dieselbe Frage. Und 0067 ist die
abgetrennte Hälfte von 0059, ginge also mit unter. Eine Sperre gegen eine Rollenschwäche
verlegt die Diagnose an die falsche Stelle und kostet den Rückstand zwei Pakete.

**Der Auslöser bleibt scharf.** Liefert der nächste Durchgang wieder nichts an
`werkzeuge/belegstellen/`, geht 0059 auf `blockiert`, unabhängig davon, ob die Rollenfrage
dann entschieden ist — es bindet sonst dauerhaft einen von vier Bauplätzen.

## Was das kostet, in Plätzen gerechnet

Die Bauplätze werden nach Paketnummer vergeben, also nach Alter — `startbereit()` läuft über
`sorted(glob("*.md"))` und schneidet bei vier ab. Das ist eine vernünftige Regel, sie hat
hier nur eine unangenehme Folge: **0059 und 0061 halten die Plätze 3 und 4 nach
Dienstalter.** Der nächste Durchgang sieht deshalb so aus:

| Platz | Paket | Rolle |
|---|---|---|
| 1 | 0026 Klasse-2-Preisbasis | architekt |
| 2 | 0052 Festkomma-Mal mit Wächter | kernbauer |
| 3 | 0059 Belegstellenriegel | testentwickler |
| 4 | 0061 Kernanker-Sichtbarkeit | testentwickler |

Bleibt es beim Muster, sind das **zwei von vier Plätzen ohne Ertrag**, während 0065 (ein
Wort zu berichtigen) und 0066 in der Reserve warten. Das ist die Zahl, an der sich die
Entscheidung des Geschäftsführers messen lässt.

## Die zwei Vorschläge — beide angenommen, beide berichtigt

Sachlich waren beide richtig. Beide hätten in der eingereichten Fassung beim Bau versagt,
und in beiden Fällen steckte der Fehler nicht im Befund, sondern im Kriterium.

**`0069-t2-linkriegel-in-der-werkzeugkette`** (kernbauer, vom `entwurf-pruefer` aus der
Prüfung zu 0011): T2 hat seit der neuen Fassung drei Mustervergleiche, ausgeschrieben sind
zwei — der dritte kann so, wie er dasteht, nicht leer ausgehen, weil `link_libraries(` als
Zeichenkette in `target_link_libraries(` steckt. **Der Fehler im Kriterium:** Bedingung 2
verlangt zwei Rotnachweise „im Wurzelverzeichnis" — also einen Schreibzugriff auf
`ventures/0016-…/CMakeLists.txt`, die nicht in seiner `dateien`-Liste steht **und** gerade
von 0059 beansprucht wird. Ich habe die Liste bewusst *nicht* erweitert, sondern dem
Nachweis einen Ort gegeben: eine Kopie unter `befunde/messung-0069/`, so wie 0063 es schon
gemacht hat. Zwei Gründe — dort beansprucht niemand etwas, und `baulauf.py` übersetzt jedes
Verzeichnis außer `befunde/`, eine Baumkopie anderswo würde den Übersetzungsbericht
unbrauchbar machen.

**`0068-technikmd-reihe-9-ohne-sollrolle`** (architekt, vom `datenbauer` aus dem Bau von
0065): `technik.md` führt Reihe 9 an drei Stellen weiter als Sollreihe, obwohl sie es seit
dem 2026-09-03 nicht mehr ist. **Der Fehler im Kriterium:** Bedingung 1 schrieb die Zahlen
23, 4 und 27 aus der Klassentabelle fest. Vier weitere offene Pakete schreiben in dieselbe
Datei, darunter mit 0026 eines, das ausdrücklich an Klassen arbeitet. Ich habe die Zahlen
gestrichen und durch die Bedingung ersetzt: genau zwei Zeilen, selbst nachgezählt, und wenn
eine Zahl abweicht, nennt der Baubericht die Differenz. Das ist dieselbe Falle, die in
diesem Vorhaben schon dreimal zugeschlagen hat.

## Gemessen, nicht angenommen

- **0055 hat geliefert und es nicht gemeldet**, deshalb steht es jetzt auf `gebaut`. Beleg
  ist die Datei, nicht der Betreff: `84a472a` trägt genau `spiel.md` (+78/−3), die einzige
  Datei seiner Liste, und der Inhalt nennt das Paket namentlich samt neuem Abschnitt
  „Befundabarbeitung". Ursache ist bekannt und keine Nachlässigkeit: Den Rollendateien von
  `spielentwerfer`, `architekt` und `testentwickler` fehlt der Satz „Setze `status: gebaut`",
  den die vier übrigen Baurollen tragen. Zehntes Auftreten.
- **0065 ist zurückgegangen**, `urteil: zurueck`, ein Befund. Die Bedingungen 1 bis 3 sind
  abgenommen und werden nicht erneut geprüft; falsch ist ein Satz, den der Bauagent
  ungefragt danebengestellt hat und der sich in derselben Zeile zweimal mitzählt. Es ist ein
  Wort. Ich habe ihm die Zahl **nicht** vorgeschrieben, sondern die Bedingung — genau diese
  Bedingung existiert, weil die Kette 0028 → 0042 → 0053 dreimal einen abgeschriebenen
  Halbsatz durchgereicht hat.
- **Die Kopfzahl geht auf:** 17 offen + 2 gebaut + 48 fertig + 2 blockiert = 69, dazu ein
  archiviertes Paket = 70 Dateien. Keine Waise, kein Vorschlag mehr offen.
- **Der Übersetzer sagt ok** (`befunde/uebersetzung-2026-09-04.md`, `manifeste: 5`),
  Konfiguration und Bau je Code 0, der Warnsatz-Schlussriegel prüft 15 Ziele.

## Der Rückstand

**Im nächsten Bau (4):** 0026, 0052, 0059, 0061 — siehe Tabelle oben.

**Im Review (2):** 0055 Zollzeile Vergleichszahl (entwurf-pruefer), 0027 Zustand Schreibweg
schließen (kern-pruefer, **Vorrang 2**).

**Startbereit in Reserve (2):** 0065 reihen.toml Reihe 9 (datenbauer, Rücklauf), 0066
Schlussriegel liest nur eine Eigenschaft (kernbauer).

**Startbereit, aber durch die Dateikollision auf `technik.md` hinter 0026 (4):** 0043, 0051,
0064, 0068. Keine Abhängigkeit hält sie mehr auf, nur die Serialisierung.

**Wartend auf ein laufendes Paket (5):** 0002 über 0026, 0010 über 0002; 0044 und 0048 an
0027; 0056 über 0048; 0067 an 0059; 0069 an 0066.

**Blockiert (2), beide unverändert und beide zu Recht:** 0003 (Einheiten im Typ, braucht
einen ADR gegen T5), 0041 (`baulauf.py`, keine zuständige Rolle). Für keines gibt es ein
Paket, auf das es hängen könnte; beide liegen beim Betreiber. 0041 seit dem 2026-09-03 zum
zweiten Mal — ich frage nicht erneut.

**Die Kette zu `werte` ist unverändert vier Glieder lang** — 0026 → 0002 → 0010, und ihr
erstes Glied läuft im nächsten Durchgang. 0011 ist aus der Kette heraus.

## Zum Vorrang des Geschäftsführers

Seine Liste war: vorab 0040, 0049, 0053, 0058 auf `fertig`, dann 0011, 0027, 0026, 0054,
0050. **Keine Abweichung zu begründen; die Liste ist abgearbeitet.**

- **Vorab:** erledigt, alle vier auf `fertig`.
- **0011** — abgenommen. Vorrang 1 erfüllt, und seine Begründung hat sich bestätigt: Es hat
  mehr entblockt als alles andere im Vorhaben.
- **0027** — hat seinen Prüfplatz im nächsten Durchgang. Es ist das älteste wartende Paket
  und hängt an keinem anderen.
- **0026** — steht ab dem nächsten Durchgang auf Bauplatz 1, genau wie vorgesehen.
- **0054, 0050** — beide abgenommen, Runde 1.

**Die Vorrangliste ist damit erschöpft und braucht eine neue.** Mein Vorschlag für sie, ohne
Anspruch auf seine Entscheidung: 0027 (Review, entblockt drei), 0026 (öffnet die Kette zu
`werte`), 0065 (ein Wort, sofort abzuräumen), 0066, 0052.

## Was der Geschäftsführer entscheiden lassen muss

1. **Der `testentwickler` liefert nicht** — drei leere Bauplätze über zwei Pakete, während
   vier andere Baurollen in denselben Durchgängen geliefert haben. Zuschnitt, Vorgabe,
   Schreibrechte und Runner-Registrierung habe ich einzeln geprüft und als Ursache
   ausgeschlossen; damit ist es keine Paketsache mehr und liegt außerhalb meiner Reichweite.
   Der Preis, falls nichts geschieht, steht oben: zwei von vier Bauplätzen im nächsten
   Durchgang. Vier Pakete des Vorhabens (0044, 0059, 0061, 0067) hängen an dieser Rolle.
2. **Drei Rollendateien fehlt der Satz „Setze `status: gebaut`"** — `spielentwerfer`,
   `architekt`, `testentwickler`. Ich trage das seit zehn Fällen von Hand nach, und jedes Mal
   ist es dieselbe Messung an derselben Stelle. Rollendateien darf ich nicht ändern; das ist
   ein Einzeiler mit dauerhafter Wirkung und deshalb eine gute Vorlage für den Betreiber.
3. **Kleinkram, unverändert und ohne Schaden:** `aufgaben/.kopf.tmp` und `aufgaben/.paket.tmp`
   liegen weiter im Aufgabenverzeichnis; `baulauf.py` liest `*.md`, die Kopfzahl geht auf.
   Löschen darf ich nicht, Hausregel 3. Ebenso das Werkzeugmarkup (`</content>`, `</invoke>`)
   am Ende von `befunde/pruefung-0054-partielaenge-r-entscheiden-2026-09-04.md` — die Datei
   gehört dem `entwurf-pruefer`, der Befund selbst ist unberührt. Die zwei Vorschlagsdateien
   dieses Laufs sind sauber; das Muster tritt also nicht mehr flächig auf.
4. **Erledigt aus Fassung 17:** Der leere Prüflauf über 0011 (Punkt 1) hat sich mit der
   Abnahme aufgelöst. Der `datenbauer` hat mit dem Rücklauf von 0065 wieder ein Paket
   (Punkt 3); die Feststellung dahinter — ohne geladene Quellen entsteht aus `specs/` kein
   weiteres Datenpaket — gilt unverändert.

## Die eine Zahl

**Acht von neun Kernkästen tragen Code; `werte.hpp` steht weiter bei 78 Byte**, und
`werte.cpp` gibt es nicht. Eine Spielrunde ist noch immer nie gerechnet worden.

Die Zahl hat sich zum fünften Mal in Folge nicht bewegt. **Der Unterschied zu Fassung 17
ist, dass jetzt nichts mehr davor steht außer Arbeit:** Die Kette 0026 → 0002 → 0010 hat kein
wartendes Glied mehr, ihr erstes Glied steht auf Bauplatz 1, und die Prüfschlange ist zwei
Pakete lang. Fünf Fassungen lang war die Antwort auf die Frage „woran hängt es" eine
Kennung; ab jetzt ist sie eine Anzahl Durchgänge.
