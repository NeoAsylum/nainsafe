#!/usr/bin/env python3
"""Faehrt die Bauphase: Arbeitspakete statt Rollen.

    python3 agents/baulauf.py [venture] [--trocken] [--gleichzeitig N]

Der Unterschied zu allen frueheren Ketten: Hier steht nicht fest, welche Rolle wann
laeuft. Es steht fest, welche **Arbeitspakete** offen sind; die Rolle ergibt sich aus
dem Paket.

Damit wird "zwei Backend-Entwickler" zu dem, was es hier sein muss. Zwei Agenten mit
derselben Rollendatei, die dieselben Dateien lesen, produzieren dieselbe Arbeit zweimal
oder schreiben sich gegenseitig ueber -- die Fabrik hat das beim Markt-Analysten schon
einmal gelernt. Zwei Agenten mit **zwei verschiedenen Paketen** arbeiten wirklich
parallel. Die Zahl der gleichzeitigen Bauagenten ist deshalb keine Rollenfrage, sondern
eine Frage des Rueckstands.

Ablauf je Lauf:

  1. projektmanager       zerlegt und entblockiert -- immer zuerst, sonst laufen die
                          Bauagenten leer
  2. Bau                  alle offenen Pakete ohne offene Abhaengigkeit, parallel
  3. Review               je Gewerk ein Pruefer auf jedes gebaute Paket
  4. Pruefung             selbstspieler, rueckvergleicher, bruchtester
  5. geschaeftsfuehrer    schreibt ops/plan.md fuer den Betreiber

Der Zustand eines Arbeitspakets:

    offen --Bauagent--> gebaut --Pruefer--> (Befund) --Projektmanager--> fertig
                                                 |
                                                 +--> zurueck --> wieder offen

Der Bauagent setzt `gebaut`, nie `fertig`. Nur der Projektmanager setzt `fertig`, und
nur, wenn ein Pruefbefund mit `urteil: geprueft` vorliegt. Damit kann keine Rolle ihre
eigene Arbeit abnehmen -- das ist der ganze Zweck der Reviewstufe.
"""

from __future__ import annotations

import os
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from lauf import WURZEL, frontmatter, jetzt, lauf  # noqa: E402
from nachtlauf import phase  # noqa: E402

BAUROLLEN = {"datenbauer", "kernbauer", "oberflaechenbauer", "auslieferer",
             "testentwickler"}
PRUEFROLLEN = {"selbstspieler", "rueckvergleicher", "bruchtester"}

# Je Gewerk ein Pruefer. Er liest das Arbeitspaket und das Ergebnis -- aber
# ausdruecklich NICHT das Logbuch des Bauagenten. Das ist dieselbe Blindheit, die die
# fuenf Angriffslinsen wirksam gemacht hat: Wer die Begruendung liest, uebernimmt sie
# und prueft dann die Absicht statt das Ergebnis.
REVIEW = {
    "datenbauer": "daten-pruefer",
    "kernbauer": "kern-pruefer",
    "oberflaechenbauer": "oberflaechen-pruefer",
    "auslieferer": "auslieferungs-pruefer",
    "testentwickler": "test-pruefer",
    "architekt": "entwurf-pruefer",
    "spielentwerfer": "entwurf-pruefer",
}

# Zwei Pakete, die dieselbe Datei anfassen, duerfen nicht gleichzeitig laufen. Das ist
# der Grund fuer das Feld `dateien` im Paket -- ohne diese Pruefung ueberschreiben sich
# zwei Bauagenten, und der Verlust faellt erst Tage spaeter auf.
GLEICHZEITIG = 4

# Wie oft ein Paket zurueckgehen darf, bevor nicht mehr der Bauagent das Problem ist,
# sondern sein Abnahmekriterium. Dieselbe Bremse wie konzeptlauf.py:RUECKLAUF_MAX --
# und sie fehlte hier, worauf der Geschaeftsfuehrer im ersten Lauf hinwies: "Im Baulauf
# gibt es keine entsprechende Grenze; dieselbe Nichtkonvergenz kostet dort Code statt
# Prosa."
RUECKLAUF_MAX = 3

ANSI = re.compile(chr(27) + r"\[[0-9;]*m")
NL = chr(10)          # Zeilenumbruch als Konstante -- haelt die Textbausteine lesbar


