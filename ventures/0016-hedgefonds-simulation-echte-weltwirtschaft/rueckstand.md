# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-03, dreizehnter Baulauf. Fassung 12, geschrieben vom Projektmanager. Diese
Datei sagt, welche Pakete es gibt, warum in dieser Reihenfolge, und was der
Geschäftsführer entscheiden lassen muss.

**Der Fund dieses Laufs: der Stau vor der Prüfung war kein Kapazitätsproblem, sondern ein
Nachzugsproblem.** Der Geschäftsführer hat heute 15:10 gemeldet, sieben gebaute Pakete
stünden vor vier Prüfplätzen und der ganze Rückstand hänge dahinter — mit dem Vorschlag,
die Prüfplätze zu erhöhen. Drei der sieben hatten ihr Urteil aber schon; es war nur nicht
eingetragen. **Nach dem Nachzug sind zum ersten Mal seit dem Baubeginn alle vier
Bauplätze und alle vier Prüfplätze belegt** (Trockenlauf 13:11), ohne dass eine Zahl im
Runner geändert wurde.

## Was dieser Lauf getan hat

**Erst der Statusnachzug.** Drei Prüfbefunde lagen vor, alle drei mit Inhalt und alle drei
mit `urteil: geprueft` — `wc -c` selbst gemessen, weil ein beschädigter Befund kein
`urteil` trägt und ein Paket dann jünger aussieht, als es ist.

| Paket | Prüfer | Urteil | Byte | jetzt |
|---|---|---|---:|---|
| 0019 Vorratsverfahren/Profilliste | test-pruefer | `geprueft`, 2 Nebenbefunde | 16.518 | `fertig` |
| 0021 Schaden Gegenkraft 5 | entwurf-pruefer | `geprueft`, 2 Nebenbefunde | 16.368 | `fertig` |
| 0028 Parameterdatei-Querverweis | daten-pruefer | `geprueft`, **0 Befunde** | 7.077 | `fertig` |

Kein Rücklauf. Das ist der erste Nachzug ohne einen einzigen — vorher lag die Quote bei
rund einem Viertel.

**Was dadurch frei wurde:** 0019 entblockt 0029, 0031 und den Vorschlag 0040; 0028
entblockt 0035 und mittelbar 0042; 0021 entblockt 0039 und mittelbar 0043.

**Dann die sechs Vorschläge, alle gesichtet.** Fünf angenommen, einer an den Betreiber
zurückgegeben. Je Vorschlag habe ich die vier Fragen meiner Rollendatei geprüft und die
Antwort in das Paket geschrieben, nicht nur den Status gesetzt.

| Vorschlag | Rolle | Antwort |
|---|---|---|
| 0038 Meldung mit Adresse | kernbauer | `offen` — wartet auf 0033 |
| 0039 Zollzeile Konjunktursockel | spielentwerfer | `offen`, **startbereit** |
| 0040 Kernanker Klassenzuteilung | testentwickler | `offen`, **startbereit** |
| 0041 `baulauf.py` Bauverzeichnisse | *(geschaeftsfuehrer)* | **`blockiert`** — keine Hand, siehe unten |
| 0042 Parameterdatei-Indexbegründung | datenbauer | `offen` — wartet auf 0035 |
| 0043 T48-Größen Gegenkraft 5 | architekt | `offen` — wartet auf 0039 |

**Die Doppelnummern sind aufgelöst**, wie der Geschäftsführer es ohne Kennung verlangt
hat. `0039` und `0040` waren je zweimal vergeben, weil vier Gewerke in derselben Nacht
vorgeschlagen haben und keines die Nummer des anderen sehen konnte. Entschieden hat, wer
zitiert wird: `0039-zollzeile` bleibt, weil `0043` es in `haengt_an` nennt;
`0040-kernanker` bleibt, weil der Prüfbefund zu 0019 es im Wortlaut nennt. Die beiden
anderen sind `0042-parameterdatei-indexbegruendung` und `0043-t48-groessen-gegenkraft-5`.
Auf keines von beiden verwies etwas — die Umbenennung bricht keine Abhängigkeit, und der
alte Name steht in beiden Paketen.

**Eine Abhängigkeit habe ich ergänzt, die kein Vorschlagender sehen konnte:** 0043 hängt
jetzt zusätzlich an 0011. Grund ist keine Sachfrage, sondern `baulauf.py:273` —
`startbereit()` vergleicht die Dateilisten **nur unter `offen`**. Ein Paket auf `gebaut`
hält keinen Anspruch auf seine eigene Datei, und `technik.md` gehört heute 0011, das im
Review steht. Dieselbe Prüfung hatte 0038 für `schritt.cpp` schon selbst gemacht.

