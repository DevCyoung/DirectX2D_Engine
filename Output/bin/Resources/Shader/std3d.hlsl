
#ifndef _STD3D
#define _STD3D

#include "Header//Struct.fxh"
#include "Header//ConstantBuffer.fxh"
#include "Header//Sampler.fxh"
#include "Header//Texture.fxh"

//static float3 g_vLightPos = float3(0.f, 0.f, 0.f);
//static float3 g_vLightDir = float3(1.f, -1.f, 1.f);

//static float3 g_vLightColor = float3(1.f, 1.f, 1.f);
//static float g_fLightSpecCoeff = 0.3f;
//static float3 g_vLightAmb = float3(0.15f, 0.15f, 0.15f); // 환경광

struct VS_IN
{
	float3 vPos : POSITION;
	float2 vUV : TEXCOORD;
    
	float3 vNormal : NORMAL;
	float3 vTangent : TANGENT;
	float3 vBinormal : BINORMAL;
	
	float4 vWeights : BLENDWEIGHT;
	float4 vIndices : BLENDINDICES;
};

struct VS_OUT
{
	float4 vPosition : SV_Position;
	float2 vUV : TEXCOORD;
    
	float3 vViewPos : POSITION;
	
	float3 vViewNormal : NORMAL;
	float3 vViewTangent : TANGENT;
	float3 vViewBinormal : BINORMAL;
    
};


// Animation3D Bone Matrix Buffer
StructuredBuffer<Matrix> g_arrBoneMat : register(t30);

matrix GetBoneMat(int _iBoneIdx, int _iRowIdx)
{
	return g_arrBoneMat[(g_iBoneCount * _iRowIdx) + _iBoneIdx];
}

struct tSkinningInfo
{
	float3 vPos;
	float3 vTangent;
	float3 vBinormal;
	float3 vNormal;
};

void Skinning(inout float3 _vPos, inout float3 _vTangent, inout float3 _vBinormal, inout float3 _vNormal
    , inout float4 _vWeight, inout float4 _vIndices
    , int _iRowIdx)
{
	tSkinningInfo info = (tSkinningInfo) 0.f;

	if (_iRowIdx == -1)
		return;

	for (int i = 0; i < 4; ++i)
	{
		if (0.f == _vWeight[i])
			continue;

		matrix matBone = GetBoneMat((int) _vIndices[i], _iRowIdx);

		info.vPos += (mul(float4(_vPos, 1.f), matBone) * _vWeight[i]).xyz;
		info.vTangent += (mul(float4(_vTangent, 0.f), matBone) * _vWeight[i]).xyz;
		info.vBinormal += (mul(float4(_vBinormal, 0.f), matBone) * _vWeight[i]).xyz;
		info.vNormal += (mul(float4(_vNormal, 0.f), matBone) * _vWeight[i]).xyz;
	}

	_vPos = info.vPos;
	_vTangent = normalize(info.vTangent);
	_vBinormal = normalize(info.vBinormal);
	_vNormal = normalize(info.vNormal);
}


VS_OUT VS_Std3D(VS_IN _in)
{
	VS_OUT output = (VS_OUT) 0.f;
        
	if (g_iAnim)
	{
		Skinning(_in.vPos, _in.vTangent, _in.vBinormal, _in.vNormal, _in.vWeights, _in.vIndices, 0);
	}
	
    // 로컬에서의 Normal 방향을 월드로 이동    
	output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    
	output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV)).xyz;
	output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), g_matWV)).xyz;
	output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV)).xyz;
       
	output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
	output.vUV = _in.vUV;
      
	return output;
}

float4 PS_Std3D(VS_OUT _in) : SV_Target
{
	float4 vOutColor = float4(0.5f, 0.5f, 0.5f, 1.f);
        
	float3 vViewNormal = _in.vViewNormal;
    
	if (g_btex_0)
	{
		vOutColor = MeshRenderer00.Sample(pointSampler, _in.vUV);
	}
    
	if (g_btex_1)
	{
		float3 vNormal = MeshRendererNormal.Sample(pointSampler, _in.vUV).xyz;
        
        // 0 ~ 1 범위의 값을 -1 ~ 1 로 확장        
		vNormal = vNormal * 2.f - 1.f;
        
		float3x3 vRotateMat =
		{	
			_in.vViewTangent,
            -_in.vViewBinormal,
            _in.vViewNormal
		};
        
		vViewNormal = mul(vNormal, vRotateMat);
	}
		
    
        
	//ViewSpace 에서의
	//광원의 방향
	float3 vViewLightDir = normalize(mul(float4(normalize(LIGHT_DIR.xyz), 0.f), g_matView)).xyz;
	
    
    // ViewSpace 에서의 노말벡터와 광원의 방향을 내적 (램버트 코사인 법칙)
	float fLightPow = saturate(dot(vViewNormal, -vViewLightDir));
    
    // 반사광
	float3 vViewReflect = normalize(vViewLightDir + 2.f * (dot(-vViewLightDir, vViewNormal)) * vViewNormal);
	float3 vEye = normalize(_in.vViewPos);
   
    // 반사광의 세기 구하기
	float fSpecPow = saturate(dot(vViewReflect, -vEye));
	fSpecPow = pow(fSpecPow, 40.f);
           
	vOutColor.xyz = (vOutColor.xyz * LIGHT_COLOR.xyz * fLightPow)
                    + (vOutColor.xyz * LIGHT_COLOR.xyz * LIGHT_AMB.xyz)	
                    + LIGHT_COLOR.xyz * LIGHT_SPEC_COEFF * fSpecPow;
	
	return vOutColor;
}
#endif