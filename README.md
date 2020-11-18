# GTK Theme for Python's tkinter/ttk
![Build Status](https://api.travis-ci.com/TkinterEP/python-gttk.svg?branch=master)

Would you like to have a more native look for your Tkinter application?
Are the themes provided in [ttkthemes](https://github.com/TkinterEP/ttkthemes)
not to your liking?

This package provides a version of [`gtkTtk`](https://github.com/Geballin/gtkTtk),
formerly [`tilegtk`](https://github.com/xiaq/tile-gtk) packaged for
usage with Python. Simply follow the installation instructions and all
required files are installed to the site package directory.

## Installation
These instructions are for Ubuntu, Python 3.5 or higher. Any lower 
version may work, but is not supported. On other distributions, package 
names may be different.
```bash
# Build Tools
sudo apt install build-essential cmake
# Required Libraries
sudo apt install libgtk2.0-dev libglib2.0-dev tcl-dev tk-dev
# Required Python packages
python -m pip install scikit-build

python setup.py install 
``` 

## Usage
Simply import the package, and the theme is loaded automatically.
```python
import tkinter as tk
from tkinter import ttk
import gttk

window = tk.Tk()
style = ttk.Style()
style.theme_use("gttk")
ttk.Button(window, text="Destroy", command=window.destroy).pack()

window.mainloop()
```

If you encounter an error because you are running in the repository, 
directory, make sure to disallow imports from the working directory
before importing `gttk`:
```python
import sys
sys.path = sys.path[2:]
import gttk
```

## Screenshots
`gttk` should work with any GTK theme you can throw at it, but below
are the themes Yaru and Adwaita as examples.

![Yaru Example](https://raw.githubusercontent.com/RedFantom/python-gttk/master/screenshots/yaru.png)
![Adapta Example](https://raw.githubusercontent.com/RedFantom/python-gttk/master/screenshots/adwaita.png)

## License and Copyright
This repository provides a wrapper around `gttk`, which is a renamed 
version of `gtkTtk`, which in turn is a renamed version of `tile-gtk`.
The original `tile-gtk` is available under hte MIT License. This version
is available only under GNU GPLv3.

```
python-gttk 
Copyright (c) 2008-2012 Georgios Petasis
Copyright (c) 2012 Cheer Xiao
Copyright (c) 2019-2020 Geballin
Copyright (c) 2020 RedFantom

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```

## Project State
`tile-gtk`, `gtkTtk` and hence also `gttk` are far from perfect. You may
encounter various graphical artifacts when using particular themes,
while others work without flaws.

You are welcome to report any issues, and pull requests are even better.
Currently the package can only be built for Linux-based systems and 
attempts to create a process for building on Windows using MSYS and
CMake have proven unfruitful. If you would like to give it a go, 
feel free to contact me.
