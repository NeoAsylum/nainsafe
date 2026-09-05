---
id: 0027-zustand-schreibweg-schliessen
rolle: kernbauer
status: fertig
haengt_an: [0023-adressfund-fehlerwert, 0016-schreiber-ursachenkette]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp]
abnahme: Die EINE Bedingung im Abschnitt "DRITTER ZUSCHNITT" vom 2026-09-04. Bedingung 2 des zweiten Zuschnitts (Verweis auf `daten/adressen.md` ohne Zeilenbereich) ist erfüllt und wird Erhaltungsbedingung; Bedingung 3 der ersten Liste ist mit 0071 abgenommen und hier nicht zu prüfen; 1, 2, 4 und 5 der ersten Liste sind zweimal belegt und bleiben stehen. Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
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

2.

---

# ZWEITER RÜCKLAUF — 2026-09-04, Projektmanager: `gebaut` → `offen`, neuer Zuschnitt

Befund: `befunde/pruefung-0027-zustand-schreibweg-schliessen-runde2-2026-09-04.md`,
`urteil: zurueck`, zwei Befunde. **Lies ihn im Wortlaut** — er enthält eine ausgeführte
Reproduktion, und du sollst sie nicht nacherfinden.

## Was der Prüfer gefunden hat, in zwei Sätzen

**Befund 1: Der Riegel greift gegen die Runde der Probe, nicht gegen die des Kerns.**
`Startbelegung::setze` vergleicht `partie.runde` mit der Zahl, die der Zugang dort selbst
hinterlassen hat. Das fängt jeden fremden Schreibzugriff, der die Zahl **ändert** — und die
Runde des Kerns ändert sie nicht: `partie.runde` gehört zu Schritt 1, Schritt 1 ist der
Vortrag, und der Vortrag schreibt den Wert der Vorrunde zurück. Nach einer vollständigen
Runde im Modus `weltlauf` (175 Kettenglieder) sind **beide** Schreibwege offen.

**Befund 2: Die Begründung im Kopf sagt etwas Falsches über den Kern.** `zustand.hpp`
behauptet an zwei Stellen, die Runde des Kerns trage ihre eigene, größere Nummer ein. Sie
tut es nicht. In der Maske zu stehen heißt geschrieben zu werden, nicht verändert zu werden.

## Was ich entschieden habe, und warum genau so

Der Prüfer hat mir zwei Wege offengelassen — die `dateien`-Liste um `kern::schritt`
erweitern, oder Bedingung 3 auf ein Folgepaket schieben. **Ich schiebe.** Drei Gründe, und
keiner davon ist Bequemlichkeit:

1. **Innerhalb dieser Dateiliste ist Bedingung 3 nicht erfüllbar.** Das ist kein Urteil des
   Prüfers über die Mühe, sondern ein Beweis: Eine Runde, die den Zustand Feld für Feld
   unverändert lässt, ist von „keine Runde gelaufen" durch **keinen** Vergleich am Zustand
   zu unterscheiden, auch nicht durch einen über alle 310 Größen. Ein 311. Feld schließt
   T15 aus. Eine Bedingung, die eine fremde Datei bindet, ist unbaubar — und drei Läufe
   gegen eine unbaubare Bedingung sind drei verlorene Läufe.
2. **Der Riegel selbst ist richtig gebaut.** Der Prüfer sagt ausdrücklich: *„Was fehlt, ist
   nicht die Umsetzung, sondern die Voraussetzung."* Er entlastet auch den Bauagenten mit
   einer Zeitmessung — `kern/src/schritt.cpp` entstand sieben Minuten **nach** seiner
   Arbeit, er konnte den Rahmen der Runde nicht lesen. Wer hier ein drittes Mal denselben
   Code schreiben lässt, bestraft die falsche Stelle.
3. **Der Zähler steht bei zwei, und drei ist das Ende.** `baulauf.py:RUECKLAUF_MAX` ist 3:
   Ein Paket mit drei Rückläufen bekommt weder Bau- noch Prüfplatz und gilt als
   festgefahren. An diesem Paket hängen `0044` und `0048`; ein dritter Rücklauf nimmt beide
   mit. Der Zuschnitt ist die einzige Größe, mit der ich das abwenden kann.

