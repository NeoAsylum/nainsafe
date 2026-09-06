import re, subprocess
W = "/home/adria/fabrik"
P = "ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml"
BT = chr(96)

def blob(c):
    return subprocess.run(["git", "show", c + ":" + P], cwd=W,
                          capture_output=True, text=True, check=True).stdout

neu = blob("84c324b")
zeilen = neu.splitlines()
a, b = zeilen[219], zeilen[1141]
print("Zeile 220:", repr(a))
print("Zeile 1142:", repr(b))
na = a.lstrip("#").strip()
nb = b.lstrip("#").strip()
print("zeichengleich nach Abzug des Kommentarzeichens:", na == nb)
print("Codepoints gleich:", [ord(c) for c in na] == [ord(c) for c in nb])

print()
print("--- Stand am 2026-09-03 (Paket 0053, Commit adfdd37) ---")
alt = blob("adfdd37")
for i, z in enumerate(alt.splitlines(), 1):
    if re.search(BT + "[a-z_0-9]*" + BT + r"\*", z) and "regulierung_start" in z:
        print(i, repr(z))
m03 = re.findall(BT + "([a-z_0-9]*)" + BT + "[*](?![*])", alt)
m03b = re.findall(BT + "([a-z_0-9]*)" + BT + r"[*]", alt)
print("2026-09-03: mit Fettdruckfilter Fundstellen", len(m03), "Namen", len(set(m03)))
print("2026-09-03: ohne Filter Fundstellen", len(m03b), "Namen", len(set(m03b)))
fett03 = re.findall(BT + "([a-z_0-9]+)" + BT + r"\*\*", alt)
print("2026-09-03: Fettdruck-Fundstellen:", fett03)
