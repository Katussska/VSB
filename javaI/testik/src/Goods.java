abstract public class Goods {
    private String name;
    private double price;


    Goods(String n, double p) {
        name = n;
        price = p;
    }

    String getDescription() {
        return name + " - " + price + " Kc";
    }

    abstract int getStock();
}
