
#ifndef _RAY_RENDER_H
#define _RAY_RENDER_H

bool render(const Scene* scene, const Camera* camera, Canvas* canvas);
Color trace_ray(const Scene* scene, const Ray* r);
Color trace_ray_priv(const Scene* scene, const Ray* _r, unsigned int depth, double n1);
Object* ray_intersect(const Scene* scene, const Ray* r, Point* intersect);

#endif
