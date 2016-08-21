//
// Created by cod3r on 20/08/2016.
//

#ifndef GAME_RECTANGLE_H
#define GAME_RECTANGLE_H


#include <GL/glew.h>
#include <GL/gl.h>
#include "../util/Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Rectangle {
    GLuint VBO, VAO;
    Shader* myShader;
    GLfloat xPos = 0.0f;
    GLfloat yPos = 0.0f;
    GLfloat zPos = 0.0f;
public:
    Rectangle(GLfloat color[]);
    void render();
    Shader shader();
    void shader(Shader* shader);
    GLfloat x();
    void x(GLfloat x);
    GLfloat y();
    void y(GLfloat y);
    GLfloat z();
    void z(GLfloat z);
};

#endif //GAME_RECTANGLE_H
