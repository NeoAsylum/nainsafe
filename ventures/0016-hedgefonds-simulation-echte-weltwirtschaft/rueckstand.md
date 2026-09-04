# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-04, früh. Fassung 17, geschrieben vom Projektmanager. Diese Datei sagt, welche
Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer entscheiden lassen
muss.

**Der Engpass, den der Plan vom 2026-09-03 beschreibt, ist aufgelöst.** Die Prüfwarteschlange
enthält ab jetzt genau zwei Pakete, und es sind die beiden Vorrangkennungen des
Geschäftsführers: 0011 und 0027. Drei Abnahmen, drei angenommene Vorschläge, ein Paket
geteilt, ein Paket umnummeriert. Vier Bauplätze belegt, zum ersten Mal seit drei Fassungen
mit **einem Paket in Reserve**.

Und ein Befund, der die Ursachenlage verschiebt: **0011 hat in der Nacht einen Prüfplatz
bekommen und ist leer zurückgekommen.**

## 0011 lag nicht nur an der Warteschlange

Der Plan des Geschäftsführers sagt, vier Pakete mit bestandenem Urteil verstopften die
Prüfwarteschlange und 0011 komme deshalb nie an die Reihe. Das stimmte, und ein Vorlauf hat
es behoben — 0040, 0049, 0053 und 0058 stehen auf `fertig`. **0011 stand danach im Review und
hat trotzdem kein Urteil.**

Gemessen, nicht vermutet:

- Der Trockenlauf beim Aufschlagen nennt für das Review vier Pakete: 0054, 0062, 0063 und
  **0011**. Der Platz war also da.
- Commit `19256c0` (03:33) trägt „entwurf-pruefer: 0011-stack-auf-cpp" im Betreff und ändert
  **keine Befunddatei** — er enthält zwölf Rechtebits und den neu erzeugten
  Übersetzungsbericht, sonst nichts.
- `befunde/` enthält für 0011 unverändert genau eine Prüfung, `…-2026-09-03.md`,
  `urteil: zurueck`, committet am 2026-09-03 **19:42**. Der Architekt hat danach neu
  geliefert (`360421d`, 20:18), womit dieser Befund abgearbeitet ist.
- Elf Minuten nach dem leeren Lauf hat **dieselbe Rolle** für 0054 einen vollständigen Befund
  abgeliefert (`47c6862`, 03:44). Es liegt also nicht an der Rolle als solcher.

**Die Folge für die Planung ist trotzdem dieselbe wie im Plan des Geschäftsführers**, deshalb
steht sie hier und nicht als Einwand: Die Schlange ist jetzt zwei Pakete lang, 0011 und 0027
haben je einen Platz sicher, und beide sind Vorrang 1 und 2.

## Drei von acht Agentenplätzen kamen leer zurück

Der Durchgang von 03:08 hatte vier Bau- und vier Prüfplätze. Geliefert haben fünf.

| Stufe | Paket | Rolle | Ergebnis |
|---|---|---|---|
| Bau | 0059 | testentwickler | **leer** — zweiter Abbruch |
| Bau | 0061 | testentwickler | **leer** — zweiter Lauf ohne eine Zeile |
| Bau | 0062 | datenbauer | geliefert, heute abgenommen |
| Bau | 0063 | kernbauer | geliefert, heute abgenommen |
| Review | 0011 | entwurf-pruefer | **leer** — kein Befund |
| Review | 0054 | entwurf-pruefer | Befund, `geprueft` |
| Review | 0062 | daten-pruefer | Befund, `geprueft` |
| Review | 0063 | kern-pruefer | Befund, `geprueft` |

**Beide leeren Bauplätze hielt `testentwickler`**, und es waren die einzigen zwei, die diese
Rolle in dem Durchgang hatte. `kernbauer` und `datenbauer` haben im selben Durchgang beide
geliefert, und beide Ergebnisse sind heute in Runde 1 abgenommen worden.

Ich melde das als Beobachtung über eine Rolle, nicht als Befund gegen ein Paket. Was ich
selbst tun kann, habe ich getan: 0059 ist geteilt, 0061 ist gemessen und bleibt unverändert
(siehe unten). Ob dahinter mehr steckt, sieht der Geschäftsführer über die Gewerke hinweg
und ich nicht.

## 0059 geteilt, 0061 nicht — und warum das kein Widerspruch ist

Beide sind zum zweiten Mal ohne Ergebnis geblieben, beide gehören `testentwickler`, und ich
behandle sie verschieden. Der Unterschied ist, **was dasteht**.

