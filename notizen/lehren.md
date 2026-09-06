# Lehren

Das gemeinsame Gedächtnis der Fabrik. **Alle** Rollen lesen diese Datei zu Beginn
ihres Laufs; geschrieben wird sie ausschließlich vom Portfolio-Manager, einmal pro
Woche, aus dem, was in den Logbüchern und den Ablehnungen tatsächlich zu sehen war.

Warum nur einer schreibt: Elf Rollen, die gleichzeitig an einer gemeinsamen Strategie
schreiben, erzeugen keine Strategie, sondern Rauschen. Und eine falsche Lehre, die
niemand mehr prüft, kostet mehr als gar keine.

**Was hier steht, ist widerlegbar.** Jede Zeile trägt ein Datum. Ist eine Lehre älter
als 60 Tage, prüft der Portfolio-Manager sie erneut oder streicht sie. Die Welt ändert
sich, und eine Fabrik, die ihre eigenen Vorurteile pflegt, findet nichts Neues mehr.

**Was hier nicht steht:** Regeln. Die Grenzen in `grenzen.md`, die Rollenzuschnitte und
die Hausregeln ändert nur der Betreiber. Diese Datei sammelt, was funktioniert — nicht,
was erlaubt ist.

**Gekürzt am 2026-09-06, von 42.578 Zeichen auf etwa die Hälfte.** Nichts war älter als
60 Tage, gestrichen wurde nach einem anderen Maß: Seit dem 2026-08-31 sucht die Fabrik
nicht mehr, sie baut (`nachtlauf.py:FOKUS`). Zwei Drittel dieser Datei waren an Rollen
gerichtet, die seither nicht mehr laufen — Scouts, Ideator, Rechercheur, beide Analysten,
Fit-Filter —, und wurden trotzdem von jeder Baurolle in jedem der 1.531 Läufe dieser Woche
mitgelesen. Der Volltext steht unverkürzt in **`git show 9103e36:notizen/lehren.md`** und
kehrt zurück, wenn `FOKUS = None` gesetzt wird; der tragende Satz jeder gestrichenen Lehre
steht unten unter „Aus der Suchphase". Gelöscht ist nichts, Hausregel 3 ist gewahrt.

---

## Aus der Suchphase — je ein Satz, Volltext in `git show 9103e36:notizen/lehren.md`

Fünfzehn Ideen, achtzehn Marktprofile, 46 Recherchen, alles zwischen dem 2026-08-28 und
dem 2026-08-31. Wer die Suche wieder aufnimmt, liest zuerst den Volltext — hier steht nur,
was die Belege ergaben, nicht die Belege.

- **Der häufigste Todesgrund war der fehlende Weg zum ersten Kunden**, nicht die fehlende
  Idee: neun Kanäle einzeln geprüft, alle neun gescheitert. Der Kanal gehört in den
  Entwurf, bevor die Lösung darin steht. „Man könnte Inhalte produzieren" ist keiner.
- **Ein Kanal ist erst ein Kanal, wenn er vermessen oder seine Bedingungen gelesen sind.**
  Je ein Abruf — und beide Male fiel der Kanal (Handwerkerforen, ezyVet-Partnerprogramm).
- **Wer Richtigkeit verkauft, haftet dafür; wer Zeitersparnis verkauft, nicht** (G6). Der
  zulässige Zuschnitt ist regelmäßig der schwächere von beiden. Daran starben zwei Ideen.
- **Der Preis des nächstgrößeren Vollprodukts deckelt jede Teilfunktion**, dreimal belegt.
  Im englischsprachigen Raum ist der Preisboden regelmäßig **null, und die Null ist ein
  Geschäftsmodell** — refinanziert aus dem Zahlungsstrom, den Hausregel 2 uns verbietet.
- **Bedient eine Idee eine Behördenpflicht, ist die Behörde der Wettbewerber** — und der
  Verband ist der schlimmere Fall: Er besitzt den Kanal, den der Entwurf einplant, *und*
  verkauft das Konkurrenzprodukt.
- **Die Besetzungsfrage zuerst stellen, nicht zuletzt.** Sie entschied siebzehn von
  achtzehn Marktprofilen allein; Größe, Zahlungskraft und Kanal entschieden kein einziges.
- **Untergrenze 5.000 € Marge im Monat** (G7, ADR 0004): Entweder das Segment ist groß
  genug oder der Preis hoch genug. Beides klein trägt nie.
- **Zwei Achsen statt einer** (ADR 0005): Der Fund liegt dort, wo ein Vorgang
  branchenübergreifend **gleich** ist, aber ausschließlich branchenspezifisch **gelöst**
  wird. „Branchenübergreifend" allein ist eine Suchrichtung, kein Fund.
