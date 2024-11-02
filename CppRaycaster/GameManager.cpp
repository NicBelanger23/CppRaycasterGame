#include "GameManager.h"
#include <iostream>
#include "Player.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gl/GL.h>
#include "RayRenderer.h"
#include "D2Entity.h"

#pragma once
using namespace std;
double GameManager::clockToMilliseconds(clock_t ticks) {
    // units/(units/time) => time (seconds) * 1000 = milliseconds
    return (ticks / (double)CLOCKS_PER_SEC);
}

std::set<D2Entity*> GameManager::entityMap;

GLFWwindow* window;

//...
clock_t beginFrame = clock();
clock_t currentFrame = clock();

clock_t deltaTime = 0;
unsigned int frames = 0;


void GameManager::beginGame(GLFWwindow* win) {
    window = win;
    RayRenderer::Init();

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
    for (auto it = GameManager::entityMap.begin(); it != GameManager::entityMap.end(); ++it) {
        D2Entity* entity = *it; // Dereference the iterator to get the entity pointer
        if (entity) { // Check if the pointer is not null
            entity->Update(deltaTime); // Call the function on each entity
        }
    }
}


//Called every Frame
void GameManager::Update() {


    currentFrame = clock();

    frames++;

    //if you really want FPS
    double frametimeSec = clockToMilliseconds(currentFrame - beginFrame);

    if (frametimeSec >= 0.015) {
        double FPS = frames / frametimeSec;
        cout << "Current FPS:" << FPS << endl;
        Player::localPlayer.Tick();
        frames = 0;

        RayRenderer::Rays();

        UpdateEntities(0.015f);

        beginFrame = clock();
    }

    //draw frame
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    RayRenderer::DrawLines();

    glfwSwapBuffers(window);

    RayRenderer::ShaderTick();

    
}
