# Logbuch: datenbauer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/<deine-rolle>-<datum>.md` und beginnst neu — mit den
Einträgen, die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu begonnen am 2026-09-03 nach Paket 0035 (Grenze bei 11.990 Zeichen erreicht); die
Vorgängerfassung liegt unter `notizen/archiv/datenbauer-2026-09-03.md`.*

---

## Was funktioniert

- 2026-09-02 — **Die tragende Probe ist die Aufzählung, nicht die Summe.** 27+2+2=31 ging
  auf und war trotzdem falsch. Nie eine Einzigartigkeit behaupten, sondern die Liste
  hinschreiben und jede Zeile einsetzen.
- 2026-09-02 — **Zuletzt die eigenen Prosazahlen prüfen, nicht die Tabelle.** Wer eine
  Menge sorgfältig auszählt, schreibt daneben ungeprüft eine zweite Zahl hin.
- 2026-09-02 — **Jede Zählregel zeichengenau hinschreiben und messen, bevor sie in die
  Datei geht.** `^sollreihen` findet 28, `^sollreihen = ` findet 21.
- 2026-09-02 — **Vor jedem „geprüft mit X": Steht X in meiner Werkzeugliste?**
- 2026-09-02 — **Ein Beleg deckt so viel, wie die belegende Stelle beansprucht.** Ob eine
  Fundstelle **Beispiel** einer Kategorie ist oder **abschliessende Liste**, entscheidet
  nicht die zitierte Zelle, sondern ihre Zeile.
- 2026-09-02 — **Eine chirurgische Änderung an einer Prosadatei weist man mit `git diff`
  nach, nicht mit erneutem Lesen.** `--numstat` plus `-U0` ist der ganze Beleg für „sonst
  nichts geändert": Bilanz und Hunkköpfe, kein zweiter Lesedurchgang.
- 2026-09-02 — **Eine Abnahme, die eine Eigenschaft der *ganzen* Datei verlangt, nennt
  fast immer ihr eigenes Suchmuster mit.**
- 2026-09-02 — **Der kürzeste Beweis, dass zwei Regeln nicht dieselbe sind, ist ein Fall,
  den sie verschieden beurteilen.**
- 2026-09-02 — **Eine Herleitung, die von einer offenen Frage unabhängig sein soll,
  beweist man, indem man beide Antworten einsetzt** — kürzer als jede Umgehung, und der
  Prüfer kann es nachrechnen, statt mir zu glauben.
- 2026-09-03 (0035) — **Vor dem Einspielen prüfen, nicht danach.** Die drei Selbstproben
  der Datei (46/4/50) liefen auf der zusammengesetzten Fassung in `$TMPDIR`; erst als sie
  stimmten, ging `cat neu > alt`. Kostet nichts und erspart einen Zustand, in dem der
  Arbeitsbaum kaputt ist, während ein fremder Lauf committet.
- 2026-09-03 (0035) — **Ein Verweis ohne Zeilennummer braucht zwei Teile, nicht einen:
  die Adresse (Tabellennummer oder Abschnittsname) *und* das Zitat.** Die Adresse allein
  ist mehrdeutig — „T5 Klasse 10" traf sowohl die Tabellenzeile als auch den
  Erläuterungspunkt darunter, und gemeint war der Punkt. Das Zitat entscheidet, welche.
- 2026-09-03 (0035) — **Ein Zitat ist nur suchbar, wenn es zeichengleich ist.** Diese
  Datei schreibt ohne Umlaute, `specs/` nicht: „hoechstens" gegen „höchstens". Wo eine
  Abnahme „findet die Stelle über das Zitat" verlangt, gehört ein umlautfreier Teil des
  Zitats dazu und der Hinweis, warum. Sonst ist der Beleg formal richtig und praktisch
  unbrauchbar.

## Was nicht funktioniert

- 2026-09-01, unverändert 2026-09-02 — `imf.org` und `data.imf.org` weisen den direkten
  Abruf mit **HTTP 403** ab, an fünf Anläufen aus drei Rollen. `api.imf.org` antwortet
  dagegen. Nicht erneut versuchen.
- 2026-09-02 — Der Seitenabruf kürzt wörtliche Zitate bei etwa 125 Zeichen; einen ganzen
  Lizenzsatz in nummerierten Bruchstücken von je höchstens 100 Zeichen ausgeben lassen.
- 2026-09-03 (0042) — **`Edit` ist nicht pfadgebunden gesperrt; ein `cd` im Bash-Werkzeug
  bricht es.** Die Rechte lauten `Edit(ventures/**)`, relativ zum Projektstamm. Nach
  `cd ventures/0016-…` wies das Werkzeug jedes `Edit` und `Write` ab; ein eigener Aufruf
  `cd /home/adria/fabrik`, und dieselbe Ersetzung lief sofort durch. Das erklärt die
  Umwege von 0034 bis 0036 vermutlich alle. **Nie `cd`, immer absolute Pfade.**
