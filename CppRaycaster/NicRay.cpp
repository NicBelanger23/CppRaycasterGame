#include "NicRay.h"
#include "Map.h"
#include <cmath>
#include "vector2.h"
using namespace std;

float angle;
int maxDepthl;

float Angle;
float M;
float B;

float xhyp = 0;
int xstep = 0;
float Foundx = 0.1f;
float foundy;
int materialy;

float yhyp = 0;
int ystep = 0;
float Foundy = 0.1f;
float foundx;
int materialx;

float NicRay::CalculateLineEquation(vector2 start, float myangle, int depth) {
    angle = myangle;

    //create a unit vector in the direction of angle
    float x = cos(angle);
    float y = sin(angle);
    return CalculateLineEquation(start, vector2(x, y), depth);
}

float NicRay::CalculateLineEquation(vector2 start, vector2 direction, int depth)
{
    materialx = 0;
    materialy = 0;
    maxDepthl = depth;
    rayVector = direction;
    //x and y variables represent values for searching for x facing sides or y facing sides of boxes
    //-----------------------------------------------

    //how may units searched looking for each face
    xstep = 0;
    ystep = 0;

    //will always be a whole number, decimal will be invalid and not counted (never hit a box)
    Foundx = 0.1f;
    Foundy = 0.1f;

    //set hypotenuse to unrealistic value so we can tell if a box was never hit while looking for that direction of faces
    xhyp = -1;
    yhyp = -1;

    //Y = MX + B
    //M = rise over run
    M = rayVector.Y / rayVector.X;
    B = start.Y - M * start.X;

    //shoot ray until max distance reached
    for (int i = 0; i < maxDepthl; i++)
    {
        //while we have hit nothing in a direction, keep searching it
        if (Foundx == 0.1f)
        {
            if (xhyp <= yhyp) {
                StepX(start);
            }

        }
        if (Foundy == 0.1f)
        {
            if (xhyp >= yhyp) {
                SetpY(start);
            }

        }
        
    }

    //once we have searched we decide which collision was closest, that is the one that will be displayed
    //------------------------------------------

    //which collision was has the smalled hypotenuse (magnitude)
    if (Foundx == 0.1f) {
        FaceY();
        collOffset = foundx;
        return yhyp;   
    }
    if (Foundy == 0.1f) {
        FaceX();
        collOffset = foundy;
        return xhyp;
    }
    if (xhyp < yhyp)
    {
        //shortest collision was on the x facing side of a box
        FaceX();
        collOffset = foundy;
        return xhyp;
    }
    else
    {
        //shortest collision was on the y facing side of a box
        FaceY();
        collOffset = foundx;
        return yhyp;;
    }
}

void NicRay::FaceX() {
    faceDirection = 4;
    foundMaterial = materialx;
    if (rayVector.X < 0)
    {
        faceDirection = 1;
    }
}

void NicRay::FaceY() {
    faceDirection = 2;
    foundMaterial = materialy;
    if (rayVector.Y < 0)
    {
        faceDirection = 3;
    }
}

//find intrsects on x axis gridlines
void NicRay::StepX(vector2 playerPos)
{

    int checkdir = 1; //are we going psitive of negitive

    if (rayVector.X < 0)
    {
        checkdir = -1;
    }
    else //if going +ve increment before calculations
    {
        xstep += checkdir;
    }


    //next x is x position plus steps, snapped to the grid (floored to int)
    int nextx = floor(playerPos.X) + xstep;

    //find the height on our rays line equation
    foundy = M * nextx + B;

    //the point at the x,y when solved in the equation
    vector2 destPos = vector2(nextx, foundy);

    //if going -ve, serch backwards or a grid collision
    int target = nextx;
    if (checkdir == -1)
    {
        target -= 1;
    }

    //mag is a^2 + b^2 == c^2

    //ComputeAdditionVector(destPos, playerPos, -1);
    xhyp = (destPos - playerPos).magnitude();//VectorMagnitude(AdditionVector);
    int gridy = floor(foundy);

    //make sure our position is valid before checking grid space  
    bool withinYRange = gridy >= 0 && gridy < Map::Level1Size[0];
    bool withinXDomain = target >= 0 && target < Map::Level1Size[0];
    if (withinYRange && withinXDomain)
    {
        //if the tile is not empty (0), we hit it
        if (Map::Level1[gridy][target] != 0)
        {
            Foundx = target;
            if (materialx == 0) { materialx = Map::Level1[gridy][target]; }
        }
    }

    //if going -ve increment after calculations
    if (rayVector.X < 0)
    {
        xstep += checkdir;
    }


}

//find intrsects on y axis gridlines
void NicRay::SetpY(vector2 playerPos)
{

    int checkdir = 1; //are we going psitive of negitive

    if (rayVector.Y < 0)
    {
        checkdir = -1;
    }
    else //if going +ve increment before calculations
    {
        ystep += checkdir;
    }

    //next y is y position plus steps, snapped to the grid (floored to int)
    int nexty = floor(playerPos.Y) + ystep;

    //get x as a fucntion of y
    foundx = (nexty - B) / M;

    //where that puts us in world space
    vector2 destPos = vector2(foundx, nexty);

    int target = nexty;
    if (checkdir == -1)
    {
        target -= 1;
    }

    //mag is a^2 + b^2 == c^2
    //ComputeAdditionVector(destPos, playerPos, -1);
    yhyp = (destPos - playerPos).magnitude();//VectorMagnitude(AdditionVector);
    int gridx = floor(foundx);

    //make sure our position is valid before checking grid space
    bool withinXDomain = gridx >= 0 && gridx < Map::Level1Size[1];
    bool withinYRange = target >= 0 && target < Map::Level1Size[0];
    if (withinXDomain && withinYRange)
    {
        //if the tile is not empty (0), we hit it
        if (Map::Level1[target][gridx] != 0)
        {
            Foundy = target;
            if(materialy == 0){ materialy = Map::Level1[target][gridx]; }

        }
    }

    //if going -ve increment after calculations
    if (rayVector.Y < 0)
    {
        ystep += checkdir;
    }

}