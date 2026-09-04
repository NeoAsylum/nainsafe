# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-04, nachts. Fassung 20, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer entscheiden
lassen muss.

**Dieser Lauf hat nichts Neues erfunden und trotzdem den Engpass verschoben.** Drei
Prüfbefunde lagen vor, alle drei `geprueft`; mit ihrer Abnahme ist die Prüfschlange von
vier auf zwei gefallen — und **0027, die Nummer zwei des Vorrangs, hat damit zum ersten Mal
seit seinem Rücklauf wieder einen Prüfplatz.** Er hatte keinen, weil vier abgearbeitete
Pakete die Plätze hielten. Das war der ganze Stau.

## Drei Abnahmen, und was sie freigeräumt haben

| Paket | Rolle | Befund | jetzt |
|---|---|---|---|
| `0048-meldung-in-zustand-nachziehen` | `kernbauer` | `geprueft`, 0 Befunde | `fertig` |
| `0052-festkomma-mal-mit-waechter` | `kernbauer` | `geprueft`, 0 Befunde | `fertig` |
| `0059-belegstellenriegel-im-baulauf` | `testentwickler` | `geprueft`, 1 Befund, nicht paketfällig | `fertig` |

Alle drei Befunde ganz gelesen, nicht nur das Frontmatter. Keiner verlangt einen Rücklauf.
Der eine Befund an 0059 — der Riegel sieht einen Dateinamen nur unmittelbar links vom
Treffer — ist vom Prüfer selbst ausdrücklich **außerhalb** dieses Pakets verortet und liegt
jetzt als Paket 0073 vor.

**Die Abnahme von 0048 hat nebenbei ein viertes Paket startbereit gemacht:**
`0056-meldung-abschneiden-kenntlich` hing daran und steht im nächsten Durchgang auf einem
Bauplatz. Es hat keinen Tag gewartet — aber es zeigt, dass die Prüfschlange nicht nur
Prüfplätze kostet, sondern auch Bauplätze hinter sich staut.

## Die letzte offene Fährte ist tot — und sie ist zugunsten der Rollen ausgegangen

Fassung 18 hatte aus drei leeren Bauplätzen über zwei Pakete auf eine schwache Rolle
geschlossen; Fassung 19 hat das widerrufen. Übrig blieb eine schwächere Vermutung: *In
jedem Durchgang, in dem zwei Pakete derselben Rolle einen Bauplatz hatten, hat höchstens
eines geliefert.* Ich hatte den Prüffall vorher benannt — der Durchgang plante 0027 und
0048, **beide `kernbauer`**.

**Beide haben geliefert.** `598b128` an `kern/src/zustand.cpp`, `7eb8061` mit 16 Zeilen an
`kern/include/kern/zustand.hpp`; 0048 ist inzwischen abgenommen, 0027 wartet auf die
Prüfung. Die Vermutung ist widerlegt, und zwar an dem Fall, den ich vorab dafür ausgewählt
hatte. **Es gibt in diesem Vorhaben keinen Rollenbefund mehr.**

## 0061 bleibt `blockiert` — aber der Grund steht jetzt auf einer anderen Messung

Das ist die Stelle, an der ich mit der neuen Tatsache gegen meine eigene Sperre geprüft
habe, statt sie fortzuschreiben. Denn die tote Korrelation war einer der Gründe, aus denen
0061 mit gesperrt wurde.

**Die Sperre hält trotzdem, weil sie nicht darauf steht.** In diesem Lauf neu gemessen:

- `git log` auf die Zieldatei `pruefstand/test/vorrat_kernanker_probe.cpp` nennt als
  einzigen und letzten Eintrag `f68e8fb` vom **2026-09-03**, Betreff
  `datenbauer: 0042-parameterdatei-indexbegruendung` — ein fremdes Paket.
- Der Commit `4e51c14` mit „testentwickler: 0061" im Betreff enthält **zwei Dateien, beide
  zu 0052** (`befunde/block-0052.txt`, `befunde/schreibprobe-0052.txt`).

Das ist Fall (d) — meldet, liefert nicht — und gilt unabhängig von jeder Aussage über
Rollen. Alle vier möglichen Ursachen (Kriterium, Vorgabe, Zuschnitt, Rolle) sind einzeln
nachgemessen und einzeln widerlegt; die verbleibende Ursache liegt über meiner Rolle. Das
steht so auch im Paket, damit niemand den Statuswert für ein Urteil über den Auftrag hält.

## Drei Vorschläge, drei Annahmen — und eine Bedingung, die ich geheilt habe

Alle drei kamen von Prüfern und Bauagenten dieses Durchgangs, alle drei sachlich richtig.

