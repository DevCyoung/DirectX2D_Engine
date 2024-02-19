#include "pch.h"
#include "EnumResourceTypeFbx.h"

static constexpr const wchar_t* eResFbxPath[static_cast<UINT>(eResFbx::End)]
{
	L"\\Fbx\\house.fbm\\SPR_Vill_Warehouse01_Diff.tga",
	L"\\Fbx\\house.fbm\\SPR_Vill_Warehouse01_Norm.tga",
	L"\\Fbx\\house.fbm\\SPR_Vill_Warehouse01_Spec.tga",
	L"\\Fbx\\house.fbm\\SPR_Vill_Warehouse02_Norm.tga",
	L"\\Fbx\\house.fbm\\SPR_Vill_Warehouse03_Diff.tga",
	L"\\Fbx\\house.fbm\\SPR_Vill_Warehouse03_Spec.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_A01_Lower_D_KGW.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_A01_Lower_N_KGW.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_A01_Lower_SP_KGW.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_A01_Shoulder_D_KGW.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_A01_Shoulder_N_KGW.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_A01_Shoulder_SP_KGW.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_A01_Upper_D_KGW.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_A01_Upper_N_KGW.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_A01_Upper_SP_KGW.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_Weapon_A01_D_KGW.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_Weapon_A01_N_KGW.tga",
	L"\\Fbx\\monster.fbm\\CH_NPC_MOB_Anashar_Weapon_A01_SP_KGW.tga",
	L"\\Fbx\\black.FBX",
	L"\\Fbx\\c7100.fbx",
	L"\\Fbx\\c9990.fbx",
	L"\\Fbx\\Dragon.fbx",
	L"\\Fbx\\house.fbx",
	L"\\Fbx\\monster.fbx",
	L"\\Fbx\\sphere.fbx",
	L"\\Fbx\\Spider.fbx",
	L"\\Fbx\\Spider_2.fbx",
	L"\\Fbx\\Spider_3.fbx",
};

const wchar_t* EnumResourcePath(eResFbx type)
{
	return eResFbxPath[static_cast<UINT>(type)];
}

