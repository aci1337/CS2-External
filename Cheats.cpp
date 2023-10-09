#include "Cheats.h"
#include "Render.hpp"
#include "Cheats.h"
#include "Render.hpp"
float DistanceToSight = 0;
float MaxAimDistance = 100000;
Vec3  AimPos{ 0,0,0 };

void RenderEntity(const CEntity& entity, const Vec3& aimPos)
{
    // Render bone, LOS line, 2D rect, and health bar for the entity.
    Render::DrawBone(entity, ImColor(255, 255, 255, 255), 1.3);
    Render::ShowLosLine(entity, 50, ImColor(255, 0, 0, 255), 1.3);
    auto Rect = Render::Draw2DBoneRect(entity, ImColor(255, 255, 255, 255), 1.3);

}
void ProcessEntities()
{

    CEntity LocalEntity;
    DWORD64 LocalControllerAddress = 0;

    if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
        return;

    if (!LocalEntity.Update(LocalControllerAddress))
        return;

    static std::map<DWORD64, Render::HealthBar> HealthBarMap;
    float MaxAimDistance = 100000;
    Vec3 AimPos{ 0, 0, 0 };

    for (int i = 0; i < 64; i++)
    {
        CEntity Entity;
        DWORD64 EntityAddress = 0;

        if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
            continue;

        if (EntityAddress == LocalEntity.EntityAddress || !Entity.Update(EntityAddress))
            continue;

         if (!Entity.IsAlive() || !Entity.IsInScreen())
            continue;
        if (GetAsyncKeyState(AimControl::HotKey))
        {
            if (AimPos != Vec3(0, 0, 0))
            {
                AimControl::AimBot(LocalEntity, LocalEntity.CameraPos, AimPos);
            }

        }

        // Calculate DistanceToSight and update AimPos as needed.
        float DistanceToSight = Entity.BoneData.BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ Gui.Window.Size.x / 2, Gui.Window.Size.y / 2 });

        if (DistanceToSight < AimControl::AimRange && DistanceToSight < MaxAimDistance)
        {
            MaxAimDistance = DistanceToSight;
            AimPos = Entity.BoneData.BonePosList[BONEINDEX::head].Pos;
        }

        // Perform rendering and other actions for the entity.
        RenderEntity(Entity, AimPos);
    }
}

// Function to render an entity and its related elements.


// Main function to run cheats.
void Cheats::Run()
{
    // Update game matrix and entity list entry.
    if (!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64))
        return;

    gGame.UpdateEntityListEntry();
    ProcessEntities();

    // Check for aim key press and process entities.
}
