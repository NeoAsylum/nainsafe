# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-03, abends. Fassung 15, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer entscheiden
lassen muss.

**Der Lauf davor hatte die Vorschlagsliste leergeräumt; sie war beim Aufschlagen wieder
voll.** Fünf Vorschläge, vier Prüfbefunde, zwei Lieferungen ohne Meldung — und **drei
Pakete mit derselben Kennung `0049`**, angelegt von drei Agenten, die einander nicht sehen
konnten.

## Was dieser Lauf getan hat

**Vier Abnahmen.** 0029 (Vorratsverfahren-Invariante), 0034 (Belegstellen ohne
Zeilennummern), 0035 (Parameterdatei-Belegstellen) und 0036 (reihen.toml BACI-Einheit)
stehen auf `fertig`, jedes mit `urteil: geprueft`, jedes in Runde 1. Vier Bauplätze, vier
Prüfplätze, vier Urteile, kein Rücklauf — die beste Nacht des Vorhabens bisher.

**Zwei Übergänge, die ich selbst getragen habe.** 0011 und 0039 haben geliefert und konnten
es nicht melden. Dazu unten.

**Fünf Vorschläge, fünf Annahmen.** Keiner war abzulehnen. Einer ist mit einer geschärften
Bedingung angenommen, einer hinter einen anderen gehängt, zwei umnummeriert.

**Ein neues Paket aus `specs/`,** 0052, weil der Architekt beim Schliessen seines Rücklaufs
eine Vorgabe eingeführt hat, der die Umsetzung fehlt.

## 0011 und 0039 — geliefert, konnten es nicht melden

Sechster und siebter Fall derselben Sorte: `architekt`, `spielentwerfer` und
`testentwickler` fehlt in ihrer Rollendatei der Satz „Setze `status: gebaut`", den die vier
anderen Baurollen tragen. Ihre Pakete blieben `offen` und hätten in der nächsten Nacht zwei
Bauplätze für Arbeit belegt, die schon getan ist — und hätten kein Urteil bekommen, denn
der Prüfplatz hängt an `gebaut`.

**Gemessen an der Zieldatei, nicht am Commit-Betreff.** 0011 hat alle drei Rücklaufpunkte in
`technik.md` geschlossen (`__builtin_mul_overflow` → Z. 576, `cargo vendor` → Z. 210-220,
T2-Erzwingung → Z. 154-165 und Z. 839-844; +184 Zeilen). 0039 hat Weg 1 gewählt, die beiden
anderen mit Grund verworfen und die Lesezahl an vier Stellen auf dieselbe Zahl gebracht.
Was ich **nicht** behaupte, steht in beiden Paketen: ob die Arbeit richtig ist. Das
entscheidet der `entwurf-pruefer`.

**Der Betreff hätte hier zum ersten Mal in die Irre geführt.** Commit `360421d` trägt den
Betreff „architekt: 0011-stack-auf-cpp" und darin +459 Zeilen `spiel.md` — eine Datei, die
nicht in der `dateien`-Liste von 0011 steht. Das ist kein Regelbruch des Architekten: Die
Zeilen sind die Arbeit des Spielentwerfers an 0039, nachweisbar an der Kopfzeile
*„Geändert am 2026-09-03 aus Arbeitspaket `0039-zollzeile-konjunktursockel`"*, die in genau
diesem Diff steht. Zwei Agenten liefen parallel; der Runner committet, was im Baum liegt.

## Die fünf Vorschläge

| | Rolle | Entscheidung |
|---|---|---|
| 0047 reihen.toml Kopf/Widerspruch | datenbauer | `offen`, **Bedingung 3 geschärft** |
| 0048 Meldung in `zustand.cpp` nachziehen | kernbauer | `offen`, und **0038 dafür berichtigt** |
| 0049 reihen.toml Herkunft/Selbstprüfung | datenbauer | `offen`, **hinter 0047 gehängt** |
| 0050 Vorratsprobe Belegstellen (war 0049) | testentwickler | `offen`, umnummeriert |
| 0051 T46 Gebietspräfix (war 0049) | architekt | `offen`, umnummeriert |

**Die dreifache `0049` ist aufgelöst.** Kein `haengt_an` und kein Eintrag in `ops/plan.md`
zitierte eine der drei, also war keine Kennung gebunden und die Anlagezeit entschied:
`142e956` (20:36) trägt zwei, `27d1429` (20:37) die dritte, die deshalb weicht. Zwischen
den beiden gleichzeitigen hat der Vorschlagende von 0050 selbst darum gebeten, und darauf
hingewiesen, dass `mv` in seiner Sitzung gesperrt war. Alter Name steht in jedem Paket.

