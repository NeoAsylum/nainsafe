# Logbuch: geschaeftsfuehrer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/geschaeftsfuehrer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

- 2026-09-01 — Erster Lauf. Die Spezifikation von 0016 ist 270 kB; sie ganz zu lesen
  ist unmöglich und unnötig. Getragen hat dieser Weg: Arbeitspakete und Befund-
  Frontmatter ganz (klein und aktuell), `specs/` nur über Gliederung und Abschnitt
  „Offene Entwurfsfragen", dazu `agents/*.py` und die Commit-Botschaft der letzten
  Änderung. Die Wahrheit über den Zustand stand in den Skripten, nicht in den Dokumenten.
- 2026-09-01 — Wenn ein Gate übersprungen wurde, steht der Grund im Gate-Dokument, die
  *Nebenwirkung* aber nirgends. `gates/0016-g1.md` nennt die archivierte Bewertungskette;
  dass damit `wip()` das Vorhaben nicht mehr als `im_bau` zählt, stand in keiner Datei.
  Übersprungene Schritte lohnen den Blick auf das Skript, das den Status liest.
- 2026-09-01 — Die nützlichste Frage nach dem Engpass war nicht „was fehlt", sondern
  „welche Größe lesen die meisten Stellen". `fondsvermoegen(z)` hat fünf Leser, und damit
  war Paket 0002 ohne Abwägung der Engpass.
- 2026-09-01 (2. Lauf) — **Nach einem Baulauf zuerst `git log --stat` gegen die
  Statuszeilen der Pakete halten, nicht die Ergebnisdateien lesen.** Der Abgleich fand in
  drei Minuten alles, worauf es ankam: ein Paket mit Datei ohne Statuswechsel, eines mit
  Commit ohne Datei. Die Befunde selbst musste ich nur für die zwei Zahlen öffnen, die in
  den Plan gehören.
- 2026-09-01 — **Ein Logbuch, das die Vorlage geblieben ist, ist der billigste Beweis für
  einen leeren Lauf.** Jede Rolle schreibt am Ende hinein; wo nichts steht, hat der Lauf
  nicht bis zum Ende gearbeitet. Schneller als jede Journalabfrage.
- 2026-09-02 — **Der Trick von gestern, verschärft: `grep -c "<datum>" notizen/*.md` über
  alle beteiligten Rollen auf einmal.** Ein Aufruf, und der ganze Engpass stand da — drei
  Bauagenten mit 0 Treffern, der Prüfer mit 10. Damit war belegbar, dass die Läufe nicht
  leer, sondern *abgeschnitten* waren: Arbeit da, Schlussarbeit nicht. Das ist ein anderes
  Fehlerbild als „leer" und keine Zählung der Fabrik sieht es.
- 2026-09-02 — **Wenn ein Paket liegen bleibt, erst prüfen, ob seine Rolle überhaupt
  eingeplant werden kann.** `BAUROLLEN` gegen das Feld `rolle` halten, zwei greps. 0011
  (Rolle `architekt`) wäre sonst monatelang als „offen" erschienen, obwohl kein Lauf es je
  anfassen kann. Ein Paket ohne planende Rolle ist kein Rückstand, sondern ein Loch.
- 2026-09-02 (2. Lauf) — **Die Fragen, die der Rückstand dem Betreiber vorlegt, auf ihre
  Ursache zurückrechnen, statt sie zu referieren.** Der Projektmanager legte sechs vor;
  alle sechs hingen an denselben zwei nicht einplanbaren Rollen. Damit war der Engpass
  ohne Abwägung benannt, und aus einer Liste wurde eine Entscheidung. Das ist die beste
  Form der Engpassfrage bisher — besser als „welche Größe hat die meisten Leser".
- 2026-09-02 (2. Lauf) — **Ein Vertagungspreis trägt nur mit Paket und Zeitpunkt.** „C
  kostet etwas" ist folgenlos; „0002 giesst die Preisbasis in `kern::werte`, sobald 0008
  gebaut ist, also in etwa einem Lauf" ist eine Frist. Dafür genügte, die `haengt_an`-Kette
  rückwärts zu lesen.
