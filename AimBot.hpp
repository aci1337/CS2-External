#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include <random>

namespace AimControl
{
	static int HotKey = VK_LMENU;
	static float AimRange = 600;	
    inline void CalculateViewAngles(const Vec3& AimPos, const Vec3& LocalPos, float& Yaw, float& Pitch)
    {
        Vec3 OppPos = AimPos - LocalPos;

        float Distance = sqrt(pow(OppPos.x, 2) + pow(OppPos.y, 2));

        Yaw = atan2f(OppPos.y, OppPos.x) * 180 / M_PI;

        if (Distance > 0)
        {
            Pitch = -atan(OppPos.z / Distance) * 180 / M_PI;
        }
        else
        {
            Pitch = 0.0f;
        }
    }

	inline void AimBot(const CEntity& Local, Vec3 LocalPos,  Vec3 AimPos)
	{
        float Yaw, Pitch;


        CalculateViewAngles(AimPos, LocalPos, Yaw, Pitch);
        gGame.SetViewAngle(Yaw, Pitch);
    }
}
