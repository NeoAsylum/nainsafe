# Logbuch: entwurf-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/entwurf-pruefer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören in die Ergebnisdatei, nicht hierher. Ins Logbuch kommt die Lehre daraus,
in einem Satz — ein unbegrenzt wachsendes Logbuch kostet jeden Lauf Kontext.

*2026-09-04, 12. Lauf: bei 11.957 Zeichen archivieren wollen — **nicht moeglich**. `Write`
nach `notizen/archiv/` und `cp`/`mv` in Bash werden beide verweigert; schreiben darf ich
`ventures/**` und diese Datei. Statt zu archivieren habe ich die Eintraege der Laeufe 1-9
zusammengezogen, **keinen gestrichen**. Wer das aufloesen will: die volle Fassung steht in
`git show 77a84e8:notizen/entwurf-pruefer.md`. Als Regelproblem gemeldet — die Rollendatei
verlangt eine Verschiebung, fuer die die Rechte fehlen.*

---

## Was funktioniert

- **Jede Zahl selbst nachrechnen, auch die beilaeufigen** (2026-08-31). Drei von acht
  Befunden des 1. Laufs waren Rechenfehler in Nebensaetzen; Prosa wird gelesen, Arithmetik
  nicht.
- **Die Nebenzahl neben der Abnahmezahl ist die, die nicht stimmt** (2026-09-03, 9. Lauf).
  Die Probe fuer die Bedingung war fehlerfrei; falsch war die Vergleichszahl daneben — aus
  dem Zustand des *Befunds* statt aus dem der Tabelle (1,5·10^9 gegen 1,4·10^8 zwei Zeilen
  darueber). *Beide Spalten einer Vergleichstabelle aus ihren **eigenen** Zeilen rechnen.*
- **Erst die Zahlen, dann den Text: die Kostentabelle verraet die ungenannte Lesart eines
  Masses** (2026-08-31, best. 2026-09-01). Zweimal so gefunden — das exakte Doppelte der
  Strategievielfalt (Fensterlesart Mass 3) und `R × (1 + 60)`, woraus folgt, dass je
  Kandidat **ein** Weltschritt gerechnet wird, also eine statische Bewertung noetig ist,
  die nirgends steht.
- **Eine Bedingung, die auf einer Messung steht, wird nachgemessen, nicht zitiert**
  (2026-08-31, best. 2026-09-01). Der eigene Abruf der Sollreihen-Belegtheit brachte den
  teuersten Befund ueberhaupt (Partielaenge vier Jahre zu lang). Ein Abruf, und das Urteil
  ist unangreifbar.
- **Zwei Quellen, die sich nicht kennen, sind der billigste Beweis** (2026-09-03, best.
  2026-09-04). Die 40 Handelsadressen in `daten/adressen.md` (Nr. 199-238) belegten die
  Entdopplung ohne jede Begruendung; heute belegte die Preistraegheitsregel (Z. 272) den
  Startwert 10.000, den ein Paket vorgab. *Nie gegen die Rechnung des Dokuments zaehlen.*
