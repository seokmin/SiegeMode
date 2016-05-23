#pragma once

namespace DEF
{
	enum PLAYER_KIND
	{
		PLAYER_RED,
		PLAYER_BLUE
	};

	enum ZORDER_KIND
	{
		ZORDER_BACKGROUND	= 0,
		ZORDER_UNIT			= 1,
		ZORDER_EFFECT		= 2,
		ZORDER_UI			= 3
	};

	enum SCREEN_SIZE
	{
		SCREEN_WIDTH = 1280,
		SCREEN_HEIGHT = 720
	};

	const auto FIGHTING_ZONE = Rect(0.f, 180.f, DEF::SCREEN_WIDTH, 200.f);
};