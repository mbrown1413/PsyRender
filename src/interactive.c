
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "ray.h"

#define ZOOM_FACTOR 3

Canvas* canvas;
Camera* camera = NULL;
Scene* scene;

void reset_view() {
    if (camera) {
        Camera_free(camera);
    }
    camera = (Camera*) Camera_Basic_new(
        800, 800,
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
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Camera_Basic_zoom(camera, x, y, ZOOM_FACTOR);
        glutPostRedisplay();
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        Camera_Basic_zoom(camera, x, y, 1.0/ZOOM_FACTOR);
        glutPostRedisplay();
    } else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        Camera_Basic_zoom(camera, x, y, 1);
        glutPostRedisplay();
    }
}

void on_key_down(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        reset_view();
        glutPostRedisplay();
    }
}

void on_reshape(int w, int h) {
    camera->image_width = w;
    camera->image_height = h;
    glutPostRedisplay();
}

void draw() {
    render(scene, camera, canvas);
    Color* image = ((Canvas_Mem*) canvas)->image;
    horizontal_flip(image, camera->image_width, camera->image_height);
    glDrawPixels(
        camera->image_width,
        camera->image_height,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        (GLvoid*) image
    );
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    Material_Basic* mat_basic;
    Sphere* sphere;
    Plane* plane;

    scene = Scene_new();

    sphere = Sphere_new(2, 5, -1, 1);
    mat_basic = (Material_Basic*) sphere->mat;
    mat_basic->color = (Color) {255, 0, 0};
    mat_basic->reflectivity = 0.9;
    Scene_add_object(scene, (Object*) sphere);

    sphere = Sphere_new(-2, 7, -1, 1);
    mat_basic = (Material_Basic*) sphere->mat;
    mat_basic->color = (Color) {0, 0, 255};
    mat_basic->reflectivity = 0.9;
    Scene_add_object(scene, (Object*) sphere);

    sphere = Sphere_new(0, 10, 1, 3);
    mat_basic = (Material_Basic*) sphere->mat;
    mat_basic->color = (Color) {0, 255, 0};
    mat_basic->reflectivity = 0.9;
    Scene_add_object(scene, (Object*) sphere);

    plane = Plane_new(-2);
    Object_set_material((Object*) plane, Material_Checker_new(2));
    plane->mat->reflectivity = 0.1;
    Scene_add_object(scene, (Object*) plane);

    reset_view();  // Initializes camera

    canvas = Canvas_Mem_new();

    printf("\n");
    printf("Usage:\n");
    printf("  Middle Click  -  Center View\n");
    printf("    Left Click  -  Zoom In and Center\n");
    printf("   Right Click  -  Zoom Out and Center\n");
    printf("        R       -  Reset View\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(camera->image_width, camera->image_height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);

    glutDisplayFunc(draw);
    glutReshapeFunc(on_reshape);
    glutMouseFunc(on_mouse);
    glutKeyboardFunc(on_key_down);

    glutMainLoop();


    Camera_free(camera);
    Scene_free(scene);
    Canvas_free(canvas);

}
