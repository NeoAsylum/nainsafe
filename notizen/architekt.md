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

- 2026-09-01 — **Eine fehlende Prüfstandsvorgabe aus dem Entwurf *ableiten* statt sie zu
  erfinden.** Die Zielgröße des Suchbots fehlte; statt eine Gewichtung zu erfinden, habe ich
  die Ergebnisgröße aus `spiel.md` auf den Zwischenzustand gerechnet. Ergebnis: keine
  Gewichtung, kein Kalibrierwert, **kein freier Parameter** — und damit fällt der Einwand
  „das Maß misst die Wahl des Bauagenten" nicht durch ein Argument, sondern weil es keine
  Wahl mehr gibt. Für jede künftige Botbewertung: erst nachsehen, ob der Entwurf die Größe
  am Partieende schon definiert.
- 2026-09-01 — **Eine Botbewertung gegen *jede* Strategieklasse einzeln prüfen, nicht nur
  gegen die, die der Prüfer nennt.** Der Befund nannte Lobby. Beim Durchgehen der anderen
  beiden fiel auf, dass Beteiligungen im Fondsvermögen von `spiel.md` womöglich gar nicht
  vorkommen — dann kann Klasse 2 Maß 2 aus Bauartgründen nicht bestehen. Prüffrage in einem
  Satz: *Welche Klasse kann diese Bewertung strukturell nicht gewinnen?*
- 2026-09-01 — **Auf eine fehlende Zeile zwei Antworten geben: den Wert und die Prüfung,
  die sein Fehlen künftig unmöglich macht.** 32 Adressen ohne Startwert waren zwei
  Tabellenzeilen; die eigentliche Antwort ist die Herkunftstabelle über alle 310 Adressen,
  die den Jahrgangsbau bei null *und* bei zwei Einträgen abbrechen lässt. Dieselbe Bauart wie
  T40 in der Vorfassung. Die naheliegende Bequemlichkeit — fehlt der Eintrag, nimm null —
  hätte den Befund in eine Zahl verwandelt, die niemand mehr hinterfragt.
- 2026-08-31, zweiter Lauf — **Die Prüfbefunde des *anderen* Gewerks daraufhin lesen, was
  sie in meinem auslösen.** Von acht Befunden waren zwei meine; sechs zwangen trotzdem
  Änderungen an `technik.md`, weil der Spielentwerfer die Partie von 40 auf 28 Runden
  kürzte, drei Sektoren neu verankerte und die Ergebnisskala zu sich zog. Wer nur seine
  eigenen abarbeitet, liefert eine Fassung, die zum neuen Entwurf nicht mehr passt — und
  erzeugt genau den zweiten Lauf, den die Rolle verbietet.
- 2026-08-31, zweiter Lauf — **Jede Summe in einer Tabelle bekommt eine Nachrechnungszeile
  im Fließtext.** Befund 8 fand einen Zählfehler, den vier Leser übersehen hatten, weil die
  Summe nirgends noch einmal aufging. Zwei Zeilen Prosa mit den Teilsummen machen den
  Fehler beim Schreiben sichtbar, nicht erst beim Prüfen.
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

- 2026-09-01 — **Eine Formulierung, die eine fehlende Vorgabe wie eine vorhandene aussehen
  lässt.** In der Botliste stand „bewertet durch ein Nachspiel von einem Zug mit dem
  Heuristikbot als Fortsetzung". Bei Tiefe 1 gibt es gar keine Fortsetzung, und der Satz
  beschrieb einen *Vorgang* statt einer *Zielgröße* — drei Fassungen lang hat ihn niemand
  als Lücke gelesen, ich selbst am wenigsten. Regel ab jetzt: Wo etwas verglichen wird, muss
  das Verglichene ein Substantiv mit Rechenvorschrift sein, kein Verb.
