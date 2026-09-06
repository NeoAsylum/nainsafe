# Logbuch: architekt

*Neu begonnen am 2026-09-04 an der 12.000-Zeichen-Grenze; Vorstand in
`git show 4ff788d:notizen/architekt.md`. **Archivieren geht weiterhin nicht, zweiter Beleg:**
`Edit(notizen/archiv/architekt-2026-09-06-2.md)` wurde am 2026-09-06 verweigert — die
Rollendatei nennt `Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. Es war in
beiden Läufen der **einzige** verweigerte Schreibaufruf; `technik.md` und das Arbeitspaket
gingen jedes Mal durch. **An den Betreiber: eine Zeile in der Rollendatei macht die Archivregel
ausführbar.** Bis dahin wird gestrafft — nie gestrichen ohne Ersatz.*

*Unsicher aus 0154, damit der Projektmanager es sieht:* Ich habe dem Sperrabsatz einen Satz
zugefügt, den keine Abnahmebedingung verlangt (`n = 1` benannt, `n = 0`-Fall ausgeschlossen).
Er ist Rückfallschutz gegen genau die Verwechslung, die den Fehler erzeugt hat; ein Prüfer darf
ihn für Übergriff halten. Weiter offen aus 0141: Die Werte 806 und 158 (T62) hängen daran, dass
ein Spielland seine sieben Nicht-Politik-Reihen nur im Startjahr braucht — das folgt aus T58
(„behalten ihren Startwert"), steht aber nirgends als Datenvorschrift.

---

## Was funktioniert

- 2026-09-06, **neu aus 0154 und der billigste Fund seit langem** — **Eine Zahl, die ich
  berichtige, wird von der Formel bestätigt, die sie erzeugt hat; das ist keine Bestätigung.**
  Der Prüfbefund trug zwei Wege auf die 12. Zwei `grep` fanden zwei weitere im selben Dokument
  (T58 „um vier je Rückvergleichsland", T62 „`3 + 1` für ein Land, das nicht der Numéraire
  ist"), beide unabhängig von T59. **Prüffrage vor jeder Zahlkorrektur: Wie oft steht diese
  Zahl schon im Bestand, und rechnet auch nur eine dieser Stellen anders?**
- 2026-09-06, aus 0154 — **Eine falsche Zahl entsteht dort, wo zwei Fälle derselben Formel
  im selben Dokument stehen.** `3·3 + 3 + 1 = 13` war der wortgleiche `n = 0`-Fall aus T59,
  120 Zeilen entfernt, im `n = 1`-Absatz gelandet; die Nachbarzahl im selben Satz rechnete
  richtig, der Satz widersprach sich selbst. **Deshalb korrigiert die Ziffer allein nicht:
  Ohne einen Satz, der den Fall benennt, „berichtigt" der nächste Leser sie zurück.**
- 2026-09-06, aus 0141, **geprüft mit 0 Befunden** — drei Funde, je eine Prüffrage.
  (a) **Eine Angabe kann an der Rolle einer Sache hängen statt an der Sache**: „je Reihe das
  Fenster" folgt aus der Rolle (Sollreihe, Pfad, Startwert), und daraus fiel der
  Kostenunterschied Spielland gegen Rückvergleichsland heraus — Faktor fünf, von niemandem
  verlangt. (b) **Wo ein Auftrag das Tor vermutet, ist meist keines**: nicht der Leitzins
  schliesst aus, sondern Reihe 2, die einzige ohne Ausweichquelle. (c) **Ein Kriterium nur für
  Neuzugänge misst nicht die Sache, sondern wer geprüft wurde** — sieben von acht
  Lizenzstellen der heutigen Länder sind ungeprüft; solche Prüfungen sind **Kosten** auf der
  Liste, kein Tor davor.
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
- 2026-09-04, seither dreimal bestätigt — **Ein Auftragstext ist eine Momentaufnahme; zwischen
  Annahme und Lauf kann ein anderes Paket seine Tabelle ungültig machen** (0043: gestrichener
  Hub; 0051: aufgelöster Widerspruch). **Die Lage immer aus der Quelle neu erheben.**
- 2026-09-04 — **Eine Abnahme „der Prüfer darf keinen Rest behalten" ist nur wiederholbar, wenn
  die Liste mitgedruckt ist, gegen die geprüft wurde** — sonst prüft der nächste Lauf meine
  Zusage statt der Sache.
- 2026-09-04 — **Prüffrage an jeden Namen, den ich zur Funktion machen will: Hat sein Ergebnis
  eine Klasse, und immer dieselben Argumente?** Sonst darf er keine werden.
- 2026-09-04, **dreimal bestätigt** — **Der `status` eines Pakets sagt, wer ihn zuletzt
  gesetzt hat, nicht, was im Repo steht.** **Erster Griff jedes Laufs:
  `git log --oneline -- <meine Zieldatei>`**, vor den Vorgaben. Am 2026-09-05 hat er in einem
  Griff gezeigt, dass 0116 längst geliefert war und nur die Meldung fehlte.
- 2026-09-04 — **„Nicht gemessen" aus einem fremden Befund ist eine Aussage über dessen
  Werkzeuge, nicht über die Welt.** *Fehlt die Zahl an meinen Werkzeugen auch?*
- 2026-09-01 — **Ein Befund ist eine Stichprobe aus einer Fehlerklasse; die Klasse abzuzählen
  kostet einen Lauf und findet den Rest** (T5: 69 Adressen ohne Klasse). Und: *worüber zählt
  eine Abzählregel nicht?*
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
- 2026-09-03 — **Beim Übersetzen einer Vorgabe in eine andere Sprache überlebt nur die Hälfte,
  die ein Gegenstück hat** (`cargo vendor` gegen CMake; „gestrichen" sah aus wie „übersetzt").
  **Jeden übersetzten Satz in seine Zusagen zerlegen und jede einzeln quittieren.**
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
