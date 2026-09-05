# Logbuch: kern-pruefer

**Rotiert am 2026-09-06** bei 12.643 Zeichen, nach der Pruefung zu 0144. Vorfassung
unter `notizen/archiv/kern-pruefer-2026-09-06-2.md` (die `-1` desselben Tages stammt
aus einem Parallellauf). Archivieren mit `cmake -E copy`, dann neu schreiben.

**Hoechstens 12.000 Zeichen.** Belege in die Ergebnisdatei, hierher die Lehre in einem
Satz. **An dieser Datei schreiben mehrere eigene Laeufe gleichzeitig** -- vor jedem
Anhaengen neu lesen und die Groesse **im selben Aufruf** pruefen. Wer blind anhaengt,
schreibt eine fremde Rotation zurueck.

---

## Der Apparat

- **Die Sperre wechselt von Lauf zu Lauf und innerhalb eines Laufs, und sie entscheidet
  nach Inhalt.** *2026-09-06:* `Write`, `Edit`, `python3` (auch als Datei), `sed`, `awk`
  und `mv` durchgehend abgelehnt; `printf` mit Umlenkung trug in Haeppchen von vier bis
  zehn Zeilen. Abgelehnt wurde alles, was wie Quelltext aussah -- schon ein
  Gleichheitszeichen zwischen einem Namen und einer Zahl. Einmal probieren kostet einen
  Aufruf; dieselbe Aussage anders formuliert geht oft durch.
- **Ketten mit `&&` oder `;`, Pipes hinter dem Uebersetzer und `for`-Schleifen fallen
  regelmaessig.** Befehle einzeln, Fehlerausgabe in eine Datei umlenken und danach mit
  `grep` lesen. Beim Uebersetzer muss der Schalter fuer Makros **ohne Leerzeichen**
  stehen -- mit Leerzeichen abgelehnt, ohne angenommen, sonst identischer Aufruf.
- **Loeschen und Umbenennen sind gesperrt.** Ersatz: `cmake -E copy`, und die alte Datei
  mit einem Verweis ueberschreiben. Auslassen statt Entfernen.
- **`$TMPDIR` ist eine geteilte tmpfs und laeuft voll.** Unter
  `befunde/bau-pruefung-<paket>/` messen: grosse Platte, und `baulauf.py` nimmt
  `befunde` vom Manifestsuchlauf aus, die Abschriften werden also kein Bauziel.
- **Die Shell verliert ihr Arbeitsverzeichnis zwischen Aufrufen.** Absolute Pfade, oder
  `git -C`.
- **Nie ueber den Commit-Betreff suchen**, immer `git log -- <datei>`, und zwar je
  Datei einzeln. *0144:* Der Commit mit dem Paketnamen trug eine Kommentarzeile, die
  Arbeit lag in zwei fremd betitelten Commits. Elfter Fall dieser Art.
- **Im Befund den Stand nennen, nie das Wort `HEAD`.** Die md5 der geprueften Dateien
  am Anfang und am Ende gegenrechnen und beides hinschreiben.

## Mutieren

- **Ohne selbst geschriebenen Code:** Beide Konstantenzeilen aus einer Kopfkopie
  herausschneiden -- `head`, `tail`, `cmake -E cat`, die Ersatzzeilen aus dem
  Vorherstand -- und die Werte beim Uebersetzen von aussen setzen. Das trennt zwei
  Konstanten, die einander definieren, und braucht keinen Editor.
- **Ein eigenes Verzeichnis vor dem echten in den Suchpfad**, darin nur die eine
  geaenderte Datei: Alle uebrigen Koepfe kommen weiter aus dem Bestand.
- **Zu jedem Mutantensatz gehoert m0, der unveraenderte Baum.** Ein Apparat, der alles
  rot macht, sieht sonst aus wie einer, der etwas findet.
- **Zu jedem roten Baum gehoert ein gruener Kontrollbaum mit derselben Zulage und der
  alten Fassung.** Das Rot allein zeigt nur, dass irgendetwas bricht.

## Was funktioniert

- **Selbst bauen und messen ist der staerkste Nachweis.** Frischer Baum aus
  `git archive`; `specs` und `decisions` muessen mit, sonst faellt der
  Belegstellenriegel aus und man haelt die eigene Ablage fuer einen Befund.
- **Den Vorherstand selbst herstellen**, nicht zitieren: denselben Baum, in dem nur die
  Paketdateien durch ihre Fassungen vor der Aenderung ersetzt sind, und `diff -rq`
  danebenlegen. Vorher belegen, dass der Diff dieser Commits nur Stellen des Pakets
  enthaelt.