## 0041 — der erste Vorschlag ohne zuständige Hand

Der Befund ist richtig: `baulauf.py:116` nimmt beim Suchen nach `CMakeLists.txt` nur
`befunde` aus, nicht `bau` — und `ventures/**/bau/` steht in `.gitignore`. Damit kann ein
Manifest, das in keinem Commit erscheint, zu einem Manifest des offiziellen
Übersetzungsberichts werden. Der Bericht sagt über sich selbst, er sei „das Urteil des
Übersetzers"; dieser Anspruch trägt nur, solange er von versioniertem Text abhängt.

**Bauen kann ihn niemand hier, und das ist nachgemessen und nicht vermutet:**

- `baulauf.py:59-61` führt zehn Rollen, die ein Paket ziehen können. `geschaeftsfuehrer`
  steht in keiner der beiden Mengen; er läuft in Stufe 5 als fester Aufruf ohne Paket.
- Keine der 43 Aufgaben nennt `agents/` in ihrer `dateien`-Liste.
- **Keine einzige Rollendatei unter `agents/rollen/` hat `Edit(agents/**)`** —
  `grep -rn 'Edit(agents' agents/rollen/` ist leer. Der `verbesserer` kommt am nächsten
  und darf ausdrücklich nichts selbst ändern.

Das ist kein Versehen, sondern Absicht: Der Runner ist Werkzeug der Fabrik, nicht
Quelltext des Spiels. **Deshalb `blockiert` und nicht `abgelehnt`** — der Befund ist gut —
**und nicht `offen`**, denn ein `offen`, das kein Lauf je zieht, ist eine Lüge im
Statusfeld. Er geht als Betreiberaufgabe weiter: eine Zeile, dazu der Neustart des
Tageslaufs, weil eine Änderung am laufenden Runner nichts ändert (`lehren.md`,
2026-09-02).

**Zwei Zeilen Aufräumarbeit gehören dazu und haben dieselbe fehlende Hand.** Der
test-pruefer hat unter `pruefstand/bau/pruefung-0019/` seinen Mutationsstand liegen
lassen — gitignoriert, berührt keine Paketdatei, und **ab dem nächsten Baulauf das vierte
Manifest im Bericht**. Er hat das Löschen versucht und den abgelehnten Aufruf im Wortlaut
in seinen Befund geschrieben. Das ist die richtige Reaktion und die einzige, die ihm
offenstand.

## Das eine, was in der letzten Nacht nicht geschehen ist

**0011 stand auf Platz 1 der Prüfwarteschlange und hat keinen Befund bekommen.** Es ist
seit dem 2026-09-02, 20:05 `gebaut`; es gibt keine Datei `pruefung-0011-*.md`, und der
Trockenlauf setzt es weiter auf Platz 1. Es ist der einzige der vier eingeplanten
Prüfläufe des letzten Durchgangs, der nichts hinterlassen hat — die anderen drei sind die
Tabelle oben.

Das trifft die Kette, an der alles hängt: **0011 → 0026 → 0002 → 0010**, also der letzte
leere Kernkasten `werte`. Es ist zugleich Vorrang 1 des Geschäftsführers.

**Was ich sehe, ohne es beweisen zu können:** In derselben Prüfphase liefen **zwei**
`entwurf-pruefer` gleichzeitig — einer auf 0011, einer auf 0021. Beide schreiben dieselbe
Logbuchdatei `notizen/entwurf-pruefer.md`, und beide committen. Der Commit `6e4486f` zeigt
die Nebenwirkung im Kleinen: Er trägt den Betreff des einen Prüfers und **sieben**
Dateien, darunter den Befund und zwei Vorschläge des *anderen*. Nur einer der beiden
Prüfer hat einen Befund hinterlassen.

**Das ist eine Vermutung, und ich schreibe sie als solche hin** — eine Fehlermeldung, die
gründlich aussieht, ist kein Beleg (`lehren.md`, 2026-09-02). Aber sie ist billig prüfbar,
und der nächste Lauf prüft sie von allein: **0021 ist jetzt `fertig` und verlässt die
Warteschlange. 0011 ist damit der einzige `entwurf-pruefer` im nächsten Durchgang —
dafür laufen zwei `kern-pruefer` gleichzeitig (0033 und 0027).** Bekommt 0011 diesmal
einen Befund und fehlt statt dessen einer der beiden Kernbefunde, ist die Vermutung
bestätigt. Bleiben alle vier vollständig, ist sie widerlegt.

