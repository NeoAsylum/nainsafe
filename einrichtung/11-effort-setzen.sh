#!/usr/bin/env bash
# Traegt in jede Rollendatei einen passenden Denkaufwand ein.
#
#   bash ~/fabrik/einrichtung/11-effort-setzen.sh
#
# Bisher lief jede Rolle auf dem Standardwert -- der Regel-Scout, der nur Fundstellen
# einsammelt, mit demselben Aufwand wie der Advocatus, der eine Idee widerlegen soll.
# Beides ist falsch: Beim Sammeln ist der Aufwand verschwendet, beim Urteilen fehlt er.
#
# Idempotent: mehrfaches Ausfuehren aendert nichts.

set -euo pipefail
cd "$HOME/fabrik"

python3 - <<'PY'
import re
from pathlib import Path

# Sammeln braucht Sorgfalt, kein tiefes Nachdenken -- die Quelle sagt, was sie sagt.
# Urteilen und Widerlegen braucht das Gegenteil: Dort entstehen die Fehler, die
# spaeter Wochen kosten.
AUFWAND = {
    "regel-scout":          "medium",
    "pain-scout":           "medium",
    "markt-scout":          "medium",
    "tech-scout":           "medium",
    "modell-scout":         "medium",
    "rechercheur":          "high",
    "ideator":              "high",
    "fit-filter":           "high",
    "advocatus-nachfrage":  "high",
    "advocatus-wettbewerb": "high",
    "advocatus-betrieb":    "high",
    # Die beiden Linsen mit Vetorecht denken am gruendlichsten: Ihr Urteil kann
    # allein toeten, und im Rechtsfall haengt daran die Nebentaetigkeitserlaubnis.
    "advocatus-recht":      "xhigh",
    "advocatus-vertrieb":   "high",
    # Waegt fuenf Angriffe gegeneinander ab und entscheidet, was dem Menschen
    # vorgelegt wird -- die folgenreichste Rolle der Fabrik.
    "portfolio-manager":    "xhigh",
    "digest-redakteur":     "medium",
}

geaendert = 0
for datei in sorted(Path("agents/rollen").glob("*.md")):
    name = datei.stem
    stufe = AUFWAND.get(name)
    if not stufe:
        print(f"  {name:24} keine Zuordnung -- bleibt auf dem Standard")
        continue

    text = datei.read_text(encoding="utf-8")
    if re.search(r"^effort:", text, re.MULTILINE):
        print(f"  {name:24} schon gesetzt")
        continue

    # Direkt hinter die Modellzeile, damit die Konfiguration beieinander steht.
    neu, anzahl = re.subn(r"^(modell:.*)$", rf"\1\neffort: {stufe}",
                          text, count=1, flags=re.MULTILINE)
    if not anzahl:
        print(f"  {name:24} keine Modellzeile gefunden -- uebersprungen")
        continue
    datei.write_text(neu, encoding="utf-8")
    print(f"  {name:24} {stufe}")
    geaendert += 1

print(f"\n{geaendert} Rollendateien ergaenzt.")
PY
