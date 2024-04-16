package cz.vsb.fei.java2.testhashcode;

public class CreditAccount extends Account {

    private int credit;

    private int balance;

    public CreditAccount(Client client, int credit, int balance) {
        super(client);
        this.credit = credit;
        this.balance = balance;
    }

    public int getCredit() {
        return this.credit;
    }

    public int getBalance() {
        return this.balance;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;

        CreditAccount that = (CreditAccount) o;
        return credit == that.credit && balance == that.balance;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + credit;
        result = 31 * result + balance;
        return result;
    }
}
