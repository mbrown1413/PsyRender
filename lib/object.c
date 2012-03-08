
#include "ray.h"

void Object_set_material(Object* obj, Material* mat) {
    Material_free(obj->mat);
    obj->mat = mat;
}

void Object_free(Object* obj) {
    Material_free(obj->mat);
    free(obj);
}
