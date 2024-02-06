#ifndef CONSTANT_BUFFER_FXH
#define CONSTANT_BUFFER_FXH

cbuffer Transform : register(b0)
{
	row_major matrix g_matWorld;
	row_major matrix g_matView;
	row_major matrix g_matProj;
    
	row_major matrix g_matWV;
	row_major matrix g_matWVP;
}

cbuffer Transform : register(b1)
{
	row_major matrix B0_World;
	row_major matrix B0_View;
	row_major matrix B0_Projection;
	
	row_major matrix B0_WV;
	row_major matrix B0_WVP;
}


cbuffer ColorInfo : register(b1)
{
	int B1_bUseColor;
	int B1_ColorType;
	float2 B1_dummy;	
	float4 B1_cbColor;
	
	int B1_bSetColorR;
	float B1_R;
	int B1_bSetColorG;
	float B1_G;
	int B1_bSetColorB;
	float B1_B;
	int B1_bSetColorA;
	float B1_A;
	
	
	int B1_bMulColorR;
	float B1_MulR;
	int B1_bMulColorG;
	float B1_MulG;
	int B1_bMulColorB;
	float B1_MulB;
	int B1_bMulColorA;
	float B1_MulA;
}

cbuffer DebugInfo : register(b2)
{
	float3 B2_MousePos;
	float B2_GridDummy;
	float2 B2_Scale;
	int2 B2_XYCount;
	
	float4 B2_Color_0;
	float4 B2_Color_1;
	float4 B2_Color_2;
	float4 B2_Color_3;
	
	float4 B2_Vector4_0;
	float4 B2_Vector4_1;
	float4 B2_Vector4_2;
	float4 B2_Vector4_3;
}

cbuffer Animation2DInfo : register(b3)
{
	float2 B3_UVBackLeftTop;
	float2 B3_UVBackSIze;

	float2 B3_UVLeftTop;
	float2 B3_UVSize;

	float2 B3_UVOffset;
	float2 B3_Dummy;
}

cbuffer GLOBAL : register(b4)
{
	float2 B4_Resolution;
	float B4_DT;
	float B4_GlobalTime;
	float B4_AccTime;
	uint B4_Light2DCount;
	uint B4_Light3DCount;
	int B4_globalpadding;
}

cbuffer Sprite2D : register(b5)
{
	float2 B5_Dummy;	
	float2 B5_SpriteUV;
	
	int B5_bSetColorR;
	float B5_R;
	int B5_bSetColorG;
	float B5_G;
	int B5_bSetColorB;
	float B5_B;
	int B5_bSetColorA;
	float B5_A;
	
	
	int B5_bMulColorR;
	float B5_MulR;
	int B5_bMulColorG;
	float B5_MulG;
	int B5_bMulColorB;
	float B5_MulB;
	int B5_bMulColorA;
	float B5_MulA;
}

cbuffer Wave : register(b6)
{
	float B6_WaveXPower;	
	float B6_WaveYPower;
	float B6_WaveSpeed;
	float B6_dummy1;
}


cbuffer MATERIAL : register(b7)
{
    // 재질 계수
	float4 g_vDiff;
	float4 g_vSpec;
	float4 g_vAmb;
	float4 g_vEmv;

    // 재질 상수
	int g_int_0;
	int g_int_1;
	int g_int_2;
	int g_int_3;
    
	float g_float_0;
	float g_float_1;
	float g_float_2;
	float g_float_3;
    
	float2 g_vec2_0;
	float2 g_vec2_1;
	float2 g_vec2_2;
	float2 g_vec2_3;

	float4 g_vec4_0;
	float4 g_vec4_1;
	float4 g_vec4_2;
	float4 g_vec4_3;
    
	row_major matrix g_mat_0;
	row_major matrix g_mat_1;
	row_major matrix g_mat_2;
	row_major matrix g_mat_3;
    
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
	int g_iAnim;
	int g_iBoneCount;
	int2 padding;
};
//52 + 12
cbuffer GlobalLight3D : register(b8)
{
	float4	LIGHT_POS;
	float4	LIGHT_DIR;

	float4	LIGHT_COLOR;
	float4	LIGHT_AMB;
	
	float	LIGHT_SPEC_COEFF;
	int3	pad;
};

#endif
