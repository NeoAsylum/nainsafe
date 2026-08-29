#!/usr/bin/env bash
# Zeigt die Token-Aufschluesselung der Laeufe, die sie bereits erfassen.
cd "$HOME/fabrik" || exit 1

echo "=== Laeufe mit Aufschluesselung ==="
sqlite3 -column -header state.db "
  SELECT count(*) AS laeufe,
         sum(tokens_frisch) AS frisch,
         sum(tokens_cneu)   AS cache_neu,
         sum(tokens_cles)   AS cache_gelesen,
         sum(tokens_out)    AS ausgabe,
         sum(tokens_denken) AS denken
  FROM lauf WHERE tokens_frisch > 0 OR tokens_cles > 0;"

echo
echo "=== Anteile ==="
sqlite3 state.db "
  SELECT 'frisch        ' || round(100.0*sum(tokens_frisch)/
           nullif(sum(tokens_frisch+tokens_cneu+tokens_cles+tokens_out),0),1) || ' %'
  FROM lauf WHERE tokens_cles > 0
  UNION ALL SELECT 'Cache neu     ' || round(100.0*sum(tokens_cneu)/
           nullif(sum(tokens_frisch+tokens_cneu+tokens_cles+tokens_out),0),1) || ' %'
  FROM lauf WHERE tokens_cles > 0
  UNION ALL SELECT 'Cache gelesen ' || round(100.0*sum(tokens_cles)/
           nullif(sum(tokens_frisch+tokens_cneu+tokens_cles+tokens_out),0),1) || ' %'
  FROM lauf WHERE tokens_cles > 0
  UNION ALL SELECT 'Ausgabe       ' || round(100.0*sum(tokens_out)/
           nullif(sum(tokens_frisch+tokens_cneu+tokens_cles+tokens_out),0),1) || ' %'
  FROM lauf WHERE tokens_cles > 0;"

echo
echo "=== Der letzte Lauf je Rolle, aufgeschluesselt ==="
sqlite3 -column -header state.db "
  SELECT rolle, tokens_frisch AS frisch, tokens_cneu AS c_neu,
         tokens_cles AS c_gelesen, tokens_out AS aus, tokens_denken AS denken
  FROM lauf WHERE tokens_cles > 0 ORDER BY id DESC LIMIT 9;"

echo
echo "=== Was der letzte Lauf gebracht hat ==="
git log --oneline -12 | grep -E 'scout|analyst|rechercheur|ideator|fit-filter' || echo "  (keine)"
