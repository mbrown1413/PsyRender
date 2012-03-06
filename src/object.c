
#include "ray.h"

void Object_set_material(Object* obj, Material* mat) {
    Material_free(obj->mat);
    obj->mat = mat;
}
