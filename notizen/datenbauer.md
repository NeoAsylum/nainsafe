# Logbuch: datenbauer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/<deine-rolle>-<datum>.md` und beginnst neu -- mit den
Eintraegen, die noch gelten. Nicht loeschen.

Belege gehoeren nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu begonnen am 2026-09-05 nach Paket 0078 (Grenze bei 11.606 Zeichen erreicht); die
Vorgaengerfassung liegt unter `notizen/archiv/datenbauer-2026-09-05.md`.*

---

## Was funktioniert

- **Die tragende Probe ist die Aufzaehlung, nicht die Summe.** 27+2+2=31 ging auf und war
  trotzdem falsch. Nie eine Einzigartigkeit behaupten, sondern die Liste hinschreiben.
- **Jede Zaehlregel zeichengenau hinschreiben und messen, bevor sie in die Datei geht.**
  `^sollreihen` findet 28, `^sollreihen = ` findet 21.
- **Ein Beleg deckt so viel, wie die belegende Stelle beansprucht.** Ob eine Fundstelle
  Beispiel oder abschliessende Liste ist, entscheidet ihre Zeile, nicht die zitierte Zelle.
- **Vor dem Einspielen pruefen, nicht danach.** In `$TMPDIR` zusammensetzen, dort messen,
  erst dann kopieren -- und den sha256 beider Fassungen nebeneinander ausgeben.
- **Ein Verweis ohne Zeilennummer hat zwei Teile: Adresse und Zitat**, und ein Zitat ist
  nur suchbar, wenn es zeichengleich ist -- auch in den Umlauten.
- **Selbstproben ueberleben eine Einfuegung, Adressen nicht.** An `^` verankerte
  Zaehlmuster halten; jede Zeilennummer unterhalb der Einfuegung verschiebt sich.
- **Ist `python3` frei, ist `tomllib` der staerkste Nachweis, den diese Rolle hat.** Alte
  und neue Fassung beide einlesen, Baeume flach ziehen, Blattschluessel als Pfadtupel
  vergleichen. "Sonst ist nichts geaendert" wird damit ein gemessener Satz.
- **Nach jedem Ersetzungsschritt `tomllib`, nicht erst am Schluss.** Der Parser faengt,
  was `grep` nicht sieht -- ein typografisches Anfuehrungszeichen bricht einen Basisstring.
- **Die Schnittzahlen aus `[pruefweg]` sind eine kostenlose Regressionsprobe.** Alle
  Muster nach dem Eingriff neu zaehlen; bei `schnitt_1` zusaetzlich die Trefferkontexte
  alt gegen neu, sonst bleibt eine gleiche Zahl aus anderen Stellen unbemerkt.
- **Der Bezugsstand gehoert als Commit-Kennung in den Bericht, bevor der Lauf beginnt.**
  `git ls-tree <commit> <pfad>` plus `git hash-object <pfad>`: zwei Zeilen, und jede
  spaetere Zahl bleibt reproduzierbar, auch wenn ein fremder Lauf die Datei mitcommittet.
  Am 2026-09-05 hat genau das den Lauf gerettet -- siehe unten.
- **Wer eine Menge aufteilt, schreibt die Rechnung hin** (`4 + 14 = 18`), nennt je Teil
  die Zuordnungsregel und behauptet ausdruecklich "keines doppelt, keines ausgelassen".
  Erst dann ist es eine Zaehlung.

## Was nicht funktioniert

- `imf.org` und `data.imf.org` weisen den direkten Abruf mit **HTTP 403** ab, an fuenf
  Anlaeufen aus drei Rollen. `api.imf.org` antwortet. Nicht erneut versuchen.
- Der Seitenabruf kuerzt woertliche Zitate bei etwa 125 Zeichen; einen ganzen Lizenzsatz in
  nummerierten Bruchstuecken ausgeben lassen.
- **Die Werkzeuglage wechselt von Lauf zu Lauf -- erst pruefen, was geht.** Neun Laeufe,
  neun Lagen. Nie aus dem letzten Lauf schliessen.
