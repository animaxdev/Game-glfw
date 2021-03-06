//
// Created by cod3r on 18/09/2016.
//

#include "Cube.h"

Cube::Cube(int windowWidth, int windowHeight) {
    this->setupGL(windowWidth, windowHeight);
}

void Cube::setupGL(int windowWidth, int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,

            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,

            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            0.5f, 0.5f, 0.5f,
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, -0.5f
    };

    GLfloat textureData[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,

            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,

            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
    };

    GLuint indices[] = {
            0, 1, 3, // First Triangle
            1, 2, 3  // Second Triangle
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(3, this->VBO);
    GLuint posititionBufferHandle = this->VBO[0];
    GLuint colorBufferHandle = this->VBO[1];
    GLuint textureBufferHandle = this->VBO[2];
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    // Vertex Position
    glBindBuffer(GL_ARRAY_BUFFER, posititionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex Texture
    glBindBuffer(GL_ARRAY_BUFFER, textureBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureData), textureData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // enable vertex attribute location 0 Position
    glEnableVertexAttribArray(0); // Vertex Position
    glEnableVertexAttribArray(2); // Vertex Texture Coord

    glBindBuffer(GL_ARRAY_BUFFER, posititionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, textureBufferHandle);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

    glBindVertexArray(0); // unbind VAO
}

void Cube::textureImage(unsigned char *image, int width, int height, GLenum format) {
    // @todo test if image has valid.
    try {
        // Load and create myTexture
        glGenTextures(1, &this->myTexture);
        glBindTexture(GL_TEXTURE_2D, this->myTexture);
        // Set out myTexture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        // Set myTexture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
        // Free memory image
        SOIL_free_image_data(image);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    } catch (unsigned char *image) {
        cout << "couldn't load image because: " << image << endl;
        throw "Error";
    } catch (int num) {
        cout << "couldn't load image because: " << num << endl;
        throw "Error";
    }
}

void Cube::render() {
    try {
        this->ShaderPoint->use();
    } catch (GLuint e) {
        cout << "GLuint error on Use Cube::ShaderPoint" << endl;
    }

    // Bind myTexture using myTexture units
    if (this->myTexture) {
        // Bind myTexture using myTexture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, this->myTexture);
        glUniform1i(glGetUniformLocation(this->ShaderPoint->program, "ourTexture"), 0);
    }

    mat4 transformationMatrix = this->maths.createTransformationMatrix(
            this->entity.getPosition(),
            this->entity.getRotX(), this->entity.getRotY(),
            this->entity.getRotZ(), this->entity.getScale()
    );

    mat4 projectionMatrix = glm::perspective(
            this->projectionMatrix.getFov(),
            this->projectionMatrix.getAspectRatio(),
            this->projectionMatrix.getNearPlane(),
            this->projectionMatrix.getFarPlane()
    );

    // Get their uniform location
    GLint transformLoc = glGetUniformLocation(this->ShaderPoint->program, "transform");
    GLint viewLoc = glGetUniformLocation(this->ShaderPoint->program, "view");
    GLint projectLoc = glGetUniformLocation(this->ShaderPoint->program, "projection");

    // pass them to the shaders
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(this->viewMatrix));
    glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(this->VAO);
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(0);
}

void Cube::shader(Shader *shader) {
    this->ShaderPoint = shader;
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(3, this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

const Entity &Cube::getEntity() const {
    return entity;
}

void Cube::setEntity(const Entity &entity) {
    Cube::entity = entity;
}

const ProjectionMatrix &Cube::getProjectionMatrix() const {
    return projectionMatrix;
}

void Cube::setProjectionMatrix(const ProjectionMatrix &projectionMatrix) {
    Cube::projectionMatrix = projectionMatrix;
}

const mat4 &Cube::getViewMatrix() const {
    return viewMatrix;
}

void Cube::setViewMatrix(const mat4 &viewMatrix) {
    Cube::viewMatrix = viewMatrix;
}
