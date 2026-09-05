"""Entwurfsfassung des Bezeichnerriegels -- nur zur Messung, nicht ausgeliefert."""
import re, os, sys, collections

WURZEL = sys.argv[1] if len(sys.argv) > 1 else "."


def kerndateien():
    aus = []
    for r, d, f in os.walk(os.path.join(WURZEL, "kern")):
        teile = set(os.path.relpath(r, WURZEL).split(os.sep))
        if "bau" in teile or any(x.startswith(".") for x in teile):
            continue
        for n in sorted(f):
            if n.endswith((".hpp", ".cpp")):
                aus.append(os.path.join(r, n))
    return sorted(aus)


def zerlege(zeile, in_block):
    code = []
    komm = []
    i = 0
    n = len(zeile)
    zustand = "block" if in_block else "code"
    while i < n:
        if zustand == "block":
            j = zeile.find("*/", i)
            if j < 0:
                komm.append(zeile[i:])
                i = n
            else:
                komm.append(zeile[i:j])
                i = j + 2
                zustand = "code"
            continue
        c = zeile[i]
        if c == '"' or c == "'":
            q = c
            code.append(c)
            i += 1
            while i < n:
                if zeile[i] == "\\":
                    code.append(zeile[i:i + 2])
                    i += 2
                    continue
                code.append(zeile[i])
                i += 1
                if zeile[i - 1] == q:
                    break
            continue
        if c == "/" and i + 1 < n and zeile[i + 1] == "/":
            komm.append(zeile[i + 2:])
            i = n
            continue
        if c == "/" and i + 1 < n and zeile[i + 1] == "*":
            i += 2
            zustand = "block"
            continue
        code.append(c)
        i += 1
    return "".join(code), "".join(komm), zustand == "block"


IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
REQ = re.compile(
    r"requires\s*\{\s*&\s*[A-Za-z_][A-Za-z0-9_]*(?:\s*::\s*[A-Za-z_][A-Za-z0-9_]*)*?"
    r"\s*::\s*([A-Za-z_][A-Za-z0-9_]*)\s*;\s*\}")

dateien = kerndateien()
deklariert = set()
codestuecke = []
kommentarzeilen = 0
absaetze = []
zusicherungsnamen = set()
for p in dateien:
    in_block = False
    lauf = None
    for nr, zeile in enumerate(open(p, encoding="utf-8").read().split("\n"), 1):
        code, komm, in_block = zerlege(zeile, in_block)
        codestuecke.append(code + "\n")
        maskiert = code
        for m in REQ.finditer(code):
            zusicherungsnamen.add(m.group(1))
            if len(sys.argv) > 2:
                continue
            a, b = m.start(1), m.end(1)
            maskiert = maskiert[:a] + "\x00" * (b - a) + maskiert[b:]
        for m in IDENT.finditer(maskiert):
            deklariert.add(m.group(0))
        if komm.strip():
            kommentarzeilen += 1
            if lauf is None:
                lauf = [p, nr, [], []]
            lauf[2].append(nr)
            lauf[3].append(komm)
        else:
            if lauf:
                absaetze.append(lauf)
            lauf = None
    if lauf:
        absaetze.append(lauf)
codetext = "".join(codestuecke)

print("Dateien", len(dateien), "Kommentarzeilen", kommentarzeilen,
      "Absaetze", len(absaetze), "deklariert", len(deklariert))
print("Zusicherungsnamen:", sorted(zusicherungsnamen))
for w in ("schreibe", "lege_ab", "lies", "feld"):
    print("   %-10s deklariert=%s" % (w, w in deklariert))


def parameterschluessel():
    aus = set()
    p = os.path.join(WURZEL, "parameter.toml")
    if not os.path.exists(p):
        return aus
    for zeile in open(p, encoding="utf-8"):
        s = zeile.strip()
        m = re.match(r"^([A-Za-z_][A-Za-z0-9_]*)\s*=", s)
        if m:
            aus.add(m.group(1))
        m = re.match(r"^\[+([^\]]+)\]+", s)
        if m:
            for teil in m.group(1).split("."):
                if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", teil):
                    aus.add(teil)
    return aus


def bauziele():
    aus = set()
    for r, d, f in os.walk(WURZEL):
        teile = os.path.relpath(r, WURZEL).split(os.sep)
        if any(x.startswith(".") for x in teile) or "bau" in teile:
            continue
        for n in f:
            if n != "CMakeLists.txt" and not n.endswith(".cmake"):
                continue
            t = open(os.path.join(r, n), encoding="utf-8").read()
            for m in re.finditer(
                    r"add_(?:executable|library|custom_target)\s*\(\s*([A-Za-z_][A-Za-z0-9_]*)", t):
                aus.add(m.group(1))
            for m in re.finditer(r"add_test\s*\(\s*NAME\s+([A-Za-z_][A-Za-z0-9_]*)", t):
                aus.add(m.group(1))
            for m in re.finditer(r"set\s*\(\s*FABRIK_MITGLIEDER(.*?)\)", t, re.S):
                for teil in re.findall(r"[A-Za-z_][A-Za-z0-9_/]*", m.group(1)):
                    for stueck in teil.split("/"):
                        aus.add(stueck)
    return aus