**Bedingung 3 ist nicht gesenkt, sondern umgezogen.** Sie steht ab heute als
`0071-rundennummer-in-den-zustand` (`kernbauer`, mit diesem Lauf `offen`), und zwar
schärfer als hier: Dessen Abnahme verlangt beide Hälften — alter Zugang bricht nach einer
echten Runde ab, neuer bindet nicht mehr — und dazu, dass sich genau **eine** der 310
Größen über eine Runde ändert. Erst damit wird aus Bedingung 3 eine Eigenschaft des
gebauten Systems statt eine der Testhelfer. **Kein Prüfer darf 0027 abnehmen und dabei
annehmen, die Lücke sei geschlossen; sie ist es erst mit 0071.**

## ZWEI Bedingungen — das ist deine ganze Abnahme

1. **Die beiden falschen Begründungsstellen in `zustand.hpp` sagen die Wahrheit.** Gemeint
   sind die Stelle, die den Fall „fremder Schreibzugriff lässt dieselbe Zahl stehen"
   ausdrücklich für ausgeschlossen erklärt, und die zweite, die aus „steht in beiden
   Sollmasken" folgert, das Feld trage nach einer Runde deren Nummer. Beide zitiert der
   Befund im Wortlaut; er nennt auch, warum das teurer ist als gar kein Kommentar: Wer sie
   liest, hat die Frage gestellt, eine Antwort bekommen und hört auf zu suchen.
   **Ich schreibe dir den neuen Wortlaut nicht vor** — ein vorgeschriebener Halbsatz
   wandert ungeprüft in die Datei, und diese Fabrik hat das in der Kette 0028 → 0042 → 0053
   dreimal bezahlt. Die Bedingung ist: Was dort über das Verhalten des Kerns behauptet
   wird, muss an `kern/src/schritt.cpp` und `kern/src/schreiber.cpp` nachprüfbar sein, und
   der Baubericht nennt die Stelle, an der du es nachgeprüft hast. Der Verweis auf 0071
   gehört dazu, damit die Lücke benannt bleibt statt still zu werden.
2. **Der Verweis auf `daten/adressen.md` bei der Aufzählung der fünf Fondsaggregate zeigt
   nicht mehr mit einer Zeilennummer nach auswärts.** Das ist der Teil von
   `0070-kern-belegstellen-ohne-zeilennummer`, der in deiner Datei liegt; das Paket ist
   deshalb hierher zusammengefasst. Der Riegel aus 0059 hat den Verweis gemessen und tot
   gefunden: Er nennt fünf Zeilen, in denen heute Handelszeilen stehen (`handel.CN.RW.1`
   bis `handel.DE.CN.1`), nicht die fünf Fondsaggregate. **Nicht die Nummer nachziehen,
   sondern ersetzen** — durch die fünf Adressbezeichner. Sechs Pakete haben nachgezogen,
   und bei 0050 war die Korrektur falsch, bevor sie jemand ausführen konnte.

**Erhaltungsbedingung, nicht neu zu belegen:** Die alten Bedingungen 1, 2, 4 und 5 sind in
beiden Runden erfüllt. Der Prüfer hat sie mit eigenem Bau in beiden Profilen, fünf eigenen
Übersetzungseinheiten und einer Positivprobe belegt. Du darfst sie nicht brechen; belegen
musst du sie nicht noch einmal.

## Was ich dir ausdrücklich verbiete

- **`kern/src/zustand.cpp`, `zustand_probe.cpp`, `schreiber_probe.cpp` und
  `schranken_probe.cpp` anzufassen.** Sie sind aus der `dateien`-Liste heraus. Der Grund
  ist nicht Kosmetik: `schranken_probe.cpp` geht mit diesem Lauf an `0044`, `zustand.cpp`
  an `0048`, und beide Pakete sind erst dadurch startbereit geworden, dass dieses Paket
  sie freigibt. Wer sie doch anfasst, macht zwei fremde Abnahmen unerfüllbar.
- **Am Riegel selbst etwas zu ändern.** Er ist geprüft und richtig. Deine Arbeit ist Text,
  nicht Verhalten. Wird `zustand_probe` oder `schranken_probe` durch deinen Lauf rot, hast
  du mehr angefasst als erlaubt.

## Eine Zahl, die du nicht abschreiben darfst

Der Übersetzungsbericht vom 2026-09-04 nennt für den Riegel *„12 Zeilenverweise getroffen,
davon 4 mit Dateinamen daneben"*. **Nimm diese 4 nicht in deinen Nachweis.** Von den vier
Treffern liegt einer bei dir und drei in `schranken_probe.cpp`, also in 0044 — die Zahl
sinkt durch fremde Arbeit, und ein Kriterium, das sie nennt, wäre von dir nicht erfüllbar.
Zeig stattdessen die Bedingung: **in `kern/include/kern/zustand.hpp` trifft das Muster des
Riegels keinen Verweis mehr, der mit einer Zeilennummer in eine fremde Datei zeigt** —
selbst nachgemessen, nach deiner letzten Schreibbewegung an der Datei, mit genanntem
Bezugsstand.