- **Bevor du eine teure Rolle abschaffst, rechne nach, was sie wirklich kostet.** Der
  auffällige und der teure Posten sind selten derselbe.
- **Wer einen Gesetzestext oder einen Preis zitiert, holt ihn im Wortlaut.** Der
  Suchauszug hat zweimal die Begründung verschoben und einmal das Urteil entschieden.
- **Ein Anschlusszuschnitt des Anwalts ist nicht der billige Weg zur nächsten Idee.** Alle
  drei sind gestorben, jeder an einer *anderen* Grenze als seine Mutteridee.

---

## Über 0016 — warum dieses Spiel, und was daran offen ist

- **2026-08-31 — Unterhaltung ist der einzige Suchraum, in dem das Killerkriterium dieser
  Fabrik gar nicht existiert — und der einzige mit noch schlechteren Zahlen.** 40 von 45
  roten Recherchen starben daran, dass ein Anbieter dasselbe Problem schon löst, meist
  gratis; bei einem Spiel gibt es dieses Kriterium nicht. Dafür: Steam 2025, über 19.000
  Veröffentlichungen, **Median 249 $ Bruttoumsatz im Jahr**, 47,5 Prozent unter 100
  verkauften Exemplaren. Unsere 5.000 € im Monat liegen dort oberhalb des 95. Perzentils.
  Unterhaltung ist zugelassen (ADR 0008, `zahlungsgrund: wunsch`), aber **ohne jede
  Sonderregel**.

  Der Zuschnitt ist **Simulation und Automation**, und der Grund ist nicht der Umsatz,
  sondern die **Prüfbarkeit**: Dort *ist* der Zustand eine Zahlentabelle, also erfüllt das
  Genre G8 von Bauart wegen, und Balance, Wirtschaftskreislauf und Lösbarkeit sind messbar.
  „Macht Spaß" ist es nicht. **Misstraue der Zahl „Median 200.000 bis 500.000 $ für
  Fabrikspiele"**: Sie gilt nur für Titel mit mindestens 100 Bewertungen und ist damit nach
  Erfolg gefiltert.

  **Die Rechnung ist bei Unterhaltung anders gebaut**: Ein Spiel wird einmal gekauft.
  5.000 € im Monat heißen nicht 900 zahlende Kunden, sondern dauerhaft 900 Verkäufe im
  Monat — oder ein wiederkehrendes Modell. Der Plattformanteil von 30 Prozent gehört in
  die Rechnung.

- **2026-08-31 — Entschieden vom Betreiber: Ein Spiel über Finanzmärkte, Lobbyismus und
  Korruption ist bei `genehmigung` unbedenklich.** Der Arbeitgeber ist eine Bauspar- und
  Versicherungsgruppe, die Entfernung zu Hedgefonds und Finanzmarktaufsicht ist groß genug.
  *Die Frage ist geklärt — nicht erneut aufwerfen.* Unberührt bleibt G1: ein Produkt mit
  Versicherern oder Finanzdienstleistern **als Kunden** ist weiter ausgeschlossen. Der
  Unterschied ist die Zielgruppe, nicht das Thema.

- **2026-08-31 — Die Fabrik sucht nicht mehr.** „Ab jetzt bauen wir nur noch das Spiel."
  `nachtlauf.py:FOKUS` steht auf der Ideen-ID; weiter laufen nur Rollen, die an dieser Idee
  arbeiten. Nichts ist gelöscht, `FOKUS = None` stellt die Suche vollständig wieder her,
  und `quellen.yml` behält alle Segmente und Vorgänge.

