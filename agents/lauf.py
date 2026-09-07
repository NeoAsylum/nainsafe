#!/usr/bin/env python3
"""Fuehrt einen einzelnen Agentenlauf aus.

    python agents/lauf.py <rolle> [gegenstand]

Eine Rolle ist eine Datei unter agents/rollen/<rolle>.md. Ihr Frontmatter legt fest,
welche Werkzeuge der Lauf bekommt -- das ist die Durchsetzung der Schreibrechte aus
CLAUDE.md. Nicht der Prompt haelt einen Agenten davon ab, ins falsche Verzeichnis zu
schreiben, sondern das fehlende Werkzeug.

Der Rumpf der Rollendatei ist der Auftrag und geht unveraendert an das Modell.
"""

from __future__ import annotations

import json
import re
import os
import shutil
import sqlite3
import subprocess
import time
import sys
from datetime import datetime, timedelta, timezone
from pathlib import Path

WURZEL = Path(__file__).resolve().parent.parent
ROLLEN = WURZEL / "agents" / "rollen"
DB = WURZEL / "state.db"
SCHEMA = WURZEL / "schema" / "state.sql"

# Berechtigungsmodus. "dontAsk" verweigert alles, was nicht ausdruecklich in der
# Werkzeugliste der Rolle steht -- ohne Rueckfrage, was im unbeaufsichtigten Lauf der
# einzig sinnvolle Umgang mit einer Rueckfrage ist.
#
# Ausdruecklich NICHT "acceptEdits": dieser Modus genehmigt Dateiaenderungen im ganzen
# Arbeitsverzeichnis und wuerde damit die Rollentrennung aufheben -- der Regel-Scout
# koennte Ideen schreiben. Aeltere Claude-Code-Versionen kennen "dontAsk" nicht; dort
# ist "default" der Ersatz (Werkzeuge ausserhalb der Liste loesen dann eine Rueckfrage
# aus, die unbeaufsichtigt ebenfalls scheitert -- gleiches Ergebnis, langsamer).
MODUS = "dontAsk"

# Zweite Verteidigungslinie: was kein Agent jemals darf, unabhaengig von seiner Rolle.
# Deny sticht Allow, auch wenn eine Rolle sich das Werkzeug in ihr Frontmatter schreibt.
NIE = [
    # **Bash als Ganzes.** Gemessen am 2026-09-06 mit den exakten Schaltern der Fabrik
    # (Werkzeugliste des kernbauer, diese Sperrliste, Modus dontAsk): Der Agent legte per
    # `echo > specs/...` und per `python3 -c` Dateien AUSSERHALB seiner Edit()-Pfade an --
    # null Verweigerungen. Nur `tee` scheiterte, weil `Bash(tee:*)` unten steht.
    #
    # `--allowedTools` erlaubt vorab, es beschraenkt nicht. Im Modus dontAsk laeuft alles,
    # was nicht ausdruecklich hier steht. Die Zeilen darunter sperrten also einzelne
    # Befehlsanfaenge, waehrend die Shell selbst offen stand -- und das Repo beschrieb
    # seit dem 2026-08-30 eine Grenze, die es nie gab ("Keine Rolle hat eine Shell").
    # Daher kamen die Schattenkopien unter bau/, die 329-Dateien-Commits und die
    # Logbuecher voller Katalogen, welcher Aufruf "durchgeht".
    #
    # Was ein Agent an Werkzeugausgabe braucht, erzeugt der Runner (Compiler, Tests,
    # Berichte) und legt es als Datei hin. Die Zeilen darunter bleiben als zweite Linie.
    "Bash",
    # Regel 1 und 2 aus CLAUDE.md -- kein Geld ausgeben, nichts nach aussen schreiben.
    "Bash(git push:*)",
    "Bash(git remote:*)",
    "Bash(gh:*)",
    "Bash(curl:*)",
    "Bash(wget:*)",
    "Bash(npm publish:*)",
    "Bash(rm:*)",
    "Bash(pip install:*)",
    # Eine Shell umgeht jede Edit()-Sperre. Nur eine Rolle hat ueberhaupt Bash
    # (der Verbesserer, und dort nur als Aufruf benannter lesender Skripte); diese
    # Sperren sind die zweite Linie fuer den Fall, dass jemand das wieder aufweicht.
    "Bash(sed:*)",
    "Bash(tee:*)",
    "Bash(cp:*)",
    "Bash(mv:*)",
    "Bash(chmod:*)",
    "Bash(git commit:*)",
    "Bash(git checkout:*)",
    "Bash(git reset:*)",
    # Die Fabrik schreibt die Regeln nicht um, nach denen sie beurteilt wird.
    # Ein Fit-Filter, der grenzen.md aendern koennte, hat keine Grenzen.
    #
    # Ausschliesslich Edit(), nie Write(): Claude Code prueft Dateirechte allein gegen
    # Edit()- und Read()-Regeln. Eine Write()-Pfadregel wird zwar angenommen, aber nie
    # ausgewertet -- sie sieht wie Schutz aus und ist keiner. Edit() deckt alle
    # eingebauten Werkzeuge ab, die Dateien aendern, das Anlegen neuer Dateien
    # eingeschlossen.
    "Edit(/CLAUDE.md)",
    "Edit(/grenzen.md)",
    "Edit(/agentenbau.md)",
    "Edit(/quellen.yml)",
    "Edit(/agents/**)",
    "Edit(/.claude/**)",
    "Edit(/schema/**)",
    # Die Vorlage bestimmt, welche Felder eine Idee ueberhaupt hat -- wer sie aendert,
    # aendert die Bewertung. Kein Werkzeug erlaubt es heute, aber Deny sticht Allow.
    "Edit(/vorlagen/**)",
    # ADRs werden ergaenzt, nie umgeschrieben.
    "Edit(/decisions/**)",
]