- 2026-09-02 (3. Lauf) — **Vor jedem „unverändert seit drei Plänen" die Uhr des Betreibers
  prüfen:** `git log` nach Commits *ohne* Rollenpräfix filtern. Sein letzter Griff war
  2026-09-01 21:02, meine drei Pläne entstanden in 100 Minuten derselben Nacht. Drei
  Pläne sind dann keine drei Ablehnungen, sondern eine Nachtschicht. Das hat meine
  Vermutung von gestern („eine Empfehlung, die um Aufmerksamkeit konkurriert, wird
  vertagt") widerlegt, bevor ich sie zur Tatsache gemacht habe.
- 2026-09-02 (3. Lauf) — **Einen Ausweg, den ich als Option anbiete, einmal wirklich
  aufmachen.** Ich führte den Konzeptlauf zwei Pläne lang als Alternative; er hält seit
  fünf `zurueck`-Urteilen bei `RUECKLAUF_MAX = 3` vor dem ersten Token an. Zwei greps
  (Bremse zählen, `return 0` lesen) haben aus einer Option eine geschlossene Tür gemacht.
  Eine Option, die ich nicht nachgesehen habe, ist eine Vermutung im Entscheidungstext.
- 2026-09-02 (4. Lauf) — **`baulauf.py --trocken` ist die schärfste Engpassmessung, die
  ich habe.** Sie sagt nicht, was offen ist, sondern was der nächste Lauf *anfasst*. Vier
  gezogene Pakete, alle vier vom Datenbauer, null Kernpakete — damit stand der Engpass
  ohne jede Abwägung da. Der Rückstand konnte das nicht zeigen: Er war 20 Minuten vor dem
  Ende des Laufs geschrieben. **Erst den Trockenlauf, dann den Rückstand lesen.**
- 2026-09-02 (4. Lauf) — **Nicht nur prüfen, ob eine Option machbar ist, sondern welche
  Nebenwirkungen das Skript ihr gibt.** Zu „Architekt in `BAUROLLEN`" fand ich zwei
  Sachen, die ich sonst geraten hätte: Er steht schon in `REVIEW` (bekommt seinen Prüfer
  automatisch), und `rueckläufe()` zählt **je Paket** — anders als im Konzeptlauf. Aus
  „eine Zeile" wurde damit „eine Zeile ohne Nebeneffekt", und das ist ein anderer Satz.

## Was nicht funktioniert

- 2026-09-01 — `cat`/`sed` über mehrere Dateien wird in diesem Harness abgelehnt; `Read`
  mit `offset`/`limit` und `grep` gehen. Kein Zeitverlust, wenn man gleich so anfängt.
- 2026-09-01 — `ops/portfolio.md` (2026-08-30) und `ops/kontingent.md` (2026-08-30) sind
  älter als die Umstellung auf 0016 und beschreiben eine Fabrik, die es nicht mehr gibt.
  Für den Stand eines Vorhabens sind sie unbrauchbar; nicht wieder dort anfangen. Dasselbe
  gilt für `ops/auslastung.md` — vom 2026-08-30, kennt keinen einzigen Baulauf.
- 2026-09-01 — **Die Commit-Betreffs sagen nicht, wer was getan hat.** Jeder Bauagent
  committet seinen ganzen Schreibpfad (`ventures/`), also nimmt der erste fertige Lauf die
  Dateien der drei parallelen mit. Wer aus `git log` auf Urheber schließt, irrt sich um bis
  zu drei Läufe; nur `--stat` gegen das Feld `dateien` des Pakets trägt.
- 2026-09-01 — `python3 -c` und mehrzeilige Bash-Schleifen sind abgelehnt, einzeilige
  `git`-, `grep`- und `ls`-Aufrufe gehen. Das Journal (`state.db`) ist damit für mich nicht
  lesbar — die Frage „warum blieb der Lauf leer" gehört in den Plan, nicht in meine
  eigene Recherche.
- 2026-09-02 (2. Lauf) — **`git commit` ist meiner Rolle nicht erlaubt**, in jeder Form
  (Heredoc, `-m`, doppeltes `-m`). `git add` geht. Der Lauf committet, nicht ich: Dateien
  schreiben, stagen, fertig — die drei abgelehnten Aufrufe spart sich der nächste Lauf.
- 2026-09-02 (2. Lauf) — **Das Paket, das nach der Vorgabe klingt, ist selten das, das sie
  ausführt.** Ich wollte schreiben, 0008 (Zustand, 310 Felder) giesse den Preisbasis-Fehler
  ein — nachgesehen: 0008 baut die *Ablage*, die Bedeutung der Zahlen entsteht in 0002.
  Ein `grep` auf die zitierten Vorgabenpunkte (`T5`, `T50`) trennt beides in Sekunden.
  Ungeprüft wäre die schärfste Zahl des Berichts falsch gewesen.
- 2026-09-02 (2. Lauf) — **Zwei Pläne hintereinander dieselbe Empfehlung, zweimal nicht
  ausgeführt.** Beim ersten Mal stand sie neben einer zweiten Frage, im Rückstand neben
  fünf. Vermutung für den nächsten Lauf: Eine Empfehlung, die um Aufmerksamkeit
  konkurriert, wird vertagt. Deshalb diesmal **eine** Frage im Plan und die anderen
  ausdrücklich darunter gehängt. Beim nächsten Lauf prüfen, ob das getragen hat — wenn
  nein, liegt es nicht an der Darstellung und ich muss eine andere Ursache suchen.
  **Erledigt am 2026-09-02 (3. Lauf): Die Vermutung war falsch, siehe oben. Nicht
  wieder aufwärmen.**

## Offene Faehrten

- **2026-09-02: Diese Datei steht bei 11.500 von 12.000 Zeichen.** Nächster Lauf zuerst
  nach `notizen/archiv/geschaeftsfuehrer-2026-09-02.md` verschieben und mit dem neu
  anfangen, was noch gilt — nicht mittendrin, wenn die Grenze reißt.
- **Erledigt und nicht wieder aufzuwärmen:** Übersetzungslauf (cmake/ctest grün seit
  2026-09-02), Rücklaufgrenze (`RUECKLAUF_MAX = 3`), Rust-Dateinamen in den Codepaketen
  (Projektmanager hat alle nachgezogen), und die abgeschnittenen Läufe — am 2026-09-02
  haben alle fünf Rollen ihr Logbuch ergänzt, **ohne dass jemand eingegriffen hat.** Die
  Ursachenfrage (Kontingentgrenze?) hat sich damit von selbst erledigt; nicht erneut
  stellen, solange das Muster nicht wiederkommt.
- **Lehre daraus, allgemein:** Einen Engpass nie aus dem letzten Plan fortschreiben, ohne
  ihn neu zu messen. Ich hätte ihn diesmal beinahe wiederholt; ein `grep -c` über die
  Logbücher hat ihn in zehn Sekunden für erledigt erklärt.
- **Nächster Lauf zuerst:** Steht `architekt` in `BAUROLLEN` (`grep -n BAUROLLEN
  agents/baulauf.py`), und ist 0002 gebaut (`grep '^status:' …/aufgaben/0002-*.md`)?
  Erste Frage nein + zweite ja = die Preisbasis-Mischung ist in Code gegossen und der
  Plan muss von Nacharbeit handeln, nicht mehr von Vorbeugung. Am 2026-09-02 (4. Lauf)
  war es zum zweiten Mal nein + nein; zusätzlich nachgesehen, dass `zustand.hpp` trotz
  1.568 Zeilen **keine** Preisbasis festlegt. Die Vorbeugung ist noch möglich.
- **Erledigt am 2026-09-02 (4. Lauf): 0008 hat geliefert**, 726 + 842 Zeilen plus Probe.
  Die Einstufung „selbstheilend" hat getragen. **Aber die Lehre ist eine andere als
  erwartet:** Leer ging derselbe Lauf trotzdem an *einem* von vier Bauplätzen aus, nur an
  einem anderen Paket (0015). **Die Einheit des Fehlers ist der Bauplatz, nicht das
  Paket** — zwei Läufe, je 1 von 4, je ein anderes Paket. Ein leeres Paket dem Paket
  anzulasten, bevor die zweite Messung da ist, wäre falsch gewesen. Dritte Messung im
  nächsten Lauf: Ging wieder genau einer von vier leer aus?
- **Ein Bauagent kann Arbeit schreiben und trotzdem aus dem Review fallen.** 0009 hat am
  2026-09-02 um 05:47 87 Zeilen `parameter.toml` bekommen, aber `status: offen` behalten —
  also plant der Runner es als Bau statt als Review, und der Prüfer sieht die Runde nie.
  Prüfmuster in zwei Aufrufen: `git log` auf die **Ergebnisdatei** gegen `git log` auf die
  **Paketdatei**. Stehen dort verschiedene Zeiten, ist die Meldung ausgefallen, nicht die
  Arbeit. Das ist ein drittes Fehlerbild neben „leer" und „abgeschnitten".
- **Ein Bauagent, der nichts liefert, verrät sich über sein Logbuch, nicht über den
  Commit.** Der Commit `kernbauer: 0008` enthielt ausschließlich fremde Dateien (das
  Quersammeln paralleler Läufe), `grep -n 0008 notizen/kernbauer.md` war leer. Der
  Commit-Betreff belegt nur, dass der Lauf *geplant* war.
- **Die 170-gegen-121-Lücke** hat seit dem 2026-09-01 niemand angefasst und sie blockiert
  noch nichts. Erst wieder aufgreifen, wenn der Kern rechnet.
- **Fährte „Abnahmekriterien werden zum zweiten Engpass" — abgeschwächt, nicht erledigt.**
  Am 2026-09-02 (4. Lauf) ging die einzige Prüfung (0012) mit `geprueft` durch, beide
  Befunde ausdrücklich nicht gegen die Artefakte. Das ist ein Gegenbeleg. Offen bleibt
  nur 0009, und dort hängen beide Rückläufe an *derselben* Bedingung 3 — ein Kriterium,
  nicht ein Muster. Erst wieder aufgreifen, wenn ein zweites Paket denselben Weg nimmt.
