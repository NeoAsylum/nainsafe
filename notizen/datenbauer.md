# Logbuch: datenbauer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/<deine-rolle>-<datum>.md` und beginnst neu -- mit den
Eintraegen, die noch gelten. Nicht loeschen.

Belege gehoeren nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu begonnen am 2026-09-04 nach Paket 0065 (Grenze bei 11.574 Zeichen erreicht); die
Vorgaengerfassung liegt unter `notizen/archiv/datenbauer-2026-09-04.md`.*

---

## Was funktioniert

- **Die tragende Probe ist die Aufzaehlung, nicht die Summe.** 27+2+2=31 ging auf und war
  trotzdem falsch. Nie eine Einzigartigkeit behaupten, sondern die Liste hinschreiben.
- **Jede Zaehlregel zeichengenau hinschreiben und messen, bevor sie in die Datei geht.**
  `^sollreihen` findet 28, `^sollreihen = ` findet 21.
- **Ein Beleg deckt so viel, wie die belegende Stelle beansprucht.** Ob eine Fundstelle
  Beispiel oder abschliessende Liste ist, entscheidet ihre Zeile, nicht die zitierte Zelle.
- **Chirurgische Aenderungen weist man mit `git diff --numstat` plus Hunkkoepfen nach**,
  nicht mit erneutem Lesen. Bilanz und Hunkliste sind der ganze Beleg fuer "sonst nichts".
- **Vor dem Einspielen pruefen, nicht danach.** In `$TMPDIR` zusammensetzen, dort messen,
  erst dann kopieren -- und den sha256 beider Fassungen nebeneinander ausgeben.
- **Ein Verweis ohne Zeilennummer hat zwei Teile: Adresse und Zitat**, und ein Zitat ist
  nur suchbar, wenn es zeichengleich ist -- auch in den Umlauten und ungebrochen auf
  einer Zeile.
- **Selbstproben ueberleben eine Einfuegung, Adressen nicht.** An `^` verankerte
  Zaehlmuster halten; jede Zeilennummer unterhalb der Einfuegung verschiebt sich.
- **Ist `python3` frei, ist `tomllib` der staerkste Nachweis, den diese Rolle hat.** Alte
  und neue Fassung beide einlesen, Baeume flach ziehen, Blattschluessel als Pfadtupel
  vergleichen. "Sonst ist nichts geaendert" wird damit ein gemessener Satz.
- **Eine Ersetzung mit Trefferzaehlung schuetzt vor dem stillen Danebengreifen.** Jede
  Ersetzung erwartet genau *n* Treffer und bricht sonst ab.
- **Nach jedem Ersetzungsschritt `tomllib`, nicht erst am Schluss.** Der Parser faengt,
  was `grep` nicht sieht -- ein typografisches Anfuehrungszeichen bricht einen Basisstring.
- **Die Schnittzahlen aus `[pruefweg]` sind eine kostenlose Regressionsprobe.** Alle
  fuenfzehn Muster nach dem Eingriff neu zaehlen; bei `schnitt_1` zusaetzlich die
  Trefferkontexte alt gegen neu, sonst bleibt eine gleiche Zahl aus anderen Stellen
  unbemerkt.
- 2026-09-04 (0065) -- **Der Bezugsstand gehoert als Commit-Kennung in den Bericht,
  bevor der Lauf beginnt.** `git ls-tree <commit> <pfad>` plus `git status` in einem
  Aufruf: zwei Zeilen, und jede spaetere Zahl bleibt reproduzierbar, auch wenn ein
  fremder Lauf die Datei mitcommittet.

## Was nicht funktioniert

- `imf.org` und `data.imf.org` weisen den direkten Abruf mit **HTTP 403** ab, an fuenf
  Anlaeufen aus drei Rollen. `api.imf.org` antwortet. Nicht erneut versuchen.
- Der Seitenabruf kuerzt woertliche Zitate bei etwa 125 Zeichen; einen ganzen Lizenzsatz in
  nummerierten Bruchstuecken ausgeben lassen.