# ------------------------------------------------- Die dritte Grenze: die Sitzung
#
# Anthropic zieht **drei** Grenzen, nicht zwei: Tag, Woche -- und ein rollendes
# Fuenf-Stunden-Fenster ("session limit"). Die Fabrik kannte bis zum 2026-09-05 nur die
# ersten beiden, und das hat an diesem Tag drei Stunden gekostet: Um 16:01 riss das
# Sitzungsfenster, und weil niemand abbrach, lief die Kette weiter und erzeugte
# **1.041 Fehllaeufe** -- jeder scheiterte in Sekunden, jeder schrieb eine Journalzeile,
# und alle vierzig Durchgaenge des Tageslaufs waren verbraucht, ohne dass ein einziges
# Paket vorankam.
#
# Die Sitzungsgrenze laesst sich nicht vorausberechnen: Sie zaehlt in Tokens ueber ein
# rollendes Fenster, und der wahre Stand ist von aussen nicht lesbar (geprueft am
# 2026-09-05, `claude --help` kennt keinen Unterbefehl dafuer). Also wird sie nicht
# vorhergesagt, sondern **erkannt** -- am Wortlaut der Absage -- und ab dann bricht die
# Kette ab, statt es weiter zu versuchen.
#
# Der stuendliche Cron-Versuch ist die richtige Wiederholung dafuer: Er kostet nichts,
# solange die Sperre steht, und faengt von selbst wieder an, sobald das Fenster offen ist.
KONTINGENT_ENDE = 3
_kontingent_ende: str | None = None


def kontingent_erschoepft() -> str | None:
    """Die Absage im Wortlaut, sobald ein Lauf sie einmal gesehen hat -- sonst None."""
    return _kontingent_ende


ZEITFORMAT = "%Y-%m-%dT%H:%M:%S"

# ---------------------------------------------------------------- Notbremse
#
# Am 2026-08-29 war das Wochenkontingent fast erschoepft, ohne dass irgendetwas
# gewarnt haette: Ein einzelner Tag hatte 95 Laeufe und 253 Dollar Gegenwert
# erzeugt. Es gab keine Stelle, an der die Fabrik von selbst haette anhalten
# koennen.
#
# Der Gegenwert ist der beste verfuegbare Naeherungswert fuer Kontingentverbrauch
# (siehe agents/kontingent.py). Diese Grenze ist bewusst grosszuegig -- sie soll
# Ausreisser abfangen, nicht den Normalbetrieb bremsen. Ein voller Nachtlauf lag
# zuletzt bei rund 40 Dollar.
# Am 2026-09-02 zum ersten Mal an echten Zahlen geeicht, statt geraten. Der Betreiber
# hat seine Anzeige vorgelesen: Fenster 4 Prozent, Woche 21 Prozent. Die Fabrik hatte im
# selben Wochenfenster (Montag 10:00 bis Mittwoch abend) 398,8 Dollar Gegenwert
# verbraucht.
#
# Daraus folgt eine Untergrenze: 100 Prozent der Woche sind MINDESTENS 1.900 Dollar
# Gegenwert -- mindestens, weil das Gespraech mit dem Betreiber auf dasselbe Kontingent
# geht und in den 21 Prozent mit drinsteckt.
#
# Und daraus zwei Korrekturen an dem, was hier vorher stand:
#
# Erstens war die Zahl zu hoch. Am 2026-09-02 abends nachgerechnet: 22 Prozent nach 2,4
# von 7 Tagen ist langsamer als linear, hochgerechnet 65 Prozent bis Montag. 400 am Tag
# passt dazu; 800 nicht. Der Tag ist ohnehin nur Glaettung -- die Woche sichert.
#
# Zweitens war die Bremse am falschen Fenster. Bindend ist die WOCHE, nicht der Tag --
# das Fuenf-Stunden-Fenster stand bei 4 Prozent, waehrend die Woche bei 21 stand. Eine
# Tagesgrenze allein laesst sieben volle Tage zu und damit ein Vielfaches des
# Wochenlimits. Deshalb steht darunter jetzt eine zweite.
#
# **Nachgeeicht am 2026-09-04 an einer viel groesseren Stichprobe.** Der Betreiber hat
# seine Anzeige vorgelesen: Woche 58 Prozent. Die Fabrik hatte im selben Fenster (ab
# Montag 08:00 UTC) 1.311,3 Dollar Gegenwert verbraucht.
#
#     1.311,3 / 0,58  =  rund 2.260 Dollar entsprechen 100 Prozent -- mit dem Bonus.
#     2.260 / 1,5     =  rund 1.510 Dollar ohne ihn, also ab dem 2026-09-13.
#
# Die alte Eichung (398,8 = 21 Prozent, also 1.900) stammte aus einem Fuenftel dieser
# Stichprobe und lag deshalb zu niedrig. Bei 1.600 hielt die Bremse die Fabrik bei
# 71 Prozent des Kontingents an und liess 661 Dollar dieser Woche verfallen. Das Abo ist
# ein Festpreis: Was die Woche nicht verbraucht, ist weg, nicht gespart.
#
# Warum 84 Prozent und nicht 95: Die Prozentanzeige ist auf ganze Zahlen gerundet, der
# Dollarwert hier ist ein modellgerechneter Gegenwert und nicht Anthropics eigene
# Buchung, und ein Lauf, der mitten in der Arbeit am echten Limit abbricht, kostet mehr
# als die ungenutzte Reserve. Der Abstand ist der Preis dafuer, dass die Rechnung oben
# eine Schaetzung bleibt.
#
# Nachzueichen am 2026-09-13, wenn der Bonus endet: dann gehoert WOCHENGRENZE_USD auf
# 1.270 (84 Prozent von 1.510) und die Tagesgrenze auf 300.
# **Am 2026-09-05 aufgeloest: Die Eichung war gegen den falschen Tarif gerechnet.**
# Der Betreiber las am 2026-09-04 abends 58 Prozent der Woche ab, am 2026-09-05 mittags
# 15 -- bei einem Fenster, das erst montags zuruecksetzt. Verbrauch kann nicht sinken.
# Die Ursache nennt der Betreiber selbst: Das Abo ist von Max 5x auf Max 20x gewechselt,
# und die Anzeige brauchte, bis sie das neue Limit fuehrte. 58 / 15 = 3,9 -- der Faktor
# vier, den der Tarifwechsel bedeutet. Beide Messungen sind richtig, nur gegen
# verschiedene Nenner.
#
# Daraus: 1.906 Dollar Gegenwert sind 15 Prozent, das Wochenkontingent liegt bei rund
# **12.700**. Die bisherigen 1.900 waren also 15 Prozent davon -- die Fabrik stand am
# 2026-09-05 ab 03:00 still, obwohl fuenf Sechstel der Woche offen lagen.
#
# `claude --help` kennt keinen Unterbefehl, der den Kontostand ausgibt; der wahre Wert
# ist aus der Fabrik heraus **nicht lesbar** (geprueft 2026-09-05). Der Dollarwert hier
# bleibt ein modellgerechneter Naeherungswert und keine Messung. **Deshalb rationiert
# diese Bremse nicht mehr, sie verhindert nur noch den Weglauf** -- einen Fehler, der die
# Fabrik in einer Nacht durch das ganze Kontingent traegt. Die Grenze zieht Anthropic
# selbst; die einzige verlaessliche Anzeige ist die des Betreibers.
#
# Zu niedrig ist nicht die sichere Seite. Das Abo ist ein Festpreis: Ein nicht genutzter
# Durchgang spart nichts, er verschenkt.
TAGESGRENZE_USD = 4000.0

