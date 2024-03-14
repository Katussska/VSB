import tkinter as tk
from tkinter import *
from tkinter.ttk import Treeview, Notebook


class BudgetTrackerApp:
    def render_add(self):
        pass

    def render_filter(self):
        pass

    def render_list(self):
        tree = Treeview(self.master, columns=('date', 'note', 'amount'), show='headings')

        tree.heading('date', text='Date')
        tree.heading('note', text='Note')
        tree.heading('amount', text='Amount')

        scrollbar = Scrollbar(self.master, orient=VERTICAL, command=tree.yview)
        tree.configure(yscroll=scrollbar.set)

        scrollbar.pack(side='right', fill='y')
        tree.pack(side='right', fill='both', expand=True)

    def list_insert(self):
        pass

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

        self.render_list()


def render_menu(master):
    menubar = Menu(master)

    filemenu = Menu(menubar, tearoff=0)
    cascmenu = Menu(menubar, tearoff=0)
    cascmenu.add_command(label="1.0.0")
    filemenu.add_cascade(label="Version", menu=cascmenu)
    filemenu.add_separator()
    filemenu.add_command(label="Quit", command=master.quit)
    menubar.add_cascade(label="File", menu=filemenu)

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
