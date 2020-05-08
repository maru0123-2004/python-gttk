import tkinter as tk
from tkinter import ttk

window = tk.Tk()
style = ttk.Style(window)
window.eval("set dir /usr/lib/tcltk/gtkTtk0.5; source /usr/lib/tcltk/gtkTtk0.5/pkgIndex.tcl")
window.tk.call("package", "require", "ttk::theme::gtkTtk");
print(style.theme_names())

style.theme_use("gtkTtk")
ttk.Button(window, text="Destroy", command=window.destroy).pack()

window.mainloop()