## Wo die Pakete stehen

43 Pakete. Der Trockenlauf zählt **12 offen, 4 gebaut, 24 fertig, 3 blockiert** — Summe
43, also geht kein Frontmatter daneben.

**Vier Bauplätze, alle belegt:**

| Rolle | Paket |
|---|---|
| testentwickler | 0029 Vorratsverfahren, Invariante |
| kernbauer | 0031 Warnsatz in die Werkzeugkette |
| datenbauer | 0034 Belegstellen ohne Zeilennummern |
| datenbauer | 0035 Parameterdatei-Belegstellen |

**Vier Reviewplätze, alle belegt:** 0011 (entwurf-pruefer), 0032 (daten-pruefer), 0033 und
0027 (kern-pruefer). Reihenfolge ist die Zahl der bisherigen Urteile, deshalb steht 0027
mit seinem einen Rücklauf hinten.

**In Reserve, startbereit, ohne Platz:** 0039 (spielentwerfer) und 0040 (testentwickler).
Zum ersten Mal überhaupt gibt es mehr startbereite Pakete als Plätze — die Bauagenten
laufen nicht mehr leer, und das war die härteste Auflage meiner Rollendatei.

**Wartend auf ein laufendes Paket:** 0026 (an 0011), 0036 (an 0032), 0038 (an 0033), 0042
(an 0035), 0043 (an 0039), 0010 (an 0002, blockiert).

**Blockiert, alle drei zu Recht:** 0002 (`kern::werte`, wartet auf die
Klasse-2-Entscheidung), 0003 (Einheiten im Typ, braucht einen ADR gegen T5, den nur der
Betreiber erlässt) und neu 0041 (siehe oben).

## Zum Vorrang des Geschäftsführers

Seine fünf Kennungen waren 0011, 0026, 0019, 0028, 0034 — dazu die Auflage ohne Kennung.
**Ich bin ihm vollständig gefolgt; drei sind erledigt, zwei liegen außerhalb meiner
Reichweite.**

| | Stand | warum |
|---|---|---|
| 1. 0011 | **im Review, Platz 1** | ich kann kein Urteil erzeugen, nur den Platz freihalten — siehe oben |
| 2. 0026 | wartet | hängt an 0011, unverändert |
| 3. 0019 | **`fertig`** | Urteil nachgezogen, entblockt 0029, 0031, 0040 |
| 4. 0028 | **`fertig`** | Urteil nachgezogen, entblockt 0035 und 0042 |
| 5. 0034 | **im Bau** | war das einzige startbereite Paket, ist es nicht mehr |
| ohne Kennung | **erledigt** | Doppelnummern aufgelöst, 0041 zurückgegeben |

**Die vier Bauplätze gingen an 0029, 0031, 0034 und 0035.** Nur 0034 steht auf der
Vorrangliste, und das ist keine Abweichung: Von den fünf Kennungen ist nur 0034 überhaupt
ein Baupaket. Die anderen drei Plätze hat der Nachzug erst erzeugt — 0029 und 0031 hängen
an 0019, 0035 an 0028.

## Was der Geschäftsführer entscheiden lassen muss

**Erstens: die Prüfplätze nicht erhöhen — noch nicht.** Sein Vorschlag steht, meine
Messung widerspricht ihm heute. Der Stau vor der Prüfung war zu 3/7 ein fehlender Nachzug,
und der ist jetzt gemacht; danach sind Bau und Prüfung gleich voll. Eine Erhöhung würde
gerade jetzt Prüfer auf Pakete setzen, die es noch gar nicht gibt. **Seine eigene
Bedingung — eine Nacht mit der neuen Rücklaufgrenze abwarten — ist erst zur Hälfte
eingelöst**, und die eine Nacht, die lief, hatte null Rückläufe. Das spricht für Abwarten,
nicht gegen ihn. *Wenn wir uns hier ein zweites Mal widersprechen, gehört es in seinen
Bericht statt in eine dritte Runde.*

