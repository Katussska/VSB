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


class DateSelector(Frame):
    def __init__(self, parent, **kwargs):
        super().__init__(parent, **kwargs)
        self.setup_ui()

    def setup_ui(self):
        self.pack(pady=5)

        for label, values in [("Day", range(1, 32)), ("Month", [
            "January", "February", "March", "April", "May", "June", "July",
            "August", "September", "October", "November", "December"]), ("Year", range(2023, 2026))]:
            frame = Frame(self)
            frame.pack(side='left', padx=5)
            label_widget = Label(frame, text=label)
            label_widget.pack()
            # Configure Comboboxes to use the same variable for selection and display
            values_combo = Combobox(frame, values=list(values), state="readonly", width=10)
            values_combo.pack()


class BudgetTrackerApp:
    def render_add(self):
        title = Label(self.page1, text='Add Expense', font='bolder', pady=20)
        title.pack(padx=100)

        for label_text in ["Note", "Amount"]:
            label = Label(self.page1, text=label_text)
            label.pack()
            entry = Entry(self.page1, width=20 if label_text == "Note" else 15)
            entry.pack()

        DateSelector(self.page1)

        choose = Frame(self.page1)
        choose.pack(pady=10)

        for text, side in [("Income", 'left'), ("Expense", 'right')]:
            Radiobutton(choose, text=text, variable=self.var, value=text).pack(side=side)

        Button(self.page1, text="Add", pady=5, width=20).pack(pady=20)

    def render_filter(self):
        title = Label(self.page2, text='Filter data', font='bolder', pady=20)
        title.pack(padx=100)

        for label_text in ["Since:", "Until:"]:
            label = Label(self.page2, text=label_text)
            label.pack()
            DateSelector(self.page2)

        choose = Frame(self.page2)
        choose.pack(pady=15)

        for text, side in [("Income", 'left'), ("Expense", 'right')]:
            Radiobutton(choose, text=text, variable=self.var, value=text).pack(side=side)

        Button(self.page2, text="Filter", pady=5, width=20).pack(pady=20)

    def render_list(self):
        tree = Treeview(self.master, columns=('date', 'note', 'amount'), show='headings')

        for header, column_id in [('Date', '#0'), ('Note', '#1'), ('Amount', '#2')]:
            tree.heading(column_id, text=header)

        example_data = generate_random_data()

        for data in example_data:
            random_value = random.choice(['income', 'expense'])
            tree.insert('', 'end', values=data, tags=(random_value,))

        for tag, background in [('income', 'lightgreen'), ('expense', 'lightcoral')]:
            tree.tag_configure(tag, background=background)

        col_width = 100
        for column, width, anchor in [('date', col_width, 'center'), ('note', col_width, 'center'),
                                      ('amount', col_width, 'center')]:
            tree.column(column, width=width, anchor=anchor)

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


def show_about_info():
    about_window = tk.Toplevel()
    about_window.title("About")
    about_window.geometry("300x200")

    about_label = tk.Label(about_window,
                           text="Project informations:\n\nURO Tkinter project 2024\n Budget tracker\nKateřina Baierová\nVŠB-FEI")
    about_label.config(justify="center", padx=20, pady=20)  # Align center and add padding
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
