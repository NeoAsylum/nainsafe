# Logbuch: architekt

*Neu begonnen am 2026-09-04 an der 12.000-Zeichen-Grenze; Vorstand in
`git show HEAD~1:notizen/architekt.md`.*

***Warum hier gekürzt und nicht verschoben wird — der Grund steht jetzt fest:***
`agents/rollen/architekt.md` nennt unter `tools` genau `Edit(notizen/architekt.md)` und kein
`Edit(notizen/archiv/**)`. Die fünf Verweigerungen vom 2026-09-04 waren also richtig.
**An den Betreiber: eine Zeile `Edit(notizen/archiv/**)` in der Rollendatei macht die
Archivregel ausführbar.** Gestrichen ist dagegen die
Notiz vom 2026-09-05 über verweigerte `Edit`-Aufrufe auf `technik.md`: Im dritten Lauf ging
`Edit` auf dieselbe Datei zweimal ohne Verweigerung durch.

*Unsicher, damit der Projektmanager es sieht:* Die Zahl 17 in T17b gilt für eine Suche nach
**festem Text**. Wer den Punkt als Platzhalter sucht, zählt 29 und findet einen Widerspruch,
den es nicht gibt. Der Absatz sagt das jetzt; ob es der Prüfer so liest, weiss ich nicht.

---

## Was funktioniert

- 2026-09-05, **an mir selbst gefunden und der Grund dieses dritten Laufs** — **Ein Absatz,
  der eine Volltextsuche bilanziert, ist selbst Teil des durchsuchten Textes.** Meine
  Zähltabelle in T17b nannte 17 Treffer; gezählt waren 18, weil derselbe Absatz die
  ungeschützte Schreibweise als Gegenbeispiel mitführte — und zugleich zusicherte, keine
  seiner Zeilen sei ein Treffer. **Wer im Dokument über ein Suchmuster schreibt, schreibt es
  nur geschützt und zählt danach noch einmal.**
- 2026-09-04, **der teuerste Fund jenes Laufs**, am 2026-09-05 erneut bestätigt — **Ein
  Auftragstext ist eine Momentaufnahme; zwischen Annahme und Lauf kann ein anderes Paket
  seine Tabelle ungültig machen.** Paket 0043 nannte `preishub`, den Paket 0039 längst
  gestrichen hatte; Paket 0051 beschrieb einen Widerspruch, den zwei Läufe vor mir schon
  aufgelöst hatten. **Die Lage immer aus der Quelle neu erheben, nie aus dem Auftrag
  übernehmen** — der Auftrag sagt, *wonach* zu suchen ist, nicht *was* zu finden ist.
- 2026-09-04 — **Eine Abnahme „der Prüfer darf keinen Rest behalten" ist nur wiederholbar,
  wenn die Liste mitgedruckt ist, gegen die geprüft wurde.** Ohne sie prüft der nächste Lauf
  meine Zusage statt der Sache. Die Erhebung fand nebenbei eine Lücke, die beim Durchlesen
  der Auftragstabelle nicht aufgefallen wäre.
- 2026-09-04 — **Der unangenehme Rest ist der Name aus einer verworfenen Gegenrechnung.**
  `wmz` und `preishub` stehen in `spiel.md` nur noch im Gegenbeispiel. Weder für Vorschrift
  halten noch stillschweigend übergehen — **benennen, in der Restetabelle.**
- 2026-09-04, **neu, und als Prüffrage brauchbar** — **Eine Größe ohne einheitliche Klasse
  *oder* einheitliche Stelligkeit darf keine Funktion werden.** `verschiebung(l, i)` ist für
  den Zoll Klasse 5 und sonst Klasse 3; `menge(l, i)` ist immer Klasse 2, hat aber in der
  Zollzeile ein Sektorargument mehr. Beide bleiben deshalb Spaltenüberschriften, gebildet
  wird `schaden(l, i)` mit der Fallunterscheidung innen — dieselbe Bauart wie `markt(p)`.
  **Prüffrage an jeden Namen, den ich zur Funktion machen will: Hat sein Ergebnis eine
  Klasse, und hat es immer dieselben Argumente?**
- 2026-09-04, **dreimal bestätigt** — **Der `status` eines Pakets sagt, wer ihn zuletzt
  gesetzt hat, nicht, was im Repo steht.** **Erster Griff jedes Laufs:
  `git log --oneline -- <meine Zieldatei>`**, vor den Vorgaben. Hat auch heute getragen: Die
  Historie zeigte 0026 dreimal und 0043 nie, also war der Lauf echte Arbeit und keine
  Wiederholung.
- 2026-09-04 — **Zwei Dokumente, die dieselbe Größe herleiten, widersprechen sich eher in
  der *Herkunft* als in der Zahl.** T53 nannte `N` „aus Reihe 1", `reihen.toml` „aus Reihe
  2"; richtig ist Reihe 1 **mal** Reihe 2 — beide unvollständig, keine Zahl betroffen, also
  bei einer Zahlenprüfung unsichtbar.
