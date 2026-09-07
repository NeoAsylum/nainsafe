---
id: 0185-standschwaeche-paketkennung-je-commit
rolle: datenbauer
status: fertig
haengt_an: [0142-vorlagentabelle-reihenliste-ohne-stand, 0170-vollstaendigkeit-mengengleichheit-berichtigen, 0200-zitate-auf-uebersetzte-ueberschriften-nachziehen]
vermerk_abnahme: "FERTIG 2026-09-07, Projektmanager, auf befunde/pruefung-0185-standschwaeche-paketkennung-je-commit-2026-09-07-ruecklauf-2.md, `urteil: geprueft`. Ruecklauf 2 von 3, drei Anlaeufe, und zwei der drei Ruecklaeufe gingen auf Bedingungen, die ich falsch gestellt hatte -- die Blob-Haelfte (unerfuellbar ohne Shell) und die Einfassung von 0214-leitzins, die erst im zweiten Ruecklauf dazukam. Bedingungen 3 und 4 sind einzeln gemessen: Zeile 194 schickt niemanden mehr auf eine verschwundene Zaehlung, die vier anderen Treffer gehoeren anderen Sachen; die zwei Leitzins-Zitate loesen bei `spiel.md:2447` auf, nachgeprueft am Ziel UND an den zwei entscheidenden Regeln des Riegels (`ist_namensende` bei :2638, Namenslaenge 61 gegen 200), und `belegstellen_riegel` steht in beiden Baeumen auf Passed. || DIE EINFASSUNG VON 0214-LEITZINS HAT GETRAGEN: das stehende Rot ist weg, ohne dass ein zweiter Bau-und-Pruef-Zyklus auf dieser Datei noetig war. || BEFUND 1 GEHT NICHT AUF DICH, sondern in Paket 0220: `spiel.md` steht in fuenf lebenden Stellen dieser Datei und in keiner der zwei Listen, die eine Nachziehpflicht ausloesen -- genau deshalb hat der Uebersetzungslauf hier ohne Warnung eingeschlagen. Dein Vermerk liess nur zwei Blattwerte zu, ein siebter Vorlageneintrag war dir verboten."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`. 0142 stand schon in deiner Liste und ist seit heute fertig; 0170 ist dazugekommen und ist eine **Reihenfolgesperre**, keine sachliche Abhaengigkeit -- ihr fasst beide `daten/reihen.toml` an, und 0170 ist heute Nacht eingeplant. Aus 0170 brauchst du inhaltlich nichts. Die Reihe auf dieser Datei lautet 0170, du. Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer, denn 0170 hat die Datei vor dir angefasst. Hinweis zur Kennung: Es gibt in diesem Verzeichnis ein zweites `0185-*`, naemlich `0185-schlussriegel-profilangabe-ohne-regressionsnachweis`. Die Nummer ist doppelt, die `id` nicht -- der Baulauf liest die `id` aus dem Frontmatter und haelt euch sauber auseinander. Kein Umzug noetig.
abnahme: "Neu gefasst 2026-09-07 nach Ruecklauf 1; DIESE Fassung gilt, nicht die zwei Bedingungen im Rumpf und nicht die dritte im vermerk_2026_09_07. Die Bedingungen 1 und 2 sind vom Pruefer einzeln nachgemessen und ERFUELLT -- sie sind nicht noch einmal zu erbringen und nicht anzufassen. Es bleiben zwei. (3) DER VERWEIS AUF DIE VERSCHWUNDENE ZAEHLUNG. Der zaehlende Teil ist weg, das ist die zugelassene Antwort; die Zeilen 193-194 schicken den Leser aber weiter dorthin: 'Die Absaetze zum Eintrag `reihenliste` weiter unten zaehlen beide Mengen auf.' Unterhalb von Zeile 194 zaehlt kein Absatz eine der beiden Mengen auf. Ein Satz ist zu streichen oder umzuschreiben, sonst nichts; nachpruefbar mit einem Grep auf `zaehlen beide|Mengen` ueber die Datei. (4) DIE ZWEI LEITZINS-ZITATE. Der ctest-Eintrag `belegstellen_riegel` gibt auf dem Baum des Liefertags 0 zurueck und meldet null unaufloesbare Abschnittszitate; erreicht dadurch, dass die Zitate bei `daten/reihen.toml:406` und `:556` (Anleser 'Der Leitzins ist seit dem 2026-09-03 keine Sollreihe') auf den Wortlaut nachgezogen sind, der an ihrem Ziel in `specs/.../spiel.md` am Tag der Aenderung gilt -- heute englisch, `spiel.md:2447`. Keine Ueberschrift in `specs/` umbenennen, kein Zitat loeschen, keine Riegellogik und keine Schwelle anfassen. GESTRICHEN, weil in dieser Fabrik unerfuellbar: die Blob-Haelfte der alten Bedingung 2 ('Bezugsstand: Commit-Kennung plus Blob'). Seit dem 2026-09-06 hat keine Rolle eine Shell und damit kein `git hash-object`; der Blob eines Commits steht nirgends im Baum. Die Commit-Kennung allein genuegt und ist erbracht."
vermerk_2026_09_07_ruecklauf_2: "ZURUECK, Ruecklauf 2 von 3, auf befunde/pruefung-0185-standschwaeche-paketkennung-je-commit-2026-09-07-ruecklauf-1.md. DIE ABNAHME IST NEU GEFASST -- es gilt das Feld `abnahme`, nicht die zwei Bedingungen im Rumpf und nicht die dritte im Vermerk darunter. Lies den Befund, bevor du anfaengst. || WAS FERTIG IST UND WAS DU NICHT ANFASST: Bedingungen 1 und 2 sind vom Pruefer einzeln nachgemessen -- 1962 Zeilen, 426 Kommentarzeilen, alle sechzehn Muster, die drei Commits des Pakets 0051 gegen den Verlauf. Der Halbsatz bei 249-262 stimmt jetzt. Daran ist nichts zu tun. Es bleibt EIN Satz aus dem alten Auftrag (Bedingung 3) und EINE dazugekommene Sache (Bedingung 4). || ICH HABE EINE BEDINGUNG GESTRICHEN, WEIL SIE UNERFUELLBAR IST. Bedingung 2 verlangte 'Bezugsstand (Commit-Kennung plus Blob)'. Der Pruefer meldet es ausdruecklich an mich statt an dich: seit dem 2026-09-06 hat keine Rolle eine Shell, also kein `git hash-object`, und der Blob von `daef750` steht nirgends im Baum. Die Formel war unerfuellbar, nicht deine Arbeit mangelhaft -- dritter Fall dieser Sorte binnen zwei Tagen. Die Commit-Kennung allein traegt; sie ist genannt. Fuer JEDES kuenftige Paket auf dieser Datei gilt dasselbe, das ist damit entschieden. || 0214-LEITZINS IST IN DIESES PAKET EINGEFASST und steht auf `fertig` mit Verweis hierher; er ist Bedingung 4. Warum bei dir und nicht als eigener Lauf: es ist dieselbe Datei, und zwei Pakete auf einer Datei laufen nie zusammen -- getrennt haettest du hinter ihm einen ganzen Bau-und-Pruef-Zyklus gewartet. Die Sache ist dringend und klein: `belegstellen_riegel` faellt seit heute in BEIDEN Baeumen aus ('2 Abschnittszitat(e) finden ihre Ueberschrift nicht'), jeder Baulauf meldet `ergebnis: fehler` bei sonst gruenem Testsatz, und es sperrt 0147 zum zweiten Mal. Der Grund ist nicht dein Vorgaenger, sondern der Uebersetzungslauf: die Ueberschrift bei `spiel.md:2447` steht seit heute englisch da, deine zwei Zitate suchen den deutschen Wortlaut. Das ist genau der Fall, den der Vermerk von 0200 vorhergesagt hat. || WICHTIG FUER DEN, DER DAS LIEST, WENN ES WIEDER ROT IST: Faellt der Riegel am Liefertag auf einem DRITTEN, neu uebersetzten Zitat aus, das nicht der Leitzins-Anleser ist, dann ist das ein Befund und kein Ruecklauf auf dich -- schreib es in deine Meldung im Wortlaut. Die wiederkehrende Haelfte ist Empfehlung B in ops/plan.md und eine Entscheidung des Betreibers, nicht deine. || NICHT ANFASSEN, unveraendert: kein Blattwert, kein `faktor`, kein `basisjahr`, keine Aenderung an `technik.md`, der Wert von `datei.vorlagen.reihenliste` bleibt. Ein reiner Kommentarwechsel bewegt kein Musterzaehlwerk, aber die Zeilenzahlen -- zaehl die getrennt nach und schreib sie fort. Den Eintrag in `datei.nachgezogen_durch` setzt du selbst. || Dein Vorher-Stand ist der dann geltende HEAD; such am Text, nicht an der Zeilennummer. Die Reihe auf daten/reihen.toml lautet: du, dann nichts."
vermerk_2026_09_07: "ZURUECK, Ruecklauf 1 von 3, auf befunde/pruefung-0185-standschwaeche-paketkennung-je-commit-2026-09-07.md. Bedingung 2 ist erfuellt und einzeln nachgemessen -- 1956 Zeilen, 420 Kommentarzeilen, alle sechzehn Muster, Bezugsstand b705e3f; daran ist nichts zu tun. Bedingung 1 faellt an einer Zahl: der Halbsatz sagt 'fuenf davon nach ce59b8b', gemessen sind es sieben. Es fehlen c3f6a8d (2026-09-06 06:30:28, Paket 0154, T60 in Abschnitt 20) und 7d4e8c8 (2026-09-06 11:14:34, uebersetzer, Abschnitt 1). Gemessen heute: 21 / 7 / 14 / sieben statt 19 / 7 / 12 / fuenf. Der Pruefer nennt seinen Weg ohne Shell -- .git/logs/HEAD nach 'commit: architekt:' und 'commit: uebersetzer:' ab Zeile 719, dann die dateien-Felder der Pakete; und er nennt seine Zahl ausdruecklich als Untergrenze. MISS SELBST, schreib seine sieben nicht ab: seit seinem Lauf sind weitere Commits gefallen, und der Fehler dieses Pakets ist genau das Fortschreiben einer fremden Zahl. || DAZUGEKOMMEN, und das ist der Grund, warum du nicht nur die Zahl berichtigst: Vorschlag 0207-standzaehlung-ueber-technikmd-ohne-messdatum (daten-pruefer, 2026-09-07) ist in dieses Paket eingefasst und steht auf fertig mit Verweis hierher. Er trifft denselben Halbsatz, und seine Begruendung entscheidet die Sache: Diese Zahlen sind eine Eigenschaft der Geschichte einer FREMDEN Datei. Sie altern bei jedem Commit auf technik.md, auch bei einem, der Abschnitt 7 nicht anfasst -- und die Nachziehpflicht von datei.vorlagen.reihenliste feuert nur bei Abschnitt 7, ist hier also strukturell blind. Zweimal binnen 24 Stunden gealtert. Nur die Zahl zu berichtigen heisst, denselben Satz in einer Woche ein drittes Mal anzufassen; zwei Laeufe auf einem Satz sind einer zu viel. Also, dritte Bedingung: entweder traegt die Zaehlung ein Messdatum und einen Bezugscommit in der Form, die diese Datei fuer alternde Aussagen schon benutzt ('Geschichte mit Datum'), ODER der zaehlende Teil faellt weg und was stehen bleibt, traegt die Aussage allein -- dass die Fassungsnummer den Abschnitt 7 nicht abdeckt, ruht auf fassung: 7 und dem Datum der letzten Aenderung an Abschnitt 7, nicht auf der Zahl verpasster Commits. Beides ist eine richtige Antwort, das stille alternde Zahlwort ist keine. Kein Riegel dafuer -- die Antwort steht im Verlauf, und keine Rolle hat eine Shell. || NICHT ANFASSEN, unveraendert aus deinem urspruenglichen Auftrag: keine andere Form des Standes, der Wert von datei.vorlagen.reihenliste bleibt, kein Blattwert, kein faktor, kein basisjahr, keine Aenderung an technik.md. Ein reiner Kommentarwechsel bewegt kein Musterzaehlwerk, aber die Zeilenzahlen -- zaehl die getrennt nach. Den Eintrag in datei.nachgezogen_durch setzt du selbst. || Dein Vorher-Stand ist der dann geltende HEAD; such am Text, nicht an der Zeilennummer. Die Reihe auf daten/reihen.toml lautet 0200 (zieht ein Abschnittszitat nach), du, dann nichts mehr."
---

# Die Schwaechenliste des neuen Standes setzt ein Paket mit einem Commit gleich

Vorschlag des Daten-Pruefers vom 2026-09-06, aufgefallen bei der Pruefung des Pakets
0142 (`befunde/pruefung-0142-vorlagentabelle-reihenliste-ohne-stand-2026-09-06.md`,
Befunde 1 und 2). **Jene Pruefung lautet `geprueft`.** Dies ist kein Rueckgabegrund und
kein Ruecklauf; die drei Abnahmebedingungen des Pakets 0142 sind erfuellt.

## Der Sachverhalt

Paket 0142 hat `datei.vorlagen.reihenliste` einen Stand gegeben, der aus einer
Fassungszahl und einem am Verlauf gemessenen Datum besteht, und hat die Schwaeche dieser
Form in drei Punkten danebengeschrieben -- genau wie verlangt. Zwei Stellen dieser
Begruendung setzen ein Paket mit einem Commit gleich, und beide Male stimmt es nicht.

**Erstens**, der zweite Schwaechepunkt:

> „Zweitens hat es Tagesgenauigkeit -- zwei Aenderungen ... am selben Tag bewegen es
> nicht; die Paketkennung daneben faengt diesen zweiten Fall ab, den ersten nicht."

Die Paketkennung faengt den Fall nur ab, wenn die beiden Aenderungen aus
**verschiedenen** Paketen kommen. Das Paket, das der Eintrag selbst als Kennung fuehrt,
`0051-t46-gebietspraefix-entscheiden`, hat die Vorlagendatei am 2026-09-05 in **drei**
Commits angefasst: `ce59b8b` (03:43), `a127600` (04:25), `9e46cfa` (05:51). Nur der
erste traf den zitierten Gliederungspunkt -- ein Zufall dieses Falls. Haette einer der
beiden anderen ihn ebenfalls getroffen, waere der eingetragene Stand buchstabengleich
derselbe geblieben, und die Datei behauptete eine Uebereinstimmung mit einem Text, den
sie nie gesehen hat. Der Satz sichert damit gerade den Fall zu, den sein eigenes
Beispiel offenlaesst.

**Zweitens**, der Absatz mit der Zaehlung ueber die Vorlagendatei:

> „Zwoelf haben ... geaendert und ... nicht, fuenf davon nach ce59b8b -- die Abschnitte
> 19, 20 und 21 stehen hinter ... und fassen ihn nicht an."

Die beiden Zahlen sind nachgemessen und richtig. Der erklaerende Halbsatz deckt aber nur
**drei** der fuenf Commits ab; die beiden anderen (`a127600`, `9e46cfa`) sind weitere
Commits desselben Pakets 0051. Wer den Satz liest, zaehlt drei Namen gegen fuenf
Commits.

Beide Belege stehen mit Aufruf und Ausgabe in der genannten Pruefdatei.

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

1. **0142 durfte es nicht mehr.** Der Fehler steckt in Absaetzen, die 0142 selbst
   geschrieben hat; er kann nicht Gegenstand desselben Pakets sein.
2. **Es ist eine Berichtigung und keine Entwurfsfrage.** Die gewaehlte Form des Standes
   bleibt, die Adresse bleibt, der Wert der Tabelle bleibt unangetastet. Zu aendern sind
   zwei Halbsaetze im Kommentar -- nicht mehr.
3. **Es ist bewusst ein kleiner Auftrag, und er darf mitfahren.** Ein Halbsatz
   rechtfertigt keine eigene volle Selbstmessung. Liegt zu dem Zeitpunkt ohnehin ein
   Paket auf `daten/reihen.toml` -- `0170-vollstaendigkeit-mengengleichheit-berichtigen`
   ist der naheliegende Fall und berichtigt ebenfalls einen Halbsatz --, ist dieser
   Vorschlag dort als Beifahrer besser aufgehoben als als eigener Lauf. Diese
   Entscheidung gehoert dem Projektmanager, weil nur er die Dateiansprueche der anderen
   Pakete sieht.

## Was zu tun ist

1. **Den zweiten Schwaechepunkt berichtigen.** Er soll sagen, was die Paketkennung
   wirklich leistet: Sie trennt zwei Aenderungen desselben Tages nur, wenn sie aus
   verschiedenen Paketen stammen. Ein Paket, das an einem Tag mehrfach committet, bleibt
   ununterscheidbar; das ist die dritte Schwaeche der Form und keine abgefangene.
2. **Den Erklaerungshalbsatz der Zaehlung vervollstaendigen**, so dass er alle fuenf
   Commits deckt und nicht nur drei. Die Zahlen selbst sind richtig und bleiben.
3. **Nicht fortschreiben, sondern zaehlen.** Alle Zahlwoerter, die dabei beruehrt
   werden, sind mit `befunde/messung-0099/zahlwoerter.py` beziehungsweise am Verlauf neu
   zu messen. Die Zahlen dieses Vorschlags sind ein Hinweis, kein Bezugsstand.

## Was nicht dazugehoert

- **Keine andere Form des Standes.** Die Wahl von Paket 0142 steht; dieser Vorschlag
  berichtigt allein ihre Beschreibung.
- **Kein Eingriff an `technik.md`.** Ob dort je Gliederungspunkt ein eigenes
  `fassung`-Feld stehen sollte, entscheidet der Architekt.
- **Kein Blattwert ausser `pruefweg.toml_geprueft` und `datei.nachgezogen_durch`.** Der
  Wert von `datei.vorlagen.reihenliste` bleibt unveraendert.

## Abnahme

1. **Beide Halbsaetze stimmen mit dem Verlauf ueberein.** Der zweite Schwaechepunkt
   nennt die Bedingung, unter der die Paketkennung traegt, und der Erklaerungshalbsatz
   der Zaehlung deckt alle fuenf Commits. Beides ist am Verlauf nachgemessen und im
   Kommentar als gemessen ausgewiesen, nicht behauptet.
2. **Die Selbstmessung stimmt nach dem letzten Schreiben**, mit genanntem Bezugsstand
   (Commit-Kennung plus Blob) und den sechzehn Mustern einzeln neu gezaehlt -- dieselbe
   Bedingung wie in 0078, 0099 und 0142. Ein reiner Kommentareingriff hebt keine der
   sechzehn Musterzahlen, aber sehr wohl die Zeilenzahlen; genau die sind separat zu
   zaehlen.

## Ein Hinweis fuer den, der die Riegelzahlen nachmisst

Diese Vorschlagsdatei und die zugehoerige Pruefdatei bewegen die drei Zahlen des
Belegstellenriegels **nicht**. Gemessen, nicht angenommen: Der Riegel gibt mit beiden
Dateien im Baum weiterhin 0 zurueck und meldet 40 Zitate, 40 aufgeloest, 55 uebergangen
-- dieselben drei Zahlen wie im Feld `pruefweg.toml_geprueft` zum Stand `aa65c70`.
Gewachsen ist allein der Zielbestand, von 235 auf 237 Dateien.
