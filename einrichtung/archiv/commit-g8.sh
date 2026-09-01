#!/usr/bin/env bash
# Einmaliges Hilfsskript: committet die G8/G9-Aenderungen, sobald kein Lauf aktiv ist.
set -euo pipefail
cd "$HOME/fabrik"

if pgrep -f 'agents/nachtlauf.py' >/dev/null; then
  echo "Nachtlauf laeuft noch -- nicht committet. Spaeter erneut aufrufen."
  exit 1
fi

git add -A
git commit -q -F - <<'ENDE'
G8 und G9: Zustand textuell inspizierbar, kein Personal

Das Unternehmen beschaeftigt niemanden. Damit faellt die Instanz weg, die
sonst Qualitaet sichert -- also muss ein Agent es koennen.

G8 zieht die Grenze aber NICHT zwischen visuell und textlich: Das
Kernversprechen darf der visuelle Eindruck sein. Entscheidend ist, ob der
Zustand des Systems exakt und uebersichtlich als Text abrufbar ist --
Uebersicht, Detail, Diff. Ein Staedtebauspiel ist zulaessig, wenn jedes
Gebaeude und jeder Simulationswert auslesbar ist; unzulaessig, wenn die
Wahrheit erst beim Rendern entsteht.

Der Grund fuer die Unterscheidung: Gestaltung faellt selten an, ist eine
Entscheidung und passt in ein Gate. Qualitaetssicherung faellt bei jedem
Erzeugnis an und muss maschinell laufen. Jede Idee muss deshalb benennen,
wie oft eine Gestaltungsentscheidung noetig waere -- quartalsweise ist
tragbar, woechentlich faellt schon unter G4.

Fuer die Konzeption folgt eine harte Architekturvorgabe: Datenmodell und
Darstellung getrennt, Zustandsausgabe als erstklassige Schnittstelle.

G9 schliesst aus, was Personal braucht, Freelancer eingeschlossen --
Personalfuehrung beginnt beim ersten Auftrag. Eine Plattform, auf der
andere einander beauftragen, bleibt zulaessig.

ADR 0002 hatte die Grenze zu grob gezogen und ist durch 0003 ersetzt.
ENDE

echo "committet:"
git log --oneline -1
