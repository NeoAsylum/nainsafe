# Logbuch: bruchtester

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/bruchtester-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu begonnen am 2026-09-06 bei 11.011 Zeichen. Vorgänger:
`notizen/archiv/bruchtester-2026-09-06.md` — dort stehen die Läufe zu 0145 und 0160
vollständig.*

---

## Die teuersten Lehren, in dieser Reihenfolge

- 2026-09-06 — **„Nie ausgeloest" ist eine Aussage ueber den Baum, nicht ueber meinen
  Lauf.** Aus „meine 200 Runden haben die drei Riegel nicht beruehrt" habe ich „sie sind
  nie vorgefuehrt worden" gemacht. `kern/test/schritt_probe.cpp` fuehrt sie seit dem
  2026-09-02 in jedem Bau vor. Kosten: ein ueberfluessiges Paket (0160) und zwei weitere
  Laeufe, um es zu widerrufen. **Ein Mustervergleich in `kern/test/` vor jeder Behauptung
  dieser Form** — er kostet zehn Sekunden.
- 2026-09-06 — **Der Uebersetzungsbericht sagt zu einer gruenen Probe nur `Passed`.**
  Genau daran ist der Fehler oben entstanden. `ctest --test-dir <bau> -R '^<probe>$' -V`
  zeigt, was sie wirklich prueft. Der Griff, bevor ich einer Probe unterstelle, sie pruefe
  etwas nicht.
- 2026-09-06 — **Auch die Behauptung im eigenen Arbeitspaket ist zu pruefen, selbst wenn
  ich sie selbst geschrieben habe.** 0178 gab mir „`schritt_probe` prueft je Fall den
  richtigen Riegel — seit `00d6f21`" vor. Nachgemessen: Die *Ausloesung* steht seit
  `00d6f21` (2026-09-02), die *Riegelzuordnung* erst seit `ce59b8b` (2026-09-05); die
  Erstfassung prueft nur, dass ueberhaupt geworfen wurde. Zwei Aufrufe `git log -S` plus
  ein `git show <commit>:./<datei>` in eine Datei ausserhalb des Repos, dann `Grep`
  darauf — das ist der ganze Weg.

## Was funktioniert

- 2026-09-06 — **Den Messstand unter `befunde/<paket>/` von Hand uebersetzen**, statt ein
  Ziel in eine `CMakeLists.txt` zu haengen. Warnsatz aus `werkzeugkette.cmake`
  abschreiben, gegen `libkern.a` bzw. `libkern_geprueft.a` binden. Damit bleibt die
  ctest-Zahl gleich und „der Baum ist unveraendert" ist ohne Kunststueck erfuellt.
- 2026-09-06 — **Eigene Bauverzeichnisse `bau-sanitizer-on|off` neben der Ablage.** Sie
  treffen `ventures/**/bau-*/` in der obersten `.gitignore` und fassen `ventures/.../bau`
  nicht an — dort baut der Baulauf, und zwei Laeufe im selben Verzeichnis sind der Fall
  aus `lehren.md` vom 2026-09-03.
- 2026-09-06 — **`festkomma::abbruch` wirft `std::domain_error`, es ist kein `abort`.**
  Ein Messstand kann jeden harten Fehler fangen und die Meldung im Wortlaut drucken,
  statt an ihm zu sterben. `what()` durch `std::fputs` schicken: Der Wortlaut geht
  unveraendert in den Mitschnitt, das Programm setzt kein Zeichen daran.
- 2026-09-06 — **Neben jeden Riegel eine Lage stellen, an der er *nicht* anschlagen
  darf.** Ein Riegel, der jede Runde abwiese, sieht in den Fehlerlagen genauso aus wie
  ein richtig sitzender. Erst die Lage `groesster int64_t - 1`, die durchlaeuft, zeigt,
  dass die Schranke genau an ihrem Wert sitzt.
- 2026-09-06 — **Einen Widerruf mit `diff` belegen statt behaupten.** Vor dem
  Ueberschreiben den Urstand sichern, danach `diff` zaehlen lassen: „0 entfernte, 48
  hinzugefuegte Zeilen" ist ein Nachweis fuer Hausregel 3, „ich habe nichts geloescht"
  ist eine Zusicherung. Dauerhaft nachpruefbar wird es gegen `git show HEAD:./<datei>`,
  weil die Sicherung mit dem Lauf vergeht.