def uebersetzen(venture: str) -> str | None:
    """Ruft den Compiler und legt sein Urteil als Befund ab.

    Der Grund, warum das hier steht und nicht in einer Rolle: Kein Bauagent hat eine
    Shell. Das ist Absicht -- eine Shell umgeht jede Edit()-Sperre, nachgemessen am
    2026-08-30. Die Folge war aber ein Fehler: Ein Agent, der Code schreiben soll und
    ihn nie uebersetzen kann, schreibt am Ende Prosa. Genau das ist am 2026-09-01
    passiert -- ein voller Baulauf, vier Markdown-Dateien, null Zeilen Rust.

    Also laeuft der Compiler dort, wo ohnehin kein Modell sitzt: im Runner. Sein Urteil
    wird eine Datei, und Dateien koennen alle lesen. Dasselbe Muster wie die Berichte
    im Wochenlauf.
    """
    wurzel = WURZEL / "ventures" / venture
    ziel = wurzel / "befunde" / f"uebersetzung-{jetzt()[:10]}.md"
    ziel.parent.mkdir(parents=True, exist_ok=True)

    # Die Bauart wird am Projekt erkannt, nicht an einer Konstante. Bis zum 2026-09-01
    # rief diese Funktion fest `cargo` -- und beim Wechsel auf C++ waere sie stumm
    # falsch geworden statt laut. Ein Runner, der eine Sprache voraussetzt, ist ein
    # Runner, der beim naechsten Vorhaben neu geschrieben werden muss.
    bauart, manifeste = None, []
    for name, art in (("CMakeLists.txt", "cmake"), ("Cargo.toml", "cargo")):
        gefunden = [m for m in sorted(wurzel.rglob(name)) if "befunde" not in m.parts]
        if gefunden:
            bauart, manifeste = art, gefunden
            break
    if not bauart:
        quellen = [q for q in wurzel.rglob("*.cpp") if "messung-stack" not in q.parts]
        if quellen:
            bauart, manifeste = "cpp-blank", quellen

    # Nichts gefunden heisst NICHT "ok". Genau diese Verwechslung hatte mein eigener
    # Patch am 2026-09-01 eingebaut: kein Quelltext, keine Fehler, also "ergebnis: ok"
    # -- die gefaehrlichste Rueckmeldung ueberhaupt, weil sie das Ausbleiben von Arbeit
    # wie gelungene Arbeit aussehen laesst.
    if not manifeste:
        ziel.write_text(
            "---" + NL + "typ: uebersetzung" + NL + f"venture: {venture}" + NL
            + f"datum: {jetzt()[:10]}" + NL + "ergebnis: kein_quelltext" + NL + "---"
            + NL + NL + "# Es gibt nichts zu uebersetzen" + NL + NL
            + f"Unter `ventures/{venture}/` liegt weder eine `CMakeLists.txt` noch eine"
            + NL + "Quelldatei. Gefunden wurden nur Textdateien." + NL + NL
            + "**Das ist ein Befund, kein Zustand.** Ein Bauagent liefert Quelldateien,"
            + NL + "keine Dokumente ueber Quelldateien. Wer ein Paket auf `gebaut`"
            + NL + "setzt, ohne dass danach etwas uebersetzbar ist, hat es nicht"
            + NL + "gebaut." + NL + NL
            + f"Der Kern gehoert nach `ventures/{venture}/kern/` mit eigener"
            + NL + "`CMakeLists.txt`." + NL, encoding="utf-8")
        return "kein_quelltext"

    umgebung = dict(os.environ)
    umgebung["PATH"] = str(Path.home() / ".cargo" / "bin") + ":" + umgebung.get("PATH", "")
    ausgaben, schlecht = [], False

    def befehle(bauart: str, manifest: Path) -> list[list[str]]:
        """Uebersetzen und pruefen, je nach erkannter Bauart.

        Die C++-Schalter sind keine Geschmacksfrage, sie stehen in ADR 0011:
        `-fwrapv` macht vorzeichenbehafteten Ueberlauf zu definiertem Umbruch -- die
        Gefahr ist nicht der Ueberlauf, sondern was ein Optimierer aus seiner
        angeblichen Unmoeglichkeit folgert. Die Sanitizer machen im Testlauf laut, was
        sonst still bliebe.
        """
        if bauart == "cargo":
            return [["cargo", "build", "--manifest-path", str(manifest)],
                    ["cargo", "test", "--manifest-path", str(manifest)]]
        if bauart == "cmake":
            bau = manifest.parent / "bau"
            return [["cmake", "-S", str(manifest.parent), "-B", str(bau),
                     "-DCMAKE_BUILD_TYPE=RelWithDebInfo",
                     "-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math"],
                    ["cmake", "--build", str(bau), "--parallel"],
                    ["ctest", "--test-dir", str(bau), "--output-on-failure"]]
        return [["g++", "-std=c++20", "-O2", "-fwrapv", "-fno-fast-math",
                 "-Wall", "-Wextra", "-o", str(manifest.with_suffix("")), str(manifest)]]

    for manifest in manifeste:
        for befehl in befehle(bauart, manifest):
            try:
                fertig = subprocess.run(befehl, cwd=WURZEL, capture_output=True,
                                        text=True, encoding="utf-8", errors="replace",
                                        env=umgebung, timeout=900)
                code, text = fertig.returncode, (fertig.stdout or "") + (fertig.stderr or "")
            except subprocess.TimeoutExpired:
                code, text = -1, "Zeitueberschreitung nach 900 s."
            except FileNotFoundError:
                code, text = -1, f"{befehl[0]} nicht gefunden -- Werkzeugkette fehlt."
            schlecht = schlecht or code != 0
            ausgaben.append(
                "## `" + " ".join(befehl[:2]) + "` -- "
                + ("FEHLER" if code else "ok")
                + " (Code " + str(code) + ")\n\n"
                + "```\n" + ANSI.sub("", text).strip()[-6000:] + "\n```\n")
            if code != 0:
                break          # ein gescheiterter Schritt macht die folgenden sinnlos

    ergebnis = "fehler" if schlecht else "ok"
    ziel.write_text(f"""---
typ: uebersetzung
venture: {venture}
datum: {jetzt()[:10]}
bauart: {bauart}
manifeste: {len(manifeste)}
ergebnis: {ergebnis}
---

# Der Compiler hat gesprochen: {ergebnis}

Erzeugt vom Baulauf, nicht von einem Modell. Was hier steht, ist keine Einschaetzung
und keine Meinung -- es ist das Urteil des Uebersetzers. Ein Pruefer, der etwas
anderes behauptet, irrt.

""" + "\n".join(ausgaben), encoding="utf-8")
    return ergebnis


