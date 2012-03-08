
#ifndef _RAY_RENDER_H
#define _RAY_RENDER_H

int render(Camera* camera, Scene* scene, char* filename);
Color trace_ray(const Scene* scene, const Ray* r, unsigned int depth);
Object* ray_intersect(const Scene* scene, const Ray* r, Point* intersect, Vector* norm);

#endif
