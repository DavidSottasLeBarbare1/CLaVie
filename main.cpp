#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Window1", glfwGetPrimaryMonitor(), nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.3f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}