---
typ: pruefung
paket: 0083-belegstellenriegel-totes-ziel-statt-uebergangen
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Rot- und Gruennachweis selbst gefahren (Vorgabenkopie ohne spiel.md gegen den Arbeitsbaum mit bau/ -> Code 1, 15 tote Ziele; echte specs/ -> Code 0, 36/36 aufgeloest, parameter.toml:11 uebergangen) plus vier eigene Mutanten an Ortsfrage und Untergrenze, alle rot.
befunde: 0
---

# Pruefung 0083, Runde 2 -- die Ortsfrage wird am Ort entschieden, und das ist gemessen

Gegenstand ist der Stand `b3dc4b0` von `werkzeuge/belegstellen/belegstellen_riegel.cpp`
(identisch mit dem Arbeitsbaum zur Pruefzeit, `git status` leer). Der Umbau der
Ruecklauf-Runde liegt in drei Commits unter fremden Betreffs (`4ee0f79` +197/-49,
`3840367` +21/-5, `b3dc4b0` +13/-3); der Commit mit dem 0083-Betreff (`497bcbc`)
enthaelt keine einzige Datei dieses Pakets. Dazu unten die Randnotiz.

Alle Messungen an einem eigenen Bau in `$TMPDIR` mit den Schaltern des Runners
(`RelWithDebInfo`, `-fwrapv -fno-fast-math`, Werkzeugkette ueber
`PROJECT_IS_TOP_LEVEL`), M0 vor jeder Mutation. Der Arbeitsbaum wurde nicht angefasst.

## Was ich wie geprueft habe, je Bedingung der Abnahme

**M0 / ctest wie der Runner:** 1/1 Test bestanden am unveraenderten Stand.

**Gruennachweis mit der echten `specs/`** (Aufruf
`belegstellen_riegel <vorhabenwurzel>`, Vorgaben per Voreinstellung):

- Code **0**. Selbsttest: 17 Faelle zur Ortsfrage, alle wie erwartet.
- **36 Zitate gefunden, 36 aufgeloest** (Untergrenze 16) -- alle Zitate aufgeloest.
- **`parameter.toml:11` uebergangen mit dem Grund** `Ziel in einem mit Absicht
  ungelesenen Ordner: befunde/pruefung-0009-parameterdatei-schluessel-runde2-...` --
  wortgleich die verlangte Sorte, und die **einzige** Fundstelle dieser Sorte im
  ganzen Lauf (die Behauptung im Kopfkommentar stimmt damit).
- **Keine der heute uebergangenen Fundstellen ist rot geworden:** Code 0 heisst null
  Befunde und null tote Ziele; die fuenf aus Paket 0067 namentlich geschuetzten
  Fundstellen (`parameter.toml:11`, `daten/lizenzbefund-reihen.md:164/:202/:364`,
  `kern/CMakeLists.txt:3`) stehen alle in der Uebergangen-Liste meines Laufs, jede mit
  unveraendertem Grund. 47 uebergangene Fundstellen insgesamt.

**Rotnachweis gegen den Arbeitsbaum mit bestehendem `bau/`** -- der Vorgang aus
*Der gemessene Sachverhalt*, an dem Runde 1 gescheitert ist: Kopie der vier
Vorgabendateien nach `$TMPDIR`, `spiel.md` entfernt, Aufruf
`belegstellen_riegel <vorhabenwurzel> <kopie>`. Die Vorhabenwurzel ist der echte
Arbeitsbaum; `bau/kp0010/quelle/specs/.../spiel.md` liegt dort nachgeprueft als
Zwilling. Ergebnis: **Code 1, 15 tote Ziele** (verlangt: mindestens 14), alle 15
Verweise auf die entfernte `spiel.md` (14 kurz, 1 lang als
`specs/.../spiel.md`). Aufgeloest faellt auf 21 und bleibt ueber der Untergrenze --
gefangen hat den Einbruch die Zielseite, nicht die Schwelle, wie der Kopfkommentar
behauptet.