- **`0072-zustandhpp-doppelpunktverweise`** (`kernbauer`) → `offen`. Zwei Verweise in
  `zustand.hpp`, die der Riegel bauartbedingt nicht sieht. `haengt_an: [0027]` bleibt und
  ist **keine** reine Reihenfolgesperre: 0027 steht auf `gebaut` und hält dieselbe Datei,
  und der Kollisionsschutz sieht `gebaut` nicht (`baulauf.py:270-281`).
- **`0073-belegstellenriegel-dateiname-weiter-links`** (`testentwickler`) → `offen`. Der
  Befund aus 0059. `haengt_an: [0067]` ist inhaltlich — erst 0067 stellt den Korpus her,
  gegen den dieses Paket grün bleiben muss. Seine Abnahme sagt richtigerweise „auf dem
  **dann** geltenden Korpus" und nennt keine feste Trefferzahl.
- **`0074-massnahme-43-mechanisch-erzwingen`** (`architekt`) → `offen`, **mit geänderter
  Bedingung 3.**

**Was an 0074 zu heilen war**, und warum es hier steht: Die Bedingung verlangte, die Zahl
„52 Zeilen" in T7 auf **54** zu berichtigen — eine absolute Zahl aus der Summe
`grep -rn ' \* ' kern/src kern/include`. In genau diese Summe schreibt das offene Paket
0071 (`schritt.cpp`, `schritt.hpp`). Hätte 0071 vorher eine Multiplikation gelegt, wäre die
Abnahme von 0074 durch fremde Arbeit unerfüllbar geworden, bevor der Architekt sie erreicht.
**Das ist in diesem Vorhaben der fünfte Fall derselben Art.** Die Bedingung verlangt jetzt
die Messung samt Bezugsstand statt des Messwerts.

## Sechs Pakete liegen auf `technik.md` — Fassung 19 hat vier gezählt

Nachgemessen an den `dateien`-Listen, nicht am Titel: `specs/…/technik.md` ist die
Kollisionseinheit von **0026, 0043, 0051, 0064, 0068 und 0074** — alle sechs `architekt`,
alle sechs `offen`. Fassung 19 nannte vier und hat 0068 übersehen; 0074 ist heute
dazugekommen.

Der Baulauf plant davon **eines je Durchgang**. Das ist der Kollisionsschutz bei der Arbeit
und kein Fehler — aber es heißt, dass der Architektenrückstand bei heutiger Geschwindigkeit
sechs Durchgänge braucht, und **0002 wartet hinter dem ersten davon**. Der Zuschnitt bleibt
trotzdem richtig: sechs verschiedene Abschnitte, und sie zusammenzuziehen widerspräche „ein
Paket, ein Agent, ein Lauf".

**Ich lege deshalb kein siebtes an.** `rueckstand.md` Punkt 6 und 7 (Wohnort der
Zustandsausgabe, Rundung bei Reihe 2) sind von 0026 ausdrücklich an „das nächste
Architektenpaket" verwiesen. Sie sind Entwurfsfragen, sie stehen hier, und sie werden das
nächste Architektenpaket — wenn die Schlange kürzer ist, nicht jetzt.

## Gemessen, nicht angenommen

| Behauptung | wie gemessen |
|---|---|
| drei Befunde sagen `geprueft` | `grep '^urteil:'` auf alle drei Dateien; jede ganz gelesen |
| 0027 und 0048 haben beide geliefert | `git show --stat` auf `598b128` und `7eb8061`: `zustand.cpp` bzw. `zustand.hpp` (16 Zeilen) |
| 0061 hat wieder nichts geliefert | `git log` auf die Zieldatei: unverändert `f68e8fb` (2026-09-03), fremdes Paket; `git show --stat 4e51c14` nennt zwei 0052-Dateien |
| sechs Pakete auf `technik.md` | `grep '^dateien:'` auf alle sechs, nicht `grep -l` auf den Text |
| 0074 kollidiert mit 0071 in einer Summe | `dateien` von 0071 = `kern/src/schritt.cpp`, `kern/include/kern/schritt.hpp`; die Summe läuft über `kern/src` und `kern/include` |
| 0002 hängt nur noch an 0026 | `haengt_an: [0008, 0026]`; 0008 steht auf `fertig` |
| Paketzahl stimmt | Kopfzahl 74 + 1 archiviert = `ls aufgaben/*.md \| wc -l` = 75 |

## Der Rückstand

**74 Pakete**, dazu ein archiviertes (doppelte Kennung 0056) — zusammen 75 Dateien.

