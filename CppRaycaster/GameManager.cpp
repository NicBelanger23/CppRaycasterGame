#include "GameManager.h"
#include <iostream>
#include "Player.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gl/GL.h>
#include "RayRenderer.h"
#include "LevelProgresser.h"
#include "D2entity.h"
#include "Map.h"
#include "./statemachine/soldier.h"
#include "./statemachine/statevals.h"

#pragma once
using namespace std;
int GameManager::remainingEntities = 0;

double GameManager::clockToMilliseconds(clock_t ticks) {
    // units/(units/time) => time (seconds) * 1000 = milliseconds
    return (ticks / (double)CLOCKS_PER_SEC);
}

std::set<D2entity*> GameManager::entityMap;
LevelProgresser lp = LevelProgresser();
GLFWwindow* window;

//...
clock_t beginFrame = clock();
clock_t currentFrame = clock();

clock_t deltaTime = 0;
unsigned int frames = 0;

statevals* statevals::Instance = new statevals();

void GameManager::beginGame(GLFWwindow* win) {
    window = win;
    RayRenderer::Init();

    lp.NextLevel(vector2::zero());

    Player p = Player();
    p.init();
    Player::localPlayer = p;

}


float g_vertex_buffer_data[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};


void UpdateEntities(float deltaTime) {
    GameManager::remainingEntities = 0;
    for (auto it = GameManager::entityMap.begin(); it != GameManager::entityMap.end(); ++it) {
        D2entity* entity = *it; // Dereference the iterator to get the entity pointer
        if (entity) { // Check if the pointer is not null
            entity->Update(deltaTime); // Call the function on each entity
            GameManager::remainingEntities++;
        }
    }
}

void HandelMouse(GLFWwindow* window) {
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
        // The window is currently focused
        
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        double xpos, ypos;

        glfwGetCursorPos(window, &xpos, &ypos);
        glfwSetCursorPos(window, RayRenderer::Width / 2, RayRenderer::Height / 2);
        Player::localPlayer.lookAxis -= (xpos - ((float)RayRenderer::Width / 2)) / 60;
    }
    else {
        // The window is not focused
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}


//Called every Frame
void GameManager::Update(GLFWwindow* window) {


    currentFrame = clock();

    frames++;

    //if you really want FPS
    double frametimeSec = clockToMilliseconds(currentFrame - beginFrame);

    if (frametimeSec >= 0.015) {
        double FPS = frames / frametimeSec;
        cout << "Current FPS:" << FPS << endl;
        HandelMouse(window);
        Player::localPlayer.Tick();
        lp.Tick();
        frames = 0;

        RayRenderer::Rays();

        UpdateEntities(0.015f);

        beginFrame = clock();
    }

    //draw frame
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    RayRenderer::DrawLines();

    glfwSwapBuffers(window);

    RayRenderer::ShaderTick();

    
}
