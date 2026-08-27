-- Zustand der Agentenfabrik.
--
-- Das Repo hält die Artefakte, diese Datenbank hält den Zustand: was lief, was es
-- kostete, was noch aussteht. Anlegen mit:  sqlite3 state.db < schema/state.sql
--
-- state.db selbst gehört NICHT ins Repo (siehe .gitignore) — sie ist reproduzierbar
-- und erzeugt sonst bei jedem Lauf Konflikte.

PRAGMA journal_mode = WAL;

-- Ein Eintrag je Agentenlauf. Die Grundlage für Kostenwächter und Digest.
CREATE TABLE IF NOT EXISTS lauf (
  id            INTEGER PRIMARY KEY,
  gestartet     TEXT    NOT NULL,          -- ISO 8601
  beendet       TEXT,
  rolle         TEXT    NOT NULL,
  gegenstand    TEXT,                      -- Ideen-ID oder Venture-ID
  tokens_in     INTEGER DEFAULT 0,
  tokens_out    INTEGER DEFAULT 0,
  -- Gegenwert zu Listenpreisen, kein Rechnungsbetrag: Claude Code meldet ihn auch
  -- bei Abo-Anmeldung, abgerechnet wird davon nichts. Der Name ist historisch.
  kosten_eur    REAL    DEFAULT 0,
  ergebnis      TEXT    NOT NULL DEFAULT 'laeuft',  -- laeuft | ok | leer | fehler
  commit_hash   TEXT,
  notiz         TEXT
);

CREATE INDEX IF NOT EXISTS idx_lauf_zeit  ON lauf (gestartet);
CREATE INDEX IF NOT EXISTS idx_lauf_rolle ON lauf (rolle, gestartet);

-- Warteschlange. Der Scheduler zieht hier, statt Rollen fest zu verdrahten.
CREATE TABLE IF NOT EXISTS aufgabe (
  id            INTEGER PRIMARY KEY,
  erstellt      TEXT    NOT NULL,
  faellig       TEXT    NOT NULL,
  rolle         TEXT    NOT NULL,
  gegenstand    TEXT,
  prioritaet    INTEGER NOT NULL DEFAULT 5,   -- 1 hoch … 9 niedrig
  status        TEXT    NOT NULL DEFAULT 'offen', -- offen | laeuft | fertig | abgebrochen
  versuche      INTEGER NOT NULL DEFAULT 0
);

CREATE INDEX IF NOT EXISTS idx_aufgabe_naechste
  ON aufgabe (status, faellig, prioritaet);

-- Spiegel des Ideenstatus für schnelle Auswertung. Wahrheit bleibt das Frontmatter
-- in ideas/ — diese Tabelle wird daraus neu aufgebaut, nie umgekehrt.
CREATE TABLE IF NOT EXISTS idee (
  id            TEXT    PRIMARY KEY,       -- z.B. 0042-rechnungspruefer
  titel         TEXT    NOT NULL,
  status        TEXT    NOT NULL,
  score_summe   INTEGER,
  score_genehm  INTEGER,
  geaendert     TEXT    NOT NULL,
  ablehnung     TEXT
);

CREATE INDEX IF NOT EXISTS idx_idee_status ON idee (status, score_summe DESC);

-- Gates, die auf eine menschliche Entscheidung warten. Speist den Digest.
CREATE TABLE IF NOT EXISTS gate (
  id            INTEGER PRIMARY KEY,
  nummer        INTEGER NOT NULL,          -- 1..4
  gegenstand    TEXT    NOT NULL,
  datei         TEXT    NOT NULL,
  erstellt      TEXT    NOT NULL,
  lesezeit_min  INTEGER,
  entscheidung  TEXT    NOT NULL DEFAULT 'offen', -- offen | ja | nein | vertagt
  entschieden   TEXT
);

CREATE INDEX IF NOT EXISTS idx_gate_offen ON gate (entscheidung, erstellt);

-- Durchsetzung des WIP-Limits: höchstens 3 aktiv, höchstens 1 im Bau.
CREATE VIEW IF NOT EXISTS wip AS
SELECT
  SUM(status IN ('erkundung','bau','live')) AS aktiv,
  SUM(status = 'bau')                       AS im_bau
FROM idee;
