
#ifndef _RAY_RENDER_H
#define _RAY_RENDER_H

int render(Camera* camera, Scene* scene, char* filename);
Color trace_ray(const Ray* ray, Scene* scene, unsigned int depth);

#endif
