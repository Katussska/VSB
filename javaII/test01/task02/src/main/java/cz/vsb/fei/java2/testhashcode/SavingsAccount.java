package cz.vsb.fei.java2.testhashcode;

public class SavingsAccount extends Account {
    private int savings;

    public SavingsAccount(Client client, int savings) {
        super(client);
        this.savings = savings;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;

        SavingsAccount that = (SavingsAccount) o;
        return savings == that.savings;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + savings;
        return result;
    }
}
