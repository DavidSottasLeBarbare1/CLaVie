#include <cmath>
#include <iostream>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <map>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct Color {
    float r, g, b;
};

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

std::unordered_map<Cell, Color, CellHash> aliveCells;

const int WIDTH = 800;

const int HEIGHT = 800;

const float CELL_SIZE = 10.0f;

Color aliveColor = {1, 0.4f, 0.8f};

void drawCell(float x, float y, const Color& color, bool alive) {
    if (alive)
        glColor3f(color.r, color.g, color.b);
    else
        glColor3f(0.3f, 0.1f, 0.5f);

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
            float x = i * CELL_SIZE;
            float y = j * CELL_SIZE;

            auto it = aliveCells.find(c);
            if (it != aliveCells.end())
                drawCell(x, y, it->second, true);
            else
                drawCell(x, y, aliveColor, false);
        }
    }
}


Cell getCellFromMouse(double mouseX, double mouseY) {
    int cx = mouseX / CELL_SIZE;
    int cy = (HEIGHT - mouseY) / CELL_SIZE;
    return {cx, cy};
}

void saveDrawing(int width, int height)
{
    std::vector<unsigned char> pixels(width * height * 3);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    for (int j = 0; j < height / 2; ++j) {
        for (int i = 0; i < width * 3; ++i) {
            std::swap(pixels[j * width * 3 + i], pixels[(height - 1 - j) * width * 3 + i]);
        }
    }
    stbi_write_png("../images/dessin.png", width, height, 3, pixels.data(), width * 3);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        aliveColor = {1, 0.0f, 0.0f};
    if (key == GLFW_KEY_G && action == GLFW_PRESS)
        aliveColor = {0, 1, 0};
    if (key == GLFW_KEY_B && action == GLFW_PRESS)
        aliveColor = {0, 0.0f, 1};
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        aliveColor = {1, 1, 0.0f};
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
        aliveColor = {1, 0.0f, 1};
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
        aliveColor = {0, 1, 1};
    if ((mods & GLFW_MOD_CONTROL) && key == GLFW_KEY_S) {
        saveDrawing(WIDTH, HEIGHT);
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
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);

            Cell c = getCellFromMouse(mx, my);
            aliveCells[c] = aliveColor;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);
            Cell c = getCellFromMouse(mx, my);

            aliveCells.erase(c);
        }
        glfwSetKeyCallback(window, key_callback);
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