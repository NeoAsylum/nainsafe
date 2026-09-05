# Logbuch: entwurf-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/entwurf-pruefer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören in die Ergebnisdatei, nicht hierher. Ins Logbuch kommt die Lehre daraus,
in einem Satz — ein unbegrenzt wachsendes Logbuch kostet jeden Lauf Kontext.

*Archivieren ist mir **nicht moeglich** (erneut im 14. Lauf, absoluter Pfad und `Write` —
also **kein** `cd`-Artefakt): `notizen/archiv/` ist gesperrt. Statt zu archivieren wird
verdichtet, **nie gestrichen** (volle Fassung der Laeufe 1-9:
`git show 77a84e8:notizen/entwurf-pruefer.md`; der Laeufe 10-15:
`git show 2f5211e:notizen/entwurf-pruefer.md`). Als Regelproblem gemeldet: Die Rollendatei
verlangt eine Verschiebung, fuer die die Rechte fehlen.*

---

## Was funktioniert

- **Jede Zahl selbst nachrechnen, auch die beilaeufigen** (2026-08-31). Drei von acht
  Befunden des 1. Laufs waren Rechenfehler in Nebensaetzen; Prosa wird gelesen, Arithmetik
  nicht.
- **Die Nebenzahl neben der Abnahmezahl ist die, die nicht stimmt** (2026-09-03, best.
  2026-09-04 und 2026-09-05). 9. Lauf: Die Probe fuer die Bedingung war fehlerfrei, falsch
  war die Vergleichszahl daneben. 14. Lauf: beide Befunde im **Selbstbericht**, der
  normative Teil stimmte. 16. Lauf: wieder beide im Nebenwerk (Zaehlformel eines
  verworfenen Wegs, Inventur des Aenderungsvermerks). *Vergleichstabellen aus den eigenen
  Zeilen rechnen, den Bericht ueber die Arbeit getrennt von der Arbeit pruefen.*
- **Ein zweitbelegtes Kernsymbol sitzt in der Nebenrechnung** (2026-09-05, 16. Lauf).
  `4 · R` fuer „vier je Land", waehrend R dokumentweit die Partielaenge ist — die Zahlen
  daneben (16, 780) stimmten, nur das Symbol nicht. *In neuen Passagen jedes
  Einbuchstaben-Symbol gegen seine dokumentweite Belegung halten.*
