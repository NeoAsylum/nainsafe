# Logbuch: Rechercheur

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 30 Zeilen.** Ist es voll, streichst du den aeltesten oder schwaechsten
Eintrag — nicht den unbequemsten.

---

## Was funktioniert

- 2026-08-28 — Bei OZG-/Verwaltungssignalen entscheidet **nicht** das Portal, sondern der
  Transportweg. Frage immer: laeuft es ueber OSCI/DVDV oder ueber FIT-Connect? DVDV ist auf
  oeffentliche Stellen beschraenkt (itzbund.de), FIT-Connect nicht (docs.fitko.de/faq).
  Das beantwortet „gibt es eine API fuer Dritte?" in zwei Abrufen statt in zehn Suchen.
- 2026-08-28 — Destatis-Pressemitteilungen liefern belastbare Segmentzahlen mit Zitat und
  fester URL. Muster: `destatis.de/DE/Presse/Pressemitteilungen/<Jahr>/<MM>/PD..._52311.html`
  (52311 = Gewerbeanzeigen). Statista war nie noetig.
- 2026-08-28 — Preise stehen fast nie auf der deutschen Seite eines Anbieters, oft aber auf
  der **englischen**: firma.de/en/... nannte 399/487 EUR netto, die deutsche Seite nichts.
- 2026-08-28 — „Was spricht dagegen" findet man schnellster ueber die Frage, was der Staat
  selbst gerade baut. Suche nach `<Thema> Pilot 2026 Bundesministerium DigitalService`
  brachte den Kombiantrag-Pilot, der die ganze Marktluecke schliesst.
- 2026-08-28 — Adressbroker (address-base.de, address-publisher.de) nennen Stueckpreise
  offen und dazu die Grundgesamtheit. Gute Quelle fuer „was ist ein Datensatz wert".

## Was nicht funktioniert

- 2026-08-28 — `xgewerbeanzeige.de` bricht mit TLS-Fehler ab. `xgewerbeordnung.de` ist die
  aktuelle Domain desselben Standards und funktioniert. Direkt dorthin.
- 2026-08-28 — Zahl der tatsaechlich angebundenen Kommunen bei EfA-Diensten war nicht zu
  ermitteln: `service.wirtschaft.nrw/hilfe/efa/nachnutzung/neuigkeiten/` gibt 404,
  FITKO-Marktplatz und digitale-verwaltung.de nennen keine Stueckzahlen. Naechstes Mal
  gar nicht erst lange suchen — als „nicht ermittelbar" notieren.
- 2026-08-28 — Nachrichtenaggregatoren (ad-hoc-news.de) als Signalquelle enthalten Zahlen
  ohne Primaerquelle („2.400 EUR Fehlerkosten"). Immer gegenpruefen; hier nicht belegbar.
  Auch die Frist „ab 2028" aus dem Signal war nirgends zu finden.

## Offene Faehrten

- FIT-Connect ist kostenlos und schliesst Private nicht aus. Fuer welche Leistung gibt es
  einen Zustellpunkt, den ein Dritter bedienen darf? Wenn irgendwo einer offensteht, ist
  das der eigentliche Baustein — nicht XGewerbe. Wert eines eigenen Laufs.
- Das Unternehmensbasisdatenregister (UBRegG, Destatis) ist im Aufbau, Evaluierung 2026,
  Zugang nur fuer gesetzlich berechtigte Stellen. Es koennte kommerzielle Firmendaten-
  Angebote entwerten. Bei jedem Datensignal mitpruefen.
