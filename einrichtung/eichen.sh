#!/usr/bin/env bash
# Setzt die beiden Eichideen auf `entwurf` zurueck und laesst den Fit-Filter erneut
# darueber laufen. Nach jeder Aenderung an grenzen.md aufrufen.
#
#   9001 muss `kandidat` werden.   9002 muss an G5 sterben.
#
# Eine Regel, die 9001 toetet, ist zu scharf. Eine, die 9002 durchlaesst, zu weich.
cd "$HOME/fabrik" || exit 1

for id in 9001-eichung-muss-durchkommen 9002-eichung-muss-sterben; do
  f="ideas/$id.md"
  python3 - "$f" <<'PY'
import re, sys
from pathlib import Path
p = Path(sys.argv[1]); t = p.read_text(encoding="utf-8")
t = re.sub(r"^status: .*$", "status: entwurf", t, count=1, flags=re.M)
t = re.sub(r"^rolle: .*$", "rolle: eichung", t, count=1, flags=re.M)
t = re.sub(r"^ablehnungsgrund: .*$", "ablehnungsgrund: null", t, count=1, flags=re.M)
t = re.sub(r"^(score:\n)(?:  \w+: .*\n)+", "score:\n" + "".join(
    f"  {k}: null\n" for k in
    ("zwang", "erreichbar", "ruhe", "marge", "genehmigung", "summe")), t, count=1, flags=re.M)
p.write_text(t, encoding="utf-8")
PY
done
echo "Eichideen zurueckgesetzt. Fit-Filter laeuft ..."
python3 agents/lauf.py fit-filter

echo
echo "Ergebnis:"
python3 - <<'PY'
import sys
sys.path.insert(0, "agents")
import repo
ROT, GRUEN = "\033[31m", "\033[32m"
AUS = "\033[0m"
soll = {"9001-eichung-muss-durchkommen": "kandidat",
        "9002-eichung-muss-sterben": "abgelehnt"}
fehler = 0
for k in repo.ideen(mit_eichung=True):
    if k.get("typ") != "eichung":
        continue
    ist, will = k.get("status"), soll[k["_id"]]
    ok = ist == will
    fehler += not ok
    farbe = GRUEN if ok else ROT
    print(f"  {farbe}{'OK  ' if ok else 'FEHL'}{AUS}  {k['_id']:34} "
          f"soll {will:10} ist {ist}")
    if not ok:
        print(f"        {k.get('ablehnungsgrund')}")
print()
print("  Die Kette urteilt wie erwartet." if not fehler else
      "  Die Kette weicht ab -- die Begruendung oben nennt die Regel.")
PY
