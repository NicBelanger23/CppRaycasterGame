#include "vector2.h"
#pragma once
class NicRay
{
    private:
        float angle;
        int maxDepthl;

        float Angle;
        float M;
        float B;
        vector2 rayVector;


        float xhyp = 0;
        int xstep = 0;
        float Foundx = 0.1f;
        float foundy;

        float yhyp = 0;
        int ystep = 0;
        float Foundy = 0.1f;
        float foundx;

        void StepX(vector2 playerPos);
        void SetpY(vector2 playerPos);

        void FaceX();
        void FaceY();

    public:
        float CalculateLineEquation(vector2 start, float myangle, int depth);
        float CalculateLineEquation(vector2 start, vector2 direction, int depth);
        int faceDirection;
        float collOffset;
        int foundMaterial;
};