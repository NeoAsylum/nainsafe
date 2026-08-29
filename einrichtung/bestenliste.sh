#!/usr/bin/env bash
# Die Ideen nach Punktzahl, mit Todesursache und dem, was der Anwalt daraus machte.
cd "$HOME/fabrik" || exit 1

python3 - <<'PY'
import sys, re
sys.path.insert(0, 'agents')
import repo
from lauf import WURZEL, frontmatter

def kurz(t, n=150):
    t = re.sub(r"\s+", " ", (t or "").strip().strip('"'))
    return t if len(t) <= n else t[:n-1] + "…"

alle = repo.ideen()
bewertet = [k for k in alle if repo._score(k) > 0]
bewertet.sort(key=lambda k: -repo._score(k))

print(f"{len(alle)} Ideen insgesamt, {len(bewertet)} kamen bis zur Bewertung.\n")

for k in bewertet:
    idee = k["_id"]
    print("=" * 78)
    print(f"{repo._score(k):>3} Punkte   {idee}")
    print(f"           {k.get('titel','')}")
    print(f"           Status: {k.get('status')}   Zahlungsgrund: {k.get('zahlungsgrund','?')}")
    sc = k.get("score")
    if isinstance(sc, dict):
        teile = "  ".join(f"{n}={w}" for n, w in sc.items() if n != "summe")
        print(f"           {teile}")
    print(f"\n  Segment: {kurz(k.get('segment',''), 120)}")

    ordner = WURZEL / "ideas" / f"{idee}.angriffe"
    if ordner.is_dir():
        print("\n  Urteile:")
        for linse in repo.LINSEN:
            d = ordner / f"{linse}.md"
            if not d.exists():
                continue
            kopf, _ = frontmatter(d.read_text(encoding="utf-8"))
            print(f"    {linse:11} {kopf.get('urteil','?'):10} "
                  f"{kurz(kopf.get('schwerster_einwand',''), 95)}")
        a = ordner / "anwalt.md"
        if a.exists():
            kopf, rumpf = frontmatter(a.read_text(encoding="utf-8"))
            print(f"\n  Anwalt: {kopf.get('empfehlung','?')} "
                  f"(entkraeftet {kopf.get('entkraeftet','?')}, "
                  f"loesbar {kopf.get('loesbar','?')}, "
                  f"teuer {kopf.get('teuer','?')}, "
                  f"unloesbar {kopf.get('unloesbar','?')})")
            print(f"    {kurz(kopf.get('kern',''), 220)}")
    print()
PY
