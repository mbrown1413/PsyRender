
PsyRender Documentation
=====================================

User Documentation
------------------

.. toctree::
    :maxdepth: 2

.. todo:: User Documentation


Development Documentation
-------------------------

.. toctree::
    :maxdepth: 3

    classes
    api/index

Rendering flow chart:

.. graph:: render_flow_chart

    node [shape=Mrecord, style="filled", fillcolor="#aaddff", fontname="Sans"];

    render_method -- scene
    render_method -- canvas
    render_method -- camera

    scene -- light
    scene -- object

    object -- material


.. Indices and tables
.. ------------------
.. * :ref:`genindex`
.. * :ref:`search`

Todo List
---------

.. todolist::
