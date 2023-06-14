#pragma once

#include <wrl.h>
#include <d3d11.h>
#include "Engine.h"

namespace engine
{
	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		End,
	};

	enum class eCBType
	{
		Transform,
		End,
	};

	class ConstantBuffer
	{
		friend class graphics::GraphicDeviceDX11;

	public:
		ConstantBuffer(const eCBType type, const UINT size);
		virtual ~ConstantBuffer();		

	private:
		eCBType mType;
		D3D11_BUFFER_DESC mDesc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;
	};
}
