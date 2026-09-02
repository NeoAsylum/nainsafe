#!/usr/bin/env python3
"""Erzeugt ops/dashboard.html -- der Blick auf die Fabrik in einer Seite.

    python3 agents/dashboard.py

Kostet nichts und veraendert nichts. Die Seite ist eigenstaendig: kein Netz, keine
Bibliotheken, alle Diagramme als SVG im Dokument. Oeffnen unter

    \\\\wsl$\\Ubuntu\\home\\<name>\\fabrik\\ops\\dashboard.html

Gerechnet wird in Tokens, nicht in Euro. Die vier Eingangsarten stehen dabei
getrennt: Cache-Lesen dominiert jede Summe, zaehlt aber anders als frisch
gesendeter Kontext -- eine Gesamtzahl allein taeuscht in beide Richtungen.
"""

from __future__ import annotations

import html
import re
import sqlite3
import sys
from collections import Counter
from datetime import datetime, timezone
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import DB, TAGESGRENZE_USD, WURZEL, frontmatter  # noqa: E402

ZIEL = WURZEL / "ops" / "dashboard.html"
TOT = ("abgelehnt", "widerlegt", "eingestellt")


# ---------------------------------------------------------------- Bausteine

def tsd(n) -> str:
    return f"{int(n or 0):,}".replace(",", ".")


def kurz(t: str, n: int = 120) -> str:
    t = re.sub(r"\s+", " ", (t or "").strip().strip('"'))
    return html.escape(t if len(t) <= n else t[: n - 1] + "…")


def balken_svg(werte: list[tuple[str, float]], breite=560, hoehe=22, luecke=6) -> str:
    """Waagerechtes Balkendiagramm. Beschriftung links, Wert rechts."""
    if not werte:
        return "<p class='leer'>keine Daten</p>"
    groesster = max(w for _, w in werte) or 1
    zeilen = []
    for i, (name, wert) in enumerate(werte):
        y = i * (hoehe + luecke)
        laenge = max(2, (wert / groesster) * (breite - 250))
        zeilen.append(
            f'<text x="0" y="{y + 15}" class="lbl">{html.escape(name)}</text>'
            f'<rect x="150" y="{y + 3}" width="{laenge:.0f}" height="{hoehe - 6}" '
            f'rx="2" class="bar"/>'
            f'<text x="{155 + laenge:.0f}" y="{y + 15}" class="val">{tsd(wert)}</text>'
        )
    h = len(werte) * (hoehe + luecke)
    return f'<svg viewBox="0 0 {breite} {h}" class="chart" role="img">{"".join(zeilen)}</svg>'


def verlauf_svg(punkte: list[tuple[str, float]], breite=560, hoehe=140) -> str:
    """Saeulen je Tag."""
    if not punkte:
        return "<p class='leer'>keine Daten</p>"
    groesster = max(w for _, w in punkte) or 1
    n = len(punkte)
    sb = breite / max(n, 1)
    teile = []
    for i, (tag, wert) in enumerate(punkte):
        h = (wert / groesster) * (hoehe - 34)
        x = i * sb
        teile.append(
            f'<rect x="{x + sb * 0.15:.1f}" y="{hoehe - 22 - h:.1f}" '
            f'width="{sb * 0.7:.1f}" height="{h:.1f}" rx="2" class="bar"/>'
            f'<text x="{x + sb / 2:.1f}" y="{hoehe - 8}" class="ax" '
            f'text-anchor="middle">{html.escape(tag[5:])}</text>'
            f'<text x="{x + sb / 2:.1f}" y="{hoehe - 27 - h:.1f}" class="ax" '
            f'text-anchor="middle">{tsd(wert)}</text>'
        )
    return f'<svg viewBox="0 0 {breite} {hoehe}" class="chart" role="img">{"".join(teile)}</svg>'


def trichter(stufen: list[tuple[str, int, str]]) -> str:
    groesster = max((n for _, n, _ in stufen), default=1) or 1
    zeilen = []
    for name, n, hinweis in stufen:
        anteil = (n / groesster) * 100
        zeilen.append(
            f'<div class="stufe"><div class="stufe-kopf">'
            f'<span>{html.escape(name)}</span><b>{n}</b></div>'
            f'<div class="spur"><div class="fuell" style="width:{anteil:.1f}%"></div></div>'
            f'<div class="hinweis">{html.escape(hinweis)}</div></div>'
        )
    return "".join(zeilen)


# ---------------------------------------------------------------- Daten

