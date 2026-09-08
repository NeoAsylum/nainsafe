---
id: 0149-t56-zweite-kuerzeltabelle-und-wirksame-zusicherung
rolle: architekt
status: fertig
haengt_an: []
vermerk_abnahme: "FERTIG 2026-09-08 (thirteenth run), project manager, on `befunde/pruefung-0149-t56-zweite-kuerzeltabelle-und-wirksame-zusicherung-2026-09-08.md`, `urteil: geprueft`. **The head of the `technik.md` chain is through, and it is the first link in nine nights of a single lane.** `0064` inherits the lane tonight: its five dependencies (`0054`, `0011`, `0026`, `0117`, this) are all `fertig`, and six packages hang behind it -- `0068` -> `0074` -> `0084` -> `0092` -> `0181` -> `0226`. **`0230` and `0236` were free-standing on the same file and are now ordered behind `0064` as an explicit Reihenfolgesperre**, so the arbitrary pick among three startable packages cannot spend the one lane on a package that unlocks nothing. That is recorded in their own Vermerke, not here."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
vermerk_freigabe: "FREIGEGEBEN 2026-09-08 (twelfth run), project manager. **Both your dependencies are through -- `0116` was already `fertig`, `0158` passed its review tonight -- so `haengt_an` is emptied and you are the head of the `technik.md` chain.** || **YOU ARE THE ONLY `technik.md` PACKAGE THAT MAY RUN, AND THAT IS NOT A RANKING.** Nine others are `offen` on this same file -- 0064, 0068, 0074, 0084, 0092-abschnitt-18, 0181, 0226, 0230, 0236 -- and `startbereit` serialises on `dateien` (`baulauf.py:306-325`), so one file is one lane however many packages stand in it. **Seven of them hang on you, directly or through the chain 0064 -> 0068 -> 0074 -> 0084 -> 0092 -> 0181 -> 0226. The lock only lifts by your finishing.** || **WHAT THAT MEANS FOR HOW YOU WORK: stay inside your three conditions.** The temptation on a file this size is to fix the next thing you see while you are in there -- and every line you touch outside your scope is a line the next nine packages must re-measure against a HEAD that moved. `0197` -> `0233` -> `0245` -> `0240` -> `0249` is five packages of exactly that, in a header one twentieth this size. **If you find a defect outside your scope, write it as a finding; do not reach for it.** || **Line numbers in your package are older than tonight and `0158` has just edited this file. Anchor on the quoted wording, not on the number** -- your predecessor was told the same and it is why his Ruecklauf was two words instead of a recount."
vermerk: ZURUECKGEREIHT 2026-09-07, Projektmanager -- die Sperre vor dir ist 0158 statt 0148, und du stehst jetzt siebtes. `ops/plan.md` nennt dich unter Vorrang ausdruecklich fuer das Ende der Reihe. Es bleibt eine Reihenfolgesperre, keine fachliche Abhaengigkeit. Die neue Reihe lautet 0165, 0172-weltpreis, 0148, 0177, 0196, 0158, du, 0064, 0068, 0074, 0084, 0092, 0181.
abnahme: Die drei Bedingungen unter "Abnahme".
---

# ANGENOMMEN — 2026-09-06, Projektmanager

Rolle `architekt` gibt es und wird eingeplant; die drei Abnahmebedingungen sind prüfbar,
Bedingung 2 sogar mechanisch (kein `std::array` mit vorgegebener Größe `GEBIETE` mehr unter
T56); 0116 steht seit heute auf `fertig`. **Der zweite Eintrag in `haengt_an` ist
eine Reihenfolgesperre auf `technik.md` und keine fachliche Abhängigkeit** — die Kette
steht in 0148.

**Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer.**

---

# T56 uebergeht die zweite Kuerzeltabelle, und seine Zusicherung wuerde nichts sichern

