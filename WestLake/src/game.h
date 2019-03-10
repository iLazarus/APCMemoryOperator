#pragma once
#include <corecrt_math.h>



class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
	{
	}

	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	~Vector3()
	{
	}



	inline Vector3 ToFRotator() //×ª»»µ½½Ç¶È
	{
		float RADPI = (float)(180 / M_PI);
		float Yaw = (float)atan2f(y, x) * RADPI;
		float Pitch = (float)atan2f(z, sqrtf(powf(x, 2.0) + powf(y, 2.0))) * RADPI;
		float Roll = 0;
		return  Vector3(Pitch, Yaw, Roll);
	}

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline float Length()
	{
		return float(sqrtf(powf(x, 2.0) + powf(y, 2.0) + powf(z, 2.0)));
	}

	inline float ToAim()
	{
		return abs(x - 960.000000f) + abs(y - 540.000000f);
	}

	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	Vector3 operator/(float f)
	{
		return Vector3(x / f, y / f, z / f);
	}
	Vector3 operator*(float f)
	{
		return Vector3(x * f, y * f, z * f);
	}
	bool operator==(Vector3 v)
	{

		return ((x == v.x) && (y == v.y) && (z == v.z));
	}
};

class FRotator
{
public:
	FRotator() : Pitch(0.f), Yaw(0.f), Roll(0.f)
	{

	}

	FRotator(float _pitch, float _yaw, float _roll) : Pitch(_pitch), Yaw(_yaw), Roll(_roll)
	{

	}
	~FRotator()
	{

	}
	float Pitch;
	float Yaw;
	float Roll;

	inline double Length()
	{
		return sqrtf(powf(Pitch, 2.0) + powf(Yaw, 2.0) + powf(Roll, 2.0));
	};

	void Clamp()
	{

		if (Pitch > 180)
			Pitch -= 360;

		else if (Pitch < -180)
			Pitch += 360;

		if (Yaw > 180)
			Yaw -= 360;

		else if (Yaw < -180)
			Yaw += 360;

		if (Pitch < -89)
			Pitch = -89;

		if (Pitch > 89)
			Pitch = 89;

		while (Yaw < -180.0f)
			Yaw += 360.0f;

		while (Yaw > 180.0f)
			Yaw -= 360.0f;

		Roll = 0;
		return;
	}

	Vector3  ToVector()
	{
		float radPitch = (float)(Pitch * M_PI / 180.f);
		float radYaw = (float)(Yaw * M_PI / 180.f);

		float SP = (float)sinf(radPitch);
		float CP = (float)cosf(radPitch);
		float SY = (float)sinf(radYaw);
		float CY = (float)cosf(radYaw);

		return  Vector3(CP * CY, CP * SY, SP);
	}

	D3DMATRIX GetAxes()
	{
		auto tempMatrix = Matrix();
		return tempMatrix;
	}

	D3DMATRIX Matrix(Vector3 origin = Vector3(0, 0, 0))
	{

		float radPitch = (Pitch * float(M_PI) / 180.0f);
		float radYaw = (Yaw * float(M_PI) / 180.0f);
		float radRoll = (Roll * float(M_PI) / 180.0f);
		float SP = sinf(radPitch);
		float CP = cosf(radPitch);
		float SY = sinf(radYaw);
		float CY = cosf(radYaw);
		float SR = sinf(radRoll);
		float CR = cosf(radRoll);

		D3DMATRIX matrix;
		matrix.m[0][0] = CP * CY;
		matrix.m[0][1] = CP * SY;
		matrix.m[0][2] = SP;
		matrix.m[0][3] = 0.f;

		matrix.m[1][0] = SR * SP * CY - CR * SY;
		matrix.m[1][1] = SR * SP * SY + CR * CY;
		matrix.m[1][2] = -SR * CP;
		matrix.m[1][3] = 0.f;

		matrix.m[2][0] = -(CR * SP * CY + SR * SY);
		matrix.m[2][1] = CY * SR - CR * SP * SY;
		matrix.m[2][2] = CR * CP;
		matrix.m[2][3] = 0.f;

		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;

		return matrix;
	}

	FRotator operator+(FRotator v)
	{
		return FRotator(Pitch + v.Pitch, Yaw + v.Yaw, Roll + v.Roll);

	}

	FRotator operator-(FRotator v)
	{
		return FRotator(Pitch - v.Pitch, Yaw - v.Yaw, Roll - v.Roll);

	}

	FRotator operator*(FRotator v)
	{
		return FRotator(Pitch * v.Pitch, Yaw * v.Yaw, Roll * v.Roll);

	}

	FRotator operator/(FRotator v)
	{
		return FRotator(Pitch / v.Pitch, Yaw / v.Yaw, Roll / v.Roll);

	}

};

struct FMinimalViewInfo
{
public:

	float FOV;	
	char pad1[0x4];
	Vector3 Location;
	char pad2[0x20];
	FRotator Rotation;
	
};

struct FCameraCacheEntry
{
public:
	float f1;
	float f2;
	float f3;
	float f4;
	struct FMinimalViewInfo  POV;
};

struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};

struct FTransform
{
public:
	FQuat rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

struct PlayerData
{
public:
	uint64_t actor;
	uint64_t root;
	uint64_t mesh;
	bool isVisual;
	Vector3 screen;
	float distance;
	float health;
	float groggyHealth;
};

struct VehicleData {
public:
	Vector3 screen;
	int id;
	float distance;
};

struct ItemsData {
public:
	Vector3 screen;
	int uid;
	float distance;
};