**Untergrenze im Quelltext, rot bei Unterschreitung:** `AUFGELOEST_MINDESTENS` steht
bei 16 und wird gemeldet (`36 davon aufgeloest (Untergrenze 16)`). Mutant auf 37
gestellt: Volllauf **Code 2** mit der Untergrenzen-Meldung. Die Zahl selbst ist
unveraendert 16 -- nichts gesenkt.

**Wird der Selbsttest rot, wenn man die Trennung kaputtmacht?** Vier eigene Mutanten,
je an einer `$TMPDIR`-Kopie mit Trefferbremse, unabhaengig vom Nachweis des Bauagenten
gewaehlt und erst danach gegengelesen:

| Mutant | Eingriff | gerissene Zielfaelle | Ausgang |
|---|---|---|---|
| ohne-nennt | Teil 1 der Ortsfrage per `|| true` neutralisiert (= Namensfrage von Runde 1) | 6, 7, 10, 12, 13 | Code 2 |
| ohne-liegt | Teil 2 per `|| true` neutralisiert (nur noch Vorsatzpruefung) | 4, 9, 11 | Code 2 |
| ohne-pfadgrenze | `versatz == 0 || ort[versatz-1] == '/'` durch `true` ersetzt | 11 | Code 2 |
| untergrenze-37 | `AUFGELOEST_MINDESTENS` 16 auf 37 | keiner; Volllauf Code 2 (36 < 37) | Code 2 |

Der erste Mutant ist die Regression, um derentwillen der Ruecklauf kam -- der
Selbsttest faengt sie, bevor der Bestand gelesen ist, und reisst genau die Faelle der
alten Luecke (darunter Fall 13, die Anwartschaft "vorhabenseigene Datei mit Zwilling
unter `bau/`"). Jeder Teil reisst andere Faelle; die Teile messen Verschiedenes.
Erstversuch mit geloeschtem Aufruf starb erwartungsgemaess an
`-Werror=unused-function` -- Werkzeugkette, nicht Test; deshalb die `|| true`-Form.

**Abgeschwaechte Tests:** Diff `f8c8598..HEAD` vollstaendig gelesen. `ZIELFAELLE` von
8 auf 17, rein zulegend; die zwei angepassten Altfaelle (2 und 5) tragen dieselbe
Erwartung mit auf Pfade umgestellter `ungelesene`-Spalte. Untergrenze unveraendert.
Keine Schwelle gesenkt, keine Zusicherung entfernt, kein Test uebersprungen.

**Die offenen Entscheidungen des Zuschnitts** sind getroffen und im Kopfkommentar
begruendet: Verweis ohne Ordner-Vorsatz gilt als **tot** (strenge Richtung, Preis
ausgeschrieben, Meldung erklaert die Berichtigung um zwei Woerter); `aufgaben/` bleibt
kein ungelesener Ordner; die Berichtszahl heisst jetzt "Pfade in ungelesenen Ordnern"
und passt zur neuen Semantik.

## Was ohne Urteilswirkung bleibt

- **Der Commit-Schnitt folgt nicht dem Paket:** `497bcbc` traegt den 0083-Betreff und
  ausschliesslich fremde Dateien (0134, 0076, bezeichner-Riegel); die 0083-Arbeit
  liegt unter den Betreffs von 0078, 0104 und 0116. Bekanntes Muster, als Pakete 0121
  und 0131 bereits eingereicht -- kein neuer Vorschlag noetig.
- Der Nachweis des Bauagenten nennt 2543-3520 "Pfade in ungelesenen Ordnern"; mein
  Lauf mass **5623**. Kein Widerspruch -- parallele Laeufe lassen `bau/` und `befunde/`
  wachsen, genau wie dort vermerkt. Die lineare Suche darin laeuft nur fuer Namen, die
  die Vorsatzfrage bejahen; sie bleibt die Stelle, die mit dem Baum waechst.
- Die Aufloesung der **gelesenen** Ziele geht weiterhin ueber den Basisnamen
  (`bestand.find(basisname(name))`, Erbe aus 0067): Ein toter Verweis wie
  `bau/x/spiel.md` faellt als `Gelesen` auf die echte `spiel.md`, solange die zitierte
  Ueberschrift dort steht. Ausserhalb dieser Abnahme; der Bauagent hat es selbst als
  moegliches eigenes Paket benannt.
