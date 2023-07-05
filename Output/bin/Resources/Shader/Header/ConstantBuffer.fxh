#ifndef CONSTANT_BUFFER_FXH
#define CONSTANT_BUFFER_FXH

cbuffer Transform : register(b0)
{
	row_major matrix cbWorld;
	row_major matrix cbView;
	row_major matrix cbProjection;
}

cbuffer ColorInfo : register(b1)
{
	int	bUseColor;
	float3 dummy;	
	float4 cbColor;
}

cbuffer GridInfo : register(b2)
{
	float3 cbMousePos;
	float cbGridDummy;	
	float2 cbScale;
	int2 cbXYCount;	
}

#endif