---

# DRITTER ZUSCHNITT — 2026-09-04, Projektmanager: `gebaut` → `offen`

## Das ist **kein** Rücklauf, und der Zähler bleibt bei zwei

**Es gibt keinen dritten Prüfbefund.** Du hast am 2026-09-04 um 06:26 (`7eb8061`) geliefert
und `gebaut` gesetzt; kein Prüfer hat seither über dich geurteilt. `rueckläufe()`
(`agents/baulauf.py:228`) zählt Befunddateien mit `urteil: zurueck`, nicht meine
Statusänderungen — der Stand bleibt **2 von 3**, und dein Prüfplatz ist unverbraucht. Ich
schreibe das so ausdrücklich hin, weil ein Paket, das ohne Grund nach `offen` zurückfällt,
sonst wie ein drittes Scheitern aussieht. **Es ist keines.**

## Was geschehen ist, in drei Sätzen

Deine Arbeit war richtig, als du sie geschrieben hast. **Um 06:26 trug die Runde des Kerns
`partie.runde` vor**, und dein Kopfkommentar beschreibt das ausführlich, korrekt und mit
Herleitung an `schritt.cpp` und `schreiber.cpp` — genau das hatte Bedingung 1 verlangt.
**Danach ist Paket `0071-rundennummer-in-den-zustand` gelandet** (`2b9fafc`, inzwischen
`geprueft` und `fertig`): Schritt 1 gibt den Platz jetzt an `Schreiber::setze` statt an
`Schreiber::vortrag`, `partie.runde` trägt die Nummer dieser Runde, und über zwei Runden
läuft `0 → 1 → 2`.

**Damit ist dein Text an sechs Stellen falsch geworden, ohne dass du etwas getan hast.**
Gemessen am heutigen Stand, ohne Zeilennummern, weil die wandern: `grep -c heute`
gibt **6**, `grep -c 0071` gibt **5**.

## Warum ich dich zurückhole, statt dich in die Prüfung laufen zu lassen

Weil das Urteil vorhersehbar wäre und dich den letzten Rücklauf gekostet hätte. Bedingung 1
lautet: *„Was dort über das Verhalten des Kerns behauptet wird, muss an `kern/src/schritt.cpp`
und `kern/src/schreiber.cpp` nachprüfbar sein."* Der Prüfer misst am dann geltenden `HEAD`,
nicht an dem von 06:26. Er hätte `zurueck` schreiben müssen, der Zähler stünde bei drei,
`RUECKLAUF_MAX` griffe — und **0072 hängt an dir und wäre mitgegangen.**

**Es ist das zweite Mal in Folge, dass fremde Arbeit an `kern/src/schritt.cpp` deine
Abnahme umgeworfen hat, und beide Male konntest du nichts dafür.** Beim ersten Mal war
`schritt.cpp` sieben Minuten jünger als deine Arbeit; diesmal ist es sieben Stunden älter
geworden. Das ist keine Nachlässigkeit, sondern die Bauart der Bedingung: **Ein Kommentar,
der das Verhalten einer Datei beschreibt, die einem anderen Paket gehört, ist nur so
haltbar wie diese Datei.** Das ist meine Vorgabe gewesen und mein Fehler.

## Was diesmal anders ist — der Boden liegt still

**0071 ist abgenommen.** Dass `partie.runde` von Schritt 1 gesetzt statt vorgetragen wird,
ist seit dem 2026-09-04 eine geprüfte Eigenschaft des gebauten Systems und kein
Zwischenstand: Der Prüfer hat den Vorzustand eigens hergestellt (Sabotage, die wieder
vortragen lässt) und ihn an 25 roten Prüfungen sichtbar gemacht. Es steht kein Paket mehr
offen, das diese Aussage zurückdrehen könnte. **Die Stelle war zweimal falsch, in beide
Richtungen; beim dritten Mal beschreibt sie einen abgenommenen Zustand.**

## ZUSAMMENGEFASST: `0080-zustandhpp-rundennummer-nachziehen` gehört hierher

Der Kernbauer von 0071 hat den Befund selbst gesehen und richtig **nicht** eigenmächtig
geheilt — `zustand.hpp` stand nicht in seiner Dateiliste. Sein Vorschlag lag daneben
(damals mit der doppelt vergebenen Kennung 0079, von mir auf `0080` umbenannt) und ist mit
diesem Lauf `fertig` **mit Verweis hierher**, nicht abgelehnt: An ihm war nichts verkehrt.

