
Interface System
=====================================

Interfaces provide polymorphism in PsyRender. A class that implements an
interface can be used interchangeably with another class that implements the
same interface. The interface is a specification for the class's API.

Before we go any further, let's define some terminology:

* Interface -
* Implement -
* Class -
* Instance -
* Method -

.. todo:: Interface terminology

One example of an interface is :c:type:`Object`, which represents a physical
object in a scene. Implementations include :c:type:`Object_Sphere` and
:c:type:`Object_Plane`. A sphere and plane can be created with
:c:func:`Object_Sphere_new` and :c:func:`Object_Plane_new` respectively. The
user can then use object methods such as :c:func:`Object_ray_intersect`
without caring or even knowing if the object is a sphere, plane, or any other
object.

.. todo:: No type checking!

.. todo:: Generic instances are almost always passed around.


How it Works
------------

Interfaces work by sharing a common struct header between implementations. The
header contains a function table and optionally structure members that are
part of the interface.

When an interface method is called, it looks at the instance's function table
and calls the class's implementation of that method. The function will cast
the instance to the appropriate class implementation.


Naming Conventions
------------------

.. todo:: Interface Naming conventions


Implementing an interface
-------------------------

.. todo:: Defining an interface


Defining an Interface
---------------------

.. todo:: Creating an interface
