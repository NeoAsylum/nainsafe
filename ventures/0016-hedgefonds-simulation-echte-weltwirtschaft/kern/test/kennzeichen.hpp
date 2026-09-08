#pragma once
//! Das Kennzeichenverzeichnis der Proben -- der Nachweis, dass eine Abbruchmeldung
//! ihren Riegel wirklich kenntlich macht (Paket 0107, zweite Kategorie aus Paket 0248,
//! hierher gehoben von Paket 0244).
//!
//! **Warum es diese Datei gibt.** Der Apparat stand bis zum 2026-09-08 vollstaendig in
//! `kern/test/schritt_probe.cpp` und in keiner zweiten Probe. `kern/test/werte_probe.cpp`
//! traegt die groessere Haelfte der Abbruchstellen und hatte nichts davon: vierzehn
//! Aufrufe, die allein pruefen, *dass* geworfen wurde, und keiner davon nannte einen
//! Riegel. Aus Paket 0242 ist dort zugleich eine zweite, kleinere Fassung derselben
//! Idee entstanden -- ein Zaehler und eine Vollzaehligkeitsprobe fuer genau einen
//! Riegel. Zwei Fassungen derselben Sache in zwei Dateien sind die Verdopplung, gegen
//! die `kern/include/kern/meldung.hpp` geschrieben wurde.
//!
//! **Eine Riegelaufzaehlung je Probe, kein gemeinsames Verzeichnis.** Die
//! Vollzaehligkeitshaelfte verlangt zu jedem eingetragenen Riegel in **jedem** Lauf eine
//! angekommene Meldung. Ein Riegel von `kern::werte`, der in `schritt_probe` feuerte,
//! waere keine Aussage ueber `kern::schritt` -- und genau diese Trennschaerfe ist der
//! Wert der Haelfte. `Buch` ist deshalb auf den Aufzaehlungstyp der Probe geschablont;
//! die Verzeichnisse selbst stehen in der Probe, nicht hier.
//!
//! **Was die Probe mitbringt und was hier steht.** Hier steht die Mechanik: das Ablegen
//! der Meldungen, der Vergleich jeder Liste gegen jede Meldung, die Vollzaehligkeit und
//! die Ausgabe. In der Probe stehen die Aufzaehlung, die Namensfunktion, die
//! Kennzeichenlisten und die Aufrufstellen. Der Fehlerzaehler der Probe wird
//! hereingereicht, damit ein Fehlschlag hier denselben Rueckgabewert erzeugt wie einer
//! dort.
//!
//! ## Die zwei Kategorien
//!
//! `Buch` fuehrt zwei Verzeichnisse, und beide sind hier richtig aufgehoben -- die
//! zweite ist **nicht** eigen zu `kern::schritt`:
//!
//!   * **Riegel mit Zustand.** Zu jedem kommt in jedem Lauf mindestens eine Meldung an.
//!     Sie tragen beide Haelften der Eindeutigkeit: Die Liste passt auf jede eigene
//!     Meldung und auf keine fremde.
//!   * **Riegel ohne Zustand** (`OhneZustand`). Eine Schranke, vor die kein Zustand
//!     kommt, liefert nie eine Meldung; sie in die erste Kategorie zu setzen faerbte
//!     einen heilen Baum rot, sie wegzulassen versteckte sie vor der Pruefung, die es
//!     gibt, damit keine Schranke unbemerkt verschwindet. Von der Eindeutigkeit bleibt
//!     die erste Haelfte -- die Liste passt auf keine fremde Meldung --, die zweite
//!     braucht eine eigene Meldung und ist ohne sie nicht zu haben. Beide Proben haben
//!     einen solchen Fall; die Begruendung je Eintrag steht in `warum` und wird in jedem
//!     Lauf gedruckt.
//!
//! Der eigene Aufzaehlungstyp der zweiten Kategorie ist die Sperre gegen den bequemen
//! Ausweg: Wer einen erreichbaren Riegel dorthin schoebe, um die Vollzaehligkeit zu
//! umgehen, muesste zugleich seine Abbruchstelle umschreiben -- `Buch::bricht_ab_mit`
//! nimmt den Typ der ersten Kategorie entgegen und keinen anderen.
//!
//! ## Die Sperre gilt fuer diese Datei nicht -- gemessen, nicht vermutet
//!
//! Die Bauliste des Kerns haelt den Sperrebindungsriegel ueber zwei Sammlern: Der eine
//! liest die Quellen unter `src/`, der andere die Proben unter `test/`. Beide sammeln nur
//! die Endung fuer eine Quelle. Ein Kopf unter `test/` steht damit in keiner der beiden
//! Mengen, und der dritte Sammler daneben nimmt allein die Koepfe unter `include/kern/`
//! und wird vom Riegel gar nicht gelesen. Diese Datei bindet `kern/sperre.hpp` nicht, und
//! niemand prueft, dass sie es tut.
//!
//! Sie **kann** ihn auch nicht einfach binden: Die Vergiftung gilt ab ihrer Zeile bis
//! zum Ende der Uebersetzungseinheit, und ein Kopf, den eine Probe vor den Koepfen des
//! Kerns einbindet, vergiftete diese mit.
//!
//! **Was die Luecke kostet.** Der Riegel nimmt die Proben ausdruecklich mit auf, weil
//! sie die teurere Haelfte sind: Was eine Quelle falsch rechnet, faellt an einer Probe
//! auf; was eine Probe falsch rechnet, faellt an nichts auf, denn sie ist die Stelle,
//! die den Sollwert nennt. Dasselbe gilt fuer diesen Kopf. Er rechnet heute nichts --
//! er vergleicht Zeichenketten und zaehlt --, also ist die Luecke heute folgenlos; wer
//! hier einen Erwartungswert ausrechnet, ist morgen ungesperrt.
//!
//! **Nicht in diesem Paket geschlossen, und das ist gewollt.** Die Bauliste des Kerns
//! steht nicht in der Dateiliste von Paket 0244. Wer die Luecke schliesst, braucht ein
//! eigenes Paket und zwei Entscheidungen: ob der Sammler auch die Koepfe unter `test/`
//! liest, und ob die zweite Bedingung des Riegels -- der Sperrkopf als letzter
//! `#include` -- fuer einen Kopf ueberhaupt gelten kann, dem in der Uebersetzungseinheit
//! noch andere folgen.

