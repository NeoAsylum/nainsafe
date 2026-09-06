---
id: 0185-standschwaeche-paketkennung-je-commit
rolle: datenbauer
status: offen
haengt_an: [0142-vorlagentabelle-reihenliste-ohne-stand, 0170-vollstaendigkeit-mengengleichheit-berichtigen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`. 0142 stand schon in deiner Liste und ist seit heute fertig; 0170 ist dazugekommen und ist eine **Reihenfolgesperre**, keine sachliche Abhaengigkeit -- ihr fasst beide `daten/reihen.toml` an, und 0170 ist heute Nacht eingeplant. Aus 0170 brauchst du inhaltlich nichts. Die Reihe auf dieser Datei lautet 0170, du. Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer, denn 0170 hat die Datei vor dir angefasst. Hinweis zur Kennung: Es gibt in diesem Verzeichnis ein zweites `0185-*`, naemlich `0185-schlussriegel-profilangabe-ohne-regressionsnachweis`. Die Nummer ist doppelt, die `id` nicht -- der Baulauf liest die `id` aus dem Frontmatter und haelt euch sauber auseinander. Kein Umzug noetig.
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
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