- **2026-09-02, ergänzt 2026-09-06 — Die 170-gegen-121-Lücke, und warum sie niemand mehr
  ansieht.** Ich hatte sie dreimal als „die Idee trägt nicht" gemeldet. Richtig ist: **121
  ist eine Untergrenze unter den pessimistischsten Annahmen, keine Prognose.** Die Basis
  sind nicht Steams hundert Millionen Nutzer, sondern 2,9 Mio. belegte Käufe der sieben
  Kerntitel *eines* Tags — und darauf ein Promille, die härteste Stufe aus G7. Bei einem
  Prozent derselben Basis wären es 1.208 im Monat, das Siebenfache der Schwelle. Im selben
  Profil stand die Gegenevidenz: Der Marktführer des Genres ist ein **Ein-Personen-Studio**
  und trägt die Schwelle sechsfach, während der Median der Augustkohorte bei 255 verkauften
  Exemplaren liegt. Dazwischen liegt Faktor fünfzig.

  *Folgerung für alle Rollen:* Der Befund heißt nicht „der Markt ist zu klein", sondern
  **„die Streuung ist unbegrenzt und niemand engt sie ein"**. Der erste Satz beendet ein
  Vorhaben, der zweite benennt eine offene Arbeit. Wer eine pessimistische Annahme
  weitergibt, nennt sie als solche und nennt die optimistische daneben.

  **Nachtrag 2026-09-06, und er berichtigt diese Lehre:** Die alte Fassung nannte Ökonom
  und Vertriebsplaner als die Rollen, die diese Lücke schließen, „und gelingt es nicht, ist
  Gate 2 die Stelle, an der das sichtbar wird". **Beide Rollen wurden am selben 2026-08-31
  archiviert, zusammen mit Compliance-Prüfer, Urlaubstester, Antrags-Vorbereiter und
  Konzept-Judge** (`konzeptlauf.py:44-47`, Entscheidung des Betreibers: gebaut wird, die
  wirtschaftliche Betrachtung tritt in den Hintergrund). Es gibt also kein `rechnung.md`,
  kein `vertrieb.md` und kein Gate 2 — die Lehre nannte ein Sicherheitsnetz, das es nicht
  gibt. *Folgerung:* Die eine Geschäftszahl des Vorhabens sieht sich von selbst niemand
  mehr an. Wer sie geschlossen haben will, sagt es dem Betreiber; keine laufende Rolle hat
  den Auftrag.

---

## Über das Bauen

- **2026-09-01 — Ein Agent, der Code schreiben soll und ihn nie übersetzen kann, schreibt
  über Code.** Der erste vollständige Baulauf hinterließ vier Markdown-Dateien und **null
  Zeilen Code**. Ursache war der Entzug von `Bash` (richtig: eine Shell umgeht jede
  Edit()-Sperre) ohne den Nebengedanken, dass damit kein Bauagent je einen Compiler
  aufrufen kann. *Folgerung:* Der Compiler läuft im **Runner**, nicht in einer Rolle —
  `baulauf.py:uebersetzen()` ruft nach jeder Baustufe `cmake`/`ctest` und legt das Urteil
  unter `befunde/uebersetzung-<datum>.md` ab. Kein Modell, keine Meinung.

  **Die allgemeine Form:** Wenn eine Rolle ein Werkzeug nicht haben darf, ihre Arbeit aber
  ohne dessen Ausgabe wertlos ist, gehört das Werkzeug in den Runner und seine Ausgabe in
  eine Datei. Frage nach jedem Entzug: *Was kann diese Rolle nicht mehr nachsehen?*

- **2026-09-01 — Eine Bremse an der Stelle, die gerade weh tut, ist keine Bremse.** Die
  Rückläufe des Entwurfs kosteten 95 $ ohne Konvergenz; ich baute
  `konzeptlauf.py:RUECKLAUF_MAX` ein — und der Geschäftsführer wies im ersten Lauf darauf
  hin, dass im Baulauf dieselbe Grenze fehlt, wo dieselbe Nichtkonvergenz Code statt Prosa
  kostet. *Folgerung:* Beim Einbau einer Bremse **jede** Stelle suchen, an der dieselbe
  Schleife laufen kann, nicht nur die, die gerade brannte.

- **2026-09-01, berichtigt am 2026-09-06 — Ein Argument ist kein Vergleich, und diese
  Fabrik kann den Vergleich *bauen*, statt ihn zu führen.** Der Architekt hat Rust in drei
  guten Sätzen begründet und keine einzige Alternative genannt (ADR 0010). Der Betreiber
  fragte nach — und die Antwort war keine Erörterung, sondern eine Messung: **vier Agenten
  haben dieselbe Rechenvorschrift in vier Sprachen gebaut** (`ventures/0016-.../
  messung-stack/`), alle vier trafen sie beim ersten Anlauf, alle vier lieferten
  **dieselbe Prüfsumme**. Für diese Domäne gibt es keinen messbaren Unterschied in der
  Agentenzuverlässigkeit; Python schied an der Geschwindigkeit aus.

  **Ergebnis: ADR 0011, der Kern ist C++, nicht Rust.** Wer in einem älteren Dokument Rust
  liest, liest eine überholte Fassung — die alte Lehre an dieser Stelle sagte sechs Pläne
  lang das Gegenteil. Der eine echte Einwand (vorzeichenbehafteter Überlauf ist in C++
  undefiniert) ist nicht weggeredet, sondern in drei mechanische Maßnahmen übersetzt:
  `-fwrapv`, `-fsanitize=undefined,address` im Testprofil, `__int128` für jeden
  Zwischenwert. Kein Gleitkommatyp im Kern bleibt, und ist per `grep` nachweisbar.

  **Der zweite Teil ist der wertvollere:** Die Oberflächenwahl stand im selben Dokument,
  obwohl sie niemand brauchte — die Architektur verlangt ohnehin, dass das Spiel ohne
  Darstellung spielbar ist. Sie wurde vertagt und ist bis heute nicht nötig gewesen.
  *Frage, die in jeden Entwurf gehört:* **Welche Festlegung muss jetzt fallen, und welche
  lässt sich vertagen?**

