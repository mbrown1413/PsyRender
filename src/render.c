
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
            c = trace_ray(&r, scene, 0);
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

Color trace_ray(const Ray* ray, Scene* scene, unsigned int depth) {
    Ray norm, closest_norm;
    double dist, closest_dist = INFINITY;
    List_start_iteration(scene->objects);
    Object* obj;
    Object* closest_obj=NULL;
    while ((obj = (Object*) List_next(scene->objects))) {

        if (Object_ray_intersect(obj, ray, &norm)) {
            dist = DIST_SQ(norm.ox, norm.oy, norm.oz, ray->ox, ray->oy, ray->oz);
            if (dist < closest_dist) {
                closest_dist = dist;
                closest_norm = norm;
                closest_obj = obj;
            }
        }

    }
    if (closest_obj) {
        return Material_ray_hit(closest_obj->mat, &closest_norm, ray, depth+1);
    } else {
        return (Color) {0, 0, 0};
    }
}
