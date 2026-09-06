import re, subprocess
W = "/home/adria/fabrik"
P = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml"
BT = chr(96)
commits = subprocess.run(["git", "log", "--format=%h %ad %s", "--date=short",
                          "--", P], cwd=W, capture_output=True, text=True).stdout
zeilen = [z for z in commits.splitlines() if z.strip()]
print("Fassungen der Datei:", len(zeilen))
for z in reversed(zeilen):
    c = z.split()[0]
    t = subprocess.run(["git", "show", c + ":" + P], cwd=W,
                       capture_output=True, text=True).stdout
    mit = re.findall(BT + "([a-z_0-9]*)" + BT + "[*](?![*])", t)
    ohne = re.findall(BT + "([a-z_0-9]*)" + BT + r"[*]", t)
    doppelt = sorted(n for n in set(mit) if mit.count(n) > 1)
    print(z[:70])
    print("    mit Fettdruckfilter: %2d Fundstellen / %2d Namen | ohne: %2d / %2d | Name mit zwei echten Marken: %s"
          % (len(mit), len(set(mit)), len(ohne), len(set(ohne)), doppelt or "keiner"))