# Der Betreiber kann die **Tages**grenze fuer einen einzelnen Aufruf anheben:
#
#     FABRIK_TAGESGRENZE=600 python3 agents/tageslauf.py --grenze 550
#
# Gedacht fuer den bewussten Nachschlag am Abend, wenn die Woche noch Luft hat und der
# Tag schon voll ist -- der Wirt schlaeft unvorhersehbar, und was heute nicht verbraucht
# ist, kann morgen an einem Schlaf verfallen. Die Konstante oben bleibt dabei stehen;
# die crontab faehrt weiter mit dem geeichten Wert.
#
# **Die Woche laesst sich so nicht uebersteuern.** WOCHENGRENZE_USD ist die Bremse, die
# das Kontingent schuetzt; der Tag ist nur Glaettung. Ein Weg, beide anzuheben, waere
# ein Weg, das Kontingent an einem Abend zu verbrauchen.
try:
    TAGESGRENZE_USD = float(os.environ.get("FABRIK_TAGESGRENZE", TAGESGRENZE_USD))
except ValueError:
    pass

# Die eigentliche Bremse -- 84 Prozent des am 2026-09-04 gemessenen Kontingents.
# Gerechnet ueber Anthropics Wochenfenster (Montag 10:00 Ortszeit), siehe
# `wochenfenster()`; die vorherige Rechnung ueber sieben rollende Tage drosselte gegen
# eine Woche, die bereits zurueckgesetzt war.
# **Zwei Toepfe, nicht einer.** Die Anzeige des Betreibers fuehrt "All models" und
# "Fable" getrennt, und sie leeren sich unabhaengig. Am 2026-09-06 um 10:05 standen sie
# bei 90 und 56 Prozent -- waehrend diese Datei noch 12.000 als eine gemeinsame Grenze
# fuehrte und 8.600 Dollar Spielraum meldete. Tatsaechlich waren rund 300 uebrig.
#
# **Der Dollarwert taugt nicht zur Eichung, und das ist jetzt dreimal gemessen:**
# 1.906 $ = 15 % (2026-09-05 mittags), 1.311 $ = 58 % (2026-09-04 abends),
# 2.834 $ = 90 % (2026-09-06 vormittags). Aus je zwei Punkten folgen drei verschiedene
# Kontingente zwischen 1.240 und 12.700. Der Grund ist nicht der Tarifwechsel allein:
# `kosten_eur` rechnet Cache-Tokens mit, die Anthropic anders wiegt. Die Zahl misst
# **Arbeit**, nicht Kontingent.
#
# Deshalb sind die Werte unten **an der Anzeige vom 2026-09-06 geeicht** und gelten fuer
# dieses Fenster: geteilter Topf 2.834 $ = 90 %, Fable 559 $ = 56 %. Sie sind eine
# Notbremse gegen den Weglauf, keine Rationierung -- und sie gehoeren nachgezogen,
# sobald der Betreiber wieder eine Anzeige vorliest. **Die Anzeige ist die einzige
# Wahrheit; diese Datei ist eine Schaetzung mit Datum.**
# WOCHENGRENZE_USD is the umbrella ("All models") and binds every run. The Fable
# figure is a sub-limit within it. Both calibrated to the 2026-09-06 readings
# (90 / 56 percent); the umbrella now includes Fable spend, so 2.800 + 900 would
# overshoot -- 3.400 is the umbrella at roughly 90 percent of what was observed.
WOCHENGRENZE_USD = 3400.0
FABLE_WOCHENGRENZE_USD = 900.0


def tagesverbrauch(verbindung) -> float:
    """Gegenwert aller Laeufe seit Mitternacht UTC."""
    zeile = verbindung.execute(
        "SELECT sum(kosten_eur) FROM lauf WHERE gestartet > date('now')"
    ).fetchone()
    return float(zeile[0] or 0)


def wochenfenster() -> str:
    """Beginn des laufenden Abo-Wochenfensters, als UTC-Zeitstempel wie im Journal.

    Bis zum 2026-09-03 rechnete die Bremse ueber sieben **rollende** Tage. Das ist die
    falsche Woche: Anthropic setzt das Wochenkontingent montags um 10:00 Ortszeit
    zurueck. Am 2026-09-03 kostete der Unterschied die halbe Fabrik -- die rollende
    Rechnung sah 1.131 von 1.600 Dollar verbraucht und liess 469 uebrig, waehrend im
    tatsaechlich laufenden Fenster erst rund 620 Dollar standen. Gedrosselt wurde also
    gegen eine Woche, die es nicht mehr gab.

    Faellt die Zeitzonendatenbank aus, bleibt es bei sieben rollenden Tagen: zu streng
    ist hier die richtige Richtung zu irren.
    """
    try:
        from zoneinfo import ZoneInfo
        ortszeit = datetime.now(ZoneInfo("Europe/Berlin"))
    except Exception:
        return (datetime.now(timezone.utc) - timedelta(days=7)).strftime(ZEITFORMAT)
    start = ortszeit.replace(hour=10, minute=0, second=0, microsecond=0) \
        - timedelta(days=ortszeit.weekday())
    if start > ortszeit:                       # montags vor 10:00 gilt noch die Vorwoche
        start -= timedelta(days=7)
    return start.astimezone(timezone.utc).strftime(ZEITFORMAT)


