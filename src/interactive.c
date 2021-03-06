
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "psyrender.h"

#define ZOOM_FACTOR 3

Renderer* renderer;
Canvas_Mem* canvas;
Camera* camera = NULL;
Scene* scene;

void reset_view() {
    if (camera) {
        Camera_free(camera);
    }
    camera = (Camera*) Camera_Basic_new(
        (Point) {0, 0, 0}
    );

}

void horizontal_flip(Color* image, unsigned int width, unsigned int height) {
    size_t widthstep = sizeof(Color) * width;
    Color* tmp = (Color*) malloc(widthstep);
    for (int y=0; y<height/2; y++) {
        Color* row1 = &image[y*width];
        Color* row2 = &image[(height-y-1)*width];
        memcpy(tmp, row1, widthstep);
        memcpy(row1, row2, widthstep);
        memcpy(row2, tmp, widthstep);
    }
    free(tmp);
}

void on_mouse(int button, int state, int x, int y) {

    // Convert to canvas coordinates: from (0, 0) to (1, 1) with (0, 0) in the
    // bottom left.
    double canvas_x = ((double)x) / canvas->width;
    double canvas_y = 1 - ((double)y) / canvas->height;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Camera_Basic_zoom(camera, canvas_x, canvas_y, ZOOM_FACTOR);
        glutPostRedisplay();
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        Camera_Basic_zoom(camera, canvas_x, canvas_y, 1.0/ZOOM_FACTOR);
        glutPostRedisplay();
    } else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        Camera_Basic_zoom(camera, canvas_x, canvas_y, 1);
        glutPostRedisplay();
    }
}

void on_key_down(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        reset_view();
        glutPostRedisplay();
    }
}

void on_special(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            camera->pos.x -= 0.1;
            glutPostRedisplay();
        break;
        case GLUT_KEY_RIGHT:
            camera->pos.x += 0.1;
            glutPostRedisplay();
        break;
        case GLUT_KEY_UP:
            camera->pos.y += 0.1;
            glutPostRedisplay();
        break;
        case GLUT_KEY_DOWN:
            camera->pos.y -= 0.1;
            glutPostRedisplay();
        break;
    }
}

void on_reshape(int w, int h) {
    canvas->width = w;
    canvas->height = h;
    glutPostRedisplay();
}

void draw() {
    Renderer_render(renderer, scene, camera, (Canvas*) canvas);
    Color* image = canvas->image;
    horizontal_flip(image, canvas->width, canvas->height);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glDrawPixels(
        canvas->width,
        canvas->height,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        (GLvoid*) image
    );
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    Material_Solid* mat_solid;
    Object* sphere;
    Object* plane;

    renderer = Renderer_RayTraceSimple_new(UINT_MAX);

    scene = Scene_new();

    sphere = Object_Sphere_new(2, 5, -1, 1);
    mat_solid = (Material_Solid*) sphere->mat;
    mat_solid->transmit.ambient = (Color) {0.1 * 255, 0, 0};
    mat_solid->transmit.diffuse = (Color) {0.4 * 255, 0, 0};
    mat_solid->transmit.reflect = (Color) {255 * 0.9, 255 * 0.9, 255 * 0.9};
    mat_solid->transmit.refract = (Color) {0, 0, 0};
    Scene_add_object(scene, (Object*) sphere);

    sphere = Object_Sphere_new(-2, 7, -1, 1);
    mat_solid = (Material_Solid*) sphere->mat;
    mat_solid->transmit.ambient = (Color) {0, 0, 0.1 * 255};
    mat_solid->transmit.diffuse = (Color) {0, 0, 0.4 * 255};
    mat_solid->transmit.reflect = (Color) {255 * 0.9, 255 * 0.9, 255 * 0.9};
    mat_solid->transmit.refract = (Color) {0, 0, 0};
    Scene_add_object(scene, (Object*) sphere);

    sphere = Object_Sphere_new(0, 10, 1, 3);
    mat_solid = (Material_Solid*) sphere->mat;
    mat_solid->transmit.ambient = (Color) {0, 0.1 * 255, 0};
    mat_solid->transmit.diffuse = (Color) {0, 0.4 * 255, 0};
    mat_solid->transmit.reflect = (Color) {255 * 0.9, 255 * 0.9, 255 * 0.9};
    mat_solid->transmit.refract = (Color) {0, 0, 0};
    Scene_add_object(scene, (Object*) sphere);

    plane = Object_Plane_new(-2);
    Object_set_material((Object*) plane, Material_Checker_new(2));
    ((Material_Checker*)plane->mat)->tile1_transmit.ambient = (Color) {255*0.0, 255*0.0, 255*0.0};
    ((Material_Checker*)plane->mat)->tile1_transmit.diffuse = (Color) {255*0.1, 255*0.1, 255*0.1};
    ((Material_Checker*)plane->mat)->tile1_transmit.reflect = (Color) {255*0.2, 255*0.2, 255*0.2};
    ((Material_Checker*)plane->mat)->tile2_transmit.ambient = (Color) {127*0.1, 127*0.1, 127*0.1};
    ((Material_Checker*)plane->mat)->tile2_transmit.diffuse = (Color) {127, 127, 127};
    ((Material_Checker*)plane->mat)->tile2_transmit.reflect = (Color) {255*0.2, 255*0.2, 255*0.2};
    Scene_add_object(scene, (Object*) plane);

    reset_view();  // Initializes camera

    canvas = (Canvas_Mem*) Canvas_Mem_new(400, 400);

    printf("\n");
    printf("Usage:\n");
    printf("  Middle Click  -  Center View\n");
    printf("    Left Click  -  Zoom In and Center\n");
    printf("   Right Click  -  Zoom Out and Center\n");
    printf("        R       -  Reset View\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(draw);
    glutReshapeFunc(on_reshape);
    glutMouseFunc(on_mouse);
    glutKeyboardFunc(on_key_down);
    glutSpecialFunc(on_special);

    glutMainLoop();

    Camera_free(camera);
    Scene_free(scene);
    Canvas_free(canvas);

}
