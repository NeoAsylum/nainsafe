# Logbuch: architekt

*Neu begonnen am 2026-09-01; Vorfassung in `notizen/archiv/architekt-2026-09-01.md`.*

*Viermal an der Grenze, **viermal wurde `Edit` auf `notizen/archiv/architekt-<datum>.md`
verweigert**, zuletzt am 2026-09-04; `Edit` auf `specs/…/technik.md` ging in denselben Läufen
durch — gesperrt ist der **Pfad**, nicht das Werkzeug. Ich kürze deshalb hier; jeder frühere
Stand liegt in `git log -p`. **An den Betreiber: Diese Rolle braucht Schreibrecht auf
`notizen/archiv/`.***

---

## Was funktioniert

- 2026-09-04, **dreimal bestätigt** — **Der `status` eines Pakets sagt, wer ihn zuletzt gesetzt
  hat, nicht, was im Repo steht.** 0026 wurde dreimal zugewiesen und war ab dem ersten Mal
  geliefert; die Rollendatei `architekt` hat keinen Satz „Setze `status: gebaut`". **Erster
  Griff jedes Laufs: `git log --oneline -- <meine Zieldatei>`**, vor den Vorgaben. Im dritten
  Lauf hat er gehalten: nachgerechnet statt neu entschieden, alle T53-Zahlen reproduzieren.
  **Ein Wiederholungslauf ist keine verlorene Zeit, wenn er nachrechnet statt neu zu
  schreiben** — die Nachrechnung fand die Stelle unten.
- 2026-09-04 — **Zwei Dokumente, die dieselbe Größe herleiten, widersprechen sich eher in der
  *Herkunft* als in der Zahl.** T53 nannte `N` „aus Reihe 1", `reihen.toml` „aus Reihe 2";
  richtig ist Reihe 1 **mal** Reihe 2 (T23 P1). Beide unvollständig, keine falsch, keine Zahl
  betroffen — deshalb fällt so etwas bei einer Zahlenprüfung nicht auf. **Prüffrage an jede
  Größe, die ich aus Reihen herleite: Steht dieselbe Herleitung anderswo, und nennt sie
  dieselben Reihen?**
- 2026-09-04 — **„Nicht gemessen" aus einem fremden Befund ist
  eine Aussage über dessen Werkzeuge, nicht über die Welt.** Paket 0026 war darauf gefasst,
  dass ich offenlassen muss: Der Einheitenbefund sagte, *keine* der vier Quellen sei auf einen
  Deflator gemessen. **Zwei WebFetch auf einen Endpunkt, den dieselbe Rolle zwei Tage vorher
  benutzt hatte**, haben einen geliefert — die PDF-Sperre gilt für PDF, nicht für die
  JSON-Schnittstelle daneben. **Bevor ich „bleibt offen" schreibe: Fehlt die Zahl an *meinen*
  Werkzeugen auch?**
- 2026-09-04 — **Führt eine Quelle dieselbe Größe laufend *und* konstant, ist ihr Quotient der
  Deflator — mit einem Basisjahr, das sich selbst nachweist.** `NE.EXP.GNFS.CD` durch `.KD` ist
  ein Preisindex zur Basis 2015; weil beide im Basisjahr denselben Wert führen, ist
  `index[2015] = 10.000` ein Selbsttest von zwei Zeilen. **Suchmuster für jede fehlende
  Preisbasis: Gibt es die Reihe bei derselben Quelle in beiden Fassungen?**
- 2026-09-01, vierter Lauf — **Ein Befund ist eine Stichprobe aus einer Fehlerklasse; die
  Klasse abzuzählen kostet einen Lauf und findet den Rest.** T5 gegen alle 310 Adressen
  gelegt: 69 ohne Skalenklasse, darunter 32 mit demselben Fehler. Zweite Hälfte: **Eine
  Abzählregel deckt nur die Menge, über die sie zählt** — T45 zählt Adressen und konnte eine
  fehlende *Funktion* nicht finden. Prüffrage: *Worüber zählt sie nicht?*
- 2026-09-02 — **Ein ADR trägt eine Entscheidung, keinen Beweis. Die Entscheidung bindet mich,
  seine technische Behauptung nicht.** ADR 0011 führt `-fsanitize=undefined` gegen stille
  Überläufe ein — das kann es nicht, weil `-fwrapv` aus derselben Liste genau diese Prüfung
  abschaltet (seit GCC 8). Zwei Minuten Websuche. Prüffrage für jeden ADR: *Welcher Satz darin
  ist eine Tatsache, und habe ich sie nachgesehen?*
- 2026-09-02 — **Trägt eine Messung ein Urteil, lies das Erzeugnis statt der Zusammenfassung.**
  ADR 0011 erklärte 947 ns mit fehlendem `__int128`; `objdump` zeigte den wahren Grund und
  machte aus der Vermutung T6b. **Welches Erzeugnis liegt herum, das die Frage beantwortet?**
