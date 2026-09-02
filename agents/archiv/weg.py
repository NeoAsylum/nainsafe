#!/usr/bin/env python3
"""Der Weg einer Idee — und was die Fabrik daraus lernen kann.

    python3 agents/weg.py <idee-id>     ein Weg im Detail
    python3 agents/weg.py               das Muster über alle Ideen

Ohne Argument beantwortet es die Fragen, aus denen Verbesserung entsteht: In welchem
Schritt sterben Ideen, an welcher Grenze, unter welcher Linse — und welche Einwände
wiederholen sich so oft, dass sie ins gemeinsame Gedächtnis gehören.

Zwölf verworfene Ideen sind kein Fehler; neun von zehn Unternehmen scheitern. Der Wert
liegt nicht darin, dass wenig durchkommt, sondern darin, dass nachvollziehbar ist,
warum — und ob der Grund jedes Mal derselbe ist.
"""

from __future__ import annotations

import re
import sqlite3
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import DB, WURZEL, frontmatter  # noqa: E402

TOT = ("abgelehnt", "widerlegt", "eingestellt")


def fett(t): return f"\033[1m{t}\033[0m"
def grau(t): return f"\033[90m{t}\033[0m"
def gelb(t): return f"\033[33m{t}\033[0m"


def kurz(t: str, n: int = 100) -> str:
    t = re.sub(r"\s+", " ", (t or "").strip().strip('"'))
    return t if len(t) <= n else t[: n - 1] + "…"


def laeufe_zu(gegenstand: str) -> list[tuple]:
    if not DB.exists():
        return []
    v = sqlite3.connect(DB)
    zeilen = v.execute(
        """SELECT rolle, substr(gestartet, 6, 11), ergebnis, round(kosten_eur, 2)
           FROM lauf WHERE gegenstand LIKE ? ORDER BY id""",
        (f"%{gegenstand}%",),
    ).fetchall()
    v.close()
    return zeilen


# ---------------------------------------------------------------- ein Weg

def einzelweg(idee_id: str) -> int:
    treffer = [k for k in repo.ideen()
               if k["_id"] == idee_id or k["_id"].startswith(idee_id)]
    if not treffer:
        print(f"\n  Keine Idee zu '{idee_id}'.\n")
        return 1
    k = treffer[0]
    datei: Path = k["_datei"]

    print(f"\n{fett(k['_id'])}")
    print(f"  {k.get('titel', '')}")
    print("─" * 88)

    # 1. Herkunft
    quelle = k.get("quelle", "—")
    print(f"\n{fett('1. Woher')}")
    print(f"   Signal: {quelle}")
    sig = WURZEL / str(quelle)
    if sig.exists():
        skopf, _ = frontmatter(sig.read_text(encoding="utf-8"))
        typ = skopf.get("typ", "?")
        print(f"   Art:    {typ}")
        for feld in ("betroffen", "vorbild", "belegte_zahlung", "potenzial",
                     "erreichbar_ueber", "kosten_der_handarbeit"):
            if skopf.get(feld):
                print(f"   {feld:22} {kurz(str(skopf[feld]), 60)}")

    # 2. Recherche
    print(f"\n{fett('2. Recherche')}")
    gefunden = False
    for r in (WURZEL / "research").glob("*.md"):
        rkopf, _ = frontmatter(r.read_text(encoding="utf-8"))
        if str(rkopf.get("signal", "")).strip() == str(quelle).strip():
            gefunden = True
            print(f"   {r.name}")
            print(f"   Ampel: {rkopf.get('ampel', '?')}   "
                  f"Segment: {kurz(str(rkopf.get('segmentgroesse', '?')), 45)}")
            print(f"   Anbieter gefunden: {rkopf.get('anbieter_gefunden', '?')}")
    if not gefunden:
        print(grau("   keine — die Idee stand auf dem Signal allein"))

    # 3. Fit-Filter
    print(f"\n{fett('3. Fit-Filter')}")
    score = k.get("score")
    if isinstance(score, dict) and score.get("summe") not in (None, "null"):
        teile = ", ".join(f"{n}={w}" for n, w in score.items() if n != "summe")
        print(f"   Score {score.get('summe')}   ({teile})")
    grund = k.get("ablehnungsgrund")
    if grund and grund != "null":
        print(gelb(f"   ABGELEHNT: {kurz(grund, 78)}"))
    else:
        print("   durchgelassen")

    # 4. Angriffe
    print(f"\n{fett('4. Die Skeptiker')}")
    ordner = WURZEL / "ideas" / f"{k['_id']}.angriffe"
    if not ordner.is_dir():
        print(grau("   noch keine"))
    else:
        for linse in repo.LINSEN:
            d = ordner / f"{linse}.md"
            if not d.exists():
                print(f"   {linse:12} {grau('offen')}")
                continue
            akopf, rumpf = frontmatter(d.read_text(encoding="utf-8"))
            urteil = akopf.get("urteil", "?")
            marke = gelb(urteil) if urteil == "widerlegt" else urteil
            print(f"   {linse:12} {marke}")
            print(f"                {kurz(akopf.get('schwerster_einwand', ''), 70)}")
            # Genau das Feld, das bisher niemand gelesen hat.
            m = re.search(r"## Was ihn entkr[aä]ften w[uü]rde\s*\n+(.+?)(?=\n##|\Z)",
                          rumpf, re.S)
            if m:
                print(grau(f"     lösbar durch: {kurz(m.group(1), 68)}"))

    # 5. Ergebnis
    print(f"\n{fett('5. Wo sie steht')}")
    print(f"   Status: {k.get('status')}")

    kosten = sum(z[3] or 0 for z in laeufe_zu(k["_id"]))
    n = len(laeufe_zu(k["_id"]))
    if n:
        print(f"   {n} Läufe auf diese Idee, {kosten:.2f} $ Gegenwert")
    print()
    return 0


