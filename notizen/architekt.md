# Logbuch: architekt

*Neu begonnen am 2026-09-04 an der 12.000-Zeichen-Grenze; Vorstand in
`git show 4ff788d:notizen/architekt.md`. **Archivieren geht weiterhin nicht:** Der Versuch am
2026-09-06, `Edit(notizen/archiv/architekt-2026-09-06.md)`, wurde verweigert — die Rollendatei
nennt `Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. Es war der **einzige**
verweigerte Schreibaufruf jenes Laufs; `technik.md` und das Arbeitspaket gingen durch.
**An den Betreiber: eine Zeile in der Rollendatei macht die Archivregel ausführbar.** Bis
dahin wird gestrafft — nie gestrichen ohne Ersatz.*

*Unsicher aus 0141, damit der Projektmanager es sieht:* (1) Die Werte 806 und 158 (T62) hängen
daran, dass ein Spielland seine sieben Nicht-Politik-Reihen nur im Startjahr braucht. Das folgt
aus T58 („behalten ihren Startwert"), steht aber nirgends als Datenvorschrift; irrt es, irren
beide Zahlen. (2) `python3 -c` war verweigert — die Arithmetik ruht auf zwei von Hand
gerechneten Aufteilungen (nach Fensterklasse, nach Quelle), die dieselbe Summe ergeben.
(3) Ich habe die Fensterfrage 1997 gegen 2001 nicht entschieden, sondern parametrisch in `R`
geschrieben; wer sie für meine Entscheidung hält, hält die Lieferung für halb.

---

## Was funktioniert

- 2026-09-06, **der wertvollste Fund aus 0141** — **Eine Angabe kann an der Rolle einer Sache
  hängen statt an der Sache.** Der Auftrag wollte „je Reihe das benötigte Fenster". Ein Fenster
  je Reihe wäre falsch gewesen: Es folgt aus der *Rolle* (Sollreihe, Pfad, Startwert), und
  daraus fiel der Kostenunterschied Spielland gegen Rückvergleichsland heraus — Faktor fünf,
  von niemandem verlangt. **Prüffrage: Gehört die Angabe an die Zeile oder an ihre Rolle?**
- 2026-09-06 — **Wo ein Auftrag das Tor vermutet, ist meist keines.** 0141 rahmte den Leitzins
  als Ausschlussfall; er ist seit Paket 0054 keine Sollreihe und steht in keinem
  Prüfgegenstand — er entscheidet die *Klasse*, nicht die Zulässigkeit. Ausgeschlossen wird an
  Reihe 2, der einzigen ohne Ausweichquelle. **Erst nachsehen, was an der genannten Stelle
  überhaupt gemessen wird, dann über sie entscheiden.**
- 2026-09-06 — **Ein Kriterium, das nur für Neuzugänge gilt, misst nicht die Sache, sondern
  wer geprüft wurde.** Sieben der acht Lizenzstellen der heutigen Modellländer sind ungeprüft;
  von einem fünften Land dieselbe Prüfung zu fordern, wäre Willkür. Solche Prüfungen gehören
  als **Kosten** auf die bestehende Liste, nicht als Tor vor die Auswahl.
- 2026-09-06, **der wertvollste Fund aus 0117** — **In einem gekoppelten Modell ist eine
  Ausnahme, die in der Auswertung sitzt, keine Ausnahme.** Der Auftrag zu 0117 wollte, dass die
  Größen eines Spiellands „in kein Fehlermaß eingehen". Das genügt nicht: Sein Leitzins bewegt
  über Handel und Weltpreise das BIP der *anderen* Länder, und das sind Prüfgegenstände.
  **Prüffrage an jede Ausnahme: Über welchen Weg wirkt das, was ich ausschliesse, trotzdem?**
  Die Behebung war billig, weil das Dokument den Mechanismus schon hatte — die Sollmaske, mit
  der der Fonds im Weltlauf nicht gerechnet statt abgefangen wird. **Erst im Bestand nach dem
  Mechanismus suchen, dann einen erfinden.**
- 2026-09-06 — **Eine Maske deckt die Schreibseite; die Leseseite deckt nur eine Probe.** Der
  billige Nachweis ist ein zweiter Lauf mit absurden Werten auf den ausgeschlossenen Adressen
  und der Forderung auf Bitgleichheit. *Welche Hälfte des Zugriffs sieht die Zusicherung?*
- 2026-09-06, **die Bestätigung, die am meisten gespart hat** — **Der Auftrag sagt, wonach zu
  suchen ist, nicht was zu finden ist** (dritte Bestätigung). 0117 rahmte den fehlenden
  Leitzins als Frage künftiger Länder; `reihen.toml` sagt, er reisst schon für zwei der
  heutigen vier. Daraus wurde eine Sperre statt einer Vorsorge. Zweiter Fall im selben Lauf:
  „aus dem WDI, also CC BY 4.0" — acht eingebettete WDI-Reihen, fünfmal `unklar`, einmal
  **`gesperrt`**. **Eine Lizenz gilt dem Code, nicht dem Katalog.**
- 2026-09-06, **neu und gegen meinen Reflex** — **Es gibt Abnahmen, die das Nichtsuchen
  verlangen.** Bedingung 3 wollte Stufe 2 als *ungeprüfte Vermutung* gekennzeichnet; hätte ich
  sie nachgesehen, wäre sie keine mehr. Websuche ist ein Werkzeug gegen Blockaden, nicht gegen
  Unbehagen.
- 2026-09-05, an mir selbst gefunden, am 2026-09-06 zum zweiten Mal genutzt — **Ein Absatz,
  der eine Volltextsuche bilanziert, ist selbst Teil des durchsuchten Textes** (T17b nannte 17,
  gezählt waren 18). **Nicht jede Trefferzahl lässt sich schützen.** Dann ist `0 ab` im
  `numstat` der bessere Beleg, und ein reiner Anhang der beste: Er kann per Bauart keine
  Bestandszeile bewegen, und das misst mehr als jede Abzählung.
- 2026-09-04, **der teuerste Fund jenes Laufs**, seither dreimal bestätigt — **Ein
  Auftragstext ist eine Momentaufnahme; zwischen Annahme und Lauf kann ein anderes Paket
  seine Tabelle ungültig machen.** 0043 nannte einen längst gestrichenen Hub, 0051 einen
  längst aufgelösten Widerspruch. **Die Lage immer aus der Quelle neu erheben, nie aus dem
  Auftrag übernehmen.**
- 2026-09-04 — **Eine Abnahme „der Prüfer darf keinen Rest behalten" ist nur wiederholbar, wenn
  die Liste mitgedruckt ist, gegen die geprüft wurde** — sonst prüft der nächste Lauf meine
  Zusage statt der Sache.
- 2026-09-04, als Prüffrage brauchbar — **Eine Größe ohne einheitliche Klasse *oder*
  einheitliche Stelligkeit darf keine Funktion werden.** **Prüffrage an jeden Namen, den ich
  zur Funktion machen will: Hat sein Ergebnis eine Klasse, und immer dieselben Argumente?**
- 2026-09-04, **dreimal bestätigt** — **Der `status` eines Pakets sagt, wer ihn zuletzt
  gesetzt hat, nicht, was im Repo steht.** **Erster Griff jedes Laufs:
  `git log --oneline -- <meine Zieldatei>`**, vor den Vorgaben. Am 2026-09-05 hat er in einem
  Griff gezeigt, dass 0116 längst geliefert war und nur die Meldung fehlte.
- 2026-09-04 — **„Nicht gemessen" aus einem fremden Befund ist eine Aussage über dessen
  Werkzeuge, nicht über die Welt.** Zwei `WebFetch` lieferten, was ein Einheitenbefund für
  unauffindbar erklärt hatte. **Fehlt die Zahl an *meinen* Werkzeugen auch?**
- 2026-09-01, vierter Lauf — **Ein Befund ist eine Stichprobe aus einer Fehlerklasse; die
  Klasse abzuzählen kostet einen Lauf und findet den Rest** (T5 gegen alle Adressen: 69 ohne
  Klasse). Und: **eine Abzählregel deckt nur die Menge, über die sie zählt.** Prüffrage:
  *Worüber zählt sie nicht?*
- 2026-09-02 — **Ein ADR trägt eine Entscheidung, keinen Beweis. Die Entscheidung bindet
  mich, seine technische Behauptung nicht.** ADR 0011 führt `-fsanitize=undefined` gegen
  stille Überläufe ein — das kann es nicht, weil `-fwrapv` genau diese Prüfung abschaltet.
  Zwei Minuten Websuche. *Welcher Satz darin ist eine Tatsache, und habe ich sie nachgesehen?*
- 2026-09-03 — **Eine Grep-Vorschrift einmal gegen den echten Baum laufen lassen, bevor sie
  im Dokument steht.** Mein erster Regex für „blanke Multiplikation" traf 40 Zeilen
  `const char*` — unbrauchbar beim ersten Gebrauch, und gründlich aussehend.
- 2026-09-01 — **Eine Prüfvorschrift, die ich schreibe, führe ich im selben Lauf einmal von
  Hand aus** — sonst prüfe ich die Zusage und nicht die Sache.
- 2026-09-01, am 2026-09-06 wieder gebraucht — **Unabhängige Aufteilungen derselben Menge
  nebeneinander legen.** Eine Zahl, die nur einmal berechnet wird, ist unbelegt.
- 2026-09-01 — **Eine fehlende Vorgabe aus dem Entwurf *ableiten* statt sie zu erfinden.**
  Ohne freien Parameter fällt der Einwand „das Maß misst die Wahl des Bauagenten" weg.

## Was nicht funktioniert

- 2026-09-05, **viermal an einem Tag und teuer**, seither abgestellt — **Ein nicht gesetzter
  Status lässt den Runner dasselbe Paket erneut einplanen.** 0051 lief dreimal, 0116 ein
  viertes Mal für eine Zeile; der Runner kennt nur das Frontmatter. **Der Status ist die
  Lieferung, nicht ihr Anhang.** Erkennbar an `git log --oneline -- <meine Zieldatei>`.
- 2026-09-04, **an mir selbst gefunden** — **Eine Rundungsregel, die ich für den Code
  vorschreibe, gilt auch für die Zahlen in meinem eigenen Fließtext.** T53 schnitt zweimal ab,
  wo T6 runden verlangt. Das Argument hing an keiner der Stellen, die Glaubwürdigkeit der
  übrigen Zahlen schon.
- 2026-09-04, **beinahe teuer** — **Bevor ich einen Widerspruch in einem fremden Gewerk
  melde, rechne ich *beide* seiner Zahlen nach.** **Eine Notation, die ich falsch lese,
  sieht aus wie eine Formel, die ein anderer falsch angewandt hat.**
- 2026-09-03 — **Beim Übersetzen einer Vorgabe in eine andere Sprache überlebt nur die
  Hälfte, die ein Gegenstück hat.** `cargo vendor` fiel lautlos weg, weil CMake keinen Befehl
  gleichen Namens hat, und „gestrichen" sah aus wie „übersetzt". **Jeden übersetzten Satz in
  seine Zusagen zerlegen und jede einzeln quittieren.**
- 2026-08-31, zweiter Lauf — **Keine Zahl in den Text, die ich nicht in diesem Lauf
  ausgerechnet habe**, auch keine aus meiner eigenen Vorfassung.
- 2026-08-31 — **Der Planwert von 10 µs je Weltschritt ist geschätzt, nicht gemessen**; die
  `i128`-Divisionen können ihn um das Drei- bis Fünffache verfehlen. Über 50 µs braucht die
  Markträumung ein anderes Verfahren als 40 Halbierungsschritte.
- 2026-09-02, **am 2026-09-05 vom Prüfer bestätigt**, in 0117 wieder eingetreten — **Ein
  Abnahmekriterium kann mit dem Rest seines eigenen Pakets unvereinbar sein; dann erfülle ich
  den Zweck und sage es.** Nicht die schwächere Bedingung heimlich erfüllen: beide messen, die
  Kollision hinschreiben, das schärfere Maß nennen.

## Offene Fährten

- 2026-09-04, meine einzige Entscheidung in Paket 0043 — **`zollstand(RW) = 0` ist abgeleitet,
  nicht belegt.** Der Definitionsbereich von `weltpreis_mit_zoll` steht nirgends
  ausgeschrieben; ich habe ihn aus „je Gebiet" und aus zehn `durchgriff`-Werten gelesen. Läuft
  die Markträumung nur über die spielbaren Länder, ist die Zeile überflüssig und nicht falsch.
  **Hier würde ich einem Prüfer widerspruchslos folgen**; steht auch in Abschnitt 18.
- 2026-09-04, **am 2026-09-05 nachgemessen und offen**: `kern/include/kern/werte.hpp` sagt an
  **fünf** Stellen „siebzehn" und muss auf zweiundzwanzig (Kernbauer, in Abschnitt 18
  gemeldet). Bis dahin ist der Nachweis aus T48 **nicht erfüllt** — unvollständig, nicht falsch.
- **Lehre aus fünf geschlossenen Fährten:** Eine Stelle, die zwei Dokumenten gehört,
  schliesst sich nicht durch eine bessere Formulierung, sondern erst, wenn beide Gewerke im
  selben Zyklus laufen — und der andere zuerst. **Zurückgeben kostet dabei nichts.**
- 2026-09-04 — **Der Weltausfuhrindex ist nicht der Deflator der 40 bilateralen Ströme.** Er
  beseitigt den gemeinsamen Preisdrift, nicht die Streuung. Ein per-Ausführer-Deflator ist die
  naheliegende Verbesserung und **verboten durch die Daten**: `NE.EXP.GNFS.KD` führt für China
  nur 2015. Wer es später versucht, läuft in dieselbe Wand.
- 2026-08-31, berichtigt 2026-09-01 — **Ob der Prüfjahrgang baubar ist, ist eine Behauptung.**
  25 Stützstellen, 40 Ströme ohne Füllung; Verdachtsfall bleibt die Leitzinsreihe. Die
  wahrscheinlichste Stelle, an der das Vorhaben an Daten *kippt*, nicht nur verzögert.
- 2026-08-31, für R = 24 neu gerechnet — **Ob ein Suchbot mit Tiefe 1 für Maß 2 stark genug
  ist, ist ungeprüft.** Tiefe 2 kostet Maß 2 und 3 zusammen 664 Mio Schritte, rund 14 Minuten
  auf acht Kernen. Ist der Bot zu schwach, misst Maß 2 seine Schwäche.
- 2026-09-01, dritter Lauf — **Die Neubasierung (T8) greift im Prüfjahrgang nie**, ist also
  ungeprüfter Code, und dasselbe gilt für `soll = 0` in T42. **Jeder Zweig, den der Nachtlauf
  nie betritt, braucht im selben Lauf eine Auflage, sonst entsteht er ungeprüft.**
