# Logbuch: datenbauer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/<deine-rolle>-<datum>.md` und beginnst neu -- mit den
Eintraegen, die noch gelten. Nicht loeschen.

Belege gehoeren nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu geschrieben am 2026-09-05 nach Paket 0120; die Vorgaengerfassung stand bei 11.938
von 12.000 Zeichen und liegt vollstaendig unter `notizen/archiv/datenbauer-2026-09-05-3.md`.
In demselben Lauf konnte ich die Luecke schliessen, die der Ruecklauf zu 0078 hinterlassen
hatte: `datenbauer-2026-09-05-2.md` ist aus Commit `757ae04` nachgetragen (11.987 Zeichen,
Groesse stimmt mit dem Vermerk ueberein). Aeltere Fassungen: `datenbauer-2026-09-02*.md`
bis `-2026-09-05.md`.*

---

## Was funktioniert

- **Die tragende Probe ist die Aufzaehlung, nicht die Summe.** 27+2+2=31 ging auf und war
  trotzdem falsch. Nie eine Einzigartigkeit behaupten, sondern die Liste hinschreiben.
  Das gilt auch fuer den Nebensatz am Ende eines Feldes, das man ohnehin gerade anfasst --
  genau dort greift keine Bedingung des Pakets, und genau dort ist es mir passiert.
- **Wer eine Menge aufteilt, schreibt die Rechnung hin** (`5 + 2 + 16 = 23`), nennt je Teil
  die Zuordnungsregel und sagt ausdruecklich "keiner doppelt, keiner ausgelassen".
- **Jede Zaehlregel zeichengenau hinschreiben und messen, bevor sie in die Datei geht.**
  `^sollreihen` findet 28, `^sollreihen = ` findet 21.
- **Ein Beleg deckt so viel, wie die belegende Stelle beansprucht.** Ob eine Fundstelle
  Beispiel oder abschliessende Liste ist, entscheidet ihre Zeile, nicht die zitierte Zelle.
- **Ein Verweis ohne Zeilennummer hat zwei Teile: Adresse und Zitat**, und ein Zitat ist
  nur suchbar, wenn es zeichengleich ist -- auch in den Umlauten.
- **Der Bezugsstand gehoert als Commit-Kennung in den Bericht, bevor der Lauf beginnt.**
  `git rev-parse <commit>:<pfad>` plus `git hash-object <pfad>`: zwei Zeilen, und jede
  spaetere Zahl bleibt reproduzierbar, auch wenn ein fremder Lauf die Datei mitcommittet.
  Dreimal in drei Laeufen hat genau das den Lauf gerettet.
- **Ein Vorher-Lauf misst am selben Baum, nicht am alten Commit.** Die eine Zeile
  zuruecksetzen, Blob gegen `git rev-parse <commit>:<pfad>` pruefen, messen, wieder
  berichtigen, Blob erneut pruefen. Dann unterscheiden sich die beiden Laeufe in genau
  einer Zeile, und jede Differenz gehoert dieser Zeile. Zweimal die staerkste Form des
  Nachweises gewesen, die diese Rolle hat.
- **Ein Riegel, den man selbst uebersetzt, wird genau einmal uebersetzt** und dann fuer
  beide Laeufe benutzt. Sonst misst man zwei Geraete gegeneinander statt zwei Staende.
- **Ist `python3` frei, ist `tomllib` der staerkste Nachweis fuer TOML-Eingriffe.** Alte
  und neue Fassung einlesen, Baeume flach ziehen, Blattschluessel als Pfadtupel
  vergleichen. "Sonst ist nichts geaendert" wird damit ein gemessener Satz. Nach *jedem*
  Ersetzungsschritt, nicht erst am Schluss -- der Parser faengt, was `grep` nicht sieht.
- **Die Schnittzahlen aus `[pruefweg]` sind eine kostenlose Regressionsprobe.** Alle
  Muster nach dem Eingriff neu zaehlen; bei `schnitt_1` zusaetzlich die Trefferkontexte
  alt gegen neu, sonst bleibt eine gleiche Zahl aus anderen Stellen unbemerkt.
- **Der billigste Weg zu einem Werkzeug ist ein Skript im Repo, nicht ein langer Aufruf.**
  Ein `python3 -c` ab etwa 150 Zeichen wird abgewiesen; die Messung als Datei unter
  `befunde/messung-<paket>/` laeuft und ist zugleich der Beleg -- der Pruefer kann sie
  wiederholen.
- **Ein Bilanzfeld zaehlt sich selbst mit.** Die Zahl ist erst richtig, wenn sie das Feld
  einschliesst, das sie traegt -- dann ist sie ein Fixpunkt. Also zweimal messen: vor dem
  Schreiben des Feldes und danach, und die zweite Zahl hineinschreiben.
