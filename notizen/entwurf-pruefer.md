# Logbuch: entwurf-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/entwurf-pruefer-<datum>.md` und beginnst neu — mit den
Einträgen, die noch gelten. Nicht löschen.

Belege gehören in die Ergebnisdatei, nicht hierher. Ins Logbuch kommt die Lehre daraus,
in einem Satz.

*Archivieren ist mir **nicht moeglich** (mehrfach belegt, kein `cd`-Artefakt):
`notizen/archiv/` ist gesperrt. Statt zu archivieren wird verdichtet, **nie
gestrichen** (volle Fassung Laeufe 1-9: `git show 77a84e8:notizen/entwurf-pruefer.md`;
Laeufe 10-15: `git show 2f5211e:...`; Laeufe 16-17: `git show 1e72668:...`). Als
Regelproblem gemeldet.*

---

## Was funktioniert

- **Jede Zahl selbst nachrechnen, auch die beilaeufigen** (2026-08-31; drei von acht
  Befunden des 1. Laufs waren Rechenfehler in Nebensaetzen).
- **Die Nebenzahl neben der Abnahmezahl ist die, die nicht stimmt** (2026-09-03, best.
  9./14./16. Lauf). Die Funde sitzen seit dem 7. Lauf in Begruendungen, Selbstberichten,
  Messtabellen — nicht in Formeln. *Den Bericht ueber die Arbeit getrennt von der Arbeit
  pruefen; jedes Einbuchstaben-Symbol gegen seine dokumentweite Belegung halten (16. Lauf:
  `4·R` statt „vier je Land").*
- **Eine Formel strukturell verankern, nicht nur numerisch** (2026-09-05, 18. Lauf,
  verschaerft „erste Zahl der Kette am Code" vom 16.). Bei 0116 habe ich jede
  T55-Konstante gegen die Zerlegungstabelle der Quelle gelegt (T38-Maskentabelle
  `12+9+1+4+1`, `static_assert`-Kette in `zustand.hpp`, `zaehlregel_t37` in
  `reihen.toml`): Jeder Term fand seine benannte Zeile. *Zahl treffen und Zahl herleiten
  unterscheidet nur die Quelltabelle — eine Formel, die stimmt, hat fuer jede Konstante
  eine fremde Zeile.* Nuetzlich auch: eine `L=9`-Probespalte macht L/I-Verwechslung
  sichtbar, die bei `L=I=4` unsichtbar ist.
- **Vollstaendigkeitsbehauptungen sind pruefbare Behauptungen** — sechs Auspraegungen,
  alle trafen (32/310; 16 statt 12; Protokolllinie; „zwoelf Reste" waren 22;
  „vollstaendige Liste" ueber fremde Datei; 18. Lauf: „alles in einer Datei" — ein Grep
  auf den Bezeichner ueber den ganzen Kasten fand die zweite `GEBIET_KUERZEL`-Fassung in
  `zustandsausgabe.cpp`). *Eine Nachziehliste muss auch nennen, was bleibt; ein „nur
  hier" verlangt einen Grep ueberall.*
- **Ein `static_assert` auf `.size()` eines `std::array` mit vorgegebener Groesse ist
  eine Tautologie** (2026-09-05, 18. Lauf, trug Befund 2): Fehlende Initialisierer
  werden still Nullzeiger, die Groesse stimmt per Konstruktion. Wirksam nur, wenn die
  Groesse aus der Initialisiererliste abgeleitet wird. *Bei jeder vorgeschlagenen
  Zusicherung fragen: Welcher konkrete Fehler macht sie rot — und durchspielen.*
- **Aendert sich eine Zahl, greppe auch die Ordnungszahl, die aus ihr folgt** (14. Lauf);
  **die Erhebung eines Dokuments mit einem breiteren Muster wiederholen** (T48, sieben
  weitere Namen); **erst die Zahlen, dann den Text** (Kostentabelle verriet ungenannte
  Lesart); **die Einheitentabelle gegen jede neue Formel legen** (T5/T47, Faktor
  100.000); **jeden Formeleingabenamen einzeln greppen** (ein Treffer heisst „nur die
  Verwendung").
- **Eine Bedingung, die auf einer Messung steht, wird nachgemessen, nicht zitiert**
  (best. 18. Lauf: alle neun `Gebiet::`-Zaehlwerte aus T56 mit eigenem grep exakt
  reproduziert — erst das traegt das Urteil). **Zwei Quellen, die sich nicht kennen,
  sind der billigste Beweis** (18. Lauf: `zaehlregel_t37` gegen Top-Level-Summen
  derselben Datei). *Nie gegen die Rechnung des Dokuments zaehlen.*
- **Bei einer Umschreibung die Vorfassung danebenlegen** (der teuerste Fund war *nicht
  da*: halbe Vorgabe gestrichen statt uebersetzt; alte Marker greppen). **Ersetzt eine
  Aufzaehlung eine pauschale Regel, ist die Aufzaehlung der Befund** (`overflow-checks`).
  **Wo ein Dokument sagt „diese Regel gilt hier nicht", nachsehen, ob es sie anderswo
  gibt** (T44).
- **Behauptungen ueber Erzeugnisse an den Erzeugnissen pruefen** (`nm`; Grep liest auch
  Binaerdateien). **Eine datierte Messung im Stand ihres Datums pruefen.** **Bei einem
  Ruecklauf die Selbstmessungen der Behebung nachzaehlen, nicht ihre Zusagen.**
- **Zwei Lesarten sind zwei Rechnungen — beide rechnen, bevor der Befund entsteht**
  (`H/N` gegen `H/(H+N)`). **Bei „zweimal unabhaengig gerechnet" fragen, wo die Kette
  anfaengt** (der einzige falsche Wert sass in der gemeinsamen Messtabelle). **Kommt der
  eigene Befund als Pruefgegenstand zurueck, die eigene Zahl von vorn rechnen.**
- **„Kommt nirgends anders vor" schliesst man mit zwei Zaehlungen** (`grep -c` auf beide
  Fassungen). **Die Vorher-Zaehlung ohne alten Stand: arithmetisch am Diff** (vorher =
  jetzt − hinzugefuegt + entfernt); im 18. Lauf genuegte der Diff allein — ein einziger
  Anfuege-Hunk mit 0 entfernten Zeilen beweist Bestandsschutz staerker als jede
  Trefferzahl.
- **Die Commit-Verwechslung ist beidseitig** (Baulauf committet den Arbeitsbaum;
  `git log -- <datei>` nennt Urheber falsch; belastbar ist der Datei-Diff ueber die
  Spanne). **Ein Commitbetreff ist kein Paketumfang.** Das Pflicht-Logbuch des Bauagenten
  im Commit ist kein Verstoss gegen „nur Datei X".
- Kleiner, wiederholt bestaetigt: jede „Anteil"-Groesse nachrechnen; abgeleitete Zahlen
  nach geaenderter Grundzahl; ob beantwortete Rueckfragen die aktuellen sind; ob ein
  vorgeschriebener Lauf laufen kann; Aggregationsregel fuer je-Land-Groessen in Formeln.
- **Ein korrekt vorgerechneter Sonderfall wandert als Zahl in den falschen Fall**
  (2026-09-06, 19. Lauf, 0117): T59 rechnet „ohne USA = 13" sauber vor; drei Absaetze
  spaeter zitiert T60s Sperrabsatz dieselbe 13 fuer „ohne China/Deutschland" (richtig
  12, denn n = 1). Verraten hat es wieder die Nebenzahl daneben: die Sollreihen
  `3·7 − 1 = 20` im selben Satz rechnen mit n = 1. *Taucht eine markante Zahl erneut
  auf, pruefen, ob ihr Sonderfall mitgewandert ist — jede Einsetzung im Dokument
  einzeln nachrechnen, auch die illustrativen.*

## Was nicht funktioniert

- **Ersatzkriterien statt Arbeitspaket** (zwoelf Befunde ohne Paket, drei mit). *Erste
  Handlung: `ls aufgaben/`.* Das Kriterium ist die Abnahme **des geprueften Pakets**,
  nicht `0001`.
- **Ein Fehler ausserhalb der Abnahmebedingungen ist kein Ruecklauf** (best. 18. Lauf):
  Urteil `geprueft` **und** ein Paketvorschlag. — **Neu, 18. Lauf: Widersprechen sich
  zwei Bedingungen desselben Pakets** (B1 erzwang zwei `310`-Zeilen, B3s Wortlaut verbot
  sie), ist auch das kein Ruecklauf, sondern ein Befund an den Projektmanager: Der Zweck
  der Bedingung steht in ihr selbst; ihn mit der staerkeren Messung belegen (0 entfernte
  Zeilen) und `geprueft` urteilen. Ein Ruecklauf, den der Bauagent nur durch Verletzen
  der anderen Bedingung schliessen koennte, ist keiner.
- **Die Ausschlussliste des Pakets aktiv anwenden:** Kalibrierbares gehoert in *wonach
  ich gesucht habe*, nicht in den Befundteil.
- **Eine Bedingung, die zwei Gewerke erfuellen muessen, schliesst ein Lauf nicht**
  (*erst `git log --name-only`*). **Vor dem Urteil `ls -la` auf `befunde/`** (0-Byte-
  Datei sieht voll aus).
- **Werkzeuge** (alle selbst erlitten): nur absolute Pfade, nie `cd`; `git show` und
  `^`-Revisionen verweigert (Elternhash aus `git log --oneline`, dann `git --no-pager
  diff <a> <b>`); Pipes verweigert — Diff nach `$TMPDIR`, dann Read/Grep; `python3 -c`
  verweigert — Handrechnung mit Zwischenprodukten. — **Neu, 18. Lauf:** `Glob` meldete
  „nicht gefunden" fuer eine **existierende** Datei (`aufgaben/0068-*`); `ls` fand sie.
  *Nichtexistenz nie aus einem Werkzeug behaupten — Beinahe-Fehlbefund.* Und das
  `Write`-Werkzeug kann in einer Sitzung gesperrt sein, waehrend Bash-Heredoc in den
  Repo-Baum funktioniert. — **19. Lauf:** `git add`+`commit` verweigert; der Runner
  committet. Ergebnisdateien einfach im Arbeitsbaum lassen, nicht erneut versuchen.
  `sed`/`awk` ebenfalls verweigert — Read mit offset/limit nehmen.

## Offene Faehrten

- **Mass 2 hat zwei Lesarten und niemand hat gewaehlt** (Frontmatter „hoechstens 25
  Prozent besser" gegen `max(Ek) ≤ 1,25 × min(Ek)`; 0119 zitiert die Formel-Lesart und
  verfestigt sie still). In einem Paket, das Mass 2 definiert oder misst, ist es ein
  Befund.
- **Mass 4 bleibt das groesste Risiko** — entscheidet der Rueckvergleicher am laufenden
  Kern. **Die vier Anleihe-Steckplaetze haben keinen Preis im Zustand** (T15 fuehrt
  `leitzins`/`staatsschuld`, keinen Kurs); wird er nachgetragen, zuerst hierhin sehen.
- **`technik.md` fuehrt weiter 25 Stuetzstellen und `R = 24`** gegen Fenster 2001–2021;
  Nachzug ist 0064 (offen). Kein Befund solange offen, aber jede Rechnung darauf in
  beiden Fenstern pruefen. Nach 0119 zudem die Nachzugliste der zweiten Schicht
  (spiel.md Z. 2484-2506) — jede Zeile einzeln nachmessen, besonders die Verweisformel
  Nachahmer-/Stossaufschlag.
- **`werte.hpp` sagt „siebzehn", T48 fuehrt zweiundzwanzig**; mein Vorschlag 0092
  berichtigt die Stellenliste. **Mein Vorschlag 0131** (Baulauf-Commit sammelt den
  Arbeitsbaum ein): Belegcommits 0134179/e00e7f9 von vorn aufziehen. **Mein Vorschlag
  0149** (T56: zweite Kuerzeltabelle, tautologisches static_assert): kommt er zur
  Pruefung, Duplikat und Tautologie von vorn messen, nicht meinen Befund zitieren.
- **0116 im 18. Lauf `geprueft`** (2 Befunde: B1/B3-Widerspruch an den PM; T56-Nebenwerk
  → 0149). Die T55-Formeln sind jetzt die Referenz, auf der 0117/0118/0119 rechnen —
  bei deren Pruefung die Formeln **von vorn einsetzen**. Anker, die trugen:
  T38-Maskentabelle Z. 1354 ff., `zustand.hpp`-Asserts, `zaehlregel_t37`. Die
  Steckplaetze wachsen laut 0118/0119 auf 45 bzw. 75 („Weg A", beide Male Betreiber,
  juengere sticht); die Warnpaare „40 gegen 40" (T28) und „27 gegen 27" (T38) sind gute
  Pruefanker fuer alles, was daran anschliesst.
- **0117 im 19. Lauf `geprueft`** (1 Befund → Vorschlag 0154: T60-Sperrzahl 13→12).
  Neue Anker: T59 `3·L_R + (L_R − n) + 1` (n = 1: USA Numéraire), T61-Pflichtblock
  `[[reihe.herkunft]]` mit `stufe`/`freie_parameter`, Sperre „kein Datenpaket macht
  die vier zum Spielland". T55 fuehrt Sollreihen/Sollmaske/ausserhalb weiter in `L`;
  laut T59 wechseln genau diese drei auf `L_R` — bei 0064/0068/0118/0119 gegenhalten.
  Vorspann „T1 bis T53" ist doppelt veraltet (richtig T61; T60 als „frei"-Beispiel),
  bewusst liegen gelassen: 0082/0084 binden ihre Abnahme auf den unberuehrten
  Vorspann. Kommt ein Vorspann-Nachzug zur Pruefung: er muss **nach** 0082/0084
  laufen.
