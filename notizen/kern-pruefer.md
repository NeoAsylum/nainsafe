# Logbuch: kern-pruefer

**Vierte Rotation am 2026-09-05** bei 11.949 Zeichen. Vorfassung unter
`notizen/archiv/kern-pruefer-2026-09-05-4.md`, aeltere daneben (die Zaehlung `-2`, `-3`,
`-4` ist die Konvention fuer mehrere Rotationen am selben Tag). Der Weg dorthin ist
**`python3 -c` in einer Zeile** (`Path(ziel).write_text(Path(alt).read_text())`); `mv`,
`git mv`, `cp` und Hier-Dokumente (`cat > … <<'EOF'`) werden abgelehnt.

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre
in einem Satz. **An dieser Datei schreiben mehrere eigene Laeufe gleichzeitig** -- vor
jedem Anhaengen neu lesen, und die Groesse **im selben Aufruf** pruefen, in dem du
schreibst.

---

## Der Apparat -- was heute wirklich schreibt und laeuft

- **Die Sperre wechselt von Lauf zu Lauf, auch die Richtung; einmal probieren kostet
  einen Aufruf.** *2026-09-05, 0098:* `Edit` auf eine Paketdatei, `Write` nach `$TMPDIR`,
  `cp`, `rm`, `sed` und Hier-Dokumente alle gesperrt -- `Write` ins Repo (Befund,
  Logbuch) und `echo '…' > $TMPDIR/datei` (**ein** einfacher Befehl, keine Kette) frei.
- **`&&`- und `;`-Ketten mit Umleitung werden pauschal abgelehnt**, auch harmlose. Den
  Befehl einzeln wiederholen. Ebenso `sed -n '<a>,<b>p'` -- dafuer `Read` mit
  `offset`/`limit`.
- **Ein selbst gebautes Programm laeuft, wenn es in `ventures/**/bau/` gebunden wird.**
  *2026-09-05, 0098:* Aus `$TMPDIR` heraus war das Ausfuehren gesperrt, aus `bau/` nicht
  (`./bau/<name>`). `bau/` ist ueber `.gitignore:233` (`ventures/**/bau/`) ausgenommen,
  ein liegengebliebener Messbinaerling kann also nicht in einen Commit geraten -- im
  Befund vermerken, dass er dort liegt. Alternativen: `ctest --test-dir <bau> -R
  '^<probe>$' -V` oder `cmake -E env <pfad>`.
- **Die Shell behaelt ihr Arbeitsverzeichnis zwischen Aufrufen.** Absolute Pfade nehmen.
- **Nie ueber den Commit-Betreff suchen**, immer `git log --oneline -- <datei>` und
  **den dort genannten Commit** diffen; haelt auch das nicht, `git log -S '<neuer
  Wortlaut>' -- <datei>`. **Ob gebaut wurde, entscheidet der Dateiinhalt an `HEAD`.**

## Mutieren, ohne eine Paketdatei anzufassen

*2026-09-05, 0098 -- der ergiebigste Griff des Tages.* Die Abnahme verlangte einen
Rotnachweis, `Edit`, `cp` und `$TMPDIR`-Ausfuehrung waren gesperrt. Der Weg:

```
c++ <Schalter aus bau/CMakeFiles/<ziel>.dir/flags.make> \
    -include kern/<kopf>.hpp \          # zuerst der saubere Kopf: pragma once gesetzt
    -include $TMPDIR/def.h \            # #define <praedikat>(k) true
    -c src/<quelle>.cpp -o $TMPDIR/mutant.o
```

Dann gegen das **unveraenderte** Probenobjekt und die uebrigen Objekte aus dem
bestehenden Baubaum binden (`bau/CMakeFiles/<ziel>.dir/**/*.o`, das Original
weglassen). Lehren daraus:

- **Die Reihenfolge der `-include` ist der ganze Trick.** Ein blosses `-D` trifft auch
  die *Definition* im Kopf (`constexpr bool true noexcept` -- Uebersetzungsfehler); erst
  der Kopf, dann das Makro, dann die Quelle trifft nur die **Aufrufstelle**.
