---
id: 0013-pruefsumme-fnv1a-64
rolle: kernbauer
status: gebaut
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/pruefsumme.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/pruefsumme.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/pruefsumme_probe.cpp]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# `kern::pruefsumme` — FNV-1a-64 und die Bytes, über die sie läuft

Vorgaben: `technik.md` T12, dazu T2, T4, T9. ADR 0011 für die Sprache.

T12 in einem Satz: *„`Zustand` wird über eine ausdrücklich geschriebene Funktion in Bytes
gefasst (feste Feldreihenfolge, `i64` in Little-Endian), **nie über die
Speicheranordnung der Struktur**. Darüber läuft FNV-1a-64. Diese Prüfsumme ist die
Währung aller Regressionstests."*

## Der Schnitt gegen 0008, und warum er hier liegt

Zwei Dinge stecken in T12, und nur eines davon braucht den `Zustand`:

- **Die Summe und die Byte-Bausteine** — FNV-1a-64 über eine Bytefolge, und die
  Umwandlung eines `int64_t` in acht Bytes in Little-Endian. Beides hängt an keinem
  Datentyp des Modells. **Das ist dieses Paket.**
- **Die feste Feldreihenfolge über die 310 Felder** — die hängt am `Zustand` und gehört
  Paket 0008, das sie als Bytefolge liefert und deine Funktion darüber laufen lässt.

Der Schnitt ist eine Paketentscheidung des Projektmanagers, keine Entwurfsentscheidung:
T12 verlangt beides, sagt aber nicht, in welcher Reihenfolge es entsteht. Er kostet
nichts und lässt dieses Modul laufen, während 0008 noch nicht steht.

## Was du baust

1. **FNV-1a-64**, selbst geschrieben (T2), mit den beiden Konstanten des Verfahrens —
   Startwert `14695981039346656037`, Faktor `1099511628211`. **Die Konstanten stehen mit
   Quelle in der Datei**, nicht nur als Zahl.
2. **Die Byte-Bausteine.** Ein `int64_t` wird über Schieben und Maskieren in acht Bytes
   zerlegt, Little-Endian, **auf jeder Maschine gleich**. Kein `memcpy` über die
   Struktur, kein `reinterpret_cast`, kein `union` — jeder dieser drei Wege liest die
   Speicheranordnung und ist genau das, was T12 verbietet.
3. **Der Kopf sagt, wofür die Summe gilt.** Sie ist die Währung der Regressionstests
   (T12) und die Zahl, die in jedem Speicherstand steht (T22). Wer das Verfahren
   wechselt, macht jeden gespeicherten Stand ungültig und braucht einen ADR — der Satz
   gehört in die Datei, weil ihn sonst niemand findet, bevor es zu spät ist.

**Was du nicht baust:** die Feldreihenfolge des `Zustand`. Sie gehört 0008. Existiert
`zustand.hpp` schon, bindest du sie trotzdem nicht ein — dieses Modul kennt Bytes, nicht
das Modell.

## Abnahme

1. **Veröffentlichte Testvektoren, mit Quelle.** Die Probe enthält mindestens drei
   FNV-1a-64-Vektoren aus einer unabhängigen Veröffentlichung, mit URL und Abrufdatum in
   der Datei; die leere Eingabe (`14695981039346656037`) ist einer davon. **Ein selbst
   erzeugter Erwartungswert ist kein Nachweis.** Der Prüfer ruft die Quelle auf und
   vergleicht Zeichen für Zeichen.
2. **Die beiden Verfahrenskonstanten stehen im Klartext in der Datei**, jede mit dem
   Satz, woher sie stammt.
3. **Little-Endian ohne Speicherzugriff:**
   `grep -nE 'memcpy|reinterpret_cast|union|bit_cast' kern/src/pruefsumme.cpp kern/include/kern/pruefsumme.hpp`
   liefert **nichts**. Die Zerlegung steht als Schiebefolge da, und eine Probe belegt sie
   mit einem ausgeschriebenen Wert — etwa `1` → `01 00 00 00 00 00 00 00` und `-1` →
   acht mal `FF`.
4. **Die Summe hängt an der Reihenfolge.** Eine Probe zeigt mit ausgeschriebenen Werten,
   dass zwei Bytefolgen mit denselben Bytes in anderer Reihenfolge verschiedene Summen
   liefern. Ohne diese Bedingung wäre eine Summe, die versehentlich über eine Menge
   statt über eine Folge läuft, nicht zu bemerken — und genau das ist der Fehler, den T9
   für den ganzen Kern ausschliesst.
5. **Kein Gleitkomma, keine Fremdabhängigkeit** (T4, T2).

## Was ausdrücklich kein Befund ist

Ob die Summe als ein Aufruf über eine Bytefolge oder als Kette aus „anfangen, füttern,
abschliessen" angeboten wird. Beides erfüllt T12; 0008 richtet sich nach dem, was hier
steht.

## Rückläufe

0.
