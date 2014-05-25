import sys
from cx_Freeze import setup, Executable

base = None
if sys.platform == "win32":
    base = "Win32GUI"

setup(  name = "MyApp",
        version = "0.1",
        description = "My PyQT application!",
        executables = [Executable("pyqt_example.py", base=base)])
