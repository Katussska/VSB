import tkinter as tk
from tkinter import *
from tkinter.ttk import Treeview, Notebook, Combobox


class BudgetTrackerApp:
    def fce(self):
        self.la.configure(text=self.cmb.get())

    def render_date(self, string: page):
        date = Frame(self.page)
        date.pack(pady=5)

        # Days
        days_frame = Frame(date)
        days_frame.pack(side='left', padx=5)
        days_l = Label(days_frame, text='Day')
        days_l.pack()
        days = [str(i) for i in range(1, 32)]
        days_vals = tuple(days)
        days_box = Combobox(days_frame, values=days_vals, state="readonly", width=5)
        days_box.pack()

        # Months
        months_frame = Frame(date)
        months_frame.pack(side='left', padx=5)
        months_l = Label(months_frame, text='Month')
        months_l.pack()
        months = ["January", "February", "March", "April", "May", "June", "July",
                  "August", "September", "October", "November", "December"]
        months_vals = tuple(months)
        months_box = Combobox(months_frame, values=months_vals, state="readonly", width=10)
        months_box.pack()

        # Years
        years_frame = Frame(date)
        years_frame.pack(side='left', padx=5)
        years_l = Label(years_frame, text='Year')
        years_l.pack()
        years = [str(i) for i in range(2023, 2026)]
        years_vals = tuple(years)
        years_box = Combobox(years_frame, values=years_vals, state="readonly", width=7)
        years_box.pack()

    def render_add(self):
        title = Label(self.page1, text='Add Expense', font='bolder', pady=20)
        title.pack(padx=100)

        note_l = Label(self.page1, text='Note')
        note_i = Entry(self.page1, width=20)
        amount_l = Label(self.page1, text='Amount')
        amount_i = Entry(self.page1, width=15)

        note_l.pack()
        note_i.pack()
        amount_l.pack()
        amount_i.pack()

        self.render_date(page1)

        choose = Frame(self.page1)
        choose.pack(pady=10)

        r1 = Radiobutton(choose, text="Income")
        r2 = Radiobutton(choose, text="Expense")

        r1.pack(side='left')
        r2.pack(side='right')

        b = Button(self.page1, text="Add", pady=5, width=20)
        b.pack(pady=20)

    def render_filter(self):
        title = Label(self.page2, text='Filter data', font='bolder', pady=20)
        title.pack(padx=100)

        since = Label(self.page2, text='Since:')
        since.pack()
        self.render_date(page2)

        Until = Label(self.page2, text='Until:')
        Until.pack()
        self.render_date(page2)

        choose = Frame(self.page2)
        choose.pack(pady=15)

        r1 = Radiobutton(choose, text="Income")
        r2 = Radiobutton(choose, text="Expense")

        r1.pack(side='left')
        r2.pack(side='right')

        b = Button(self.page2, text="Filter", pady=5, width=20)
        b.pack(pady=20)

    def render_list(self):
        tree = Treeview(self.master, columns=('date', 'note', 'amount'), show='headings')

        tree.heading('date', text='Date')
        tree.heading('note', text='Note')
        tree.heading('amount', text='Amount')

        example_data = [
            ('2024-03-21', 'Example Note 1', '100'),
            ('2024-03-22', 'Example Note 2', '200'),
            ('2024-03-23', 'Example Note 3', '300')
        ]

        for idx, data in enumerate(example_data):
            if idx % 2 == 0:
                tree.insert('', 'end', values=data, tags=('income',))
            else:
                tree.insert('', 'end', values=data, tags=('expense',))

        tree.tag_configure('income', background='lightgreen')
        tree.tag_configure('expense', background='lightcoral')

        col_width = 100
        tree.column('date', width=col_width, anchor='center')  # Center align the column
        tree.column('note', width=col_width, anchor='center')  # Center align the column
        tree.column('amount', width=col_width, anchor='center')  # Center align the column

        scrollbar = Scrollbar(self.master, orient=VERTICAL, command=tree.yview)
        tree.configure(yscroll=scrollbar.set)

        scrollbar.pack(side='right', fill='y')
        tree.pack(side='right', fill='both', expand=True)

    def __init__(self, master):
        self.master = master
        self.master.title("Budget Tracker")
        self.master.resizable(False, False)

        self.notebook = Notebook(master)
        self.notebook.pack(side='left', fill='both', expand=True)

        self.page1 = Frame(self.notebook, width=300, height=400)
        self.page2 = Frame(self.notebook, width=300, height=400)

        self.notebook.add(self.page1, text='Add')
        self.notebook.add(self.page2, text='Filter')

        self.render_add()
        self.render_list()
        self.render_filter()


def render_menu(master):
    menubar = Menu(master)

    filemenu = Menu(menubar, tearoff=0)
    cascmenu = Menu(menubar, tearoff=0)
    cascmenu.add_command(label="1.0.0")
    filemenu.add_cascade(label="Version", menu=cascmenu)
    filemenu.add_separator()
    filemenu.add_command(label="Quit", command=master.quit)
    menubar.add_cascade(label="File", menu=filemenu)

    # TODO: udelat z about popup okno s informacemi o projektu
    editmenu = Menu(menubar, tearoff=0)
    editmenu.add_command(label="URO Tkinter project 2024")
    editmenu.add_command(label="Kateřina Baierová")
    editmenu.add_command(label="Bai0033")
    editmenu.add_command(label="VŠB")
    menubar.add_cascade(label="About", menu=editmenu)

    master.config(menu=menubar)


def main():
    master = tk.Tk()
    render_menu(master)
    BudgetTrackerApp(master)
    master.mainloop()


if __name__ == "__main__":
    main()
