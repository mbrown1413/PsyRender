
#ifndef _RAY_RENDER_H
#define _RAY_RENDER_H

bool render(const Scene* scene, const Camera* camera, Canvas* canvas);
Color trace_ray(const Scene* scene, const Ray* r, unsigned int depth, Object* ignore);
Object* ray_intersect(const Scene* scene, const Ray* r, Point* intersect, Object* ignore);

#endif
