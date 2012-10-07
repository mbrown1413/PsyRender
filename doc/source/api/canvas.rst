
Canvas Interface
=====================================

A canvas provides a place for the rendered output to go.  Output can be written
to a file, written in memory, displayed to the user, etc.

Implementations
---------------

.. todo:: Canvas Implementations

Workflow
--------

:c:func:`Canvas_start` and :c:func:`Canvas_finish` are called at the beginning
and end of interacting with the canvas.  :c:func:`Canvas_get_next_row` and
:c:func:`Canvas_write_row` are called for every row in order from top to bottom
to provide data to the canvas.

.. todo:: Boilerplate example

The implementation can assume that it is used correctly.  For example there
don't need to be any checks to make sure :c:func:`Canvas_get_next_row` is
called before :c:func:`Canvas_start`.

Reference
---------

.. autocfile:: canvas.h
