#include <iostream>
#include "Player.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gl/GL.h>
#include "RayRenderer.h"
#include <set>
#include "D2Entity.h"

#pragma once
using namespace std;
class GameManager
{
    friend class D2Entity;

    public: void beginGame(GLFWwindow* win);
            void Update();
            static set<D2Entity*> entityMap;
            
    private:
        double clockToMilliseconds(clock_t t);
        
};