#include <array>
#include <cstddef>
#include <cstdio>
#include <span>
#include <stdexcept>

namespace probe::kennzeichen {

/// Die Textstuecke, an denen eine Abbruchmeldung ihren Riegel zu erkennen gibt.
using Kennzeichen = std::span<const char* const>;

/// Was von einem Abbruch uebrig bleibt, nachdem der Fangblock zu ist.
///
/// Die Meldung wird **abgeschrieben** und nicht gemerkt: `what()` zeigt in die Ausnahme,
/// und die ist hinter der schliessenden Klammer fort. Die Kennzeichen dagegen sind
/// Zeichenkettenliterale mit statischer Lebensdauer -- von ihnen genuegen die Zeiger;
/// nur das Feld, in dem sie an der Aufrufstelle stehen, stirbt mit ihrer Funktion.
///
/// `MELDUNGEN_MAX` ist eine Puffergrenze und keine Zusicherung: Sie faengt die Probe,
/// die mehr Abbruchstellen bekommt, als das Verzeichnis fassen kann, statt still die
/// uebrigen zu uebergehen. Sie steht auf 64, weil `werte_probe` seit Paket 0255 allein
/// fuenfunddreissig Meldungen ablegt -- vierzehn ueber `bricht_ab_mit`, einundzwanzig
/// ueber `merke` -- und die Zahl bei jedem Paket waechst.
constexpr std::size_t MELDUNGEN_MAX = 64;
constexpr std::size_t MELDUNG_ZEICHEN = 512;
constexpr std::size_t KENNZEICHEN_MAX = 8;

/// Ob `nadel` in `heuhaufen` vorkommt -- ohne `<cstring>` und ohne `<string>`, die nach
/// dem Sperrkopf keine Probe mehr einbinden darf.
inline bool enthaelt(const char* heuhaufen, const char* nadel)
{
    if (heuhaufen == nullptr || nadel == nullptr) {
        return false;
    }
    for (std::size_t i = 0; heuhaufen[i] != '\0'; ++i) {
        std::size_t j = 0;
        while (nadel[j] != '\0' && heuhaufen[i + j] == nadel[j]) {
            ++j;
        }
        if (nadel[j] == '\0') {
            return true;
        }
    }
    return false;
}

/// Ob **alle** Stuecke einer Kennzeichenliste in `text` vorkommen -- dieselbe Frage, die
/// `Buch::bricht_ab_mit` an der eigenen Meldung stellt, hier an einer fremden.
///
/// Eine leere Liste passt auf jeden Text. Das ist gewollt und harmlos: Der leere Fall
/// faellt schon vorher auf -- bei einem Riegel mit Zustand an der Aufrufstelle, bei
/// einem ohne Zustand in seiner eigenen Pruefung --, und ihn hier zusaetzlich
/// durchzulassen ergaebe nur eine zweite Meldung ueber dieselbe Sache.
inline bool alle_stuecke_in(Kennzeichen kennzeichen, const char* text)
{
    for (const char* const stueck : kennzeichen) {
        if (!enthaelt(text, stueck)) {
            return false;
        }
    }
    return true;
}

/// Eine abgelegte Abbruchmeldung samt der Liste, mit der ihre Aufrufstelle sie erwartet
/// hat.
///
/// `riegel` traegt keinen Ausserhalbwert: Gelesen werden nur die Eintraege bis
/// `Buch::anzahl`, und die sind alle belegt. Ein zusaetzlicher Leerwert waere ein Zustand
/// mehr, den jede Schleife hier mitfuehren muesste.
template <typename R>
struct Angekommen {
    R                                       riegel = R{};
    const char*                             was = nullptr;
    int                                     zeile = 0;
    std::size_t                             anzahl = 0;
    std::array<const char*, KENNZEICHEN_MAX> kennzeichen{};
    std::array<char, MELDUNG_ZEICHEN>       meldung{};
};

/// Ein Eintrag des zweiten Verzeichnisses: ein Riegel, den kein Zustand erreicht.
///
/// `warum` steht daneben und wird ausgedruckt. Ein Riegel ohne Zustand ist eine
/// Behauptung ueber die Erreichbarkeit, und wer sie im naechsten Lauf pruefen will, soll
/// den Grund lesen koennen, ohne ihn zu suchen.
template <typename O>
struct OhneZustand {
    O           riegel;
    const char* name;
    const char* warum;
    Kennzeichen kennzeichen;
};

/// Das Verzeichnis einer Probe: die angekommenen Meldungen, die beiden Kategorien und
/// die Auswertung.
///
/// Der erste Schablonenparameter ist der Aufzaehlungstyp der Riegel mit Zustand, der
/// zweite der der Riegel ohne. Zwei Typen und nicht einer -- der Unterschied ist die
/// Sperre, die im Kopf begruendet ist.
///
/// Der Fehlerzaehler wird als Verweis gehalten und nicht zurueckgegeben: Ein Fehlschlag
/// im Verzeichnis soll denselben Rueckgabewert erzeugen wie jede andere Pruefung der
/// Probe, ohne dass eine Aufrufstelle ihn weiterreichen muss.
template <typename R, typename O>
class Buch {
public:
    /// Die Namensfunktion der Probe. Hereingereicht und nicht ueber die Argumentsuche
    /// gefunden: Der Aufzaehlungstyp steht im namenlosen Namensbereich der Probe, und
    /// eine Bindung, die davon abhinge, waere beim naechsten Umbau still weg.
    using Namensgeber = const char* (*)(R);

