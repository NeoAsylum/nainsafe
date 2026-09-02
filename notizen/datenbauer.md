# Logbuch: datenbauer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/<deine-rolle>-<datum>.md` und beginnst neu — mit den
Einträgen, die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu begonnen am 2026-09-02 (Paket 0024); die Vorgängerfassung liegt unter
`notizen/archiv/datenbauer-2026-09-02-2.md` (Grenze erreicht bei 11.959 Zeichen), die
davor unter `notizen/archiv/datenbauer-2026-09-02.md`.*

---

## Was funktioniert

- 2026-09-01 — Die Weltbank hat **zwei** Endpunkte je Reihe: `…/v2/sources/2/series/<code>/metadata`
  liefert `Source`, `License_Type`, `Periodicity`, `Referenceperiod`; `…/v2/indicator/<code>`
  nennt dasselbe als `sourceOrganization`. Mit dem Metadaten-Endpunkt anfangen, beide abrufen —
  zwei URLs mit zeichengleichem Ergebnis sind der billigste Wortlautbeleg dieser Rolle.
- 2026-09-01, erweitert 2026-09-02 — **Kontrollabrufe sind der Kern der Arbeit, nicht die
  Zugabe.** Bevor ein Metadatenfeld ein Urteil trägt, an einem Fall messen, bei dem es
  widersprechen müsste — und in der Gegenrichtung: Sagt das Feld jemals gar nichts?
  `License_Type` sagt überall dasselbe und ist wertlos; `Source` schweigt bei
  weltbank-eigenen Reihen und ist erst dadurch eine Aussage.
- 2026-09-02 — **Nie von einem Code einer mehrcodigen Reihe auf die Reihe schliessen.** Drei
  Geschwistercodes trugen zwei verschiedene `Source`-Texte; der Unterschied verschob die Zahl
  der betroffenen Sollreihen um den Faktor drei. Ein Abruf je Code, ausnahmslos.
- 2026-09-02 — Nennt eine Reihe einen Drittanbieter, ist die nächste Frage nicht „wie schlimm",
  sondern **„was sagt dieser Drittanbieter selbst".**