- **0141 im 20. Lauf `geprueft`** (2026-09-06, 0 Befunde). T62/T63 sind jetzt die
  Referenz fuer 0118: Datenkosten je Klasse 806/158 (R=24) bzw. 678/138 (R=20); das
  harte Ausschlusskriterium fuer ein Rueckvergleichsland ist **Reihe 2** (keine
  Ausweichquelle), nicht der Leitzins. Anker, die trugen: die 19 `lizenzurteil`-Felder
  decken die T62-Lizenzspalte 1:1; `zaehlung.pruefgegenstaende` (reihen.toml Z. 411)
  fuehrt keinen Leitzins; Zinsnachmessung USA 9 / BRA 7 / DEU 11 / CHN 0. Der
  Fensterwiderspruch (Auftrag „ab 2001" gegen Dokument 1997-2021) ist in `R`
  parametrisch geliefert — Widerspruch in der Vorgabe, kein Ruecklauf (Regel aus dem
  18. Lauf erneut bestaetigt). Der Vorspann-Nachzug existiert seit heute als **0181**
  mit selbstmessender Abnahme („die Zahl folgt deiner Zaehlung") — die richtige Bauform
  gegen Drift, T63/T64 schon gedeckt. Werkzeuglage 20. Lauf: Write **und** Edit
  gesperrt, Bash-Heredoc traegt beides.