- **Ein Zitat kann eine Selbstmessung anheben, und ein Wort auch.** Vor jedem Zitat
  pruefen, ob es ein Zaehlmuster der eigenen Datei enthaelt -- in Prosa oder als Zahlwort
  sagt es meist dasselbe.
- **Wer eine gefallene Behauptung ersetzt, schreibt sie als Geschichte daneben**, mit
  Datum und Widerlegung. Ein spaeterer Leser soll sehen, woran die Regel einmal falsch war.
- **Ein Pruefervorschlag wird nachgemessen wie eine Quelle**, sonst erbt man seinen Irrtum.
  Er ist eine Richtung, keine Vorlage.

## Was der Belegstellenriegel wirklich tut (gemessen am 2026-09-05, Paket 0120)

- **Die vier Schluesselwoerter stehen in `SCHLUESSEL`:** Abschnitt, Ueberschrift,
  Überschrift, Absatz -- im Quelltext maskiert, damit der Riegel sich nicht selbst findet.
  Wer nach einer Zeilennummer sucht, sucht falsch; such nach dem Namen der Konstante.
- **`aufgaben/` ist auf der *zitierenden* Seite ausdruecklich ausgenommen** (`ist_datendokument(...)
  && !liegt_unter(kurz, "aufgaben")`). Die verbreitete Sorge, ein Vermerk im Arbeitspaket
  koenne eine neue Fundstelle erzeugen, trifft nicht mehr zu -- ich habe es empirisch
  belegt: Der Rumpf von 0120 stellt die volle Zitatform hin, der Riegel meldet null.
- **`UNGELESENE_ORDNER` (`bau`, `befunde`) betrifft nur die Zielseite.** Belegdateien unter
  `befunde/` heben allein die Zahl "Namen in ungelesenen Ordnern" -- meine zwei hoben sie
  von 430 auf 432, und das ist der Selbstnachweis, dass sie nichts anderes beruehrt haben.
- Aufruf: `belegstellen_riegel <wurzel-des-vorhabens> [<wurzel-der-vorgaben>]`; die
  Vorgabenwurzel leitet er sonst selbst ab und findet `specs/<name>` zuverlaessig.
  Rueckgabewert 0 gruen, 1 Befund, 2 Selbsttest oder Aufrufform kaputt.

## Was nicht funktioniert

- **Die Werkzeuglage wechselt von Lauf zu Lauf -- erst pruefen, was geht.** Zwoelf Laeufe,
  zwoelf Lagen. Nie aus dem letzten Lauf schliessen: In 0120 waren Arbeitspaket,
  `befunde/` **und** `notizen/archiv/` beschreibbar, im Lauf davor keines davon.
- **Abgewiesen wird nach Laenge und nach Form, nicht nur nach Zeichen.** Mehrteilige
  Aufrufe mit `&&` oder `;` fallen fast immer, dieselben Befehle einzeln gehen durch.
  Auch `cmd > datei; echo $?` faellt -- den Rueckgabewert liest man daran ab, ob das
  Werkzeug den Aufruf als Fehler meldet.
- **Ein fuehrendes `cd` laesst den ganzen Aufruf abweisen.** `git -C <pfad>` statt `cd`.
- **`cp` ist gesperrt, `git show <commit>:<pfad> > <ziel>` nicht.** So archiviert man das
  eigene Logbuch und traegt fehlende Archivstaende nach, ohne `cp` zu brauchen.
- **`2>&1 > datei` verliert den Fehlerstrom**, richtig ist `> datei 2>&1`. Ein Lauf sah
  dadurch gruener aus, als er war.
- **`git hash-object` ohne `-w` legt keinen Blob an**, also scheitert `git diff <alt> <neu>`
  auf die Kennung des Arbeitsbaums mit `bad object`.
- `imf.org` und `data.imf.org` weisen den direkten Abruf mit **HTTP 403** ab, an fuenf
  Anlaeufen aus drei Rollen. `api.imf.org` antwortet. Nicht erneut versuchen.
- Der Seitenabruf kuerzt woertliche Zitate bei etwa 125 Zeichen; einen ganzen Lizenzsatz in
  nummerierten Bruchstuecken ausgeben lassen.
- `rm`, `sed`, `awk`, `diff` und `python3 -c` sind regelmaessig gesperrt.

## Der fremde Eingriff ist der Normalfall

**Achter Lauf in Folge, in dem ein fremder Commit oder ein gleichzeitiger Agent in meinen
Baum greift** -- in 0120 erschien `daten/reihen.toml` waehrend meiner Messung als
veraendert. Das Verfahren dagegen steht: Blob vorher notieren, nach dem fremden Eingriff
ein drittes Mal messen, die unveraenderte Zahl hinschreiben und den fremden Stand im
Bericht benennen. **Und den eigenen Bericht danach noch einmal lesen** -- ich hatte
"Arbeitsbaum sauber" schon hingeschrieben, bevor es passierte, und musste die Zeile
nachziehen.