def _ordner(pfad):
    """Eintraege eines Verzeichnisses, das es nach dem Aufraeumen nicht mehr geben muss.

    `signals/` liegt seit dem 2026-09-02 unter `archiv/suche/`. Ohne diese Huelle ist
    das Dashboard alle dreissig Minuten still gescheitert -- die Seite blieb einfach
    stehen, und nichts sagte warum.
    """
    return sorted(pfad.iterdir()) if pfad.is_dir() else []


def sammeln() -> dict:
    d: dict = {"erzeugt": datetime.now(timezone.utc).strftime("%Y-%m-%d %H:%M UTC")}
    v: sqlite3.Connection = sqlite3.connect(DB)

    d["heute"] = v.execute(
        """SELECT count(*), sum(tokens_in + tokens_out), sum(kosten_eur)
           FROM lauf WHERE gestartet > date('now')"""
    ).fetchone()

    d["woche"] = v.execute(
        """SELECT count(*), sum(tokens_in + tokens_out), sum(kosten_eur)
           FROM lauf WHERE gestartet > strftime('%Y-%m-%dT%H:%M:%S','now','-7 days')"""
    ).fetchone()

    d["arten"] = v.execute(
        """SELECT sum(tokens_frisch), sum(tokens_cneu), sum(tokens_cles),
                  sum(tokens_out), sum(tokens_denken)
           FROM lauf WHERE gestartet > strftime('%Y-%m-%dT%H:%M:%S','now','-7 days')"""
    ).fetchone()

    d["rollen"] = v.execute(
        """SELECT rolle, count(*), sum(ergebnis='leer'),
                  sum(ergebnis IN ('fehler','abgebrochen')),
                  sum(tokens_in + tokens_out)
           FROM lauf WHERE gestartet > strftime('%Y-%m-%dT%H:%M:%S','now','-7 days') AND ergebnis!='laeuft'
           GROUP BY rolle ORDER BY sum(tokens_in + tokens_out) DESC"""
    ).fetchall()

    d["tage"] = v.execute(
        """SELECT date(gestartet), count(*), sum(tokens_in + tokens_out)
           FROM lauf WHERE gestartet > strftime('%Y-%m-%dT%H:%M:%S','now','-14 days')
           GROUP BY date(gestartet) ORDER BY date(gestartet)"""
    ).fetchall()

    d["letzte"] = v.execute(
        """SELECT substr(gestartet,6,11), rolle, ergebnis,
                  tokens_in + tokens_out, substr(gegenstand,1,44)
           FROM lauf ORDER BY id DESC LIMIT 12"""
    ).fetchall()

    d["laeuft"] = v.execute(
        "SELECT count(*) FROM lauf WHERE ergebnis='laeuft'").fetchone()[0]
    v.close()

    # --- Pipeline aus dem Dateisystem ---
    signale = {o.name: len(list(o.glob("*.md")))
               for o in sorted(_ordner(WURZEL / "signals")) if o.is_dir()}
    alle = repo.ideen()
    d["signale"] = signale
    d["pipeline"] = [
        ("Signale", sum(signale.values()), "von sechs Sensoren gesammelt"),
        ("Recherchen", len(list((WURZEL / "research").glob("*.md"))),
         "ausgegraben, mit Ampel"),
        ("Ideen", len(alle), "vom Ideator geschrieben"),
        ("Kandidaten", len([k for k in alle if k.get("status") == "kandidat"]),
         "durch den Fit-Filter"),
        ("geprueft", len(repo.bereit_zur_bewertung()),
         "fuenf Linsen plus Anwalt"),
        ("Vorlagen", len(list((WURZEL / "gates").glob("*.md"))),
         "warten auf dich"),
    ]

    # --- Todesursachen ---
    gruende, linsen = Counter(), Counter()
    for k in alle:
        if k.get("status") in TOT:
            g = (k.get("ablehnungsgrund") or "").strip().strip('"')
            m = re.match(r"(G\d)", g)
            gruende[m.group(1) if m else "ohne Angabe"] += 1
        ordner = WURZEL / "ideas" / f"{k['_id']}.angriffe"
        for linse in repo.LINSEN:
            datei = ordner / f"{linse}.md"
            if datei.exists():
                kopf, _ = frontmatter(datei.read_text(encoding="utf-8"))
                if kopf.get("urteil") == "widerlegt":
                    linsen[linse] += 1
    d["gruende"], d["linsen"] = gruende, linsen

    d["tot"] = [(k["_id"], k.get("ablehnungsgrund", ""))
                for k in alle if k.get("status") in TOT][-6:]
    d["lebend"] = [(k["_id"], k.get("status"), repo._score(k))
                   for k in alle if k.get("status") not in TOT]

    # --- Logbuecher ---
    d["logbuecher"] = sorted(
        ((f.stem, f.stat().st_size) for f in (WURZEL / "notizen").glob("*.md")
         if f.stem not in ("lehren", "VORLAGE")),
        key=lambda x: -x[1])[:6]
    d["grundlast"] = sum(
        (WURZEL / n).stat().st_size
        for n in ("CLAUDE.md", "grenzen.md", "notizen/lehren.md")
        if (WURZEL / n).exists())
    return d


