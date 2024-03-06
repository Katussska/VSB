# -*- coding: utf-8 -*-

import tkinter.font
from tkinter import *


class myApp:

    def convert_temperature(self, event=None):
        v = float(self.ent_in.get())
        if self.dir.get() == 1:  # C -> F
            result = v * 9 / 5 + 32
        else:  # F -> C
            result = (v - 32) * 5 / 9
        self.ent_out.delete(0, END)
        self.ent_out.insert(0, str(round(result, 2)))

    def __init__(self, root):
        root.title('Převodník teplot')
        root.resizable(False, False)
        root.bind('<Return>', self.convert_temperature)

        def_font = tkinter.font.nametofont("TkDefaultFont")
        def_font.config(size=16)

        self.left_frame = Frame(root)
        self.right_frame = Frame(root)

        self.dir = IntVar()
        self.dir.set(1)

        self.ent_frame = Frame(self.left_frame)
        self.lbl_in = Label(self.ent_frame, text="Vstup")
        self.ent_in = Entry(self.ent_frame, width=10, font=def_font)
        self.ent_in.insert(0, '0')

        self.lbl_out = Label(self.ent_frame, text="Výstup")
        self.ent_out = Entry(self.ent_frame, width=10, font=def_font)

        self.ca = Canvas(self.right_frame, width=300, height=400)
        self.photo = PhotoImage(file="th_empty.png")
        self.ca.create_image(150, 200, image=self.photo)

        self.left_frame.pack(side="left", fill=Y)
        self.right_frame.pack(side="right")
        self.ent_frame.pack()
        self.lbl_in.pack()
        self.ent_in.pack()
        self.lbl_out.pack()
        self.ent_out.pack()

        self.ent_in.focus_force()


root = Tk()
app = myApp(root)
root.mainloop()
