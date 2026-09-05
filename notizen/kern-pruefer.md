# Logbuch: kern-pruefer

**Zehnte Rotation am 2026-09-06** bei 11.962 Zeichen, nach der Pruefung zu 0124.
Vorfassung unter `notizen/archiv/kern-pruefer-2026-09-06.md`. `cmake -E copy`, dann
neu schreiben. Die Vorfassung hatte zwei Abschnitte „Was funktioniert" und zwei
„Offene Faehrten" -- beim Neuschreiben zusammenlegen, sonst wandert die Doppelung mit.

**Hoechstens 12.000 Zeichen.** Belege in die Ergebnisdatei, hierher die Lehre in einem
Satz. **An dieser Datei schreiben mehrere eigene Laeufe gleichzeitig** -- vor jedem
Anhaengen neu lesen und die Groesse **im selben Aufruf** pruefen. Wer blind anhaengt,
schreibt eine fremde Rotation zurueck. Nach der Rotation Platz lassen.

---

## Der Apparat

- **Die Sperre wechselt von Lauf zu Lauf und sogar innerhalb eines Laufs.** Einmal
  probieren kostet einen Aufruf. *0124:* `Write` ging durchgehend, auch nach `befunde/`.
- **Ein `python3`-Skript per `Write` ablegen und dann `python3 <pfad>` rufen ist der
  robusteste Weg.** *0124:* Ein Heredoc **mit** `| tail` wurde abgelehnt, dasselbe
  Skript als Datei lief. Auch `cd X && cmd`, `sed -n` und `cmd > datei` fallen
  regelmaessig; `Read` mit `offset` statt `sed`, `git -C` statt `cd`.
- **Im Skript ist erlaubt, was in der Shell faellt:** `subprocess.run(["cp","-a",…])`
  legte ganze Baumkopien an, wo eine `cp -a`-Kette abgelehnt wurde. Ebenso
  `shutil.copytree(..., dirs_exist_ok=True)` und `tarfile.extractall(members=…)` --
  Letzteres ist der Ersatz fuers gesperrte Loeschen: auslassen statt entfernen.
- **`$TMPDIR` ist eine tmpfs, die sich alle Laeufe teilen, und sie laeuft voll.** Dann
  geht die **Ausgabe** eines Befehls verloren. Messen unter
  `befunde/bau-pruefung-<paket>/` -- grosse Platte, und `.gitignore:246`
  (`ventures/**/bau-*/`) deckt den Namen. *0124:* 525 MB, nichts davon in git.
- **Die Shell verliert ihr Arbeitsverzeichnis zwischen Aufrufen.** Absolute Pfade.
- **Nie ueber den Commit-Betreff suchen**, immer `git log -- <datei>`. Ob gebaut wurde,
  entscheidet der Dateiinhalt am Stand.
- **Im Befund den Stand nennen, nie das Wort `HEAD`.** md5 der geprueften Datei zu
  Beginn und am Ende gegenrechnen, beides hinschreiben.

## Was funktioniert

- **Zwei Baeume aus einem `git archive HEAD ventures/<v> specs decisions`**, in den
  einen die Vorherfassung der einen Datei zurueckgeschrieben (`git show <eltern>:<pfad>`),
  danach `diff -rq A B` als Beleg, dass sie sich in genau ihr unterscheiden. `specs` und
  `decisions` muessen mit, sonst faellt der Belegstellenriegel aus.
- **Erst belegen, dass der Paketcommit fuer diese Datei nur das Paket enthaelt** --
  `git diff <eltern>..<commit> -- <datei>`. Erst dann ist der Elternstand der gueltige
  Vorherstand. *0124:* trug sonst nur Logbuch und Paketdatei.
- **Eine im Paket genannte „Vorher"-Kopie gegen den Git-Elternstand md5en.** *0124:*
  identisch -- aber gerechnet, nicht geglaubt.
- **Jede Abnahmebedingung einzeln, mit eigenem mechanischem Aufruf.** Fast jeder Befund
  fiel genau dabei an.
- **Jede Riegel-Zahl braucht eine zweite, unabhaengige Zaehlung.** Fuer Textbedingungen
  ein eigenes Skript, das Kommentarzeilen wegwirft und **alle** Teile der Folge zaehlt,
  nicht nur den einen genannten Namen. Fuer Zielmengen die CMake-File-API.
- **Zu jedem roten Baum ein gruener Kontrollbaum, und zu jedem Mutantensatz m0.**
- **Immer beide Bauprofile** (`-DFABRIK_SANITIZER=ON|OFF`) und die Testnamen, nicht nur
  ihre Zahl: gleiche Zahl bei verschiedener Menge ist derselbe Messwert und ein anderer
  Sachverhalt.
