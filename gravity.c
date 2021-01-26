#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define NBODIES 35

int WIDTH = 828;
int HEIGHT = 828;

GLFWwindow* setupWindow() {
    if (!glfwInit()) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return 0;
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Gravity", NULL, NULL);
    if (!window) {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    GLint framebufferWidth = 0, framebufferHeight = 0;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, 0.0, HEIGHT, 0.0, 1.0);
    return window;
}

struct Body {
    double x;
    double y;
    double vx;
    double vy;
    double mass;
    int radius;
};

struct Space {
    struct Body** bodies;
} space;

void printSpace(struct Space* space){
    printf("++++++++++\n");
    printf("%p\n", space->bodies);
    for (int i = 0; i < NBODIES; i++) {
        printf("%p\n", space->bodies[i]);
        printf("%f\n", space->bodies[i]->x);
        printf("%f\n", space->bodies[i]->y);
        printf("%f\n", space->bodies[i]->vx);
        printf("%f\n", space->bodies[i]->vy);
        printf("%f\n", space->bodies[i]->mass);
        printf("%d\n", space->bodies[i]->radius);
        printf("***\n");
    }
    printf("----------\n");
}

void drawSpace(GLFWwindow* window){
    glClear(GL_COLOR_BUFFER_BIT);
    printf("foo\n");
    glfwSwapBuffers(window);
    glfwPollEvents();
    printf("bar\n");
}

void setSpace(struct Space* space){
    space->bodies = malloc(NBODIES * sizeof(struct Body*));
    printf("%p\n", space->bodies);
    for (int i = 0; i < NBODIES; i++) {
        double a = (i - (double)NBODIES / 2);
        space->bodies[i] = malloc(sizeof(struct Body*));
        printf("%p\n", space->bodies[i]);
        space->bodies[i]->x = WIDTH * (double)(i + 1) / (NBODIES + 1);
        space->bodies[i]->y = HEIGHT / 2;
        space->bodies[i]->vx = 0;
        space->bodies[i]->vy = a * 40;
        space->bodies[i]->mass = 10e3;
        space->bodies[i]->radius = (int)((3. / 4.) / 3.142 * pow(10e3, 1. / 3.));
    }
}

int main() {
    GLFWwindow* window = setupWindow();
    setSpace(&space);
    while(!glfwWindowShouldClose(window)) {
        printSpace(&space);
        drawSpace(window);
        sleep(1);
    }
    glfwTerminate();
    return 1;
}