    Buch(const char* wessen, int& fehlgeschlagen, std::span<const R> alle_riegel,
         Namensgeber namensgeber, std::span<const OhneZustand<O>> ohne_zustand)
        : wessen_(wessen),
          fehlgeschlagen_(fehlgeschlagen),
          alle_riegel_(alle_riegel),
          namensgeber_(namensgeber),
          ohne_zustand_(ohne_zustand)
    {
    }

    /// Fuehrt `tun` aus und sichert zu, dass **dieser** Riegel abgebrochen hat -- nicht
    /// irgendeiner (Paket 0085).
    ///
    /// Der Unterschied zu einem blossen "es hat geworfen" ist der Grund des Apparats:
    /// Eine Schranke wird oft doppelt gehalten. Faellt die aeussere weg, wirft die
    /// innere weiter, nur mit einer Meldung, die die Ursache nicht mehr nennt -- eine
    /// Probe, die nur nach dem Wurf fragt, bleibt dabei gruen.
    ///
    /// **Nicht der ganze Wortlaut, sondern Stuecke.** Ein Volltextvergleich ginge bei
    /// jeder Umformulierung rot und erzoege dazu, die erwartete Zeichenkette nachzuziehen
    /// statt hinzusehen. Verlangt wird, was den Riegel eindeutig macht und eine
    /// Umformulierung des Restes ueberlebt.
    ///
    /// **Die Kennung des Riegels ist ein eigenes Argument** und nicht aus den
    /// Kennzeichen erschlossen. Sie zu erschliessen ginge im Kreis: Ob zwei Stellen
    /// denselben Riegel meinen, waere dann eine Aussage ueber genau die Textstuecke,
    /// deren Trennschaerfe die Zusicherung erst nachweisen soll.
    ///
    /// Der Fehlerfall druckt **beide** Zeichenketten, die erwartete und die angekommene:
    /// Ein "falsche Meldung" ohne Wortlaut kostet den naechsten Lauf einen eigenen Bau,
    /// nur um zu sehen, was denn nun ankam.
    template <typename Aufgabe>
    void bricht_ab_mit(const char* was, R welcher, Kennzeichen kennzeichen, int zeile,
                       Aufgabe tun)
    {
        // Alles am Wortlaut geschieht **innerhalb** des Fangblocks: `what()` zeigt in die
        // Ausnahme, und die ist hinter der schliessenden Klammer fort. Was danach kommt --
        // ablegen, vergleichen, urteilen -- steht in `verzeichne` und nicht hier: Es ist
        // dasselbe, was `merke` tut, und zwei Fassungen davon waeren zwei Gestalten
        // desselben Eintrags.
        try {
            tun();
        } catch (const std::domain_error& fehler) {
            verzeichne(welcher, was, zeile, kennzeichen, fehler.what());
            return;
        } catch (...) {
            std::fprintf(stderr,
                         "FEHLGESCHLAGEN Zeile %d: %s -- abgebrochen, aber nicht mit "
                         "std::domain_error; zu einem Wortlaut kommt die Probe so nicht\n",
                         zeile, was);
            ++fehlgeschlagen_;
            return;
        }

        std::fprintf(stderr,
                     "FEHLGESCHLAGEN Zeile %d: %s -- kein Abbruch.\n  erwartet war eine "
                     "Meldung mit: \"%s\"\n  angekommen ist:         (nichts, der Aufruf "
                     "kam durch)\n",
                     zeile, was, kennzeichen.empty() ? "(keins genannt)" : kennzeichen[0]);
        ++fehlgeschlagen_;
    }

