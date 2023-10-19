#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "util.h"

/*float color1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float color2[] = { 1.0f, 0.0f, 0.0f, 1.0f };

unsigned int program;
GLint color1Loc, color2Loc;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        for (int i = 0; i < 4; i++)
        {
            color1[i] = (rand() * 1.0f) / RAND_MAX;
            color2[i] = (rand() * 1.0f) / RAND_MAX;
        }

        std::cout << color1[0] << " " << color1[1] << " " << color1[2] << " " << color1[3] << std::endl;
        std::cout << color2[0] << " " << color2[1] << " " << color2[2] << " " << color2[3] << std::endl;

        glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);
        glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);
    }
}*/

float velocitySecondPointer = -6;
float velocityMinutePointer = -0.1;
float velocityHourPointer = -0.00417;

float currentSecondPointer = 270.0f;
float currentMinutePointer = 90.0f;
float currentHourPointer = 90.0f;

float currentTime = 0.0f;
float lastTime = 0.0f;
float deltaTime = 0.0f;

float speedUp = 1.0f;

GLint color1Loc, color2Loc, color3Loc;

float color1[] = { 1.0, 0.0, 0.0, 1.0 };
float color2[] = { 0.0, 1.0, 0.0, 1.0 };
float color3[] = { 0.0, 0.0, 1.0, 1.0 };

// fungsi tombol
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // mempercepat gerakan waktu
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        speedUp = speedUp + 5.0f;
        std::cout << "Current speed: " << speedUp << std::endl;
    }

    // reset kecepatan
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        speedUp = 4.0f;
        std::cout << "Speed is back to normal (" << speedUp << ")" << std::endl;

    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

    GLenum err = glewInit();

    // data yg dikirim ke GPU
    float vertices[] = {
        1.0, 1.0,
        -1.0, 1.0,
        -1.0, -1.0,
        1.0, -1.0
    };

    unsigned indexArr[] = {
        0, 1, 2, 0, 2, 3
    };

    unsigned int vertexBuffer = 0;

    glGenBuffers(1, &vertexBuffer);
    // informasi penggunaan buffer ke GPU 
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices, GL_STATIC_DRAW); // vertices = tempat data itu diambil

    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, indexArr, GL_STATIC_DRAW);

    // instruksi ke GPU
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // index, brp dimensi (2d), tipe data, normalized, jarak antar vertex, pada index keberapa dimulai)

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    GLint currentSecondPointerLoc = glGetUniformLocation(program, "currentSecondPointer");
    GLint currentMinutePointerLoc = glGetUniformLocation(program, "currentMinutePointer");
    GLint currentHourPointerLoc = glGetUniformLocation(program, "currentHourPointer");

    color1Loc = glGetUniformLocation(program, "color1");
    glUniform4f(color1Loc, color1[0], color1[1], color1[2], color1[3]);

    color2Loc = glGetUniformLocation(program, "color2");
    glUniform4f(color2Loc, color2[0], color2[1], color2[2], color2[3]);

    color3Loc = glGetUniformLocation(program, "color3");
    glUniform4f(color3Loc, color3[0], color3[1], color3[2], color3[3]);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = (currentTime - lastTime) * speedUp;
        lastTime = currentTime;

        currentSecondPointer = currentSecondPointer + (deltaTime * velocitySecondPointer);
        currentMinutePointer = currentMinutePointer + (deltaTime * velocityMinutePointer);
        currentHourPointer = currentHourPointer + (deltaTime * velocityHourPointer);

        glUniform1f(currentSecondPointerLoc, (currentSecondPointer * 3.14) / 180.0f);
        glUniform1f(currentMinutePointerLoc, currentMinutePointer * 3.14 / 180.0f);
        glUniform1f(currentHourPointerLoc, currentHourPointer * 3.14/ 180.0f);


        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        //glDrawArrays(GL_TRIANGLES, 0, 6); // ada 3 vertex
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /*
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}