cmake_minimum_required(VERSION 3.10)
project(CLaVie)

set(CMAKE_CXX_STANDARD 17)

# Ajoute GLFW depuis le dossier local
add_subdirectory(glfw)

# Trouve OpenGL
find_package(OpenGL REQUIRED)

# Crée l’exécutable principal
add_executable(${PROJECT_NAME} main.cpp)

# Lie les bibliothèques
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)