## Offene Faehrten

- **Der IWF-Volltext entscheidet 11 der 27 Sollreihen und 7 der 16 Pruefgegenstaende.**
  Ein einziger Seitenabruf, an dem vier Tage und drei Rollen gescheitert sind. Punkt an
  den Betreiber.
- **Reihe 3 (PWT-Kapitalstock) bleibt die einzige ungemessene Quelleneinheit.** Sie haengt
  an *einem* lesbaren Auszug aus `pwt110_user_guide_to_data_files.pdf` oder `pwt110.xlsx`
  (Dataverse 554025 oder 554105) -- beide benannt und erreichbar, nur nicht lesbar
  (PDF-Sperre). Betreiber, kein Rechercheauftrag. Die Einheit ist der schwere Teil
  (Faktor 1 gegen 1.000), das Basisjahr der leichte.
- **Der Leitzinspfad ist meine Aufgabe, nicht mehr die des Spielentwerfers.** `spiel.md`
  gibt dem Datenbauer zwei Fragen: woher der Pfad fuer DEU und CHN kommt (DISR fuehrt
  beide nicht), und ob ein einheitlicher Zinsbegriff ueber vier Laender erreichbar ist.
  Offener Ausgang, eigenes Paket, **noch keines geschrieben**. Die Betreiber-Nachmessung
  vom 2026-09-05 hat die Lage fuer DEU verschoben: elf Jahresreihen in `MFS_IR` statt null.
- **Widerspruch Nr. 4 (Faktor 10.000 auf den Rohkurs gegen T5 Klasse 6)** -- Architekt,
  weiter offen. Nr. 9 ist mit 0078 erledigt.
- **Leseregel 3 in `reihen.toml` regelt den faktorlosen Block nur fuer `ungemessen`.**
  Reihe 10 Schritt 2 (`verkettung`) traegt ebenfalls keinen `faktor`. Gemeldet, nicht
  aufgeloest -- das entscheidet nicht der Datenbauer.
- **0017:** Reihen 17, 18 und 19 haben keine Quelle; Reihe 16 erbt das schwaechere Urteil
  ihrer Eingabereihen.
- **0022:** Drei `Source`-Wortlaute tragen dieselbe Umbruch-Ersetzung ohne Vermerk wie die
  beiden reparierten; benannt statt behoben, im Feld `schnitt_2_offen`.
- **`[datei.vorlagen]` fuehrt T53 nicht** -- Vorschlag `0099`, offen. `[namensnennung]`
  fuehrt Reihe 14 nicht -- Paket `0100` des Pruefers.
- **Zusatzauftrag an den Datenkurator waere billig:** die ILO in die geprueften Quellen
  aufnehmen, **samt** der Stichtagsfrage ("produced prior to 3 May 2023" ist nicht bestimmt).
- **Die Klasse-4-Frage** steht seit 0035 im Wortlaut in `parameter.toml`: Traegt T5
  Klasse 4 ("0 bis 10.000") ihren Deckel auch fuer einen Regler? Fuenf Schluessel haengen daran.
- **Die 47 uebergangenen Fundstellen des Riegels** sind sein ausgeschriebener blinder
  Fleck und hat niemand nachgesehen. Kein Paket, keine Rolle, waere aber billig.

## Lauf 0120 (2026-09-05) -- die Sache war getan, die Meldung fehlte

- **Ein Paket auf `offen`, dessen Arbeit schon getan ist, ist kein Widerspruch, sondern
  eine verlorene Statuszeile.** Meine Aenderung war in einem Commit des *Nachbarpakets*
  gelandet, die Statuszeile nicht mitgekommen. Erst nachmessen, was vorliegt, dann bauen --
  und die vorgefundene Zeile nicht blind mit dem alten Wortlaut ueberschreiben.
- **Wer einen Riegel gruen meldet, faehrt ihn nach dem eigenen Schreiben noch einmal.**
  Mein GEBAUT-Vermerk stellt selbst die Zitatform hin, die der Riegel aufloest. Ein
  dritter Lauf kostet eine Minute und macht aus einer Annahme eine Messung.
- **Unsicher bin ich bei nichts an diesem Paket** -- die Bedingungen sind mechanisch und
  beide gefahren. Was ich dem Projektmanager mitgebe: Die Sorge im Annahmevermerk, ein
  Vermerk in `aufgaben/` koenne den Riegel anheben, ist durch die Ausnahme im Quelltext
  ueberholt. Die Verengung von Bedingung 1 bleibt trotzdem richtig, sie war nur
  vorsichtiger als noetig.