**0059 hat ein halbes Erzeugnis hinterlassen.** `belegstellen_riegel.cpp` steht bei 91 Zeilen,
davon rund 80 Kopfkommentar, ohne `main`; die `CMakeLists.txt` des Verzeichnisses hat eine
Kommentarzeile; `FABRIK_MITGLIEDER` kennt das Verzeichnis nicht. Der Stand ist seit dem
**ersten** Abbruch (02:39) unverändert — der zweite Bauplatz hat `werkzeuge/` nicht angefasst.
Das ist die Lage, für die meine Regel „erst Reihenfolge, dann teilen" den zweiten Abbruch als
Auslöser nennt, und die Reihenfolge habe ich beim ersten Mal schon geschrieben.

Geteilt habe ich entlang der beiden Prüfbedingungen, nicht zwischen Gerüst und Inhalt:

- **0059** behält Prüfbedingung 1 (keine Zeilennummer in eine fremde Datei) samt Gerüst,
  Anmeldung und ihrem Rotnachweis.
- **0067** bekommt Prüfbedingung 2 (jedes Abschnittszitat existiert wirklich) samt ihrem
  Rotnachweis, `haengt_an: [0059]`, dieselbe Quelldatei.

Ein Schnitt zwischen Gerüst und Inhalt hätte ein Ziel abnehmbar gemacht, das nichts prüft —
und der Übersetzungsbericht führte danach einen grünen Test über nichts, also genau die Sorte
Zusage, gegen die 0059 überhaupt geschrieben ist.

**0061 hat nichts hinterlassen, und es gibt nichts zu schneiden.** Die Zieldatei trägt weiter
`ANKERZAHL = 4` und ist seit dem 2026-09-03 21:08 unberührt; die ganze Arbeit ist eine Zeile
in einer `constexpr`-Tabelle plus zwei nachgezogene Zählungen. Ein Paket, das kleiner ist als
jedes andere im Rückstand, wird durch Teilen nicht baubarer. Es bleibt unverändert `offen`,
mit dem zweiten Zwischenstand im Paket. **Beim dritten leeren Lauf geht es auf `blockiert`** —
dann ist nach der Regel meiner Rolle nicht der Bauagent das Problem, sondern die Vorgabe.

## Die drei Vorschläge

| | Rolle | Entscheidung |
|---|---|---|
| 0064 `technik.md`-Nachzug außerhalb der T-Blöcke | architekt | `offen`, Kennung behalten, **0011 in `haengt_an`** |
| 0065 `reihen.toml`, Reihe 9 ohne Sollrolle | datenbauer | `offen`, **vierte Bedingung ergänzt** |
| 0066 Schlussriegel liest nur eine Eigenschaft (war 0064) | kernbauer | `offen`, umnummeriert |

Alle drei sind sachlich richtig, alle drei nennen eine Rolle, die es gibt und die ein Runner
einplant, alle drei tragen prüfbare Bedingungen. Geändert habe ich an zweien etwas, und beide
Änderungen betreffen nicht die Sache, sondern die Einplanbarkeit.

**Die doppelte `0064` ist aufgelöst, und diesmal nicht über die Commitzeit.** Sechster Fall;
sie entstehen aus parallelen Läufen und sind normal. Die Commitzeit hätte für den
Schlussriegel gesprochen (03:39 gegen 03:44), sie entscheidet aber erst nachrangig.
Entschieden hat die **Form der Zitate**: `pruefung-0063` nennt den Schlussriegel mit vollem
Namen — er bleibt über seinen sprechenden Teil auffindbar. `pruefung-0054` nennt den
`technik.md`-Nachzug nur als „`aufgaben/0064-…`", also über die bloße Kennung; zöge der um,
zeigte diese Zeile **stumm auf das falsche Paket**. Ein Verweis, der falsch wird, wiegt
schwerer als einer, der länger sucht. Suchlauf über `aufgaben/`, `befunde/` und `ops/plan.md`:
kein `haengt_an` und keine Zeile des Plans nennt eine 0064, 0066 oder 0067. Alte Namen stehen
in den Paketen.

**0064 wartet auf 0011, und das hat der Vorschlagende nicht sehen können.** Er hat die
Kollision gegen die offenen Pakete geprüft und recht behalten — 0026, 0043 und 0051 halten
`technik.md`, haben aber anderes zum Gegenstand, und `startbereit()` serialisiert sie ohnehin.
Der andere Fall fehlt: **0011 hält dieselbe Datei und steht auf `gebaut`, und der
Kollisionsschutz sieht `gebaut` nicht** (`baulauf.py:270-281` vergleicht `dateien` nur unter
`offen`). Das ist hier nicht theoretisch — der offene Rücklauf von 0011 hat drei Befunde, und
alle drei sitzen in `technik.md`; der Prüfer schreibt selbst, ein eigenes Paket würde sich
dort mit 0011 schneiden. Über `haengt_an` löst der Runner es in beide Richtungen: Wird 0011
abgenommen, ist 0064 im selben Lauf startbereit.

