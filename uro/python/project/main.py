import random
import tkinter as tk
from tkinter import *
from tkinter.ttk import Treeview, Notebook, Combobox


def generate_random_data():
    data = []

    for _ in range(40):
        random_date = "2024-03-" + str(random.randint(1, 30))
        random_note = "Example Note " + str(random.randint(4, 100))
        random_amount = str(random.randint(100, 1000))
        data.append((random_date, random_note, random_amount))
    return data


def render_date(page):
    date = Frame(page)
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


class BudgetTrackerApp:
    def fce(self):
        self.la.configure(text=self.cmb.get())

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

        render_date(self.page1)

        choose = Frame(self.page1)
        choose.pack(pady=10)

        r1 = Radiobutton(choose, text="Income", variable=self.var, value="Income")
        r2 = Radiobutton(choose, text="Expense", variable=self.var, value="Expense")

        r1.pack(side='left')
        r2.pack(side='right')

        b = Button(self.page1, text="Add", pady=5, width=20)
        b.pack(pady=20)

    def render_filter(self):
        title = Label(self.page2, text='Filter data', font='bolder', pady=20)
        title.pack(padx=100)

        since = Label(self.page2, text='Since:')
        since.pack()
        render_date(self.page2)

        until = Label(self.page2, text='Until:')
        until.pack()
        render_date(self.page2)

        choose = Frame(self.page2)
        choose.pack(pady=15)

        r1 = Radiobutton(choose, text="Income", variable=self.var, value="Income")
        r2 = Radiobutton(choose, text="Expense", variable=self.var, value="Expense")

        r1.pack(side='left')
        r2.pack(side='right')

        b = Button(self.page2, text="Filter", pady=5, width=20)
        b.pack(pady=20)

    def render_list(self):
        tree = Treeview(self.master, columns=('date', 'note', 'amount'), show='headings')

        tree.heading('date', text='Date')
        tree.heading('note', text='Note')
        tree.heading('amount', text='Amount')

        example_data = generate_random_data()

        for data in example_data:
            random_value = random.choice(['income', 'expense'])
            tree.insert('', 'end', values=data, tags=(random_value,))

        tree.tag_configure('income', background='lightgreen')
        tree.tag_configure('expense', background='lightcoral')

        col_width = 100
        tree.column('date', width=col_width, anchor='center')
        tree.column('note', width=col_width, anchor='center')
        tree.column('amount', width=col_width, anchor='center')

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

        self.var = StringVar(value="Income")

        self.render_add()
        self.render_list()
        self.render_filter()

    def show_about(self):
        self.about_window = tk.Toplevel(self.root)
        self.about_window.title("About")
        self.about_window.resizable(False, False)
        about_label = tk.Label(self.about_window, text="KnihaDB v0.1")
        author_label = tk.Label(self.about_window, text="Filip Sikora SIK0207 @ vsb.cz")
        about_label.pack(padx=20, pady=10)
        author_label.pack(padx=20, pady=10)
        ok_btn = tk.Button(self.about_window, text="OK", command=self.close_about)
        ok_btn.pack(padx=20, pady=10)


def show_about_info():
    about_window = tk.Toplevel()
    about_window.title("About")
    about_window.geometry("300x200")

    about_label = tk.Label(about_window,
                           text="Project informations:\n\nURO Tkinter project 2024\nKateřina Baierová\nVŠB-FEI")
    about_label.config(justify="center", padx=20, pady=20)  # Zarovnání na střed a padding
    about_label.pack()

    close_button = tk.Button(about_window, text="Close", command=about_window.destroy)
    close_button.pack()


def render_menu(master):
    menubar = Menu(master)

    filemenu = Menu(menubar, tearoff=0)
    cascmenu = Menu(menubar, tearoff=0)
    cascmenu.add_command(label="1.0.0")
    filemenu.add_cascade(label="Version", menu=cascmenu)
    filemenu.add_separator()
    filemenu.add_command(label="Quit", command=master.quit)
    menubar.add_cascade(label="File", menu=filemenu)

    about = Menu(menubar, tearoff=0)
    about.add_command(label="About", command=show_about_info)
    menubar.add_cascade(label="Help", menu=about)

    master.config(menu=menubar)


def main():
    master = tk.Tk()
    render_menu(master)
    BudgetTrackerApp(master)
    master.mainloop()


if __name__ == "__main__":
    main()
