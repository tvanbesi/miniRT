# miniRT
This a simple ray tracer I made as a school project, in C. More information are available in the MINIRT.pdf.

The code compiles on Linux.
You might need to install the `libxext-dev` and `libbsd-dev` packages for the project to compile.
Simply clone the repo, `make` at the root of the repository, then use the `miniRT` executable with an appropriate file as argument.
More informations about how the file have to be formatted can be found in the MINIRT.pdf.
Some example files are available, scenex.rt.

Try it! `./miniRT scene1.rt`

The scene will take a while to load, and you need press space once for it to load, be patient. Press space again to switch between different camera angles.

I am aware that the code is very ugly, I was still learning at the time. The display will bug if you minimize the window and maximize it again as well.