- 2026-09-03 — **Eine Aufzählung von Rechenarten muss eine Partition sein, sonst ist sie eine
  Liste mit Loch.** T7 Massnahme 4 liess die blanke `i64`-Multiplikation zwischen ihren
  Punkten liegen. **Wo ich Operationen aufzähle, schneide ich nach der Rechenart und frage,
  welche Art zwischen zwei Punkten liegt** — nach der *Stelle* geschnitten wird die Liste beim
  nächsten Zusatz wieder unvollständig.
- 2026-09-03 — **Eine Grep-Vorschrift einmal gegen den echten Baum laufen lassen, bevor sie im
  Dokument steht.** Mein erster Regex für „blanke Multiplikation" traf 40 Zeilen `const char*`
  und kursive Sterne. Ohne Probelauf stünde dort eine Vorschrift, die beim ersten Gebrauch
  unbrauchbar ist — und gründlich aussieht.

- 2026-09-01, dritter Lauf — **Eine Prüfvorschrift, die ich schreibe, führe ich im selben Lauf
  einmal von Hand aus** — sonst prüfe ich die Zusage und nicht die Sache. Gegen T45 fielen elf
  Adressen ohne Eintrag heraus; der Prüfer hatte die Bedingung zuvor für erfüllt erklärt.
- 2026-09-01 — **Unabhängige Aufteilungen derselben Menge nebeneinander legen.** Die 310
  Adressen sind dreifach aufgeteilt (T15, T45, T49); jede neue fand Lücken. Eine Zahl, die nur
  einmal berechnet wird, ist unbelegt, auch wenn sie stimmt.
- 2026-09-01 — **Eine fehlende Vorgabe aus dem Entwurf *ableiten* statt sie zu erfinden.** Die
  Zielgröße des Suchbots entstand als Rechnung auf `spiel.md`; ohne freien Parameter fällt der
  Einwand „das Maß misst die Wahl des Bauagenten" weg. Der Spielentwerfer hat daraufhin seine
  Formel an meine angeglichen, statt umgekehrt.
- 2026-08-31, zweiter Lauf — **Die Prüfbefunde des *anderen* Gewerks daraufhin lesen, was sie
  in meinem auslösen.** Wer nur die eigenen abarbeitet, liefert eine Fassung, die zum neuen
  Entwurf nicht mehr passt.
- 2026-08-31 — **Jede Summe in einer Tabelle bekommt eine Nachrechnungszeile im Fließtext.**

## Was nicht funktioniert

- 2026-09-04, **an mir selbst gefunden** — **Eine Rundungsregel, die ich für den Code
  vorschreibe, gilt auch für die Zahlen in meinem eigenen Fließtext.** T53 nannte 3.577 und
  1,5570, wo 3.577,80 und 1,55710 stehen — zweimal abgeschnitten statt gerundet, in einem
  Dokument, dessen T6 genau das verbietet. Das Argument hing an keiner der beiden Stellen, die
  Glaubwürdigkeit der übrigen Zahlen schon. **Nachrechnen heisst auch: meine eigene
  Rundungsvorschrift auf meine eigenen Zahlen anwenden.**
- 2026-09-04, **beinahe teuer** — **Bevor ich einen Widerspruch in einem fremden Gewerk melde,
  rechne ich *beide* seiner Zahlen nach.** `spiel.md`s `71,94/98,71 → 7.288` sah nach der alten
  Formel `H/N` aus; es ist `H/(H+N)` mit ausgeschriebenen Zahlen. **Eine Notation, die ich
  falsch lese, sieht aus wie eine Formel, die ein anderer falsch angewandt hat.**
- 2026-09-04, **neu** — **Ein Sammelabruf über mehrere Einheiten mischt sie, und die Antwort
  kann sich selbst widersprechen.** Ein Abruf über vier Länder meldete für Brasilien
  „Complete data: No" und „Null years: None" **in derselben Antwort**. Einzeln nachgefragt und
  nur um Abschrift gebeten: China trägt 24 der 25 Stützstellen als `null`. Das entschied den
  Zuschnitt des Deflators. **Wenn eine Abfrage etwas entscheidet: eine Einheit je Abruf, und
  „transkribiere" statt „fasse zusammen".**
- 2026-09-03 — **Beim Übersetzen einer Vorgabe in eine andere Sprache überlebt nur die Hälfte,
  die ein Gegenstück hat.** Der T1-Satz trug zwei Zusagen; die zweite (`cargo vendor`) fiel
  lautlos weg, weil CMake keinen Befehl gleichen Namens hat, und „gestrichen" sah aus wie
  „übersetzt". **Regel: Jeden übersetzten Satz vorher in seine Zusagen zerlegen und jede
  einzeln quittieren** — übersetzt, anders eingelöst oder ausdrücklich fallengelassen.
- 2026-09-01, vierter Lauf — **Eine Vorgabe, die eine *Menge* nennt, ohne sie abzählbar zu
  machen.** T8 sagte „alle nominalen Größen dieses Landes"; es sind genau fünf Adressen je
  Gebiet. Der Bauagent hätte raten müssen, und die Produktivität wäre der wahrscheinliche
  Fehlgriff gewesen.
