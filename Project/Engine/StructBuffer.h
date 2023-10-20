#pragma once

struct alignas(16) tCBTransform // b0
{
	Matrix World;
	Matrix View;
	Matrix Proj;
}; // 48 bytes


struct /*alignas(16)*/ tCBColorInfo // b1
{
	int	bUseColor;
	int bColorType;
	Vector2 Dummy;
	Vector4 Color;

	int bSetColorR;
	float R;
	int bSetColorG;
	float G;
	int bSetColorB;
	float B;
	int bSetColorA;
	float A;

	int bMulColorR;
	float MulR;
	int bMulColorG;
	float MulG;
	int bMulColorB;
	float MulB;
	int bMulColorA;
	float MulA;
}; // 32 bytes


struct alignas(16) tCBDebugInfo // b2
{
	Vector3 MouseWorldPos;
	float dummy;
	Vector2 Scale;
	int XYCount[2];

	Vector4 Color_0;
	Vector4 Color_1;
	Vector4 Color_2;
	Vector4 Color_3;

	Vector4 Vector4_0;
	Vector4 Vector4_1;
	Vector4 Vector4_2;
	Vector4 Vector4_3;

}; // 16 bytes


struct alignas(16) tCBAnimationInfo // b3
{
	Vector2 UVBackLeftTop;
	Vector2 UVBackSIze;

	Vector2 UVLeftTop;
	Vector2 UVSize;

	Vector2 UVOffset;
	Vector2 Dummy;
}; // 16 bytes


struct alignas(16) tLightColor
{
	Vector4 Diffuse;	// ���� ����
	Vector4 Ambient;	// �ֺ� ��(ȯ�� ��)
	Vector4 Specular; // �ݻ籤 ����
};

// LightInfo
struct alignas(16) tLightInfo // b4
{
	tLightColor Color;		 // ���� ����

	Vector4		WorldPos;   // ������ ���� �����̽� ��ġ
	Vector4		WorldDir;	 // ���� ������ ����

	UINT		LightType;   // ���� Ÿ��(���⼺, ��, ����Ʈ)
	float		Radius;		 // ���� �ݰ�(��Ÿ�)
	float		Angle;		 // ���� ����
	int			padding;
};

struct alignas(16) tGlobalInfo // b5
{
	Vector2	Resolution;
	float	Deltatime;
	float   GlobalTime;
	float	AccTime;	
	UINT	Light2DCount;
	UINT	Light3DCount;
	int		globalpadding;
};


struct alignas(16) tParticleInfo // 
{
	Vector2	Resolution;
	float	Deltatime;
	float   GlobalTime;
	float	AccTime;
	UINT	Light2DCount;
	UINT	Light3DCount;
	int		globalpadding;
};

struct /*alignas(16)*/ tSprite2DInfo // b5
{
	Vector2 Dummy;
	Vector2 UV;

	int bSetColorR;
	float R;
	int bSetColorG;
	float G;
	int bSetColorB;	
	float B;	
	int bSetColorA;
	float A;


	int bMulColorR;
	float MulR;
	int bMulColorG;
	float MulG;
	int bMulColorB;
	float MulB;
	int bMulColorA;
	float MulA;
};

struct alignas(16) tWaveInfo // b6
{
	float WaveXPower;
	float WaveYPower;
	float WaveSpeed;	
	float dummy2;
};