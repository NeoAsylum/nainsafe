# Logbuch: portfolio-manager

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Höchstens 12.000 Zeichen (`wc -c`).

---

## Was funktioniert

- 2026-08-29 — **Erst `anwalt.md` lesen, dann zählen — und nur die Frontmatter-Zeilen
  `entkraeftet/loesbar/teuer/unloesbar` zählen.** Der Anwalt hat das Urteil je Linse
  bereits gefällt; die fünf Angriffsdateien musste ich in diesem Lauf gar nicht öffnen.
  Das spart drei Viertel der Lesezeit. Nachlesen lohnt nur, wenn der Anwalt eine Linse
  auf `loesbar` dreht — dort ist die Begründung die eigentliche Entscheidung.
- 2026-08-29 — **Die Anschlusszuschnitte gegen `ideas/*.md` prüfen, bevor man sie
  weiterreicht.** Alle drei „Andere Idee daraus" dieser Woche waren bereits ausgearbeitet
  und gestorben (0006, 0014, 0015) oder vom Ideator vorab widerlegt. Hätte ich sie
  ungeprüft ins Portfolio kopiert, hätte der Ideator dreimal dasselbe Nichts gefunden.
  Suchmuster: `ablehnungsgrund`-Zeilen aller Ideen am Stück lesen, dazu `notizen/ideator.md`.
- 2026-08-29 — **Die Logbücher der Rollen sind die bessere Quelle für Lehren als die
  Ablehnungsgründe.** Die Ablehnung sagt, woran eine Idee starb; das Logbuch sagt, welches
  Suchmuster es herausgefunden hat. Für „Folgerung für Rolle X" brauche ich Letzteres.
- 2026-08-29 — `ops/auslastung.md` beantwortet die Kostenfrage vollständig. Nicht selbst
  im Journal zählen; die Datei war aktuell (erzeugt am Lauftag).
- 2026-08-30 — **`grep -rn "Portfolio-Manager" notizen/` ist der billigste Einstieg in
  die Betreibermeldungen.** Ideator und Rechercheur adressieren mich wörtlich („Das gehört
  an den Portfolio-Manager", „Vorschlag für den Portfolio-Manager (ich darf ihn nicht
  selbst umsetzen)"). Beide Punkte dieses Laufs — Zuschnitt der Scouts, 90-Tage-Regel für
  Ausstiegssignale — standen fertig formuliert da. Die Rollen wissen, was falsch läuft;
  sie dürfen es nur nicht ändern.
- 2026-08-30 — **In einem Lauf ohne Kandidaten liegt der ganze Ertrag in `lehren.md`.**
  Reichte: `ops/auslastung.md`, die Frontmatter aller Ideen, die drei Zeilen
  `potenzial`/`preis_plausibel`/`kunden_erreichbar` der neuen Marktprofile und vier
  Logbücher (ideator, markt-analyst, rechercheur, fit-filter). Keine Angriffsdatei, kein
  Signal im Volltext.
- 2026-08-30 — **Eine Lehre wird stärker, wenn zwei Logbücher sie unabhängig melden.**
  Preisboden null und „der Verband ist der Wettbewerber" standen je bei Ideator *und*
  Markt-Analyst. Das ist der beste Filter gegen Einzelfälle, den ich habe — besser als
  die Zahl der betroffenen Ideen.

## Was nicht funktioniert

- 2026-08-29 — **`agents/repo.py` hat keinen CLI-Einstieg**, nur importierbare Funktionen
  (`bereit_zur_bewertung()`, `angriffe()`). `python3 agents/repo.py status` gibt nichts
  aus. Nächstes Mal direkt die Frontmatter der Ideen greppen, das kostet einen Aufruf.
- 2026-08-29, **am 2026-08-30 zur Hälfte widerlegt** — Ich hatte notiert, zusammengesetzte
  Bash-Befehle würden verweigert. `cmd && cmd` und `cmd; cmd` liefen heute problemlos;
  verweigert wurde nur die `for`-Schleife über Dateien. Ersatz dafür ist das Grep-Werkzeug
  mit `output_mode: content` — es liest die Frontmatter aller Ideen in einem Aufruf.
- 2026-08-29, **erledigt** — `notizen/rechercheur.md` war mit ~92.000 Tokens nicht am Stück
  lesbar. Nach der Rotation am 2026-08-29 sind es 7.582 Zeichen; der Vorschlag des
  Verbesserers (Zeichen statt Zeilen messen) ist in `CLAUDE.md` umgesetzt und wirkt.
- 2026-08-30 — **`lehren.md` wächst schneller, als die 60-Tage-Prüfung sie leert**: 9.608 →
  13.394 Zeichen in einem Lauf, danach auf 12.977 zusammengezogen. Für diese Datei gilt
  keine Grenze, aber *alle* Rollen lesen sie zu Beginn jedes Laufs — sie ist die Datei mit
  der größten Verdünnungswirkung im Repo. Nächstes Mal: neue Befunde zuerst als
  *Erweiterung* an einen bestehenden Eintrag hängen, statt einen sechsten anzulegen. Das
  hat hier bei vier von fünf funktioniert.

## Offene Faehrten

- 2026-08-29, **am 2026-08-30 präzisiert** — „Der Trichter ist leer, nicht verstopft"
  stimmt, war aber zu freundlich. `signals/` *ist* gewachsen (fünf neue Signale am
  2026-08-30), und trotzdem kam nichts durch: Jeder Verfasser hat sein eigenes Signal
  gleich mit erledigt. Der Zufluss fehlt nicht, er ist **strukturell negativ**. Beim
  nächsten Lauf nicht zählen, ob `signals/` gewachsen ist, sondern ob ein Signal ohne
  eigenes Todesurteil dabei ist — `grep -L 'gering\|rot' signals/*/2026-*.md`.
- 2026-08-30 — **Das Promille aus G7 ist die schärfste offene Frage, die ich nicht
  entscheiden darf.** Die Regel gibt ein Promille für den Fall vor, dass *kein* Kanal
  belegt ist; alle drei neuen Marktprofile benennen einen Kanal und rechnen trotzdem so.
  Faktor zehn auf jede Marge. Steht als Meldung 3 im Portfolio. Beim nächsten Lauf prüfen,
  ob der Betreiber geantwortet hat — sonst rechnet die Fabrik weiter gegen sich selbst.
- 2026-08-29 — Ungeprüft geblieben: ob die Score-Summen überhaupt noch etwas taugen. Alle
  drei Kandidaten lagen bei 16 bis 18 Punkten und starben trotzdem eindeutig; der
  bestbewertete (0012, 18) starb am klarsten. Die Punkte kommen vor der Prüfung, die
  Einwände danach — beim nächsten Mal beobachten, ob die Reihenfolge je stimmt.
- 2026-08-29 — Für einen künftigen Lauf zu klären: Was passiert mit einer `widerlegt`-Idee,
  wenn ihr Widerlegungsgrund selbst veraltet? 0012 hängt an einem Verordnungstext, 0009 an
  einem Wettbewerberpreis. Beides kann sich ändern; ein Wiedervorlagedatum kennt das
  Statusmodell nicht.
