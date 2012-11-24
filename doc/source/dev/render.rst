
Rendering Overview
==================

.. todo:: Rendering Overview

.. graph:: render_flow_chart

    node [shape=Mrecord, style="filled", fillcolor="#aaddff", fontname="Sans"];

    render_method -- scene
    render_method -- canvas
    render_method -- camera

    scene -- light
    scene -- object

    object -- material