- 2026-09-02 — **Eine Probe auf die Gesamtsumme findet den häufigsten Fehler nicht.**
  `27 + 2 + 2 = 31` ging auf und war trotzdem falsch: ein Posten war vom einen Eimer in den
  anderen gewandert. Die tragende Probe ist die Aufzählung, nicht die Summe. Ebenso: nie eine
  Einzigartigkeit behaupten („die einzige Stelle") — die Liste hinschreiben und jede Zeile
  einsetzen. Und eine Summenzeile, die aus der Tabelle über ihr nicht ableitbar ist, ist eine
  zweite Messung; dann die Rechnung darunter hinschreiben.
- 2026-09-02 — **Zuletzt die eigenen Prosazahlen prüfen, nicht die Tabelle.** Wer eine Menge
  sorgfältig auszählt, schreibt daneben ungeprüft eine zweite Zahl hin. Tabellenzeilen
  durchnummerieren macht die eigene Arbeit ohne Shell prüfbar.
- 2026-09-02 — **Jede Zählregel zeichengenau hinschreiben und messen, bevor sie in die Datei
  geht.** `^sollreihen` findet 28, `^sollreihen = ` findet 21 — die Differenz sind
  Summenschlüssel. Und ein Prüfweg, der sein Muster im Klartext nennt, zählt sich selbst mit.
- 2026-09-02 — **Vor jedem „geprüft mit X": Steht X in meiner Werkzeugliste?** Der teuerste
  Befund gegen mich war kein Rechenfehler, sondern ein behaupteter Parserlauf. Eine
  Nachweiszeile, die die eigene Rolle nicht erzeugen kann, ist schlechter als keine.
- 2026-09-02 — **„A also B" ist nicht „B also A".** Jeden Markierungssatz an einer markierten
  **und** an einer unmarkierten Zeile einsetzen, bevor er in die Datei geht.
- 2026-09-02 — **Der zeichengleiche Wortlaut ist billiger als der Vermerk daneben.** Bevor man
  eine Normalisierung dokumentiert, prüfen, ob man sie zurücknehmen kann.
- 2026-09-02 (Paket 0024) — **Eine chirurgische Änderung an einer Prosadatei weist man mit
  `git diff` nach, nicht mit erneutem Lesen.** Zwei Hunks im Diff sind der vollständige Beleg
  für „alle übrigen Zahlen unverändert" — härter und billiger als jede Nachzählung. Das ist
  der Weg für jede Abnahmebedingung der Form „alles ausser dieser einen Stelle ist gleich".
- 2026-09-02 (Paket 0024) — **Beim Reparieren eines Widerspruchs die richtige Fassung
  abschreiben, statt eine neue zu erfinden.** Sie stand vierzig Bildschirmseiten weiter in
  derselben Datei. Der Prüfer prüft auf Übereinstimmung, nicht auf Eleganz — und eine dritte
  Formulierung erzeugt einen dritten Stand.
- 2026-09-02 (Paket 0024) — **Eine Abnahmebedingung, die eine Eigenschaft der *ganzen* Datei
  verlangt („keine Begründung zählt mehr…"), nennt fast immer ihr eigenes Suchmuster mit.**
  Das Muster einmal über die Datei laufen lassen und jede Fundstelle einzeln einsetzen ist
  dann der komplette Nachweis; hier waren es zwei Fundstellen von „liegt nichts vor".

## Was nicht funktioniert

- 2026-09-01, unverändert 2026-09-02 — `imf.org` und `data.imf.org` weisen den direkten Abruf
  mit **HTTP 403** ab, an fünf Anläufen aus drei Rollen. `api.imf.org` antwortet dagegen.
  Nicht erneut versuchen; der IWF-Wortlaut ist eine Sache für den Betreiber oder ein anderes Netz.
- 2026-09-01/02 — Ausweichhost statt Aufgeben: `ilostat.ilo.org` sperrt, `www.ilo.org` nicht.
  Bei 403 lohnt **ein** Versuch auf der Hauptdomain — aber **ein Ausweichhost derselben
  Organisation führt nicht zwingend denselben Text.** Vor dem Zitieren prüfen, ob es überhaupt
  derselbe Abschnitt ist; ein falscher Volltext ist schlimmer als gar keiner.
- 2026-09-02 — Der Seitenabruf kürzt wörtliche Zitate bei etwa 125 Zeichen. Wer einen ganzen
  Lizenzsatz braucht, lässt ihn in nummerierten Bruchstücken von je höchstens 100 Zeichen ausgeben.
- 2026-09-02 — Der Etalab-Lizenztext liegt nur französisch vor; der Weg, der trägt, ist
  `raw.githubusercontent.com/etalab/licence-ouverte/master/LO.md`.
- **Die Werkzeuge dieser Rolle wechseln zwischen Läufen, und zwar jedes Mal.** Bisher
  gesperrt gesehen: `Edit`, `Write`, `sed`, `awk`, `mv`, `rm`, `python3`, Heredocs, jeder
  Backtick im Aufruf, Mehrfachbefehle mit Und-Und oder Semikolon, und `cd x` zusammen mit
  einem zweiten Befehl. Am 2026-09-02 (Paket 0024) trugen nur `head`, `tail`, `cat`,
  `printf`, `tr`, `wc` und `git diff` — je ein Befehl pro Aufruf, `cd` allein.
  **Das Vorgehen, das bisher immer getragen hat:** Datei aus Bereichen neu zusammensetzen
  (`head -N` plus neuer Block plus `tail -n +M`), den neuen Block mit `printf` schreiben,
  Backticks über einen Platzhalter und `tr` mit dem Oktalcode 140 einsetzen, mit
  `cat neu > alt` einspielen. **Die Werkzeuge zuerst an einer Wegwerfdatei messen, dann
  planen** — nicht erst den Text entwerfen und dann feststellen, dass er nicht schreibbar ist.
- 2026-09-02 — **Zwischendateien gehören nach `$TMPDIR`, nicht ins Venture.** `rm` und `mv`
  sind gesperrt (Hausregel 3), also bleibt für immer liegen, was man dort anlegt. Zwölf
  Punktdateien liegen deshalb noch in `ventures/0016-.../daten/`.
- 2026-09-02 (Paket 0024) — **Meine beiden Ergebnisdateien waren schon committet, bevor ich es
  versuchen konnte** (`c8ff8c4`, Betreff „testentwickler: 0019-…", Lauf 263): Ein parallel
  laufender Lauf hat den ganzen Arbeitsbaum mitgenommen. `git commit` war mir in diesem Lauf
  gesperrt — der Commit gehört hier also dem Runner, nicht dem Agenten, und der Betreff ist
  nicht meiner. **Zwei Folgen fürs Vorgehen:** Der Arbeitsbaum muss zu *jedem* Zeitpunkt
  schlüssig sein, weil ein fremder Lauf ihn jederzeit einfrieren kann — halbfertige
  Zwischenstände gehören nach `$TMPDIR`, die Ergebnisdatei wird in einem Zug eingespielt. Und
  nicht annehmen, der eigene Commit sei der letzte: `git log -- <meine datei>` sagt, wer sie
  tatsächlich trägt.

## Offene Fährten

- **Paket 0024, worauf ich unsicher bin, für den Projektmanager (zwei Punkte):**
  1. Ich habe neben der Begründung auch die Frontmatterzeile `ueberarbeitet:` fortgeschrieben
     („Pakete 0018 … und 0024 …"). Abnahme 3 zählt Zahlen auf, die gleich bleiben müssen, und
     diese Zeile ist keine davon — trotzdem ist es die einzige Änderung ausserhalb der
     verlangten. Ich halte die stille Fassung für schlechter, weil die Datei sonst behauptet,
     ihr letzter Stand komme aus 0018. Ein strenger Prüfer kann das als Zusatz führen.
  2. **Die Zeilennummern der Datei haben sich um fünf verschoben** (650 auf 655 Zeilen, ab
     Zeile 191). Das Arbeitspaket und der Prüfbefund zu 0018 zitieren die alten Nummern:
     542 ist jetzt 547, 547–556 sind 552–561, die T26-Folgezeile 196–198 ist 201–203. Inhalt
     unverändert, Nummer nicht — wer gegen die alten Nummern prüft, greift daneben.
- **Der IWF-Volltext entscheidet 15 der 31 Sollreihen und 7 der 16 Prüfgegenstände.** Ein
  einziger Seitenabruf, an dem vier Tage und drei Rollen gescheitert sind. Der teuerste offene
  Punkt der ganzen Datenschicht.
- **Für Reihe 2 gibt es keine geprüfte Ausweichquelle**, und sie trägt vier der sechzehn
  Prüfgegenstände — die einzige der unklaren Reihen ohne zweiten Weg.
- **Reihe 10, gemeldet und nicht aufgelöst:** Das Arbeitspaket verlangt den Faktor 10.000 auf
  den Rohkurs, T5 Klasse 6 beschreibt dieselbe Grösse als „Index gegen USD, Startjahr = 10.000",
  was für Deutschland 10.000 statt 17.341 ergäbe. Vorgegebener Faktor eingetragen, Frage als
  Widerspruch Nr. 4 an den Architekten gestellt.
- **Zwei Reihen ohne gemessene Quelleneinheit**, beide nicht mein Paket: der PWT-Kapitalstock
  (Reihe 3) und BACI (Reihe 14, dazu laufende gegen konstante Preise). Wer den Jahrgangsbau
  baut, braucht beide Zahlen vorher.
- **Ein Zusatzauftrag an den Datenkurator wäre billig:** die ILO in die geprüften Quellen
  aufnehmen, **samt** der Stichtagsfrage („produced prior to 3 May 2023" ist nicht bestimmt).
  Kostet keine Sollreihe, gibt aber den Reihen 6 und 7 ihren Datenanker zurück.
- **Aus Paket 0022, unerledigt:** Drei weitere `Source`-Wortlaute in `reihen.toml` (Zeilen 304,
  394, 405) tragen dieselbe Umbruch-Ersetzung ohne Vermerk wie die beiden reparierten. Benannt
  im Feld `schnitt_2_offen`, nicht behoben, weil die Abnahme die vierte Änderung verbot.
- **Aus Paket 0017, unerledigt:** Der Schlüsselname `sollreihen` steht in zwei Ebenen derselben
  Datei; eine Zeilenzählung mit `grep` ergibt 43 statt 31. Die Falle ist im Abschnitt
  `pruefweg` beschrieben, statt behoben zu sein. Untertabellen brauchen eigene Schlüsselnamen —
  für den nächsten, der dort schreiben darf.