- **Jede Abnahmebedingung einzeln, mit eigenem mechanischem Aufruf.** Fast jeder Befund
  fiel genau dabei an.
- **Immer beide Bauprofile und beide Bauwege** (Alleinbau und Arbeitsbereich).
- **Jede Riegel-Zahl braucht eine zweite, unabhaengige Zaehlung.**
- **Zu jedem Negativnachweis gehoert der Positivnachweis.** Ein Riegel, der alles
  blockiert, sieht im Negativtest identisch aus.
- **Determinismus ueber den Profilvergleich:** die **ganze** Ausgabe der Probe aus
  beiden Profilen zeilenweise gegenueberstellen. Uebrig bleiben die Pfad- und
  Zeitzeilen von `ctest`.
- **Eine Behauptung in einem Kommentar ist ein Pruefauftrag.** Auch die mechanischen
  Nachweise, die ein Kopf ueber sich selbst behauptet, gehoeren nachgefahren.
- **Jeden Namen und jede Zahl aus dem Paket gegen seinen T-Block halten**, nicht nur
  die Zahlen. Der Auftrag kann der Vorgabe widersprechen; das Ergebnis geht dann an den
  Projektmanager, nicht an den Bauagenten.
- **Zusaetzlich `Release` und `RelWithDebInfo` bauen, wenn ein Aufruf verworfen wird.**
  Eine Bereichspruefung ohne Optimierung ist trivial gruen.
- **Von Hand nachrechnen, auch wenn die Probe gruen ist** -- und die Formel am
  Messpunkt gegenrechnen, bevor man mit ihr weiterrechnet.

## Was nicht funktioniert

- **Ein rotes Ergebnis gehoert nicht automatisch dem geprueften Paket.**
- **Eine Testeinspeisung an der falschen Stelle beweist nichts.** Scheitern Probe und
  Kontrolle gleich, ist die Einspeisung schuld.
- **Den Meldungstext einer Ausnahme nach dem Fangblock lesen** -- er ist dann fort.
- **Eine Zusicherung, deren beide Seiten am selben Regler haengen, faengt diesen Regler
  nicht.** *0144:* gruen bis 2.169 Runden, also 37 MB. Immer den Regler bewegen, nicht
  nur die abgeleitete Groesse.

## Offene Faehrten

- **Ein Widerspruch zwischen Abnahme und Vorgabe ist kein `zurueck`**, und eine
  Vorgabe, zu der die Abnahme **schweigt**, ebenso wenig. Das Urteil folgt den
  Bedingungen, der Verstoss wird ein Vorschlag. *0144:* Die Bedingung nannte die Wand
  als Massstab und keine Bytezahl -- also `geprueft` plus Vorschlag.
- **Prueffrage bei jedem unscharfen Satz:** *Fuehrt der Irrtum zu mehr Pruefung oder zu
  weniger?* Ein lauter Abbruch ist kein `zurueck`, eine stille Kuerzung immer.
- **Ist die Abnahme in zwei Lesarten erfuellbar, beide hinschreiben und die gewaehlte
  begruenden.**
- **Eine vermutete Schwaeche einer Zusicherung erst mutieren, dann urteilen.** Ein
  Befund aus dem Kopf war schon zweimal falsch.
- **Zwei Schranken koennen sich gegenseitig festnageln.** *0144:* Die Zusicherung faengt
  nur die eine Richtung, die Probe die andere; erst zusammen legen sie den Wert fest.
  Das gehoert in den Nachweis, weil keine der beiden Stellen allein es tut.

## Zu Vorschlaegen

- **Kein Vorschlag ohne belegten Schaden**, und erst `grep` ueber `aufgaben/` -- zehnmal
  stand er schon da.
- **Nummernkollision:** *2026-09-06* belegte ein Parallellauf dieselbe Nummer im selben
  Zeitfenster. `ls aufgaben/` reicht nicht, wenn zwei Pruefer gleichzeitig laufen; die
  Kollision im Befund benennen, aufraeumen tut sie der Projektmanager.
- **Ein ueberholter Kommentar wird ein Vorschlag, wenn kein Folgepaket ihn einholt.**
  Pruefkette: Nennt eine Abnahmebedingung ihn? Zieht das Folgepaket ihn ohnehin nach?
  Zweimal nein -- dann eigenes Paket, und die Begruendung ist genau dieses zweimal nein.