def fable_rollen() -> set[str]:
    """Welche Rollen auf Fable laufen -- gelesen aus den Rollendateien, nicht geraten.

    Das Journal kennt nur die Rolle, nicht das Modell. Rollen, deren Modell sich spaeter
    aendert, werden dadurch rueckwirkend dem neuen Topf zugerechnet; bei einer Handvoll
    Rollen ist das kleiner als die Unschaerfe des Dollarwerts selbst.
    """
    namen = set()
    for d in (WURZEL / "agents" / "rollen").glob("*.md"):
        try:
            kopf, _ = frontmatter(d.read_text(encoding="utf-8"))
        except (ValueError, OSError):
            continue
        if kopf and str(kopf.get("modell", "")).strip() == "fable":
            namen.add(d.stem)
    return namen


def wochenverbrauch(verbindung, topf: str = "geteilt") -> float:
    """Gegenwert im laufenden Wochenfenster, je Topf.

    `topf="geteilt"` sind alle Rollen ausser den Fable-Rollen -- das ist die Anzeige
    "All models". `topf="fable"` ist die zweite Anzeige.
    """
    fable = fable_rollen()
    if not fable:
        platzhalter, werte = "('')", []
    else:
        platzhalter = "(" + ",".join("?" * len(fable)) + ")"
        werte = sorted(fable)
    rein = "IN" if topf == "fable" else "NOT IN"
    zeile = verbindung.execute(
        f"SELECT sum(kosten_eur) FROM lauf WHERE gestartet > ? AND rolle {rein} {platzhalter}",
        (wochenfenster(), *werte),
    ).fetchone()
    return float(zeile[0] or 0)


def jetzt() -> str:
    return datetime.now(timezone.utc).strftime(ZEITFORMAT)


# ---------------------------------------------------------------- Frontmatter

def frontmatter(text: str) -> tuple[dict, str]:
    """Minimaler YAML-Frontmatter-Parser fuer die drei hier benutzten Formen:

        schluessel: wert
        schluessel:
          - listeneintrag
        schluessel:
          unterschluessel: wert     (eine Ebene, z.B. score.summe)

    Bewusst ohne PyYAML, damit ein frischer VPS ohne Paketinstallation laeuft. Ein
    Schluessel ohne Wert startet als Liste und wird zur Map, sobald eine eingerueckte
    Zuweisung folgt -- welche der beiden Formen gemeint war, zeigt erst die naechste Zeile.
    """
    if not text.startswith("---"):
        return {}, text
    _, kopf, rumpf = text.split("---", 2)
    daten: dict = {}
    offen = None  # Schluessel, unter dem eingerueckte Zeilen landen
    for zeile in kopf.splitlines():
        if not zeile.strip() or zeile.lstrip().startswith("#"):
            continue
        eingerueckt = zeile[:1].isspace()
        roh = zeile.strip()

        if roh.startswith("- "):
            if offen is not None and isinstance(daten.get(offen), list):
                daten[offen].append(roh[2:].strip().strip("\"'"))
            continue

        if ":" not in roh:
            continue
        k, _, v = roh.partition(":")
        # YAML-Semantik: " #" beginnt einen Kommentar. Die Vorlagen dokumentieren die
        # zulaessigen Werte hinter dem Feld -- ohne dieses Abschneiden waere der Status
        # einer aus der Vorlage kopierten Idee nie ein gueltiger Status.
        k, v = k.strip(), v.split(" #")[0].strip().strip("\"'")

        if eingerueckt and offen is not None:
            if isinstance(daten.get(offen), list):
                daten[offen] = {}
            daten[offen][k] = v
            continue

        if v:
            daten[k] = v
            offen = None
        else:
            daten[k] = []
            offen = k
    return daten, rumpf.lstrip("\n")


# ---------------------------------------------------------------- Journal

def db() -> sqlite3.Connection:
    """Oeffnet die Zustandsdatenbank und legt bei Bedarf das Schema an.

    Geprueft wird das Schema, nicht die Datei: Eine leere oder halb angelegte state.db
    kommt in der Praxis vor (abgebrochener Lauf, versehentliches sqlite3-Oeffnen) und
    wuerde bei einer reinen Dateipruefung stumm zu Folgefehlern fuehren.
    """
    # timeout: Bei parallelen Laeufen schreiben mehrere Threads ins Journal. Ohne
    # Wartezeit wirft sqlite sofort "database is locked" und der Lauf verliert seinen
    # Journaleintrag, obwohl er sauber gearbeitet hat. Mit WAL aus dem Schema und
    # dieser Wartezeit serialisieren sich die Schreiber von selbst.
    verbindung = sqlite3.connect(DB, timeout=30)
    vorhanden = verbindung.execute(
        "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='lauf'"
    ).fetchone()[0]
    if not vorhanden:
        verbindung.executescript(SCHEMA.read_text(encoding="utf-8"))
        verbindung.commit()

    # Fehlende Spalten nachruesten. sqlite kennt kein ADD COLUMN IF NOT EXISTS, und
    # state.db darf beim Fortschreiben des Schemas nicht neu angelegt werden muessen --
    # sie ist die einzige Quelle fuer jede Eichung. ADD COLUMN haelt die Schreibsperre
    # nur Millisekunden; laufende Agenten mit dem alten UPDATE stoert eine zusaetzliche
    # Spalte nicht.
    haben = {z[1] for z in verbindung.execute("PRAGMA table_info(lauf)")}
    for name, art in (("zuege", "INTEGER DEFAULT 0"),):
        if name not in haben:
            verbindung.execute(f"ALTER TABLE lauf ADD COLUMN {name} {art}")
            verbindung.commit()
    return verbindung


