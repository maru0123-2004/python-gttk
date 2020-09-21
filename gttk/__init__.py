"""
Author: RedFantom
License: GNU GPLv3
Copyright (c) 2020 RedFantom
"""
import os
from tkinter import ttk


__orig_ttk_Style_init__ = ttk.Style.__init__


def __ttk_Style_init__(self, *args, **kwargs):
    __orig_ttk_Style_init__(self, *args, **kwargs)

    folder = os.path.dirname(os.path.abspath(__file__))

    self.tk.eval("set dir {0}; source {0}/pkgIndex.tcl".format(folder))
    self.tk.call("package", "require", "ttk::theme::gtkTtk")


ttk.Style.__init__ = __ttk_Style_init__