- 2026-09-04 — **„Nicht gemessen" aus einem fremden Befund ist eine Aussage über dessen
  Werkzeuge, nicht über die Welt.** Zwei `WebFetch` auf eine JSON-Schnittstelle lieferten,
  was ein Einheitenbefund für unauffindbar erklärt hatte; die PDF-Sperre galt für PDF.
  **Bevor ich „bleibt offen" schreibe: Fehlt die Zahl an *meinen* Werkzeugen auch?**
- 2026-09-01, vierter Lauf — **Ein Befund ist eine Stichprobe aus einer Fehlerklasse; die
  Klasse abzuzählen kostet einen Lauf und findet den Rest.** T5 gegen alle 310 Adressen
  gelegt: 69 ohne Skalenklasse. Zweite Hälfte: **Eine Abzählregel deckt nur die Menge, über
  die sie zählt** — T45 zählt Adressen und konnte eine fehlende *Funktion* nicht finden.
  Prüffrage: *Worüber zählt sie nicht?*
- 2026-09-02 — **Ein ADR trägt eine Entscheidung, keinen Beweis. Die Entscheidung bindet
  mich, seine technische Behauptung nicht.** ADR 0011 führt `-fsanitize=undefined` gegen
  stille Überläufe ein — das kann es nicht, weil `-fwrapv` genau diese Prüfung abschaltet.
  Zwei Minuten Websuche. *Welcher Satz darin ist eine Tatsache, und habe ich sie nachgesehen?*
- 2026-09-02 — **Trägt eine Messung ein Urteil, lies das Erzeugnis statt der
  Zusammenfassung.** `objdump` machte aus einer Vermutung T6b. **Welches Erzeugnis liegt
  herum, das die Frage beantwortet?**
- 2026-09-03 — **Eine Aufzählung von Rechenarten muss eine Partition sein.** Nach der
  *Rechenart* schneiden, nicht nach der Stelle — sonst hat die Liste beim nächsten Zusatz
  wieder ein Loch.
- 2026-09-03 — **Eine Grep-Vorschrift einmal gegen den echten Baum laufen lassen, bevor sie
  im Dokument steht.** Mein erster Regex für „blanke Multiplikation" traf 40 Zeilen
  `const char*`. Ohne Probelauf steht dort eine Vorschrift, die beim ersten Gebrauch
  unbrauchbar ist — und gründlich aussieht.
- 2026-09-01, dritter Lauf — **Eine Prüfvorschrift, die ich schreibe, führe ich im selben
  Lauf einmal von Hand aus** — sonst prüfe ich die Zusage und nicht die Sache.
- 2026-09-01 — **Unabhängige Aufteilungen derselben Menge nebeneinander legen.** Eine Zahl,
  die nur einmal berechnet wird, ist unbelegt, auch wenn sie stimmt.
- 2026-09-01 — **Eine fehlende Vorgabe aus dem Entwurf *ableiten* statt sie zu erfinden.**
  Ohne freien Parameter fällt der Einwand „das Maß misst die Wahl des Bauagenten" weg.
- 2026-08-31 — **Jede Summe in einer Tabelle bekommt eine Nachrechnungszeile im Fließtext.**

## Was nicht funktioniert

- 2026-09-05, **zweimal hintereinander und teuer** — **Ich habe den Status meines eigenen
  Pakets nicht gesetzt, und der Runner hat es zweimal neu eingeplant.** 0051 lief am
  2026-09-05 dreimal (`ce59b8b`, `a127600`, dieser), weil `status: offen` stehen blieb; der
  Runner kennt nur das Frontmatter, nicht meine Arbeit. **Der Status gehört an den Anfang
  der Abschlussarbeit, nicht ans Ende.** Erkennbar war es sofort an
  `git log --oneline -- <meine Zieldatei>` — der zeigte zwei fremde Läufe auf mein eigenes
  Paket, bevor ich eine Zeile gelesen hatte.
- 2026-09-04, **an mir selbst gefunden** — **Eine Rundungsregel, die ich für den Code
  vorschreibe, gilt auch für die Zahlen in meinem eigenen Fließtext.** T53 nannte 3.577 und
  1,5570, wo 3.577,80 und 1,55710 stehen — zweimal abgeschnitten statt gerundet, in einem
  Dokument, dessen T6 genau das verbietet. Das Argument hing an keiner der Stellen, die
  Glaubwürdigkeit der übrigen Zahlen schon.
- 2026-09-04, **beinahe teuer** — **Bevor ich einen Widerspruch in einem fremden Gewerk
  melde, rechne ich *beide* seiner Zahlen nach.** **Eine Notation, die ich falsch lese,
  sieht aus wie eine Formel, die ein anderer falsch angewandt hat.**
- 2026-09-04 — **Ein Sammelabruf über mehrere Einheiten mischt sie, und die Antwort kann
  sich selbst widersprechen.** **Wenn eine Abfrage etwas entscheidet: eine Einheit je Abruf,
  und „transkribiere" statt „fasse zusammen".**
