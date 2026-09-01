import java.math.BigInteger;

/**
 * Stack-Messung fuer 0016: deterministischer Festkomma-Weltschritt in Java.
 *
 * Vorgabe: messung-stack/AUFGABE.md. Ganzzahlarithmetik durchgehend, kein
 * Komma-Typ, keine Fremdbibliothek, keine Eingabe, keine Argumente.
 *
 * Uebersetzen und laufen lassen:
 *   javac -d <zielverzeichnis> Schritt.java && java -cp <zielverzeichnis> Schritt
 */
public final class Schritt {

    private static final int BREITE = 64;
    private static final long SCHRITTE = 1_000_000L;
    private static final long UNTERGRENZE = 0L;
    private static final long OBERGRENZE = 1_000_000_000_000L;

    private Schritt() {
    }

    public static void main(String[] args) {
        long[] z = new long[BREITE];
        for (int i = 0; i < BREITE; i++) {
            z[i] = 1_000_000L + (long) i * 37L;
        }

        long beginn = System.nanoTime();
        for (long s = 0L; s < SCHRITTE; s++) {
            weltschritt(z);
        }
        long dauer = System.nanoTime() - beginn;

        // Ueberlaufumbruch ist in Java die Vorgabe fuer long, nichts weiter zu tun.
        long pruefsumme = 0L;
        for (int i = 0; i < BREITE; i++) {
            pruefsumme += z[i] * (long) (i + 1);
        }

        System.out.println("pruefsumme=" + pruefsumme);
        System.out.println("nanosekunden_je_schritt=" + (dauer / SCHRITTE));
        System.out.println("zustand0=" + z[0]);
    }

    /**
     * Ein Weltschritt, i aufsteigend, in derselben Tabelle. Ein spaeteres i sieht
     * also bereits fortgeschriebene Nachbarn -- das ist so gewollt.
     */
    private static void weltschritt(long[] z) {
        for (int i = 0; i < BREITE; i++) {
            long alt = z[i];
            long nachbar = z[(i + 17) % BREITE];
            long roh = malGeteilt(alt, 10_000L + Math.floorMod(nachbar, 977L), 10_000L);
            z[i] = klemme(roh + (nachbar / 1024L) - (alt / 4096L), UNTERGRENZE, OBERGRENZE);
        }
    }

    /**
     * a * b / c ohne Ueberlauf im Zwischenergebnis, gerundet auf halbe Betraege
     * von null weg.
     *
     * Schneller Weg: passt das 128-Bit-Produkt in 64 Bit -- erkennbar daran, dass
     * das obere Wort nur die Vorzeichenerweiterung des unteren ist --, rechnet die
     * Maschine direkt. Sonst uebernimmt BigInteger.
     */
    private static long malGeteilt(long a, long b, long c) {
        long tief = a * b;
        long hoch = Math.multiplyHigh(a, b);
        if (hoch != (tief >> 63)) {
            return malGeteiltGross(a, b, c);
        }

        long q = tief / c;   // schneidet gegen null ab
        long rest = tief % c;
        if (rest == 0L) {
            return q;
        }
        long betragRest = Math.abs(rest);
        long betragC = Math.abs(c);
        // |rest| * 2 >= |c|, ohne die Verdopplung ueberlaufen zu lassen.
        if (betragRest >= betragC - betragRest) {
            q += ((tief < 0L) != (c < 0L)) ? -1L : 1L;
        }
        return q;
    }

    /** Derselbe Vertrag wie malGeteilt, nur ohne Breitenbegrenzung. */
    private static long malGeteiltGross(long a, long b, long c) {
        BigInteger produkt = BigInteger.valueOf(a).multiply(BigInteger.valueOf(b));
        BigInteger nenner = BigInteger.valueOf(c);
        BigInteger[] geteilt = produkt.divideAndRemainder(nenner);
        BigInteger q = geteilt[0];
        BigInteger rest = geteilt[1];
        if (rest.signum() != 0
                && rest.abs().shiftLeft(1).compareTo(nenner.abs()) >= 0) {
            q = q.add(BigInteger.valueOf(produkt.signum() == nenner.signum() ? 1L : -1L));
        }
        return q.longValue();
    }

    private static long klemme(long x, long unten, long oben) {
        if (x < unten) {
            return unten;
        }
        if (x > oben) {
            return oben;
        }
        return x;
    }
}
