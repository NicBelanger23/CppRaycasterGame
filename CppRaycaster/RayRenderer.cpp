#include "RayRenderer.h"
#include <iostream>
#include "Player.h"
#include "GameManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include "NicRay.h"
#include "textureshader.h"
#include "stb_image.h"
#include <filesystem>
#include <direct.h> 
#include "D2entity.h"
#include "LinkedList.h"

using namespace std;
namespace fs = std::experimental::filesystem;
int RayRenderer::Width = 10;
int RayRenderer::Height = 10;

//usefull objects
NicRay ray = NicRay();

//textures needed for the game
GLuint mapTextures;
GLuint reticleTexture;
GLuint emenyTexture;
GLuint gunTexture;

//verticies needed for 4k
float RayRenderer::Vertices[12];
float FaceInformation[15360];

void RayRenderer::SendRayToGPU(int index, float posx, float dist) {
    float height = 1 / dist;
    float colloffset = ray.collOffset;
    while (colloffset > 1) {
        colloffset -= 1;
    }
    FaceInformation[index * 4] = (float)ray.faceDirection;
    FaceInformation[(index * 4) + 1] = dist;
    FaceInformation[(index * 4) + 2] = colloffset;
    FaceInformation[(index * 4) + 3] = float(ray.foundMaterial) - 1;
	index *= 4;
}

float FOV = 1;
void RayRenderer::Rays() {

	for (float i = 0; i < Width; i++) {
		float angle = (FOV / 2) - (i * FOV/Width);
        float dist = ray.CalculateLineEquation(Player::localPlayer.position, Player::localPlayer.rotation + angle, 20);
        if (angle < 0) { angle += 2 * 3.14f; }
        if (angle > 2 * 3.14) { angle -= 2 * 3.14f; } 
        dist *= cos(angle);
		SendRayToGPU(i, -1 + (i / Width) * 2, dist);
	}

    Vertices[0] = -1;
    Vertices[1] = 1;
    Vertices[2] = 1;
    Vertices[3] = 1;
    Vertices[4] = -1;
    Vertices[5] = -1;
    Vertices[6] = 1;
    Vertices[7] = -1;
    Vertices[8] = 1;
    Vertices[9] = 1;
    Vertices[10] = -1;
    Vertices[11] = -1;

}

unsigned int shaderProgram;

unsigned int MapTexture;

Shader* ourShader;
Shader* characterShader;
Shader* reticleShader;
Shader* healthBarShader;
Shader* gunShader;

void RayRenderer::DrawLines() {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mapTextures);
    ourShader->setInt("textureSampler", 0); // The sampler2D uniform in the shader
    
    ourShader->use();

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, Vertices, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 6);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);


    //swap to redicle texture
    ourShader->setInt("textureSampler", 0); // The sampler2D uniform in the shader

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, emenyTexture);
    DrawEntities();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, reticleTexture);

    DrawHud();

    



    // color attribute


    
}

