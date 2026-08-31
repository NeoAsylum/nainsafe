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

- 2026-08-31, zweiter Lauf — **Drei falsche Zahlen, eine Ursache: übernommen statt
  nachgerechnet.** Die Feldsumme (`4 × 41 + 20`, in Wahrheit 21 wegfallende Felder), die
  Kalibrierschleife („zwei Stunden auf acht Kernen", tatsächlich 4,7) und die Tiefe-2-Kosten
  („sprengt den Nachtlauf", tatsächlich 16 Minuten auf acht Kernen) — alle drei standen im
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
  Überrendite hat) und das Startjahr (1995, weil BACI dort beginnt). Die Neubasierung für
  Brasilien greift im Prüfjahrgang nie mehr und bleibt als Vorsorge für die Spieljahrgänge
  vor 1995 — **mit Testauflage**, sonst wäre sie ungeprüfter Code.
- 2026-08-31, zweiter Lauf — **Ob der Prüfjahrgang 1995 überhaupt baubar ist, ist eine
  Behauptung.** `spiel.md` verlangt alle 31 Sollreihen über 29 Stützstellen **ohne
  Füllung**. Das ist die wahrscheinlichste Stelle, an der das Vorhaben an Daten scheitert;
  Verdachtsfall sind chinesische und brasilianische Leitzinsreihen der neunziger Jahre. Der
  Jahrgangsbau gehört deshalb an den Anfang der Paketfolge und nicht ans Ende — das steht
  jetzt im Hinweis für den Projektmanager.
- 2026-08-31, zweiter Lauf — **Vier der 31 Sollreihen sind Eingabe des Rückvergleichs, nicht
  Prüfung.** Weil die Politikinstrumente auf die historischen Werte gesetzt werden, hat die
  Leitzinsreihe per Konstruktion Fehler null; die Staatsschuldenquote ist fast determiniert.
  Ich habe beide Zahlen in den Befund gelegt (T37) und die Entscheidung, welche die Abnahme
  trägt, dem Spielentwerfer vorgelegt. Allgemein: **Wo ein Maß eine Größe zugleich setzt und
  misst, ist es milder, als es aussieht** — das ist bei jedem Orakel nachzusehen.
- 2026-08-31, korrigiert im zweiten Lauf — **Ob ein Suchbot mit Tiefe 1 für Maß 2 stark
  genug ist, ist weiter ungeprüft, aber die Ausweichmöglichkeit ist grösser als gedacht.**
  Tiefe 2 kostet je Partie 102.508 statt 1.708 Weltschritte; Maß 2 und 3 zusammen 775 Mio,
  also rund 16 Minuten auf acht Kernen beim Planwert. Meine alte Notiz („sprengt den
  Nachtlauf") war falsch. Ist der Bot zu schwach, misst Maß 2 seine Schwäche statt die des
  Spiels — dann ist Tiefe 2 der Weg, nicht eine Schwellenänderung.
