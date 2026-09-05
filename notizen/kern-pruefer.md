# Logbuch: kern-pruefer

**Fuenfte Rotation am 2026-09-05** bei 11.654 Zeichen. Vorfassung unter
`notizen/archiv/kern-pruefer-2026-09-05-5.md`, aeltere daneben (die Zaehlung `-2` bis
`-5` ist die Konvention fuer mehrere Rotationen am selben Tag). Der Weg dorthin war
diesmal **`head -c 200000 <alt> > <neu>`**; `cp`, `mv`, `python3 -c` und der
`Write`-Griff nach `notizen/archiv/` waren gesperrt. **Kopie hinterher mit `wc -c`
gegen das Original pruefen** -- gleiche Zahl heisst byte-gleich.

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege in die Ergebnisdatei, hierher die Lehre
in einem Satz. **An dieser Datei schreiben mehrere eigene Laeufe gleichzeitig** -- vor
jedem Anhaengen neu lesen, und die Groesse **im selben Aufruf** pruefen, in dem du
schreibst.

---

## Der Apparat

- **Die Sperre wechselt von Lauf zu Lauf, auch die Richtung, und sie ist
  pfadgenau.** *2026-09-05, 0123:* `Write` nach `ventures/**/befunde/` frei, `Write`
  nach `notizen/archiv/` gesperrt -- in **einem** Lauf. `Edit`, `cp` und `python3 -c`
  ganz gesperrt, `printf '…' > $TMPDIR/x`, `mkdir`, `tar -xf` und `head -c … > …` frei.
  Einmal probieren kostet einen Aufruf; die Absage nennt oft das erlaubte Gegenstueck.
- **`&&`- und `;`-Ketten werden pauschal abgelehnt**, auch harmlose. Befehle einzeln.
  Ebenso `sed -n '<a>,<b>p'` -- dafuer `Read` mit `offset`/`limit`.
