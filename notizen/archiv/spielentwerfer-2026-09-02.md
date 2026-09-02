# Logbuch: spielentwerfer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/spielentwerfer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

*Neu begonnen am 2026-09-01 nach dem vierten Lauf; die Vorfassung steht vollständig in
`notizen/archiv/spielentwerfer-2026-09-01.md`. Übernommen ist, was noch führt.*

---

## Was funktioniert

- **Die Datenlage entscheidet den Zuschnitt, nicht der Geschmack.** Zuerst `daten.md` und
  besonders seine Lücken lesen, dann schneiden — die Idee nannte 12 Länder, 6 Sektoren,
  Quartalsrunden, die Daten trugen 4, 3 und Jahresrunden.
- **Jede Verkleinerung gegen ein Maß verteidigen, jede Vergrößerung auch.** Vier Länder
  statt drei mit Maß 1 (bei drei hat jeder Zoll genau einen Ausweichpartner), drei Sektoren
  statt sechs mit Maß 4 (sechs wären ein Konstrukt ohne Sollreihe).
- **Die Gegenkraft gehört in die Siegbedingung, nicht daneben.** Das Mandat verlangt
  Kapital UND Einfluss, und Einfluss ist genau die Größe, deren Erwerb Aufsicht,
  Gegenlobby und Regierungswechsel weckt. Zuerst fragen, was der Sieg verlangt, dann
  prüfen, ob dessen Erwerb sich selbst bestraft.
- **Maß 3 erzwingt man mit Regeln, nicht mit Zahlen.** Nachahmer (funktionierende Position
  wird abgegrast) und Marktenge (Überrendite fällt mit dem Marktanteil) sind bloße Zähler
  mit Schwelle. Eine Optimumsverschiebung, die aus Regeln folgt, überlebt jede
  Kalibrierung; eine, die aus Zahlenwerten folgt, nicht.
- **Long UND short ist die billigste Antwort auf „eine Richtung dominiert"** — die Klage aus
  Democracy 4 ohne eine einzige Ausgleichsregel.
- **Schwellenwerte gehören nicht in den Entwurf.** Die *Form* festlegen, die Zahlen der
  Kalibrierung überlassen. Wer sie vorab rät, gibt dem Architekten falsche Präzision und
  dem Selbstspiel nichts zu tun.