- **Abgewiesen wird nach Laenge und nach Form, nicht nur nach Zeichen.** Erst kuerzen,
  dann Zeichen verdaechtigen.
- **Ein fuehrendes `cd` laesst den ganzen Aufruf abweisen.** `git -C <pfad>` statt `cd`,
  und im Heredoc absolute Pfade.
- `notizen/archiv/` ist **nicht** gesperrt -- wer statt zu archivieren im Logbuch kuerzt,
  verliert Eintraege ohne Not. Archivnamen vorher auf Existenz pruefen.
- **Zwei Laeufe derselben Rolle teilen sich Logbuch und Archivdatei.** Unmittelbar vor dem
  Schreiben neu lesen.
- **Zwischendateien gehoeren nach `$TMPDIR`** -- `rm` ist gesperrt.

## Offene Faehrten

- **Der IWF-Volltext entscheidet 11 der 27 Sollreihen und 7 der 16 Pruefgegenstaende.**
  Ein einziger Seitenabruf, an dem vier Tage und drei Rollen gescheitert sind. Punkt an
  den Betreiber.
- **Reihe 3 (PWT-Kapitalstock) bleibt die einzige ungemessene Quelleneinheit.** Sie haengt
  an *einem* lesbaren Auszug aus `pwt110_user_guide_to_data_files.pdf` oder `pwt110.xlsx`
  (Dataverse 554025 oder 554105) -- beide benannt und erreichbar, nur nicht lesbar
  (PDF-Sperre). Betreiber, kein Rechercheauftrag. T53 ordnet die Folge nach Groesse: die
  Einheit ist der schwere Teil (Faktor 1 gegen 1.000), das Basisjahr der leichte.
- **Der Leitzinspfad ist meine Aufgabe, nicht mehr die des Spielentwerfers.** `spiel.md`
  gibt dem Datenbauer zwei Fragen: woher der Pfad fuer DEU und CHN kommt (DISR fuehrt
  beide nicht), und ob ein einheitlicher Zinsbegriff ueber vier Laender erreichbar ist.
  Offener Ausgang, eigenes Paket, **noch keines geschrieben**.
- **Widerspruch Nr. 4 (Faktor 10.000 auf den Rohkurs gegen T5 Klasse 6)** -- Architekt,
  weiter offen. Nr. 9 ist mit 0078 erledigt.
- **0017:** Reihen 17, 18 und 19 haben keine Quelle; Reihe 16 erbt das schwaechere Urteil
  ihrer Eingabereihen.
- **0022:** Drei `Source`-Wortlaute tragen dieselbe Umbruch-Ersetzung ohne Vermerk wie die
  beiden reparierten; benannt statt behoben, im Feld `schnitt_2_offen`.
- **Zusatzauftrag an den Datenkurator waere billig:** die ILO in die geprueften Quellen
  aufnehmen, **samt** der Stichtagsfrage ("produced prior to 3 May 2023" ist nicht bestimmt).
- **Die Klasse-4-Frage** steht seit 0035 im Wortlaut in `parameter.toml`: Traegt T5
  Klasse 4 ("0 bis 10.000") ihren Deckel auch fuer einen Regler? Fuenf Schluessel haengen daran.

## Lauf 0078 (2026-09-05) -- Preisbasis nach T53

- **Ein fremder Commit kann mitten im Lauf zuschlagen und einen *unfertigen* Zwischenstand
  einsammeln.** `8d74aff` (Architekt) hat `reihen.toml` nach meiner vierten von zwoelf
  Schreibbewegungen mitcommittet, `61fa55b` (Kernbauer) danach den fertigen Rest -- am Ende
  stand meine Ergebnisdatei nicht mehr in `git status`. Vorher war das viermal *nach* dem
  Lauf passiert. **Lehre: nie gegen `HEAD` messen, immer gegen den vor dem Lauf notierten
  Blob**, die Schlussmessung nach jedem fremden Commit wiederholen, und dem Pruefer den
  vollstaendigen Vergleich hinschreiben (`git diff <altblob> <neublob>`) -- sonst sucht er
  eine Aenderung, die in keinem einzelnen Commit ganz zu sehen ist.