def journal_start(verbindung, rolle: str, gegenstand: str | None) -> int:
    # Laeufe, die beim letzten Mal hart abgebrochen wurden -- Distro heruntergefahren,
    # Rechner aus, Prozess gekillt -- stehen sonst fuer immer auf "laeuft" und
    # verfaelschen Kostenbericht und Digest. Zwei Stunden liegen weit ueber dem
    # laengsten zulaessigen Timeout (1800s), koennen also keinen echten Lauf treffen.
    verbindung.execute(
        """UPDATE lauf SET ergebnis = 'abgebrochen', beendet = ?
           WHERE ergebnis = 'laeuft' AND gestartet < datetime('now', '-2 hours')""",
        (jetzt(),),
    )
    zeiger = verbindung.execute(
        "INSERT INTO lauf (gestartet, rolle, gegenstand) VALUES (?,?,?)",
        (jetzt(), rolle, gegenstand),
    )
    verbindung.commit()
    return zeiger.lastrowid


def journal_ende(verbindung, lauf_id: int, ergebnis: str, nutzung: dict,
                 commit_hash: str | None, notiz: str | None) -> None:
    verbindung.execute(
        """UPDATE lauf SET beendet=?, tokens_in=?, tokens_frisch=?, tokens_cneu=?,
                           tokens_cles=?, tokens_denken=?, tokens_out=?, zuege=?,
                           kosten_eur=?, ergebnis=?, commit_hash=?, notiz=?
           WHERE id=?""",
        (
            jetzt(),
            nutzung.get("input_tokens", 0),
            nutzung.get("frisch", 0),
            nutzung.get("cache_neu", 0),
            nutzung.get("cache_gelesen", 0),
            nutzung.get("denken", 0),
            nutzung.get("output_tokens", 0),
            nutzung.get("zuege", 0),
            nutzung.get("kosten", 0.0),
            ergebnis,
            commit_hash,
            (notiz or "")[:500],
            lauf_id,
        ),
    )
    verbindung.commit()


# ---------------------------------------------------------------- Git

# Git haelt beim Schreiben eine Sperre auf dem Index. Laufen mehrere Agenten
# gleichzeitig -- und das ist der Normalfall, sobald man die Auslastung hochdreht --,
# scheitert der zweite mit "index.lock: File exists" und verliert seine Arbeit, obwohl
# nichts kaputt ist. Deshalb wird jeder schreibende Git-Aufruf wiederholt.
SPERRE_VERSUCHE = 12
SPERRE_PAUSE = 2.0


def git(*args: str, geduldig: bool = False) -> str:
    """Ruft git auf. `geduldig` wartet, wenn ein anderer Lauf gerade den Index haelt."""
    for versuch in range(SPERRE_VERSUCHE if geduldig else 1):
        fertig = subprocess.run(
            ["git", *args], cwd=WURZEL, capture_output=True, text=True,
            encoding="utf-8", errors="replace",
        )
        if fertig.returncode == 0 or "index.lock" not in (fertig.stderr or ""):
            return (fertig.stdout or "").strip()
        time.sleep(SPERRE_PAUSE * (versuch + 1) / 2)
    return (fertig.stdout or "").strip()


def schreibpfade(werkzeuge: list[str]) -> list[str]:
    """Die Verzeichnisse, die eine Rolle laut ihrer Werkzeugliste anfassen darf."""
    pfade = []
    for w in werkzeuge:
        treffer = re.match(r"Edit\((.+?)\)$", w.strip())
        if treffer:
            p = treffer.group(1).lstrip("/")
            p = p.split("*", 1)[0].rstrip("/")
            if p:
                pfade.append(p)
    return pfade


def commitpfade(gegenstand: str | None, rolle: str, breit: list[str]) -> list[str]:
    """Die Pfade, die **dieser** Lauf committen darf -- eng, wenn es ein Paket ist.

    Bis zum 2026-09-05 bekam `committen` die Schreibpfade der **Rolle**
    (`schreibpfade(werkzeuge)`). Fuer `kernbauer` und `testentwickler` ist das
    `ventures/**`, also faktisch das ganze Vorhaben: Zwei Kernbauer an verschiedenen
    Paketen teilten sich denselben Commit-Pfad, und wer zuerst fertig wurde, nahm die
    Arbeit des anderen unter seinem Betreff mit. Nachgewiesen vom kern-pruefer an
    `9e46cfa` (Betreff `architekt: 0051`, acht Dateien aus drei Paketen und zwei Rollen)
    und `2de4de7` (Betreff `kernbauer: 0072`, von 0072 nichts darin). Pakete 0121, 0131.

    Eng heisst hier vier Dinge und **nicht** mehr:

    - die `dateien`-Liste des Pakets -- die Koernigkeit, in der der Baulauf ohnehin
      schon Kollisionen vermeidet;
    - die Paketdatei selbst, damit der Agent seinen Status melden kann;
    - sein eigenes Logbuch;
    - Befunde und Messbaeume, die **seinen** Paketnamen tragen.

    Ausdruecklich **nicht** das ganze `befunde/`-Verzeichnis: Dort schreiben mehrere
    Pruefer gleichzeitig, und es mitzunehmen waere genau der Fehler, der hier behoben
    wird.

    Faellt irgendetwas davon aus -- kein Paket zu diesem Gegenstand, kein lesbares
    Frontmatter --, gibt die Funktion die breiten Rollenpfade zurueck. Der schlechteste
    Fall ist damit das Verhalten von gestern und nicht ein verlorener Commit.
    """
    if not gegenstand:
        return breit
    treffer = sorted(WURZEL.glob(f"ventures/*/aufgaben/{gegenstand}.md"))
    if not treffer:
        return breit
    datei = treffer[0]
    try:
        kopf, _ = frontmatter(datei.read_text(encoding="utf-8"))
    except OSError:
        return breit

    eng = [str(datei.relative_to(WURZEL))]
    # Wortgleich zu baulauf.py:240.  liefert  als **Zeichenkette**
    # ("[a/b.md, c/d.md]"), nicht als Liste -- wer darueber iteriert, bekommt einzelne
    # Buchstaben. Genau das ist mir am 2026-09-05 beim ersten Versuch passiert, und der
    # Pfadfilter darunter hat es stillschweigend verdeckt: Der Commit haette Paketdatei
    # und Logbuch getragen und die eigentliche Arbeit im Arbeitsbaum gelassen.
    for d in {s.strip() for s in
              str(kopf.get('dateien', '')).strip('[]').split(',') if s.strip()}:
        eng.append(d)
    eng.append(f"notizen/{rolle}.md")

    befunde = datei.parent.parent / "befunde"
    for spur in sorted(befunde.glob(f"*{gegenstand}*")):
        eng.append(str(spur.relative_to(WURZEL)))

    # Nie mehr als die Rolle ueberhaupt schreiben darf.
    erlaubt = [e for e in eng if any(e == b or e.startswith(b + "/") for b in breit)]
    return erlaubt or breit


