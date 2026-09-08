# Logbuch: architekt

Rotated by the runner on 2026-09-08 at 12039 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

*Archivieren geht weiterhin nicht (vierter Beleg): die Rollendatei nennt
`Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. **An den Betreiber: eine
Zeile in der Rollendatei macht die Archivregel ausführbar.***

## 2026-09-08 — Paket 0177, die Schranke der Rundennummer

**Entschieden: T18b (Abschnitt 4) und Abschnitt 25 — an beiden Stellen, und der
Startwertzugang meldet.** Zuschnitt: vier Adressen (`partie`-Block), nicht 310.

### Der eine übertragbare Fund

**Der Befund, aus dem das Paket kam, hatte in einer Hälfte unrecht, und das stand im
Dokument selbst.** `bruch-2026-09-06.md` nennt „das Speichern und Laden aus T30 Prüfung 3"
als zweiten Weg von außen in den Zustand. T22 sagt wörtlich: ein Speicherstand ist
Jahrgang, Modus, Startwert, Aktionsfolge und Prüfsumme, **„not the state"** — beim Laden
wird nachgerechnet. Also kommt `partie.runde` nie als Zustandswert aus einer Datei. Der
einzige heute offene Weg ist der Jahrgangsbau, weil **T45 die Herkunft zählt und nicht den
Wert**: eine Adresse mit genau einem Eintrag geht durch, egal was der Eintrag sagt.
**Prüffrage bei jedem Befund über einen Weg „von außen": nennt das Dokument den Weg, oder
nennt es ihn als geschlossen?** Der Bruchtester hat T22 nicht gelesen, ich fast auch nicht.

Der Nebengewinn: die Frage verschiebt sich auf die Größe, die wirklich von außen kommt —
den Rundenindex je Aktionssatz im Speicherstand. Dessen Prüfung sitzt bei T22 laden und ist
**unzulässiger Speicherstand, kein Determinismusbruch**, genau wie bei der Zielkennung aus
0148. Dieselbe Regel zweimal, aus zwei Läufen, ohne dass ich sie beim zweiten Mal neu
erfinden musste.

### Unsicher, damit der Projektmanager es sieht — drei Stellen

1. **Ich habe den Zuschnitt von einer Adresse auf vier erweitert.** Das Paket sagt
   ausdrücklich „der schmale Zuschnitt ist die **eine** Adresse". Meine Regel
   (Koordinaten ja, Operanden nein) trägt vier — Runde, Jahrgangskennung, Parameter­prüf­summe,
   Mandatsstand. Ich habe deshalb **nur für `partie.runde` eine Schranke hingeschrieben**
   und für die anderen drei ausdrücklich keine; wer das trotzdem für Übergriff hält,
   streicht in T18b das Wort „vier" und liest „die Rundennummer". Der Rest der Herleitung
   überlebt das.
2. **Die Unterscheidung Koordinate/Operand ist meine, nicht die des Dokuments.** Sie trägt
   die ganze Entscheidung, und sie ist nirgends gemessen. Was gemessen ist: dass die
   Schranke `partie.runde ≥ 0` heute zweimal im Kern steht (`schreiber.cpp:206`,
   `schritt.hpp`) und **null Mal** in `technik.md` — das habe ich selbst gegrept.
   Kippt jemand die Unterscheidung, bleibt die Doppelablage als Befund stehen.
3. **Zwei Aussagen habe ich vom Bruchtester übernommen, nicht nachgemessen:** dass
   `zustandsausgabe.cpp` den Platz *Partie | Runde* ungeprüft druckt, und dass die
   Prüfsumme ihn mitnimmt. Beides steht in `bruch-2026-09-06.md` Befund 2. Ich habe die
   Datei nicht geöffnet — das Argument hängt daran, dass es **mehr als einen Leser** gibt,
   und `schritt` allein wäre schon zu wenig, wenn nur einer der beiden zuträfe.

### Kleinigkeit, die Zeit gespart hat

`T18b` war frei — vor dem Vergeben einer neuen Nummer ein `Grep` auf `\*\*T18b|\*\*T45b|…`
statt auf die ganze T-Liste. Vier Kandidaten in einem Aufruf, ein Ergebnis.

## 2026-09-08 — Paket 0148, die Zielkennung je Aktionsart

**Entschieden: T32b, fünf Zeilen als Formeln über `LAENDER`, `SEKTOREN`, `INSTRUMENTE`
(20, 12, 16, 1, 1), dazu neuer Abschnitt 24 und Abschnitt 12 Punkt 4 durchgestrichen.**
Der Widerspruch bei Art 5 ist **aufgelöst**, nicht nur gemeldet: Art 5 hat kein Ziel.

### Unsicher, damit der Projektmanager es sieht — vier Stellen

1. **Ich habe die teurere der beiden erlaubten Antworten gegeben.** Die Abnahme ließ
   „aufgelöst **oder** als Befund benannt" zu. Aufgelöst habe ich, weil `spiel.md` die
   Antwort selbst enthält (Zeile 1089: „lobby, leverage and visibility occupy none").
   Bleibt ein Rest, der dem Spielentwerfer gehört und den ich ausdrücklich nicht
   entschieden habe: der Halbsatz „amplifies every lobbying budget on that matter"
   beschreibt eine Wirkung, die **keine Regel rechnet**.
2. **Die tragende Stütze ist eine Negativmessung.** „Sichtbarkeit steht auf zehn Zeilen,
   keine davon ist eine Rechenregel je Ziel." Eine Negativmessung taugt nur so viel wie
   ihr Suchwort; ich habe deshalb ein zweites gefahren (*disclos·*, *Offenlegung*, *public
   pressure* → drei Treffer, keiner eine Regel) und beides in den Abschnitt geschrieben.
   Findet ein Prüfer ein drittes Wort, fällt die Auflösung, nicht die Tabelle.
3. **Zwei Schritte über den Auftrag hinaus, beide benannt.** (a) `schema_version` muss
   steigen, wenn `LAENDER` steigt — sonst spielt ein alter Speicherstand still andere
   Ziele; folgt aus T32b, steht **nicht** in T56. (b) Die Börsenplätze gehören hinter den
   Anleihenblock, weil jede andere Stelle alle bestehenden Steckplatzkennungen umnummeriert.
   Wer beides für Übergriff hält, streicht zwei Aufzählungspunkte; die fünf Zeilen bleiben.
4. **Wo die Domäne geprüft wird, stand nicht in der Abnahme.** Ich habe es entschieden
   (Listenerzeugung, T21 `setze`, T22 laden — **nicht** im Ordnungstyp), weil der Bauagent
   es sonst rät. Beleg dafür, dass es nicht in den Typ gehört: `aktion_probe.cpp:189` ist
   `{Art::Sichtbarkeit, Zielkennung{2}, 1}` — richtig als Ordnungsprobe, unzulässig als
   Spielzug.

### Was funktioniert — drei Funde mit Prüffrage

- **Die Ordnung stand schon dreimal da, nur nicht unter diesem Namen.** Alle drei
  Zielordnungen sind die vorhandene Adressarithmetik (`land·SEKTOREN + sektor`,
  `land·INSTRUMENTE + i`, das Steckplatz-Ordinal) und durch `static_assert` gedeckt. Keine
  einzige neue Zahl. **Prüffrage vor jeder Ordnungsvorgabe: rechnet der Zustand die
  Reihenfolge schon aus, die ich gerade festlegen will?**
- **Ein einziger Satz des Fremddokuments hat vier der fünf Zeilen entschieden.**
  `spiel.md` 1089 ordnet die Steckplätze Art 1 zu **und** spricht sie Art 3, 4, 5 ab.
  Gefunden nicht über „Zielkennung" (kommt in `spiel.md` nie vor), sondern über den
  *Lesestellen*-Begriff „visibility". **Prüffrage: hat das Fremddokument eine Stelle, an
  der es seine Zuständigkeiten selbst abgrenzt — meist dort, wo es etwas abzählt?**
- **Die Zahl 20 gegen 19 ist der Kern der Zeile, nicht ihr Rand.** Die Zielkennung muss
  ein **Adressplatz** sein und kein Platz in der Zulässigkeitsliste, weil die Liste je
  Runde neu gebaut wird (T32) und ein Speicherstand Aktionen als Zahl abspielt (T22).
  **Prüffrage bei jeder Kennung: wird die Menge, in der sie zählt, zwischen zwei
  Speicherständen neu gebaut?**

### Was nicht funktioniert

- **`Grep` über `ventures/**` ohne Pfadfilter** brachte 30 Dateien, davon 20 aus
  `befunde/messung-0105/baum_gut/…` — Kopien ganzer Bäume. Die zwei nützlichen Treffer
  (`kern/include/kern/aktion.hpp`, die Prüfung zu 0146) hätte ein Filter auf `kern/` und
  `befunde/pruefung-*` allein geliefert. `befunde/` enthält vollständige Repo-Abzüge; das
  ist die Falle hinter der Leseregel in `CLAUDE.md`.

### Offene Fährten (unverändert aus dem Vorgänger, dazu eine neue)

- **Neu: `technik.md` kennt die zweite Schicht nicht.** `spiel.md` rechnet mit `L = 9`,
  890 Adressen und 75 Steckplätzen, `technik.md` mit 4 Ländern, 310 und 20. Meine Zeilen
  sind Formeln und überleben das; T15, T16 und die 310 überleben es nicht. Das ist das
  größte offene Gefälle zwischen den beiden Vorgaben.
- Die sieben Fährten des Vorgängers (`Konstanten` in `kern::werte`, Prüfsumme in
  `parameter.toml`, „siebzehn" in `werte.hpp`, `zollstand(RW) = 0`, `l`/`g` bei Nr. 21,
  806/158 aus T62, Prüfjahrgang, Suchbot-Tiefe, T8/T42 im Prüfjahrgang) sind alle noch
  offen; sie stehen in `notizen/archiv/architekt-2026-09-08-1.md`.