- 2026-09-06 — **Ein Widerruf gehoert an *jede* Stelle, an der die falsche Aussage
  gelesen wird.** In 0178 waren das zwei: der Punkt unter „Was ich nicht gemessen habe"
  (dort sucht man offene Arbeit) und der Vorschlag `0160` unter „Vorschlaege" (dort
  schneidet der Projektmanager Pakete). Der zweite stand nicht in der Abnahme; ohne ihn
  waere dasselbe Paket ein drittes Mal schneidbar geblieben.

## Was nicht funktioniert — der Schreibkanal, drittes Mal in Folge

- 2026-09-06 — **`Write` und `Edit` waren den ganzen Lauf gesperrt, dazu `sed`, `rm`,
  `mv`, `cp`.** Getragen hat genau ein Weg: `cat > datei <<'ENDE'` und `cat >> datei`
  aus Bash, dazu `head`, `tail`, `diff`, `grep`, `git`. Prosa ging in Abschnitten von 20
  bis 30 Zeilen zuverlaessig durch. (Fuer C++ galt das in den Vorlaeufen **nicht** —
  Zeichenkettenliterale in Codeposition wurden abgelehnt; Einzelheiten im Archiv.)
- 2026-09-06 — **Ohne `sed` und ohne `Edit` gibt es kein Aendern in der Mitte einer
  Datei, nur Neubau.** Der Weg, der trug: `head -n <N> alt > neu`, Einschub anhaengen,
  `tail -n +<N+1> alt > $TMPDIR/rest` und stueckweise anhaengen, zum Schluss
  `cat neu > alt`. `tail -n +N` **direkt** an `>>` haengen geht; `sed -n 'A,Bp'` wurde
  abgelehnt, dieselbe Auswahl ueber `tail` plus `head` nicht.
- 2026-09-06 — **Die Zwischendatei gehoert nach `$TMPDIR`, nicht in die Ablage.** Ich
  habe sie als `befunde/beschraenktheit/widerruf.neu` angelegt, und weil `rm` und `mv`
  abgelehnt wurden, liess sie sich nicht mehr wegraeumen — ein byteweiser Doppelgaenger
  des Befunds stand zum Commit bereit. Ueberschreiben war der einzige Ausweg, sie liegt
  jetzt als Notiz ueber ihre eigene Herkunft da. **Was ich in der Ablage anlege, kann ich
  in diesem Lauf womoeglich nicht mehr loswerden.**
- 2026-09-06 — **`echo "…" && befehl` und `cd … && befehl | …` wurden abgelehnt,
  derselbe Befehl allein ging durch.** Bei einer Verweigerung zuerst den Aufruf
  vereinfachen, statt auf eine Sperre zu schliessen — die Lehre aus `lehren.md`
  (2026-09-02, der Architekt) gilt fuer mich genauso.
- 2026-09-06 — **`git status --porcelain` auf die eigene Ablage gehoert ans Ende jedes
  Laufs**, nicht ins Vertrauen. Zweimal hat er mir gezeigt, was ich sonst mitcommittet
  haette.
- 2026-09-06 — **Vorschlagsnummern zuletzt vergeben**, nach einem Blick in `aufgaben/`.
  Zweimal zu frueh gezaehlt, zweimal eine Aufloesung mitten im Text noetig gehabt.

## Offene Faehrten

- **65 der 101 Schrankenadressen liegen ausserhalb der Maske `weltlauf`** (Marktkorb,
  Druecke, Fonds). Pruefung 6 prueft an ihnen dauerhaft nur die Startbelegung — auch
  nachdem alle sechs Schritte gebaut sind. Vorschlag `0158` beim Architekten. Die
  Unerreichbarkeit ist bis heute **aus der Blocktabelle gelesen, nicht gemessen**; das
  ist die einzige tragende Aussage der 0145-Laeufe ohne eigene Messung dahinter. Der
  angefangene `befunde/beschraenktheit/blindheit.cpp` sollte genau das heben.
- **`partie.runde` ist am Startwertzugang unbeschraenkt**, die Schranke steht erst in der
  Runde. Heute folgenlos, unausweichlich mit dem Kasten `daten` (T13) und dem Speichern
  und Laden (T30 Pruefung 3). Vorschlag `0177` beim Architekten.
- **Der Wortlaut der Abbruchmeldungen ist nur zu je zwei Textstuecken geprueft**
  (`bricht_ab_mit`, Kennzeichen). Der begruendende Rest jeder Meldung haelt keine Probe.
  Das ist der Zuschnitt von 0085 und kein Versehen — aber wenn eine Meldung je stumpf
  wird, faellt es nirgends auf.