LOGBUCH_MAX = 12_000


def logbuch_rotieren(rolle: str) -> str | None:
    """Rotates an oversized logbook into notizen/archiv/ and leaves a short head.

    The 12,000-character cap is the roles' own convention, and most of them honour it by
    hand. Three could not: `architekt`, `projektmanager` and `geschaeftsfuehrer` each
    reported to the operator that copying into `notizen/archiv/` was denied them, and
    they struck entries instead of archiving — against house rule 3. Since 2026-09-06
    `Bash` is denied globally, so no role can do it any more.

    So the runner does it. It never deletes: the full file moves to the archive, and the
    new logbook names its predecessor. The agent writes the next entry into an empty
    book, which is also why this runs *after* the run and not before.
    """
    datei = WURZEL / "notizen" / f"{rolle}.md"
    try:
        text = datei.read_text(encoding="utf-8")
    except OSError:
        return None
    if len(text) <= LOGBUCH_MAX:
        return None

    archiv = WURZEL / "notizen" / "archiv"
    archiv.mkdir(parents=True, exist_ok=True)
    heute = datetime.now(timezone.utc).strftime("%Y-%m-%d")
    n = 1
    while (ziel := archiv / f"{rolle}-{heute}-{n}.md").exists():
        n += 1
    ziel.write_text(text, encoding="utf-8")

    kopf = text.split("\n\n", 1)[0].strip()
    datei.write_text(
        f"{kopf}\n\n"
        f"Rotated by the runner on {heute} at {len(text)} characters "
        f"(cap {LOGBUCH_MAX:,}). Predecessor: `notizen/archiv/{ziel.name}`.\n"
        f"Carry forward only what holds beyond a single package; the rest is in the\n"
        f"predecessor and stays readable.\n\n",
        encoding="utf-8")
    return ziel.name


def frisch_geschrieben(pfade: list[str], seit: float) -> int:
    """Wie viele Dateien in den Schreibpfaden nach `seit` veraendert wurden.

    Noetig, weil bei parallelen Laeufen ein Agent die Dateien eines anderen
    mitcommittet: `committen` nimmt ganze Verzeichnisse, nicht einzelne Dateien.
    Der zweite Lauf findet dann nichts mehr vor und meldete bisher "leer", obwohl
    er sauber gearbeitet hatte. Das verfaelscht jede Auswertung in die gefaehrliche
    Richtung -- eine produktive Rolle sieht aus, als taugte ihr Auftrag nichts.
    """
    anzahl = 0
    for p in pfade:
        ziel = WURZEL / p
        if ziel.is_file():
            kandidaten = [ziel]
        elif ziel.is_dir():
            kandidaten = [d for d in ziel.rglob("*") if d.is_file()]
        else:
            continue
        for d in kandidaten:
            try:
                if d.stat().st_mtime > seit:
                    anzahl += 1
            except OSError:
                pass
    return anzahl


def committen(rolle: str, gegenstand: str | None, lauf_id: int,
              pfade: list[str]) -> tuple[str | None, int, str | None]:
    """Committet, was der Lauf hinterlassen hat. Kein Ergebnis, kein Commit.

    Committet ausschliesslich die Pfade, die die Rolle laut Werkzeugliste beschreiben
    darf. Ein `git add -A` wuerde alles mitnehmen, was gerade sonst im Arbeits-
    verzeichnis liegt -- der Agent signierte dann fremde Aenderungen unter seinem
    Namen, und die Historie sagt nicht mehr, wer was getan hat.

    Gibt (Hash, Anzahl Dateien, Fehlermeldung) zurueck. Der Rueckgabewert von
    `git commit` wird geprueft: Scheitert er -- fehlende Identitaet, Hook, gesperrter
    Index --, liegen die Dateien zwar im Arbeitsverzeichnis, aber die Historie kennt
    sie nicht. Ohne diese Pruefung meldet der Lauf "ok" und niemand merkt es.
    """
    if not pfade:
        return None, 0, None
    geaendert = [z for z in git("status", "--porcelain", "--", *pfade).splitlines()
                 if z.strip()]
    if not geaendert:
        return None, 0, None
    git("add", "--", *pfade, geduldig=True)
    betreff = f"{rolle}: {gegenstand or 'lauf'} ({len(geaendert)} Dateien)"

    # Auch der Commit selbst wartet auf die Sperre. Zwei Agenten, die im selben
    # Moment fertig werden, sind bei hoher Auslastung der Regelfall, kein Ausnahmefall.
    # **Die Pfadangabe gehoert an den Commit, nicht nur an das `git add`.** Bis zum
    # 2026-09-05 stand hier ein `git commit` ohne `--`, und damit committete der Lauf den
    # **ganzen Index** -- auch das, was ein gleichzeitig laufender Agent Sekunden vorher
    # hineingelegt und noch nicht committet hatte. Die Zusicherung im Docstring oben hielt
    # die naechste Anweisung nicht.
    #
    # Bewiesen vom kern-pruefer am 2026-09-05 an zwei Commits (Paket 0121): `9e46cfa`
    # traegt den Betreff `architekt: 0051`, enthaelt acht Dateien aus **drei** Paketen und
    # **zwei** Rollen -- darunter vier unter `kern/`, die die Werkzeugliste des Architekten
    # gar nicht abdeckt. Sie koennen nicht aus seinem `git add` stammen, nur aus dem Index.
    # Umgekehrt enthaelt `2de4de7` mit dem Betreff `kernbauer: 0072` von 0072 nichts.
    #
    # Die Folgen sind keine Kosmetik: `git log -- <datei>` nennt das falsche Paket, und ein
    # `git revert` auf ein Urteil `zurueck` nimmt fremde Pakete mit.
    #
    # Mit `--` gilt: Was nicht in `pfade` liegt, bleibt im Index liegen und gehoert dem
    # Lauf, der es hineingelegt hat.
    for versuch in range(SPERRE_VERSUCHE):
        fertig = subprocess.run(
            ["git", "commit", "-q", "-m", betreff, "-m", f"Lauf {lauf_id}",
             "--", *pfade],
            cwd=WURZEL, capture_output=True, text=True,
            encoding="utf-8", errors="replace",
        )
        if fertig.returncode == 0:
            return git("rev-parse", "--short", "HEAD"), len(geaendert), None
        meldung = ((fertig.stderr or "") + (fertig.stdout or "")).strip()
        if "index.lock" not in meldung:
            break
        time.sleep(SPERRE_PAUSE * (versuch + 1) / 2)

    return None, len(geaendert), meldung[:300] or "git commit fehlgeschlagen"


