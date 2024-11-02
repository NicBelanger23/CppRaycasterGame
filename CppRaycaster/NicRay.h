#pragma once
class NicRay
{
    private:
        float angle;
        int maxDepthl;

        float Angle;
        float M;
        float B;
        float rayVector[3];


        float xhyp = 0;
        int xstep = 0;
        float Foundx = 0.1f;
        float foundy;

        float yhyp = 0;
        int ystep = 0;
        float Foundy = 0.1f;
        float foundx;

        void StepX(float playerPos[3]);
        void SetpY(float playerPos[3]);

        void FaceX();
        void FaceY();

    public:
        float CalculateLineEquation(float playerPos[3], float myangle, int depth);
        int faceDirection;
        float collOffset;
        int foundMaterial;
};