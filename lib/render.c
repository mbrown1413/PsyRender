
#include <stdlib.h>
#include <math.h>

#include <png.h>

#include "ray.h"

int render(Camera* camera, Scene* scene, char* filename) {

    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Could not open file!\n");
        return -1;
    }

    png_structp write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);
    if (!write_ptr) {
        fprintf(stderr, "png_create_write_struct failed!\n");
        fclose(fp);
        return -1;
    }

    png_infop info_ptr = png_create_info_struct(write_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&write_ptr, (png_infopp) NULL);
        fclose(fp);
        return -1;
    }

    if (setjmp(png_jmpbuf(write_ptr)))
    {
        png_destroy_write_struct(&write_ptr, &info_ptr);
        fclose(fp);
        fprintf(stderr, "PNG Error!\n");
        return -1;
    }

    png_init_io(write_ptr, fp);

    png_set_IHDR(write_ptr, info_ptr, camera->width, camera->height, 8, PNG_COLOR_TYPE_RGB,
            PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT);


    png_write_info(write_ptr, info_ptr);

    // How much to move the ray direction each time we move one x or y in the
    // image
    Point dx = {6.0/camera->width, 0, 0};
    Point dy = {0, 0, -6.0/camera->height};

    Color c;
    Ray r;  // Initialize pointing to upper left of image
    r.dx = -3;
    r.dy = 3;
    r.dz = 3;
    r.ox = 0;
    r.oy = 0;
    r.oz = 0;
    unsigned char* row = (unsigned char*) malloc(camera->width*3*sizeof(unsigned char));
    for (int y=0; y<camera->height; y++) {

        r.dx = -3;
        for (int x=0; x<camera->width*3; x+=3) {
            r.dx += dx.x;
            r.dy += dx.y;
            r.dz += dx.z;
            c = trace_ray(scene, &r, 0);
            row[x+0] = c.r;
            row[x+1] = c.g;
            row[x+2] = c.b;
        }
        r.dx += dy.x;
        r.dy += dy.y;
        r.dz += dy.z;

        png_write_row(write_ptr, row);
    }
    free(row);

    png_write_end(write_ptr, info_ptr);
    png_destroy_write_struct(&write_ptr, &info_ptr);

    fclose(fp);
    return 0;
}

Color trace_ray(const Scene* scene, const Ray* r, unsigned int depth) {
    Point intersect;
    Vector norm;
    Object* closest_obj;

    closest_obj = ray_intersect(scene, r, &intersect, &norm);

    if (closest_obj) {

        Material* mat = closest_obj->mat;
        Color mat_color = Material_ray_hit(scene, mat, r, &intersect, &norm, depth+1);

        if (mat->reflectivity) {
            Ray reflected;
            ray_reflect(r, &intersect, &norm, &reflected);
            Color reflected_color = trace_ray(scene, &reflected, depth);
            return (Color) {
                (1-mat->reflectivity)*mat_color.r + mat->reflectivity*reflected_color.r,
                (1-mat->reflectivity)*mat_color.g + mat->reflectivity*reflected_color.g,
                (1-mat->reflectivity)*mat_color.b + mat->reflectivity*reflected_color.b
            };
        }

        return mat_color;

    } else {
        return (Color) {0, 0, 0};
    }
}

Object* ray_intersect(const Scene* scene, const Ray* r, Point* intersect, Vector* norm) {
    Point obj_intersect, closest_intersect;
    Vector obj_norm, closest_norm;
    double dist, closest_dist = INFINITY;
    Object* obj;
    Object* closest_obj=NULL;

    List_start_iteration(scene->objects);
    while ((obj = (Object*) List_next(scene->objects))) {

        if (Object_ray_intersect(obj, r, &obj_intersect, &obj_norm)) {
            dist = DIST_SQ(obj_intersect.x, obj_intersect.y, obj_intersect.z, r->ox, r->oy, r->oz);
            if (dist < closest_dist) {
                closest_dist = dist;
                closest_norm = obj_norm;
                closest_intersect = obj_intersect;
                closest_obj = obj;
            }
        }
    }

    *intersect = closest_intersect;
    *norm = closest_norm;
    return closest_obj;
}