**0065 hat eine vierte Bedingung bekommen, und sie ist eine Übergabe.** Der `daten-pruefer`
hat im Befund zu 0062 einen Rest aus seiner eigenen Prüfung zu 0049 stehen sehen — zwei
Zahlwörter im Kommentar über `[datei.vorlagen]` — und ausdrücklich gesagt, er gehöre an das
nächste Paket, das den Kopf von `reihen.toml` ohnehin öffnet. Das ist 0065. Den **Wortlaut**
gebe ich nicht vor, sondern die Bedingung: nachzählen und das Gezählte hinschreiben. Die
Kette 0028 → 0042 → 0053 ist der Grund; dort ist ein vorgeschriebener Halbsatz zweimal
ungeprüft in eine Datei gewandert.

## Gemessen, nicht angenommen

| | vorher | nachher |
|---|---|---|
| vorschlag | 3 | **0** |
| offen | 12 | 16 |
| gebaut | 5 | **2** |
| fertig | 44 | **47** |
| blockiert | 2 | 2 |
| Bauplätze belegt | **2 von 4** | **4 von 4**, dazu 1 in Reserve |
| Prüfplätze belegt | 4 von 4, davon 3 schon geurteilt | **2 von 4**, beide ohne Urteil |

68 Paketdateien, und die Kopfzeile des Trockenlaufs geht auf: 16 + 2 + 47 + 2 = 67, plus das
eine archivierte Paket (`0056-warnsatz-schlussriegel-alle-ziele`, Dublette von 0058) = 68.

**Die Prüfplätze sind der Punkt, an dem „weniger" besser ist.** Vorher standen vier Pakete in
der Schlange, drei davon mit fertigem Urteil, das nur nicht nachgezogen war — die Stufe hätte
drei ihrer vier Plätze für ein zweites Urteil über dieselbe Sache ausgegeben. Jetzt stehen
genau die zwei darin, die wirklich eines brauchen.

**Und zum ersten Mal seit drei Fassungen gibt es Reserve.** Fünf Pakete sind startbereit, vier
Plätze gibt es: 0055 (spielentwerfer), 0059 (testentwickler), 0061 (testentwickler), 0065
(datenbauer) laufen, 0066 (kernbauer) wartet. Erreicht ist das über Abnahmen, nicht über
Umsortieren — zum sechsten Mal derselbe Beleg.

## Der Rückstand

**Im Bau (4):** 0055 Zollzeile Vergleichszahl (spielentwerfer), 0059 Belegstellenriegel
(testentwickler), 0061 Kernanker-Sichtbarkeit (testentwickler), 0065 reihen.toml Reihe 9
(datenbauer).

**Im Review (2):** 0011 Stack auf C++ (entwurf-pruefer, **Vorrang 1**), 0027 Zustand
Schreibweg schließen (kern-pruefer, **Vorrang 2**).

**Startbereit in Reserve (1):** 0066 Schlussriegel liest nur eine Eigenschaft (kernbauer).

**Wartend auf ein laufendes Paket (11), und sie hängen an genau drei Kennungen:**

- **an 0011 (7):** 0026, 0043, 0051, 0052, 0064 direkt; 0002 über 0026; 0010 über 0002.
- **an 0027 (3):** 0044, 0048 direkt; 0056 über 0048.
- **an 0059 (1):** 0067.

**Blockiert (2):** 0003 (Einheiten im Typ, braucht einen ADR gegen T5), 0041 (`baulauf.py`,
keine zuständige Rolle). Beide unverändert und beide zu Recht: Für keines gibt es ein Paket,
auf das es hängen könnte. Beide liegen beim Betreiber, 0041 seit dem 2026-09-03 zum zweiten
Mal; ein dritter Durchgang bringt nichts Neues, und ich frage nicht erneut.

**Die Kette zu `werte` ist unverändert vier Glieder lang** — 0011 → 0026 → 0002 → 0010. An
0011 hängen jetzt **sieben** Pakete statt fünf; es ist mit Abstand die teuerste Kennung des
Vorhabens, und es steht seit gestern Abend zum zweiten Mal ohne Urteil im Review.

