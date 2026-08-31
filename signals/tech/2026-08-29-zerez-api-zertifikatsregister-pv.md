---
typ: tech
erfasst: 2026-08-29
quelle: https://www.pv-magazine.de/unternehmensmeldungen/zerez-erweitert-funktionalitaeten-um-digitale-schnittstelle-api-und-erweiterte-datenzugangssteuerung/
abgerufen: 2026-08-29
baustein: API des Zentralen Registers für Einheiten- und Komponentenzertifikate (ZEREZ)
verfuegbar_seit: 2026-04-17
ermoeglicht: automatisierte Massenprüfung von PV-Zertifikaten (ZEREZ-IDs) bei Netzanschlussanträgen statt einzelner manueller Abfrage pro Anlage über die Weboberfläche
---

# ZEREZ, das seit 1.2.2025 für jede netzgekoppelte PV-Anlage verpflichtende Zertifikatsregister, bietet seit 17.4.2026 registrierten Nutzern eine API statt nur der Web-Oberfläche.

Bisher mussten Netzbetreiber und Installateure jede ZEREZ-ID einzeln über die Website
zerez.net nachschlagen, um die Einheiten- und Komponentenzertifikate für einen
Netzanschlussantrag zu prüfen. Mit der neuen API können registrierte Nutzer diese
Prüfung programmatisch und in Serie abfragen, inklusive granularer Freigabesteuerung für
einzelne Nutzer/Gruppen ohne manuellen Genehmigungsprozess je Zugriff.

## Belegstelle

"Das Zentrale Register für Einheiten- und Komponentenzertifikate (ZEREZ) hat seine
Funktionalitäten erweitert und stellt ab sofort allen registrierten Nutzerinnen und
Nutzern eine digitale Schnittstelle (API) zur Verfügung." (pv-magazine.de, 2026-04-17,
abgerufen 2026-08-29)

## Was unklar ist

Ob die API-Nutzung selbst kostenpflichtig ist, wird in der gesichteten Quelle nicht
erwähnt — nur die Registrierungspflicht. Unklar auch, ob Mengenbegrenzungen (Rate
Limits) bestehen und ob die API für alle Spannungsebenen gilt oder nur für die laut
älteren Quellen ohne Login öffentlich einsehbaren Basisdaten (Nieder-/Mittelspannung,
VDE-AR-N 4105/4110) — höhere Spannungsebenen waren bisher nur registrierten Nutzern
zugänglich. Primärdokumentation von ZEREZ selbst (nicht nur Sekundärquelle
pv-magazine) noch nicht geprüft.

**Nachtrag 2026-08-31:** Primärquelle gefunden (shop.wind-fgw.de/zerez-faq/, abgerufen
2026-08-31). Kosten geklärt: "ZEREZ ist aufgrund der Vorgaben der NELEV-Novelle
kostenfrei. Für die Registrierung und Nutzung der Basisfunktionen des Registers fallen
keine Gebühren an." Aber: dieselbe FAQ schränkt die API-Nutzung auf Netzbetreiber ein
("aktuell nur für Netzbetreiber verfügbar") — nicht für Installateure oder sonstige
Dritte. Das schwächt den ursprünglichen `ermoeglicht`-Satz: Massenprüfung per API steht
demnach (noch) nicht jedem registrierten Nutzer offen, nur Netzbetreibern. Rate Limits
und Spannungsebenen-Abdeckung weiterhin nicht dokumentiert.
