# Abschnitte der Vorgaben -- 0016-hedgefonds-simulation-echte-weltwirtschaft

Erzeugt von `agents/inhalt.py`. **Nicht von Hand aendern**, jeder Tageslauf
ueberschreibt die Datei.

## Wozu das hier da ist

Lies **nie** eine Vorgabe ganz. Der Kontext eines Laufs wird in jedem Zug
erneut gesendet -- am 2026-09-07 gemessen: im Schnitt 39 Mal. Wer `technik.md`
ganz liest, traegt rund 73.000 Token durch jeden folgenden Zug.

**Die Ueberschrift ist der Anker, nicht die Zeilennummer.** Der Uebersetzer
schreibt `technik.md` laufend um und verschiebt dabei jede Zeile darunter.
Die Spannen hier sind Minuten alt; sie sagen dir, wie **gross** ein Abschnitt
ist, nicht mehr verlaesslich, wo er steht. So greifst du sicher zu:

```
Grep(pattern="^## <Ueberschrift>", path=<datei>, output_mode="content", -n=true)
Read(datei, offset=<gefundene Zeile>, limit=<Zeilen laut Tabelle>)
```

Steht die erwartete Ueberschrift nicht in der ersten gelesenen Zeile, ist die
Datei unter dir verrutscht -- dann `Grep` erneut, statt weiterzulesen.

Brauchst du nur eine Stelle, ist `Grep` mit `-n` billiger als jedes Lesen.

## daten.md -- 27.010 Zeichen, 5 Abschnitte

| Abschnitt | Zeilen | Zeichen |
|---|---|---|
| The blocking question | 13-36 | 1.507 |
| Sources one by one | 37-321 | 16.643 |
| The proposal | 322-365 | 2.683 |
| What the model needs and what is missing | 366-423 | 3.621 |
| What is unclear | 424-451 | 2.013 |

## spiel.md -- 271.100 Zeichen, 15 Abschnitte

| Abschnitt | Zeilen | Zeichen |
|---|---|---|
| The game length R, and why it stands here as a letter | 109-275 | 11.440 |
| The loop | 276-398 | 6.593 |
| The actions | 399-430 | 2.152 |
| The state | 431-1235 | 54.396 |
| Die drei Schichten der Welt | 1236-1618 | 25.616 |
| Die Gegenkraefte | 1619-2474 | 54.099 |
| Wie die vier Masse berechnet werden | 2475-2853 | 24.158 |
| Was bewusst fehlt | 2854-3074 | 17.181 |
| Offene Entwurfsfragen | 3075-3277 | 16.325 |
| Was der Architekt neu rechnen muss | 3278-3561 | 28.057 |
| Befundabarbeitung — Prüfung 0039 vom 2026-09-03, Paket 0055 | 3562-3604 | 2.825 |
| Befundabarbeitung — Prüfung 0021 vom 2026-09-02, Paket 0039 | 3605-3648 | 3.112 |
| Befundabarbeitung — Prüfung der Runde 6 vom 2026-09-01 | 3649-3721 | 4.968 |
| Befundabarbeitung — Prüfung der Runde 4 vom 2026-09-01 | 3722-3777 | 3.841 |
| Befundabarbeitung — Prüfung der zweiten Fassung vom 2026-08-31 | 3778-3863 | 5.913 |

## technik.md -- 286.199 Zeichen, 21 Abschnitte

| Abschnitt | Zeilen | Zeichen |
|---|---|---|
| 1. Stack | 89-246 | 11.512 |
| 2. Der deterministische Kern | 247-1033 | 54.449 |
| 3. Trennung von Modell und Darstellung | 1034-1104 | 4.267 |
| 4. Datenmodell | 1105-1390 | 17.861 |
| 5. Die drei Zustandsebenen (G8) | 1391-1407 | 1.030 |
| 6. Maschinenschnittstelle und Partieformat | 1408-1449 | 2.838 |
| 7. Datenschicht | 1450-1846 | 28.842 |
| 8. Markträumung und die beiden Renditen | 1847-2233 | 25.490 |
| 9. Test- und Prüfstandsaufbau | 2234-2625 | 27.263 |
| 10. Was das Modell an Rechenzeit kostet | 2626-2745 | 7.795 |
| 11. Auslieferung, und wo Geld anfängt | 2746-2763 | 1.109 |
| 12. Was ich nicht entschieden habe | 2764-2857 | 7.470 |
| 13. Hinweis für den Projektmanager | 2858-2882 | 1.630 |
| 14. Befundabarbeitung — die vier früheren Prüfungen | 2883-2901 | 1.180 |
| 15. Befundabarbeitung — Prüfung der Runde 6 vom 2026-09-01 und `spiel.md` Fassung 5 | 2902-3004 | 8.333 |
| 16. Befundabarbeitung — Prüfung zu Paket `0011-stack-auf-cpp`, Runde 1 vom 2026-09-03 | 3005-3064 | 4.395 |
| 17. Paket `0026-klasse-2-preisbasis` — Umfang, und was ausdrücklich liegen bleibt | 3065-3191 | 9.163 |
| 18. Paket `0043-t48-groessen-gegenkraft-5` — Umfang und die Meldung an den Projektmanager | 3192-3273 | 6.142 |
| 19. Die Länderzahl als Parameter — Paket `0116` | 3274-3475 | 13.651 |
| 20. Zwei Länderklassen und der geschätzte Politikpfad — Paket `0117` | 3476-3838 | 26.183 |
| 21. Was ein fünftes Land an Daten mitbringt — Paket `0141` | 3839-4066 | 16.639 |

## zielbild.md -- 5.320 Zeichen, 5 Abschnitte

| Abschnitt | Zeilen | Zeichen |
|---|---|---|
| The directive verbatim | 15-24 | 598 |
| Two views | 25-32 | 267 |
| Why this fits the rest — and is not decoration | 33-52 | 910 |
| What it costs — the one place where it collides | 53-97 | 2.468 |
| The order stands | 98-110 | 643 |