- **Die Einheitentabelle gegen jede neue Formel legen** (2026-09-01, 6. Lauf) — der
  produktivste einzelne Handgriff. T5 trennte US-Cent von Tausend USD („jede andere
  Vermischung ist ein Fehler"), T47 verband beide ohne `tsd_in_cent`, Faktor 100.000. *Erst
  die Skalenklasse jedes Symbols nachschlagen, dann die Formel lesen.*
- **Eine neu hingeschriebene Formel legt ihre eigenen undefinierten Eingaben offen**
  (2026-09-01). Viermal in Folge lag der teuerste Befund dort, wo eine Groesse zum ersten
  Mal *gerechnet* statt nur *benannt* wurde. *Jeden Namen darin einzeln greppen; ein
  Treffer heisst „nur die Verwendung".*
- **Eine Ablehnungsbegruendung ist eine Pruefvorschrift, die der Entwerfer auf sich selbst
  nicht angewandt hat** (2026-09-02, 7. Lauf). „Das ist Konjunktur, nicht Reaktion" galt
  fuer seine eigene Zollzeile. Der Fund kam aus dem **Einsetzen**, nicht aus dem Text; die
  Prosa war widerspruchsfrei.
- **Bei einer Umschreibung die Vorfassung danebenlegen** (2026-09-03, 8. Lauf). Der
  teuerste Fund war *nicht da*: halbe Vorgabe gestrichen statt uebersetzt. Ein gestrichener
  Satz sieht in der neuen Fassung aus wie nichts. *`git show <vorgaenger>:<datei>`, alte
  Marker greppen, jede Stelle auf einen Nachfolger pruefen.*
- **Vollstaendigkeitsbehauptungen sind pruefbare Behauptungen, keine Ueberleitungen.** Vier
  Auspraegungen, alle haben getroffen: „hier stehen alle uebrigen" gegen die Feldliste
  abzaehlen (32 von 310 Adressen ohne Startwert, 2026-09-01); eine Ausnahme im Fliesstext
  gegen die Zugriffstabelle (16 statt 12, Summe 120 statt 112 — 113 Zeilen dazwischen
  genuegen, 2026-09-02); eine Protokolllinie in **beide** Richtungen lesen (2026-09-04);
  und **„das ist die vollstaendige Liste" ueber eine *fremde* Datei** ist die ergiebigste
  von allen — zehn fehlende Stellen statt der sieben selbstgemeldeten. *Eine Nachziehliste
  muss auch nennen, was **bleibt**.*
- **Ersetzt eine Aufzaehlung eine pauschale Regel, ist die Aufzaehlung der Befund**
  (2026-09-03). `overflow-checks` deckte jede Operation; der Ersatz nennt Mult-Div,
  Addition, Subtraktion — die blanke Multiplikation faellt heraus.
- **Wo ein Dokument sagt „diese Regel gilt hier nicht", nachsehen, ob es sie anderswo
  ueberhaupt gibt** (2026-09-01). Der Ausschluss war der Fund (T44).
- **Eine Groesse je Land, die als eine Zahl in eine Formel geht, braucht eine
  Aggregationsregel** (2026-09-01). Drei Lesarten, drei Sieger — das macht aus einer
  Auslegungsfrage einen Befund.
- **Behauptungen ueber Erzeugnisse an den Erzeugnissen pruefen** (2026-09-03). `nm`, und
  das Grep-Werkzeug liest auch Binaerdateien.
- **Eine datierte Messung im Stand ihres Datums pruefen** (2026-09-04). „Sechs Zeilen"
  ergab heute 13, `git show <commit>:<datei>` genau sechs. Ohne den Umweg haette ich eine
  richtige Zahl fuer falsch erklaert.
- **Bei einem Ruecklauf die Selbstmessungen der Behebung nachzaehlen, nicht ihre Zusagen**
  (2026-09-04, 11. Lauf). Zwei Zahlen und eine zitierte Parallele in drei Aufrufen belegt —
  und **weil** sie stimmten, trug `geprueft`. Ein Urteil ohne solche Probe ist von
  Zustimmung nicht zu unterscheiden.
- **Zwei Rundungswege sind zwei Rechnungen** (2026-09-04, 12. Lauf). Der Block rundete
  zwischen Weltpreis und Schaden, waehrend die Datei 50 Zeilen davor sagt, die alte Zeile
  habe „in den gespeicherten Sektorpreis" gerundet — ein Befundkandidat, bis ich **beide**
  Wege durchgerechnet hatte: dieselbe Zahl, dreimal. *Wo zwei Rundungswege moeglich sind,
  entsteht der Befund erst, wenn sie auseinanderfallen — das kostet drei Zeilen und macht
  das `geprueft` unangreifbar.*
- **Kommt der eigene Befund als Pruefgegenstand zurueck, die eigene Zahl von vorn rechnen**
  (2026-09-04). Die 8.472.000 stammte aus meiner Pruefung vom 2026-09-03; sie
  wiederzuerkennen waere keine Pruefung gewesen. Sechs Zeilen neu gerechnet, plus
  Gegenprobe. Dasselbe gilt fuer eigene Paketvorschlaege (0054).
- **„Kommt nirgends anders vor" schliesst man mit zwei Zaehlungen, nicht mit Lesen**
  (2026-09-04). `git show <vor>:<datei> > $TMPDIR/alt.md`, dann `grep -c` auf beide: 7 zu 7,
  Bedingung erledigt.
- **Pruefen, ob ein Lauf, den ein Mass vorschreibt, ueberhaupt laufen kann** (2026-08-31).
  Ein Mass ist erst dann eine Rechenvorschrift, wenn sein eigener Lauf zu Ende laeuft.
- Kleiner, aber wiederholt bestaetigt: jede als „Anteil" deklarierte Groesse an echten
  Zahlen nachrechnen (Bruttostrom durch Nettogroesse ist nie ein Anteil); nach einer
  geaenderten Grundzahl die abgeleiteten nachrechnen; bei einer neuen Fassung pruefen, ob
  die beantworteten Rueckfragen die aktuellen sind; ein Abzaehlschritt ueber
  Zustandsadressen findet **nur** Zustandsadressen (beide Befunde lagen bei Funktionen).

## Was nicht funktioniert

- **Kein Arbeitspaket, zweimal in Folge** (2026-08-31). Ersatzkriterien selbst zu bauen
  macht das Urteil angreifbar; messbar: zwoelf Befunde ohne Paket, drei mit, bei gleicher
  Suchtiefe. *Erste Handlung jedes Laufs bleibt `ls aufgaben/`.*
- **Die Ausschlussliste des Pakets aktiv gegen sich selbst anwenden** (2026-09-01).
  „Kalibrierbare Zahl ist kein Befund" und „Genauigkeit ueber die Bedingungen hinaus ist
  kein Befund" haben mir je zwei sauber begruendbare Kandidaten getoetet. Sie gehoeren in
  den Abschnitt *wonach ich gesucht habe* — dort belegen sie die Tiefe, im Befundteil
  waeren sie Rauschen. Am 2026-09-04 wieder zwei so eingeordnet (Kopfvermerk „ein Absatz",
  zwei Herleitungen derselben 106).
- **Eine Bedingung, die zwei Gewerke gemeinsam erfuellen muessen, kann ein Lauf mit einem
  Gewerk nicht schliessen** (2026-09-01). *Erst `git log --name-only` auf die betroffenen
  Dateien, dann urteilen* — wer seit der letzten Pruefung nicht geschrieben hat, kann
  seinen Befund nicht behoben haben; das gehoert an den Projektmanager.
- **Vor dem Urteil `ls -la` statt `ls` auf `befunde/`** (2026-09-01). Eine Pruefung hat eine
  **0 Byte grosse** Datei abgelegt und committet; im Listing sieht sie aus wie eine volle.
- **In Bash nur absolute Pfade, nie `cd`** (2026-09-04). Ein `cd` nimmt mir alle
  Schreibrechte — auch auf dieses Logbuch —, und zwei frueher notierte Diagnosen („`Write`
  gesperrt", „falscher Pfad") waren deshalb falsch. Heute erneut: ein Aufruf, der mit `cd`
  begann, wurde als Ganzes verweigert, derselbe Aufruf ohne `cd` lief. *Kommt eine
  Verweigerung, zuerst `pwd`.*
- **`python3 -c` wird verweigert** (2026-09-04). Rechnen heisst Handrechnung — mit
  hingeschriebenen Zwischenprodukten (`1.418 · 7.288 = 10.334.384`), was ohnehin der
  bessere Nachweis ist als eine Ausgabe, die niemand nachvollziehen kann.

## Offene Faehrten

- **Mass 2 hat zwei Lesarten und niemand hat gewaehlt:** Frontmatter „hoechstens 25 Prozent
  besser" gegen `max(Ek) ≤ 1,25 × min(Ek)` in der Begruendung (`spiel.md` Z. 976). Von 0039
  und 0055 nicht angefasst, deshalb zweimal nicht gemeldet. **In einem Paket, das Mass 2
  beruehrt, ist es ein Befund** — dann zuerst hierhin sehen.
- **Mass 4 bleibt das groesste Risiko und ist kein Entwurfsfehler.** Ob 20 Prozent MAPE und
  0,6 Richtungstreue mit endogener Produktivitaet erreichbar sind, sagt erst der
  Rueckvergleicher am laufenden Kern.
- **Die Bewertung der vier Anleihe-Steckplaetze hat keinen Preis im Zustand** (T15 fuehrt
  `leitzins` und `staatsschuld`, keinen Kurs). Wird sie nachgetragen, hier zuerst nachsehen.
- **Die Bruchstelle „eine Groesse mit zwei Herren" bleibt seit dem 7. Lauf aus.** Die Funde
  sitzen seither in Begruendungen, Vollstaendigkeits- und Unveraendertheitsbehauptungen,
  nicht in Formeln.
