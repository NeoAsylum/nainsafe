//! # Der Kennzeichenriegel -- Paket 0251
//!
//! ## Der Fall
//!
//! Ein **Riegel ohne Zustand** ist eine Schranke, vor die kein Zustand kommt. Sein Eintrag
//! im Verzeichnis einer Probe traegt eine Liste von Textstuecken -- die **Kennzeichen** --,
//! an denen seine Abbruchmeldung zu erkennen **waere**. Waere: Die Meldung kommt nie an,
//! also haelt nichts die Liste an ihrem Wortlaut fest. Wer die Meldung im Kern umformuliert,
//! laesst die Liste ins Leere zeigen, und kein Lauf wird rot. Auffallen wuerde es erst an
//! dem Tag, an dem die Schranke erreichbar wird -- an einer Aenderung, die damit nichts zu
//! tun hat, und mit einer Meldung, die in die falsche Richtung zeigt.
//!
//! Paket 0248 hat die eine Haelfte der Zusicherung gebaut: Die Liste muss auf **keine
//! fremde** Meldung passen. Die andere Haelfte braucht die **eigene**, und die gibt es
//! nicht. Der Grund ist nicht der fehlende Zustand, sondern die Bindung: Die Funktion, die
//! die Meldung baut, steht im namenlosen Namensbereich ihrer Quelle -- keine Probe kann sie
//! rufen, wie genau sie die Argumente auch kennte.
//!
//! **Der Ausweg, den es gibt:** Eine ankommende Meldung ist nicht die einzige Bindung an
//! einen Wortlaut. Der Wortlaut steht in der Quelle, und die Quelle ist lesbar. Genau das
//! tun der Belegstellen- und der Bezeichnerriegel nebenan fuer ihre eigenen Faelle. Dieser
//! Riegel liest die Verzeichnisse aus den Proben, nimmt jedes Kennzeichen und verlangt, dass
//! es im Kern **in einer Zeichenkette** vorkommt.
//!
//! ## Was dieses Programm liest
//!
//! Zweierlei, und die Trennung ist der ganze Gegenstand:
//!
//!   * **Die Verzeichnisse** -- jede Zuweisung an `RIEGEL_OHNE_ZUSTAND` unter `kern/test`,
//!     gefunden **am Namen und nicht an einem Pfad**. Das ist keine Feinheit. Am 2026-09-08
//!     hat Paket 0244 den Apparat aus einer Probe in einen gemeinsamen Kopf gehoben und die
//!     Aufzaehlungen dort gelassen, wo sie waren; seither steht das erste Verzeichnis nicht
//!     mehr allein. Ein Werkzeug mit eingebautem Dateinamen waere von diesem Umbau still auf
//!     null Eintraege gefallen -- und ein Riegel, der nichts findet, weil er nirgends
//!     hinsieht, ist genau der Zustand, gegen den dieses Paket geschrieben ist. Weder der
//!     Dateiname noch die Zahl der Verzeichnisse steht deshalb in diesem Programm; beide
//!     werden gefunden und ausgedruckt.
//!
//!   * **Den Wortlaut** -- jede Zeichenkette aus `kern/src` und `kern/include`.
//!
//! **Warum die Koepfe mitgelesen werden, obwohl die Abnahme `kern/src` nennt:** Ein Riegel
//! steht dort, wo die Groesse gerechnet wird, und der Kern rechnet in beiden Baeumen.
//! Gemessen am 2026-09-08 unter `kern/include`: **57 Vorkommen von `abbruch(` in sieben
//! Koepfen**, der Zustand traegt 26 davon, die Festkommarechnung 10. Ein Eintrag, dessen
//! Schranke in einem Kopf sitzt, waere mit dem engen Zuschnitt ein Befund gewesen, ohne
//! dass irgendetwas rostet -- heute trifft das keinen der Eintraege. Die Erweiterung
//! schwaecht die Pruefung um das, was sie zusaetzlich durchlaesst -- ein Stueck, das nur in
//! einer fremden Meldung eines Kopfes steht --, und dieser Riegel behauptet ohnehin nicht,
//! das Stueck stehe in der **richtigen** Meldung. Er behauptet, es stehe ueberhaupt
//! irgendwo im Kern. Das ist die Bindung, die heute fehlt.
//!
//! Beide Baeume ohne `bau` und ohne versteckte Ordner, aus demselben Grund wie beim
//! Bezeichnerriegel: Ein Riegel, der seinen eigenen Baubaum mitliest, misst sich doppelt.
//!
//! ## Die Zerlegung, und warum sie der tragende Teil ist
//!
//! Gesucht wird der Wortlaut **in Zeichenketten**, nicht im Dateitext. Der Unterschied ist
//! nicht theoretisch: Das Stueck `"Zustimmungsregel"` steht im Kern in einer Abbruchmeldung
//! **und** in einem gewoehnlichen Kommentar daneben. Wer den rohen Dateitext durchsucht,
//! findet es auch dann noch, wenn die Meldung laengst anders lautet -- und meldet gruen,
//! waehrend genau der Rost eingetreten ist, der hier gefangen werden soll. Ein Fall des
//! Selbsttests haelt das fest.
//!
//! Aus demselben Grund werden Kommentare auch in den Proben entfernt, ehe dort ein
//! Verzeichnis gesucht wird. Ein Verzeichnis, das in einem auskommentierten Block steht,
//! ist keines.
//!
//! **Benachbarte Zeichenketten werden verschmolzen**, weil die Sprache das tut: Der Kern
//! schreibt seine Meldungen ueber mehrere Zeilen, und ein Stueck darf die Naht zwischen zwei
//! Teilen ueberspannen. Wer sie einzeln nimmt, meldet einen Befund an einer Meldung, die
//! vollstaendig da steht. Ein Fall des Selbsttests legt ein Stueck genau auf so eine Naht.
//!
//! **Was hier nicht verschmolzen wird, und das ist der ausgeschriebene blinde Fleck:** Eine
//! Meldung, die aus mehreren getrennten Aufrufen zusammenwaechst -- der Kern hat dafuer
//! einen Schreiber --, ist zur Uebersetzungszeit kein Text. Ein Kennzeichen, das die Grenze
//! zwischen zwei solchen Aufrufen ueberspannt, meldet dieser Riegel als Befund, obwohl es
//! zur Laufzeit passte. Das ist Absicht: Ein solches Stueck ist an keiner Stelle der Quelle
//! ablesbar, also traegt es die Bindung nicht, um die es hier geht. Es kuerzer zu fassen
//! kostet eine Zeile im Verzeichnis und stellt sie wieder her.
//!
//! **Rohe Zeichenketten kann diese Zerlegung nicht**, und sie schweigt darueber nicht: Trifft
//! sie eine, bricht der Lauf mit Code 2 ab. Im Kern gibt es heute keine. Der stille Ausfall
//! -- eine Zerlegung, die an einer unbekannten Schreibweise verrutscht und danach zu wenig
//! findet -- ist die teuerste Fehlerart, die dieses Werkzeug haben kann.
//!
//! ## Wie ein Verzeichnis gelesen wird
//!
//! Ein Eintrag ist die **innerste geschweifte Gruppe, die einen qualifizierten Namen
//! enthaelt** -- also die Gruppe mit dem Aufzaehlungswert des Riegels darin, und keine
//! weitere Gruppe unter ihr, die selbst einen traegt. Das trifft die heutige Form und
//! haengt nicht an ihr: Weder die Zahl der Felder noch ihre Reihenfolge noch die Zahl der
//! Klammerebenen um die Tabelle steht in diesem Programm.
//!
//! Das Kennzeichenfeld ist unter den Feldern des Eintrags dasjenige, das **entweder eine
//! geschweifte Gruppe oder ein einfacher Bezeichner** ist -- die uebrigen Felder sind der
//! qualifizierte Aufzaehlungswert und Zeichenketten. Ein Bezeichner wird als benannte Liste
//! aufgeloest, in derselben Probe oder in einer anderen.
//!
//! Gibt es kein solches Feld oder mehr als eines, ist der Eintrag nicht lesbar, und der
//! Lauf bricht mit Code 2 ab statt mit null Befunden durchzugehen. Dasselbe gilt fuer einen
//! Bezeichner, zu dem sich keine Liste findet. Ein Riegel, der seinen Gegenstand nicht mehr
//! versteht, hat keinen gruenen Zustand.
//!
//! ## Der Boden: was dieser Riegel von sich selbst verlangt
//!
//! Alle uebrigen Schranken hier pruefen auf **null** -- keine Probe, kein Verzeichnis, kein
//! Eintrag, kein Kennzeichen. Gegen den halben Bestand hilft keine davon. Faellt die Zahl
//! der gelesenen Verzeichnisse von drei auf zwei, weil eines seine Form geaendert hat, dann
//! ist keine der Zahlen null, der Lauf bleibt gruen, und was noch geprueft wird, ist ein
//! Teilbestand, den niemand als Teil erkennt. Die Zahl selbst faengt das nicht: `ctest`
//! verschluckt die Ausgabe eines bestandenen Laufs, also gibt es keinen Leser, der zwei mit
//! drei vergleicht.
//!
//! Der Boden ist deshalb ein Quervergleich statt einer Zahl: **Jede Probe, die den Namen der
//! Tabelle im Code fuehrt, muss ein Verzeichnis hergeben.** Was zu erwarten ist, sagt der
//! Baum selbst, und eine hinzukommende Probe bringt ihre Erwartung mit. Eine eingebaute Zahl
//! taete das nicht: Sie waere eine zweite Stelle zum Nachziehen, und an dem Tag, an dem ein
//! zweites Verzeichnis entstand, waere sie rot geworden, ohne dass etwas kaputt war.
//!
//! **Gefragt wird auf der Maske**, also weder im Kommentar noch in einer Zeichenkette. Fuer
//! den Kommentar ist das die Vorgabe; fuer die Zeichenkette ist es eine Verengung, und sie
//! ist in beide Richtungen begruendet. Sie verliert nichts: Eine Tabelle ist Code und kann
//! in keiner Zeichenkette stehen, also gibt es kein verlorenes Verzeichnis, das dadurch
//! durchginge. Sie gewinnt etwas: Eine Probe darf den Namen in einer Meldung fuehren -- "kein
//! Eintrag in ..." --, ohne selbst eine Tabelle zu haben, und mit der weiteren Lesart waere
//! sie von diesem Tag an dauerhaft rot, ohne dass es dafuer einen Grund gaebe. Zwei Faelle
//! des Selbsttests halten beide Grenzen fest.
//!
//! **Wo er rot wird, und woran.** Die Auswahl trifft `stumme_proben`: eine Probe steht in
//! ihrem Ergebnis, wenn `nennungen` groesser als null und `tabellen` leer ist. Beides
//! entsteht in `lies_verzeichnisse` aus derselben Wortsuche `finde_woerter` auf derselben
//! Zerlegung -- `tabellen` traegt eine Reihe je Nennung mit `= {` dahinter, hat also nie
//! mehr davon als `nennungen`. Der Abbruch steht in `main`, unmittelbar hinter dem
//! Ausdruck der Zahlen und **vor** den drei Nullpruefungen, und beginnt mit `%zu Probe(n)
//! nennen`. Die Eingabe, die ihn erreicht: ein Probentext, in dem `RIEGEL_OHNE_ZUSTAND`
//! ausserhalb eines Kommentars steht, ohne dass irgendwo `RIEGEL_OHNE_ZUSTAND = {` folgt --
//! genau der Fall `der Name steht im Code und keine Tabelle kommt heraus`, der im Selbsttest
//! als eigener Probentext steht und dort eine gemeldete Probe ergeben **muss**. Danebengesetzt
//! stehen drei Texte, auf denen dieselbe Auswahl schweigen muss: der Name allein im
//! Kommentar, der Name allein in einer Meldung, und eine zweite Probe ohne den Namen. Ohne
//! diese drei waere der Boden eine Schranke, die jede Probe trifft.
//!
//! **Derselbe Boden eine Ebene tiefer: jede gelesene Tabelle muss einen Eintrag hergeben.**
//! Die Frage nach der Probe faengt die Tabelle nicht, die gefunden und gezaehlt, aber nicht
//! mehr verstanden wird: `lies_verzeichnisse` zaehlt eine Tabelle, sobald ihre Klammer
//! schliesst, und `eintragsgruppen` laeuft erst danach. Ein `using enum` in einer Probe
//! genuegt -- die Aufzaehlungswerte verlieren ihr Doppelpunktpaar, kein Eintrag kommt mehr
//! heraus, und weil die uebrigen Tabellen ihre Eintraege weiter liefern, faellt keine Zahl
//! auf null und keine Probe wird stumm. `leere_tabellen` sammelt diese Faelle; der Abbruch
//! steht in `main` hinter dem der stummen Proben, beginnt mit `aus %zu gelesenen Tabelle(n)`
//! und nennt zu jeder Probe die Zeile der Tabelle. Auch hier steht keine Erwartung im
//! Programm: Was eine Tabelle schuldet, sagt sie, indem sie eine ist. Die Eingabe, die den
//! Abbruch erreicht, steht als eigener Fall im Selbsttest -- eine Tabelle ohne einen
//! qualifizierten Namen darin --, daneben dieselbe Tabelle mit ihm, auf der geschwiegen
//! werden muss, und ein Text mit zwei Tabellen, von denen nur die leere gemeldet werden
//! darf. Ohne den letzten waere nicht geprueft, dass diese Schranke die Tabelle meint und
//! nicht die Probe.
//!
//! Ob eine absichtlich leere Tabelle je legitim ist, entscheidet dann die Meldung an ihrer
//! Stelle und keine Ausnahme hier -- dieselbe Doktrin wie bei den Nullpruefungen unten.
//!
//! ## Der Selbsttest, der bei jedem Aufruf mitlaeuft
//!
//! Drei Falltabellen im Programm. Sie laufen vor dem ersten Lesen des Bestands; ein
//! verfehlter Fall bricht mit Code 2 ab, ehe eine Zahl entsteht. Sie lesen den Baum nicht --
//! die Einstiege nehmen **Text und keinen Pfad**, und ein Selbsttest, der am Bestand haengt,
//! misst den Bestand statt das Programm.
//!
//! Die dritte Tabelle ist die tragende: Sie schickt zu jedem richtigen Stueck, das **nicht**
//! gemeldet werden darf, ein danebengeschriebenes, das gemeldet werden **muss**. Eine
//! Zusicherung, die auf keiner Eingabe fehlschlagen kann, ist nichts wert; also steht die
//! Eingabe, auf der sie fehlschlaegt, mit im Programm.
//!
//! ## Aufruf und Rueckgabe
//!
//! Ein Argument: die Wurzel des Vorhabens. Sie kommt von CMake und nicht aus dem Programm --
//! ein eingebauter Pfad liefe nur auf einem Rechner.
//!
//! Rueckgabe: 0 kein Befund, 1 Befunde gefunden, 2 der Riegel selbst taugt nicht -- Aufruf-
//! oder Lesefehler, ein verfehlter Fall des Selbsttests, eine rohe Zeichenkette, ein nicht
//! lesbarer Eintrag, eine Probe, die den Namen der Tabelle im Code fuehrt und kein
//! Verzeichnis hergibt, eine gelesene Tabelle ohne einen einzigen Eintrag, oder eine der
//! Zahlen unten auf null: keine gelesene Probe, kein gefundenes Verzeichnis, kein Eintrag,
//! kein Kennzeichen, keine Zeichenkette im Kern.
//!
//! Vorgaben: T4 (kein Gleitkomma -- hier trivial, es wird nichts gerechnet), ADR 0011
//! (C++20, g++). Kein Zeiger, kein rohes Feld, jeder Zugriff ueber Index.

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace {

namespace fs = std::filesystem;

// ---------------------------------------------------------------------------
// Kleine Pruefzeichen
// ---------------------------------------------------------------------------

bool ist_ziffer(char c) { return c >= '0' && c <= '9'; }

bool ist_klein(char c) { return c >= 'a' && c <= 'z'; }

bool ist_gross(char c) { return c >= 'A' && c <= 'Z'; }

bool ist_buchstabe(char c) { return ist_klein(c) || ist_gross(c); }

bool ist_namenszeichen(char c) { return ist_buchstabe(c) || ist_ziffer(c) || c == '_'; }

bool ist_namensanfang(char c) { return ist_buchstabe(c) || c == '_'; }

bool ist_leerraum(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; }

/// Der Nichtwert fuer einen Index. Ausgeschrieben und nicht als `0`, weil `0` ein
/// gueltiger Index ist und der Unterschied hier ueber einen stillen Fehlgriff entscheidet.
constexpr std::size_t NICHTS = static_cast<std::size_t>(-1);

/// Die Marke, die in der Maske an der Stelle einer Zeichenkette steht. Ein Steuerzeichen
/// und kein druckbares: Es darf mit keinem Zeichen zusammenfallen, das in Code vorkommt.
constexpr char MARKE = '\001';

// ---------------------------------------------------------------------------
// Die Zerlegung: Code ohne Kommentare, Zeichenketten als Marken
// ---------------------------------------------------------------------------

/// Der zerlegte Text einer Datei.
///
/// `maske` traegt den Code, aus dem jeder Kommentar und jede Zeichenkonstante entfernt und
/// jede Zeichenkette durch **eine** Marke ersetzt ist. Auf ihr wird nach Klammern, Kommas
/// und Namen gesucht -- ein Schraegstrichpaar in einer Zeichenkette erfindet dort keinen
/// Kommentar, und ein Doppelpunktpaar in einer Zeichenkette keinen qualifizierten Namen.
///
/// `zeile` und `literalnr` laufen zeichenweise neben `maske` her. Zwei Felder statt eines
/// Verbunds je Zeichen: Gesucht wird auf `maske` mit den Mitteln der Zeichenkette selbst,
/// und ein Feld von Verbunden traegt keine.
struct Zerlegt {
    std::string              maske;
    std::vector<std::size_t> zeile;
    std::vector<std::size_t> literalnr;
    std::vector<std::string> literale;
    std::vector<std::size_t> literalzeile;
    bool                     rohe_zeichenkette = false;
    std::size_t              rohe_zeile = 0;
};

/// Was ein Fluchtzeichen bedeutet.
///
/// Die Regel ist bewusst kurz und **auf beiden Seiten dieselbe**: Der Wortlaut im Kern und
/// das Kennzeichen in der Probe gehen durch denselben Entschluessler. Solange das so ist,
/// bleibt die Teilzeichenkettenbeziehung erhalten, auch wenn eine exotische Schreibweise
/// hier anders herauskaeme als beim Uebersetzer. Was nicht in der Liste steht, ergibt das
/// Zeichen selbst -- das trifft `\\?` und `\\/` richtig und `\\0` nicht; eine Null in einer
/// Meldung waere ihr Ende, und der Kern schreibt keine.
char entschluesselt(char c)
{
    if (c == 'n') {
        return '\n';
    }
    if (c == 't') {
        return '\t';
    }
    if (c == 'r') {
        return '\r';
    }
    return c;
}

/// Ob an `i` eine rohe Zeichenkette beginnt -- `R` unmittelbar vor einem
/// Anfuehrungszeichen, und `R` nicht selbst Teil eines Namens.
bool beginnt_rohe_zeichenkette(std::string_view text, std::size_t i)
{
    if (text[i] != 'R' || i + 1 >= text.size() || text[i + 1] != '"') {
        return false;
    }
    return i == 0 || !ist_namenszeichen(text[i - 1]);
}

/// Ob das Anfuehrungszeichen an `i` ein Zifferntrenner ist (`1'000'000`) und keine
/// Zeichenkonstante eroeffnet.
///
/// Nicht "irgendein Namenszeichen davor": Ein Trenner steht nur **in einer Zahl**, und
/// `L'x'` haette mit jener Regel eine Zeichenkonstante verloren. Zurueckgelaufen wird
/// deshalb bis zum Anfang des Wortes davor; faengt es mit einer Ziffer an, ist es eine Zahl.
/// Das trifft auch `0x1F'00`, wo das Zeichen unmittelbar davor ein Buchstabe ist.
bool ist_ziffertrenner(std::string_view text, std::size_t i)
{
    if (i == 0 || !ist_namenszeichen(text[i - 1])) {
        return false;
    }
    std::size_t anfang = i - 1;
    while (anfang > 0 && ist_namenszeichen(text[anfang - 1])) {
        --anfang;
    }
    return ist_ziffer(text[anfang]);
}

/// Ab `i` Leerraum und Kommentare ueberspringen, ohne etwas auszugeben. Wird allein
/// gebraucht, um zu sehen, ob hinter einer Zeichenkette die naechste steht -- die Sprache
/// laesst zwischen zwei benachbarten Teilen beides zu.
std::size_t hinter_fuellsel(std::string_view text, std::size_t i, std::size_t& z)
{
    const std::size_t n = text.size();
    while (i < n) {
        if (text[i] == '\n') {
            ++z;
            ++i;
        } else if (ist_leerraum(text[i])) {
            ++i;
        } else if (text[i] == '/' && i + 1 < n && text[i + 1] == '/') {
            while (i < n && text[i] != '\n') {
                ++i;
            }
        } else if (text[i] == '/' && i + 1 < n && text[i + 1] == '*') {
            i += 2;
            while (i < n && !(text[i] == '*' && i + 1 < n && text[i + 1] == '/')) {
                if (text[i] == '\n') {
                    ++z;
                }
                ++i;
            }
            i = (i < n) ? i + 2 : n;
        } else {
            break;
        }
    }
    return i;
}

Zerlegt zerlege(std::string_view text)
{
    Zerlegt z;
    const std::size_t n = text.size();
    std::size_t       i = 0;
    std::size_t       zl = 1;

    // Ein Zeichen an die Maske haengen, samt seiner Zeile. Immer ueber diese Stelle, damit
    // die drei Felder nie auseinanderlaufen koennen.
    const auto anhaengen = [&z](char zeichen, std::size_t nr_zeile, std::size_t nr_literal) {
        z.maske.push_back(zeichen);
        z.zeile.push_back(nr_zeile);
        z.literalnr.push_back(nr_literal);
    };

    while (i < n) {
        const char c = text[i];

        if (c == '\n') {
            anhaengen('\n', zl, NICHTS);
            ++zl;
            ++i;
            continue;
        }

        // Zeilenkommentar: nichts ausgeben, den Zeilenumbruch stehen lassen.
        if (c == '/' && i + 1 < n && text[i + 1] == '/') {
            while (i < n && text[i] != '\n') {
                ++i;
            }
            continue;
        }

        // Blockkommentar: ein Leerzeichen, damit nichts zusammenwaechst, was getrennt
        // geschrieben war -- und je Zeilenumbruch darin einer, damit die Zeilenzahl stimmt.
        if (c == '/' && i + 1 < n && text[i + 1] == '*') {
            anhaengen(' ', zl, NICHTS);
            i += 2;
            while (i < n && !(text[i] == '*' && i + 1 < n && text[i + 1] == '/')) {
                if (text[i] == '\n') {
                    anhaengen('\n', zl, NICHTS);
                    ++zl;
                }
                ++i;
            }
            i = (i < n) ? i + 2 : n;
            continue;
        }

        // Rohe Zeichenkette: nicht behandelt, und deshalb laut. Weitergelesen wird
        // trotzdem, damit die Meldung am Ende die erste Fundstelle nennen kann.
        if (beginnt_rohe_zeichenkette(text, i)) {
            if (!z.rohe_zeichenkette) {
                z.rohe_zeichenkette = true;
                z.rohe_zeile = zl;
            }
            anhaengen(' ', zl, NICHTS);
            i += 2;
            continue;
        }

        // Zeichenkonstante -- aber nur, wenn das Anfuehrungszeichen keine Ziffern trennt.
        if (c == '\'' && !ist_ziffertrenner(text, i)) {
            anhaengen(' ', zl, NICHTS);
            ++i;
            while (i < n && text[i] != '\'') {
                if (text[i] == '\\' && i + 1 < n) {
                    ++i;
                }
                if (text[i] == '\n') {
                    ++zl;
                }
                ++i;
            }
            i = (i < n) ? i + 1 : n;
            continue;
        }

        // Zeichenkette, samt allen unmittelbar folgenden Teilen. Die Sprache setzt sie
        // zusammen; wer sie einzeln nimmt, zerschneidet Meldungen an der Zeilengrenze.
        if (c == '"') {
            std::string       inhalt;
            const std::size_t erste = zl;
            while (true) {
                ++i;  // ueber das oeffnende Anfuehrungszeichen
                while (i < n && text[i] != '"') {
                    if (text[i] == '\\' && i + 1 < n) {
                        inhalt.push_back(entschluesselt(text[i + 1]));
                        i += 2;
                        continue;
                    }
                    if (text[i] == '\n') {
                        ++zl;
                    }
                    inhalt.push_back(text[i]);
                    ++i;
                }
                i = (i < n) ? i + 1 : n;

                std::size_t       weiter_zl = zl;
                const std::size_t weiter = hinter_fuellsel(text, i, weiter_zl);
                if (weiter < n && text[weiter] == '"') {
                    i = weiter;
                    zl = weiter_zl;
                    continue;
                }
                break;
            }
            anhaengen(MARKE, erste, z.literale.size());
            z.literale.push_back(inhalt);
            z.literalzeile.push_back(erste);
            continue;
        }

        anhaengen(c, zl, NICHTS);
        ++i;
    }
    return z;
}

// ---------------------------------------------------------------------------
// Suchen auf der Maske
// ---------------------------------------------------------------------------

std::size_t hinter_leerraum(std::string_view text, std::size_t i)
{
    while (i < text.size() && ist_leerraum(text[i])) {
        ++i;
    }
    return i;
}

/// Alle Stellen, an denen `name` als ganzes Wort auf der Maske steht -- also **jede**
/// Nennung im Code, die Definition wie die Benutzung. Zurueckgegeben wird der Index des
/// ersten Zeichens.
///
/// Weil auf der Maske gesucht wird, ist ein Treffer nie einer aus einem Kommentar und nie
/// einer aus einer Zeichenkette. Das ist der Unterschied, an dem der Boden weiter unten
/// haengt: Eine Tabelle ist Code, also kann sie in keiner Zeichenkette stehen, und eine
/// Probe, die den Namen bloss in einer Meldung fuehrt, hat deshalb keine verlorene.
std::vector<std::size_t> finde_woerter(const Zerlegt& z, std::string_view name)
{
    std::vector<std::size_t> stellen;
    const std::string&       m = z.maske;
    std::size_t              ab = 0;
    while (true) {
        const std::size_t p = m.find(name, ab);
        if (p == std::string::npos) {
            break;
        }
        ab = p + 1;
        if (p > 0 && ist_namenszeichen(m[p - 1])) {
            continue;
        }
        const std::size_t j = p + name.size();
        if (j < m.size() && ist_namenszeichen(m[j])) {
            continue;
        }
        stellen.push_back(p);
    }
    return stellen;
}

/// Alle Stellen, an denen `name` als ganzes Wort steht und dahinter `= {` folgt -- also
/// die Definitionen und nicht die Benutzungen. Zurueckgegeben wird der Index der
/// oeffnenden Klammer.
///
/// Die Wortgrenze wird nicht zweimal geschrieben: Nennung und Zuweisung sind dieselbe
/// Suche mit einer Bedingung mehr, und der Boden vergleicht die beiden Zahlen. Zwei
/// Fassungen derselben Regel koennten auseinanderlaufen, und dann verglichen sich zwei
/// Zaehlungen, die verschiedene Dinge zaehlen.
std::vector<std::size_t> finde_zuweisungen(const Zerlegt& z, std::string_view name)
{
    std::vector<std::size_t>       stellen;
    const std::string&             m = z.maske;
    const std::vector<std::size_t> woerter = finde_woerter(z, name);
    for (std::size_t w = 0; w < woerter.size(); ++w) {
        std::size_t j = hinter_leerraum(m, woerter[w] + name.size());
        if (j >= m.size() || m[j] != '=') {
            continue;
        }
        j = hinter_leerraum(m, j + 1);
        if (j >= m.size() || m[j] != '{') {
            continue;
        }
        stellen.push_back(j);
    }
    return stellen;
}

/// Die zu `auf` gehoerende schliessende Klammer, oder `NICHTS`.
std::size_t balanciert(std::string_view m, std::size_t auf)
{
    std::size_t tiefe = 0;
    for (std::size_t i = auf; i < m.size(); ++i) {
        if (m[i] == '{') {
            ++tiefe;
        } else if (m[i] == '}') {
            --tiefe;
            if (tiefe == 0) {
                return i;
            }
        }
    }
    return NICHTS;
}

struct Gruppe {
    std::size_t auf = 0;
    std::size_t zu = 0;
};

/// Alle geschweiften Gruppen im Bereich `[auf, zu]`, die aeussere eingeschlossen.
std::vector<Gruppe> gruppen_in(std::string_view m, std::size_t auf, std::size_t zu)
{
    std::vector<Gruppe>      gefunden;
    std::vector<std::size_t> stapel;
    for (std::size_t i = auf; i <= zu && i < m.size(); ++i) {
        if (m[i] == '{') {
            stapel.push_back(i);
        } else if (m[i] == '}' && !stapel.empty()) {
            Gruppe g;
            g.auf = stapel.back();
            g.zu = i;
            stapel.pop_back();
            gefunden.push_back(g);
        }
    }
    return gefunden;
}

/// Ob im Bereich der Gruppe irgendwo ein Doppelpunktpaar steht. Auf der Maske gefragt,
/// also nie in einer Zeichenkette und nie in einem Kommentar.
bool traegt_qualifizierten_namen(std::string_view m, const Gruppe& g)
{
    const std::size_t p = m.find("::", g.auf);
    return p != std::string::npos && p < g.zu;
}

/// Die Eintraege einer Tabelle: die **innersten** Gruppen mit einem qualifizierten Namen.
///
/// Das ist die Form eines Eintrags ohne eine Annahme ueber die Zahl der Klammerebenen
/// darueber. Die aeusseren Gruppen tragen den Namen nur, weil ein Eintrag in ihnen liegt;
/// eine eingebettete Kennzeichenliste traegt ihn gar nicht.
std::vector<Gruppe> eintragsgruppen(std::string_view m, std::size_t auf, std::size_t zu)
{
    const std::vector<Gruppe> alle = gruppen_in(m, auf, zu);
    std::vector<Gruppe>       eintraege;
    for (std::size_t i = 0; i < alle.size(); ++i) {
        if (!traegt_qualifizierten_namen(m, alle[i])) {
            continue;
        }
        bool kind_traegt = false;
        for (std::size_t k = 0; k < alle.size() && !kind_traegt; ++k) {
            const bool darin = alle[k].auf > alle[i].auf && alle[k].zu < alle[i].zu;
            if (darin && traegt_qualifizierten_namen(m, alle[k])) {
                kind_traegt = true;
            }
        }
        if (!kind_traegt) {
            eintraege.push_back(alle[i]);
        }
    }
    std::sort(eintraege.begin(), eintraege.end(),
              [](const Gruppe& a, const Gruppe& b) { return a.auf < b.auf; });
    return eintraege;
}

struct Feld {
    std::size_t auf = 0;  // erstes Zeichen
    std::size_t zu = 0;   // hinter dem letzten Zeichen
};

/// Die Felder eines Eintrags: an Kommas der aeussersten Ebene getrennt, aussen beschnitten.
std::vector<Feld> felder_von(std::string_view m, const Gruppe& g)
{
    std::vector<Feld> roh;
    std::size_t       tiefe = 0;
    std::size_t       anfang = g.auf + 1;
    for (std::size_t i = g.auf + 1; i < g.zu; ++i) {
        const char c = m[i];
        if (c == '{' || c == '(' || c == '[') {
            ++tiefe;
        } else if (c == '}' || c == ')' || c == ']') {
            if (tiefe > 0) {
                --tiefe;
            }
        } else if (c == ',' && tiefe == 0) {
            Feld f;
            f.auf = anfang;
            f.zu = i;
            roh.push_back(f);
            anfang = i + 1;
        }
    }
    Feld letzt;
    letzt.auf = anfang;
    letzt.zu = g.zu;
    roh.push_back(letzt);

    std::vector<Feld> beschnitten;
    for (std::size_t i = 0; i < roh.size(); ++i) {
        Feld f = roh[i];
        while (f.auf < f.zu && ist_leerraum(m[f.auf])) {
            ++f.auf;
        }
        while (f.zu > f.auf && ist_leerraum(m[f.zu - 1])) {
            --f.zu;
        }
        if (f.auf < f.zu) {
            beschnitten.push_back(f);
        }
    }
    return beschnitten;
}

bool ist_einfacher_bezeichner(std::string_view m, const Feld& f)
{
    if (f.auf >= f.zu || !ist_namensanfang(m[f.auf])) {
        return false;
    }
    for (std::size_t i = f.auf; i < f.zu; ++i) {
        if (!ist_namenszeichen(m[i])) {
            return false;
        }
    }
    return true;
}

bool ist_klammergruppe(std::string_view m, const Feld& f)
{
    return f.auf < f.zu && m[f.auf] == '{';
}

bool traegt_doppelpunktpaar(std::string_view m, const Feld& f)
{
    const std::size_t p = m.find("::", f.auf);
    return p != std::string::npos && p + 1 < f.zu;
}

// ---------------------------------------------------------------------------
// Was am Ende verglichen wird
// ---------------------------------------------------------------------------

struct Stueck {
    std::string text;
    std::size_t zeile = 0;
};

struct Eintrag {
    std::string         riegel;
    std::string         quelle;
    std::size_t         zeile = 0;
    std::vector<Stueck> kennzeichen;
};

struct Zeichenkette {
    std::string inhalt;
    std::string quelle;
    std::size_t zeile = 0;
};

struct Befund {
    std::string eintrag;
    std::string quelle;
    std::size_t zeile = 0;
    std::string stueck;
    bool        leere_liste = false;
};

/// Ein eingelesener Text mit seinem Kurznamen. **Text und kein Pfad** -- daran haengt,
/// dass der Selbsttest denselben Einstieg benutzt wie der Lauf ueber den Baum.
struct Benannt {
    std::string name;
    std::string text;
};

/// Eine einzelne gelesene Tabelle: wo sie steht und wie viele Eintraege aus ihr kamen.
///
/// Die Zeile gehoert zur Tabelle und nicht zur Probe, weil eine Probe mehr als eine tragen
/// darf. Es ist die Zeile der oeffnenden Klammer -- die Stelle, die `finde_zuweisungen`
/// zurueckgibt, und damit die einzige, die ohne eine zweite Suche zu haben ist.
struct Tabellenzahl {
    std::size_t zeile = 0;
    std::size_t eintraege = 0;
};

/// Was eine einzelne Probe zum Bestand beigetragen hat.
///
/// `nennungen` sind alle Vorkommen des Tabellennamens im Code; `tabellen` traegt eine Reihe
/// je Vorkommen, hinter dem `= {` steht und dessen Klammer dieses Programm gelesen hat.
/// Beides kommt aus derselben Zerlegung und derselben Wortsuche, also ist `tabellen.size()`
/// nie groesser als `nennungen`, und der Fall, auf den es ankommt, ist der Abstand zur Null.
///
/// Eine Reihe je Tabelle statt eines Zaehlers: Der Zaehler ist daraus abzulesen, die Zeile
/// waere aus dem Zaehler nicht zu gewinnen, und zwei Felder, die dasselbe behaupten, koennen
/// sich widersprechen.
struct Probenzahl {
    std::string               name;
    std::size_t               nennungen = 0;
    std::vector<Tabellenzahl> tabellen;
};

/// Alle Zeichenketten einer Gruppe, in der Reihenfolge der Quelle.
void stuecke_aus(const Zerlegt& z, std::size_t auf, std::size_t zu, std::vector<Stueck>& raus)
{
    for (std::size_t i = auf; i <= zu && i < z.maske.size(); ++i) {
        if (z.maske[i] != MARKE) {
            continue;
        }
        const std::size_t nr = z.literalnr[i];
        if (nr == NICHTS || nr >= z.literale.size()) {
            continue;
        }
        Stueck s;
        s.text = z.literale[nr];
        s.zeile = z.literalzeile[nr];
        raus.push_back(s);
    }
}

/// Der Name der Tabelle. Er steht **einmal** hier und nirgends sonst; der Dateiname, in
/// der sie liegt, steht ueberhaupt nicht in diesem Programm.
constexpr std::string_view TABELLE = "RIEGEL_OHNE_ZUSTAND";

/// Liest die Verzeichnisse aus einer Reihe von Probentexten.
///
/// Zwei Durchgaenge, weil eine Kennzeichenliste in einer anderen Probe stehen darf als der
/// Eintrag, der sie nennt: erst alles zerlegen, dann suchen.
///
/// `false` heisst nicht "nichts gefunden", sondern "nicht lesbar" -- der Aufrufer bricht
/// darauf ab, statt null Befunde zu melden.
///
/// `zahlen` bekommt zu **jeder** Probe einen Eintrag, auch zu der, die den Tabellennamen
/// gar nicht kennt. Erst dadurch ist die Reihe eine Erhebung und keine Trefferliste: Der
/// Boden fragt nach den Proben, aus denen nichts kam, und die stehen in einer Trefferliste
/// nicht drin.
bool lies_verzeichnisse(const std::vector<Benannt>& proben, std::vector<Eintrag>& eintraege,
                        std::vector<Probenzahl>& zahlen, std::string& klage)
{
    std::vector<Zerlegt> zerlegt;
    zerlegt.reserve(proben.size());
    for (std::size_t i = 0; i < proben.size(); ++i) {
        zerlegt.push_back(zerlege(proben[i].text));
        if (zerlegt.back().rohe_zeichenkette) {
            klage = "rohe Zeichenkette in " + proben[i].name + ", Zeile "
                    + std::to_string(zerlegt.back().rohe_zeile)
                    + " -- diese Zerlegung kann sie nicht, und still daran vorbeizulesen"
                      " waere schlimmer als abzubrechen.";
            return false;
        }
    }

    zahlen.clear();
    zahlen.reserve(proben.size());
    for (std::size_t d = 0; d < zerlegt.size(); ++d) {
        const Zerlegt&                 z = zerlegt[d];
        const std::vector<std::size_t> tabellen = finde_zuweisungen(z, TABELLE);

        Probenzahl zahl;
        zahl.name = proben[d].name;
        zahl.nennungen = finde_woerter(z, TABELLE).size();
        zahlen.push_back(zahl);
        const std::size_t zi = zahlen.size() - 1;

        for (std::size_t t = 0; t < tabellen.size(); ++t) {
            const std::size_t auf = tabellen[t];
            const std::size_t zu = balanciert(z.maske, auf);
            if (zu == NICHTS) {
                klage = "die Tabelle in " + proben[d].name + " schliesst ihre Klammer nicht.";
                return false;
            }

            const std::vector<Gruppe> gruppen = eintragsgruppen(z.maske, auf, zu);

            // Die Reihe wird hier vermerkt und nicht erst hinter der Schleife: Eine Tabelle
            // ist gelesen, sobald ihre Klammer schliesst, und ob aus ihr etwas kam, ist
            // genau die Frage, die `leere_tabellen` weiter unten stellt. Waere die Reihe
            // ein Ergebnis der Schleife, gaebe es die leere Tabelle in den Zahlen nicht --
            // dasselbe Loch eine Ebene tiefer.
            Tabellenzahl tz;
            tz.zeile = z.zeile[auf];
            tz.eintraege = gruppen.size();
            zahlen[zi].tabellen.push_back(tz);

            for (std::size_t g = 0; g < gruppen.size(); ++g) {
                const std::vector<Feld> felder = felder_von(z.maske, gruppen[g]);

                Eintrag e;
                e.quelle = proben[d].name;
                e.zeile = z.zeile[gruppen[g].auf];
                for (std::size_t f = 0; f < felder.size() && e.riegel.empty(); ++f) {
                    if (traegt_doppelpunktpaar(z.maske, felder[f])) {
                        e.riegel = z.maske.substr(felder[f].auf, felder[f].zu - felder[f].auf);
                    }
                }

                // Das Kennzeichenfeld an seiner Form erkannt und nicht an seiner Stelle:
                // Wer die Reihenfolge der Felder aendert, aendert dieses Programm nicht mit.
                std::size_t traeger = NICHTS;
                std::size_t treffer = 0;
                for (std::size_t f = 0; f < felder.size(); ++f) {
                    if (ist_klammergruppe(z.maske, felder[f])
                        || ist_einfacher_bezeichner(z.maske, felder[f])) {
                        traeger = f;
                        ++treffer;
                    }
                }
                if (treffer != 1) {
                    klage = "der Eintrag " + (e.riegel.empty() ? std::string("(ohne Namen)")
                                                              : e.riegel)
                            + " in " + proben[d].name + ", Zeile " + std::to_string(e.zeile)
                            + ", hat " + std::to_string(treffer)
                            + " Felder in der Form einer Kennzeichenliste; genau eines ist"
                              " lesbar.";
                    return false;
                }

                const Feld& kf = felder[traeger];
                if (ist_klammergruppe(z.maske, kf)) {
                    const std::size_t innen_zu = balanciert(z.maske, kf.auf);
                    if (innen_zu == NICHTS) {
                        klage = "die eingebettete Kennzeichenliste in " + proben[d].name
                                + ", Zeile " + std::to_string(e.zeile)
                                + ", schliesst ihre Klammer nicht.";
                        return false;
                    }
                    stuecke_aus(z, kf.auf, innen_zu, e.kennzeichen);
                } else {
                    const std::string listenname = z.maske.substr(kf.auf, kf.zu - kf.auf);

                    // Zwei Durchgaenge, und die eigene Probe zuerst. Jede Probe haelt ihre
                    // Listen im namenlosen Namensbereich; zwei Proben duerfen deshalb
                    // denselben Listennamen tragen, ohne dass etwas mehrdeutig waere.
                    // Wer ueber alle Proben zugleich sucht, macht aus dieser erlaubten
                    // Form einen roten Lauf. Erst wenn die eigene Probe nichts hat, ist
                    // die Frage ueberhaupt eine ueber den ganzen Baum.
                    std::size_t gefunden = 0;
                    std::size_t quelle = NICHTS;
                    std::size_t stelle = NICHTS;
                    for (std::size_t runde = 0; runde < 2 && gefunden == 0; ++runde) {
                        for (std::size_t q = 0; q < zerlegt.size(); ++q) {
                            const bool eigene = (q == d);
                            if (eigene != (runde == 0)) {
                                continue;
                            }
                            const std::vector<std::size_t> stellen =
                                finde_zuweisungen(zerlegt[q], listenname);
                            for (std::size_t s = 0; s < stellen.size(); ++s) {
                                if (balanciert(zerlegt[q].maske, stellen[s]) == NICHTS) {
                                    continue;
                                }
                                ++gefunden;
                                quelle = q;
                                stelle = stellen[s];
                            }
                        }
                    }
                    if (gefunden != 1) {
                        klage = "zum Kennzeichenfeld `" + listenname + "` des Eintrags in "
                                + proben[d].name + ", Zeile " + std::to_string(e.zeile)
                                + ", gibt es " + std::to_string(gefunden)
                                + " lesbare Liste(n); genau eine wird gebraucht.";
                        return false;
                    }
                    const std::size_t listen_zu =
                        balanciert(zerlegt[quelle].maske, stelle);
                    stuecke_aus(zerlegt[quelle], stelle, listen_zu, e.kennzeichen);
                }
                eintraege.push_back(e);
            }
        }
    }
    return true;
}

/// Die Zahl der gelesenen Verzeichnisse ueber alle Proben.
///
/// Abgeleitet und nicht danebengezaehlt: Ein zweiter Zaehler ist eine zweite Stelle, an der
/// dieselbe Sache steht, und zwei Zahlen, die dasselbe behaupten, koennen sich
/// widersprechen. Eine Summe kann das nicht.
std::size_t tabellen_zusammen(const std::vector<Probenzahl>& zahlen)
{
    std::size_t summe = 0;
    for (std::size_t i = 0; i < zahlen.size(); ++i) {
        summe += zahlen[i].tabellen.size();
    }
    return summe;
}

/// Die Proben, die den Tabellennamen ueberhaupt im Code fuehren. Das ist der Nenner des
/// Bodens weiter unten: Er verlangt genau von diesen ein Verzeichnis und von keiner anderen.
std::size_t nennende_proben(const std::vector<Probenzahl>& zahlen)
{
    std::size_t wieviele = 0;
    for (std::size_t i = 0; i < zahlen.size(); ++i) {
        if (zahlen[i].nennungen > 0) {
            ++wieviele;
        }
    }
    return wieviele;
}

/// **Der Boden dieses Riegels.** Die Proben, die den Tabellennamen im Code fuehren und aus
/// denen doch keine Tabelle kam -- zurueckgegeben als Stellen in `zahlen`, damit der
/// Aufrufer Namen und beide Zahlen ausdrucken kann.
///
/// Wogegen er steht, ist der **halb blinde Lauf**. Die uebrigen Schranken dieses Programms
/// pruefen auf null: keine Probe, kein Verzeichnis, kein Eintrag, kein Kennzeichen. Fallen
/// aber drei Verzeichnisse auf zwei, weil eines seine Form geaendert hat, dann ist keine
/// dieser Zahlen null, der Lauf bleibt gruen, und was er noch prueft, ist ein Teilbestand,
/// den niemand als Teil erkennt. Am 2026-09-08 ist ein Verzeichnis innerhalb seiner Probe
/// gewandert und ein zweites entstanden; beide Male haette eine eingebaute Zahl den Lauf
/// rot gefaerbt, ohne dass etwas kaputt war.
///
/// Der Boden ist deshalb **keine Zahl, sondern ein Quervergleich**: Was der Baum an Proben
/// hergibt, sagt selbst, wie viele Verzeichnisse zu erwarten sind. Eine Probe, die den
/// Namen nennt, hat eines; kommt keines heraus, versteht dieses Programm ihre Form nicht
/// mehr. Eine Probe, die den Namen nicht nennt, wird nicht gefragt -- deshalb kostet eine
/// neue Probe ohne Riegel ohne Zustand nichts, und eine hinzukommende mit einem ist vom
/// Tag ihres Anlegens an mitgeprueft, ohne dass hier etwas nachgezogen wird.
///
/// **Die Richtung, in die er absichtlich zu streng ist:** Eine Nennung im Code, die keine
/// Definition sein soll -- eine Deklaration ohne Rumpf etwa --, meldet er. Das ist der
/// gutmuetige Fehlschlag: Er kostet eine Zeile Begruendung an der Stelle, an der jemand so
/// etwas schreibt, waehrend die andere Richtung ein stiller Teilbestand waere.
std::vector<std::size_t> stumme_proben(const std::vector<Probenzahl>& zahlen)
{
    std::vector<std::size_t> stumm;
    for (std::size_t i = 0; i < zahlen.size(); ++i) {
        if (zahlen[i].nennungen > 0 && zahlen[i].tabellen.empty()) {
            stumm.push_back(i);
        }
    }
    return stumm;
}

/// Die Stelle einer Tabelle im Ergebnis von `lies_verzeichnisse` -- Probe und Tabelle darin.
/// Zwei Indizes statt einer Kopie von Name und Zeile: Der Aufrufer hat die Zahlen ohnehin,
/// und eine Kopie waere eine zweite Fassung derselben Angabe.
struct Leerstelle {
    std::size_t probe = 0;
    std::size_t tabelle = 0;
};

/// **Der Boden eine Ebene unter `stumme_proben`:** die Tabellen, die gelesen wurden und aus
/// denen kein einziger Eintrag kam.
///
/// `stumme_proben` fragt, ob aus einer Probe eine Tabelle kam; diese Frage laesst sich mit
/// ja beantworten, waehrend die Tabelle nichts mehr hergibt. `lies_verzeichnisse` zaehlt
/// eine Tabelle, sobald ihre Klammer schliesst -- was danach `eintragsgruppen` daraus macht,
/// aendert die Zahl nicht mehr. Verliert eine Aufzaehlung ihr Doppelpunktpaar, etwa durch
/// ein `using enum` in der Probe, findet `eintragsgruppen` keinen Eintrag; die Probe bleibt
/// nicht stumm, die Zahl der Verzeichnisse bleibt dieselbe, und nur die Zahl der Eintraege
/// faellt -- um so viel, wie in dieser einen Tabelle stand. Solange die uebrigen Tabellen
/// ihre Eintraege liefern, ist keine Zahl null und der Lauf gruen.
///
/// Wie beim Boden darueber steht die Erwartung nicht im Programm: Eine Tabelle schuldet
/// einen Eintrag, weil sie eine Tabelle ist. Eine hinzukommende bringt ihre Erwartung mit,
/// eine wegfallende nimmt sie mit sich.
///
/// **Die Richtung, in die er absichtlich zu streng ist:** Eine Tabelle, die mit Absicht leer
/// steht, meldet er. Das ist derselbe gutmuetige Fehlschlag wie oben -- er kostet eine Zeile
/// Begruendung an der Stelle, an der jemand eine leere Tabelle schreibt, waehrend die andere
/// Richtung ein Bestand waere, den niemand als Teilbestand erkennt.
std::vector<Leerstelle> leere_tabellen(const std::vector<Probenzahl>& zahlen)
{
    std::vector<Leerstelle> leer;
    for (std::size_t i = 0; i < zahlen.size(); ++i) {
        for (std::size_t t = 0; t < zahlen[i].tabellen.size(); ++t) {
            if (zahlen[i].tabellen[t].eintraege == 0) {
                Leerstelle l;
                l.probe = i;
                l.tabelle = t;
                leer.push_back(l);
            }
        }
    }
    return leer;
}

/// Sammelt den Wortlaut des Kerns: jede Zeichenkette, ohne Kommentare und ohne
/// Zeichenkonstanten.
bool sammle_wortlaut(const std::vector<Benannt>& quellen, std::vector<Zeichenkette>& raus,
                     std::string& klage)
{
    for (std::size_t i = 0; i < quellen.size(); ++i) {
        const Zerlegt z = zerlege(quellen[i].text);
        if (z.rohe_zeichenkette) {
            klage = "rohe Zeichenkette in " + quellen[i].name + ", Zeile "
                    + std::to_string(z.rohe_zeile)
                    + " -- diese Zerlegung kann sie nicht, und still daran vorbeizulesen"
                      " waere schlimmer als abzubrechen.";
            return false;
        }
        for (std::size_t k = 0; k < z.literale.size(); ++k) {
            Zeichenkette zk;
            zk.inhalt = z.literale[k];
            zk.quelle = quellen[i].name;
            zk.zeile = z.literalzeile[k];
            raus.push_back(zk);
        }
    }
    return true;
}

/// Die Pruefung selbst: jedes Kennzeichen muss in einer Zeichenkette des Kerns vorkommen.
///
/// Ein leeres Stueck und eine leere Liste sind Befunde und keine bestandene Bedingung. Ein
/// leeres Stueck steckt in jedem Text, eine leere Liste passt auf jeden -- beides bindet die
/// Meldung an nichts, und das Binden ist der ganze Zweck dieses Verzeichnisfeldes.
std::vector<Befund> gleiche_ab(const std::vector<Eintrag>&      eintraege,
                               const std::vector<Zeichenkette>& wortlaut)
{
    std::vector<Befund> befunde;
    for (std::size_t i = 0; i < eintraege.size(); ++i) {
        const Eintrag& e = eintraege[i];
        if (e.kennzeichen.empty()) {
            Befund b;
            b.eintrag = e.riegel;
            b.quelle = e.quelle;
            b.zeile = e.zeile;
            b.leere_liste = true;
            befunde.push_back(b);
            continue;
        }
        for (std::size_t k = 0; k < e.kennzeichen.size(); ++k) {
            const Stueck& s = e.kennzeichen[k];
            bool          gefunden = false;
            if (!s.text.empty()) {
                for (std::size_t q = 0; q < wortlaut.size() && !gefunden; ++q) {
                    if (wortlaut[q].inhalt.find(s.text) != std::string::npos) {
                        gefunden = true;
                    }
                }
            }
            if (!gefunden) {
                Befund b;
                b.eintrag = e.riegel;
                b.quelle = e.quelle;
                b.zeile = s.zeile;
                b.stueck = s.text;
                befunde.push_back(b);
            }
        }
    }
    return befunde;
}

// ---------------------------------------------------------------------------
// Der Selbsttest, erste Tabelle: die Zerlegung
// ---------------------------------------------------------------------------
//
// Die Marke steht in den Erwartungen als `\001` und nicht als `\x01`: Eine Achtzahlfolge
// endet nach drei Ziffern, eine Sechzehnzahlfolge frisst jede weitere Ziffer daneben. Mit
// der zweiten Schreibweise haette `"\x01" "3 Stueck"` eine andere Bedeutung als gemeint --
// eine Falle, die genau dann zuschlaegt, wenn jemand einen Fall ergaenzt.

struct Zerlegefall {
    std::string_view was;
    std::string_view eingabe;
    std::string_view maske;
    std::string_view literale;  // mit '|' verbunden
};

constexpr std::array<Zerlegefall, 8> ZERLEGEFAELLE = {{
    {"Zeilenkommentar faellt weg", "int x = 1;  // ein Wort\n", "int x = 1;  \n", ""},
    {"Ziffertrenner ist keine Zeichenkonstante", "a = 1'000'000;", "a = 1'000'000;", ""},
    {"Zeichenkonstante wird zu Leerraum", "if (c == '/') { }", "if (c ==  ) { }", ""},
    {"Schraegstrichpaar in einer Zeichenkette erfindet keinen Kommentar",
     "const char* s = \"a//b\";", "const char* s = \001;", "a//b"},
    {"Benachbarte Teile werden verschmolzen, auch ueber einen Kommentar hinweg",
     "\"eins\" /* dazwischen */ \"zwei\"", "\001", "einszwei"},
    {"Fluchtzeichen werden entschluesselt", "const char* s = \"a\\\"b\";",
     "const char* s = \001;", "a\"b"},
    {"Der Blockkommentar haelt die Zeilenzahl", "/* a\nb */ x", " \n x", ""},
    {"Ein Doppelpunktpaar in einer Zeichenkette steht nicht in der Maske",
     "f(\"a::b\");", "f(\001);", "a::b"},
}};

std::string verbunden(const std::vector<std::string>& teile)
{
    std::string ganz;
    for (std::size_t i = 0; i < teile.size(); ++i) {
        if (i > 0) {
            ganz += '|';
        }
        ganz += teile[i];
    }
    return ganz;
}

std::size_t selbsttest_zerlegung()
{
    std::size_t falsch = 0;
    for (std::size_t i = 0; i < ZERLEGEFAELLE.size(); ++i) {
        const Zerlegefall& fall = ZERLEGEFAELLE[i];
        const Zerlegt      z = zerlege(fall.eingabe);
        const std::string  lit = verbunden(z.literale);
        if (z.maske != std::string(fall.maske) || lit != std::string(fall.literale)) {
            std::fprintf(stderr,
                         "Selbsttest Zerlegung, Fall %zu verfehlt (%s).\n"
                         "  Maske:     '%s' erwartet '%s'\n"
                         "  Literale:  '%s' erwartet '%s'\n",
                         i + 1, std::string(fall.was).c_str(), z.maske.c_str(),
                         std::string(fall.maske).c_str(), lit.c_str(),
                         std::string(fall.literale).c_str());
            ++falsch;
        }
        if (z.maske.size() != z.zeile.size() || z.maske.size() != z.literalnr.size()) {
            std::fprintf(stderr,
                         "Selbsttest Zerlegung, Fall %zu: die drei Felder der Maske sind "
                         "verschieden lang (%zu, %zu, %zu). Ab hier zeigt jede Zeilenangabe "
                         "irgendwohin.\n",
                         i + 1, z.maske.size(), z.zeile.size(), z.literalnr.size());
            ++falsch;
        }
    }
    return falsch;
}

// ---------------------------------------------------------------------------
// Der Selbsttest, zweite Tabelle: das Lesen eines Verzeichnisses
// ---------------------------------------------------------------------------

struct Tabellenfall {
    std::string_view was;
    std::string_view probe;
    std::string_view zweite;    // leer, wenn es nur eine gibt
    bool             lesbar;
    std::string_view erwartet;  // "Riegel=stueck;stueck", Eintraege mit '|' getrennt
    std::size_t      stumm;     // Proben, die den Namen im Code fuehren und nichts liefern
    std::size_t      leer;      // gelesene Tabellen, aus denen kein Eintrag kam
};

constexpr std::string_view PROBE_BENANNT =
    "namespace {\n"
    "enum class RiegelOhneZustand : std::size_t { Summe, Anzahl, };\n"
    "constexpr std::array<const char*, 2> KZ_SUMME = {\n"
    "    \"Zustimmungsregel\", \"klemmt erst hinter der Summe\"};\n"
    "constexpr std::array<OhneZustand<RiegelOhneZustand>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
    "    {RiegelOhneZustand::Summe, \"Summe ausserhalb von i64\",\n"
    "     \"kein Zustand kommt hierher, \"\n"
    "     \"solange schritt_3_politik vortraegt\",\n"
    "     KZ_SUMME},\n"
    "}};\n"
    "static_assert(RIEGEL_OHNE_ZUSTAND.size() == 1);\n"
    "}\n";

constexpr std::array<Tabellenfall, 16> TABELLENFAELLE = {{
    {"benannte Liste in derselben Probe", PROBE_BENANNT, "", true,
     "RiegelOhneZustand::Summe=Zustimmungsregel;klemmt erst hinter der Summe", 0, 0},

    {"eingebettete Liste",
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {R::Eins, \"n\", \"w\", {\"alpha\", \"beta\"}},\n"
     "}};\n",
     "", true, "R::Eins=alpha;beta", 0, 0},

    {"zwei Eintraege, beide gelesen",
     "constexpr std::array<OhneZustand<R>, 2> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {R::Eins, \"n\", \"w\", {\"alpha\"}},\n"
     "    {R::Zwei, \"n\", \"w\", {\"beta\"}},\n"
     "}};\n",
     "", true, "R::Eins=alpha|R::Zwei=beta", 0, 0},

    {"Liste in einer anderen Probe",
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {R::Eins, \"n\", \"w\", KZ_ANDERSWO},\n"
     "}};\n",
     "constexpr std::array<const char*, 1> KZ_ANDERSWO = {\"gamma\"};\n", true,
     "R::Eins=gamma", 0, 0},

    {"leere Liste wird gelesen und nicht uebergangen",
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {R::Eins, \"n\", \"w\", {}},\n"
     "}};\n",
     "", true, "R::Eins=", 0, 0},

    {"derselbe Listenname in zwei Proben ist keine Mehrdeutigkeit -- die eigene gilt",
     "constexpr std::array<const char*, 1> KZ_DOPPELT = {\"eigen\"};\n"
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {R::Eins, \"n\", \"w\", KZ_DOPPELT},\n"
     "}};\n",
     "constexpr std::array<const char*, 1> KZ_DOPPELT = {\"fremd\"};\n", true,
     "R::Eins=eigen", 0, 0},

    {"zwei Felder in der Form einer Liste sind nicht lesbar",
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {R::Eins, \"n\", KZ_A, KZ_B},\n"
     "}};\n",
     "", false, "", 0, 0},

    {"kein Feld in der Form einer Liste ist nicht lesbar",
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {R::Eins, \"n\", \"w\"},\n"
     "}};\n",
     "", false, "", 0, 0},

    {"eine rohe Zeichenkette bricht ab, statt still danebenzulesen",
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {R::Eins, \"n\", \"w\", {\"alpha\"}},\n"
     "}};\n"
     "const char* roh = R\"(x)\";\n",
     "", false, "", 0, 0},

    // Die vier Faelle des Bodens. Der erste ist der, auf dem er fehlschlagen **muss**; die
    // drei danach sind die Eingaben, auf denen er schweigen muss, und ohne die er bloss
    // eine Schranke waere, die jede Probe trifft.
    {"der Name steht im Code und keine Tabelle kommt heraus -- gemeldet",
     "constexpr auto RIEGEL_OHNE_ZUSTAND = verzeichnis_bauen();\n"
     "static_assert(RIEGEL_OHNE_ZUSTAND.size() == 1);\n",
     "", true, "", 1, 0},

    {"der Name steht nur im Kommentar -- nicht gemeldet, dort steht nie eine Tabelle",
     "// siehe RIEGEL_OHNE_ZUSTAND in der Nachbarprobe\nint x = 1;\n", "", true, "", 0, 0},

    {"der Name steht nur in einer Meldung -- nicht gemeldet, Code steht in keiner",
     "void melde() { fehler(\"kein Eintrag in RIEGEL_OHNE_ZUSTAND\"); }\n", "", true, "", 0,
     0},

    {"eine zweite Probe ohne den Namen macht die erste nicht stumm",
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {R::Eins, \"n\", \"w\", {\"alpha\"}},\n"
     "}};\n",
     "int nebenan = 1;\n", true, "R::Eins=alpha", 0, 0},

    // Die Faelle des Bodens eine Ebene tiefer. Der erste ist der Koeder: eine Tabelle
    // steht da, sie wird gefunden und gezaehlt, und kein Eintrag kommt aus ihr, weil kein
    // Doppelpunktpaar darin steht -- genau das, was ein `using enum` in einer Probe
    // anrichtet. Er wird gemeldet, ohne dass die Probe stumm waere.
    {"eine Tabelle ohne qualifizierten Namen darin -- gefunden, gezaehlt, leer, gemeldet",
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {Eins, \"n\", \"w\", {\"alpha\"}},\n"
     "}};\n",
     "", true, "", 0, 1},

    // Derselbe Text mit den zwei Zeichen `R::` davor: Er muss schweigen. Ohne ihn waere
    // nicht gezeigt, dass die neue Schranke an der Leere haengt und nicht an der Tabelle.
    {"dieselbe Tabelle mit dem qualifizierten Namen -- nicht gemeldet",
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {R::Eins, \"n\", \"w\", {\"alpha\"}},\n"
     "}};\n",
     "", true, "R::Eins=alpha", 0, 0},

    // Zwei Tabellen in **einer** Probe, davon eine leer. Der Fall steht so und nicht als
    // zwei Proben, weil er sonst nichts unterschiede: Eine Schranke, die je Probe fragt,
    // wuerde bei zwei Proben ebenfalls anschlagen. Hier schlaegt sie nur an, wenn die Frage
    // der Tabelle gilt -- die Probe hat einen Eintrag und ist nicht stumm.
    {"zwei Tabellen in einer Probe, nur die leere wird gemeldet",
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {R::Eins, \"n\", \"w\", {\"alpha\"}},\n"
     "}};\n"
     "constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n"
     "    {Zwei, \"n\", \"w\", {\"beta\"}},\n"
     "}};\n",
     "", true, "R::Eins=alpha", 0, 1},
}};

std::string als_text(const std::vector<Eintrag>& eintraege)
{
    std::string ganz;
    for (std::size_t i = 0; i < eintraege.size(); ++i) {
        if (i > 0) {
            ganz += '|';
        }
        ganz += eintraege[i].riegel;
        ganz += '=';
        for (std::size_t k = 0; k < eintraege[i].kennzeichen.size(); ++k) {
            if (k > 0) {
                ganz += ';';
            }
            ganz += eintraege[i].kennzeichen[k].text;
        }
    }
    return ganz;
}

std::vector<Benannt> als_proben(std::string_view erste, std::string_view zweite)
{
    std::vector<Benannt> proben;
    Benannt              a;
    a.name = "probe_a.cpp";
    a.text = std::string(erste);
    proben.push_back(a);
    if (!zweite.empty()) {
        Benannt b;
        b.name = "probe_b.cpp";
        b.text = std::string(zweite);
        proben.push_back(b);
    }
    return proben;
}

std::size_t selbsttest_verzeichnis()
{
    std::size_t falsch = 0;
    for (std::size_t i = 0; i < TABELLENFAELLE.size(); ++i) {
        const Tabellenfall&        fall = TABELLENFAELLE[i];
        const std::vector<Benannt> proben = als_proben(fall.probe, fall.zweite);
        std::vector<Eintrag>       eintraege;
        std::vector<Probenzahl>    zahlen;
        std::string                klage;
        const bool lesbar = lies_verzeichnisse(proben, eintraege, zahlen, klage);
        if (lesbar != fall.lesbar) {
            std::fprintf(stderr,
                         "Selbsttest Verzeichnis, Fall %zu verfehlt (%s).\n"
                         "  lesbar: %d erwartet %d\n  Klage:  %s\n",
                         i + 1, std::string(fall.was).c_str(), lesbar ? 1 : 0,
                         fall.lesbar ? 1 : 0, klage.empty() ? "(keine)" : klage.c_str());
            ++falsch;
            continue;
        }
        if (!lesbar) {
            continue;
        }
        const std::string gelesen = als_text(eintraege);
        if (gelesen != std::string(fall.erwartet)) {
            std::fprintf(stderr,
                         "Selbsttest Verzeichnis, Fall %zu verfehlt (%s).\n"
                         "  gelesen:  '%s'\n  erwartet: '%s'\n",
                         i + 1, std::string(fall.was).c_str(), gelesen.c_str(),
                         std::string(fall.erwartet).c_str());
            ++falsch;
        }
        if (zahlen.size() != proben.size()) {
            std::fprintf(stderr,
                         "Selbsttest Verzeichnis, Fall %zu (%s): %zu Zahlenreihe(n) zu %zu "
                         "Probe(n). Der Boden fragt nach den Proben, aus denen nichts kam; "
                         "eine fehlende Reihe ist genau eine solche Probe, die er nicht "
                         "sieht.\n",
                         i + 1, std::string(fall.was).c_str(), zahlen.size(), proben.size());
            ++falsch;
        }
        const std::vector<std::size_t> stumm = stumme_proben(zahlen);
        if (stumm.size() != fall.stumm) {
            std::fprintf(stderr,
                         "Selbsttest Verzeichnis, Fall %zu verfehlt (%s).\n"
                         "  stumme Proben: %zu erwartet %zu\n",
                         i + 1, std::string(fall.was).c_str(), stumm.size(), fall.stumm);
            ++falsch;
        }
        const std::vector<Leerstelle> leer = leere_tabellen(zahlen);
        if (leer.size() != fall.leer) {
            std::fprintf(stderr,
                         "Selbsttest Verzeichnis, Fall %zu verfehlt (%s).\n"
                         "  leere Tabellen: %zu erwartet %zu\n",
                         i + 1, std::string(fall.was).c_str(), leer.size(), fall.leer);
            ++falsch;
        }
        for (std::size_t l = 0; l < leer.size(); ++l) {
            const Probenzahl& p = zahlen[leer[l].probe];
            if (leer[l].tabelle >= p.tabellen.size() || p.tabellen[leer[l].tabelle].zeile == 0) {
                std::fprintf(stderr,
                             "Selbsttest Verzeichnis, Fall %zu (%s): die gemeldete leere "
                             "Tabelle in %s traegt keine Zeile. Die Meldung soll die Stelle "
                             "nennen, an der jemand nachsieht; ohne Zeile nennt sie nur die "
                             "Datei.\n",
                             i + 1, std::string(fall.was).c_str(), p.name.c_str());
                ++falsch;
            }
        }
    }
    return falsch;
}

// ---------------------------------------------------------------------------
// Der Selbsttest, dritte Tabelle: der Abgleich -- die tragende
// ---------------------------------------------------------------------------
//
// Zu jedem Stueck, das nicht gemeldet werden darf, steht ein danebengeschriebenes, das
// gemeldet werden muss. Beide Faelle benutzen denselben Kerntext; sie unterscheiden sich
// allein im Verzeichnis. Eine Zusicherung, die auf keiner Eingabe fehlschlaegt, ist keine.

/// Der Kerntext aller Abgleichfaelle.
///
/// Drei Dinge stecken absichtlich darin. Erstens steht `Zustimmungsregel` sowohl in einem
/// Kommentar als auch in der Meldung -- der Kommentar darf nichts retten. Zweitens
/// zerfaellt die Meldung in zwei benachbarte Teile, und die Naht liegt **mitten** in einem
/// der gesuchten Stuecke; ohne Verschmelzung wird der richtige Fall rot. Drittens steht
/// `nur im Kommentar` allein im Kommentar und in keiner Zeichenkette.
constexpr std::string_view KERNTEXT =
    "namespace {\n"
    "// Die Bedingung an die Summe der Zustimmungsregel -- nur im Kommentar,\n"
    "// und ein Kommentar ist kein Wortlaut.\n"
    "void summe_der_regel_pruefen(i128 wert)\n"
    "{\n"
    "    if (wert > OBERGRENZE) {\n"
    "        festkomma::abbruch(\n"
    "            \"kern::schritt -- Zustimmungsregel: min(...) aus spiel.md klemmt \"\n"
    "            \"erst hinter der Summe. Ueber den ganzen Lauf.\");\n"
    "    }\n"
    "}\n"
    "}\n";

struct Abgleichfall {
    std::string_view was;
    std::string_view kennzeichen;  // Inhalt der Liste, roh in den Probentext gesetzt
    std::size_t      befunde;
};

constexpr std::array<Abgleichfall, 6> ABGLEICHFAELLE = {{
    {"jedes Stueck steht in der Meldung -- kein Befund",
     "\"Zustimmungsregel\", \"erst hinter der Summe\"", 0},
    {"ein Stueck ueberspannt die Naht zweier benachbarter Teile -- kein Befund",
     "\"klemmt erst hinter der Summe\"", 0},
    {"ein Stueck ist danebengeschrieben -- ein Befund",
     "\"Zustimmungsregel\", \"klemmt erst hinter dem Summe\"", 1},
    {"zwei Stuecke sind danebengeschrieben -- zwei Befunde",
     "\"Zustimmungsrogel\", \"klemmt erst hinter dem Summe\"", 2},
    {"ein Stueck steht nur im Kommentar des Kerns -- ein Befund", "\"nur im Kommentar\"", 1},
    {"eine leere Liste bindet nichts -- ein Befund", "", 1},
}};

std::size_t selbsttest_abgleich()
{
    std::vector<Zeichenkette> wortlaut;
    std::string               klage;
    std::vector<Benannt>      kern;
    Benannt                   k;
    k.name = "kern_a.cpp";
    k.text = std::string(KERNTEXT);
    kern.push_back(k);
    if (!sammle_wortlaut(kern, wortlaut, klage)) {
        std::fprintf(stderr, "Selbsttest Abgleich: der eigene Kerntext ist nicht lesbar -- %s\n",
                     klage.c_str());
        return ABGLEICHFAELLE.size();
    }
    if (wortlaut.empty()) {
        std::fprintf(stderr,
                     "Selbsttest Abgleich: aus dem eigenen Kerntext kam keine einzige "
                     "Zeichenkette. Jeder Fall unten waere damit gruen, und keiner haette "
                     "etwas geprueft.\n");
        return ABGLEICHFAELLE.size();
    }

    std::size_t falsch = 0;
    for (std::size_t i = 0; i < ABGLEICHFAELLE.size(); ++i) {
        const Abgleichfall& fall = ABGLEICHFAELLE[i];
        const std::string   probentext =
            std::string("constexpr std::array<OhneZustand<R>, 1> RIEGEL_OHNE_ZUSTAND = {{\n")
            + "    {R::Summe, \"n\", \"w\", {" + std::string(fall.kennzeichen) + "}},\n"
            + "}};\n";

        std::vector<Eintrag>    eintraege;
        std::vector<Probenzahl> zahlen;
        std::string             lesefehler;
        if (!lies_verzeichnisse(als_proben(probentext, ""), eintraege, zahlen, lesefehler)) {
            std::fprintf(stderr,
                         "Selbsttest Abgleich, Fall %zu (%s): das eigene Verzeichnis ist "
                         "nicht lesbar -- %s\n",
                         i + 1, std::string(fall.was).c_str(), lesefehler.c_str());
            ++falsch;
            continue;
        }
        const std::vector<Befund> befunde = gleiche_ab(eintraege, wortlaut);
        if (befunde.size() != fall.befunde) {
            std::fprintf(stderr,
                         "Selbsttest Abgleich, Fall %zu verfehlt (%s).\n"
                         "  Befunde: %zu erwartet %zu\n",
                         i + 1, std::string(fall.was).c_str(), befunde.size(), fall.befunde);
            ++falsch;
        }
    }
    return falsch;
}

// ---------------------------------------------------------------------------
// Der Baum
// ---------------------------------------------------------------------------

/// Ordner, die gar nicht erst betreten werden -- derselbe Grund wie beim Bezeichnerriegel:
/// Ein Riegel, der seinen eigenen Baubaum mitliest, misst sich doppelt.
constexpr std::array<std::string_view, 2> UNGELESENE_ORDNER = {"bau", "befunde"};

bool ist_ungelesener_ordner(std::string_view name)
{
    for (std::size_t i = 0; i < UNGELESENE_ORDNER.size(); ++i) {
        if (name == UNGELESENE_ORDNER[i]) {
            return true;
        }
    }
    return false;
}

bool ist_maschinerie(std::string_view name) { return !name.empty() && name.front() == '.'; }

bool ist_quelle(const fs::path& pfad)
{
    const std::string endung = pfad.extension().string();
    return endung == ".cpp" || endung == ".hpp";
}

/// Alle Quellen unter `wurzel`, absteigend, ohne die ungelesenen und die versteckten
/// Ordner. **Sortiert**, weil die Reihenfolge eines Verzeichnisses nicht festgelegt ist und
/// ein Riegel, dessen Ausgabe zwischen zwei Laeufen wandert, nicht vergleichbar ist.
std::vector<fs::path> sammle_quellen(const fs::path& wurzel, std::error_code& fehler)
{
    std::vector<fs::path> gefunden;
    std::vector<fs::path> offen;
    offen.push_back(wurzel);
    while (!offen.empty()) {
        const fs::path ordner = offen.back();
        offen.pop_back();
        fs::directory_iterator it(ordner, fehler);
        if (fehler) {
            return gefunden;
        }
        const fs::directory_iterator ende;
        while (it != ende) {
            const fs::path    eintrag = it->path();
            const std::string name = eintrag.filename().string();
            std::error_code   art;
            if (fs::is_directory(eintrag, art)) {
                if (!ist_maschinerie(name) && !ist_ungelesener_ordner(name)) {
                    offen.push_back(eintrag);
                }
            } else if (fs::is_regular_file(eintrag, art) && ist_quelle(eintrag)) {
                gefunden.push_back(eintrag);
            }
            it.increment(fehler);
            if (fehler) {
                return gefunden;
            }
        }
    }
    std::sort(gefunden.begin(), gefunden.end());
    return gefunden;
}

std::string kurzname(const fs::path& pfad, const std::string& wurzeltext)
{
    const std::string ganz = pfad.string();
    if (ganz.size() > wurzeltext.size() + 1
        && ganz.compare(0, wurzeltext.size(), wurzeltext) == 0) {
        return ganz.substr(wurzeltext.size() + 1);
    }
    return ganz;
}

bool lies_ganz(const fs::path& pfad, std::string& inhalt)
{
    std::ifstream strom(pfad, std::ios::binary);
    if (!strom) {
        return false;
    }
    std::ostringstream puffer;
    puffer << strom.rdbuf();
    inhalt = puffer.str();
    return true;
}

/// Liest einen Baum vollstaendig ein. `false` heisst: eine Datei war nicht lesbar -- ein
/// uebersprungener Text waere ein stiller Teilbestand und damit eine unwahre Zahl.
bool lies_baum(const fs::path& wurzel, const std::string& wurzeltext,
               std::vector<Benannt>& raus, std::string& klage)
{
    std::error_code             fehler;
    const std::vector<fs::path> pfade = sammle_quellen(wurzel, fehler);
    if (fehler) {
        klage = "Lesefehler unter '" + wurzel.string() + "': " + fehler.message();
        return false;
    }
    for (std::size_t i = 0; i < pfade.size(); ++i) {
        Benannt b;
        b.name = kurzname(pfade[i], wurzeltext);
        if (!lies_ganz(pfade[i], b.text)) {
            klage = "'" + pfade[i].string() + "' laesst sich nicht lesen.";
            return false;
        }
        raus.push_back(b);
    }
    return true;
}

/// Die Baeume, aus denen der Wortlaut kommt. Als benannte Liste und nicht verstreut in der
/// Bedingung: Wer den Kern umbaut, hat dann eine Stelle zu aendern. Die Begruendung fuer
/// **zwei** statt einem steht im Kopf dieser Datei.
constexpr std::array<std::string_view, 2> WORTLAUTBAEUME = {"src", "include"};

/// Der Baum, in dem die Verzeichnisse gesucht werden. Ein Ordner und kein Dateiname -- die
/// Datei findet dieses Programm am Namen der Tabelle.
constexpr std::string_view VERZEICHNISBAUM = "test";

}  // namespace

int main(int argc, char** argv)
{
    // Der Selbsttest laeuft vor allem anderen und braucht kein Argument. Stimmt die
    // Zerlegung oder das Lesen eines Verzeichnisses nicht, ist jede Zahl weiter unten
    // wertlos -- auch und gerade eine gruene.
    const std::size_t verfehlt =
        selbsttest_zerlegung() + selbsttest_verzeichnis() + selbsttest_abgleich();
    const std::size_t faelle =
        ZERLEGEFAELLE.size() + TABELLENFAELLE.size() + ABGLEICHFAELLE.size();
    if (verfehlt > 0) {
        std::fprintf(stderr,
                     "\nkennzeichen_riegel: %zu von %zu Faellen des Selbsttests sind nicht "
                     "wie erwartet\nausgegangen. Der Riegel hat den Bestand gar nicht erst "
                     "gelesen -- ein Messgeraet,\ndas seine eigenen Faelle verfehlt, misst "
                     "auch fremde nicht.\n",
                     verfehlt, faelle);
        return 2;
    }
    std::fprintf(stdout,
                 "kennzeichen_riegel, Selbsttest: %zu Faelle zur Zerlegung, %zu zum Lesen "
                 "eines\nVerzeichnisses und %zu zum Abgleich, alle wie erwartet.\n",
                 ZERLEGEFAELLE.size(), TABELLENFAELLE.size(), ABGLEICHFAELLE.size());

    const std::vector<std::string> argumente(argv, argv + argc);
    if (argumente.size() != 2) {
        std::fprintf(stderr,
                     "Aufruf: kennzeichen_riegel <wurzel-des-vorhabens>\n"
                     "Die Wurzel kommt von CMake; ein eingebauter Pfad liefe nur auf einem "
                     "Rechner.\n");
        return 2;
    }

    std::error_code fehler;
    const fs::path  wurzel = fs::weakly_canonical(fs::path(argumente[1]), fehler);
    if (fehler || !fs::is_directory(wurzel, fehler)) {
        std::fprintf(stderr, "kennzeichen_riegel: '%s' ist kein Verzeichnis.\n",
                     argumente[1].c_str());
        return 2;
    }
    const std::string wurzeltext = wurzel.string();
    const fs::path    kernwurzel = wurzel / "kern";
    if (!fs::is_directory(kernwurzel, fehler)) {
        std::fprintf(stderr,
                     "kennzeichen_riegel: unter '%s' liegt kein Kern. Dieser Riegel prueft "
                     "den Kern\nund nichts sonst; ohne ihn hat er keinen Gegenstand.\n",
                     wurzeltext.c_str());
        return 2;
    }

    // ------------------------------------------------------------------
    // Die Proben mit den Verzeichnissen
    // ------------------------------------------------------------------
    const fs::path probenwurzel = kernwurzel / std::string(VERZEICHNISBAUM);
    if (!fs::is_directory(probenwurzel, fehler)) {
        std::fprintf(stderr,
                     "kennzeichen_riegel: '%s' ist kein Verzeichnis. Dort stehen die "
                     "Proben, und ohne\nsie gibt es kein Verzeichnis zu lesen.\n",
                     probenwurzel.string().c_str());
        return 2;
    }
    std::vector<Benannt> proben;
    std::string          klage;
    if (!lies_baum(probenwurzel, wurzeltext, proben, klage)) {
        std::fprintf(stderr, "kennzeichen_riegel: %s\n", klage.c_str());
        return 2;
    }
    if (proben.empty()) {
        std::fprintf(stderr,
                     "kennzeichen_riegel: keine einzige Probe unter '%s'. Das ist kein "
                     "gruener Lauf,\nsondern ein Riegel ohne Gegenstand.\n",
                     probenwurzel.string().c_str());
        return 2;
    }

    std::vector<Eintrag>    eintraege;
    std::vector<Probenzahl> zahlen;
    if (!lies_verzeichnisse(proben, eintraege, zahlen, klage)) {
        std::fprintf(stderr,
                     "kennzeichen_riegel: %s\nEin Riegel, der seinen Gegenstand nicht mehr "
                     "versteht, hat keinen gruenen Zustand.\n",
                     klage.c_str());
        return 2;
    }
    const std::size_t verzeichnisse = tabellen_zusammen(zahlen);

    std::size_t kennzeichen = 0;
    for (std::size_t i = 0; i < eintraege.size(); ++i) {
        kennzeichen += eintraege[i].kennzeichen.size();
    }

    // Die Zahlen stehen hier und nicht als Erwartung im Programm. Wie viele Verzeichnisse
    // es gibt, entscheidet der Baum: Am 2026-09-08 wurde aus einem ein zweites, und ein
    // Werkzeug mit eingebauter Zahl waere an dem Tag rot geworden, ohne dass etwas kaputt
    // war. Auf null geprueft wird trotzdem -- das ist keine Erwartung, sondern die Frage,
    // ob ueberhaupt hingesehen wurde.
    std::fprintf(stdout,
                 "kennzeichen_riegel: %zu Probe(n) unter kern/%s gelesen, davon nennen %zu "
                 "den Namen\nder Tabelle im Code; %zu Verzeichnis(se) gefunden, %zu "
                 "Eintrag/Eintraege, %zu Kennzeichen\ngeprueft.\n",
                 proben.size(), std::string(VERZEICHNISBAUM).c_str(), nennende_proben(zahlen),
                 verzeichnisse, eintraege.size(), kennzeichen);

    // Der Boden, und er steht **vor** den Nullpruefungen darunter: Er stellt dieselbe Frage
    // je Probe statt ueber den ganzen Baum und nennt dabei die Datei. Faellt der Bestand von
    // drei Verzeichnissen auf zwei, ist keine der Zahlen darunter null und nur diese
    // Schranke schlaegt an; faellt er auf null, schlagen beide an, und die genauere Meldung
    // soll die sein, die der Leser zuerst bekommt.
    const std::vector<std::size_t> stumm = stumme_proben(zahlen);
    if (!stumm.empty()) {
        std::fprintf(stderr,
                     "\nkennzeichen_riegel: %zu Probe(n) nennen `%s` im Code, und aus ihnen "
                     "hat dieses\nProgramm kein Verzeichnis gelesen:\n",
                     stumm.size(), std::string(TABELLE).c_str());
        for (std::size_t i = 0; i < stumm.size(); ++i) {
            const Probenzahl& p = zahlen[stumm[i]];
            std::fprintf(stderr, "  %-40s %zu Nennung(en) im Code, 0 gelesene Tabelle(n)\n",
                         p.name.c_str(), p.nennungen);
        }
        std::fprintf(stderr,
                     "Gelesen wurden im ganzen Baum %zu Verzeichnis(se) aus %zu Probe(n).\n"
                     "Das ist kein leerer Bestand, sondern ein halber -- und ein halber "
                     "Bestand geht ohne\ndiese Schranke gruen durch, weil keine Zahl dabei "
                     "auf null faellt. Entweder hat eine\nTabelle ihre Form geaendert, dann "
                     "liest dieses Programm sie wieder, wenn die Form\nhier steht; oder die "
                     "Probe fuehrt den Namen nur noch, ohne eine zu haben, dann faellt\nder "
                     "Name.\n",
                     verzeichnisse, proben.size());
        return 2;
    }

    // Derselbe Boden eine Ebene tiefer, und aus demselben Grund vor den Nullpruefungen: Eine
    // Tabelle, die gefunden und gezaehlt wird und keinen Eintrag hergibt, laesst keine der
    // Zahlen darunter auf null fallen, solange die uebrigen Tabellen liefern. Diese Schranke
    // nennt die Probe und die Zeile; `eintraege.empty()` weiter unten nennt nur eine Summe.
    const std::vector<Leerstelle> leer = leere_tabellen(zahlen);
    if (!leer.empty()) {
        std::fprintf(stderr,
                     "\nkennzeichen_riegel: aus %zu gelesenen Tabelle(n) ist kein einziger "
                     "Eintrag\ngekommen:\n",
                     leer.size());
        for (std::size_t i = 0; i < leer.size(); ++i) {
            const Probenzahl& p = zahlen[leer[i].probe];
            std::fprintf(stderr, "  %-40s Zeile %zu\n", p.name.c_str(),
                         p.tabellen[leer[i].tabelle].zeile);
        }
        std::fprintf(stderr,
                     "Gelesen wurden im ganzen Baum %zu Verzeichnis(se) mit %zu "
                     "Eintrag/Eintraegen.\nEin Eintrag ist die innerste geschweifte Gruppe "
                     "mit einem qualifizierten Namen darin;\nverliert die Aufzaehlung ihr "
                     "Doppelpunktpaar -- ein `using enum` in der Probe genuegt --,\nsteht "
                     "die Tabelle weiter da, wird weiter gezaehlt und ist doch nicht mehr "
                     "gelesen.\nEntweder faellt das `using enum`, oder die Form des Eintrags "
                     "steht hier neu; eine\nabsichtlich leere Tabelle wird an ihrer Stelle "
                     "begruendet und nicht hier ausgenommen.\n",
                     verzeichnisse, eintraege.size());
        return 2;
    }

    if (verzeichnisse == 0) {
        std::fprintf(stderr,
                     "kennzeichen_riegel: keine einzige Zuweisung an `%s` unter '%s' "
                     "gefunden.\nEin Werkzeug, das nichts findet, weil es nirgends "
                     "hinsieht, ist genau der\nZustand, gegen den dieser Riegel geschrieben "
                     "ist -- also Code 2 und nicht gruen.\n",
                     std::string(TABELLE).c_str(), probenwurzel.string().c_str());
        return 2;
    }
    if (eintraege.empty()) {
        std::fprintf(stderr,
                     "kennzeichen_riegel: %zu Verzeichnis(se) gefunden und keinen einzigen "
                     "Eintrag darin.\nEntweder hat sich die Form der Tabelle geaendert, dann "
                     "ist das die Ursache, oder\nes gibt keinen Riegel ohne Zustand mehr. Nur "
                     "im zweiten Fall wird diese Schranke\ngeaendert, und zwar mit "
                     "Begruendung an ihrer Stelle.\n",
                     verzeichnisse);
        return 2;
    }
    if (kennzeichen == 0) {
        std::fprintf(stderr,
                     "kennzeichen_riegel: %zu Eintrag/Eintraege und kein einziges "
                     "Kennzeichen darin.\nDann prueft der Abgleich unten nichts, und seine "
                     "Null waere keine Aussage.\n",
                     eintraege.size());
        return 2;
    }

    // ------------------------------------------------------------------
    // Der Wortlaut des Kerns
    // ------------------------------------------------------------------
    std::vector<Benannt> quellen;
    std::string          baumnamen;
    for (std::size_t i = 0; i < WORTLAUTBAEUME.size(); ++i) {
        const std::string baum(WORTLAUTBAEUME[i]);
        if (i > 0) {
            baumnamen += " und ";
        }
        baumnamen += "kern/" + baum;
        const fs::path unterbaum = kernwurzel / baum;
        if (!fs::is_directory(unterbaum, fehler)) {
            std::fprintf(stderr,
                         "kennzeichen_riegel: '%s' ist kein Verzeichnis. Dort steht der "
                         "Wortlaut, gegen den\ngeprueft wird; fehlt einer der Baeume, ist "
                         "die Pruefung unvollstaendig statt gruen.\n",
                         unterbaum.string().c_str());
            return 2;
        }
        if (!lies_baum(unterbaum, wurzeltext, quellen, klage)) {
            std::fprintf(stderr, "kennzeichen_riegel: %s\n", klage.c_str());
            return 2;
        }
    }

    std::vector<Zeichenkette> wortlaut;
    if (!sammle_wortlaut(quellen, wortlaut, klage)) {
        std::fprintf(stderr, "kennzeichen_riegel: %s\n", klage.c_str());
        return 2;
    }
    std::fprintf(stdout,
                 "kennzeichen_riegel: %zu Quelle(n) unter %s gelesen, %zu Zeichenkette(n).\n",
                 quellen.size(), baumnamen.c_str(), wortlaut.size());
    if (wortlaut.empty()) {
        std::fprintf(stderr,
                     "kennzeichen_riegel: keine einzige Zeichenkette unter %s. Dann waere "
                     "jedes\nKennzeichen ein Befund, und die Befunde saegen an der Zerlegung "
                     "statt am Kern.\n",
                     baumnamen.c_str());
        return 2;
    }

    // ------------------------------------------------------------------
    // Die Pruefung
    // ------------------------------------------------------------------
    const std::vector<Befund> befunde = gleiche_ab(eintraege, wortlaut);
    if (befunde.empty()) {
        std::fprintf(stdout,
                     "kennzeichen_riegel: kein Befund -- jedes Kennzeichen steht im "
                     "Wortlaut des Kerns.\n");
        return 0;
    }

    std::fprintf(stderr, "\nkennzeichen_riegel: %zu Befund(e).\n\n", befunde.size());
    for (std::size_t i = 0; i < befunde.size(); ++i) {
        const Befund& b = befunde[i];
        if (b.leere_liste) {
            std::fprintf(stderr,
                         "  %s (%s, Zeile %zu)\n"
                         "      Die Kennzeichenliste ist leer. Eine leere Liste passt auf "
                         "jeden Text und\n      bindet den Eintrag an keine Meldung -- das "
                         "ist der Rost, nicht sein Gegenteil.\n",
                         b.eintrag.c_str(), b.quelle.c_str(), b.zeile);
            continue;
        }
        std::fprintf(stderr,
                     "  %s (%s, Zeile %zu)\n"
                     "      Kennzeichen: '%s'\n"
                     "      Dieses Stueck steht in keiner Zeichenkette unter %s.\n",
                     b.eintrag.c_str(), b.quelle.c_str(), b.zeile,
                     b.stueck.empty() ? "(leer)" : b.stueck.c_str(), baumnamen.c_str());
    }
    std::fprintf(stderr,
                 "\nEin Kennzeichen ist die Behauptung, die Meldung des Riegels sei daran zu "
                 "erkennen.\nSteht das Stueck im Kern nirgends, ist die Behauptung falsch "
                 "geworden -- entweder\nwurde die Meldung umformuliert, dann gehoert die "
                 "Liste nachgezogen, oder das Stueck\nwar nie ihr Wortlaut. Beides wird an "
                 "der Liste geaendert und nicht hier.\n");
    return 1;
}
