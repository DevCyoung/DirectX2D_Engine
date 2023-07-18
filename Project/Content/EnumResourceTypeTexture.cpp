﻿#include "pch.h"
#include "EnumResourceTypeTexture.h"

static constexpr const wchar_t* eResTexturePath[static_cast<UINT>(eResTexture::End)]
{
	L"\\Texture\\charactor\\atlas_zero_black.bmp",
	L"\\Texture\\charactor\\atlas_zero_ori.bmp",
	L"\\Texture\\charactor\\atlas_zero_s.bmp",
	L"\\Texture\\charactor\\atlas_zero_virus.bmp",
	L"\\Texture\\Chinatown01\\spr_chinatown_parallax_1.png",
	L"\\Texture\\Chinatown01\\spr_chinatown_parallax_2.png",
	L"\\Texture\\Chinatown01\\spr_chinatown_parallax_3.png",
	L"\\Texture\\Map\\Chinatown04\\Tilemap.png",
	L"\\Texture\\Map\\Chinatown05\\spr_chinatown_loop_parallax_1.png",
	L"\\Texture\\Map\\Chinatown05\\spr_chinatown_loop_parallax_2.png",
	L"\\Texture\\Map\\Chinatown05\\Tilemap.png",
	L"\\Texture\\Noise\\01.png",
	L"\\Texture\\Noise\\02.png",
	L"\\Texture\\Noise\\03.png",
	L"\\Texture\\Noise\\04.png",
	L"\\Texture\\TileMap\\bg_club_background.png",
	L"\\Texture\\TileMap\\bg_haunted_background.png",
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

