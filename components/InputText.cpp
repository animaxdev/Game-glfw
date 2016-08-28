//
// Created by cod3r on 24/08/2016.
//

#include "InputText.h"

// Initialize Static Properties.
double InputText::mouseXpos = 0.0f;
double InputText::mouseYPos = 0.0f;
int InputText::windowW = 0;
int InputText::windowH = 0;
int InputText::MouseButton = 0;
int InputText::MouseAction = 0;
unsigned int InputText::codepoint = 0;
string InputText::convertCharToString = "";

InputText::InputText(GLFWwindow *window, int windowWidth, int windowHeight) {
    this->windowW = windowWidth;
    this->windowH = windowHeight;
    // Set cursor position callback
    glfwSetCursorPosCallback(window, this->cursorPositionCallBack);
    GLfloat positionData[] = {
            this->xScale, this->yScale,
            this->xScale, -this->yScale,
            -this->xScale, -this->yScale,
            -this->xScale, this->yScale
    };

    GLfloat colorData[] = {
            0.50f, 0.49f, 0.49f,
            0.50f, 0.49f, 0.49f,
            0.50f, 0.49f, 0.49f,
            0.50f, 0.49f, 0.49f
    };

    // Create and set-up the vertex array object
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    // Buffer Object
    glGenBuffers(2, this->VBO);
    GLuint positionBufferHandle = this->VBO[0];
    GLuint colorBufferHandle = this->VBO[1];

    // Create and set-up the Element Buffer object
    glGenBuffers(1, &this->EBO);
    GLuint indices[] = {
            0, 2, 3,
            0, 2, 1
    };

    // Populate position Buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

    // Populate color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

    // set-up EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Enable the vertex attribute array
    glEnableVertexAttribArray(0); // Position
    glEnableVertexAttribArray(1); // Color

    // Map index 0 to the position buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (GLvoid *) 0);

    // Map index 1 to the color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid *) 0);

    this->setUpTextDraw();
}

/**
 * Receive the cursor position and assign Y and X position
 * @param xpos
 * @param ypos
 */
void InputText::cursorPositionCallBack(GLFWwindow* window, double xpos, double ypos) {
    /**
     * Convert x,y position in x,y projection position. Example X = 1280 in 1.0 or Window full width in 1.0 a 0.0
     */
    InputText::mouseXpos = xpos * (2.0f / InputText::windowW) - 1.0f;
    /**
     * When mouse in top Y need to negative number. For fixed this add * -1
     */
    InputText::mouseYPos = (ypos * (2.0f / InputText::windowH) - 1.0f) * -1;

//    cout << "Mouse Xpos: " << xpos << " Converted: " <<  InputText::mouseXpos << " Teste Calc: " << ((InputText::mouseXpos + 1.0f) * (InputText::windowW / 2.0f)) << endl;
//    cout << "Mouse Ypos: " << ypos << " Converted: " <<  InputText::mouseYPos << " Teste Calc: " << ((-InputText::mouseYPos + 1.0f) * (InputText::windowH / 2.0f)) << endl;
}

void InputText::render() {
    this->mouseOver();
    this->mouseClick();

    this->shader.use();

    // set-up color
    GLint vertexColorLocation = glGetUniformLocation(this->shader.program, "ourColor");
    glUniform4f(vertexColorLocation, 0.50f, 0.49f, 0.49f, this->opacity);

    // set-up transform
    glm::mat4 projection;
    projection = glm::translate(projection, glm::vec3(this->xPos, this->yPos, 0.0f));

    // Get Matrix's uniform location and set matrix
    GLint projectionLoc = glGetUniformLocation(this->shader.program, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    this->renderTextDraw();
}

void InputText::x(GLfloat xpos) {
    this->xPos = xpos;
}

void InputText::y(GLfloat ypos) {
    this->yPos = ypos;
}

/**
 * Check if mouse is above of element.
 */
void InputText::mouseOver() {
    if ((this->mouseYPos >= (this->yPos - this->yScale) && this->mouseYPos <= (this->yPos + this->yScale)) &&
        (this->mouseXpos >= (this->xPos - this->xScale) && this->mouseXpos <= (this->xPos + this->xScale))) {
        this->opacity = 0.6f;
        this->isMouseOver = true;
    } else {
        this->opacity = 1.0f;
        this->isMouseOver = false;
    }
}

void InputText::mouseClick() {
    if (this->MouseAction == GLFW_PRESS) {
        if (this->MouseButton == GLFW_MOUSE_BUTTON_LEFT) {
            this->isActive = (this->isMouseOver);
        }
    }
}

void InputText::fontShader(Shader *shader) {
    this->textDraw.shader(shader);
}

void InputText::setUpTextDraw() {
    this->textDraw.color(glm::vec3(0.5, 0.8f, 0.2f));
    this->textDraw.windowWidth(this->windowW);
    this->textDraw.windowHeight(this->windowH);
    this->textDraw.setupGL();
}

void InputText::characters(map<GLchar, Character> characters) {
    this->textDraw.characters(characters);
}

void InputText::renderTextDraw() {
    this->textDraw.x(((this->xPos - this->xScale) + 1.0f) * (this->windowW / 2.0f));
    this->textDraw.y((-(this->yPos + (this->yScale / 2)) + 1.0f) * (this->windowH / 2.f));
    // Max input string length is 38 characters
    this->textDraw.text(this->inputText);
    this->textDraw.scale(1.0f);
    this->textDraw.render();
}

void InputText::text(string text) {
    this->inputText = text;
}

string InputText::text() {
    return this->inputText;
}

void InputText::receiveKeyboardEvents() {
    if (this->isActive && this->codepoint) {
        this->convertCharToString = (char)this->codepoint;
        this->inputText.append(this->convertCharToString);
    }

    this->codepoint = 0;
}

InputText::~InputText() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(2, &this->VBO[0]);
    glDeleteBuffers(1, &this->VBO[1]);
    glDeleteBuffers(1, &this->EBO);
}