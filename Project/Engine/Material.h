#pragma once
#include "Resource.h"
#include "EnumRenderType.h"

class Shader;
class Texture;

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
	const Texture*  GetTexture() const { Assert(mTexture, ASSERT_MSG_NULL); return mTexture; }
	const Shader* GetShader() const { Assert(mShader, ASSERT_MSG_NULL); return mShader; }
	eRenderPriorityType GetRenderType() const { return mRenderType; }

	void SetShader(Shader* const shader) { Assert(shader, ASSERT_MSG_NULL); mShader = shader; }
	void SetTexture(Texture* const texture) { Assert(texture, ASSERT_MSG_NULL); mTexture = texture; }

	virtual HRESULT Load(const std::wstring& filePath) override final;

private:
	Shader* mShader;
	Texture* mTexture;
	eRenderPriorityType mRenderType;
};
