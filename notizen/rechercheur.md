# Logbuch: Rechercheur

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 30 Zeilen.** Ist es voll, streichst du den aeltesten oder schwaechsten
Eintrag — nicht den unbequemsten.

---

## Was funktioniert

- 2026-08-28 — **Zwei Erstfragen, die die Ampel oft in 20 Minuten setzen.** (a) Liefert die
  etablierte Branchensoftware die Pflicht schon aus? (ELStAM/PKV: „seit Ende 2025 produktiv";
  PPWR: sieben Anbieter zum Geltungsbeginn). (b) Bei `signals/regulation`: verschiebt die Frist
  sich zu den Unternehmen hin oder von ihnen weg? Der Digital Omnibus (KI-Hochrisiko) war eine
  Entlastung um 16 Monate — der Verkaufsdruck war *weg*. Der Scout erfasst Stichtage neutral.
- 2026-08-28 — **Gesetzeswortlaut DE: `buzer.de/<nr>_<GESETZ>.htm`** und
  `gesetze-im-internet.de/<gesetz>/__<nr>.html`. Zwei unabhaengige Datenbanken, wortgetreu,
  ein Abruf je Paragraph. Fuer EU-Recht gibt es kein Gegenstueck (siehe unten).
- 2026-08-28 — **Bei EU-Recht nach Bestandsschutz suchen** (`Art. 111`, „erhebliche
  Konzeptionsaenderung", „bereits in Verkehr gebracht"). Bei der KI-VO schrumpft die
  „muss bis 2027 konform sein"-Gruppe auf Neu- und Umbauten. Erschlaegt Segmentzahlen
  staerker als jede Anbieterrecherche und steht nie in der Schlagzeile.
- 2026-08-28 — **Beste Einzelzahl fuer die Groesse einer Aenderung: der Erfuellungsaufwand aus
  dem Gesetzentwurf.** Suchmuster `<Gesetz> Erfuellungsaufwand Normenkontrollrat Millionen
  betroffene Unternehmen`. VerpackDG: 2,46 Mio EUR/Jahr fuer die *gesamte* Wirtschaft. Findbar
  ist die Zahl nicht im PDF, sondern in der Fachpresse, die daraus zitiert.
- 2026-08-28 — **Drei Saettigungsindikatoren, jeder spart die halbe Recherche:** (1) Preis-
  vergleichsportale *mit Gutscheincodes*; (2) ein existierender „Software-Vergleich <Jahr>";
  (3) betreibt schon ein **Einzelunternehmer** genau dieses Produkt? nachweisfertig.de
  (KI-Verzeichnis, App gratis, 14,99 EUR/Mon) ist derselbe Betriebstyp wie diese Fabrik — der
  Preisanker steht, bevor irgendwer anfaengt. Gezielt nach Einzelunternehmen suchen.
- 2026-08-28 — **Pruefen, ob die Behoerde die Technik selbst kostenlos stellt.** ZSVR:
  XML-Upload + Registerabruf-API (`fileadmin/LUCID/`-PDFs). EU-Kommission: AI Act Service Desk
  mit Compliance Checker, Explorer und mehrsprachigem Helpdesk, dazu ein nach Art. 11 KI-VO
  *verpflichtend* bereitzustellendes vereinfachtes Anhang-IV-Formular fuer KMU.
- 2026-08-28 — Englische Fassungen und IHK-Seiten bestaetigen Fristen unabhaengig.
  Verbandsstellungnahmen (Muster `pkv.de/positionen/`) listen Praxisprobleme vor dem Start —
  beste Quelle fuer Frage 5. Kanzlei-Blogs ebenso, aber immer drei unabhaengige.
- 2026-08-28 — **Bitkom-Presseinformationen (`bitkom.org/Presse/Presseinformation/<Thema>`) sind
  die beste Ersatzquelle, wenn kein Register zaehlt** — Stichprobe, Grundgesamtheit und
  Erhebungswochen stehen sauber drin. Aber Selbsteinschaetzung, und die Klasse „ab 20
  Beschaeftigte" gibt es bei Destatis nicht. Ergebnis als Korridor ausweisen, nie als Wert.