**Zweitens, unverändert seit vier Plänen: die Rohdaten.** `daten/` enthält weiter keine
Datenzeile. Ich habe dazu nichts hinzuzufügen und schließe mich seiner Empfehlung B an
(der Betreiber lädt die vier Quellen einmal von Hand). **Eine Zahl gehört aber richtig
gestellt, weil sie die Dringlichkeit trägt:** Von den zwölf offenen Paketen sind heute
**vier** Datenbau (0034, 0035, 0036, 0042), nicht mehr die Mehrheit — und alle vier
arbeiten an Belegstellen und Begründungen in Textdateien, keines an Datenzeilen. Der
Trade läuft also nicht länger ins Leere, aber er läuft aus: Nach 0042 hat der Datenbauer
ohne geladene Quellen nichts mehr zu tun.

**Drittens: 0041 braucht eine Hand.** Eine Zeile in `agents/baulauf.py` plus Neustart des
Tageslaufs, dazu ein `rm -rf` auf `pruefstand/bau/pruefung-0019/`. Beides steht im
Wortlaut im Paket. Solange es liegen bleibt, ist der Übersetzungsbericht ab dem nächsten
Lauf um ein Manifest falsch.

**Nicht mehr auf dieser Liste: die drei Rollendateien.** Der Punkt aus Fassung 11
(`architekt`, `spielentwerfer` und `testentwickler` fehlt der Satz „Setze `status:
gebaut`") ist heute nicht aufgetreten — alle drei Gewerke haben in der letzten Nacht
entweder nicht gebaut oder korrekt gemeldet. **Er ist damit nicht erledigt, sondern nur
nicht fällig**; die drei Sätze fehlen weiter, und beim nächsten Lauf dieser Rollen kommt
er wieder. Ich halte ihn hier klein, statt ihn zum dritten Mal groß zu schreiben.

## Was quer liegt, aber keine Entscheidung braucht

**Der Scheduler hat weiter keine Vorfahrt**, und diesmal hat es zum ersten Mal keinen
Schaden angerichtet: Von sechs startbereiten Paketen kamen die ersten vier nach
Dateinamen dran, und die beiden übrigen (0039, 0040) sind Reserve statt Verlust. Der
Befund aus Fassung 11 gilt weiter — der Scheduler braucht keine Vorfahrt, solange der
Statusnachzug stimmt. Ein Vorschlag bleibt aus.

**Drei Pakete arbeiten gleichzeitig im Kasten `pruefstand`, und das ist geprüft.** 0029
legt zwei neue Quellen an, 0040 eine neue Probe, 0031 schreibt das Manifest. Sie
kollidieren nicht, weil die `CMakeLists.txt` aus 0019 mit
`file(GLOB … CONFIGURE_DEPENDS)` sammelt — niemand muss das Manifest anfassen, um eine
Datei hinzuzufügen. **Das ist der Kastenschnitt, der den Kollisionsschutz überhaupt
tragfähig macht**, und er zahlt sich hier zum ersten Mal in drei parallelen Paketen aus.

**`parameter.toml` ist die engste Stelle des Vorhabens:** vier Pakete nacheinander an
derselben Datei (0009 → 0028 → 0035 → 0042), keine zwei gleichzeitig. Das ist kein
Zuschnittfehler, sondern der Preis dafür, dass die Datei die Kollisionseinheit ist. Wer
sie teilen wollte, müsste die Datei teilen.

**Fünf Rollen haben kein Paket, und das ist weiter richtig.** `oberflaechenbauer` steht in
T13 als letzter Kasten; `auslieferer` hat nichts auszuliefern; die drei Prüfrollen
(`selbstspieler`, `rueckvergleicher`, `bruchtester`) brauchen eine gespielte Partie.
Allen fünf fehlt eine Voraussetzung nachweisbar.

## Die eine Zahl

**Acht von neun Kernkästen tragen Code, und der neunte hat weiter kein Paket im Bau.**
`werte` (78 Byte) hängt an 0002, 0002 an 0026, 0026 an dem Urteil zu 0011 — vier Glieder,
und das erste ist der eine Prüflauf des letzten Durchgangs, der leer zurückkam. **Wenn
dieser Plan eine Zahl hat, dann diese: ein fehlendes Urteil, viermal weitergereicht.**

Eine Spielrunde ist noch immer nie gerechnet worden. Der Nachweis, dass sich das ändert,
bleibt derselbe und kann von keinem Agenten erfunden werden: 175 Ursachensätze und eine
FNV-1a-64-Prüfsumme, die sich nicht bewegt hat.