    /// Legt eine Abbruchmeldung ab, die die Aufrufstelle **selbst** gefangen hat
    /// (Paket 0255).
    ///
    /// Der zweite Eingang neben `bricht_ab_mit`, und er fuehrt auf dieselbe Ablage. Es
    /// gibt ihn, weil es Stellen gibt, die ihren Abbruch nicht hergeben koennen: Sie
    /// pruefen den Wortlaut in **beiden** Richtungen -- welches Stueck ankommen muss und
    /// welches gerade *nicht* --, und die zweite Richtung kann das Verzeichnis nicht.
    /// Solche Stellen an `bricht_ab_mit` zu uebergeben hiesse, die negative Zusicherung
    /// aufzugeben; sie hier abzugeben kostet keine.
    ///
    /// Was sie gewinnen, sind die beiden Aussagen, die eine einzelne Stelle ueber sich
    /// selbst gar nicht treffen kann: dass ihr Riegel in diesem Lauf ueberhaupt gefeuert
    /// hat -- verschwindet die Aufrufstelle, faellt die Vollzaehligkeit auf -- und dass
    /// ihre Liste auf keine der fremden Meldungen passt.
    ///
    /// **Ein leerer Wortlaut ist ein Fehlschlag und keine leere Ablage.** Er hiesse, dass
    /// nichts angekommen ist; ein Eintrag daraus faerbte die Vollzaehligkeit dieses
    /// Riegels gruen, ohne dass eine Schranke gefeuert haette -- genau das Loch, gegen
    /// das das Verzeichnis steht.
    void merke(R welcher, const char* was, int zeile, Kennzeichen kennzeichen,
               const char* angekommen)
    {
        if (angekommen == nullptr || angekommen[0] == '\0') {
            std::fprintf(stderr,
                         "FEHLGESCHLAGEN Zeile %d: %s -- kein Wortlaut abzulegen; die "
                         "Stelle hat nichts gefangen, und ein leerer Eintrag machte die "
                         "Vollzaehligkeit dieses Riegels gruen\n",
                         zeile, was);
            ++fehlgeschlagen_;
            return;
        }
        verzeichne(welcher, was, zeile, kennzeichen, angekommen);
    }