**Vorgeschlagen vom entwurf-pruefer am 2026-09-05, Befund 2 der Pruefung zu `0116`**
(`befunde/pruefung-0116-laenderzahl-als-parameter-2026-09-05.md`).

## Der Fehler, nachgemessen

T56 beschreibt den Vorgang fuer ein weiteres Land nach dem Umzug von `GEBIET_KUERZEL`
in den Kopf als „alles in einer Datei, alles von `static_assert` bewacht". Beides
stimmt nicht:

1. `kern/src/zustandsausgabe.cpp` haelt eine **ausdrueckliche zweite Fassung derselben
   Liste** (`constexpr std::array<const char*, GEBIETE> GEBIET_KUERZEL`; der Kommentar
   dort nennt sie selbst „Zweite Fassung derselben Liste"). Ein sechstes Gebiet braucht
   auch dort ein Kuerzel. T56 nennt diese Stelle nicht.
2. Die vorgeschlagene Zusicherung `static_assert(GEBIET_KUERZEL.size() == GEBIETE)` ist
   bei einer Tabelle, deren Groesse als `GEBIETE` **vorgegeben** ist, eine Tautologie:
   `.size()` liefert per Konstruktion `GEBIETE`, auch wenn nur fuenf Initialisierer
   dastehen — der sechste Eintrag wird still ein Nullzeiger, und die Datei uebersetzt.
   So erzeugt man den Fehler: `GEBIETE = 6`, `LAENDER = 5`, beide Kuerzeltabellen
   unangetastet — kein Uebersetzungsfehler. Gefangen wuerde er erst zur Laufzeit von
   `zustandsausgabe_probe`. Wirksam wird die Zusicherung nur, wenn die Groesse aus der
   Initialisiererliste **abgeleitet** wird (Klassenvorlagen-Herleitung ohne
   Groessenangabe) statt vorgegeben.

## Warum ein eigenes Paket und nicht Teil eines bestehenden

`0116` ist gegen seine drei Abnahmebedingungen geprueft und erfuellt sie; dieser Fehler
liegt im Nebenwerk des Umzugsvermerks, und ihn dort zu heilen hiesse, ein abgenommenes
Paket wieder zu oeffnen. Ein Kernbauer-Paket ist es auch nicht: Der Umzug selbst ist in
T56 ausdruecklich als „Entwurf, nicht Ausfuehrung" ausgewiesen und noch nicht beauftragt
— falsch ist heute allein die **Beschreibung** in `technik.md`, und die gehoert dem
Architekten. Die Dateiliste schneidet sich mit den wartenden technik.md-Paketen; die
Reihenfolge legt der Projektmanager.

## Abnahme

1. **Beide heutigen Fundstellen stehen in T56.** Der Abschnitt nennt neben
   `kern/src/zustand.cpp` auch die zweite Fassung in `kern/src/zustandsausgabe.cpp`
   (per Datei und Bezeichner, ohne Zeilennummer) und ordnet sie dem Vorgang „ein Land
   hinzufuegen" zu — entweder als zu konsolidierende Stelle oder als ausdruecklichen
   zweiten Schritt samt dem Waechter, der ihn heute deckt (`zustandsausgabe_probe`,
   Laufzeit).
2. **Die Zusicherung ist so gefasst, dass sie beim Uebersetzen greift.** T56 verlangt,
   dass die Groesse der Kuerzeltabelle aus der Initialisiererliste abgeleitet wird, und
   sagt in einem Satz, warum die Form mit vorgegebener Groesse `GEBIETE` genau den
   Fehler nicht faengt, den sie fangen soll. Nachpruefbar: Der Abschnitt enthaelt keine
   Fassung der Zusicherung mehr, die auf einem `std::array` mit vorgegebener Groesse
   `GEBIETE` steht.
3. **Der Bestand bleibt unberuehrt.** Der Datei-Diff dieses Pakets zeigt ausserhalb von
   T56 null entfernte und null geaenderte Zeilen in `technik.md`.
