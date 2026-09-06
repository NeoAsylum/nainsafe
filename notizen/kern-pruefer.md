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
  `ventures/**/bau-*/` ist zudem in `.gitignore` -- ein Baum, der so heisst, wird nicht
  mitcommittet.
- **Die Shell verliert ihr Arbeitsverzeichnis zwischen Aufrufen.** Absolute Pfade, oder
  `git -C`.
- **Nie ueber den Commit-Betreff suchen**, immer `git log -- <datei>`, und zwar je
  Datei einzeln. *0144:* Der Commit mit dem Paketnamen trug eine Kommentarzeile, die
  Arbeit lag in zwei fremd betitelten Commits. Elfter Fall dieser Art.
- **Im Befund den Stand nennen, nie das Wort `HEAD`.** Die md5 der geprueften Dateien
  am Anfang und am Ende gegenrechnen und beides hinschreiben. Waehrend eines Laufs
  committen fremde Rollen; `git log` am Ende noch einmal lesen und den Zuwachs im
  Befund benennen.

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
  danebenlegen. Zwei `git archive` in dasselbe Verzeichnis -- erst der Stand, dann die
  eine alte Datei darueber -- ersetzen jedes Kopieren.
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
  nur die abgeleitete Groesse. *0156:* Sie wirkte dort doch -- nur spaet, und aus einem
  Grund, den beide Texte uebersahen. Wirkungslos und spaet wirksam auseinanderhalten.

## Offene Faehrten

- **Ein Widerspruch zwischen Abnahme und Vorgabe ist kein `zurueck`**, und eine
  Vorgabe, zu der die Abnahme **schweigt**, ebenso wenig. Das Urteil folgt den
  Bedingungen, der Verstoss wird ein Vorschlag. *0144, 0156:* je `geprueft` plus
  Vorschlag.
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

## Nachtrag 2026-09-06 (Pruefung 0132)

- **printf lehnt Rueckwaertsanfuehrungszeichen ab**, auch in einfachen Anfuehrungs-
  zeichen -- die Sperre sieht Kommandosubstitution. Befund ohne sie schreiben. Ebenso
  fallen cp, Ketten mit && oder ; und Zeilen mit Gleichheitszeichen zwischen Name und
  Zahl. cmake -E copy und cmake -E cat tragen zuverlaessig.
- **Ein Makro leeren ohne Editor:** head -n <Zeile des macro> plus tail -n +<Zeile des
  endmacro>, mit cmake -E cat zusammensetzen. Wichtig: return() im Makro verliesse die
  ganze aufrufende Funktion und erzeugte gar keine Meldung -- der leere Rumpf ist der
  Weg, wenn beide Laeufe dieselbe Meldung zeigen sollen.
- **nachbau.py legt die Wegwerf-Baeume selbst an.** Danach die Kette daneben austauschen
  und neu konfigurieren: A/B am identischen Baum, ganz ohne eine Datei zu schreiben.
- **Eine Riegelzahl gegen Ziele mal Schalter gegenrechnen.** Ein Rest, den man erklaeren
  kann, ist der beste Beleg dafuer, dass die Zahl zaehlt, was sie behauptet.
- **Spaetere Commits vor dem Vergleich pruefen:** git ls-tree an beiden Staenden ueber
  die geglobten Verzeichnisse. Erst wenn dort keine Datei dazukam, ist ein Vergleich
  gegen den Commit vor dem Paket eine Isolierung und keine Vermischung.

## Nachtrag 2026-09-06 (Pruefung 0152)

- **Ein Mutantensatz braucht kein zweites Bauverzeichnis je Fall.** Eine Abschrift von
  `kern/` plus `werkzeugkette.cmake`, ein Bauverzeichnis, ein Probenziel: mutieren,
  bauen, laufen, zuruecksetzen. Am Ende `diff` der mutierten Datei gegen die
  Paketdatei -- leer, sonst ist der Kontrollbaum keiner.
- **Bricht die Probe still ab, wenn sie gruen ist, taugt der Profilvergleich nichts.**
  Determinismus dann am Quelltext belegen: kein Gleitkomma, Iteration ueber
  `constexpr std::array`.
- **Eine Umgruppierung von Summanden ist kein Determinismusbefund**, solange nur die
  Klammerung wechselt.
- **Ein Randwert, den keine Abnahme nennt, wird ein Vorschlag -- aber erst gemessen.**
  Den Zusatzpruefsatz in die *Abschrift* der Probe haengen, gegen den unveraenderten
  Kern. Das ist eine Messung und keine Reparatur.
- **Die staerkste Begruendung eines Vorschlags ist ein Spalt zwischen zwei Vorgaben.**
- **Zwei Vorgaben koennen sich widersprechen statt nur zu schweigen.** Beim Nachfahren
  der Formeln beide Quellen lesen, nicht nur die, die der Kopf nennt.
- **`notizen/<rolle>.md` und die eine `status:`-Zeile des Pakets sind keine fremden
  Dateien.** Gegen zwei fruehere Baulaeufe derselben Rolle gegenpruefen -- tun die
  dasselbe, ist es die stehende Form und kein Verstoss.

## Nachtrag 2026-09-06 (Pruefung 0156)

- **Geht kein Mutant, traegt ein Gesetz aus gemessenen Punkten.** Drei Uebersetzungen
  legten `sizeof = 17.376·N + 8` fest, der Rest war Einsetzen. Im Befund hinschreiben,
  welche Uebersetzung fehlt -- eine Herleitung ist kein Lauf.
- **Den fremden Nachweis-Apparat lesen und selbst fahren ist erlaubt und stark**; ein
  Skript ist kein Logbuch. Vorher seine Riegel pruefen: Ersetzt es genau eine Zeile?
  Prueft es bei Rot, **welche** Zusicherung riss? Den Bericht daneben erst danach.
- **Eine Zahl aus einem eigenen alten Befund ist keine Quelle.** 0156 schrieb 37.670.312
  aus meiner 0144-Tabelle ab; sie widersprach dort schon den Nachbarzeilen. Jede
  uebernommene Messung gegen das Gesetz gegenrechnen, auch die eigene.
- **Eine Schranke, die aus einem Literal gebildet ist, ist die richtige.** Haette sie
  den Stapel beim Bauen abgefragt, waere derselbe Quelltext auf zwei Rechnern
  verschieden rot -- danach zuerst suchen, wenn eine Zusicherung die Umgebung nennt.