    /// Wie viele Meldungen in diesem Lauf zu diesem Riegel angekommen sind.
    ///
    /// Der Zaehler waechst allein in `verzeichne`, also an einer angekommenen Meldung und
    /// gleichgueltig, ueber welchen der beiden Eingaenge sie kam. Eine Probe, die eine
    /// **genaue** Zahl je Riegel verlangt statt "mindestens eine", bekommt damit den
    /// Nachweis, dass keine Aufrufstelle stillschweigend verschwunden ist -- die
    /// Vollzaehligkeit unten sieht nur die letzte.
    [[nodiscard]] std::size_t anzahl_zu(R welcher) const
    {
        std::size_t gezaehlt = 0;
        for (std::size_t i = 0; i < anzahl_; ++i) {
            if (angekommene_[i].riegel == welcher) {
                ++gezaehlt;
            }
        }
        return gezaehlt;
    }

    /// Wie viele Meldungen insgesamt angekommen sind.
    [[nodiscard]] std::size_t anzahl() const { return anzahl_; }

    /// Die Auswertung. Sie laeuft **zuletzt** und nicht in `bricht_ab_mit`: Sie
    /// vergleicht jede Liste gegen jede Meldung, kann also erst anfangen, wenn alle
    /// Meldungen da sind. Stuende sie in der Vorlage, saehe die erste Stelle nur sich
    /// selbst und die letzte alles -- eine Zusicherung, deren Schaerfe von der
    /// Reihenfolge abhaengt, ist keine.
    ///
    /// Die Aussage in einem Satz: **Die Liste einer Stelle passt genau auf die Meldungen
    /// ihres eigenen Riegels.** Zwei Haelften, und beide werden gebraucht.
    ///
    ///   *Passt auf keine fremde.* Das ist die Haelfte, um die es geht. Verkuerzt jemand
    ///   eine Liste auf ein Allerweltsstueck, passt sie sofort auch auf fremde Meldungen
    ///   und die Zeile wird rot, ohne dass an der Quelle etwas geaendert wurde.
    ///
    ///   *Passt auf jede eigene.* Ohne sie gaebe es einen bequemen Ausweg: Wer die
    ///   verkuerzte Liste behalten will, erklaert ihren Riegel kurzerhand zu dem, mit dem
    ///   sie kollidiert -- und die erste Haelfte schwiege, weil nur noch fremde Paare
    ///   geprueft werden. Diese Haelfte macht daraus einen Tausch statt eines Auswegs.
    ///
    /// Der naheliegende Riegel waere "mindestens zwei Textstuecke je Liste" gewesen. Er
    /// taugt nichts: Zwei nichtssagende Stuecke bestehen ihn.
    void auswerten()
    {
        // Zuerst die Vollzaehligkeit. Ohne sie hoehlt jede geloeschte Abbruchstelle die
        // Zusicherung still aus -- eine Meldung, die nicht ankommt, widerspricht keiner
        // Liste, und die Probe bliebe gruen und saegte weniger.
        for (const R welcher : alle_riegel_) {
            bool gesehen = false;
            for (std::size_t i = 0; i < anzahl_ && !gesehen; ++i) {
                gesehen = angekommene_[i].riegel == welcher;
            }
            if (!gesehen) {
                std::fprintf(stderr,
                             "FEHLGESCHLAGEN (%s): zum Riegel \"%s\" ist in diesem Lauf "
                             "keine Meldung angekommen; seine Eindeutigkeit ist "
                             "ungeprueft\n",
                             wessen_, namensgeber_(welcher));
                ++fehlgeschlagen_;
            }
        }

        std::size_t fremde_paare = 0;
        std::size_t eigene_paare = 0;
        std::size_t verletzungen = 0;

        for (std::size_t i = 0; i < anzahl_; ++i) {
            const Angekommen<R>& liste = angekommene_[i];
            for (std::size_t j = 0; j < anzahl_; ++j) {
                if (i == j) {
                    continue;
                }
                const Angekommen<R>& andere = angekommene_[j];
                const bool derselbe_riegel = liste.riegel == andere.riegel;
                const bool passt = liste_passt(liste, andere.meldung.data());

                if (derselbe_riegel) {
                    ++eigene_paare;
                    if (!passt) {
                        std::fprintf(
                            stderr,
                            "FEHLGESCHLAGEN Zeile %d: %s -- diese Stelle und \"%s\" "
                            "nennen beide den Riegel \"%s\", aber die Liste der ersten "
                            "passt nicht auf die Meldung der zweiten. Entweder sind es "
                            "zwei Riegel und nicht einer, oder die Liste greift zu eng."
                            "\n  fremde Meldung: \"%s\"\n",
                            liste.zeile, liste.was, andere.was,
                            namensgeber_(liste.riegel), andere.meldung.data());
                        ++fehlgeschlagen_;
                        ++verletzungen;
                    }
                    continue;
                }

                ++fremde_paare;
                if (passt) {
                    std::fprintf(stderr,
                                 "FEHLGESCHLAGEN Zeile %d: %s -- die Kennzeichenliste "
                                 "dieser Stelle kennzeichnet nicht: Sie passt auch auf die "
                                 "Meldung des Riegels \"%s\" (Stelle \"%s\").\n  fremde "
                                 "Meldung: \"%s\"\n",
                                 liste.zeile, liste.was, namensgeber_(andere.riegel),
                                 andere.was, andere.meldung.data());
                    ++fehlgeschlagen_;
                    ++verletzungen;
                }
            }
        }

        // Und die Riegel ohne Zustand. Von der Vollzaehligkeit oben sind sie ausgenommen,
        // indem sie in der ersten Kategorie gar nicht stehen; was von der Eindeutigkeit
        // bleibt, ist die erste Haelfte -- die Liste passt auf keine fremde Meldung.
        std::size_t ohne_zustand_paare = 0;
        for (const OhneZustand<O>& eintrag : ohne_zustand_) {
            // Ohne Kennzeichen passte die Liste auf jeden Text. Bei einem Riegel mit
            // Zustand faengt `bricht_ab_mit` das ab; hier gibt es keine Aufrufstelle,
            // die es taete.
            if (eintrag.kennzeichen.empty()) {
                std::fprintf(stderr,
                             "FEHLGESCHLAGEN (%s): der Riegel ohne Zustand \"%s\" nennt "
                             "kein Kennzeichen; seine Liste passte damit auf jede "
                             "Meldung\n",
                             wessen_, eintrag.name);
                ++fehlgeschlagen_;
                ++verletzungen;
                continue;
            }

            std::size_t getroffene = 0;
            for (std::size_t i = 0; i < anzahl_; ++i) {
                ++ohne_zustand_paare;
                if (!alle_stuecke_in(eintrag.kennzeichen, angekommene_[i].meldung.data())) {
                    continue;
                }
                ++getroffene;
                std::fprintf(stderr,
                             "FEHLGESCHLAGEN (%s): die Kennzeichenliste des Riegels ohne "
                             "Zustand \"%s\" kennzeichnet nicht: Sie passt auch auf die "
                             "Meldung des Riegels \"%s\" (Stelle \"%s\").\n  fremde "
                             "Meldung: \"%s\"\n",
                             wessen_, eintrag.name,
                             namensgeber_(angekommene_[i].riegel), angekommene_[i].was,
                             angekommene_[i].meldung.data());
                ++fehlgeschlagen_;
                ++verletzungen;
            }

            // Beim Namen genannt, in jedem Lauf: Ein Verzeichnis, das niemand ausdruckt,
            // ist von einem leeren nicht zu unterscheiden. Gedruckt wird die getroffene
            // Zahl und nicht die Behauptung, es sei keine -- ein Satz, den derselbe Lauf
            // auf der Fehlerausgabe widerlegt, ist schlimmer als keiner.
            std::printf("  Riegel ohne Zustand (%s) \"%s\": %zu Kennzeichen, passend auf "
                        "%zu der %zu angekommenen Meldungen -- unerreichbar, weil %s\n",
                        wessen_, eintrag.name, eintrag.kennzeichen.size(), getroffene,
                        anzahl_, eintrag.warum);
        }

        // Drei Zaehlungen, die nicht null sein duerfen. Eine Schleife ueber null Paare
        // laeuft gruen durch und misst nichts; das ist genau der Zustand, den der Apparat
        // abschafft, und er darf nicht durch eine spaetere Umstellung zurueckkommen.
        verlange(fremde_paare > 0, "fremde_paare > 0");
        verlange(eigene_paare > 0, "eigene_paare > 0");
        verlange(ohne_zustand_paare > 0, "ohne_zustand_paare > 0");
        verlange(verletzungen == 0, "verletzungen == 0");

        std::printf("  Kennzeichen (%s): %zu Meldungen aus %zu Riegeln mit Zustand, dazu "
                    "%zu Riegel ohne Zustand; %zu fremde, %zu eigene und %zu Paare ohne "
                    "Zustand geprueft, %zu Verletzung(en)\n",
                    wessen_, anzahl_, alle_riegel_.size(), ohne_zustand_.size(),
                    fremde_paare, eigene_paare, ohne_zustand_paare, verletzungen);
    }

private:
    /// Schreibt `quelle` nach `ziel` ab. Rueckgabe `false` heisst **abgeschnitten** --
    /// eine halbe Meldung koennte ein fremdes Kennzeichen verlieren und die Zusicherung
    /// still schwaechen, also ist das ein Fehlschlag und keine Nebensache.
    static bool schreibe_ab(std::array<char, MELDUNG_ZEICHEN>& ziel, const char* quelle)
    {
        std::size_t i = 0;
        while (quelle[i] != '\0' && i + 1 < ziel.size()) {
            ziel[i] = quelle[i];
            ++i;
        }
        ziel[i] = '\0';
        return quelle[i] == '\0';
    }

