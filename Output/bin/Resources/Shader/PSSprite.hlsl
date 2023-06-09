#include "Header//Struct.fxh"
#include "Header//Sampler.fxh"
#include "Header//Texture.fxh"
#include "Header//ConstantBuffer.fxh"

float4 main(tVSOut In) : SV_TARGET
{
	float4 color = (float) 0.0f;
	color = MeshRenderer00.Sample(pointSampler, In.UV);	
	
	if (color.r == 1.0f && color.g == 0.0f && color.b == 1.0f)
	{
		discard;
	}	
	else if (color.a == 0.f)
	{
		discard;
	}
	
	//Test Module
	if (B1_bUseColor == 1)	
	{		
		if (B1_cbColor.x <= In.UV.x)
		{
			discard;			
		}
		
		float yNormal = (sin(B1_cbColor.y) + 1) / 2.f;
		float width = 0.08f;
	
		if (yNormal - width / 2.f <= In.UV.y && In.UV.y <= yNormal + width / 2.f)
		{
			color.rgba = float4(1.0f, 0.0f, 1.0f, 1.0f);
		}				
	}

	return color;
}