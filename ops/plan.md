# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-03 15:10. Erster Bericht nach der Umstellung auf **einmal je Nacht**
(Betreiber, 2026-09-02 19:46). Abgedeckt: 2026-09-02 19:33 bis 2026-09-03 14:54.

## Wo das Vorhaben steht

**Der Kern rechnet eine Runde:** `schritt.cpp` trägt 26.697 Byte und `schritt_probe` läuft
grün — von neun Kernkästen ist nur noch `werte.hpp` (78 Byte) ein Platzhalter. **Die
Vorgabe ist eingeholt** — der Architekt hat 0011 am 2026-09-02 20:05 geliefert, `technik.md`
schreibt C++20 vor und nennt Rust nur noch als verworfene Alternative; die Divergenz, die
ich sechs Pläne lang gemeldet habe, ist erledigt. **Aus 32 Paketen sind 43 geworden** (21
fertig, 7 gebaut, 7 offen, 2 blockiert, 6 Vorschläge), und der Rückstand wächst schneller,
als er abgearbeitet wird.

## Der Engpass

**Die Prüfung. Sieben gebaute Pakete stehen vor vier Prüfplätzen** (`GLEICHZEITIG = 4`,
`agents/baulauf.py:80`), und der ganze übrige Rückstand hängt hinter ihnen.

Der Trockenlauf des nächsten Durchgangs (heute 12:57) zeigt es unmittelbar:
**vier von vier Prüfplätzen belegt, einer von vier Bauplätzen.** Drei Bauagenten haben
nichts zu tun. Sechs der sieben offenen Pakete hängen an einem Paket, das `gebaut` ist und
auf sein Urteil wartet — und **fünf der sechs Vorschläge ebenso.** Der komplette Rückstand
ist auf eine einzige Warteschlange zusammengelaufen.

Das ist zugleich die teuerste Stelle. `einrichtung/bauleistung.py` (heute gerechnet, seit
2026-09-01 15:00): 113 Läufe, 604,60 $, davon **40 % Prüfung**. Der `daten-pruefer` allein
kostet 135,60 $ in 24 Läufen — mehr als jeder Bauagent.

## Was quer liegt

- **Vier Vorschläge, zwei Nummern.** `0039` und `0040` gibt es je zweimal
  (`0039-parameterdatei-indexbegruendung` / `0039-zollzeile-konjunktursockel`,
  `0040-kernanker-klassenzuteilung` / `0040-t48-groessen-gegenkraft-5`). Die
  `haengt_an`-Verweise tragen, weil sie den vollen Namen nennen; meine Vorrangliste und
  jede mündliche Rede über „0039" trägt nicht mehr. Vier Gewerke haben gleichzeitig
  vorgeschlagen und keines konnte die Nummer des anderen sehen.
- **Die Kette zum letzten Kernkasten hängt ganz am Urteil zu 0011:** 0011 (Prüfung) → 0026
  (Klasse-2-Preisbasis) → 0002 (`werte`) → 0010. 0002 ist ausdrücklich *nicht* wegen eines
  Fehlers blockiert, sondern weil seine Vorgabe an der Stelle in Revision ist, die es
  abschreiben soll.
- **Vorschlag 0041 kann von keinem Gewerk gebaut werden.** Er ändert `agents/baulauf.py`
  (Zeile 116 findet `CMakeLists.txt` in ignorierten `bau/`-Verzeichnissen — damit hängt der
  Übersetzungsbericht an unversioniertem Text). Keine der 43 Aufgaben darf `agents/`
  schreiben. Siebter Fall der vom Betreiber benannten Fehlerklasse, und der erste ohne
  zuständige Hand.
- **Die Nacht vom 2026-09-02 steht in keinem Betriebslog** — `ops/nachtlauf.log` endet
  08:17, die elf Läufe von 19:33 bis 21:23 sind nur über `git log` rekonstruierbar.
  Unverändert: 18 `.tmp`-Dateien im Repo.

## Was der Betreiber entscheiden muss

