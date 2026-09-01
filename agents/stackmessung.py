#!/usr/bin/env python3
"""Misst vier Sprachen an derselben Aufgabe.

    python3 agents/stackmessung.py

Vier Argumente ueber den Stack, alle aus fremden Benchmarks. Diese Messung ersetzt sie
durch eigene Zahlen: Uebersetzt es? Wie schnell? Kommen alle vier auf dieselbe
Pruefsumme?

Der Runner uebersetzt und misst -- kein Modell. Was hier steht, ist das Urteil des
Compilers und der Uhr.

Die Aufgabe steht in
`ventures/<venture>/messung-stack/AUFGABE.md`, die Umsetzungen in den
Unterverzeichnissen `rust/`, `cpp/`, `java/` und `python/`.
"""

from __future__ import annotations

import os
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from lauf import WURZEL, jetzt  # noqa: E402

VENTURE = "0016-hedgefonds-simulation-echte-weltwirtschaft"
ORT = WURZEL / "ventures" / VENTURE / "messung-stack"

# (Verzeichnis, Quellmuster, Uebersetzungsbefehl, Startbefehl)
SPRACHEN = [
    ("rust", "*.rs",
     lambda q, w: ["rustc", "-O", "-o", str(w / "schritt"), str(q)],
     lambda q, w: [str(w / "schritt")]),
    ("cpp", "*.cpp",
     lambda q, w: ["g++", "-O2", "-std=c++20", "-o", str(w / "schritt"), str(q)],
     lambda q, w: [str(w / "schritt")]),
    ("java", "*.java",
     lambda q, w: ["javac", "-d", str(w), str(q)],
     lambda q, w: ["java", "-cp", str(w), q.stem]),
    ("python", "*.py", None,
     lambda q, w: ["python3", str(q)]),
]

GLEITKOMMA = re.compile(r"\b(float|double|f32|f64|Float|Double)\b")


def umgebung() -> dict:
    u = dict(os.environ)
    u["PATH"] = str(Path.home() / ".cargo" / "bin") + ":" + u.get("PATH", "")
    return u


def lauf(befehl: list[str], sekunden: int = 600) -> tuple[int, str]:
    try:
        f = subprocess.run(befehl, capture_output=True, text=True, encoding="utf-8",
                           errors="replace", env=umgebung(), timeout=sekunden)
        return f.returncode, (f.stdout or "") + (f.stderr or "")
    except subprocess.TimeoutExpired:
        return -1, f"Zeitueberschreitung nach {sekunden} s"
    except FileNotFoundError as fehlt:
        return -2, f"Werkzeug fehlt: {fehlt}"


def zahl(text: str, feld: str) -> int | None:
    treffer = re.search(rf"^{feld}=(-?\d+)\s*$", text, re.M)
    return int(treffer.group(1)) if treffer else None


def messen() -> list[dict]:
    ergebnisse = []
    for name, muster, uebersetzen, starten in SPRACHEN:
        ordner = ORT / name
        e = {"sprache": name, "vorhanden": ordner.is_dir()}
        ergebnisse.append(e)
        if not e["vorhanden"]:
            continue

        quellen = [q for q in sorted(ordner.glob(muster)) if q.is_file()]
        if not quellen:
            e["fehler"] = f"keine Datei nach Muster {muster}"
            continue
        quelle = quellen[0]
        e["datei"] = quelle.name
        e["zeilen"] = len(quelle.read_text(encoding="utf-8", errors="replace").splitlines())
        e["gleitkomma"] = len(GLEITKOMMA.findall(
            quelle.read_text(encoding="utf-8", errors="replace")))

        if uebersetzen:
            code, text = lauf(uebersetzen(quelle, ordner))
            e["uebersetzt"] = code == 0
            if code != 0:
                e["fehler"] = text.strip()[-1500:]
                continue
        else:
            e["uebersetzt"] = None      # gedeutet, nichts zu uebersetzen

        laeufe = []
        for _ in range(2):
            code, text = lauf(starten(quelle, ordner), sekunden=1800)
            if code != 0:
                e["fehler"] = text.strip()[-1500:]
                break
            laeufe.append(text)
        else:
            e["pruefsumme"] = zahl(laeufe[0], "pruefsumme")
            e["zustand0"] = zahl(laeufe[0], "zustand0")
            e["ns_je_schritt"] = zahl(laeufe[0], "nanosekunden_je_schritt")
            e["wiederholbar"] = (zahl(laeufe[0], "pruefsumme")
                                 == zahl(laeufe[1], "pruefsumme"))
    return ergebnisse


