public abstract class File {
    private String name;


    File(String n) {
        this.name = n;
    }

    public abstract String getInfo();

    public String getName() {
        return name;
    }
}