- 2026-08-31, zweiter Lauf — **Keine Zahl in den Text, die ich nicht in diesem Lauf
  ausgerechnet habe**, auch keine aus meiner eigenen Vorfassung. Drei falsche Zahlen hatten
  dieselbe Ursache: übernommen statt nachgerechnet.
- 2026-08-31 — **Der Planwert von 10 µs je Weltschritt ist geschätzt, nicht gemessen**, und
  die `i128`-Divisionen können ihn um das Drei- bis Fünffache verfehlen. Deshalb steht
  `ticks_je_sekunde` als Berichtspflicht in jedem Prüfstandsbefund; über 50 µs muss die
  Markträumung anders gebaut werden als über 40 Halbierungsschritte.
- 2026-09-02, am 2026-09-03 bestätigt — **Ein Abnahmekriterium kann mit dem Rest seines
  eigenen Pakets unvereinbar sein, und dann erfülle ich den Zweck und sage es.**
  `0011-stack-auf-cpp` verlangte ein `grep` ohne Rust-Treffer und im selben Paket eine
  Kandidatentabelle, in der Rust eine gemessene Zeile ist. Der Projektmanager hat das
  Kriterium berichtigt. Still gehalten, wäre die Tabelle weggefallen.

## Offene Fährten

- **Lehre aus fünf geschlossenen Fährten (Läufe drei und vier):** Eine Stelle, die zwei
  Dokumenten gehört, schliesst sich nicht durch eine bessere Formulierung, sondern erst, wenn
  beide Gewerke im selben Zyklus laufen — und der andere zuerst.
- 2026-09-04, **neu, die Restgrösse von T53** — **Der Weltausfuhrindex ist nicht der Deflator
  der 40 bilateralen Ströme.** Er beseitigt den gemeinsamen Preisdrift (MAPE-Anteil 2.203 von
  2.000 Budget, gemessen), nicht die Streuung zwischen den Strömen. Die bleibt ungemessen und
  steht in T53 als solche. Ein per-Ausführer-Deflator ist die naheliegende Verbesserung und
  **verboten durch die Daten**: `NE.EXP.GNFS.KD` führt für China nur 2015. Wer es später
  versucht, läuft in dieselbe Wand.
- 2026-09-04, **nachgesehen** — **Die zwei Nachzüge aus Paket 0026 haben am
  2026-09-04 kein Paket**: Reihenliste-Zeile 20 und der Übertrag nach `reihen.toml`; 0068 deckt
  nur die Reihe-9-Frage. Beide liegen fertig in Abschnitt 17 von `technik.md`.
- 2026-09-01, vierter Lauf — **Zwei Beobachtungen an `spiel.md`, die ein Prüfer als Befund
  zählen könnte und die dann nicht mir gehören:** „Schaden" in Gegenkraft 5 hat keine
  Rechenvorschrift, und `fonds.sichtbarkeit` ist **eine** Adresse, während Aktion 5 von *einer
  Position* spricht. Beide stehen in Abschnitt 12. Fülle ich sie selbst, misst Maß 2 meine Wahl.
- 2026-09-02 — **ADR 0011 stützt sein erstes Argument auf einen Wechsel, den es nicht
  anordnet** (Spielstand speichert Zustand statt Aktionsfolge; T22 gilt unverändert). Ich habe
  daraus T52 gemacht statt den ADR zu deuten. Zuerst nachsehen, ob der Betreiber den Wechsel
  angeordnet hat; dann wird T52 billiger, aber nicht überflüssig.
- 2026-08-31, berichtigt 2026-09-01 — **Ob der Prüfjahrgang baubar ist, ist eine Behauptung.**
  1997–2021, 25 Stützstellen, R = 24, 31 Sollreihen, 40 Ströme ohne Füllung; Verdachtsfall
  bleibt die chinesische und brasilianische Leitzinsreihe (IWF IFS, HTTP 403). Die
  wahrscheinlichste Stelle, an der das Vorhaben an Daten *kippt*, nicht nur verzögert.
- 2026-08-31, für R = 24 neu gerechnet am 2026-09-01 — **Ob ein Suchbot mit Tiefe 1 für Maß 2
  stark genug ist, ist ungeprüft.** Tiefe 2 kostet Maß 2 und 3 zusammen 664 Mio Schritte, rund
  14 Minuten auf acht Kernen — meine ältere Notiz („sprengt den Nachtlauf") war falsch. Ist
  der Bot zu schwach, misst Maß 2 seine Schwäche.
- 2026-09-03 — **`festkomma.hpp` hat kein `mal(a, b)`.** T7 Massnahme 4.3 verlangt es; in
  Abschnitt 16 an den Projektmanager gemeldet. Nachsehen, ob es gebaut ist — daran hängt, ob
  die Vorgabe eine Zusage oder eine Tatsache ist.
- 2026-09-01, dritter Lauf — **Die Neubasierung (T8) greift im Prüfjahrgang nie**, ist also
  ungeprüfter Code, und dasselbe gilt für `soll = 0` in T42. Beide haben eine Testauflage
  (Regressionspartie 1980). **Jeder Zweig, den der Nachtlauf nie betritt, braucht im selben
  Lauf eine Auflage, sonst entsteht er ungeprüft.**
