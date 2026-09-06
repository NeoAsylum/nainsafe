import glob, re, os
for p in sorted(glob.glob("aufgaben/*.md")):
    t = open(p, encoding="utf-8").read()
    kopf = t.split("---")[1] if t.startswith("---") else ""
    st = re.search(r"^status:\s*(\S+)", kopf, re.M)
    da = re.search(r"^dateien:\s*(.*)$", kopf, re.M)
    if da and "parameter.toml" in da.group(1):
        print("%-8s %s" % (st.group(1) if st else "?", os.path.basename(p)))