//sort by entity distance, then draw
void RayRenderer::DrawEntities() {

    LinkedList sortedentitys = LinkedList();

    for (auto it = GameManager::entityMap.begin(); it != GameManager::entityMap.end(); ++it) {
        D2entity* entity = *it; // Dereference the iterator to get the entity pointer
        if (entity) { // Check if the pointer is not null

            sortedentitys.insertSorted(entity);

        }
    }

    LinkedNode* temp = sortedentitys.head;
    while (temp) {
        float* verts = new float[12];
        temp->data->CalcVertices(verts);

        float a = temp->data->AnglePlayer;

        characterShader->use();

        characterShader->setFloat("AnglePlayer", a);
        characterShader->setFloat("DistPlayer", temp->data->DistanceFromPlayer);
        if (temp->data->myWeapon) {
            characterShader->setFloat("State", temp->data->myWeapon->drawFiring);
        }
        else {
            characterShader->setFloat("State", 0);
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, verts, GL_STATIC_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        delete[] verts;

        temp = temp->next;
    }



}


void RayRenderer::DrawHud() {

    //drawoing reticle
    float aspect = (float)Width / (float)Height;
    reticleShader->use();
    reticleShader->setFloat("Aspect", aspect);
    float* reticleverts = new float[12];

    reticleverts[0] = -0.2f;
    reticleverts[1] = 0.2f * aspect;
    reticleverts[2] = -0.2f;
    reticleverts[3] = -0.2f * aspect;
    reticleverts[4] = 0.2f;
    reticleverts[5] = -0.2f * aspect;
    reticleverts[6] = 0.2f;
    reticleverts[7] = 0.2f * aspect;
    reticleverts[8] = -0.2f;
    reticleverts[9] = 0.2f * aspect;
    reticleverts[10] = 0.2f;
    reticleverts[11] = -0.2f * aspect;

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, reticleverts, GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    delete[] reticleverts;

    //drawing health bar
    healthBarShader->use();
    healthBarShader->setFloat("Health", Player::localPlayer.GetHealth()/100.0);
    healthBarShader->setFloat("Ammo", Player::localPlayer.currentWeapon->AmmoPercentage());
    float* healthverts = new float[12];

    healthverts[0] = -1.0f;
    healthverts[1] = 0.2f;
    healthverts[2] = -1.0f;
    healthverts[3] = -1.0f;
    healthverts[4] = -0.8f;
    healthverts[5] = -1.0f;
    healthverts[6] = -0.8f;
    healthverts[7] = 0.2f;
    healthverts[8] = -1.0f;
    healthverts[9] = 0.2f;
    healthverts[10] = -0.8f;
    healthverts[11] = -1.0f;

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, healthverts, GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    delete[] healthverts;

    //draw weapon
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gunTexture);

    gunShader->use();
    if (Player::localPlayer.currentWeapon->isReloading) {
        gunShader->setInt("State", 2);
    }
    else if (Player::localPlayer.currentWeapon->drawFiring) {
        gunShader->setInt("State", 1);
    }
    else {
        gunShader->setInt("State", 0);
    }

    gunShader->setFloat("Bobbing", (cos(Player::localPlayer.bobbingTicks * 150) - 1)/50);

    float* gunverts = new float[12];

    gunverts[0] = -1.0f;
    gunverts[1] = 1.0f;
    gunverts[2] = -1.0f;
    gunverts[3] = -1.0f;
    gunverts[4] = 1.0f;
    gunverts[5] = -1.0f;
    gunverts[6] = -1.0f;
    gunverts[7] = 1.0f;
    gunverts[8] = 1.0f;
    gunverts[9] = 1.0f;
    gunverts[10] = 1.0f;
    gunverts[11] = -1.0f;

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, gunverts, GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    delete[] gunverts;

}





void RayRenderer::ShaderTick() {
	ourShader -> passAdditionalInfo(FaceInformation, Width * 4);
	ourShader->setInt("Width", Width);
}

string GetWD() {
    const size_t size = 1024;
    char buffer[size];
    if (_getcwd(buffer, size)) {};
    return buffer;
}

// Function to load a texture
GLuint loadTexture(const char* filePath) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture: " << filePath << std::endl;
    }
    stbi_image_free(data);
    return textureID;
}

// Load two textures

//GLuint texture2 = loadTexture((GetWD() + "\\textures\\MapAtlas.jpg").c_str());



void RayRenderer::Init() {

    //create shaders
	ourShader = new Shader("./vs.shader", "./fs.shader", "abc");
    ourShader->GenBuff(1);
    characterShader = new Shader("./charactervertex.shader", "./charactershader.shader", "def");
    characterShader->GenBuff(0);
    reticleShader = new Shader("./reticlevertex.shader", "./reticleshader.shader", "ghi");
    reticleShader->GenBuff(2);
    healthBarShader = new Shader("./charactervertex.shader", "./healthbar.shader", "jkl");
    reticleShader->GenBuff(3);
    gunShader = new Shader("./charactervertex.shader", "./weapon.shader", "mno");
    gunShader->GenBuff(4);
	unsigned int VBO;


	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use

	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    mapTextures = loadTexture((GetWD() + "\\textures\\MapAtlas.png").c_str());
    reticleTexture = loadTexture((GetWD() + "\\textures\\croshair.png").c_str());
    emenyTexture = loadTexture((GetWD() + "\\textures\\EntityStates.png").c_str());
    gunTexture = loadTexture((GetWD() + "\\textures\\GunStates.png").c_str());
    //LoadTextures();


    
};







