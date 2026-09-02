---
id: 0027-zustand-schreibweg-schliessen
rolle: kernbauer
status: offen
haengt_an: [0023-adressfund-fehlerwert, 0016-schreiber-ursachenkette]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/zustand.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/zustand_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schreiber_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schranken_probe.cpp]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme", in der Fassung des Rücklaufs vom 2026-09-02. Bedingung 3 ist neu gefasst; 1, 2, 4 und 5 sind unverändert und bereits einmal belegt. Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# `Zustand::feld` schliessen — die zweite Hälfte von T18

Vorgabe: `technik.md` T18, dazu T19. Der Befund, aus dem dieses Paket entsteht:
`befunde/pruefung-0016-schreiber-ursachenkette-2026-09-02.md`, Befund 1. Lies ihn im
Wortlaut; hier steht nur, was zu tun ist.

**Das ist kein Rücklauf.** Paket 0016 ist `geprueft` und `fertig`, alle sechs Bedingungen
erfüllt. Der Befund reisst keine davon — er betrifft eine Zusage, die 0016 in seinen drei
Dateien gar nicht durchsetzen **konnte**.

## Der Befund, in drei Sätzen

T18 sagt: *„Die Felder von `Zustand` sind ausserhalb des Kerns nicht schreibbar; innerhalb
schreibt niemand direkt, sondern über `Schreiber::setze(...)`."* Gebaut ist die eine
Hälfte — `setze` existiert und tut das Richtige. Die andere gibt es nicht:
`kern::zustand::Zustand` ist ein `struct` mit öffentlichem `std::array<i64, 310> feld` und
öffentlichem `schreibe(index, wert)` (`zustand.hpp:390-410`).

**So erzeugt man den Fehler:** Eine beliebige Übersetzungseinheit bindet `kern/zustand.hpp`
ein — `schreiber.hpp` ist dafür nicht nötig —, hält einen `Zustand` und ruft
`zustand.schreibe(adresse, wert)` oder schreibt `zustand.feld[adresse] = wert`. Der Wert
steht im Zustand. Es entsteht **kein** Ursachensatz, das Bitfeld sieht nichts, die
Rundenendprüfung sieht nichts, und kein Übersetzer und kein Sanitizer meldet etwas.

**Was daran teuer ist.** Die Zusagen „genau einmal je Runde" und „acht Kanäle, nicht neun"
gelten nur für Schreibzugriffe durch `setze`. Ein späterer Bauagent, der in `kern::schritt`
einmal `feld[i] = ...` schreibt, erzeugt einen neunten Rückkopplungskanal, der in keiner
Ursachenkette auftaucht — und die `diff`-Ebene aus T20 zeigt dann eine Änderung ohne
Ursache. Das ist genau die Sorte Fehler, die T18 verhindern soll, und sie fällt erst auf,
wenn jemand einem Diff nicht glaubt.

## Warum es zwischen zwei Paketen durchgefallen ist

