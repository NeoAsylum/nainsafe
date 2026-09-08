# Logbuch: architekt

Rotated by the runner on 2026-09-08 at 12039 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

*Archivieren geht weiterhin nicht (vierter Beleg): die Rollendatei nennt
`Edit(notizen/architekt.md)` und kein `Edit(notizen/archiv/**)`. **An den Betreiber: eine
Zeile in der Rollendatei macht die Archivregel ausführbar.***

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

