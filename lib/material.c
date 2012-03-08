
#include "ray.h"

Material* Material_new_default() {
    return (Material*) Material_Basic_new();
}