Paket 0008 hat die Durchsetzung ausdrücklich weitergereicht (`zustand.hpp:385-389`: *„die
Durchsetzung gehört deshalb dem Paket, das den Schreiber baut"*), und Paket 0016 hat sie
nicht aufgenommen — `zustand.hpp` stand nicht in seiner `dateien`-Liste. Zwischen beiden
lag eine Lücke, die keiner der beiden Bauagenten schliessen durfte. Dieses Paket hält
deshalb **beide** Kästen.

## Was du baust

1. **`feld` und `schreibe` werden unzugänglich** — privat, mit
   `friend class schreiber::Schreiber` oder einem Zugriffsschlüssel. Welche der beiden
   Formen, entscheidest du; begründe sie in einem Satz.
2. **Der Startwertweg bekommt einen benannten zweiten Zugang.** Er wird gebraucht: Der
   Kasten `daten` muss die Startwerte einmal einsetzen können, und die Proben von 0008 und
   0016 brauchen ihn ebenfalls — `schreiber_probe.cpp:212` und `:364-365` schreiben heute
   mit `vorrunde.schreibe(...)` am Schreiber vorbei. Dort ist das mangels Startwertquelle
   alternativlos und harmlos; es belegt aber, dass der Weg offensteht. Gib diesem Zugang
   einen Namen, der sagt, wofür er da ist, und schreib in einem Satz daneben, warum er
   **kein** zweiter Schreibweg im Sinne von T18 ist.
3. **Die Proben von 0008 und 0016 laufen weiter** — sie werden auf den neuen Zugang
   umgestellt, nicht gelöscht und nicht ausgeklammert.

## Was du nicht baust

- **Keine Änderung an der Bedeutung von `setze`, an der Ursachenkette, am Bitfeld oder an
  der Rundenendprüfung.** Sie sind abgenommen. Dieses Paket ändert, **wer** schreiben darf,
  nicht **was** beim Schreiben passiert.
- **Keine neuen Felder in `Ursachensatz`.** Bedingung 1 von 0016 hält die Zahl auf sieben.
- **`kern::schritt` nicht.** Es hat kein Paket.

## Abnahme

1. **`Zustand::feld` und `Zustand::schreibe` sind ausserhalb des Schreibers nicht mehr
   erreichbar.** Der Prüfer schreibt eine Übersetzungseinheit, die nur `kern/zustand.hpp`
   einbindet und `zustand.feld[0] = 1` beziehungsweise `zustand.schreibe(0, 1)` versucht:
   **beides muss ein Übersetzungsfehler sein.** Ein Laufzeitabbruch genügt nicht — die
   Zusage ist eine Eigenschaft des Codes oder keine.
2. **Die Grep-Regel läuft leer.** `grep -rn '\.feld\[' kern/` und
   `grep -rn '\.schreibe(' kern/` liefern ausserhalb von `zustand.hpp`, `zustand.cpp` und
   dem in Punkt 2 benannten Startwertzugang keinen Treffer. Damit ist die Regel danach so
   mechanisch prüfbar wie die Gleitkommasperre aus T4.
3. **Der benannte Startwertzugang existiert, ist begründet, und er riegelt beim
   *Schreiben* ab, nicht beim *Binden*.** Neu gefasst im Rücklauf vom 2026-09-02; die
   Begründung steht unten im Abschnitt *Rücklauf 1*. Drei Teilbedingungen, alle drei am
   laufenden Test zu zeigen:

   a. **Ein über den Zugang gesetzter Wert erzeugt keinen Ursachensatz.** Unverändert,
      gewollt, und der Grund, warum es den Riegel überhaupt gibt. War erfüllt.
   b. **Das Binden an einen Zustand mit gelaufener Runde ist ein harter Fehler.**
      Unverändert. War erfüllt.
   c. **Ein bereits gebundener Zugang, an dem eine Runde vorbeigelaufen ist, bricht beim
      nächsten Schreibzugriff ab** — mit ausgeschriebener Meldung, die den Grund nennt und
      nicht nur den Ort. Die Probe führt es vor: Zugang vor der ersten Runde binden, eine
      Runde über denselben Zustand laufen lassen, das Rundenende zurückschreiben, den
      alten Zugang benutzen. **Das ist der gerissene Teil.**

   Und die Gegenprobe dazu, damit c. nicht durch Zubetonieren erfüllt wird: **Die beiden
   Belegungsschleifen in `zustand_probe.cpp` laufen weiter durch.** Der Zählzustand ergibt
   weiterhin die Prüfsumme `25e8b19071bea26c`, die Gegenprobe mit zwei getauschten Feldern
   weiterhin eine andere. Wer diese Zahl ändert, hat die Feldreihenfolge angefasst und
   braucht dafür einen eigenen Grund.
4. **Alle sechs Bedingungen von 0016 und die von 0008 halten unverändert.** Insbesondere:
   `Ursachensatz` trägt sieben Felder, `UrsacheArt` sechs Formen, zweiter Schreibzugriff
   und `lies_neu` vor dem Schreiben sterben weiterhin, die Maskenprüfung bleibt zweiseitig
   (175 / 135 / 310).
5. **`ctest` nennt `zustand_probe` und `schreiber_probe` beide namentlich und bestanden.**
   Der Übersetzungsbericht `befunde/uebersetzung-<datum>.md` ist der Nachweis. Ein Kasten
   ohne benannten Test ist im Bericht von einem, den es nicht gibt, nicht zu unterscheiden
   — ein leerer Bauabschnitt ist deshalb ein Rücklauf, kein Bestehen.

## Was ausdrücklich kein Befund ist

- **Die Wahl zwischen `friend` und Zugriffsschlüssel**, der Name des Startwertzugangs und
  die Frage, ob er eine eigene Klasse oder eine Methode ist. `specs/` schweigt dazu.
- **Dass die Startwerte selbst noch nirgends herkommen.** Der Kasten `daten` legt sie
  später auf die Platte; dieses Paket baut nur den Zugang, nicht die Quelle.

---

# Rücklauf 1 — 2026-09-02

Befund: `befunde/pruefung-0027-zustand-schreibweg-schliessen-2026-09-02.md`,
`urteil: zurueck`. **Lies ihn im Wortlaut.** Hier steht, was daraus für dich folgt.

## Was steht und nicht angefasst wird

**Vier von fünf Bedingungen halten**, und der Prüfer hat sie nicht auf dein Wort hin
abgenommen, sondern selbst gebaut: beide Bauprofile grün, 6 von 6 Tests, drei eigene
Übersetzungseinheiten gegen `kern/zustand.hpp` — alle drei abgewiesen, einschliesslich des
neuen rohen Schreibzugriffs, den die Bedingung gar nicht verlangt hatte.

Das ist der Ausgangspunkt: **Bedingung 1, 2, 4 und 5 sind belegt und müssen belegt
bleiben.** Sie stehen nicht zur Disposition, und die Wahl der Zugriffsform ist es auch
nicht — der Prüfer nennt sie ausdrücklich richtig und gut begründet.

## Was gerissen ist

Bedingung 3 verlangte, ein Versuch, den Zugang **während** einer Runde zu benutzen, sei ein
harter Fehler. Geprüft wird aber nur **im Konstruktor**. Die Setzfunktion
(`zustand.cpp:887-891`) besteht aus einer Anweisung: Sie reicht Adresse und Wert weiter und
prüft nichts. Ein einmal gebundener Zugang schreibt beliebig lange weiter.

**Der Nachweis läuft heute schon, in deiner eigenen grünen Probe.**
`zustand_probe.cpp:619-625` bindet einen Zugang an einen frischen Zustand und benutzt ihn
über alle 310 Plätze. Bei Platz 306 schreibt er die 306 nach `partie.runde`; ab Platz 307
meldet `vor_der_ersten_runde` falsch — und derselbe Zugang schreibt trotzdem 307, 308, 309.
Der Block `:640-648` wiederholt es fünfmal. **Acht ausgeführte Schreibzugriffe hinter dem
Riegel, ohne Ursachensatz, alle grün.** Dass sie wirklich landen, beweist die Probe selbst:
Ihre Prüfsumme `25e8b19071bea26c` wäre eine andere, wenn dort Nullen stünden.

Dein Kommentar `:635-639` („derselbe Riegel wie unten, nur hier gewollt umgangen") trifft
die Wirkung, aber nicht den Grund: Umgangen wird der Riegel nicht dadurch, dass die Belegung
von vorn beginnt, sondern dadurch, dass er nie wieder gefragt wird.

## Warum das teuer ist und nicht bloss unschön

Der Schaden entsteht in der Form, die `kern::schritt` bekommt — Paket 0033 baut sie gerade.
Der Schreiber nimmt den Vorrundenzustand unveränderlich entgegen; die natürliche
Rundenschleife bindet den Startwertzugang also **vor** der Schleife und schreibt das
Ergebnis jedes Mal zurück. Danach steht der Zugang immer noch da und ist immer noch offen.
Die nächste Setzung ist dann eine Änderung ohne Ursache — wortgleich der Schaden, den dieses
Paket oben unter *Was daran teuer ist* verhindern soll.

## Der Weg, den der Prüfer sieht — die Form entscheidest du

Die naheliegende Fassung geht nicht, und dein Grund dafür gilt: Unter den 310 Grössen ist
`partie.runde` selbst. Eine Prüfung, die vor jeder Setzung stumpf verlangt, dass die Runde
null ist, liesse dieselbe Belegung je nach Reihenfolge ihrer Aufrufe mal zu und bräche mal
ab — und rötete die beiden Schleifen sofort.

**Der Ausweg:** Ein Zugang darf weiterschreiben, solange die Partie vor ihrer ersten Runde
steht **oder er die Rundennummer selbst gesetzt hat.** Dann trägt die Schleife weiter, und
ein Zugang, an dem die Runde vorbeigelaufen ist, fällt beim nächsten Schreibzugriff auf.

Zwei Nebendinge, die dazugehören und ausgeschrieben werden müssen, so oder so:

1. **Ein Zugang lässt sich heute kopieren.** Ob eine Kopie das Recht mitnimmt, beantwortet
   dieses Paket — ausdrücklich, nicht stillschweigend.
2. **Der Zugang zeigt auf einen Zustand, den er nicht besitzt**, und kann ihn überleben. Ob
   du das mit der Verriegelung oder mit einer engeren Lebensdauer löst, ist deine
   Entscheidung.

**Kein 311. Feld.** T15 hält die Zahl der Grössen bei 310, und du hast aus gutem Grund den
Riegel auf ein vorhandenes Feld gelegt statt auf einen Merker daneben. Dabei bleibt es.

**Nicht anfassen:** Setzfunktion des Schreibers, Ursachenkette, Bitfeld, Rundenendprüfung,
Sichtbarkeit des rohen Schreibzugriffs. Alle abgenommen.

## `schranken_probe.cpp` — warum sie jetzt in `dateien` steht

Der zweite Befund ging an mich, nicht an dich: Dein Commit `6df9a3b` hat
`kern/test/schranken_probe.cpp` an 43 Aufrufstellen geändert, obwohl die Datei nicht in der
Liste stand. **Du konntest nicht anders** — Bedingung 2 verlangt, dass der alte Aufruf im
ganzen Kernbaum verschwindet. Der Fehler lag in meiner Paketbeschreibung. Sie steht jetzt
drin, und damit ist auch die Fussangel dieses Rücklaufs erreichbar: Die Hilfsfunktion
`schranken_probe.cpp:91` bindet **je Aufruf** einen neuen Zugang. Heute geht das gut, weil
keine der 43 Stellen `partie.runde` anfasst — mit dem Riegel aus Teilbedingung c. bricht sie
ab, sobald eine Schranke einen Randfall auf einem Zustand mit gelaufener Runde braucht.
Bring sie im selben Lauf in Ordnung; sie ist Teil der Arbeit, nicht ein Folgepaket.

## Warum das kein eigenes Paket geworden ist

Der Prüfer hat einen Vorschlag danebengelegt (`0037-startbelegung-riegel-je-schreibzugriff`)
und dafür argumentiert, dies sei „kein Rücklauf in der Sache". Das Argument ist gut, aber es
kollidiert mit dem Urteil, das er selbst gesetzt hat. **Als eigenes Paket wäre es ein
Deadlock:** Es hängt laut Vorschlag an 0027, und 0027 kann ohne genau diese Arbeit nie
`fertig` werden. Dazu beanspruchen beide dieselben vier Dateien und dürften ohnehin nie
gleichzeitig laufen. Der Vorschlag ist deshalb **in dieses Paket zusammengefasst**; sein
Inhalt steht oben. — *Projektmanager, 2026-09-02*

## Rückläufe

1.
