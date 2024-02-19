#pragma once

enum class eResFbx
{
	house.fbm_SPR_Vill_Warehouse01_Diff,
	house.fbm_SPR_Vill_Warehouse01_Norm,
	house.fbm_SPR_Vill_Warehouse01_Spec,
	house.fbm_SPR_Vill_Warehouse02_Norm,
	house.fbm_SPR_Vill_Warehouse03_Diff,
	house.fbm_SPR_Vill_Warehouse03_Spec,
	monster.fbm_CH_NPC_MOB_Anashar_A01_Lower_D_KGW,
	monster.fbm_CH_NPC_MOB_Anashar_A01_Lower_N_KGW,
	monster.fbm_CH_NPC_MOB_Anashar_A01_Lower_SP_KGW,
	monster.fbm_CH_NPC_MOB_Anashar_A01_Shoulder_D_KGW,
	monster.fbm_CH_NPC_MOB_Anashar_A01_Shoulder_N_KGW,
	monster.fbm_CH_NPC_MOB_Anashar_A01_Shoulder_SP_KGW,
	monster.fbm_CH_NPC_MOB_Anashar_A01_Upper_D_KGW,
	monster.fbm_CH_NPC_MOB_Anashar_A01_Upper_N_KGW,
	monster.fbm_CH_NPC_MOB_Anashar_A01_Upper_SP_KGW,
	monster.fbm_CH_NPC_MOB_Anashar_Weapon_A01_D_KGW,
	monster.fbm_CH_NPC_MOB_Anashar_Weapon_A01_N_KGW,
	monster.fbm_CH_NPC_MOB_Anashar_Weapon_A01_SP_KGW,
	black,
	c7100,
	c9990,
	Dragon,
	house,
	monster,
	sphere,
	Spider,
	Spider_2,
	Spider_3,
	End
};

const wchar_t* EnumResourcePath(eResFbx type);

