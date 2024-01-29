#pragma once
#include "Resource.h"
#include "EnumRenderType.h"
#include "StructVertex.h"

class Shader;
class Texture;

enum TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,
	TEX_6,
	TEX_7,

	TEX_CUBE_0,
	TEX_CUBE_1,

	TEX_ARR_0,
	TEX_ARR_1,

	TEX_END,
};


// Material ���
struct tMtrlData
{
	Vector4 vDiff;
	Vector4 vSpec;
	Vector4 vAmb;
	Vector4 vEmv;
};

struct tMaterialData
{
	tMtrlData mtrl;

	int arrInt[4];
	float arrFloat[4];
	Vector2 arrV2[4];
	Vector4 arrV4[4];
	Matrix arrMat[4];

	// �ؽ��� ���� true / false �뵵
	int arrBTex[(UINT)TEX_PARAM::TEX_END];

	// 3D Animation ����
	int	arrAnimData[4];
};

class Material : public Resource
{	
	friend class GraphicDeviceDX11;
public:
	Material() = default;
	Material(const eRenderPriorityType renderPriorityType);
	virtual ~Material();
	Material(const Material&) = delete;
	Material& operator=(const Material&) = delete;

public:
	const Texture*  GetTexture(const TEX_PARAM param) const 
	{ 
		Assert(mTextures[param], ASSERT_MSG_NULL); return mTextures[param];
	}
	const Shader* GetShader() const { Assert(mShader, ASSERT_MSG_NULL); return mShader; }
	eRenderPriorityType GetRenderType() const { return mRenderType; }

	void SetShader(Shader* const shader) { Assert(shader, ASSERT_MSG_NULL); mShader = shader; }
	void SetTexture(const TEX_PARAM param, Texture* const texture)
	{ 
		Assert(texture, ASSERT_MSG_NULL); mTextures[param] = texture;
	}

	virtual HRESULT Load(const std::wstring& filePath) override final;

	void UpdateData();

	tMaterialData& GetMaterialData() { return mData; }

private:
	Shader*					mShader;	
	tMaterialData           mData;
	Texture*				mTextures[TEX_END];
	eRenderPriorityType		mRenderType;
};
