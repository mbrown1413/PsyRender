
#include <stdlib.h>
#include <stdio.h>

#include <png.h>

#include "ray.h"

Canvas* Canvas_Png_new(const char* filename, unsigned int width, unsigned int height) {
    Canvas_Png* canvas = (Canvas_Png*) malloc(sizeof(Canvas_Png));
    canvas->fp = fopen(filename, "wb");
    if (!canvas->fp) {
        fprintf(stderr, "Could not open file!");
        return false;
    }
    canvas->width = width;
    canvas->height = height;
    canvas->func.start = Canvas_Png_start;
    canvas->func.get_next_row = Canvas_Png_get_next_row;
    canvas->func.write_row = Canvas_Png_write_row;
    canvas->func.finish = Canvas_Png_finish;
    canvas->func.free = Canvas_Png_free;
    return (Canvas*) canvas;
}

bool Canvas_Png_start(Canvas* _canvas) {
    Canvas_Png* canvas = (Canvas_Png*) _canvas;

    canvas->write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);
    if (!canvas->write_ptr) {
        fprintf(stderr, "png_create_write_struct failed!");
        fclose(canvas->fp);
        return false;
    }

    canvas->info_ptr = png_create_info_struct(canvas->write_ptr);
    if (!canvas->info_ptr) {
        fprintf(stderr, "png_create_info_struct failed!");
        png_destroy_write_struct(&canvas->write_ptr, (png_infopp) NULL);
        fclose(canvas->fp);
        return false;
    }

    if (setjmp(png_jmpbuf(canvas->write_ptr)))
    {
        png_destroy_write_struct(&canvas->write_ptr, &canvas->info_ptr);
        fclose(canvas->fp);
        fprintf(stderr, "setjmp failed!");
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
        fprintf(stderr, "Failed to allocate memory for image row");
        return false;
    }

    return true;
}

Color* Canvas_Png_get_next_row(Canvas* _canvas) {
    Canvas_Png* canvas = (Canvas_Png*) _canvas;
    return canvas->row;
}

bool Canvas_Png_write_row(Canvas* _canvas, Color* row) {
    Canvas_Png* canvas = (Canvas_Png*) _canvas;
    png_write_row(canvas->write_ptr, (unsigned char*) canvas->row);
    return true;
}

bool Canvas_Png_finish(Canvas* _canvas) {
    Canvas_Png* canvas = (Canvas_Png*) _canvas;
    if (canvas->row) {
        free(canvas->row);
        canvas->row = NULL;
    }
    png_write_end(canvas->write_ptr, canvas->info_ptr);
    png_destroy_write_struct(&canvas->write_ptr, &canvas->info_ptr);
    fclose(canvas->fp);
    return true;
}

void Canvas_Png_free(Canvas* _canvas) {
    Canvas_Png* canvas = (Canvas_Png*) _canvas;
    if (canvas->row) {
        free(canvas->row);
        canvas->row = NULL;
    }
    free(canvas);
}
