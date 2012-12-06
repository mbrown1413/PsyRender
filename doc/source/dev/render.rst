
Rendering Overview
==================

.. todo:: Rendering Overview

.. graph:: render_flow_chart

    node [shape=Mrecord, style="filled", fillcolor="#aaddff", fontname="Sans"];

    renderer -- scene
    renderer -- canvas
    renderer -- camera

    scene -- light
    scene -- object

    object -- material
