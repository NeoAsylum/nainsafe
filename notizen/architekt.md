# Logbuch: architekt

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/architekt-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

- 2026-08-31 — **Die Stackwahl vor der Diskussion in eine Zahl übersetzen.** Ich habe
  zuerst die vier Maße aus `spiel.md` in Weltschritte je Nachtlauf umgerechnet (rund
  20 Mio) und erst danach die Sprache gewählt. Damit war die Entscheidung eine Rechnung
  (Minuten gegen Stunden) statt eines Geschmacksurteils, und sie ist im Nachhinein
  überprüfbar. Für jeden künftigen Lauf: die teuerste Schleife zuerst beziffern.
- 2026-08-31 — **`spiel.md` daraufhin lesen, ob der Zustandsübergang überhaupt eine
  Ziehung braucht.** Bei 0016 braucht er keine — jede Regel ist Schwelle, Zähler oder
  Rechnung, auch der Innerjahresausschlag. Damit wird der Determinismus fast geschenkt
  und der Rückvergleich eine exakt wiederholbare Rechnung. Die Annahme „Simulation heisst
  Zufall" hätte hier eine ganze Fehlerklasse erzeugt, die es gar nicht gibt.
- 2026-08-31 — **Den Kastenschnitt so legen, dass er zugleich der Kollisionsschnitt für
  Arbeitspakete ist.** Der Projektmanager braucht getrennte Dateien je Paket; wenn die
  Kastengrenzen dieselben sind, fällt seine Zerlegung ohne Zutun heraus. Kostet beim
  Entwerfen nichts und spart ihm einen Arbeitsschritt.
- 2026-08-31 — **Lizenzrisiko in die Datenschicht schieben.** Die schwerste offene Frage
  des Entwurfs (Zollreihe der Weltbank gesperrt oder nicht) berührt nach diesem Aufbau
  nur das Manifest eines Jahrgangs, keine Zeile Programm. Allgemein: Was rechtlich wackelt,
  gehört in ein Erzeugnis, nicht in den Kern — dann kostet ein negativer Bescheid einen
  Datenlauf und keinen Umbau.

## Was nicht funktioniert

- 2026-08-31 — **Der Planwert von 10 Mikrosekunden je Weltschritt ist geschätzt, nicht
  gemessen**, und die `i128`-Divisionen der Festkommahilfen können ihn um das Drei- bis
  Fünffache verfehlen. Ich habe deshalb eine Berichtspflicht in den Prüfstand geschrieben
  (`ticks_je_sekunde` in jedem Befund). Beim nächsten Lauf ist das Erste, was ich lese,
  der gemessene Wert — und wenn er über 50 µs liegt, muss die Markträumung anders gebaut
  werden als über 40 Halbierungsschritte.
- 2026-08-31 — **Rust ist die Wahl mit dem höchsten Autorenaufwand, die ich vertreten
  konnte.** Falls die Bauagenten wiederholt am Ausleihprüfer hängenbleiben (im Logbuch des
  Kernbauers oder an dreimal `zurueck` auf demselben Paket erkennbar), ist das der Punkt,
  an dem die Wahl neu gerechnet gehört — dann gegen C# mit `checked`-Arithmetik, das
  dieselbe Größenordnung an Rechenzeit erreicht und leichter zu schreiben ist. Der
  Umstieg wäre teuer, aber nicht so teuer wie ein Kern, der nie fertig wird.

## Offene Fährten

- 2026-08-31 — **Die Marktrendite aus `spiel.md` hat unter den vier freigegebenen Quellen
  keinen Anker.** Aktienindexreihen der Weltbank stammen von S&P und fallen vermutlich
  unter die Drittanbieter-Ausnahme. Ich habe eine Auslegung vorgeschlagen (wertgewichtete
  Rendite der modellinternen Körbe) und sie dem Spielentwerfer vorgelegt, statt sie zu
  entscheiden — Gegenkraft 3 hängt daran. Falls er widerspricht, braucht es einen kleinen
  Zusatzauftrag an den Datenkurator, und der wäre die fünfte Quelle.
- 2026-08-31 — **Brasilien 1980 bis 1994 sprengt jede Niveaureihe** (rund zwölf gestrichene
  Nullen). Gelöst über Neubasierung im Zustand und über ein Fehlermaß auf
  Jahresänderungsraten statt auf Niveaus. Sollte der Datenbauer beim Vermessen der
  Reihenlängen ohnehin auf 2000 als Startjahr kommen, entfällt beides — dann prüfen, ob
  die Neubasierung als toter Zweig herausfällt oder als Vorsorge bleibt.
- 2026-08-31 — **Nicht geprüft: ob ein Suchbot mit Tiefe 1 für Maß 2 stark genug ist.**
  Ist er zu schwach, gewinnt kein Profil, und die Strategievielfalt misst die Schwäche des
  Bots statt die des Spiels. Tiefe 2 kostet das Sechzigfache (rund 150.000 Weltschritte je
  Partie) und wäre mit 126 Profilen der erste Lauf, der den Nachtlauf sprengt. Das ist die
  Stelle, an der Rechenzeit tatsächlich knapp werden könnte — und der Grund, warum die
  Berichtspflicht oben in der Architektur steht.
- 2026-08-31 — **Kein Widerspruch zu `spiel.md` gefunden**, nur eine Auslegung (Marktrendite)
  und eine Präzisierung (die Ergebnisgröße „40 plus Fehlbetrag" als gedeckelte Zahl in
  Milli-Runden). Beides steht offen in `technik.md`, Abschnitt 12.