    /// Dieselbe Frage wie `alle_stuecke_in` fuer eine angekommene Meldung, deren Liste im
    /// Feld statt in einer Spanne liegt. Beide Verzeichnisse fragen damit **wortgleich**
    /// dasselbe -- zwei Fassungen der Bedingung waeren zwei Stellen, an denen sie
    /// auseinanderlaufen kann.
    static bool liste_passt(const Angekommen<R>& eintrag, const char* text)
    {
        return alle_stuecke_in(Kennzeichen{eintrag.kennzeichen.data(), eintrag.anzahl},
                               text);
    }

    void verlange(bool bedingung, const char* text)
    {
        if (!bedingung) {
            std::fprintf(stderr, "FEHLGESCHLAGEN (%s): %s\n", wessen_, text);
            ++fehlgeschlagen_;
        }
    }

    /// Die eine Ablage, auf die **beide** Eingaenge fuehren -- `bricht_ab_mit` aus seinem
    /// Fangblock heraus, `merke` von einer Stelle, die selbst gefangen hat.
    ///
    /// Sie steht hier und nicht zweimal, weil sonst zwei Wege in dasselbe Buch zwei
    /// Gestalten des Eintrags waeren: Was abgelegt wird, wogegen es verglichen wird und
    /// was im Fehlerfall gedruckt wird, muss von der Herkunft des Wortlauts unabhaengig
    /// sein -- sonst haengt die Schaerfe der Zusicherung daran, welchen Eingang eine
    /// Stelle zufaellig benutzt.
    ///
    /// Abgeschrieben wird **vor** jedem Urteil: Auch eine Stelle, die gleich als
    /// "falscher Riegel" rot wird, liefert eine Meldung, gegen die die anderen Listen
    /// gehalten werden. Die Zusicherung soll nicht davon abhaengen, ob der Rest dieser
    /// Stelle gerade in Ordnung ist.
    void verzeichne(R welcher, const char* was, int zeile, Kennzeichen kennzeichen,
                    const char* angekommen)
    {
        // Ohne Kennzeichen prueft die Stelle wieder nur, *dass* geworfen wurde -- also
        // genau das, was der Apparat abschafft. Er faellt lieber auf, als still zu
        // verwaessern. Gemeldet und trotzdem abgelegt: Die Meldung wird als fremde
        // weiterhin gebraucht.
        if (kennzeichen.empty()) {
            std::fprintf(stderr,
                         "FEHLGESCHLAGEN Zeile %d: %s -- kein Kennzeichen genannt; so "
                         "prueft die Stelle nur, dass ueberhaupt geworfen wurde\n",
                         zeile, was);
            ++fehlgeschlagen_;
        }

        merke_meldung(welcher, was, zeile, kennzeichen, angekommen);

        const char* fehlendes = nullptr;
        for (const char* const stueck : kennzeichen) {
            if (!enthaelt(angekommen, stueck)) {
                fehlendes = stueck;
                break;
            }
        }
        if (fehlendes == nullptr) {
            std::printf("  Abbruch wie erwartet (%s): %s\n", was, angekommen);
            return;
        }
        std::fprintf(stderr,
                     "FEHLGESCHLAGEN Zeile %d: %s -- es hat abgebrochen, aber der "
                     "falsche Riegel.\n  erwartetes Textstueck: \"%s\"\n  angekommene "
                     "Meldung:   \"%s\"\n",
                     zeile, was, fehlendes, angekommen);
        ++fehlgeschlagen_;
    }

