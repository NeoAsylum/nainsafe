---
id: 0027-zustand-schreibweg-schliessen
rolle: kernbauer
status: offen
haengt_an: [0023-adressfund-fehlerwert, 0016-schreiber-ursachenkette]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/zustand.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/zustand_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schreiber.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schreiber.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schreiber_probe.cpp]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
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
3. **Der benannte Startwertzugang existiert, ist begründet, und er umgeht die
   Rundenendprüfung nicht.** Die Probe zeigt: Ein über ihn gesetzter Wert erzeugt keinen
   Ursachensatz — das ist gewollt und der Grund, warum er nur vor der ersten Runde
   zulässig ist —, und ein Versuch, ihn **während** einer Runde zu benutzen, ist ein harter
   Fehler. Zeig beides ausgelöst, mit ausgeschriebener Meldung.
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

## Rückläufe

0.