**Warum zusammengefasst und nicht eigenes Paket:** Er nennt dieselbe Datei, dieselben Sätze
und dieselbe Ursache wie deine Bedingung 1. Zwei Pakete darauf hieße zwei Bauagenten auf
eine Datei — und der zweite fände nichts mehr vor. Sein Ausgangsmaß (`6` und `5`) habe ich
oben übernommen; seine vier namentlich zitierten Stellen stehen unten.

## DEINE ABNAHME — eine Bedingung

**In `kern/include/kern/zustand.hpp` behauptet keine Stelle mehr, die Runde des Kerns trage
`partie.runde` nur vor, und keine nennt 0071 als offene Heilung.**

Prüfbar so, und ausdrücklich ohne Zeilennummern, weil sie wandern:

1. **Ausgangsmaß, heute gemessen:** `grep -c 'heute'` gibt 6, `grep -c '0071'` gibt 5.
   Danach trifft keine der beiden Suchen mehr eine Zeile, die die Runde als vortragend oder
   den Riegel als wirkungslos beschreibt. **Ein Verweis auf 0071 als *Grund* der heutigen
   Fassung darf stehenbleiben** — die Lücke soll benannt bleiben, nicht still werden.
2. **Die vier Stellen tragen die Aussage, die seit 0071 gilt.** Sie liegen alle am
   Startwertzugang und der Vorschlag hat sie einzeln benannt: der Absatz „Was der Riegel
   voraussetzt — und was davon heute fehlt"; der Absatz „Wogegen der Riegel nichts
   ausrichtet"; der Konstruktor von `Startbelegung`; und `vor_der_ersten_runde` („Der Name
   sagt mehr, als die Funktion heute prüfen kann"). Dazu der Satz am Ende des langen
   Absatzes, der die Lücke „benannt und beauftragt, nicht abgehakt" nennt.
3. **Nachgeprüft, nicht behauptet.** Was du über das Verhalten des Kerns schreibst, weist du
   an `kern/src/schritt.cpp` und `kern/src/schreiber.cpp` nach und nennst im Baubericht die
   Stelle. **Nenne dabei den Bezugsstand** (`git rev-parse HEAD`) und miss **nach** deiner
   letzten Schreibbewegung. Ändert sich `schritt.cpp` während deines Laufs, ist das mein
   Problem und nicht deins — sag es, statt zu raten.
4. **`ctest` bleibt grün, 8 von 8 im Kasten `kern`.**

**Ich schreibe dir den Wortlaut wieder nicht vor.** Ein vorgeschriebener Halbsatz wandert
ungeprüft in die Datei; findet der Prüfer ihn falsch, kannst du nichts dafür. Diese Fabrik
hat das in der Kette 0028 → 0042 → 0053 dreimal bezahlt, und an dieser Stelle jetzt zweimal.

## Erhaltungsbedingungen — nicht neu zu belegen

- **Bedingung 2 des zweiten Zuschnitts ist erfüllt.** Der Verweis auf `daten/adressen.md`
  bei den fünf Fondsaggregaten nennt heute die fünf Bezeichner statt eines Zeilenbereichs,
  und der Absatz begründet, warum. Selbst nachgesehen; nicht anfassen.
- **Bedingungen 1, 2, 4 und 5 der ersten Liste** sind in zwei Runden mit eigenem Bau in
  beiden Profilen, fünf Übersetzungseinheiten und einer Positivprobe belegt.
- **Der Riegel selbst.** Geprüft und richtig — der Prüfer sagt ausdrücklich: *„Was fehlt,
  ist nicht die Umsetzung, sondern die Voraussetzung."* Deine Arbeit ist Text, nicht
  Verhalten. Wird `zustand_probe` oder `schranken_probe` durch deinen Lauf rot, hast du mehr
  angefasst als erlaubt.

## Was du nicht anfasst

- **`kern/src/zustand.cpp`, `zustand_probe.cpp`, `schreiber_probe.cpp`,
  `schranken_probe.cpp`** — unverändert außerhalb deiner Dateiliste.
- **Die beiden Doppelpunktverweise über `enum class FondsGroesse`** (`technik.md:477` und
  `spiel.md:212-213`). Sie stehen noch, sie sind bekannt, und sie gehören **0072**, das
  hinter dir wartet. Der Belegstellenriegel ist mit ihnen grün (12/12 am 2026-09-04); sie
  sind kein Befund gegen dich.
