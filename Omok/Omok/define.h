#pragma once

enum class GROUP_TYPE
{
	DEFAULT,
	BACK_GROUND,
	BOARD,
	STONE,

	UI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	INGAME,

	END,
};

constexpr int OMOK_BALL_SIZE = 22;
constexpr int OMOK_BOARD_COUNT = 18;

constexpr int OMOK_BOARD_SIZE_X = 38;
constexpr int OMOK_BOARD_SIZE_Y = 36;

enum class EVENT_TYPE
{
	CREATE_OBJECT,

	END,
};

enum class GAME_STATE
{
	PLAY,
	PAUSE,
	VICTORY,
	END
};

enum class STONE_INFO
{
	NONE,
	BLACK,
	WHITE,
};

enum class BRUSH_TYPE
{
	WOOD,
	BLACK,
	HOLLOW,

	END,
};

enum class PEN_TYPE
{
	GREEN,
	RED,

	END,
};