def pakete(venture: str) -> list[dict]:
    ordner = WURZEL / "ventures" / venture / "aufgaben"
    if not ordner.is_dir():
        return []
    alle = []
    for d in sorted(ordner.glob("*.md")):
        kopf, _ = frontmatter(d.read_text(encoding="utf-8"))
        if not kopf:
            continue
        kopf["_id"] = kopf.get("id") or d.stem
        kopf["_dateien"] = {s.strip() for s in
                            str(kopf.get("dateien", "")).strip("[]").split(",") if s.strip()}
        kopf["_haengt"] = {s.strip() for s in
                           str(kopf.get("haengt_an", "")).strip("[]").split(",") if s.strip()}
        alle.append(kopf)
    return alle


def rueckläufe(venture: str, paket: str) -> int:
    """Wie oft dieses Paket schon zurueckgewiesen wurde."""
    ordner = WURZEL / "ventures" / venture / "befunde"
    if not ordner.is_dir():
        return 0
    n = 0
    for d in ordner.glob("pruefung-" + paket + "-*.md"):
        kopf, _ = frontmatter(d.read_text(encoding="utf-8"))
        n += kopf.get("urteil") == "zurueck"
    return n


def startbereit(alle: list[dict], rollen: set[str], zustand: str = "offen") -> list[dict]:
    """Pakete im genannten Zustand, deren Abhaengigkeiten fertig sind --
    und die sich nicht in denselben Dateien treffen."""
    fertig = {p["_id"] for p in alle if p.get("status") == "fertig"}
    dran, belegt = [], set()
    for p in alle:
        if p.get("status") != zustand or p.get("rolle") not in rollen:
            continue
        if p["_haengt"] - fertig:
            continue
        if p["_dateien"] & belegt:
            continue  # kollidiert mit einem schon eingeplanten Paket
        belegt |= p["_dateien"]
        dran.append(p)
    return dran


