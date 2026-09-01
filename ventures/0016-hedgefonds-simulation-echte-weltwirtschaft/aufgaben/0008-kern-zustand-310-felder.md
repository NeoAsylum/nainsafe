---
id: 0008-kern-zustand-310-felder
rolle: kernbauer
status: offen
haengt_an: [0004-werkstattgeruest-festkomma, 0007-adressverzeichnis-310]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/zustand.rs]
abnahme: Die Struktur trägt genau 310 i64 ohne Vec, String, HashMap oder Option; jede Adresse aus daten/adressen.md ist über eine Adressfunktion erreichbar und umgekehrt; ein Test rechnet die Feldzahl aus der Typgröße nach und nennt 2480 Byte.
---

# `kern::zustand` — die 310 Adressen als Wert fester Größe

Vorgaben: `technik.md` T15, T16, T17, T9, T12. Eingabe ist das Verzeichnis aus Paket
0007 (`daten/adressen.md`) — **bau gegen das Verzeichnis, nicht gegen die Prosa von
T15.** Weicht das Verzeichnis von T15 ab, ist das ein Befund und keine Gelegenheit, es
still zu glätten.

Vorher lesen: `rueckstand.md`, Abschnitt *Es gibt keinen Übersetzer*.

## Was du baust

1. **`Zustand`** als Wert fester Größe: feste Felder, feste Arrays, **kein `Vec`, kein
   `String`, kein `HashMap`, kein `Option<Box<…>>`** (T15). 310 `i64`, 2.480 Byte.
   `Clone` ist ein Speicherumzug und keine Zuteilung — der Prüfstand startet Millionen
   Nachspiele aus Zwischenständen, und daran hängt es.
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
5. **Kanonische Byteform und Prüfsumme** (T12), falls sie ohne das Modul `pruefsumme`
   auskommt; sonst nur die Byteform, und die Prüfsumme bleibt dem eigenen Paket. Sag in
   der Datei, welchen der beiden Wege du gegangen bist.

## Abnahme

1. **310 `i64`**, nachgezählt. Ein Test rechnet die Feldzahl aus `size_of::<Zustand>()`
   nach und nennt `2_480` als Erwartungswert.
2. `grep -n 'Vec<\|String\|HashMap\|BTreeMap\|Option<' kern/src/zustand.rs` liefert
   nichts (T15).
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
