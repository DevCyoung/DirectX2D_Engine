#ifndef CONSTANT_BUFFER_FXH
#define CONSTANT_BUFFER_FXH

cbuffer Transform : register(b0)
{
	row_major matrix B0_World;
	row_major matrix B0_View;
	row_major matrix B0_Projection;
}

cbuffer ColorInfo : register(b1)
{
	int B1_bUseColor;
	float3 B1_dummy;
	float4 B1_cbColor;
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

#endif
