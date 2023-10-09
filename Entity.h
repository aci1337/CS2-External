#pragma once
#include "Game.h"
#include "View.hpp"
#include "Bone.h"

class PlayerController
{
public:
	DWORD64 Address = 0;
	int TeamID = 0;
	int Health = 0;
	int AliveStatus = 0;
	DWORD Pawn = 0;
public:
	bool GetTeamID();
	bool GetHealth();
	bool GetIsAlive();
	DWORD64 GetPlayerPawnAddress();
};

class PlayerPawn
{
public:
	DWORD64 Address = 0;
	CBone BoneData;
	Vec2 ViewAngle;
	Vec3 Pos;
	Vec2 ScreenPos;
	Vec3 CameraPos;
public:
	bool GetPos();
	bool GetViewAngle();
	bool GetCameraPos();
};

class CEntity
{
public:
	PlayerController Controller;
	PlayerPawn Pawn;
public:
	// ��������
	bool UpdateController(const DWORD64& PlayerControllerAddress);
	bool UpdatePawn(const DWORD64& PlayerPawnAddress);
	// �Ƿ���
	bool IsAlive();
	// �Ƿ�����Ļ��
	bool IsInScreen();
	// ��ȡ��������
	CBone GetBone() const;
};