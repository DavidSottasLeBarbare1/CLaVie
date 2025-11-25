#include <cmath>
#include <iostream>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <map>

struct Cell {
    int x, y;
    bool operator==(const Cell& o) const {
        return x == o.x && y == o.y;
    }
};

struct CellHash {
    size_t operator()(const Cell& c) const {
        return (static_cast<size_t>(c.x) << 32) ^ static_cast<size_t>(c.y);
    }
};
std::unordered_map<Cell, bool, CellHash> aliveCells;
const int WIDTH = 800;
const int HEIGHT = 800;
const float CELL_SIZE = 10.0f;

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

            Cell c{i, j};
            bool isAlive = aliveCells.find(c) != aliveCells.end();
            float x = i * CELL_SIZE;
            float y = j * CELL_SIZE;
            drawCell(x, y, isAlive);
        }
    }
}
Cell getCellFromMouse(double mouseX, double mouseY) {
    int cx = mouseX / CELL_SIZE;
    int cy = (HEIGHT - mouseY) / CELL_SIZE;
    return {cx, cy};
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
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);

            Cell c = getCellFromMouse(mx, my);
            aliveCells[c] = true; // On place un carré vivant
        }

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

