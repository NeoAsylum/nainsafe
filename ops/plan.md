# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-03 23:55. Abgedeckt: 2026-09-03 15:10 bis 23:43 — der Nachtlauf nach dem
Ausfall des Wirts und nach acht Betriebs-Commits des Betreibers (18:41–19:08).

## Wo das Vorhaben steht

**Aus 43 Paketen sind 61 geworden:** 37 fertig, 14 offen, 6 gebaut, 2 Vorschläge, 2
blockiert. In achteinhalb Stunden wurden 16 Pakete abgenommen und 18 neue angelegt — der
Rückstand wächst weiter schneller, als er schrumpft. **Die eine Zahl steht dabei den
dritten Plan in Folge still.** Der Betreiber hat in derselben Nacht die Wochenbremse
repariert (sie rechnete gegen die Vorwoche und drosselte die Fabrik um 510 $) und den Takt
auf stündliches Nachholen umgestellt; beides wirkt, der Durchsatz ist sichtbar gestiegen.

## Der Engpass

**Vier Pakete mit bestandenem Urteil stehen weiter auf `gebaut` und verstopfen damit die
gesamte Prüfwarteschlange.**

0040, 0049, 0053 und 0058 tragen `urteil: geprueft` — drei davon zweimal, weil sie in
derselben Nacht ein zweites Mal geprüft wurden. Nur der Projektmanager darf `geprueft` →
`fertig` ziehen (`agents/rollen/projektmanager.md:95`). Die Urteile fielen 22:58–23:07, er
lief um 23:18 — und hat in diesem Lauf eine einzige Datei angefasst: ein neues Paket.

Die Folge ist nicht bloß Nacharbeit. `reviewbereit()` sortiert nach der Zahl der Rückläufe,
das am wenigsten geprüfte zuerst (`agents/baulauf.py:264`), und nimmt vier. Die vier haben
null Rückläufe und belegen damit dauerhaft alle vier Prüfplätze. **0011 und 0027 haben je
einen Rücklauf und kommen deshalb nie an die Reihe.** 0011 wurde am 20:18 neu geliefert und
hat seither fünf Durchgänge ohne ein einziges Urteil überstanden; 0027 wartet seit dem
2026-09-02 21:10, über vierundzwanzig Stunden. *Der Projektmanager schreibt, 0011 „steht im
Review" — es steht nicht darin; der Trockenlauf von 23:43 nennt die vier anderen.*

An diesen beiden hängt fast der ganze Rückstand: **0011 blockiert sechs der vierzehn
offenen Pakete** (0026, 0051, 0052, 0043 direkt; 0002 und 0010 darüber), **0027 drei**
(0044, 0048, 0056). Elf von vierzehn offenen Paketen warten hinter den sechs gebauten.
Startbereit sind genau zwei.

**Der Ausweg kostet einen Lauf:** Setzt der Projektmanager die vier auf `fertig`, sind 0011
und 0027 die einzigen in der Schlange und bekommen im nächsten Durchgang ihr Urteil.

## Was quer liegt

- **Die Sortierregel hat ihr eigenes Spiegelbild erzeugt.** Sie kam am 2026-09-02, weil
  0009 und 0015 dreimal zurückkamen und 0023–0025 aushungerten. Jetzt hungert sie aus, was
  einmal zurückkam. Beide Male dieselbe Lücke: Ein Paket verlässt die Schlange nicht von
  selbst, sondern nur, wenn sein Urteil nachgezogen wird.
- **Drei Baurollen fehlt der Satz „Setze `status: gebaut`"** — `architekt`,
  `spielentwerfer`, `testentwickler` (nachgemessen: 0 Treffer, bei `kernbauer` und
  `datenbauer` je 1). Der Projektmanager trägt jeden dieser Übergänge von Hand und meldet
  es als achten Fall der vom Betreiber benannten Fehlerklasse. `agents/rollen/` darf kein
  Gewerk schreiben.
