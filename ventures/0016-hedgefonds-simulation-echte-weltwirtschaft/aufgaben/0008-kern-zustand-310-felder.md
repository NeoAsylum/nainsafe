---
id: 0008-kern-zustand-310-felder
rolle: kernbauer
status: offen
haengt_an: [0007-adressverzeichnis-310]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/zustand.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/zustand_probe.cpp]
abnahme: Die Struktur trägt genau 310 int64_t ohne std::vector, std::string, std::unordered_map oder std::optional; jede Adresse aus daten/adressen.md ist über eine Adressfunktion erreichbar und umgekehrt; ein static_assert rechnet die Feldzahl aus sizeof(Zustand) nach und nennt 2480 Byte.
---

# `kern::zustand` — die 310 Adressen als Wert fester Größe

Vorgaben: `technik.md` T15, T16, T17, T9, T12. Eingabe ist das Verzeichnis aus Paket
0007 (`daten/adressen.md`) — **bau gegen das Verzeichnis, nicht gegen die Prosa von
T15.** Weicht das Verzeichnis von T15 ab, ist das ein Befund und keine Gelegenheit, es
still zu glätten.

## Zwei Änderungen am 2026-09-02, beide vom Projektmanager

**Erstens: C++20 statt Rust** (ADR 0011 vom 2026-09-01). Die Vorgaben sind dieselben,
die Namen nicht: `int64_t` statt `i64`, `sizeof` statt `size_of::<…>()`,
`std::vector`/`std::string`/`std::unordered_map`/`std::optional` statt
`Vec`/`String`/`HashMap`/`Option`, drei Dateien statt einer (Kopf, Quelle, Probe). Dass
`technik.md` an zehn Stellen weiter Rust sagt, ist bekannt und gehört Paket 0011; für
den Bau gilt der ADR.

**Zweitens: `haengt_an` ist von 0004 befreit.** Das Gerüst existiert und übersetzt —
`befunde/uebersetzung-2026-09-02.md` zeigt `cmake`, `cmake --build` und `ctest` grün, und
`kern/CMakeLists.txt` sammelt Quellen und Proben über `file(GLOB … CONFIGURE_DEPENDS)`
ein. Du legst also drei Dateien dazu und fasst keine gemeinsame an. 0004 steht auf
`gebaut` und wartet nur auf den Kern-Prüfer; sein Rücklauf träfe `festkomma`, die
Werkzeugkette oder den Sammelkopf — nichts davon braucht dieses Paket. **Was du
trotzdem nicht tust:** eine Platzhalterdatei ausserhalb deiner drei anfassen. Kommt 0004
zurück, sperrt die Kollisionsprüfung die beiden Pakete ohnehin gegeneinander.

## Was du baust

1. **`Zustand`** als Wert fester Größe: feste Felder, feste `std::array`, **kein
   `std::vector`, kein `std::string`, kein `std::unordered_map`, kein `std::optional`,
   keine eigene Speicherverwaltung** (T15, T9). 310 `int64_t`, 2.480 Byte. Kopieren ist
   ein Speicherumzug und keine Zuteilung — der Prüfstand startet Millionen Nachspiele
   aus Zwischenständen, und daran hängt es.
2. **Die feste Reihenfolge** für Länder, Sektoren, Instrumente und Steckplätze (T9) als
   benannte Aufzählungen mit fester Nummerierung. Keine streuende Menge, nirgends.
3. **Die zwanzig Steckplätze** als Plätze, nicht als Liste (T16): eine Position ist eine
   vorzeichenbehaftete Stufenzahl auf einem festen Platz, null heisst „keine". Der Platz
   *Währung USA* bleibt dauerhaft leer — er existiert für die gleichförmige Adressierung
   und wird von der Zulässigkeitsprüfung nie angeboten. Spielbar sind 19 von 20.
4. **Die Adressabbildung** (T17): In beide Richtungen, und beide Richtungen sind
   vollständig. Adresse als Zeichenkette nach T17 ⟷ Feld. Sie wird von Protokoll, Kette,
   Testvorlagen und Oberfläche benutzt; wer eine Adresse umbenennt, macht den
   Regressionsbestand ungültig und braucht einen ADR.
5. **Die kanonische Byteform** (T12): feste Feldreihenfolge, `int64_t` in
   Little-Endian, **nie über die Speicheranordnung der Struktur**. Die Prüfsumme selbst
   baut Paket 0013; du lieferst die Bytefolge, über die sie läuft. Steht 0013 schon,
   rufst du seine Funktion auf, statt eine zweite zu schreiben.

## Abnahme

1. **310 `int64_t`**, nachgezählt. Ein `static_assert` rechnet die Feldzahl aus
   `sizeof(Zustand)` nach und nennt `2480` als Erwartungswert. Der Übersetzungslauf
   macht daraus einen mechanischen Nachweis: Stimmt die Zahl nicht, ist der Bau rot.
2. `grep -nE 'std::vector|std::string|std::unordered_map|std::optional|new |delete ' kern/src/zustand.cpp kern/include/kern/zustand.hpp`
   liefert nichts (T15, T9).
3. **Jede der 310 Zeilen aus `daten/adressen.md` ist über die Adressabbildung
   erreichbar, und die Abbildung kennt keine Adresse, die dort nicht steht.** Der Prüfer
   prüft das über beide Richtungen stichprobenweise und über die Zählung vollständig.
4. Die Reihenfolgen aus T9 stehen als Aufzählung mit ausgeschriebenen Nummern da, nicht
   als Kommentar.
5. Kein Gleitkomma (T4), keine Fremdabhängigkeit (T2).

## Was ausdrücklich kein Befund ist

Wie die 310 auf Untertypen verteilt sind — ob ein `Land`-Untertyp die 44 Felder
zusammenfasst oder ob alles flach steht, ist Bauentscheidung, solange die Zählung, die
Adressabbildung und die feste Größe stimmen. `specs/` schweigt dazu, also ist die
Entscheidung des Bauagenten gültig.

## Rückläufe

0.