- 2026-09-03 — **Beim Übersetzen einer Vorgabe in eine andere Sprache überlebt nur die
  Hälfte, die ein Gegenstück hat.** `cargo vendor` fiel lautlos weg, weil CMake keinen
  Befehl gleichen Namens hat, und „gestrichen" sah aus wie „übersetzt". **Jeden übersetzten
  Satz vorher in seine Zusagen zerlegen und jede einzeln quittieren.**
- 2026-09-01, vierter Lauf — **Eine Vorgabe, die eine *Menge* nennt, ohne sie abzählbar zu
  machen.** T8 sagte „alle nominalen Größen dieses Landes"; es sind genau fünf Adressen je
  Gebiet. Der Bauagent hätte raten müssen.
- 2026-08-31, zweiter Lauf — **Keine Zahl in den Text, die ich nicht in diesem Lauf
  ausgerechnet habe**, auch keine aus meiner eigenen Vorfassung.
- 2026-08-31 — **Der Planwert von 10 µs je Weltschritt ist geschätzt, nicht gemessen**, und
  die `i128`-Divisionen können ihn um das Drei- bis Fünffache verfehlen. Über 50 µs muss die
  Markträumung anders gebaut werden als über 40 Halbierungsschritte.
- 2026-09-02, am 2026-09-03 bestätigt — **Ein Abnahmekriterium kann mit dem Rest seines
  eigenen Pakets unvereinbar sein, und dann erfülle ich den Zweck und sage es.** Still
  gehalten, wäre die Kandidatentabelle aus 0011 weggefallen.

## Offene Fährten

- 2026-09-04, **neu, und meine einzige Entscheidung in Paket 0043** — **`zollstand(RW) = 0`
  ist abgeleitet, nicht belegt.** Zehn `durchgriff`-Werte für fünf Gebiete sagen, dass die
  Restwelt an der Preisübertragung teilnimmt; Instrumente hat sie keine. Der
  Definitionsbereich von `weltpreis_mit_zoll` steht aber nirgends ausgeschrieben — ich habe
  ihn aus „je Gebiet" und aus der Zahl zehn gelesen. Läuft die Markträumung nur über die
  vier spielbaren Länder, ist die Zeile überflüssig und nicht falsch. **Hier würde ich einem
  Prüfer widerspruchslos folgen**; es steht auch in Abschnitt 18.
- 2026-09-04, **am 2026-09-05 nachgemessen und offen**: `kern/include/kern/werte.hpp` sagt
  an **fünf** Stellen „siebzehn" und muss auf zweiundzwanzig. Kernbauer-Arbeit, in
  Abschnitt 18 gemeldet. Bis dahin ist der mechanische Nachweis aus T48 **nicht erfüllt** —
  der Kopf ist unvollständig, nicht falsch.
- **Lehre aus fünf geschlossenen Fährten:** Eine Stelle, die zwei Dokumenten gehört,
  schliesst sich nicht durch eine bessere Formulierung, sondern erst, wenn beide Gewerke im
  selben Zyklus laufen — und der andere zuerst. **Zurückgeben kostet dabei nichts:** Hätte
  ich die offene Zahl in Gegenkraft 5 selbst gefüllt, stünde in Maß 2 meine Wahl.
- 2026-09-04 — **Der Weltausfuhrindex ist nicht der Deflator der 40 bilateralen Ströme.** Er
  beseitigt den gemeinsamen Preisdrift, nicht die Streuung zwischen den Strömen. Ein
  per-Ausführer-Deflator ist die naheliegende Verbesserung und **verboten durch die Daten**:
  `NE.EXP.GNFS.KD` führt für China nur 2015. Wer es später versucht, läuft in dieselbe Wand.
- 2026-09-02 — **ADR 0011 stützt sein erstes Argument auf einen Wechsel, den es nicht
  anordnet** (Spielstand speichert Zustand statt Aktionsfolge; T22 gilt unverändert). Ich
  habe daraus T52 gemacht statt den ADR zu deuten. Zuerst nachsehen, ob der Betreiber den
  Wechsel angeordnet hat.
- 2026-08-31, berichtigt 2026-09-01 — **Ob der Prüfjahrgang baubar ist, ist eine
  Behauptung.** 1997–2021, 25 Stützstellen, 40 Ströme ohne Füllung; Verdachtsfall bleibt die
  chinesische und brasilianische Leitzinsreihe (IWF IFS, HTTP 403). Die wahrscheinlichste
  Stelle, an der das Vorhaben an Daten *kippt*, nicht nur verzögert.
- 2026-08-31, für R = 24 neu gerechnet — **Ob ein Suchbot mit Tiefe 1 für Maß 2 stark genug
  ist, ist ungeprüft.** Tiefe 2 kostet Maß 2 und 3 zusammen 664 Mio Schritte, rund 14
  Minuten auf acht Kernen. Ist der Bot zu schwach, misst Maß 2 seine Schwäche.
- 2026-09-01, dritter Lauf — **Die Neubasierung (T8) greift im Prüfjahrgang nie**, ist also
  ungeprüfter Code, und dasselbe gilt für `soll = 0` in T42. **Jeder Zweig, den der Nachtlauf
  nie betritt, braucht im selben Lauf eine Auflage, sonst entsteht er ungeprüft.**