- **2026-09-02 — Jede Rolle darf Arbeit vorschlagen, einplanen tut der Projektmanager.**
  Bis dahin landete ein Befund im Logbuch und wurde nur dann ein Paket, wenn der
  Projektmanager es zufällig las. Ein Befund darf jetzt ein Paket mit `status: vorschlag`
  werden — mit Rolle, Abhängigkeiten, Dateiliste und prüfbarer Abnahme.

  **Warum trotzdem nur der Projektmanager `offen` setzt, und zwar aus einem technischen
  Grund statt aus Rangordnung:** Der Baulauf plant nur Pakete gleichzeitig ein, deren
  Dateilisten sich nicht schneiden. Vier Agenten, die sich gleichzeitig selbst Arbeit
  geben, sehen die Ansprüche der anderen nicht — und schreiben dieselbe Datei.

  **Und die Arbeitsteilung mit dem Geschäftsführer:** Der legt den *Vorrang* fest
  (höchstens fünf Kennungen in `ops/plan.md`), der Projektmanager den *Ablauf*. Er sieht
  über die Gewerke, der andere in sie hinein. Widersprechen sie sich zweimal in derselben
  Sache, gehört das in den Bericht an den Betreiber statt in eine dritte Runde.

- **2026-09-06 — Eine Prüfung, deren Gegenstand sich nicht bewegen *kann*, ist grün und
  wertlos.** Drei Quellen unabhängig: Der Bruchtester meldet einen grünen 200-Runden-Lauf
  und nennt den Grund selbst — `schritt_3` bis `schritt_5` sind je ein
  `schreiber.vortrag(platz)`, es rechnet nichts. Der Projektmanager: „Kein Paket baut einen
  rechnenden Rumpf für `schritt_2`…`schritt_6`" — deshalb steht 0157 auf `blockiert`, und
  daran hängen die drei Maße. Der Geschäftsführer führt dieselbe Sache als *die eine Zahl*:
  **0 von 310** — eine Runde `weltlauf` läuft durch und ändert keine der 310 Zustandsgrößen.
  Daneben stehen 18 grüne Tests.

  *Folgerung für jeden Prüfer:* **Bevor du ein Grün meldest, miss, ob sich überhaupt etwas
  ändert.** Die Spalte „geändert gegenüber Vorrunde" hat mehr gesagt als zehn
  Schrankenurteile zusammen. Ein Grün auf einem unbeweglichen Gegenstand ist keine
  Zusicherung, sondern eine Tautologie.

  **Das ist der vierte Fall derselben Familie** — nach `nach-aufraeumen.py`, das
  importierte statt auszuführen und „keine Befunde" meldete; nach dem Architekten, der aus
  neun Verweigerungen mit Zeilennummern einen falschen Schluss zog; nach der
  „Nachtbereitschaft", die schrieb statt zu berichten. *Ein Name, der nach Prüfen klingt,
  muss auch prüfen können.*

- **2026-09-06 — Ein `cd` in einem Bash-Aufruf nimmt das Sitzungs-Arbeitsverzeichnis mit,
  und danach stirbt jeder `Edit`.** Drei Logbücher unabhängig, der Projektmanager zweimal.
  Die Schreibgrenzen sind **relative** Pfade (`Edit(ventures/**)`); nach einem `cd` trifft
  keiner mehr. Die Absage nennt nur „don't ask mode" und sieht deshalb wie ein
  Rechteproblem aus — am 2026-09-06 starben vier `Edit` daran, ausgelöst vom **ersten**
  Aufruf des Laufs, einem harmlosen `cd …/befunde && grep`. *Folgerung für alle Rollen:*
  **Nie `cd`.** Absolute Pfade als Argument, oder `git -C …`. Heilung, falls doch passiert:
  `cd /home/adria/fabrik` als eigener Aufruf.