**Die Rohdaten — zum zweiten Mal, mit der Zahl, die mir beim ersten Mal fehlte.**
`…/daten/` enthält nach elf Bauläufen fünf Textbefunde und `reihen.toml`. Die Datei sagt
über sich selbst: *„Sie enthaelt keine Datenzeile."* Das stimmt für das ganze Verzeichnis.

Was das gekostet hat: `datenbauer` 93,30 $ und `daten-pruefer` 135,60 $ — zusammen
**228,90 $, also 38 % der gesamten Bauphase, für Arbeit über Daten, die niemand geladen
hat.** Die Arbeit ist nicht verschwendet — Lizenz-, Deckungs- und Einheitenbefunde
mussten vor dem Laden entstehen. Aber das Gewerk kann von allein nicht aufhören: Vier der
sieben offenen und zwei der sechs vorgeschlagenen Pakete sind wieder Datenbau, und der
nächste Schritt braucht eine Hand, die herunterlädt. Kein Gate — `daten.md` nennt für alle
vier tragenden Quellen ausdrücklich keine Registrierung und kein Abonnement.

- **A — der Runner bekommt einen Ladeschritt.** Einmal Arbeit, danach hat jeder Datenbauer
  echte Zeilen.
- **B — der Betreiber lädt die vier Quellen einmal von Hand** nach `…/daten/roh/`.

**Weiter Empfehlung B**, eine Viertelstunde: Sie beantwortet die Frage, die A voraussetzt
— ob die Quellen so aussehen, wie `daten.md` sie beschreibt. *Der Betreiber hat meinen
Output vom 2026-09-02 gelesen und darauf geantwortet (`45041d7`, 19:46) — aber auf die
Berichtstaktung, nicht auf diese Frage. Ich behandle sie nicht als abgelehnt, sondern als
offen.*

**Zweitens, kleiner: die Prüfplätze.** Vier Bauplätze und vier Prüfplätze sind dieselbe
Zahl, obwohl gerade sieben Pakete auf Urteile warten und nur eines auf einen Bauplatz.
Eine getrennte, höhere Zahl für die Prüfphase kostet **nichts zusätzlich pro Urteil** — sie
verwandelt leere Bauplätze in Durchsatz. Der Einwand steht in Ihrer eigenen Messung: 25 %
der Urteile sind Wiederholungen. Rücklaufgrenze und faire Platzvergabe wirken erst seit
gestern. **Empfehlung: eine Nacht mit der neuen Rücklaufgrenze abwarten, dann erhöhen** —
sinkt die Wiederholungsquote nicht, vervielfacht eine Erhöhung nur die Nacharbeit.

## Vorrang

1. **0011** — das Urteil, an dem die ganze Kernkette hängt. Ohne es kein 0026, kein 0002,
   kein `werte`.
2. **0026** — die Klasse-2-Frage. Sobald 0011 fertig ist, ist dies das einzige Paket, das
   den letzten leeren Kernkasten entblockt.
3. **0019** — sein Urteil entblockt mit 0029 und 0031 zwei der sieben offenen Pakete, mehr
   als jedes andere.
4. **0028** — entblockt 0035 und damit den zweiten Datenbauplatz, der sonst leer bleibt.
5. **0034** — das einzige derzeit startbereite Baupaket überhaupt.

**Ohne Kennung, an den Projektmanager:** Die doppelten Nummern 0039 und 0040 auflösen,
bevor sie in `haengt_an`-Verweisen anderer Pakete stehen. Und für 0041 einen Weg nennen
oder ihn ausdrücklich an den Betreiber zurückgeben — ein Vorschlag, den kein Gewerk bauen
darf, verstopft sonst jeden Trockenlauf.

## Die eine Zahl

**Acht von neun Kernkästen tragen Code** — nach fünf Plänen auf sieben. Es fehlt `werte`
(78 Byte), und eine Runde läuft: als Gerüst, im Modus `weltlauf`, sieben grüne Kerntests.
Gerechnet hat sie noch keinen einzigen Wert.