# ---------------------------------------------------------------- Lauf

def claude_pfad() -> str:
    for name in ("claude", "claude.cmd", "claude.exe"):
        pfad = shutil.which(name)
        if pfad:
            return pfad
    # cron und der Windows-Aufgabenplaner starten mit einem kargen PATH, in dem die
    # ueblichen Installationsorte von Claude Code nicht vorkommen. Ohne diesen Zweig
    # scheitert jeder naechtliche Lauf stumm, waehrend er von Hand einwandfrei laeuft.
    for kandidat in (
        Path.home() / ".local" / "bin" / "claude",
        Path.home() / ".claude" / "local" / "claude",
        Path("/usr/local/bin/claude"),
    ):
        if kandidat.is_file():
            return str(kandidat)
    sys.exit("claude nicht gefunden - Claude Code installieren oder PATH pruefen.")


def pruefe_umgebung() -> None:
    """Prueft vor dem ersten Token, was den Lauf am Ende wertlos machen wuerde.

    Eine fehlende Git-Identitaet faellt sonst erst auf, wenn der Agent fertig
    recherchiert hat: Die Dateien liegen da, der Commit scheitert, die Tokens sind weg.
    """
    if not git("config", "user.email") or not git("config", "user.name"):
        sys.exit(
            "Keine Git-Identitaet gesetzt -- jeder Commit wuerde scheitern und der Lauf\n"
            "waere umsonst. Einmalig im Repo setzen:\n"
            '  git config user.name "<Name>"\n'
            '  git config user.email "<Mail>"'
        )


