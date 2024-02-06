#pragma once

struct alignas(16) tCBTransform // b0
{
	Matrix World;
	Matrix View;
	Matrix Proj;

	Matrix WV;
	Matrix WVP;
}; // 80 bytes


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
	Vector4 Diffuse;	// 빛의 색상
	Vector4 Ambient;	// 주변 광(환경 광)
	Vector4 Specular; // 반사광 세기
};

// LightInfo
struct alignas(16) tLightInfo // b4
{
	tLightColor Color;		 // 빛의 색상

	Vector4		WorldPos;   // 광원의 월드 스페이스 위치
	Vector4		WorldDir;	 // 빛을 보내는 방향

	UINT		LightType;   // 빛의 타입(방향성, 점, 스포트)
	float		Radius;		 // 빛의 반경(사거리)
	float		Angle;		 // 빛의 각도
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

struct alignas(16) tMaterial // b7
{
	// 재질 계수
	Vector4 g_vDiff;
	Vector4 g_vSpec;
	Vector4 g_vAmb;
	Vector4 g_vEmv;

	// 재질 상수
	int g_int_0;
	int g_int_1;
	int g_int_2;
	int g_int_3;

	float g_float_0;
	float g_float_1;
	float g_float_2;
	float g_float_3;

	Vector2 g_vec2_0;
	Vector2 g_vec2_1;
	Vector2 g_vec2_2;
	Vector2 g_vec2_3;

	Vector4 g_vec4_0;
	Vector4 g_vec4_1;
	Vector4 g_vec4_2;
	Vector4 g_vec4_3;

	Matrix g_mat_0;
	Matrix g_mat_1;
	Matrix g_mat_2;
	Matrix g_mat_3;

	int g_btex_0;
	int g_btex_1;
	int g_btex_2;
	int g_btex_3;
	int g_btex_4;
	int g_btex_5;
	int g_btex_6;
	int g_btex_7;
	int g_btexcube_0;
	int g_btexcube_1;
	int g_btexarr_0;
	int g_btexarr_1;

	// 3D Animation 정보
	int                 g_iAnim;
	int                 g_iBoneCount;
	int                 padding[2];
};

//static float3 g_vLightPos = float3(0.f, 0.f, 0.f);
//static float3 g_vLightDir = float3(1.f, -1.f, 1.f);
//
//static float3 g_vLightColor = float3(1.f, 1.f, 1.f);
//static float g_fLightSpecCoeff = 0.3f;
//static float3 g_vLightAmb = float3(0.15f, 0.15f, 0.15f); // 환경광
//짝수단위로
struct /*alignas(16)*/ tLight3DInfo
{
	Vector4 LightPos;
	Vector4 LightDir;

	Vector4 LightColor;
	Vector4 LightAmb;
	
	float	LightSpecCoeff;
	int		pad[3];
};

// Material 계수
struct tMtrlData
{
	Vector4 vDiff;
	Vector4 vSpec;
	Vector4 vAmb;
	Vector4 vEmv;
};
