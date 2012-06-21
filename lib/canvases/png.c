
#include <stdlib.h>

#include <png.h>

#include "ray.h"

static bool Canvas_Png_init(Canvas_Png* canvas);
static void Canvas_Png_finish(Canvas_Png* canvas);

Canvas* Canvas_Png_new(const char* filename, unsigned int width, unsigned int height) {
    Canvas_Png* canvas = (Canvas_Png*) malloc(sizeof(Canvas_Png));
    canvas->fp = fopen(filename, "wb");
    if (!canvas->fp) {
        Canvas_set_error((Canvas*) canvas, "Could not open file!");
        return false;
    }
    canvas->width = width;
    canvas->height = height;
    canvas->func.render = Canvas_Png_render;
    canvas->func.free = Canvas_Png_free;
    return (Canvas*) canvas;
}

bool Canvas_Png_render(Canvas* _canvas, const Scene* scene, const Camera* cam) {
    Canvas_Png* canvas = (Canvas_Png*) _canvas;
    Ray ray;

    if (!Canvas_Png_init(canvas))
        return false;

    for (int y=canvas->height-1; y>=0; y--) {

        for (int x=0; x<canvas->width; x++) {
            Camera_map(cam, ((double)x)/canvas->width, ((double)y)/canvas->height, &ray);
            canvas->row[x] = trace_ray_priv(scene, &ray, 0, ETHER_INDEX_OF_REFRACTION);
        }
        png_write_row(canvas->write_ptr, (unsigned char*) canvas->row);

    }

    Canvas_Png_finish(canvas);
    return true;
}

static bool Canvas_Png_init(Canvas_Png* canvas) {

    canvas->write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);
    if (!canvas->write_ptr) {
        Canvas_set_error((Canvas*)canvas, "png_create_write_struct failed!");
        fclose(canvas->fp);
        return false;
    }

    canvas->info_ptr = png_create_info_struct(canvas->write_ptr);
    if (!canvas->info_ptr) {
        Canvas_set_error((Canvas*)canvas, "png_create_info_struct failed!");
        png_destroy_write_struct(&canvas->write_ptr, (png_infopp) NULL);
        fclose(canvas->fp);
        return false;
    }

    if (setjmp(png_jmpbuf(canvas->write_ptr)))
    {
        png_destroy_write_struct(&canvas->write_ptr, &canvas->info_ptr);
        fclose(canvas->fp);
        Canvas_set_error((Canvas*)canvas, "setjmp failed!");
        return false;
    }

    png_init_io(canvas->write_ptr, canvas->fp);

    png_set_IHDR(canvas->write_ptr,
                 canvas->info_ptr,
                 canvas->width,
                 canvas->height,
                 8,
                 PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    png_write_info(canvas->write_ptr, canvas->info_ptr);

    canvas->row = (Color*) malloc(canvas->width*sizeof(Color));
    if (!canvas->row) {
        Canvas_set_error((Canvas*)canvas, "Failed to allocate memory for image row");
        return false;
    }

    return true;
}

static void Canvas_Png_finish(Canvas_Png* canvas) {
    if (canvas->row) {
        free(canvas->row);
        canvas->row = NULL;
    }
    png_write_end(canvas->write_ptr, canvas->info_ptr);
    png_destroy_write_struct(&canvas->write_ptr, &canvas->info_ptr);
    fclose(canvas->fp);
}

void Canvas_Png_free(Canvas* _canvas) {
    Canvas_Png* canvas = (Canvas_Png*) _canvas;
    if (canvas->row) {
        free(canvas->row);
        canvas->row = NULL;
    }
    free(canvas);
}