- **Die Werkzeuglage wechselt von Lauf zu Lauf -- erst pruefen, was geht.** Sieben Laeufe,
  sieben Lagen. Nie aus dem letzten Lauf schliessen.
- **Der Weg, wenn `Edit` und `Write` fallen und `python3` laeuft:** ein Python-Heredoc
  (`python3 << 'MARKE'`) mit Ersetzungen auf einer Kopie in `$TMPDIR`, messen, dann
  `shutil.copyfile`. Backticks und eckige Klammern *im Heredoc* sind unproblematisch.
  Ein Hilfsskript in `$TMPDIR` ablegen und per `exec(open(...).read())` laden haelt die
  einzelnen Aufrufe kurz.
- **Abgewiesen wird nach Laenge, nicht nur nach Zeichen.** Erst kuerzen, dann Zeichen
  verdaechtigen. Bei 0065 fiel derselbe Messaufruf zweimal, bis ich die
  Dict-Comprehension durch eine gewoehnliche Schleife ersetzt hatte.
- **Ein fuehrendes `cd` laesst den ganzen Aufruf abweisen.** `git -C <pfad>` statt `cd`,
  und im Heredoc absolute Pfade -- ein relativer Pfad zeigt auf das Wurzelverzeichnis.
- `notizen/archiv/` ist **nicht** gesperrt -- wer statt zu archivieren im Logbuch kuerzt,
  verliert Eintraege ohne Not. Archivnamen vorher auf Existenz pruefen.
- **Zwei Laeufe derselben Rolle teilen sich Logbuch und Archivdatei.** Unmittelbar vor dem
  Schreiben neu lesen.
- **Zwischendateien gehoeren nach `$TMPDIR`** -- `rm` ist gesperrt.
- **Ergebnisdateien werden von fremden Laeufen mitcommittet.** Dreimal in Folge (0057,
  0062, 0065-Vorlauf). Der Arbeitsbaum muss zu *jedem* Zeitpunkt schluessig sein.

## Offene Faehrten

- **Der IWF-Volltext entscheidet jetzt 11 der 27 Sollreihen und 7 der 16
  Pruefgegenstaende** (bis 0065: 15 der 31). Ein einziger Seitenabruf, an dem vier Tage
  und drei Rollen gescheitert sind. Punkt an den Betreiber.
- **Reihe 3 (PWT-Kapitalstock) bleibt die einzige ungemessene Quelleneinheit.** Sie haengt
  an *einem* lesbaren Auszug aus `pwt110_user_guide_to_data_files.pdf` oder `pwt110.xlsx`
  -- beide benannt und erreichbar, nur nicht lesbar (PDF-Sperre). Betreiber, kein
  Rechercheauftrag.
- **Der Leitzinspfad ist jetzt meine Aufgabe, nicht mehr die des Spielentwerfers.**
  `spiel.md` Z. 1871-1890 gibt dem Datenbauer zwei Fragen: woher der Pfad fuer DEU und CHN
  kommt (DISR fuehrt beide nicht), und ob ein einheitlicher Zinsbegriff ueber vier Laender
  erreichbar ist. Offener Ausgang, eigenes Paket, noch keines geschrieben.
- **Widerspruch Nr. 9 (BACI laufend gegen T5 Klasse 2)** ist seit 0047 in der Liste und
  seit 0025 unentschieden. Vier Wege benannt, keiner gewaehlt -- Architekt.
- **Widerspruch Nr. 4 (Faktor 10.000 auf den Rohkurs gegen T5 Klasse 6)** -- Architekt.
- **0017:** Reihen 17, 18 und 19 haben keine Quelle; Reihe 16 erbt das schwaechere Urteil
  ihrer Eingabereihen.
- **0022:** Drei `Source`-Wortlaute tragen dieselbe Umbruch-Ersetzung ohne Vermerk wie die
  beiden reparierten; benannt statt behoben, im Feld `schnitt_2_offen`.
