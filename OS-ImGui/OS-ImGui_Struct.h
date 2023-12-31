#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_internal.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxgi.lib")
#include <d3d11.h>

/****************************************************
* Copyright (C)	: Liv
* @file			: OS-ImGui_Struct.h
* @author		: Liv
* @email		: 1319923129@qq.com
* @version		: 1.0
* @date			: 2023/9/17	11:30
****************************************************/

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Vec2
{
public:
	float x, y;
public:
	Vec2() :x(0.f), y(0.f) {}
	Vec2(float x_, float y_) :x(x_), y(y_) {}
	Vec2(ImVec2 ImVec2_) :x(ImVec2_.x), y(ImVec2_.y) {}
	Vec2 operator=(ImVec2 ImVec2_)
	{
		x = ImVec2_.x;
		y = ImVec2_.y;
		return *this;
	}
	Vec2& operator+(Vec2 Vec2_)
	{
		x += Vec2_.x;
		y += Vec2_.y;
		return *this;
	}
	Vec2& operator-(Vec2 Vec2_)
	{
		x -= Vec2_.x;
		y -= Vec2_.y;
		return *this;
	}
	Vec2& operator*(Vec2 Vec2_)
	{
		x *= Vec2_.x;
		y *= Vec2_.y;
		return *this;
	}
	Vec2& operator/(Vec2 Vec2_)
	{
		x /= Vec2_.x;
		y /= Vec2_.y;
		return *this;
	}
	bool operator==(Vec2 Vec2_)
	{
		return x == Vec2_.x && y == Vec2_.y;
	}
	bool operator!=(Vec2 Vec2_)
	{
		return x != Vec2_.x || y != Vec2_.y;
	}
	ImVec2 ToImVec2()
	{
		return ImVec2(x, y);
	}
	float Length()
	{
		return sqrtf(powf(x, 2) + powf(y, 2));
	}
	float DistanceTo(const Vec2& Pos)
	{
		return sqrtf(powf(Pos.x - x, 2) + powf(Pos.y - y, 2));
	}
};

class Vec3
{
public:
	float x, y, z;

	Vec3() : x(0.f), y(0.f), z(0.f) {}
	Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

	// Non-member operator+ for addition.
	friend Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	// Non-member operator- for subtraction.
	friend Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	// Non-member operator* for element-wise multiplication.
	friend Vec3 operator*(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	// Non-member operator/ for element-wise division.
	friend Vec3 operator/(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	bool operator==(const Vec3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator!=(const Vec3& other) const
	{
		return !(*this == other);
	}

	float Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float DistanceTo(const Vec3& Pos) const
	{
		return (*this - Pos).Length();
	}
};


template <typename T>
class Singleton
{
public:
	static T& get()
	{
		static T instance;
		return instance;
	}
};