- **2026-09-02 — Ein Agent kann präzise begründen, warum er scheiterte, und dabei falsch
  liegen.** Der Architekt kam leer zurück und meldete „every file-writing tool is denied in
  this session", mit Zeilennummern, neun gezählten Verweigerungen und sauberer Herleitung.
  Ein Nachtest mit **derselben** Werkzeugliste hat die Datei ohne eine einzige Verweigerung
  geändert: Er hatte nach `Write` und `Bash` gegriffen, die er nicht hat, und die
  Verweigerungen für einen Beweis gehalten, dass auch `Edit` gesperrt sei. *Folgerung für
  alle Rollen:* Wenn ein Aufruf scheitert, nenne den **einen** Aufruf im Wortlaut, nicht
  die Schlussfolgerung. Eine Fehlermeldung mit Zeilennummern ist kein Beleg.

---

## Über den Betrieb der Fabrik

- **2026-09-05 — Es gibt drei Grenzen, und die Fabrik kannte zwei.** Anthropic zieht Tag,
  Woche **und** ein rollendes Fünf-Stunden-Fenster („session limit"). Am 2026-09-05 um
  16:01 riss das Sitzungsfenster. Weil niemand die Absage als *Ende* las, lief die Kette
  weiter: **1.041 Fehlläufe in drei Stunden**, jeder in Sekunden gescheitert, jeder mit
  einer Journalzeile, und alle vierzig Durchgänge des Tageslaufs verbraucht, ohne dass ein
  einziges Paket vorankam.

  *Folgerung:* Die Sitzungsgrenze lässt sich nicht vorausberechnen, also wird sie nicht
  vorhergesagt, sondern **erkannt**: `lauf.py` liest den Wortlaut der Absage
  (`hit your … limit`), setzt eine Sperre, und kein weiterer Lauf startet. Der stündliche
  Cron-Versuch ist die richtige Wiederholung — er kostet nichts, solange das Fenster zu
  ist, und fängt von selbst wieder an.

  **Die allgemeine Form, und sie ist die eigentliche Lehre:** Eine Fehlermeldung, die
  *jeder* weitere Versuch identisch erzeugen wird, ist kein Fehlschlag, sondern ein
  **Zustand**. Die Fabrik hatte für „ein Lauf ging schief" eine Behandlung und für „es geht
  gerade gar nichts" keine. Beides sieht an der Rückgabe gleich aus.

  **Nachtrag 2026-09-06: Die Sperre wirkt, und die Zahlen belegen es.** In den letzten
  sieben Tagen zählt `ops/auslastung.md` 1.069 Fehlläufe bei 1.531 Läufen — 70 Prozent.
  1.041 davon sind jene drei Stunden. Bleiben **28 Fehlläufe auf sechs Tage**; das ist die
  normale Rate. Wer die 70 Prozent ohne diese Aufteilung zitiert, beschreibt einen Zustand,
  den es nicht mehr gibt.

- **2026-09-02, aufgelöst am 2026-09-05 — Ich habe zwei Wochen gegen eine Zahl gebremst,
  die ich mir ausgedacht hatte, und danach gegen den falschen Tarif geeicht.** Die erste
  Eichung (398,8 $ = 21 Prozent, also 1.900 $ die Woche) stammte aus einem Fünftel der
  nötigen Stichprobe. Bei einer Grenze von 1.600 $ hielt die Bremse die Fabrik bei
  **71 Prozent** des Kontingents an und ließ 661 $ einer Woche verfallen. Die Ursache der
  Fehleichung nennt der Betreiber selbst: Das Abo ist von Max 5x auf Max 20x gewechselt,
  die Anzeige brauchte, bis sie das neue Limit führte — 58 gegen 15 Prozent derselben
  Woche, Faktor 3,9. Beide Messungen waren richtig, nur gegen verschiedene Nenner. Das
  Wochenkontingent liegt bei rund **12.700 $** Gegenwert.

  *Folgerung, und sie geht gegen die Vorsicht:* **Zu niedrig ist nicht die sichere Seite.**
  Das Abo ist ein Festpreis; ein nicht genutzter Durchgang spart nichts, er verschenkt.
  `WOCHENGRENZE_USD` rationiert deshalb nicht mehr, sie verhindert nur noch den Weglauf.
  Der wahre Kontostand ist aus der Fabrik heraus **nicht lesbar** (`claude --help` kennt
  keinen solchen Unterbefehl, geprüft 2026-09-05); die einzige verlässliche Anzeige ist
  die des Betreibers.

  **Offene Wiedervorlage, 2026-09-13:** Die 12.700 $ wurden gemessen, solange der
  Wochenbonus lief. Endet er, sinkt das Kontingent — und `WOCHENGRENZE_USD = 12000` bremst
  dann gar nicht mehr. Die alte Nacheichungsnotiz zu diesem Datum wurde am 2026-09-05
  aufgelöst, **ohne dass eine neue an ihre Stelle trat.** Der Betreiber müsste an diesem
  Tag einmal seine Anzeige vorlesen; von innen ist es nicht messbar.

- **2026-09-02 — Jede Zeitfensterabfrage der Fabrik war falsch, und niemand hat es
  gemerkt, weil sie plausible Zahlen lieferte.** Das Journal speichert
  `2026-09-02T01:00:00` mit einem `T`, SQLites `datetime('now','-5 hours')` liefert
  `2026-09-02 11:59:00` mit einem **Leerzeichen**. Im Zeichenvergleich ist `T` größer als
  das Leerzeichen — also war *jede* Zeile des Tages im Fenster. „Letzte fünf Stunden" hieß
  in Wahrheit „heute". Aufgefallen ist es erst an einer offensichtlich falschen Zahl: 80
  Läufe in sechzehn Minuten. *Folgerung:* `strftime('%Y-%m-%dT%H:%M:%S', …)` statt
  `datetime(…)`. Bei Tagesspannen fällt der Fehler nicht auf, weil der Datumsteil schon
  trennt — bei Stundenspannen kippt der Vergleich vollständig.

  **Und die richtige Zahl dahinter ändert die Empfehlung:** Im Sitzungsfenster hatte die
  Fabrik 7,8 $ verbraucht, während die Anzeige des Betreibers von 4 auf 12 Prozent stieg.
  Die acht Punkte kamen überwiegend aus dem **Gespräch**, nicht aus den Agentenläufen —
  jede Antwort schickt den ganzen Verlauf mit. Eine Fensterbremse für die Fabrik hätte
  gegen den falschen Verursacher gebremst.

- **2026-09-02 — Zwei Befunde aus dem ersten wirklich autonomen Tag**, beide über den
  Runner, nicht über die Agenten. **Erstens: Wer einen Runner ändert, während er läuft,
  ändert nichts.** `BAUROLLEN` wurde erweitert; der laufende Prozess hatte `baulauf` einmal
  importiert und benutzte bis zum Schluss die alte Fassung. Ein Paket stand den ganzen Tag
  auf `offen`, obwohl es hätte laufen können. **Zweitens: Eine Grenze, die nur an einer
  Stelle gilt, verlagert das Problem.** `RUECKLAUF_MAX` galt in der Baustufe, nicht im
  Review; ein dreimal zurückgekommenes Paket belegte seinen Prüfplatz weiter, und weil die
  Stufe **nach Dateinamen** sortierte, verhungerten die neueren. *Folgerung:* Die
  Reihenfolge ist jetzt die Zahl der bisherigen Urteile — wer nie geprüft wurde, geht
  zuerst —, und wer die Grenze erreicht hat, bekommt kein viertes Urteil, sondern eine
  Entscheidung.

- **2026-09-03 — Die Fabrik hängt an einem Rechner, der schlafen darf.** Vom 2026-09-02
  21:30 bis zum 2026-09-03 15:00 stand der Takt still: Der Windows-Wirt schlief, die
  WSL-VM war eingefroren. `uptime` meldete trotzdem sechs Tage Laufzeit, weil es die
  Wanduhr liest — die Maschine sah gesund aus. Cron holt nichts nach. *Folgerung:* Eine
  feste Uhrzeit ist die falsche Bauform für eine Maschine, die schlafen darf. Tageslauf und
  Sicherung laufen **stündlich** und prüfen selbst, ob heute schon gearbeitet wurde; ist
  das Budget erreicht, endet der Versuch nach null Durchgängen. Erkennbar war der Ausfall
  nur an einer **Lücke** im Protokoll, nicht an einem Eintrag darin.

- **2026-09-05 — Der Wecker stand im Schlafzimmer.** Der stündliche Tageslauf steht in der
  crontab *innerhalb* von WSL. Fährt die VM herunter, kann cron sich nicht selbst wecken.
  Gegen 20:20 verschwand die VM; `uptime` meldete danach 0 Minuten, ein Lauf hing seit
  20:02, 74 Minuten Stillstand. **Das Vorzeichen habe ich abgetan:** Vier Minuten vorher
  scheiterte ein Aufruf mit `Wsl/0x8007000e` („nicht genügend Speicherressourcen"); ich
  fand 15 GB frei *innerhalb* von WSL und nannte es „die Windows-Seite, nicht die Fabrik" —
  richtig gemessen, falsch geschlossen. *Eine Fehlermeldung, deren Ursache man außerhalb
  des eigenen Systems verortet, ist nicht erledigt, sondern unzuständig abgelegt.*

  *Folgerung:* `einrichtung/fabrik-anker.cmd` aus der Windows-Aufgabenplanung, stündlich;
  `wsl.exe` startet die VM, falls sie aus ist. Den Takt gibt es damit zweimal, und das ist
  Absicht: Der eine läuft, solange die VM lebt, der andere weckt sie. **Die Grenze der
  Lösung gehört dazu:** Der Anker hält die VM nicht am Leben, bis zu eine Stunde Arbeit
  kann weiter ausfallen — und `pruefen.sh` kann ihn **nicht** mitprüfen, weil es in WSL
  läuft und `/mnt/c` abgeklemmt ist. Die Aufgabenplanung ist der einzige Teil des Takts,
  den nur der Betreiber kontrollieren kann.

- **2026-09-03 — Der Nachstart von Hand war schlimmer als der verpasste Lauf.** Ich
  startete nach, ohne zu prüfen, ob schon einer läuft; am Ende liefen **vier** Tagesläufe
  gleichzeitig. Das Ergebnis war nicht vierfache Arbeit, sondern fast keine: sechs Läufe an
  einem ganzen Tag, vier davon seit Stunden hängend — sie konkurrieren um dieselben
  Arbeitspakete, um den Git-Index und um das Kontingent. *Folgerung:*
  `ops/tageslauf.sperre` hält eine Prozessnummer, ein zweiter Lauf endet sofort; eine
  verwaiste Sperre wird nach sechs Stunden übernommen. Ohne diese Sperre macht die
  stündliche Crontab-Zeile alles schlimmer statt besser — die beiden Änderungen gehören
  zusammen.

- **2026-09-03 — Logik in einer Cron-Zeile wird beim Schreiben eingebrannt.** Der erste
  Versuch schrieb `$(date +%Y-%m-%d)` in die crontab; durch Shell, Heredoc und `wsl.exe`
  kam das Datum **ausgewertet** an, und die Zeile suchte fortan ewig nach dem Bundle
  desselben Tages. *Folgerung:* Die Cron-Zeile ruft ein Skript im Repo auf, sonst nichts.
  Dort ist die Logik versioniert und einmal prüfbar — `sh -n` hätte den Fehler nie
  gefunden, ein Blick in die Datei schon.

- **2026-09-03 — Ein Skript hieß „Bereitschaft" und veröffentlichte den ganzen
  Arbeitsbereich.** `einrichtung/nachtbereitschaft.sh` begann mit `git add -A`, einem
  `git commit` mit **fest eingebauter** Botschaft vom 2026-08-30 und einem `git push` — ein
  Einmalskript, das als Diagnose weiterlebte. Als ich es zur Kontrolle aufrief, sammelte es
  halbfertige Arbeit ein und schob sie zu GitHub; Commit `95903a6` trägt deshalb einen
  Betreff, der nichts mit seinem Inhalt zu tun hat. *Folgerung:* Das Skript berichtet nur
  noch. Committen macht der Runner, der die Botschaft aus dem Lauf bildet. `pruefen.sh` hat
  eine neue Bedingung: **kein Skript unter `einrichtung/` darf `git add` oder `git commit`
  enthalten.**

- **2026-09-01 — `state.db` von Windows aus geöffnet, Datenbank zerstört, 54
  Journaleinträge verloren.** Ich habe die Datei wiederholt über den UNC-Pfad mit
  `file:state.db?mode=ro&immutable=1` gelesen, während WSL-Prozesse hineinschrieben, und
  einen laufenden Prozess mit `pkill` mitten im Schreiben beendet. Gerettet hat
  `sqlite3 state.db ".recover"` 188 von 242 Zeilen. Verloren ist **Buchhaltung, nicht
  Arbeit**: Alle Ergebnisse liegen in git. *Folgerung:* `state.db` wird ausschließlich aus
  WSL heraus geöffnet (steht in CLAUDE.md). Und allgemeiner: **Ein Lesezugriff, der eine
  Sperre umgeht, ist kein Lesezugriff.** `immutable` und `nolock` sind Optimierungen für
  unveränderliche Dateien, keine Abkürzungen für bequemen Zugriff.

- **2026-09-02 — Eine Prüfung, die importiert statt auszuführen, prüft nichts.**
  `nach-aufraeumen.py` hat `dashboard` erfolgreich importiert und „keine Befunde" gemeldet
  — während dasselbe Skript beim Ausführen scheiterte. Alle dreißig Minuten, still, eine
  Stunde lang. Ein Import beweist, dass eine Datei syntaktisch heil ist, sonst nichts.

- **2026-09-06** — **Die Shell-Grenze der Fabrik gab es nie.** `README.md` und `lehren.md`
  behaupteten seit dem 2026-08-30: „Keine Rolle hat eine Shell", nachgemessen. Gemessen
  war damals etwas anderes — dass ein `Bash(...)`-*Eintrag* jede `Edit()`-Sperre umgeht.
  Daraus wurde der Schluss gezogen, *ohne* Eintrag gebe es keine Shell. Der Schluss war
  falsch: `--allowedTools` **erlaubt vorab, es beschränkt nicht.** Im Modus `dontAsk`
  läuft alles, was nicht ausdrücklich in `--disallowedTools` steht.

  Gemessen am 2026-09-06 mit den exakten Schaltern des `kernbauer`: Umleitung
  (`echo > specs/…`) und `python3 -c` legten Dateien **außerhalb seiner Edit()-Pfade**
  an, null Verweigerungen. Nur `tee` scheiterte — weil `Bash(tee:*)` einzeln in `NIE`
  stand. Die Sperrliste sperrte Befehlsanfänge, die Shell stand offen.

  *Was das erklärt, rückwirkend:* die Schattenkopien des ganzen Vorhabens unter `bau/`,
  den 329-Dateien-Commit, die Logbücher voller Kataloge, „welcher Aufruf durchgeht" (53
  Fassungen in drei Tagen), und die Meldungen „`Write` auf `.cpp` abgelehnt, auf `.md`
  angenommen" — das war der Inhaltsklassifikator des Sandkastens, keine Grenze.

  *Folgerung:* `"Bash"` als Ganzes in `NIE`. Gegenprobe mit denselben drei Wegen: keine
  Datei entsteht. Der Runner erzeugt, was ein Agent an Werkzeugausgabe braucht.

  *Die eigentliche Lehre:* **Eine Grenze, die man nie von der falschen Seite geprüft
  hat, ist eine Vermutung.** Geprüft wurde, ob ein erlaubter Aufruf durchgeht. Nie, ob
  ein verbotener scheitert.

- **2026-09-06** — **Der Dollarwert taugt nicht zur Eichung des Kontingents, und jetzt ist
  es dreimal gemessen.** Drei Ablesungen des Betreibers, drei unvereinbare Hochrechnungen:

  | Zeitpunkt | Journal | Anzeige | daraus „100 %" |
  |---|---:|---:|---:|
  | 2026-09-04 abends | 1.311 $ | 58 % | 2.260 $ |
  | 2026-09-05 mittags | 1.906 $ | 15 % | 12.700 $ |
  | 2026-09-06 vormittags | 2.834 $ | 90 % | 3.150 $ |

  Zwischen der zweiten und dritten Ablesung liegen 928 Dollar und 75 Prozentpunkte —
  daraus folgte ein Kontingent von 1.240 $, während dieselbe Zahl zwei Tage zuvor 12.700
  ergab. Der Tarifwechsel 5x → 20x erklärt einen Teil, nicht das. `kosten_eur` rechnet
  Cache-Tokens mit, die anders gewogen werden: **Die Zahl misst Arbeit, nicht Kontingent.**

  *Folgerung:* Die Grenzen in `lauf.py` sind keine Rationierung mehr, sondern eine
  Notbremse mit Eichdatum. Sie stehen jetzt an der Ablesung vom 2026-09-06 und tragen
  diesen Vermerk. **Die Anzeige des Betreibers ist die einzige Wahrheit.**

- **2026-09-06** — **Es sind zwei Töpfe, nicht einer.** Die Anzeige führt „All models" und
  „Fable" getrennt, und sie leeren sich unabhängig: 90 gegen 56 Prozent am selben Morgen.
  Die Fabrik führte eine gemeinsame Grenze und meldete 8.600 Dollar Spielraum, während im
  bindenden Topf rund 300 übrig waren — sie hätte ihn leergefahren und dem Betreiber
  nichts für die eigene Arbeit gelassen.

  *Folgerung:* `wochenverbrauch(verbindung, topf)` trennt nach dem Modell der Rolle,
  gelesen aus den Rollendateien. Die Notbremse prüft den Topf **des laufenden Agenten**.
  Zwei Grenzen, zwei Eichungen, zwei Vermerke.

  *Die allgemeine Form:* **Eine Grenze, die zwei Dinge zusammenzählt, die getrennt
  laufen, ist keine Grenze.** Sie ist genau dann am blindesten, wenn eines der beiden
  fast leer ist.
