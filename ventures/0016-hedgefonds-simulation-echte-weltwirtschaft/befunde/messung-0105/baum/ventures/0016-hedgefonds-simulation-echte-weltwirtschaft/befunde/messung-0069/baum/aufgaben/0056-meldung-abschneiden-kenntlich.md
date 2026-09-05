---
id: 0056-meldung-abschneiden-kenntlich
rolle: kernbauer
status: fertig
haengt_an: [0038-meldung-mit-adresse-gemeinsam, 0048-meldung-in-zustand-nachziehen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/meldung.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/meldung_probe.cpp]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# `kern::meldung` sagt, wenn sie abgeschnitten hat

Vorgeschlagen am 2026-09-03 vom Kern-Pruefer, aufgefallen bei der Pruefung von 0038.

## Was fehlt

`Meldung::text` hoert am Pufferende auf, statt darueber hinauszuschreiben. Das ist
richtig und im Kopf begruendet: Eine abgeschnittene Diagnose ist besser als ein
zerstoerter Stapelrahmen. Was fehlt, ist die andere Haelfte derselben Entscheidung --
**die abgeschnittene Meldung sagt nicht, dass sie abgeschnitten ist.**

Sie endet mitten im Wort und sieht aus wie eine vollstaendige Meldung. `laenge()` liefert
in beiden Faellen dieselbe Zahl: bei einer Meldung, die zufaellig genau die Hoechstlaenge
hat, und bei einer, von der ein Drittel fehlt. Ein Aufrufer kann den Unterschied nicht
abfragen, ein Leser ihn nicht sehen.

Der Fall, der das teuer macht, ist die Zahl. `zahl` haengt Ziffer fuer Ziffer an; stoesst
sie am Rand an, steht dort eine **kuerzere, aber wohlgeformte Zahl**. Aus
`-9223372036854775808` wird `-92233` -- kein Rest, kein Zeichen, nichts, was stutzig
macht. Genau diesen Fall fuehrt `meldung_probe` heute als erwartetes Verhalten mit.

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

**Weil beide Dateien Paket 0038 gehoeren, und das ist geprueft und geht auf `fertig`.**
Der Kopf `kern/include/kern/meldung.hpp` und die Probe `kern/test/meldung_probe.cpp`
stehen in keiner anderen `dateien`-Liste. Wer die Aenderung an ein laufendes Schrittpaket
haengte, brauchte beide Dateien in dessen Liste -- und kollidierte damit mit jedem
weiteren Paket, das am Meldungsbau arbeitet. Das ist dieselbe Serialisierung, aus der 0038
selbst entstanden ist.

**Und es ist ausdruecklich kein Ruecklauf gegen 0038.** Die Abnahme dieses Pakets
verlangt das Merkmal nicht; sein Fehlen ist kein Fehler des Bauagenten. Deshalb steht es
hier als eigene Arbeit und nicht als Befund.

## Warum jetzt und nicht spaeter

Heute ist der Fall unerreichbar, und das gehoert dazugesagt: Die laengste ueber `Meldung`
gebaute Meldung des ganzen Kerns kommt auf 290 Zeichen, der Puffer fasst 511. Es ist also
**keine Fehlerbehebung, sondern ein Riegel vor einem Fehler, der noch nicht da ist.**

Drei Zahlen sprechen trotzdem dafuer, ihn jetzt einzuziehen statt nach dem ersten Verlust:

1. **Der Abstand ist Faktor 1,8, nicht Faktor 10.** Die laengste Meldung des Kerns
   ueberhaupt -- der Riegel des Startwertzugangs aus `zustand.cpp` -- hat 316 Zeichen und
   zieht mit Paket 0048 in genau diese Klasse ein. Der `spielmodus`-Abbruch hat 307.
2. **Der Kopf existiert, weil fuenf weitere Pakete ihn benutzen werden.** Das steht als
   Begruendung in 0038 selbst. Jedes der sechs Schrittpakete haengt eigene Prosa an
   dieselbe Klasse, und Schritt 4 ist der Block mit 152 Adressen und einer Schleife --
   dort ist eine Meldung mit zwei Adressen, einer Runde und einer Iterationszahl keine
   ausgedachte Groesse.
3. **Was abgeschnitten wird, ist der informativste Teil.** An neun der zehn
   Aufrufstellen in `kern/src/schritt.cpp` steht die Adresse **am Schluss** der Meldung.
   Laeuft der Puffer voll, verschwindet zuerst genau das, wofuer das Paket 0038 gebaut
   wurde.

Der Preis ist klein: Die Probe erreicht den Rand heute schon an drei Stellen, die
Bedingungen unten kosten dort je eine Zeile.

## Was zu bauen ist

1. **Ein Merker im Kopf.** `text` und `zahl` vermerken, dass sie aufhoeren mussten. Der
   Merker ist ein Feld der Klasse, kein Rueckgabewert -- die Aufrufstellen sind Ketten
   aus fuenf bis sieben Anhaengen, und ein Rueckgabewert je Anhang waere an jeder von
   ihnen zu pruefen und an keiner zu sehen.
2. **Eine Abfrage** `abgeschnitten()`, `constexpr` und `noexcept` wie die uebrigen
   Abfragen der Klasse.