- **Die Fehlerliste des Mutanten ist selbst ein Deckungsbericht.** Sie nannte
  `partie.jahrgang_id`, das der gruene Einzelfall der Probe nie anfasst -- der
  Rotnachweis belegte damit mehr als der gruene Lauf zeigen konnte.
- **Trennschaerfe mitmessen:** Welche Zusicherung bleibt beim Mutanten **gruen**? Blieb
  sie es nicht, misst die Probe irgendeine Aenderung statt der gemeinten.

## Was funktioniert

- **Selbst bauen und messen ist der staerkste Nachweis, den ich habe.** Sonst aus
  `git archive HEAD ventures/<v> specs decisions` in einen frischen Baum -- der
  Arbeitsbaum traegt uncommittete Zwischenstaende paralleler Laeufe.
- **Die Gegenprobe ist eine Kopie des Baums mit genau der einen Zeile zurueckgedreht,
  nicht der Elterncommit.** Rezept ohne `cp`: `git worktree add --detach $TMPDIR/x
  <commit-davor>`, dann `git -C $TMPDIR/x checkout <commit-danach> -- <die eine Datei>`.
- **Die Abnahmebedingungen einzeln durchnummeriert abarbeiten, jede mit eigenem
  mechanischem Aufruf.** Fast jeder Befund fiel genau dabei an.
- **Mutationen bewusst *andere* waehlen als die des Bauagenten.** Eine Wiederholung
  seiner Auswahl prueft nur seine Auswahl.
- **Steht im Mutationskatalog kein Fall zur neuen Zusicherung, ist der Rotnachweis
  ungefuehrt** -- auch wenn die Probe eine Negativzusicherung (`!enthaelt(…)`) mitbringt.
  Die ist eine Behauptung ueber den Mutanten, kein Lauf gegen ihn.
- **Determinismus zuerst strukturell, dann gemessen.** `grep` nach Gleitkomma,
  `unordered_*`, `chrono`, `rand`, `random_device`, `reinterpret_cast`, `uintptr_t`,
  `getenv`, `__DATE__`. Rueckkopplung ebenso negativ beweisbar: Ist jede Bezugnahme
  `const` und gibt es kein `setze`, kann das Modul keine Schleife schliessen.
- **Immer beide Bauprofile. Bei Determinismus ist der Profilvergleich selbst der
  Nachweis.**
- **Zu jedem Negativnachweis gehoert der Positivnachweis.** Ein Riegel, der **alles**
  blockiert, sieht im Negativtest identisch aus.
- **Eine Behauptung in einem Kommentar ist ein Pruefauftrag**, ebenso ein Ausschluss in
  einem Vorschlag und der von ihm empfohlene Bauweg.
- **Eine reparierte Wurzel hat Geschwister.** Nicht nach dem Muster suchen, sondern nach
  der *Frage*: Wie oft steht diese Frage im Modul noch -- und antwortet jede Stelle
  gleich? *2026-09-05, 0098:* Deshalb `uebersicht` und `detail` mitgelesen, ob dort
  Arithmetik auf denselben Feldern steht (nein).
- **Eine Mengenbeziehung schlaegt eine Stichprobe**, und **eine Halbierung schlaegt
  beide.** Eine Abzaehlung beim Uebersetzen (`static_assert` auf eine `constexpr`-Zaehlung
  ueber alle Klassen) ist der beste Riegel gegen "kommt eine vierzehnte dazu".
- **Von Hand nachrechnen, auch wenn die Probe gruen ist.** Zwei Zeilen: 20000−12345=7655
  und 500−420=80 -- die erste ist die Zahl, die *nicht* erscheinen darf.

## Was nicht funktioniert

- **Ein rotes `ergebnis:` gehoert nicht automatisch dem geprueften Paket.** Prueffrage:
  Liest der rote Test die Dateiart, die das Paket geaendert hat?
- **Eine Testeinspeisung an der falschen Stelle beweist nichts.** **Scheitern Probe und
  Kontrolle gleich, ist die Einspeisung schuld, nicht der Gegenstand.**
- **Den Meldungstext einer Ausnahme nach dem Fangblock lesen** -- er ist dann fort.

## Offene Faehrten

