import tkinter as tk
from tkinter import filedialog, ttk


class Book:
    def __init__(self, title: str, author: str, isbn: str):
        self.title = title
        self.author = author
        self.isbn = isbn


class App:
    about_window = 0
    data: [Book] = [
        Book("Volani Cthulhu", "H. P. Lovecraft", "278347826"),
        Book("Robinson Crusoe", "Daniel Defoe", "298357927")
    ]
    data_filtered: [Book] = data
    table_headers = ["Titul", "Autor", "ISBN"]
    table_content = []

    def open_file(self):
        file_path = filedialog.askopenfilename()
        if file_path:
            self.data = []
            with open(file_path, 'r') as f:
                lines = f.read().splitlines()
                for line in lines:
                    d = line.split(';')
                    self.data.append(Book(d[0], d[1], d[2]))
            self.reset_filter()

    def save_file(self):
        file_path = filedialog.asksaveasfilename()
        if file_path:
            with open(file_path, 'w') as f:
                for book in self.data:
                    f.write(f'{book.title};{book.author};{book.isbn}\n')

    def close_about(self):
        self.about_window.destroy()

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

    def reset_filter(self):
        self.filter_title.set('')
        self.filter_author.set('')
        self.filter_isbn.set('')
        self.data_filtered = self.data
        self.render_table()

    def apply_filter(self):
        title = self.filter_title.get().lower()
        author = self.filter_author.get().lower()
        isbn = self.filter_isbn.get().lower()
        if title == '' and author == '' and isbn == '':
            self.reset_filter()
            return
        self.data_filtered = []
        for book in self.data:
            if (title != '' and title in book.title.lower()) or (author != '' and author in book.author.lower()) or (
                    isbn != '' and isbn in book.isbn.lower()):
                self.data_filtered.append(book)
        self.render_table()

    def render_table(self):
        for e in self.table_content:
            e.destroy()

        for col, header in enumerate(self.table_headers):
            lbl = tk.Label(self.table, text=header)
            lbl.grid(row=0, column=col, padx=5, pady=5)
            self.table_content.append(lbl)

        for row, book in enumerate(self.data_filtered, start=1):
            title = tk.StringVar()
            title.set(book.title)
            val1 = tk.Entry(self.table, textvariable=title, state='readonly')
            val1.grid(row=row, column=0, padx=0, pady=0)
            self.table_content.append(val1)

            author = tk.StringVar()
            author.set(book.author)
            val2 = tk.Entry(self.table, textvariable=author, state='readonly')
            val2.grid(row=row, column=1, padx=0, pady=0)
            self.table_content.append(val2)

            isbn = tk.StringVar()
            isbn.set(book.isbn)
            val3 = tk.Entry(self.table, textvariable=isbn, state='readonly')
            val3.grid(row=row, column=2, padx=0, pady=0)
            self.table_content.append(val3)

    def add_book(self):
        title = self.add_title.get()
        author = self.add_author.get()
        isbn = self.add_isbn.get()
        if title != '' and author != '' and isbn != '':
            self.data.append(Book(title, author, isbn))
            self.render_table()
            self.add_title.set('')
            self.add_author.set('')
            self.add_isbn.set('')

    def render_add_tab(self):
        label_title = tk.Label(self.frame_add, text="Titul:")
        label_title.grid(row=0, column=0, sticky="w")
        input_title = tk.Entry(self.frame_add, textvariable=self.add_title)
        input_title.grid(row=1, column=0, sticky="w")

        label_author = tk.Label(self.frame_add, text="Autor:")
        label_author.grid(row=2, column=0, sticky="w")
        input_title = tk.Entry(self.frame_add, textvariable=self.add_author)
        input_title.grid(row=3, column=0, sticky="w")

        label_isbn = tk.Label(self.frame_add, text="ISBN:")
        label_isbn.grid(row=4, column=0, sticky="w")
        input_isbn = tk.Entry(self.frame_add, textvariable=self.add_isbn)
        input_isbn.grid(row=5, column=0, sticky="w")

        tk.Button(self.tab_add, text="Pridat", command=self.add_book).grid(row=1, column=0, columnspan=2, pady=10)

    def render_filter_tab(self):
        label_title = tk.Label(self.frame_filter, text="Titul:")
        label_title.grid(row=0, column=0, sticky="w")
        input_title = tk.Entry(self.frame_filter, textvariable=self.filter_title)
        input_title.grid(row=1, column=0, sticky="w")

        label_author = tk.Label(self.frame_filter, text="Autor:")
        label_author.grid(row=2, column=0, sticky="w")
        input_title = tk.Entry(self.frame_filter, textvariable=self.filter_author)
        input_title.grid(row=3, column=0, sticky="w")

        label_isbn = tk.Label(self.frame_filter, text="ISBN:")
        label_isbn.grid(row=4, column=0, sticky="w")
        input_isbn = tk.Entry(self.frame_filter, textvariable=self.filter_isbn)
        input_isbn.grid(row=5, column=0, sticky="w")

        (tk.Button(self.tab_filter, text="Filtrovat", command=self.apply_filter)
         .grid(row=1, column=0, columnspan=2, pady=5))
        tk.Button(self.tab_filter, text="Reset", command=self.reset_filter).grid(row=2, column=0, columnspan=2, pady=5)

    def __init__(self, root):
        self.root = root
        self.root.title('KnihaDB v0.1 SIK0207')
        self.root.resizable(False, False)

        self.add_title = tk.StringVar()
        self.add_author = tk.StringVar()
        self.add_isbn = tk.StringVar()

        self.filter_title = tk.StringVar()
        self.filter_author = tk.StringVar()
        self.filter_isbn = tk.StringVar()

        # Menu Bar
        menubar = tk.Menu(root)

        # File menu
        filemenu = tk.Menu(menubar, tearoff=0)
        filemenu.add_command(label="Open", command=self.open_file)
        filemenu.add_command(label="Save", command=self.save_file)
        filemenu.add_separator()
        filemenu.add_command(label="Exit", command=root.quit)
        menubar.add_cascade(label="File", menu=filemenu)

        # About menu
        aboutmenu = tk.Menu(menubar, tearoff=0)
        aboutmenu.add_command(label="About", command=self.show_about)
        menubar.add_cascade(label="About", menu=aboutmenu)

        root.config(menu=menubar)

        notebook = ttk.Notebook(root)
        notebook.pack(padx=10, pady=10, side=tk.LEFT, fill='both', expand=True)

        self.tab_add = ttk.Frame(notebook)
        notebook.add(self.tab_add, text="Pridat")
        self.tab_filter = ttk.Frame(notebook)
        notebook.add(self.tab_filter, text="Filtruj")

        self.frame_add = ttk.Frame(self.tab_add)
        self.frame_add.grid(row=0, column=0, padx=10, pady=10, sticky="w")

        self.frame_filter = ttk.Frame(self.tab_filter)
        self.frame_filter.grid(row=0, column=0, padx=10, pady=10, sticky="w")

        self.render_add_tab()
        self.render_filter_tab()

        self.table = ttk.Frame(root)
        self.table.pack(padx=10, pady=10, side=tk.LEFT)
        self.render_table()


def main():
    root = tk.Tk()
    App(root)
    root.mainloop()


if __name__ == "__main__":
    main()