- **0041 ist jetzt mir zugewiesen** (`rolle: geschaeftsfuehrer`) und ändert
  `agents/baulauf.py`. Ich schreibe keinen Code, und `geschaeftsfuehrer` steht nicht in
  `BAUROLLEN` — der Runner plant es nie ein. Der Befund selbst ist eingetreten: Der heutige
  Übersetzungsbericht meldet `manifeste: 4`, und das vierte ist
  `pruefstand/bau/pruefung-0019/CMakeLists.txt`, ein unversioniertes Erzeugnis. **Die elf
  grünen Tests unter „Der Compiler hat gesprochen" stammen daraus, nicht aus dem Kern.**
- Unverändert 18 `.tmp`-Dateien im Repo, dazu `aufgaben/.kopf.tmp` und `.paket.tmp` —
  Schaden vom Projektmanager mit null gemessen, `baulauf.py:215` liest nur `*.md`.

## Was der Betreiber entscheiden muss

**Wofür die letzten 648,6 $ der Abo-Woche ausgegeben werden.** Verbraucht sind 951,4 von
1.600 $; das Fenster setzt Montag 2026-09-07 10:00 zurück. Die letzten fünf Stunden kosteten
330,9 $. Bei der Tagesgrenze von 350 $ (`agents/lauf.py:TAGESGRENZE_USD`, Tageslauf 350) ist
die Woche **Samstagfrüh leer** — und damit stillgelegt, bevor das Wochenende beginnt.

- **A — laufen lassen wie jetzt.** Zwei volle Nächte, danach zwei Tage Stillstand.
- **B — Tagesgrenze für den Rest der Woche auf ~180 $.** Die Fabrik läuft bis Montag durch.

**Empfehlung B**, aus einem Grund: Eine Entscheidung, die Sie am Samstag treffen — etwa die
Rohdaten zu laden —, kann in Fassung A in dieser Woche nicht mehr wirken. Dazu kommt, dass
mehr Tempo derzeit nicht mehr Fortschritt heißt: In der vergangenen Nacht sind 18 Pakete
entstanden und 16 abgenommen worden, während die eine Zahl stillstand.

**Kein zweiter Punkt — sondern ein Befund.** Die Rohdaten habe ich zweimal vorgelegt; ein
drittes Mal frage ich nicht. `daten/roh/` existiert nicht, `reihen.toml` sagt über sich
selbst weiter „Sie enthaelt keine Datenzeile", und `datenbauer` plus `daten-pruefer` stehen
inzwischen bei **334,25 $ — 35 % der Bauphase für Arbeit über Daten, die niemand geladen
hat.** Nach 0057 hat das Datengewerk kein Paket mehr; dann läuft der Bauplatz leer. Ich
behandle das Ausbleiben der Antwort als die Antwort und nehme die Frage aus dem Plan.

## Vorrang

**Zuerst, ohne Kennung, an den Projektmanager: 0040, 0049, 0053 und 0058 auf `fertig`
ziehen.** Solange sie stehen, wirkt keine der fünf Kennungen unten.

1. **0011** — sein Urteil entblockt sechs der vierzehn offenen Pakete, mehr als alles andere
   im Vorhaben. Fünf Durchgänge ohne Prüfung.
2. **0027** — entblockt drei weitere und wartet am längsten, seit über vierundzwanzig Stunden.
3. **0026** — sobald 0011 durch ist, das einzige Paket, das über 0002 den letzten leeren
   Kernkasten öffnet.
4. **0054** — startbereit und beantwortet die älteste offene Entwurfsfrage, die Partielänge.
   Solange sie offen ist, sind alle vier Maßvorschriften vorläufig.
5. **0050** — das zweite startbereite Paket; sonst läuft ein Bauplatz leer.

## Die eine Zahl

**Acht von neun Kernkästen tragen Code; `werte.hpp` steht bei 78 Byte**, `werte.cpp` gibt es
nicht. Unverändert seit drei Plänen, während 18 neue Pakete entstanden sind. Eine Spielrunde
ist noch immer nie gerechnet worden.
