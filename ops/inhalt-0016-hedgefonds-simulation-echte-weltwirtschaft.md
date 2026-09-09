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

## daten.md -- 27.025 Zeichen, 5 Abschnitte

| Abschnitt | Zeilen | Zeichen |
|---|---|---|
| The blocking question | 13-36 | 1.507 |
| Sources one by one | 37-321 | 16.643 |
| The proposal | 322-365 | 2.683 |
| What the model needs and what is missing | 366-423 | 3.621 |
| What is unclear | 424-451 | 2.013 |

## spiel.md -- 270.734 Zeichen, 15 Abschnitte

| Abschnitt | Zeilen | Zeichen |
|---|---|---|
| The game length R, and why it stands here as a letter | 110-276 | 11.455 |
| The loop | 277-399 | 6.591 |
| The actions | 400-431 | 2.153 |
| The state | 432-1251 | 53.797 |
| Die drei Schichten der Welt | 1252-1634 | 25.629 |
| Die Gegenkraefte | 1635-2495 | 54.474 |
| Wie die vier Masse berechnet werden | 2496-2874 | 24.158 |
| Was bewusst fehlt | 2875-3095 | 17.181 |
| Offene Entwurfsfragen | 3096-3298 | 16.325 |
| Was der Architekt neu rechnen muss | 3299-3582 | 28.062 |
| Befundabarbeitung — Prüfung 0039 vom 2026-09-03, Paket 0055 | 3583-3625 | 2.825 |
| Befundabarbeitung — Prüfung 0021 vom 2026-09-02, Paket 0039 | 3626-3669 | 3.112 |
| Befundabarbeitung — Prüfung der Runde 6 vom 2026-09-01 | 3670-3742 | 4.968 |
| Befundabarbeitung — Prüfung der Runde 4 vom 2026-09-01 | 3743-3798 | 3.841 |
| Befundabarbeitung — Prüfung der zweiten Fassung vom 2026-08-31 | 3799-3884 | 5.913 |

## technik.md -- 435.580 Zeichen, 35 Abschnitte

| Abschnitt | Zeilen | Zeichen |
|---|---|---|
| 1. Stack | 88-245 | 11.512 |
| 2. Der deterministische Kern | 246-1268 | 71.168 |
| 3. Trennung von Modell und Darstellung | 1269-1339 | 4.267 |
| 4. Datenmodell | 1340-1658 | 20.174 |
| 5. Die drei Zustandsebenen (G8) | 1659-1675 | 1.030 |
| 6. Maschinenschnittstelle und Partieformat | 1676-1748 | 5.184 |
| 7. Datenschicht | 1749-2185 | 32.188 |
| 8. Markträumung und die beiden Renditen | 2186-2609 | 28.045 |
| 9. Test- und Prüfstandsaufbau | 2610-3111 | 36.831 |
| 10. Was das Modell an Rechenzeit kostet | 3112-3235 | 8.118 |
| 11. Auslieferung, und wo Geld anfängt | 3236-3253 | 1.109 |
| 12. Was ich nicht entschieden habe | 3254-3351 | 7.529 |
| 13. Hinweis für den Projektmanager | 3352-3389 | 2.351 |
| 14. Befundabarbeitung — die vier früheren Prüfungen | 3390-3408 | 1.151 |
| 15. Befundabarbeitung — Prüfung der Runde 6 vom 2026-09-01 und `spiel.md` Fassung 5 | 3409-3511 | 8.206 |
| 16. Befundabarbeitung — Prüfung zu Paket `0011-stack-auf-cpp`, Runde 1 vom 2026-09-03 | 3512-3571 | 4.350 |
| 17. Paket `0026-klasse-2-preisbasis` — Umfang, und was ausdrücklich liegen bleibt | 3572-3731 | 11.165 |
| 18. Paket `0043-t48-groessen-gegenkraft-5` — Umfang und die Meldung an den Projektmanager | 3732-3840 | 7.928 |
| 19. Die Länderzahl als Parameter — Paket `0116` | 3841-4077 | 15.976 |
| 20. Zwei Länderklassen und der geschätzte Politikpfad — Paket `0117` | 4078-4554 | 33.870 |
| 21. Was ein fünftes Land an Daten mitbringt — Paket `0141` | 4555-4783 | 16.336 |
| 22. Der Schadenseingang — Paket `0165` | 4784-4946 | 10.574 |
| 23. Die Untergrenze des Zollfaktors — Paket `0172` | 4947-5065 | 8.261 |
| 24. Die Zielkennung je Aktionsart — Paket `0148` | 5066-5209 | 9.345 |
| 25. Where the value range of an address is checked — Paket `0177` | 5210-5344 | 8.671 |
| 26. One reading of the country count — Paket `0221` | 5345-5431 | 5.334 |
| 27. The class is formed from two sorts of series — Paket `0196` | 5432-5486 | 3.907 |
| 28. Check 6 names its mode — Paket `0158` | 5487-5532 | 3.137 |
| 29. Der R-Nachzug ausserhalb der T-Blöcke — Paket `0064` | 5533-5623 | 7.727 |
| 30. Reihe 9 ohne Sollrolle — Paket `0068` | 5624-5702 | 5.095 |
| 31. Wodurch Massnahme 4.3 durchgesetzt wird — Paket `0074` | 5703-5753 | 3.206 |
| 32. Reihe 20 in der Reihenliste, und was die Selbstmessung zu T53 wirklich deckte — Paket `0084` | 5754-5860 | 6.908 |
| 33. Die zwei Zeilen, die der Regelsatz nicht erreichte — Paket `0268` | 5861-5967 | 6.998 |
| 34. Der Weg eines Pfadwerts in die Runde — Paket `0277` | 5968-6156 | 11.483 |
| 35. Zwei Zeilen, die keine der fünf Regeln erreichte — Paket `0274` | 6157-6271 | 7.506 |

## zielbild.md -- 5.320 Zeichen, 5 Abschnitte

| Abschnitt | Zeilen | Zeichen |
|---|---|---|
| The directive verbatim | 15-24 | 598 |
| Two views | 25-32 | 267 |
| Why this fits the rest — and is not decoration | 33-52 | 910 |
| What it costs — the one place where it collides | 53-97 | 2.468 |
| The order stands | 98-110 | 643 |

