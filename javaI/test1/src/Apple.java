public class Apple extends PhysicalGoods implements IExpiration {
    private int expiration;

    Apple(String n, double p, int s, int e) {
        super("jablko | " + n, p, s);
        expiration = e;
    }

    @Override
    public int getExpiration() {
        return expiration;
    }
}
