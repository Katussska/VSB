package cz.vsb.fei.java2.testhashcode;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Bank {
    String name;

    private List<Account> accounts = new ArrayList<>();

    private List<PropertyChangeListener> propertyChangeListeners = new ArrayList<>();

    public Bank(String name) {
        this.name = name;
    }

    public void add(Account account) {
        accounts.add(account);
        firePropertyChanged();
    }

    public boolean add(PropertyChangeListener listener) {
        return propertyChangeListeners.add(listener);
    }

    public boolean remove(PropertyChangeListener listener) {
        return propertyChangeListeners.remove(listener);
    }

    private void firePropertyChanged() {
        PropertyChangeEvent evt = new PropertyChangeEvent(this, "accounts", Collections.emptyList(), accounts);
        for (PropertyChangeListener propertyChangeListener : propertyChangeListeners) {
            propertyChangeListener.propertyChange(evt);
        }
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Bank bank = (Bank) o;
        return name.equals(bank.name) && accounts.equals(bank.accounts) && propertyChangeListeners.equals(bank.propertyChangeListeners);
    }

    @Override
    public int hashCode() {
        int result = name.hashCode();
        result = 31 * result + accounts.hashCode();
        result = 31 * result + propertyChangeListeners.hashCode();
        return result;
    }

    public List<Account> getAccounts() {
        return accounts;
    }

}
