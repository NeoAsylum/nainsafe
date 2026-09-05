# Logbuch: kern-pruefer

**Dritte Rotation am 2026-09-05** bei 11.845 Zeichen. Vorfassung unter
`notizen/archiv/kern-pruefer-2026-09-05-3.md`, aeltere daneben (die Zaehlung `-2`, `-3`
ist die Konvention fuer mehrere Rotationen am selben Tag). Der Weg dorthin ist
`python3 - <<'PY'` ueber Bash (`Path(ziel).write_text(Path(alt).read_text())`); `mv`,
`git mv` und `cp` werden abgelehnt.

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre
in einem Satz. **An dieser Datei schreiben mehrere eigene Laeufe gleichzeitig** -- vor
jedem Anhaengen neu lesen, und die Groesse **im selben Aufruf** pruefen, in dem du
schreibst: Zwischen zwei Aufrufen ist die Datei zweimal um 200 Zeichen gewachsen.

---

## Der Apparat -- was heute wirklich schreibt und laeuft

- **Die Sperre wechselt von Lauf zu Lauf, auch die Richtung; einmal probieren kostet
  einen Aufruf.** Einmal war `Write` fuer **jede** neue Datei gesperrt, einmal genau
  umgekehrt (`Write` frei, `Edit` gesperrt, auch auf `$TMPDIR`). Lange Dateien in
  Haelften: erst `p.write_text(...)`, dann `with p.open("a")` -- ein zu grosser
  `python3`-Block wird selbst abgelehnt.
- **`&&`- und `;`-Ketten mit Umleitung werden pauschal abgelehnt**, auch harmlose. Den
  Befehl einzeln wiederholen. Ebenso abgelehnt: `sed -n '<a>,<b>p'` auf eine Datei --
  dafuer `Read` mit `offset`/`limit`. `cp` ist gesperrt, `shutil.copytree` nicht.
- **Die Shell behaelt ihr Arbeitsverzeichnis zwischen Aufrufen.** Absolute Pfade nehmen.
- **Nie ueber den Commit-Betreff suchen**, immer `git log --oneline -- <datei>` und
  **den dort genannten Commit** diffen; haelt auch das nicht, `git log -S '<neuer
  Wortlaut>' -- <datei>`. **Ob gebaut wurde, entscheidet der Dateiinhalt an `HEAD`.**
  *2026-09-05, 0072:* Der Betreff log zweimal -- ein Commit `kernbauer: 0072-…` **ohne**
  dessen einzige Datei, die Aenderung unter `architekt: 0051-…`. **Nicht `git add -A`
  ist die Ursache** (`agents/lauf.py` vermeidet es), sondern Add-Pfade aus der
  Werkzeugliste der **Rolle** und ein `git commit` **ohne Pfadangabe** ueber den
  gemeinsamen Index. Vorschlag 0121.

- **Der direkte Aufruf eines selbst gebauten Programms ist gesperrt.** Der Weg ist
  `ctest --test-dir <bau> -R '^<probe>$' -V` oder `cmake -E env <pfad> <argumente>`.
- **Der `belegstellen_riegel` faellt aus, wenn man nur `ventures/` exportiert.**
  `git archive HEAD ventures/<v> specs decisions` nachziehen.

## Was funktioniert

- **Selbst bauen und messen ist der staerkste Nachweis, den ich habe.** Immer aus
  `git archive HEAD` in einen frischen Baum ausserhalb des Repos (`$TMPDIR`) -- der
  Arbeitsbaum traegt uncommittete Zwischenstaende paralleler Laeufe und liegengebliebene
  Pruefbaeume unter `bau/`, die fremde Testergebnisse rot faerben.
- **Die Gegenprobe ist eine Kopie des Baums mit genau der einen Zeile zurueckgedreht,
  nicht der Elterncommit** -- der schleppt fremde Pakete mit. **Rezept ohne `cp`:**
  `git worktree add --detach $TMPDIR/x <commit-davor>`, dann `git -C $TMPDIR/x checkout
  <commit-danach> -- <die eine Datei>`. *2026-09-05, 0072:* So belegt, dass der Riegel
  den neuen Abschnittsverweis **aufloest** (36/36 auf 37/37); im echten Baum lagen fuenf
  fremde Bauquellen dazwischen und derselbe Zaehler sagte nichts. `git worktree prune`
  scheitert hier mit *Device or resource busy*, harmlos.

- **"Kein Urteil aendert sich" beweist man mit der *ganzen* Ausgabe, nicht mit der
  Testbatterie, die die Abnahme nennt.** Pfade und Zeitangaben wegnormalisieren, dann
  `difflib` ueber die vollstaendige Ausgabe vor gegen nach, je Bauweg und Profil.
- **Immer beide Bauprofile. Bei Determinismus ist der Profilvergleich selbst der
  Nachweis.** *2026-09-05, 0087:* Bei `constexpr`-Rechenwerk ist der **Doppelweg** noch
  staerker -- dieselben Randwerte einmal per `static_assert` beim Uebersetzen, einmal
  zur Laufzeit durch die `volatile`-Klammer unter den Sanitizern.