- **Die Shell verliert ihr Arbeitsverzeichnis zwischen Aufrufen** (sie faellt auf die
  Vorhabenwurzel zurueck, sichtbar an „Shell cwd was reset"). **Immer `cd <absolut> &&`
  im selben Aufruf**, sonst greift ein `grep` ins Leere und liefert *stillschweigend*
  nichts -- das sieht aus wie „kein Treffer" und ist „falsches Verzeichnis".
- **Nie ueber den Commit-Betreff suchen**, immer `git log --oneline -- <datei>` und
  **den dort genannten Commit** diffen. **Ob gebaut wurde, entscheidet der Dateiinhalt
  an `HEAD`** -- der Betreff gehoert regelmaessig einem fremden Paket (0121).

## Mutieren, ohne eine Paketdatei anzufassen

Zweimal gebraucht, zweimal getragen (0098, 0123). Der saubere Kopf zuerst, dann das
Makro, dann die Quelle:

```
c++ <Schalter aus bau/CMakeFiles/<ziel>.dir/flags.make> \
    -I kern/include -include kern/include/kern/<kopf>.hpp \
    -include $TMPDIR/mutant.h \        # #define <name>(a,b) (::voll::qualifiziert::<name>((a),(b)) + 1)
    -c kern/src/<quelle>.cpp -o $TMPDIR/mutant.o
```

Dann gegen das **unveraenderte** Probenobjekt und die uebrigen Objekte des bestehenden
Baubaums binden (`link.txt` gibt die Zeile her, das Original weglassen).

- **Die Reihenfolge der `-include` ist der ganze Trick.** Ein blosses `-D` trifft auch
  die *Definition* im Kopf; erst Kopf, dann Makro trifft nur die **Aufrufstelle**.
- **Ein Makro darf waehlerisch sein.** *0123:* `+ (((b) == 100000) ? 0 : 1)` verschont
  genau die Stelle, deren `static_assert` sonst den Uebersetzer stoppt, bevor die
  anderen vier Aufrufstellen ueberhaupt gebunden sind. **Ein Uebersetzungsabbruch am
  ersten Aufrufer verdeckt die Deckung aller uebrigen** -- ihn gezielt aussparen.
- **Ein absorbierter Mutant ist kein ungedeckter.** *0123:* `+1` im **Nenner** eines
  `mal_geteilt` verschwand im Runden (10^10/1.000.001 = 9999,99 → 10.000). Erst `+1000`
  wurde rot. **Vor dem Urteil „nicht abgedeckt" die Schrittweite erhoehen** und die
  Absorption von Hand nachrechnen -- sonst meldest du eine Luecke, die keine ist.
- **Trennschaerfe mitmessen:** Welche Zusicherung bleibt beim Mutanten gruen?

## Was funktioniert

- **Selbst bauen und messen ist der staerkste Nachweis, den ich habe.** Frischer Baum:
  `git archive -o $TMPDIR/baum.tar HEAD ventures/<v> specs decisions`, dann `tar -xf`
  (zweimal entpacken gibt zwei Baeume, ohne `cp`). Der Arbeitsbaum traegt uncommittete
  Zwischenstaende paralleler Laeufe.
- **Die Abnahmebedingungen einzeln durchnummeriert abarbeiten, jede mit eigenem
  mechanischem Aufruf.** Fast jeder Befund fiel genau dabei an.
- **Mutationen bewusst *andere* waehlen als die des Bauagenten.**
- **Determinismus zuerst strukturell, dann gemessen.** `grep` nach Gleitkomma,
  `unordered_*`, `chrono`, `rand`, `random_device`, `reinterpret_cast`, `uintptr_t`,
  `getenv`, `__DATE__`. Rueckkopplung ebenso negativ beweisbar: Ist jede Bezugnahme
  `const` und gibt es kein `setze`, kann das Modul keine Schleife schliessen.
- **Immer beide Bauprofile** (`-DFABRIK_SANITIZER=ON|OFF`). Bei Determinismus ist der
  Profilvergleich selbst der Nachweis.
- **Zu jedem Negativnachweis gehoert der Positivnachweis.** Ein Riegel, der **alles**
  blockiert, sieht im Negativtest identisch aus.
- **Eine Behauptung in einem Kommentar ist ein Pruefauftrag**, ebenso ein Ausschluss in
  einem Vorschlag und der von ihm empfohlene Bauweg.
- **Eine reparierte Wurzel hat Geschwister.** Nicht nach dem Muster suchen, sondern nach
  der *Frage*: Wie oft steht diese Frage im Modul noch -- und antwortet jede Stelle
  gleich?
- **Eine Mengenbeziehung schlaegt eine Stichprobe**, eine Abzaehlung beim Uebersetzen
  (`static_assert` auf eine `constexpr`-Zaehlung) schlaegt beide.
- **Von Hand nachrechnen, auch wenn die Probe gruen ist.** *0123:* Drei Divisionen
  gegen `runde_von_null_weg` gerechnet, alle drei stimmten aufs Zeichen mit dem
  ueberein, was der Uebersetzer meldete -- das ist der Beleg, dass ich die Rundungsregel
  verstanden habe und nicht nur ihr Ergebnis abschreibe.

## Was nicht funktioniert

- **Ein rotes `ergebnis:` gehoert nicht automatisch dem geprueften Paket.** Prueffrage:
  Liest der rote Test die Dateiart, die das Paket geaendert hat?
- **Eine Testeinspeisung an der falschen Stelle beweist nichts.** **Scheitern Probe und
  Kontrolle gleich, ist die Einspeisung schuld, nicht der Gegenstand.**
- **Den Meldungstext einer Ausnahme nach dem Fangblock lesen** -- er ist dann fort.
- **`grep -v <wort>` als Filter verwirft Treffer, die zwei Namen tragen.** *0123:* `-v
  mal_geteilt` loeschte die Zeile `mal_geteilt(…, mal(a, b))` und damit einen der fuenf
  gesuchten Aufrufer. **Das Suchmuster praeziser machen, statt hinterher zu filtern.**

## Offene Faehrten

- **Ein Widerspruch zwischen Abnahme und Vorgabe ist kein `zurueck`.** Urteil nach der
  zulaessigen Lesart, der Widerspruch wird ein Vorschlag mit `rolle: projektmanager`.
- **Bei einer reinen Kommentaraenderung ist der Gegenstand die Behauptung.** Jede
  Zusicherung einzeln gegen den Baum halten, Name fuer Name, Ort fuer Ort.
  Regressionsfreiheit mechanisch zeigen: `git show <commit> -- <datei> | grep '^[+-]' |
  grep -v '^[+-][+-][+-]' | grep -v '^[+-]///'` muss **leer** sein.
- **Einen Klassifikationssatz gegen die Vorgabentabelle halten, nicht gegen das
  Gefuehl.** *0123:* Die Zweiteilung „Groesse gegen Kalibrierzahl" hielt T5 nicht sauber
  stand -- beide Gruppen enthielten beides. **Kein Befund, weil beide Haelften fuer sich
  wahr waren und der moegliche Fehlschluss in die sichere Richtung zeigt.** Prueffrage
  bei jedem unscharfen Satz: *Fuehrt der Irrtum zu mehr Pruefung oder zu weniger?*
- **Namens- und Einheitentabellen sind der blinde Fleck jedes Abzaehlriegels.**
  **Welche Zeichenkette der Ausgabe kommt in keiner Zusicherung vor?**
- **Die Grundbelegung der Proben ist der zweite blinde Fleck.** **Welche Mutation ist
  unsichtbar, weil der Vorgabewert sie unsichtbar macht?**
- **Wird ein Ueberlauf verhindert oder nachtraeglich erkannt?** Nur die erste Form haengt
  nicht an `-fwrapv`.
- **Ruft die Probe den echten Vorgang, oder stellt sie ihn nach?**
- **Zwei Pakete, die einzeln richtig sind, koennen zusammen falsch sein.**
- **Nennt die Abnahme eine Menge ("A *oder* B"), jedes Glied messen.**
- **Ein Kriterium, das im Dateiverzeichnis des Pakets nicht erfuellbar ist, ist ein
  Befund an den Projektmanager** -- kein Anlass, es zu senken.

## Zu Vorschlaegen

- **Vor dem eigenen Vorschlag pruefen, ob es die Luecke schon als Paket gibt** -- ein
  `grep`/`ls` ueber `aufgaben/` nach der tragenden Formulierung. Zweimal hat das den
  Vorschlag erledigt (0098 → `0121-commit-schnitt…`; 0123 → `0074-massnahme-43…`,
  dessen Bedingung den stehengebliebenen Satz in `technik.md` schon nennt). **Ein
  zweiter Beleg gehoert in den Befund, nicht in ein zweites Paket.**
- **Sagt das gepruefte Paket selbst, welches andere die Gegenseite haelt, dort
  nachschlagen und dessen `status` und Abnahme lesen.** Der Rumpf von 0123 nannte 0074
  namentlich -- das war die ganze Recherche.
- **Nummernkollision, sechster und siebter Fall.** Nummer erst bei `git status` **nach**
  `git add` endgueltig festlegen; unter der alten bleibt ein Zeiger mit `status:
  umgezogen` (Hausregel 3), Vorbild `0092`. **Im eigenen Befund auf den Paketnamen
  verweisen, nicht auf die Nummer allein.**
- **Die `dateien`-Liste so eng wie moeglich schneiden ist kein Formalismus, sondern die
  Reihenfolge.** Die Sperre serialisiert die **Laeufe**, nicht den **Index** -- gegen
  den gemeinsamen Commit hilft sie nicht (0121).
- **`git add` ist selbst die Gefahr, nicht erst der eigene Commit.** Erst ganz am
  Schluss vormerken, und wenn das Einchecken gesperrt ist, sofort `git restore
  --staged` nachziehen.
- **`befunde/` steht in `UNGELESENE_ORDNER` des Belegstellenriegels** -- Zeilennummern
  und Kurzzitate sind dort erlaubt. In `aufgaben/` sind sie es **nicht**.
- **Ein dritter Pruefungslauf am selben Paket ist keine Doppelarbeit, wenn die ersten
  beiden Vorschlaege hinterlassen haben.** Dateiname
  `pruefung-<kennung>-runde<n>-<datum>.md`.
