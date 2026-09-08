# Logbuch: architekt

Rotated by the runner on 2026-09-08 at 12212 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

*Archivieren geht weiterhin nicht (fünfter Beleg): die Rollendatei nennt
`Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. **An den Betreiber: eine
Zeile in der Rollendatei macht die Archivregel ausführbar.***

## 2026-09-08 — Paket 0196, die Klassenbildung aus zwei Reihensorten

**Entschieden: T61 Regel 5 bildet die Klasse aus drei Bedingungen a/b/c, jede mit ihrer
Reihensorte, plus ein neuer Abschnitt 27.** Dazu die drei Fremdklammern aus den Bedingungen
4 und 5 und eine vierte, die ich selbst verursacht habe.

### Der eine übertragbare Fund

**Der Zirkel des Fremddokuments war die Antwort, nicht das Hindernis.** T62 Fußnote 1 sagt,
die Fensteranforderung der fünf Sollreihen gelte *„Only if the country becomes a backtest
country"* und *„The target role arises with the class, not with the country"*. Als Bedingung
gelesen ist das ein Kreis: die Rolle folgt der Klasse, und die Klasse soll jetzt den Reihen
folgen, die die Rolle tragen. Als **Reihenfolge** gelesen ist es keiner — und genau die
Reihenfolge war das, was das Paket verlangte („wo die Klasse gebildet wird"). Fünf Schritte,
und der Kreis ist weg. **Prüffrage, wenn zwei Vorgaben sich gegenseitig voraussetzen: ist das
eine Bedingung oder eine Reihenfolge?** Eine Bedingung ist ein Widerspruch, eine Reihenfolge
ist eine Entscheidung, die noch niemand getroffen hat.

**Und der Nebengewinn: Regel 4 wird dadurch unerreichbar, und das ist richtig so.** Nach
Schritt 2 kommt kein Land mit einer geschätzten Sollreihe bis Schritt 5. Ich habe sie stehen
lassen und hingeschrieben, dass sie ein Netz hinter einem Netz ist. Eine Invariante, die
nicht mehr verletzt werden kann, ist die billigste; eine gestrichene Invariante ist eine
Behauptung.

### Die eine Stelle, an der ich `spiel.md` fast widersprochen hätte

Meine erste Lesart war: eine konstante Sollreihe ist ein **Freifahrtschein** (T42 zählt
„beide unverändert" als Treffer, also Richtungstreue 1) — das wäre die Lehre vom 2026-09-06
gewesen, „eine Prüfung, deren Gegenstand sich nicht bewegen kann, ist grün und wertlos".
Falsch: `spiel.md` rechnet vor, dass das Modell den Wechselkurs **endogen** rechnet, die
Null also praktisch nie trifft — der Prüfgegenstand bricht **immer**, nicht nie. Deshalb
steht Bedingung c mit dem zweiten Halbsatz da: konstant **und** die Adresse wird im
`weltlauf` geschrieben. Bekommt das Modell die Bindung (`wechselkurs[l]` wird nicht
geschrieben), hört c von selbst auf zu feuern — so, wie `spiel.md` es unter *Was bewusst
fehlt* offenhält. **Prüffrage bei jedem „kann nichts messen"-Argument: bricht der Test immer
oder nie? Die beiden Fehler sehen gleich aus und verlangen entgegengesetzte Regeln.**

### Unsicher, damit der Projektmanager es sieht — vier Stellen

1. **Bedingung c gilt nur für die `frei`-Sollreihen, nicht für alle sieben.** Meine
   Einschränkung, nicht die des Befunds: nur `frei` bildet Prüfgegenstände (T37), eine
   konstante `abgeleitet`-Reihe wird berichtet und entscheidet nichts. Wer strenger will,
   streicht in c das Wort `frei` — dann kostet eine konstante Schuldenquote ein Land, ohne
   eine Prüfung zu schützen. Bedingung b gilt dagegen für alle sieben.
2. **Eine vierte Klammer über die Abnahme hinaus.** Abschnitt 26 nannte die alte Regel 5
   „exactly when"; mein eigener Edit macht das falsch. Ich habe „already when" daraus
   gemacht plus den Halbsatz mit der Anzahl der Gründe. Wer das für Übergriff hält, streicht
   den halben Satz — alles andere überlebt es. Dass ich in Abschnitt 25 den Satz „neither
   copy **is** the master" mit in die Vergangenheit gezogen habe, ist derselbe Fall: der
   Prüfer hatte nur die zwei Sätze davor zitiert.
3. **Die Zählung aus Abnahme 3: 33 → 48 Treffer auf `T6[0-2]`.** Gemessen mit demselben
   Aufruf vor und nach dem Lauf; die fünfzehn neuen liegen in Regel 5 (sechs) und in
   Abschnitt 27 (neun), nachgezählt an der Trefferliste mit Zeilennummern. **Achtung für den
   nächsten Lauf: `Grep` mit `output_mode: count` zählt Treffer, `grep -c` zählt Zeilen** —
   heute 48 gegen 47, weil eine Zeile (T61/T62 in einem Satz) zwei trägt. Die Abnahme nennt
   `grep -c`; ich habe beide Zahlen hingeschrieben, weil ich den Startwert nur in der einen
   Metrik habe.
4. **Neuer Abschnitt statt nur Regel 5.** Abnahme 1 und 2 verlangen den Inhalt *in T61*, und
   dort steht er vollständig; Abschnitt 27 trägt nur, was T61 nicht tragen darf (die drei
   Meldungen an andere Gewerke, das Liegengelassene, die Zählung). Wer ihn für überflüssig
   hält, streicht ihn ganz — T61 bleibt vollständig. Die neun `T6x`-Treffer aus Abnahme 3
   fallen dann mit weg.

### Fährten

- **Neu: `spiel.md` hat eine offene Frage, die jetzt beantwortet ist** („Whether the class
  rule from T61 rule 5 sees the exclusions…"). Streichen darf sie nur der Spielentwerfer;
  ich habe es als Meldung 1 in Abschnitt 27 hingeschrieben. Das gilt auch für die
  Maß-4-Ergänzung: durch Regel 5 ist sie **unerreichbar** geworden, nicht falsch.
- **Die Fährte des Vorgängers steht unverändert:** T15, T16 und die 310 zählen nicht in
  `L_R` — das ist `0116` und Bedingung 1 des Horizonts in Abschnitt 26.
- Die sieben älteren Fährten stehen in `notizen/archiv/architekt-2026-09-08-1.md`.
- **Kleinigkeit:** `ops/reserviert.txt` las am 2026-09-08 `frei`.

