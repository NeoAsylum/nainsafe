---
typ: pruefung
paket: 0107-kennzeichen-gegen-nachbarmeldungen
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Beide Sabotagen der Abnahme selbst gefahren (Abschwaechung rot mit Stelle und fremder Meldung im Wortlaut, Auslieferstand gruen, fuenf Listen zeichengleich zu 564d4b8), dazu drei eigene Mutanten, alle rot.
befunde: 0
---

# Pruefung 0107 -- die Eindeutigkeit der Kennzeichen als laufende Zusicherung

Unabhaengig gemessen: eigene Mutanten, eigener Bau mit der Kommandozeile des Runners
(Schalter aus `bau/kern/CMakeFiles/schritt_probe.dir/flags.make` und `link.txt`,
gelinkt gegen `libkern_geprueft.a`). Den Nachweis des Bauagenten
(`befunde/messung-0107/nachweis.md`) habe ich **nicht gelesen**; sein Bericht in der
Aufgabendatei war beim Lesen des Abnahmekriteriums unvermeidbar, die Messung unten ist
davon unabhaengig aufgebaut.

## Die beiden Sabotagen der Abnahme

**Sabotage 1, die Abschwaechung (Mutant m1).** `spielmodus`-Liste auf
`{"kern::schritt"}` verkuerzt -- als Textersetzung an einer Kopie, das Repo blieb
unberuehrt, an der Quelle (`kern/src/`) nichts geaendert. Ergebnis: Exit 1 mit vier
Verletzungen, jede rote Zeile nennt die Stelle (`Zeile 767: Modus spielmodus`) und die
fremde Meldung im Wortlaut (obere Rundenschranke und Runde vor der ersten, je zweimal).
Die 0085-Pruefung der Stelle selbst blieb dabei gruen ("Abbruch wie erwartet") -- das
Rot kommt allein aus der neuen Zusicherung. **Erfuellt.**

**Sabotage 2, die Gegenprobe.** Am unveraenderten Auslieferstand (HEAD, `f7d9822`)
laeuft `ctest -R schritt_probe` gruen: `7 Meldungen aus 5 Riegeln, 38 fremde und 4
eigene Paare geprueft, 0 Verletzung(en)`. Die fuenf Kennzeichenlisten sind gegenueber
dem Bezugsstand `564d4b8` **zeichengleich** (git-Diff der Datei: kein Literal
geaendert, nur das neue `Riegel`-Argument dazwischengeschoben). **Erfuellt.**

**Die Doppelstellen-Bedingung** ("Zeile 485 und der dritte Fall in `probe_rundennummer`
gelten als eine") ist im Lauf bestaetigt, nicht nur im Quelltext: 7 Meldungen ergeben
42 geordnete Paare; genau 4 davon sind eigene (2x obere Rundenschranke mit
zeichengleichen Meldungen, 2x negative Rundennummer mit Zahlvariation), 38 fremde,
0 Verletzungen -- kein falscher Fund am ersten Tag.

## Eigene Mutanten ueber die Abnahme hinaus

| Mutant | Eingriff | Ergebnis |
|---|---|---|
| M0 | Kontrolle ohne Eingriff, eigener Bau | gruen, Ausgabe zeilengleich zum ctest-Lauf im Baubaum |
| m2 | m1 plus Riegel der Stelle zu `RundeVorDerErsten` erklaert (der Aneignungs-Ausweg) | rot, dreifach: Vollzaehligkeit ("keine Meldung zum Riegel Spielmodus"), Fremdkollision der Restliste, und die Listen der echten Stellen passen nicht auf die angeeignete Meldung |
| m3 | Liste des Falls -1 zu eng gefasst (`"ist -1 und damit negativ"`) | rot mit genau einer Verletzung -- Haelfte 2 isoliert nachgewiesen, alle sieben Abbruchstellen selbst gruen |
| m4 | `probe_spielmodus_bricht_ab` samt Aufruf entfernt | rot mit genau einem Fehlschlag: die Vollzaehligkeitspruefung |

Nebenbefund ohne Gewicht: m4 in der Erstform (nur die Aufrufzeile entfernt) stirbt
schon beim Uebersetzen an `-Werror=unused-function` -- die Werkzeugkette faengt diese
Sabotageform selbst, gezaehlt habe ich sie nicht als Empfindlichkeit.

## Zur zweiten Haelfte, nach der der Bauagent gefragt hat

Der Bauagent nennt die Gegenrichtung ("jede Liste passt auf jede Meldung ihres eigenen
Riegels") die einzige Stelle ueber dem Wortlaut der Abnahme. Sie ist keine
Ueberdehnung: Die Abnahme verlangt selbst, dass zwei Stellen desselben Riegels **als
eine gelten** -- und "als eine gelten" ist genau dann eine Messung statt einer
Behauptung, wenn ihre Listen wechselseitig auf die Meldungen des Riegels passen. m2
und m3 zeigen ihren eigenstaendigen Fangwert.

## Was offen bleibt (kein Befund gegen dieses Paket)

- Die Riegelkennung ist ein Handargument der Aufrufstelle (Unsicherheit 1 des
  Bauagenten). m2 belegt, dass der einfache Aneignungsweg dreifach rot wird; der
  verbleibende Weg braeuchte zwei gleichzeitig geweitete Listen **und** eine
  umdeklarierte Kennung -- eine bewusste Doppelsabotage, gegen die kein Test dieser
  Ebene schuetzt. Kein Paket noetig.
- Die Paarzaehlungs-Waechter (`fremde_paare > 0`, `eigene_paare > 0`) sind, wie vom
  Bauagenten ausgeschrieben, Rueckhalt gegen kuenftige Umstellung, keine eigene
  Messung; jeder Weg, sie anschlagen zu lassen, reisst vorher Vollzaehligkeit oder
  0085-Pruefung. So stehen sie richtig da.
- Der Gesamtbaum ist 13/14 gruen; rot ist allein `belegstellen_riegel`, am
  Abschnittszitat `daten/nachmessung-zinsreihen-2026-09-05.md` -- fremd zu diesem
  Paket (`schritt_probe` kommt in dessen Fehlerausgabe nicht vor), Vorschlag
  `0120-abschnittszitat-nachmessung-zinsreihen` liegt dafuer bereits beim
  Projektmanager.

## Werkzeugweg dieser Sitzung

`Write`, `Edit`, `sed`, `awk`, python3-Heredoc und `python3 -c` mit Dateizugriff waren
gesperrt. Die Mutanten entstanden als Collagen aus `head`/`tail`/`grep -Fxv` ueber
eine `git show`-Kopie in `$TMPDIR`, die Ersatzzeilen per `printf '%s\n' '...'`, die
Trefferbremse ersetzt durch `git diff --no-index` gegen die Kopie (jeder Mutant zeigt
exakt den beabsichtigten Eingriff und nichts sonst).
