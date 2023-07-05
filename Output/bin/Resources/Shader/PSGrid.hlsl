#include "Header//Struct.fxh"
#include "Header//Sampler.fxh"
#include "Header//Texture.fxh"
#include "Header//ConstantBuffer.fxh"

float4 main(tVSOut In) : SV_TARGET
{
	float4 color = float4(0.1f, 0.3f, 0.7f, 1.0f);
	
	int2 normalXY = int2(In.UV * cbScale + 1);
	
	int2 width = int2(cbScale.xy / cbXYCount.xy);
	int2 mouseIdx = int2( (cbMousePos.xy - 1) / width.xy);
	int2 gridIdx  = int2( (normalXY.xy	 - 1 )/ width.xy);

	if (mouseIdx.y == gridIdx.y && mouseIdx.x == gridIdx.x)
	{
		color = float4(1.0f, 0.0f, 0.f, 0.8f);
	}
	else if (normalXY.x % width.x >= 2 && normalXY.y % width.y >= 2)
	{
		discard;
	}

	return color;
}