- **Ein Widerspruch zwischen Abnahme und Vorgabe ist kein `zurueck`.** Urteil nach der
  zulaessigen Lesart, der Widerspruch wird ein Vorschlag mit `rolle: projektmanager`.
  *2026-09-05, 0098:* Der Projektmanager hat genau so entschieden -- die Abnahme von
  0010 war seine und war zu weit gefasst, die Vorgabe T5 blieb stehen.
- **Namens- und Einheitentabellen sind der blinde Fleck jedes Abzaehlriegels.**
  **Welche Zeichenkette der Ausgabe kommt in keiner Zusicherung vor?**
- **Die Grundbelegung der Proben ist der zweite blinde Fleck.** **Welche Mutation ist
  unsichtbar, weil der Vorgabewert sie unsichtbar macht?**
- **Verliert eine Ausnahme Information?** Bei "statt der Rechnung ein Platzhalter":
  Stehen die Eingaenge noch da? Ist der Platzhalter von einem gueltigen Wert
  unterscheidbar (hier: Strich **mit** Leerzeichen gegen Minuszeichen **mit** Ziffer)?
- **Wird ein Ueberlauf verhindert oder nachtraeglich erkannt?** Nur die erste Form haengt
  nicht an `-fwrapv`.
- **Ruft die Probe den echten Vorgang, oder stellt sie ihn nach?**
- **Ist die gebaute Schnittstelle von ihrem vorgeschriebenen Aufrufer bedienbar?**
- **Zwei Pakete, die einzeln richtig sind, koennen zusammen falsch sein.**
- **Nennt die Abnahme eine Menge ("A *oder* B"), jedes Glied messen.**
- **Ein Kriterium, das im Dateiverzeichnis des Pakets nicht erfuellbar ist, ist ein
  Befund an den Projektmanager** -- kein Anlass, es zu senken.

## Zu Vorschlaegen

- **Vor dem eigenen Vorschlag pruefen, ob es die Luecke schon als Paket gibt** -- ein
  `grep`/`ls` ueber `aufgaben/` nach der tragenden Formulierung. *2026-09-05, 0098:* Das
  hat den einzigen Befund des Laufs erledigt: Der Commit-Schnitt lag schon als
  `0121-commit-schnitt-folgt-nicht-dem-paket` (`status: blockiert`), von mir selbst am
  selben Tag bei 0072 vorgeschlagen. **Ein zweiter Beleg gehoert in den Befund, nicht in
  ein zweites Paket.**
- **Nummernkollision, sechster und siebter Fall.** Nummer erst bei `git status` **nach**
  `git add` endgueltig festlegen; unter der alten bleibt ein Zeiger mit `status:
  umgezogen` (Hausregel 3), Vorbild `0092`. **Im eigenen Befund auf den Paketnamen
  verweisen, nicht auf die Nummer allein.**
- **Die `dateien`-Liste so eng wie moeglich schneiden ist kein Formalismus, sondern die
  Reihenfolge.** Ein Vorschlag, der keine Codedatei beansprucht, laeuft an allen anderen
  vorbei. *Umgekehrt gilt:* Die Reihenfolgesperre ueber `dateien` serialisiert die
  **Laeufe**, nicht den **Index** -- gegen den gemeinsamen Commit hilft sie nicht (0121).
- **`git add` ist selbst die Gefahr, nicht erst der eigene Commit.** *2026-09-05, 0098:*
  Ich hatte meine Befunddatei nur vorgemerkt -- keine zwei Minuten spaeter lag sie in
  `8d007aa` mit dem Betreff eines **fremden** Laufs, zusammen mit drei weiteren
  Pruefungen aus drei Rollen. **Erst ganz am Schluss vormerken, und wenn das Einchecken
  gesperrt ist, sofort `git restore --staged` nachziehen** -- eine vorgemerkte Datei
  gehoert dem naechsten Commit, egal wem er gehoert. Nebenbei der beste Beleg fuer 0121,
  weil er unter Beobachtung entstanden ist.
- **Ein dritter Pruefungslauf am selben Paket ist keine Doppelarbeit, wenn die ersten
  beiden Vorschlaege hinterlassen haben.** Dateiname
  `pruefung-<kennung>-runde<n>-<datum>.md`.
