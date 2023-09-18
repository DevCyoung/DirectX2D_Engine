﻿#include "pch.h"
#include "EnumResourceTypeTexture.h"

static constexpr const wchar_t* eResTexturePath[static_cast<UINT>(eResTexture::End)]
{
	L"\\Texture\\Atlas\\Gangster\\gangster.png",
	L"\\Texture\\Atlas\\Player\\ori.png",
	L"\\Texture\\Atlas\\Player\\slash.png",
	L"\\Texture\\Atlas\\Player\\zero.png",
	L"\\Texture\\Atlas\\Title\\Plants.png",
	L"\\Texture\\charactor\\atlas_zero_black.bmp",
	L"\\Texture\\charactor\\atlas_zero_ori.bmp",
	L"\\Texture\\charactor\\atlas_zero_s.bmp",
	L"\\Texture\\charactor\\atlas_zero_virus.bmp",
	L"\\Texture\\Chinatown01\\spr_chinatown_parallax_1.png",
	L"\\Texture\\Chinatown01\\spr_chinatown_parallax_2.png",
	L"\\Texture\\Chinatown01\\spr_chinatown_parallax_3.png",
	L"\\Texture\\Map\\Chinatown01\\spr_chinatown_parallax_1.png",
	L"\\Texture\\Map\\Chinatown01\\spr_chinatown_parallax_2.png",
	L"\\Texture\\Map\\Chinatown01\\spr_chinatown_parallax_3.png",
	L"\\Texture\\Map\\Chinatown01\\Tilemap.png",
	L"\\Texture\\Map\\Chinatown04\\Tilemap.png",
	L"\\Texture\\Map\\Chinatown05\\spr_chinatown_loop_parallax_1.png",
	L"\\Texture\\Map\\Chinatown05\\spr_chinatown_loop_parallax_2.png",
	L"\\Texture\\Map\\Chinatown05\\Tilemap.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_0.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_1.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_10.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_11.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_12.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_13.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_14.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_15.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_16.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_17.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_18.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_19.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_2.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_20.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_21.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_22.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_23.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_24.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_25.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_26.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_27.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_28.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_29.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_3.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_30.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_31.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_32.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_33.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_4.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_5.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_6.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_7.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_8.png",
	L"\\Texture\\Map\\HeadHunter\\spr_vaultdoor_open\\spr_vaultdoor_open_9.png",
	L"\\Texture\\Map\\HeadHunter\\map.png",
	L"\\Texture\\Map\\HeadHunter\\map_alpha.png",
	L"\\Texture\\Noise\\01.png",
	L"\\Texture\\Noise\\02.png",
	L"\\Texture\\Noise\\03.png",
	L"\\Texture\\Noise\\04.png",
	L"\\Texture\\TileMap\\bg_club_background.png",
	L"\\Texture\\TileMap\\bg_haunted_background.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_0.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_1.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_10.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_11.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_2.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_3.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_4.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_5.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_6.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_7.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_8.png",
	L"\\Texture\\Title\\spr_title_plants\\spr_title_plants_9.png",
	L"\\Texture\\Title\\spr_titlegraphic_big2.png",
	L"\\Texture\\Title\\spr_titlegraphic_big_1.png",
	L"\\Texture\\Title\\spr_titlegraphic_big_2.png",
	L"\\Texture\\Title\\spr_title_background.png",
	L"\\Texture\\Title\\spr_title_fence.png",
	L"\\Texture\\Title\\spr_title_grass.png",
	L"\\Texture\\Title\\spr_title_plants_0.png",
	L"\\Texture\\UI\\spr_battery_part.png",
	L"\\Texture\\UI\\spr_cursor.png",
	L"\\Texture\\UI\\spr_hud.png",
	L"\\Texture\\UI\\spr_hud_battery.png",
	L"\\Texture\\UI\\spr_hud_subweapon.png",
	L"\\Texture\\UI\\spr_hud_timer_0.png",
	L"\\Texture\\UI\\spr_hud_timer_1.png",
	L"\\Texture\\UI\\spr_itemicons_0.png",
	L"\\Texture\\UI\\spr_katanaicons_0.png",
	L"\\Texture\\UI\\spr_keyboard_shift_0.png",
	L"\\Texture\\UI\\spr_keyboard_shift_1.png",
	L"\\Texture\\UI\\spr_left_click_1.png",
	L"\\Texture\\UI\\spr_right_click_1.png",
	L"\\Texture\\UI\\spr_timer.png",
	L"\\Texture\\bg_bar_0.png",
	L"\\Texture\\bg_cathedral_background_0.png",
	L"\\Texture\\bg_club_full_0.png",
	L"\\Texture\\bg_dreamshed_0.png",
	L"\\Texture\\bg_studio_outside_0.png",
	L"\\Texture\\chinatown1_test.png",
	L"\\Texture\\door.bmp",
	L"\\Texture\\map.png",
	L"\\Texture\\orange.bmp",
	L"\\Texture\\spr_bg_neighbor_apartment_0.png",
	L"\\Texture\\TILE.bmp",
	L"\\Texture\\walk.bmp",
};

const wchar_t* EnumResourcePath(eResTexture type)
{
	return eResTexturePath[static_cast<UINT>(type)];
}

