
=========
PsyRender
=========

PsyRender (Physical Render) is a physically based rendering framework written
entirely in C. It allows different rendering algorithms, such as ray tracing
and photon mapping, to be implemented without duplicating the tedious work.


Compiling
---------

You will need development libraries for:

* libpng
* opengl
* glut

To compile, use the make command in the top level directory:

    $ make

This compiles a library in `lib/libpsyrender.so` and compiles executables in
the `bin/` directory. Unless `lib/libpsyrender.so` is installed in a library
path, you will need to use the `LD_LIBRARY_PATH` to run the executables:

    $ LD_LIBRARY_PATH=lib/ ./bin/interactive


Directory Structure
-------------------

* `lib/` - The library source
* `include/` - The library include folder. `include/psyrender.h` is the main
    header.
* `src/` - C files with a `main` method. For each file, an executable is
    created in `bin/` with the same name.
* `doc/` - Documentation written using [Sphinx](http://sphinx.pocoo.org/)
