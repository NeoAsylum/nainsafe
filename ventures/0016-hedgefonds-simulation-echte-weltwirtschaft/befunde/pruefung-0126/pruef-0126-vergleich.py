import subprocess, os, sys, re, shutil, tarfile, io

REPO = os.path.abspath(".")
VREL = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
SREL = "specs/0016-hedgefonds-simulation-echte-weltwirtschaft"
EXE = os.path.join(REPO, VREL, "werkzeuge/belegstellen/bau/belegstellen_riegel")
TMP = os.environ.get("TMPDIR", "/tmp")

AUS = ("bau/", "befunde/")


def baue(rev, ziel):
    """Vorhaben und Vorgaben eines Commits nach <ziel> auspacken, ohne bau/ und befunde/."""
    if os.path.isdir(ziel):
        shutil.rmtree(ziel)
    os.makedirs(ziel)
    for rel, unter in ((VREL, "vorhaben"), (SREL, "vorgaben")):
        tar = subprocess.run(["git", "archive", rev, rel], capture_output=True).stdout
        with tarfile.open(fileobj=io.BytesIO(tar)) as t:
            for m in t.getmembers():
                p = m.name[len(rel) + 1:]
                if not p:
                    continue
                if unter == "vorhaben" and p.startswith(AUS):
                    continue
                m.name = p
                t.extract(m, os.path.join(ziel, unter), filter="data")
    return ziel


def messe(wurzel):
    r = subprocess.run([EXE, os.path.join(wurzel, "vorhaben"),
                        os.path.join(wurzel, "vorgaben")], capture_output=True)
    out = r.stdout.decode("utf-8", "replace")
    err = r.stderr.decode("utf-8", "replace")
    ganz = out + err
    m = re.search(r"(\d+) Zitate der geprueften Form gefunden, (\d+) davon aufgeloest.*?(\d+) Fundstellen uebergangen", ganz, re.S)
    zahlen = m.groups() if m else ("?", "?", "?")
    rueck = [l.strip() for l in ganz.splitlines() if "rueckstand" in l.lower()]
    return r.returncode, zahlen, rueck, ganz


FAELLE = [
    ("VORHER  b2829c8 (Bezugsstand)", "b2829c8"),
    ("NACHHER 8903184 (Paket 0126)", "8903184"),
    ("HEUTE   HEAD (nach 0142)", "HEAD"),
]

berichte = {}
for name, rev in FAELLE:
    z = baue(rev, os.path.join(TMP, "p0126_" + rev))
    rc, zahlen, rueck, ganz = messe(z)
    berichte[rev] = ganz
    print(name)
    print("   rc =", rc, " gefunden/aufgeloest/uebergangen =", zahlen)
    print("   Zeilen mit 'rueckstand':", rueck if rueck else "(keine)")

# Zusatzprobe: NACHHER-Kopie ohne rueckstand.md
z = os.path.join(TMP, "p0126_ohne")
baue("8903184", z)
os.remove(os.path.join(z, "vorhaben", "rueckstand.md"))
rc, zahlen, rueck, ganz = messe(z)
print("NACHHER 8903184 OHNE rueckstand.md")
print("   rc =", rc, " gefunden/aufgeloest/uebergangen =", zahlen)
print("   Zeilen mit 'rueckstand':", rueck if rueck else "(keine)")
berichte["ohne"] = ganz

# Uebergangen-Mengen vergleichen
def menge(t):
    return set(re.findall(r"^  (\S+:\d+)\s", t, re.M))

v = menge(berichte["b2829c8"]); n = menge(berichte["8903184"])
print()
print("uebergangen nur VORHER:", sorted(v - n))
print("uebergangen nur NACHHER:", sorted(n - v))
