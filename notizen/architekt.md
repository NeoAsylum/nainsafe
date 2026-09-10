# Logbuch: architekt

Rotated by the runner on 2026-09-10 at 13071 characters (cap 12,000). Predecessor: `notizen/archiv/architekt-2026-09-10-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-10 — `0236`, Ruecklauf 1: der Satz war richtig und galt fuer die Haelfte der Faelle

**Der Fehler, den ich wiederholen koennte.** Ich habe eine Antwort auf den *Anlass* des
Pakets geschrieben und nicht auf ihren *Geltungsbereich*. Der Anlass war der Rundenrumpf,
also hiess der Satz „Rundengrenze" — und das ist genau die eine Klasse, die nach meiner
eigenen Entscheidung **keinen** `Zustand` mehr uebergibt. Die Klassen, fuer die er ab
sofort allein gilt (Jahrgangsbau, Pruefstand), standen elf Zeilen weiter in meinem eigenen
Absatz. **Regel fuer mich: wenn ein Satz eine Klasse ausschliesst, ist die Aufzaehlung der
verbleibenden Klassen kein Beiwerk, sondern der Satz.**

**Was gut lief:** Der Pruefer hat die Reparatur woertlich hingeschrieben, der
Projektmanager sie noch einmal zitiert statt verwiesen. Der Lauf war zwei Edits plus
Nachmessen. Wo ein Ruecklaufvermerk die Reparatur mitliefert, ist Nachdenken ueber den
Zuschnitt verschwendet — abarbeiten, nicht neu entwerfen.

**Zeilennummern in `technik.md` altern schneller als ihre Aussagen.** Fuenf `werte.hpp`-
Verweise standen gleichmaessig 3 zu tief; der gleichmaessige Versatz ist das Signal, dass
die *Datei* gewandert ist und die Behauptung haelt. Ungleichmaessiger Versatz waere das
Gegenteil. Nachgemessen kostet einen `Read`.

**Unsicher, fuer den Projektmanager und nicht fuer den Pruefer:** Der neue Satz nennt drei
Klassen vollstaendiger Zustaende. Vollstaendig ist er heute; er ist es nicht mehr, sobald
jemand eine vierte Quelle eines fertigen `Zustand` baut — ein geladener Spielstand aus G8
ist der naechste Kandidat (Abschnitt 22, Zeile 3 der Lesertabelle, „displays a saved or
finished game"). Ich habe ihn bewusst **nicht** als vierte Klasse aufgenommen, weil er in
keinem Aufruf einer T48-Groesse mit `const Zustand&` heute vorkommt und der Ruecklauf
ausdruecklich nicht verbreitert werden sollte. Faellt der Befund ein zweites Mal auf
dieselbe Aufzaehlung, liegt es an dieser Auslassung und dann gehoert das Kriterium
geaendert, nicht der Satz.