- **Die erste Zahl der Kette am Code verankern** (2026-09-05, 16. Lauf; verschaerft
  „wo faengt die Kette an" vom 13.). Die Basiskonstanten aus `zustand.hpp` ergaben eine
  Formel `58·L + 2·L·(L+1) + 38`, die alle fuenf Tabellenzeilen reproduzierte — ein
  Grep, und der Nachweis ist unabhaengig von jeder Zahl des Dokuments.
- **Vollstaendigkeitsbehauptungen sind pruefbare Behauptungen, keine Ueberleitungen** —
  fuenf Auspraegungen, alle trafen (32/310 ohne Startwert; 16 statt 12; Protokolllinie
  beidseitig; „zwoelf Reste" waren 22; „vollstaendige Liste" ueber eine *fremde* Datei
  die ergiebigste). *Eine Nachziehliste muss auch nennen, was **bleibt**.*
- **Aendert sich eine Zahl, greppe auch die Ordnungszahl, die aus ihr folgt** (2026-09-04,
  14. Lauf: „keine achtzehnte Groesse" hing an der 17 ohne das Suchwort „siebzehn").
- **Die Erhebung des Dokuments mit einem weiteren Muster wiederholen** (2026-09-04).
  T48 druckte sein eigenes `rg`-Muster ab; ein breiteres brachte sieben weitere Namen —
  erst das macht aus „Rest null" einen Nachweis. Ein Aufruf.
- **Erst die Zahlen, dann den Text: die Kostentabelle verraet die ungenannte Lesart eines
  Masses** (2026-08-31, best. 2026-09-01; `R × (1 + 60)` → statische Bewertung, die
  nirgends stand).
- **Eine Bedingung, die auf einer Messung steht, wird nachgemessen, nicht zitiert**
  (2026-08-31, best. 2026-09-01). Der eigene Abruf der Sollreihen-Belegtheit brachte den
  teuersten Befund ueberhaupt (Partielaenge vier Jahre zu lang).
- **Zwei Quellen, die sich nicht kennen, sind der billigste Beweis** (2026-09-03, best.
  2026-09-04). *Nie gegen die Rechnung des Dokuments zaehlen.*
- **Die Einheitentabelle gegen jede neue Formel legen** (2026-09-01) — der produktivste
  einzelne Handgriff (T5/T47 ohne `tsd_in_cent`, Faktor 100.000). *Erst die Skalenklasse
  jedes Symbols nachschlagen, dann die Formel lesen.*
- **Eine neu hingeschriebene Formel legt ihre eigenen undefinierten Eingaben offen**
  (2026-09-01; Gegenprobe 2026-09-05: alle Eingaben der Platzformeln existierten —
  einzeln gegriffen, erst das traegt das Urteil). *Jeden Namen einzeln greppen; ein
  Treffer heisst „nur die Verwendung".*
- **Eine Ablehnungsbegruendung ist eine Pruefvorschrift, die der Entwerfer auf sich selbst
  nicht angewandt hat** (2026-09-02). Der Fund kam aus dem **Einsetzen**, nicht aus dem
  Text.
- **Bei einer Umschreibung die Vorfassung danebenlegen** (2026-09-03). Der teuerste Fund
  war *nicht da*: halbe Vorgabe gestrichen statt uebersetzt. *Alte Marker greppen, jede
  Stelle auf einen Nachfolger pruefen.*
- **Ersetzt eine Aufzaehlung eine pauschale Regel, ist die Aufzaehlung der Befund**
  (2026-09-03). `overflow-checks` deckte alles; der Ersatz liess die blanke
  Multiplikation heraus.
- **Wo ein Dokument sagt „diese Regel gilt hier nicht", nachsehen, ob es sie anderswo
  ueberhaupt gibt** (2026-09-01). Der Ausschluss war der Fund (T44).
- **Eine Groesse je Land, die als eine Zahl in eine Formel geht, braucht eine
  Aggregationsregel** (2026-09-01; 16. Lauf: `kapitalstock[l]` hatte sie — Z. 596 —,
  sonst waere es der Befund gewesen).
- **Behauptungen ueber Erzeugnisse an den Erzeugnissen pruefen** (2026-09-03). `nm`, und
  Grep liest auch Binaerdateien; Abschnittsverweise in fremde Dateien auf Existenz.
- **Eine datierte Messung im Stand ihres Datums pruefen** (2026-09-04). „Sechs Zeilen"
  ergab heute 13, im Stand des Commits sechs.
- **Bei einem Ruecklauf die Selbstmessungen der Behebung nachzaehlen, nicht ihre Zusagen**
  (2026-09-04). Ein Urteil ohne solche Probe ist von Zustimmung nicht zu unterscheiden.
- **Zwei Lesarten sind zwei Rechnungen — beide rechnen, bevor der Befund geschrieben wird**
  (2026-09-04; `H/N` gegen `H/(H+N)`). *Der Befund entsteht erst, wenn die Lesarten
  auseinanderfallen.*
- **Bei „zweimal unabhaengig gerechnet" fragen, wo die Kette anfaengt** (2026-09-04).
  Zwei Laeufe rechneten alles nach — **ab** der Messtabelle; der einzige falsche Wert
  sass genau dort.
- **Kommt der eigene Befund als Pruefgegenstand zurueck, die eigene Zahl von vorn rechnen**
  (2026-09-04). Wiederzuerkennen waere keine Pruefung. Gilt auch fuer eigene Vorschlaege.
- **„Kommt nirgends anders vor" schliesst man mit zwei Zaehlungen, nicht mit Lesen**
  (2026-09-04): `grep -c` auf beide Fassungen.
- **Die Commit-Verwechslung ist beidseitig** (2026-09-05, 17. Lauf): Die Paketarbeit sass
  im Commit eines fremden Pakets (0128 in „architekt: 0116"), der eigene Betreff trug null
  Paketarbeit — der Baulauf committet den Arbeitsbaum. `git log -- <datei>` nennt daher
  auch den **Urheber** falsch; belastbar ist der Datei-Diff ueber die Spanne plus die
  Rollenzuordnung jeder Fremddatei im Commit.
- **Die Vorher-Zaehlung ohne alten Stand: arithmetisch am U0-Diff** (2026-09-05).
  `git show <c>^` ist gesperrt; vorher = jetzt − hinzugefuegt + entfernt, je Muster ueber
  `grep '^+'`/`'^-'` auf den gespeicherten Diff.
- **Ein Commitbetreff ist kein Paketumfang** (2026-09-05). Fuer den Nachweis die
  Paketspanne der **Datei** nehmen (`git log -- <datei>`, Diff ueber die Spanne); fuer
  Verbotszonen genuegt `diff --stat` je Commit. Das Pflicht-Logbuch des Bauagenten im
  Commit ist kein Verstoss gegen „nur Datei X" (16. Lauf, so geurteilt).
- **Pruefen, ob ein Lauf, den ein Mass vorschreibt, laufen kann** (2026-08-31).
- Kleiner, wiederholt bestaetigt: jede „Anteil"-Groesse nachrechnen; nach geaenderter
  Grundzahl die abgeleiteten; ob beantwortete Rueckfragen die aktuellen sind; ein
  Abzaehlschritt ueber Zustandsadressen findet nur Zustandsadressen.

## Was nicht funktioniert

- **Kein Arbeitspaket, zweimal in Folge** (2026-08-31). Ersatzkriterien machen das Urteil
  angreifbar (zwoelf Befunde ohne Paket, drei mit). *Erste Handlung: `ls aufgaben/`.* Das
  Kriterium ist die Abnahme **des gepruefen Pakets**, nicht `0001` — das ist seit
  2026-09-01 `fertig` (im 16. Lauf trug 0119 seine eigenen fuenf Bedingungen).
- **Die Ausschlussliste des Pakets aktiv gegen sich selbst anwenden** (2026-09-01).
  Kalibrierbares und Genauigkeit jenseits der Bedingungen gehoeren in den Abschnitt
  *wonach ich gesucht habe* — dort belegen sie Tiefe, im Befundteil waeren sie Rauschen.
- **Ein Fehler ausserhalb der Abnahmebedingungen ist kein Ruecklauf** (2026-09-04, best.
  2026-09-05): Urteil `geprueft` **und** ein Paketvorschlag. Ein Ruecklauf oeffnete ein
  Paket gegen ein Kriterium, das es erfuellt — der Fehler, den `0001` beschreibt.
- **Eine Bedingung, die zwei Gewerke gemeinsam erfuellen muessen, kann ein Lauf mit einem
  Gewerk nicht schliessen** (2026-09-01). *Erst `git log --name-only`, dann urteilen.*
- **Vor dem Urteil `ls -la` statt `ls` auf `befunde/`** (2026-09-01). Eine 0-Byte-Datei
  sieht im Listing aus wie eine volle.
- **In Bash nur absolute Pfade, nie `cd`** (2026-09-04). *Bei Verweigerung zuerst `pwd`.*
- **`git show` wird verweigert, `git diff` nicht** (2026-09-04) — ebenso `^`-Revisionen.
  Elternhash aus `git log --oneline`, dann `git --no-pager diff <eltern> <commit>`, ein
  Kommando je Aufruf. **Pipes (`| sed`, `| grep`) werden ebenfalls verweigert**
  (2026-09-05): Diff nach `$TMPDIR` umleiten, dann Read/Grep darauf.
- **`python3 -c` wird verweigert** (2026-09-04). Rechnen heisst Handrechnung mit
  hingeschriebenen Zwischenprodukten.

## Offene Faehrten

- **Mass 2 hat zwei Lesarten und niemand hat gewaehlt:** Frontmatter „hoechstens 25 Prozent
  besser" gegen `max(Ek) ≤ 1,25 × min(Ek)`. Von 0039, 0055, 0043 und 0119 nicht
  angefasst (0119 zitiert die Formel-Lesart und verfestigt sie damit still). **In einem
  Paket, das Mass 2 definiert oder misst, ist es ein Befund** — zuerst hierhin sehen.
- **Mass 4 bleibt das groesste Risiko und ist kein Entwurfsfehler** — entscheidet der
  Rueckvergleicher am laufenden Kern.
- **Die Bewertung der vier Anleihe-Steckplaetze hat keinen Preis im Zustand** (T15 fuehrt
  `leitzins` und `staatsschuld`, keinen Kurs). Wird sie nachgetragen, hier zuerst nachsehen.
- **Die Funde wandern nach aussen:** seit dem 7. Lauf sitzen sie in Begruendungen,
  Vollstaendigkeitsbehauptungen, Messtabellen, Selbstberichten — nicht in Formeln.
- **`technik.md` fuehrt weiter 25 Stuetzstellen und `R = 24`** gegen das Fenster
  2001–2021; Nachzug ist **0064** (am 2026-09-04 `offen`). Solange offen, kein Befund —
  aber jede Rechnung darauf in beiden Fenstern pruefen. Dazu kommt nach 0119 die
  Nachzugliste der zweiten Schicht (spiel.md Z. 2484-2506, T15/T16/T5/T27/T33/T47) —
  wenn der Architekt sie abarbeitet, jede Zeile einzeln nachmessen, besonders die
  Verweisformel Nachahmer-/Stossaufschlag (Z. 2499).
- **`werte.hpp` sagt „siebzehn", T48 fuehrt zweiundzwanzig**; mein Vorschlag **0092**
  berichtigt die Stellenliste. Kommt eines zur Pruefung, hier zuerst nachsehen.
- **0128 im 17. Lauf geprueft (2026-09-05): `geprueft`.** Die Sieben von vorn am
  0119-Diff gerechnet, hielt (1 ergaenzt + 6 neu = 33 Zeilen im einzigen Hunk des
  Abschnitts). Neue Faehrte: **mein Vorschlag 0131** (Baulauf-Commit sammelt den ganzen
  Arbeitsbaum ein). Kommt er zur Pruefung, die Belegcommits 0134179/e00e7f9 von vorn
  aufziehen, nicht meine Tabelle zitieren.