# ---------------------------------------------------------------- Seite

def bauen(d: dict) -> str:
    h_laeufe, h_tok, h_wert = (d["heute"][0] or 0, d["heute"][1] or 0,
                               d["heute"][2] or 0)
    w_laeufe, w_tok, _ = (d["woche"][0] or 0, d["woche"][1] or 0, d["woche"][2] or 0)
    frisch, cneu, cles, aus, denken = (x or 0 for x in d["arten"])
    anteil_bremse = min(h_wert / TAGESGRENZE_USD, 1.0) if TAGESGRENZE_USD else 0

    rollen_bar = balken_svg([(r[0], r[4] or 0) for r in d["rollen"][:12]])
    tage_bar = verlauf_svg([(t[0], t[2] or 0) for t in d["tage"]])
    signal_bar = balken_svg(sorted(d["signale"].items(), key=lambda x: -x[1]))
    grund_bar = balken_svg(d["gruende"].most_common())
    linsen_bar = balken_svg(d["linsen"].most_common())
    log_bar = balken_svg(d["logbuecher"])

    rollen_zeilen = "".join(
        f"<tr><td>{html.escape(r[0])}</td><td class='n'>{r[1]}</td>"
        f"<td class='n'>{r[2] or 0}</td><td class='n'>{r[3] or 0}</td>"
        f"<td class='n'>{tsd(r[4])}</td>"
        f"<td class='n'>{tsd((r[4] or 0) // max(r[1], 1))}</td></tr>"
        for r in d["rollen"])

    letzte_zeilen = "".join(
        f"<tr><td class='mono'>{html.escape(l[0] or '')}</td>"
        f"<td>{html.escape(l[1])}</td>"
        f"<td><span class='pill {l[2]}'>{html.escape(l[2])}</span></td>"
        f"<td class='n'>{tsd(l[3])}</td>"
        f"<td class='mono dim'>{html.escape(l[4] or '')}</td></tr>"
        for l in d["letzte"])

    lebend_zeilen = "".join(
        f"<tr><td class='mono'>{html.escape(i)}</td><td>{html.escape(s or '')}</td>"
        f"<td class='n'>{p or ''}</td></tr>" for i, s, p in d["lebend"]) \
        or "<tr><td colspan='3' class='dim'>keine offenen Ideen</td></tr>"

    tot_zeilen = "".join(
        f"<tr><td class='mono'>{html.escape(i)}</td><td class='dim'>{kurz(g, 150)}</td></tr>"
        for i, g in d["tot"])

    return f"""<!doctype html>
<html lang="de"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Agentenfabrik</title>
<style>
:root {{
  --grund:#f7f8fa; --karte:#fff; --tinte:#141821; --leise:#5c6675;
  --linie:#e2e7ee; --akzent:#2c5f8d; --warn:#9a6316; --tot:#96352e; --gut:#2f6b4f;
}}
@media (prefers-color-scheme:dark) {{
  :root:not([data-theme=light]) {{
    --grund:#0f131a; --karte:#161b23; --tinte:#e3e8ef; --leise:#8590a0;
    --linie:#2a323d; --akzent:#7fb0dd; --warn:#dda55c; --tot:#dd8b82; --gut:#7fc4a0;
  }}
}}
* {{ box-sizing:border-box }}
body {{ margin:0; background:var(--grund); color:var(--tinte);
  font:15px/1.55 "IBM Plex Sans",-apple-system,Segoe UI,system-ui,sans-serif; }}
.seite {{ max-width:1180px; margin:0 auto; padding:2rem 1.25rem 4rem }}
h1 {{ font-size:1.7rem; margin:0 0 .2rem; letter-spacing:-.01em }}
h2 {{ font-size:1.02rem; margin:0 0 .9rem; letter-spacing:.02em;
  text-transform:uppercase; color:var(--leise); font-weight:600 }}
.stand {{ color:var(--leise); font-size:.86rem; margin-bottom:1.6rem }}
.raster {{ display:grid; gap:1rem; grid-template-columns:repeat(auto-fit,minmax(330px,1fr)) }}
.karte {{ background:var(--karte); border:1px solid var(--linie); border-radius:8px;
  padding:1.15rem 1.25rem }}
.karte.weit {{ grid-column:1/-1 }}
.kennzahlen {{ display:grid; gap:1px; background:var(--linie);
  grid-template-columns:repeat(auto-fit,minmax(150px,1fr));
  border:1px solid var(--linie); border-radius:8px; overflow:hidden; margin-bottom:1rem }}
.kennzahlen div {{ background:var(--karte); padding:.85rem 1rem }}
.kennzahlen dt {{ font-size:.7rem; text-transform:uppercase; letter-spacing:.09em;
  color:var(--leise); margin-bottom:.25rem }}
.kennzahlen dd {{ margin:0; font-size:1.5rem; font-weight:600;
  font-variant-numeric:tabular-nums }}
.kennzahlen small {{ display:block; color:var(--leise); font-size:.78rem;
  font-weight:400; margin-top:.1rem }}
table {{ width:100%; border-collapse:collapse; font-size:.87rem }}
th {{ text-align:left; font-size:.7rem; text-transform:uppercase; letter-spacing:.08em;
  color:var(--leise); font-weight:600; padding:.35rem .5rem; border-bottom:1px solid var(--linie) }}
td {{ padding:.38rem .5rem; border-bottom:1px solid var(--linie) }}
tr:last-child td {{ border-bottom:none }}
.n {{ text-align:right; font-variant-numeric:tabular-nums }}
.mono {{ font-family:"IBM Plex Mono",ui-monospace,Consolas,monospace; font-size:.8rem }}
.dim {{ color:var(--leise) }}
.pill {{ font-size:.7rem; padding:.1rem .45rem; border-radius:3px;
  background:var(--linie); color:var(--leise) }}
.pill.ok {{ color:var(--gut) }} .pill.leer {{ color:var(--leise) }}
.pill.fehler,.pill.abgebrochen {{ color:var(--tot) }} .pill.laeuft {{ color:var(--warn) }}
.chart {{ width:100%; height:auto; overflow:visible }}
.chart .bar {{ fill:var(--akzent); opacity:.85 }}
.chart .lbl {{ font-size:11px; fill:var(--tinte) }}
.chart .val {{ font-size:11px; fill:var(--leise); font-variant-numeric:tabular-nums }}
.chart .ax {{ font-size:9px; fill:var(--leise) }}
.stufe {{ margin-bottom:.7rem }}
.stufe-kopf {{ display:flex; justify-content:space-between; font-size:.85rem;
  margin-bottom:.2rem }}
.stufe-kopf b {{ font-variant-numeric:tabular-nums }}
.spur {{ height:7px; background:var(--linie); border-radius:4px; overflow:hidden }}
.fuell {{ height:100%; background:var(--akzent) }}
.hinweis {{ font-size:.74rem; color:var(--leise); margin-top:.15rem }}
.bremse {{ height:9px; background:var(--linie); border-radius:5px; overflow:hidden;
  margin:.5rem 0 .35rem }}
.bremse div {{ height:100%; background:{'var(--tot)' if anteil_bremse > .8 else 'var(--akzent)'} }}
.fuss {{ margin-top:2rem; padding-top:1rem; border-top:1px solid var(--linie);
  color:var(--leise); font-size:.8rem }}
.leer {{ color:var(--leise); font-size:.85rem }}
code {{ font-family:"IBM Plex Mono",monospace; font-size:.85em;
  background:var(--linie); padding:.05rem .3rem; border-radius:3px }}
</style></head><body><div class="seite">

<h1>Agentenfabrik</h1>
<p class="stand">Stand {d['erzeugt']} &middot; erzeugt von <code>agents/dashboard.py</code>
{'&middot; <b>' + str(d['laeuft']) + ' Lauf/Läufe aktiv</b>' if d['laeuft'] else ''}</p>

<dl class="kennzahlen">
  <div><dt>Läufe heute</dt><dd>{h_laeufe}</dd><small>{w_laeufe} in sieben Tagen</small></div>
  <div><dt>Tokens heute</dt><dd>{tsd(h_tok)}</dd><small>{tsd(w_tok)} in sieben Tagen</small></div>
  <div><dt>Signale</dt><dd>{sum(d['signale'].values())}</dd><small>in {len(d['signale'])} Arten</small></div>
  <div><dt>Ideen offen</dt><dd>{len(d['lebend'])}</dd><small>{len(d['tot'])}+ verworfen</small></div>
  <div><dt>Wartet auf dich</dt><dd>{d['pipeline'][-1][1]}</dd><small>Gate-Vorlagen</small></div>
</dl>

<div class="raster">

  <div class="karte">
    <h2>Tagesbremse</h2>
    <div class="bremse"><div style="width:{anteil_bremse * 100:.1f}%"></div></div>
    <p class="hinweis">{h_wert:.0f} von {TAGESGRENZE_USD:.0f} Einheiten Gegenwert.
    Ab der Grenze startet kein Lauf mehr — sie fängt Ausreißer ab, nicht den
    Normalbetrieb. Steht in <code>agents/lauf.py</code>.</p>
  </div>

  <div class="karte">
    <h2>Wohin die Tokens gehen (7 Tage)</h2>
    {balken_svg([("frisch", frisch), ("Cache neu", cneu), ("Cache gelesen", cles),
                 ("Ausgabe", aus), ("davon Denken", denken)])}
    <p class="hinweis">Cache-Lesen dominiert jede Summe, zählt aber anders als frisch
    gesendeter Kontext. Wer nur die Gesamtzahl liest, täuscht sich in beide Richtungen.
    Ältere Läufe haben die Aufschlüsselung nicht.</p>
  </div>

  <div class="karte weit">
    <h2>Tokens je Tag</h2>
    {tage_bar}
  </div>

  <div class="karte">
    <h2>Der Trichter</h2>
    {trichter(d['pipeline'])}
  </div>

  <div class="karte">
    <h2>Signale je Quelle</h2>
    {signal_bar}
  </div>

  <div class="karte weit">
    <h2>Tokens je Rolle (7 Tage)</h2>
    {rollen_bar}
    <table style="margin-top:1rem">
      <tr><th>Rolle</th><th class="n">Läufe</th><th class="n">leer</th>
          <th class="n">Fehler</th><th class="n">Tokens</th><th class="n">je Lauf</th></tr>
      {rollen_zeilen}
    </table>
  </div>

  <div class="karte">
    <h2>Woran Ideen sterben</h2>
    {grund_bar}
  </div>

  <div class="karte">
    <h2>Welche Linse widerlegt</h2>
    {linsen_bar}
  </div>

  <div class="karte">
    <h2>Offene Ideen</h2>
    <table><tr><th>Idee</th><th>Status</th><th class="n">Punkte</th></tr>
    {lebend_zeilen}</table>
  </div>

  <div class="karte">
    <h2>Zuletzt verworfen</h2>
    <table>{tot_zeilen}</table>
  </div>

  <div class="karte weit">
    <h2>Die letzten Läufe</h2>
    <table>
      <tr><th>Zeit (UTC)</th><th>Rolle</th><th>Ergebnis</th>
          <th class="n">Tokens</th><th>Gegenstand</th></tr>
      {letzte_zeilen}
    </table>
  </div>

  <div class="karte">
    <h2>Logbücher</h2>
    {log_bar}
    <p class="hinweis">Zeichen. Grenze 12.000 — darüber wird archiviert. Jedes Logbuch
    wird von seiner Rolle bei jedem Lauf gelesen.</p>
  </div>

  <div class="karte">
    <h2>Grundlast</h2>
    <p style="font-size:1.5rem;font-weight:600;margin:.2rem 0">{tsd(d['grundlast'])}
      <span style="font-size:.85rem;font-weight:400;color:var(--leise)">Zeichen</span></p>
    <p class="hinweis">CLAUDE.md, grenzen.md und lehren.md zusammen — das lädt
    <em>jeder</em> Lauf, bevor er irgendetwas tut. Rund
    {tsd(d['grundlast'] // 4)} Tokens.</p>
  </div>

</div>

<p class="fuss">Neu erzeugen mit <code>python3 agents/dashboard.py</code>.
Die Seite ist eigenständig — sie liest nichts aus dem Netz und schickt nichts dorthin.</p>
</div></body></html>"""


if __name__ == "__main__":
    if not DB.exists():
        sys.exit("Kein Journal vorhanden.")
    ZIEL.parent.mkdir(parents=True, exist_ok=True)
    ZIEL.write_text(bauen(sammeln()), encoding="utf-8")
    print(f"{ZIEL.relative_to(WURZEL)} geschrieben "
          f"({ZIEL.stat().st_size // 1024} kB).")