def bericht(ergebnisse: list[dict]) -> str:
    summen = {e["sprache"]: e.get("pruefsumme") for e in ergebnisse
              if e.get("pruefsumme") is not None}
    einig = len(set(summen.values())) == 1 if summen else False

    zeilen = [
        "---",
        "typ: stackmessung",
        f"datum: {jetzt()[:10]}",
        f"sprachen_gemessen: {len(summen)}",
        f"pruefsummen_einig: {'ja' if einig else 'nein'}",
        "---",
        "",
        "# Vier Sprachen, dieselbe Aufgabe",
        "",
        "Erzeugt von `agents/stackmessung.py`. Kein Modell, kein Gutachten -- das",
        "Urteil des Compilers und der Uhr.",
        "",
        "| Sprache | übersetzt | Zeilen | ns/Schritt | wiederholbar | Gleitkomma | Prüfsumme |",
        "|---|---|---:|---:|---|---:|---:|",
    ]
    for e in ergebnisse:
        if not e.get("vorhanden"):
            zeilen.append(f"| {e['sprache']} | *nicht abgegeben* | | | | | |")
            continue
        u = {True: "ja", False: "**nein**", None: "gedeutet"}[e.get("uebersetzt")]
        w = {True: "ja", False: "**nein**"}.get(e.get("wiederholbar"), "—")
        zeilen.append(
            f"| {e['sprache']} | {u} | {e.get('zeilen', '—')} | "
            f"{e.get('ns_je_schritt', '—')} | {w} | {e.get('gleitkomma', '—')} | "
            f"{e.get('pruefsumme', '—')} |")

    zeilen += ["", "## Stimmen die Prüfsummen überein?", ""]
    if not summen:
        zeilen.append("Keine Sprache ist bis zu einem Ergebnis gekommen.")
    elif einig:
        zeilen.append(f"**Ja** — alle {len(summen)} auf `{list(summen.values())[0]}`. "
                      "Damit haben die Umsetzungen dieselbe Rechenvorschrift getroffen, "
                      "und die übrigen Spalten sind vergleichbar.")
    else:
        zeilen.append("**Nein.** Mindestens eine Umsetzung hat die Vorgabe verfehlt:")
        zeilen.append("")
        for s, v in sorted(summen.items()):
            zeilen.append(f"- `{s}`: {v}")
        zeilen.append("")
        zeilen.append("Welche falsch liegt, sagt die Mehrheit — und *dass* eine falsch "
                      "liegt, ist der wertvollere Befund: Er misst, wie zuverlässig ein "
                      "Agent eine präzise Rechenvorschrift in dieser Sprache trifft.")

    for e in ergebnisse:
        if e.get("fehler"):
            zeilen += ["", f"## Fehler bei `{e['sprache']}`", "", "```",
                       e["fehler"], "```"]
    return "\n".join(zeilen) + "\n"


def main() -> int:
    if not ORT.is_dir():
        sys.exit(f"{ORT.relative_to(WURZEL)} gibt es nicht.")
    print(f"[{jetzt()}] Stackmessung in {ORT.relative_to(WURZEL)}")
    ergebnisse = messen()
    ziel = ORT / "BEFUND.md"
    ziel.write_text(bericht(ergebnisse), encoding="utf-8")
    for e in ergebnisse:
        print(f"  {e['sprache']:8} {'-' if not e.get('vorhanden') else ''}"
              f"{'ok' if e.get('pruefsumme') is not None else e.get('fehler', '')[:60]}")
    print(f"  Befund: {ziel.relative_to(WURZEL)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