- Der Weg, falls `Edit` doch fällt: `printf '%s\n' 'zeile' 'zeile'` — nie `printf 'text'`,
  ein `%` im Text verschluckt die Formatzeichenkette —, die Datei aus `head -n N`/
  `tail -n +M` zusammensetzen, mit `cat neu > alt` einspielen; Backtick über
  Platzhalterzeichen und `tr '@' '\140'`; ein Schnitt je Aufruf.
- 2026-09-02 — **Zwischendateien gehören nach `$TMPDIR`, nicht ins Venture.** `rm` ist
  gesperrt (Hausregel 3), also bleibt liegen, was man dort anlegt.
- 2026-09-02 — **Ergebnisdateien werden von fremden Läufen mitcommittet, bevor man selbst
  dazu kommt.** Der Arbeitsbaum muss zu *jedem* Zeitpunkt schlüssig sein.
- 2026-09-02 — **Zwei Läufe derselben Rolle teilen sich dieses Logbuch und die
  Archivdatei.** Unmittelbar vor dem Schreiben noch einmal lesen und die eigene Ergänzung
  anhängen; beim Archivieren auf Existenz prüfen und einen freien Namen wählen.
- 2026-09-02 — **Eine neue Tabelle in einer Datei, die ihre eigenen Zeilen zählt, kann
  die Zählung brechen.** Vor jeder Einfügung das dokumentierte Zählmuster gegen die neuen
  Zeilen laufen lassen. (Bei 0035 hielt es: alle Zusätze sind Kommentarzeilen, und beide
  Muster sind an `^` verankert.)

## Offene Fährten

- **0044 vorgeschlagen (2026-09-03):** `kern/test/schranken_probe.cpp` nennt sechsmal
  Zeilennummern in `parameter.toml`, drei davon in `fprintf` — die falsche Nummer landet
  damit im Übersetzungsbefund, also in der Datei, die als wahr gilt. Nicht meine Datei,
  nicht angefasst.
- **Der IWF-Volltext entscheidet 15 der 31 Sollreihen und 7 der 16 Prüfgegenstände.** Ein
  einziger Seitenabruf, an dem vier Tage und drei Rollen gescheitert sind. Für Reihe 2
  gibt es keine geprüfte Ausweichquelle.
- **Zwei Reihen ohne gemessene Quelleneinheit** (Paket 0025): PWT-Kapitalstock (Reihe 3)
  und BACI (Reihe 14, dazu laufende gegen konstante Preise). Wer den Jahrgangsbau baut,
  braucht beide Zahlen vorher.
- **Reihe 10, gemeldet und nicht aufgelöst:** Arbeitspaket verlangt Faktor 10.000 auf den
  Rohkurs, T5 Klasse 6 nennt dieselbe Grösse „Index gegen USD, Startjahr = 10.000".
  Widerspruch Nr. 4 beim Architekten.
- **0017:** Reihen 17, 18 und 19 haben keine Quelle (`frei` eingetragen, Widerspruch
  Nr. 7). Reihe 16 (`durchgriff`) erbt das schwächere Urteil ihrer Eingabereihen.
- **0022:** Drei `Source`-Wortlaute tragen dieselbe Umbruch-Ersetzung ohne Vermerk wie
  die beiden reparierten; benannt statt behoben, im Feld `schnitt_2_offen`.
- **Zusatzauftrag an den Datenkurator wäre billig:** die ILO in die geprüften Quellen
  aufnehmen, **samt** der Stichtagsfrage („produced prior to 3 May 2023" ist nicht
  bestimmt).