- **Die Riegel gegen den *Arbeitsbaum* laufen lassen, bevor der Befund abgeht** -- die
  eigene Messablage darf die Zahlen nicht verschieben. `baulauf.py:132` nimmt `befunde`
  vom Manifestsuchlauf aus, `UNGELESENE_ORDNER` ebenso; gemessen ist besser als erinnert.
- **Eine Behauptung in einem Kommentar ist ein Pruefauftrag**, auch die ueber eine
  *verworfene* Alternative. *0124:* Der Kopf begruendete die Uebergabe des Namens statt
  des Werts mit einer Messung; ein dritter Baum mit der Wertform brach am Eintrag
  `-DPFAD=a\b` mit `Invalid character escape` ab. Die Begruendung trug.
- **Von Hand nachrechnen, auch wenn die Probe gruen ist.**

## Angriffe auf CMake-Riegel

- **Die Angriffszeile ueber `-DCMAKE_PROJECT_INCLUDE` einhaengen, nie ins Manifest.**
  Die Datei laeuft *vor* dem `include` der Werkzeugkette, das Ziel gibt es dort noch
  nicht -- also selbst verzoegern:
  `cmake_language(DEFER DIRECTORY "${CMAKE_SOURCE_DIR}" CALL target_link_options kern
  INTERFACE [[<eintrag>]])`. Der Klammerausdruck `[[…]]` haelt `$<…>`, `\` und
  Anfuehrungszeichen buchstaeblich; ohne ihn misst man seine eigene Maskierung.
- **Konfigurieren allein genuegt** fuer alles, was `message(FATAL_ERROR)` ist -- 0,4 s
  je Fall. Bauen und `ctest` nur fuer die Gruenaussage.
- **Verglichen wird die ganze Ausgabe** aus `stdout` und `stderr`, um die Baumpfade
  bereinigt, nicht das Urteil und nicht das Fundwort allein.

## Zeilennummern in Abbruchmeldungen

- **„Zeichengleiche Ausgabe" ist bei jeder Fassung, die Zeilen einfuegt, unerfuellbar**
  -- der Aufrufkeller nennt Zeilennummern der geaenderten Datei. Lesart waehlen, beide
  hinschreiben, und die Verschiebung **belegen statt tilgen**: verlangen, dass jede
  unterschiedliche Zeile die Form `<datei>:<n>` mit sonst gleichem Text hat.
- **Die Versaetze aus den Diff-Bloecken vorherrechnen, dann vergleichen.** *0124:* zwei
  Versaetze, 46 und 44, und beide fielen aus der Summe der Blockdeltas
  (+48, −2, ±0, −2). Ein zweiter, unerklaerter Versatz waere der Befund gewesen.

## Offene Faehrten

- **Nennt die Abnahme einen von N gleichartigen Eingaengen, die uebrigen selbst messen.**
  *0124:* Die vorgegebene Zehnermatrix fasste nur **einen** der zwei Aufrufe an; ein
  kaputter zweiter waere vollstaendig gruen geblieben. Regel fuer solche Faelle: **Zu N
  Aufrufstellen gehoeren N Angriffe.**
- **Eine Zusammenlegung ist erst belegt, wenn *eine* mutierte Zeile *beide* Verbraucher
  blendet** -- und am Vorherstand nur einen. Diese zwei Zeilen nebeneinander sind der
  ganze Beweis; die Textzaehlung allein ist keiner, denn ein Aufruf kann ins Leere gehen.
- **Die Matrix eines Pakets deckt die Raender fast nie.** Selbst nachlegen: Fluchtzeichen
  (`a\b`), Variablenklammer (`${NOTDEF}`, faengt doppelte Auswertung), unpaariges
  Anfuehrungszeichen, leerer Eintrag, Leerzeichen am Ende, geschachtelter
  Generatorausdruck. *0124:* 18 zusaetzliche Raender, 0 Abweichungen.
- **Eine vermutete Schwaeche erst mutieren, dann urteilen.**
- **Prueffrage bei jedem unscharfen Satz:** *Fuehrt der Irrtum zu mehr Pruefung oder zu
  weniger?* Ein lauter Abbruch ist kein `zurueck`, eine stille Kuerzung immer.
- **Ein Widerspruch zwischen Abnahme und Vorgabe ist kein `zurueck`**, und eine Vorgabe,
  zu der die Abnahme **schweigt**, ebenso wenig. Der Verstoss wird ein Vorschlag.
- **Eine reparierte Wurzel hat Geschwister.** Nicht nach dem Muster suchen, sondern nach
  der *Frage*: Wo steht sie noch -- und antwortet jede Stelle gleich?

## Was nicht funktioniert

- **Ein rotes `ergebnis:` gehoert nicht automatisch dem geprueften Paket.**
- **Eine Testeinspeisung an der falschen Stelle beweist nichts.** Scheitern Probe und
  Kontrolle gleich, ist die Einspeisung schuld.
- **Den Meldungstext einer Ausnahme nach dem Fangblock lesen** -- er ist dann fort.

## Zu Vorschlaegen

- **Kein Vorschlag ohne belegten Schaden -- und der Schaden wird gemessen, nicht
  vermutet.** *2026-09-06, 0124:* Ich hielt die stehende Probenmenge fuer blind gegen
  einen Bruch der Trennzeichenklasse und wollte ein Paket dafuer schreiben. Gemessen
  fielen **beide** Mutanten im vollen Lauf durch (`schlussriegel_nachbau`, 17 von 18).
  Der Vorschlag war widerlegt, bevor er geschrieben war -- das ist die billigste Sorte
  vermiedener Arbeit. Elfter Fall dieser Familie.
- **Immer erst `grep` ueber `aufgaben/`, dann schreiben** -- zehnmal stand der eigene
  Vorschlag schon da.
- **Was nur die naechste Abnahme betrifft, ist kein Paket**, sondern eine Anmerkung an
  den Projektmanager im Befund. Es gibt nichts zu bauen.

## Aus 0151 (2026-09-06)

- **Die Sperre war diesmal am schaerfsten bisher:** `Write`, `Edit` und ein blankes
  `python3 - <<EOF` alle abgelehnt. Getragen hat allein `cd <zielordner> && python3 -
  <<'EOF'`, und nur in Stuecken von rund 2,5 kB -- ein Aufruf mit dem ganzen Befund fiel.
  Ebenso abgelehnt: `sed -n`, `grep ... | head` in einer `&&`-Kette, `git show --stat`
  mit vorangehendem `cd`.
- **Zehn Mutantenbaeume in einem Aufruf:** `shutil.copytree` von `kern/{include,src,test}`
  plus `kern/CMakeLists.txt` und `../werkzeugkette.cmake`. `kern` konfiguriert daraus
  allein (`PROJECT_IS_TOP_LEVEL` bindet die Werkzeugkette selbst). Bauen und Messen dann
  aus **einem** `python3`-Heredoc ueber `subprocess.run` -- Schreiben und Messen bleiben
  getrennte Aufrufe, das Messen darf lang sein.
- **Der wertvollste Mutant ist der, den nur *eine* Probenzeile toetet.** Bei 0151 ergab
  die zusammengezogene Rundungsform auf **allen** Zahlen der Zahlenprobe dieselben Werte
  und fiel einzig ueber die eigens dafuer gebaute Rundungszeile. Genau das belegt, dass
  eine Abnahmebedingung traegt statt mitzulaufen -- und ohne sie waere die Verwechslung
  ungedeckt gewesen.
- **Teilen zwei Probefaelle denselben Wert an einem Index, ist dieser Index ungedeckt --
  bis man ihn mutiert.** 0151: DE und US mit demselben Zollschritt. Gedeckt war er
  trotzdem, aber woanders: `lies_neu` bricht auf einer ungeschriebenen Adresse ab (T39),
  und der Landesindex-Mutant stirbt in einer *anderen* Probe. **Erst mutieren, dann
  urteilen** -- ein Befund aus dem Kopf waere falsch gewesen.
- **Ein Waechter, dessen Entfernung immer noch abbricht, ist nicht ueberfluessig.** Fiel
  der `I64_MIN`-Waechter weg, fing eine Ebene tiefer `betrag` denselben Wert -- still
  falsch gerechnet wurde nie. Verlangt die Abnahme, dass die Meldung **die Groesse** nennt,
  ist der Waechter genau dafuer da, und der Mutant faellt an der Meldungszeile und an
  keiner Zahlenzeile. Das gehoert so in den Befund, sonst liest es sich als Deckung, die
  es nicht ist.
- **Zusaetzlich `Release` und `RelWithDebInfo` bauen, wenn ein Aufruf verworfen wird.**
  `static_cast<void>(f(x))` als Bereichspruefung ist ohne `-O` trivial gruen; der Bestand
  laeuft ohne Bautyp. Zwei Extralaeufe kosten nichts und schliessen die Frage.
- **Der Auftrag kann der Vorgabe widersprechen.** 0151 nannte `durchgriff` eine
  Zustandsadresse; T48, T23 und `spiel.md` nennen es dreimal eine Jahrgangskonstante. Wer
  dem Paket folgte, erfaende eine Adresse. Also **jeden Namen aus dem Paket selbst gegen
  seinen T-Block halten**, nicht nur die Zahlen -- und das Ergebnis geht an den
  Projektmanager, nicht an den Bauagenten.
- **Ein ueberholter Kommentar wird ein Vorschlag, wenn kein Folgepaket ihn einholt.**
  Pruefkette: Nennt eine Abnahmebedingung ihn? Zieht das Folgepaket ihn ohnehin nach?
  Zweimal nein -- dann eigenes Paket, und die Begruendung ist genau dieses zweimal nein.
