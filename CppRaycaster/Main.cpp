#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Player.h"
#include "GameManager.h"
#include "RayRenderer.h"
#include <iostream>
#include <gl/GL.h>
#include "./statemachine/statevals.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
using namespace std;
GameManager GameMan = GameManager();
GLFWwindow* MainWindow;

int main()
{
    glfwInit();

    MainWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "C++ OOP Finial", NULL, NULL);

    glfwMakeContextCurrent(MainWindow);
    glfwSetFramebufferSizeCallback(MainWindow, framebuffer_size_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    //initial GameCode
    glfwGetWindowSize(MainWindow, &RayRenderer::Width, &RayRenderer::Height);

    GameMan.beginGame(MainWindow);

    // render loop
    while (!glfwWindowShouldClose(MainWindow))
    {
        //handel input and do next uodate logic
        processInput(MainWindow);

        GameMan.Update();




        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    //walking
    Player::localPlayer.forwardAxis = 0;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        Player::localPlayer.forwardAxis += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        Player::localPlayer.forwardAxis -= 1.0f;
    }

    //looking
    Player::localPlayer.lookAxis = 0;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        Player::localPlayer.lookAxis += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        Player::localPlayer.lookAxis -= 1.0f;
    }

    //strafing
    Player::localPlayer.rightAxis = 0;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        Player::localPlayer.rightAxis += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        Player::localPlayer.rightAxis -= 1.0f;
    }

    //reloading
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        Player::localPlayer.Reload();
    }

    Player::localPlayer.pressingTrigger = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    RayRenderer::Width = width;
    RayRenderer::Height = height;
    glViewport(0, 0, width, height);

}