def dateinamen():
    aus = set()
    for r, d, f in os.walk(WURZEL):
        teile = os.path.relpath(r, WURZEL).split(os.sep)
        if any(x.startswith(".") for x in teile) or "bau" in teile:
            continue
        for n in list(f) + list(d):
            aus.add(n)
            aus.add(os.path.splitext(n)[0])
    return {a for a in aus if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", a)}


def vergiftete():
    aus = set()
    for p in dateien:
        for zeile in open(p, encoding="utf-8"):
            m = re.match(r"\s*#\s*pragma\s+GCC\s+poison\s+(.*)$", zeile)
            if m:
                aus.update(re.findall(r"[A-Za-z_][A-Za-z0-9_]*", m.group(1)))
    return aus


SCHLUESSELWORTE = set("""alignas alignof and and_eq asm atomic_cancel atomic_commit
atomic_noexcept auto bitand bitor bool break case catch char char8_t char16_t char32_t
class compl concept const consteval constexpr constinit const_cast continue co_await
co_return co_yield decltype default delete do double dynamic_cast else enum explicit
export extern false float for friend goto if inline int long mutable namespace new
noexcept not not_eq nullptr operator or or_eq private protected public reflexpr register
reinterpret_cast requires return short signed sizeof static static_assert static_cast
struct switch synchronized template this thread_local throw true try typedef typeid
typename union unsigned using virtual void volatile wchar_t while xor xor_eq""".split())

PSCHL = parameterschluessel()
ZIELE = bauziele()
DATEIEN = dateinamen()
GIFT = vergiftete()
print("parameter.toml:", len(PSCHL), " Bauziele:", len(ZIELE), " Dateinamen:", len(DATEIEN),
      " vergiftet:", sorted(GIFT))

KAND = re.compile(r"`([^`\n]*)`")
NAME = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*(?:::[A-Za-z_][A-Za-z0-9_]*)*)(\(\))?$")

fundstellen = []
for datei, start, nrs, zeilen in absaetze:
    absatztext = " ".join(zeilen)
    vorlauf = ""
    for nr, z in zip(nrs, zeilen):
        for m in KAND.finditer(z):
            roh = m.group(1).strip()
            g = NAME.match(roh)
            if not g:
                continue
            voll = g.group(1)
            fundstellen.append((voll.split("::")[-1], voll, datei, nr, absatztext,
                                vorlauf + z[:m.start(0)]))
        vorlauf += z + " "

print("geprueft (Fundstellen):", len(fundstellen),
      " verschieden:", len({k[0] for k in fundstellen}))


BEHAELTER = set()
for p in dateien:
    t = open(p, encoding="utf-8").read()
    BEHAELTER.update(re.findall(r"\bnamespace\s+([A-Za-z_][A-Za-z0-9_]*)", t))
    BEHAELTER.update(re.findall(r"\b(?:class|struct|union)\s+([A-Za-z_][A-Za-z0-9_]*)", t))
    BEHAELTER.update(re.findall(r"\benum\s+(?:class\s+)?([A-Za-z_][A-Za-z0-9_]*)", t))
print("eigene Behaelter:", len(BEHAELTER))

QUELLE = re.compile(r"\[[A-Z][A-Z0-9]{2,}[^\]]*\]")
MARKE = re.compile(r"(?:nicht\s+mehr|hiess|hiessen|frueher|statt|kein|keine|keinen|keiner"
                   r"|nicht|ohne|gegen)\W{0,4}$", re.I)


def regel(letzt, voll, absatz, links):
    if re.fullmatch(r"[A-Z]{1,2}[0-9]{1,3}", letzt):
        return "kennung"
    if (re.fullmatch(r"[0-9a-f]{7,40}", letzt) and re.search(r"[0-9]", letzt)
            and re.search(r"[a-f]", letzt)):
        return "commitkennung"
    if letzt.startswith("__") or re.match(r"^_[A-Z]", letzt):
        return "reserviert"
    if letzt in SCHLUESSELWORTE:
        return "schluesselwort"
    if letzt in GIFT:
        return "vergiftet"
    if letzt in PSCHL:
        return "parameterschluessel"
    if letzt in ZIELE:
        return "bauziel"
    if letzt in DATEIEN:
        return "dateiname"
    if letzt.endswith("_") and any(d.startswith(letzt) and d != letzt for d in deklariert):
        return "namensvorsilbe"
    if any(d != letzt and d.startswith(letzt) and ("`%s`" % d) in absatz for d in deklariert):
        return "namensteil"
    if MARKE.search(links):
        return "abgelegter_name"
    if "::" in voll and voll.split("::")[0] not in BEHAELTER:
        return "fremder_behaelter"
    if "http://" in absatz or "https://" in absatz or QUELLE.search(absatz):
        return "quellenangabe"
    if "_" not in letzt and "::" not in voll and letzt not in codetext:
        return "fremdwort"
    return None


befunde = collections.defaultdict(list)
uebergangen = collections.defaultdict(list)
for letzt, voll, datei, nr, absatz, links in fundstellen:
    if letzt in deklariert:
        continue
    g = regel(letzt, voll, absatz, links)
    if g:
        uebergangen[(letzt, g)].append((datei, nr))
    else:
        befunde[letzt].append((datei, nr))

print("\nuebergangen:", sum(len(v) for v in uebergangen.values()), "Fundstellen,",
      len(uebergangen), "Faelle")
for (k, g) in sorted(uebergangen):
    print("   %-24s %-18s %s" % (k, g, uebergangen[(k, g)][0]))
print("\nBEFUNDE:", len(befunde))
for k in sorted(befunde):
    print("   %-24s %s" % (k, befunde[k]))
