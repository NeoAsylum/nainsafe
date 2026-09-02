#!/usr/bin/env python3
"""Was liegt an? Der Blick auf die Fabrik in einem Bildschirm.

    python3 agents/stand.py

Beantwortet in dieser Reihenfolge: Was will etwas von mir? Was laeuft? Was ist
gestorben und woran? Die letzte Frage ist die wichtigste -- wenn immer dieselbe
Grenze toetet, stimmt etwas mit den Signalquellen nicht, nicht mit den Ideen.

Kostet nichts und veraendert nichts. Beliebig oft aufrufbar.
"""

from __future__ import annotations

import re
import sqlite3
import subprocess
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import DB, WURZEL, frontmatter  # noqa: E402

GATES = WURZEL / "gates"

# Was der Mensch an welchem Gate entscheidet.
GATE_FRAGE = {
    "vorlage": ("Gate 1", "Lohnt die Ausarbeitung?", "~5 min"),
    "erkundung": ("Gate 2", "Genehmigungsfaehig, tragfaehig, gewollt?", "~30 min"),
    "bau": ("Gate 3", "Geht online, nimmt Geld", "~30 min"),
    "live": ("Gate 4", "Skalieren, halten oder einstellen", "~45 min"),
}


def farbe(text: str, code: str) -> str:
    return f"\033[{code}m{text}\033[0m"


def titel(t: str) -> None:
    print(f"\n{farbe(t, '1')}")
    print("─" * len(t))


def kurz(text: str, n: int = 100) -> str:
    text = re.sub(r"\s+", " ", (text or "").strip().strip('"'))
    return text if len(text) <= n else text[: n - 1] + "…"