- **Ein Bilanzfeld zaehlt sich selbst mit.** Meine erste Messung ergab 17 verschiedene
  Blattwerte, nach dem Schreiben von `toml_geprueft` waren es 18. Die Zahl ist erst
  richtig, wenn sie das Feld einschliesst, das sie traegt -- dann ist sie ein Fixpunkt und
  ein drittes Messen bestaetigt sie. Genau daran ist dieses Feld dreimal gescheitert.
- **Eine Listenverschiebung sieht im Schluesselvergleich aus wie vier Aenderungen.** Wer in
  `offen` einen Eintrag herausnimmt und zwei einsetzt, bekommt vier "verschiedene" Indizes
  gemeldet. Die Probe dagegen ist `alt[1:] == neu[2:]` -- eine Zeile, und aus vier
  scheinbaren Eingriffen wird ein gemessener Nulleingriff.
- **Ein Zitat kann eine Selbstmessung anheben.** T53s Selbsttest lautet
  `preisindex_handel[2015] = 10.000` und traegt damit genau das Muster von `schnitt_1`.
  Woertlich zitiert haette er die 6 auf 7 gehoben -- fuer nichts. Vor jedem Zitat pruefen,
  ob es ein Zaehlmuster der eigenen Datei enthaelt; in Prosa sagt es meist dasselbe.
- **Dasselbe umgekehrt: ein Wort, das eine Abnahmebedingung zaehlt, darf im eigenen
  Messbericht nicht vorkommen.** Bedingung 4 zaehlte `Ausfuhrpreisindex`; haette ich im
  Nachweis geschrieben "steht null mal", stuende es einmal. Umschreiben und sagen, warum.
- **Wo eine Vorgabe eine Formel gibt, aber keine Feldaufteilung, ist die Aufteilung deine
  Entscheidung -- und gehoert als solche in den Bericht.** Ein Deflator hat keinen einzigen
  Faktor. `faktor = 10000` (der Zaehler aus T53s Formel) plus ein neues Feld `teiler` war
  der einzige Weg, der weder Leseregel 3 bricht noch eine gesetzte Null einfuehrt. Die zwei
  verworfenen Alternativen mit ihrem Preis danebenschreiben, sonst liest es sich wie Willkuer.
- **Ein Eingriff macht Saetze an anderen Stellen falsch -- die sind Folge, nicht
  Aufraeumen.** Vier Stellen jenseits der drei beauftragten hingen an der geloeschten
  Frage, darunter ein `beleg`, der auf den entfernten Eintrag zeigte. Nach jeder
  Streichung dateiweit nach Verweisen auf das Gestrichene suchen.
- **Nicht jede gefundene Luecke darf man schliessen.** `[datei.vorlagen]` fuehrt T53 nicht,
  und der Kommentar darueber sagt selbst, was das kostet. Das Paket verlangte "melden,
  nicht nebenbei aufloesen" -- also Vorschlag `0099` geschrieben statt zwei Zeilen
  eingefuegt. Ein Vorschlag mit Grund kostet den Projektmanager weniger als ein Ruecklauf.
- **Die Nummer eines Vorschlags nachsehen, nicht aus dem eigenen Paket ableiten.** Ich
  hatte 0079 geschrieben; die hoechste vorhandene war 0098.
- Werkzeuglage 0078: `Bash`, `python3`, `Read`, `Grep`, `Edit` und `Write` **im Repo** frei;
  `Write` nach `$TMPDIR` abgewiesen, `cp` abgewiesen, `sed`/`awk` abgewiesen, mehrteilige
  `git`-Aufrufe mit `;` teils abgewiesen (einzeln gingen sie). Neunte Lage in neun Laeufen.