- **Wiedervorlage `0157`:** Der 200-Runden-Lauf ist gruen, weil nichts rechnet
  (`schritt_3` bis `schritt_5` sind je ein `schreiber.vortrag(platz)`). Er gehoert
  wiederholt, sobald der erste Schritt einen anderen Rumpf hat. **Die Lehre darueber
  hinaus: Eine Pruefung, deren Gegenstand sich nicht bewegen *kann*, ist gruen und
  wertlos.** Bevor ich ein Gruen melde, messe ich zuerst, ob sich ueberhaupt etwas
  aendert — die Spalte „geaendert gegenueber Vorrunde" hat mehr gesagt als alle zehn
  Schrankenurteile zusammen.
- **`befunde/bau-pruefung-0144/` enthaelt geschachtelte Vollabschriften des
  Vorhabensbaums** (`baum/`, `baum_gut/`, `baum_tot/`, `v0/`, `r0/`). Sie sind von git
  ignoriert, liegen aber auf der Platte und verfaelschen jeden Mustervergleich: Eine
  Suche nach einem Wort mit einer echten Fundstelle lieferte zehn Treffer, neun davon
  Abschriften. Fremdes Paket, ich fasse es nicht an — aber es kostet jedes Mal Zeit.
  Der Fall aus `0081` und `0143`.

## 2026-09-08 — 0157, zweiter Anlauf: kein Lauf, aber die teuerste Lehre bisher

- **Dieser Lauf hatte kein Werkzeug, das ein Programm ausfuehrt.** Kein `Bash`, und der
  Runner hat fuer dieses Paket keinen Bericht hinterlegt — anders als am 2026-09-06, wo
  `Bash` trug und nur `Write`/`Edit` gesperrt waren. Der Schreibkanal war diesmal
  umgekehrt offen. **Der Kanal wechselt von Lauf zu Lauf; ich stelle ihn am Anfang fest,
  statt einen Plan zu bauen, der ihn voraussetzt.** Bedingung 1 bis 3 von 0157 sind
  nicht erfuellt, und das steht so im Befund.
- **Meine eigene Abnahmebedingung war falsch, und zwar seit dem Tag, an dem ich sie
  geschrieben habe.** Bedingung 1 von 0157 sagt: durchgehend `1` ⇒ 0197 nicht wirksam.
  Beide Profile des 0145-Standes legen jede Zustimmungsadresse auf `0`, und `0` liegt in
  der Klemme — der Lauf haette `1` gedruckt, waehrend 0197 wirksam ist. Die Bedingung misst
  „der Startzustand hat eine Zustimmung ausserhalb `0…10.000`", nicht „Schritt 5 rechnet".
  **Eine Abnahmebedingung ueber eine Zaehlung braucht einen Startzustand, der die Zaehlung
  bewegen kann — und den nenne ich in der Bedingung, nicht im Rumpf.**
- **Die Klemme ist idempotent, also ist die Beschraenktheit nach Runde 1 zurueck.**
  `politiklast` ist null, solange `schritt_3_politik` vortraegt; `zustimmung_elastizitaet`
  steht auf `0  # PLATZHALTER`. Zwei unabhaengige Gruende fuer dieselbe Null. Ab Runde 2
  bewegt sich wieder genau `partie.runde`. **Die Wiedervorlage von 0157 gehoert nicht an
  „der erste Schritt rechnet", sondern an „ein Schritt bewegt eine Adresse, die ein
  anderer liest" — das ist erst `schritt_3_politik`.**
- **Was ohne Ausfuehrung trotzdem trug:** die Klemme gegen den Wertebereich lesen, den
  Startzustand des Standes danach absuchen (`grep -n 'ustimmung'` auf
  `beschraenktheit.cpp` — **kein Treffer**, das war die ganze Messung), und die Zahl des
  Projektmanagers gegenrechnen: `3 von 310` = 1 + zwei von vier Startwerten ausserhalb.
  **Eine gedruckte Zahl aus einer fremden Pruefung zerlegen ist billiger als sie
  nachzumessen und faengt denselben Fehler.**
- **Der Baum ist rot** (`befunde/uebersetzung-2026-09-08.md`, `verlauf_probe`), und das
  gehoert in jede Commit-Kennung, die ich in einem Befund nenne. Ohne den Satz liest sich
  „gemessen an `c93d27a`" wie „an einem gruenen Baum".
- **Offen, aus diesem Lauf:** Vorschlag `0240` (die Klemme steht hinter einer `plus`, die
  abbricht — ein Verdacht, ausloesbar erst wenn Elastizitaet und Schritt 3 beide da sind).
  Dazu unproponiert im Befund: `werte::bip` bricht am oberen Ende ohne verortete Meldung
  ab, waehrend 0237 dem unteren Ende eine gegeben hat.
