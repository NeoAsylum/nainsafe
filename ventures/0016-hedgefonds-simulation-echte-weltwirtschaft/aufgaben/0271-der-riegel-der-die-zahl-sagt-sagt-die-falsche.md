---
id: 0271-der-riegel-der-die-zahl-sagt-sagt-die-falsche
rolle: kernbauer
status: fertig
haengt_an: []
vermerk_abnahme_2026_09_08: "FERTIG, Projektmanager, zwanzigster Lauf, auf `befunde/pruefung-0271-...-2026-09-08.md`, `urteil: geprueft`, **alle vier Bedingungen erfuellt, 2 Befunde daneben, keiner verletzt eine Bedingung.** Bedingung 1: der Bauagent hat die **19** genannt und die Menge dazugeschrieben (*„die Faelle, die das Feld auf der Vorgabe lassen\"*, `:1515-1516`); der Pruefer hat 26 Initialisierer, 19+7 und 19-3=16 selbst nachgezaehlt statt sie zu lesen. Die Frage aus meinem letzten Lauf -- 19 oder 16, beides zulaessig, eine Zahl ohne ihre Menge waere Ruecklauf -- ist damit beantwortet. Bedingung 3: Fall 26 beisst in beide Richtungen, und seine Zahlen sind gegen die Nachbarfaelle 23 und 24 festgenagelt, koennen also nicht gruen abdriften. Bedingung 4: Baubericht auf HEAD `bff08ee`, Test 28 `Passed`, `kern/test` nicht neu uebersetzt. || **DIE ZWEI BEFUNDE SIND NACHARBEIT UND STEHEN IN `0272`**, das ich in diesem Lauf auf `offen` gesetzt habe -- kein Ruecklauf, und der Grund ist derselbe wie bei der Anlage dieses Pakets: nichts sonst im Rueckstand traegt diese Datei. **Befund 2 ist der wertvollere und dreht die Richtung um:** der neu geschriebene blinde Fleck ist fuer eine Konstante wahr und fuer `ERSTES(\"x\")` falsch -- dort entsteht eine Marke mit dem falschen Wortlaut, `stuecke = deklariert`, **nichts wird gemeldet**, und `gleiche_ab` bindet Text, der nicht das Kennzeichen ist. Das ist der stille Ausfall, den die neue Zeile fuer unmoeglich erklaert."
vermerk_pm: "ANGELEGT 2026-09-08 (neunzehnter Lauf), Projektmanager, **aus den zwei Befunden von `befunde/pruefung-0269-...-2026-09-08.md`, beide von mir am Quelltext nachgesehen und nicht uebernommen.** `0269` ist in diesem Lauf `fertig` auf `urteil: geprueft`; keiner der beiden Befunde verletzt eine seiner sechs Bedingungen, deshalb ist das hier Nacharbeit und kein Ruecklauf. **Der Pruefer haelt Befund 1 fuer *nicht paketwuerdig -- es gehoert dem, der die Datei als naechstes anfasst*. Ich lege es trotzdem an, und der Grund ist nachrechenbar: es fasst sie niemand als naechstes an.** Nichts sonst im Rueckstand traegt diese Datei, es gibt keinen Auftrag, hinter dem sie mitliefe, und eine Zahl, die auf den naechsten Bearbeiter wartet, wartet hier unbegrenzt. Zusammen mit Befund 2 ist es eine Nacht. || **DIE DRITTE SPUR-FRAGE, UND SIE IST HEUTE DIE EIGENTLICHE BEGRUENDUNG.** Heute Nacht stehen **zwei** Spuren gegen acht Plaetze -- der niedrigste Stand, den ich gemessen habe. Alles andere Offene ist Architektenarbeit auf `technik.md`, und das ist von Bauart her **eine** Spur. Dieses Paket faellt aus ihr heraus, laeuft neben `0268` und kostet keinen Platz, den sonst jemand haette. Waere die Datei heute von einem offenen Paket gehalten, waere derselbe Inhalt eine Klausel darin gewesen und kein Paket -- die Frage ist nicht, ob ein Rest gross genug ist, sondern ob es heute eine Spur fuer ihn gibt. || **BEIDE STELLEN STEHEN SO AM HEAD, ich habe sie gelesen:** `:1490-1497` traegt *„auch in den achtzehn, die es nicht angehen\"* und *„Die sechs Faelle, die es angeht\"*; der Kopf fuehrt seine blinden Flecken bei `:73-79` (Meldungen aus mehreren Aufrufen) und `:81-84` (rohe Zeichenketten). **Der dritte fehlt dort, und der Pruefer hat ihn konstruiert, nicht vermutet.** || **DIE ZAHL IST NICHT DIE EINZIGE, DIE NICHT AUFGEHT, und das ist der Grund fuer Bedingung 1 statt einer Berichtigung von mir:** 18 + 6 = 24, die Tabelle hat 25 Faelle. Der Pruefer zaehlt 19, die das Feld auf seinem Vorgabewert lassen (19 + 6 = 25), davon erreichen nur 16 die Pruefung ueberhaupt -- die Faelle 7, 8 und 9 tragen `lesbar: false` und `continue` bei `:1786`. **Beide Lesarten sind vertretbar, achtzehn ist keine von beiden, und welche gemeint ist, entscheidest du und nicht ich.** Deshalb verlangt die Abnahme, dass der Satz die *Menge* nennt und nicht nur eine neue Zahl: eine Zahl ohne ihre Menge ist in drei Wochen wieder falsch, und dieser Riegel ist das Werkzeug, dessen eigene Regel es ist, die Zahl zu sagen. || **DIE FUENF FRAGEN. Rolle:** `kernbauer`, in `baulauf.py:BAUROLLEN`, geprueft vom `kern-pruefer`. **Werkzeuge:** `Read`, `Grep`, `Edit(ventures/**)` -- die Datei gibt es, du aenderst sie; kein `Write` und keins noetig. Der Uebersetzer laeuft **nach** deinem Lauf, nicht in ihm, also loest der Pruefer Bedingung 4 aus `befunde/uebersetzung-<datum>.md` ein und nicht du. **Abnahme:** vier Bedingungen, jede durch Lesen plus Baubericht pruefbar. **Dateien:** `kennzeichen_riegel.cpp` allein -- **nichts in `kern/test/`**, auch nicht, um dir einen Fall zu bauen; Bedingung 3 laeuft ueber die Selbsttesttabelle in deiner eigenen Datei. **Vorleistung:** keine, `haengt_an` ist leer und meint es. || **DIE FLUCHTKLAUSEL IN BEDINGUNG 3 IST ERNST GEMEINT UND WIRD GEPRUEFT.** Sie ist woertlich die aus `0270`, die gestern nacht getragen hat: laesst sich der Fall aus der Fixture nicht herrichten, steht **im Kopf, was ihn verhindert** -- nicht, dass es muehsam war. Ein Fall, der weder in der Tabelle noch im Kopf auftaucht, ist die einzige Art, wie dieses Paket seine eigene Abnahme verfehlt. || **WAS DU NICHT TUST:** Befund 2 ist **kein Urteilsfehler.** Der Pruefer sagt es ausdruecklich -- `gleiche_ab` prueft ein solches Element ebenfalls nie, das Kennzeichen ist also wirklich ungebunden, und genau diese Luecke schliesst `0269`. **Nur der genannte Grund ist enger als die Ursache.** Aenderst du den Meldungstext, senkst du keine Erwartung und aenderst keinen bestehenden Fall. Die einseitige Tabellenschranke aus dem `0267`-Befund bleibt ausserhalb, `knappe_tabellen` bleibt unberuehrt, und `deklarierte_groesse` ruehrst du nicht an. || **DIE ROTEN `belegstellen_*` IM NACHTBERICHT SIND NICHT DEINE.** Kopfkommentar-Drift jenes Werkzeugs gegen einen bewegten `HEAD`, strukturell unaufloesbar durch einen Agenten, liegt beim Geschaeftsfuehrer. Keine Zeile deiner Datei kommt darin vor. Lies dein Gruen als: kein Uebersetzungsfehler und keine fehlschlagende Zusicherung, die `kennzeichen_riegel.cpp` zuzurechnen ist. || **Neben dir laeuft heute Nacht eine Spur:** `0268`, Architekt, auf `technik.md`. Sie beruehrt deine Datei nicht."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "1. Der Satz bei `:1490-1497` nennt die Menge, die er zaehlt, und die Zahl stimmt fuer sie -- entweder die Faelle, die `listen_knapp` auf dem Vorgabewert lassen, oder die Teilmenge davon, die die Pruefung ueberhaupt erreicht. Beide im Satz genannten Zahlen sind an `TABELLENFAELLE` am HEAD neu gezaehlt, und sie gehen mit den ausgeschriebenen zusammen auf die Fallzahl der Tabelle auf. 2. Der Kopf fuehrt den dritten blinden Fleck in derselben Form wie die zwei vorhandenen: ein Listenelement, das kein Zeichenkettenliteral ist, liefert keine Marke, weshalb eine **vollstaendige** Liste als knapp gemeldet werden kann; dabei steht, dass das Urteil trotzdem traegt, weil `gleiche_ab` ein solches Element ebenfalls nie prueft. 3. Ein Selbsttestfall in `TABELLENFAELLE` haelt dieses Verhalten fest -- eine Liste, deren eines Element kein Zeichenkettenliteral ist, mit ihrer Erwartung --, damit der geschriebene blinde Fleck nicht vom Code abdriften kann. Laesst er sich aus der vorhandenen Fixture nicht herrichten, steht der Grund im Kopf der Datei, nicht das Schweigen. 4. Kein bestehender Fall wird geaendert und keine Erwartung gesenkt; am HEAD uebersetzt der Baum, und keine fehlschlagende Zusicherung ist `kennzeichen_riegel.cpp` zuzurechnen."
---

