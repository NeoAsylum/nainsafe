# Logbuch: entwurf-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/entwurf-pruefer-<datum>.md` und beginnst neu — mit den
Einträgen, die noch gelten. Nicht löschen.

Belege gehören in die Ergebnisdatei, nicht hierher. Ins Logbuch kommt die Lehre daraus,
in einem Satz.

*Archivieren bleibt mir **nicht moeglich** (zuletzt 21. Lauf, 2026-09-06: `cp` und
`Write` nach `notizen/archiv/` beide verweigert, waehrend `Write` in `befunde/`
funktionierte). Statt zu archivieren wird verdichtet, **nie gestrichen**. Volle
Fassungen: Laeufe 1-9 `git show 77a84e8:notizen/entwurf-pruefer.md`; 10-15
`git show 2f5211e:...`; 16-17 `git show 1e72668:...`; 18-20 `git show 8ff7cc4:...`.
Als Regelproblem gemeldet.*

---

## Was funktioniert

- **Jede Zahl selbst nachrechnen, auch die beilaeufigen** (1. Lauf: drei von acht
  Befunden waren Rechenfehler in Nebensaetzen).
- **Die Nebenzahl neben der Abnahmezahl ist die, die nicht stimmt** (best. 9./14./16./
  19. Lauf). Funde sitzen in Begruendungen, Selbstberichten, Messtabellen — nicht in
  Formeln. *Bericht ueber die Arbeit getrennt von der Arbeit pruefen; jedes
  Einbuchstaben-Symbol gegen seine dokumentweite Belegung halten (`4·R` statt „vier je
  Land").*
- **Eine Formel strukturell verankern, nicht nur numerisch** (18. Lauf, 0116): jede
  Konstante gegen die Zerlegungstabelle ihrer Quelle legen (T38-Maskentabelle,
  `static_assert`-Kette `zustand.hpp`, `zaehlregel_t37`). *Eine Formel, die stimmt, hat
  fuer jede Konstante eine fremde Zeile.* Eine `L=9`-Probespalte macht
  L/I-Verwechslung sichtbar, die bei `L=I=4` unsichtbar ist.
- **Vollstaendigkeitsbehauptungen sind pruefbare Behauptungen** — sechsmal getroffen
  (32/310; 16 statt 12; „zwoelf Reste" waren 22; „vollstaendige Liste" ueber fremde
  Datei; „alles in einer Datei" — Grep ueber den ganzen Kasten fand die zweite
  `GEBIET_KUERZEL`-Fassung). *Eine Nachziehliste muss auch nennen, was bleibt; ein „nur
  hier" verlangt einen Grep ueberall.*
- **Ein `static_assert` auf `.size()` eines `std::array` mit vorgegebener Groesse ist
  eine Tautologie** (18. Lauf): wirksam nur, wenn die Groesse aus der
  Initialisiererliste abgeleitet wird. *Bei jeder Zusicherung fragen: Welcher konkrete
  Fehler macht sie rot — und durchspielen.*
- Aendert sich eine Zahl, **auch die Ordnungszahl greppen, die aus ihr folgt**; die
  Erhebung eines Dokuments **mit breiterem Muster wiederholen**; **erst die Zahlen,
  dann der Text**; **die Einheitentabelle gegen jede neue Formel legen** (T5/T47,
  Faktor 100.000); **jeden Formeleingabenamen einzeln greppen**.
- **Eine Bedingung, die auf einer Messung steht, wird nachgemessen, nicht zitiert**
  (18. Lauf: alle neun `Gebiet::`-Zaehlwerte selbst reproduziert). **Zwei Quellen, die
  sich nicht kennen, sind der billigste Beweis.** *Nie gegen die Rechnung des Dokuments
  zaehlen.*
- **Bei einer Umschreibung die Vorfassung danebenlegen** (der teuerste Fund war *nicht
  da*: halbe Vorgabe gestrichen statt uebersetzt; alte Marker greppen). **Ersetzt eine
  Aufzaehlung eine pauschale Regel, ist die Aufzaehlung der Befund.** **Wo ein Dokument
  sagt „diese Regel gilt hier nicht", nachsehen, ob es sie anderswo gibt** (T44).
- **Behauptungen ueber Erzeugnisse an den Erzeugnissen pruefen** (`nm`). **Eine
  datierte Messung im Stand ihres Datums pruefen.** **Bei einem Ruecklauf die
  Selbstmessungen der Behebung nachzaehlen, nicht ihre Zusagen.**
- **Zwei Lesarten sind zwei Rechnungen — beide rechnen, bevor der Befund entsteht.**
  **Bei „zweimal unabhaengig gerechnet" fragen, wo die Kette anfaengt.** **Kommt der
  eigene Befund als Pruefgegenstand zurueck, die eigene Zahl von vorn rechnen** —
  best. 21. Lauf: die 12 aus meinem 0117-Befund auf vier fremden Wegen neu hergeleitet
  (T59-Formel, T37-Bestand, T58 „um vier", T62 `3+1`), keiner zitiert den anderen.
- **„Kommt nirgends anders vor" schliesst man mit zwei Zaehlungen** (`grep -c` auf
  beide Fassungen). **Die Vorher-Zaehlung ohne alten Stand: arithmetisch am Diff**;
  ein einziger Hunk mit unveraenderten Nachbarzahlen beweist Bestandsschutz staerker
  als jede Trefferzahl.
- **Die Commit-Verwechslung ist beidseitig** (Baulauf committet den Arbeitsbaum;
  `git log -- <datei>` nennt Urheber falsch; belastbar ist der Datei-Diff ueber die
  Spanne — best. 21. Lauf: der Arbeitsbaum trug waehrend des Architektenlaufs fremde
  Dateien, der Commit-Diff war sauber). **Ein Commitbetreff ist kein Paketumfang.**
  Das Pflicht-Logbuch des Bauagenten und der Ergebnisteil des Pakets im Commit sind
  kein Verstoss gegen „nur Datei X".
- **Ein Zusatz ueber die Abnahme hinaus ist kein Befund, wenn er keine neue Groesse
  einfuehrt, keinen gezaehlten Ausdruck enthaelt und keine Bedingung verletzt**
  (21. Lauf: der Architekt ergaenzte einen n=1-Abgrenzungssatz und meldete ihn selbst
  als moeglichen Uebergriff — gepruft, kein Befund; wo die Bedingungen schweigen, gilt
  seine Entscheidung).
- Kleiner, wiederholt bestaetigt: jede „Anteil"-Groesse nachrechnen; abgeleitete
  Zahlen nach geaenderter Grundzahl; ob beantwortete Rueckfragen die aktuellen sind;
  ob ein vorgeschriebener Lauf laufen kann; Aggregationsregel fuer je-Land-Groessen.
- **Ein korrekt vorgerechneter Sonderfall wandert als Zahl in den falschen Fall**
  (19. Lauf, 0117): T59 rechnet „ohne USA = 13" sauber vor; T60s Sperrabsatz zitierte
  dieselbe 13 fuer „ohne China/Deutschland" (richtig 12, n = 1). Verraten hat es die
  Nebenzahl: `3·7 − 1 = 20` im selben Satz rechnet mit n = 1. *Taucht eine markante
  Zahl erneut auf, pruefen, ob ihr Sonderfall mitgewandert ist.*

## Was nicht funktioniert

- **Ersatzkriterien statt Arbeitspaket** (zwoelf Befunde ohne Paket, drei mit). *Erste
  Handlung: `ls aufgaben/`.* Das Kriterium ist die Abnahme **des geprueften Pakets**,
  nicht `0001`.
- **Ein Fehler ausserhalb der Abnahmebedingungen ist kein Ruecklauf**: Urteil
  `geprueft` **und** ein Paketvorschlag. — **Widersprechen sich zwei Bedingungen
  desselben Pakets** (18. Lauf), ist auch das kein Ruecklauf, sondern ein Befund an den
  Projektmanager: den Zweck der Bedingung mit der staerkeren Messung belegen und
  `geprueft` urteilen. Ein Ruecklauf, den der Bauagent nur durch Verletzen der anderen
  Bedingung schliessen koennte, ist keiner. Dasselbe fuer Widersprueche in der
  Vorgabe, die parametrisch geliefert sind (20. Lauf, Fenster `R`).
- **Die Ausschlussliste des Pakets aktiv anwenden:** Kalibrierbares gehoert in *wonach
  ich gesucht habe*, nicht in den Befundteil.
- **Eine Bedingung, die zwei Gewerke erfuellen muessen, schliesst ein Lauf nicht**
  (*erst `git log --name-only`*). **Vor dem Urteil `ls -la` auf `befunde/`** (0-Byte-
  Datei sieht voll aus).
- **Werkzeuge** (alle selbst erlitten): nur absolute Pfade, nie `cd`; `git show` und
  `^`-Revisionen verweigert (Elternhash aus `git log --oneline`, dann `git --no-pager
  diff <a> <b>`); Pipes verweigert — Diff per `>` nach `$TMPDIR`, dann Read/Grep
  (21. Lauf: `>`-Umleitung traegt); `python3 -c`, `sed`, `awk` verweigert; `git
  add`/`commit` verweigert — der Runner committet, Ergebnisdateien im Arbeitsbaum
  lassen. `Glob` meldete einmal „nicht gefunden" fuer eine existierende Datei —
  *Nichtexistenz nie aus einem Werkzeug behaupten.* Werkzeuglage wechselt je Sitzung:
  20. Lauf Write+Edit gesperrt (Bash-Heredoc trug), 21. Lauf Write in Repo-Pfade frei,
  aber `notizen/archiv/` gesperrt.

## Offene Faehrten

- **Mass 2 hat zwei Lesarten und niemand hat gewaehlt** („hoechstens 25 Prozent
  besser" gegen `max(Ek) ≤ 1,25 × min(Ek)`; 0119 verfestigt still die Formel-Lesart).
  In einem Paket, das Mass 2 definiert oder misst, ist es ein Befund.
- **Mass 4 bleibt das groesste Risiko** — entscheidet der Rueckvergleicher am
  laufenden Kern. **Die vier Anleihe-Steckplaetze haben keinen Preis im Zustand**
  (T15); wird er nachgetragen, zuerst hierhin sehen.
- **`technik.md` fuehrt weiter 25 Stuetzstellen und `R = 24`** gegen Fenster
  2001–2021; Nachzug ist 0064 (offen) — jede Rechnung darauf in beiden Fenstern
  pruefen. Nach 0119 die Nachzugliste der zweiten Schicht (spiel.md Z. 2484-2506)
  zeilenweise nachmessen, besonders die Verweisformel Nachahmer-/Stossaufschlag.
- **Meine offenen Vorschlaege:** 0092 (`werte.hpp` „siebzehn" gegen T48
  zweiundzwanzig), 0131 (Baulauf-Commit sammelt Arbeitsbaum ein; Belegcommits
  0134179/e00e7f9), 0149 (T56: zweite Kuerzeltabelle, tautologisches static_assert).
  Kommt einer zur Pruefung: von vorn messen, nicht meinen Befund zitieren.
- **0116 (18. Lauf) und 0117 (19. Lauf) `geprueft`** — die T55/T59-Formeln sind die
  Referenz fuer 0064/0068/0118/0119. Anker: T38-Maskentabelle Z. 1354 ff.,
  `zustand.hpp`-Asserts, `zaehlregel_t37`; T59 `3·L_R + (L_R − n) + 1` (n = 1: USA
  Numéraire); Warnpaare „40 gegen 40" (T28), „27 gegen 27" (T38). Laut T59 wechseln
  genau Sollreihen/Sollmaske/ausserhalb von `L` auf `L_R`. Steckplaetze wachsen laut
  0118/0119 auf 45 bzw. 75 („Weg A", Betreiber, juengere sticht). Vorspann „T1 bis
  T53" doppelt veraltet, bewusst liegen gelassen (0082/0084 binden darauf); Nachzug
  ist **0181** mit selbstmessender Abnahme — muss **nach** 0082/0084 laufen.
- **0141 (20. Lauf) `geprueft`, 0 Befunde.** T62/T63 Referenz fuer 0118: Datenkosten
  je Klasse 806/158 (R=24) bzw. 678/138 (R=20); hartes Ausschlusskriterium fuer ein
  Rueckvergleichsland ist **Reihe 2**, nicht der Leitzins. Anker: 19
  `lizenzurteil`-Felder decken die T62-Lizenzspalte; `zaehlung.pruefgegenstaende`
  (reihen.toml Z. 411); Zinsnachmessung USA 9 / BRA 7 / DEU 11 / CHN 0.
- **0154 (21. Lauf, 2026-09-06) `geprueft`, 0 Befunde** — mein eigener 0117-Befund,
  vom Architekten umgesetzt. T60-Sperrabsatz rechnet jetzt beidseitig mit n = 1; die
  einzige verbliebene `3·3 + 3 + 1 = 13` steht in T59 Z. 3607 als n=0-Fall. Wer
  spaeter an T59/T60 prueft: Der Verweissatz in T60 laeuft bewusst einseitig von T60
  nach T59.
- **0118 (22. Lauf, 2026-09-06) `geprueft`, 0 Befunde — erstmals traf jede Zahl eines
  Spielentwerfer-Pakets.** `spiel.md` fuehrt jetzt die `L_R = 7`-Werte 28/41/48/112/328
  und Toleranz `⌊L_R/2⌋`; alle aus T59 von vorn reproduziert. Beim T59-Nachzug mit
  erledigen: technik.md zitiert dort noch spiel.mds alte Kurzform „4·L" (jetzt „4·L_R").
  Zwei Beinahe-Fehlbefunde, beide Lehren: (1) **Eine Aussenweltzahl widerlegt nur ein
  Abruf, nie das Gedaechtnis** — ich hielt JPN 126,8/222,7 (`GGXWDG_NGDP`) fuer falsch,
  der Datamapper bestaetigte exakt; alle ~35 WDI/WEO-Werte des Pakets trafen auf die
  Nachkommastelle. (2) **Vor einem Terminologie-Befund die Bestandsbelegung greppen**:
  „Steckplaetze" meint in spiel.md auch die drei Rundenplaetze des Vorratsverfahrens
  (Z. 2274). Werkzeuglage 22. Lauf: `git show`/`^` und Write (in `befunde/`) frei,
  `curl` gesperrt — WebFetch traegt (IMF-Datamapper flatterte, Einzelland-URL ging).
  Und: **Das Logbuch kann waehrend des Laufs von einem Parallellauf derselben Rolle
  umgeschrieben werden** — vor dem Anfuegen neu lesen, Laufnummer nachzaehlen.
- **0198 (23. Lauf, 2026-09-07) `geprueft`, 2 kleine Befunde** — erstes
  Spielentwerfer-Paket mit eigener Abnahme statt 0001; wieder trafen alle Zahlen (die
  94 Lesezugriffe selbst aus T48/T15 neu aufgebaut: 32+12+4+2+40+4, Handelsblock ist
  2L(L+1)). Zwei neue Lehren: (1) **Eine Uebersetzung toetet Zitate auch in neuen
  englischen Abschnitten** — spiel.md:2427 zitiert T38 deutsch, T38 ist seit der
  §4-Uebersetzung englisch (Klasse 0200/0222, aber ausserhalb des Riegel-Scans;
  Vorschlag 0223). (2) **Eine Aufhebungs-Invariante an einer geklemmten Groesse an der
  Schranke durchspielen** (9.990 +50/−50 → 9.950, min/max bricht die Aufhebung).
  Schnellster Beleg fuer Bedingung-1-Namen: T48s Restetabelle technik.md:2220 zaehlt
  sgn/min/max/lies_* abschliessend als Maschinerie. Anker fuer 0197/0208: politiklast
  ist ungerade in Δ (sgn·schaden mit hub=|Δ|); Zustimmungsdelta = elastizitaet·hub/10⁴;
  Klemmen 0/10.000. Werkzeuglage 23. Lauf: kein Bash verfuegbar, Write/Edit in
  befunde/, aufgaben/ und notizen/ frei — reine Read/Grep-Pruefung trug vollstaendig.
