﻿#pragma once

enum class eResAudioClip
{
	HeadHunter_circle,
	HeadHunter_dash,
	HeadHunter_groundLazer,
	HeadHunter_headHunterShot,
	HeadHunter_lockon,
	HeadHunter_vanish,
	HeadHunter_wallShot,
	Title_goScene,
	Title_promptGo,
	Title_Skip,
	actorDisinegrate,
	actorDisinegrate2,
	block,
	breakBlock,
	breakPipe,
	breakWood,
	bulletDie,
	bulletHit1,
	bulletHit2,
	bulletHit3,
	bulletWhiz,
	cantThrow,
	doorOpen,
	enemySlice,
	enterGame,
	getItem,
	glassbreak,
	headBloodSpurt,
	headFloor,
	headWall,
	huntressbeam_circle,
	itemThrow,
	knifeDislodge,
	knifeWall,
	levelStart,
	playerCasettePlay,
	playerCasetteRewind,
	PlayerDie,
	playerFootStep,
	playerHeadphones,
	playerJump,
	playerKickDoor,
	playerLand,
	playerLandWire,
	playerPickUp,
	playerPreRun,
	playerRoll,
	playerSwordDraw,
	playerSwordQuickDraw,
	playerWallKick1,
	playerWallKick2,
	playerWallKick3,
	playerWallSlide,
	replayFF,
	replayPause,
	replayPlay,
	replayRew,
	rewind,
	ShieldCopShot,
	slash1,
	slash2,
	slash3,
	slashBullet,
	slomoDisengage,
	slomoEngage,
	song_bossbattle,
	song_chinatown,
	song_fullconfession,
	song_rainonbrick,
	start,
	throwableBullet,
	TitleMenuSkip,
	titleSplash,
	TitleToGame,
	TitleUIClick,
	TransitionBegin,
	TransitionEnd,
	turretActivate,
	turretDeath,
	turretOverheat,
	tvThump,
	End
};

const wchar_t* EnumResourcePath(eResAudioClip type);
