package cz.vsb.fei.java2.testhashcode;

public class CreditAccountMath extends CreditAccount {
    public CreditAccountMath(Client client, int credit, int balance) {
        super(client, credit, balance);
    }

    @Override
    public boolean equals(Object o) {
        return super.equals(o);
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }

    public boolean canPay(int amount) {
        return amount + getBalance() <= getCredit();
    }
}
