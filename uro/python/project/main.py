import tkinter as tk
from tkinter import *


class BudgetTrackerApp:
    def render_add(self):
        pass

    def render_filter(self):
        pass

    def render_list(self):
        pass

    def __init__(self, master):
        self.master = master
        self.master.title("Budget Tracker")
        self.master.resizable(False, False)

        list_headers = ["Date", "Note", "Amount"]
        list_content = []

        big_font = ('Helvetica', 15, 'bold')
        form_frame = Frame(master, bd=50)

        label = Label(form_frame, text="Add record", font=big_font)
        info_label = Label(form_frame, text="Note")
        info_input = Entry(form_frame, width=20)

        label.grid(row=0, column=1, sticky=NSEW)
        info_label.grid(row=1, column=1, sticky=W)
        info_input.grid(row=1, column=1, sticky=E)
        form_frame.pack(side="left")

        self.render_add()


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