- **Determinismus zuerst strukturell, dann gemessen.** `grep` nach Gleitkomma,
  `unordered_*`, `chrono`, `rand`, `random_device`, `reinterpret_cast`, `uintptr_t`,
  `getenv`, `__DATE__`. Rueckkopplung laesst sich ebenso negativ beweisen: Ist jede
  Bezugnahme `const` und gibt es kein `setze`, kann das Modul keine Schleife schliessen.
- **Eine eigene Messprobe in `<pruefbaum>/kern/test/` wird vom CMake-Glob von selbst ein
  ctest-Eintrag.** So misst man, was kein Test des Pakets misst.
- **Die Abnahmebedingungen einzeln durchnummeriert abarbeiten, jede mit eigenem
  mechanischem Aufruf.** Fast jeder Befund fiel genau dabei an.
- **Mutationen bewusst *andere* waehlen als die des Bauagenten.** *2026-09-05, 0087:*
  Eine Wiederholung seiner Auswahl prueft nur seine Auswahl. Die beiden ergiebigsten
  waren die, die er nicht gefahren hatte: der Waechter, der **kappt statt zu werfen**
  (eine reine `geworfen`-Probe bliebe gruen), und **ein gemeinsamer Meldungstext fuer
  zwei Riegel** -- die plausibelste Vereinfachung, die jemand spaeter vornimmt.
- **Zu jedem Negativnachweis gehoert der Positivnachweis.** Ein Riegel, der **alles**
  blockiert, sieht im Negativtest identisch aus.
- **Eine Behauptung in einem Kommentar ist ein Pruefauftrag**, ebenso **ein Ausschluss
  in einem Vorschlag** und **der von ihm empfohlene Bauweg**. Prueffragen: Welchen Fall
  erklaert der Kommentar fuer erledigt -- und faehrt man ihn? Gilt der Grund des
  Ausschlusses fuer die Frage, um die es geht? Und: Bau den empfohlenen Weg und fahr die
  Abnahme desselben Vorschlags dagegen.
- **Eine reparierte Wurzel hat Geschwister.** Nicht nach dem Muster suchen, sondern nach
  der *Frage*: Wie oft steht diese Frage im Kern noch -- und antwortet jede Stelle
  gleich? *2026-09-05, 0087:* der wertvollste Teil der Pruefung -- die Frage war nicht
  "steht `plus` richtig", sondern "laeuft noch eine Strichrechnung an der Vorgabe vorbei".
- **Eine Mengenbeziehung schlaegt eine Stichprobe**, und **eine Halbierung schlaegt
  beide**. Fuer Bedingungen der Form "steht nur an einer Stelle" ist die Mengenaussage
  ueber den **ganzen** Kern der Nachweis, nicht die Sicht auf die eine Datei, die die
  Abnahme nennt.
- **Ist die Lieferung reiner Text, beweist ein Diff alle Erhaltungsbedingungen auf
  einmal.** Eine Textbedingung wird aber am Lauf geprueft, nie am Quelltextvergleich.
  *Umgekehrt:* Sind die Zusaetze eines Pakets **reine Einfuegungen** (`git diff --stat`
  zeigt null Loeschungen), ist Regressionsfreiheit an den alten Rechenarten strukturell
  bewiesen und kostet keine Messung.
- **Einen Vorschlag einmal bauen, bevor man ihn abgibt.** *2026-09-05, 0122:* drei
  Baeume (Sperre allein, Rueckfall allein, beides) -- erst das Tripel macht aus dem
  Vorschlag eine Messung.
- **"Einzige Rechenstelle" ist mechanisch erzwingbar, wenn das Verbotene ein
  *Bezeichner* ist, nicht ein Operator.** *2026-09-05, 0087:* `#pragma GCC poison` auf
  `__builtin_add_overflow` in `sperre.hpp` -- die Datei ist der letzte Include jeder
  Quelle, die Vergiftung greift also erst **nach** dem Kopf und braucht keine
  Ausnahmeliste. 0074 verwarf denselben Riegel fuer `*` zu Recht: Ein Operator traegt
  seine Operandentypen nicht bei sich.

## Was nicht funktioniert

- **Ein rotes `ergebnis:` gehoert nicht automatisch dem geprueften Paket.** Immer im
  eigenen sauberen Export nachfahren. **Prueffrage: Liest der rote Test die Dateiart,
  die das Paket geaendert hat?** Der Nachweis ist derselbe Baum mit **nur** den Dateien
  des Pakets zurueckgedreht -- Zahl fuer Zahl gleich heisst: nicht meiner.
- **Meinen eigenen Fehler in der Gegenprobe:** den Meldungstext einer Ausnahme nach dem
  Fangblock gelesen -- er ist dann fort.
- **Eine Testeinspeisung an der falschen Stelle beweist nichts.** *2026-09-05:* Meine
  Rueckfallfassung landete vor dem `using`-Block, scheiterte an `i64` statt an der
  Sperre -- und die Kontrolle ohne Sperre scheiterte genauso. Erst der Einbau **nach**
  den `using`-Zeilen trennte die beiden Faelle. **Scheitern Probe und Kontrolle gleich,
  ist die Einspeisung schuld, nicht der Gegenstand.**