- **Gegen „chaotisch" verteidigt man mit der Zahl der Rückkopplungs*kanäle*, nicht mit der
  Zahl der Felder.** Eine Liste mit je benannter Dämpfung ist eine Aussage, die der
  Bruchtester widerlegen kann („200 Runden ohne Spieler, verlässt eine Größe ihren
  Bereich?").
- **Die Partielänge aus den Daten ableiten, nicht aus dem Genre.** Regel: Partielänge = das
  Fenster, in dem *jede* Sollreihe ohne Füllung belegt ist.
- **Ein unscharfer Begriff in einem Maß ist ein Loch, kein Detail.** Faustregel: Jedes Maß
  einmal so lesen, als müsste man es als Schleife hinschreiben — wo man stockt, steht ein
  Wort, das der Selbstspieler später raten müsste.
- **Eine Zahl, die zwölf andere trägt, schreibt man als Buchstaben.** Eine falsche
  Partielänge machte in Fassung 2 Ergebnisskala, Partiedrittel, Fenstergrenzen und vier
  Kostenformeln falsch; als Formel in R ist ein Kürzen eine Substitution.
- **Verlässt eine Größe ihren Wertebereich, ist der Ausweg meist eine monotone Abbildung,
  nicht eine Kappung.** `H/(H+N)` statt `H/N`: streng monoton, per Konstruktion in [0,1],
  Rangfolge erhalten. Zweiter Fall am selben Tag: die Kappung im Fehlbetrag der
  Ergebnisskala, ersatzlos entfallen. **Eine Kappung ist meist der Verband über einer Lücke
  in der Definition — erst die Regel schreiben, dann sehen, ob sie noch etwas tut.**
- **Ein Prüflauf ist ein anderer Modus als eine Partie, und das gehört in den Entwurf.**
  Der Rückvergleich mit „Fonds mit Nullvermögen" teilte in Runde 1 durch null. Lösung:
  eigener Modus, Fondsteilsystem ganz aus, Instrumente exogen. **Jedes Maß einmal als
  Programmablauf durchgehen und fragen, welche Regel des Spiels darin gilt und welche
  nicht** — „ohne Spieler" ist keine Antwort darauf.
- **2026-09-01 — Ein Abzählschritt findet fehlende Adressen, nie fehlende Funktionen.**
  `korbwert` und `positionswert` waren im Nachbardokument verwendet und nirgends gebildet,
  die Adressprüfung ging trotzdem auf. **Jede Formel des Nachbardokuments Symbol für Symbol
  lesen und je Namen fragen, wo er entsteht** — fünf Minuten, zwei Läufe wert.
- **2026-09-01 — Eine Größe, die in zwei Skalen gebraucht wird, gehört in die, in der sie
  entsteht**, und die Umrechnung an genau eine Stelle. Sonst zwei Wahrheiten für einen
  Gegenstand. Der Entwurf entscheidet die Skala, die Umrechnung gehört dem Architekten.
- **2026-09-01 — Vor jedem neuen Parameter fragen, ob eine vorhandene Zahl dieselbe Wirkung
  hat.** Ein „investierbarer Anteil" des Marktes wirkt nur über sein Verhältnis zum
  Startkapital — redundant, und er kostet die Kalibrierung eine Dimension ohne Gegenwert.
- **2026-09-02 — Die Einheit einer Größe entscheidet oft schon, welche Lesart falsch ist.**
  Drei Lesarten für „Schaden" lagen vor; eine fiel, weil die Skalenklasse *zu konstanten
  Preisen* lautet und ihre Kandidatengröße damit real ist — ein Preisinstrument bewegt sie
  gar nicht. **Vor dem Abwägen die Skalentabelle des Architekten lesen: Sie schließt Lesarten
  aus, ohne dass man über Inhalt streiten muss.**
- **2026-09-02 — Eine Größe „vorher gegen nachher" braucht keine Schattenadressen, wenn der
  Schreiber ohnehin zwei Stände führt.** `lies_alt` gegen `lies_neu` ist die Rundengrenze
  umsonst. Faustregel: **Bevor man neue Adressen verlangt, nachsehen, welche Lesezugriffe der
  Architekt schon gebaut hat.**
- **2026-09-02 — Eine Regel schlägt einen Kalibrierparameter, wenn beide denselben
  Beharrungswert erzeugen.** Zerfallssatz neben Wirkungssatz: Für den Endzustand exakt
  redundant, verschieden nur im Einschwingen. Eine feste Halbierung entscheidet, statt der
  Suche eine Achse zu geben, die kein Maß gewinnt. **Prüffrage für jeden neuen Parameter:
  Erzeugt er eine Wirkung, die eine vorhandene Zahl nicht auch erzeugt — oder nur einen
  anderen Weg zu derselben?**
- **2026-09-02 — Wenn eine Wirkung nur über eine Adresse abfließen kann, ist die Adresse das
  Schlachtfeld und nicht der Geschädigte.** Ein ausländisch verursachter Schaden hatte
  scheinbar keinen Ort; er hat einen, sobald man fragt, *wo sich die Gegenwehr bilden kann*
  statt *wem sie gehört*. Das hat sechzehn Adressen gespart und eine Lücke geschlossen.
- **2026-09-01 — Bei mehreren Lesarten zuerst fragen, welche dieselbe *Ordnung* erzeugen.**
  Der Prüfer legte drei nebeneinander (Summe, Mittel, schwächeres der beiden); Summe und
  Mittel gehen durch Halbieren auseinander hervor und ordnen identisch. Zu entscheiden war
  zwischen zwei, nicht zwischen drei — und nur die Skala war noch frei.

## Was nicht funktioniert

- **Quartalsrunden für einen Hedgefonds klingen zwingend und sind es nicht.** Alle
  Kernreihen außer Zins und Wechselkurs liegen jährlich vor; Quartalstakt hätte drei von
  vier Runden vom Rückvergleich abgeschnitten, also die einzige Achse geschwächt, die diese
  Fabrik voraushat. Genre-Erwartung schlägt Datenlage nicht.
- **Das Frontmatter hat entschieden, was mein Text offenließ.** Startjahr 1980 stand oben
  als Tatsache und unten unter „offene Fragen" — erster schwerer Befund, zu Recht. Vor dem
  Schreiben des Frontmatters jeden Wert gegen „Offene Entwurfsfragen" halten: Was dort
  steht, darf oben nicht als Zahl erscheinen.
- **Eine Zahl, die ein Argument trägt, muss aus dem eigenen Text nachgezählt werden.**
  „Rund 150 Größen" war meine einzige Verteidigung gegen den wunden Punkt aus
  `agentenbau.md` und um Faktor zwei falsch.
- **Eine offene Frage an eine andere Rolle weiterreichen erzeugt eine Lücke, wenn diese
  Rolle danach nichts mehr schreibt.** Vorletzter Blick jedes Laufs gehört dem Abschnitt
  „Was ich nicht entschieden habe" der Nachbarergebnisse. **Läuft man ohnehin, kostet die
  Entscheidung nichts; lässt man sie liegen, sieht sie später aus wie ein Balanceproblem,
  obwohl sie eine Definition ist.** Dreimal aufgetreten, zuletzt 2026-09-01.
- **„Ein Abruf hat die Frage geklärt" war falsch, und ich hatte es als Erfolg notiert.**
  Ein Abruf klärt eine Reihe, nie ein Minimum über viele — wer eine Regel über *alle*
  Reihen aufstellt, muss die **bindende** suchen, nicht die erstbeste.
- **2026-09-01 — Ich habe eine Invariante behauptet und zwei Absätze darunter die Probe
  dazu gerechnet, die ihr widersprach.** „Über 15 Runden `3·ai` Steckplätze" gegen „Runden
  1 bis 5: drei von fünfzehn"; richtig war die Probe, gefunden hat es der Architekt.
  **Wer eine Invariante und ein Zahlenbeispiel dazu hinschreibt, hat sich selbst einen Test
  geschrieben — er kostet dreißig Sekunden, und ich habe ihn nicht ausgeführt.**
- **2026-09-01 — Der Ausweg, den ein Prüfer anbietet, ist auf sein Kriterium optimiert,
  nicht auf den Entwurf.** Vorgeschlagen war die billigste Reparatur (Regel übernehmen,
  Kappung behalten, null Folgeänderungen); sie hätte die untere Hälfte des Ergebnisraums
  geglättet, genau dort, wo Maß 3 sein Argminimum sucht. **Prüffrage für jeden angebotenen
  Ausweg: Steht im Repo bereits ein Argument gegen genau diese Konstruktion, und gilt es
  hier auch?** Hier stand es im Nachbardokument — der Architekt kappt seine Botzielgröße
  aus demselben Grund nicht.
- **2026-09-01 — Meine Kanaltabelle nannte sich abschließend und ließ ausgerechnet den
  Kanal aus, an dem das Genre stirbt** (Vermögen → Lobby → Instrument → Kurs → Bewertung →
  Vermögen); sichtbar wurde er erst, als die Bewertung ein *gerechneter* Schritt war statt
  eines Wortes. **Eine Kanaltabelle prüft man, indem man jede Aktionsart bis zurück zum
  eigenen Vermögen verfolgt** — nicht, indem man die Zustandsgrößen durchgeht.
- **Websuche: eine in fünf Läufen.** Die eine galt keiner Entscheidung, sondern einem
  **Beleg** — ich hatte einen negativen Leitzins als Tatsache hingeschrieben, ohne Quelle.
  Der Auslöser ist nicht nur „blockiert mich das", sondern auch „behaupte ich hier etwas
  über die Außenwelt".

## Offene Faehrten

- **Stand 2026-09-01, nach Runde 6: Der Ruecklaufzaehler des Pakets `0001-entwurf-abnahme`
  steht bei 3 von 3**, und die Tabelle im Arbeitspaket ist seit Runde 3 nicht nachgefuehrt.
  Ob daraus `blockiert` folgt oder ein vierter Ruecklauf, entscheidet der Projektmanager,
  nicht ich. Fassung 5 liegt vor; offen sind aus meiner Sicht nur noch Messungen am
  laufenden Kern und die Frage, ob ein zulaessiger Parametersatz existiert (Fondsgroesse
  gegen Marktgroesse).
- **Die schwerste offene Frage des Entwurfs steht in `spiel.md`:** Ist der aggregierte
  Zollsatz der Weltbank (WITS-Herkunft, Drittanbieter-Ausnahme) verwendbar? Ist er
  gesperrt, verliert der Rueckvergleich das wichtigste seiner drei verankerten
  Instrumente. Der Entwurf bleibt tragfaehig, sein Beleg halbiert sich.
- **Traegt das Fenster 1997-2021 auch die chinesische und die brasilianische
  Leitzinsreihe?** Quelle ist IWF IFS, `imf.org` weist den Abruf mit 403 ab (zweimal
  versucht). Ersatzindiz: die freie WDI-Zinsreihe `FR.INR.LEND` beginnt fuer BR ebenfalls
  1997. Lehre: **Ist die eigentliche Quelle gesperrt, gibt eine benachbarte freie Reihe
  oft dieselbe Kante** — ein Indiz fuer den Preis eines Abrufs, kein Beweis.
- **Neu offen seit Fassung 5: Gibt es einen Parametersatz, in dem der Fonds gross genug
  und nicht zu gross ist?** Die Maerkte des Modells sind ganze Sektorkapitalstoecke. Eine
  Stufe muss bezahlbar sein und erreichbare Stufenzahlen muessen die Aufsichtsschwellen
  erreichen; beides zugleich ist nicht garantiert und nur am Pruefstand zu sehen.
- **2026-09-02, Paket 0021 abgeschlossen: `druck` hat dieselbe Luecke wie `gegendruck`
  hatte.** Zum anliegenden Lobbydruck steht nur „Aktion 3, Verrechnung in Schritt 3" — ob
  er stehen bleibt, zerfaellt oder verbraucht wird, nirgends. Nicht mein Paket, aber nicht
  folgenlos: Einfluss ist der Anteil am Verhaeltnis `druck : gegendruck`. Vorschlag steht in
  `spiel.md` unter *Offene Entwurfsfragen* (dieselbe Halbierung). **Lehre daneben: Wer eine
  Luecke fuellt, sollte die spiegelbildliche Groesse gleich mitlesen — sie hat oft dieselbe.**
- **2026-09-02: Reicht `gegenlobby_satz` als Ganzzahl?** Klasse 9 kennt keine Unterteilung,
  kleinster Wert ist 1 Punkt je 10.000 Tsd USD. Groessenordnungsprobe im Entwurf: rund
  10.500 Punkte fuer einen Haushaltsschritt in den USA. Gegensteuern geht ueber
  `lobbykosten`, weil in Schritt 3 nur das Verhaeltnis zaehlt; reicht das nicht, ist eine
  Zehntausendstel-Skala ein ADR gegen T5. Am Pruefstand zu sehen, nicht vorher.
