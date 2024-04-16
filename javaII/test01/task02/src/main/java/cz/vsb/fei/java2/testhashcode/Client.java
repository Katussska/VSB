package cz.vsb.fei.java2.testhashcode;

public class Client {
    private final String firstName;
    private final String secondName;

    public Client(String firstName, String secondName) {
        this.firstName = firstName;
        this.secondName = secondName;
    }

    public String firstName() {
        return this.firstName;
    }

    public String secondName() {
        return this.secondName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Client client = (Client) o;
        return firstName.equals(client.firstName) && secondName.equals(client.secondName);
    }

    @Override
    public int hashCode() {
        int result = firstName.hashCode();
        result = 31 * result + secondName.hashCode();
        return result;
    }
}

