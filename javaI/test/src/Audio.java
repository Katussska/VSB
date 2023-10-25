public class Audio extends File implements IDuration {
    private final int duration;

    Audio(String n, int d) {
        super(n);
        duration = d;
    }

    @Override
    public String getInfo() {
        return "Audio | " + getName() + " | " + getDuration();
    }

    @Override
    public int getDuration() {
        return duration;
    }
}
