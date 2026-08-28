#!/usr/bin/env python3
"""Lesender Zugriff auf das Repo-Gedaechtnis.

Was sich deterministisch beantworten laesst, beantwortet kein Agent: Welche Ideen
welchen Status haben, wie viele Angriffe vorliegen, was ein Lauf gekostet hat. Diese
Fragen kosten hier null Tokens und geben immer dieselbe Antwort.
"""

from __future__ import annotations

from pathlib import Path

from lauf import frontmatter

WURZEL = Path(__file__).resolve().parent.parent
IDEEN = WURZEL / "ideas"

# Fuenf unabhaengige Blickwinkel je Kandidat. Recht kam dazu, weil zwei der ersten vier
# Ideen an Erlaubnispflicht starben -- aber erst im Fit-Filter, nach voller Ausarbeitung.
# Vertrieb kam dazu, weil daran Nebenerwerbe am haeufigsten scheitern: nicht am Produkt,
# sondern daran, dass niemand davon erfaehrt.
LINSEN = ("nachfrage", "wettbewerb", "betrieb", "recht", "vertrieb")

# Ab wie vielen "widerlegt" eine Idee stirbt. Bei drei Linsen waren es zwei; bei fuenf
# bleibt es eine einfache Mehrheit.
MEHRHEIT = 3


def ideen(status: str | None = None) -> list[dict]:
    """Alle Ideen, optional nach Status gefiltert. Sortiert nach Score, dann Datei."""
    treffer = []
    for datei in sorted(IDEEN.glob("*.md")):
        kopf, _ = frontmatter(datei.read_text(encoding="utf-8"))
        if not kopf:
            continue
        if status and kopf.get("status") != status:
            continue
        kopf["_datei"] = datei
        kopf["_id"] = kopf.get("id") or datei.stem
        treffer.append(kopf)
    return sorted(treffer, key=lambda k: (-_score(k), str(k["_datei"])))


def _score(kopf: dict) -> int:
    wert = kopf.get("score")
    if isinstance(wert, dict):
        wert = wert.get("summe")
    try:
        return int(wert)
    except (TypeError, ValueError):
        return 0


def angriffe(idee_id: str) -> set[str]:
    """Welche Linsen diese Idee schon angegriffen haben."""
    ordner = IDEEN / f"{idee_id}.angriffe"
    if not ordner.is_dir():
        return set()
    return {d.stem for d in ordner.glob("*.md")}


def offene_angriffe(grenze: int = 2) -> list[tuple[str, str]]:
    """Paare aus (Ideen-ID, Linse) fuer Kandidaten, die noch nicht durchgeprueft sind.

    `grenze` deckelt die Zahl der Ideen je Nacht -- drei Linsen mal viele Kandidaten
    waeren sonst schnell ein zweistelliger Lauf, dessen Ergebnis ohnehin niemand liest.
    """
    auftraege: list[tuple[str, str]] = []
    for kopf in ideen("kandidat")[:grenze]:
        fehlend = [l for l in LINSEN if l not in angriffe(kopf["_id"])]
        auftraege += [(kopf["_id"], linse) for linse in fehlend]
    return auftraege


def bereit_zur_bewertung() -> list[dict]:
    """Kandidaten, bei denen alle Linsen vorliegen -- reif fuer den Vorstand."""
    return [k for k in ideen("kandidat") if angriffe(k["_id"]) >= set(LINSEN)]


SIGNALE = WURZEL / "signals"
RESEARCH = WURZEL / "research"


def offene_recherchen(grenze: int = 6) -> list[str]:
    """Signale, zu denen noch keine Recherche vorliegt -- neueste zuerst.

    Der Rechercheur laeuft je Signal einmal. Was er einmal ausgegraben hat, bleibt
    gueltig, bis jemand es bewusst erneuert -- eine Segmentgroesse aendert sich nicht
    ueber Nacht.
    """
    erledigt = set()
    for d in RESEARCH.glob("*.md"):
        kopf, _ = frontmatter(d.read_text(encoding="utf-8"))
        if kopf.get("signal"):
            erledigt.add(str(kopf["signal"]).strip())

    offen = []
    for sig in sorted(SIGNALE.glob("*/*.md"), reverse=True):
        pfad = sig.relative_to(WURZEL).as_posix()
        if pfad not in erledigt:
            offen.append(pfad)
    return offen[:grenze]
