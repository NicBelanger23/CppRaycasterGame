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
#include "D2Entity.h"
#include "LinkedList.h"

using namespace std;
namespace fs = std::experimental::filesystem;
int RayRenderer::Width = 10;
int RayRenderer::Height = 10;

//usefull objects
NicRay ray = NicRay();
D2Entity Entity = D2Entity(1);
D2Entity OtherEntity = D2Entity(2);
D2Entity OtherEntity2 = D2Entity(3);
D2Entity OtherEntity3 = D2Entity(4);

//textures needed for the game
GLuint mapTextures;
GLuint reticleTexture;
GLuint emenyTexture;

//verticies needed for 4k
float RayRenderer::Vertices[15360];
float FaceInformation[15360];

void RayRenderer::SendRayToGPU(int index, float posx, float dist) {
    float height = 1 / dist;
    float colloffset = ray.collOffset;
    while (colloffset > 1) {
        colloffset -= 1;
    }
    FaceInformation[index * 4] = ray.faceDirection;
    FaceInformation[(index * 4) + 1] = dist;
    FaceInformation[(index * 4) + 2] = colloffset;
    FaceInformation[(index * 4) + 3] = float(ray.foundMaterial) - 1;
	index *= 4;
	Vertices[index] = posx;
	Vertices[index + 1] = -height;
	Vertices[index + 2] = posx;
	Vertices[index + 3] = height;

}

float FOV = 1;
void RayRenderer::Rays() {

	for (float i = 0; i < Width; i++) {
		float angle = (FOV / 2) - (i * FOV/Width);
        float dist = ray.CalculateLineEquation(Player::localPlayer.position, Player::localPlayer.rotation + angle, 10);
        if (angle < 0) { angle += 2 * 3.14f; }
        if (angle > 2 * 3.14) { angle -= 2 * 3.14f; } 
        dist *= cos(angle);
		SendRayToGPU(i, -1 + (i / Width) * 2, dist);
	}
}

unsigned int shaderProgram;

unsigned int MapTexture;

Shader* ourShader;
Shader* characterShader;
Shader* reticleShader;

void RayRenderer::DrawLines() {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mapTextures);
    ourShader->setInt("textureSampler", 0); // The sampler2D uniform in the shader
    
    ourShader->use();

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Width * 4, Vertices, GL_STATIC_DRAW);
	glDrawArrays(GL_LINES, 0, Width * 2);

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
        D2Entity* entity = *it; // Dereference the iterator to get the entity pointer
        if (entity) { // Check if the pointer is not null

            sortedentitys.insertSorted(entity);

        }
    }

    LinkedNode* temp = sortedentitys.head;
    while (temp) {
        float* verts = new float[12];
        temp->data->CalcVertices(verts);

        float a = temp->data->AngleToPlayer();

        characterShader->use();

        characterShader->setFloat("AnglePlayer", a);
        characterShader->setFloat("DistPlayer", temp->data->DistFromPlayer());

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, verts, GL_STATIC_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        delete[] verts;

        temp = temp->next;
    }



}


void RayRenderer::DrawHud() {
    reticleShader->use();
    float* verts = new float[12];
    for (int i = 0; i < 12; i++) {
        verts[i] = 0.05f * i;
    }

    verts[0] = -0.2;
    verts[1] = 0.2;
    verts[2] = -0.2;
    verts[3] = -0.2;
    verts[4] = 0.2;
    verts[5] = -0.2;
    verts[6] = 0.2;
    verts[7] = 0.2;
    verts[8] = -0.2;
    verts[9] = 0.2;
    verts[10] = 0.2;
    verts[11] = -0.2;

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, verts, GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    delete[] verts;
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
    characterShader = new Shader("./charactervertex.shader", "./charactershader.shader", "chr");
    characterShader->GenBuff(0);
    reticleShader = new Shader("./reticlevertex.shader", "./reticleshader.shader", "chr");
    reticleShader->GenBuff(2);
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

    mapTextures = loadTexture((GetWD() + "\\textures\\MapAtlas.jpg").c_str());
    reticleTexture = loadTexture((GetWD() + "\\textures\\croshair.png").c_str());
    emenyTexture = loadTexture((GetWD() + "\\textures\\enemy.png").c_str());
    //LoadTextures();


    
};