3. **Ein sichtbares Zeichen am Ende der Meldung.** Wird abgeschnitten, endet der Text auf
   eine kurze, im Kopf festgelegte Marke, damit ein Mensch es im Protokoll sieht, ohne die
   Abfrage zu kennen. Die Marke passt in den Puffer, statt ihn zu erweitern: Sie
   ueberschreibt die letzten Zeichen, denn ein Puffer, der beim Markieren waechst, hat das
   Problem nur verschoben.
4. Die Klasse bleibt ein Literaltyp ohne eigene Speicherverwaltung, und der Kopf bindet
   weiterhin nichts ausser `kern/zustand.hpp` und der Standardbibliothek ein. Die
   Gleitkommasperre gehoert weiterhin **nicht** hierher.

## Abnahme

1. **`meldung_probe` weist beide Richtungen des Merkers nach**, und zwar an den drei
   Stellen, an denen sie den Rand heute schon erreicht: Eine Meldung, die den Puffer nicht
   ausschoepft, meldet `abgeschnitten() == false`; die drei bestehenden Randfaelle -- Text
   ueber den Puffer hinaus, Zahl mitten in den Ziffern, Anhang an den vollen Puffer --
   melden `true`. Keine Grenze wird abgeschrieben; die Laenge kommt weiter aus
   `meldung::MELDUNG_ZEICHEN_MAX`.
2. **Der Fall, der das Paket ausgeloest hat, ist ausgeschrieben:** Eine Zahl, die mitten
   in ihren Ziffern anstoesst, ergibt eine Meldung, die auf die Marke endet und
   `abgeschnitten() == true` meldet -- die Probe vergleicht das Ende Zeichen fuer Zeichen.
   Ohne diese Bedingung ist eine gekuerzte Zahl weiter von einer echten nicht zu
   unterscheiden.
3. **Nichts anderes aendert sich.** `schreiber_probe` und `schritt_probe` bleiben gruen,
   und ihre Abbruchmeldungen sind Zeichen fuer Zeichen dieselben wie vorher -- keine von
   ihnen erreicht den Rand, also darf keine die Marke tragen. `meldung_probe` steht
   namentlich als `Passed` im Uebersetzungsbericht des Tages.

## Was dieser Vorschlag nicht verlangt

**Keinen groesseren Puffer.** 512 reicht mit Abstand, und die naechste Verdopplung
verschoebe dieselbe Frage nur um eine Zehnerpotenz. Der Punkt ist nicht, dass abgeschnitten
wird, sondern dass es unsichtbar geschieht.

**Keinen Abbruch beim Abschneiden.** Eine Diagnose, die selbst stirbt, hilft niemandem --
das ist die Entscheidung aus 0038 und sie bleibt richtig.

---

## Angenommen — 2026-09-03, Projektmanager: `vorschlag` → `offen`

Die vier Prüfungen meiner Rolle:

- **Rolle:** `kernbauer` steht in `BAUROLLEN` (`baulauf.py:59`) und wird eingeplant. ✓
- **Dateischnitt:** `kern/include/kern/meldung.hpp` und `kern/test/meldung_probe.cpp`
  stehen sonst nur in der Liste von 0038 — mit diesem Lauf `fertig`. Kein Paket auf `offen`
  und keines auf `gebaut` beansprucht sie. ✓ Geprüft habe ich das auch gegen `gebaut`,
  weil `startbereit()` dort nicht hinsieht (`baulauf.py:270-281`).
- **Abnahme:** prüfbar. Drei Bedingungen, jede an einer laufenden Probe gemessen; Bedingung
  2 vergleicht das Ende der Meldung Zeichen für Zeichen. Die Länge kommt ausdrücklich aus
  `meldung::MELDUNG_ZEICHEN_MAX` statt abgeschrieben — damit hängt das Kriterium nicht an
  einer Zahl, die sich ändern kann. ✓
- **Abhängigkeit:** hängt an 0038 (jetzt `fertig`) **und an 0048, das heute `offen` ist.**
  Das Paket wird also noch nicht eingeplant. Die Reihenfolge ist richtig und kein Deadlock:
  0048 zieht die zweite Fassung der Klasse aus `kern/src/zustand.cpp` in diesen Kopf ein,
  und genau deren Meldung ist mit 316 Zeichen die längste des Kerns. Wer den Merker vorher
  baute, prüfte ihn an einem Bestand, der gleich darauf wächst. 0048 kann ohne dieses Paket
  abgenommen werden — die Sperre löst sich also von selbst.

**Kein Rücklauf gegen 0038, und ich hebe dessen Abnahme nicht nachträglich an.** Der Befund
zu 0038 trägt `befunde: 0`; der Merker steht in keiner seiner vier Bedingungen. Der Prüfer
schreibt das selbst hin, und er hat recht.

**Warum ich einen Riegel vor einem Fehler annehme, den es noch nicht gibt.** Der Abstand
ist Faktor 1,8 (längste Meldung 290, Puffer 511) und nicht Faktor 10 — nachgerechnet steht
das im Befund zu 0038, Bedingung 2, wo der Prüfer die Obergrenze jeder Meldung einzeln
gebildet hat. Mit 0048 zieht eine Meldung von 316 Zeichen ein, und die sechs Schrittpakete
hängen ihre eigene Prosa an dieselbe Klasse. Der Fall ist nicht ausgedacht, er ist
terminiert.
