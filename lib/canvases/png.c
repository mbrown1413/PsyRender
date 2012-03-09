
#include <stdlib.h>

#include <png.h>

#include "ray.h"

Canvas* Canvas_Png_new(const char* filename) {
    Canvas_Png* canvas = (Canvas_Png*) malloc(sizeof(Canvas_Png));
    canvas->fp = fopen(filename, "wb");
    if (!canvas->fp) {
        Canvas_set_error((Canvas*) canvas, "Could not open file!");
        return false;
    }
    canvas->func.init = Canvas_Png_init;
    canvas->func.get_next_row = Canvas_Png_get_next_row;
    canvas->func.finish_row = Canvas_Png_finish_row;
    canvas->func.finish = Canvas_Png_finish;
    return (Canvas*) canvas;
}

bool Canvas_Png_init(Canvas* canvas, const Camera* cam) {
    Canvas_Png* png_canvas = (Canvas_Png*) canvas;

    png_canvas->write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);
    if (!png_canvas->write_ptr) {
        Canvas_set_error(canvas, "png_create_write_struct failed!");
        fclose(png_canvas->fp);
        return false;
    }

    png_canvas->info_ptr = png_create_info_struct(png_canvas->write_ptr);
    if (!png_canvas->info_ptr) {
        Canvas_set_error(canvas, "png_create_info_struct failed!");
        png_destroy_write_struct(&png_canvas->write_ptr, (png_infopp) NULL);
        fclose(png_canvas->fp);
        return false;
    }

    if (setjmp(png_jmpbuf(png_canvas->write_ptr)))
    {
        png_destroy_write_struct(&png_canvas->write_ptr, &png_canvas->info_ptr);
        fclose(png_canvas->fp);
        Canvas_set_error(canvas, "setjmp failed!");
        return false;
    }

    png_init_io(png_canvas->write_ptr, png_canvas->fp);

    png_set_IHDR(png_canvas->write_ptr,
                 png_canvas->info_ptr,
                 cam->image_width,
                 cam->image_height,
                 8,
                 PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_canvas->write_ptr, png_canvas->info_ptr);

    png_canvas->row = (Color*) malloc(cam->image_width*sizeof(Color));
    if (!png_canvas->row) {
        Canvas_set_error(canvas, "Failed to allocate memory for image row");
        return false;
    }

    return true;
}

Color* Canvas_Png_get_next_row(Canvas* canvas) {
    Canvas_Png* png_canvas = (Canvas_Png*) canvas;
    return png_canvas->row;
}

void Canvas_Png_finish_row(Canvas* canvas, Color* row) {
    Canvas_Png* png_canvas = (Canvas_Png*) canvas;
    png_write_row(png_canvas->write_ptr, (unsigned char*) png_canvas->row);
}

void Canvas_Png_finish(Canvas* canvas) {
    Canvas_Png* png_canvas = (Canvas_Png*) canvas;
    free(png_canvas->row);
    png_write_end(png_canvas->write_ptr, png_canvas->info_ptr);
    png_destroy_write_struct(&png_canvas->write_ptr, &png_canvas->info_ptr);
    fclose(png_canvas->fp);
}