    /// Legt eine angekommene Meldung fuer die Eindeutigkeitspruefung ab.
    void merke_meldung(R welcher, const char* was, int zeile, Kennzeichen kennzeichen,
                       const char* angekommen)
    {
        if (anzahl_ >= angekommene_.size()) {
            std::fprintf(stderr,
                         "FEHLGESCHLAGEN Zeile %d: %s -- mehr als %zu Abbruchmeldungen; "
                         "die Eindeutigkeitspruefung saehe die uebrigen nicht\n",
                         zeile, was, angekommene_.size());
            ++fehlgeschlagen_;
            return;
        }
        if (kennzeichen.size() > KENNZEICHEN_MAX) {
            std::fprintf(stderr,
                         "FEHLGESCHLAGEN Zeile %d: %s -- %zu Kennzeichen, abgelegt werden "
                         "hoechstens %zu\n",
                         zeile, was, kennzeichen.size(), KENNZEICHEN_MAX);
            ++fehlgeschlagen_;
            return;
        }

        Angekommen<R>& eintrag = angekommene_[anzahl_];
        eintrag.riegel = welcher;
        eintrag.was = was;
        eintrag.zeile = zeile;
        eintrag.anzahl = kennzeichen.size();
        for (std::size_t k = 0; k < kennzeichen.size(); ++k) {
            eintrag.kennzeichen[k] = kennzeichen[k];
        }
        if (!schreibe_ab(eintrag.meldung, angekommen)) {
            std::fprintf(stderr,
                         "FEHLGESCHLAGEN Zeile %d: %s -- die Meldung ist laenger als %zu "
                         "Zeichen und wurde abgeschnitten\n",
                         zeile, was, MELDUNG_ZEICHEN - 1);
            ++fehlgeschlagen_;
        }
        ++anzahl_;
    }

    const char*                             wessen_;
    int&                                    fehlgeschlagen_;
    std::span<const R>                      alle_riegel_;
    Namensgeber                             namensgeber_;
    std::span<const OhneZustand<O>>         ohne_zustand_;
    std::array<Angekommen<R>, MELDUNGEN_MAX> angekommene_{};
    std::size_t                             anzahl_ = 0;
};

}  // namespace probe::kennzeichen
