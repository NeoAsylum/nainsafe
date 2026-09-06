import subprocess, re

V = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
P = V + "/rueckstand.md"

commits = subprocess.run(["git", "log", "--format=%h %ad", "--date=short", "--", P],
                         capture_output=True).stdout.decode().splitlines()
print("Versionen von rueckstand.md:", len(commits))

AUF = chr(0x201e)   # „
ZU = chr(0x201c)    # “
ASCII = chr(0x22)

treffer = {}
for zeile in commits:
    c = zeile.split()[0]
    txt = subprocess.run(["git", "show", c + ":" + P], capture_output=True).stdout.decode("utf-8", "replace")
    for l in txt.splitlines():
        if "in der Spalte" in l and "Rolle" in l:
            m = re.search(r"Spalte (.)Rolle(.)", l)
            key = (hex(ord(m.group(1))), hex(ord(m.group(2)))) if m else ("?", "?")
            treffer.setdefault(key, []).append(c)
for k, v in treffer.items():
    print("Anfuehrungszeichen", k, "in", len(v), "Fassungen, z.B.", v[:5])

# Kommt der Wortlaut mit geschweiftem Schlusszeichen irgendwo im Repo vor?
out = subprocess.run(["git", "grep", "-l", "Spalte " + AUF + "Rolle" + ZU, "HEAD"],
                     capture_output=True).stdout.decode()
print("--- HEAD-Dateien mit " + AUF + "Rolle" + ZU + ":")
print(out or "(keine)")
out2 = subprocess.run(["git", "grep", "-l", "Spalte " + AUF + "Rolle" + ASCII, "HEAD"],
                      capture_output=True).stdout.decode()
print("--- HEAD-Dateien mit " + AUF + "Rolle" + ASCII + ":")
print(out2 or "(keine)")