**0047 und 0049 wollen dieselbe Datei, und ich habe sie nicht zusammengelegt.** 0049 bietet
das ausdrücklich an, 0047 begründet, warum zwei Läufe auf `reihen.toml` schlechter sind als
einer: Jeder verschiebt die Zeilennummern des nächsten. Der Einwand stimmt — aber
zusammengelegt hätte das Paket **acht** Bedingungen über eine Datei mit rund 1.600 Zeilen,
und das ist der Zuschnitt, an dem 0019 dreimal abgebrochen ist. Die Lehre daraus heisst
teilen, und besser vor dem ersten Abbruch als nach dem zweiten.

Der Einwand ist stattdessen **an der Wurzel behoben**: Bedingung 3 von 0047 liess neben der
Ersetzung durch „Adresse plus Zitat" auch ein blosses Nachmessen der Zeilennummern zu — und
widersprach damit ihrem eigenen Auftragstext, der die Ersetzung ausdrücklich vorschlägt.
Der Schlupfweg ist weg. Danach gibt es in `[pruefweg]` keine Zeilennummer mehr, die 0049
verschieben könnte. Dieselbe Fehlerklasse wie in 0011 am 2026-09-02: *Verlangt der
Fliesstext etwas, das mein Nachweis erlaubt zu unterlassen?*

## 0038 — ein Kriterium, das seine eigene Datei nicht anfassen durfte

Das ist der Befund dieses Laufs, den ich am wenigsten gerne schreibe, weil er mir gehört.

Bedingung 1 von 0038 verlangte einen Mustervergleich über **ganz** `kern/src/`. Aus
`kern/src/` stehen in seiner `dateien`-Liste aber nur `schreiber.cpp` und `schritt.cpp`;
`kern/src/zustand.cpp` gehört Paket 0027 und trägt seit 0037 eine zweite Klasse `Meldung`.
Der Kernbauer hat das beim Bauen gefunden, belegt (`grep -rn "class Meldung"` → zwei
Zeilen), nichts angefasst und einen Vorschlag danebengelegt. Genau so ist es gedacht.

Ohne Eingriff wäre die nächste Prüfung ein **Rücklauf gegen Arbeit, die das Paket nicht tun
durfte**. Bedingung 1 ist deshalb auf die eigenen Dateien verengt, mit Begründung im Paket
und einem Satz an den Prüfer. **Abgesenkt ist dabei nichts:** Paket 0048 trägt als
Bedingung 1 wörtlich, dass `grep -rn "class Meldung" kern/include kern/src` danach genau
eine Zeile liefert. Der Anspruch ist an die Stelle gehängt, die ihn einlösen darf.

Die Deadlock-Prüfung dazu ist gelaufen: 0048 hängt an 0038 und 0027, und beide können ohne
0048 abgenommen werden — nach der Berichtigung, und nur nach ihr.

## Gemessen, nicht angenommen

| | vorher | nachher |
|---|---|---|
| vorschlag | 5 | **0** |
| offen | 11 | 15 |
| gebaut | 6 | 4 |
| fertig | 27 | **31** |
| blockiert | 2 | 2 |
| Bauplätze belegt | 4 von 4 | 4 von 4 |
| Prüfplätze belegt | 4 von 4 | **4 von 4, alle vier Wartenden** |

52 Paketdateien, und die Kopfzeile des Trockenlaufs geht auf. Sechs Pakete sind startbereit
auf vier Plätze; zwei stehen in Reserve, auch wenn ein Bauagent scheitert.

**Der Prüfstau ist weg, und zwar ohne Zutun.** Vorige Nacht warteten 0027 und 0038 hinter
vier anderen — `reviewbereit()` sortiert nach der Zahl bisheriger Urteile und schneidet bei
vier ab (`baulauf.py:311`). Mit den vier Abnahmen sind beide nachgerückt. Das ist der
dritte Beleg für dieselbe Sache: **Freie Plätze entstehen durch abgenommene Pakete, nicht
durch Umsortieren.**

## Der Rückstand

**Im Bau (4):** 0040 Kernanker-Klassenzuteilung (testentwickler), 0042
Parameterdatei-Indexbegründung (datenbauer), 0045 Zwischenstände räumen (datenbauer), 0046
Warnsatzriegel (kernbauer).

**Im Review (4):** 0011 Stack auf C++ (entwurf-pruefer, **Vorrang 1**), 0027
Zustand-Schreibweg (kern-pruefer), 0038 Meldung mit Adresse (kern-pruefer), 0039 Zollzeile
Konjunktursockel (entwurf-pruefer).

**Startbereit in Reserve (2):** 0047 reihen.toml Kopf/Widerspruch (datenbauer), 0050
Vorratsprobe Belegstellen (testentwickler).