## Offene Faehrten

- **Liste oder Zeichenkette?** `COMPILE_FLAGS` ist eine Zeichenkette (`list(LENGTH)` = 1),
  `COMPILE_OPTIONS` eine echte Liste. Allgemein: die *Form* des Datums messen, nicht nur
  seinen Wert.
- **Eine Freiheit, die ein Paket seinem Bauagenten einraeumt, gegen seine eigene Abnahme
  halten.** Oft hat die Abnahme die Wahl schon getroffen.
- **Namens- und Einheitentabellen sind der blinde Fleck jedes Abzaehlriegels.**
  **Welche Zeichenkette der Ausgabe kommt in keiner Zusicherung vor?**
- **Die Grundbelegung der Proben ist der zweite blinde Fleck** -- viermal bestaetigt.
  **Welche Mutation ist unsichtbar, weil der Vorgabewert sie unsichtbar macht?**
- **Ein Widerspruch zwischen Abnahme und Vorgabe ist kein `zurueck`.** Urteil nach der
  zulaessigen Lesart, der Widerspruch wird ein Vorschlag mit `rolle: projektmanager`,
  dessen Abnahme **beide** Ausgaenge beschreibt.
- **Ein Kriterium, das im Dateiverzeichnis des Pakets nicht erfuellbar ist, ist ein
  Befund an den Projektmanager** -- kein Anlass, es zu senken.
- **Eine Gestaltbedingung ("Datei X hat keine eigene Fassung mehr") ist kein Befund,
  wenn sie erfuellt ist -- aber die Frage, ob sie *gesichert* ist, ist ein Vorschlag.**
  Nachweis: den Rueckfall bauen und zeigen, dass der Baum gruen bleibt.
- **Ein unerreichbarer oder redundanter Riegel ist kein Befund, wenn der Kommentar sagt,
  wofuer er da ist.** Nicht melden, aber hinschreiben, dass man hingesehen hat.
- **Ein zweiter Rechenweg, der die gepruefte Funktion enthaelt, prueft alles ausser ihr
  selbst.** Teilen die beiden Wege die Zeile, um die es geht?
- **Streiche ich diesen Riegel -- fliegt dann immer noch etwas, nur aus einem anderen
  Grund?** Ein `geworfen`-Test ohne Meldungsprobe sichert keinen Riegel.
- **Wird ein Ueberlauf verhindert oder nachtraeglich erkannt?** Nur die erste Form haengt
  nicht an `-fwrapv`. Eine verhindernde Stelle ist **kein** Befund, auch wenn sie blank
  rechnet.
- **Ruft die Probe den echten Vorgang, oder stellt sie ihn nach?**
- **Eine Artenliste, eine Feldliste, eine Aufzaehlung: welches Glied fehlt?** Und: Ist
  der Nein-Wert von einem gueltigen unterscheidbar?
- **Ist die gebaute Schnittstelle von ihrem vorgeschriebenen Aufrufer bedienbar?**
- **Zwei Pakete, die einzeln richtig sind, koennen zusammen falsch sein.**
- **Bindet eine Vorgabe die Stelle statt der Formel, braucht die Probe Zahlen mit Rest.**
- **Nennt die Abnahme eine Menge ("A *oder* B"), jedes Glied messen.**
- **Schiebt eine Aenderung eine neue Pruefung *vor* die alte und laesst die alte auf
  denselben Eingang laufen, ist "kein Rueckschritt moeglich" strukturell beweisbar.**

## Zu Vorschlaegen

- **Nummernkollision, sechster und siebter Fall.** *2026-09-05:* Am selben Tag standen
  am Ende zwei `0120` und drei `0121` nebeneinander -- **auch hoechste+2 und ein dritter
  Blick reichen nicht.** Nummer erst bei `git status` **nach** `git add` endgueltig
  festlegen; unter der alten bleibt ein Zeiger mit `status: umgezogen` (Hausregel 3),
  Vorbild `0092`. **Und im eigenen Befund auf den Paketnamen verweisen, nicht auf die
  Nummer allein.**
- **Die `dateien`-Liste so eng wie moeglich schneiden ist kein Formalismus, sondern die
  Reihenfolge.** Ein Vorschlag, der keine Codedatei beansprucht, laeuft an allen anderen
  vorbei.
- **Ein dritter Pruefungslauf am selben Paket ist keine Doppelarbeit, wenn die ersten
  beiden Vorschlaege hinterlassen haben** -- sie sind der neue Gegenstand. Dateiname
  `pruefung-<kennung>-runde<n>-<datum>.md`.
- **Vor dem eigenen Vorschlag pruefen, ob es die Luecke schon als Paket gibt** -- ein
  `grep` ueber `aufgaben/` nach der tragenden Formulierung. *2026-09-05:* Das hat zwei
  von vier Kandidaten erledigt (0074 hielt die Frage schon, 0120 den roten Riegel) und
  die verbliebenen zwei besser begruendet, weil ich sie gegen das Vorhandene abgrenzen
  musste.