def main() -> int:
    alle = repo.ideen()
    nach_status: dict[str, list] = {}
    for k in alle:
        nach_status.setdefault(k.get("status", "?"), []).append(k)

    # ---- Was will etwas von mir? -------------------------------------------
    titel("Wartet auf dich")
    offen = sorted(GATES.glob("*.md"))
    wartende = [k for s in GATE_FRAGE for k in nach_status.get(s, [])]

    if not offen and not wartende:
        print("  Nichts. Kein offenes Gate, keine Idee wartet auf eine Entscheidung.")
        print("  Das ist ein normaler Wochentag — der Portfolio-Manager legt")
        print("  Vorlagen sonntags an, und nur wenn eine Idee es verdient.")
    else:
        for datei in offen:
            kopf, _ = frontmatter(datei.read_text(encoding="utf-8"))
            nr = kopf.get("gate", "?")
            zeit = kopf.get("lesezeit", "?")
            stand = kopf.get("entscheidung", "offen")
            marke = farbe("OFFEN", "33") if stand == "offen" else stand
            print(f"  [{marke}] Gate {nr} · {zeit} · {datei.relative_to(WURZEL)}")
            print(f"          {kurz(kopf.get('idee', ''))}")
        for k in wartende:
            g, frage, zeit = GATE_FRAGE[k["status"]]
            print(f"  [{farbe('OFFEN', '33')}] {g} · {zeit} · {k['_id']}")
            print(f"          {frage}")

    # ---- Was laeuft? -------------------------------------------------------
    titel("Im Portfolio")
    aktiv = [k for s in ("erkundung", "bau", "live") for k in nach_status.get(s, [])]
    print(f"  {len(aktiv)}/3 aktiv, "
          f"{len(nach_status.get('bau', []))}/1 im Bau")
    for k in aktiv:
        print(f"    {k['status']:10} {k['_id']}")

    warten = nach_status.get("kandidat", [])
    if warten:
        print(f"\n  {len(warten)} Kandidaten in Pruefung:")
        for k in warten:
            fehlend = [l for l in repo.LINSEN if l not in repo.angriffe(k["_id"])]
            stand = "geprueft" if not fehlend else f"offen: {', '.join(fehlend)}"
            print(f"    {repo._score(k):3} Pkt  {k['_id']:42} {stand}")

    entwuerfe = nach_status.get("entwurf", [])
    if entwuerfe:
        print(f"\n  {len(entwuerfe)} Entwuerfe warten auf den Fit-Filter.")

    # ---- Was ist gestorben? ------------------------------------------------
    tot = nach_status.get("abgelehnt", []) + nach_status.get("widerlegt", [])
    titel(f"Gestorben ({len(tot)})")
    if not tot:
        print("  Noch nichts. Das ist kein gutes Zeichen — ein Filter, der")
        print("  nichts ablehnt, filtert nicht.")
    else:
        gruende = Counter()
        for k in tot:
            g = (k.get("ablehnungsgrund") or "").strip().strip('"')
            treffer = re.match(r"(G\d)", g)
            gruende[treffer.group(1) if treffer else "sonstige"] += 1
        for k in tot[-4:]:
            print(f"  {k['_id']}")
            print(f"    {kurz(k.get('ablehnungsgrund', '—'), 110)}")
        if len(tot) > 4:
            print(f"  … und {len(tot) - 4} weitere")

        print(f"\n  Verteilung: " + ", ".join(f"{g}×{n}" for g, n in gruende.most_common()))
        haeufigste, anzahl = gruende.most_common(1)[0]
        if anzahl >= 3 and anzahl / len(tot) > 0.5:
            print(farbe(
                f"  Mehr als die Haelfte stirbt an {haeufigste}. Das ist ein Befund\n"
                f"  ueber deine Signalquellen, nicht ueber die Ideen — dieselbe Sorte\n"
                f"  Signal erzeugt dieselbe Sorte Idee. Andere Quellen eintragen.", "33"))

    # ---- Bestand -----------------------------------------------------------
    titel("Bestand")
    # Nicht hartcodieren: Neue Signalarten -- modelle, maerkte -- waeren sonst
    # unsichtbar, und gerade sie sind die interessanten.
    for ordner in sorted((WURZEL / "signals").iterdir()):
        if not ordner.is_dir():
            continue
        n = len(list(ordner.glob("*.md")))
        marke = "" if n else farbe("  ← liefert nichts", "31")
        print(f"  signals/{ordner.name:11} {n:3}{marke}")

    for name, pfad in (("research", WURZEL / "research"),
                       ("ideas", WURZEL / "ideas")):
        n = len(list(pfad.glob("*.md")))
        print(f"  {name:19} {n:3}")

    if DB.exists():
        v: sqlite3.Connection = sqlite3.connect(DB)
        letzte = v.execute(
            """SELECT substr(gestartet,6,11), rolle, ergebnis
               FROM lauf ORDER BY id DESC LIMIT 1"""
        ).fetchone()
        heute = v.execute(
            """SELECT count(*), sum(tokens_in+tokens_out) FROM lauf
               WHERE gestartet > date('now')"""
        ).fetchone()
        v.close()
        if letzte:
            print(f"\n  Letzter Lauf: {letzte[0]} {letzte[1]} ({letzte[2]})")
        if heute and heute[0]:
            # Nur die Zahl umstellen -- ein replace auf der ganzen Zeile erwischt
            # auch das Komma im Satz.
            tok = f"{heute[1] or 0:,}".replace(",", ".")
            print(f"  Heute: {heute[0]} Laeufe, {tok} Tokens")

    # ---- Was hat die Fabrik gelernt? ---------------------------------------
    notizen = WURZEL / "notizen"
    lehren = notizen / "lehren.md"
    if lehren.exists():
        titel("Gelernt")
        eintraege = [z.strip() for z in lehren.read_text(encoding="utf-8").splitlines()
                     if re.match(r"^-\s+\*\*\d{4}-\d{2}-\d{2}\*\*", z.strip())]
        logbuecher = [d for d in notizen.glob("*.md")
                      if d.name not in ("lehren.md", "VORLAGE.md")]
        print(f"  {len(eintraege)} Lehren, {len(logbuecher)} Logbuecher gefuehrt")
        for e in eintraege[-2:]:
            print(f"    {kurz(e.lstrip('- '), 105)}")
        if eintraege:
            print(farbe(
                "\n  Lies das gelegentlich gegen: Eine falsche Lehre steuert ab jetzt\n"
                "  jeden Lauf. notizen/lehren.md", "33"))

    # ---- Was tun -----------------------------------------------------------
    titel("Naechster Schritt")
    if offen or wartende:
        print("  Vorlage lesen, dann entscheiden:")
        print("    python3 agents/entscheiden.py <idee-id> ja")
        print("    python3 agents/entscheiden.py <idee-id> nein 'Begruendung'")
    else:
        print("  Nichts zu tun. Naechster Nachtlauf 03:00, Vorstand sonntags 07:00.")
    print()
    return 0


if __name__ == "__main__":
    sys.exit(main())