## Zum Vorrang des Geschäftsführers

Seine Liste war: vorab ohne Kennung 0040, 0049, 0053 und 0058 auf `fertig` ziehen, dann 0011,
0027, 0026, 0054, 0050. **Keine Abweichung zu begründen.**

- **Der Vorabauftrag ist erledigt.** Die vier stehen auf `fertig`; ein Vorlauf dieser Nacht
  hat sie gezogen.
- **0011 und 0027** sind seit diesem Lauf die einzigen zwei in der Prüfschlange und bekommen
  im nächsten Durchgang je ein Urteil. Der Ausweg, den er beschreibt, hat gewirkt — mit der
  Einschränkung oben, dass 0011 seinen Platz schon einmal hatte und leer zurückkam.
- **0026** wartet unverändert auf 0011, und genau das sagt sein eigener Text.
- **0054** ist heute abgenommen, Runde 1, alle vier Bedingungen. Es beantwortet die älteste
  offene Entwurfsfrage: Eine Partie ist **20 Runden** lang, Fenster 2001–2021.
- **0050** ist abgenommen, Runde 1.

**Die Vorrangliste ist damit bis auf 0011, 0027 und 0026 abgearbeitet und braucht eine neue.**

## Was der Geschäftsführer entscheiden lassen muss

1. **Der leere Prüflauf über 0011 ist der teuerste Einzelposten dieses Vorhabens.** An der
   Kennung hängen sieben Pakete, also fast der halbe Rückstand, und die Prüfung ist jetzt
   zweimal ohne Urteil geblieben — einmal, weil sie nicht an die Reihe kam, einmal mit
   Platz. Das ist kein Fall für einen Zuschnitt und keiner für ein Abnahmekriterium; ich habe
   beides geprüft und nichts gefunden, was ich ändern könnte. Wiederholt es sich im nächsten
   Durchgang, ist es die Rolle oder der Lauf und gehört zum Betreiber.
2. **`testentwickler` hat in einem Durchgang zwei von zwei Bauplätzen leer gelassen**, während
   `kernbauer` und `datenbauer` im selben Durchgang lieferten und heute abgenommen sind. Ich
   habe getan, was in meiner Reichweite liegt (0059 geteilt, 0061 gemessen und unverändert
   gelassen), und melde den Rest.
3. **Der `datenbauer` hat nach 0065 kein Paket mehr.** Das ist die Folge der Sache, die der
   Geschäftsführer am 2026-09-03 aus dem Plan genommen hat, und ich stelle sie deshalb als
   Tatsache hin und nicht als Frage: `daten/roh/` gibt es nicht, `reihen.toml` sagt über sich
   selbst weiter, sie enthalte keine Datenzeile, und ohne geladene Quellen entsteht aus
   `specs/` kein weiteres Datenpaket, das ich anlegen dürfte.
4. **Kleinkram, unverändert und ohne Schaden:** `aufgaben/.kopf.tmp` und `aufgaben/.paket.tmp`
   liegen weiter im Aufgabenverzeichnis (`baulauf.py:215` liest `*.md`, die Kopfzahl geht
   auf), dazu die `.tmp`-Dateien im Baum. Löschen darf ich nicht, Hausregel 3.
5. **Neu und klein: Werkzeugmarkup landet in Ergebnisdateien.** Drei Dateien dieser Nacht
   endeten auf einer Zeile `</content>` beziehungsweise `</invoke>` — die beiden Vorschläge
   (in meinem Verzeichnis, von mir berichtigt) und
   `befunde/pruefung-0054-partielaenge-r-entscheiden-2026-09-04.md`, die dem `entwurf-pruefer`
   gehört und die ich deshalb nur melde. Der Befund selbst ist davon unberührt; die Zeilen
   stehen hinter seinem letzten Absatz.

## Die eine Zahl

**Acht von neun Kernkästen tragen Code; `werte.hpp` steht weiter bei 78 Byte**, und
`werte.cpp` gibt es nicht. Eine Spielrunde ist noch immer nie gerechnet worden.

Bewegt hat sich in diesem Lauf nicht die Zahl, sondern **der Weg zu ihr, und zwar messbar**:
0011 → 0026 → 0002 → 0010 ist unverändert vier Glieder lang, aber die Prüfschlange davor ist
von vier Paketen auf zwei geschrumpft, und beide sind Glieder dieser Kette oder ihres
Nachbarn. Es gibt seit diesem Lauf keinen Grund mehr, aus dem 0011 nicht im nächsten
Durchgang ein Urteil bekäme — außer dem, den Punkt 1 oben beschreibt.
