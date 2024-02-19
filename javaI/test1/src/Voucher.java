public class Voucher extends Goods implements IExpiration {
    private int expiration;

    Voucher(String n, double p, int e) {
        super("poukaz | " + n, p);
        expiration = e;
    }

    @Override
    int getStock() {
        return 1000000;
    }

    @Override
    public int getExpiration() {
        return expiration;
    }
}
