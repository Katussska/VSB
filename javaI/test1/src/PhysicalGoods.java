abstract public class PhysicalGoods extends Goods {
    private int stock;

    PhysicalGoods(String n, double p, int s) {
        super(n, p);
        stock = s;
    }

    @Override
    int getStock() {
        return stock;
    }
}
