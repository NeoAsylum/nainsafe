"""Erzeugt aus der ausgelieferten Quelle einen Mutanten, in dem genau eine Regel
abgeschaltet ist. Nur fuer den Rotnachweis, nicht ausgeliefert.

Aufruf: mutant.py <quelle> <ziel> <fall>

Faelle:
  bedingung2   die negative Sichtbarkeitszusicherung zaehlt wieder als Deklaration
  zerlegung    der Kommentarteil endet am Zeilenende statt am Blockschluss
  form         das Klammerpaar am Ende gehoert wieder zum Namen
  zusicherung  die Anforderung braucht keinen Namensraumdoppelpunkt mehr
  regeln       die Wendungssuche nimmt das ganze Umfeld statt der letzten zwei Woerter
"""
import sys

QUELLE, ZIEL, FALL = sys.argv[1], sys.argv[2], sys.argv[3]
t = open(QUELLE, encoding="utf-8").read()

SCHNITTE = {
    "bedingung2": (
        "                if (zus[k].anfang == i && zus[k].ende == ende) {\n"
        "                    zugesichert = true;\n"
        "                }\n",
        "                if (zus[k].anfang == i && zus[k].ende == ende) {\n"
        "                    zugesichert = false;  // MUTANT\n"
        "                }\n",
    ),
    "zerlegung": (
        "        if (c == '\"' || (c == '\\'' && !trenner_links)) {\n",
        "        if (false && (c == '\"' || (c == '\\'' && !trenner_links))) {  // MUTANT\n",
    ),
    "form": (
        "    if (text.size() >= 2 && text.substr(text.size() - 2) == \"()\") {\n"
        "        text = text.substr(0, text.size() - 2);\n"
        "    }\n",
        "    // MUTANT: das Klammerpaar bleibt am Namen\n",
    ),
    "zusicherung": (
        "        if (teile == 0) {\n            continue;\n        }\n",
        "        if (false) {  // MUTANT\n            continue;\n        }\n",
    ),
    # Die satzweite statt der unmittelbaren Fassung von Regel 11 -- die naheliegende
    # Alternative, gegen die der Zuschnitt entschieden ist.
    "regeln": (
        "bool wendung_links(std::string_view links) {\n"
        "    std::string letztes;\n",
        "bool wendung_links(std::string_view links) {  // MUTANT: satzweit\n"
        "    std::size_t a = 0;\n"
        "    while (a < links.size()) {\n"
        "        if (!ist_buchstabe(links[a])) { ++a; continue; }\n"
        "        std::size_t b = a;\n"
        "        while (b < links.size() && ist_buchstabe(links[b])) { ++b; }\n"
        "        for (std::size_t w = 0; w < WENDUNGEN.size(); ++w) {\n"
        "            if (gleich_ohne_fall(links.substr(a, b - a), WENDUNGEN[w])) {\n"
        "                return true;\n"
        "            }\n"
        "        }\n"
        "        a = b;\n"
        "    }\n"
        "    std::string letztes;\n",
    ),
}

alt, neu = SCHNITTE[FALL]
if t.count(alt) != 1:
    raise SystemExit("Schnittstelle '%s' kommt %d mal vor -- erwartet genau einmal."
                     % (FALL, t.count(alt)))
open(ZIEL, "w", encoding="utf-8").write(t.replace(alt, neu))
print("Mutant '%s' geschrieben: %s" % (FALL, ZIEL))
