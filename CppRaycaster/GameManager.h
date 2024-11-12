#include <iostream>
#include "Player.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gl/GL.h>
#include "RayRenderer.h"
#include <set>
#include "D2entity.h"

#pragma once
using namespace std;
class GameManager
{
    friend class D2entity;

    public: void beginGame(GLFWwindow* win);
            void Update();
            static set<D2entity*> entityMap;
            
    private:
        double clockToMilliseconds(clock_t t);
        
};

