#!/usr/bin/env python3
"""Eine Gate-Entscheidung treffen. Der einzige Weg, einen Status anzuheben.

    python3 agents/entscheiden.py <idee-id> ja
    python3 agents/entscheiden.py <idee-id> nein "Begruendung"
    python3 agents/entscheiden.py <idee-id> vertagt "Was noch fehlt"

`ja` hebt die Idee auf die naechste Stufe, `nein` stellt sie ein. Kein Agent kann
das -- die Werkzeuglisten geben es keinem, und dieses Skript ist die menschliche
Gegenseite dazu.

Geprueft wird vorher, was sich pruefen laesst: ob der Uebergang ueberhaupt vorgesehen
ist und ob das WIP-Limit ihn erlaubt. Die inhaltliche Frage beantwortest du, nicht
dieses Skript.
"""

from __future__ import annotations

import re
import subprocess
import sys
from datetime import date
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import WURZEL, git  # noqa: E402

# Welcher Status auf welchen folgt, wenn der Mensch zustimmt.
WEITER = {
    "vorlage": "erkundung",
    "erkundung": "bau",
    "bau": "live",
    "live": "live",          # Gate 4 "ja" heisst: weiterlaufen lassen
}

GATE_NR = {"vorlage": 1, "erkundung": 2, "bau": 3, "live": 4}

WIP_AKTIV_MAX = 3
WIP_BAU_MAX = 1


def frontmatter_setzen(datei: Path, feld: str, wert: str) -> None:
    """Ersetzt ein Feld im Frontmatter, ohne den Rest der Datei anzufassen."""
    text = datei.read_text(encoding="utf-8")
    kopf_ende = text.index("---", 3)
    kopf, rumpf = text[:kopf_ende], text[kopf_ende:]
    muster = re.compile(rf"^{re.escape(feld)}:.*$", re.MULTILINE)
    if muster.search(kopf):
        kopf = muster.sub(f"{feld}: {wert}", kopf, count=1)
    else:
        kopf = kopf.rstrip("\n") + f"\n{feld}: {wert}\n"
    datei.write_text(kopf + rumpf, encoding="utf-8")


def main(argv: list[str]) -> int:
    if len(argv) < 3:
        print(__doc__)
        return 1

    idee_id, urteil = argv[1], argv[2].lower()
    begruendung = argv[3] if len(argv) > 3 else ""

    if urteil not in ("ja", "nein", "vertagt"):
        return _fehler("Urteil muss 'ja', 'nein' oder 'vertagt' sein.")

    treffer = [k for k in repo.ideen() if k["_id"] == idee_id or k["_id"].startswith(idee_id)]
    if not treffer:
        return _fehler(f"Keine Idee gefunden zu '{idee_id}'.\n"
                       "  Uebersicht: python3 agents/stand.py")
    if len(treffer) > 1:
        return _fehler("Mehrdeutig: " + ", ".join(k["_id"] for k in treffer))

    idee = treffer[0]
    datei: Path = idee["_datei"]
    jetzt_status = idee.get("status", "?")

    if jetzt_status not in WEITER:
        return _fehler(
            f"'{idee['_id']}' steht auf '{jetzt_status}' und wartet damit nicht auf dich.\n"
            f"  Auf eine Entscheidung warten nur: {', '.join(WEITER)}.\n"
            "  Die Maschine hebt Ideen bis 'vorlage' selbst an.")

    gate = GATE_NR[jetzt_status]

    if urteil == "vertagt":
        neu = jetzt_status
    elif urteil == "nein":
        neu = "eingestellt"
    else:
        neu = WEITER[jetzt_status]
        # WIP nur pruefen, wenn die Idee wirklich neu in den aktiven Bereich kommt.
        if jetzt_status == "vorlage":
            aktiv = len([k for k in repo.ideen()
                         if k.get("status") in ("erkundung", "bau", "live")])
            if aktiv >= WIP_AKTIV_MAX:
                return _fehler(
                    f"WIP-Limit erreicht: {aktiv}/{WIP_AKTIV_MAX} aktiv.\n"
                    "  Erst etwas einstellen, dann das hier hochstufen. Das Limit ist\n"
                    "  die Zusage an dich selbst, dass zwei Stunden pro Woche reichen.")
        if neu == "bau":
            im_bau = len([k for k in repo.ideen() if k.get("status") == "bau"])
            if im_bau >= WIP_BAU_MAX:
                return _fehler(f"Schon {im_bau} Vorhaben im Bau. Erst fertigstellen.")

    heute = date.today().isoformat()
    frontmatter_setzen(datei, "status", neu)
    frontmatter_setzen(datei, "geaendert", heute)
    frontmatter_setzen(datei, "rolle", "mensch")
    if urteil == "nein" and begruendung:
        frontmatter_setzen(datei, "ablehnungsgrund", f'"Gate {gate}: {begruendung}"')

    # Die Entscheidung selbst gehoert protokolliert, nicht nur ihr Ergebnis.
    protokoll = WURZEL / "decisions" / f"gate{gate}-{idee['_id']}-{heute}.md"
    protokoll.write_text(
        f"""---
nr: gate{gate}-{idee['_id']}
titel: "Gate {gate} fuer {idee.get('titel', idee['_id'])}: {urteil}"
datum: {heute}
status: gueltig
betrifft: [ideen]
---

# Gate {gate} — {idee.get('titel', idee['_id'])}

**Entscheidung:** {urteil} ({jetzt_status} → {neu})

**Begruendung:** {begruendung or '(keine angegeben)'}

Entschieden vom Betreiber, nicht von einem Agenten.
""", encoding="utf-8")

    for g in (WURZEL / "gates").glob(f"*{idee['_id']}*"):
        g.unlink()

    git("add", "-A")
    subprocess.run(
        ["git", "commit", "-q", "-m",
         f"gate {gate}: {idee['_id']} → {neu}",
         "-m", begruendung or "ohne Begruendung"],
        cwd=WURZEL, capture_output=True, text=True, encoding="utf-8",
    )

    print(f"\n  {idee['_id']}")
    print(f"  {jetzt_status} → {neu}")
    print(f"  Protokoll: {protokoll.relative_to(WURZEL)}\n")

    if neu == "erkundung":
        print("  Die Konzeptionsebene existiert noch nicht — Architekt, Oekonom,")
        print("  Compliance-Pruefer und die uebrigen Rollen aus Phase 3 fehlen.")
        print("  Solange bleibt diese Idee liegen.\n")
    return 0


def _fehler(text: str) -> int:
    print(f"\n  {text}\n")
    return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv))