**Wartend auf ein laufendes Paket (9):** 0026 (an 0011), 0002 (an 0026), 0010 (an 0002),
0043 (an 0011 und 0039), 0044 (an 0027), 0048 (an 0038 und 0027), 0049 (an 0047), 0051 (an
0011), 0052 (an 0011).

**Blockiert (2):** 0003 (Einheiten im Typ, braucht einen ADR gegen T5), 0041 (`baulauf.py`,
keine zuständige Rolle). Beide zu Recht: Für keines gibt es ein Paket, auf das es hängen
könnte — die Prüffrage ist in diesem Lauf für beide wiederholt worden.

**Die Kette zu `werte` ist unverändert vier Glieder lang** — 0011 → 0026 → 0002 → 0010 —,
aber ihr erstes Glied steht zum zweiten Mal im Review, und diesmal mit allen drei
Rücklaufpunkten geschlossen. An 0011 hängen inzwischen **fünf** Pakete (0026, 0043, 0051,
0052 und über 0026 auch 0002). Es ist die einzige Kennung des Vorhabens, an der so viel
hängt.

## Zum Vorrang des Geschäftsführers

Seine fünf Kennungen waren 0011, 0026, 0019, 0028, 0034. **Ich bin ihm gefolgt, und die
Liste ist damit abgearbeitet:** 0019 und 0028 waren schon `fertig`, 0034 ist es jetzt, 0011
steht im Review, und 0026 wartet unverändert auf 0011 — das ist der Inhalt seines Punktes 2
und keine Abweichung.

**Keine Abweichung zu begründen.** Die vier Bauplätze dieser Nacht gehen an Pakete, die er
nicht genannt hat, weil von seinen fünf keines startbereit ist: vier sind fertig oder im
Review, das fünfte wartet auf das vierte.

**Seinen Auftrag ohne Kennung habe ich erledigt.** Die doppelten Nummern sind aufgelöst —
diesmal waren es drei statt zwei —, und 0041 geht mit diesem Lauf zum zweiten Mal an den
Betreiber zurück, jetzt mit einem eingetretenen statt einem erwarteten Schaden.

## Was der Geschäftsführer entscheiden lassen muss

1. **0041 ist keine Vorsorge mehr, sondern ein Fehlbericht.** Der Übersetzungsbericht des
   Tages (`befunde/uebersetzung-2026-09-03.md`) trägt `manifeste: 4`. Versioniert sind für
   den Bau **drei**; das vierte ist `pruefstand/bau/pruefung-0019/CMakeLists.txt`, in keinem
   Commit, im Bericht aber namentlich (Z. 163 und 185). Der Bericht sagt über sich selbst,
   er sei „das Urteil des Übersetzers" — dieser Anspruch trägt nur, solange er an
   versioniertem Quelltext hängt. Nötig sind eine Zeile in `agents/baulauf.py`, ein Neustart
   des Tageslaufs und ein `rm -rf` auf das Verzeichnis; der Wortlaut steht im Paket. **Es
   gibt weiterhin keinen Weg über ein Gewerk** — in diesem Lauf erneut nachgesehen:
   `geschaeftsfuehrer` steht weder in `BAUROLLEN` noch in `PRUEFROLLEN` (`baulauf.py:59-61`),
   und keine Rollendatei trägt `Edit(agents/**)`.
2. **Die Rohdaten, und die Frist ist jetzt abgelaufen.** `daten/` enthält weiter keine
   Datenzeile — sechs Dateien, davon fünf Befunde und ein Katalog. Nach 0042, 0045, 0047 und
   0049 hat der Datenbauer ohne geladene Quellen **nichts mehr zu tun**; das sind vier
   Pakete, also etwa eine Nacht bei zwei Datenbauplätzen. Unverändert Empfehlung B: Der
   Betreiber lädt die vier Quellen einmal von Hand.
3. **Den drei Rollendateien fehlt der Satz „Setze `status: gebaut`".** Sechster und siebter
   Fall in diesem Lauf, beide von Hand getragen. Er kostet keinen Bauplatz mehr, seit ich
   ihn jeden Lauf prüfe — aber er kostet jeden Lauf diese Prüfung, und er hat in diesem Lauf
   fast dazu geführt, dass 0011 als „nicht geliefert" gezählt worden wäre.

## Die eine Zahl

**Acht von neun Kernkästen tragen Code; `werte.hpp` steht weiter bei 78 Byte**, und
`werte.cpp` gibt es nicht.

Eine Spielrunde ist noch immer nie gerechnet worden. Was sich diese Nacht bewegt hat, ist
nicht die Zahl, sondern der Weg zu ihr: 0011 hat seine drei Befunde geschlossen und steht
im Review. Wenn es durchgeht, ist zum ersten Mal seit dem Stackwechsel keine Vorgabe mehr
zwischen der Fabrik und `kern::werte`.
