import subprocess, os, re, shutil

V = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
S = "specs/0016-hedgefonds-simulation-echte-weltwirtschaft"
EXE = os.path.abspath(V + "/werkzeuge/belegstellen/bau/belegstellen_riegel")
TMP = os.environ.get("TMPDIR", "/tmp")


def lauf(p):
    r = subprocess.run([EXE, p + "/vorhaben", p + "/vorgaben"], capture_output=True)
    return r.returncode, r.stdout + r.stderr


# --- Wiederholbarkeit: zweimal derselbe Aufruf, bitgleich? ---
p = os.path.join(TMP, "p0126_8903184")
rc1, a = lauf(p)
rc2, b = lauf(p)
print("Riegel zweimal auf demselben Baum: rc", rc1, rc2, "| bitgleich:", a == b,
      "|", len(a), "Bytes")

# tomllib zweimal auf denselben Bytes -> schon in pruef-0126-bilanz.py belegt

# --- Woher die 46 -> 54 zwischen Paketstand und HEAD kommen ---
def uebergangen(p):
    _, t = lauf(p)
    return re.findall(r"^  (\S+:\d+)  \((.*?)\)\n      gesucht war: (.*)$",
                      t.decode("utf-8", "replace"), re.M)


n = uebergangen(os.path.join(TMP, "p0126_8903184"))
h = uebergangen(os.path.join(TMP, "p0126_HEAD"))
print()
print("uebergangen Paketstand:", len(n), " HEAD:", len(h))
sn = set((x[1], x[2]) for x in n)
sh = set((x[1], x[2]) for x in h)
print("nur bei HEAD (also von 0142 dazugekommen):")
for x in sorted(sh - sn):
    print("   ", x)
print("nur beim Paketstand:")
for x in sorted(sn - sh):
    print("   ", x)

# --- Aufraeumen: Pruefskripte in einen eigenen Ordner ---
ziel = os.path.join(V, "befunde", "pruefung-0126")
os.makedirs(ziel, exist_ok=True)
for f in sorted(os.listdir(os.path.join(V, "befunde"))):
    if f.startswith("pruef-0126-") and f.endswith(".py"):
        shutil.move(os.path.join(V, "befunde", f), os.path.join(ziel, f))
        print("verschoben:", f)
