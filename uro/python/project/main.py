import tkinter as tk
from tkinter import ttk


def add_example_records():
    # Add example records to the display
    records = [
        ("Prijem", "10.03.2024", "Vyplata", "20000Kc"),
        ("Vydaj", "08.03.2024", "Nakup", "-1500Kc"),
        ("Vydaj", "05.03.2024", "Obed", "-180Kc")
    ]

    for i, record in enumerate(records):
        for j, value in enumerate(record):
            ttk.Label(root, text=value).grid(row=i + 11, column=j)


class BudgetTrackerApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Budget Tracker")

        # Labels and Entry Widgets
        ttk.Label(root, text="Poznamka").grid(row=0, column=0)
        self.note_entry = ttk.Entry(root)
        self.note_entry.grid(row=0, column=1)

        ttk.Label(root, text="Castka").grid(row=2, column=0)
        self.amount_entry = ttk.Entry(root)
        self.amount_entry.grid(row=2, column=1)

        # Date Entry Fields
        ttk.Label(root, text="Den").grid(row=4, column=0)
        self.day_entry = ttk.Entry(root)
        self.day_entry.grid(row=4, column=1)

        ttk.Label(root, text="Mesic").grid(row=5, column=0)
        self.month_entry = ttk.Entry(root)
        self.month_entry.grid(row=5, column=1)

        ttk.Label(root, text="Rok").grid(row=6, column=0)
        self.year_entry = ttk.Entry(root)
        self.year_entry.grid(row=6, column=1)

        # Radio Buttons
        self.transaction_type = tk.StringVar()
        ttk.Radiobutton(root, text="Prijem", variable=self.transaction_type, value="Prijem").grid(row=3, column=0)
        ttk.Radiobutton(root, text="Vydaj", variable=self.transaction_type, value="Vydaj").grid(row=3, column=1)

        # Add Button
        ttk.Button(root, text="Pridat", command=self.add_transaction).grid(row=7, column=0, columnspan=2)

        # Filter Section
        ttk.Label(root, text="od: Kc").grid(row=8, column=0)
        self.filter_from_entry = ttk.Entry(root)
        self.filter_from_entry.grid(row=8, column=1)

        ttk.Label(root, text="do: Kc").grid(row=8, column=2)
        self.filter_to_entry = ttk.Entry(root)
        self.filter_to_entry.grid(row=8, column=3)

        ttk.Radiobutton(root, text="Prijem", variable=self.transaction_type, value="Prijem").grid(row=9, column=0)
        ttk.Radiobutton(root, text="Vydaj", variable=self.transaction_type, value="Vydaj").grid(row=9, column=1)

        ttk.Button(root, text="Filter", command=self.apply_filter).grid(row=9, column=2, columnspan=2)

        # Table-like Display
        ttk.Label(root, text="P/V").grid(row=10, column=0)
        ttk.Label(root, text="Datum").grid(row=10, column=1)
        ttk.Label(root, text="Poznamka").grid(row=10, column=2)
        ttk.Label(root, text="Castka").grid(row=10, column=3)

        # Example Records
        add_example_records()

    def add_transaction(self):
        """
        Přidá novou transakci na základě zadaných údajů.
        """
        note = self.note_entry.get()
        text = self.text_entry.get()
        amount = self.amount_entry.get()
        transaction_type = self.transaction_type.get()
        day = self.day_entry.get()
        month = self.month_entry.get()
        year = self.year_entry.get()

        # Zde implementujte logiku pro přidání transakce do vašeho datového úložiště (např. seznamu).

        # Příklad: Přidání transakce do seznamu
        new_transaction = {
            "P/V": transaction_type,
            "Datum": f"{day}.{month}.{year}",
            "Poznamka": note,
            "Castka": amount
        }
        # Přidejte new_transaction do vašeho datového úložiště (seznamu, databáze atd.)

        # Aktualizujte zobrazení tabulky
        self.add_example_records()

    def apply_filter(self):
        """
        Aplikuje filtr na základě zadaných kritérií.
        """
        filter_from = self.filter_from_entry.get()
        filter_to = self.filter_to_entry.get()
        transaction_type = self.transaction_type.get()

        # Zde implementujte logiku pro filtrování transakcí podle zadaných kritérií.

        # Příklad: Filtrování transakcí podle typu (Prijem/Vydaj)
        filtered_transactions = []
        for transaction in self.all_transactions:
            if transaction["P/V"] == transaction_type:
                filtered_transactions.append(transaction)

        # Aktualizujte zobrazení tabulky s filtrovanými transakcemi
        self.display_filtered_records(filtered_transactions)

    def display_filtered_records(self, filtered_transactions):
        """
        Zobrazí filtrované transakce v tabulce.
        """
        # Vymažte stávající záznamy v tabulce
        # ...

        # Přidejte filtrované transakce do tabulky
        for i, record in enumerate(filtered_transactions):
            for j, value in enumerate(record.values()):
                ttk.Label(root, text=value).grid(row=i + 11, column=j)


if __name__ == "__main__":
    root = tk.Tk()
    app = BudgetTrackerApp(root)
    root.mainloop()