def lauf(rolle: str, gegenstand: str | None = None) -> int:
    global _kontingent_ende
    datei = ROLLEN / f"{rolle}.md"
    if not datei.exists():
        sys.exit(f"Unbekannte Rolle: {rolle} (erwartet {datei})")
    pruefe_umgebung()

    kopf, auftrag = frontmatter(datei.read_text(encoding="utf-8"))
    werkzeuge = kopf.get("tools") or []
    if not werkzeuge:
        sys.exit(f"Rolle {rolle} definiert keine Werkzeuge - das waere ein Blankoscheck.")

    if gegenstand:
        auftrag += f"\n\n## Gegenstand dieses Laufs\n\n{gegenstand}\n"

    befehl = [
        claude_pfad(), "-p", auftrag,
        "--output-format", "json",
        "--model", kopf.get("modell", "sonnet"),
        # Denkaufwand je Rolle. Sammeln braucht Sorgfalt, Urteilen braucht Tiefe --
        # ohne diesen Schalter laeuft beides auf demselben Standardwert, und der ist
        # fuer die eine Haelfte verschwendet und fuer die andere zu wenig.
        "--effort", kopf.get("effort", "medium"),
        "--permission-mode", MODUS,
        "--allowedTools", *werkzeuge,
        "--disallowedTools", *NIE,
    ]

    # Hat ein Lauf dieser Kette die Absage schon gesehen, faengt keiner mehr an. Ohne
    # diese vier Zeilen entstanden am 2026-09-05 tausend Journalzeilen in drei Stunden.
    if _kontingent_ende:
        print(f"  Uebersprungen -- Kontingent erschoepft: {_kontingent_ende}")
        return KONTINGENT_ENDE

    verbindung = db()

    # Notbremse vor dem Start, nicht danach: Ein Lauf, der die Grenze reisst,
    # soll gar nicht erst beginnen.
    # "All models" is the umbrella: every run counts against it, Fable included.
    # Measured 2026-09-06 21:56 -- the translator on Fable (56 percent) was refused
    # with "hit your weekly limit" while the shared line stood at 100. Until then this
    # check let Fable runs bypass the umbrella. The Fable cap is a second, narrower
    # brake on top, not an alternative.
    fable = str(kopf.get("modell", "")).strip() == "fable"
    gesamt = wochenverbrauch(verbindung, "geteilt") + wochenverbrauch(verbindung, "fable")
    grenze, topf, woche = WOCHENGRENZE_USD, "gesamt", gesamt
    if fable and woche < grenze:
        f = wochenverbrauch(verbindung, "fable")
        if f >= FABLE_WOCHENGRENZE_USD:
            grenze, topf, woche = FABLE_WOCHENGRENZE_USD, "fable", f
    if woche >= grenze:
        verbindung.close()
        print(f"  ABGEBROCHEN: Wochengrenze '{topf}' erreicht "
              f"({woche:.0f} von {grenze:.0f} $ Gegenwert).")
        print("  Das ist die Grenze, die wirklich bindet -- Anthropic rechnet")
        print("  woechentlich. Grenze in agents/lauf.py:WOCHENGRENZE_USD.")
        return 2

    heute = tagesverbrauch(verbindung)
    if heute >= TAGESGRENZE_USD:
        verbindung.close()
        print(f"  ABGEBROCHEN: Tagesgrenze erreicht "
              f"({heute:.0f} von {TAGESGRENZE_USD:.0f} $ Gegenwert).")
        print("  Die Fabrik haelt an, damit das Wochenkontingent nicht in einem Tag")
        print("  aufgebraucht wird. Grenze steht in agents/lauf.py:TAGESGRENZE_USD.")
        return 2

    lauf_id = journal_start(verbindung, rolle, gegenstand)
    begonnen = time.time()
    print(f"[{jetzt()}] Lauf {lauf_id}: {rolle}" + (f" -> {gegenstand}" if gegenstand else ""))

    try:
        fertig = subprocess.run(
            befehl, cwd=WURZEL, capture_output=True, text=True,
            encoding="utf-8", errors="replace", timeout=int(kopf.get("timeout", 1800)),
        )
    except subprocess.TimeoutExpired:
        journal_ende(verbindung, lauf_id, "fehler", {}, None, "Zeitueberschreitung")
        print(f"  Zeitueberschreitung nach {kopf.get('timeout', 1800)}s")
        return 1

    nutzung: dict = {}
    antwort = ""
    try:
        roh = json.loads(fertig.stdout)
        antwort = roh.get("result", "") or ""
        verbrauch = roh.get("usage") or {}
        # input_tokens allein ist irrefuehrend: Es zaehlt nur den ungecachten Rest.
        # Ein Trivialaufruf meldete 2 input_tokens -- und 14.102 cache_creation plus
        # 24.432 cache_read. Alle drei gehen durchs Kontingent; wer nur input_tokens
        # journalisiert, untertreibt seinen Verbrauch um Groessenordnungen und dreht
        # die Auslastung im guten Glauben immer weiter hoch.
        eingang = (
            verbrauch.get("input_tokens", 0)
            + verbrauch.get("cache_creation_input_tokens", 0)
            + verbrauch.get("cache_read_input_tokens", 0)
        )
        nutzung = {
            "input_tokens": eingang,
            "frisch": verbrauch.get("input_tokens", 0),
            "cache_neu": verbrauch.get("cache_creation_input_tokens", 0),
            "cache_gelesen": verbrauch.get("cache_read_input_tokens", 0),
            "denken": (verbrauch.get("output_tokens_details") or {}).get(
                "thinking_tokens", 0),
            "output_tokens": verbrauch.get("output_tokens", 0),
            # num_turns steht neben usage, nicht darin: Werkzeugaufrufe des Laufs.
            # Der Kontext wird in JEDEM Zug erneut gesendet -- Zuege mal Kontext ist
            # die eigentliche Rechnung. Ohne diese Zahl ist nicht zu unterscheiden,
            # ob ein teurer Lauf zu viel liest oder zu oft greift.
            "zuege": roh.get("num_turns", 0) or 0,
            # Claude Code meldet total_cost_usd auch bei Abo-Anmeldung. Der Betrag
            # wird dann NICHT abgerechnet -- er ist der rechnerische Gegenwert zu
            # Listenpreisen, also das, was derselbe Lauf ueber die API gekostet haette.
            # Nuetzlich als Mass dafuer, was die Fabrik aus dem Abo zieht; keine Ausgabe.
            "kosten": roh.get("total_cost_usd", 0.0) or 0.0,
        }
        # Verweigerte Werkzeuge sind der wertvollste Fruehwarnwert ueberhaupt: Genau
        # so sah der Write()-Fehler aus, der einen ganzen Tag lang Laeufe leer laufen
        # liess, waehrend das Journal "ok" meldete.
        verweigert = roh.get("permission_denials") or []
        if verweigert:
            namen = sorted({str(d.get("tool_name", d)) for d in verweigert}) \
                if isinstance(verweigert, list) else [str(verweigert)]
            antwort = (f"[{len(verweigert)}x Werkzeug verweigert: "
                       f"{', '.join(namen)[:120]}] " + antwort)
    except (json.JSONDecodeError, AttributeError):
        antwort = (fertig.stdout or fertig.stderr or "")[:500]

    if fertig.returncode != 0:
        # "You've hit your session limit - resets 6:20pm" und Verwandte. Der Wortlaut
        # ist die einzige Quelle; die Grenze selbst ist nicht abfragbar.
        if re.search(r"hit your .{0,24}limit", antwort, re.I):
            _kontingent_ende = antwort.strip().splitlines()[0][:160]
            journal_ende(verbindung, lauf_id, "abgebrochen", nutzung, None, antwort)
            print(f"  KONTINGENT ERSCHOEPFT: {_kontingent_ende}")
            print("  Die Kette haelt an. Der stuendliche Versuch nimmt sie wieder auf,")
            print("  sobald das Fenster offen ist -- er kostet nichts, solange es zu ist.")
            return KONTINGENT_ENDE
        journal_ende(verbindung, lauf_id, "fehler", nutzung, None, antwort)
        print(f"  Fehlgeschlagen (Code {fertig.returncode}): {antwort[:200]}")
        return fertig.returncode

    breit = schreibpfade(werkzeuge)
    pfade = commitpfade(gegenstand, rolle, breit)
    commit_hash, anzahl, commit_fehler = committen(rolle, gegenstand, lauf_id, pfade)
    rotiert = logbuch_rotieren(rolle)
    if rotiert:
        print(f"  Logbuch rotiert -> notizen/archiv/{rotiert}")
    tokens = nutzung.get("input_tokens", 0) + nutzung.get("output_tokens", 0)

    # Nichts zu committen heisst nicht, dass nichts entstanden ist: Bei parallelen
    # Laeufen hat ein anderer Agent die Dateien schon mitgenommen.
    mitgenommen = 0
    if not anzahl and not commit_fehler:
        mitgenommen = frisch_geschrieben(breit, begonnen)

    if commit_fehler:
        journal_ende(verbindung, lauf_id, "fehler", nutzung, None,
                     f"Commit gescheitert: {commit_fehler}")
        print(f"  {anzahl} Dateien geschrieben, aber NICHT committet ({tokens} Tokens)")
        print(f"  {commit_fehler.splitlines()[0] if commit_fehler else ''}")
        return 1

    ergebnis = "ok" if (anzahl or mitgenommen) else "leer"
    journal_ende(verbindung, lauf_id, ergebnis, nutzung, commit_hash, antwort)
    if anzahl:
        print(f"  {anzahl} Dateien, {tokens} Tokens, Commit {commit_hash}")
    elif mitgenommen:
        print(f"  {mitgenommen} Dateien geschrieben, von einem parallelen Lauf "
              f"mitcommittet ({tokens} Tokens)")
    else:
        print(f"  Nichts Neues ({tokens} Tokens) - das ist ein gueltiges Ergebnis.")
    return 0


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    sys.exit(lauf(sys.argv[1], sys.argv[2] if len(sys.argv) > 2 else None))