- 2026-08-31, zweiter Lauf — **Drei falsche Zahlen, eine Ursache: übernommen statt
  nachgerechnet.** Die Feldsumme (`4 × 41 + 20`, in Wahrheit 21 wegfallende Felder), die
  Kalibrierschleife („zwei Stunden auf acht Kernen", tatsächlich 4,7) und die Tiefe-2-Kosten
  („sprengt den Nachtlauf", tatsächlich Minuten auf acht Kernen; die aktuelle Zahl steht
  unten unter *Offene Fährten*) — alle drei standen im
  Text, weil sie plausibel klangen, nicht weil ich sie in diesem Lauf gerechnet hatte. Regel
  ab jetzt: **Keine Zahl in den Text, die ich nicht in diesem Lauf ausgerechnet habe**, auch
  keine aus meiner eigenen Vorfassung. Der Prüfer hat zwei der drei gefunden; die dritte
  hätte den Selbstspieler eine Möglichkeit gekostet, die es gibt.
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

- **Geschlossen am 2026-08-31, zweiter Lauf:** Marktrendite (der Spielentwerfer hat meine
  Auslegung übernommen, aber nach Modellmarktwerten statt nach Fondsbestand gewichtet —
  seine Fassung war die bessere und vermeidet, dass ein grosser Fonds rechnerisch nie
  Überrendite hat) und das Startjahr — damals 1995, **seit Fassung 3 aber 1997**, weil die
  WDI-Sektoranteile erst dort lückenlos sind. Die Neubasierung für Brasilien greift im
  Prüfjahrgang nie mehr und bleibt als Vorsorge für die frühen Spieljahrgänge — **mit
  Testauflage**, sonst wäre sie ungeprüfter Code.
- 2026-08-31, **Zahlen berichtigt am 2026-09-01** — **Ob der Prüfjahrgang baubar ist, ist
  eine Behauptung.** Er heisst seit Fassung 3 nicht mehr 1995, sondern **1997–2021** mit
  **25 Stützstellen** und R = 24; `spiel.md` verlangt alle 31 Sollreihen und alle 40
  Handelsströme darüber **ohne Füllung**. Das bleibt die wahrscheinlichste Stelle, an der das
  Vorhaben an Daten scheitert; Verdachtsfall sind die chinesische und die brasilianische
  Leitzinsreihe (IWF IFS, Abruf mit HTTP 403 abgewiesen). Der Jahrgangsbau gehört an den
  Anfang der Paketfolge — jetzt aber nur noch, weil er das Vorhaben *kippen* kann, nicht
  weil ein engeres Fenster teuer wäre: Seit T40 kostet es eine Manifestzeile.
- 2026-09-01 — **Zum zweiten Mal gemeldet: `spiel.md` sagt „über 15 Runden `3·ai`", die
  Probe zwei Absätze darunter rechnet fünf Runden.** Meine Zahl ist die richtige, ändern darf
  ich sie nicht. Was diesmal geholfen hat: die allgemeine Form hinschreiben (`5k` Runden →
  `3k·ai` von `15k`), damit beide Sätze Sonderfälle einer Regel sind und **ein** Wort
  genügt — wahlweise `15 → fünf` oder `3·ai → 9·ai`. Zwei Reparaturen anzubieten ist
  billiger als eine Rückfrage. Kommt der Befund ein drittes Mal, liegt es an
  Abnahmebedingung 3, die eine Übereinstimmung verlangt, die kein Gewerk allein herstellt.
- 2026-09-01 — **Offen und nicht von mir zu entscheiden: Gehören Beteiligungen zum
  Fondsvermögen?** `spiel.md` schreibt „Kasse + bewertete Positionen − Hebel" und trennt
  anderswo Positionen von Beteiligungen. Fallen sie heraus, kann Klasse 2 Maß 2 nie
  bestehen. Steht als dritte Beobachtung in Abschnitt 12; beim nächsten Lauf ist das Erste,
  was ich in `spiel.md` nachsehe.
- 2026-08-31, zweiter Lauf — **Vier der 31 Sollreihen sind Eingabe des Rückvergleichs, nicht
  Prüfung.** Weil die Politikinstrumente auf die historischen Werte gesetzt werden, hat die
  Leitzinsreihe per Konstruktion Fehler null; die Staatsschuldenquote ist fast determiniert.
  Ich habe beide Zahlen in den Befund gelegt (T37) und die Entscheidung, welche die Abnahme
  trägt, dem Spielentwerfer vorgelegt. Allgemein: **Wo ein Maß eine Größe zugleich setzt und
  misst, ist es milder, als es aussieht** — das ist bei jedem Orakel nachzusehen.
- 2026-08-31, **Zahlen für R = 24 neu gerechnet am 2026-09-01** — **Ob ein Suchbot mit
  Tiefe 1 für Maß 2 stark genug ist, ist weiter ungeprüft; die Ausweichmöglichkeit ist
  grösser als gedacht.** *Wonach* er sucht, ist seit T44 entschieden und parameterfrei; offen
  ist nur, *wie weit*. Tiefe 2 kostet je Partie `24 × (1 + 60 × 61) = 87.864` statt 1.464
  Weltschritte, Maß 2 und 3 zusammen 664 Mio, also rund 14 Minuten auf acht Kernen beim
  Planwert. Meine ältere Notiz („sprengt den Nachtlauf") war falsch. Ist der Bot zu schwach,
  misst Maß 2 seine Schwäche statt die des Spiels — dann ist Tiefe 2 der Weg, nicht eine
  Schwellenänderung. Zusätzliches Argument seit heute: Der Umweg der Klasse 2 (Beteiligung
  verbilligt späteres Lobbying) ist bei Tiefe 1 grundsätzlich unsichtbar.
