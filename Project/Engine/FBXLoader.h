#pragma once
class Mesh;
class GameObject;
#include <FBXLoader/FBXLoadManager.h>

// ============
// Animation 3D
// ============
struct tFrameTrans
{
	Vector4	vTranslate;
	Vector4	vScale;
	Vector4	qRot;
};

struct tMTAnimClip
{
	std::wstring			strAnimName;
	int						iStartFrame;
	int						iEndFrame;
	int						iFrameLength;

	double					dStartTime;
	double					dEndTime;
	double					dTimeLength;
	float					fUpdateTime; // �̰� �Ⱦ�

	FbxTime::EMode			eMode;
};

struct tMTKeyFrame
{
	double	dTime;
	int		iFrame;
	Vector3	vTranslate;
	Vector3	vScale;
	Vector4	qRot;
};

struct tMTBone
{
	std::wstring				strBoneName;
	int							iDepth;
	int							iParentIndx;
	Matrix						matOffset;	// Offset ���(�� -> ��Ʈ ������ ���)
	Matrix						matBone;   // �̰� �Ⱦ�
	std::vector<tMTKeyFrame>	vecKeyFrame;
};

class FBXLoader
{
public:
	static void LoadFBX(const std::wstring& relativePath);
	static void CreateMeshFromFBX();
	static GameObject* FbxInstantiate(const std::wstring& relativePath);
};

