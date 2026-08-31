#!/usr/bin/env python3
"""Prueft jede Rollendatei gegen die Regeln aus CLAUDE.md.

    python3 einrichtung/rollen-pruefen.py

Was hier auffaellt, faellt sonst erst im Lauf auf -- und dann ist das Kontingent weg.
Angelegt am 2026-08-30, nachdem eine Durchsicht drei Befunde gefunden hat, die jeder
fuer sich ueber Wochen unbemerkt geblieben waeren: ein blankes `Bash` in einer
Rollendatei, deren Text "nur lesend" versprach; ein Logbuch, das es nicht gab; und
eine Rolle, die sich selbst anders nannte als ihre Datei.
"""

from __future__ import annotations

import sys
from pathlib import Path

WURZEL = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(WURZEL / "agents"))

from lauf import NIE, frontmatter  # noqa: E402

PFLICHTFELDER = ("rolle", "modell", "timeout", "effort", "takt")

# Werkzeuge, die eine Rolle nur mit ausdruecklicher Einschraenkung haben darf. Eine
# blanke Shell umgeht jede Edit()-Sperre: `cat > grenzen.md` braucht kein Edit.
NUR_EINGESCHRAENKT = ("Bash", "Write", "NotebookEdit")


def sperrpraefix(regel: str) -> str:
    """Der Pfadanfang, den eine Edit()-Sperre abdeckt."""
    return regel[len("Edit("):-1].lstrip("/").split("*", 1)[0]


def main() -> int:
    rollen = sorted((WURZEL / "agents" / "rollen").glob("*.md"))
    sperren = [sperrpraefix(n) for n in NIE if n.startswith("Edit(")]
    befunde: list[str] = []

    for datei in rollen:
        name = datei.stem
        kopf, rumpf = frontmatter(datei.read_text(encoding="utf-8"))
        werkzeuge = kopf.get("tools") or []

        def melde(text: str) -> None:
            befunde.append(f"{name}: {text}")

        if not werkzeuge:
            melde("keine Werkzeuge -- das waere ein Blankoscheck")
        if not rumpf.strip():
            melde("leerer Auftrag")
        for feld in PFLICHTFELDER:
            if not kopf.get(feld):
                melde(f"Feld `{feld}` fehlt")
        if kopf.get("rolle") and kopf["rolle"] != name:
            melde(f"Feld rolle={kopf['rolle']!r} passt nicht zum Dateinamen")

        for w in werkzeuge:
            if w in NUR_EINGESCHRAENKT:
                melde(f"`{w}` ohne Einschraenkung -- umgeht die Edit()-Sperren")

        # Genau ein eigenes Logbuch, keine fremden.
        logbuecher = [w for w in werkzeuge if w.startswith("Edit(notizen/")]
        eigenes = f"Edit(notizen/{name}.md)"
        if eigenes not in logbuecher:
            melde("kein eigenes Logbuch in der Werkzeugliste")
        for w in logbuecher:
            # lehren.md ist das gemeinsame Gedaechtnis; der Portfolio-Manager
            # traegt dort ein, was alle angeht. Das ist die einzige Ausnahme.
            if w not in (eigenes, "Edit(notizen/lehren.md)"):
                melde(f"schreibt in fremdes Logbuch: {w}")
        if not (WURZEL / "notizen" / f"{name}.md").exists():
            melde(f"Logbuchdatei notizen/{name}.md fehlt -- der erste Lauf schreibt ins Leere")

        # Kein Schreibpfad darf in einem gesperrten Bereich liegen.
        for w in werkzeuge:
            if not w.startswith("Edit("):
                continue
            ziel = w[len("Edit("):-1].lstrip("/").split("*", 1)[0]
            for s in sperren:
                if s and ziel.startswith(s):
                    melde(f"Schreibpfad {w} liegt in gesperrtem Bereich {s}")

    # Steht jede Rolle in einer Kette, und laeuft jede Kette nur bekannte Rollen an?
    import nachtlauf  # noqa: E402
    import wochenlauf  # noqa: E402
    verkettet = set(nachtlauf.SENSOREN) | set(nachtlauf.VERDICHTUNG) | set(wochenlauf.KETTE)
    verkettet |= {"markt-analyst", "prozess-analyst", "rechercheur", "anwalt"}
    verkettet |= {f"advocatus-{l}" for l in __import__("repo").LINSEN}
    # Die Konzeptionsphase, seit 2026-08-31. Sie laeuft nicht naechtlich, sondern auf
    # Zuruf nach Gate 1 -- deshalb steht sie in konzeptlauf.py und nicht im Nachtlauf.
    import konzeptlauf  # noqa: E402
    for _, stufenrollen in konzeptlauf.STUFEN:
        verkettet |= set(stufenrollen)
    vorhanden = {d.stem for d in rollen}
    for r in sorted(verkettet - vorhanden):
        befunde.append(f"KETTE: ruft `{r}` auf, aber agents/rollen/{r}.md fehlt")
    for r in sorted(vorhanden - verkettet):
        befunde.append(f"WAISE: agents/rollen/{r}.md steht in keiner Kette")

    print(f"{len(rollen)} Rollen geprueft.")
    for b in befunde:
        print(f"  BEFUND  {b}")
    if not befunde:
        print("  Keine Befunde.")
    return 1 if befunde else 0


if __name__ == "__main__":
    sys.exit(main())
