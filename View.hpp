#pragma once
#include "OS-ImGui/OS-ImGui.h"
#include <math.h>
#define M_PI 3.14159265358979323846

// ”Œœ∑ ”Õº¿‡
class CView
{
public:

    float Matrix[4][4]{};

    // Add a new function to apply a spinning transformation
    void ApplySpin(float angleDegrees)
    {
        // Convert the angle to radians
        float angleRadians = angleDegrees * (M_PI / 180.0);

        // Define the spinning matrix
        float spinningMatrix[4][4] = {
            {cos(angleRadians), -sin(angleRadians), 0.0f, 0.0f},
            {sin(angleRadians), cos(angleRadians), 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        };

        // Multiply the current matrix by the spinning matrix
        MatrixMultiply(Matrix, spinningMatrix);
    }

    bool WorldToScreen(const Vec3& Pos, Vec2& ToPos)
    {
        float View = Matrix[3][0] * Pos.x + Matrix[3][1] * Pos.y + Matrix[3][2] * Pos.z + Matrix[3][3];
        if (View <= 0.01)
            return false;

        float SightX = Gui.Window.Size.x / 2;
        float SightY = Gui.Window.Size.y / 2;

        float X = Matrix[0][0] * Pos.x + Matrix[0][1] * Pos.y + Matrix[0][2] * Pos.z + Matrix[0][3];
        float Y = Matrix[1][0] * Pos.x + Matrix[1][1] * Pos.y + Matrix[1][2] * Pos.z + Matrix[1][3];

        ToPos.x = SightX + (X / View) * SightX;
        ToPos.y = SightY - (Y / View) * SightY;

        return true;
    }

    // Helper function for matrix multiplication
    void MatrixMultiply(float A[4][4], float B[4][4])
    {
        float result[4][4];

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result[i][j] = 0.0f;
                for (int k = 0; k < 4; k++) {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        // Copy the result back to Matrix
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                Matrix[i][j] = result[i][j];
            }
        }
    }

};

