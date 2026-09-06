import subprocess, os, re

VREL = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
SREL = "specs/0016-hedgefonds-simulation-echte-weltwirtschaft"
EXE = os.path.abspath(VREL + "/werkzeuge/belegstellen/bau/belegstellen_riegel")
TMP = os.environ.get("TMPDIR", "/tmp")

for w in ["p0126_b2829c8", "p0126_8903184", "p0126_ohne"]:
    p = os.path.join(TMP, w)
    r = subprocess.run([EXE, p + "/vorhaben", p + "/vorgaben"], capture_output=True)
    ganz = r.stdout.decode("utf-8", "replace") + "\n@@STDERR@@\n" + r.stderr.decode("utf-8", "replace")
    print("=====", w, "rc =", r.returncode)
    teil = ganz.split("@@STDERR@@")[1]
    print(teil.strip()[:1500])
    print()
