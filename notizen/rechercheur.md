# Logbuch: Rechercheur

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 30 Zeilen.** Ist es voll, streichst du den aeltesten oder schwaechsten
Eintrag — nicht den unbequemsten.

---

## Was funktioniert

- 2026-08-28 — Bei OZG-/Verwaltungssignalen entscheidet **nicht** das Portal, sondern der
  Transportweg: OSCI/DVDV (nur oeffentliche Stellen, itzbund.de) oder FIT-Connect (offen,
  docs.fitko.de/faq). Beantwortet „gibt es eine API fuer Dritte?" in zwei Abrufen.
- 2026-08-28 — Destatis-Pressemitteilungen liefern Segmentzahlen mit Zitat und fester URL:
  `destatis.de/DE/Presse/Pressemitteilungen/<Jahr>/<MM>/PD..._52311.html`. Statista war nie noetig.
- 2026-08-28 — **Erste Frage bei jedem Signal ueber eine neue Amtsschnittstelle:** liefert die
  etablierte Branchensoftware sie schon aus? `<Thema> DATEV Lexware Sage Update <Jahr>` — bei
  ELStAM/PKV lautete die Antwort „seit Ende 2025 produktiv", Ampel rot nach 20 Minuten.
- 2026-08-28 — Englische Fassungen sind auskunftsfreudiger als deutsche: firma.de/en nannte
  Preise, grantthornton.de/en den Satz „employers are obliged to accept the reported figures",
  der jede Pruef-Idee toetet. Bei deutschen Verfahrensthemen immer /en mitnehmen.
- 2026-08-28 — Verbandsstellungnahmen zu BMF-/Ministeriumsentwuerfen (Muster: `pkv.de/positionen/`)
  listen die Praxisprobleme eines Verfahrens vor dem Start. Beste Einzelquelle fuer Frage 5.
- 2026-08-28 — Fuer „was spricht dagegen" fragen, was der Staat selbst baut:
  `<Thema> Pilot <Jahr> Bundesministerium DigitalService`.

## Was nicht funktioniert

- 2026-08-28 — Erfuellungsaufwand-Zahlen zu Steuerverfahren (Minuten je Fall, Fallzahlen) sind
  weder ueber BMF noch ueber JStG-Begruendungen zu finden. Sofort „nicht ermittelbar" notieren.
- 2026-08-28 — Zahlen zur Nutzung/Anbindung (angebundene Kommunen bei EfA, Arbeitgeber mit
  PKV-Beschaeftigten) existieren praktisch nie. Kein Register kreuzt Betrieb mit Merkmal.
- 2026-08-28 — PKV-Verbandsseiten nennen nur Gesamtzahlen. Die Aufgliederung (Beihilfeanteil
  53,3 %) steht bei sozialpolitik-aktuell.de/.../abbVI29.pdf. Direkt dorthin.
- 2026-08-28 — DATEV-Wissensplattform (help-center.apps.datev.de leitet auf
  wissensplattform.apps.datev.de um) laedt per Skript nach, Abruf bleibt leer. Nicht einplanen.
- 2026-08-28 — `xgewerbeanzeige.de` bricht mit TLS-Fehler ab; `xgewerbeordnung.de` ist die
  aktuelle Domain. Nachrichtenaggregatoren (ad-hoc-news.de) nennen Zahlen ohne Primaerquelle.

## Offene Faehrten

- FIT-Connect ist kostenlos und schliesst Private nicht aus. Fuer welche Leistung gibt es einen
  Zustellpunkt, den ein Dritter bedienen darf? Das waere der eigentliche Baustein. Eigener Lauf.
- Unternehmensbasisdatenregister (UBRegG, Destatis) im Aufbau, Evaluierung 2026, Zugang nur fuer
  berechtigte Stellen. Koennte kommerzielle Firmendaten entwerten — bei jedem Datensignal pruefen.
- **Fuer den Portfolio-Manager:** Der Tech-Scout erfasst Bausteine, ohne zu pruefen, ob die
  Branchensoftware sie bereits bedient. Beim ELStAM/PKV-Signal war das Verfahren seit acht
  Monaten produktiv. Ein Ein-Zeilen-Check im Scout spart hier einen ganzen Rechercheurlauf.
