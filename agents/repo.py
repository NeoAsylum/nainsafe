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


def offene_anwaelte(grenze: int = 10) -> list[str]:
    """Kandidaten mit vollstaendigen Angriffen, aber ohne Verteidigung.

    Der Anwalt laeuft nach den Skeptikern und vor dem Vorstand: Er prueft, ob die
    Einwaende loesbar sind, statt sie als Endurteil zu nehmen. In fast jeder
    Angriffsdatei steht ein Abschnitt "Was ihn entkraeften wuerde" -- ohne diese Rolle
    liest ihn niemand.
    """
    offen = []
    for k in ideen("kandidat"):
        vorhanden = angriffe(k["_id"])
        if vorhanden >= set(LINSEN) and "anwalt" not in vorhanden:
            offen.append(k["_id"])
    return offen[:grenze]


def bereit_zur_bewertung() -> list[dict]:
    """Kandidaten, bei denen alle Linsen UND die Verteidigung vorliegen.

    Ohne den Anwalt bewertet der Vorstand nur die Anklage.
    """
    noetig = set(LINSEN) | {"anwalt"}
    return [k for k in ideen("kandidat") if angriffe(k["_id"]) >= noetig]


SIGNALE = WURZEL / "signals"
RESEARCH = WURZEL / "research"
QUELLEN = WURZEL / "quellen.yml"


def _schluessel(text: str) -> str:
    """Vergleichsform: klein, ohne Umlaute, nur Buchstaben."""
    t = text.lower()
    for alt, neu in (("ä", "ae"), ("ö", "oe"), ("ü", "ue"), ("ß", "ss")):
        t = t.replace(alt, neu)
    return "".join(c for c in t if c.isalpha())


def _liste(schluessel: str) -> list[str]:
    """Ein Aufzaehlungsblock aus quellen.yml.

    Bewusst ein Zeilenleser statt PyYAML: Die Fabrik soll auf einem frischen VPS
    ohne Paketinstallation laufen, und diese Bloecke haben ein festes Format.
    """
    if not QUELLEN.exists():
        return []
    eintraege, drin = [], False
    for zeile in QUELLEN.read_text(encoding="utf-8").splitlines():
        if zeile.strip().startswith(schluessel + ":"):
            drin = True
            continue
        if drin:
            roh = zeile.strip()
            if roh.startswith("- "):
                eintraege.append(roh[2:].strip().strip("\"'"))
            elif roh and not roh.startswith("#"):
                break  # naechster Schluessel, Block zu Ende
    return eintraege


def segmentliste() -> list[str]:
    """Der Suchraum des Markt-Analysten: Branchen."""
    return _liste("segmente")


def vorgangsliste() -> list[str]:
    """Der Suchraum des Prozess-Analysten: Vorgaenge.

    Die zweite Achse, seit ADR 0005. Der Markt-Analyst schneidet nach Branche, der
    Prozess-Analyst nach Vorgang -- und zwar auf denselben Daten: Jedes Marktprofil
    nennt in `handarbeit` genau einen Vorgang. Sechzehn Segmente galten einzeln als
    zu klein; ueber den Vorgang zusammengefasst ist keines davon klein.
    """
    return _liste("vorgaenge")


def offene_segmente() -> list[str]:
    """Segmente ohne Marktprofil, in der Reihenfolge der Liste.

    Drei Kennungen je Profil, in dieser Rangfolge:

    1. `auftrag` -- der Listeneintrag im Wortlaut, seit 2026-08-29 Pflichtfeld. Nur
       dieser Vergleich ist exakt und damit verlaesslich.
    2. das `segment`-Feld. Der Analyst benennt Segmente fachlich praeziser um: aus
       "Kaelte- und Klimaanlagenwartung" wurde "Kaelteanlagenbauerhandwerk", und aus
       "Tierarztpraxen" wurde "Tierarztpraxen in Deutschland (niedergelassene ...)".
       Der Auftrag steckt dann noch drin, aber laenger.
    3. der Dateiname ohne Datum. Er behaelt den Auftrag meist unveraendert.

    Fuer 2 und 3 gilt nur eine Richtung: **der Listeneintrag muss im Profilnamen
    stecken**, nicht umgekehrt. Die Gegenrichtung hat beim Oeffnen des Suchraums
    prompt danebengegriffen -- "Tierarztpraxen im englischsprachigen Raum" galt als
    erledigt, weil ein Profil ueber deutsche Tierarztpraxen existierte. Es ist ein
    anderer Markt mit anderer Groesse; genau darum steht er auf der Liste.
    """
    bearbeitet, auftraege = [], set()
    for d in (SIGNALE / "maerkte").glob("*.md"):
        kopf, _ = frontmatter(d.read_text(encoding="utf-8"))
        if kopf.get("auftrag"):
            auftraege.add(_schluessel(str(kopf["auftrag"])))
        bearbeitet.append(_schluessel(str(kopf.get("segment", ""))))
        bearbeitet.append(_schluessel(d.stem[11:] if d.stem[:2].isdigit() else d.stem))

    offen = []
    for s in segmentliste():
        k = _schluessel(s)
        if k in auftraege:
            continue
        if any(k in b for b in bearbeitet if len(b) > 6):
            continue
        offen.append(s)
    return offen


def offene_prozesse() -> list[str]:
    """Vorgaenge ohne Prozessprofil, in der Reihenfolge der Liste.

    Wie `offene_segmente`, aber ohne dessen Altlast: Das Feld `auftrag` ist hier von
    Anfang an Pflicht, ein Fuzzy-Vergleich also nicht noetig.
    """
    ordner = SIGNALE / "prozesse"
    erledigt = set()
    if ordner.is_dir():
        for d in ordner.glob("*.md"):
            kopf, _ = frontmatter(d.read_text(encoding="utf-8"))
            if kopf.get("auftrag"):
                erledigt.add(_schluessel(str(kopf["auftrag"])))
    return [v for v in vorgangsliste() if _schluessel(v) not in erledigt]


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
        # Marktprofile brauchen keine Recherche -- sie SIND welche. Der Markt-Analyst
        # beantwortet dieselben Fragen bereits mit Quellen; ein Rechercheur darauf
        # waere rund fuenf Dollar fuer eine zweite Fassung derselben Arbeit.
        if sig.parent.name == "maerkte":
            continue
        pfad = sig.relative_to(WURZEL).as_posix()
        if pfad not in erledigt:
            offen.append(pfad)
    return offen[:grenze]
