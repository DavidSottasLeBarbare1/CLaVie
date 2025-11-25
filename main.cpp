#include <cmath>
#include <iostream>
#include <GLFW/glfw3.h>

const int WIDTH = 800;
const int HEIGHT = 800;
const float CELL_SIZE = 20.0f;



void drawCell(float x, float y, bool alive) {
    if (alive) glColor3f(1, 0.4f, 0.8f);
    else glColor3f(0.3f, 0.1f, 0.5f);

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + CELL_SIZE, y);
    glVertex2f(x + CELL_SIZE, y + CELL_SIZE);
    glVertex2f(x, y + CELL_SIZE);
    glEnd();
}

void renderGrid() {
    int cols = WIDTH / CELL_SIZE;
    int rows = HEIGHT / CELL_SIZE;

    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < cols; i++) {

            bool isAlive = (i == 0 && j == 0);
            float x = i * CELL_SIZE;
            float y = j * CELL_SIZE;
            drawCell(x, y, isAlive);
        }
    }
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "CLaVie", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.3f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        renderGrid();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 67;
}

