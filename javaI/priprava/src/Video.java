public class Video extends File implements IDuration {
    private int duration;
    private int height;
    private int width;

    Video(String n, int d, int h, int w) {
        super(n);
        duration = d;
        height = h;
        width = w;
    }

    @Override
    public String getInfo() {
        return "Video | " + getName() + " | " + height + " x " + width + " | " + getDuration();
    }

    @Override
    public int getDuration() {
        return duration;
    }
}