## Was nicht funktioniert

- 2026-08-28 — **Amtliche Volltexte sind fuer WebFetch weitgehend tot.** recht.bund.de (BGBl),
  dserver.bundestag.de, bundesumweltministerium.de liefern Binaerstroeme. **EUR-Lex auch als
  HTML**: `legal-content/DE/TXT/HTML/` und `eli/reg/<jahr>/<nr>/oj` geben leere Dokumente. Die
  Konsolidierer `ai-act-law.eu`/`.de` fuehren Altfassungen (Art. 113 noch Stand 2024-06-13).
  Fuer EU-Wortlaut habe ich derzeit **keinen** funktionierenden Weg.
- 2026-08-28 — Destatis nennt Groessenklassen oeffentlich nur in **Prozent**, Absolutwerte nur in
  GENESIS-Online (nicht abrufbar). Ab Berichtsjahr 2024 Umstellung auf „Jobkonzept",
  Vorjahresvergleich laut Destatis unzulaessig — nie Absolutzahlen zweier Jahrgaenge mischen.
- 2026-08-28 — `anwalt.de` und viele IHK-Unterseiten antworten 403; kanzlei-eigene Domains
  (noerr.com, it-recht-kanzlei.de, gleisslutz.com, itmr-legal.de) gehen problemlos.
  DATEV-Wissensplattform laedt per Skript nach, bleibt leer.
- 2026-08-28 — Zahlen zur *Zusammensetzung* eines Registers (deutscher Anteil an LUCID,
  Arbeitgeber mit PKV-Beschaeftigten) existieren praktisch nie: Register veroeffentlichen
  Summen, keine Schnitte. Ebenso: SaaS-Anbieter mit Preisseite nennen oft **keine** Zahl
  (SimpleAct, Kopexa, Cortina) — Preiskorridor auf die zwei, drei belegten Anbieter stuetzen.
- 2026-08-28 — E-Commerce-Zahlen aus Content-Marketing-Blogs (doofinder, listflix) haben nie
  eine Primaerquelle. Nicht verwenden, auch nicht „mit Vorbehalt".

## Offene Faehrten

- **Fuer den Portfolio-Manager, dringend:** Der Regel-Scout erfasst Stichtage ungeprueft — beim
  VerpackDG lag die Frist 15 Tage nach Erfassung (chancenlos), beim Digital Omnibus war es gar
  keine Pflicht, sondern eine Entlastung. Zwei Zeilen im Scout („Frist minus heute < 6 Monate →
  abgelaufen" und „Frist hin oder weg?") sparen je einen ganzen Rechercheurlauf.
- **Offene Flanke der KI-Hochrisiko-Recherche:** Art. 111 Abs. 2 KI-VO (Bestandsschutz;
  Behoerdensysteme bis 2030) nur bei *einer* Quelle (itmr-legal.de) gefunden. Baut eine Idee
  darauf auf, muss das am Wortlaut nachgeprueft werden — siehe EUR-Lex-Problem.
- Signal Art. 50 KI-Kennzeichnung (2026-08-27) ist von der Verschiebung *nicht* betroffen, gilt
  seit 2026-08-02 (Bestandssysteme bis 2026-12-02), noch nicht recherchiert. Vorher pruefen, ob
  dort dieselben 21 Anbieter sitzen wie bei Hochrisiko — vermutlich ja.
- FIT-Connect ist kostenlos und schliesst Private nicht aus. Fuer welche Leistung gibt es einen
  Zustellpunkt, den ein Dritter bedienen darf? Das waere der eigentliche Baustein. Eigener Lauf.
- EU-weite EPR-Bevollmaechtigte: zentrale EU-Registrierung nicht vor Mitte 2028, bis dahin je
  Land ein Bevollmaechtigter. Groesser als die LUCID-Pflicht, aber Landbell, zmart und
  ecosistant sind schon drin. Unternehmensbasisdatenregister (UBRegG) im Aufbau, Evaluierung
  2026, Zugang nur fuer berechtigte Stellen — bei jedem Datensignal auf Entwertung pruefen.