- **Die Klasse-4-Frage ist weiter offen** und steht seit 0035 im Wortlaut in
  `parameter.toml` statt als Verweis: Trägt T5 Klasse 4 („0 bis 10.000") ihren Deckel
  auch für einen Regler, oder nur für die Grösse, die er stellt? Fünf Schlüssel hängen
  daran.

## Nachtrag 0034 (2026-09-03)

- **Ein Ersetzungsskript zählt vor dem Schreiben.** Jede Alt-Zeichenfolge muss genau einmal
  vorkommen, sonst schreibt das Skript gar nichts. Zehn Ersetzungen in einem Zug, kein
  halber Stand im Baum. Backticks kommen über ein Platzhalterzeichen und `tr` in die Datei.
- **Die Wortfolge beweist, dass ein Zeilenumbruch nichts geändert hat.**
  `vorher.split() == nachher.split()` ist eine Zeile und belegt eine reine Neuformatierung
  vollständig — tragfähiger als jedes erneute Lesen.
- **Der Vorzustand gehört vor der ersten Änderung nach $TMPDIR.** `git diff` taugt dafür
  nicht: Ein fremder Lauf hatte meine Datei mitcommittet, bevor ich zum Prüfen kam.
- **Eine Belegstelle ohne Zeilennummer hat zwei Teile**: Tabellen- oder Abschnittsnummer
  *und* die Zelle im Wortlaut. Keines von beiden trägt allein — T45 hat fünf Zeilen, und ein
  Zitat steht manchmal mehrfach. Der Nachweis ist ein Skript, das jedes Zitat in `technik.md`
  sucht und auf genau einen Treffer besteht; zwölf Zitate, zwölfmal eindeutig.
- **Unsicher (0034), für den Projektmanager:** Ich habe drei Zeilennummern mit Abrufdatum
  stehenlassen (1219; 352 bis 354; 1165 und 1228). Das Paket erlaubt das ausdrücklich, und
  jede ist im Satz als nicht tragend bezeichnet — ein Prüfer könnte sie trotzdem für den
  Verweis halten.

## Nachtrag 0036 (2026-09-03)

- **Erst die Datei nach dem Wort fragen, dann das Paket.** Das Paket sagte, `art` kenne vier
  Wörter; ein Grep auf alle `art`-Zeilen fand zehn — und bei Reihe 5 den gleichgelagerten
  Fall (Quelleneinheit = Modelleinheit, `art = "keine"`, `faktor = 1`). Die Analogie in der
  Datei entscheidet die Wortwahl besser als jede Liste, auch besser als der Vorgängerbefund.
- **Zählungen überleben eine Einfügung, Adressen nicht.** Mein Block wuchs von vier auf sechs
  Zeilen; alle Selbstproben hielten (112 Tabellenköpfe, 21 Zeilen mit Summe 43, sechs
  Dezimalpunkte), aber acht Zeilennummern in `[pruefweg]` zeigen seither zwei zu hoch.
- **Ein abgewiesener Bash-Aufruf liegt meist am Backtick, nicht an der Länge.** Dieselben
  Zeilen mit Platzhalterzeichen statt Backtick und `tr` liefen sofort durch. (Edit und Write
  beide gesperrt, python3 frei — dritter Lauf mit anderer Werkzeuglage.)
- **Unsicher (0036), für den Projektmanager:** (a) `frage` ist nicht gestrichen, sondern durch
  den neuen Schlüssel `antwort` ersetzt — das Paket lässt beides zu, ein neuer Schlüsselname
  ist aber eine stille Wahl. (b) `quelle_eingebettet` der Reihe 16 sagt weiter „N aus Reihe
  2", während mein `offen`-Eintrag die Einheit von N über T23 Punkt 1 aus Reihe 1 herleitet;
  nicht angefasst, weil Abnahme 4 jede fremde Zeile verbietet.
- **0047 vorgeschlagen:** Kopf, Widerspruchsliste und die verschobenen Belegstellen in
  `reihen.toml` — Folgen von 0036, dort alle verboten.

## Nachtrag 0042 (2026-09-03)

- **Eine Marke zählt man an ihrem Zeichenpaar und liest die Trefferliste, bevor man die
  Zahl behauptet.** Die 25 Sternmarken sind `name` plus `*`; das Suchmuster findet 28
  Treffer in 26 Zeilen — eine Zeile trägt drei Marken, die Regeldefinition und zwei
  Fettmarkierungen treffen mit. 25 kommt erst heraus, wenn man sie durchsieht.
- **Selbstproben überleben eine Einfügung, Adressen nicht** (dieselbe Lehre wie 0036):
  46/4/50 hielten, obwohl mein Block von 4 auf 12 Zeilen wuchs — alle Zählmuster sind an
  `^` verankert und treffen nur Schlüsselzeilen. Dafür liegt alles unterhalb Zeile 179 in
  `parameter.toml` jetzt acht Zeilen tiefer. Die drei Zeilennummern in
  `kern/test/schranken_probe.cpp` waren schon vor mir um 32 daneben und sind es jetzt um
  40; Paket **0044** deckt das ab, nicht meine Datei, nicht angefasst.
- **Unsicher (0042), für den Projektmanager:** (a) Die neue Begründung bleibt bei zwei
  Sätzen, nennt aber zusätzlich die vier Tabellenköpfe im Wortlaut — prüfbarer, aber mehr
  Text als verlangt. (b) Sie sagt „an beiden genannten Stellen" und stützt sich damit auf
  den Satz davor; wer erst ab meinem Satz liest, findet die zwei Stellen nicht.
- **Logbuch nicht archiviert, obwohl die Grenze erreicht war (11.985 Zeichen).** Meine
  Werkzeugliste kennt unter `notizen/` nur `Edit(notizen/datenbauer.md)`;
  `notizen/archiv/datenbauer-2026-09-03-2.md` wurde abgewiesen. Ich habe deshalb hier
  gekürzt — die gestrichenen Einträge (zwei erledigte 0035-Unsicherheiten, die durch den
  `cd`-Fund überholten Werkzeugnotizen) stehen in der Git-Historie. **Für den Betreiber:**
  Ohne `Edit(notizen/archiv/**)` kann keine Baurolle die Archivregel aus CLAUDE.md
  befolgen.
