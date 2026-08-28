# Logbuch: Markt-Scout

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 30 Zeilen.** Ist es voll, streichst du den ältesten oder schwächsten
Eintrag — nicht den unbequemsten. Ein Logbuch, das unbegrenzt wächst, liest am Ende
niemand mehr, auch du nicht.

---

## Was funktioniert

- 2026-08-28 — `quellen.yml` Block `market` ist leer (keine `quellen:`-Eintraege).
  Ohne konkrete Quellen liefert die deutsche Websuche mit den `suchmuster`-Phrasen
  fast nur SEO-Vergleichsportale. Ergiebiger war es, gezielt nach konkreten grossen
  Anbietern zu suchen, die fuer Kurswechsel bekannt sind (SAP, DATEV, Microsoft),
  und dann mit Folgesuchen (Produktname + Datum) die Primaerquelle zu jagen.
- 2026-08-28 — Bei Preiserhoehungen/Tarifstreichungen ohne Primaerquelle hilft es,
  nach mehreren *unabhaengigen* Drittportalen zu suchen, die dieselben Zahlen nennen
  (bexio-Fall: 4 verschiedene Vergleichsportale, gleiche CHF-Betraege) — ersetzt
  keine Primaerquelle, senkt aber das Risiko einer erfundenen/uebertriebenen Zahl.

## Was nicht funktioniert

- 2026-08-28 — Suchmuster `"kleinster Tarif" gestrichen SaaS 2026` (fast) woertlich
  aus quellen.yml lieferte nur generische SaaS-Pricing-Trend-Artikel, keinen
  konkreten Fall. Direkter Produktname + "Preise" + Jahr war ergiebiger als das
  generische Suchmuster.
- 2026-08-28 — Fuer SAP Business ByDesign keine eigene SAP-Pressemitteilung
  gefunden (auch nicht ueber site:sap.com) — nur uebereinstimmende Partnerberichte
  (All for One, NTT DATA). SAP scheint solche Vertriebsstopps nicht selbst laut zu
  kommunizieren, sondern die Partner das Feld ueberlassen zu haben.

## Offene Faehrten

- 2026-08-28 — bexio ist Schweizer Anbieter (CHF); Relevanz fuer den deutschen
  Markt ungeprueft. Naechstes Mal pruefen, ob es eine vergleichbare, aber
  eindeutig deutsche Buchhaltungs-/Handwerkersoftware-Preiserhoehung gibt (Lexware,
  sevdesk, Papierkram, HERO) statt Schweiz mitzunehmen.
- 2026-08-28 — SQL Server 2016 EOL (Support-Ende Juli 2026) taucht in Suchen als
  KMU-relevant auf, aber das ist eher ein normaler Lebenszyklus-Ablauf als ein
  Wettbewerbssignal mit Nutzergruppen-Luecke — nicht aufgenommen. Falls der
  Tech-Scout das nicht ohnehin abdeckt, waere zu pruefen, ob irgendein Anbieter
  daraus eine Migrations-Nachfrage bedient, die noch offen ist.
- 2026-08-28 — SAP Business ByDesign: unklar, ob Neukunden tatsaechlich zu
  S/4HANA Public Cloud wechseln oder zu Drittanbietern (Odoo wurde in
  Sekundaerquellen mehrfach als Ausweichoption genannt) — noch nicht verfolgt,
  ob das ein eigenes Signal waere (Odoo-Wachstum durch SAP-Abwanderung).