| Zustand | Zahl | welche |
|---|---:|---|
| `fertig` | 53 | — |
| `offen` | 16 | 0002, 0010, 0026, 0043, 0051, 0056-meldung, 0064, 0065, 0066, 0067, 0068, 0069, 0071, 0072, 0073, 0074 |
| `gebaut` | 2 | 0027, 0044 |
| `blockiert` | 3 | 0003, 0041, 0061 |
| `vorschlag` | 0 | alle drei dieses Laufs entschieden |

**Der nächste Durchgang baut** 0026 (`architekt`), 0056-meldung (`kernbauer`), 0065
(`datenbauer`), 0066 (`kernbauer`) — vier Plätze, drei Gewerke, keine Kollision.
**Geprüft werden** 0027 und 0044.

**Zwei Prüfplätze laufen leer**, und das ist diesmal kein Versäumnis: Prüfbar ist nur, was
gebaut ist, und `gebaut` steht bei zwei. Der Bauvorrat ist mit 16 offenen Paketen auf vier
Plätzen reichlich; die Schlange füllt sich von selbst wieder.

## Zum Vorrang des Geschäftsführers

Der Plan vom 2026-09-04 nennt fünf Kennungen. **Vier sind abgearbeitet, die fünfte läuft:**

- 1. **0011** — abgenommen. 2. **0027** — gebaut, hat in diesem Lauf seinen Prüfplatz
  bekommen. 3. **0026** — auf einem Bauplatz. 4. **0054** — abgenommen. 5. **0050** —
  abgenommen.

**Ich bin in diesem Lauf nicht vom Plan abgewichen.** Der Vorrang ist damit weitgehend
erschöpft und braucht eine neue Fassung; der nächste Plan sollte sagen, ob der
Architektenrückstand auf `technik.md` Vorrang vor der Aufräumarbeit an den Verweisen hat.

## Was der Geschäftsführer entscheiden lassen muss

1. **0061: drei belegte Bauplätze, null Zeilen, keine benennbare Ursache.** Unverändert
   offen und in diesem Lauf erneut an der Zieldatei bestätigt. Frage an den Runner oder das
   Harness, nicht an das Paket. Der Auftrag ist gültig und in einem Lauf ausführbar.
2. **Der fehlende Satz „Setze `status: gebaut`" in drei Rollendateien** (`architekt`,
   `spielentwerfer`, `testentwickler`). Elfmal von mir nachgetragen. Bis er dort steht,
   bleibt jede Lieferung dieser drei Rollen einen Lauf lang unsichtbar.
3. **Maß 2 widerspricht sich zwischen Frontmatter und Text von `spiel.md`** („höchstens 25
   Prozent besser" gegen `max(Ek) ≤ 1,25 × min(Ek)`). Entwurfsfrage, kein Paket von mir.
4. **Dateileichen unter `aufgaben/` und `befunde/`**: `.kopf.tmp`, `.paket.tmp` und neu
   `befunde/append.tmp` (vier Zeilen fremdes Frontmatter, aus dem 0059-Lauf). Hausregel 3
   verbietet mir das Löschen — jemand muss entscheiden, ob sie wandern.
5. **Sechs `architekt`-Pakete auf einer Datei** (neu). Kein Fehler, aber der Grund, warum
   die Spezifikationsarbeit sechsmal langsamer läuft als die Zahl der Pakete vermuten lässt.

## Die eine Zahl

**`werte.hpp` steht unverändert bei 78 Byte, `werte.cpp` gibt es nicht.** Acht von neun
Kernkästen tragen Code, der neunte seit fünf Fassungen nicht. **Eine Spielrunde ist noch
immer nie gerechnet worden.**

Der Weg dorthin ist so kurz wie noch nie und vollständig sichtbar: `0002-fondsbewertung`
hängt an genau zwei Paketen, **0008 ist abgenommen**, und **0026 liegt jetzt auf einem
Bauplatz**. Fällt 0026 durch Bau und Prüfung, ist 0002 startbereit — dann ist zum ersten
Mal nichts mehr zwischen dem Vorhaben und dem letzten leeren Kernkasten.

**Eine Bedingung dazu ist bereits verdrahtet, und sie fällt an mich:** Bedingung 4 von 0026
verlangt vom Architekten die ausdrückliche Aussage, ob T47, T48 und T50 unberührt bleiben.
Bleiben sie es, geht 0002 unverändert weiter; ändern sie sich, ziehe ich Umfang und Abnahme
von 0002 nach — dessen Abnahme nennt heute die feste Zahl 4.200.000.000.000 Cent aus T47.
**Das ist der erste Auslöser, den ich im nächsten Lauf ziehe.**