# ---------------------------------------------------------------- das Muster

def muster() -> int:
    alle = repo.ideen()
    tot = [k for k in alle if k.get("status") in TOT]
    lebend = [k for k in alle if k.get("status") not in TOT]

    print(f"\n{fett('Wo Ideen sterben')}")
    print("─" * 88)
    print(f"  {len(alle)} Ideen gesamt, {len(tot)} verworfen, {len(lebend)} in Arbeit")
    print()
    print("  Neun von zehn Unternehmen scheitern. Eine hohe Verwerfungsquote ist kein")
    print("  Fehler, sondern der Zweck der Fabrik — die Frage ist, ob immer dasselbe")
    print("  Muster tötet und ob man ihm früher begegnen könnte.")

    # Im Fit-Filter oder erst bei den Skeptikern?
    im_filter = [k for k in tot if k.get("status") == "abgelehnt"]
    bei_skeptikern = [k for k in tot if k.get("status") == "widerlegt"]
    print(f"\n{fett('In welchem Schritt')}")
    print("─" * 88)
    print(f"  Fit-Filter   {len(im_filter):3}   billig — eine Grenze, ein Lauf")
    print(f"  Skeptiker    {len(bei_skeptikern):3}   teuer — fünf Läufe je Idee")
    if len(bei_skeptikern) > len(im_filter):
        print(gelb("\n  Mehr Ideen sterben bei den Skeptikern als im Filter. Alles, was"))
        print(gelb("  der Fit-Filter früher erkennen könnte, spart fünf Angriffsläufe."))

    # Welche Grenze
    grenzen = Counter()
    for k in tot:
        g = (k.get("ablehnungsgrund") or "").strip().strip('"')
        t = re.match(r"(G\d)", g)
        grenzen[t.group(1) if t else "ohne Grenzenangabe"] += 1
    if grenzen:
        print(f"\n{fett('Welche Grenze')}")
        print("─" * 88)
        for g, n in grenzen.most_common():
            print(f"  {g:22} {n:3}")

    # Welche Linse
    linsen, entkraeftbar = Counter(), Counter()
    for k in alle:
        ordner = WURZEL / "ideas" / f"{k['_id']}.angriffe"
        if not ordner.is_dir():
            continue
        for linse in repo.LINSEN:
            d = ordner / f"{linse}.md"
            if not d.exists():
                continue
            akopf, rumpf = frontmatter(d.read_text(encoding="utf-8"))
            if akopf.get("urteil") == "widerlegt":
                linsen[linse] += 1
                m = re.search(r"## Was ihn entkr[aä]ften w[uü]rde\s*\n+(\S.+?)(?=\n##|\Z)",
                              rumpf, re.S)
                if m and len(m.group(1).strip()) > 40:
                    entkraeftbar[linse] += 1

    if linsen:
        print(f"\n{fett('Welche Linse tötet')}")
        print("─" * 88)
        print(f"  {'Linse':14} {'widerlegt':>10} {'davon mit Weg heraus':>22}")
        for linse, n in linsen.most_common():
            print(f"  {linse:14} {n:>10} {entkraeftbar.get(linse, 0):>22}")
        gesamt_weg = sum(entkraeftbar.values())
        if gesamt_weg:
            print()
            print(gelb(f"  {gesamt_weg} der Einwände nennen selbst einen Weg, sie zu"))
            print(gelb("  entkräften. Niemand liest ihn — genau das ändert der Anwalt."))
    print()
    return 0


if __name__ == "__main__":
    sys.exit(einzelweg(sys.argv[1]) if len(sys.argv) > 1 else muster())
