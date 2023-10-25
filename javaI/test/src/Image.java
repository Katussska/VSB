public class Image extends File {
    private final int height;
    private final int width;

    Image(String n, int h, int w) {
        super(n);
        height = h;
        width = w;
    }

    @Override
    public String getInfo() {
        return "Image | " + getName() + " | " + height + " x " + width;
    }
}