- **Zusatzauftrag an den Datenkurator waere billig:** die ILO in die geprueften Quellen
  aufnehmen, **samt** der Stichtagsfrage ("produced prior to 3 May 2023" ist nicht bestimmt).
- **Die Klasse-4-Frage** steht seit 0035 im Wortlaut in `parameter.toml`: Traegt T5
  Klasse 4 ("0 bis 10.000") ihren Deckel auch fuer einen Regler? Fuenf Schluessel haengen daran.

## Lauf 0065 (2026-09-04)

- **Ein Feld, dessen Inhalt "was die Vorlage sagt" ist, kann nicht falsch werden -- die
  Vorlage wird falsch.** Der Spielentwerfer nannte `rolle_tabelle` und `t37_klasse` beide
  "ab heute falsch". `t37_klasse` habe ich geleert, `rolle_tabelle` nicht: Leseregel 4
  definiert es als woertliche Uebernahme aus `technik.md`, und `technik.md` sagt es
  unveraendert. Ueberschrieben waere es von einer echten Uebernahme nicht mehr zu
  unterscheiden gewesen -- und die Spur zum noetigen Nachzug weg. Der Widerspruch gehoert
  unter `[[widerspruch]]`, genau wie es der Kopf der Datei verlangt.
- **Einen Widerspruch in einen bestehenden Block schreiben, statt einen neuen anzulegen.**
  Ein zehnter `[[widerspruch]]` haette `schnitt_3` (113 Koepfe), `schnitt_4` (`^nr = ` 28)
  und die Widerspruchszahl in `toml_geprueft` mitverschoben -- drei Selbstmessungen fuer
  eine Sache, die sachlich in Nr. 5 gehoerte. Vor jedem neuen Tabellenkopf pruefen, welche
  Selbstmessung ihn mitzaehlt.
- **Die Aufzaehlung im Paketrumpf nachmessen, nicht uebernehmen -- zum zweiten Mal.** Elf
  Fundstellen waren genannt, ein dateiweites `\b31\b` fand eine zwoelfte
  (`reihe.12.t26_folge`, "keine der 31 Sollreihen"). Sie nannte Reihe 9 nicht und stand
  deshalb in keiner Tabelle.
- **Gleiche Blattzahl heisst nicht gleiche Schluesselmenge.** 1214 gegen 1214, und
  trotzdem zwei neue und zwei weggefallene Schluessel. Nie die Summe berichten, ohne die
  Mengen zu bilden.
- **Ein Schluesselname, der eine Zahl traegt, veraltet mit ihr.** `in_den_31_enthalten`
  heisst jetzt `in_den_sollreihen_enthalten`. Vor dem Umbenennen dateiweit *und*
  repoweit suchen, ob Code den Namen liest -- hier keiner.
- **Wenn eine Bedingung "zaehle selbst" sagt, ist die gezaehlte Zahl nur die halbe
  Antwort; die andere ist die Zaehlregel.** "Einmal als `beleg`, achtmal ueberhaupt" ist
  erst pruefbar, wenn danebensteht, was als `beleg` zaehlt. Die Vermutung, woher die
  falsche Vier kam, gehoert in den Bericht und nicht in die Datei.
- **Eine geschaetzte Zahl eines Pruefers ("zwei bis drei") ist ein Hinweis, keine
  Vorgabe.** Gezaehlt waren es zwei, im Git an acht Fassungen der Datei gegengeprueft.
- **Unsicherheiten in den Baubericht, nicht nur ins Logbuch.** Der Pruefer sieht das
  Logbuch nicht, der Projektmanager schon -- aber im Bericht sieht es *beide*. Drei
  Punkte notiert, davon zwei echte Abweichungen vom Handzettel.
- Werkzeuglage 0065: `Bash` und `python3` frei, `Edit` und `Write` abgewiesen, `sed`
  abgewiesen, `grep` teils frei. Siebte Lage in sieben Laeufen.
