package cz.vsb.fei.java2.testhashcode;

public abstract class Account {

    private final Client client;

    protected Account(Client client) {
        this.client = client;
    }

    public Client getClient() {
        return this.client;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Account account = (Account) o;
        return client.equals(account.client);
    }

    @Override
    public int hashCode() {
        return client.hashCode();
    }
}
