#include <iostream>
#include "Player.h"
#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gl/GL.h>
#include <list>
#include <vector>

using namespace std;
#pragma once
class RayRenderer
{
	private:
		static void SendRayToGPU(int index, float posx, float dist);
	public: 
		static void Rays();
		static void DrawLines();
		static int Width;
		static int Height;
		static GLfloat Vertices[];
		static void Init();
		static void ShaderTick();
		static void DrawEntities();
		static void DrawHud();


};

