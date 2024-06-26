public class Negate {
    public int negateInt(int value) {
        return -value;
    }

    public long negateLong(long value) {
        return -value;
    }

    public float negateFloat(float value) {
        return -value;
    }

    public double negateDouble(double value) {
        return -value;
    }

    public static void main(String[] args) {
        Negate test = new Negate();

        System.out.println("Negate int 5: " + test.negateInt(5));
        System.out.println("Negate long 10L: " + test.negateLong(10L));
        System.out.println("Negate float 5.5f: " + test.negateFloat(5.5f));
        System.out.println("Negate double 10.5: " + test.negateDouble(10.5));
    }
}