def main(venture: str, trocken: bool = False, gleichzeitig: int = GLEICHZEITIG) -> int:
    alle = pakete(venture)
    zaehl = {z: len([p for p in alle if p.get("status") == z])
             for z in ("offen", "gebaut", "zurueck", "fertig", "blockiert")}

    print(f"[{jetzt()}] Baulauf {venture} -- "
          + ", ".join(f"{n} {z}" for z, n in zaehl.items() if n))
    if not alle:
        print("  Noch keine Arbeitspakete.")

    bau = startbereit(alle, BAUROLLEN)[:gleichzeitig]
    pruef = startbereit(alle, PRUEFROLLEN)[:gleichzeitig]

    review = [p for p in alle if p.get("status") == "gebaut" and p.get("rolle") in REVIEW]

    if trocken:
        print("  1. projektmanager")
        print(f"  2. Bau        {len(bau)} Pakete gleichzeitig")
        for p in bau:
            print(f"       {p.get('rolle'):18} {p['_id']}")
        print(f"  3. Review     {len(review[:gleichzeitig])} Pakete")
        for p in review[:gleichzeitig]:
            print(f"       {REVIEW[p['rolle']]:18} {p['_id']}")
        print(f"  4. Pruefung   {len(pruef)} Pakete")
        for p in pruef:
            print(f"       {p.get('rolle'):18} {p['_id']}")
        print("  5. geschaeftsfuehrer")
        if not alle:
            print()
            print("  Es gibt noch keine Arbeitspakete. Der erste Lauf legt sie an --")
            print("  der Projektmanager liest specs/ und zerlegt sie.")
        return 0

    # Konvergenzbremse, bevor Tokens fliessen: Ein Paket, das RUECKLAUF_MAX Mal
    # zurueckgewiesen wurde, geht nicht noch einmal in den Bau. Dann ist nicht der
    # Bauagent das Problem, sondern sein Abnahmekriterium -- und das aendert kein
    # weiterer Versuch, sondern der Projektmanager oder der Betreiber.
    for q in alle:
        if q.get("status") in ("offen", "gebaut") and                 rueckläufe(venture, q["_id"]) >= RUECKLAUF_MAX:
            print(f"  FESTGEFAHREN: {q['_id']} ist {RUECKLAUF_MAX} Mal zurueckgewiesen "
                  "worden -- zu pruefen ist das Abnahmekriterium, nicht die Arbeit.")

    fehler = 0

    # Immer zuerst: ohne Rueckstand laufen die Bauagenten leer.
    if lauf("projektmanager", venture) != 0:
        fehler += 1
        print("  projektmanager fehlgeschlagen -- Kette laeuft weiter.")

    alle = pakete(venture)
    bau = [q for q in startbereit(alle, BAUROLLEN)
           if rueckläufe(venture, q["_id"]) < RUECKLAUF_MAX][:gleichzeitig]
    if bau:
        fehler += phase("Bau", [(p["rolle"], p["_id"]) for p in bau])

    # Der Compiler urteilt vor dem Pruefer. Findet er etwas, weiss der Pruefer es schon,
    # wenn er liest -- und muss es nicht selbst suchen.
    ergebnis = uebersetzen(venture)
    print(f"  Uebersetzung: {ergebnis}")

    # Review: jedes gebaute Paket bekommt einen Pruefer seines Gewerks. Er liest den
    # Auftrag und das Ergebnis, nicht die Begruendung des Bauagenten.
    alle = pakete(venture)
    review = [p for p in alle if p.get("status") == "gebaut"
              and p.get("rolle") in REVIEW][:gleichzeitig]
    if review:
        fehler += phase("Review",
                        [(REVIEW[p["rolle"]], p["_id"]) for p in review])

    alle = pakete(venture)
    pruef = startbereit(alle, PRUEFROLLEN)[:gleichzeitig]
    if pruef:
        fehler += phase("Pruefung", [(p["rolle"], p["_id"]) for p in pruef])

    if lauf("geschaeftsfuehrer", venture) != 0:
        fehler += 1

    uebrig = len([p for p in pakete(venture) if p.get("status") == "offen"])
    print(f"[{jetzt()}] Baulauf beendet, {fehler} Fehler. {uebrig} Pakete offen.")
    plan = WURZEL / "ops" / "plan.md"
    if plan.exists():
        print(f"  Bericht fuer den Betreiber: {plan.relative_to(WURZEL)}")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    n = GLEICHZEITIG
    if "--gleichzeitig" in sys.argv:
        n = int(sys.argv[sys.argv.index("--gleichzeitig") + 1])
    if args:
        v = args[0]
    else:
        vs = sorted(p.name for p in (WURZEL / "ventures").iterdir() if p.is_dir())
        if len(vs) != 1:
            sys.exit("Aufruf: python3 agents/baulauf.py <venture>\n"
                     "Vorhanden: " + (", ".join(vs) or "keins"))
        v = vs[0]
    sys.exit(main(v, "--trocken" in sys.argv, n))
