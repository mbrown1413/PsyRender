
=========
PsyRender
=========

PsyRender (Physical Render) is a physically based rendering framework written
entirely in C.  It allows different rendering methods, such as ray tracing and
photon mapping, to be implemented without duplicating the tedious work.


Compiling
---------

You will need development libraries for:

* libpng
* opengl
* glut

To compile, use the make command in the top level directory:

    $ make

This puts creates executables in the bin/ directory:

    $ ./bin/interactive


Directory Structure
-------------------

* `lib/` - The library source
* `src/` - Programs with a `main` method
* `bin/` - Executables are put in here
* `doc/` - Documentation written using [Sphinx](http://sphinx.pocoo.org/)
