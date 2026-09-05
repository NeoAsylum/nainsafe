---
id: 0155-werte-konstantenkopf-zwei-jahrgangskonstanten
rolle: kernbauer
status: offen
haengt_an: [0152-werte-zweiundzwanzig-statt-siebzehn]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/werte.hpp]
abnahme: Die zwei Bedingungen unter "Abnahme".
---

## ANGENOMMEN — 2026-09-06, Projektmanager: `vorschlag` → `offen`, drittes Glied auf `werte.hpp`

Vier Prüfungen. **Rolle** `kernbauer` steht in `BAUROLLEN`, Prüfer ist der `kern-pruefer`.
**Abnahme** prüfbar: zwei benannte Bedingungen über einen Satz, der in derselben Datei
steht wie das, was er zählt — `grep -n "Jahrgangskonstante"` an der eigenen Zieldatei
entscheidet sie. **Abhängigkeit** 0152, noch offen. **Dateien**: nur `werte.hpp`.

**`haengt_an: [0152]` ist beides** — Reihenfolgesperre auf `werte.hpp` und der Grund,
warum du nicht früher laufen kannst: 0152 ändert die Zahl der Größen im selben Träger,
und ein Kopf, der nach 0152 wieder falsch zählt, wäre zweimal dieselbe Arbeit. Die Reihe
auf `werte.hpp` lautet

> 0151 (fertig) → 0152 → **0155**.

**Die Nummer 0155 war doppelt vergeben.** Ein Parallellauf legte am 2026-09-06 unter
derselben Kennung `0155-verlaufgroesse-auch-absolut-beschraenkt.md` an. Dieses Paket
behält die Nummer, das andere ist nach `0156-verlaufgroesse-auch-absolut-beschraenkt.md`
umgezogen; die alte Datei trägt nur noch den Verweis und kein Frontmatter mehr.

**Zähl selbst nach, statt den Rumpf abzuschreiben.** Er ist am 2026-09-06 gemessen
(zwei Jahrgangskonstanten: `leitzins_start` und `durchgriff`). Ergibt deine Zählung nach
0152 eine andere Zahl, gilt deine Zählung, und die abweichende Zahl gehört als Befund in
deinen Bericht. Such am Text, nicht an der Zeilennummer.

# Der Kopf von `Konstanten` zaehlt eine Jahrgangskonstante; es sind zwei

**Vorgeschlagen am 2026-09-06 vom kern-pruefer**, aus der Pruefung zu `0151`
(`befunde/pruefung-0151-werte-die-drei-hubgroessen-2026-09-06.md`, Befund 2).

## Der Widerspruch, in einer Datei

`kern/include/kern/werte.hpp`:

```
Zeile  65:  /// Die Kalibrierwerte und die eine Jahrgangskonstante, die in den Formeln
Zeile  66:  /// aus T47 und T48 neben den Zustandsadressen vorkommen.
...
Zeile 111:      std::array<zustand::i64, zustand::LAENDER> leitzins_start{};
Zeile 116:      /// **Die zweite Jahrgangskonstante dieses Traegers**, aus demselben Grund
Zeile 130:          durchgriff{};
```

`grep -n "Jahrgangskonstante" kern/include/kern/werte.hpp` gibt beide Zeilen aus. Der
Kopf zaehlt eine, die Struktur traegt zwei -- `leitzins_start` (T23 Punkt 5, vier Werte)
und seit `0151` `durchgriff` (T23 Punkt 5, zehn Werte).

Der Satz war richtig, als `0002` ihn geschrieben hat
(`aufgaben/0002-fondsbewertung-definieren.md` Zeile 223, Status `fertig`). Er ist es seit
dem 2026-09-06 nicht mehr.

## Warum das ein eigenes Paket ist und nicht Teil von `0151` oder `0152`

**Nicht `0151`:** Dessen vier Abnahmebedingungen nennen den Satz nicht. Sie sind erfuellt,
das Paket ist geprueft, und eine Bedingung nachtraeglich hineinzulesen waere das Gegenteil
dessen, was der Pruefauftrag verlangt.

**Nicht `0152`:** Dieses Paket zieht ausdruecklich die Zahlwoerter „siebzehn" nach und
legt `regulierung_last` in `Konstanten` an. `regulierung_last` ist nach `technik.md`
Zeile 3243 ein **Parameterschluessel nach T27** und keine Jahrgangskonstante -- die Zahl
im Kopf bleibt danach also unveraendert falsch. Wer den Satz in `0152` mitnaehme, mischte
eine Berichtigung, die niemand angeordnet hat, in ein Paket mit fuenf eigenen Bedingungen;
wer ihn dort weglaesst, hinterlaesst ihn. Beides ist schlechter als eine eigene Zeile.

**`haengt_an: 0152`** ist keine fachliche Abhaengigkeit, sondern die Reihenfolgesperre:
`0152` faellt dieselbe Datei an, und zwei Laeufe auf `werte.hpp` gleichzeitig kollidieren.

## Der Auftrag

Zeile 65--66 so umschreiben, dass sie die Struktur beschreibt, die darunter steht:
Kalibrierwerte **und zwei Jahrgangskonstanten** (`leitzins_start`, `durchgriff`), beide
nach T23 Punkt 5. Der Kommentar an `durchgriff` (Zeile 113--128) sagt schon, warum es
zwei sind und warum sie nicht in `parameter.toml` stehen; der Kopf soll es nicht
wiederholen, sondern nur nicht mehr widersprechen.

**Was ausdruecklich nicht dazugehoert:** die Zahl der Felder insgesamt, die Zahlwoerter
aus T48 (`0152`) und jede Aenderung an der Struktur selbst. Das ist ein Kommentar und
sonst nichts.

## Abnahme

1. **`grep -n "Jahrgangskonstante" kern/include/kern/werte.hpp` liefert keine Stelle mehr,
   die eine andere Zahl nennt als die gezaehlte.** Nachgewiesen durch die Gegenprobe:
   Die Zahl im Kopf und die Zahl der Felder, deren Kommentar sie als Groesse des Jahrgangs
   ausweist, stimmen ueberein -- heute zwei. Steht am Ende eine andere Zahl, folgt der
   Kopf der Zaehlung und nicht diesem Paket.
2. **Der Bestand bleibt gruen und die Struktur unberuehrt.** `ctest` in beiden
   Bauprofilen (`FABRIK_SANITIZER=ON` und `OFF`), Belegstellen-, Bezeichner- und
   Sperrebindungsriegel mit Code 0. `git diff` zeigt ausschliesslich Kommentarzeilen in
   `werte.hpp`, keine Deklaration und kein Feld; ausserhalb dieser einen Datei null
   geaenderte Zeilen.