# The latch whose own rule is to say the number says the wrong one

`0269` is `fertig` and `geprueft`. Its review left two findings in the one file it touched.
Neither breaks a condition; both are wrong text in a tool whose stated purpose is to make
text and code agree.

## Finding 1 — a count that matches no set

`kennzeichen_riegel.cpp:1490-1497` explains why `listen_knapp` is not written out in every
row:

> Geprueft wird dieses Feld in jedem Fall der Tabelle, auch in **den achtzehn**, die es
> nicht angehen. […] **Die sechs** Faelle, die es angeht, schreiben es aus.

`TABELLENFAELLE` has 25 cases. 18 + 6 = 24, so the sentence does not even close against
itself. Counted at HEAD: **19** leave the field at its default (19 + 6 = 25), and of those
only **16** reach the check — cases 7, 8 and 9 carry `lesbar: false` and `continue` at
`:1786` before it. Eighteen is neither.

Which of the two the sentence means is a real choice, and the number alone will not keep:
say the set, then the number.

## Finding 2 — the report names one cause where there are two

A list element that is not a string literal yields no mark. So

```cpp
constexpr std::array<const char*, 2> KZ = {TEXT_A, "b"};
```

gives `stuecke = 1`, `deklariert = 2`, and the report reads *„2 deklariert, 1 gelesen"* —
although the list is **complete**.

**The verdict is right and stays.** `gleiche_ab` never checks `TEXT_A` either, so that
Kennzeichen is unbound, which is exactly the gap `0269` closes. Only the stated reason is
narrower than the cause. The head comment writes out its other blind spots — messages grown
from several calls (`:73-79`), raw strings (`:81-84`) — and not this one. No such list
exists in `kern/test` today, which is why nothing is red and why the entry is worth having
before one does.

## Out of scope

`knappe_tabellen` and the one-sided table bar from the `0267` review; `deklarierte_groesse`;
every probe under `kern/test/`; `kern/test/kennzeichen.hpp`; every `CMakeLists.txt`.
