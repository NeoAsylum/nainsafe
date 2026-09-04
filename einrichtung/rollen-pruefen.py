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
from fnmatch import fnmatch
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
    verkettet |= {"markt-analyst", "prozess-analyst", "rechercheur"}
    # Fit-Filter, die fuenf Linsen und der Anwalt liegen seit dem 2026-08-31 unter
    # agents/rollen/archiv/ -- sie werden nicht mehr gerufen und deshalb hier nicht
    # mehr verlangt. Wer sie zurueckholt, schiebt sie zurueck und nimmt diese Zeile
    # wieder heraus.
    # Die Konzeptionsphase, seit 2026-08-31. Sie laeuft nicht naechtlich, sondern auf
    # Zuruf nach Gate 1 -- deshalb steht sie in konzeptlauf.py und nicht im Nachtlauf.
    import konzeptlauf  # noqa: E402
    for _, stufenrollen in konzeptlauf.STUFEN:
        verkettet |= set(stufenrollen)
    # Die Bauphase, seit 2026-08-31. Sie faehrt Arbeitspakete, nicht Rollen -- die
    # Rollenmenge steht deshalb im Runner und nicht in einer Kette.
    import baulauf  # noqa: E402
    verkettet |= baulauf.BAUROLLEN | baulauf.PRUEFROLLEN
    verkettet |= set(baulauf.REVIEW.values())
    verkettet |= {"projektmanager", "geschaeftsfuehrer", "spielentwerfer", "datenkurator"}
    vorhanden = {d.stem for d in rollen}
    for r in sorted(verkettet - vorhanden):
        befunde.append(f"KETTE: ruft `{r}` auf, aber agents/rollen/{r}.md fehlt")
    for r in sorted(vorhanden - verkettet):
        befunde.append(f"WAISE: agents/rollen/{r}.md steht in keiner Kette")

    # Arbeitspakete: Gibt es welche fuer Rollen, die kein Runner einplanen kann?
    #
    # Diese Pruefung fehlte, und dieselbe Fehlerklasse hat binnen zwei Tagen dreimal
    # zugeschlagen: eine Ruecklaufgrenze im Arbeitspaket statt im Runner, eine
    # Torpruefung nach einem Dateinamen, der sich aenderte, und ein Paket fuer den
    # Architekten, den `baulauf` nicht kannte. Jedes Mal lag die Regel an einer Stelle,
    # die der Ablauf nicht erreicht -- und jedes Mal fiel es erst auf, als etwas nicht
    # geschah. Ausbleibende Arbeit sieht aus wie erledigte.
    import baulauf  # noqa: E402
    einplanbar = baulauf.BAUROLLEN | baulauf.PRUEFROLLEN
    for ordner in sorted((WURZEL / "ventures").glob("*/aufgaben")):
        for datei in sorted(ordner.glob("*.md")):
            kopf, _ = frontmatter(datei.read_text(encoding="utf-8"))
            rolle = kopf.get("rolle")
            if kopf.get("status") in ("fertig", None):
                continue
            if rolle and rolle not in einplanbar:
                befunde.append(
                    f"PAKET: {datei.name} steht auf `{kopf.get('status')}` und "
                    f"gehoert `{rolle}` -- diese Rolle plant kein Runner ein, "
                    f"das Paket wird nie laufen")

    # --- Jede Baurolle muss wissen, wie sie ihr Paket abschliesst ---
    #
    # Am 2026-09-04 fehlte der Satz "Setze `status: gebaut`" in `architekt`,
    # `spielentwerfer` und `testentwickler` -- den drei Rollen, die spaeter fuer die
    # Spieleentwicklung dazukamen. Die Folge ist nicht ein Fehler, sondern eine
    # Wiederholung: Der Runner liest nur das Frontmatter, sieht `offen` und plant
    # dasselbe Paket erneut ein. 0026-klasse-2-preisbasis wurde in einer Nacht dreimal
    # zugewiesen und war ab dem ersten Mal geliefert.
    #
    # Der Fehler ist unsichtbar, weil jeder einzelne Lauf gelingt.
    try:
        sys.path.insert(0, str(WURZEL / "agents"))
        from baulauf import BAUROLLEN
    except Exception as fehler:
        befunde.append(f"KETTE: BAUROLLEN nicht lesbar ({fehler})")
        BAUROLLEN = []
    for r in BAUROLLEN:
        datei = WURZEL / "agents" / "rollen" / f"{r}.md"
        if not datei.exists():
            continue
        text = datei.read_text(encoding="utf-8")
        if "status: gebaut" not in text:
            befunde.append(
                f"ABSCHLUSS: {r}.md sagt nicht, dass die Rolle `status: gebaut` "
                f"setzen muss -- der Runner plant ihr Paket dann wieder und wieder ein")
            continue

        # Die Pflicht braucht das passende Recht. Am 2026-09-04 hat der Betreiber die
        # Pflicht ergaenzt und das Recht vergessen: `architekt` und `spielentwerfer`
        # durften nur `specs/**` schreiben, Arbeitspakete liegen aber unter
        # `ventures/<id>/aufgaben/`. Der Architekt meldete daraufhin drei verweigerte
        # Edit-Aufrufe und kam leer zurueck -- eine Regel an einer Stelle, die der
        # Ablauf nicht erfuellen kann.
        kopf_r, _ = frontmatter(text)
        ziel = "ventures/beispiel/aufgaben/0001-beispiel.md"
        muster = [w[5:-1] for w in (kopf_r.get("tools") or [])
                  if isinstance(w, str) and w.startswith("Edit(") and w.endswith(")")]
        if not any(fnmatch(ziel, m.replace("**", "*")) for m in muster):
            befunde.append(
                f"RECHT: {r}.md verlangt `status: gebaut`, hat aber kein Edit-Recht "
                f"auf `ventures/**/aufgaben/**` -- die Rolle kann ihre eigene Pflicht "
                f"nicht erfuellen. Erlaubt sind: {muster or 'nichts'}")

    print(f"{len(rollen)} Rollen geprueft.")
    for b in befunde:
        print(f"  BEFUND  {b}")
    if not befunde:
        print("  Keine Befunde.")
    return 1 if befunde else 0


if __name__ == "__main__":
    sys.exit(main())
